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
#include "Project.h"
#include "CookieManager.h"
#include "StudentsToProjects.h"
#include "Utility.h"

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
	windowResult = new Fl_Window(1500, 800, "Capstone Team Assignment Results");

	Fl_Box *backBox1 = new Fl_Box(0, 0, 10, 800);
	backBox1->box(FL_FLAT_BOX);
	backBox1->color(ASU_BLACK);

	Fl_Box *backBox2 = new Fl_Box(0, 0, 1500, 10);
	backBox2->box(FL_FLAT_BOX);
	backBox2->color(ASU_BLACK);

	Fl_Box *backBox3 = new Fl_Box(0, 790, 1000, 10);
	backBox3->box(FL_FLAT_BOX);
	backBox3->color(ASU_BLACK);

	// Buffer
	buffer = new Fl_Text_Buffer();
	borderBox = new Fl_Box(840, 0, 660, 800);
	borderBox->box(FL_FLAT_BOX);
	borderBox->color(ASU_BLACK);

	borderBox2 = new Fl_Box(850, 10, 640, 130);
	borderBox2->box(FL_FLAT_BOX);
	borderBox2->color(ASU_GREY);

	//Text Display
	textDisplay = new Fl_Text_Display(850, 140, 640, 650);
	textDisplay->buffer(buffer);
	textDisplay->textfont(FL_HELVETICA);
	textDisplay->textsize(15);
	textDisplay->selection_color(ASU_GOLD);

	//Post Teams BUTTON
	buttonPostGroups = new Fl_Button(875, 20, 175, 50, "Post Groups");
	buttonPostGroups->color(ASU_GOLD);
	buttonPostGroups->labelfont(FL_HELVETICA);
	buttonPostGroups->labelcolor(ASU_BLACK);
	buttonPostGroups->labelsize(15);
	buttonPostGroups->selection_color(ASU_BLACK);

	//uncomment this to activate the post teams button.
	//buttonPostGroups->callback(static_postGroups, this);
	buttonPostGroups->callback(static_recommenderWindow, this);

	//Save BUTTON
	buttonSave = new Fl_Button(1075, 20, 175, 50, "Save .csv Report");
	buttonSave->color(ASU_GOLD);
	buttonSave->labelfont(FL_HELVETICA);
	buttonSave->labelcolor(ASU_BLACK);
	buttonSave->labelsize(15);
	buttonSave->selection_color(ASU_BLACK);
	buttonSave->callback(static_saveClicked, this);

	//Exit BUTTON
	buttonExit = new Fl_Button(1275, 20, 175, 50, "Exit");
	buttonExit->color(ASU_GOLD);
	buttonExit->labelfont(FL_HELVETICA);
	buttonExit->labelcolor(ASU_BLACK);
	buttonExit->labelsize(15);
	buttonExit->selection_color(ASU_BLACK);
	buttonExit->callback(static_exitClicked, this);


	//Recommender System BUTTON
	buttonRecommender = new Fl_Button(875, 80, 300, 50, "Replacement Team Recommender");
	buttonRecommender->color(ASU_GOLD);
	buttonRecommender->labelfont(FL_HELVETICA);
	buttonRecommender->labelcolor(ASU_BLACK);
	buttonRecommender->labelsize(15);
	buttonRecommender->selection_color(ASU_BLACK);
	buttonRecommender->callback(static_recommenderWindow, this);

	permBox = new Fl_Box(410, 90, 5, 20, "");
	permBox->box(FL_FLAT_BOX);
	permBox->color(ASU_GREY);
	permBox->align(FL_ALIGN_RIGHT);
	permBox->labelfont(FL_HELVETICA_BOLD);
	permBox->labelsize(15);
	permBox->labelcolor(ASU_WHITE);

	swapBox = new Fl_Box(410, 120, 5, 20, "");
	swapBox->box(FL_FLAT_BOX);
	swapBox->color(ASU_GREY);
	swapBox->align(FL_ALIGN_RIGHT);
	swapBox->labelfont(FL_HELVETICA_BOLD);
	swapBox->labelsize(15);
	swapBox->labelcolor(ASU_WHITE);

	teamBox = new Fl_Box(410, 150, 5, 20, "");
	teamBox->box(FL_FLAT_BOX);
	teamBox->color(ASU_GREY);
	teamBox->align(FL_ALIGN_RIGHT);
	teamBox->labelfont(FL_HELVETICA_BOLD);
	teamBox->labelsize(15);
	teamBox->labelcolor(ASU_WHITE);

	bestBox = new Fl_Box(410, 210, 5, 20, "");
	bestBox->box(FL_FLAT_BOX);
	bestBox->color(ASU_GREY);
	bestBox->align(FL_ALIGN_RIGHT);
	bestBox->labelfont(FL_HELVETICA_BOLD);
	bestBox->labelsize(15);
	bestBox->labelcolor(ASU_WHITE);

	badBox = new Fl_Box(410, 180, 5, 20, "");
	badBox->box(FL_FLAT_BOX);
	badBox->color(ASU_GREY);
	badBox->align(FL_ALIGN_RIGHT);
	badBox->labelfont(FL_HELVETICA_BOLD);
	badBox->labelsize(15);
	badBox->labelcolor(ASU_WHITE);

	labelBox3 = new Fl_Box(170, 280, 5, 15, "Low");
	labelBox3->box(FL_FLAT_BOX);
	labelBox3->color(ASU_GREY);
	labelBox3->align(FL_ALIGN_RIGHT);
	labelBox3->labelfont(FL_HELVETICA_BOLD);
	labelBox3->labelsize(12);
	labelBox3->labelcolor(ASU_BLUE);

	labelBox4 = new Fl_Box(395, 280, 5, 15, "Medium");
	labelBox4->box(FL_FLAT_BOX);
	labelBox4->color(ASU_GREY);
	labelBox4->align(FL_ALIGN_RIGHT);
	labelBox4->labelfont(FL_HELVETICA_BOLD);
	labelBox4->labelsize(12);
	labelBox4->labelcolor(ASU_ORANGE);

	labelBox5 = new Fl_Box(620, 280, 5, 15, "High");
	labelBox5->box(FL_FLAT_BOX);
	labelBox5->color(ASU_GREY);
	labelBox5->align(FL_ALIGN_RIGHT);
	labelBox5->labelfont(FL_HELVETICA_BOLD);
	labelBox5->labelsize(12);
	labelBox5->labelcolor(ASU_GOLD);

	pieChart = new Fl_Chart(20, 20, 380, 220,
			"Number of Teams within Score Range");
	pieChart->type(FL_PIE_CHART);
	pieChart->textfont(FL_HELVETICA);
	pieChart->textcolor(ASU_BLACK);
	pieChart->textsize(14);
	pieChart->labelfont(FL_HELVETICA_BOLD);
	pieChart->labelsize(16);
	pieChart->labelcolor(ASU_WHITE);

	barChart = new Fl_Chart(20, 300, 810, 210,
			"Team Scores by Project Priority");
	barChart->type(FL_SPIKE_CHART);
	barChart->textfont(FL_HELVETICA);
	barChart->textcolor(ASU_BLACK);
	barChart->textsize(12);
	barChart->labelfont(FL_HELVETICA_BOLD);
	barChart->labelsize(16);
	barChart->labelcolor(ASU_WHITE);

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

