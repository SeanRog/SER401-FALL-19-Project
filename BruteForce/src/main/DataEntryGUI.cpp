/*
 * DataEntryGUI.cpp
 *
 *  Created on: Feb 6, 2020
 *      Author: myles
 */

#include "DataEntryGUI.h"
#include "MainWindow.h"
#include "GUIStyles.h"
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

Fl_PNG_Image LOGO_BLACK1("./Images/asu_sunburst_rgb_maroongold_150ppi.png");


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
DataEntryGUI::DataEntryGUI(Fl_Window* win) {

	   //reference to the homepage window
	   prevWindow = win;

	    masterWindow = new Fl_Window(750, 580, "Capstone Team Assignment System");

	    //background box 3 - course selector
	    Fl_Box boxBack3(10,170,730,400);
	    boxBack3.box(FL_FLAT_BOX);
	    boxBack3.color(ASU_MAROON);

	    //Header box with logo
	    boxHeader = new Fl_Box(10,10,450,150,"Select courses        \n to generate teams   ");
	    boxHeader->box(FL_BORDER_BOX);
	    boxHeader->color(ASU_BLACK);
	    boxHeader->labelfont(FL_HELVETICA_BOLD_ITALIC);
	    boxHeader->labelsize(30);
	    boxHeader->labelcolor(ASU_WHITE);
	    boxHeader->redraw();

	    boxHeader2 = new Fl_Box(450,10,290,150);
	    boxHeader2->box(FL_BORDER_BOX);
	    boxHeader2->color(ASU_BLACK);
	    boxHeader2->image(LOGO_BLACK1);
	    boxHeader2->redraw();

	    // Go back button
	    goBack = new Fl_Button(420, 508, 150, 50, "Go Back");
		goBack->color(ASU_GOLD);
		goBack->labelfont(FL_HELVETICA_ITALIC);
		goBack->labelcolor(ASU_BLACK);
		goBack->labelsize(18);
		goBack->selection_color(ASU_MAROON);
		goBack->callback(static_GobackClick, this);

	    // Confirm button
	    Confirm = new Fl_Button(580, 508, 150, 50, "Confirm");
	    Confirm->color(ASU_GOLD);
	    Confirm->labelfont(FL_HELVETICA_ITALIC);
	    Confirm->labelcolor(ASU_BLACK);
	    Confirm->labelsize(18);
	    Confirm->selection_color(ASU_MAROON);
	    Confirm->callback(static_ConfirmClick, this);



	    //INITIALIZE CLASS SECTION SELECTOR COMPONENTS

	    // input year
	    inputYear = new Fl_Input(230,180,100,40, "Enter Year (YYYY):  ");
	    inputYear->labelfont(FL_HELVETICA_BOLD);
	    inputYear->labelcolor(ASU_WHITE);
	    inputYear->textfont(FL_HELVETICA);
	    inputYear->labelsize(18);

	    // Class Browser / selector
	    classBrowser = new Fl_Check_Browser(360, 180, 370, 260, "\nSelect classes, then click confirm");
	    classBrowser->scrollbar;
	    classBrowser->color(ASU_WHITE);
		classBrowser->textfont(FL_HELVETICA_ITALIC);
		classBrowser->textsize(18);
		classBrowser->labelcolor(ASU_WHITE);
	    classBrowser->labelfont(FL_HELVETICA_BOLD);
	    classBrowser->labelsize(18);
	    classBrowser->callback(static_BrowserSelection, this);

	    // Semester Selector
	    inputSemester = new Fl_Input_Choice(230,240, 100, 40, "Select Semester:    ");
	    inputSemester->add("Spring");
	    inputSemester->add("Summer");
	    inputSemester->add("Fall");
	    inputSemester->value("Fall");
	    inputSemester->textsize(18);
	    inputSemester->labelfont(FL_HELVETICA_BOLD);
	    inputSemester->labelcolor(ASU_WHITE);
	    inputSemester->textfont(FL_HELVETICA);
	    inputSemester->labelsize(18);
	    inputSemester->menubutton()->color(ASU_GOLD);
	    inputSemester->menubutton()->selection_color(ASU_MAROON);
	    inputSemester->menubutton()->textfont(FL_HELVETICA);
	    inputSemester->menubutton()->box(FL_BORDER_BOX);
	    inputSemester->menubutton()->textsize(18);

	    // Generates course broswer with selections
	    findCourses = new Fl_Button(30, 310, 300, 40, "Search for Courses");
		findCourses->color(ASU_GOLD);
	    findCourses->labelfont(FL_HELVETICA);
	    findCourses->labelcolor(ASU_BLACK);
	    findCourses->labelsize(18);
	    findCourses->selection_color(ASU_MAROON);
	    findCourses->callback(static_FindCoursesClick, this);


	    masterWindow->color(ASU_WHITE);
		masterWindow->box(FL_BORDER_BOX);
	    masterWindow->show();
	    masterWindow->end();

	    Fl::run();

}//end constructor


DataEntryGUI::~DataEntryGUI() {
	// TODO Auto-generated destructor stub
}

