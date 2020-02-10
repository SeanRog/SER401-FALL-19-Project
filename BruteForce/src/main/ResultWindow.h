#ifndef RESULTWIDOW_H_
#define RESULTWINDOW_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Input_.H>
#include <FL/Fl_Text_Buffer.H>


using namespace std;

class ResultWindow {

	static void static_saveClicked(Fl_Widget* w, void * data) {
		((ResultWindow*)data)->saveClicked(w);	}

	void saveClicked(Fl_Widget* w);

    public:
		static int permutations;
		static int swaps;

		Fl_Window *windowResult;
		Fl_Text_Display *textDisplay;
		Fl_Text_Buffer *buffer;
		Fl_Button *buttonSave;
		Fl_Box *permBox;
		Fl_Box *swapBox;

        ResultWindow();
        ~ResultWindow();
        void addText();

};

#endif /*SRC_MAIN_RESULTWINDOW_H_*/
