@echo off

g++ -o brute.exe main.cpp generator.cpp tests.cpp argparser.cpp brute.cpp -std=c++11 -pthread -Lc:\MinGW\lib

