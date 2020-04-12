/*
 * MainWindow.h
 *
 * Description:
 *	This class creates the main window that pops up on startup, with 2 tabs:
 *	- HOME:
 *		- Gives ASU logo and start button to click and begin the application
 *		- For testing there are two boxes: #Projects and #students to calculate
 *	- ABOUT:
 *		- The left side lists the team members to initially created the assignment
 *		- the right side explains the "why" for the application
 *
 *
 * Copyright (C) 2020 ASU
 *	Matthew Cilibraise, Myles Colina, Cristi DeLeo, Elizabeth Marquise, Sean Rogers,
 *	initial idea contributed by Douglas Sandy, All rights reserved
 *
 *
 * List of functions:
 *	void MainWindow(void)
 *		- Constructor, sets up basic framework for the GUI
 *
 *	constexpr int toConstInt(int)
 *		- takes an int and returns it as a const
 *
 *	void running(Fl_Window *w)
 *		- loops while window is running
 *
 *	void MainWindow2()
 *		- second Constructor, sets up basic framework for the GUI
 *
 *	void TeamsButtonClick(Fl_Window *w)
 *		- takes the inputs from the input boxes, and passes them to the
 *	    main Team assignment class, creates a new window with a progress bar.
 *
 *	void ~MainWindow(void)
 *		- Destructor, properly removes all GUI framework
 *
 *	void cookieLoad(Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar)
 *		- Circles cookie images until progress bar reaches 100%
 *
 *	void animate(Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar,
 *	Fl_PNG_Image *loadingPngs[23])
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
 *	static void destroyWindowCb(GtkWidget *widget, GtkWidget *window)
 *		- callback when the window is closed via the close button
 *
 *	static gboolean closeWebViewCb(WebKitWebView *webView, GtkWidget *window)
 *		- callback when the window is closed via the close button
 *
 *	static void minimizeWindowCb(GtkWidget *widget, GtkWidget *window)
 *		- minimizes last window
 *
 *	void getCookiesCB(WebKitCookieManager *manager,GAsyncResult *asyncResult)
 *		- Finishes getting the cookies from the mini-browser session. Takes in the
 *		data in a Glist, and loops over the contents type casting to a soupcookie
 *		and storing it in a vector to pass to the libcurl HTTP request functions.
 *
 *	void okClick2(Fl_Widget *w)
 *		- hides last window when "okay" is clicked
 *
 *	static gboolean load_changedWebViewCb(WebKitWebView *webView,GtkWidget *window)
 *		- listens for a change in the url in the mini-browser, & exits reaches the login
 *		success page, calls cookie manager get cookies function to get incoming cookies
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
#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_


/********* BEGINNING OF INCLUSIONS **********/


/* Class Inclusions */
#include "Student.h"
#include "ClassSection.h"
#include "main.h"


/* Library Inclusions */
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <vector>


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


class MainWindow {

	 /***** Static event handler functions for buttons *****/
	static void static_TeamsButtonClick(Fl_Widget *w, void *data) {
		((MainWindow*) data)->TeamsButtonClick(w);
	}
	void TeamsButtonClick(Fl_Widget *w);


	static void static_ProgressTeamsButtonClick(Fl_Widget *w, void *data) {
		((MainWindow*) data)->ProgressTeamsButtonClick(w);
	}
	void ProgressTeamsButtonClick(Fl_Widget *w);


	static void static_DoneButtonClick(Fl_Widget *w, void *data) {
		((MainWindow*) data)->DoneButtonClick(w);
	}
	void DoneButtonClick(Fl_Widget *w);


	static void static_StartButtonClick(Fl_Widget *w, void *data) {
		((MainWindow*) data)->StartButtonClick(w);
	}
	void StartButtonClick(Fl_Widget *w);


public:

	/***** public & static variables *****/
	static int num_projects;
	static int num_students;
	static int num_classes;
	int mwNumCourses;
	bool nextWindowFlag;
	bool Authenticated;
	string mwProjfile;
	vector<Student> studentsFromCanvas;
	vector <ClassSection> mwCourses;
	vector<vector<Student>>  mwAllStudents;
	vector <SoupCookie> mwCookies;


	/***** FLTK GUI frames and text boxes *****/
	int barCount;
	Fl_Window *progressWindow;
	Fl_Progress *progressBar;
	Fl_Box *progressBox;
	Fl_Button *TeamsButton;
	Fl_Button *doneButton;
	Fl_Box *imageBox;
	Fl_Text_Display *terminalTextDisplay;
	Fl_Text_Buffer *terminalBuffer;
	Fl_Window *windowMain;
	Fl_Window *nextWindow;
	Fl_Box *boxHeader;
	Fl_Button *buttonStart;
	Fl_Button *buttonOpenProject;
	Fl_Button *generateTeams;
	Fl_Int_Input *inputprojects;
	Fl_Int_Input *inputstudents;


	/***** functions for class *****/
	void MainWindow1();
	void MainWindow2();
	MainWindow();
	~MainWindow();
	void callTeams(Fl_Widget *w);
	int handle(int);

};

#endif /*SRC_MAIN_MAINWINDOW_H_*/
