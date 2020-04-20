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


/********* BEGINNING OF INCLUSIONS **********/


#define WEBVIEW_GTK


/* Class Inclusions */
#include "MainWindow.h"
#include "DataEntryGUI.h"
#include "GUIStyles.h"
#include "ResultWindow.h"
#include "CookieManager.h"
#include "main.h"
#include "webview.h"
#include "Utility.h"


/* Library Inclusions */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <thread>
#include <stdio.h>
#include <vector>
#include <FL/names.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <libsoup/soup.h>
#include <curl/curl.h>


/* FLTK Inclusions */
#include <FL/Fl.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Scroll.H>


using namespace std;


 /********* BEGINNING OF PROGRAM CODE **********/


/***** Declaring static variables from ResultsWindow.cpp *****/
int MainWindow::num_projects = 0;
int MainWindow::num_students = 0;
int MainWindow::num_classes = 0;
Fl_Window *backWindow;
GtkWidget *main_window;


//variables for the mini-browser session static functions
bool Auth;
typedef void *user_data;
vector<SoupCookie> cookiedata;
Fl_Window *backWindow2;
WebKitWebView *webView;

/***** Declaring GUI logos variables for use *****/
/* ASU logos */
Fl_PNG_Image ASU_LOGO_BLACK1("./Images/asu_sunburst_rgb_black_150ppi_1.png");
Fl_PNG_Image ASU_LOGO_BLACK2("./Images/asu_sunburst_rgb_black_150ppi_0.png");
Fl_PNG_Image ASU_LOGO_WHITE2("./Images/asu_university_horiz_rgb_white_600.png");


/* Application specific logos */
Fl_PNG_Image TeamLogo1("./Images/TeamsButton.png");
Fl_PNG_Image TeamLogo2("./Images/TeamsButton2.png");
Fl_PNG_Image AboutLogo("./Images/About3.png");
Fl_PNG_Image *LoadingPngs[22];


/*********************************************************
 * Title: constexpr int toConstInt(int)
 *
 * Description: Function to convert integers into constant expressions
 *
 * Arguments: int
 *
 * Returns: constexpr int
 */
constexpr int toConstInt(int constInt) {

	return constInt;

}


/*********************************************************
 * Title: void MainWindow(void)
 *
 * Description: Constructor, sets up basic framework for the GUI
 *
 * Arguments: none
 *
 * Returns: none
 */
MainWindow::MainWindow() {

	Authenticated = false;

}
void MainWindow::MainWindow1() { }


/*********************************************************
 * Title: void ~MainWindow(void)
 *
 * Description: class destructor. Properly removes all GUI framework
 *
 * Arguments: none
 *
 * Returns: none
 */
MainWindow::~MainWindow() {
	delete progressWindow;
	delete progressBar;
	delete progressBox;
	delete TeamsButton;
	delete doneButton;
	delete imageBox;
	delete windowMain;
	delete nextWindow;
	delete boxHeader;
	delete buttonStart;
	delete buttonOpenProject;
	delete generateTeams;
	delete inputprojects;
	delete inputstudents;

}


/*********************************************************
 * Title: void running(void)
 *
 * Description: loops while window is running
 *
 * Arguments: none
 *
 * Returns: none
 */
void running(Fl_Window *w) {

	while (w->shown() == true) {	}

}


/*********************************************************
 * Title: void MainWindow2(void)
 *
 * Description: Constructor, sets up basic framework for the GUI
 *
 * Arguments: none
 *
 * Returns: none
 */
