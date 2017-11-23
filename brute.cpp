#include "brute.h"

void BruteHelper::CrackParallel()
{
    for(int i = 0; i < NumThreads; ++i)
    {
        shared_ptr<BrutePerformer> p(new BrutePerformer(this));
	PVec.push_back(p);
	std::thread thread(&BrutePerformer::Crack, p.get());
	thread.detach(); 
    }

    int left_threads = NumThreads;
    while(left_threads)
    {
	unique_lock<mutex> lock(Mutex);
	Condition.wait(lock); 
	if(Found) {
	    return;
	}
	left_threads--;
    }
}

void BruteHelper::PrintResult() const
{
    string s = "OK";
    if(!Found)
	s = "FAIL";

    cout     << "Force brute completed:   " << s << endl;
    if(Found)
	cout << "Found key:               " << SrcKey << endl;
}


void BrutePerformer::Crack()
{
    StrVec vec;
    int generated = 0;
    while( (generated=Helper->GetGenerator()->GenerateChunk(&vec))>0)
    {
	for(int i = 0; i < vec.size(); ++i)
	{
	    if(Helper->IsFound())
		return;
	    string hash = Md5.digestString(&vec[i][0]);

	    if(hash == Helper->GetHash())
	    {
		unique_lock<mutex> lock(*Helper->GetMutex());
		Helper->SetFound(vec[i]);
		Helper->GetCondition()->notify_one();
		return;
	    }
	}
    }
    // no more data to process, returning
    unique_lock<mutex> lock(*Helper->GetMutex());
    Helper->GetCondition()->notify_one();
}

