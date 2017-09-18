This program was compiled and tested on:
1. Windows 7 x32, Mingw with posix-threads support ( http://win-builds.org/download.html), g++ (GCC) 4.8.2
2. Ubuntu 12.04, g++ 4.6.3

Compiling on Windows:
g++ -o brute.exe main.cpp generator.cpp tests.cpp argparser.cpp brute.cpp -std=c++11 -pthread -Lc:\MinGW\lib
If you have your MinGW libs installed in a place other from default c:\MinGW\lib, you should provide it in a command line.

Compiling on Ubuntu:
g++ -o brute main.cpp generator.cpp tests.cpp argparser.cpp brute.cpp -std=c++0x -pthread  

For testing needs I have provided two scripts: tst.bat(Windows), tst.sh(Ubuntu).
These simple scripts run the program with some predefined data for different number of threads.
The program outputs the algorithm execution time, so it is possible to evaluate
the advantage of the multithreaded version.
