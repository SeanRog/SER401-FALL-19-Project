/*
 * AuthTokenGUI.h
 *
 *  Created on: Jan 31, 2020
 *      Author: myles
 */

#ifndef SRC_MAIN_AUTHTOKENGUI_H_
#define SRC_MAIN_AUTHTOKENGUI_H_
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Check_Browser.H>
#include <FL/Fl_File_Browser.H>
#include <FL/Fl_Output.H>

#include "MainWindow.h"

using namespace std;

class AuthTokenGUI {

		//'static' callback functions which call the real callbacks
		static void static_FileSelection(Fl_Widget* w, void * data) {
			((AuthTokenGUI*)data)->FileSelection(w);
		}

		//'static' callback functions which call the real callbacks
		static void static_FindFileClick(Fl_Widget* w, void * data) {
			((AuthTokenGUI*)data)->FindFileClick(w);
		}

		static void static_GobackClick(Fl_Widget* w,void * data) {
			((AuthTokenGUI*)data)->GobackClick(w);
		}

		static void static_ContinueClick(Fl_Widget* w, void * data) {
			((AuthTokenGUI*)data)->ContinueClick(w);
		}


	//callback functions
	void FileSelection(Fl_Widget* w);
	void FindFileClick(Fl_Widget* w);
	void GobackClick(Fl_Widget* w);
	void ContinueClick(Fl_Widget* w);

public:

	string Authentication_Token;
	bool nextWindowFlag;

	Fl_File_Chooser* tokenChooser;
	Fl_Window* tokenWindow;
	Fl_Window* prevWindow;
	Fl_Window* nextWindow;

	Fl_Box *boxHeader;
	Fl_Output *outputToken;
	Fl_Button *findFile;
	Fl_Button *Continue;
	Fl_Button *goBack;

	AuthTokenGUI(Fl_Window* prev, Fl_Window* next);
	virtual ~AuthTokenGUI();
};

#endif /* SRC_MAIN_AUTHTOKENGUI_H_ */
