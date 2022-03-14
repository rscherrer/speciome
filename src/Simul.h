#ifndef SPECIOME_SIMUL_H
#define SPECIOME_SIMUL_H

// This is the header containing the main simulation function and some
// accompanying functions. The core of the program was encapsulated into a
// simulate() function in order for it to be tested separately.

#include "Param.h"
#include "GenArch.h"
#include "Random.h"
#include "MetaPop.h"
#include "Collector.h"
#include "Printer.h"
#include "Freezer.h"
#include <stddef.h>
#include <iostream>
#include <cstdio>

int simulate(const std::vector<std::string>&);

bool timetosave(const int &t, const int &tsave);
bool timetofreeze(const int &t, const int &tfreeze);

#endif
