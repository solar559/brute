#ifndef BRUTE_DOT_H
#define BRUTE_DOT_H
#include <condition_variable>
#include <mutex>
#include <memory>
#include <atomic>
#include "generator.h"
#include "argparser.h"
#include "md5.h"

class BruteHelper;
// Performs single thread force brute 
class BrutePerformer
{
    public:
        BrutePerformer(BruteHelper *helper) : Helper(helper) { }

	void Crack();

    private:
	BruteHelper   *Helper;
	MD5            Md5;
};


typedef vector<shared_ptr<BrutePerformer>> PerformerVec;


// Performs parallel force brute 

class BruteHelper
{
    public:

	BruteHelper(StrGenerator *generator, unsigned int num_threads, string const & hash): 
	    Generator(generator),
	    NumThreads(num_threads),
	    Hash(hash),
	    SrcKey(""),
	    Found(false) {}
	void                 CrackParallel();
	string const        &GetHash() const { return Hash;}
	mutex               *GetMutex() { return &Mutex;} 
	condition_variable  *GetCondition() { return &Condition;}
	StrGenerator        *GetGenerator() { return Generator;}
	void                 SetFound(string const& key)     { Found=true; SrcKey = key;}
	atomic_bool  const&  IsFound()  const   { return Found;}
	string const &       GetSrcKey() const { return SrcKey;}
	
	void PrintResult() const;
	    

    private:

	StrGenerator *Generator;
	unsigned int NumThreads;
	string       Hash;
	string       SrcKey; //Here will be stored the searched string for given Hash (if found)

	condition_variable Condition;
	mutex              Mutex;
	atomic_bool        Found;
	PerformerVec       PVec;
};



#endif

