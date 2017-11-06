#ifndef ARGPARSER_DOT_H
#define ARGPARSER_DOT_H

#include "common.h"

// Command line parser class
class ArgParser
{ 
    public:

        ArgParser(int argc, char **argv);

	bool IsArgsOk() const { return ArgsOk; }
	void PrintUsage() const; 
	void PrintArgs() const;

	int  GetStartLen() const { return StartLen;}
	int  GetEndLen() const { return EndLen;}

	char GetFirst1() const { return First1;} 
	char GetLast1() const { return Last1;}
	char GetFirst2() const { return First2;}
	char GetLast2() const { return Last2;}

	char GetCnt1() const { return Last1-First1+1;}
	char GetCnt2() const { return Last2-First2+1;}
	string const & GetHash() const { return Hash;}
	static int  ChunkSize() { return 1000;} // Default block size for StrGenerator
	unsigned int GetNumCores() { return NumCores;}
	unsigned int GetNumThreads() { return NumThreads;}

    private: 

	template<class T>
	    T Parse(string const &str, bool *ok )
	    {
		*ok = false;
		T val;
		istringstream stream(str);
		stream >> val;
		*ok = !stream.fail();
		return val;
	    }
	StrVec Split(const string &s, char delim);
	StrVec &Split(const string &s, char delim, StrVec  &elems);


	bool ArgsOk;
	int  StartLen;
	int  EndLen;
	char First1;
	char Last1;
	char First2;
	char Last2;
	string Hash;
	static const int ArgsAmnt=5; // Number of command line arguments
	unsigned int NumCores;
	unsigned int NumThreads; // extra thread amount parameter 
};


#endif

