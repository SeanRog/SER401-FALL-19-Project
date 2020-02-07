#include <iostream>
#include <string>
#include <curl/curl.h>

// To execute in terminal:
//  1. $ cd ~
//  2. $ sudo apt-get install libcurl4-openssl-dev
//  3. $ cd /SER401-FALL-19-Project35/BruteForce/src/main
//  4. $ g++ CurlGet.cpp -o CurlGet -lcurl
//  5. $ ./CurlGet

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main1(void)
{
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://www.google.com");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    std::cout << readBuffer << std::endl;
  }
  return 0;
}
