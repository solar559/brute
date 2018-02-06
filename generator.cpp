#include "generator.h"


StrGenerator::StrGenerator(char first, int cnt1, char second, int cnt2, int maxlen, int start_len)
:MaxPassLen(maxlen), PassLen(start_len), AmntToGen(300)
{
    InitCurStateVec();
    for(int i = 0; i < cnt1; ++i)
        SymbolVec.push_back(first+i);
    for(int i = 0; i < cnt2; ++i)
        SymbolVec.push_back(second+i);
}

void StrGenerator::PrintSymbols() const
{
    for(int i = 0; i < SymbolVec.size(); ++i)
    {
        cout << SymbolVec[i];
    }
    cout << endl;
}

void StrGenerator::InitCurStateVec()
{
    for(int i=0; i<PassLen; ++i)
	CurStateVec.push_back(0);

}

int StrGenerator::GenerateChunk(StrVec *result_vec, int chunk_len)
{
    lock_guard<std::mutex> lock(Mutex);

    StrVec vec0;
    int left_chunk_len = chunk_len;

    result_vec->clear();
    AmntToGen = chunk_len;
    while((left_chunk_len > 0) && (PassLen<=MaxPassLen))
    {
	vec0.clear();
	try
	{
	    Generate(&vec0, 0);
	    left_chunk_len -= vec0.size();
	    if(left_chunk_len > 0)
	    {
		AmntToGen = left_chunk_len;
		PassLen++;
	    }
	    InitCurStateVec();
	}
	catch(DataCompletedException ex)
	{
	    left_chunk_len -= vec0.size();
	}
	for(int i = 0; i < vec0.size(); ++i)
	{
	    result_vec->push_back(vec0[i]);
	}
	CurGenStr = "";
    }
    return result_vec->size();
}


void StrGenerator::Generate(StrVec *str_vec, int recursion_depth)
{
    unsigned int i = 0;
    for (i = CurStateVec[recursion_depth]; i < SymbolVec.size(); ++i)
    {
	CurGenStr.push_back(SymbolVec[i]);
	if(recursion_depth == PassLen-1)
	{
	    str_vec->push_back(CurGenStr);
	    assert(!CurGenStr.empty());
	    CurGenStr.erase(CurGenStr.size()-1);
	    assert(recursion_depth < PassLen);
	    CurStateVec[recursion_depth]++;
	    if(str_vec->size() == AmntToGen)
	    {
		// chunk of data is ready, now we should unwind the stack
		throw DataCompletedException(recursion_depth);
	    }
	    continue;
	}

	Generate(str_vec, recursion_depth+1);
	CurStateVec[recursion_depth]++;

    }
    CurStateVec[recursion_depth] = 0;
    if(!CurGenStr.empty())
	CurGenStr.erase(CurGenStr.size()-1);
}

void StrGenerator::PrintVec(StrVec const &vec)
{
    for(int i = 0; i < vec.size(); ++i)
    {
	cout << vec[i] << endl;
    }
}


void StrGenerator::PrintIVec(IntVec const &vec)
{
    for(int i = 0; i < vec.size(); ++i)
    {
	cout << vec[i] << " " << endl;
    }
}

