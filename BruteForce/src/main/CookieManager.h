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

using namespace std;

class CookieManager {
    public:
        CookieManager();
        ~CookieManager();
        int newHttpsSession(const char *hostURL);
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
        static void print_cookies(CURL *curl);
};

#endif /* SRC_MAIN_COOKIEMANAGER_H_ */