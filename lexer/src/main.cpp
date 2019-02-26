#include <iostream>
#include "analyze.hpp"

void usage(const char *function_name)
{
    std::cout << "Usage: " << function_name << " filename\n";
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        usage(argv[0]);

        return 1;
    }
    else if (argc == 2)
    {
        analyze(argv[1]);

        return 0;
    }
    else
    {
        std::cout << "Error: should only specify one input file.\n";

        usage(argv[0]);

        return 2;
    }
}
