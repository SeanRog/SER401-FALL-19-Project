/*
 * CookieManager.cpp
 *
 * Description:
 * 		This class contains all the HTTP request functions for connecting to Canvas.
 *		This class utilIzes libcurl to make the HTTP requests.
 *		HTTP GET requests include getting the students roster data, and the
 *		student quiz data directly from Canvas.
 *		This class uses the cookie data read in via the mini-browser authentication
 *		to authenticate the user, and maintain the authenticated session for
 *		repeated HTTP requests.
 *
 *		-Post functions
 *		The ability to post student groups to canvas has been implemented,
 *		but has not been tested as of yet.
 *
 *		-For a list of functions, see CookieManager.h
 * 
 *  Copyright (C) 2020 ASU
 *	Matthew Cilibraise, Myles Colina, Cristi DeLeo, Elizabeth Marquise, Sean Rogers,
 *	initial idea contributed by Douglas Sandy, All rights reserved
 *
 */

/********* BEGINNING OF INCLUSIONS **********/

/* Class Inclusions */
#include "CookieManager.h"
#include "Utility.h"
#include "Student.h"
#include "Team.h"

/* Library Inclusions */
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <libsoup/soup.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <map>
#include <boost/algorithm/string.hpp>

using namespace std;

/********* BEGINNING OF PROGRAM CODE **********/

//constructor
CookieManager::CookieManager() {

}

//destructor
CookieManager::~CookieManager() {
	// TODO Auto-generated destructor stub
}

//Function to convert char[] into constant expressions.
constexpr char* toConstChar(char *constInt) {
	return constInt;
}

//function to print the cookies for debugging purposes.
void CookieManager::print_cookies(CURL *curl) {
	CURLcode res;
	struct curl_slist *cookies;
	struct curl_slist *nc;
	int i;

	printf("Cookies, curl knows:\n");

	res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);

	if (res != CURLE_OK) {
		fprintf(stderr, "Curl curl_easy_getinfo failed: %s\n",
				curl_easy_strerror(res));
		exit(1);
	}

	nc = cookies;
	i = 1;

	while (nc) {
		printf("[%d]: %s\n", i, nc->data);
		nc = nc->next;
		i++;
	}
	if (i == 1) {
		printf("(none)\n");
	}
	curl_slist_free_all(cookies);
}

/*********************************************************
 * getCourses
 *
 * Author: Myles Colina, Cristi Deleo
 *
 * Description:
 * 	Performs an HTTP get request to CANVAS to get all the courses
 * 	That the user has access to. Implements pagination to get all
 * 	of the data.
 *
 *Arguments:
 *	vector<SoupCookie> cookiedata, int course_ID, string quizName
 *
 *Returns:
 *  nothing
 */
