/*
 * ResultWindow.h
 *
 * Description:
 *	This class creates the final 'results' window GUI frame and fills in:
 *	- a pie chart to represent the team scores divided into ranges (low to max)
 *	- a spike chart to represent the team scores vs. the project priority
 *	- a spike chart representing the class sections and their respective team scores
 *	- a text display which displays the programs final output per class section:
 *		- each project number, the students assigned to it, and the team score
 *	- it displays 3 buttons:
 *		- the first will be implemented to post the groups to canvas
 *		- the second will store the program results as a .csv file
 *		- the third exits the program.
 *	- It also displays final program outcome information:
 *		- Number of permutations - number of different scenarios
 *			the program calculated through to find the best result
 *		- Number of swaps - number of duplicate students swapped
 *			out until the program found 1 unique team assignment
 *		- Average Team score - the calculated average of all final team scores
 *		- Best Team Score - the team score which is the highest
 *			of all team scores, (team which scored it)
 *		- Worst Team Score - the team score which is the lowest
 *			of all team scores, (team which scored it)
 *
 *
 * Copyright (C) 2020 ASU
 *	Matthew Cilibraise, Myles Colina, Cristi DeLeo, Elizabeth Marquise, Sean Rogers,
 *	initial idea contributed by Douglas Sandy, All rights reserved
 *
 *
 * List of functions:
 *	void ResultWindow(void)
 *		- Constructor, sets up basic framework for the GUI
 *
 *	constexpr int toConstInt(int)
 *		- takes an int and returns it as a const
 *
 *	void saveClicked(Fl_Widget *w)
 *		- action handler for "save .csv" button, saves assignment results
 *
 *	void exitClicked(Fl_Widget *w)
 *		- action handler for the exit button. exits program
 *
 *	void addText(void)
 *		- Adds calculated results into text boxes and graphs
 *
 *	 void calculateStats(void)
 *		- calculates the data needed to add to the text boxes and graphs
 *
 *	void postGroups(Fl_Widget *w)
 *		- event handler for the Post groups button
 *
 *	void ~ResultWindow(void)
 *		- Destructor, properly removes all GUI framework
 */

#ifndef RESULTWINDOW_H_
#define RESULTWINDOW_H_

/********* BEGINNING OF INCLUSIONS **********/

/* Class Inclusions */
#include "Project.h"
#include "ClassSection.h"
#include "Team.h"

/* Library Inclusions */
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <libsoup/soup.h>

/* FLTK Inclusions */
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Input_.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Chart.H>
#include <FL/Fl_Scroll.H>

using namespace std;

/********* BEGINNING OF PROGRAM CODE **********/

class ResultWindow {

	/***** Static event handler functions for buttons *****/
	static void static_saveClicked(Fl_Widget *w, void *data) {
		((ResultWindow*) data)->saveClicked(w);
	}
	void saveClicked(Fl_Widget *w);

	static void static_exitClicked(Fl_Widget *w, void *data) {
		((ResultWindow*) data)->exitClicked(w);
	}
	void exitClicked(Fl_Widget *w);

	static void static_postGroups(Fl_Widget *w, void *data) {
		((ResultWindow*) data)->postGroups(w);
	}

	static void static_recommenderWindow(Fl_Widget *w, void *data) {
		((ResultWindow*) data)->recommenderSystemWindow(w);
	}

	static void static_recommender(Fl_Widget *w, void *data) {
		((ResultWindow*) data)->recommenderSystem(w);
	}

	/***** private variables for data calculations *****/
	int teamScoreAvg, bestScore, badScore;
	int bestTeam, worstTeam, percent, notAssign;
	int low1, low2, avg1, avg2, high1, high2;

public:

	/***** public static variables *****/
	static int permutations;
	static int swaps;
	static int count;
	static int project_pool[5][200];
	static vector<Team> studentTeams;
	static vector<ClassSection> courses;
	static vector<SoupCookie> cookies;

	/***** FLTK GUI frames and text boxes *****/
	Fl_Window *windowResult;
	Fl_Text_Display *textDisplay;
	Fl_Text_Buffer *buffer;
	Fl_Button *buttonSave, *buttonExit, *buttonPostGroups, *buttonRecommender;
	Fl_Box *permBox, *swapBox;
	Fl_Box *teamBox, *bestBox, *badBox;
	Fl_Box *spacer, *borderBox, *borderBox2;
	Fl_Box *labelBox3, *labelBox4, *labelBox5;
	Fl_Box *labelBox1, *labelBox2;
	Fl_Chart *pieChart, *barChart, *classChart;
	Fl_Scroll *scroll1;

	//Recommender window
	Fl_Window *windowRecommender;
	Fl_Text_Display *textDisplay2;
	Fl_Text_Buffer *buffer2;
	Fl_Button *FindReplacements;
	Fl_Input *inputStudent;
	Fl_Box *backBox;
	Fl_Scroll *scroll2;
	/***** functions for class *****/
	ResultWindow();
	~ResultWindow();
	void addText();
	void calculateStats();
	void postGroups(Fl_Widget *w);
	void recommenderSystem(Fl_Widget *w);
	void recommenderSystemWindow(Fl_Widget *w);

};

#endif /*SRC_MAIN_RESULTWINDOW_H_*/
