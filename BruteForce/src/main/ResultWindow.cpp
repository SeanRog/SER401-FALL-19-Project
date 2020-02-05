/*
 * ResultWindow.cpp
 *
 * Description:  prints out the team assignment results for the user to review
 *
 *
 * Created on:   01/29/2020
 *
 * Authors:   M. Cilibra, M. Colina, C. DeLeo, E. Marquise, S. Rogers
 *
 * List of functions:
 *
 */

#include "ResultWindow.h"
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
#include <FL/Fl_Text_Display.H>



using namespace std;


//Function to convert integers into constant expressions.
constexpr int toConstInt(int constInt) {
	return constInt;
}


/* constructor, preps the results window and buffer */
ResultWindow::ResultWindow() {

    // MAIN WINDOW
    windowResult = new Fl_Window(640, 480, "Project 35");

    // Buffer
    buffer = new Fl_Text_Buffer();

    //Text Display
    textDisplay = new Fl_Text_Display(20,90,640-40,480-110, "Results:");
    textDisplay->buffer(buffer);

    //Save BUTTON
    buttonSave = new Fl_Button(20,20,100,50, "Save Report");
    buttonSave->callback(static_saveClicked, this);

}


/* event handler for the save button. Saves file as .txt */
void ResultWindow::saveClicked(Fl_Widget* w) {
	cout <<"Saving Report as PDF" <<endl;
	buffer->savefile("results.csv", 1000000);
}


/* method to show the results window once the buffer has been filled */
void ResultWindow::addText() {
    windowResult->resizable(textDisplay);
    windowResult->show();
    windowResult->end();
    Fl::run();
}


// DESTRUCTOR
ResultWindow::~ResultWindow() {
    // TODO
}
