
  /*
   2  * Copyright (C) 2006, 2007 Apple Inc.
   3  * Copyright (C) 2007 Alp Toker <alp@atoker.com>
   4  * Copyright (C) 2011 Lukasz Slachciak
   5  * Copyright (C) 2011 Bob Murphy
   6  *
   7  * Redistribution and use in source and binary forms, with or without
   8  * modification, are permitted provided that the following conditions
   9  * are met:
  10  * 1. Redistributions of source code must retain the above copyright
  11  *    notice, this list of conditions and the following disclaimer.
  12  * 2. Redistributions in binary form must reproduce the above copyright
  13  *    notice, this list of conditions and the following disclaimer in the
  14  *    documentation and/or other materials provided with the distribution.
  15  *
  16  * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
  17  * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  18  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  19  * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
  20  * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
  21  * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
  22  * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
  23  * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
  24  * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  25  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  26  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  27  */
   
  #include <gtk/gtk.h>
  #include <webkit2/webkit2.h>
   
   
   static void destroyWindowCb(GtkWidget* widget, GtkWidget* window);
   static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window);
   
 int main(int argc, char* argv[])
   {
       // Initialize GTK+
       gtk_init(&argc, &argv);
   
       // Create an 800x600 window that will contain the browser instance
      GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
       gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);
   
       // Create a browser instance
       WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());
   
       // Put the browser area into the main window
       gtk_container_add(GTK_CONTAINER(main_window), GTK_WIDGET(webView));
  
       // Set up callbacks so that if either the main window or the browser instance is
       // closed, the program will exit
       g_signal_connect(main_window, "destroy", G_CALLBACK(destroyWindowCb), NULL);
       g_signal_connect(webView, "close", G_CALLBACK(closeWebViewCb), main_window);
   
       // Load a web page into the browser instance
       webkit_web_view_load_uri(webView, "https://canvas.asu.edu/login");
   
       // Make sure that when the browser area becomes visible, it will get mouse
       // and keyboard events
       gtk_widget_grab_focus(GTK_WIDGET(webView));
   
       // Make sure the main window and all its contents are visible
      gtk_widget_show_all(main_window);
   
      // Run the main GTK+ event loop
       gtk_main();
  
       return 0;
   }
   
   
   static void destroyWindowCb(GtkWidget* widget, GtkWidget* window)
   {
       gtk_main_quit();
   }
  
   static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window)
   {
      gtk_widget_destroy(window);
       return TRUE;
   }