void CookieManager::getCourses(vector<SoupCookie> cookiedata) {

	CURL *curl;
	CURLcode res;
	std::string cookieBuffer;
	struct curl_slist *headers = NULL;

	bool next_url_present = true;
	bool first = true;

	//the URL for the first HTTP request
	char *url_request;
	string url_string;
	string url_request_string =
			"https://canvas.asu.edu/api/v1/courses?page=1&per_page=100";

	//convert the cookie string to a char*
	int length_url_string = url_request_string.length();
	char url_request1[length_url_string + 1];
	strcpy(url_request1, url_request_string.c_str());
	url_request = url_request1;

	//read in the cookie data from the vector and store it in a string
	std::string cookies;
	std::string temp_cookies;

	cookies = cookiedata[0].name;
	cookies += "=";
	cookies += cookiedata[0].value;
	cookies += "; ";

	for (int i = 1; i < cookiedata.size(); i++) {
		cookies += cookiedata[i].name;
		cookies += "=";
		cookies += cookiedata[i].value;
		cookies += "; ";
	}

	//convert the cookie string to a char*
	int length = cookies.length();
	char cookie_char[length + 1];
	strcpy(cookie_char, cookies.c_str());

	char *cookiesAll = cookie_char;
	//cout << cookiesAll << endl;

	//while loop
	while (next_url_present == true) {
		std::string Headers;
		std::string readBuffer;

		//start libcurl
		curl = curl_easy_init();

		if (curl) {
			//curl_easy_setopt(curl, CURLOPT_URL,
			//		"https://canvas.asu.edu/api/v1/courses?page=1&per_page=100");

			if (first == true) {
				curl_easy_setopt(curl, CURLOPT_URL, url_request);
			} else {

				int length_url = url_string.length();
				char url_char[length_url + 1];
				strcpy(url_char, url_string.c_str());

				//cout << url_char << endl;
				curl_easy_setopt(curl, CURLOPT_URL, url_char);
			}

			curl_easy_setopt(curl, CURLOPT_COOKIE, cookiesAll);

			curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L); /* no more POST */
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); /* redirects! */

			//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //for debugging

			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &Headers);

			res = curl_easy_perform(curl);

			if (first == true) {
				readBuffer.erase(0, 9); //removes the "while (1);" from the string.

			} else {
				readBuffer.erase(0, 10); //removes the "while (1);[" from the string.
			}

			//for debugging
			//std::cout << readBuffer << std::endl;
			//std::cout << Headers << std::endl;

			//store the header string into a map of string Key and Value pairs.
			std::map<string, string> HeaderMap;
			istringstream resp(Headers);
			string header;
			string::size_type index;
			while (getline(resp, header) && header != "\r") {
				index = header.find(':', 0);
				if (index != string::npos) {
					HeaderMap.insert(
							std::make_pair(
									boost::algorithm::trim_copy(
											header.substr(0, index)),
									boost::algorithm::trim_copy(
											header.substr(index + 1))));
				}
			}

			//get the Link Headers from the header string.
			string LinkHeaders;
			for (auto &KeyValue : HeaderMap) {

				if (KeyValue.first.compare("Link") == 0) {

					LinkHeaders = KeyValue.second;
				}
			}

			//if the link header contains rel ="next" then get the corresponding url
			//from link header to the next page.
			if (LinkHeaders.find("rel=\"next\"") != string::npos) {

				std::string delimiter1 = ">; rel=\"next\"";
				std::string delimiter2 = ">; rel=\"current\",<";

				size_t pos = 0;
				size_t pos2 = 0;
				string url;
				string url_temp;
				pos = LinkHeaders.find(delimiter1);
				pos2 = LinkHeaders.find(delimiter2);
				pos2 += delimiter2.length();

				url_temp = LinkHeaders.substr(0, pos);
				url = url_temp.substr(pos2, url_temp.length());

				//set the url string to the one found in the
				//link header
				url_string = url;

			} else {
				//no more pages.
				next_url_present = false;
			}

			//write the course data to a Json file
			if (first == true) {

				//if there is another page to read in
				if (next_url_present == true) {

					readBuffer.erase(
							readBuffer.begin() + readBuffer.length() - 2,
							readBuffer.end());
				}
				//write all the courses to a json file.
				ofstream courses;
				courses.open("allCourses.json");
				courses << "{\"courses\": ";
				courses << readBuffer;
				courses.close();

			} else {

				//if there is another page to read in
				if (next_url_present == true) {

					readBuffer.erase(
							readBuffer.begin() + readBuffer.length() - 2,
							readBuffer.end());
				}
				ofstream courses;
				courses.open("allCourses.json", ios::app);
				courses << ",";
				courses << readBuffer;
				courses.close();
			}

			first = false;

		}

		//add the final bracket to the Json file
		ofstream courses;
		courses.open("allCourses.json", ios::app);
		courses << "}";
		courses.close();

		// Check for errors
		if (res != CURLE_OK) {
			fprintf(stderr, "second curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
		}
	}

	// always cleanup
	curl_easy_cleanup(curl);
}

/*********************************************************
 * getQuizzes
 *
 * Author: Myles Colina
 *
 * Description:
 * 	Performs an HTTP get request to CANVAS to get the quiz submissions.
 * 	Then calls a utility function to get the quiz id whose title mathces the
 * 	name entered in the GUI.
 *
 *
 *Arguments:
 *	vector<SoupCookie> cookiedata, int course_ID, string quizName
 *
 *Returns:
 *  nothing
 */