void MainWindow::MainWindow2() {

	/***** Declaring GUI window  *****/
	const char windowMainStr[] =
			"_______________________________________________\nCAPSTONE TEAM ASSIGNMENT SYSTEM";
	windowMain = new Fl_Window(750, 450, "CLIQUE");
	windowMain->color(ASU_WHITE);
	scroll1 =  new Fl_Scroll(0,0,750,450);
	scroll1->color(ASU_WHITE);//background color


	/***** Setting up 2 tabs *****/ {
	Fl_Tabs *tabs = new Fl_Tabs(10, 10, 730, 350);
	tabs->selection_color(ASU_GOLD);
	windowMain->resizable(tabs);

		/***** Adding first tab, HOME to main window *****/ {
		Fl_Group *homeTab = new Fl_Group(10, 40, 720, 300, "   Home   ");
		homeTab->labelsize(15);
		homeTab->labelfont(FL_HELVETICA_BOLD);
		windowMain->box(FL_BORDER_BOX);


		/***** Setting up all items on tab, "HOME"*****/ {
		homeTab->color(ASU_BLACK);
		homeTab->selection_color(ASU_BLACK);
		homeTab->labelcolor(ASU_WHITE);


			/***** Window with large ASU logo *****/
			boxHeader = new Fl_Box(20, 50, 710, 250, windowMainStr);
			boxHeader->box(FL_BORDER_BOX);
			boxHeader->color(ASU_MAROON);
			boxHeader->image(ASU_LOGO_WHITE2);
			boxHeader->labelfont(FL_HELVETICA_BOLD);
			boxHeader->labelsize(24);
			boxHeader->labelcolor(ASU_WHITE);
			boxHeader->redraw();


			/***** Start button to begin application *****/
			buttonStart = new Fl_Button(20, 305, 710, 50, "Start");
			buttonStart->color(ASU_GOLD);
			buttonStart->labelfont(FL_HELVETICA_ITALIC);
			buttonStart->labelsize(20);
			buttonStart->labelcolor(ASU_BLACK);
			buttonStart->selection_color(ASU_MAROON);
			buttonStart->callback(static_StartButtonClick, this);

		/***** End of Tab HOME *****/ }	homeTab->end();


		/***** Adding second tab, ABOUT to main window *****/
		Fl_Group *aboutTab = new Fl_Group(40, 50, 750, 360, "   About   ");


			/***** Setting up all items on tab, "ABOUT"*****/ {
			aboutTab->color(ASU_WHITE);
			aboutTab->selection_color(ASU_BLACK);
			aboutTab->labelcolor(ASU_WHITE);
			aboutTab->labelsize(15);
			aboutTab->labelfont(FL_HELVETICA_BOLD);

			/***** Variable declarations *****/
			Fl_Box *aboutBox1;
			Fl_Box *aboutBox2;
			Fl_Box *TextBox1;
			Fl_Box *TextBox2;
			Fl_Text_Display *aboutTextDisplay;
			Fl_Text_Buffer *aboutBuffer;
			const char AboutStr[] =
					"\nCLIQUE\n[the Capstone Team Assignment System]\n was developed "
							"by five senior software \n engineering students during the \n Fall 2019 and Spring 2020 semesters.\n "
							"\n SOFTWARE TEAM ";
			const char TeamStr[] =
					"\n Elizabeth Marquise\n Myles Colina          \n Sean Rogers          \n"
							" Cristi Deleo           \n Matthew Cilibraise\n";


			/***** Asu logo on left side of about tab *****/
			aboutBox1 = new Fl_Box(20, 55, 345, 295);
			aboutBox1->box(FL_FLAT_BOX);
			aboutBox1->color(ASU_WHITE);
			aboutBox1->labelcolor(ASU_WHITE);
			aboutBox1->labelsize(15);
			aboutBox1->labelfont(FL_HELVETICA_BOLD);
			aboutBox1->image(AboutLogo);


			/***** the "what built for" section *****/
			TextBox1 = new Fl_Box(20, 55, 345, 100, AboutStr);
			TextBox1->labelcolor(ASU_BLACK);
			TextBox1->labelsize(15);
			TextBox1->labelfont(FL_HELVETICA_BOLD);


			/***** Team members who developed the application *****/
			TextBox2 = new Fl_Box(20, 125, 345, 200, TeamStr);
			TextBox2->labelcolor(ASU_MAROON);
			TextBox2->labelsize(20);
			TextBox2->labelfont(FL_HELVETICA_BOLD);


			/***** The  "Why" for the application on right side *****/
			aboutBox2 = new Fl_Box(375, 55, 355, 30, "About Clique");
			aboutBox2->box(FL_FLAT_BOX);
			aboutBox2->color(ASU_MAROON);
			aboutBox2->labelcolor(ASU_WHITE);
			aboutBox2->labelsize(15);
			aboutBox2->labelfont(FL_HELVETICA_BOLD);


			/***** Sets up text display and buffer *****/
			aboutBuffer = new Fl_Text_Buffer();
			aboutTextDisplay = new Fl_Text_Display(375, 85, 355, 265);
			aboutTextDisplay->buffer(aboutBuffer);
			aboutTextDisplay->textfont(FL_HELVETICA);
			aboutTextDisplay->textcolor(ASU_BLACK);
			aboutTextDisplay->textsize(15);
			aboutTextDisplay->selection_color(ASU_GOLD);
			aboutBuffer->text("\nThis software application creates \n"
						"high-quality assignments of student teams\n"
						"to ASU Capstone projects.This automizes a\n"
						"previously manual task reducing the time\n"
						"to just minutes. The task of assigning\n"
						"teams to projects is of NP-hard complexity,\n"
						"with the ‘brute force’ method of finding\n "
						"all possible combinations to arrive at\n"
						"the most optimal solution taking more\n"
						"years than there are atoms in the\n"
						"universe!\n"
						"The team has devised a software solution\n "
						"that reduces this time to minutes, \n"
						"and provides excellent student teams\n "
						"to project matches.\n \n"
						"The algorithm that the team created takes\n"
						"into account the student's skills, among\n"
						"other factors, and matches them to \n"
						"projects based on the required skills.\n"
						"The algorithm focuses on the quality of the\n"
						"entire team, ensuring that students are\n"
						"assigned to teams that closely match their\n"
						"own skill level, and the skills required\n"
						"for the project.\n"
				);

			}

			aboutTab->end();

		}

		tabs->end();
	}


	/***** For testing and runnng application. When developed, the mainWindow
		 * should be moved shorter by 50 and this section will be commented out *****/
	inputprojects = new Fl_Int_Input(150, 400, 200, 30, "#Projects:");
	inputstudents = new Fl_Int_Input(500, 400, 200, 30, "#Students:");


	/***** Running and showing the window *****/
	scroll1->end();
	windowMain->resizable(scroll1);
	windowMain->show();
	windowMain->end();
	Fl::run();

}


