#ifndef SPECIOME_PRINTER_HPP
#define SPECIOME_PRINTER_HPP

// This module is used to save summary statistics from the Collector to output
// files

#include "Utilities.hpp"
#include "Collector.hpp"
#include "MetaPop.hpp"
#include <cassert>

class Printer
{

public:

    Printer(const std::string& = "");
    ~Printer();

    void open();
    void print(const int&, const Collector&, const MetaPop&);
    void shutdown();

private:

    std::vector<std::string> whattosave(const std::string&) const;

    std::vector<std::string> filenames;
    vecStreams files;

};


#endif
