#include "Freezer.hpp"

// This is the source code for the member functions of the Freezer class.

// Constructor
Freezer::Freezer() :
    freezer(new std::ofstream),
    locivalues(new std::ofstream)
{

}

// Destructor
Freezer::~Freezer()
{
    shutdown();
}

void Freezer::shutdown() {
    freezer->close();
    locivalues->close();
}

// Member functions
//-----------------

// Open a file and link it to its container
void Freezer::open(Stream &container, const std::string &filename) {

    container->open(filename, std::ios::binary);
    if (!container->is_open()) {
        std::string msg = "Unable to open output file " + filename;
        throw std::runtime_error(msg);
    }

}

// Open a file where to save individual whole-genome data
void Freezer::open(const std::string &filename) {

    if (filename == "individual_whole_genomes.dat") {
        open(freezer, filename);
    } else if (filename == "individual_locus_genvalues.dat") {
        open(locivalues, filename);
    } else {
        std::string msg = "Invalid output file to open " + filename;
        throw std::runtime_error(msg);
    }

}

// Save the genomes of all individuals in the population
void Freezer::freeze(const MetaPop &pop, const size_t &nloci) {

    for (size_t i = 0u; i < pop.getSize(); ++i) {
        saveIndivGenome(pop.population[i], nloci);
        for (size_t locus = 0u; locus < nloci; ++locus) {
            stf::write(pop.getLocusValue(i, locus), locivalues);
        }
    }

}

// Save the full genome of an individual in 64bit-chunks
void Freezer::saveIndivGenome(const Individual &ind, const size_t &n) {

    // ind: individual
    // n: number of loci

    // Number of 64bit-chunks that can contain the full genome
    const size_t nchunks = n * 2u / 64u + 1u;

    // Save each chunk as a long integer
    for (size_t i = 0u; i < nchunks; ++i) {

        // Integer representation of a 64bit-chunk of genome
        const size_t chunk = ind.getGenomeChunk(i).to_ulong();
        stf::write2(chunk, freezer);

    }

}
