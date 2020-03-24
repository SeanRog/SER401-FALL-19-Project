/*
 * DataEntryGUI.cpp
 *
 *  Created on: Feb 6, 2020
 *      Author: myles
 */

#include "DataEntryGUI.h"
#include "MainWindow.h"
#include "GUIStyles.h"
#include "ClassSectionJson.h"
#include "ClassSection.h"
#include "CookieManager.h"
#include "Utility.h"
#include "main.h"

#include <libsoup/soup.h>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <bits/stdc++.h>

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

// ASU LOGO
Fl_PNG_Image LOGO_BLACK1("./Images/asu_sunburst_rgb_maroongold_150ppi.png");
string dataEntryGUIFilename;
vector<SoupCookie> cookiedataDE;



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

DataEntryGUI::DataEntryGUI(Fl_Window *win, vector<SoupCookie> cookies) {

	//reference to the homepage window
	prevWindow = win;
	masterWindow = new Fl_Window(750, 760, "Capstone Team Assignment System");

	cookiedataDE = cookies;
	ClassSectionJson CSJson;

	//read in all the courses from canvas.
	const string CLASS_SECTION_FILE = "./allCourses.json";
	const int NUM_CLASS_SECTIONS = CSJson.getNumClasses(CLASS_SECTION_FILE);
	num_of_all_courses = NUM_CLASS_SECTIONS;
	num_of_selected_courses = 0;

	ClassSection Courses[NUM_CLASS_SECTIONS];


	CSJson.getAllClassSectionJsonObjects(CLASS_SECTION_FILE, Courses);

	//end
	cout<<"Read in all courses!"<<endl;
//<<<<<<< HEAD
	//cout<<Courses[0].Course_Code<<endl;
	//cout<<Courses[1].Course_Code<<endl;
//=======

//>>>>>>> dev

	string courses[NUM_CLASS_SECTIONS];
	AllCourseNames = courses;
	AllCourses = Courses;

	for (int i = 0; i < NUM_CLASS_SECTIONS; i++) {
		AllCourseNames[i] = AllCourses[i].Course_Code;
		cout<<AllCourseNames[i]<<endl;
	}

	//remove("allCourses.json");

	// Initialize components in scope, but not on main data entry gui
	GenerateTeamsButton = NULL;
	yesButton = NULL;
	confirmWindow = NULL;
	cancelButton1 = NULL;
	cancelButton2 = NULL;
	backWindow = NULL;

	//background box 3 - background file chooser
	Fl_Box boxBack3(10, 170, 730, 100);
	boxBack3.box(FL_FLAT_BOX);
	boxBack3.color(ASU_MAROON);

	//background for course selector
	Fl_Box boxBack5(10, 390, 730, 240);
	boxBack5.box(FL_FLAT_BOX);
	boxBack5.color(ASU_MAROON);

	//background for course selector
	Fl_Box boxBack6(10, 640, 730, 110);
	boxBack6.box(FL_FLAT_BOX);
	boxBack6.color(ASU_MAROON);

	//Header box with logo
	boxHeader = new Fl_Box(10, 10, 450, 150,
			"Complete the \ninformation below");
	boxHeader->box(FL_BORDER_BOX);
	boxHeader->color(ASU_BLACK);
	boxHeader->labelfont(FL_HELVETICA_BOLD_ITALIC);
	boxHeader->labelsize(30);
	boxHeader->labelcolor(ASU_WHITE);
	boxHeader->redraw();

	boxHeader2 = new Fl_Box(450, 10, 290, 150);
	boxHeader2->box(FL_BORDER_BOX);
	boxHeader2->color(ASU_BLACK);
	boxHeader2->image(LOGO_BLACK1);
	boxHeader2->redraw();

	// Go back button
	goBack = new Fl_Button(420, 680, 150, 60, "Go Back");
	goBack->color(ASU_GOLD);
	goBack->labelfont(FL_HELVETICA_ITALIC);
	goBack->labelcolor(ASU_BLACK);
	goBack->labelsize(20);
	goBack->selection_color(ASU_MAROON);
	goBack->callback(static_GobackClick, this);

	// Confirm button
	Confirm = new Fl_Button(580, 680, 150, 60, "Confirm");
	Confirm->color(ASU_GOLD);
	Confirm->labelfont(FL_HELVETICA_ITALIC);
	Confirm->labelcolor(ASU_BLACK);
	Confirm->labelsize(20);
	Confirm->selection_color(ASU_MAROON);
	Confirm->callback(static_ConfirmClick, this);

	//Initialize Project File Chooser - Step 1 Choose Project File
	projectFileChooserButton = new Fl_Button(20, 210, 50, 50);
	projectFileChooserButton->callback(static_chooseProjectFile_cb, this);
	fileInput_Project = new Fl_Input(80, 220, 650, 30);
	fileInput_Project->value(".");

	Fl_PNG_Image Folder("./Images/folder.png");
	projectFileChooserButton->color(ASU_GOLD);
	projectFileChooserButton->selection_color(ASU_MAROON);
	projectFileChooserButton->image(Folder);

	//Initialize Student Quiz Textbox - Step 2 Enter name of Capstone Survey
	//background box 3 - background quiz questionnaire
	Fl_Box boxBack4(10, 310, 730, 50);
	boxBack4.box(FL_FLAT_BOX);
	boxBack4.color(ASU_MAROON);
	fileInput_StudentQuizName = new Fl_Input(20, 320, 710, 30);

	//>>>>Set the initial value to Survey. Need to remove for the Final System.
    fileInput_StudentQuizName->value("Survey");

	//INITIALIZE CLASS SECTION SELECTOR COMPONENTS
	// input year
	inputYear = new Fl_Input(220, 460, 100, 40, "Enter Year (YYYY):  ");
	inputYear->labelfont(FL_HELVETICA_BOLD);
	inputYear->labelcolor(ASU_WHITE);
	inputYear->textfont(FL_HELVETICA);
	inputYear->labelsize(15);

	// Class Browser / selector
	classBrowser = new Fl_Check_Browser(360, 410, 370, 210);
	classBrowser->scrollbar;
	classBrowser->color(ASU_WHITE);
	classBrowser->textfont(FL_HELVETICA_ITALIC);
	classBrowser->textsize(18);
	classBrowser->callback(static_BrowserSelection, this);

	// Semester Selector
	inputSemester = new Fl_Input_Choice(220, 410, 100, 40,
			"Select Semester:    ");
	inputSemester->add("Spring");
	inputSemester->add("Summer");
	inputSemester->add("Fall");
	inputSemester->value("Fall");
	inputSemester->textsize(15);
	inputSemester->labelfont(FL_HELVETICA_BOLD);
	inputSemester->labelcolor(ASU_WHITE);
	inputSemester->textfont(FL_HELVETICA);
	inputSemester->labelsize(15);
	inputSemester->menubutton()->color(ASU_GOLD);
	inputSemester->menubutton()->selection_color(ASU_MAROON);
	inputSemester->menubutton()->textfont(FL_HELVETICA);
	inputSemester->menubutton()->box(FL_BORDER_BOX);
	inputSemester->menubutton()->textsize(18);

	//Project File Chooser Instructions
	projectFileInstructionsBox = new Fl_Box(10, 170, 730, 30);
	projectFileInstructionsBox->box(FL_FLAT_BOX);
	projectFileInstructionsBox->color(ASU_GREY);
	projectFileInstructionsBox->labelfont(FL_HELVETICA_BOLD);
	projectFileInstructionsBox->labelcolor(ASU_WHITE);
	projectFileInstructionsBox->labelsize(18);
	projectFileInstructionsBox->label(
			"Step 1: Choose the Project .csv File to be used.");
	projectFileInstructionsBox->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);

	// Student Quiz Name Instructions
	quizFileInstructionsBox = new Fl_Box(10, 280, 730, 30);
	quizFileInstructionsBox->box(FL_FLAT_BOX);
	quizFileInstructionsBox->color(ASU_GREY);
	quizFileInstructionsBox->labelfont(FL_HELVETICA_BOLD);
	quizFileInstructionsBox->labelcolor(ASU_WHITE);
	quizFileInstructionsBox->labelsize(18);
	quizFileInstructionsBox->label(
			"Step 2: Enter name of Capstone Survey Quiz.");
	quizFileInstructionsBox->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);

	// Class Section Instructions
	classSectionInstructionsBox = new Fl_Box(10, 370, 730, 30);
	classSectionInstructionsBox->box(FL_FLAT_BOX);
	classSectionInstructionsBox->color(ASU_GREY);
	classSectionInstructionsBox->labelfont(FL_HELVETICA_BOLD);
	classSectionInstructionsBox->labelcolor(ASU_WHITE);
	classSectionInstructionsBox->labelsize(18);
	classSectionInstructionsBox->label("Step 3: Select Class Sections below.");
	classSectionInstructionsBox->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);

	// Go Back or Confirm Instructions
	goBackorConfirmInstructionsBox = new Fl_Box(10, 640, 730, 30);
	goBackorConfirmInstructionsBox->box(FL_FLAT_BOX);
	goBackorConfirmInstructionsBox->color(ASU_GREY);
	goBackorConfirmInstructionsBox->labelfont(FL_HELVETICA_BOLD);
	goBackorConfirmInstructionsBox->labelcolor(ASU_WHITE);
	goBackorConfirmInstructionsBox->labelsize(18);
	goBackorConfirmInstructionsBox->label("Step 4: Go Back or Confirm");
	goBackorConfirmInstructionsBox->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);

	// Generates course broswer with selections
	findCourses = new Fl_Button(30, 530, 300, 40, "Search for Courses");
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

}	//end constructor

