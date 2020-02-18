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
#include "GUIStyles.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Input_.H>
#include <FL/Fl_Text_Buffer.H>

using namespace std;

//Function to convert integers into constant expressions.
constexpr int toConstInt(int constInt) {
	return constInt;
}

/* constructor, preps the results window and buffer */
ResultWindow::ResultWindow() {

	// MAIN WINDOW
	windowResult = new Fl_Window(900, 600, "Capstone Team Assignment Results");

	Fl_Box *backBox1 = new Fl_Box(0, 0, 10, 200);
	backBox1->box(FL_FLAT_BOX);
	backBox1->color(ASU_BLACK);

	Fl_Box *backBox2 = new Fl_Box(0, 0, 900, 10);
	backBox2->box(FL_FLAT_BOX);
	backBox2->color(ASU_BLACK);

	Fl_Box *backBox3 = new Fl_Box(890, 0, 10, 200);
	backBox3->box(FL_FLAT_BOX);
	backBox3->color(ASU_BLACK);

	// Buffer
	buffer = new Fl_Text_Buffer();
	borderBox = new Fl_Box(0, 200, 900, 400);
	borderBox->box(FL_FLAT_BOX);
	borderBox->color(ASU_BLACK);

	//Text Display
	textDisplay = new Fl_Text_Display(10, 210, 900 - 20, 600 - 220);
	textDisplay->buffer(buffer);
	textDisplay->textfont(FL_HELVETICA);
	textDisplay->textsize(15);

	//Save BUTTON
	buttonSave = new Fl_Button(50, 130, 175, 50, "Save .csv Report");
	buttonSave->color(ASU_GOLD);
	buttonSave->labelfont(FL_HELVETICA);
	buttonSave->labelcolor(ASU_BLACK);
	buttonSave->labelsize(15);
	buttonSave->selection_color(ASU_BLACK);
	buttonSave->callback(static_saveClicked, this);

	permBox = new Fl_Box(275, 130, 5, 20, "");
	permBox->box(FL_FLAT_BOX);
	permBox->color(ASU_MAROON);
	permBox->align(FL_ALIGN_RIGHT);
	permBox->labelfont(FL_HELVETICA_BOLD);
	permBox->labelsize(15);
	permBox->labelcolor(ASU_WHITE);

	swapBox = new Fl_Box(275, 160, 5, 20, "");
	swapBox->box(FL_FLAT_BOX);
	swapBox->color(ASU_MAROON);
	swapBox->align(FL_ALIGN_RIGHT);
	swapBox->labelfont(FL_HELVETICA_BOLD);
	swapBox->labelsize(15);
	swapBox->labelcolor(ASU_WHITE);

}

/* event handler for the save button. Saves file as .txt */
void ResultWindow::saveClicked(Fl_Widget *w) {
	buffer->savefile("results.csv", 1000000);
}

/* method to show the results window once the buffer has been filled */
void ResultWindow::addText() {

	char permNum[50];
	int buff = sprintf(permNum, "Number of possible permutations: %d",
			permutations);
	const char *permNum1 = permNum;
	permBox->label(permNum1);

	char swapNum[50];
	buff = sprintf(swapNum, "Number of students swapped: %d", swaps);
	const char *swapNum1 = swapNum;
	swapBox->label(swapNum1);

	windowResult->resizable(textDisplay);
	windowResult->color(ASU_MAROON);
	windowResult->show();
	windowResult->end();
	Fl::run();
}

// DESTRUCTOR
ResultWindow::~ResultWindow() {
	// TODO
}
