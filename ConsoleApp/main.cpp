#include "Processing/ArgParser.h"
#include "Processing/Parser.h"

#include "Execution/Computation.h"

int main(int argc, char* argv[])
{
    try {
        Processing::ArgParser ap(argc, argv);
        ap.Parse();

        Processing::Parser p(L"example2.cm");
        p.Parse();
        Execution::Computation c{ p.GetResultComputation(), ap.GetInits() };
        c.Run();
        std::cout << c.GetResult();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << "\n";
    }
    getchar();

    return 0;
}