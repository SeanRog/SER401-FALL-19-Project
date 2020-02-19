#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <bits/stdc++.h>
#include <stdio.h>
#include <curl/curl.h>
#include "CanvasUtility.h"

using namespace std;

// To execute in terminal:
//  1. $ cd ~
//  2. $ sudo apt-get install libcurl4-openssl-dev
//  3. $ cd /SER401-FALL-19-Project35/BruteForce/src/main
//  4. $ g++ CanvasUtility.cpp -o CanvasUtility -lcurl
//  5. $ ./CanvasUtility
/* <DESC>
 * Simple HTTPS GET
 * </DESC>
 */





static void print_cookies(CURL *curl) {
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

static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
		void *userp) {
	((std::string*) userp)->append((char*) contents, size * nmemb);
	return size * nmemb;
}

//Function to convert integers into constant expressions.
constexpr char* toConstChar(char* constInt) {
	return constInt;
}


//function to get all courses
void CanvasUtility::getCourses() {

	CURL *curl;
	CURLcode res;
	std::string readBuffer;
	struct curl_slist *headers = NULL;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL,
				"https://canvas.asu.edu/api/v1/courses?page=1&per_page=100");

	/*	headers = curl_slist_append(headers, "Content-Type: application/json");
		char auth[] = "Authorization: Bearer ";
		char AuthToken[] = "";
		strcat(auth, AuthToken);
		const char* authT = toConstChar(auth);
		headers = curl_slist_append(headers, authT);*/

		//curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L); /* no more POST */
		//curl_easy_setopt(curl, CURLOPT_HEADER, 0);
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
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
		courses << readBuffer;
		courses.close();

		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "second curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
	}

	print_cookies(curl);
	/* always cleanup */
	curl_easy_cleanup(curl);


}

void CanvasUtility::getQuizzes() {

	CURL *curl;
	CURLcode res;
	std::string readBuffer;
	struct curl_slist *headers = NULL;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL,
				"https://canvas.asu.edu/api/v1/courses/47570/quizzes?page=1&per_page=100");

   /*	headers = curl_slist_append(headers, "Content-Type: application/json");
		char auth[] = "Authorization: Bearer " ;
		char AuthToken[] = "";
		strcat(auth, AuthToken);
		headers = curl_slist_append(headers, auth);

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);*/

		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L); /* no more POST */
		//curl_easy_setopt(curl, CURLOPT_HEADER, 0);
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
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
		if (res != CURLE_OK)
			fprintf(stderr, "second curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
	}

	print_cookies(curl);
	/* always cleanup */
	curl_easy_cleanup(curl);


}




int main2(void) {
	CURL *curl;
	CURLcode res;
	std::string readBuffer;
	struct curl_slist *headers = NULL;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();

	if (curl) {

		curl_easy_setopt(curl, CURLOPT_URL,
				"https://canvas.asu.edu/api/v1/courses");

		headers = curl_slist_append(headers, "Content-Type: application/json");
		headers = curl_slist_append(headers,
				"Authorization: Bearer <ENTER TOKEN HERE>");

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		std::cout << readBuffer << std::endl;
	}
	curl_global_cleanup();
	return 0;
}

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
