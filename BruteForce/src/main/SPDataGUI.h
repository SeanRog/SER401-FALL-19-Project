/*
 * SPDataGUI.h
 *
 * Description:
 *	This class creates the steampunk data entry window for the GUI, including:
 *	- a project file input selector
 *	- a entry for course survey questionnaire
 *	- entry for semester and year to narrow down course selection *
 *
 * Copyright (C) 2020 ASU
 *	Matthew Cilibraise, Myles Colina, Cristi DeLeo, Elizabeth Marquise, Sean Rogers,
 *	initial idea contributed by Douglas Sandy, All rights reserved
 *
 *
 * List of functions:
 * void SteamAnimate(Fl_Window *w, Fl_Box *b, Fl_Box *b2, int end)
 * 		- Circles given image until progress bar reaches 100%
 *
 * 	SPDataGUI(Fl_Window *win, vector<SoupCookie> cookies)
 * 		- Constructor function for the class section selector GUI window
 *
 * ~SPDataGUI
 * 		- Destructor function for the class section selector GUI window
 *
 * FindCoursesClick(Fl_Widget  *w)
 *		- updates the Browser based on the year and semester selected. Then
 *		it searches the course sections for the relevant courses, and displays.
 *
 * GobackClick(Fl_Widget  *w)
 *		- callback for the Go back button, returns to the previous GUI window.
 *
 *	YesClick(Fl_Widget  *w)
 *		- callback for the Confirm button, opens the next GUI window.
 *
 *	CancelClick1(Fl_Widget *w)
 *		- event handler to cancel
 *
 *	CancelClick2(Fl_Widget *w)
 *		- event handler to cancel
 *
 *	ConfirmClick(Fl_Widget *w)
 *		- callback for the Confirm button, opens the next GUI window.
 *
 *	GenerateTeamsClick(Fl_Widget *w)
 *		- event handler for generate teams button
 *
 *	chooseProjectFile_cb(Fl_Widget*)
 *		- event handler for the user to select the project file
 */
#ifndef SRC_MAIN_SPDATAGUI_H_
#define SRC_MAIN_SPDATAGUI_H_


/********* BEGINNING OF INCLUSIONS **********/


/* Class Inclusions */
#include "SteamPunkGUI1.h"
#include "GUIStyles.h"
#include "main.h"
#include "ClassSectionJson.h"
#include "ClassSection.h"


/* Library Inclusions */
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <libsoup/soup.h>
#include <vector>


/* FLTK Inclusions */
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Check_Browser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Native_File_Chooser.H>


using namespace std;


/********* BEGINNING OF PROGRAM CODE **********/


class SPDataGUI {

	//'static' callback functions which call the real callbacks
	static void static_BrowserSelection(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->BrowserSelection(w);
	}

	static void static_FindCoursesClick(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->FindCoursesClick(w);
	}

	static void static_GobackClick(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->GobackClick(w);
	}

	static void static_ConfirmClick(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->ConfirmClick(w);
	}

	static void static_GenerateTeamsClick(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->GenerateTeamsClick(w);
	}

	static void static_CancelClick1(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->CancelClick1(w);
	}

	static void static_CancelClick2(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->CancelClick2(w);
	}

	static void static_YesClick(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->YesClick(w);
	}
	static void static_chooseProjectFile_cb(Fl_Widget *w, void *data) {
		((SPDataGUI*) data)->chooseProjectFile_cb(w);
	}


	//callback functions
	void BrowserSelection(Fl_Widget *w);
	void FindCoursesClick(Fl_Widget *w);
	void GobackClick(Fl_Widget *w);
	void ConfirmClick(Fl_Widget *w);
	void YesClick(Fl_Widget *w);
	void CancelClick1(Fl_Widget *w);
	void CancelClick2(Fl_Widget *w);
	void GenerateTeamsClick(Fl_Widget *w);
	void chooseProjectFile_cb(Fl_Widget *w);


public:


	// Variables
	string *AllCourseNames;
	string *SelectedCourseNames;
	ClassSection *AllCourses;
	ClassSection *SelectedCourses;
	int num_of_all_courses;
	int num_of_selected_courses;
	int course_count;
	//string array of courses for use in testing.
	string courses[17] = { "2020Fall-X-SER401-90586", "2019Fall-X-SER401-80888",
			"2020Fall-X-SER401-84566", "2019Fall-X-SER401-91286",
			"2020Fall-X-SER401-70346", "2018Fall-X-SER401-65686",
			"2018Fall-X-SER401-52586", "2020Spring-X-SER401-43586",
			"2020Spring-X-SER401-65686", "2018Spring-X-SER401-93286",
			"2020Spring-X-SER401-45586", "2019Fall-X-SER486-21686",
			"2019Fall-X-SER455-10286", "2019Fall-X-SER423-45336",
			"2018Summer-X-SER530-14186", "2019Summer-X-SER219-10986",
			"2020Summer-X-SER323-55536", };


	// FLTK Declarations
	Fl_Window *masterWindow;
	Fl_Window *prevWindow;
	Fl_Box *steamBox1;
	Fl_Box *steamBox2;


	//Class Section Selector Components
	Fl_Box *boxHeader;
	Fl_Box *boxHeader2;
	Fl_Check_Browser *classBrowser;
	Fl_Button *findCourses;
	Fl_Button *Confirm;
	Fl_Button *goBack;
	Fl_Input *inputYear;
	Fl_Input_Choice *inputSemester;
	Fl_Box *classSectionInstructionsBox;
	Fl_Scroll *scroll;


	//Go Back window Components
	Fl_Window *backWindow;
	Fl_Button *yesButton;
	Fl_Button *cancelButton1;


	//Go Back window Components
	Fl_Window *confirmWindow;
	Fl_Button *GenerateTeamsButton;
	Fl_Button *cancelButton2;


	//Choose Project File Components
	Fl_Box *projectFileInstructionsBox;
	Fl_Button *projectFileChooserButton;
	Fl_Input *fileInput_Project;


	//Enter Student Survey Quiz Components
	Fl_Box *quizFileInstructionsBox;
	Fl_Input *fileInput_StudentQuizName;


	// Confirm or Go Back
	Fl_Box *goBackorConfirmInstructionsBox;


	// Class Constructor and Destructor
	SPDataGUI(Fl_Window *win, vector<SoupCookie> cookiedata);
	virtual ~SPDataGUI();

};

#endif /* SRC_MAIN_SPDATAGUI_H_ */
