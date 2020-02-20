
// main.c
#define WEBVIEW_IMPLEMENTATION
//don't forget to define WEBVIEW_WINAPI,WEBVIEW_GTK or WEBVIEW_COCAO

#include "webview.h"
#include <stdio.h>
#include <string.h>

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInt, HINSTANCE hPrevInst, LPSTR lpCmdLine,
                   int nCmdShow) {
#else
int main() {
#endif

 struct webview webview = {
      .title = "ASU Login",
      .url = "https://canvas.asu.edu/login",
      .width = 800,
      .height = 600,
  };

 /* Create webview window using the provided options */
  webview_init(&webview);
  /* Main app loop, can be either blocking or non-blocking */
  while (webview_loop(&webview, 0) == 0){
//printf("%s", webview.url);

if(strcmp(webview.url,"https://canvas.asu.edu")==0){

printf("Terminate worked!");
  webview_terminate(&webview);}}




  	//webview("Web login exapmle","https://canvas.asu.edu/login", 800, 600, 1);



  return 0;
}
