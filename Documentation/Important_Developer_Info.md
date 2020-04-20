# IMPORTANT DEVELOPER DOCUMENTATION.

This document contains important information about the code base for developers.
The video going over the installation and use of the application can be found here: https://www.youtube.com/watch?v=oZRtO0qsZb0&feature=youtu.be 

### Development Team

SOFTWARE TEAM 
@author(s) Elizabeth Marquise, Myles Colina, Sean Rogers, Cristi Deleo, Matthew Cilibraise

Copyright (C) 2020, ASU Capstone Project
All Rights Reserved

## TWO DIFFERENT SETS OF GUI CLASSES:

There are 2 GUI style options, steampunk and ASU. Each of these style options actually has their own set of classes, so if a change is made to one, you will probably need to update the other version as well.

* ASU version classes: MainWindow.cpp, MainWindow.h, DataEntryGUI.cpp, DataEntryGUI.h 

* Steampunk Version classes:  SteamPunkGUI1.cpp, SteamPunkGUI1.h, SPDataGUI.cpp, SPDataGUI.h

Both versions share the same classes, ResultsWindow.cpp and ResultsWindow.h.

## NUMBER OF PROJECTS/ STUDENTS/ CLASS SECTIONS:

In the current set up of the application, the number of projects, and students must be entered manually at the start of the application.
* Projects: the number of projects must match the number of projects in the csv file to be read in.
* Students: The number of students must match the number of students in all the class sections to read in from canvas.
* Class Sections:The number of Class sections must be hard-coded as an integer in the code, in man.cpp, function (main_run). This is so that the application can use the threads.

## SKILLS:

To change the number of skills used in the program, there are various changes that must be made to the code.
 there are 3 places in the code where you must change the integer value for the number of skills.

* 1. Student.h  ->  Int Skills[ ] (line 52 in file)
* 2. Project .h  ->  Int Skills[] (line 59 in)
* 3. main.cpp   ->  Const int NUM_SKILLS (line 742)

There are also changes that must be made to the following file in Utility.cpp, function name: csvToProjectsVector, Line 2715.

* 5. Update the string skills1[numSkills], with the exact list, in order, of all the skills listed in the student survey. (line 2718)
* 6. Change the value, int numTechAreas, to reflect the number of technology areas, (not programming languages) in the list of skills. (line 2728)


