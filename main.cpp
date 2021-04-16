#include "src/Param.h"
#include "src/GenArch.h"
#include "src/Random.h"
#include "src/Simul.h"
#include <cassert>
#include <iostream>
#include <chrono>
#include <vector>
#include <string>


int main(int argc, char * argv[])
{

    // Convert arguments into a vector of strings
    const std::vector<std::string> args(argv, argv + argc);

    // Run the program
    return simulate(args);

}
