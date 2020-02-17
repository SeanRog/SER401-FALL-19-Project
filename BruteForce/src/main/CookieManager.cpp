/*
 * Class:   CookieManager
 * Purpose: Store functions related to Canvas API session.
 * Author:  Team 35 
 *          (Cristi DeLeo, Myles Colina, Sean Rogers, Elizabeth Marquise, 
 *          and Matthew Cilibraise)
 */
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include <openssl/ssl.h>
#include <curl/curl.h>

CURL *curl;

static size_t wf(void *ptr, size_t size, size_t nmemb, void *stream)
{
  const struct curl_tlssessioninfo *info = NULL;
  CURLcode res = curl_easy_getinfo(curl, CURLINFO_TLS_SSL_PTR, &info);
  if(info && !res) {
    if(CURLSSLBACKEND_OPENSSL == info->backend) {
       printf("OpenSSL ver. %s\n", SSL_get_version((SSL*)info->internals));
    }
  }
  return size * nmemb;
}

static void print_cookies(CURL *curl) {
    CURLcode res;
    struct curl_slist *cookies;
    struct curl_slist *nc;
    int i;
 
    printf("Cookies, curl knows:\n");
    
    res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
    
    if(res != CURLE_OK) {
        fprintf(stderr, "Curl curl_easy_getinfo failed: %s\n",
                curl_easy_strerror(res));
        exit(1);
    }
    nc = cookies;
    i = 1;
    while(nc) {
        printf("[%d]: %s\n", i, nc->data);
        nc = nc->next;
        i++;
    }
    if(i == 1) {
        printf("(none)\n");
    }
    curl_slist_free_all(cookies);
}

/*
 * Simple HTTPS GET
 */ 
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, 
        void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
 
int main(void) {
    //CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    std::string readBuffer;
    struct curl_slist* headers = NULL;
    
    curl = curl_easy_init();
    
    if(curl) {
        
        char nline[256];
 
        //curl_easy_setopt(curl, CURLOPT_URL, "https://weblogin.asu.edu/");
        curl_easy_setopt(curl, CURLOPT_URL, "https://canvas.asu.edu/api/v1/courses");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./cookies.txt"); /* start cookie engine */ 
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./cookies.txt");
        curl_easy_setopt(curl, CURLOPT_LOGIN_OPTIONS, "AUTH=*");
        //curl_easy_setopt(curl, CURLOPT_USERPWD, "");

        headers = curl_slist_append(headers, 
                "Content-Type: application/json");
        headers = curl_slist_append(headers, 
                "Authorization: Bearer canvas-lms");
        
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        
        //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, wf);
        
        printf("Erasing curl's knowledge of cookies!\n\n");
        curl_easy_setopt(curl, CURLOPT_COOKIELIST, "ALL");
        
        res = curl_easy_perform(curl);

        if(!res) {
            /* extract all known cookies */
            struct curl_slist *cookies = NULL;
            res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
            if(!res && cookies) {
            /* a linked list of cookies in cookie file format */
            struct curl_slist *each = cookies;
            while(each) {
                printf("if(!res) while loop: !\n\n");
                printf("%s\n", each->data);

                each = each->next;
            }
            /* we must free these cookies when we're done */
            curl_slist_free_all(cookies);
            }
        }
        
        if(res != CURLE_OK) {
            fprintf(stderr, "Curl perform failed: %s\n\n", 
                    curl_easy_strerror(res));
            return 1;
        }
 
        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Curl init failed!\n");
        return 1;
    }
 
    curl_global_cleanup();
    return 0;
}
