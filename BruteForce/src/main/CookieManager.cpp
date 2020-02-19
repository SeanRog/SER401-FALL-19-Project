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
 */
#include "CookieManager.h"

#include <curl/curl.h>
#include <iostream>
#include <utility>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>
#include <string>
#include <stdio.h>

using namespace std;

CookieManager::CookieManager() {
	// TODO Auto-generated constructor stub
}

CookieManager::~CookieManager() {
	// TODO Auto-generated destructor stub
}
//std::system(R"("C:\Program Files\Mozilla Firefox\firefox.exe" google.com)");
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
void CookieManager::newHttpsSession(string url) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    struct curl_slist* headers = NULL;
  
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
  
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
    
        headers = curl_slist_append(headers, "Content-Type: application/json");
        //headers = curl_slist_append(headers, 
        //    "Authorization: Bearer <ENTER TOKEN HERE>");
    
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        res = curl_easy_perform(curl);
        
        curl_easy_cleanup(curl);

        std::cout << readBuffer << std::endl;
    }
    curl_global_cleanup();
    return ;
}

/*
 * Simple HTTPS GET
 */ 
int CookieManager::WriteCallback(void *contents, size_t size, 
        size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

