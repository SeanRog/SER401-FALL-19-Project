#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include "Student.h"
#include "ClassSection.h"
#include "main.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/names.h>

using namespace std;

class MainWindow {

	//generate teams 'static' callback function
	//this function calls the real TeamsButtonClick callback function.
	static void static_TeamsButtonClick(Fl_Widget *w, void *data) {
		((MainWindow*) data)->TeamsButtonClick(w);
	}

	static void static_ProgressTeamsButtonClick(Fl_Widget *w, void *data) {
		((MainWindow*) data)->ProgressTeamsButtonClick(w);
	}
	static void static_DoneButtonClick(Fl_Widget *w, void *data) {
		((MainWindow*) data)->DoneButtonClick(w);
	}

	static void static_StartButtonClick(Fl_Widget *w, void *data) {
		((MainWindow*) data)->StartButtonClick(w);
	}

	// callback functions
	void ProgressTeamsButtonClick(Fl_Widget *w);
	void DoneButtonClick(Fl_Widget *w);
	void StartButtonClick(Fl_Widget *w);
	int handle(int);
	void TeamsButtonClick(Fl_Widget *w);

public:
	static int num_projects;
	static int num_students;
	//string csvProjectFileName;
	bool nextWindowFlag;
	bool Authenticated;
	string mwProjfile;
	vector<Student> studentsFromCanvas;

	vector <ClassSection> mwCourses;
	vector<vector<Student>>  mwAllStudents;
	vector <SoupCookie> mwCookies;

	//progress bar window
	int barCount;
	//Fl_Box *backBox;
	Fl_Window *progressWindow;
	Fl_Progress *progressBar;
	Fl_Box *progressBox;
	Fl_Button *TeamsButton;
	Fl_Button *doneButton;
	Fl_Box *imageBox;
	Fl_Text_Display *terminalTextDisplay;
	Fl_Text_Buffer *terminalBuffer;

	//main window
	Fl_Window *windowMain;
	//ClassSelectorGUI *nextWindow;
	Fl_Window *nextWindow;
	Fl_Box *boxHeader;
	Fl_Button *buttonStart;
	Fl_Button *buttonOpenProject;
	Fl_Button *generateTeams;
	Fl_Int_Input *inputprojects;
	Fl_Int_Input *inputstudents;


	//virtual int handle(int event);
	void MainWindow1();
	void MainWindow2();
	MainWindow();
	~MainWindow();
	void callTeams(Fl_Widget *w);


};

#endif /*SRC_MAIN_MAINWINDOW_H_*/