/*****************************************************************************
 * Title: TeamsButtonClick
 *
 * Description: When the Generate Teams button is clicked, this callback
 * 		function takes the inputs from the int text input boxes, and passes
 * 		them to the main Team assignment function (main_run).
 *	    It creates a new window with a progress bar.
 *
 * Arguments: Fl_Widget* w
 *
 * Returns: nothing
 */
void MainWindow::TeamsButtonClick(Fl_Widget *w) {


	/***** Loads and loops images *****/
	for (int i = 0; i < 22; i++) {

		string filename = "./Images/Loading/" + to_string(i + 1) + ".png";
		int length = filename.length();
		char png_char[length + 1];
		strcpy(png_char, filename.c_str());
		LoadingPngs[i] = new Fl_PNG_Image(png_char);

	}


	/***** Sets up new GUI window for program progress *****/
	progressWindow = new Fl_Window(570, 500, "CLIQUE - Progress Window");
	progressWindow->begin();
	scroll2 =  new Fl_Scroll(0,0,570,500);
	scroll2->color(ASU_WHITE);//background color


	/***** border or edge coloring boxes *****/
	Fl_PNG_Image *baseImage = new Fl_PNG_Image("./Images/Loading/1.png");

	Fl_Box *backBox = new Fl_Box(0, 250, 570, 250);
	backBox->box(FL_BORDER_BOX);
	backBox->color(ASU_GREY);

	Fl_Box *backBox1 = new Fl_Box(0, 0, 10, 500);
	backBox1->box(FL_FLAT_BOX);
	backBox1->color(ASU_GREY);

	Fl_Box *backBox2 = new Fl_Box(0, 0, 570, 10);
	backBox2->box(FL_FLAT_BOX);
	backBox2->color(ASU_GREY);

	Fl_Box *backBox3 = new Fl_Box(560, 0, 10, 500);
	backBox3->box(FL_FLAT_BOX);
	backBox3->color(ASU_GREY);

	imageBox = new Fl_Box(10, 20, 550, 200);
	imageBox->color(ASU_WHITE);
	imageBox->box(FL_FLAT_BOX);
	imageBox->image(baseImage);
	imageBox->redraw();

	progressBox = new Fl_Box(10, 230, 550, 25, "");
	progressBox->box(FL_FLAT_BOX);
	progressBox->color(ASU_WHITE);


	/***** Buttons and progress bar at bottom of window *****/
	//Teams
	TeamsButton = new Fl_Button(25, 360, 200, 50, "Generate Teams");
	TeamsButton->color(ASU_GOLD);
	TeamsButton->selection_color(ASU_MAROON);
	TeamsButton->labelfont(FL_HELVETICA_ITALIC);
	TeamsButton->labelsize(15);
	TeamsButton->labelcolor(ASU_BLACK);

	// Done button
	doneButton = new Fl_Button(345, 360, 200, 50, "Done");
	doneButton->color(ASU_GOLD);
	doneButton->selection_color(ASU_MAROON);
	doneButton->labelfont(FL_HELVETICA_ITALIC);
	doneButton->labelsize(15);
	doneButton->labelcolor(ASU_BLACK);

	// Progress Bar
	progressBar = new Fl_Progress(20, 425, 530, 40);
	progressBar->minimum(0);               // set progress range to be 0.0 ~ 1.0
	progressBar->maximum(1);
	progressBar->color(ASU_GOLD);               // background color
	progressBar->selection_color(ASU_MAROON);     // progress bar color
	progressBar->labelcolor(FL_WHITE);            // percent text color
	progressBar->labelfont(FL_HELVETICA_BOLD);
	progressBar->labelsize(15);
	progressBar->box(FL_RFLAT_BOX);


	/***** Creates the text Buffer and text display to be filled
	 * by program output and styles it accordingly *****/
	terminalBuffer = new Fl_Text_Buffer();
	terminalTextDisplay = new Fl_Text_Display(10, 260, 550, 80);
	terminalTextDisplay->buffer(terminalBuffer);
	terminalTextDisplay->textfont(FL_HELVETICA);
	terminalTextDisplay->textcolor(ASU_BLACK);
	terminalTextDisplay->textsize(15);
	terminalTextDisplay->selection_color(ASU_GOLD);


	/***** Stylizing and running progress window *****/
	scroll2->end();
	progressWindow->resizable(scroll2);
	progressWindow->color(ASU_WHITE);
	progressWindow->box(FL_BORDER_BOX);

	doneButton->deactivate();

	progressWindow->end();
	progressWindow->show();

	progressBar->value(0);
	progressBar->label(0);

	TeamsButton->callback(static_ProgressTeamsButtonClick, this);
	doneButton->callback(static_DoneButtonClick, this);

	progressWindow->redraw();
	usleep(500000);
	Fl::run();

}


