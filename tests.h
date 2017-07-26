#ifndef TEST_DOT_H
#define TEST_DOT_H
#include "generator.h"

//Contains some helper testing methods for char sequence data generation ( StrGenerator ) 
class BruteTester
{
    public:
       BruteTester(char first, int cnt1, char second, int cnt2, int maxlen, int startlen=1);
       void GeneratorSimpleTest();
       void GeneratorCompareTest();
       void GenerateToFile(string const &);
       void BlocksGenerateToFile(string const &);
    private:
       char FirstChar;
       int  FirstCount;
       char SecondChar;
       int  SecondCount;
       int  MaxPassLen;
       int  StartLen;
};




#endif

