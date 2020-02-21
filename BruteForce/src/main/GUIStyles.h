/*
 * Stlyes.h
 *
 * Description:  Contains global variables such as colors for use throughout the
 * 				program when creating GUI frames.
 *
 * Created on:   02/05/2020
 *
 * Authors:   M. Cilibra, M. Colina, C. DeLeo, E. Marquise, S. Rogers
 */

#include <FL/Fl.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Widget.H>

#ifndef SRC_MAIN_GUISTLYES_H_
#define SRC_MAIN_GUISTLYES_H_

//OfficialASU  main colors
const Fl_Color ASU_GOLD = fl_rgb_color(255, 198, 39);
const Fl_Color ASU_MAROON = fl_rgb_color(140, 29, 64);
const Fl_Color ASU_WHITE = fl_rgb_color(255, 255, 255);
const Fl_Color ASU_BLACK = fl_rgb_color(0, 0, 0);

//Official ASU secondary colors for limited complimentary use
const Fl_Color ASU_GREEN = fl_rgb_color(120, 190, 32);
const Fl_Color ASU_BLUE = fl_rgb_color(0, 163, 224);
const Fl_Color ASU_ORANGE = fl_rgb_color(255, 127, 50);
const Fl_Color ASU_GREY = fl_rgb_color(92, 102, 112);

class Styles {

};

#endif /* SRC_MAIN_GUISTLYES_H_ */