/*****************************************************************************
 * Title: cookieLoad
 *
 * Description: Circles cookie images until progress bar reaches 100%
 *
 * Arguments: Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar
 *
 * Returns: nothing
 */
void cookieLoad(Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar) {

	int i = 0;

	/***** while progress isn't complete *****/
	while (progressBar->value() != 100) {


		/***** Copy image from file location *****/
		string filename = "./Images/cookies/" + to_string(i) + ".png";
		int length = filename.length();
		char png_char[length + 1];
		strcpy(png_char, filename.c_str());


		/***** Display new image *****/
		Fl_PNG_Image *cookies = new Fl_PNG_Image(png_char);
		Fl::check();
		b->image(cookies);
		b->redraw();
		usleep(100000);
		i++;
		if (i == 10) {
			i = 0;
		}
	}            //end while loop

}


/*****************************************************************************
 * Title: animate
 *
 * Description: Circles given images until progress bar reaches 100%
 *
 * Arguments: Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar,
 *		Fl_PNG_Image *loadingPngs[23]
 *
 * Returns: nothing
 */
void animate(Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar,
		Fl_PNG_Image *loadingPngs[23]) {

	int i = 0;
	while (progressBar->value() != 100) {
		mtx.lock();
		Fl::check();
		b->image(loadingPngs[i]);
		b->redraw();
		mtx.unlock();
		usleep(50000);
		i++;
		if (i == 22) {
			i = 0;
		}
	}
}


