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

#include "MainWindow.h"
#include "DataEntryGUI.h"
#include "AuthTokenGUI.h"
#include "GUIStyles.h"
#include "main.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <FL/names.h>

#include <FL/Fl.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Progress.H>
#include "ResultWindow.h"


using namespace std;

//Function to convert integers into constant expressions.
constexpr int toConstInt(int constInt) {
	return constInt;
}

// CONSTRUCTOR
MainWindow::MainWindow(){

}
//ASU logos
Fl_PNG_Image ASU_LOGO_BLACK1("./Images/asu_sunburst_rgb_black_150ppi_1.png");
Fl_PNG_Image ASU_LOGO_BLACK2("./Images/asu_sunburst_rgb_black_150ppi_0.png");
Fl_PNG_Image ASU_LOGO_WHITE2("./Images/asu_university_horiz_rgb_white_150.png");

//team button
Fl_PNG_Image TeamLogo1("./Images/TeamsButton.png");
Fl_PNG_Image TeamLogo2("./Images/TeamsButton2.png");


void MainWindow::MainWindow1() {
    // MAIN WINDOW
	num_students=0;
	num_projects=0;
	nextWindowFlag=false;

    const int windowMainW = 400;
    const int windowMainH = 400;
    const char windowMainStr[] = "Project 35";

    // HEADER BOX
    const int boxHeaderX = 20;
    const int boxHeaderY = 20;
    const int boxHeaderW = toConstInt(windowMainW - (boxHeaderX * 2));
    const int boxHeaderH = 90;
    const char boxHeaderStr[] = "CAPSTONE TEAM ASSIGNMENT SYSTEM";

    // NEW PROJECT BUTTON
    const int buttonStartX = toConstInt(boxHeaderX);
    const int buttonStartY = toConstInt(boxHeaderY + boxHeaderH + 20);
    const int buttonStartW = 100;
    const int buttonStartH = 50;
    const char buttonStartStr[] = "Start";

    // OPEN PROJECT BUTTON
    const int buttonOpenProjectX = toConstInt(buttonStartX + buttonStartW + 20);
    const int buttonOpenProjectY = toConstInt(buttonStartY);
    const int buttonOpenProjectW = toConstInt(buttonStartW);
    const int buttonOpenProjectH = toConstInt(buttonStartH);
    const char buttonOpenProjectStr[] = "Open Project";

    // PROJECT INPUT
    const int InputProjectX = toConstInt(buttonStartX + buttonStartW + 20);
    const int InputProjectY = toConstInt(buttonStartY + 70);
    const int InputProjectW = toConstInt(buttonStartW);
    const int InputProjectH = toConstInt(buttonStartH);
    const char InputPStr[] = "#Projects";

    // STUDENT INPUT
    const int InputStudentX = toConstInt(buttonStartX + buttonStartW + 20);
    const int InputStudentY = toConstInt(buttonStartY + 140);
    const int InputStudentW = toConstInt(buttonStartW);
    const int InputStudentH = toConstInt(buttonStartH);
    const char InputSStr[] = "#Students";

     // GENERATE TEAMS BUTTON
    const int generateTeamsX = toConstInt(buttonStartX + buttonStartW + 130);
    const int generateTeamsY = toConstInt(buttonStartY + 120);
    const int generateTeamsW = toConstInt(buttonStartW);
    const int generateTeamsH = toConstInt(buttonStartH + 20);
    const char generateTeamsStr[] = "Generate Teams";


    // INITIALIZE COMPONENTS
    windowMain = new Fl_Window(windowMainW, windowMainH, windowMainStr);
    boxHeader = new Fl_Box(boxHeaderX, boxHeaderY, boxHeaderW,
        boxHeaderH, boxHeaderStr);
    buttonStart = new Fl_Button(buttonStartX, buttonStartY,
        buttonStartW, buttonStartH, buttonStartStr);
    buttonOpenProject = new Fl_Button(buttonOpenProjectX, buttonOpenProjectY,
        buttonOpenProjectW, buttonOpenProjectH, buttonOpenProjectStr);

    inputprojects = new Fl_Int_Input(InputProjectX, InputProjectY,
    		InputProjectW, InputProjectH, InputPStr );

    inputstudents = new Fl_Int_Input(InputStudentX, InputStudentY,
    		InputStudentW, InputStudentH, InputSStr );

     generateTeams = new Fl_Button(generateTeamsX, generateTeamsY,
    		 TeamLogo1.w(), TeamLogo1.h());

    //CALLBACKS
    generateTeams->callback(static_TeamsButtonClick, this);
    buttonStart->callback(static_StartButtonClick, this);



    windowMain->color(ASU_WHITE);
    windowMain->box(FL_BORDER_BOX);
    windowMain->resizable(boxHeader);

    //windowMain->color(ASU_GOLD);
    //windowMain->image(ASU_BLACK_LOGO);

    buttonStart->color(ASU_GOLD);
    //buttonStart->box(FL_SHADOW_BOX);
    buttonStart->labelfont(FL_HELVETICA_BOLD);
    buttonStart->labelcolor(ASU_BLACK);
    buttonStart->labelsize(12);
    buttonStart->selection_color(ASU_MAROON);

    generateTeams->image(TeamLogo1);
    generateTeams->color(ASU_GOLD);
	generateTeams->selection_color(ASU_MAROON);
    generateTeams->labelcolor(ASU_BLACK);
    generateTeams->labelfont(FL_HELVETICA_ITALIC);
    generateTeams->labelsize(12);
    generateTeams->box(FL_NO_BOX);
    generateTeams->tooltip("Generate Teams");
    generateTeams->down_box(FL_NO_BOX);


    buttonOpenProject->color(ASU_GOLD);
    buttonOpenProject->labelcolor(ASU_BLACK);
    //buttonOpenProject->box(FL_SHADOW_BOX);

    //buttonStart->activate();
	//fltk::set_background(ASU_MAROON);
	//boxHeader->color(FL_WHITE);

    boxHeader->box(FL_FLAT_BOX);
    boxHeader->color(ASU_MAROON);
    boxHeader->image(ASU_LOGO_BLACK1);
    boxHeader->labelfont(FL_HELVETICA_ITALIC);
    boxHeader->labelsize(15);
    //boxHeader->labeltype(_FL_SHADOW_LABEL);
    boxHeader->labelcolor(ASU_WHITE);
    boxHeader->redraw();

    windowMain->show();
    windowMain->end();


    Fl::run();

}




