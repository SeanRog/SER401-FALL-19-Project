/*
 * StudentsToProjects.cpp
 *
 *  Created on: Oct 30, 2019
 *  Created on: Oct 30, 2019
 *      Created by: Sean, Myles, Cristi, Matthew
 *
 *
 * Description:
 *		This class is for the assignment of students to projects. It contains various scoring, helper and check
 *		functions to assist the main function StudentsToProjectsAssignment(). The main function finds all the possible
 *		team combinations for each project, stores a certain number of top teams, finds the horizontal mapping of those
 *		teams to projects with the least amount of duplicates, and then swaps the duplicates with the best replacement student.
 *
 *
 * List of Functions:
 *
 *		StudentsToProjects() - constructor
 *
 *		~StudentsToProjects() - destructor
 *
 *		void StudentsToProjectsAssignment(Student studentPool[],
 *				Project projectPool[],const int numStudents,const int numProjects, const int numSkills,
 *				const int teamSize,const int numTopTeams)  -  a function to assign the students to projects.
 *
 *		void updateProgressBar(int value, Fl_Progress* pW); - a function to update the progress bar.
 *
 *		bool NegativeAffinityCheck(Student team[5]) - a function to check a student team to see if their is any negative affinity.
 *
 *		int getDuplicatesOfStudents(Team currentSet[], int size) - a function to find the number of duplicate students in a set of teams.
 *
 *		int AvailabilityTeamScore(Student team[5]) - a function to compare the availability of students on a team, returns a score 0-20.
 *
 *		int SkillCompareTeamScore(int studentSkills[5]) - a function to compare the skills of students on a team, returns a score 0-40.
 *
 *	    int ProjectCompareTeamScore( int studentSkills[5], int maxProjectScore)- a function to compare the student's skills to the project,
 *	    																		returns a score 0-40.
 *
 *		int StudentToStudentSkill( int skillsum1, int skillsum2)  - a helper function for SkillCompareTeamScore.
 *
 *		int StudentToStudentAvailibility(Student s1, Student s2)  - a helper function for AvailabilityTeamScore.
 *
 *		int parseLine(char* line) - a function to monitor system memory usage
 *
 *		int getValuePhy() - a function to monitor system memory usage
 *
 *		int getValueVirt() - a function to monitor system memory usage
 *
 *		constexpr int toConstInt(int constInt) - a function to convert an int to a constant
 *
 */

#include "StudentsToProjects.h"
#include "Project.h"
#include "Student.h"
#include "Team.h"
#include "ClassSection.h"
#include "json/json.h"
#include "Utility.h"

#include <FL/Fl.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <string>

#include <bits/stdc++.h>
#include "sys/types.h"
#include "sys/sysinfo.h"

using namespace std;
using namespace std::chrono;
//Constructor
StudentsToProjects::StudentsToProjects() {
}
//Destructor
StudentsToProjects::~StudentsToProjects() {
}

//Function to convert integers into constant expressions.
constexpr int StudentsToProjects::toConstInt(int constInt) {
	return constInt;
}

/*********************************************************
 * parseLine
 *
 * Author: Sean Rogers
 *
 * Description:
 *
 *Arguments:
 *	char* line
 *Returns:
 *  integer value.
 */
int StudentsToProjects::parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

/*********************************************************
 * getValuePhy
 *
 * Author: Sean Rogers
 *
 * Description:
 *    Gets the physical memory usage of the program
 *
 *Arguments:
 *	nothing
 *Returns:
 *  integer value.
 */