void teamAssignment(int num_students, int num_projects,
		Fl_Progress *progressBar) { }


/*****************************************************************************
 * Title: ProgressTeamsButtonClick
 *
 * Description: When the Generate Teams button is clicked, this callback function
 *	    takes the inputs from the int text input boxes, and passes them to the
 *	    main Team assignment function (main_run). The progress bar then gets
 *	    updated with the progress, and updates the message.
 *
 * Arguments: Fl_Widget* w
 *
 * Returns: nothing
 */
void MainWindow::ProgressTeamsButtonClick(Fl_Widget *w) {

	/* Loads up progress window */
	TeamsButton->deactivate();
	progressBox->label("Clique Team Assignment Running...");
	progressBox->labelfont(FL_HELVETICA_BOLD);
	progressBox->labelsize(18);
	progressBox->labelcolor(ASU_GREY);
	imageBox->redraw();
	XInitThreads();
	thread threads[1];
	threads[0] = thread(animate, progressWindow, imageBox, progressBar,
			LoadingPngs);

	//if you want to load cookies.
	//threads[0] = thread (cookieLoad, progressWindow, imageBox, progressBar);
	num_classes = mwCourses.size();


	//call to main.cpp function main_run, to run the team assignment system.
	main m;
	m.main_run(num_projects, num_students, mwProjfile, progressBar,
			terminalBuffer, mwAllStudents, mwCourses, mwCookies);


	//join threads
	for (int i = 0; i < 1; i++) {
		threads[i].join();
	}


	/* Draws done image in green */
	Fl_PNG_Image *doneImage = new Fl_PNG_Image("./Images/Loading/done.png");
	imageBox->image(doneImage);
	imageBox->redraw();


	/* Activate done button and shows done message */
	doneButton->activate();
	progressBox->label("Team Assignment Complete! Click 'Done' to continue.");
	progressBox->labelsize(16);
	progressBox->labelfont(FL_HELVETICA_BOLD);
	progressBox->labelcolor(ASU_GREEN);

}


/*****************************************************************************
 * Title: okClick
 *
 * Description: hides last window when "okay" is clicked
 *
 * Arguments: Fl_Widget* w
 *
 * Returns: nothing
 */
void okClick(Fl_Widget *w) {

	backWindow->hide();

}


/*****************************************************************************
 * Title: errorMessage
 *
 * Description: Pops up an error message if the number of project/students
 * 		does not meet minimum requirements
 *
 * Arguments: Fl_Widget* w
 *
 * Returns: nothing
 */
void errorMessage() {

	/* Setting up GUI window */
	backWindow = new Fl_Window(650, 220, "CLIQUE");
	backWindow->begin();


	/* Title Message */
	Fl_Box promptBox1(0, 10, 650, 50, "Error!");
	promptBox1.align(FL_ALIGN_CENTER);
	promptBox1.labelsize(40);

	Fl_Box promptBox2(50, 70, 550, 20,
			"There are not enough projects for the students.");
	promptBox2.align(FL_ALIGN_CENTER);
	promptBox2.labelsize(20);
	promptBox2.labelfont(FL_HELVETICA_BOLD_ITALIC);

	Fl_Box promptBox3(50, 90, 550, 20, "Please enter more projects.");
	promptBox3.align(FL_ALIGN_CENTER);
	promptBox3.labelsize(20);
	promptBox3.labelfont(FL_HELVETICA);


	/* Button for user */
	Fl_Button okButton(250, 150, 175, 50, "OK");
	okButton.color(ASU_WHITE);
	okButton.labelfont(FL_HELVETICA);
	okButton.labelcolor(ASU_BLACK);
	okButton.labelsize(15);
	okButton.selection_color(ASU_MAROON);
	okButton.callback(okClick);


	/***** Stylizing and running window *****/
	backWindow->color(ASU_GOLD);
	backWindow->box(FL_BORDER_BOX);
	backWindow->resizable(promptBox2);
	backWindow->end();
	backWindow->show();
	Fl::run();

}


