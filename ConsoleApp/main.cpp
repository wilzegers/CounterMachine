#include "Processing/InputParser.h"
#include "Processing/Parser.h"

#include "Execution/Computation.h"

int main(int argc, char* argv[])
{
    try {
        Processing::InputParser ip(argc, argv);
        ip.Parse();

        Processing::Parser p(L"example2.cm");
        p.Parse();
        Execution::Computation c{ p.GetResultComputation(), ip.GetInits() };
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