/*
 #include "webapp.hpp"
 #include <iostream>
 #include <cstring>

 WebApp::WebApp() :
 Gtk::Widget (webkit_web_view_new())
 {
 // Create a new websettings and disable java script 
 WebKitSettings *settings = webkit_settings_new();
 WebKitCookieManager *cookiejar;
 webkit_cookie_manager_set_persistent_storage(*this, "cookies.sqlite", 
 WEBKIT_COOKIE_PERSISTENT_STORAGE_SQLITE);

 g_object_set (G_OBJECT(settings), "enable-offline-web-application-cache", 
 TRUE, NULL);

 // Apply the result 
 webkit_web_view_set_settings (*this, settings);
 WebKitCookieManager

 }

 WebApp::~WebApp()
 {
 }

 //operator WebKitWebView * () //  Allow this to stand in for a Web View
 //{
 //    return WEBKIT_WEB_VIEW(gobj());
 //}

 void WebApp::load_uri (const gchar *strUri)
 {
 webkit_web_view_load_uri(*this, strUri);
 }*/