int StudentsToProjects::getValuePhy(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

/*********************************************************
 * getValueVirt
 *
 * Author: Sean Rogers
 *
 * Description:
 *   Gets the virtual memory usage of the program
 *
 *Arguments:
 *	nothing
 *Returns:
 *  integer value.
 */
int StudentsToProjects::getValueVirt(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

int progressBarValue = 0;


/*********************************************************
 * updateProgressBar
 *
 * Author: Sean Rogers
 *
 * Description:
 *   updates the progress bar in the GUI window.
 *
 *Arguments:
 *	int num, Fl_Progress* pb
 *Returns:
 *  integer value.
 */
void StudentsToProjects::updateProgressBar(int num, Fl_Progress* pb){
			 progressBarValue += pb->value() + num;
			 pb->value(progressBarValue/100.0);
			 char percent[10];
			 sprintf(percent, "%d%%", int((progressBarValue/100.0)*100.0));
			 pb->label(percent);
			 Fl::check();
}

/*********************************************************
 * StudentsToProjectsAssignment
 *
 *Authors: Sean, Myles, Matthew, Cristi
 *
 *Description:
 *  This function assigns the students taken in, to the projects taken in.
 *  It finds all the possible team combinations for all the students, for each project.
 *  It stores the top number of teams (user specified) for all the combinations for each project.
 *  Then, based on those top teams it finds the combination of combinations of the horizontal mapping
 *  of teams to the projects. It stores the highest scoring teams to projects set, that has no duplicate
 *  students. If this can not be found, it stores the highest scoring teams to projects set, with the least
 *  amount of duplicate students. It then swaps out the duplicate students, with the highest scoring replacement
 *  student for that project, making sure that there is no negative affinity on the team.
 *
 *Arguments:
 *	Student studentPool[], Project projectPool[], const int numStudents,const int numProjects,
 *	const int numSkills, const int teamSize,const int numTopTeams
 *
 *Returns:
 *	void
 *
 *	NOTES:
 *		For the combination of combinations of the horizontal mapping of student teams to projects,
 *		research code was found here:https://www.geeksforgeeks.org/combinations-from-n-arrays-picking-one-element-from-each-array/
 *		This was used as a reference when completing this portion of the function.
 *
 */
string StudentsToProjects::StudentsToProjectsAssignment(Student studentPool[],
	Project projectPool[], const int numStudents,const int numProjects,const int numSkills,
	const int teamSize,const int numTopTeams, Fl_Progress* progressBar, int progressIncrement) {

	string result = "";


	//timer to keep track of program runtime
    auto start = high_resolution_clock::now();
	srand(time(NULL));

	//constants
	const int TOP_TEAMS = toConstInt(numTopTeams);
	const int TEAM_SIZE = toConstInt(5);
	int PxSskill_size = numStudents*numProjects;
	const int PROJECTXSTUDETNSKILL_SIZE = toConstInt(PxSskill_size);

    //used to store the current team combinaniton.
	Team currentTeam;
	Team temp;

    //used to store the top teams for every project.
	Team currentTopTeams[TOP_TEAMS];

	//array to store checks for the top scores.
	int topscores[TOP_TEAMS];

    //initialize arrays to 0,
	for(int j = 0; j < TOP_TEAMS; j++) {
		currentTopTeams[j]=temp;
		topscores[j] = 0;
	}

	//2d array to store the top teams for every project
	Team topTeams[numProjects][TOP_TEAMS];

    //variable to store the team's skill score
    int teamskillscore = 0;
    //counter to keep track of students on a team
    int num =0;

 //------------------Do skill calculations for the student pool and the project pool.

    //give each student a PoolID.
    //and fill in skill sum score
    int studentSkillSums[numStudents];
    for(int i = 0; i < numStudents; i++) {
    	studentPool[i].PoolID = i;
    	studentPool[i].Assigned= false;
    	//studentPool[i] = *(studentPool+i);
    	studentSkillSums[i] = 0;
    	for(int j = 0; j < numSkills; j++) {
    	studentSkillSums[i] += studentPool[i].Skills[j];
    	 }
    }

    //give each project a PoolID
    //Calculate max skill score for each project.
    int maxProjectSkills[numProjects];
    int maxProjectScore=0;
    for(int i = 0; i < numProjects; i++) {
    	projectPool[i].PoolID = i;
    	maxProjectSkills[i] = 0;

    	for(int j = 0; j < numSkills; j++) {
    	maxProjectScore += projectPool[i].Skills[j] * 4;
    		}
    	maxProjectSkills[i] = maxProjectScore * TEAM_SIZE;
    	maxProjectScore = 0;
    }

    //get project skill X student skill matrix
    int ProjectXStudentSkills[PROJECTXSTUDETNSKILL_SIZE];

    Utility util;
    util.initProjectStudentSkills(projectPool, studentPool,
    		ProjectXStudentSkills, numProjects, numStudents,numSkills);

    //skillSums stores the sum of each students skills(based on a project) on a given team.
    int skillSums[TEAM_SIZE];
    //studentSkills stores the sum of each students skills(of all thier skills) on a given team.
    int studentSkills[TEAM_SIZE];
    for(int i = 0; i < TEAM_SIZE; i++) {
    	studentSkills[i] =0;
    	skillSums[i]=0;
    }
//------------------------end skill calculations


 //START--------------Team Combination process to find every student team combination for each project
    cout << "STUDENTS TO PROJECTS ASSIGNMENT RUNNING..." << endl;
    cout << getValueVirt() + getValuePhy() << " KB of memory usage: Start of Assignment" << endl;
        	for(int i = 0; i < numProjects; i++) {

        		//new combination process
        		int studentIndexes[teamSize];
        		for(int i = 0; i < teamSize; i++) {
        			studentIndexes[i] = i+1;
        		}
        		int indexToIncrement = teamSize - 1;
        		bool permuting = true;

        		//creates the combination of student teams
        		while(permuting) {
        			for(int j = 0; j < teamSize; j++) {
        				//adds the student to the team for each combination
        				currentTeam.team[num] = studentPool[studentIndexes[j] - 1];
        				studentSkills[num] =*(ProjectXStudentSkills + (i * numStudents) + currentTeam.team[num].PoolID);
        				skillSums[num] = studentSkillSums[currentTeam.team[num].PoolID];
        				num++;
        				//following commented out portion is for debugging purposes,
        				//for(int k = 0; k < numSkills; k++) {
        				//	teamskillscore += studentPool[studentIndexes[j] - 1].Skills[k] * projectPool[i].Skills[k];
        				//}
        			}
        			//----Now the team for this combination is formed.-----

        			//Negative Affinity Check
        			//check returns true if there is negative affinity on the team,
        	        //and false if there is no negative affinity.
        			if (NegativeAffinityCheck(currentTeam.team) == false){

        				//call to 3 team score functions
        				//TeamScore = func1() + func2() + func3()
        			    teamskillscore = ProjectCompareTeamScore(studentSkills, maxProjectSkills[i]) +
        				SkillCompareTeamScore(skillSums) + AvailabilityTeamScore(currentTeam.team);

        				currentTeam.TeamScore = teamskillscore;
        				currentTeam.projectID = projectPool[i].ProjectID;

                        //loop to compare the new team's score to the top scores.
        				for(int k = 0; k < TOP_TEAMS; k++) {
        						    if (k == 0){
        						    	if (currentTeam.TeamScore > topscores[k] ){
        						    	topscores[k] = currentTeam.TeamScore;
        						        currentTopTeams[k] = currentTeam;
        						        break;

        						    	}
        						    }else{
        						    	if ( currentTeam.TeamScore == topscores[k-1] | currentTeam.TeamScore > topscores[k] ){
        						        		topscores[k] = currentTeam.TeamScore;
        						        	    currentTopTeams[k] = currentTeam;
        						        	    break;
        								 }

        				}}

        		    }//end affinity check

        		   //reset these values for the next team combination
        			num = 0;
        			teamskillscore = 0;
        			currentTeam.TeamScore = 0;

        			studentIndexes[indexToIncrement]++;
        			while(studentIndexes[indexToIncrement] == numStudents - ((teamSize - 1) - (indexToIncrement + 1))){
        				indexToIncrement--;
        				if(indexToIncrement < 0) {
        					permuting = false;
        					break;
        				} else {
        					studentIndexes[indexToIncrement]++;
        				}
        			}
        			while(indexToIncrement < teamSize - 1 && permuting) {
        				indexToIncrement++;
        				studentIndexes[indexToIncrement] = studentIndexes[indexToIncrement - 1] + 1;
        			}
        		}//return to create the next team combination


        		//for each iteration over the number of projects, add in the top teams for that project into
        		//the top teams 2d array.
        		 for(int j = 0; j < TOP_TEAMS; j++) {
        				 topTeams[i][j] = currentTopTeams[j];
        				 topscores[j] = 0;
        				 }

        		cout << "Project # " + to_string(projectPool[i].ProjectID) + "  team combinations complete. " << endl;

        	} // end i loop (for each project)

 //END---------------------Team Combination process


    		//update the progress bar
    		updateProgressBar(progressIncrement*(0.35), progressBar);


 // START--------------------Project Set combinations

        	// START -Project Set combinations here
        	cout << "TOP TEAMS TO PROJECTS SET RUNNING..." << endl;

        	//Needed variables
        	//holds the current set of teams.
        	Team currentSet[numProjects];
        	//holds the current best set(with the least duplicates)
        	Team bestSet[numProjects];

        	Team temp2;

        	int teamNum = 0;
        	int topscore = 0;
        	//stores the score for currentSet[]
        	int ProjectSetScore = 0;
        	//holds the score for bestSet[]
        	int BestProjectSetScore = 0;

        	//this stores the number of duplicates in the
        	//first set, and is used as the threshold value.
        	int threshold = 0;
        	//stores the number of duplicate students in the current set.
        	int duplicateCount=0;
        	//flag to indicate if the current set has less duplicates than the threshold.
        	bool flag = false;

        	//populate arrays with temp team values
        	for (int i = 0; i < numProjects; i++) {
        	    currentSet[i] = temp2;
        	    bestSet[i] = temp2;
        	}

        	// to keep track of next element in each of
        	// the n arrays
        	//int* indices = new int[numProjects];
        	int indices[numProjects];
        	// initialize with first element's index
        	for (int i = 0; i < numProjects; i++){
        	    indices[i] = 0;}

        	//Find the duplicate student threshold (the number of duplicates in the first set)
        	for (int i = 0; i < numProjects; i++) {
        	     currentSet[teamNum] = topTeams[i][indices[i]];
        	     threshold = getDuplicatesOfStudents(currentSet, i+1);
        	     ProjectSetScore += topTeams[i][indices[i]].TeamScore;
        	     teamNum++;
        	 }

           cout << "Number of duplicates Threshold : " << threshold << endl;
        	//reset values
           topscore = ProjectSetScore;
           ProjectSetScore = 0;
           teamNum = 0;


        	while (1) {
        	    //adds a team from each top team array to the project Set.
        	    for (int i = 0; i < numProjects; i++) {

        	        currentSet[teamNum] = topTeams[i][indices[i]];

        	        ProjectSetScore += topTeams[i][indices[i]].TeamScore;
        	        teamNum++;

        	    }
        	    // return number of duplicates in currentSet
        	    duplicateCount = getDuplicatesOfStudents(currentSet, numProjects);
        	    //if the current set has more duplicates than the threshold,
        	    //end the loop.
        	    if (duplicateCount > threshold){
        	     flag = true;

        	     }

        	    if (flag==false){
        	    //Project teams combination formed,

        	    //if duplicate student check == 0.
        	    //check value against topUnique score
        	    if(duplicateCount == threshold){
        	    if(ProjectSetScore >= topscore){

        	        for (int i = 0; i < numProjects; i++) {
        	            bestSet[i] = currentSet[i];
        	            BestProjectSetScore = ProjectSetScore;
        	            topscore = BestProjectSetScore;
        	        }
        	    }
        	    }else{
        	    	//new threshold
        	    	threshold = duplicateCount;
        	        for (int i = 0; i < numProjects; i++) {
        	            bestSet[i] = currentSet[i];
        	            BestProjectSetScore = ProjectSetScore;
        	            topscore = BestProjectSetScore;
        	        }
        	    }
        	    }//end if flag

        	    //reset values
        	    teamNum = 0;
        	    ProjectSetScore = 0;
        	    duplicateCount = 0;
				flag = false;

        	    int next = numProjects - 1;
        	    while (next >= 0 &&
        	           (indices[next] + 1 >= TOP_TEAMS))
        	        next--;

        	    // no such array is found so no more
        	    // combinations left
        	    if (next < 0){
        	        break;}

        	    indices[next]++;

        	    for (int i = next + 1; i < numProjects; i++){
        	        indices[i] = 0;
        	    }
        	}

        	// END -Project Set combinations



// END -------------------Project Set combinations


    		//update the progress bar
    		updateProgressBar(progressIncrement*(0.65), progressBar);


	//Print out all the top teams with team scores for each project.
	cout<< "Top "<<TOP_TEAMS<<" teams for each project"<<endl;

	for(int i = 0; i < numProjects; i++) {
		Project project = *(projectPool + i);
		cout<< "Projects #" + to_string(project.ProjectID) + " Student Teams:"<<endl;
		for(int j = 0; j < TOP_TEAMS; j++) {

			cout << "Team #" + to_string(j) + " ";
			for(int k = 0; k < teamSize; k++) {

				cout<< to_string(topTeams[i][j].team[k].StudentID) + " ";

			}
			cout << endl;
			cout<< "TeamScore: " + to_string(topTeams[i][j].TeamScore)<<endl;
		}
		cout << endl;
	}

	//Prints out the best project set found.
	cout << endl;
	cout<< "Best Project Set with duplicates "<<endl;
	cout<< "==============================================="<<endl;
	for(int i = 0; i < numProjects; i++){
		cout << "Team for project#" + to_string(bestSet[i].projectID) + " ";
	    for(int k = 0; k < teamSize; k++) {
	        	cout<< to_string(bestSet[i].team[k].StudentID) + " ";
	   }
	    cout << endl;
	    cout << "Team Score: "<<bestSet[i].TeamScore <<endl;
	     }
	     cout<< "Best Project Set score: "<< BestProjectSetScore<<endl;
	     cout<< "Number of Duplicate Students: "<< threshold<<endl;


// START -------------------Duplicate Student Swapping

	             	//set the assigned attribute for all the students on the bestSet to true.
	             	for (int i = 0; i < numProjects; i++) {
	             	    for (int j = 0; j < TEAM_SIZE; j++){
	             	     bestSet[i].team[j].Assigned = true;
	             	     studentPool[bestSet[i].team[j].PoolID] = bestSet[i].team[j];
	             	    }
	             	}

	             	//find all the students who have not been assigned.
	             	//get the number of unassigned students.
	             	int count=0;
	             	for (int i = 0; i < numStudents; i++) {
	             		if (studentPool[i].Assigned == false){
	             			count ++;
	             		}
	             	}

	                int num_assigned = numStudents - count;
	             	const int NUM_UNASSIGNED = toConstInt(count);

	             	cout<<"Assigned Students : "<<num_assigned<<endl;
	             	cout<<"UnAssigned Students : "<<count<<endl;


	             	//Find the number of placeholder students that we will need
	             	int numPlaceholderStudents = util.NumOfTeamsOf4(numStudents,  teamSize);


	             	//reserve pool of students
	             	vector <Student> reserveStudents;


	             	for (int i = 0; i < numStudents; i++) {
	             	       if (studentPool[i].Assigned == false){
	             	        		//(array version) reservePool[element] = studentPool[i];
	             	        		reserveStudents.push_back(studentPool[i]);
	             	        }
	             	 }

	             	//add in fake students.
	             	vector<Student> fakeStudents;
	             	for (int i = 0; i < numPlaceholderStudents; i++) {
	             		Student fakeStudent;
	             		fakeStudent.StudentID = 99999;
	             		fakeStudent.PoolID = numStudents+i;
	             		//reserveStudents.push_back(fakeStudent);
	             		fakeStudents.push_back(fakeStudent);
	             	}

	             	//if number of teams of 4 needed is the same as the number of projects,
	             	//swap a fake student into the first team
	             	int minTeamCount = 0;
	             	if(numPlaceholderStudents == numProjects){
	             		//studentPool[bestSet[0].team[4].PoolID].Assigned = false;
	             		reserveStudents.push_back(studentPool[bestSet[0].team[4].PoolID]);
	             		bestSet[0].team[4] = fakeStudents[minTeamCount];
	             		fakeStudents.erase(fakeStudents.begin()+minTeamCount);
	             		 bestSet[0].team[4].ProjectID= bestSet[0].team[3].ProjectID;
	             		minTeamCount++;
	             	}
	             	if(numProjects == 1){
	             	}else{

	          ///-------swapping mechanism------

	             	 int numDuplicates = 0;
	             	 int toptempscore =0;
	             	 int tempBestStudent;

	             	 //array to store all the unique student IDs in bestSet
	             	 int uniqueStudents[num_assigned];

	             	     for (int k= 0; k< num_assigned; k ++){
	             	         uniqueStudents[k]=-1;
	             	     }
	             	     //fill unique students with the students in the first team.
	             	     if(minTeamCount == 1){
	             	     for (int i = 0 ; i < 4 ; i++){
	             	         uniqueStudents[i] = bestSet[0].team[i].StudentID;
	             	     }}else{
	             	    	for (int i = 0 ; i < 5 ; i++){
	             	    	 uniqueStudents[i] = bestSet[0].team[i].StudentID;
	             	        }

	             	     }

	             	     int num1 = TEAM_SIZE;
	             	     int num2 = 0;
	             	     bool isduplicate =false;
	             	     bool fakeST = false;
	             	     bool fakeSTNeeded = true;
	             	     bool DuplicateFound = false;

	             	     for (int i= 1; i< numProjects; i ++){

	             	    	fakeST = false;
	             	    	if(minTeamCount == numPlaceholderStudents){
	             	    		fakeSTNeeded = false;
	             	    	}else{
	             	    		fakeSTNeeded = true;
	             	    	}

								 //Get the project that the current team is assigned to.
	             	        	 Project CurrentProject;
	             	        	  for (int x= 0; x< numProjects; x ++){
	             	        	 if (bestSet[x].projectID == projectPool[x].ProjectID){
	             	        	 CurrentProject = projectPool[x];
	             	        	 }}


	             	        	 //Get a list of the reserve students, along with their skill score for that project.
	             	        	  vector< pair <int,int>> replacements;
	             	        	  for (int x= 0; x< reserveStudents.size(); x ++){

	             	        		  pair <int, int> temp = {*(ProjectXStudentSkills + (CurrentProject.PoolID * numStudents)
	             	        				  + reserveStudents[x].PoolID), reserveStudents[x].PoolID};
	             	        		  replacements.push_back(temp);
	             	        	  }

	             	        	  //sort based on the first pair element, (the reserve students skill score for that project.)
	             	        	  sort(replacements.begin(), replacements.end(), greater<>());


	             	        	  //J loop for each student in the current team.
	             	        	 for (int j= 0; j< 5; j ++){

	             	        	 //K loop to check each J student against all the unique students to find a duplicate.
	             	             for (int k= 0; k< num1; k ++){

	             	            	 //If a duplicate is found, find the best replacement student,
	             	            	 //and swap that student into the team.
	             	                 if (uniqueStudents[k] == bestSet[i].team[j].StudentID){
	             	                     numDuplicates++;
	             	                     isduplicate =true;
	             	                     DuplicateFound = true;

	             	                     for (int x= 0; x< replacements.size(); x ++){
	             	                    	 //replace the duplicate with the highest scoring student
	             	                    	 //for the current project, who is not already assigned.

	             	                    	 //check if fake student is needed.
	             	                    	if(fakeSTNeeded==true){
	             	                    	if(minTeamCount < numPlaceholderStudents){

	             	                    		 bestSet[i].team[j] = fakeStudents[minTeamCount];
	             	                    		fakeStudents.erase(fakeStudents.begin()+minTeamCount);
	             	                    		 bestSet[i].team[j].ProjectID= CurrentProject.ProjectID;
		             	                    		minTeamCount++;
		             	                    		fakeSTNeeded=false;
		             	                    		break;
	             	                    	 }}


	             	                    	 bestSet[i].team[j] = studentPool[replacements[x].second];

	             	                    	 //make sure this replacement does not have any negative affinity
	             	                    	 //with the team.
	             	                    	 if (NegativeAffinityCheck(bestSet[i].team) == false){
	             	                    		 for (int y= 0; y< reserveStudents.size(); y ++){
	             	                    			 if(reserveStudents[y].StudentID == studentPool[replacements[x].second].StudentID)
	             	                    			 //remove added student from the reserve pool
	             	                    			 reserveStudents.erase(reserveStudents.begin() + y);
	             	                    		 }
	             	                    		 //remove added student from the replacement pool
	             	                    		 replacements.erase(replacements.begin()+x);
	             	                    		 break;
	             	                    	 }

	             	                     }
	             	                 }
	             	             }//end k loop


	             	             if (isduplicate==false){
	             	                 for (int k= 0; k< num_assigned; k ++){

	             	                     if (uniqueStudents[k] == -1){
	             	                         uniqueStudents[k] = bestSet[i].team[j].StudentID;
	             	                         num2++;
	             	                         break;
	             	                         }
	             	                 }}
	             	             isduplicate = false;


	             	         }//end j loop

             	            //recalculate team score, now that all the duplicate
             	           	//students have been swapped out.
             	           	 for (int x= 0; x< TEAM_SIZE; x ++){

             	           	 if(bestSet[i].team[x].StudentID != 99999){
             	           	 studentSkills[x] =*(ProjectXStudentSkills + (CurrentProject.PoolID * numStudents) + bestSet[i].team[x].PoolID);
             	           	 skillSums[x] = studentSkillSums[bestSet[i].team[x].PoolID];
             	           	 }else{
             	           	  studentSkills[x] = 0;
             	           	   skillSums[x] = 0;
             	           	 }
             	           	 }
             	           	bestSet[i].TeamScore = ProjectCompareTeamScore(studentSkills, maxProjectSkills[CurrentProject.PoolID]) +
             	           	 SkillCompareTeamScore(skillSums) + AvailabilityTeamScore(bestSet[i].team);

	             	        	 if(DuplicateFound == false){
	             	        		if(minTeamCount < numPlaceholderStudents){

	             	        		   reserveStudents.push_back(bestSet[i].team[4]);


	             	        		  for (int k= 0; k< num1; k ++){
	             	        		  if (uniqueStudents[k] == bestSet[i].team[4].StudentID){
	             	        			 uniqueStudents[k] = 88888;

	             	        		  }
	             	        		  }

	             	        		   bestSet[i].team[4] = fakeStudents[minTeamCount];
	             	        		  fakeStudents.erase(fakeStudents.begin()+minTeamCount);
	             	        		  bestSet[i].team[4].ProjectID= bestSet[i].team[3].ProjectID;
	             	        		   minTeamCount++;

	             	        		 }
	             	        	}


	             	        DuplicateFound = false;
	             	        num1 += num2;
	             	        num2 = 0;

	             	     }//end i loop


	 	             	//set all the students in the best set to assigned.
	 	             	for (int i = 0; i < numProjects; i++) {
	 	             	    for (int j = 0; j < TEAM_SIZE; j++){
	 	             	     bestSet[i].team[j].Assigned = true;
	 	             	     bestSet[i].team[j].ProjectID =  bestSet[i].projectID;
	 	             	     if(bestSet[i].team[j].StudentID != 99999){
	 	             	     studentPool[bestSet[i].team[j].PoolID] = bestSet[i].team[j];

	 	             	     *(studentPool+(bestSet[i].team[j].PoolID))=bestSet[i].team[j];
	 	             	    }}
	 	             	}
	             	}
// END -------------------Duplicate Student Swapping

	             	     int newProjectSetScore = 0;
	             	    for(int i = 0; i < numProjects; i++){
	             	    	newProjectSetScore += bestSet[i].TeamScore;
	             	    }


	             		//Prints out the best project set found, without duplicates.
	             		cout << endl;
	             		cout<< "All duplicates Swapped out "<<endl;
	             		cout<< "==============================================="<<endl;
	             		result.append("RESULT FOR SECTION " + to_string(studentPool[0].ClassID) + ":\n");
	             		cout << "RESULT FOR SECTION " + to_string(studentPool[0].ClassID) << endl;

	             		for(int i = 0; i < numProjects; i++){
	             			cout << "Team for project#" + to_string(bestSet[i].projectID) + " ";

	             			result.append("Project#" + to_string(bestSet[i].projectID) + ": ");
	             		    for(int k = 0; k < teamSize; k++) {
	             		        	cout<< to_string(bestSet[i].team[k].StudentID) + " ";
	             		        	result.append(to_string(bestSet[i].team[k].StudentID) + " ");
	             		        	bestSet[i].team[k].ProjectID = bestSet[i].projectID;
	             		    }
	             		    result.append("\n");
	             		    cout << endl;
	             		    cout << "Team Score: "<<bestSet[i].TeamScore <<endl;
	             		    }
	             		    cout<< "Best Project Set score: "<< newProjectSetScore<<endl;
	             		    cout<< "Number of Duplicate Students: "<< 0 <<endl;



	     //KEEP TRACK OF TIME THE PROGRAM TAKES TO RUN
	  	auto stop = high_resolution_clock::now();
	  	auto duration = duration_cast<milliseconds>(stop - start);
		cout << endl;
		cout << endl;
		cout << getValueVirt() + getValuePhy() << " KB of memory usage: End of program" << endl;
		cout << endl;
		cout << "Program Runtime"<<endl;
	  	cout << "time in milliseconds: ";
	  	cout << duration.count() << endl;;
	  	cout << endl;


return result;
}//END StudentsToProjectsAssignment


//-----TEAM SCORE CALCULATING FUNCTIONS------


/*********************************************************
 * AvailabilityTeamScore
 *
 * Author: Myles Colina
 *
 * Description:
 * 	This function returns a score of 0-20 determining
 * 	the quality of the team by comparing the Availability of students
 * 	on a team to each other.
 *
 *Arguments:
 *	Student team[]
 *
 *Returns:
 *  integer value from 0 to 20.
 */
int StudentsToProjects::AvailabilityTeamScore(Student team[5]){

	int timeCompareScore = 0;

	// 10 calls to StudentToStudentAvailibility. One for each possible combination
	// of every student in the team to each-other.
	timeCompareScore += StudentToStudentAvailibility(team[0], team[1]);
	timeCompareScore += StudentToStudentAvailibility(team[0], team[2]);
	timeCompareScore += StudentToStudentAvailibility(team[0], team[3]);
	timeCompareScore += StudentToStudentAvailibility(team[0], team[4]);
	timeCompareScore += StudentToStudentAvailibility(team[1], team[2]);
	timeCompareScore += StudentToStudentAvailibility(team[1], team[3]);
	timeCompareScore += StudentToStudentAvailibility(team[1], team[4]);
	timeCompareScore += StudentToStudentAvailibility(team[2], team[3]);
	timeCompareScore += StudentToStudentAvailibility(team[2], team[4]);
	timeCompareScore += StudentToStudentAvailibility(team[3], team[4]);

	    //timeCompareScore contains a score 0-40

		//configure the score from 0-40 to 0-20
		float percent= 0;
		float max = 40;
		percent = timeCompareScore/ max;
		percent = percent * 20;
		percent = (int)percent;

		//return the score 0-20
		return percent;
}


/*********************************************************
 * StudentToStudentAvailibility
 *
 * Author: Myles Colina
 *
 * Description:
 * 	helper function for AvailabilityTeamScore, compares 2 students
 * 	returns an Availability comparison score of 0 - 4.
 *
 *Arguments:
 *	Student s1, Student s2
 *
 *Returns:
 *  integer value from 0 to 4.
 */
 int StudentsToProjects::StudentToStudentAvailibility(Student s1, Student s2){

	int score = 0;

	//checks preferred weekday selections
	if(s1.Availability[0] == s2.Availability[0]){
		score += 2;
	}else if ((s1.Availability[1] == s2.Availability[1]) | (s1.Availability[1] == s2.Availability[0])
			|(s1.Availability[0] == s2.Availability[1])){
		score += 2;
	}

	//checks preferred weekend selections
	if(s1.Availability[2] == s2.Availability[2]){
			score += 2;
		}else if ((s1.Availability[3] == s2.Availability[3]) | (s1.Availability[3] == s2.Availability[2])
				|(s1.Availability[2] == s2.Availability[3])){
			score += 2;
		}
	return score;
}

 /*********************************************************
 * SkillCompareTeamScore
 *
 * Author: Myles Colina
 *
 * Description:
 * 	This function returns a score of 0-40 determining
 * 	the quality of the team by comparing the student's skills to each other
 *
 *Arguments:
 *	Student team[]
 *
 *Returns:
 *  integer value from 0 to 40.
 */
int StudentsToProjects::SkillCompareTeamScore( int studentSkills[5]){

int teamCompareScore = 0;


teamCompareScore += StudentToStudentSkill(studentSkills[0], studentSkills[1]);
teamCompareScore += StudentToStudentSkill(studentSkills[0], studentSkills[2]);
teamCompareScore += StudentToStudentSkill(studentSkills[0], studentSkills[3]);
teamCompareScore += StudentToStudentSkill(studentSkills[0], studentSkills[4]);
teamCompareScore += StudentToStudentSkill(studentSkills[1], studentSkills[2]);
teamCompareScore += StudentToStudentSkill(studentSkills[1], studentSkills[3]);
teamCompareScore += StudentToStudentSkill(studentSkills[1], studentSkills[4]);
teamCompareScore += StudentToStudentSkill(studentSkills[2], studentSkills[3]);
teamCompareScore += StudentToStudentSkill(studentSkills[2], studentSkills[4]);
teamCompareScore += StudentToStudentSkill(studentSkills[3], studentSkills[4]);


	return teamCompareScore;

}

/*********************************************************
 * StudentToStudentSkill
 *
 * Author: Myles Colina
 *
 * Description:
 * 	helper function for SkillCompareTeamScore
 * 	returns a student to student comparison score of 0 - 4.
 *
 *Arguments:
 *	Student s1, Student s2
 *
 *Returns:
 *  integer value from 0 to 4.
 */
int StudentsToProjects::StudentToStudentSkill( int skillsum1, int skillsum2){

	  int score = skillsum1 - skillsum2;
      score = abs(score);

	  if (score == 0 || score == 1){
	  	return 4;

	  	}else if(score == 2 || score == 3){
	  	return 3;

	  	}else if(score == 4 || score == 5){
	  	return 2;

	  	}else if(score > 5 && score < 9){
	  	return 1;

	  	}else if(score >= 9){
	  	return 0;

	  	}

}


/*********************************************************
 * ProjectCompareTeamScore
 *
 * Author: Myles Colina
 *
 * Description:
 * 	This function returns a score of 0-40 determining
 * 	the quality of the team by comparing the max skills a team could have
 *  on a certain project, to the team's overall skills.
 *
 *Arguments:
 *	int studentSkills[5] -(each element is sum of each students skills for that project)
 *	int maxProjectScore - (integer that stores the maximum skill sum a team could possibly have
 *						  for this project.)
 *
 *Returns:
 *  integer value from 0 to 40.
 *
 */
 int StudentsToProjects::ProjectCompareTeamScore(int studentSkills[5], int maxProjectScore){

	int teamSkillSum = 0;

	for( int i = 0; i < 5 ; i++ ){
	 teamSkillSum += studentSkills[i]; }

    //calculate percentage
	float percent= 0;
	float max = 0;
	max = maxProjectScore;
	percent = teamSkillSum/ max;
	percent = percent * 40;
	percent = (int)percent;

    //return the score 0-40
	return percent;

}

 /*********************************************************
  * getDuplicatesOfStudents
  *
  * Author: Matthew Cilibraise
  *
  * Description:
  *   This function returns the number of duplicate students in a set of teams.
  *   Stores the IDs of unique students and compares the student IDs of the
  *   teams to that.
  *
  *Arguments:
  *	 Team currentSet[] - (array containing all the teams in the set)
  *	 int size  - (the number of teams to check in the array)
  *
  *Returns:
  *  integer value depicting the number of duplicate students.
  *
  */
 int StudentsToProjects::getDuplicatesOfStudents(Team currentSet[], int size){

     // (Debugging)show what's in currentSet
     /*    for (int i = 0 ; i < size ; i++){
      cout << "students in team: ";
      for (int j = 0 ; j < 5 ; j++){
      cout << currentSet[i].team[j].StudentID << ", ";
      }
      cout << endl;
      }*/

	 int numDuplicates = 0;
     int numStudentIDs = size*5;
     int uniqueStudents[numStudentIDs] ;

     for (int k= 0; k< numStudentIDs; k ++){
         uniqueStudents[k]=-1;
     }
     //fill unique students with the students in the first team.
     for (int i = 0 ; i < 5 ; i++){
         uniqueStudents[i] = currentSet[0].team[i].StudentID;

     }

     int num = 5;
     int num2 = 0;
     bool isduplicate = false;
     for (int i= 1; i< size; i ++){
         for (int j= 0; j< 5; j ++){
             for (int k= 0; k< num; k ++){
            	 //check the current student against all the unique studentIDs.
            	 //if the student is a duplicate, increase the count.
                 if (uniqueStudents[k] == currentSet[i].team[j].StudentID){
                     numDuplicates++;
                     isduplicate = true;
                     //cout << " DUPLICATE FOUND" << endl;
                 }
             }//end k loop

             //if the current student is not a duplicate, add them to the array of
             //unique studetnIDs.
             if (isduplicate == false){
                 for (int k= 0; k< numStudentIDs; k ++){

                     if (uniqueStudents[k] == -1){
                         uniqueStudents[k] = currentSet[i].team[j].StudentID;
                         num2++;
                         break;}
                 }}
             isduplicate = false;

         }//end j loop
         num += num2;
         num2=0;

     }//end i loop

     return numDuplicates;
 }




 /*********************************************************
 * NegativeAffinityCheck
 *
 * Author: Matthew Cilibraise
 *
 * Description:
 * currently takes in a vector of students, which represents a possible team combination.
 * function checks to see if any students have negative affinity toward one another.
 * If negative affinity between team members IS NOT found, function will return a boolean value of false,
 * If negative affinity between team member IS found, function will return a boolean value of true.
 *
 *Arguments:
 *	Student team[5] (the team of students to check)
 *
 *Returns:
 *  boolean value depicting whether the team has negative affinity or not.
 *  True - If negative affinity between team members IS found
 *  False- If negative affinity between team members IS NOT found
 *
 */
bool StudentsToProjects::NegativeAffinityCheck(Student team[5]){
	// start of with negativeAffinity being false - meaning we have not found negative affinity.
	// We will return true if we find an instance of negative affinity in this team combination.
	bool negativeAffinity = false;
	// We begin with an outer loop of that will examine each student in the team
	for (int studentTeamCounter = 0; studentTeamCounter < 5; studentTeamCounter++){

		// if the current student's affinity list is empty - we don't need about comparing any other students - so on to the next iteration
		if (team[studentTeamCounter].StudentAffinity.empty()){
			continue;
		} else {
			// lets take a look at the current students affinity list
			for (int currentStudentAffinityCounter = 0; currentStudentAffinityCounter <
			team[studentTeamCounter].StudentAffinity.size(); currentStudentAffinityCounter++){
				// next we will loop through all other students comparing the current students affinity to other students, checking for negative affinity.
				for (int otherStudentsCounter = 0; otherStudentsCounter < 5; otherStudentsCounter++){

					// because we are looping, if the current student happens to be the other student, lets continue to the next iteration.
					if (team[studentTeamCounter].StudentID == team[otherStudentsCounter].StudentID){
						continue;
						// next for each student id in the current students affinity list, lets see if the other student has the same Student ID
						// and if the affinity boolean value is false, meaning negative affinity. The current student doesn't want to work with
						// the other student. In this case we will change our negativeAffinity flag to true. We can break out of this function with
						// one instance of negative affinity. The team won't work.
					} else {
						if ((team[studentTeamCounter].StudentAffinity.at(currentStudentAffinityCounter).first == team[otherStudentsCounter].StudentID) &&
								(team[studentTeamCounter].StudentAffinity.at(currentStudentAffinityCounter).second == false)){
							negativeAffinity = true;
							break;
						}
					} // end otherStudentsCounter loop
				}
				if (negativeAffinity == true){
					break;
				}
			} // end currentStudentAffinityCounter loop
		}
		if (negativeAffinity == true){
			break;
		}
	} // end studentTeamCounter loop
	return negativeAffinity;
}
