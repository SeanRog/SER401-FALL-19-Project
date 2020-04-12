/*
 * ResultWindow.cpp
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


/********* BEGINNING OF INCLUSIONS **********/


/* Class Inclusions */
#include "ResultWindow.h"
#include "main.h"
#include "GUIStyles.h"
#include "Project.h"
#include "CookieManager.h"
#include "Utility.h"


/* Library inclusions */
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>


/* FLTK Inclusions */
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
#include <FL/Fl_Chart.H>


using namespace std;


/********* BEGINNING OF PROGRAM CODE **********/


/*********************************************************
 * Title: constexpr int toConstInt(int)
 *
 * Description: Function to convert integers into constant expressions
 *
 * Arguments: int
 *
 * Returns: constexpr int
 */
constexpr int toConstInt(int constInt) {
	return constInt;
}


/*********************************************************
 * Title: void ResultWindow(void)
 *
 * Description: class constructor. Preps the results window GUI, boxes,
 		labels, graphs, text display and text buffer
 *
 * Arguments: none
 *
 * Returns: none
 */
ResultWindow::ResultWindow() {


	/***** Creates the main window frame *****/
	windowResult = new Fl_Window(1500, 800, "Capstone Team Assignment Results");


	/***** Creates the black border frame boxes around GUI *****/
	Fl_Box *backBox1 = new Fl_Box(0, 0, 10, 800);
	backBox1->box(FL_FLAT_BOX);
	backBox1->color(ASU_BLACK);

	Fl_Box *backBox2 = new Fl_Box(0, 0, 1500, 10);
	backBox2->box(FL_FLAT_BOX);
	backBox2->color(ASU_BLACK);

	Fl_Box *backBox3 = new Fl_Box(0, 790, 1000, 10);
	backBox3->box(FL_FLAT_BOX);
	backBox3->color(ASU_BLACK);

	borderBox = new Fl_Box(840, 0, 660, 800);
	borderBox->box(FL_FLAT_BOX);
	borderBox->color(ASU_BLACK);

	borderBox2 = new Fl_Box(850, 10, 640, 70);
	borderBox2->box(FL_FLAT_BOX);
	borderBox2->color(ASU_GREY);


	/***** Creates the text Buffer and text display to be filled
	 * by program output and styles it accordingly *****/

	// Buffer
	buffer = new Fl_Text_Buffer();

	//Text Display
	textDisplay = new Fl_Text_Display(850, 80, 640, 710);
	textDisplay->buffer(buffer);
	textDisplay->textfont(FL_HELVETICA);
	textDisplay->textsize(15);
	textDisplay->selection_color(ASU_GOLD);


	/***** Create the 3 buttons above the text display and styles it accordingly *****/

	/* "Post Teams" BUTTON, this will post team assignment result to CANVAS */
	buttonPostGroups = new Fl_Button(870, 20, 175, 50, "Post Groups");
	buttonPostGroups->color(ASU_GOLD);
	buttonPostGroups->labelfont(FL_HELVETICA);
	buttonPostGroups->labelcolor(ASU_BLACK);
	buttonPostGroups->labelsize(15);
	buttonPostGroups->selection_color(ASU_BLACK);
//uncomment this to activate the post teams button.
//buttonPostGroups->callback(static_postGroups, this);

	/* "Save to .csv" BUTTON, this creates a .csv file of the team assignment results */
	buttonSave = new Fl_Button(1070, 20, 175, 50, "Save .csv Report");
	buttonSave->color(ASU_GOLD);
	buttonSave->labelfont(FL_HELVETICA);
	buttonSave->labelcolor(ASU_BLACK);
	buttonSave->labelsize(15);
	buttonSave->selection_color(ASU_BLACK);
	buttonSave->callback(static_saveClicked, this);

	/* "Exit" BUTTON, this properly exits the program */
	buttonExit = new Fl_Button(1270, 20, 175, 50, "Exit");
	buttonExit->color(ASU_GOLD);
	buttonExit->labelfont(FL_HELVETICA);
	buttonExit->labelcolor(ASU_BLACK);
	buttonExit->labelsize(15);
	buttonExit->selection_color(ASU_BLACK);
	buttonExit->callback(static_exitClicked, this);


	/***** This section creates the text boxes to display program
	 * calculations/results and then styles the boxes accordingly.
	 * Text is filled in with later function( addText()) *****/

	/* "Number of Permutations", Number of assignment
	 * possibilities the program calculated */
	permBox = new Fl_Box(410, 90, 5, 20, "");
	permBox->box(FL_FLAT_BOX);
	permBox->color(ASU_GREY);
	permBox->align(FL_ALIGN_RIGHT);
	permBox->labelfont(FL_HELVETICA_BOLD);
	permBox->labelsize(15);
	permBox->labelcolor(ASU_WHITE);

	/* "Number of swaps", Number of duplicate students that
	 * had to be swapped out to find unique assignment*/
	swapBox = new Fl_Box(410, 120, 5, 20, "");
	swapBox->box(FL_FLAT_BOX);
	swapBox->color(ASU_GREY);
	swapBox->align(FL_ALIGN_RIGHT);
	swapBox->labelfont(FL_HELVETICA_BOLD);
	swapBox->labelsize(15);
	swapBox->labelcolor(ASU_WHITE);

	/* "Average Team Score", gives the average team score */
	teamBox = new Fl_Box(410, 150, 5, 20, "");
	teamBox->box(FL_FLAT_BOX);
	teamBox->color(ASU_GREY);
	teamBox->align(FL_ALIGN_RIGHT);
	teamBox->labelfont(FL_HELVETICA_BOLD);
	teamBox->labelsize(15);
	teamBox->labelcolor(ASU_WHITE);

	/* "Best Team Score: (), gives the highest team score and team */
	bestBox = new Fl_Box(410, 210, 5, 20, "");
	bestBox->box(FL_FLAT_BOX);
	bestBox->color(ASU_GREY);
	bestBox->align(FL_ALIGN_RIGHT);
	bestBox->labelfont(FL_HELVETICA_BOLD);
	bestBox->labelsize(15);
	bestBox->labelcolor(ASU_WHITE);

	/* "Worst Team Score: (), gives the lowest team score and team */
	badBox = new Fl_Box(410, 180, 5, 20, "");
	badBox->box(FL_FLAT_BOX);
	badBox->color(ASU_GREY);
	badBox->align(FL_ALIGN_RIGHT);
	badBox->labelfont(FL_HELVETICA_BOLD);
	badBox->labelsize(15);
	badBox->labelcolor(ASU_WHITE);


	/***** This section contains labels for the project priority graph *****/

	/* Creates the "low" level in blue to correspond with graph */
	labelBox3 = new Fl_Box(170, 280, 5, 15, "Low");
	labelBox3->box(FL_FLAT_BOX);
	labelBox3->color(ASU_GREY);
	labelBox3->align(FL_ALIGN_RIGHT);
	labelBox3->labelfont(FL_HELVETICA_BOLD);
	labelBox3->labelsize(12);
	labelBox3->labelcolor(ASU_BLUE);

	/* Creates the "medium" level in orange to correspond with graph */
	labelBox4 = new Fl_Box(395, 280, 5, 15, "Medium");
	labelBox4->box(FL_FLAT_BOX);
	labelBox4->color(ASU_GREY);
	labelBox4->align(FL_ALIGN_RIGHT);
	labelBox4->labelfont(FL_HELVETICA_BOLD);
	labelBox4->labelsize(12);
	labelBox4->labelcolor(ASU_ORANGE);

	/* Creates the "high" level in gold to correspond with graph */
	labelBox5 = new Fl_Box(620, 280, 5, 15, "High");
	labelBox5->box(FL_FLAT_BOX);
	labelBox5->color(ASU_GREY);
	labelBox5->align(FL_ALIGN_RIGHT);
	labelBox5->labelfont(FL_HELVETICA_BOLD);
	labelBox5->labelsize(12);
	labelBox5->labelcolor(ASU_GOLD);


	/***** This section creates the 3 graphs for the GUI window and styles accordingly *****/

	/* Creates a pie chart that takes the max team score - min team score, divides this
	 * into 6 ranges, and displays how many teams are within each range. This gives
	 * the user an idea of overall calculated team scores, or how well the program did*/
	pieChart = new Fl_Chart(20, 20, 380, 220,
			"Number of Teams within Score Range");
	pieChart->type(FL_PIE_CHART);
	pieChart->textfont(FL_HELVETICA);
	pieChart->textcolor(ASU_BLACK);
	pieChart->textsize(14);
	pieChart->labelfont(FL_HELVETICA_BOLD);
	pieChart->labelsize(16);
	pieChart->labelcolor(ASU_WHITE);

	/* This creates a spike chart which shows the team scores compared to the
	 * project priority (low/med/high). That way the user can see that the high
	 * priority projects hopefully have better team scores */
	barChart = new Fl_Chart(20, 300, 810, 210,
			"Team Scores by Project Priority");
	barChart->type(FL_SPIKE_CHART);
	barChart->textfont(FL_HELVETICA);
	barChart->textcolor(ASU_BLACK);
	barChart->textsize(12);
	barChart->labelfont(FL_HELVETICA_BOLD);
	barChart->labelsize(16);
	barChart->labelcolor(ASU_WHITE);

	/* The class chart shows each class section and their corresponding
	 * team scores. That way the suer can determine that each section
	 * is overall the same */
	classChart = new Fl_Chart(20, 545, 810, 220,
			"Team Scores per Class Section");
	classChart->type(FL_SPIKE_CHART);
	classChart->textfont(FL_HELVETICA);
	classChart->textcolor(ASU_BLACK);
	classChart->textsize(14);
	classChart->labelfont(FL_HELVETICA_BOLD);
	classChart->labelsize(16);
	classChart->labelcolor(ASU_WHITE);

}


