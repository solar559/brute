#include <thread>
#include "argparser.h"


void ArgParser::PrintUsage() const
{
    cout << "brute: sample brute-force attack utility." << endl;
    cout << "Author:  Bagdasaryan E.G." << endl;
    cout << "Version: 1.0" << endl << endl;

    cout << "Sample usage:  brute.exe 3 10 65-90:97-122 hash_to_check [num_threads]" << endl;
}

void ArgParser::PrintArgs() const
{
    cout << "=================== Arguments: ======================" << endl;
    cout << setw(15) << left <<  "StartLen" << " = " << StartLen << endl;
    cout << setw(15) << left << "EndLen" << " = " << EndLen << endl;
    cout << setw(15) << left << "FirstChar1" << " = " << First1 << endl;
    cout << setw(15) << left << "LastChar1" << " = " << Last1 << endl;
    cout << setw(15) << left << "FirstChar2" << " = " << First2 << endl;
    cout << setw(15) << left << "LastChar2" << " = " << Last2 << endl;
    cout << setw(15) << left << "Hash" <<  " = " << Hash << endl; 
    cout << setw(15) << left << "NumCores" <<  " = " << NumCores << endl;
    cout << setw(15) << left << "NumThreads" <<  " = " << NumThreads << endl;
}

ArgParser::ArgParser(int argc, char **argv) : ArgsOk(false)
{
    if( (argc > ArgsAmnt + 1)  || ( argc < ArgsAmnt)  )
	return;
    bool ok(false);
    StartLen = Parse<int>(argv[1], &ok);
    if(!ok)
	return;
    EndLen = Parse<int>(argv[2], &ok);
    if(!ok)
	return;
    if(StartLen>EndLen)
    {
	cerr << "Parse arguments error: StartLen>EndLen" << endl << endl;
	return;
    }

    StrVec vec = Split(argv[3], ':');
    if(vec.size() != 2)
	return;
    StrVec vec1 = Split(vec[0], '-');
    StrVec vec2 = Split(vec[1], '-');
    if(vec1.size() != 2)
	return;
    if(vec2.size() != 2)
	return;

    First1 = static_cast<char>(Parse<int>(vec1[0], &ok));
    if(!ok)
	return;
    Last1 = static_cast<char>(Parse<int>(vec1[1], &ok));
    if(!ok)
	return;

    if(First1>Last1)
    {
	cerr << "Parse arguments error: First1>Last1" << endl << endl;
	return;
    }


    First2 = static_cast<char>(Parse<int>(vec2[0], &ok));
    if(!ok)
	return;
    Last2 = static_cast<char>(Parse<int>(vec2[1], &ok));
    if(!ok)
	return;
    
    if(First2>Last2)
    {
	cerr << "Parse arguments error: First1>Last1" << endl << endl;
	return;
    }

    Hash = argv[4];
    NumCores = std::thread::hardware_concurrency();
    NumThreads = NumCores;
    // extra thread number parameter
    if(argc == ArgsAmnt+1)
    {
	NumThreads = Parse<int>(argv[5], &ok);
	if(!ok)
	    NumThreads=NumCores;
    }

    ArgsOk = true;
}


StrVec &ArgParser::Split(const string &s, char delim, StrVec  &elems)
{
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) 
    {
	elems.push_back(item);
    }
    return elems;
}

StrVec ArgParser::Split(const string &s, char delim)
{
    StrVec elems;
    Split(s, delim, elems);
    return elems;
}


