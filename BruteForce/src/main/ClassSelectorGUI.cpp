/*
 * ClassSelectorGUI.cpp
 *
 * Description:  Contains functions relating to the creation and user
 * interaction with the class section selector of the GUI/application.
 *
 * Created on: Jan 30, 2020
 *
 * Authors:   M. Cilibra, M. Colina, C. DeLeo, E. Marquise, S. Rogers
 *
 * List of functions:
 *    -ClassSelectorGUI() //constructor
 *    -~ClassSelectorGUI() //destructor
 *    -FindCoursesClick(Fl_Widget* w) //callback function
 *    -BrowserSelection(Fl_Widget* w) //callback function
 *
 */
#include "ClassSelectorGUI.h"
#include "MainWindow.h"
#include "main.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>

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
#include <FL/Fl_File_Chooser.H>


/*************************************************************************************
 * ClassSelectorGUI
 *
 * Description:
 *		Constructor function for the class section selector GUI window.
 *
 *Arguments:
 *	nonthing
 *
 *Returns:
 *	nothing
 */
ClassSelectorGUI::ClassSelectorGUI(Fl_Window* win) {

	//previous window
	  prevWindow = win;

	// INITIALIZE COMPONENTS
	    classWindow = new Fl_Window(600, 400, "Class Section Selector");
	    //FL_(X, Y, W, H, STRING)
	    boxHeader = new Fl_Box(20,20,560,50, "Select The Capstone Class Sections To Create Teams For");
	    classBrowser = new Fl_Check_Browser(20,100,300,250, "Class Section List");
	    inputYear = new Fl_Input(450, 100, 100, 30, "Enter Year (YYYY)");
	    inputSemester = new Fl_Input_Choice(450, 150, 100, 30, "Select Semester");
	    findCourses = new Fl_Button(450, 200, 100, 30, "Find Courses");
	    goBack = new Fl_Button(400, 350, 80, 30, "Go_Back");
	    Continue = new Fl_Button(500, 350, 80, 30, "Continue");

	     //callbacks
	    findCourses->callback(static_FindCoursesClick, this);
	    classBrowser->callback(static_BrowserSelection, this);
	    goBack->callback(static_GobackClick, this);
	    Continue->callback(static_ContinueClick, this);

	    //Additions to the components
	    classBrowser->scrollbar;


	    inputSemester->add("Spring");
	    inputSemester->add("Summer");
	    inputSemester->add("Fall");
	    inputSemester->value("Fall");

	    boxHeader->box(FL_UP_BOX);
	    boxHeader->labelfont(FL_BOLD);
	    boxHeader->labelsize(40);
	    boxHeader->labelcolor(FL_BLUE);


	    classWindow->show();
	    classWindow->end();

	    Fl::run();

}//end constructor


ClassSelectorGUI::~ClassSelectorGUI() {
	// TODO Auto-generated destructor stub
}


//TODO
void ClassSelectorGUI::BrowserSelection(Fl_Widget* w){

}


/*************************************************************************************
 * FindCoursesClick
 *
 * Description:
 *		This function is the callback for the Find Courses button.
 *		It updates the Browser based on the year entered into the
 *		input box, and the semester selected in the input choice box.
 *		It searches the course sections for the relevent courses, and
 *		only displays those.
 *
 *Arguments:
 *	FL_Widget* w
 *
 *Returns:
 *	nothing
 */
void ClassSelectorGUI::FindCoursesClick(Fl_Widget* w){

	classBrowser->add("");
	//clear the browser of all entries
	classBrowser->clear();

	string year;
	string semester;

	year = inputYear->value();
	semester = inputSemester->value();

	cout<<year<<endl;
	cout<<semester<<endl;

  for(auto & course : courses){

	  if((course.find(year) != string::npos)&&(course.find(semester) != string::npos)){

		  int length = course.length();
		  char course_char[length+1];

		  strcpy(course_char, course.c_str());

		  cout<<course<<endl;
		  classBrowser->add(course_char);
	  }
  }


}

/*************************************************************************************
 * GobackClick
 *
 * Description:
 *		This function is the callback for the Go back button.
 *		This button returns to the previous GUI window.
 *
 *Arguments:
 *	FL_Widget* w
 *
 *Returns:
 *	nothing
 */
void ClassSelectorGUI::GobackClick(Fl_Widget* w){

	classWindow->hide();
	prevWindow->show();


}

/*************************************************************************************
 * ContinueClick
 *
 * Description:
 *		This function is the callback for the Continue button.
 *		This button opens the next GUI window.
 *
 *Arguments:
 *	FL_Widget* w
 *
 *Returns:
 *	nothing
 */
void ClassSelectorGUI::ContinueClick(Fl_Widget* w){

	classWindow->hide();
	//nextWindow->show();

}