/*********************************************************
 * Title: void saveClicked(Fl_Widget *w)
 *
 * Description: event handler for the save button. Saves file as .csv
 *
 * Arguments: results window widget
 *
 * Returns: none, saves .csv to computer
 */
void ResultWindow::saveClicked(Fl_Widget *w) {
	buffer->savefile("results.csv", 1000000);
}


/*********************************************************
 * Title: void exitClicked(Fl_Widget *w)
 *
 * Description: event handler for the exit button. exits program
 *
 * Arguments: results window widget
 *
 * Returns: none, saves .csv to computer
 */
void ResultWindow::exitClicked(Fl_Widget *w) {
	exit(0);
}


/*********************************************************
 * Title: void addText(void)
 *
 * Description: Adds calculated results into text boxes and graphs
 *
 * Arguments: none
 *
 * Returns: none
 */
void ResultWindow::addText() {

	/***** Calls another function to calculate the data *****/
	calculateStats();


	/***** Fills in text boxes with data by copying data into a char array and
	* then copying from a char array into a const char*, for FLTK parameters*****/

	/* fills permutation box label with data results */
	char permNum[70];
	int buff = sprintf(permNum, "Number of possible permutations: %d",
			permutations);
	const char *permNum1 = permNum;
	permBox->label(permNum1);

	/* fills swap box label with data results */
	char swapNum[70];
	buff = sprintf(swapNum, "Number of students swapped:        %d", swaps);
	const char *swapNum1 = swapNum;
	swapBox->label(swapNum1);

	/* fills average team score label with data results */
	char teamNum[70];
	buff = sprintf(teamNum, "Average Team Score:  %d", teamScoreAvg);
	const char *teamNum1 = teamNum;
	teamBox->label(teamNum1);

	/* fills best team score label with data results */
	char bestNum[70];
	buff = sprintf(bestNum, "Best Team Score:         %d (Team %d)", bestScore,
			bestTeam);
	const char *bestNum1 = bestNum;
	bestBox->label(bestNum1);

	/* fills worst team score label with data results */
	char badNum[70];
	buff = sprintf(badNum, "Worst Team Score:      %d (Team %d)", badScore,
			worstTeam);
	const char *badNum1 = badNum;
	badBox->label(badNum1);


	/***** Fills in pie chart graph with data by copying data into a char array and
	* then copying from a char array into a const char*, for FLTK parameters. The pie
	* chart is divided into 6 sections: lowest, second lowest, low average, high average,
	* second highest scores and then highest scores. These ranges are calculated out from
	* the range max to min score, divided into 6 section ranges *****/

	/* fills lowest section pie charts with data results */
	char low1a[50];
	buff = sprintf(low1a, " %d-%d (%d)", badScore, badScore + percent, low1);
	const char *low1b = low1a;
	pieChart->add(low1, low1b, ASU_GREEN);

	/* fills second lowest pie chart with data results */
	char low2a[50];
	buff = sprintf(low2a, " %d-%d (%d)", badScore + (percent) + 1,
			badScore + (percent * 2) + 1, low2);
	const char *low2b = low2a;
	pieChart->add(low2, low2b, ASU_BLUE);

	/* fills in low average pie chart with data results */
	char avg1a[50];
	buff = sprintf(avg1a, " %d-%d (%d)", badScore + (percent * 2) + 2,
			badScore + (percent * 3) + 1, avg1);
	const char *avg1b = avg1a;
	pieChart->add(avg1, avg1b, ASU_WHITE);

	/* fills in high average pie chart with data results */
	char avg2a[50];
	buff = sprintf(avg2a, " %d-%d (%d)", badScore + (percent * 3) + 2,
			badScore + (percent * 4) + 1, avg2);
	const char *avg2b = avg2a;
	pieChart->add(avg2, avg2b, ASU_ORANGE);

	/* fills in second highest pie chart with data results */
	char high1a[50];
	buff = sprintf(high1a, " %d-%d (%d)", badScore + (percent * 4) + 2,
			badScore + (percent * 5) + 1, high1);
	const char *high1b = high1a;
	pieChart->add(high1, high1b, ASU_GOLD);

	/* fills in highest pie chart with data results */
	char high2a[50];
	buff = sprintf(high2a, " %d-%d (%d)", badScore + (percent * 5) + 2,
			bestScore, high2);
	const char *high2b = high2a;
	pieChart->add(high2, high2b, ASU_MAROON);


	/***** Fills in project priority spike chart graph with data by copying data into a
	* char array and then copying from a char array into a const char*, for FLTK parameters.
	* The project priority chart loops through all team assignment array 3 times. First, it
	* looks for low priority and adds to the graph, then medium priority and then high
	* priority. For each different priority it has a corresponding color to distinguish*****/

	/* Filling in low project priority chart  - blue */
	for (int i = 0; i < count; i++) {
		if (project_pool[1][i] == 0 && project_pool[2][i] != 0) {
			char priob[2];
			buff = sprintf(priob, "%d", project_pool[2][i]);
			const char *prioa = priob;
			barChart->add(project_pool[2][i], prioa, ASU_BLUE);
		}
	}

	/* Filling in medium project priority chart  - orange */
	for (int i = 0; i < count; i++) {
		if (project_pool[1][i] == 1 && project_pool[2][i] != 0) {
			char priob[2];
			buff = sprintf(priob, "%d", project_pool[2][i]);
			const char *prioa = priob;
			barChart->add(project_pool[2][i], prioa, ASU_ORANGE);
		}
	}

	/* Filling in high project priority chart  - gold */
	for (int i = 0; i < count; i++) {
		if (project_pool[1][i] == 2 && project_pool[2][i] != 0) {
			char priob[2];
			buff = sprintf(priob, "%d", project_pool[2][i]);
			const char *prioa = priob;
			barChart->add(project_pool[2][i], prioa, ASU_GOLD);
		}
	}


	/***** Fills in class section spike chart graph with data by copying data
	 * into a char array and then copying from a char array into a const char*,
	 * for FLTK parameters. The project priority chart loops through all team
	 * assignment array multiple times. First, it loops through to distinguish
	 * how many different sections there are and then it loops through to find
	 * any matching class sections. Then it displays each class section, varying
	 * in color for different sections to distinguish *****/

	/* class section chart variables */
	int count1 = 0, sections[10], changed = 0;

	/* looping through to find each class section and display all of their team scores */
	for (int j = 0; j < count; j++) {
		for (int i = 0; i < count; i++) {

			/* if the class section matches and has not already been displayed */
			if (project_pool[3][i] == project_pool[3][j]
					&& project_pool[4][i] != 1) {

				/* notes the new class section and marks it as displayed */
				if (project_pool[3][i] != sections[count1 - 1]) {
					sections[count1] = project_pool[3][i];
					count1++;
					changed = 1;
				}

				/* variables to copy data into and use to display */
				project_pool[4][i] = 1;
				char priob[10];

				/* if a new class section */
				if (changed == 1) {

					/* separate each class section with "0"s */
					classChart->add(0, "", ASU_MAROON);
					classChart->add(0, "", ASU_MAROON);

					/* copying from a char array into a const char*, for
					* FLTK parameters, displaying new section # for user */

					buff = sprintf(priob, "S#%d-  %d", project_pool[3][i],
							project_pool[2][i]);
					changed = 0;

				/* else if it is in the same section add on */
				} else {
					buff = sprintf(priob, "%d", project_pool[2][i]);
				}
				const char *prioa = priob;

				/* this section alternates the color so that each class section can
				 * be distinguished on the chart. Maroon / gold/ maroon /gold, etc */

				if (j % 2 == 0) {
					classChart->add(project_pool[2][i], prioa, ASU_GOLD);
				} else {
					classChart->add(project_pool[2][i], prioa, ASU_MAROON);
				}
			}
		}
	}


	/* gives space at end of chart to match spacing throughout entire chart */
	classChart->add(0, "", ASU_MAROON);
	classChart->add(0, "", ASU_MAROON);


	/* Show  and run the result window */
	windowResult->resizable(textDisplay);
	windowResult->color(ASU_GREY);
	windowResult->show();
	windowResult->end();
	Fl::run();
}


