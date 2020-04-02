/*
 *SteamPunkGUI1.cpp
 *
 * Description:  Contains functions relating to the creation and user
 * interaction with the main window of the GUI/application.
 *
 * Created on:   Feb 19, 2020
 *
 * Authors:   M. Cilibra, M. Colina, C. DeLeo, E. Marquise, S. Rogers
 *
 * List of functions:
 *    - TODO
 *
 */

#include "SteamPunkGUI1.h"
#include "SPDataGUI.h"
#include "GUIStyles.h"
#include "ResultWindow.h"
#include "CookieManager.h"
#include "main.h"
#include "Utility.h"

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

#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <libsoup/soup.h>
#include <curl/curl.h>

using namespace std;
int SteamPunkGUI1::num_projects = 0;
int SteamPunkGUI1::num_students = 0;

//Function to convert integers into constant expressions.
constexpr int toConstInt(int constInt) {
	return constInt;
}

SteamPunkGUI1::SteamPunkGUI1() {
	// TODO Auto-generated constructor stub
	Authenticated = false;

}

Fl_PNG_Image *LoadingPngsSP[22];

Fl_PNG_Image *TrainPngs[7];
Fl_PNG_Image *PreTrainPngs[8];
Fl_PNG_Image *EndTrainPngs[9];