/*****************************************************************************
 * Title: DoneButtonClick
 *
 * Description: When the Done button is clicked, the results window is opened.
 *
 * Arguments: Fl_Widget* w
 *
 * Returns: nothing
 */
void MainWindow::DoneButtonClick(Fl_Widget *w) {

	progressWindow->hide();
	ResultWindow windowResult;
	windowResult.buffer->loadfile("results.txt", 1000000);
	windowResult.addText();

}


/*****************************************************************************
 * Title: destroyWindowCb
 *
 * Description: callback when the window is closed via the close button
 *
 * Arguments: Fl_Widget* w
 *
 * Returns: nothing
 */
static void destroyWindowCb(GtkWidget *widget, GtkWidget *window) {

	cout << "Mini-Browser Exited" << endl;
	gtk_main_quit();

	if (Auth != true) {
		cout << "Quit login session! EXITING PROGRAM" << endl;
		exit(1);
	}
}


/*****************************************************************************
 * Title: closewebViewCb
 *
 * Description: callback when the window is closed via the close button
 *
 * Arguments: Fl_Widget* w
 *
 * Returns: nothing
 */
static gboolean closeWebViewCb(WebKitWebView *webView, GtkWidget *window) {

	gtk_widget_destroy(window);
	return TRUE;

}


/*****************************************************************************
 * Title: minimimzeWindowCb
 *
 * Description: callback when the window is minimized
 *
 * Arguments: Fl_Widget* w
 *
 * Returns: nothing
 */
static void minimizeWindowCb(GtkWidget *widget, GtkWidget *window) {

	gtk_widget_destroy(window);

}


/*****************************************************************************
 * Title: getCookiesCB
 *
 * Description: Callback function for the cookie fetch function. Finishes
 * 		getting the cookies from the mini-browser session.Takes in the data
 * 		in a Glist, and loops over the contents type casting the data to a
 * 		soupcookie, and storing it in a vector to pass to the libcurl
 *		HTTP request functions.
 *
 * Arguments: WebKitCookieManager *manager, GAsyncResult *asyncResult
 *
 * Returns: nothing
 */
static void getCookiesCB(WebKitCookieManager *manager, GAsyncResult *asyncResult) {

	GList *dataList = webkit_cookie_manager_get_cookies_finish(manager,
			asyncResult, NULL);

	//clear cookie data from the vector
	cookiedata.clear();
	SoupCookie *cookies;

	int i = 0;
	for (GList *l = dataList; l && l->data; l = g_list_next(l)) {

		cookies = (SoupCookie*) l->data;

		//add the current cookie to the cookiedata vector
		cookiedata.push_back(*cookies);
		i++;

	}
}


/*****************************************************************************
 * Title: okClick2
 *
 * Description: hides last window when "okay" is clicked
 *
 * Arguments: Fl_Widget* w
 *
 * Returns: nothing
 */
void OkClick2(Fl_Widget *w) {

	backWindow2->hide();

}


/*****************************************************************************
 * Title: load_changedWebViewCb
 *
 * Description: Callback function that listens for a change in the url in the
 * 		mini-browser. Once the mini-browser reaches the login success page, the
 * 		mini-browser is exited. This function also calls the cookie manager get
 * 		cookies function to get the incoming cookies for every url change.
 *
 * Arguments: WebKitWebView *webView, GtkWidget *window
 *
 * Returns: gboolean
 */