/*********************************************************
 * Title: void calculateStats(void)
 *
 * Description: Calculates the data needed to add to the text boxes and graphs
 *
 * Arguments: none
 *
 * Returns: none
 */
void ResultWindow::calculateStats() {

	//initialize variables
	teamScoreAvg = 0, bestScore = 0, badScore = 100, notAssign = 0;
	int next1 = 0, next2 = 0;
	low1 = 0, low2 = 0, avg1 = 0, avg2 = 0, high1 = 0, high2 = 0;
	string line;


	//calculating average team score
	for (int i = 0; i < count; i++) {
		if (project_pool[2][i] != 0) {
			teamScoreAvg += project_pool[2][i];
		} else {
			notAssign++;
		}
	}

	teamScoreAvg = teamScoreAvg / (count - notAssign);


	//calculating best team score
	for (int i = 0; i < count; i++) {
		if (project_pool[2][i] > bestScore) {
			bestScore = project_pool[2][i];
			bestTeam = i;
		}
	}


	//calculating worst team score
	for (int i = 0; i < count; i++) {
		if ((project_pool[2][i] < badScore) && (project_pool[2][i] != 0)) {
			badScore = project_pool[2][i];
			worstTeam = i;
		}
	}


	/* subtracts max - mine score and divides it into 6 for pie
	 * chart, so each time the program is run, it will divide the
	 * results into 6 sections */
	percent = (bestScore - badScore) / 6;

	//filling teams within 6 data groups for pie chart
	for (int i = 0; i < count; i++) {
		if (project_pool[2][i] <= (badScore + percent)) {
			low1++;
		}
		if ((project_pool[2][i] <= badScore + (percent * 2))
				&& (project_pool[2][i]) > (badScore + percent)) {
			low2++;
		}
		if ((project_pool[2][i] <= badScore + (percent * 3))
				&& (project_pool[2][i]) > (badScore + percent * 2)) {
			avg1++;
		}
		if ((project_pool[2][i] <= badScore + (percent * 4))
				&& (project_pool[2][i]) > (badScore + percent * 3)) {
			avg2++;
		}
		if ((project_pool[2][i] <= badScore + (percent * 5))
				&& (project_pool[2][i]) > (badScore + percent * 4)) {
			high1++;
		}
		if ((project_pool[2][i] <= bestScore)
				&& (project_pool[2][i]) > (badScore + percent * 5)) {
			high2++;
		}
	}
}


