/*
 * MainWindow.cpp
 *
 * Description:  Contains functions relating to the creation and user
 * interaction with the main window of the GUI/application.
 *
 * Created on:   01/25/2020
 *
 * Authors:   M. Cilibra, M. Colina, C. DeLeo, E. Marquise, S. Rogers
 *
 * List of functions:
 *    - TODO
 *
 */

#define WEBVIEW_GTK

#include "MainWindow.h"
#include "DataEntryGUI.h"
#include "GUIStyles.h"
#include "ResultWindow.h"
#include "CookieManager.h"
#include "main.h"
#include "webview.h"

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

int MainWindow::num_projects = 0;
int MainWindow::num_students = 0;

//Function to convert integers into constant expressions.
constexpr int toConstInt(int constInt) {
	return constInt;
}

// CONSTRUCTOR
MainWindow::MainWindow() {

	Authenticated = false;

}
//ASU logos
Fl_PNG_Image ASU_LOGO_BLACK1("./Images/asu_sunburst_rgb_black_150ppi_1.png");
Fl_PNG_Image ASU_LOGO_BLACK2("./Images/asu_sunburst_rgb_black_150ppi_0.png");
Fl_PNG_Image ASU_LOGO_WHITE2("./Images/asu_university_horiz_rgb_white_150.png");

//team button
Fl_PNG_Image TeamLogo1("./Images/TeamsButton.png");
Fl_PNG_Image TeamLogo2("./Images/TeamsButton2.png");

Fl_PNG_Image AboutLogo("./Images/About3.png");

Fl_PNG_Image *LoadingPngs[22];

void MainWindow::MainWindow1() {

}

// DESTRUCTOR
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