static gboolean load_changedWebViewCb(WebKitWebView *webView, GtkWidget *window) {

	//cout << "listening" << endl;
	//cout << webkit_web_view_get_uri(webView) << endl;
	void *data;


	//Get request for the current cookies in the mini-browser session.
	webkit_cookie_manager_get_cookies(webkit_web_context_get_cookie_manager(
	(webkit_web_view_get_context(webView))),webkit_web_view_get_uri(webView),
	0,(GAsyncReadyCallback) getCookiesCB, data);


	//check to see if the login success page has been reached.
	if (strcmp(webkit_web_view_get_uri(webView),
			"https://canvas.asu.edu/?login_success=1") == 0) {


		//check to see if the login success page is done loading.
		if (webkit_web_view_is_loading(webView) == false) {

			//cout << "Canvas reached! authentication complete!" << endl;
			Auth = true;

			usleep(500000);

			gtk_widget_destroy(GTK_WIDGET(webView));
			gtk_widget_destroy(main_window);

			//gtk_widget_destroy(GTK_WIDGET(webView));
			//gtk_widget_destroy(window);
			//gtk_window_close(GTK_WINDOW(window));
			//gtk_window_iconify(GTK_WINDOW(window));
			//gtk_main_quit();

			//cout << "Closed mini-browser" << endl;
			//closeWebViewCb(webView, window);

			//TO-DO Find a way to close the browser window correctly,
			//as it eats up memory while open.

/*				backWindow2 = new Fl_Window(650, 220, "Capstone Team Assignment System");
				backWindow2->begin();

				Fl_Box promptBox1(0, 10, 650, 50, "ATTENTION!");
				promptBox1.align(FL_ALIGN_CENTER);
				promptBox1.labelsize(40);

				Fl_Box promptBox2(50, 70, 550, 20,
						"Please close the mini-browser window to continue");
				promptBox2.align(FL_ALIGN_CENTER);
				promptBox2.labelsize(20);
				promptBox2.labelfont(FL_HELVETICA);

				/*Fl_Box promptBox3(50, 90, 550, 20, "All information entered will be lost");
				promptBox3.align(FL_ALIGN_CENTER);
				promptBox3.labelsize(20);
				promptBox3.labelfont(FL_HELVETICA_BOLD_ITALIC);*/

				/*Fl_Box promptBox4(50, 110, 550, 20, "Are you sure?");
				promptBox4.align(FL_ALIGN_CENTER);
				promptBox4.labelsize(20);
				promptBox4.labelfont(FL_HELVETICA);*/

	/*			Fl_Button OkButton(425, 150, 175, 50, "OK");
				OkButton.color(ASU_WHITE);
				OkButton.labelfont(FL_HELVETICA);
				OkButton.labelcolor(ASU_BLACK);
				OkButton.labelsize(15);
				OkButton.selection_color(ASU_MAROON);
				OkButton.callback(OkClick2);

				backWindow2->color(ASU_GOLD);
				backWindow2->box(FL_BORDER_BOX);
				backWindow2->resizable(promptBox1);
				backWindow2->end();
				backWindow2->show();

				Fl::run();*/

		}

	}

	return TRUE;
}


/*****************************************************************************
 * Title: mini_browser
 *
 * Description: This function creates a mini-browser session so the user can login
 *		and create an authenticated session. The cookies from this session will
 *		be stored for future HTTP requests. This function uses gtk, and webkitgtk
 *		to create the mini-browser.
 *
 * Arguments: nothing
 *
 * Returns: nothing
 */
void mini_browser() {

	int argc;
	char **argv;


	//Initialize GTK+
	gtk_init(&argc, &argv);


	// Create an 800x600 window that will contain the browser instance
	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);
	gtk_window_set_title(GTK_WINDOW(main_window), "ASU Canvas Authentication");


	//create the data manager
	WebKitWebsiteDataManager *manager = webkit_website_data_manager_new(0);


	//create the context
	WebKitWebContext *context =
			webkit_web_context_new_with_website_data_manager(manager);


	//create cookie manager
	WebKitCookieManager *cookiejar = webkit_web_context_get_cookie_manager(
			context);


	// Create a browser instance
	webView = WEBKIT_WEB_VIEW(
			webkit_web_view_new_with_context(context));
	WebKitSettings *settings = webkit_settings_new();


	// Apply the result
	webkit_web_view_set_settings(webView, settings);


	// Put the browser area into the main window
	gtk_container_add(GTK_CONTAINER(main_window), GTK_WIDGET(webView));


	/* Set up callbacks so that if either the main window or the browser
	 * instance is closed, the program will exit */
	g_signal_connect(main_window, "destroy", G_CALLBACK(destroyWindowCb), NULL);
	g_signal_connect(webView, "close", G_CALLBACK(closeWebViewCb), main_window);
	g_signal_connect(webView, "load-changed", G_CALLBACK(load_changedWebViewCb),
			G_OBJECT(main_window));


	// Load a web page into the browser instance
	webkit_web_view_load_uri(webView, "https://canvas.asu.edu/login");


	/* Make sure that when the browser area becomes visible, it will
	 * get mouse and keyboard events */
	gtk_widget_grab_focus(GTK_WIDGET(webView));


	// Make sure the main window and all its contents are visible
	gtk_widget_show_all(main_window);


	// Run the main GTK+ event loop
	gtk_main();

}


