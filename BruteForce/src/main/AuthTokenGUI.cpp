/*
 * AuthTokenGUI.cpp
 *
 * Description:  Contains functions relating to the creation and user
 * interaction with the Authentication Token File chooser of the GUI/application.
 *
 * Created on: Jan 31, 2020
 *
 * Authors:  Team #35
 *
 * List of functions:
 *    - AuthTokenGUI() //constructor
 *    -~AuthTokenGUI() //destructor
 *    -FindFileClick(Fl_Widget* w) //callback function
 *    -GobackClick(Fl_Widget* w) //callback function
 *    -ContinueClick(Fl_Widget* w) //callback function
 *
 */

#include "AuthTokenGUI.h"
#include "ClassSelectorGUI.h"
#include "MainWindow.h"
#include "main.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_File_Browser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_File_Chooser.H>

/*************************************************************************************
 * AuthTokenGUI
 *
 * Description:
 *		Constructor function for the Authentication Token GUI window.
 *
 *Arguments:
 *	nonthing
 *
 *Returns:
 *	nothing
 */
AuthTokenGUI::AuthTokenGUI(Fl_Window* prev, Fl_Window* next) {
	//previous window
	  prevWindow = prev;
	  next = tokenWindow;


	//INITIALIZE COMPONENTS
	    tokenWindow = new Fl_Window(450, 250, "Authentication Token");
	    //FL_(X, Y, W, H, STRING)
	    boxHeader = new Fl_Box(20,20,400,50, "Please Select The File That Contains The Authentication Token.");
	    outputToken = new Fl_Output(20, 150, 410, 30, "");

	    findFile = new Fl_Button(50, 100, 100, 30, "Find File");
	    goBack = new Fl_Button(250, 200, 80, 30, "Go_Back");
	    Continue = new Fl_Button(350, 200, 80, 30, "Continue");

	    //callbacks
	    findFile->callback(static_FindFileClick, this);
	    goBack->callback(static_GobackClick, this);
	    Continue->callback(static_ContinueClick, this);

	    //Additions to the components
	    Continue->deactivate();

	    boxHeader->box(FL_UP_BOX);
	    boxHeader->labelfont(FL_BOLD);
	    boxHeader->labelsize(40);
	    boxHeader->labelcolor(FL_BLUE);

	    tokenWindow->end();
	    tokenWindow->show();

	    Fl::run();

}//end constructor


//destructor
AuthTokenGUI::~AuthTokenGUI() {
	// TODO Auto-generated destructor stub
}




/*************************************************************************************
 * FindFileClick
 *
 * Description:
 *		Opens a file chooser window, and allows thw user to select the Authentication Token
 *		file. Once the file is selected, and OK clicked, the output window is updated with the
 *		authentication token. (The authentication token is read into the code, and stored as a string
 *		for later use.
 *
 *Arguments:
 *	FL_Widget* w
 *
 *Returns:
 *	nothing
 */
void AuthTokenGUI::FindFileClick(Fl_Widget* w){

	Fl_Native_File_Chooser fileChooser;
		fileChooser.title("Choose Authentication Token File");
		fileChooser.type(Fl_Native_File_Chooser::BROWSE_FILE);

		//fileChooser.preset_file(fileInput_Student->value());
		switch ( fileChooser.show() ) {
			default:
				if ( fileChooser.filename() ) {
					//fileInput_Student->value(fileChooser.filename());
				} else {
					//fileInput_Student->value("NULL");
				}
				break;
		}


		//read in the file
		  ifstream AuthtokenFile;
		  AuthtokenFile.open(fileChooser.filename());
		  char output[100];
		  if (AuthtokenFile.is_open()) {
		  while (!AuthtokenFile.eof()) {
			 AuthtokenFile >> output;
		     Authentication_Token = output;
		  }
		 }
		  AuthtokenFile.close();

		  cout<<"The Authentication Token is: "<<Authentication_Token<<endl;

		  //convert the string to char*
		  int length = Authentication_Token.length();
		  char token_char[length+1];
		  strcpy(token_char, Authentication_Token.c_str());


		  outputToken->value(token_char);
		  Continue->activate();


}


/*************************************************************************************
 * FileSelection
 *
 * Description:
 *		This function is the callback for the File Chooser.
 *
 *
 *Arguments:
 *	FL_Widget* w
 *
 *Returns:
 *	nothing
 */
void AuthTokenGUI::FileSelection(Fl_Widget* w){

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
void AuthTokenGUI::GobackClick(Fl_Widget* w){

	tokenWindow->hide();

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
void AuthTokenGUI::ContinueClick(Fl_Widget* w){

	tokenWindow->hide();

	 //call to next GUI window.
	    if(nextWindowFlag == false){
	    ClassSelectorGUI classGUI(tokenWindow);
	    nextWindow = classGUI.classWindow;
	    nextWindowFlag = true;

	    }else{
	    nextWindow->show();
	    cout<<"nextWindow is shown"<<endl;

	    }

}
