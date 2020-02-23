
#ifndef WEBAPP_HPP
#define WEBAPP_HPP

#include <gtkmm/widget.h>
#include <webkit2/webkit2.h>

class WebApp : public Gtk::Widget
{
public:
    WebApp();
    virtual ~WebApp();
    void load_uri(const gchar *strUri);
    operator WebKitWebView * ()
    {
        return WEBKIT_WEB_VIEW(gobj());
    }

protected:
    //Overrides:

};

#endif //WEBAPP_HPP