/*****************************************************************************
 * Title: StartButtonClick
 *
 * Description: When the Start button is clicked, this callback function
 *	   Opens the next GUI window.
 *
 * Arguments: Fl_Widget* w
 *
 * Returns: nothing
 */
void MainWindow::StartButtonClick(Fl_Widget *w) {

	bool error = false;
	num_projects = atol(inputprojects->value());
	num_students = atol(inputstudents->value());


	//check to make sure that there are enough projects given the
	//entered number of students. This check can be changed to work
	//in the final system, by letting the user know if there are not enough
	//projects in the csv file for the students read in from Canvas.


	//find the number of students in each of the 4 class sections
	int num_students1 = num_students * 0.25;
	int num_students2 = num_students * 0.25;
	int num_students3 = num_students - num_students1 + num_students2;
	int num_students4 = num_students - num_students1 + num_students2;


	//find the number of projects for each of the 4 class sections
	int num_projects1 = num_projects * 0.25;
	int num_projects2 = num_projects * 0.25;
	int num_projects3 = num_projects - num_projects1 + num_projects2;
	int num_projects4 = num_projects - num_projects1 + num_projects2;

	Utility util;

	int needed_projects1 = util.calc_projects(num_students1, 5, 4);
	int needed_projects2 = util.calc_projects(num_students2, 5, 4);
	int needed_projects3 = util.calc_projects(num_students3, 5, 4);
	int needed_projects4 = util.calc_projects(num_students4, 5, 4);

	if (needed_projects1 > num_projects1 || needed_projects2 > num_projects2
			|| needed_projects3 > num_projects3
			|| needed_projects4 > num_projects4 || num_projects == 0 || num_students == 0) {
		errorMessage();
		error = true;
	}


	/* if the user is not authenticated yet,
	 * open the mini-browser for canvas authentication */
	if (error == false) {

		//cout<<"working"<<endl;

		if (Authenticated != true) {
			Auth = false;

			//DO NOT REMOVE THIS COUT STATEMENT!!!!
			cout<<"Mini-Browser Opened"<<endl;

			mini_browser();
		}

		Authenticated = Auth;
		windowMain->hide();


		//call to get the course information
		CookieManager cookieMonster;
		cookieMonster.getCourses(cookiedata);
		DataEntryGUI dataGUI(windowMain, cookiedata);

	}
}


/*****************************************************************************
 * Title: handle
 *
 * Description: changes different logos on different events
 *
 * Arguments: Fl_Widget* w
 *
 * Returns: nothing
 */
int MainWindow::handle(int event) {

	fprintf(stderr, "EVENT: %s(%d)\n", fl_eventnames[event], event);
	switch (event) {

		case FL_PUSH:
			//cout << "FL_PUSH" << endl;
			Fl_PNG_Image TeamLogo2("./Images/button2.png");
			generateTeams->image(TeamLogo2);

		return 1;
	}

	return 0;

}


/*****************************************************************************
 * Tile: callTeams
 *
 * Description: event handler to create teams
 *
 * Arguments: Fl_Widget* w
 *
 * Returns: nothing
 */
void MainWindow::callTeams(Fl_Widget *w) {

	TeamsButtonClick(windowMain);

}
