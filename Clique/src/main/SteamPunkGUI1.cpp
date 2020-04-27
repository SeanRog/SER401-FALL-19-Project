/*
 *SteamPunkGUI1.cpp
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


/********* BEGINNING OF INCLUSIONS **********/


/* Class Inclusions */
#include "SteamPunkGUI1.h"
#include "SPDataGUI.h"
#include "GUIStyles.h"
#include "ResultWindow.h"
#include "CookieManager.h"
#include "main.h"
#include "Utility.h"


/* Library Inclusions */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <thread>
#include <vector>
#include <stdio.h>
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


// Variable declarations
int SteamPunkGUI1::num_projects = 0;
int SteamPunkGUI1::num_students = 0;
int SteamPunkGUI1::num_classes = 0;
Fl_Window *backWindowSP;
Fl_PNG_Image *LoadingPngsSP[22];
Fl_PNG_Image *TrainPngs[7];
Fl_PNG_Image *PreTrainPngs[8];
Fl_PNG_Image *EndTrainPngs[9];
Fl_PNG_Image *Gears1Pngs[10];
Fl_PNG_Image *Gears3Pngs[10];
Fl_PNG_Image *Gears2Pngs[10];

//variables for the mini-browser session static functions
bool Auth1;
typedef void *user_data;
vector<SoupCookie> cookiedata1;
GtkWidget *main_windowSP;
WebKitWebView *webViewSP;


/********* BEGINNING OF PROGRAM CODE **********/


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
 * Title: SteamPunkGUI1
 *
 * Description: Constructor, sets up basic framework for the GUI
 *
 * Arguments: none
 *
 * Returns: constructor
 */
SteamPunkGUI1::SteamPunkGUI1() {

	Authenticated = false;

}


/*********************************************************
 * Title: GearsAnimate
 *
 * Description: Animates gears on steam punk window
 *
 * Arguments: Fl_Window *w, Fl_Box *b, Fl_Box *b2
 *
 * Returns: none
 */
void GearsAnimate(Fl_Window *w, Fl_Box *b, Fl_Box *b2) {

	int i = 0;
	while (w->shown() == true) {

		Fl::check();
		b->image(Gears1Pngs[i]);
		b2->image(Gears2Pngs[i]);
		w->redraw();
		usleep(100000);
		i++;

		if (i == 10) {
			i = 0;
		}

	}
}


/*********************************************************
 * Title: MainWindow2()
 *
 * Description: second Constructor, sets up basic framework for the GUI
 *
 * Arguments: None
 *
 * Returns: none
 */
