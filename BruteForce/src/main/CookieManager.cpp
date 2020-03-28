/*
 * CookieManager.cpp
 *
 * Description:
 *
 *  Created on: 
 *      Authors: Fall 2019 Team 35 (Matthew, Cristi, Myles, Elizabeth, Sean)
 *
 * List of function:
 *  (see header file Utility.h)
 * 
 * To test, add the following code to int main() in main.cpp before other calls:
 *        
 *  CookieManager cookieMgr;
 *  const char* hostURL = "https://weblogin.asu.edu/";
 *  cookieMgr.newHttpsSession(hostURL);
 * 
 *
 */
#include "CookieManager.h"
#include "Utility.h"
#include "Student.h"

#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <libsoup/soup.h>
#include <curl/curl.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>
#include <string>
#include <stdio.h>

#include <stdlib.h>
#include <sstream>
#include <map>
#include <boost/algorithm/string.hpp>

using namespace std;

CookieManager::CookieManager() {

}

CookieManager::~CookieManager() {
	// TODO Auto-generated destructor stub
}

//Function to convert char[] into constant expressions.
constexpr char* toConstChar(char *constInt) {
	return constInt;
}

/***********************************************
 * newHttpSession
 *
 * Description:
 * Initializes a new HTTP session
 *
 * Arguments:
 * 
 *
 * returns -
 * 
 */
int CookieManager::newHttpSession(const char *hostURL) {

	CURL *curl;

	CURLcode res;
	std::string readBuffer;
	struct curl_slist *headers = NULL;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();

	if (curl) {

		curl_easy_setopt(curl, CURLOPT_URL, hostURL);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_NETRC, CURL_NETRC_REQUIRED);

		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./cookies.txt"); /* start cookie engine */
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./cookies.txt");

		headers = curl_slist_append(headers, "Content-Type: application/json");
		//headers = curl_slist_append(headers, 
		//    "Authorization: Bearer <ENTER TOKEN HERE>");

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		printf("Erasing curl's knowledge of cookies!\n\n");
		curl_easy_setopt(curl, CURLOPT_COOKIELIST, "ALL");

		res = curl_easy_perform(curl);

		if (!res) {
			/* extract all known cookies */
			struct curl_slist *cookies = NULL;
			res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);

			if (!res && cookies) {
				/* a linked list of cookies in cookie file format */
				struct curl_slist *each = cookies;

				while (each) {
					printf("if(!res) while loop: !\n\n");
					printf("%s\n", each->data);

					each = each->next;
				}
				/* we must free these cookies when we're done */
				curl_slist_free_all(cookies);
			}
		}

		if (res != CURLE_OK) {
			fprintf(stderr, "Curl perform failed: %s\n\n",
					curl_easy_strerror(res));
			return 1;
		}

		curl_easy_cleanup(curl);

		std::cout << readBuffer << std::endl;
	}
	curl_global_cleanup();
	return 0;
}

/***********************************************
 * newHttpsSession
 *
 * Description:
 * Initializes the a new session
 *
 * Arguments:
 * 
 *
 * returns -
 * 
 */
int CookieManager::newHttpsSession(const char *hostURL) {
	CURL *curl;
	CURLcode res;
	std::string readBuffer;
	struct curl_slist *headers = NULL;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	/*  SKIP_PEER_VERIFICATION
	 * If you want to connect to a site who isn't using a certificate that is
	 * signed by one of the certs in the CA bundle you have, you can skip the
	 * verification of the server's certificate. This makes the connection
	 * A LOT LESS SECURE.
	 *
	 * If you have a CA cert for the server stored someplace else than in the
	 * default bundle, then the CURLOPT_CAPATH option might come handy for
	 * you.
	 *
	 * curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	 
	 SKIP_HOSTNAME_VERIFICATION
	 *
	 * If the site you're connecting to uses a different host name that what
	 * they have mentioned in their server certificate's commonName (or
	 * subjectAltName) fields, libcurl will refuse to connect. You can skip
	 * this check, but this will make the connection less secure.
	 * 
	 * curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	 */

	curl = curl_easy_init();

	if (curl) {

		//curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/4.0");
		curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

		curl_easy_setopt(curl, CURLOPT_URL, hostURL);

		//curl_easy_setopt(curl, CURLOPT_LOGIN_OPTIONS, "AUTH=*");
		//curl_easy_setopt(curl, CURLOPT_COOKIESESSION, 1L);
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./cookies.txt"); /* start cookie engine */
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./cookies.txt");

		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers,
				"Authorization: Bearer <ENTER TOKEN HERE>");

		//curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		printf("Erasing curl's knowledge of cookies!\n\n");
		//curl_easy_setopt(curl, CURLOPT_COOKIELIST, "RELAOD");

		res = curl_easy_perform(curl);

		if (!res) {
			/* extract all known cookies */
			struct curl_slist *cookies = NULL;
			res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);

			if (!res && cookies) {
				/* a linked list of cookies in cookie file format */
				struct curl_slist *each = cookies;

				while (each) {
					printf("if(!res) while loop: !\n\n");
					printf("%s\n", each->data);

					each = each->next;
				}
				/* we must free these cookies when we're done */
				curl_slist_free_all(cookies);
			}
		}

		if (res != CURLE_OK) {
			fprintf(stderr, "Curl perform failed: %s\n\n",
					curl_easy_strerror(res));
			return 1;
		}

		curl_easy_cleanup(curl);

		std::cout << readBuffer << std::endl;
	}
	curl_global_cleanup();
	return 0;
}

/*
 * Simple HTTPS GET
 */
size_t CookieManager::WriteCallback(void *contents, size_t size, size_t nmemb,
		void *userp) {
	((std::string*) userp)->append((char*) contents, size * nmemb);
	return size * nmemb;
}

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

		temp_cookies += cookiedata[i].name;
		temp_cookies += "=";
		temp_cookies += cookiedata[i].value;
		temp_cookies += "; \n";
	}

	//print temp_cookie string to console for debugging
	cout<<"\n\nTHE CANVAS ASU AUTHENTICATION COOKIES:"<<endl;
	cout<<temp_cookies<<endl;


	//convert the cookie string to a char*
	int length = cookies.length();
	char cookie_char[length + 1];
	strcpy(cookie_char, cookies.c_str());

	char *cookiesAll = cookie_char;
	cout << cookiesAll << endl;

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

				cout << url_char << endl;
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
	cout << cookiesAll << endl;

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

				cout << url_char << endl;
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

	cout << "Quiz ID for the quiz: " << quiz_ID << endl;

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
	cout << cookiesAll << endl;

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

				cout << url_char << endl;
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
	cout << cookiesAll << endl;

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

				cout << url_char << endl;
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

	cout << "Assignment ID for the quiz: " << assignment_ID << endl;

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

	// Create a browser instance
	WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());


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
	cout << cookiesAll << endl;

	//configure the URL
	//the URL for the first HTTP request
	char *url_request;
	string url_string;
	string url_request_string;

	url_request_string = "https://canvas.asu.edu/api/v1/courses/";
	url_request_string += to_string(course_ID);
	url_request_string += "/assignments/";
	url_request_string += to_string(assignment_ID);
	url_request_string += "/submissions?include[]=submission_history&page=1&per_page=100";

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

				cout << url_char << endl;
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