void CookieManager::getQuizzes(vector<SoupCookie> cookiedata, int course_ID,
		string quizName, vector<Student> students) {

	CURL *curl;
	CURLcode res;
	std::string cookieBuffer;
	struct curl_slist *headers = NULL;

	bool next_url_present = true;
	bool first = true;

	//read in the cookie data from the vector and store it in a string
	std::string cookies;
	std::string temp_cookies;

	cookies = cookiedata[0].name;
	cookies += "=";
	cookies += cookiedata[0].value;
	cookies += "; ";

	for (int i = 1; i < cookiedata.size(); i++) {
		cookies += cookiedata[i].name;
		cookies += "=";
		cookies += cookiedata[i].value;
		cookies += "; ";
	}

	//convert the cookie string to a char*
	int length = cookies.length();
	char cookie_char[length + 1];
	strcpy(cookie_char, cookies.c_str());

	char *cookiesAll = cookie_char;
	//cout << cookiesAll << endl;

	//configure the URL
	//the URL for the first HTTP request
	char *url_request;
	string url_string;
	string url_request_string;
	url_request_string = "https://canvas.asu.edu/api/v1/courses/";
	url_request_string += to_string(course_ID);
	url_request_string += "/quizzes?page=1&per_page=100";

	//convert the cookie string to a char*
	int length_url_string = url_request_string.length();
	char url_request1[length_url_string + 1];
	strcpy(url_request1, url_request_string.c_str());
	url_request = url_request1;

	//while loop
	while (next_url_present == true) {
		std::string Headers;
		std::string readBuffer;

		//start libcurl
		curl = curl_easy_init();

		if (curl) {

			if (first == true) {
				curl_easy_setopt(curl, CURLOPT_URL, url_request);
			} else {

				int length_url = url_string.length();
				char url_char[length_url + 1];
				strcpy(url_char, url_string.c_str());

			//cout << url_char << endl;
				curl_easy_setopt(curl, CURLOPT_URL, url_char);
			}

			curl_easy_setopt(curl, CURLOPT_COOKIE, cookiesAll);

			curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L); /* no more POST */
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); /* redirects! */

			//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //for debugging

			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &Headers);

			res = curl_easy_perform(curl);

			if (first == true) {
				readBuffer.erase(0, 9); //removes the "while (1);" from the string.

			} else {
				readBuffer.erase(0, 10); //removes the "while (1);[" from the string.
			}

			//for debugging
			//std::cout << readBuffer << std::endl;
			//std::cout << Headers << std::endl;

			//store the header string into a map of string Key and Value pairs.
			std::map<string, string> HeaderMap;
			istringstream resp(Headers);
			string header;
			string::size_type index;
			while (getline(resp, header) && header != "\r") {
				index = header.find(':', 0);
				if (index != string::npos) {
					HeaderMap.insert(
							std::make_pair(
									boost::algorithm::trim_copy(
											header.substr(0, index)),
									boost::algorithm::trim_copy(
											header.substr(index + 1))));
				}
			}

			//get the Link Headers from the header string.
			string LinkHeaders;
			for (auto &KeyValue : HeaderMap) {

				if (KeyValue.first.compare("Link") == 0) {

					LinkHeaders = KeyValue.second;
				}
			}

			//if the link header contains rel ="next" then get the corresponding url
			//from link header to the next page.
			if (LinkHeaders.find("rel=\"next\"") != string::npos) {

				std::string delimiter1 = ">; rel=\"next\"";
				std::string delimiter2 = ">; rel=\"current\",<";

				size_t pos = 0;
				size_t pos2 = 0;
				string url;
				string url_temp;
				pos = LinkHeaders.find(delimiter1);
				pos2 = LinkHeaders.find(delimiter2);
				pos2 += delimiter2.length();

				url_temp = LinkHeaders.substr(0, pos);
				url = url_temp.substr(pos2, url_temp.length());

				//set the url string to the one found in the
				//link header
				url_string = url;

			} else {
				//no more pages.
				next_url_present = false;
			}

			//write the course data to a Json file
			if (first == true) {

				//if there is another page to read in
				if (next_url_present == true) {

					readBuffer.erase(
							readBuffer.begin() + readBuffer.length() - 2,
							readBuffer.end());
				}
				//write all the courses to a json file.
				ofstream courses;
				courses.open("allQuizzes.json");
				courses << "{\"quizzes\": ";
				courses << readBuffer;
				courses.close();

			} else {

				//if there is another page to read in
				if (next_url_present == true) {

					readBuffer.erase(
							readBuffer.begin() + readBuffer.length() - 2,
							readBuffer.end());
				}
				ofstream courses;
				courses.open("allQuizzes.json", ios::app);
				courses << ",";
				courses << readBuffer;
				courses.close();
			}

			first = false;

		}

		//add the final bracket to the Json file
		ofstream courses;
		courses.open("allQuizzes.json", ios::app);
		courses << "}";
		courses.close();

		// Check for errors
		if (res != CURLE_OK) {
			fprintf(stderr, "second curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
		}
	}

	// always cleanup
	curl_easy_cleanup(curl);

	//Get the unique Quiz id, by searching all the quizzes in the Json file
	//for the quiz whose name matches the quiz name.
	Utility util;
	int quiz_ID = util.getQuizID(quizName, "allQuizzes.json");

	//cout << "Quiz ID for the quiz: " << quiz_ID << endl;

	//delete the quiz json file now that we are done with it.
	remove("allQuizzes.json");

	getAssignment(cookiedata, course_ID, quiz_ID, students);

}

/*********************************************************
 * getStudents
 *
 * Author: Matt Cilibraise
 *
 * Description:
 * 	Performs an HTTP get request to CANVAS to get the student enrollment.
 * 	Then calls a utility function to get the student enrollment for a
 * 	course id
 *
 *
 *Arguments:
 *	vector<SoupCookie> cookiedata, int course_ID
 *
 *Returns:
 *  vector of students from the selected course
 */