void MainWindow::MainWindow2() {
	const int windowMainW = 750;
	const int windowMainH = 450;
	const char windowMainStr[] =
			"_______________________________________________\nCAPSTONE TEAM ASSIGNMENT SYSTEM";
	windowMain = new Fl_Window(windowMainW, windowMainH,
			"Capstone Team Assignment System");
	windowMain->color(ASU_WHITE);

	{
		Fl_Tabs *tabs = new Fl_Tabs(10, 10, 730, 350);
		tabs->selection_color(ASU_GOLD);
		windowMain->resizable(tabs);
		{
			Fl_Group *homeTab = new Fl_Group(10, 40, 720, 300, "   Home   ");
			homeTab->labelsize(15);
			homeTab->labelfont(FL_HELVETICA_BOLD);
			windowMain->box(FL_BORDER_BOX);
			{
				homeTab->color(ASU_BLACK);
				homeTab->selection_color(ASU_BLACK);
				homeTab->labelcolor(ASU_WHITE);

				boxHeader = new Fl_Box(20, 50, 710, 250, windowMainStr);
				buttonStart = new Fl_Button(20, 305, 710, 50, "Start");

				boxHeader->box(FL_BORDER_BOX);
				boxHeader->color(ASU_MAROON);
				boxHeader->image(ASU_LOGO_WHITE2);

				boxHeader->labelfont(FL_HELVETICA_BOLD);
				boxHeader->labelsize(24);
				boxHeader->labelcolor(ASU_WHITE);
				boxHeader->redraw();

				buttonStart->color(ASU_GOLD);
				buttonStart->labelfont(FL_HELVETICA_ITALIC);
				buttonStart->labelsize(20);
				buttonStart->labelcolor(ASU_BLACK);
				buttonStart->selection_color(ASU_MAROON);
				buttonStart->callback(static_StartButtonClick, this);
			}

			homeTab->end();
			Fl_Group *aboutTab = new Fl_Group(40, 50, 750, 360, "   About   ");
			{

				aboutTab->color(ASU_WHITE);
				aboutTab->selection_color(ASU_BLACK);
				aboutTab->labelcolor(ASU_WHITE);
				aboutTab->labelsize(15);
				aboutTab->labelfont(FL_HELVETICA_BOLD);

				Fl_Box *aboutBox1;
				Fl_Box *aboutBox2;
				Fl_Box *TextBox1;
				Fl_Box *TextBox2;
				Fl_Text_Display *aboutTextDisplay;
				Fl_Text_Buffer *aboutBuffer;

				aboutBox1 = new Fl_Box(20, 55, 345, 295);
				aboutBox1->box(FL_FLAT_BOX);
				aboutBox1->color(ASU_WHITE);
				aboutBox1->labelcolor(ASU_WHITE);
				aboutBox1->labelsize(15);
				aboutBox1->labelfont(FL_HELVETICA_BOLD);
				aboutBox1->image(AboutLogo);

				const char AboutStr[] =
						"\nThe Capstone Team Assignment System\n was developed "
								"by five senior software \n engineering students during the \n Fall 2019 and Spring 2020 semesters.\n "
								"\n SOFTWARE TEAM ";
				const char TeamStr[] =
						"\n Elizabeth Marquise\n Myles Colina          \n Sean Rogers          \n"
								" Cristi Deleo           \n Matthew Cilibraise\n";

				TextBox1 = new Fl_Box(20, 55, 345, 100, AboutStr);
				TextBox1->labelcolor(ASU_BLACK);
				TextBox1->labelsize(15);
				TextBox1->labelfont(FL_HELVETICA_BOLD);

				TextBox2 = new Fl_Box(20, 125, 345, 200, TeamStr);
				TextBox2->labelcolor(ASU_MAROON);
				TextBox2->labelsize(20);
				TextBox2->labelfont(FL_HELVETICA_BOLD);

				aboutBox2 = new Fl_Box(375, 55, 355, 30, "About The Software");
				aboutBox2->box(FL_FLAT_BOX);
				aboutBox2->color(ASU_MAROON);
				aboutBox2->labelcolor(ASU_WHITE);
				aboutBox2->labelsize(15);
				aboutBox2->labelfont(FL_HELVETICA_BOLD);

				// Buffer
				aboutBuffer = new Fl_Text_Buffer();

				//Text Display
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

	/* for running / testing inputs */
	inputprojects = new Fl_Int_Input(150, 400, 200, 30, "#Projects:");
	inputstudents = new Fl_Int_Input(500, 400, 200, 30, "#Students:");
	/* end */

	windowMain->show();
	windowMain->end();

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
void MainWindow::TeamsButtonClick(Fl_Widget *w) {

	for (int i = 0; i < 22; i++) {

		string filename = "./Images/Loading/" + to_string(i + 1) + ".png";
		int length = filename.length();
		char png_char[length + 1];
		strcpy(png_char, filename.c_str());
		LoadingPngs[i] = new Fl_PNG_Image(png_char);

	}

	//PROGRESS BAR WINDOW

	progressWindow = new Fl_Window(570, 500, "Team Assignment Progress");
	progressWindow->begin();

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

	TeamsButton = new Fl_Button(25, 360, 200, 50, "Generate Teams");
	doneButton = new Fl_Button(345, 360, 200, 50, "Done");
	progressBar = new Fl_Progress(20, 425, 530, 40);

	//progressBox = new Fl_Box(10, 330, 550, 40, "");

	progressBar->minimum(0);               // set progress range to be 0.0 ~ 1.0
	progressBar->maximum(1);
	progressBar->color(ASU_GOLD);               // background color
	progressBar->selection_color(ASU_MAROON);     // progress bar color
	progressBar->labelcolor(FL_WHITE);            // percent text color
	progressBar->labelfont(FL_HELVETICA_BOLD);
	progressBar->labelsize(15);
	progressBar->box(FL_RFLAT_BOX);

	progressWindow->resizable(progressBar);

	Fl_PNG_Image *baseImage = new Fl_PNG_Image("./Images/Loading/1.png");
	//Fl_PNG_Image* baseImage = new Fl_PNG_Image("./Images/cookies/0.png");

	imageBox = new Fl_Box(10, 20, 550, 200);
	imageBox->color(ASU_WHITE);
	imageBox->box(FL_FLAT_BOX);
	imageBox->image(baseImage);
	imageBox->redraw();

	// Buffer
	terminalBuffer = new Fl_Text_Buffer();

	//Text Display
	terminalTextDisplay = new Fl_Text_Display(10, 260, 550, 80);
	terminalTextDisplay->buffer(terminalBuffer);
	terminalTextDisplay->textfont(FL_HELVETICA);
	terminalTextDisplay->textcolor(ASU_BLACK);
	terminalTextDisplay->textsize(15);
	terminalTextDisplay->selection_color(ASU_GOLD);

	progressBox = new Fl_Box(10, 230, 550, 25, "");
	progressBox->box(FL_FLAT_BOX);
	progressBox->color(ASU_WHITE);

	doneButton->color(ASU_GOLD);
	doneButton->selection_color(ASU_MAROON);
	doneButton->labelfont(FL_HELVETICA_ITALIC);
	doneButton->labelsize(15);
	doneButton->labelcolor(ASU_BLACK);

	TeamsButton->color(ASU_GOLD);
	TeamsButton->selection_color(ASU_MAROON);
	TeamsButton->labelfont(FL_HELVETICA_ITALIC);
	TeamsButton->labelsize(15);
	TeamsButton->labelcolor(ASU_BLACK);

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

	Fl::run();
}

void cookieLoad(Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar) {

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

void animate(Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar,
		Fl_PNG_Image *loadingPngs[23]) {

	int i = 0;
	while (progressBar->value() != 100) {
		Fl::check();
		b->image(loadingPngs[i]);
		b->redraw();
		usleep(50000);
		i++;
		if (i == 22) {
			i = 0;
		}
	}            //end while loop

}

void teamAssignment(int num_students, int num_projects,
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
void MainWindow::ProgressTeamsButtonClick(Fl_Widget *w) {

	TeamsButton->deactivate();
	progressBox->label("Team Assignment System Running...");
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

	//call to main.cpp function main_run, to run the team assignment system.
	main m;

	m.main_run(num_projects, num_students, progressBar, terminalBuffer);

	//join threads
	for (int i = 0; i < 1; i++) {
		threads[i].join();
	}

	Fl_PNG_Image *doneImage = new Fl_PNG_Image("./Images/Loading/done.png");
	imageBox->image(doneImage);
	imageBox->redraw();

	doneButton->activate();
	progressBox->label("Team Assignment Complete! Click 'Done' to continue.");
	progressBox->labelsize(16);
	progressBox->labelfont(FL_HELVETICA_BOLD);
	progressBox->labelcolor(ASU_GREEN);

}

/*****************************************************************************
 * DoneButtonClick
 *
 * Author(s): Team#35
 *
 * Description:
 *		When the Done button is clicked, the results window is opened.
 *
 * Arguments:
 *		Fl_Widget* w
 *
 * Returns:
 *		nothing
 */
void MainWindow::DoneButtonClick(Fl_Widget *w) {

	progressWindow->hide();
	ResultWindow windowResult;
	windowResult.buffer->loadfile("results.txt", 1000000);
	windowResult.addText();
}


static void destroyWindowCb(GtkWidget *widget, GtkWidget *window) {
	cout << "quit!" << endl;
	gtk_main_quit();

}

static gboolean closeWebViewCb(WebKitWebView *webView, GtkWidget *window) {
	gtk_widget_destroy(window);
	cout << "destroyed!" << endl;
	return TRUE;
}


typedef void *user_data;
vector<SoupCookie> cookiedata;
Fl_Window *nextWindow;
bool Auth;

//callback function for the cookie fetch method. stores the cookies in a vector.
static void getCookiesCB(WebKitCookieManager *manager, GAsyncResult *asyncResult) {
	//GList *dataList = webkit_website_data_manager_fetch_finish(manager, asyncResult, NULL);

	GList *dataList = webkit_cookie_manager_get_cookies_finish(manager,
			asyncResult, NULL);

	//clear cookie data from the vector
	cookiedata.clear();

	SoupCookie *cookies;

	int i = 0;
	for (GList *l = dataList; l && l->data; l = g_list_next(l)) {

		cookies = (SoupCookie*) l->data;
		cout << cookies->name << endl;
		cout << cookies->value << endl;
		cout << cookies->domain << endl;
		cout << cookies->path << endl;
		cout << cookies->expires << endl;

		//add the current cookie to the cookiedata vector
		cookiedata.push_back(*cookies);
		i++;
	}
}


//callback that listens for a change in the url in the mini-browser
static gboolean load_changedWebViewCb(WebKitWebView *webView,
		GtkWidget *window) {
	cout << "listening" << endl;
	cout << webkit_web_view_get_uri(webView) << endl;
	void *data;

	//Get request for the current cookies in the mini-browser session.
	webkit_cookie_manager_get_cookies(
			webkit_web_context_get_cookie_manager(
					(webkit_web_view_get_context(webView))),
			webkit_web_view_get_uri(webView), 0,
			(GAsyncReadyCallback) getCookiesCB, data);

	//check to see if the login success page has been reached.
	if (strcmp(webkit_web_view_get_uri(webView),
			"https://canvas.asu.edu/?login_success=1") == 0) {

		//check to see if the login success page is done loading.
		if (webkit_web_view_is_loading(webView) == false) {

			cout << "Canvas reached! authentication complete!" << endl;

			//quit the mini-browser
			gtk_main_quit();
			//TO-DO Find a way to close the browser window correctly,
			//as it eats up memory while open.

		}
	}

	return TRUE;
}

//function create and open the mini-browser session
void mini_browser() {

	int argc;
	char **argv;

	//Initialize GTK+
	gtk_init(&argc, &argv);

	// Create an 800x600 window that will contain the browser instance
	GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
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
	WebKitWebView *webView = WEBKIT_WEB_VIEW(
			webkit_web_view_new_with_context(context));

	webkit_web_context_set_automation_allowed(context, 1);

	webkit_cookie_manager_set_accept_policy(cookiejar,
			WEBKIT_COOKIE_POLICY_ACCEPT_ALWAYS);

	webkit_cookie_manager_set_persistent_storage(cookiejar, "./cookies.txt",
			WEBKIT_COOKIE_PERSISTENT_STORAGE_TEXT);

	WebKitSettings *settings = webkit_settings_new();

	g_object_set(G_OBJECT(settings), "enable-offline-web-application-cache",
	TRUE, NULL);

	// Apply the result
	webkit_web_view_set_settings(webView, settings);

	// Put the browser area into the main window
	gtk_container_add(GTK_CONTAINER(main_window), GTK_WIDGET(webView));

	// Set up callbacks so that if either the main window or the browser instance is
	// closed, the program will exit
	g_signal_connect(main_window, "destroy", G_CALLBACK(destroyWindowCb), NULL);
	g_signal_connect(webView, "close", G_CALLBACK(closeWebViewCb), main_window);

	g_signal_connect(webView, "load-changed", G_CALLBACK(load_changedWebViewCb),
			main_window);


	// Load a web page into the browser instance
	webkit_web_view_load_uri(webView, "https://canvas.asu.edu/login");

	// Make sure that when the browser area becomes visible, it will get mouse
	// and keyboard events
	gtk_widget_grab_focus(GTK_WIDGET(webView));

	// Make sure the main window and all its contents are visible
	gtk_widget_show_all(main_window);

	// Run the main GTK+ event loop
	gtk_main();

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
void MainWindow::StartButtonClick(Fl_Widget *w) {

	num_projects = atol(inputprojects->value());
	num_students = atol(inputstudents->value());

	//nextWindow = windowMain;
	cout << "working" << endl;

	//if the user is not authenticated yet,
	//open the mini-browser for canvas authentication
	if (Authenticated != true) {
		Auth = false;
		mini_browser();
	}
	Authenticated = Auth;

	windowMain->hide();

	//call to get the course information
	CookieManager cookieMonster;
	cookieMonster.getCourses(cookiedata);

	DataEntryGUI dataGUI(windowMain);
}

int MainWindow::handle(int event) {

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

void MainWindow::callTeams(Fl_Widget *w) {

	TeamsButtonClick(windowMain);

}