DataEntryGUI::~DataEntryGUI() {
	delete masterWindow;
	delete prevWindow;
	delete boxHeader;
	delete boxHeader2;
	delete classBrowser;
	delete findCourses;
	delete Confirm;
	delete goBack;
	delete inputYear;
	delete inputSemester;
	delete classSectionInstructionsBox;
	delete backWindow;
	delete yesButton;
	delete cancelButton1;
	delete confirmWindow;
	delete GenerateTeamsButton;
	delete cancelButton2;
	delete projectFileInstructionsBox;
	delete projectFileChooserButton;
	delete fileInput_Project;
	delete quizFileInstructionsBox;
	delete fileInput_StudentQuizName;
	delete goBackorConfirmInstructionsBox;
}

//TODO
void DataEntryGUI::BrowserSelection(Fl_Widget *w) {
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
void DataEntryGUI::FindCoursesClick(Fl_Widget *w) {
	string year;
	string semester;
	classBrowser->add("");
	//clear the browser of all entries
	classBrowser->clear();
	year = inputYear->value();
	semester = inputSemester->value();

	for (int i = 1; i < num_of_all_courses; i++)
	{  string course = AllCourseNames[i];
		if ((course.find(year) != string::npos)
				&& (course.find(semester) != string::npos)) {
			int length = course.length();
			char course_char[length + 1];
			strcpy(course_char, course.c_str());
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
void DataEntryGUI::GobackClick(Fl_Widget *w) {
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
void DataEntryGUI::YesClick(Fl_Widget *w) {
	backWindow->hide();
	masterWindow->hide();
	prevWindow->show();
}

void DataEntryGUI::CancelClick1(Fl_Widget *w) {
	backWindow->hide();
}

void DataEntryGUI::CancelClick2(Fl_Widget *w) {
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
void DataEntryGUI::ConfirmClick(Fl_Widget *w) {

	confirmWindow = new Fl_Window(850, 220, "Confirmation Window");

	//course selection values
	vector <string> selections;
	int course_count = 0;

	//project file values
	string projectFilePath = fileInput_Project->value();
	dataEntryGUIFilename = fileInput_Project->value();
	int length = projectFilePath.length();
	char prompt1[length + 1];
	strcpy(prompt1, projectFilePath.c_str());

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
			   //int char_size = sizeof(classBrowser->text(i)) / sizeof(char);
				//string text1 = convertToString(classBrowser->text(i), char_size);
				//selections[i] = text1;
				selections.push_back(classBrowser->text(i));

				course_count++;
				first = 1;
			} else {
				classes = classes + ", " + classBrowser->text(i);
				selections.push_back(classBrowser->text(i));
				//selections[i] = classBrowser->text(i);
				//selections[i] = classBrowser->text(i);
				course_count++;
			}
		}
	}
	length = classes.length();
	char prompt3[length + 1];
	strcpy(prompt3, classes.c_str());

	string s[course_count];
	if(course_count>0){

	//once courses are selected read and store them in a string array

	for (int i = 0; i < course_count; i++) {
		s[i] = selections[i];
	}
	num_of_selected_courses = course_count;
	SelectedCourseNames = s;
	}


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

void DataEntryGUI::GenerateTeamsClick(Fl_Widget *w) {

	//store the selected class sections into a new Class section Array.
	//for use in the assignment system.
	ClassSection classes[num_of_selected_courses];

	for (int i = 0; i < num_of_all_courses; i++) {
		for (int j = 0; j < num_of_selected_courses; j++) {


		if((AllCourses[i].Course_Code).compare(SelectedCourseNames[j]) == 0){
			classes[j] = AllCourses[i];
		}
		}

	}
	SelectedCourses=classes;

	for (int j = 0; j < num_of_selected_courses; j++) {

		cout<<classes[j].Course_Name<<"  "<<classes[j].OfficialClassID<<SelectedCourses[j].Course_Code<<" "<<SelectedCourses[j].OfficialClassID<<endl;
	}

	//Get the Quiz data from the student survey.
	string QuizName = fileInput_StudentQuizName->value();
    CookieManager CM;
    Utility util;

	//Get Student data from each course
	// test with one course
	//CM.getStudents(cookiedataDE, 47570);
	vector<vector<Student>> allStudents;
	vector<Student> students;
	for (int j = 0; j < num_of_selected_courses; j++) {
		students = CM.getStudents(cookiedataDE, classes[j].OfficialClassID);

		CM.getQuizzes(cookiedataDE, classes[j].OfficialClassID, QuizName, students);
		students = CM.currentStudents;

		allStudents.push_back(students);
	}

	// debug students
	cout << endl << "Debugging Students" << endl;
	for (int j = 0; j < allStudents.size(); j++){
		for (int k = 0; k < allStudents.at(j).size(); k++){
			cout << "ClassID: "<< allStudents.at(j).at(k).ClassID << endl;
			cout << "StudentID: "<< allStudents.at(j).at(k).StudentID << endl;
			cout << "ASUriteID: "<< allStudents.at(j).at(k).ASUriteID << endl;
			cout<<"name: "<<allStudents.at(j).at(k).name<<endl;

			cout<<"Affinity: "<<endl;
			for(int x = 0;x< 6;x++){
			cout<<allStudents.at(j).at(k).StudentAffinity[x].first<<allStudents.at(j).at(k).StudentAffinity[x].second<<endl;
			}

			cout<<"skill scores: "<<endl;
			for(int x = 0; x<14 ;x++){
			cout<<"skill "<<to_string(x+1)<<": "<<allStudents.at(j).at(k).Skills[x]<<endl;
			}

			cout<<"Availability: "<<endl;
			for(int x = 0; x<4 ;x++){
			cout<<allStudents.at(j).at(k).Availability[x]<<endl;
			}

		}
	}

	masterWindow->hide();
	confirmWindow->hide();
	MainWindow mainWin;
	mainWin.mwProjfile = dataEntryGUIFilename;
	mainWin.callTeams(w);
}

void DataEntryGUI::chooseProjectFile_cb(Fl_Widget*) {
	string filename;

	// Create the file chooser, and show it
	Fl_File_Chooser chooser(".","*",
			Fl_File_Chooser::SINGLE,
			"Select Project CSV file");

	chooser.color(ASU_WHITE);
	chooser.textfont(FL_HELVETICA);

	chooser.show();

	// Block until user picks something.
	//     (The other way to do this is to use a callback())
	//
	while (chooser.shown()) {
		Fl::wait();

		if (chooser.value() != NULL) {
			fileInput_Project->value(chooser.value());
			filename = chooser.value();

		} else {
			fileInput_Project->value("NULL");
		}
	}

}

// Callback: when user picks 'Quit'
void quit_cb(Fl_Widget*, void*) {
	exit(0);
}
