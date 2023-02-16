#ifndef SPECIOME_SIMUL_HPP
#define SPECIOME_SIMUL_HPP

// This is the header containing the main simulation function and some
// accompanying functions. The core of the program was encapsulated into a
// simulate() function in order for it to be tested separately.

#include "Param.hpp"
#include "GenArch.hpp"
#include "Random.hpp"
#include "MetaPop.hpp"
#include "Collector.hpp"
#include "Printer.hpp"
#include "Freezer.hpp"
#include <stddef.h>
#include <iostream>
#include <cstdio>

int simulate(const std::vector<std::string>&);

bool timetosave(const int &t, const int &tsave);
bool timetofreeze(const int &t, const int &tfreeze);

#endif
