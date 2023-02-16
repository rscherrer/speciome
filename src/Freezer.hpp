#ifndef SPECIOME_FREEZER_HPP
#define SPECIOME_FREEZER_HPP

// This module is a special printer used for saving individual full genomes,
// directly from the MetaPop.
// Note: Using 64bit integers is a way to save space when saving full genomes.
// The stf::write function saves in binary format, meaning that it will
// convert back the integers into their underlying bitsets.
// The resulting binary output file should therefore be interpreted as
// a bit-wise array; each value (allele) is encoded by a single bit.

#include "Utilities.hpp"
#include "MetaPop.hpp"
#include "Printer.hpp"
#include <cassert>

class Freezer
{

public:

    Freezer();
    ~Freezer();

    void open(const std::string&);
    void open(Stream&, const std::string&);
    void freeze(const MetaPop&, const size_t&);
    void saveIndivGenome(const Individual&, const size_t&);
    void shutdown();

private:

    Stream freezer;
    Stream locivalues;

};

#endif // FREEZER_H