Fl_PNG_Image *Gears1Pngs[10];
Fl_PNG_Image *Gears3Pngs[10];
Fl_PNG_Image *Gears2Pngs[10];

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
	}            //end while loop
}

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

	const int windowMainW = 750;
	const int windowMainH = 450;
	const char windowMainStr[] =
			"_______________________________________________\nCAPSTONE TEAM ASSIGNMENT SYSTEM";
	windowMain = new Fl_Window(windowMainW, windowMainH,
			"Capstone Team Assignment System");
	windowMain->color(DARK_TAUPE);

	{
		Fl_Tabs *tabs = new Fl_Tabs(10, 10, 730, 350);
		tabs->selection_color(DARK_BRASS);
		windowMain->resizable(tabs);
		{
			Fl_Group *homeTab = new Fl_Group(10, 40, 720, 300, "   Home   ");
			homeTab->labelsize(15);
			homeTab->labelfont(FL_TIMES_ITALIC);
			windowMain->box(FL_BORDER_BOX);
			{
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
				//buttonStart->labelfont(FL_TIMES_ITALIC);
				//buttonStart->labelsize(20);
				buttonStart->image(start);
				buttonStart->labelcolor(ASU_BLACK);
				buttonStart->selection_color(DARK);
				buttonStart->callback(static_StartButtonClick, this);
			}

			homeTab->end();
			Fl_Group *aboutTab = new Fl_Group(40, 50, 750, 360, "   About   ");
			{

				aboutTab->color(DARK_BRASS);
				aboutTab->selection_color(ASU_BLACK);
				aboutTab->labelcolor(LIGHT_CREAM);
				aboutTab->labelsize(15);
				aboutTab->labelfont(FL_TIMES_ITALIC);
				//Fl_PNG_Image *brass1 = new Fl_PNG_Image("./Images/Steampunk/Brass1.png");
				//aboutTab->image(brass1);

				Fl_Box *aboutBox1;
				Fl_Box *aboutBox2;
				Fl_Box *TextBox1;
				Fl_Box *TextBox2;
				Fl_Text_Display *aboutTextDisplay;
				Fl_Text_Buffer *aboutBuffer;

				aboutBox1 = new Fl_Box(20, 55, 345, 295);
				aboutBox1->box(FL_FLAT_BOX);
				Fl_PNG_Image *aboutpng = new Fl_PNG_Image(
						"./Images/Steampunk/about8.png");
				aboutBox1->image(aboutpng);
				//aboutBox1->color(ASU_WHITE);
				aboutBox1->labelcolor(LIGHT_CREAM);
				aboutBox1->labelsize(15);
				aboutBox1->labelfont(FL_TIMES_BOLD_ITALIC);
				//aboutBox1->image(AboutLogo);

				const char AboutStr[] =
						"\nThe Capstone Team Assignment System\n was developed "
								"by five senior software \n engineering students during the \n Fall 2019 and Spring 2020 semesters.\n "
								"\n SOFTWARE TEAM ";
				const char TeamStr[] =
						"\n Elizabeth Marquise\n Matthew Cilibraise\n Sean Rogers          \n"
								" Cristi Deleo           \n Myles Colina          \n";

				TextBox1 = new Fl_Box(20, 55, 345, 100, AboutStr);
				TextBox1->labelcolor(ASU_BLACK);
				TextBox1->labelsize(15);
				TextBox1->labelfont(FL_TIMES_BOLD_ITALIC);

				TextBox2 = new Fl_Box(20, 125, 345, 200, TeamStr);
				TextBox2->labelcolor(ASU_BLACK);
				TextBox2->labelsize(22);
				TextBox2->labelfont(FL_TIMES_BOLD);

				aboutBox2 = new Fl_Box(375, 55, 355, 30, "About The Software");
				aboutBox2->box(FL_FLAT_BOX);
				aboutBox2->color(DARK_TAUPE);
				aboutBox2->labelcolor(LIGHT_CREAM);
				aboutBox2->labelsize(15);
				aboutBox2->labelfont(FL_TIMES_BOLD_ITALIC);

				// Buffer
				aboutBuffer = new Fl_Text_Buffer();

				//Text Display
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

	/* for running / testing inputs */
	inputprojects = new Fl_Int_Input(150, 400, 200, 30, "#Projects: ");
	inputstudents = new Fl_Int_Input(500, 400, 200, 30, "#Students: ");

	inputprojects->labelcolor(LIGHT_CREAM);
	inputprojects->color(LIGHT_CREAM);
	inputprojects->labelfont(FL_TIMES_ITALIC);

	inputstudents->labelcolor(LIGHT_CREAM);
	inputstudents->color(LIGHT_CREAM);
	inputstudents->labelfont(FL_TIMES_ITALIC);

	/* end */

	windowMain->show();
	windowMain->end();

	XInitThreads();
	thread threads[1];

	threads[0] = thread(GearsAnimate, windowMain, gearBox1, gearBox2);

	//join threads
	for (int i = 0; i < 1; i++) {
		threads[i].join();
	}

	//tabs->show();
	Fl::run();

}

/*****************************************************************************
 * TeamsButtonClick
 *
 * Author(s): Team#35
 *
 * Description:
 *		When the Generate Teams button is clicked, this callback function
 *	    takes the inputs from the int text input boxes, and passes them
 *	    to the main Team assignment function (main_run).
 *	    It creates a new window with a progress bar.
 *
 *
 * Arguments:
 *		Fl_Widget* w
 *
 * Returns:
 *		nothing
 */
void SteamPunkGUI1::TeamsButtonClick(Fl_Widget *w) {

	/*for (int i = 0; i < 22; i++) {

	 string filename = "./Images/Loading/" + to_string(i + 1) + ".png";
	 int length = filename.length();
	 char png_char[length + 1];
	 strcpy(png_char, filename.c_str());
	 LoadingPngsSP[i] = new Fl_PNG_Image(png_char);

	 }*/

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

	//PROGRESS BAR WINDOW

	progressWindow = new Fl_Window(870, 800, "Team Assignment Progress");
	progressWindow->begin();

	/*Fl_Box *backBox = new Fl_Box(0, 550, 870, 150);
	 backBox->box(FL_BORDER_BOX);
	 backBox->color(DARK_TAUPE);*/

	Fl_Box *backBox1 = new Fl_Box(5, 5, 865, 500);
	backBox1->box(FL_FLAT_BOX);
	backBox1->color(DARK_BRASS);

	Fl_Box *backBox2 = new Fl_Box(0, 0, 870, 510);
	backBox2->box(FL_NO_BOX);
	//backBox2->color(DARK_BRASS);
	Fl_PNG_Image *frame = new Fl_PNG_Image(
			"./Images/Steampunk/trainframe1.png");
	backBox2->image(frame);
	/*
	 Fl_Box *backBox1 = new Fl_Box(0, 0, 65, 550);
	 backBox1->box(FL_FLAT_BOX);
	 backBox1->color(DARK_TAUPE);

	 Fl_Box *backBox2 = new Fl_Box(0, 0, 870, 20);
	 backBox2->box(FL_FLAT_BOX);
	 backBox2->color(DARK_TAUPE);

	 Fl_Box *backBox3 = new Fl_Box(805, 0, 65, 550);
	 backBox3->box(FL_FLAT_BOX);
	 backBox3->color(DARK_TAUPE);*/

	TeamsButton = new Fl_Button(25, 660, 200, 50, "Generate Teams");
	doneButton = new Fl_Button(645, 660, 200, 50, "Done");
	progressBar = new Fl_Progress(20, 725, 830, 40);

	progressBar->minimum(0);               // set progress range to be 0.0 ~ 1.0
	progressBar->maximum(1);
	progressBar->color(DARK);               // background color
	progressBar->selection_color(GREY_BLUE);     // progress bar color
	progressBar->labelcolor(FL_WHITE);            // percent text color
	progressBar->labelfont(FL_HELVETICA_BOLD);
	progressBar->labelsize(15);
	progressBar->box(FL_BORDER_BOX);

	progressWindow->resizable(progressBar);

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

	// Buffer
	terminalBuffer = new Fl_Text_Buffer();

	//Text Display
	terminalTextDisplay = new Fl_Text_Display(220, 550, 430, 80);
	terminalTextDisplay->buffer(terminalBuffer);
	terminalTextDisplay->textfont(FL_HELVETICA);
	terminalTextDisplay->textcolor(ASU_BLACK);
	terminalTextDisplay->textsize(15);
	terminalTextDisplay->color(LIGHT_CREAM);
	terminalTextDisplay->selection_color(DARK_BRASS);

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

	doneButton->color(DARK_BRASS);
	doneButton->selection_color(DARK);
	doneButton->labelfont(FL_TIMES_ITALIC);
	doneButton->labelsize(15);
	doneButton->labelcolor(ASU_BLACK);

	TeamsButton->color(DARK_BRASS);
	TeamsButton->selection_color(DARK);
	TeamsButton->labelfont(FL_TIMES_ITALIC);
	TeamsButton->labelsize(15);
	TeamsButton->labelcolor(ASU_BLACK);

	progressWindow->color(DARK_TAUPE);
	progressWindow->box(FL_BORDER_BOX);

	doneButton->deactivate();

	progressWindow->end();
	progressWindow->show();

	progressBar->value(0);
	progressBar->label(0);

	TeamsButton->callback(static_ProgressTeamsButtonClick, this);
	doneButton->callback(static_DoneButtonClick, this);
	progressWindow->redraw();

	Fl::run();
}

void cookieLoadSP(Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar) {

	int i = 0;
	while (progressBar->value() != 100) {

		string filename = "./Images/cookies/" + to_string(i) + ".png";
		int length = filename.length();
		char png_char[length + 1];
		strcpy(png_char, filename.c_str());

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

void animateSP(Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar,
		Fl_PNG_Image *loadingPngs[23], Fl_Box *b2, Fl_Box *b3) {

	b->image(PreTrainPngs[0]);
	b->redraw();
	std::this_thread::sleep_for(std::chrono::milliseconds(110));

	for (int i = 0; i < 8; i++) {
		Fl::check();
		b->image(PreTrainPngs[i]);
		b->redraw();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		//usleep(50000);
	}

	int j = 0;
	int k = 0;
	while (progressBar->value() != 100) {
		Fl::check();
		b->image(TrainPngs[j]);
		b->redraw();

		/*b2->image(Gears1Pngs[k]);
		 b2->redraw();

		 b3->image(Gears3Pngs[k]);
		 b3->redraw();*/

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		//usleep(50000);
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
		Fl::check();
		b->image(EndTrainPngs[i]);
		b->redraw();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		//usleep(50000);
	}

}

void teamAssignmentSP(int num_students, int num_projects,
		Fl_Progress *progressBar) {

	//main m;
	//m.main_run(num_projects, num_students, progressBar, terminalBuffer);
}

/*****************************************************************************
 * ProgressTeamsButtonClick
 *
 * Author(s): Team#35
 *
 * Description:
 *		When the Generate Teams button is clicked, this callback function
 *	    takes the inputs from the int text input boxes, and passes them
 *	    to the main Team assignment function (main_run).
 *	    The progress bar then gets updated with the progress, and updates
 *	    the message.
 *
 *
 * Arguments:
 *		Fl_Widget* w
 *
 * Returns:
 *		nothing
 */
void SteamPunkGUI1::ProgressTeamsButtonClick(Fl_Widget *w) {

	TeamsButton->deactivate();
	progressBox->label("Team Assignment System Running...");
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
	m.main_run(num_projects, num_students, SPGprojfile, progressBar,
/*<<<<<<< HEAD
			terminalBuffer, studentsFromCanvas);
=======*/
			terminalBuffer,spAllStudents, spCourses, spCookies);
//>>>>>>> dev

	//join threads
	for (int i = 0; i < 1; i++) {
		threads[i].join();
	}

	Fl_PNG_Image *doneImage = new Fl_PNG_Image(
			"./Images/Steampunk/EndTrain/8.png");
	imageBox->image(doneImage);
	imageBox->redraw();

	doneButton->activate();
	progressBox->label("Team Assignment Complete! Click 'Done' to continue.");
	progressBox->labelsize(15);
	progressBox->labelfont(FL_HELVETICA);

}

/*****************************************************************************
 * DoneButtonClick
 *
 * Author(s): Team#35
 *
 * Description:
 *		When the Done button is clicked, the results window is opened.
 *
 *
 * Arguments:
 *		Fl_Widget* w
 *
 * Returns:
 *		nothing
 */
void SteamPunkGUI1::DoneButtonClick(Fl_Widget *w) {

	progressWindow->hide();
	ResultWindow windowResult;
	windowResult.buffer->loadfile("results.txt", 1000000);
	windowResult.addText();
}

Fl_Window *backWindowSP;

void okClickSP(Fl_Widget *w) {

	backWindowSP->hide();
	//exit(1);
}

void errorMessageSP() {
	backWindowSP = new Fl_Window(650, 220, "Capstone Team Assignment System");
	backWindowSP->begin();

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

	Fl_Button okButton(250, 150, 175, 50, "OK");
	okButton.color(DARK_BRASS);
	okButton.labelfont(FL_TIMES_ITALIC);
	okButton.labelcolor(ASU_BLACK);
	okButton.labelsize(15);
	okButton.selection_color(DARK);
	okButton.callback(okClickSP);

	backWindowSP->color(DARK_TAUPE);
	backWindowSP->box(FL_BORDER_BOX);
	backWindowSP->resizable(promptBox2);
	backWindowSP->end();
	backWindowSP->show();

	Fl::run();
}

//variables for the mini-browser session static functions
bool Auth1;
typedef void *user_data;
vector<SoupCookie> cookiedata1;
GtkWidget *main_windowSP;

//callback when the window is closed via the close button
static void destroyWindowCb1(GtkWidget *widget, GtkWidget *window) {
	cout << "Exiting mini-browser" << endl;
	gtk_main_quit();
	if (Auth1 != true) {
		cout << "Quit login session! EXITING PROGRAM" << endl;
		exit(1);
	}
}

//callback when the window is closed via the close button
static gboolean closeWebViewCb1(WebKitWebView *webView, GtkWidget *window) {
	gtk_widget_destroy(window);

	return TRUE;
}


/*****************************************************************************
 * getCookiesCB1
 *
 * Author(s): Myles,
 *
 * Description:
 *		Callback function for the cookie fetch function.
 *		Finishes getting the cookies from the mini-browser session.
 *		Takes in the data in a Glist, and loops over the contents type casting
 *		the data to a soupcookie, and storing it in a vector to pass to the libcurl
 *		HTTP request functions.
 *
 * Arguments:
 *		WebKitCookieManager *manager,
 *	    GAsyncResult *asyncResult
 *
 * Returns:
 *		nothing
 */
static void getCookiesCB1(WebKitCookieManager *manager,
		GAsyncResult *asyncResult) {
	//GList *dataList = webkit_website_data_manager_fetch_finish(manager, asyncResult, NULL);

	GList *dataList = webkit_cookie_manager_get_cookies_finish(manager,
			asyncResult, NULL);

	//clear cookie data from the vector
	cookiedata1.clear();

	SoupCookie *cookies;

	int i = 0;
	for (GList *l = dataList; l && l->data; l = g_list_next(l)) {

		cookies = (SoupCookie*) l->data;
	/*	cout << cookies->name << endl;
		cout << cookies->value << endl;
		cout << cookies->domain << endl;
		cout << cookies->path << endl;
		cout << cookies->expires << endl;*/

		//add the current cookie to the cookiedata vector
		cookiedata1.push_back(*cookies);
		i++;
	}
}

/*****************************************************************************
 * load_changedWebViewCb1
 *
 * Author(s): Myles,
 *
 * Description:
 *		Callback function that listens for a change in the url in the mini-browser.
 *		Once the mini-browser reaches the login success page, the mini-browser is exited.
 *		This function also calls the cookie manager get cookies function to get the incoming cookies
 *		for every url change.
 *
 * Arguments:
 *		WebKitWebView *webView,
		GtkWidget *window
 *
 * Returns:
 *		gboolean
 */
static gboolean load_changedWebViewCb1(WebKitWebView *webView,
		GtkWidget *window) {
	cout << "listening" << endl;
	cout << webkit_web_view_get_uri(webView) << endl;
	void *data;

	//Get request for the current cookies in the mini-browser session.
	webkit_cookie_manager_get_cookies(
			webkit_web_context_get_cookie_manager(
					(webkit_web_view_get_context(webView))),
			webkit_web_view_get_uri(webView), 0,
			(GAsyncReadyCallback) getCookiesCB1, data);

	//check to see if the login success page has been reached.
	if (strcmp(webkit_web_view_get_uri(webView),
			"https://canvas.asu.edu/?login_success=1") == 0) {

		//check to see if the login success page is done loading.
		if (webkit_web_view_is_loading(webView) == false) {

			cout << "Canvas reached! authentication complete!" << endl;

			Auth1 = true;
			//quit the mini-browser
			gtk_widget_destroy(main_windowSP);
			//gtk_main_quit();


		}
	}

	return TRUE;
}


/*****************************************************************************
 * mini_browserSP
 *
 * Author(s): Myles, Matthew, Cristi
 *
 * Description:
 *		This function creates a mini-browser session so the user can login
 *		and create an authenticated session. The cookies from this session will
 *		be stored for future HTTP requests. This function uses gtk, and webkitgtk
 *		to create the mini-browser.
 *
 * Arguments:
 *		nothing
 *
 * Returns:
 *		nothing
 */
void mini_browserSP() {

	int argc;
	char **argv;

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
	WebKitWebView *webView = WEBKIT_WEB_VIEW(
			webkit_web_view_new_with_context(context));

	webkit_web_context_set_automation_allowed(context, 1);

	WebKitSettings *settings = webkit_settings_new();

	g_object_set(G_OBJECT(settings), "enable-offline-web-application-cache",
	TRUE, NULL);

	// Apply the result
	webkit_web_view_set_settings(webView, settings);

	// Put the browser area into the main window
	gtk_container_add(GTK_CONTAINER(main_windowSP), GTK_WIDGET(webView));

	// Set up callbacks so that if either the main window or the browser instance is
	// closed, the program will exit
	g_signal_connect(main_windowSP, "destroy", G_CALLBACK(destroyWindowCb1),
			NULL);
	g_signal_connect(webView, "close", G_CALLBACK(closeWebViewCb1),
			main_windowSP);

	g_signal_connect(webView, "load-changed",
			G_CALLBACK(load_changedWebViewCb1), main_windowSP);

	// Load a web page into the browser instance
	webkit_web_view_load_uri(webView, "https://canvas.asu.edu/login");

	// Make sure that when the browser area becomes visible, it will get mouse
	// and keyboard events
	gtk_widget_grab_focus(GTK_WIDGET(webView));

	// Make sure the main window and all its contents are visible
	gtk_widget_show_all(main_windowSP);

	// Run the main GTK+ event loop
	gtk_main();

	//terminate the window
	//gtk_widget_destroy(main_window);

	cout << "Website running" << endl;

}

/*****************************************************************************
 * StartButtonClick
 *
 * Author(s): Team#35
 *
 * Description:
 *		When the Start button is clicked, this callback function
 *	   Opens the next GUI window.
 *
 * Arguments:
 *		Fl_Widget* w
 *
 * Returns:
 *		nothing
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
				|| needed_projects3 > num_projects3
				|| needed_projects4 > num_projects4 || num_projects == 0 || num_students == 0) {
			errorMessageSP();
			error = true;
		}

		if (error == false) {

/*<<<<<<< HEAD
			cout<<"Working"<<endl;
			//if the user is not authenticated yet,
			//open the mini-browser for canvas authentication
			if (Authenticated != true) {
				Auth1 = false;
				mini_browserSP();
			}
			Authenticated = Auth1;

			windowMain->hide();
			//call to get the course information
			CookieManager cookieMonster;
			cookieMonster.getCourses(cookiedata1);
			SPDataGUI dataGUI(windowMain, cookiedata1);
=======*/

			cout<<"Working"<<endl;
	//if the user is not authenticated yet,
	//open the mini-browser for canvas authentication
	if (Authenticated != true) {
		Auth1 = false;
		mini_browserSP();
	}
	Authenticated = Auth1;

	windowMain->hide();
	//call to get the course information
	CookieManager cookieMonster;
	cookieMonster.getCourses(cookiedata1);

	SPDataGUI dataGUI(windowMain, cookiedata1);
//>>>>>>> dev

		}
}

int SteamPunkGUI1::handle(int event) {

	fprintf(stderr, "EVENT: %s(%d)\n", fl_eventnames[event], event);
	switch (event) {
	case FL_PUSH:
		cout << "FL_PUSH" << endl;
		Fl_PNG_Image TeamLogo2("./Images/button2.png");
		generateTeams->image(TeamLogo2);
		//windowMain.redraw();

		return 1;
	}
	return 0;
}

void SteamPunkGUI1::callTeams(Fl_Widget *w) {

	TeamsButtonClick(windowMain);

}

SteamPunkGUI1::~SteamPunkGUI1() {
	// TODO Auto-generated destructor stub
}