//TODO
void DataEntryGUI::BrowserSelection(Fl_Widget* w){

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
void DataEntryGUI::FindCoursesClick(Fl_Widget* w){

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
void DataEntryGUI::GobackClick(Fl_Widget* w){

	backWindow = new Fl_Window(650, 220, "Capstone Team Assignment System");
	backWindow->begin();

	Fl_Box promptBox1(0,10,650,50, "WARNING!");
	promptBox1.align(FL_ALIGN_CENTER);
	promptBox1.labelsize(40);

	Fl_Box promptBox2(50,70,550,20, "You are about to return to the main screen,");
	promptBox2.align(FL_ALIGN_CENTER);
	promptBox2.labelsize(20);
	promptBox2.labelfont(FL_HELVETICA);

	Fl_Box promptBox3(50,90,550,20, "All information entered will be lost");
	promptBox3.align(FL_ALIGN_CENTER);
	promptBox3.labelsize(20);
	promptBox3.labelfont(FL_HELVETICA_BOLD_ITALIC);

	Fl_Box promptBox4(50,110,550,20, "Are you sure?");
	promptBox4.align(FL_ALIGN_CENTER);
	promptBox4.labelsize(20);
	promptBox4.labelfont(FL_HELVETICA);

	yesButton = new Fl_Button(425,150,175,50,"Yes");
	yesButton->color(ASU_WHITE);
	yesButton->labelfont(FL_HELVETICA);
	yesButton->labelcolor(ASU_BLACK);
	yesButton->labelsize(15);
	yesButton->selection_color(ASU_MAROON);
	yesButton->callback(static_YesClick, this);

	cancelButton1 = new Fl_Button(40,150,175,50,"Cancel");
	cancelButton1->color(ASU_WHITE);
	cancelButton1->labelfont(FL_HELVETICA);
	cancelButton1->labelcolor(ASU_BLACK);
	cancelButton1->labelsize(15);
	cancelButton1->selection_color(ASU_MAROON);
	cancelButton1->callback(static_CancelClick1, this);


	backWindow->color(ASU_GOLD);
	backWindow->box(FL_BORDER_BOX);
	backWindow->resizable(w);
	backWindow->end();
	backWindow->show();

	Fl::run();

}

/*************************************************************************************
 * ConfirmClick
 *
 * Description:
 *		This function is the callback for the Confirm button.
 *		This button opens the next GUI window.
 */
void DataEntryGUI::YesClick(Fl_Widget* w){

	backWindow->hide();
	masterWindow->hide();
	prevWindow->show();

}


void DataEntryGUI::CancelClick1(Fl_Widget* w){

	backWindow->hide();
}

void DataEntryGUI::CancelClick2(Fl_Widget* w){

	confirmWindow->hide();
}


/*************************************************************************************
 * ConfirmClick
 *
 * Description:
 *		This function is the callback for the Confirm button.
 *		This button opens the next GUI window.
 *
 *Arguments:
 *	FL_Widget* w
 *
 *Returns:
 *	nothing
 */
void DataEntryGUI::ConfirmClick(Fl_Widget* w){


	confirmWindow = new Fl_Window(650, 220, "Confirmation Window");

	const char prompt1[] = "./Images/asu_sunburst_rgb_maroongold_150ppi.png";
	const char prompt2[] = "Capstone Questionnaire";
	const char prompt3[] = "2020_Projects.csv";
	confirmWindow->begin();

	Fl_Box promptBox1(0,10,650,30, "Does all the information look correct?");
	promptBox1.align(FL_ALIGN_CENTER);
	promptBox1.labelsize(30);

	Fl_Box promptBox2(20,60,20,20, "Project file:");
	promptBox2.align(FL_ALIGN_RIGHT);
	promptBox2.labelsize(15);
	promptBox2.labelfont(FL_HELVETICA_BOLD);
	Fl_Box promptBox2R(130,60,50,20, prompt1);
	promptBox2R.align(FL_ALIGN_RIGHT);
	promptBox2R.labelsize(15);
	promptBox2R.labelfont(FL_HELVETICA);

	Fl_Box promptBox3(20,80,20,20, "Survey Name:");
	promptBox3.align(FL_ALIGN_RIGHT);
	promptBox3.labelsize(15);
	promptBox3.labelfont(FL_HELVETICA_BOLD);
	Fl_Box promptBox3R(130,80,50,20, prompt2);
	promptBox3R.align(FL_ALIGN_RIGHT);
	promptBox3R.labelsize(15);
	promptBox3R.labelfont(FL_HELVETICA);

	Fl_Box promptBox4(20,100,20,20, "Courses:");
	promptBox4.align(FL_ALIGN_RIGHT);
	promptBox4.labelsize(15);
	promptBox4.labelfont(FL_HELVETICA_BOLD);
	Fl_Box promptBox4R(130,100,50,20, prompt3);
	promptBox4R.align(FL_ALIGN_RIGHT);
	promptBox4R.labelsize(15);
	promptBox4R.labelfont(FL_HELVETICA);

	GenerateTeamsButton = new Fl_Button(425,150,175,50,"Generate Teams");
	GenerateTeamsButton->color(ASU_WHITE);
	GenerateTeamsButton->labelfont(FL_HELVETICA);
	GenerateTeamsButton->labelcolor(ASU_BLACK);
	GenerateTeamsButton->labelsize(15);
	GenerateTeamsButton->selection_color(ASU_MAROON);
	GenerateTeamsButton->callback(static_GenerateTeamsClick, this);

	cancelButton2 = new Fl_Button(40,150,175,50,"Cancel");
	cancelButton2->color(ASU_WHITE);
	//cancelButton2->box(FL_SHADOW_BOX);
	cancelButton2->labelfont(FL_HELVETICA);
	cancelButton2->labelcolor(ASU_BLACK);
	cancelButton2->labelsize(15);
	cancelButton2->selection_color(ASU_MAROON);
	cancelButton2->callback(static_CancelClick2, this);

	confirmWindow->color(ASU_GOLD);
	confirmWindow->box(FL_BORDER_BOX);
	confirmWindow->resizable(w);
	confirmWindow->end();
	confirmWindow->show();

	Fl::run();

}


void DataEntryGUI::GenerateTeamsClick(Fl_Widget* w){

	masterWindow->hide();
	confirmWindow->hide();

	MainWindow mainWin;
	mainWin.MainWindow1();

}