/* event handler for the save button. Saves file as .txt */
void ResultWindow::saveClicked(Fl_Widget *w) {
	buffer->savefile("results.csv", 1000000);
}

/* event handler for the save button. Saves file as .txt */
void ResultWindow::exitClicked(Fl_Widget *w) {
	exit(0);
}

/* method to show the results window once the buffer has been filled */
void ResultWindow::addText() {

	calculateStats();

	// Fill test box labels with data results
	char permNum[70];
	int buff = sprintf(permNum, "Number of possible permutations: %d",
			permutations);
	const char *permNum1 = permNum;
	permBox->label(permNum1);

	char swapNum[70];
	buff = sprintf(swapNum, "Number of students swapped:        %d", swaps);
	const char *swapNum1 = swapNum;
	swapBox->label(swapNum1);

	char teamNum[70];
	buff = sprintf(teamNum, "Average Team Score:  %d", teamScoreAvg);
	const char *teamNum1 = teamNum;
	teamBox->label(teamNum1);

	char bestNum[70];
	buff = sprintf(bestNum, "Best Team Score:         %d (Team %d)", bestScore,
			bestTeam);
	const char *bestNum1 = bestNum;
	bestBox->label(bestNum1);

	char badNum[70];
	buff = sprintf(badNum, "Worst Team Score:      %d (Team %d)", badScore,
			worstTeam);
	const char *badNum1 = badNum;
	badBox->label(badNum1);

	//Fills pie charts with data results
	char low1a[50];
	buff = sprintf(low1a, " %d-%d (%d)", badScore, badScore + percent, low1);
	const char *low1b = low1a;
	pieChart->add(low1, low1b, ASU_GREEN);

	char low2a[50];
	buff = sprintf(low2a, " %d-%d (%d)", badScore + (percent) + 1,
			badScore + (percent * 2) + 1, low2);
	const char *low2b = low2a;
	pieChart->add(low2, low2b, ASU_BLUE);

	char avg1a[50];
	buff = sprintf(avg1a, " %d-%d (%d)", badScore + (percent * 2) + 2,
			badScore + (percent * 3) + 1, avg1);
	const char *avg1b = avg1a;
	pieChart->add(avg1, avg1b, ASU_WHITE);

	char avg2a[50];
	buff = sprintf(avg2a, " %d-%d (%d)", badScore + (percent * 3) + 2,
			badScore + (percent * 4) + 1, avg2);
	const char *avg2b = avg2a;
	pieChart->add(avg2, avg2b, ASU_ORANGE);

	char high1a[50];
	buff = sprintf(high1a, " %d-%d (%d)", badScore + (percent * 4) + 2,
			badScore + (percent * 5) + 1, high1);
	const char *high1b = high1a;
	pieChart->add(high1, high1b, ASU_GOLD);

	char high2a[50];
	buff = sprintf(high2a, " %d-%d (%d)", badScore + (percent * 5) + 2,
			bestScore, high2);
	const char *high2b = high2a;
	pieChart->add(high2, high2b, ASU_MAROON);

	// Filling in project priority chart
	for (int i = 0; i < count; i++) {
		if (project_pool[1][i] == 0 && project_pool[2][i] != 0) {
			char priob[2];
			buff = sprintf(priob, "%d", project_pool[2][i]);
			const char *prioa = priob;
			barChart->add(project_pool[2][i], prioa, ASU_BLUE);
		}
	}

	for (int i = 0; i < count; i++) {
		if (project_pool[1][i] == 1 && project_pool[2][i] != 0) {
			char priob[2];
			buff = sprintf(priob, "%d", project_pool[2][i]);
			const char *prioa = priob;
			barChart->add(project_pool[2][i], prioa, ASU_ORANGE);
		}
	}

	for (int i = 0; i < count; i++) {
		if (project_pool[1][i] == 2 && project_pool[2][i] != 0) {
			char priob[2];
			buff = sprintf(priob, "%d", project_pool[2][i]);
			const char *prioa = priob;
			barChart->add(project_pool[2][i], prioa, ASU_GOLD);
		}
	}

	// Filling in class section chart
	int count1 = 0, sections[10], changed = 0;

	for (int j = 0; j < count; j++) {
		for (int i = 0; i < count; i++) {
			if (project_pool[3][i] == project_pool[3][j]
					&& project_pool[4][i] != 1) {

				if (project_pool[3][i] != sections[count1 - 1]) {
					sections[count1] = project_pool[3][i];
					count1++;
					changed = 1;
				}

				project_pool[4][i] = 1;
				char priob[10];

				if (changed == 1) {
					classChart->add(0, "", ASU_MAROON);
					classChart->add(0, "", ASU_MAROON);

					buff = sprintf(priob, "S#%d-  %d", project_pool[3][i],
							project_pool[2][i]);
					changed = 0;
				} else {
					buff = sprintf(priob, "%d", project_pool[2][i]);
				}
				const char *prioa = priob;

				if (j % 2 == 0) {
					classChart->add(project_pool[2][i], prioa, ASU_GOLD);
				} else {
					classChart->add(project_pool[2][i], prioa, ASU_MAROON);
				}
			}
		}
	}

	classChart->add(0, "", ASU_MAROON);
	classChart->add(0, "", ASU_MAROON);

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

/* event handler for the Post groups button. */
void ResultWindow::postGroups(Fl_Widget *w) {

	cout << "Post Groups clicked" << endl;
	CookieManager canvas;

	//test data using the dev course id, and the test student id.
	/*vector <ClassSection> test_courses;
	 vector <Team> test_team;
	 ClassSection course;
	 Student test_student;

	 Team emptyteam;
	 test_team.push_back(emptyteam);
	 course.OfficialClassID = 47570;
	 test_student.StudentID = 461471;

	 test_team[0].OfficialClassID = 47570;
	 test_team[0].team[0] = test_student;

	 test_courses.push_back(course);

	 courses = test_courses;
	 studentTeams = test_team;*/

	//vector pair to store the courseID and the Group_CategoryID.
	vector<pair<int, int>> course_group;

	for (int i = 0; i < courses.size(); i++) {

		cout << "Here 1 " << endl;
		int groupCategory_ID = canvas.postGroupCategories(cookies, courses[i]);

		cout << groupCategory_ID << endl;

		course_group.push_back(
				make_pair(courses[i].OfficialClassID, groupCategory_ID));

	}

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


void ResultWindow::recommenderSystemWindow(Fl_Widget *w)  {

	// MAIN WINDOW
	windowRecommender = new Fl_Window(840, 640, "Student Team Replacement Recommendation System");

	Fl_Box *titleBox = new Fl_Box(140, 10, 690, 30, "REPLACEMENT TEAM RECOMMENDER");
	titleBox->box(FL_NO_BOX);
	titleBox->labelcolor(ASU_GOLD);
	titleBox->labelfont(FL_HELVETICA_BOLD);
	titleBox->labelsize(25);
	//titleBox->color(ASU_BLACK);

	Fl_Box *backBox1 = new Fl_Box(140, 40, 690, 30, "Finds the best replacement project and team for a certain student.");
	backBox1->box(FL_NO_BOX);
	backBox1->labelcolor(ASU_WHITE);
	backBox1->labelfont(FL_HELVETICA);
	backBox1->labelsize(15);
	backBox1->color(ASU_BLACK);

	Fl_Box *backBox2 = new Fl_Box(140, 70, 690, 30, "Gives the top choices for (teams of 4) and top choices for (teams of 5).");
	backBox2->box(FL_NO_BOX);
	backBox2->labelcolor(ASU_WHITE);
	backBox2->labelfont(FL_HELVETICA);
	backBox2->labelsize(15);
	backBox2->color(ASU_BLACK);

	Fl_Box *backBox3 = new Fl_Box(140, 100, 690, 30, "For teams of 5, the system recommends which student would be best to swap out.");
	backBox3->box(FL_NO_BOX);
	backBox3->labelcolor(ASU_WHITE);
	backBox3->labelfont(FL_HELVETICA);
	backBox3->labelsize(15);
	backBox3->color(ASU_BLACK);


	Fl_PNG_Image logo("./Images/CapstoneTeams120by120.png");
	Fl_Box *imageBox = new Fl_Box(20, 10, 120, 120);
	imageBox->box(FL_NO_BOX);
	imageBox->image(logo);
	//imageBox->color(ASU_WHITE);


	/*Fl_Box *backBox2 = new Fl_Box(0, 0, 1500, 10);
	backBox2->box(FL_FLAT_BOX);
	backBox2->color(ASU_BLACK);

	Fl_Box *backBox3 = new Fl_Box(0, 790, 1000, 10);
	backBox3->box(FL_FLAT_BOX);
	backBox3->color(ASU_BLACK);*/

	//text input
	inputStudent = new Fl_Input(300, 160, 150, 50, "Enter the student's asuriteID  ");
	inputStudent->labelfont(FL_HELVETICA_BOLD);
	inputStudent->labelcolor(ASU_WHITE);
	inputStudent->textfont(FL_HELVETICA);
	inputStudent->labelsize(15);

	// Buffer
	buffer2 = new Fl_Text_Buffer();
	/*borderBox = new Fl_Box(840, 0, 660, 800);
	borderBox->box(FL_FLAT_BOX);
	borderBox->color(ASU_BLACK);

	borderBox2 = new Fl_Box(850, 10, 640, 70);
	borderBox2->box(FL_FLAT_BOX);
	borderBox2->color(ASU_GREY);*/

	//Text Display
	textDisplay2 = new Fl_Text_Display(20, 220, 800, 400);
	textDisplay2->buffer(buffer2);
	textDisplay2->textfont(FL_HELVETICA);
	textDisplay2->textsize(15);
	textDisplay2->selection_color(ASU_GOLD);

	//Post Teams BUTTON
	FindReplacements = new Fl_Button(560, 160, 250, 50, "Find Replacement Teams");
	FindReplacements->color(ASU_GOLD);
	FindReplacements->labelfont(FL_HELVETICA);
	FindReplacements->labelcolor(ASU_BLACK);
	FindReplacements->labelsize(15);
	FindReplacements->selection_color(ASU_BLACK);


	FindReplacements->callback(static_recommender, this);

	windowRecommender->color(ASU_GREY);
	windowRecommender->show();
	windowRecommender->end();
	Fl::run();

}

bool sortinrev(const pair<int,Team> &a,
               const pair<int,Team> &b)
{
       return (a.first > b.first);
}



void ResultWindow::recommenderSystem(Fl_Widget *w)  {


	string asuriteIDX = inputStudent->value();
	Student studentX;
	Team teamX;
	int classIDX;
	int placeIDX;
	int numSkills = 14;
	int bestTeamScore = 0;

	vector <Team> teamsOf4;
	vector <Team> teamsOf5;
	Team BestTeamOf5, BestTeamOf4;
	vector<pair<int, Team>> topTeams5, topTeams4;
	bool isTeam4;
	bool teamXis4 = false;
	studentX.name = "null";

	BestTeamOf4.projectID = 99999;
	BestTeamOf5.projectID = 99999;

	//find the team, and class section the student belongs to.
	for(int i = 0; i <studentTeams.size(); i++){
		for(int j = 0; j < 5; j++){
			if(studentTeams[i].team[j].ASUriteID.compare(asuriteIDX) == 0){

				studentX = studentTeams[i].team[j];
				teamX = studentTeams[i];
				classIDX = studentTeams[i].ClassID;
				placeIDX = j;
				break;
			}
		}
	}

	//find all the teams of 4 and 5 that are in the same class section
	for(int i = 0; i <studentTeams.size(); i++){

			if(studentTeams[i].ClassID == classIDX){
				isTeam4 = false;
				for(int j = 0; j < 5; j++){

					if(studentTeams[i].team[j].StudentID == 99999){

						isTeam4 = true;
					}
				}
				if(isTeam4 == true){
					teamsOf4.push_back(studentTeams[i]);
				}else{
					teamsOf5.push_back(studentTeams[i]);
				}

			}
	}

	//find out if the student's team is a team of 4 or not.
	for(int i = 0; i < 5 ; i++){
		if(teamX.team[i].StudentID == 99999){
			teamXis4 = true;
		}
	}

	StudentsToProjects stp;
	cout<<"TEAMS OF 4"<<endl;
	//find the best team of 4 that the student can be placed in
	for(int i = 0; i <teamsOf4.size(); i++){

		for(int j = 0; j < 5; j++){
				if(teamsOf4[i].team[j].StudentID == 99999){

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
							studentProjectSkills[x] += currentTeam.team[x].Skills[y] * currentTeam.project.Skills[y];
						}

						skillSum += studentSkillSums[x];
					}

					//Calculate max skill score for the current project.
					int maxProjectScore = 0;
						for (int y = 0; y < numSkills; y++) {
							maxProjectScore += currentTeam.project.Skills[y] * 4;
						}
						maxProjectScore = maxProjectScore * 5;

						currentTeam.TeamScore = stp.ProjectCompareTeamScore(studentProjectSkills,
							maxProjectScore)
							+ stp.SkillCompareTeamScore(studentSkillSums)
							+ stp.AvailabilityTeamScore(currentTeam.team);

					if ((stp.NegativeAffinityCheck(currentTeam.team) == false)
								&& (stp.NDA_IPRCheck(currentTeam.team, currentTeam.project) == true)) {


							if(currentTeam.TeamScore >= OldTeamScore || bestTeamScore < (OldTeamScore - currentTeam.TeamScore) ){

							bestTeamScore = OldTeamScore - currentTeam.TeamScore;
							BestTeamOf4 = currentTeam;


						}
						cout<<"Old Team Score: "<<OldTeamScore<< "NewTeamScore: "<<currentTeam.TeamScore
														<<endl;
						if(OldTeamScore <= currentTeam.TeamScore && currentTeam.project.ProjectID != teamX.project.ProjectID){
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

	cout<<"TEAMS OF 5"<<endl;

	//find the best team of 5 that the student can be placed in,
	//and the student to be swapped.
	for(int i = 0; i <teamsOf5.size(); i++){

		for(int k = 0; k <5; k++){
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
							studentProjectSkills[x] += currentTeam.team[x].Skills[y] * currentTeam.project.Skills[y];
						}

						skillSum += studentSkillSums[x];
					}

					//Calculate max skill score for the current project.
					int maxProjectScore = 0;
						for (int y = 0; y < numSkills; y++) {
							maxProjectScore += currentTeam.project.Skills[y] * 4;
						}
						maxProjectScore = maxProjectScore * 5;

						currentTeam.TeamScore = stp.ProjectCompareTeamScore(studentProjectSkills,
							maxProjectScore)
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
								studentProjectSkills2[x] += replacedTeam.team[x].Skills[y] * replacedTeam.project.Skills[y];
							}

							skillSum2 += studentSkillSums2[x];
						}

						//Calculate max skill score for the current project.
						int maxProjectScore2 = 0;
							for (int y = 0; y < numSkills; y++) {
								maxProjectScore2 += replacedTeam.project.Skills[y] * 4;
							}
							maxProjectScore2 = maxProjectScore * 5;

							replacedTeam.TeamScore = stp.ProjectCompareTeamScore(studentProjectSkills2,
								maxProjectScore2)
								+ stp.SkillCompareTeamScore(studentSkillSums2)
								+ stp.AvailabilityTeamScore(replacedTeam.team);




					if ((stp.NegativeAffinityCheck(currentTeam.team) == false)
								&& (stp.NDA_IPRCheck(currentTeam.team, currentTeam.project) == true)) {

						if ((stp.NegativeAffinityCheck(replacedTeam.team) == false)
									&& (stp.NDA_IPRCheck(replacedTeam.team, replacedTeam.project) == true)) {

							cout<<"Old Team Score: "<<oldTeamScore<< " NewTeamScore: "<<currentTeam.TeamScore<<" oldTeamX: "<<teamXScore<<" ReplacedTeamScore: "<<replacedTeam.TeamScore<<endl;

						if(currentTeam.TeamScore >= bestTeamScore && currentTeam.project.ProjectID != teamX.project.ProjectID){
							bestTeamScore = currentTeam.TeamScore;
							BestTeamOf5 = currentTeam;
						}



						//cout<<"Old Team Score: "<<oldTeamScore<< "NewTeamScore: "<<currentTeam.TeamScore
						//		<<"oldTeamX: "<<teamXScore<<" ReplacedTeamScore: "<<replacedTeam.TeamScore<<endl;
						if(oldTeamScore <= currentTeam.TeamScore
								&& currentTeam.project.ProjectID != teamX.project.ProjectID){
						pair<int, Team> temp;
						temp.first = currentTeam.TeamScore;
						temp.second = currentTeam;
							topTeams5.push_back(temp);}
						//}
						}

					}
				}



			}

if(studentX.name.compare("null") != 0){
	//now sort through the list of teams to get the top 5.
	sort(topTeams4.begin(), topTeams4.end(), sortinrev);

	sort(topTeams5.begin(), topTeams5.end(), sortinrev);

	//Print out to the display all the following information
	string output = "";
		output += "STUDENT:   "+studentX.name + "\n";
		output += "ASUriteID:  "+studentX.ASUriteID +"\n";
		output += "CLASS ID:   "+to_string(studentX.ClassID) +"\n";
		output += "CURRENT PROJECT: #"+to_string(studentX.ProjectID)+"\n";
		if(teamXis4 == false ){
			output += "CURRENT TEAM SIZE: 5\n";
		}else{
			output += "CURRENT TEAM SIZE: 4\n";

		}

		if(teamXis4 == false || topTeams5.size() == 0 ){

		output += "\n     Recommended replacement teams of 4 \n";
		output += "======================================================\n";
		cout<<"Recommended replacement teams of 4 for student: "<<studentX.name<<"  ASUriteID:"<<studentX.ASUriteID<<endl;
		cout<<endl;

		if(BestTeamOf4.projectID != 99999 || topTeams5.size() == 0 ){
		output += "Best replacement Team of 4: ";
		output += "Project #" + to_string(BestTeamOf4.project.ProjectID) + "  New TeamScore: " + to_string(BestTeamOf4.TeamScore) + "\n";
		output += "Students: ";
		for(int j = 0; j < 5; j++){
			output += " " + BestTeamOf4.team[j].name + ", ";

		}
		output += "\n\n";

		cout<<"Best replacement Team of 4: ";
		cout<<"Project #"<<BestTeamOf4.project.ProjectID<<"  New TeamScore: "<<BestTeamOf4.TeamScore<<endl;
		cout<<"Students: ";
		for(int j = 0; j < 5; j++){
			cout<<" "<<BestTeamOf4.team[j].name<<", ";

		}
		cout<<"\n"<<endl;
		}
		cout<<"Full list in order (possible teams of 4)"<<endl;



	for(int i = 0; i <topTeams4.size(); i++){

		output += "*Project #" + to_string(topTeams4[i].second.project.ProjectID) + "  New TeamScore: " + to_string(topTeams4[i].first) + "\n";
		output += "Students: ";
		for(int j = 0; j < 5; j++){
			output +=" " + topTeams4[i].second.team[j].name + ", ";

		}
		output += "\n\n";

		cout<<"Project #"<<topTeams4[i].second.project.ProjectID<<"  New TeamScore: "<<topTeams4[i].first<<endl;

		cout<<"Students: ";
		for(int j = 0; j < 5; j++){
			cout<<" "<<topTeams4[i].second.team[j].name<<", ";

		}
		cout<<"\n"<<endl;
	}}

	output +="\n     Recommended replacement teams of 5 \n";
	output += "======================================================\n";
	output += "\n";
	cout<<"Recommended replacement teams of 5 for student: "<<studentX.name<<"  ASUriteID:"<<studentX.ASUriteID<<endl;
	cout<<endl;

	if(BestTeamOf5.projectID != 99999 && topTeams5.size() == 0){
		Student replacedStudent;
		output +="Best replacement Team of 5: ";
		output+="Project #" + to_string(BestTeamOf5.project.ProjectID) + "  New TeamScore: " + to_string(BestTeamOf5.TeamScore) + "\n";

	cout<<"Best replacement Team of 5: ";
	cout<<"*Project #"<<BestTeamOf5.project.ProjectID<<"  New TeamScore: "<<BestTeamOf5.TeamScore<<endl;

	for(int i = 0; i <teamsOf5.size(); i++){
	if( BestTeamOf5.project.ProjectID== teamsOf5[i].project.ProjectID){
		for(int j = 0; j< 5; j++){
		if((studentX.name).compare(BestTeamOf5.team[j].name)==0){
			replacedStudent = teamsOf5[i].team[j];
			output += "Student to be replaced -> ASUriteID:" + teamsOf5[i].team[j].ASUriteID + "  name: " + teamsOf5[i].team[j].name+ "\n";
			cout<<"Student to be replaced -> ASUriteID:"<<teamsOf5[i].team[j].ASUriteID<<"  name: "<<teamsOf5[i].team[j].name<<endl;
		}}
	}}
	cout<<"Students: ";
	for(int j = 0; j < 5; j++){
		output += " " + BestTeamOf5.team[j].name + ", ";
		cout<<" "<<BestTeamOf5.team[j].name<<", ";

	}
	output+= "\n";
	cout<<endl;

	output += "New Team for Project #" + to_string(teamX.project.ProjectID)+"\n";
	output += "Student Team: ";
	cout<<"New Team for Project #"<<teamX.project.ProjectID<<endl;
	cout<<"Student Team: ";
	for(int j = 0; j< 5; j++){
	if((studentX.name).compare(teamX.team[j].name)==0){
		output += replacedStudent.name + ", ";
		cout<<replacedStudent.name<<", ";
	}else{
		output += teamX.team[j].name + ", ";
		cout<<teamX.team[j].name<<", ";

	}
	}
	output += "\n";
	cout<<endl;

	}

	cout<<"Full list in order of possible project teams of 5 to switch."<<endl;
for(int i = 0; i <topTeams5.size(); i++){

	Student replacedStudent;
	if(i == 0){
		output += "*Project #" + to_string(topTeams5[i].second.project.ProjectID) + "  New TeamScore: " + to_string(topTeams5[i].first) + "\n";
		cout<<"Project #"<<topTeams5[i].second.project.ProjectID<<"  New TeamScore: "<<topTeams5[i].first<<endl;

		//cout<<"Student to be replaced -> ASUriteID:"<<topTeams5[i].second.team[4].ASUriteID<<"  name: "<<topTeams5[i].second.team[4].name<<endl;
		for(int x = 0; x <teamsOf5.size(); x++){

				if( topTeams5[i].second.project.ProjectID== teamsOf5[x].project.ProjectID){
					for(int j = 0; j< 5; j++){
					if((studentX.name).compare(topTeams5[i].second.team[j].name)==0){
						replacedStudent = teamsOf5[x].team[j];
						output += "Student to be replaced -> ASUriteID:" + teamsOf5[x].team[j].ASUriteID +"  name: " + teamsOf5[x].team[j].name+"\n";
						cout<<"Student to be replaced -> ASUriteID:"<<teamsOf5[x].team[j].ASUriteID<<"  name: "<<teamsOf5[x].team[j].name<<endl;
					}}
				}
			}
		output += "Students: ";
		cout<<"Students: ";
		for(int j = 0; j < 5; j++){
			output += " " + topTeams5[i].second.team[j].name + ", ";
			cout<<" "<<topTeams5[i].second.team[j].name<<", ";
		}
		output += "\n";
		cout<<endl;

		output += "New Team for Project #" + to_string(teamX.project.ProjectID) + "\n";
		output += "Student Team: ";
		cout<<"New Team for Project #"<<teamX.project.ProjectID<<endl;
		cout<<"Student Team: ";
		for(int j = 0; j< 5; j++){
		if((studentX.name).compare(teamX.team[j].name)==0){
			output += replacedStudent.name+", ";
			cout<<replacedStudent.name<<", ";
		}else{
			output+= teamX.team[j].name + ", ";
			cout<<teamX.team[j].name<<", ";

		}
		}


		output += "\n\n";
		cout<<"\n"<<endl;
	}
	else if(topTeams5[i].second.project.ProjectID != topTeams5[i-1].second.project.ProjectID){
		output += "*Project #" + to_string(topTeams5[i].second.project.ProjectID) + "  New TeamScore: " + to_string(topTeams5[i].first) + "\n";
		cout<<"Project #"<<topTeams5[i].second.project.ProjectID<<"  New TeamScore: "<<topTeams5[i].first<<endl;

		//cout<<"Student to be replaced -> ASUriteID:"<<topTeams5[i].second.team[4].ASUriteID<<"  name: "<<topTeams5[i].second.team[4].name<<endl;
		for(int x = 0; x <teamsOf5.size(); x++){

				if( topTeams5[i].second.project.ProjectID== teamsOf5[x].project.ProjectID){
					for(int j = 0; j< 5; j++){
					if((studentX.name).compare(topTeams5[i].second.team[j].name)==0){
						replacedStudent = teamsOf5[x].team[j];
						output += "Student to be replaced -> ASUriteID:" + teamsOf5[x].team[j].ASUriteID +"  name: " + teamsOf5[x].team[j].name+"\n";
						cout<<"Student to be replaced -> ASUriteID:"<<teamsOf5[x].team[j].ASUriteID<<"  name: "<<teamsOf5[x].team[j].name<<endl;
					}}
				}
			}
		output += "Students: ";
		cout<<"Students: ";
		for(int j = 0; j < 5; j++){
			output += " " + topTeams5[i].second.team[j].name + ", ";
			cout<<" "<<topTeams5[i].second.team[j].name<<", ";
		}
		output += "\n";
		cout<<endl;

		output += "New Team for Project #" + to_string(teamX.project.ProjectID) + "\n";
		output += "Student Team: ";
		cout<<"New Team for Project #"<<teamX.project.ProjectID<<endl;
		cout<<"Student Team: ";
		for(int j = 0; j< 5; j++){
		if((studentX.name).compare(teamX.team[j].name)==0){
			output += replacedStudent.name+", ";
			cout<<replacedStudent.name<<", ";
		}else{
			output+= teamX.team[j].name + ", ";
			cout<<teamX.team[j].name<<", ";

		}
		}


		output += "\n\n";
		cout<<"\n"<<endl;
}}



int length = output.length();
char output_char[length + 1];
strcpy(output_char, output.c_str());
//terminal->append(output_char);
//char* text = buffer2->text();
buffer2->text("");
buffer2->append(output_char);
//buffer->append(text);
}
else{
	buffer2->text("\n\tNo Student found.");
}


}


// DESTRUCTOR
ResultWindow::~ResultWindow() {
	delete windowResult;
	delete textDisplay;
	delete buffer;
	delete buttonSave;
	delete buttonExit;
	delete permBox;
	delete swapBox;
	delete borderBox;

}