/*********************************************************
 * Title: void postGroups(Fl_Widget *w)
 *
 * Description: event handler for the Post groups button
 *
 * Arguments: results window widget
 *
 * Returns: none, saves groups to canvas
 */
void ResultWindow::postGroups(Fl_Widget *w) {

	cout << "Post Groups clicked" << endl;

	/* Initializing canvas connection */
	CookieManager canvas;


	/* vector pair to store the courseID and the Group_CategoryID */
	vector<pair<int, int>> course_group;


	/* loops through courses to match section to class*/
	for (int i = 0; i < courses.size(); i++) {

		cout << "Here 1 " << endl;
		int groupCategory_ID = canvas.postGroupCategories(cookies, courses[i]);

		cout << groupCategory_ID << endl;

		course_group.push_back(
				make_pair(courses[i].OfficialClassID, groupCategory_ID));

	}


	/* Loops through student teams to match to class section courses */
	for (int i = 0; i < studentTeams.size(); i++) {

		for (int j = 0; j < courses.size(); j++) {

			if (studentTeams[i].OfficialClassID == courses[j].OfficialClassID) {

				for (int k = 0; k < course_group.size(); k++) {

					if (course_group[k].first
							== studentTeams[i].OfficialClassID) {

						//make and get the group ID for this team
						int group_ID = canvas.postGroups(cookies,
								course_group[k].first, course_group[k].second,
								studentTeams[i].project.ProjectID);

						cout << group_ID << endl;

						//edit the group and add in the students
						canvas.putStudentstoGroups(cookies, studentTeams[i],
								group_ID);

					}
				}
			}
		}
	}
}


/*********************************************************
 * Title: void ~ResultWindow(void)
 *
 * Description: class destructor. Properly removes all GUI framework
 *
 * Arguments: none
 *
 * Returns: none
 */
ResultWindow::~ResultWindow() {
	delete windowResult;
	delete textDisplay;
	delete buffer;
	delete buttonSave;
	delete buttonExit;
	delete permBox;
	delete swapBox;
	delete borderBox;
	delete borderBox2;
	delete buttonPostGroups;
	delete teamBox;
	delete bestBox;
	delete badBox;
	delete labelBox3;
	delete labelBox4;
	delete labelBox5;
	delete pieChart;
	delete barChart;
	delete classChart;
}
