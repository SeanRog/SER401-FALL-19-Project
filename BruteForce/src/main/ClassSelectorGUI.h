/*
 * ClassSelectorGUI.h
 *
 * Description:  Header file for the class section selector.
 *
 * Created on: Jan 30, 2020
 *
 * Authors:   M. Cilibra, M. Colina, C. DeLeo, E. Marquise, S. Rogers
 *
 */

#ifndef SRC_MAIN_CLASSSELECTORGUI_H_
#define SRC_MAIN_CLASSSELECTORGUI_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Check_Browser.H>
#include <FL/Fl_Output.H>

using namespace std;

class ClassSelectorGUI {

//'static' callback functions which call the real callbacks
	static void static_BrowserSelection(Fl_Widget* w, void * data) {
		((ClassSelectorGUI*)data)->BrowserSelection(w);
	}

	static void static_FindCoursesClick(Fl_Widget* w, void * data) {
		((ClassSelectorGUI*)data)->FindCoursesClick(w);
	}


	static void static_GobackClick(Fl_Widget* w,void * data) {
			((ClassSelectorGUI*)data)->GobackClick(w);
		}

	static void static_ContinueClick(Fl_Widget* w, void * data) {
			((ClassSelectorGUI*)data)->ContinueClick(w);
		}


//callback functions
	void BrowserSelection(Fl_Widget* w);
	void FindCoursesClick(Fl_Widget* w);
	void GobackClick(Fl_Widget* w);
	void ContinueClick(Fl_Widget* w);

public:

	Fl_Window* classWindow;
	Fl_Window* prevWindow;
	Fl_Window* nextWindow;
	Fl_Box *boxHeader;
	Fl_Check_Browser *classBrowser;
	Fl_Button *findCourses;
	Fl_Button *Continue;
	Fl_Button *goBack;
	Fl_Input* inputYear;
	Fl_Input_Choice* inputSemester;
	ClassSelectorGUI(Fl_Window* win);
	virtual ~ClassSelectorGUI();

	//string array of courses for use in testing.
	string courses[17]={"2020Fall-X-SER401-90586","2019Fall-X-SER401-80888",
			"2020Fall-X-SER401-84566","2019Fall-X-SER401-91286","2020Fall-X-SER401-70346",
			"2018Fall-X-SER401-65686","2018Fall-X-SER401-52586","2020Spring-X-SER401-43586",
			"2020Spring-X-SER401-65686","2018Spring-X-SER401-93286","2020Spring-X-SER401-45586",
			"2019Fall-X-SER486-21686","2019Fall-X-SER455-10286","2019Fall-X-SER423-45336",
			"2018Summer-X-SER530-14186","2019Summer-X-SER219-10986","2020Summer-X-SER323-55536",};

};

#endif /* SRC_MAIN_CLASSSELECTORGUI_H_ */
