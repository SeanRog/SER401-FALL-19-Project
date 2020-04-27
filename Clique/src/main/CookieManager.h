/*
 * CookieManager.h
 *
 * Description:
 *		This class is the header file for CookieManager.cpp.
 *		It contains all the HTTP request functions for connecting to,
 *		and retrieving data from Canvas.
 *
 *  Copyright (C) 2020 ASU
 *	Matthew Cilibraise, Myles Colina, Cristi DeLeo, Elizabeth Marquise, Sean Rogers,
 *	initial idea contributed by Douglas Sandy, All rights reserved
 */

#ifndef COOKIEMANAGER_H_
#define COOKIEMANAGER_H_

#include <curl/curl.h>
#include <string>
#include <vector>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <libsoup/soup.h>
#include "Student.h"
#include "Project.h"
#include "ClassSection.h"
#include "Team.h"

using namespace std;

class CookieManager {
public:
	vector <Student> currentStudents;

	CookieManager();
	~CookieManager();

	void getCourses(vector<SoupCookie> cookiedata);
	void getQuizzes(vector<SoupCookie> cookiedata, int course_id, string quizName, vector<Student> students);
	void getAssignment(vector<SoupCookie> cookiedata, int course_ID, int quiz_ID, vector<Student> students);
	void getQuizSubmissions(vector<SoupCookie> cookiedata,int course_ID, int quiz_ID, int assignment_ID, vector<Student> students);
	vector<Student> getStudents(vector<SoupCookie> cookiedata, int course_ID);

	static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
			void *userp);
	static void print_cookies(CURL *curl);

	int postGroupCategories(vector<SoupCookie> cookiedata, ClassSection course);
	int postGroups(vector<SoupCookie> cookiedata, int course_ID, int group_category_ID, int project_number);
	void putStudentstoGroups(vector<SoupCookie> cookiedata, Team currentTeam, int group_ID);
	int MiniBrowser(int argc, char*[]);
};

#endif /* SRC_MAIN_COOKIEMANAGER_H_ */
