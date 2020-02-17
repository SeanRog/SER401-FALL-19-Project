/*
 * CookieManager.h
 *
 * Description:
 *
 *  Created on: 
 *      Author: Team 35
 * 
 */

#ifndef COOKIE_MANAGER_H_
#define COOKIE_MANAGER_H_

#include <string>

using namespace std;

class CookieManager {
    public:
        CookieManager();
        void initSession(string url);
        ~Utility();
};

#endif /* SRC_MAIN_COOKIE_MANAGER_H_ */