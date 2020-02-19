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

#include <string>

using namespace std;

class CookieManager {
    public:
        CookieManager();
        ~CookieManager();
        void newHttpsSession(string url);
        int WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
        
};

#endif /* SRC_MAIN_COOKIEMANAGER_H_ */