void SteamPunkGUI1::MainWindow2() {

	//ASU logos
	Fl_PNG_Image ASU_LOGO_BLACK1(
			"./Images/asu_university_horiz_rgb_black_600.png");
	Fl_PNG_Image ASU_LOGO_BLACK2(
			"./Images/asu_sunburst_rgb_black_150ppi_0.png");
	Fl_PNG_Image ASU_LOGO_WHITE2(
			"./Images/asu_university_horiz_rgb_white_150.png");
	Fl_PNG_Image AboutLogo("./Images/About3.png");


	for (int i = 0; i < 10; i++) {

		string filename = "./Images/Steampunk/Gears1/" + to_string(i) + ".png";
		int length = filename.length();
		char png_char[length + 1];
		strcpy(png_char, filename.c_str());
		Gears1Pngs[i] = new Fl_PNG_Image(png_char);

		string filename1 = "./Images/Steampunk/Gears3/" + to_string(i) + ".png";
		int length1 = filename1.length();
		char png_char1[length1 + 1];
		strcpy(png_char1, filename1.c_str());
		Gears3Pngs[i] = new Fl_PNG_Image(png_char1);

	}


	for (int i = 0; i < 10; i++) {

		string filename = "./Images/Steampunk/Gears2/" + to_string(i) + ".png";
		int length = filename.length();
		char png_char[length + 1];
		strcpy(png_char, filename.c_str());
		Gears2Pngs[i] = new Fl_PNG_Image(png_char);

	}


	// Setting up S.P. GUI window
	const char windowMainStr[] =
			"_______________________________________________\nCAPSTONE TEAM ASSIGNMENT SYSTEM";
	windowMain = new Fl_Window(750, 450, "CLIQUE - Steampunk");
	windowMain->color(DARK_TAUPE);
	scroll1 =  new Fl_Scroll(0,0,750,450);
	scroll1->color(DARK_TAUPE);//background color

	/***** Setting up 2 tabs *****/ {
	Fl_Tabs *tabs = new Fl_Tabs(10, 10, 730, 350);
	tabs->selection_color(DARK_BRASS);
	windowMain->resizable(tabs);

		/***** Adding first tab, HOME to main window *****/ {
		Fl_Group *homeTab = new Fl_Group(10, 40, 720, 300, "   Home   ");
		homeTab->labelsize(15);
		homeTab->labelfont(FL_TIMES_ITALIC);
		windowMain->box(FL_BORDER_BOX);

			/***** Setting up all items on tab, "HOME"*****/ {
			homeTab->color(ASU_BLACK);
			homeTab->selection_color(ASU_BLACK);
			homeTab->labelcolor(LIGHT_CREAM);

			Fl_Box *boxHeader2 = new Fl_Box(20, 50, 710, 250);
			Fl_PNG_Image *silver = new Fl_PNG_Image(
							"./Images/Steampunk/Silver.png");
			boxHeader2->image(silver);
			boxHeader2->box(FL_NO_BOX);

			boxHeader = new Fl_Box(20, 50, 710, 250, windowMainStr);
			Fl_PNG_Image *start = new Fl_PNG_Image(
							"./Images/Steampunk/start1.png");

			buttonStart = new Fl_Button(20, 305, 710, 50);
			gearBox1 = new Fl_Box(540, 45, 210, 210);
			gearBox1->box(FL_NO_BOX);
			gearBox2 = new Fl_Box(15, 40, 150, 150);
			gearBox2->box(FL_NO_BOX);

			boxHeader->box(FL_NO_BOX);
			boxHeader->color(ASU_MAROON);
			boxHeader->image(ASU_LOGO_BLACK1);
			boxHeader->labelfont(FL_TIMES_BOLD_ITALIC);
			boxHeader->labelsize(24);
			boxHeader->labelcolor(LIGHT_CREAM);
			boxHeader->redraw();

			buttonStart->color(DARK_BRASS);
			buttonStart->image(start);
			buttonStart->labelcolor(ASU_BLACK);
			buttonStart->selection_color(DARK);
			buttonStart->callback(static_StartButtonClick, this);

		/***** End of Tab HOME *****/ }	homeTab->end();


		/***** Adding second tab, ABOUT to main window *****/
		Fl_Group *aboutTab = new Fl_Group(40, 50, 750, 360, "   About   ");


			/***** Setting up all items on tab, "ABOUT"*****/ {
			aboutTab->color(DARK_BRASS);
			aboutTab->selection_color(ASU_BLACK);
			aboutTab->labelcolor(LIGHT_CREAM);
			aboutTab->labelsize(15);
			aboutTab->labelfont(FL_TIMES_ITALIC);


			/***** Variable declarations *****/
			Fl_Box *aboutBox1;
			Fl_Box *aboutBox2;
			Fl_Box *TextBox1;
			Fl_Box *TextBox2;
			Fl_Text_Display *aboutTextDisplay;
			Fl_Text_Buffer *aboutBuffer;
			const char AboutStr[] =
					"\nCLIQUE, [Team Assignment System]\n was developed "
							"by five senior software \n engineering students during the \n Fall 2019 and Spring 2020 semesters.\n "
							"\n SOFTWARE TEAM ";
			const char TeamStr[] =
					"\n Elizabeth Marquise\n Matthew Cilibraise\n Sean Rogers          \n"
							" Cristi Deleo           \n Myles Colina          \n";


			/***** Asu logo on left side of about tab *****/
			aboutBox1 = new Fl_Box(20, 55, 345, 295);
			aboutBox1->box(FL_FLAT_BOX);
			Fl_PNG_Image *aboutpng = new Fl_PNG_Image(
						"./Images/Steampunk/about8.png");
			aboutBox1->image(aboutpng);
			aboutBox1->labelcolor(LIGHT_CREAM);
			aboutBox1->labelsize(15);
			aboutBox1->labelfont(FL_TIMES_BOLD_ITALIC);


			/***** the "what built for" section *****/
			TextBox1 = new Fl_Box(20, 55, 345, 100, AboutStr);
			TextBox1->labelcolor(ASU_BLACK);
			TextBox1->labelsize(15);
			TextBox1->labelfont(FL_TIMES_BOLD_ITALIC);


			/***** Team members who developed the application *****/
			TextBox2 = new Fl_Box(20, 125, 345, 200, TeamStr);
			TextBox2->labelcolor(ASU_BLACK);
			TextBox2->labelsize(22);
			TextBox2->labelfont(FL_TIMES_BOLD);


			/***** The  "Why" for the application on right side *****/
			aboutBox2 = new Fl_Box(375, 55, 355, 30, "About Clique");
			aboutBox2->box(FL_FLAT_BOX);
			aboutBox2->color(DARK_TAUPE);
			aboutBox2->labelcolor(LIGHT_CREAM);
			aboutBox2->labelsize(15);
			aboutBox2->labelfont(FL_TIMES_BOLD_ITALIC);


			/***** Sets up text display and buffer *****/
			aboutBuffer = new Fl_Text_Buffer();
			aboutTextDisplay = new Fl_Text_Display(375, 85, 355, 265);
			aboutTextDisplay->buffer(aboutBuffer);
			aboutTextDisplay->textfont(FL_TIMES);
			aboutTextDisplay->textcolor(ASU_BLACK);
			aboutTextDisplay->textsize(15);
			aboutTextDisplay->selection_color(ASU_GOLD);
			aboutTextDisplay->color(CREAM);
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
						"universe!\n \n"
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

	inputprojects->labelcolor(LIGHT_CREAM);
	inputprojects->color(LIGHT_CREAM);
	inputprojects->labelfont(FL_TIMES_ITALIC);

	inputstudents->labelcolor(LIGHT_CREAM);
	inputstudents->color(LIGHT_CREAM);
	inputstudents->labelfont(FL_TIMES_ITALIC);


	/***** running the gears and showing the window *****/
	scroll1->end();
	windowMain->resizable(scroll1);
	windowMain->show();
	windowMain->end();

	XInitThreads();
	thread threads[1];
	threads[0] = thread(GearsAnimate, windowMain, gearBox1, gearBox2);

	//join threads
	for (int i = 0; i < 1; i++) {
		threads[i].join();
	}

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
void SteamPunkGUI1::TeamsButtonClick(Fl_Widget *w) {

	//read in pngs for Pre-Train
	for (int i = 0; i < 8; i++) {

		string filename = "./Images/Steampunk/PreTrain/" + to_string(i)
				+ ".png";
		int length = filename.length();
		char png_char[length + 1];
		strcpy(png_char, filename.c_str());
		PreTrainPngs[i] = new Fl_PNG_Image(png_char);

	}


	for (int i = 0; i < 7; i++) {

		string filename = "./Images/Steampunk/Train/" + to_string(i) + ".png";
		int length = filename.length();
		char png_char[length + 1];
		strcpy(png_char, filename.c_str());
		TrainPngs[i] = new Fl_PNG_Image(png_char);

	}


	for (int i = 0; i < 9; i++) {

		string filename = "./Images/Steampunk/EndTrain/" + to_string(i)
				+ ".png";
		int length = filename.length();
		char png_char[length + 1];
		strcpy(png_char, filename.c_str());
		EndTrainPngs[i] = new Fl_PNG_Image(png_char);

	}


	/***** Sets up new GUI window for program progress *****/
	progressWindow = new Fl_Window(870, 800, "CLIQUE - Progress Window");
	progressWindow->begin();
	scroll2 =  new Fl_Scroll(0,0,870,800);
	scroll2->color(DARK_TAUPE);//background color


	/***** border or edge coloring boxes *****/
	Fl_Box *backBox1 = new Fl_Box(5, 5, 865, 500);
	backBox1->box(FL_FLAT_BOX);
	backBox1->color(DARK_BRASS);

	Fl_Box *backBox2 = new Fl_Box(0, 0, 870, 510);
	backBox2->box(FL_NO_BOX);
	Fl_PNG_Image *frame = new Fl_PNG_Image(
			"./Images/Steampunk/trainframe1.png");
	backBox2->image(frame);

	imageBox = new Fl_Box(75, 55, 700, 380);
	imageBox->color(DARK_BRASS);
	imageBox->box(FL_FLAT_BOX);
	imageBox->image(PreTrainPngs[0]);
	imageBox->redraw();

	progressBox = new Fl_Box(220, 530, 430, 20,
			"Click 'Generate Teams' to start.");
	progressBox->labelfont(FL_HELVETICA);
	progressBox->labelsize(15);
	progressBox->labelcolor(LIGHT_CREAM);

	gearBox3 = new Fl_Box(50, 510, 150, 150);
	Fl_PNG_Image gear1("./Images/Steampunk/Gear1.png");
	gearBox3->image(gear1);
	gearBox3->box(FL_FLAT_BOX);
	gearBox3->color(DARK_TAUPE);

	gearBox4 = new Fl_Box(670, 510, 150, 150);
	Fl_PNG_Image gear2("./Images/Steampunk/Gear2.png");
	gearBox4->image(gear2);
	gearBox4->box(FL_FLAT_BOX);
	gearBox4->color(DARK_TAUPE);


	/***** Buttons and progress bar at bottom of window *****/
	// Teams
	TeamsButton = new Fl_Button(25, 660, 200, 50, "Generate Teams");
	TeamsButton->color(DARK_BRASS);
	TeamsButton->selection_color(DARK);
	TeamsButton->labelfont(FL_TIMES_ITALIC);
	TeamsButton->labelsize(15);
	TeamsButton->labelcolor(ASU_BLACK);

	// Done button
	doneButton = new Fl_Button(645, 660, 200, 50, "Done");
	doneButton->color(DARK_BRASS);
	doneButton->selection_color(DARK);
	doneButton->labelfont(FL_TIMES_ITALIC);
	doneButton->labelsize(15);
	doneButton->labelcolor(ASU_BLACK);

	//progress Bar
	progressBar = new Fl_Progress(20, 725, 830, 40);
	progressBar->minimum(0);               // set progress range to be 0.0 ~ 1.0
	progressBar->maximum(1);
	progressBar->color(DARK);               // background color
	progressBar->selection_color(GREY_BLUE);     // progress bar color
	progressBar->labelcolor(FL_WHITE);            // percent text color
	progressBar->labelfont(FL_HELVETICA_BOLD);
	progressBar->labelsize(15);
	progressBar->box(FL_BORDER_BOX);


	/***** Creates the text Buffer and text display to be filled
	 * by program output and styles it accordingly *****/
	terminalBuffer = new Fl_Text_Buffer();
	terminalTextDisplay = new Fl_Text_Display(220, 550, 430, 80);
	terminalTextDisplay->buffer(terminalBuffer);
	terminalTextDisplay->textfont(FL_HELVETICA);
	terminalTextDisplay->textcolor(ASU_BLACK);
	terminalTextDisplay->textsize(15);
	terminalTextDisplay->color(LIGHT_CREAM);
	terminalTextDisplay->selection_color(DARK_BRASS);


	/***** Stylizing and running progress window *****/
	progressWindow->resizable(progressBar);
	progressWindow->color(DARK_TAUPE);
	progressWindow->box(FL_BORDER_BOX);

	doneButton->deactivate();
	scroll2->end();
	progressWindow->resizable(scroll2);
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
 * Title: cookieLoadSP
 *
 * Description: Circles cookie images until progress bar reaches 100%
 *
 * Arguments: Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar
 *
 * Returns: nothing
 */
void cookieLoadSP(Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar) {

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
	}
}


/*****************************************************************************
 * Title: animateSP
 *
 * Description: Circles given images until progress bar reaches 100%
 *
 * Arguments: Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar,
 *		Fl_PNG_Image *loadingPngs[23]
 *
 * Returns: nothing
 */
void animateSP(Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar,
		Fl_PNG_Image *loadingPngs[23], Fl_Box *b2, Fl_Box *b3) {

	b->image(PreTrainPngs[0]);
	b->redraw();
	std::this_thread::sleep_for(std::chrono::milliseconds(110));

	for (int i = 0; i < 8; i++) {
		mtx.lock();
		Fl::check();
		b->image(PreTrainPngs[i]);
		b->redraw();
		mtx.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	int j = 0;
	int k = 0;
	while (progressBar->value() != 100) {
		mtx.lock();
		Fl::check();
		b->image(TrainPngs[j]);
		b->redraw();
		mtx.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		j++;
		k++;
		if (j == 7) {
			j = 0;
		}
		if (k == 10) {
			k = 0;
		}

	}            //end while loop

	for (int i = 0; i < 9; i++) {
		mtx.lock();
		Fl::check();
		b->image(EndTrainPngs[i]);
		b->redraw();
		mtx.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}


void teamAssignmentSP(int num_students, int num_projects,
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
void SteamPunkGUI1::ProgressTeamsButtonClick(Fl_Widget *w) {

	/* Loads up progress window */
	TeamsButton->deactivate();
	progressBox->label("Clique Team Assignment Running...");
	progressBox->labelfont(FL_HELVETICA);
	progressBox->labelsize(15);
	progressBox->labelcolor(LIGHT_CREAM);
	imageBox->redraw();
	XInitThreads();
	thread threads[1];
	threads[0] = thread(animateSP, progressWindow, imageBox, progressBar,
			LoadingPngsSP, gearBox4, gearBox3);


	//if you want to load cookies.
	//threads[0] = thread (cookieLoad, progressWindow, imageBox, progressBar);

	//call to main.cpp function main_run, to run the team assignment system.
	main m;
	num_classes = spNumCourses;
	m.main_run(num_projects, num_students, SPGprojfile, progressBar,
			terminalBuffer,spAllStudents, spCourses, spCookies);


	//join threads
	for (int i = 0; i < 1; i++) {
		threads[i].join();
	}


	/* Draws done image in green */
	Fl_PNG_Image *doneImage = new Fl_PNG_Image(
			"./Images/Steampunk/EndTrain/8.png");
	imageBox->image(doneImage);
	imageBox->redraw();


	/* Activate done button and shows done message */
	doneButton->activate();
	progressBox->label("Team Assignment Complete! Click 'Done' to continue.");
	progressBox->labelsize(15);
	progressBox->labelfont(FL_HELVETICA);

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
void SteamPunkGUI1::DoneButtonClick(Fl_Widget *w) {

	progressWindow->hide();
	ResultWindow windowResult;
	windowResult.buffer->loadfile("results.txt", 1000000);
	windowResult.addText();
}


/*****************************************************************************
 * Title: okClickSP
 *
 * Description: hides last window when "okay" is clicked
 *
 * Arguments: Fl_Widget* w
 *
 * Returns: nothing
 */
void okClickSP(Fl_Widget *w) {

	backWindowSP->hide();

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
void errorMessageSP() {

	/* Setting up GUI window */
	backWindowSP = new Fl_Window(650, 220, "CLIQUE");
	backWindowSP->begin();


	/* Title Message */
	Fl_Box promptBox1(0, 10, 650, 50, "ERROR!");
	promptBox1.align(FL_ALIGN_CENTER);
	promptBox1.labelsize(40);
	promptBox1.labelcolor(ASU_WHITE);

	Fl_Box promptBox2(50, 70, 550, 20,
			"There are not enough projects for the students.");
	promptBox2.align(FL_ALIGN_CENTER);
	promptBox2.labelsize(20);
	promptBox2.labelfont(FL_TIMES_BOLD_ITALIC);
	promptBox2.labelcolor(ASU_WHITE);

	Fl_Box promptBox3(50, 90, 550, 20, "Please enter more projects.");
	promptBox3.align(FL_ALIGN_CENTER);
	promptBox3.labelsize(20);
	promptBox3.labelfont(FL_TIMES);
	promptBox3.labelcolor(ASU_WHITE);


	/* Button for user */
	Fl_Button okButton(250, 150, 175, 50, "OK");
	okButton.color(DARK_BRASS);
	okButton.labelfont(FL_TIMES_ITALIC);
	okButton.labelcolor(ASU_BLACK);
	okButton.labelsize(15);
	okButton.selection_color(DARK);
	okButton.callback(okClickSP);


	/***** Stylizing and running window *****/
	backWindowSP->color(DARK_TAUPE);
	backWindowSP->box(FL_BORDER_BOX);
	backWindowSP->resizable(promptBox2);
	backWindowSP->end();
	backWindowSP->show();
	Fl::run();

}


/*****************************************************************************
 * Title: destroyWindowCb1
 *
 * Description: callback when the window is closed via the close button
 *
 * Arguments: GtkWidget *widget, GtkWidget *window
 *
 * Returns: nothing
 */
static void destroyWindowCb1(GtkWidget *widget, GtkWidget *window) {

	cout << "Mini-Browser Exited" << endl;
	gtk_main_quit();

	if (Auth1 != true) {
		cout << "Quit login session! EXITING PROGRAM" << endl;
		exit(1);
	}

}


/*****************************************************************************
 * Title: closewebViewCb1
 *
 * Description: callback when the window is closed via the close button
 *
 * Arguments:WebKitWebView *webView, GtkWidget *window
 *
 * Returns: nothing
 */
static gboolean closeWebViewCb1(WebKitWebView *webView, GtkWidget *window) {

	gtk_widget_destroy(window);
	return TRUE;

}


/*****************************************************************************
 * Title: getCookiesCB1
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
static void getCookiesCB1(WebKitCookieManager *manager,
		GAsyncResult *asyncResult) {


	GList *dataList = webkit_cookie_manager_get_cookies_finish(manager,
			asyncResult, NULL);

	//clear cookie data from the vector
	cookiedata1.clear();
	SoupCookie *cookies;

	int i = 0;
	for (GList *l = dataList; l && l->data; l = g_list_next(l)) {

		cookies = (SoupCookie*) l->data;

		//add the current cookie to the cookiedata vector
		cookiedata1.push_back(*cookies);
		i++;

	}

}


/*****************************************************************************
 * Title: load_changedWebViewCb1
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
static gboolean load_changedWebViewCb1(WebKitWebView *webView,GtkWidget *window) {

	//cout << "listening" << endl;
	//cout << webkit_web_view_get_uri(webView) << endl;
	void *data;


	//Get request for the current cookies in the mini-browser session.
	webkit_cookie_manager_get_cookies(webkit_web_context_get_cookie_manager(
		(webkit_web_view_get_context(webView))),webkit_web_view_get_uri(webView),
		 0,(GAsyncReadyCallback) getCookiesCB1, data);


	//check to see if the login success page has been reached.
	if (strcmp(webkit_web_view_get_uri(webView),
			"https://canvas.asu.edu/?login_success=1") == 0) {


		//check to see if the login success page is done loading.
		if (webkit_web_view_is_loading(webView) == false) {

			//cout << "Canvas reached! authentication complete!" << endl;

			Auth1 = true;
			usleep(50000);
			gtk_widget_destroy(GTK_WIDGET(webViewSP));
			gtk_widget_destroy(main_windowSP);

		}
	}

	return TRUE;

}


/*****************************************************************************
 * Title: mini_browserSP
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
void mini_browserSP() {

	int argc = 1;
	//char **argv;
	char **argv = new char *[2];
	argv[0] = "";
	argv[1] = NULL;
	//&argc = 0x7f90496aaf1c 0x7f18c9de7f1c 0x7f2d6b748f1c
	//&argv = 0x7f90496aaf20 0x7f18c9de7f20 0x7f2d6b748f20

	//Initialize GTK+
	gtk_init(&argc, &argv);

	// Create an 800x600 window that will contain the browser instance
	main_windowSP = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(main_windowSP), 800, 600);
	gtk_window_set_title(GTK_WINDOW(main_windowSP), "ASU Canvas Authentication");


	//create the data manager
	WebKitWebsiteDataManager *manager = webkit_website_data_manager_new(0);


	//create the context
	WebKitWebContext *context =
			webkit_web_context_new_with_website_data_manager(manager);


	//create cookie manager
	WebKitCookieManager *cookiejar = webkit_web_context_get_cookie_manager(
			context);

	// Create a browser instance
	webViewSP = WEBKIT_WEB_VIEW(
			webkit_web_view_new_with_context(context));

	webkit_web_context_set_automation_allowed(context, 1);
	WebKitSettings *settings = webkit_settings_new();
	g_object_set(G_OBJECT(settings), "enable-offline-web-application-cache",
	TRUE, NULL);


	// Apply the result
	webkit_web_view_set_settings(webViewSP, settings);


	// Put the browser area into the main window
	gtk_container_add(GTK_CONTAINER(main_windowSP), GTK_WIDGET(webViewSP));


	/* Set up callbacks so that if either the main window or the
	 * browser instance is closed, the program will exit */
	g_signal_connect(main_windowSP, "destroy", G_CALLBACK(destroyWindowCb1),
			NULL);
	g_signal_connect(webViewSP, "close", G_CALLBACK(closeWebViewCb1),
			main_windowSP);

	g_signal_connect(webViewSP, "load-changed",
			G_CALLBACK(load_changedWebViewCb1), main_windowSP);


	// Load a web page into the browser instance
	webkit_web_view_load_uri(webViewSP, "https://canvas.asu.edu/login");

	/* Make sure that when the browser area becomes visible,
	 * it will get mouse and keyboard events */
	gtk_widget_grab_focus(GTK_WIDGET(webViewSP));


	// Make sure the main window and all its contents are visible
	gtk_widget_show_all(main_windowSP);


	// Run the main GTK+ event loop
	gtk_main();
	delete[] argv;

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
void SteamPunkGUI1::StartButtonClick(Fl_Widget *w) {

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
	|| needed_projects3 > num_projects3 || needed_projects4 > num_projects4
	|| num_projects == 0 || num_students == 0) {

			errorMessageSP();
			error = true;

		}

	if (error == false) {

		/* if the user is not authenticated yet,
		* open the mini-browser for canvas authentication */
		if (Authenticated != true) {
			Auth1 = false;
			//DO NOT REMOVE THIS COUT STATEMENT!!!!
			cout<<"Mini-Browser Opened"<<endl;

			mini_browserSP();
		}

		Authenticated = Auth1;
		windowMain->hide();


		//call to get the course information
		CookieManager cookieMonster;
		cookieMonster.getCourses(cookiedata1);
		SPDataGUI dataGUI(windowMain, cookiedata1);

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
int SteamPunkGUI1::handle(int event) {

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
void SteamPunkGUI1::callTeams(Fl_Widget *w) {

	TeamsButtonClick(windowMain);

}


/*********************************************************
 * Title: void ~SteamPunkGUI
 *
 * Description: class destructor. Properly removes all GUI framework
 *
 * Arguments: none
 *
 * Returns: none
 */
SteamPunkGUI1::~SteamPunkGUI1() {

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
