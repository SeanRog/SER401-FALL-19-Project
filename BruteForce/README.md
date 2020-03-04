# ASU Capstone Team Assignment System

![Capstone Teams Logo](./Images/CapstoneTeams3.png)

## Development Team

The Capstone Team Assignment System was developed by five ASU-online senior 
software engineering students during the Fall 2019 and Spring 2020 semesters. 
Our sponsor for this project was the software engineering ASU instructor Douglas 
Sandy.

SOFTWARE TEAM 
* Elizabeth Marquise, Myles Colina, Sean Rogers, Cristi Deleo, Matthew Cilibraise
## General Information

This software application creates high-quality assignments of student teams to 
ASU Capstone projects. This automizes a previously manual task reducing the time 
to just minutes. The task of assigning teams to projects is an optimization 
problem of NP-hard complexity. The ‘brute force’ method of finding all possible 
combinations would arrive at the most optimal solution, but it would take more 
years than there are atoms in the universe! The software solution that the team 
has developed reduces this time to minutes, and provides excellent student teams 
to project matches. The invented algorithm is a cross betweeen a binning and 
swapping alogirhutm, that takes into account the student's skills, among other 
factors, and matches them to projects based on the projects required skills. 
The algorithm focuses on the quality of the entire team, ensuring that students 
are assigned to teams that closely match their own skill level, and the skills 
required for the project.

This software application connects to Canvas, the online course website for ASU, 
and prefomrs HTTP requests to collect the course and student roster information.

As of 03/02/2020, the computational time is between 2 and 10 minutes.

### Technologies
This project is written in C++.

### Third-Party Libraries
This project utilizes third party software, namely: 
* JsonCPP, libcurl, fltk-1.3.5, gtk, webkit2, pkg-config.

## Project Setup
To run this project, various installs are necessary.
Clone it locally using git and use make commands to run the software once 
installed (steps detailed below):
```
$ git clone https://github.com/SeanRog/SER401-FALL-19-Project35
$ cd ./SER401-FALL-19-Project35/BruteForce
$ chmod u+x install.sh
$ sudo ./install.sh
```

### Dependency Setup
#### FLTK
FLTK 1.3.5 is the C++ GUI library used by the project.  In order to successfully
execute the application, FLTK will need to be installed and configured as
shown below:
```
$ sudo apt-get install libfltk1.3-dev
```

#### pkg-config
pkg-config is used to execute the commands specified in the Makefile.  In order 
to successfully execute the application using 'make' commands, pkg-config will 
need to be installed as shown below:
```
$ sudo apt-get install pkg-config
```

#### GTK-3.0
GTK-3.0 is the cross-platform widget toolkit used for creating the mini-browser
GUI.  In order to successfully execute the application, GTK-3.0 will need to be
installed, as shown below:
```
$ sudo apt-get install libgtk-3-dev
```

#### WebKit2GTK-4.0
WebKit2GTK-4.0 is the library used for managing the mini-browser session.  In 
order to successfully execute the Canvas authentication feature, WebKit2GTK-4.0 
will need to be installed, as shown below:
```
$ sudo apt-get install webkit2gtk-4.0
```

#### LibCurl4-OpenSSL-Dev
LibCurl4-OpenSSL-Dev is the library used for managing session information.  In 
order to successfully execute the Canvas authentication feature, 
LibCurl4-OpenSSL-Dev will need to be installed, as shown below:
```
$ sudo apt-get install libcurl4-openssl-dev
```

## Executing the Application
From the terminal, use the commands shown below to run the application:
```
$ cd ./SER401-FALL-19-Project35/BruteForce
$ make clean
$ make
$ make run
```