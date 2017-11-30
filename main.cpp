#include <chrono>
#include "generator.h"
#include "tests.h"
#include "brute.h"


static void Func()
{}

int main(int argc, char**argv)
{
    ArgParser parser(argc, argv);
    if(!parser.IsArgsOk())
    {
        parser.PrintUsage();
        return 1;
    }
    parser.PrintArgs();

    StrGenerator generator(parser.GetFirst1(),
            parser.GetCnt1(),
            parser.GetFirst2(),
            parser.GetCnt2(),
            parser.GetEndLen(),
            parser.GetStartLen());

    BruteHelper helper(&generator, parser.GetNumThreads(),  parser.GetHash());

    std::chrono::time_point<std::chrono::system_clock> start, end;

    cout << endl;
    cout << "Executing brute-force  ..." << endl;
    cout << endl;
    start = std::chrono::system_clock::now();
    helper.CrackParallel();
    end = std::chrono::system_clock::now();
    helper.PrintResult();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << endl;
    return 0;
}

