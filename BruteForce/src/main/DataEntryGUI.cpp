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


	    masterWindow = new Fl_Window(800, 1000, "CAPSTONE TEAM ASSIGNMENT SYSTEM");


	    //background box 1
	    Fl_Box boxBack2(20,200,760,500);
	    boxBack2.box(FL_NO_BOX);
	    boxBack2.color(ASU_WHITE);

	    //background box 3
	    Fl_Box boxBack3(20,600,760,300);
	    boxBack3.box(FL_FLAT_BOX);
	    boxBack3.color(ASU_GREY);

	    //FL_(X, Y, W, H, STRING)
	    boxHeader = new Fl_Box(20,20,760,50,"Please Complete The Following");
	    goBack = new Fl_Button(460, 920, 110, 50, "GO BACK");
	    Confirm = new Fl_Button(600, 920, 110, 50, "CONFIRM");

	    //Initialize Project File Chooser - Step 1 Choose Project File
		projectFileInstructionsBox = new Fl_Box(20,90,760,30);
		projectFileChooserButton = new Fl_Button(20,140,50,50,"@+3fileopen");
		fileInput_Project = new Fl_Input(90,150,690,30);
		fileInput_Project->value(".");

		//Initialize Student Quiz Textbox - Step 2 Enter name of Capstone Survey
		quizFileInstructionsBox = new Fl_Box(20,210, 760, 30);
		fileInput_StudentQuizName = new Fl_Input(20,260,760,30);

	    //INITIALIZE CLASS SECTION SELECTOR COMPONENTS
	    classBrowser = new Fl_Check_Browser(40,650,300,200, "Class Section List");
	    inputYear = new Fl_Input(480, 650, 100, 30, "Enter Year (YYYY)");
	    inputSemester = new Fl_Input_Choice(480,700, 100, 30, "Select Semester ");
	    findCourses = new Fl_Button(480, 750, 120, 30, "Find Courses");

	     //callbacks
	    findCourses->callback(static_FindCoursesClick, this);
	    classBrowser->callback(static_BrowserSelection, this);
	    goBack->callback(static_GobackClick, this);
	    Confirm->callback(static_ConfirmClick, this);
	    projectFileChooserButton->callback(static_chooseProjectFile_cb, this);

	    //Additions to the components
	    classBrowser->scrollbar;
	    classBrowser->color(ASU_WHITE);
		classBrowser->textfont(FL_HELVETICA);
		classBrowser->textsize(16);
		classBrowser->labelcolor(ASU_WHITE);
	    classBrowser->labelfont(FL_HELVETICA_BOLD);
	    classBrowser->labelsize(15);


		findCourses->color(ASU_GOLD);
	    //findCourses->box(FL_SHADOW_BOX);
	    findCourses->labelfont(FL_HELVETICA);
	    findCourses->labelcolor(ASU_BLACK);
	    findCourses->labelsize(15);
	    findCourses->selection_color(ASU_MAROON);

	    inputSemester->add("Spring");
	    inputSemester->add("Summer");
	    inputSemester->add("Fall");
	    inputSemester->value("Fall");
	    //inputSemester->box(FL_SHADOW_BOX);
	    inputSemester->labelfont(FL_HELVETICA);
	    inputSemester->labelcolor(ASU_WHITE);
	    inputSemester->textfont(FL_HELVETICA);
	    inputSemester->menubutton()->color(ASU_GOLD);
	    inputSemester->menubutton()->selection_color(ASU_MAROON);
	    inputSemester->menubutton()->textfont(FL_HELVETICA);
	    inputSemester->menubutton()->box(FL_BORDER_BOX);

	    //inputYear->box(FL_SHADOW_BOX);
	    inputYear->labelfont(FL_HELVETICA);
	    inputYear->labelcolor(ASU_WHITE);
	    inputYear->textfont(FL_HELVETICA);


	//End CLASS SECTION SELECTOR COMPONENTS
	    boxHeader->box(FL_FLAT_BOX);
	    boxHeader->color(ASU_MAROON);
	    boxHeader->labelfont(FL_BOLD);
	    boxHeader->labelsize(20);
	    boxHeader->labelcolor(ASU_WHITE);

	    //Project File Chooser Instructions
	    projectFileInstructionsBox->box(FL_FLAT_BOX);
	    projectFileInstructionsBox->color(ASU_GOLD);
	    projectFileInstructionsBox->labelfont(FL_HELVETICA_BOLD);
	    projectFileInstructionsBox->labelcolor(ASU_BLACK);
	    projectFileInstructionsBox->labelsize(15);
	    projectFileInstructionsBox->label("Step 1: Choose the Project .csv File to be used.");
	    projectFileInstructionsBox->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);

	    // Student Quiz Name Instructions
	    quizFileInstructionsBox->box(FL_FLAT_BOX);
	    quizFileInstructionsBox->color(ASU_GOLD);
	    quizFileInstructionsBox->labelfont(FL_HELVETICA_BOLD);
	    quizFileInstructionsBox->labelcolor(ASU_BLACK);
	    quizFileInstructionsBox->labelsize(15);
	    quizFileInstructionsBox->label("Step 2: Enter name of Capstone Survey Quiz.");
	    quizFileInstructionsBox->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);


		goBack->color(ASU_GOLD);
		//goBack->box(FL_SHADOW_BOX);
		goBack->labelfont(FL_HELVETICA);
		goBack->labelcolor(ASU_BLACK);
		goBack->labelsize(15);
		goBack->selection_color(ASU_MAROON);

		Confirm->color(ASU_GOLD);
		//Confirm->box(FL_SHADOW_BOX);
		Confirm->labelfont(FL_HELVETICA);
		Confirm->labelcolor(ASU_BLACK);
		Confirm->labelsize(15);
		Confirm->selection_color(ASU_MAROON);

	    masterWindow->resizable(boxBack2);
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


	backWindow = new Fl_Window(400, 200, "WARNING");

	const char prompt1[] = "You are about to return to the main screen.";
	const char prompt2[] = "If you do, you will lose all information entered.";
	const char prompt3[] = "Are you sure?";
	backWindow->begin();
	Fl_Box promptBox1(10,10,390,20,prompt1);
	Fl_Box promptBox2(10,30,390,20, prompt2);
	Fl_Box promptBox3(10,50,390,40, prompt3);

	promptBox3.labelsize(20);

	yesButton = new Fl_Button(220,120,80,50,"YES");
	cancelButton1 = new Fl_Button(100,120,100,50, "CANCEL");


	backWindow->color(ASU_GOLD);
	backWindow->box(FL_BORDER_BOX);

	yesButton->color(ASU_MAROON);
	//yesButton->box(FL_SHADOW_BOX);
	yesButton->labelfont(FL_HELVETICA_BOLD);
	yesButton->labelcolor(ASU_WHITE);
	yesButton->labelsize(15);
	yesButton->selection_color(ASU_GREY);

	cancelButton1->color(ASU_MAROON);
	//cancelButton1->box(FL_SHADOW_BOX);
	cancelButton1->labelfont(FL_HELVETICA_BOLD);
	cancelButton1->labelcolor(ASU_WHITE);
	cancelButton1->labelsize(15);
	cancelButton1->selection_color(ASU_GREY);

	//callbacks
	yesButton->callback(static_YesClick, this);
	cancelButton1->callback(static_CancelClick1, this);


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


	confirmWindow = new Fl_Window(400, 200, "Confirmation Window");

	const char prompt1[] = "Does all the information look correct?";
	const char prompt2[] = "Project file:  Blank    Survey Name:  Blank  ";
	const char prompt3[] = "Courses:  Blank ";
	confirmWindow->begin();
	Fl_Box promptBox1(10,10,390,40,prompt1);
	Fl_Box promptBox2(10,50,390,20, prompt2);
	Fl_Box promptBox3(10,70,390,20, prompt3);

	promptBox1.labelsize(20);

	GenerateTeamsButton = new Fl_Button(200,120,170,50,"GENERATE TEAMS");
	cancelButton2 = new Fl_Button(80,120,80,50,"CANCEL");

	confirmWindow->color(ASU_GOLD);
	confirmWindow->box(FL_BORDER_BOX);

	GenerateTeamsButton->color(ASU_MAROON);
	//GenerateTeamsButton->box(FL_SHADOW_BOX);
	GenerateTeamsButton->labelfont(FL_HELVETICA_BOLD);
	GenerateTeamsButton->labelcolor(ASU_WHITE);
	GenerateTeamsButton->labelsize(15);
	GenerateTeamsButton->selection_color(ASU_GREY);

	cancelButton2->color(ASU_MAROON);
	//cancelButton2->box(FL_SHADOW_BOX);
	cancelButton2->labelfont(FL_HELVETICA_BOLD);
	cancelButton2->labelcolor(ASU_WHITE);
	cancelButton2->labelsize(15);
	cancelButton2->selection_color(ASU_GREY);

	//callbacks
	GenerateTeamsButton->callback(static_GenerateTeamsClick, this);
	cancelButton2->callback(static_CancelClick2, this);

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

void DataEntryGUI::chooseProjectFile_cb(Fl_Widget*){
	Fl_Native_File_Chooser fileChooser;
	fileChooser.title("Choose File");
	fileChooser.type(Fl_Native_File_Chooser::BROWSE_FILE);
	fileChooser.preset_file(fileInput_Project->value());
	switch ( fileChooser.show() ) {
		default:
			if ( fileChooser.filename() ) {
				fileInput_Project->value(fileChooser.filename());
			} else {
				fileInput_Project->value("NULL");
			}
			break;
	}
}


