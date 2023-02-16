#include "src/Param.hpp"
#include "src/GenArch.hpp"
#include "src/Random.hpp"
#include "src/Simul.hpp"
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