vector<Student> CookieManager::getStudents(vector<SoupCookie> cookiedata,
		int course_ID) {

	CURL *curl;
	CURLcode res;
	std::string cookieBuffer;
	struct curl_slist *headers = NULL;

	bool next_url_present = true;
	bool first = true;

	//read in the cookie data from the vector and store it in a string
	std::string cookies;
	std::string temp_cookies;

	cookies = cookiedata[0].name;
	cookies += "=";
	cookies += cookiedata[0].value;
	cookies += "; ";

	for (int i = 1; i < cookiedata.size(); i++) {
		cookies += cookiedata[i].name;
		cookies += "=";
		cookies += cookiedata[i].value;
		cookies += "; ";
	}

	//convert the cookie string to a char*
	int length = cookies.length();
	char cookie_char[length + 1];
	strcpy(cookie_char, cookies.c_str());

	char *cookiesAll = cookie_char;
	//cout << cookiesAll << endl;

	//configure the URL
	//the URL for the first HTTP request
	char *url_request;
	string url_string;
	string url_request_string;

	url_request_string = "https://canvas.asu.edu/api/v1/courses/";
	url_request_string += to_string(course_ID);
	url_request_string += "/enrollments?page=1&per_page=100";

	//convert the cookie string to a char*
	int length_url_string = url_request_string.length();
	char url_request1[length_url_string + 1];
	strcpy(url_request1, url_request_string.c_str());
	url_request = url_request1;

	//while loop
	while (next_url_present == true) {
		std::string Headers;
		std::string readBuffer;

		//start libcurl
		curl = curl_easy_init();

		if (curl) {

			if (first == true) {
				curl_easy_setopt(curl, CURLOPT_URL, url_request);
			} else {

				int length_url = url_string.length();
				char url_char[length_url + 1];
				strcpy(url_char, url_string.c_str());

				//cout << url_char << endl;
				curl_easy_setopt(curl, CURLOPT_URL, url_char);
			}

			curl_easy_setopt(curl, CURLOPT_COOKIE, cookiesAll);

			curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L); /* no more POST */
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); /* redirects! */

			//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //for debugging

			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &Headers);

			res = curl_easy_perform(curl);

			if (first == true) {
				readBuffer.erase(0, 9); //removes the "while (1);" from the string.

			} else {
				readBuffer.erase(0, 10); //removes the "while (1);[" from the string.
			}

			//for debugging
			//std::cout << readBuffer << std::endl;
			//std::cout << Headers << std::endl;

			//store the header string into a map of string Key and Value pairs.
			std::map<string, string> HeaderMap;
			istringstream resp(Headers);
			string header;
			string::size_type index;
			while (getline(resp, header) && header != "\r") {
				index = header.find(':', 0);
				if (index != string::npos) {
					HeaderMap.insert(
							std::make_pair(
									boost::algorithm::trim_copy(
											header.substr(0, index)),
									boost::algorithm::trim_copy(
											header.substr(index + 1))));
				}
			}

			//get the Link Headers from the header string.
			string LinkHeaders;
			for (auto &KeyValue : HeaderMap) {

				if (KeyValue.first.compare("Link") == 0) {

					LinkHeaders = KeyValue.second;
				}
			}

			//if the link header contains rel ="next" then get the corresponding url
			//from link header to the next page.
			if (LinkHeaders.find("rel=\"next\"") != string::npos) {

				std::string delimiter1 = ">; rel=\"next\"";
				std::string delimiter2 = ">; rel=\"current\",<";

				size_t pos = 0;
				size_t pos2 = 0;
				string url;
				string url_temp;
				pos = LinkHeaders.find(delimiter1);
				pos2 = LinkHeaders.find(delimiter2);
				pos2 += delimiter2.length();

				url_temp = LinkHeaders.substr(0, pos);
				url = url_temp.substr(pos2, url_temp.length());

				//set the url string to the one found in the
				//link header
				url_string = url;

			} else {
				//no more pages.
				next_url_present = false;
			}

			//write the course data to a Json file
			if (first == true) {

				//if there is another page to read in
				if (next_url_present == true) {

					readBuffer.erase(
							readBuffer.begin() + readBuffer.length() - 2,
							readBuffer.end());
				}
				//write all the courses to a json file.
				ofstream courses;
				courses.open("allStudents.json");
				courses << "{\"students\": ";
				courses << readBuffer;
				courses.close();

			} else {

				//if there is another page to read in
				if (next_url_present == true) {

					readBuffer.erase(
							readBuffer.begin() + readBuffer.length() - 2,
							readBuffer.end());
				}
				ofstream courses;
				courses.open("allStudents.json", ios::app);
				courses << ",";
				courses << readBuffer;
				courses.close();
			}

			first = false;

		}

		//add the final bracket to the Json file
		ofstream courses;
		courses.open("allStudents.json", ios::app);
		courses << "}";
		courses.close();

		// Check for errors
		if (res != CURLE_OK) {
			fprintf(stderr, "second curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
		}
	}

	// always cleanup
	curl_easy_cleanup(curl);

	Utility u;
	vector<Student> students = u.getStudentsFromJson("allStudents.json");

	remove("allStudents.json");

	return students;

}

/*********************************************************
 * getAssignment
 *
 * Author: Myles Colina
 *
 * Description:
 * 	Performs an HTTP get request to CANVAS to get the assignments
 * 	for all the students based on the course. Then calls a utility
 * 	function to get the assignment id for the survey.
 *
 *
 *Arguments:
 *	vector<SoupCookie> cookiedata,int course_ID, int quiz_ID
 *
 *Returns:
 *  nothing
 */
