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
#include "StudentsToProjects.h"
#include "Utility.h"

/* Library inclusions */
#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <string>
#include <mutex>

#include <bits/stdc++.h>
#include "sys/types.h"
#include "sys/sysinfo.h"

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
#include <FL/Fl_Scroll.H>

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
	windowResult = new Fl_Window(1500, 800, "CLIQUE - Results");
	scroll1 =  new Fl_Scroll(0,0,1500,800);
	scroll1->color(ASU_GREY);//background color

	/***** Creates the Title Box *****/
	Fl_Box *titleBox = new Fl_Box(450, 10, 300, 50,
			"FINAL RESULTS");
	titleBox->box(FL_NO_BOX);
	titleBox->labelcolor(ASU_GOLD);
	titleBox->labelfont(FL_HELVETICA_BOLD_ITALIC);
	titleBox->labelsize(30);

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

	borderBox2 = new Fl_Box(850, 10, 640, 130);
	borderBox2->box(FL_FLAT_BOX);
	borderBox2->color(ASU_GREY);

	/***** Creates the text Buffer and text display to be filled
	 * by program output and styles it accordingly *****/

	// Buffer
	buffer = new Fl_Text_Buffer();

	//Text Display
	textDisplay = new Fl_Text_Display(850, 140, 640, 650);
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

	/* "Recommender System" BUTTON, this opens up the replacment team recommender window */
	buttonRecommender = new Fl_Button(1005, 80, 300, 50,
			"Replacement Team Recommender");
	buttonRecommender->color(ASU_GOLD);
	buttonRecommender->labelfont(FL_HELVETICA);
	buttonRecommender->labelcolor(ASU_BLACK);
	buttonRecommender->labelsize(15);
	buttonRecommender->selection_color(ASU_BLACK);
	buttonRecommender->callback(static_recommenderWindow, this);

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
	scroll1->end();
	windowResult->resizable(scroll1);
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

	//cout << "Post Groups clicked" << endl;

	/* Initializing canvas connection */
	CookieManager canvas;

	/* vector pair to store the courseID and the Group_CategoryID */
	vector<pair<int, int>> course_group;

	/* loops through courses to match section to class*/
	for (int i = 0; i < courses.size(); i++) {

		//cout << "Here 1 " << endl;
		int groupCategory_ID = canvas.postGroupCategories(cookies, courses[i]);

		//cout << groupCategory_ID << endl;

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

						//cout << group_ID << endl;

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
 * Title: recommenderSystemWindow(Fl_Widget *w)
 *
 * Description: event handler for the recommender System button.
 * Opens a new GUI window for searching for replacment team
 * options for any student. Input both for the student's ASUtriteID,
 * and a text display showing the output, once the 'Find Replacement Teams'
 * button is clicked.
 *
 * Author: Myles
 *
 * Arguments: results window widget
 *
 * Returns: nothing
 */
void ResultWindow::recommenderSystemWindow(Fl_Widget *w) {

	// MAIN WINDOW
	windowRecommender = new Fl_Window(840, 640,
			"CLIQUE - Team Replacement Recommendation System");
	scroll2 =  new Fl_Scroll(0,0,840,640);
	scroll2->color(ASU_GREY);//background color

	//Title box
	Fl_Box *titleBox = new Fl_Box(140, 10, 690, 30,
			"REPLACEMENT TEAM RECOMMENDER");
	titleBox->box(FL_NO_BOX);
	titleBox->labelcolor(ASU_GOLD);
	titleBox->labelfont(FL_HELVETICA_BOLD);
	titleBox->labelsize(25);

	Fl_Box *backBox1 =
			new Fl_Box(140, 40, 690, 30,
					"Finds the best replacement project and team for a certain student.");
	backBox1->box(FL_NO_BOX);
	backBox1->labelcolor(ASU_WHITE);
	backBox1->labelfont(FL_HELVETICA);
	backBox1->labelsize(15);
	backBox1->color(ASU_BLACK);

	Fl_Box *backBox2 =
			new Fl_Box(140, 70, 690, 30,
					"Gives the top choices for (teams of 4) and top choices for (teams of 5).");
	backBox2->box(FL_NO_BOX);
	backBox2->labelcolor(ASU_WHITE);
	backBox2->labelfont(FL_HELVETICA);
	backBox2->labelsize(15);
	backBox2->color(ASU_BLACK);

	Fl_Box *backBox3 =
			new Fl_Box(140, 100, 690, 30,
					"For teams of 5, the system recommends which student would be best to swap out.");
	backBox3->box(FL_NO_BOX);
	backBox3->labelcolor(ASU_WHITE);
	backBox3->labelfont(FL_HELVETICA);
	backBox3->labelsize(15);
	backBox3->color(ASU_BLACK);

	//image box
	Fl_PNG_Image logo("./Images/CapstoneTeams120by120.png");
	Fl_Box *imageBox = new Fl_Box(20, 10, 120, 120);
	imageBox->box(FL_NO_BOX);
	imageBox->image(logo);

	//text input
	inputStudent = new Fl_Input(300, 160, 150, 50,
			"Enter the student's asuriteID  ");
	inputStudent->labelfont(FL_HELVETICA_BOLD);
	inputStudent->labelcolor(ASU_WHITE);
	inputStudent->textfont(FL_HELVETICA);
	inputStudent->labelsize(15);

	// Buffer
	buffer2 = new Fl_Text_Buffer();

	//Text Display
	textDisplay2 = new Fl_Text_Display(20, 220, 800, 400);
	textDisplay2->buffer(buffer2);
	textDisplay2->textfont(FL_HELVETICA);
	textDisplay2->textsize(15);
	textDisplay2->selection_color(ASU_GOLD);

	//Post Teams BUTTON
	FindReplacements = new Fl_Button(560, 160, 250, 50,
			"Find Replacement Teams");
	FindReplacements->color(ASU_GOLD);
	FindReplacements->labelfont(FL_HELVETICA);
	FindReplacements->labelcolor(ASU_BLACK);
	FindReplacements->labelsize(15);
	FindReplacements->selection_color(ASU_BLACK);
	//button callback
	FindReplacements->callback(static_recommender, this);

	scroll2->end();
	windowRecommender->resizable(scroll2);
	windowRecommender->color(ASU_GREY);
	windowRecommender->show();
	windowRecommender->end();
	Fl::run();

}

//function to sort in descending order.
bool reverseSort(const pair<int, Team> &a, const pair<int, Team> &b) {
	return (a.first > b.first);
}

/*********************************************************
 * Title: recommenderSystem(Fl_Widget *w)
 *
 * Description: event handler for the Find Replacement Teams button.
 * This function finds the best replacement project and team for a certain student.
 *  Gives the top choices for (teams of 4) and top choices for (teams of 5).
 *  For teams of 5, the system also recommends which student would be best to swap out.
 *  This function takes into account the negative affinity, NDA/IPR, and configures a new
 *  team score for every possible combination for possible new project teams for this student.
 *  The only choices that are shown, are teams that have no negative affinity, and are listed
 *  in order from the best scoring team, to the lowest scoring.
 *
 *	Author: Myles
 *
 * Arguments: recommender window widget
 *
 * Returns: nothing
 */
void ResultWindow::recommenderSystem(Fl_Widget *w) {

	//Needed Variables
	string asuriteIDX = inputStudent->value();
	Student studentX;
	Team teamX;
	int classIDX;
	int placeIDX;
	int numSkills = 14;
	int bestTeamScore = 0;

	vector<Team> teamsOf4;
	vector<Team> teamsOf5;
	Team BestTeamOf5, BestTeamOf4;
	vector<pair<int, Team>> topTeams5, topTeams4;
	bool isTeam4;
	bool teamXis4 = false;
	studentX.name = "null";

	BestTeamOf4.projectID = 99999;
	BestTeamOf5.projectID = 99999;

	//find the team, and class section the student belongs to.
	for (int i = 0; i < studentTeams.size(); i++) {
		for (int j = 0; j < 5; j++) {
			if (studentTeams[i].team[j].ASUriteID.compare(asuriteIDX) == 0) {

				studentX = studentTeams[i].team[j];
				teamX = studentTeams[i];
				classIDX = studentTeams[i].ClassID;
				placeIDX = j;
				break;
			}
		}
	}

	//find all the teams of 4 and 5 that are in the same class section
	for (int i = 0; i < studentTeams.size(); i++) {

		if (studentTeams[i].ClassID == classIDX) {
			isTeam4 = false;
			for (int j = 0; j < 5; j++) {

				if (studentTeams[i].team[j].StudentID == 99999) {

					isTeam4 = true;
				}
			}
			if (isTeam4 == true) {
				teamsOf4.push_back(studentTeams[i]);
			} else {
				teamsOf5.push_back(studentTeams[i]);
			}

		}
	}

	//find out if the student's team is a team of 4 or not.
	for (int i = 0; i < 5; i++) {
		if (teamX.team[i].StudentID == 99999) {
			teamXis4 = true;
		}
	}

	StudentsToProjects stp;

	/*TEAMS OF 4 */
	//find the best team of 4 that the student can be placed in
	for (int i = 0; i < teamsOf4.size(); i++) {

		for (int j = 0; j < 5; j++) {
			if (teamsOf4[i].team[j].StudentID == 99999) {

				int OldTeamScore = teamsOf4[i].TeamScore;
				Team currentTeam = teamsOf4[i];
				currentTeam.team[j] = studentX;
				//find each students skill sums
				int studentSkillSums[5];
				int studentProjectSkills[5];
				int skillSum = 0;
				for (int x = 0; x < 5; x++) {
					studentSkillSums[x] = 0;
					studentProjectSkills[x] = 0;
					for (int y = 0; y < numSkills; y++) {
						studentSkillSums[x] += currentTeam.team[x].Skills[y];
						studentProjectSkills[x] += currentTeam.team[x].Skills[y]
								* currentTeam.project.Skills[y];
					}

					skillSum += studentSkillSums[x];
				}

				//Calculate max skill score for the current project.
				int maxProjectScore = 0;
				for (int y = 0; y < numSkills; y++) {
					maxProjectScore += currentTeam.project.Skills[y] * 4;
				}
				maxProjectScore = maxProjectScore * 5;

				currentTeam.TeamScore = stp.ProjectCompareTeamScore(
						studentProjectSkills, maxProjectScore)
						+ stp.SkillCompareTeamScore(studentSkillSums)
						+ stp.AvailabilityTeamScore(currentTeam.team);

				if ((stp.NegativeAffinityCheck(currentTeam.team) == false)
						&& (stp.NDA_IPRCheck(currentTeam.team,
								currentTeam.project) == true)) {

					if (currentTeam.TeamScore >= OldTeamScore
							|| bestTeamScore
									< (OldTeamScore - currentTeam.TeamScore)) {

						bestTeamScore = OldTeamScore - currentTeam.TeamScore;
						BestTeamOf4 = currentTeam;

					}

					if (OldTeamScore <= currentTeam.TeamScore
							&& currentTeam.project.ProjectID
									!= teamX.project.ProjectID) {
						pair<int, Team> temp;
						temp.first = currentTeam.TeamScore;
						temp.second = currentTeam;

						topTeams4.push_back(temp);
					}
				}

			}
		}
	}
	bestTeamScore = 0;

	/*TEAMS OF 5*/
	//find the best team of 5 that the student can be placed in,
	//and the student to be swapped.
	for (int i = 0; i < teamsOf5.size(); i++) {

		for (int k = 0; k < 5; k++) {
			int oldTeamScore = teamsOf5[i].TeamScore;
			int teamXScore = teamX.TeamScore;
			Student replacedStudent = teamsOf5[i].team[k];
			Team currentTeam = teamsOf5[i];
			Team replacedTeam = teamX;
			replacedTeam.team[placeIDX] = replacedStudent;

			currentTeam.team[k] = studentX;

			//find each students skill sums
			int studentSkillSums[5];
			int studentProjectSkills[5];
			int skillSum = 0;
			for (int x = 0; x < 5; x++) {
				studentSkillSums[x] = 0;
				studentProjectSkills[x] = 0;
				for (int y = 0; y < numSkills; y++) {
					studentSkillSums[x] += currentTeam.team[x].Skills[y];
					studentProjectSkills[x] += currentTeam.team[x].Skills[y]
							* currentTeam.project.Skills[y];
				}

				skillSum += studentSkillSums[x];
			}

			//Calculate max skill score for the current project.
			int maxProjectScore = 0;
			for (int y = 0; y < numSkills; y++) {
				maxProjectScore += currentTeam.project.Skills[y] * 4;
			}
			maxProjectScore = maxProjectScore * 5;

			currentTeam.TeamScore = stp.ProjectCompareTeamScore(
					studentProjectSkills, maxProjectScore)
					+ stp.SkillCompareTeamScore(studentSkillSums)
					+ stp.AvailabilityTeamScore(currentTeam.team);

			//now for the team of the replacement student
			//find each students skill sums
			int studentSkillSums2[5];
			int studentProjectSkills2[5];
			int skillSum2 = 0;
			for (int x = 0; x < 5; x++) {
				studentSkillSums2[x] = 0;
				studentProjectSkills2[x] = 0;
				for (int y = 0; y < numSkills; y++) {
					studentSkillSums2[x] += replacedTeam.team[x].Skills[y];
					studentProjectSkills2[x] += replacedTeam.team[x].Skills[y]
							* replacedTeam.project.Skills[y];
				}

				skillSum2 += studentSkillSums2[x];
			}

			//Calculate max skill score for the current project.
			int maxProjectScore2 = 0;
			for (int y = 0; y < numSkills; y++) {
				maxProjectScore2 += replacedTeam.project.Skills[y] * 4;
			}
			maxProjectScore2 = maxProjectScore * 5;

			replacedTeam.TeamScore = stp.ProjectCompareTeamScore(
					studentProjectSkills2, maxProjectScore2)
					+ stp.SkillCompareTeamScore(studentSkillSums2)
					+ stp.AvailabilityTeamScore(replacedTeam.team);

			if ((stp.NegativeAffinityCheck(currentTeam.team) == false)
					&& (stp.NDA_IPRCheck(currentTeam.team, currentTeam.project)
							== true)) {

				if ((stp.NegativeAffinityCheck(replacedTeam.team) == false)
						&& (stp.NDA_IPRCheck(replacedTeam.team,
								replacedTeam.project) == true)) {

					if (currentTeam.TeamScore >= bestTeamScore
							&& currentTeam.project.ProjectID
									!= teamX.project.ProjectID) {
						bestTeamScore = currentTeam.TeamScore;
						BestTeamOf5 = currentTeam;
					}

					if (oldTeamScore <= currentTeam.TeamScore
							&& currentTeam.project.ProjectID
									!= teamX.project.ProjectID) {
						pair<int, Team> temp;
						temp.first = currentTeam.TeamScore;
						temp.second = currentTeam;
						topTeams5.push_back(temp);
					}

				}

			}
		}

	}

	//If the student is an actual student find and display all the possible replacment
	//project teams.
	if (studentX.name.compare("null") != 0) {
		//now sort through the list of teams to get the top 5.
		sort(topTeams4.begin(), topTeams4.end(), reverseSort);

		sort(topTeams5.begin(), topTeams5.end(), reverseSort);

		//Print out to the display all the following information
		string output = "";
		output += "STUDENT:   " + studentX.name + "\n";
		output += "ASUriteID:  " + studentX.ASUriteID + "\n";
		output += "CLASS ID:   " + to_string(studentX.ClassID) + "\n";
		output += "CURRENT PROJECT: #" + to_string(studentX.ProjectID) + "\n";
		if (teamXis4 == false) {
			output += "CURRENT TEAM SIZE: 5\n";
		} else {
			output += "CURRENT TEAM SIZE: 4\n";

		}

		if (teamXis4 == false || topTeams5.size() == 0) {

			output += "\n     Recommended replacement teams of 4 \n";
			output +=
					"======================================================\n";

			if (BestTeamOf4.projectID != 99999 || topTeams5.size() == 0) {
				output += "Best replacement Team of 4: ";
				output += "Project #" + to_string(BestTeamOf4.project.ProjectID)
						+ "  New TeamScore: " + to_string(BestTeamOf4.TeamScore)
						+ "\n";
				output += "Students: ";
				for (int j = 0; j < 5; j++) {
					output += " " + BestTeamOf4.team[j].name + ", ";

				}
				output += "\n\n";

			}

			for (int i = 0; i < topTeams4.size(); i++) {

				output += "*Project #"
						+ to_string(topTeams4[i].second.project.ProjectID)
						+ "  New TeamScore: " + to_string(topTeams4[i].first)
						+ "\n";
				output += "Students: ";
				for (int j = 0; j < 5; j++) {
					output += " " + topTeams4[i].second.team[j].name + ", ";

				}
				output += "\n\n";

			}
		}

		output += "\n     Recommended replacement teams of 5 \n";
		output += "======================================================\n";
		output += "\n";

		if (BestTeamOf5.projectID != 99999 && topTeams5.size() == 0) {
			Student replacedStudent;
			output += "Best replacement Team of 5: ";
			output += "Project #" + to_string(BestTeamOf5.project.ProjectID)
					+ "  New TeamScore: " + to_string(BestTeamOf5.TeamScore)
					+ "\n";

			for (int i = 0; i < teamsOf5.size(); i++) {
				if (BestTeamOf5.project.ProjectID
						== teamsOf5[i].project.ProjectID) {
					for (int j = 0; j < 5; j++) {
						if ((studentX.name).compare(BestTeamOf5.team[j].name)
								== 0) {
							replacedStudent = teamsOf5[i].team[j];
							output += "Student to be replaced -> ASUriteID:"
									+ teamsOf5[i].team[j].ASUriteID + "  name: "
									+ teamsOf5[i].team[j].name + "\n";

						}
					}
				}
			}
			output += "Students: ";
			for (int j = 0; j < 5; j++) {
				output += " " + BestTeamOf5.team[j].name + ", ";

			}
			output += "\n";

			output += "New Team for Project #"
					+ to_string(teamX.project.ProjectID) + "\n";
			output += "Student Team: ";
			for (int j = 0; j < 5; j++) {
				if ((studentX.name).compare(teamX.team[j].name) == 0) {
					output += replacedStudent.name + ", ";
				} else {
					output += teamX.team[j].name + ", ";

				}
			}
			output += "\n";

		}

		for (int i = 0; i < topTeams5.size(); i++) {

			Student replacedStudent;
			if (i == 0) {
				output += "*Project #"
						+ to_string(topTeams5[i].second.project.ProjectID)
						+ "  New TeamScore: " + to_string(topTeams5[i].first)
						+ "\n";

				for (int x = 0; x < teamsOf5.size(); x++) {

					if (topTeams5[i].second.project.ProjectID
							== teamsOf5[x].project.ProjectID) {
						for (int j = 0; j < 5; j++) {
							if ((studentX.name).compare(
									topTeams5[i].second.team[j].name) == 0) {
								replacedStudent = teamsOf5[x].team[j];
								output += "Student to be replaced -> ASUriteID:"
										+ teamsOf5[x].team[j].ASUriteID
										+ "  name: " + teamsOf5[x].team[j].name
										+ "\n";
							}
						}
					}
				}
				output += "Students: ";
				for (int j = 0; j < 5; j++) {
					output += " " + topTeams5[i].second.team[j].name + ", ";
				}
				output += "\n";

				output += "New Team for Project #"
						+ to_string(teamX.project.ProjectID) + "\n";
				output += "Student Team: ";
				for (int j = 0; j < 5; j++) {
					if ((studentX.name).compare(teamX.team[j].name) == 0) {
						output += replacedStudent.name + ", ";

					} else {
						output += teamX.team[j].name + ", ";

					}
				}

				output += "\n\n";
			} else if (topTeams5[i].second.project.ProjectID
					!= topTeams5[i - 1].second.project.ProjectID) {
				output += "*Project #"
						+ to_string(topTeams5[i].second.project.ProjectID)
						+ "  New TeamScore: " + to_string(topTeams5[i].first)
						+ "\n";

				for (int x = 0; x < teamsOf5.size(); x++) {

					if (topTeams5[i].second.project.ProjectID
							== teamsOf5[x].project.ProjectID) {
						for (int j = 0; j < 5; j++) {
							if ((studentX.name).compare(
									topTeams5[i].second.team[j].name) == 0) {
								replacedStudent = teamsOf5[x].team[j];
								output += "Student to be replaced -> ASUriteID:"
										+ teamsOf5[x].team[j].ASUriteID
										+ "  name: " + teamsOf5[x].team[j].name
										+ "\n";

							}
						}
					}
				}
				output += "Students: ";
				for (int j = 0; j < 5; j++) {
					output += " " + topTeams5[i].second.team[j].name + ", ";

				}
				output += "\n";

				output += "New Team for Project #"
						+ to_string(teamX.project.ProjectID) + "\n";
				output += "Student Team: ";

				for (int j = 0; j < 5; j++) {
					if ((studentX.name).compare(teamX.team[j].name) == 0) {
						output += replacedStudent.name + ", ";

					} else {
						output += teamX.team[j].name + ", ";

					}
				}
				output += "\n\n";

			}
		}

		int length = output.length();
		char output_char[length + 1];
		strcpy(output_char, output.c_str());
		buffer2->text("");
		buffer2->append(output_char);

	} else {
		buffer2->text("\nNo Student found.");
	}

}

// DESTRUCTOR
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
	delete windowRecommender;
	delete textDisplay2;
	delete buffer2;
	delete FindReplacements;
	delete inputStudent;
	delete backBox;
}
