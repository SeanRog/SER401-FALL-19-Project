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
#include <fstream>

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



//Function to convert integers into constant expressions.
constexpr int toConstInt(int constInt) {
	return constInt;
}



/* constructor, preps the results window and buffer */
ResultWindow::ResultWindow() {

	// MAIN WINDOW
	windowResult = new Fl_Window(900, 800, "Capstone Team Assignment Results");

	Fl_Box *backBox1 = new Fl_Box(0, 0, 10, 400);
	backBox1->box(FL_FLAT_BOX);
	backBox1->color(ASU_BLACK);

	Fl_Box *backBox2 = new Fl_Box(0, 0, 900, 10);
	backBox2->box(FL_FLAT_BOX);
	backBox2->color(ASU_BLACK);

	Fl_Box *backBox3 = new Fl_Box(890, 0, 10, 400);
	backBox3->box(FL_FLAT_BOX);
	backBox3->color(ASU_BLACK);

	// Buffer
	buffer = new Fl_Text_Buffer();
	borderBox = new Fl_Box(0, 400, 900, 400);
	borderBox->box(FL_FLAT_BOX);
	borderBox->color(ASU_BLACK);

	//Text Display
	textDisplay = new Fl_Text_Display(10, 410, 900 - 20, 600 - 220);
	textDisplay->buffer(buffer);
	textDisplay->textfont(FL_HELVETICA);
	textDisplay->textsize(15);
	textDisplay->selection_color(ASU_GOLD);

	//Save BUTTON
	buttonSave = new Fl_Button(50, 330, 175, 50, "Save .csv Report");
	buttonSave->color(ASU_GOLD);
	buttonSave->labelfont(FL_HELVETICA);
	buttonSave->labelcolor(ASU_BLACK);
	buttonSave->labelsize(15);
	buttonSave->selection_color(ASU_BLACK);
	buttonSave->callback(static_saveClicked, this);

	permBox = new Fl_Box(280, 330, 5, 20, "");
	permBox->box(FL_FLAT_BOX);
	permBox->color(ASU_GREY);
	permBox->align(FL_ALIGN_RIGHT);
	permBox->labelfont(FL_HELVETICA_BOLD);
	permBox->labelsize(15);
	permBox->labelcolor(ASU_WHITE);

	swapBox = new Fl_Box(280, 360, 5, 20, "");
	swapBox->box(FL_FLAT_BOX);
	swapBox->color(ASU_GREY);
	swapBox->align(FL_ALIGN_RIGHT);
	swapBox->labelfont(FL_HELVETICA_BOLD);
	swapBox->labelsize(15);
	swapBox->labelcolor(ASU_WHITE);

	teamBox = new Fl_Box(320, 270, 5, 20, "");
	teamBox->box(FL_FLAT_BOX);
	teamBox->color(ASU_GREY);
	teamBox->align(FL_ALIGN_RIGHT);
	teamBox->labelfont(FL_HELVETICA_BOLD);
	teamBox->labelsize(15);
	teamBox->labelcolor(ASU_WHITE);

	bestBox = new Fl_Box(610, 270, 5, 20, "");
	bestBox->box(FL_FLAT_BOX);
	bestBox->color(ASU_GREY);
	bestBox->align(FL_ALIGN_RIGHT);
	bestBox->labelfont(FL_HELVETICA_BOLD);
	bestBox->labelsize(15);
	bestBox->labelcolor(ASU_WHITE);

	badBox = new Fl_Box(15, 270, 5, 20, "");
	badBox->box(FL_FLAT_BOX);
	badBox->color(ASU_GREY);
	badBox->align(FL_ALIGN_RIGHT);
	badBox->labelfont(FL_HELVETICA_BOLD);
	badBox->labelsize(15);
	badBox->labelcolor(ASU_WHITE);

	spacer = new Fl_Box(20, 290, 900-40, 20, "______________________________________"
			"________________________________________________________________________");
	spacer->box(FL_FLAT_BOX);
	spacer->color(ASU_GREY);
	spacer->align(FL_ALIGN_CENTER);
	spacer->labelfont(FL_HELVETICA_BOLD);
	spacer->labelsize(15);
	spacer->labelcolor(ASU_BLACK);

	pieChart = new Fl_Chart(20, 20, 400, 230);
	pieChart->type(FL_BAR_CHART);
	pieChart->textfont(FL_HELVETICA_BOLD);
	pieChart->textcolor(ASU_BLACK);
	pieChart->textsize(12);

}



/* event handler for the save button. Saves file as .txt */
void ResultWindow::saveClicked(Fl_Widget *w) {
	buffer->savefile("results.csv", 1000000);
}