void CookieManager::getAssignment(vector<SoupCookie> cookiedata, int course_ID,
		int quiz_ID, vector<Student> students) {

	CURL *curl;
	CURLcode res;
	std::string cookieBuffer;
	struct curl_slist *headers = NULL;

	bool next_url_present = true;
	bool first = true;

	//read in the cookie data from the vector and store it in a string
	std::string cookies;
	std::string temp_cookies;

	cookies = cookiedata[0].name;
	cookies += "=";
	cookies += cookiedata[0].value;
	cookies += "; ";

	for (int i = 1; i < cookiedata.size(); i++) {
		cookies += cookiedata[i].name;
		cookies += "=";
		cookies += cookiedata[i].value;
		cookies += "; ";
	}

	//convert the cookie string to a char*
	int length = cookies.length();
	char cookie_char[length + 1];
	strcpy(cookie_char, cookies.c_str());

	char *cookiesAll = cookie_char;
	//cout << cookiesAll << endl;

	//configure the URL
	//the URL for the first HTTP request
	char *url_request;
	string url_string;
	string url_request_string;

	url_request_string = "https://canvas.asu.edu/api/v1/courses/";
	url_request_string += to_string(course_ID);
	url_request_string += "/assignments?page=1&per_page=100";

	//convert the cookie string to a char*
	int length_url_string = url_request_string.length();
	char url_request1[length_url_string + 1];
	strcpy(url_request1, url_request_string.c_str());
	url_request = url_request1;

	//while loop
	while (next_url_present == true) {
		std::string Headers;
		std::string readBuffer;

		//start libcurl
		curl = curl_easy_init();

		if (curl) {

			if (first == true) {
				curl_easy_setopt(curl, CURLOPT_URL, url_request);
			} else {

				int length_url = url_string.length();
				char url_char[length_url + 1];
				strcpy(url_char, url_string.c_str());

				//cout << url_char << endl;
				curl_easy_setopt(curl, CURLOPT_URL, url_char);
			}

			curl_easy_setopt(curl, CURLOPT_COOKIE, cookiesAll);

			curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L); /* no more POST */
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); /* redirects! */

			//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //for debugging

			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &Headers);

			res = curl_easy_perform(curl);

			if (first == true) {
				readBuffer.erase(0, 9); //removes the "while (1);" from the string.

			} else {
				readBuffer.erase(0, 10); //removes the "while (1);[" from the string.
			}

			//for debugging
			//std::cout << readBuffer << std::endl;
			//std::cout << Headers << std::endl;

			//store the header string into a map of string Key and Value pairs.
			std::map<string, string> HeaderMap;
			istringstream resp(Headers);
			string header;
			string::size_type index;
			while (getline(resp, header) && header != "\r") {
				index = header.find(':', 0);
				if (index != string::npos) {
					HeaderMap.insert(
							std::make_pair(
									boost::algorithm::trim_copy(
											header.substr(0, index)),
									boost::algorithm::trim_copy(
											header.substr(index + 1))));
				}
			}

			//get the Link Headers from the header string.
			string LinkHeaders;
			for (auto &KeyValue : HeaderMap) {

				if (KeyValue.first.compare("Link") == 0) {

					LinkHeaders = KeyValue.second;
				}
			}

			//if the link header contains rel ="next" then get the corresponding url
			//from link header to the next page.
			if (LinkHeaders.find("rel=\"next\"") != string::npos) {

				std::string delimiter1 = ">; rel=\"next\"";
				std::string delimiter2 = ">; rel=\"current\",<";

				size_t pos = 0;
				size_t pos2 = 0;
				string url;
				string url_temp;
				pos = LinkHeaders.find(delimiter1);
				pos2 = LinkHeaders.find(delimiter2);
				pos2 += delimiter2.length();

				url_temp = LinkHeaders.substr(0, pos);
				url = url_temp.substr(pos2, url_temp.length());

				//set the url string to the one found in the
				//link header
				url_string = url;

			} else {
				//no more pages.
				next_url_present = false;
			}

			//write the course data to a Json file
			if (first == true) {

				//if there is another page to read in
				if (next_url_present == true) {

					readBuffer.erase(
							readBuffer.begin() + readBuffer.length() - 2,
							readBuffer.end());
				}
				//write all the courses to a json file.
				ofstream courses;
				courses.open("allAssignments.json");
				courses << "{\"assignments\": ";
				courses << readBuffer;
				courses.close();

			} else {

				//if there is another page to read in
				if (next_url_present == true) {

					readBuffer.erase(
							readBuffer.begin() + readBuffer.length() - 2,
							readBuffer.end());
				}
				ofstream courses;
				courses.open("allAssignments.json", ios::app);
				courses << ",";
				courses << readBuffer;
				courses.close();
			}

			first = false;

		}

		//add the final bracket to the Json file
		ofstream courses;
		courses.open("allAssignments.json", ios::app);
		courses << "}";
		courses.close();

		// Check for errors
		if (res != CURLE_OK) {
			fprintf(stderr, "second curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
		}
	}

	// always cleanup
	curl_easy_cleanup(curl);

	//Get the unique assignment id, by searching all the quizzes in the Json file
	//for the quiz whose name matches the quiz name.
	Utility util;
	int assignment_ID = util.getAssignmentID(quiz_ID, "allAssignments.json");

	//cout << "Assignment ID for the quiz: " << assignment_ID << endl;

	//delete the quiz json file now that we are done with it.
	remove("allAssignments.json");

	getQuizSubmissions(cookiedata, course_ID, quiz_ID, assignment_ID, students);

}

