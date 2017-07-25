#include <fstream>
#include "tests.h"

BruteTester::BruteTester(char first, int cnt1, char second, int cnt2, int maxlen, int startlen)
    :FirstChar(first), FirstCount(cnt1), SecondChar(second), SecondCount(cnt2), MaxPassLen(maxlen), StartLen(startlen)

{
}

void BruteTester::BlocksGenerateToFile(string const &fname)
{
    int len1 = 10;
    StrVec vec;
    StrGenerator p1(FirstChar, FirstCount, SecondChar, SecondCount, MaxPassLen, StartLen); 
    ofstream myfile (fname);
    if (myfile.is_open())
    {
	while( p1.GenerateChunk(&vec, len1) > 0)
	{
	    for(int i = 0; i < vec.size(); ++i)
	    {
		myfile << vec[i] << endl;
	    }
	}
	myfile.close();
    }
}

void BruteTester::GeneratorSimpleTest()
{
    int len1 = 1000;
    StrVec vec1;
    StrGenerator p1(FirstChar, FirstCount, SecondChar, SecondCount, MaxPassLen, StartLen); 
    p1.GenerateChunk(&vec1, len1);
}  

void BruteTester::GeneratorCompareTest()
{  
    cout << "GeneratorTest started" << endl;
    int len1 = 100;
    int len2 = 1;
    StrVec vec1, vec2, vec3;
    StrGenerator p1(FirstChar, FirstCount, SecondChar, SecondCount, MaxPassLen, StartLen); 
    StrGenerator p2(FirstChar, FirstCount, SecondChar, SecondCount, MaxPassLen, StartLen); 
    p1.GenerateChunk(&vec1, len1);
    for(int i = 0; i<len1/len2; ++i)
    {
	p2.GenerateChunk(&vec2, len2);
	vec3.insert(vec3.end(), vec2.begin(), vec2.end());
    }
    assert(vec1.size() == vec3.size());

    for(int i = 0; i < vec1.size(); ++i)
    {
	assert(vec1[i] == vec3[i]);
    }
    p1.PrintVec(vec1);
    
    cout << "GeneratorTest completed" << endl;
}


void BruteTester::GenerateToFile(string const& fname)
{
    StrVec vec;
    StrGenerator p1(FirstChar, FirstCount, SecondChar, SecondCount, MaxPassLen, StartLen); 
    p1.GenerateChunk(&vec, 1000);
    ofstream myfile (fname);
    if (myfile.is_open())
    {
	for(int i = 0; i < vec.size(); ++i)
	{
	    myfile << vec[i] << endl;
	}
	myfile.close();
    }
}