// DESTRUCTOR
MainWindow::~MainWindow() {

}


void MainWindow::MainWindow2(){

   const int windowMainW = 750;
   const int windowMainH = 370;
   const char windowMainStr[] =
		   "_______________________________________________\nCAPSTONE TEAM ASSIGNMENT SYSTEM";
   windowMain = new Fl_Window(windowMainW, windowMainH, "Capstone Team Assignment System");
   windowMain->color(ASU_GREY);

   {
	Fl_Tabs *tabs = new Fl_Tabs(20,5,740,360);
	tabs->selection_color(ASU_WHITE);
	windowMain->resizable(tabs);
	{
	    Fl_Group *homeTab = new Fl_Group(20,30,750,360,"   Home   ");
	    homeTab->labelsize(15);
	    homeTab->labelfont(FL_HELVETICA_BOLD);
	    windowMain->box(FL_BORDER_BOX);
	    {
	    	homeTab->color(ASU_WHITE);
	    	homeTab->selection_color(ASU_BLACK);
	    	homeTab->labelcolor(ASU_WHITE);

	    	boxHeader = new Fl_Box(25,33,710,250, windowMainStr);
	    	buttonStart = new Fl_Button(20, 303, 710, 50, "Start");

		    boxHeader->box(FL_BORDER_BOX);
		    boxHeader->color(ASU_MAROON);
		    boxHeader->image(ASU_LOGO_WHITE2);

		    boxHeader->labelfont(FL_HELVETICA);
		    boxHeader->labelsize(22);
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
	    Fl_Group *aboutTab = new Fl_Group(30,30,750,360,"   About   ");
	    {

	    	aboutTab->color(ASU_WHITE);
	    	aboutTab->selection_color(ASU_BLACK);
	    	aboutTab->labelcolor(ASU_WHITE);
	    	aboutTab->labelsize(15);
	    	aboutTab->labelfont(FL_HELVETICA_BOLD);

	    }
	    aboutTab->end();
	}

	tabs->end();

	}
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
void MainWindow::TeamsButtonClick(Fl_Widget* w) {

	num_projects = atol(inputprojects->value());
	num_students = atol(inputstudents->value());

	  generateTeams->image(TeamLogo2);
	  generateTeams->deactivate();

	cout <<"'Generate Teams' button clicked" <<endl;
	cout << num_projects<<endl;
	cout<< num_students<<endl;
	cout<<endl;

				//PROGRESS BAR WINDOW

		        progressWindow = new Fl_Window(450, 180, "Team Assignment Progress");
		        progressWindow->begin();
		        TeamsButton = new Fl_Button(10,10,140,40,"GENERATE TEAMS");//child 0
		        doneButton = new Fl_Button(340,10,100,40,"DONE");//child 1
		        progressBar = new Fl_Progress(10,70,430,40);  //child 2
		        progressBox = new Fl_Box(10, 120, 430, 40, ""); //child 3
		        progressBar->minimum(0);                      // set progress range to be 0.0 ~ 1.0
		        progressBar->maximum(1);
		        progressBar->color(ASU_GREY);               // background color
		        progressBar->selection_color(ASU_BLUE);     // progress bar color
		        progressBar->labelcolor(FL_WHITE);            // percent text color
		        progressBar->labelfont(FL_HELVETICA_BOLD);
		        progressBar->labelsize(15);

		        progressWindow->resizable(progressBar);

		        doneButton->color(ASU_GOLD);
		        doneButton->selection_color(ASU_MAROON);
		        doneButton->labelfont(FL_HELVETICA_BOLD);
		        doneButton->labelsize(12);

		        TeamsButton->color(ASU_GOLD);
		        TeamsButton->selection_color(ASU_MAROON);
		        TeamsButton->labelfont(FL_HELVETICA_BOLD);
		        TeamsButton->labelsize(12);

		        progressWindow->color(ASU_WHITE);
		        progressWindow->box(FL_BORDER_BOX);

		        doneButton->deactivate();

		        progressWindow->end();
		        progressWindow->show();

		        progressBar->value(0);
		        progressBar->label(0);


		        TeamsButton->callback(static_ProgressTeamsButtonClick, this);
		        doneButton->callback(static_DoneButtonClick, this);


		        Fl::run();
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
void MainWindow::ProgressTeamsButtonClick(Fl_Widget* w) {

	TeamsButton->deactivate();
	progressBox->label("Team Assignment System Running...");
	//call to main.cpp function main_run, to run the team assignment system.
		main m;
		m.main_run(num_projects, num_students, progressBar);

	doneButton->activate();
	progressBox->label("Team Assignment Complete! Click 'Done' to continue.");

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
void MainWindow::DoneButtonClick(Fl_Widget* w){

	  generateTeams->activate();
	  generateTeams->image(TeamLogo1);

	 progressWindow->hide();
	 ResultWindow windowResult;
	 windowResult.buffer->loadfile("results.txt", 1000000);
	 windowResult.addText();




	//call and create the results window
	//show results window.

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
void MainWindow::StartButtonClick(Fl_Widget* w) {

	cout <<"'Start' button clicked" <<endl;
	cout<<endl;

	windowMain->hide();

	//call to next GUI window.
	DataEntryGUI dataGUI(windowMain);


}

int MainWindow::handle(int event) {

	fprintf(stderr, "EVENT: %s(%d)\n", fl_eventnames[event], event);
    switch(event) {
    case FL_PUSH:
    	  cout<<"FL_PUSH"<<endl;
    	  Fl_PNG_Image TeamLogo2("./Images/button2.png");
    	  generateTeams->image(TeamLogo2);
    	  //windowMain.redraw();

    	  return 1;
    }
  return 0;
}




