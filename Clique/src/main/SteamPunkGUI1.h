/*
 *SteamPunkGUI1.h
 *
 * Description:
 * This class contains functions relating to the creation and user
 * interaction with the main window of the GUI/application.
 *
 * Copyright (C) 2020 ASU
 *	Matthew Cilibraise, Myles Colina, Cristi DeLeo, Elizabeth Marquise, Sean Rogers,
 *	initial idea contributed by Douglas Sandy, All rights reserved
 *
 *
 * List of functions:
 *	void SteamPunkGUI1(void)
 *		- Constructor, sets up basic framework for the GUI
 *
 *	constexpr int toConstInt(int)
 *		- takes an int and returns it as a const
 *
 * ~void SteamPunkGUI1(void)
 *		- Destructor, sets up basic framework for the GUI
 *
 *	GearsAnimate(Fl_Window *w, Fl_Box *b, Fl_Box *b2)
 *		- Animates gears on steam punk window
 *
 *	void MainWindow2()
 *		- second Constructor, sets up basic framework for the GUI
 *
 *	void TeamsButtonClick(Fl_Window *w)
 *		- takes the inputs from the input boxes, and passes them to the
 *	    main Team assignment class, creates a new window with a progress bar.
 *
 *	void cookieLoadSP(Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar)
 *		- Circles cookie images until progress bar reaches 100%
 *
 *	animateSP(Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar,
 *		Fl_PNG_Image *loadingPngs[23], Fl_Box *b2, Fl_Box *b3)
 *		- Circles given image until progress bar reaches 100%
 *
 *	void ProgressTeamsButtonClick(Fl_Window *w)
 *		- Takes the inputs and passes them to the main Team assignment class.
 *
 *	void okClick(Fl_Widget *w)
 *		- hides last window when "okay" is clicked
 *
 *	void errorMessage(void)
 *		- Pops up an error message if # project/students do not meet min requirements
 *
 *	void DoneButtonClick(Fl_Widget *w)
 *		- When the Done button is clicked, the results window is opened.
 *
 *	void destroyWindowCb1(GtkWidget *widget, GtkWidget *window)
 *		- callback when the window is closed via the close button
 *
 *	gboolean closeWebViewCb1(WebKitWebView *webView, GtkWidget *window)
 *		- callback when the window is closed via the close button
 *
 *	 void getCookiesCB1(WebKitCookieManager *manager,GAsyncResult *asyncResult)
 *		- Finishes getting the cookies from the mini-browser session. Takes in the
 *		data in a Glist, and loops over the contents type casting to a soupcookie
 *		and storing it in a vector to pass to the libcurl HTTP request functions.
 *
 *	static gboolean load_changedWebViewCb1(WebKitWebView *webView,GtkWidget *window)
 *		- listens for a change in the url in the mini-browser, & exits reaches the login
 *		success page, calls the cookie manager get cookies function to get the incoming cookies
 *
 *	void mini_browserSP(void)
 *		- creates a mini-browser session so the user can authenticated, stores cookies
 *
 *	void StartButtonClick(Fl_Widget *w)
 *		- When the Start button is clicked, Opens the next GUI window.
 *
 *	int MainWindow::handle(int event)
 *		- changes different logos on different events
 *
 *	void MainWindow::callTeams(Fl_Widget *w)
 *		- event handler to create teams
 */
#ifndef SRC_MAIN_STEAMPUNKGUI1_H_
#define SRC_MAIN_STEAMPUNKGUI1_H_


/********* BEGINNING OF INCLUSIONS **********/


/* Class Inclusions */
#include "Student.h"
#include "ClassSection.h"


/* Library Inclusions */
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <libsoup/soup.h>


/* FLTK Inclusions */
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/names.h>


using namespace std;


 /********* BEGINNING OF PROGRAM CODE **********/



class SteamPunkGUI1 {

	//generate teams 'static' callback function
	//this function calls the real TeamsButtonClick callback function.
	static void static_TeamsButtonClick(Fl_Widget *w, void *data) {
		((SteamPunkGUI1*) data)->TeamsButtonClick(w);
	}

	static void static_ProgressTeamsButtonClick(Fl_Widget *w, void *data) {
		((SteamPunkGUI1*) data)->ProgressTeamsButtonClick(w);
	}

	static void static_DoneButtonClick(Fl_Widget *w, void *data) {
		((SteamPunkGUI1*) data)->DoneButtonClick(w);
	}

	static void static_StartButtonClick(Fl_Widget *w, void *data) {
		((SteamPunkGUI1*) data)->StartButtonClick(w);
	}


	// callback functions
	void ProgressTeamsButtonClick(Fl_Widget *w);
	void DoneButtonClick(Fl_Widget *w);
	void StartButtonClick(Fl_Widget *w);
	int handle(int);
	void TeamsButtonClick(Fl_Widget *w);


public:


	//Static and public variables
	static int num_projects;
	static int num_students;
	static int num_classes;
	int spNumCourses;
	string SPGprojfile;
	vector<Student> studentsFromCanvas;
	bool nextWindowFlag;
	bool Authenticated;
	vector <ClassSection> spCourses;
	vector<vector<Student>> spAllStudents;
	vector <SoupCookie> spCookies;


	//FLTK Declarations

	//progress bar window
	int barCount;
	Fl_Window *progressWindow;
	Fl_Progress *progressBar;
	Fl_Box *progressBox;
	Fl_Button *TeamsButton;
	Fl_Button *doneButton;
	Fl_Box *imageBox;
	Fl_Text_Display *terminalTextDisplay;
	Fl_Text_Buffer *terminalBuffer;

	//main window
	Fl_Window *windowMain;
	Fl_Window *nextWindow;
	Fl_Box *boxHeader;
	Fl_Button *buttonStart;
	Fl_Button *buttonOpenProject;
	Fl_Button *generateTeams;
	Fl_Int_Input *inputprojects;
	Fl_Int_Input *inputstudents;
	Fl_Box *gearBox1;
	Fl_Box *gearBox2;
	Fl_Box *gearBox3;
	Fl_Box *gearBox4;


	// Class functions
	void MainWindow2();
	SteamPunkGUI1();
	~SteamPunkGUI1();
	void callTeams(Fl_Widget *w);

};

#endif /* SRC_MAIN_STEAMPUNKGUI1_H_ */
