#ifndef EXPLICITGENOMESPECIATION_SIMUL_H
#define EXPLICITGENOMESPECIATION_SIMUL_H

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