/*********************************************************
 * getQuizSubmissions
 *
 * Author: Myles Colina
 *
 * Description:
 * 	Performs an HTTP get request to CANVAS to get the quiz submission answers
 * 	for all the students. Then calls a utility
 * 	function to assign all the quiz answer data to the students.
 *
 *
 *Arguments:
 *	vector<SoupCookie> cookiedata, int course_ID, int quiz_ID, int assignment_ID
 *
 *Returns:
 *  nothing
 */
void CookieManager::getQuizSubmissions(vector<SoupCookie> cookiedata,
		int course_ID, int quiz_ID, int assignment_ID,
		vector<Student> students) {

	CURL *curl;
	CURLcode res;
	std::string cookieBuffer;
	struct curl_slist *headers = NULL;

	bool next_url_present = true;
	bool first = true;

	//read in the cookie data from the vector and store it in a string
	std::string cookies;
	std::string temp_cookies;

	cookies = cookiedata[0].name;
	cookies += "=";
	cookies += cookiedata[0].value;
	cookies += "; ";

	for (int i = 1; i < cookiedata.size(); i++) {
		cookies += cookiedata[i].name;
		cookies += "=";
		cookies += cookiedata[i].value;
		cookies += "; ";
	}

	//convert the cookie string to a char*
	int length = cookies.length();
	char cookie_char[length + 1];
	strcpy(cookie_char, cookies.c_str());

	char *cookiesAll = cookie_char;
	//cout << cookiesAll << endl;

	//configure the URL
	//the URL for the first HTTP request
	char *url_request;
	string url_string;
	string url_request_string;

	url_request_string = "https://canvas.asu.edu/api/v1/courses/";
	url_request_string += to_string(course_ID);
	url_request_string += "/assignments/";
	url_request_string += to_string(assignment_ID);
	url_request_string +=
			"/submissions?include[]=submission_history&page=1&per_page=100";

	//convert the cookie string to a char*
	int length_url_string = url_request_string.length();
	char url_request1[length_url_string + 1];
	strcpy(url_request1, url_request_string.c_str());
	url_request = url_request1;

	//while loop
	while (next_url_present == true) {
		std::string Headers;
		std::string readBuffer;

		//start libcurl
		curl = curl_easy_init();

		if (curl) {

			if (first == true) {
				curl_easy_setopt(curl, CURLOPT_URL, url_request);
			} else {

				int length_url = url_string.length();
				char url_char[length_url + 1];
				strcpy(url_char, url_string.c_str());

				//cout << url_char << endl;
				curl_easy_setopt(curl, CURLOPT_URL, url_char);
			}

			curl_easy_setopt(curl, CURLOPT_COOKIE, cookiesAll);

			curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L); /* no more POST */
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); /* redirects! */

			//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //for debugging

			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &Headers);

			res = curl_easy_perform(curl);

			if (first == true) {
				readBuffer.erase(0, 9); //removes the "while (1);" from the string.

			} else {
				readBuffer.erase(0, 10); //removes the "while (1);[" from the string.
			}

			//for debugging
			//std::cout << readBuffer << std::endl;
			//std::cout << Headers << std::endl;

			//store the header string into a map of string Key and Value pairs.
			std::map<string, string> HeaderMap;
			istringstream resp(Headers);
			string header;
			string::size_type index;
			while (getline(resp, header) && header != "\r") {
				index = header.find(':', 0);
				if (index != string::npos) {
					HeaderMap.insert(
							std::make_pair(
									boost::algorithm::trim_copy(
											header.substr(0, index)),
									boost::algorithm::trim_copy(
											header.substr(index + 1))));
				}
			}

			//get the Link Headers from the header string.
			string LinkHeaders;
			for (auto &KeyValue : HeaderMap) {

				if (KeyValue.first.compare("Link") == 0) {

					LinkHeaders = KeyValue.second;
				}
			}

			//if the link header contains rel ="next" then get the corresponding url
			//from link header to the next page.
			if (LinkHeaders.find("rel=\"next\"") != string::npos) {

				std::string delimiter1 = ">; rel=\"next\"";
				std::string delimiter2 = ">; rel=\"current\",<";

				size_t pos = 0;
				size_t pos2 = 0;
				string url;
				string url_temp;
				pos = LinkHeaders.find(delimiter1);
				pos2 = LinkHeaders.find(delimiter2);
				pos2 += delimiter2.length();

				url_temp = LinkHeaders.substr(0, pos);
				url = url_temp.substr(pos2, url_temp.length());

				//set the url string to the one found in the
				//link header
				url_string = url;

			} else {
				//no more pages.
				next_url_present = false;
			}

			//write the data to a Json file
			if (first == true) {

				//if there is another page to read in
				if (next_url_present == true) {

					readBuffer.erase(
							readBuffer.begin() + readBuffer.length() - 2,
							readBuffer.end());
				}
				//write all the courses to a json file.
				ofstream courses;
				courses.open("allSubmissions.json");
				courses << "{\"submissions\": ";
				courses << readBuffer;
				courses.close();

			} else {

				//if there is another page to read in
				if (next_url_present == true) {

					readBuffer.erase(
							readBuffer.begin() + readBuffer.length() - 2,
							readBuffer.end());
				}
				ofstream courses;
				courses.open("allSubmissions.json", ios::app);
				courses << ",";
				courses << readBuffer;
				courses.close();
			}

			first = false;

		}

		//add the final bracket to the Json file
		ofstream courses;
		courses.open("allSubmissions.json", ios::app);
		courses << "}";
		courses.close();

		// Check for errors
		if (res != CURLE_OK) {
			fprintf(stderr, "second curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
		}
	}

	// always cleanup
	curl_easy_cleanup(curl);

	Utility util;

	vector<Student> Allstudents = util.getSurveyAnswers(students, assignment_ID,
			"allSubmissions.json");

	currentStudents = Allstudents;

	remove("allSubmissions.json");

}
/*********************************************************
 * postGroupCategories
 *
 * Author: Myles Colina,
 *
 * Description:
 * 	Performs an HTTP post request to CANVAS to make a groups categories, for the
 * 	given course.
 *
 *Arguments:
 *	vector<SoupCookie> cookiedata, ClassSection course
 *
 *Returns:
 *  int the group_categoriy ID
 */
