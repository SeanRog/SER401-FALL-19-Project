/*
 * MainWindow.cpp
 *
 * Description:  Contains functions relating to the creation and user
 * interaction with the main window of the GUI/application.
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
#include "ClassSelectorGUI.h"
#include "AuthTokenGUI.h"
#include "main.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Progress.H>



using namespace std;

//Function to convert integers into constant expressions.
constexpr int toConstInt(int constInt) {
	return constInt;
}

// CONSTRUCTOR
MainWindow::MainWindow() {
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
    const int boxHeaderH = 75;
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
    const int generateTeamsY = toConstInt(buttonStartY + 140);
    const int generateTeamsW = toConstInt(buttonStartW);
    const int generateTeamsH = toConstInt(buttonStartH);
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
    		 generateTeamsW, generateTeamsH, generateTeamsStr);

    //CALLBACKS
    generateTeams->callback(static_TeamsButtonClick, this);
    buttonStart->callback(static_StartButtonClick, this);

    boxHeader->box(FL_UP_BOX);
    boxHeader->labelfont(FL_BOLD + FL_ITALIC);
    boxHeader->labelsize(18);
    boxHeader->labeltype(_FL_SHADOW_LABEL);
    boxHeader->labelcolor(FL_BLUE);

    windowMain->show();
    windowMain->end();


    Fl::run();

}

// DESTRUCTOR
MainWindow::~MainWindow() {
    // TODO
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

	cout <<"'Generate Teams' button clicked" <<endl;
	cout << num_projects<<endl;
	cout<< num_students<<endl;
	cout<<endl;

				//PROGRESS BAR WINDOW

		        progressWindow = new Fl_Window(350, 180, "Team Assignment Progress");
		        progressWindow->begin();
		        TeamsButton = new Fl_Button(10,10,100,40,"Generate Teams");//child 0
		        doneButton = new Fl_Button(240,10,100,40,"Done");//child 1
		        progressBar = new Fl_Progress(10,70,330,40);  //child 2
		        progressBox = new Fl_Box(10, 120, 330, 40, ""); //child 3
		        progressBar->minimum(0);                      // set progress range to be 0.0 ~ 1.0
		        progressBar->maximum(1);
		        progressBar->color(0x88888800);               // background color
		        progressBar->selection_color(0x4444ff00);     // progress bar color
		        progressBar->labelcolor(FL_WHITE);            // percent text color

		        doneButton->deactivate();

		        progressWindow->end();
		        progressWindow->show();

		        progressBar->value(0);              // update progress bar with 0.0 ~ 1.0 value
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

	 progressWindow->hide();


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

	if(nextWindowFlag == false){

	AuthTokenGUI tokenGUI(windowMain, nextWindow);

	nextWindow = tokenGUI.tokenWindow;
	nextWindowFlag = true;

	}else{
	nextWindow->show();

	}

}
