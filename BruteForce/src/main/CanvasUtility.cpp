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
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main_canvas(void)
{
  CURL *curl;
  CURLcode res;
  std::string readBuffer;
  struct curl_slist* headers = NULL;
  
  curl_global_init(CURL_GLOBAL_DEFAULT);
  
  curl = curl_easy_init();
  
  if(curl) {  
    
    curl_easy_setopt(curl, CURLOPT_URL, "https://canvas.asu.edu/api/v1/courses");
    
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
