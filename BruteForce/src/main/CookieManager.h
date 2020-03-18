/*
 * CookieManager.h
 *
 * Description:
 *
 *  Created on: 
 *      Author: Team 35
 * 
 */

#ifndef COOKIEMANAGER_H_
#define COOKIEMANAGER_H_

#include <curl/curl.h>
#include <string>
#include <vector>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <libsoup/soup.h>

using namespace std;

class CookieManager {
public:
	CookieManager();
	~CookieManager();
	int newHttpsSession(const char *hostURL);

	void getCourses(vector<SoupCookie> cookiedata);
	void getQuizzes();
	void getStudents(vector<SoupCookie> cookiedata);
	static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
			void *userp);
	static void print_cookies(CURL *curl);
	int newHttpSession(const char *hostURL);
	int MiniBrowser(int argc, char*[]);
};

#endif /* SRC_MAIN_COOKIEMANAGER_H_ */