int CookieManager::postGroupCategories(vector<SoupCookie> cookiedata,
		ClassSection course) {

	CURL *curl;
	CURLcode res;
	std::string cookieBuffer;
	struct curl_slist *headers = NULL;

	//read in the cookie data from the vector and store it in a string
	std::string cookies;
	std::string temp_cookies;

	cookies = cookiedata[0].name;
	cookies += "=";
	cookies += cookiedata[0].value;
	cookies += "; ";

	for (int i = 1; i < cookiedata.size(); i++) {
		cookies += cookiedata[i].name;
		cookies += "=";
		cookies += cookiedata[i].value;
		cookies += "; ";
	}

	//convert the cookie string to a char*
	int length = cookies.length();
	char cookie_char[length + 1];
	strcpy(cookie_char, cookies.c_str());

	char *cookiesAll = cookie_char;
	//cout << cookiesAll << endl;

	std::string Headers;
	std::string readBuffer;

	//start libcurl
	curl = curl_easy_init();

	if (curl) {

		//the URL for request
		string url_request_string = "https://canvas.asu.edu/api/v1/courses/";
		url_request_string += to_string(course.OfficialClassID);
		url_request_string += "/group_categories";

		//convert the url string to a char*
		int length_url_string = url_request_string.length();
		char url_request[length_url_string + 1];
		strcpy(url_request, url_request_string.c_str());

		curl_easy_setopt(curl, CURLOPT_URL, url_request);

		curl_easy_setopt(curl, CURLOPT_COOKIE, cookiesAll);

		//set the group category data
		string group_data = "name=ProjectGroups";

		//convert the group data string to a char*
		int length_group = group_data.length();
		char group_data_char[length_group + 1];
		strcpy(group_data_char, group_data.c_str());

		cout << group_data_char << endl;

		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE,
				(long ) strlen(group_data_char));

		curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, group_data_char);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);

		readBuffer.erase(0, 9); //removes the "while (1);" from the string.
		//cout << readBuffer << endl;

		//write the data to a Json file
		ofstream file;
		file.open("groupCategories.json");
		file << "{\"categories\": ";
		file << readBuffer;
		file << "}";
		file.close();

		// Check for errors
		if (res != CURLE_OK) {
			fprintf(stderr, "second curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
		}

		// always cleanup
		curl_easy_cleanup(curl);
	}

	Utility util;
	int group_category_ID = util.getCategoryID(course.OfficialClassID,
			"groupCategories.json");
	remove("groupCategories.json");

	return group_category_ID;
}

/*********************************************************
 * postGroups
 *
 * Author: Myles Colina
 *
 * Description:
 * 	Performs an HTTP post request to CANVAS to make a group, given the team, class section
 * 	and project number.
 *
 *Arguments:
 *	vector<SoupCookie> cookiedata
 *
 *Returns:
 *  nothing
 */
