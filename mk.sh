#! /bin/sh

echo ================== Parameters ================
echo $TestParam
printenv
echo ==============================================

g++ -Wall -o brute main.cpp generator.cpp tests.cpp argparser.cpp brute.cpp -std=c++0x -pthread 
