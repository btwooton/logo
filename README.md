# logo
An attempt to implement a Logo interpreter in C

A full rewrite in C++ is planned, to simplify the process of working with more complex data structures such as Hash Table based components.

## As of March 21, 2019
This program has been completely rewritten in C++, and the majority of the language features should be functioning correctly, although haven't been thoroughly tested. User defined, and built in procedures are both working, as well as nested repeats and repcounts are all evaluated properly. I need to figure out how to save previous renderings so that they don't get wiped by Allegro whenever I call al_flip_display().

## Installation/Dependencies
The only dependency that this program really has is the Allegro5 library, the download instructions for which can be found [here](https://liballeg.org/download.html). Follow the instructions on the site for your specific platform (only tested on Linux and MacOS) and ensure that your compiler of choice knows where to find the headers.

## Compiling
Within the /main subdirectory, invoking `make main` from the terminal should output a binary titled `main.out` which can then be invoked via ./main.out within any POSIX compliant shell. An allegro display will start up, with the turtle rendered in the middle of it, and you should be able to input Logo expressions in the terminal and have them evaluated. The `-lflags` in the Makefile include `-lallegro_main` which is needed to properly compile on MacOS systems. If you are not on MacOS, simply delete this flag. Also, the compilation flag `-std=c++17` is being used, although I am not actually leveraging any modern C++ features at this point in time, so you should be able to change this flag to point to an earlier version of the standard if you happen to have an out of date compiler, and things should still compile just fine.

## Future Improvements
I need to add support for more built in language and graphics routines, such as setting colors for drawing. I am also going to look into improving the build system a bit so that there is less overhead involved in getting things installed and running on various platforms. This project was written for fun, and to see if I could port an earlier Python prototype Logo interpreter ito a working C/C++ version that uses a proper parser to parse the Logo expressions. I have worked on programming language interpreter projects in the past, having finished work on large parts of a mostly R7RS compliant Scheme interpreter roughly 1 year ago. Programming language theory and implementation is of great interest to me, and I have had much fun working on this Logo interpreter, and look forward to improving it in the future. Pull requests and issue requests are welcome from all who should choose to use this software.
