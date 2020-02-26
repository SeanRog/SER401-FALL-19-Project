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

#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

#include <curl/curl.h>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>
#include <string>
#include <stdio.h>

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

		curl_easy_setopt(curl, CURLOPT_URL, hostURL);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_LOGIN_OPTIONS, "AUTH=*");
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

//function to get all courses
void CookieManager::getCourses() {

	CURL *curl;
	CURLcode res;
	std::string readBuffer;

	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL,
				"https://canvas.asu.edu/api/v1/courses?page=1&per_page=100");

		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L); /* no more POST */
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); /* redirects! */

		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./cookies.txt");
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./cookies.txt");

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);

		std::cout << readBuffer << std::endl;

		//write all the courses to a json file.
		ofstream courses;
		courses.open("allCourses.json");
		courses.close();

		/* Check for errors */
		if (res != CURLE_OK) {
			fprintf(stderr, "second curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
		}
	}

	print_cookies(curl);
	/* always cleanup */
	curl_easy_cleanup(curl);
}

void CookieManager::getQuizzes() {
	CURL *curl;
	CURLcode res;
	std::string readBuffer;
	struct curl_slist *headers = NULL;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL,
				"https://canvas.asu.edu/api/v1/courses/47570/quizzes?page=1&per_page=100");

		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L); /* no more POST */
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); /* redirects! */

		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./cookies.txt");
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./cookies.txt");

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);

		std::cout << readBuffer << std::endl;

		//write all the quizzes to a json file.
		ofstream courses;
		courses.open("allQuizzes.json");
		courses << readBuffer;
		courses.close();

		/* Check for errors */
		if (res != CURLE_OK) {
			fprintf(stderr, "second curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
		}
	}

	print_cookies(curl);
	/* always cleanup */
	curl_easy_cleanup(curl);
}

static void destroyWindowCb(GtkWidget *widget, GtkWidget *window);
static gboolean closeWebViewCb(WebKitWebView *webView, GtkWidget *window);

int main2(int argc, char *argv[]) {
	// Initialize GTK+
	gtk_init(&argc, &argv);

	// Create an 800x600 window that will contain the browser instance
	GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);

	// Create a browser instance
	WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

	// Put the browser area into the main window
	gtk_container_add(GTK_CONTAINER(main_window), GTK_WIDGET(webView));

	// Set up callbacks so that if either the main window or the browser instance is
	// closed, the program will exit
	g_signal_connect(main_window, "destroy", G_CALLBACK(destroyWindowCb), NULL);
	g_signal_connect(webView, "close", G_CALLBACK(closeWebViewCb), main_window);

	// Load a web page into the browser instance
	webkit_web_view_load_uri(webView, "https://canvas.asu.edu/login");

	// Make sure that when the browser area becomes visible, it will get mouse
	// and keyboard events
	gtk_widget_grab_focus(GTK_WIDGET(webView));

	// Make sure the main window and all its contents are visible
	gtk_widget_show_all(main_window);

	// Run the main GTK+ event loop
	gtk_main();

	return 0;
}

static void destroyWindowCb(GtkWidget *widget, GtkWidget *window) {
	gtk_main_quit();
}

static gboolean closeWebViewCb(WebKitWebView *webView, GtkWidget *window) {
	gtk_widget_destroy(window);
	return TRUE;
}

int CookieManager::MiniBrowser(int argc, char *argv[]) {

	main2(argc, argv);
	return 1;
}