/* method to show the results window once the buffer has been filled */
void ResultWindow::addText() {

	calculateStats();

	// Fill test box labels with data results
	char permNum[50];
	int buff = sprintf(permNum, "Number of possible permutations: %d",
			permutations);
	const char *permNum1 = permNum;
	permBox->label(permNum1);

	char swapNum[50];
	buff = sprintf(swapNum, "Number of students swapped:       %d", swaps);
	const char *swapNum1 = swapNum;
	swapBox->label(swapNum1);

	char teamNum[50];
	buff = sprintf(teamNum, "Average Team Score: %d", teamScoreAvg);
	const char *teamNum1 = teamNum;
	teamBox->label(teamNum1);

	char bestNum[50];
	buff = sprintf(bestNum, "Best Team Score: %d (Team %d)", bestScore, bestTeam);
	const char *bestNum1 = bestNum;
	bestBox->label(bestNum1);

	char badNum[50];
	buff = sprintf(badNum, "Worst Team Score: %d (Team %d)", badScore, worstTeam);
	const char *badNum1 = badNum;
	badBox->label(badNum1);


	//Fills charts with data results
	char low1a[50];
	buff = sprintf(low1a, " %d-%d (%d)", badScore, badScore+percent, low1);
	const char *low1b = low1a;
	pieChart->add(low1,low1b, ASU_GOLD);

	char low2a[50];
	buff = sprintf(low2a, " %d-%d (%d)", badScore+(percent)+1, badScore+(percent*2), low2);
	const char *low2b = low2a;
	pieChart->add(low2, low2b, ASU_MAROON);

	char avg1a[50];
	buff = sprintf(avg1a, " %d-%d (%d)", badScore+(percent*2)+1, badScore+(percent*3), avg1);
	const char *avg1b = avg1a;
	pieChart->add(avg1, avg1b, ASU_GOLD);

	char avg2a[50];
	buff = sprintf(avg2a, " %d-%d (%d)", badScore+(percent*3)+1, badScore+(percent*4), avg2);
	const char *avg2b = avg2a;
	pieChart->add(avg2, avg2b, ASU_MAROON);

	char high1a[50];
	buff = sprintf(high1a, " %d-%d (%d)", badScore+(percent*4)+1, badScore+(percent*5), high1);
	const char *high1b = high1a;
	pieChart->add(high1, high1b, ASU_GOLD);

	char high2a[50];
	buff = sprintf(high2a, " %d-%d (%d)", badScore+(percent*5)+1, bestScore, high2);
	const char *high2b = high2a;
	pieChart->add(high2, high2b, ASU_MAROON);


	//Show window
	windowResult->resizable(textDisplay);
	windowResult->color(ASU_GREY);
	windowResult->show();
	windowResult->end();
	Fl::run();
}


// Calculate the stats of how well the teams were formed
void ResultWindow::calculateStats() {

	//initialize variables
	teamScoreAvg = 0, bestScore = 0, badScore = 100;
	low1 =0, low2 =0, avg1 =0, avg2 =0, high1 =0, high2 =0;
	string line;
	int next1 = 0, next2 = 0, count = 0;
	int projTeamScore [2][200];

	//open results and store into a 2D array [project#][TeamScore]
	ifstream resultFile;
	resultFile.open("./results.txt");
	if (resultFile.is_open()) {
		while (!resultFile.eof()) {

			char score[2];
			char proj[2];
			int value;
			resultFile >> line;

			if(next1 == 1) {

				score[0] = line[0];
				score[1] = line[1];
				value = atoi(score);
				projTeamScore[1][count] = value;
				next1=0;
				count++;

			} else if(next2 == 1) {

				if(line[9] == ':') {
					proj[0] = '0';
					proj[1] = line[8];
					value = atoi(proj);
					projTeamScore[0][count] = value;
				} else {
					proj[0] = line[8];
					proj[1] = line[9];
					value = atoi(proj);
					projTeamScore[0][count] = value;
				}
				next2 =0;

			} else {

				string temp1 = "Scor";
				string temp2 = line.substr(0,4);
				string temp3 = "Proj";
				if(temp1.compare(temp2) == 0) { next1 = 1;}
				else if(temp3.compare(temp2) == 0) { next2 = 1;}

			}
		}
	}


	//calculating average team score
	for(int i =  0; i < count; i ++) { teamScoreAvg += projTeamScore[1][i];	}
	teamScoreAvg = teamScoreAvg/count;

	//calculating best team score
	for(int i =  0; i < count; i ++) {
		if(projTeamScore[1][i] > bestScore) {
				bestScore = projTeamScore[1][i];
				bestTeam = projTeamScore[0][i];
		}
	}


	//calculating worst team score
	for(int i =  0; i < count; i ++) {
		if(projTeamScore[1][i] < badScore) {
				badScore = projTeamScore[1][i];
				worstTeam = projTeamScore[0][i];
		}
	}

	percent = (bestScore-badScore)/6;

	//Teams within 6 data groups
	for(int i =  0; i < count; i ++) {
		if(projTeamScore[1][i] <= (badScore+percent)) { low1++;	}
		if((projTeamScore[1][i] <= badScore+(percent*2)) &&
				(projTeamScore[1][i]) > (badScore+percent)) { low2++;	}
		if((projTeamScore[1][i] <= badScore+(percent*3)) &&
				(projTeamScore[1][i]) > (badScore+percent*2)) { avg1++;	}
		if((projTeamScore[1][i] <= badScore+(percent*4)) &&
				(projTeamScore[1][i]) > (badScore+percent*3)) { avg2++;	}
		if((projTeamScore[1][i] <= badScore+(percent*5)) &&
				(projTeamScore[1][i]) > (badScore+percent*4)) { high1++;}
		if((projTeamScore[1][i] <= bestScore) &&
				(projTeamScore[1][i]) > (badScore+percent*5)) { high2++;}
	}

}


// DESTRUCTOR
ResultWindow::~ResultWindow() {
	// TODO
}
