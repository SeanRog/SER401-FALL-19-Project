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



using namespace std;

//Function to convert integers into constant expressions.
constexpr int toConstInt(int constInt) {
	return constInt;
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

	//call to main.cpp function main_run, to run the team assignment system.
	main m;
	m.main_run(num_projects, num_students);

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
	//nextWindow = tokenGUI.tokenWindow;
	nextWindow = tokenGUI.tokenWindow;
	nextWindowFlag = true;

	}else{
	nextWindow->show();

	}


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

    //buttonNewProject->callback(newProjectButtonClick);

    Fl::run();

}

// DESTRUCTOR
MainWindow::~MainWindow() {
    // TODO
}



