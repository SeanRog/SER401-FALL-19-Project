/*
#include <iostream>
#include <string>
#include <curl/curl.h>

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
/*
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

//https://weblogin.asu.edu/cas/login?service=https%3A%2F%2Fweblogin.asu.edu%2Fcgi-bin%2Fcas-login%3Fcallapp%3Dhttps%253A%252F%252Fwebapp4.asu.edu%252Fmyasu%252F%253Finit%253Dfalse
//https://canvas.asu.edu/api/v1/login/oauth2/auth?client_id=480883488&response_type=code&redirect_uri=https://canvas.asu.edu/oauth_complete
int main(void)
{
  CURL *curl;
  CURLcode res;
  std::string readBuffer;
  struct curl_slist* headers = NULL;
  
  curl_global_init(CURL_GLOBAL_DEFAULT);
  
  curl = curl_easy_init();
  
  if(curl) {  
    
    //curl_easy_setopt(curl, CURLOPT_URL, "https://canvas.asu.edu/api/v1/courses");
    curl_easy_setopt(curl, CURLOPT_URL, "https://canvas.asu.edu/api/v1/login/oauth2/auth?client_id=480883488&response_type=code&redirect_uri=https://canvas.asu.edu/oauth_complete");
    //curl_easy_setopt(curl, CURLOPT_URL, "https://canvas.asu.edu/api/v1/login/session_token");
      
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Authorization: Bearer <ENTER TOKEN HERE>");
    
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
*/
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

/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2018, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/ 
/* <DESC>
 * Import and export cookies with COOKIELIST.
 * </DESC>
 */ 
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
 
#include <curl/curl.h>
 
static void
print_cookies(CURL *curl)
{
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
 
int
main2(void)
{
  CURL *curl;
  CURLcode res;
 
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if(curl) {
    char nline[256];
 
    curl_easy_setopt(curl, CURLOPT_URL, "https://canvas.asu.edu/");
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "./cookies.txt"); /* start cookie engine */ 
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "./cookies.txt");
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
      fprintf(stderr, "Curl perform failed: %s\n", curl_easy_strerror(res));
      return 1;
    }
 
    print_cookies(curl);
 
    printf("Erasing curl's knowledge of cookies!\n");
    curl_easy_setopt(curl, CURLOPT_COOKIELIST, "ALL");
 
    print_cookies(curl);
 
    printf("-----------------------------------------------\n"
           "Setting a cookie \"PREF\" via cookie interface:\n");
#ifdef WIN32
#define snprintf _snprintf
#endif
    /* Netscape format cookie */ 
    snprintf(nline, sizeof(nline), "%s\t%s\t%s\t%s\t%lu\t%s\t%s",
             "canvas.asu.edu/", "TRUE", "/", "FALSE",
             (unsigned long)time(NULL) + 31337UL,
             "PREF", "hello example, i like you very much!");
    res = curl_easy_setopt(curl, CURLOPT_COOKIELIST, nline);
    if(res != CURLE_OK) {
      fprintf(stderr, "Curl curl_easy_setopt failed: %s\n",
              curl_easy_strerror(res));
      return 1;
    }
 
    /* HTTP-header style cookie. If you use the Set-Cookie format and don't
    specify a domain then the cookie is sent for any domain and will not be
    modified, likely not what you intended. Starting in 7.43.0 any-domain
    cookies will not be exported either. For more information refer to the
    CURLOPT_COOKIELIST documentation.
    */ 
    snprintf(nline, sizeof(nline),
      "Set-Cookie: OLD_PREF=3d141414bf4209321; "
      "expires=Sun, 17-Jan-2038 19:14:07 GMT; path=/; domain=canvas.asu.edu/");
    res = curl_easy_setopt(curl, CURLOPT_COOKIELIST, nline);
    if(res != CURLE_OK) {
      fprintf(stderr, "Curl curl_easy_setopt failed: %s\n",
              curl_easy_strerror(res));
      return 1;
    }
 
    print_cookies(curl);
 
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
      fprintf(stderr, "Curl perform failed: %s\n", curl_easy_strerror(res));
      return 1;
    }
 
    curl_easy_cleanup(curl);
  }
  else {
    fprintf(stderr, "Curl init failed!\n");
    return 1;
  }
 
  curl_global_cleanup();
  return 0;
}