int CookieManager::postGroups(vector<SoupCookie> cookiedata, int course_ID,
		int group_category_ID, int project_number) {

	CURL *curl;
	CURLcode res;
	std::string cookieBuffer;
	struct curl_slist *headers = NULL;

	//the URL for the first HTTP request
	char *url_request;
	string url_string;
	string url_request_string =
			"https://canvas.asu.edu/api/v1/group_categories/";
	url_request_string += to_string(group_category_ID);
	url_request_string += "/groups";

	//convert the url string to a char*
	int length_url_string = url_request_string.length();
	char url_request1[length_url_string + 1];
	strcpy(url_request1, url_request_string.c_str());
	url_request = url_request1;

	//read in the cookie data from the vector and store it in a string
	std::string cookies;
	std::string temp_cookies;

	cookies = cookiedata[0].name;
	cookies += "=";
	cookies += cookiedata[0].value;
	cookies += "; ";

	for (int i = 1; i < cookiedata.size(); i++) {
		cookies += cookiedata[i].name;
		cookies += "=";
		cookies += cookiedata[i].value;
		cookies += "; ";
	}

	//convert the cookie string to a char*
	int length = cookies.length();
	char cookie_char[length + 1];
	strcpy(cookie_char, cookies.c_str());

	char *cookiesAll = cookie_char;

	std::string Headers;
	std::string readBuffer;

	//start libcurl
	curl = curl_easy_init();

	if (curl) {

		curl_easy_setopt(curl, CURLOPT_URL, url_request);

		curl_easy_setopt(curl, CURLOPT_COOKIE, cookiesAll);

		//for each team set the GROUP name

		string group_data = "name=Project ";
		group_data += to_string(project_number);
		group_data += " ASU (Capstone Project Assignment)";

		group_data += "&is_public=false";

		//convert the group data string to a char*
		int length_group = group_data.length();
		char group_data_char[length_group + 1];
		strcpy(group_data_char, group_data.c_str());

		//cout << group_data_char << endl;

		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE,
				(long ) strlen(group_data_char));

		curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, group_data_char);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);

		readBuffer.erase(0, 9); //removes the "while (1);" from the string.
		//cout << readBuffer << endl;

		//write the data to a Json file
		ofstream file;
		file.open("groups.json");
		file << "{\"groups\": ";
		file << readBuffer;
		file << "}";
		file.close();

		// Check for errors
		if (res != CURLE_OK) {
			fprintf(stderr, "second curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
		}

		// always cleanup
		curl_easy_cleanup(curl);
	}

	Utility util;
	int group_ID = util.getGroupID(course_ID, "groups.json");
	remove("groups.json");

	return group_ID;
}

size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
	FILE *readhere = (FILE*) userdata;
	curl_off_t nread;

	/* copy as much data as possible into the 'ptr' buffer, but no more than
	 'size' * 'nmemb' bytes! */
	size_t retcode = fread(ptr, size, nmemb, readhere);

	nread = (curl_off_t) retcode;

	fprintf(stderr, "*** We read %" CURL_FORMAT_CURL_OFF_T
	" bytes from file\n", nread);
	return retcode;
}

/*********************************************************
 * putStudentstoGroups
 *
 * Author: Myles Colina,
 *
 * Description:
 * 	Performs an HTTP put request to CANVAS to add students to the groups.
 *
 *Arguments:
 *	vector<SoupCookie> cookiedata, Team currentTeam, int group_ID
 *
 *Returns:
 *  nothing
 */
void CookieManager::putStudentstoGroups(vector<SoupCookie> cookiedata,
		Team currentTeam, int group_ID) {

	CURL *curl;
	CURLcode res;
	std::string cookieBuffer;
	struct curl_slist *headers = NULL;
	struct stat file_info;

	//the URL for the first HTTP request
	char *url_request;
	string url_string;
	string url_request_string = "https://canvas.asu.edu/api/v1/groups";
	url_request_string += to_string(group_ID);

	//convert the url string to a char*
	int length_url_string = url_request_string.length();
	char url_request1[length_url_string + 1];
	strcpy(url_request1, url_request_string.c_str());
	url_request = url_request1;

	//read in the cookie data from the vector and store it in a string
	std::string cookies;
	std::string temp_cookies;

	cookies = cookiedata[0].name;
	cookies += "=";
	cookies += cookiedata[0].value;
	cookies += "; ";

	for (int i = 1; i < cookiedata.size(); i++) {
		cookies += cookiedata[i].name;
		cookies += "=";
		cookies += cookiedata[i].value;
		cookies += "; ";
	}

	//convert the cookie string to a char*
	int length = cookies.length();
	char cookie_char[length + 1];
	strcpy(cookie_char, cookies.c_str());

	char *cookiesAll = cookie_char;

	std::string Headers;
	std::string readBuffer;

	//start libcurl
	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);

		/* enable uploading */
		curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
		curl_easy_setopt(curl, CURLOPT_PUT, 1L);

		curl_easy_setopt(curl, CURLOPT_URL, url_request);

		curl_easy_setopt(curl, CURLOPT_COOKIE, cookiesAll);

		string group_data;

		//for each team add in the students to the group.
		for (int i = 0; i < 5; i++) {
			if (currentTeam.team[i].StudentID != 99999) {
				group_data += "members[]=";
				group_data += to_string(currentTeam.team[i].StudentID);
				if (i != 4 && currentTeam.team[4].StudentID != 99999) {
					group_data += "&";

				}
			}
		}

		//convert the group data string to a char*
		int length_group = group_data.length();
		char group_data_char[length_group + 1];
		strcpy(group_data_char, group_data.c_str());
		const char *group = group_data_char;

		//cout << group_data_char << endl;

		//curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) strlen(group_data_char));

		FILE *file = fopen(group, "rb");
		CURLcode result;

		/* get the file size of the local file */
		stat(group, &file_info);

		/* pass in suitable argument to callback */
		curl_easy_setopt(curl, CURLOPT_READDATA, file);

		curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,
				(curl_off_t )file_info.st_size);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);

		//cout << readBuffer << endl;
		//cout<<""<<endl;

		// Check for errors
		if (res != CURLE_OK) {
			fprintf(stderr, "second curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
		}

		fclose(file); /* close the local file */
	}

	// always cleanup
	curl_easy_cleanup(curl);
}

