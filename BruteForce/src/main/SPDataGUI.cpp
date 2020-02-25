/*
 * SPDataGUI.cpp
 *
 *  Created on: Feb 25, 2020
 *      Author: myles
 */

#include "SPDataGUI.h"
#include "SteamPunkGUI1.h"
#include "GUIStyles.h"
#include "main.h"
#include "SteamPunkGUI1.h"

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

Fl_PNG_Image Pipes1("./Images/Steampunk/PipesBrick1.png");
Fl_PNG_Image Pipes2("./Images/Steampunk/PipesBrick2.png");
Fl_PNG_Image Wall1("./Images/Steampunk/Wall1.png");
Fl_PNG_Image Wall2("./Images/Steampunk/Wall3.png");
Fl_PNG_Image Wall3("./Images/Steampunk/Wall14.png");


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
SPDataGUI::SPDataGUI(Fl_Window *win) {

	//reference to the homepage window
	prevWindow = win;

	masterWindow = new Fl_Window(750, 790, "Capstone Team Assignment System");

	//background box 3 - background file chooser
	Fl_Box boxBack3(10, 170, 730, 100);
	boxBack3.box(FL_FLAT_BOX);
	boxBack3.color(ASU_BLACK);
	boxBack3.image(Wall2);

	//background for course selector
	Fl_Box boxBack5(10, 390, 730, 237);
	boxBack5.box(FL_FLAT_BOX);
	boxBack5.image(Wall1);
	boxBack5.color(ASU_BLACK);

	//background for course selector
	Fl_Box boxBack6(10, 670, 730, 105);
	boxBack6.box(FL_FLAT_BOX);
	boxBack6.color(ASU_MAROON);
	boxBack6.image(Pipes2);

	boxHeader2 = new Fl_Box(10, 10, 730, 150);
	boxHeader2->box(FL_BORDER_BOX);
	boxHeader2->color(ASU_BLACK);
	boxHeader2->image(Pipes1);
	boxHeader2->redraw();

	//Header box with logo
	boxHeader = new Fl_Box(35, 10, 450, 150,
			"Complete the \ninformation below");
	boxHeader->box(FL_NO_BOX);
	boxHeader->color(ASU_BLACK);
	boxHeader->labelfont(FL_TIMES_BOLD_ITALIC);
	boxHeader->labelsize(30);
	boxHeader->labelcolor(ASU_BLACK);
	boxHeader->redraw();

	// Go back button
	goBack = new Fl_Button(412, 695, 150, 60, "Go Back");
	goBack->color(DARK_BRASS);
	goBack->labelfont(FL_TIMES_BOLD_ITALIC);
	goBack->labelcolor(ASU_BLACK);
	goBack->labelsize(20);
	goBack->selection_color(DARK);
	goBack->callback(static_GobackClick, this);

	// Confirm button
	Confirm = new Fl_Button(576, 695, 150, 60, "Confirm");
	Confirm->color(DARK_BRASS);
	Confirm->labelfont(FL_TIMES_BOLD_ITALIC);
	Confirm->labelcolor(ASU_BLACK);
	Confirm->labelsize(20);
	Confirm->selection_color(DARK);
	Confirm->callback(static_ConfirmClick, this);

	//Initialize Project File Chooser - Step 1 Choose Project File
	projectFileChooserButton = new Fl_Button(20, 210, 50, 50);
	projectFileChooserButton->callback(static_chooseProjectFile_cb, this);
	fileInput_Project = new Fl_Input(80, 220, 650, 30);
	fileInput_Project->value(".");
	fileInput_Project->textfont(FL_TIMES_ITALIC);

	Fl_PNG_Image Folder("./Images/folder.png");
	projectFileChooserButton->color(DARK_BRASS);
	projectFileChooserButton->selection_color(DARK);
	projectFileChooserButton->image(Folder);

	//Initialize Student Quiz Textbox - Step 2 Enter name of Capstone Survey
	//background box 3 - background quiz questionnaire
	Fl_Box boxBack4(10, 310, 730, 50);
	boxBack4.box(FL_FLAT_BOX);
	boxBack4.color(ASU_MAROON);
	boxBack4.image(Wall3);
	fileInput_StudentQuizName = new Fl_Input(20, 320, 710, 30);
	fileInput_StudentQuizName->textfont(FL_TIMES_ITALIC);

	//INITIALIZE CLASS SECTION SELECTOR COMPONENTS
	// input year
	inputYear = new Fl_Input(220, 460, 100, 40, "Enter Year (YYYY):  ");
	inputYear->labelfont(FL_TIMES_BOLD_ITALIC);
	inputYear->labelcolor(ASU_WHITE);
	inputYear->textfont(FL_TIMES_ITALIC);
	inputYear->labelsize(15);

	// Class Browser / selector
	classBrowser = new Fl_Check_Browser(360, 410, 370, 190);
	classBrowser->scrollbar;
	classBrowser->color(ASU_WHITE);
	classBrowser->labelfont(FL_TIMES_ITALIC);
	classBrowser->textsize(18);
	classBrowser->textfont(FL_TIMES_BOLD_ITALIC);
	classBrowser->callback(static_BrowserSelection, this);

	// Semester Selector
	inputSemester = new Fl_Input_Choice(220, 410, 100, 40,
			"Select Semester:    ");
	inputSemester->add("Spring");
	inputSemester->add("Summer");
	inputSemester->add("Fall");
	inputSemester->value("Fall");
	inputSemester->textsize(15);
	inputSemester->labelfont(FL_TIMES_BOLD_ITALIC);
	inputSemester->labelcolor(ASU_WHITE);
	inputSemester->textfont(FL_TIMES_ITALIC);
	inputSemester->labelsize(15);
	inputSemester->menubutton()->color(DARK_BRASS);
	inputSemester->menubutton()->selection_color(DARK);
	inputSemester->menubutton()->textfont(FL_TIMES_ITALIC);
	inputSemester->menubutton()->box(FL_BORDER_BOX);
	inputSemester->menubutton()->textsize(18);

	//Project File Chooser Instructions
	projectFileInstructionsBox = new Fl_Box(10, 170, 730, 30);
	projectFileInstructionsBox->box(FL_FLAT_BOX);

	projectFileInstructionsBox->color(DARK);
	projectFileInstructionsBox->labelfont(FL_TIMES_BOLD_ITALIC);
	projectFileInstructionsBox->labelcolor(ASU_WHITE);

	projectFileInstructionsBox->labelsize(18);
	projectFileInstructionsBox->label(
			"Step 1: Choose the Project .csv File to be used.");
	projectFileInstructionsBox->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);

	// Student Quiz Name Instructions
	quizFileInstructionsBox = new Fl_Box(10, 280, 730, 30);
	quizFileInstructionsBox->box(FL_FLAT_BOX);

	quizFileInstructionsBox->color(DARK);
	quizFileInstructionsBox->labelfont(FL_TIMES_BOLD_ITALIC);
	quizFileInstructionsBox->labelcolor(ASU_WHITE);

	quizFileInstructionsBox->labelsize(18);
	quizFileInstructionsBox->label(
			"Step 2: Enter name of Capstone Survey Quiz.");
	quizFileInstructionsBox->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);

	// Class Section Instructions
	classSectionInstructionsBox = new Fl_Box(10, 370, 730, 30);
	classSectionInstructionsBox->box(FL_FLAT_BOX);

	classSectionInstructionsBox->color(DARK);
	classSectionInstructionsBox->labelfont(FL_TIMES_BOLD_ITALIC);
	classSectionInstructionsBox->labelcolor(ASU_WHITE);

	classSectionInstructionsBox->labelsize(18);
	classSectionInstructionsBox->label("Step 3: Select Class Sections below.");
	classSectionInstructionsBox->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);

	// Go Back or Confirm Instructions
	goBackorConfirmInstructionsBox = new Fl_Box(10, 640, 730, 30);
	goBackorConfirmInstructionsBox->box(FL_FLAT_BOX);

	goBackorConfirmInstructionsBox->color(DARK);
	goBackorConfirmInstructionsBox->labelfont(FL_TIMES_BOLD_ITALIC);
	goBackorConfirmInstructionsBox->labelcolor(ASU_WHITE);

	goBackorConfirmInstructionsBox->labelsize(18);
	goBackorConfirmInstructionsBox->label("Step 4: Go Back or Confirm");
	goBackorConfirmInstructionsBox->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);

	// Generates course broswer with selections
	findCourses = new Fl_Button(30, 530, 300, 40, "Search for Courses");
	findCourses->color(DARK_BRASS);
	findCourses->labelfont(FL_TIMES_BOLD_ITALIC);
	findCourses->labelcolor(ASU_BLACK);
	findCourses->labelsize(18);
	findCourses->selection_color(DARK);
	findCourses->callback(static_FindCoursesClick, this);

	masterWindow->color(DARK_TAUPE);
	masterWindow->box(FL_BORDER_BOX);
	masterWindow->show();
	masterWindow->end();


	Fl::run();

}	    //end constructor

