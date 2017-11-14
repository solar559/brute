#ifndef GENERATOR_DOT_H
#define GENERATOR_DOT_H

#include <thread>
#include <mutex>
#include "common.h"
#include "argparser.h"


class DataCompletedException
{
    public:
        DataCompletedException(int depth = 0)
        : Depth(depth) {}
	int Depth;
};


// Char sequence generator
class StrGenerator
{
    public:
	StrGenerator(char first, int cnt1, char second, int cnt2, int len, int start_len=1);

	// thread safe method for generation blocks of char sequences
	// successive calls of this method bring next portion of data to crack
	// returns 0 when all data in a given char set was generated
	int GenerateChunk(StrVec *result_vec, int chunk_len);
	int GenerateChunk(StrVec *result_vec) { return GenerateChunk(result_vec, ArgParser::ChunkSize()); }

	// testing methods
        void PrintVec(StrVec const &vec);
	void PrintIVec(IntVec const &vec);

    private:
	void InitCurStateVec();
	void Generate(StrVec *str_vec, int recursion_depth);
	void PrintSymbols() const;

	CharVec SymbolVec;  //input character set
	string CurGenStr;
	int PassLen;        //Minimum length of char sequence to crack
	int MaxPassLen;     //Maximum length of char sequence to crack
	std::mutex Mutex;
	int AmntToGen;
	IntVec CurStateVec; // Saves internal state between successive calls of GenerateChunk()
};


#endif