SPDataGUI::~SPDataGUI() {
	// TODO Auto-generated destructor stub
}

//TODO
void SPDataGUI::BrowserSelection(Fl_Widget *w) {

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
void SPDataGUI::FindCoursesClick(Fl_Widget *w) {

	classBrowser->add("");
	//clear the browser of all entries
	classBrowser->clear();

	string year;
	string semester;

	year = inputYear->value();
	semester = inputSemester->value();

	cout << year << endl;
	cout << semester << endl;


	for (auto &course : courses) {

		if ((course.find(year) != string::npos)
				&& (course.find(semester) != string::npos)) {

			int length = course.length();
			char course_char[length + 1];
			strcpy(course_char, course.c_str());

			cout << course << endl;
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
void SPDataGUI::GobackClick(Fl_Widget *w) {

	backWindow = new Fl_Window(650, 220, "Capstone Team Assignment System");
	backWindow->begin();

	Fl_Box promptBox1(0, 10, 650, 50, "WARNING!");
	promptBox1.align(FL_ALIGN_CENTER);
	promptBox1.labelsize(40);

	Fl_Box promptBox2(50, 70, 550, 20,
			"You are about to return to the main screen,");
	promptBox2.align(FL_ALIGN_CENTER);
	promptBox2.labelsize(20);
	promptBox2.labelfont(FL_HELVETICA);

	Fl_Box promptBox3(50, 90, 550, 20, "All information entered will be lost");
	promptBox3.align(FL_ALIGN_CENTER);
	promptBox3.labelsize(20);
	promptBox3.labelfont(FL_HELVETICA_BOLD_ITALIC);

	Fl_Box promptBox4(50, 110, 550, 20, "Are you sure?");
	promptBox4.align(FL_ALIGN_CENTER);
	promptBox4.labelsize(20);
	promptBox4.labelfont(FL_HELVETICA);

	yesButton = new Fl_Button(425, 150, 175, 50, "Yes");
	yesButton->color(ASU_WHITE);
	yesButton->labelfont(FL_HELVETICA);
	yesButton->labelcolor(ASU_BLACK);
	yesButton->labelsize(15);
	yesButton->selection_color(ASU_MAROON);
	yesButton->callback(static_YesClick, this);

	cancelButton1 = new Fl_Button(40, 150, 175, 50, "Cancel");
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
void SPDataGUI::YesClick(Fl_Widget *w) {

	backWindow->hide();
	masterWindow->hide();
	prevWindow->show();

}

void SPDataGUI::CancelClick1(Fl_Widget *w) {

	backWindow->hide();
}

void SPDataGUI::CancelClick2(Fl_Widget *w) {

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
void SPDataGUI::ConfirmClick(Fl_Widget *w) {

	confirmWindow = new Fl_Window(850, 220, "Confirmation Window");

	//project file values
	string proj = fileInput_Project->value();
	int length = proj.length();
	char prompt1[length + 1];
	strcpy(prompt1, proj.c_str());

	// questionnaire name value
	string quest = fileInput_StudentQuizName->value();
	length = quest.length();
	char prompt2[length + 1];
	strcpy(prompt2, quest.c_str());

	// broswer selection values
	string classes = "";
	int first = 0;
	for (int i = 0; i <= classBrowser->nitems(); i++) {
		if (classBrowser->checked(i)) {
			if (first == 0) {
				classes = classes + classBrowser->text(i);
				first = 1;
			} else {
				classes = classes + ", " + classBrowser->text(i);
			}
		}
	}
	length = classes.length();
	char prompt3[length + 1];
	strcpy(prompt3, classes.c_str());


	confirmWindow->begin();

	Fl_Box promptBox1(0, 10, 850, 30, "Does all the information look correct?");

	promptBox1.align(FL_ALIGN_CENTER);
	promptBox1.labelsize(30);

	Fl_Box promptBox2(20, 60, 20, 20, "Project file:");
	promptBox2.align(FL_ALIGN_RIGHT);
	promptBox2.labelsize(15);
	promptBox2.labelfont(FL_HELVETICA_BOLD);
	Fl_Box promptBox2R(130, 60, 50, 20, prompt1);
	promptBox2R.align(FL_ALIGN_RIGHT);
	promptBox2R.labelsize(15);
	promptBox2R.labelfont(FL_HELVETICA);

	Fl_Box promptBox3(20, 80, 20, 20, "Survey Name:");
	promptBox3.align(FL_ALIGN_RIGHT);
	promptBox3.labelsize(15);
	promptBox3.labelfont(FL_HELVETICA_BOLD);
	Fl_Box promptBox3R(130, 80, 50, 20, prompt2);
	promptBox3R.align(FL_ALIGN_RIGHT);
	promptBox3R.labelsize(15);
	promptBox3R.labelfont(FL_HELVETICA);

	Fl_Box promptBox4(20, 100, 20, 20, "Courses:");
	promptBox4.align(FL_ALIGN_RIGHT);
	promptBox4.labelsize(15);
	promptBox4.labelfont(FL_HELVETICA_BOLD);
	Fl_Box promptBox4R(130, 100, 50, 20, prompt3);
	promptBox4R.align(FL_ALIGN_RIGHT);
	promptBox4R.labelsize(15);
	promptBox4R.labelfont(FL_HELVETICA);


	GenerateTeamsButton = new Fl_Button(635, 150, 175, 50, "Generate Teams");
	GenerateTeamsButton->color(ASU_WHITE);
	GenerateTeamsButton->labelfont(FL_HELVETICA);
	GenerateTeamsButton->labelcolor(ASU_BLACK);
	GenerateTeamsButton->labelsize(15);
	GenerateTeamsButton->selection_color(ASU_MAROON);
	GenerateTeamsButton->callback(static_GenerateTeamsClick, this);

	cancelButton2 = new Fl_Button(40, 150, 175, 50, "Cancel");
	cancelButton2->color(ASU_WHITE);
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

void SPDataGUI::GenerateTeamsClick(Fl_Widget *w) {

	masterWindow->hide();
	confirmWindow->hide();

	//MainWindow mainWin;
	SteamPunkGUI1 mainWin;
	mainWin.callTeams(w);

}

void SPDataGUI::chooseProjectFile_cb(Fl_Widget*) {
	Fl_Native_File_Chooser fileChooser;
	fileChooser.title("Choose File");
	fileChooser.type(Fl_Native_File_Chooser::BROWSE_FILE);
	fileChooser.preset_file(fileInput_Project->value());
	switch (fileChooser.show()) {
	default:
		if (fileChooser.filename()) {
			fileInput_Project->value(fileChooser.filename());
		} else {
			fileInput_Project->value("NULL");
		}
		break;
	}
}


