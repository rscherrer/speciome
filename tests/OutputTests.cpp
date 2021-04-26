#include "src/Collector.h"
#include "src/Printer.h"
#include "src/Freezer.h"
#include "src/Random.h"
#include "src/Utilities.h"
#include "tests/TestUtilities.h"
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cassert>
#include <fstream>

// Test the output files

// One big test case in which we make sure everything is saved properly

// Testing correct output files
BOOST_AUTO_TEST_CASE(OutputFilesAreCorrectlyWritten)
{

    Param pars;
    pars.rdynamics = 1u;
    pars.hsymmetry = 1.0;
    pars.demesizes = { 100u, 0u };
    pars.allfreq = 0.5;
    pars.ecosel = 1.0;

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    Collector collector = Collector(arch);
    Printer printer = Printer();
    printer.open();

    size_t cumulsize = 0u;
    size_t lastgenfirst = 0u;
    size_t lastgensize = 0u;

    metapop.exitburnin();

    for (int t = 0; t < 10; ++t) {

      metapop.consume(pars);
      collector.analyze(metapop, pars, arch);
      printer.print(static_cast<size_t>(t), collector, metapop);

      if (t != 9) lastgenfirst += metapop.getSize();
      else lastgensize = metapop.getSize();

      cumulsize += metapop.getSize();

    }

    printer.shutdown();

    assert(cumulsize - lastgenfirst == lastgensize);

    // Read output files
    std::vector<double> time = tst::readfile("time.dat");
    std::vector<double> ei = tst::readfile("EI.dat");
    std::vector<double> si = tst::readfile("SI.dat");
    std::vector<double> ri = tst::readfile("RI.dat");

    // Check output files
    BOOST_CHECK_EQUAL(time.size(), 10u);\
    BOOST_CHECK_EQUAL(ei.size(), 10u);
    BOOST_CHECK_EQUAL(si.size(), 10u);
    BOOST_CHECK_EQUAL(ri.size(), 10u);

    // Read individual trait values and ecotypes
    std::vector<double> popx = tst::readfile("individual_trait.dat");
    std::vector<double> ecotypes = tst::readfile("individual_ecotype.dat");

    BOOST_CHECK_EQUAL(popx.size() / 3u, cumulsize);

}

// Test that burnin is saved correctly (negative time values)
BOOST_AUTO_TEST_CASE(SaveBurnin)
{

    Param pars;
    pars.tburnin = 10;
    pars.tend = 10;

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);

    Collector collector = Collector(arch);
    Printer printer = Printer();
    printer.open();

    // This should save also during the burnin
    for (int t = -pars.tburnin; t <= pars.tend; ++t) {

        if (t == 0) metapop.exitburnin();

        // Collect stats
        collector.analyze(metapop, pars, arch);

        // Save them to files
        printer.print(t, collector, metapop);

    }

    printer.shutdown();

    // Read output files
    std::vector<double> time = tst::readfile("time.dat");

    // Check that the first time point saved is negative (burnin)
    BOOST_CHECK(time[0u] < 0.0);

}

// Test saving one individual genome
BOOST_AUTO_TEST_CASE(SaveOneGenome)
{

    Param pars = Param();
    pars.allfreq = 0.9;

    GenArch arch = GenArch(pars);

    Freezer freezer = Freezer();
    freezer.openFreezer("freezer_test.dat");

    // Save the full genome of one individual
    Individual ind(Individual(pars, arch));
    freezer.saveIndivGenome(ind, pars.nloci);
    freezer.shutdown(); // close the freezer to be able to read the file

    // Read the genome back
    std::bitset<180u> genome;
    std::vector<size_t> genomeChunks = tst::readfile2("freezer_test.dat");
    size_t k = 0u;

    for (size_t i = 0u; i < genomeChunks.size(); ++i) {

        // Convert back from integer to bitset
        std::bitset<64u> chunk(genomeChunks[i]);

        // Store every bit in the reconstructed genome
        for (size_t l = 0u; l < 64u && k < 180u; ++l) {
            if (chunk.test(l)) genome.set(k);
            ++k;
        }
    }

    // Check that all positions are identical to the original genome
    Genome original(ind.getFullGenome());

    for (size_t l = 0u; l < 2u * pars.nloci; ++l)
        BOOST_CHECK_EQUAL(original.test(l), genome.test(l));

}

// Test saving all individual genomes
BOOST_AUTO_TEST_CASE(SaveAllGenomes)
{

    Param pars = Param();
    pars.allfreq = 0.9;
    pars.demesizes = { 10u, 0u };

    GenArch arch = GenArch(pars);
    MetaPop pop(MetaPop(pars, arch));

    Freezer freezer = Freezer();
    freezer.openFreezer("freezer_test2.dat");
    freezer.openLoci("locivalues2.dat");

    // Save the genomes
    freezer.freeze(pop, pars.nloci);
    freezer.shutdown(); // close the freezer to be able to read the file

    // Read the genomes back
    std::vector<size_t> genomeChunks = tst::readfile2("freezer_test2.dat");

    // Get the original integer-chunks of genome from the population
    const size_t nchunks = 2u * pars.nloci / 64u + 1u; // per individual
    std::vector<size_t> originalChunks(pop.getSize() * nchunks);

    for (size_t i = 0u, k = 0u; i < pop.getSize(); ++i)
        for (size_t j = 0u; j < nchunks; ++j, ++k)
            originalChunks[k] = pop.getGenomeChunk(i, j).to_ulong();

    // Check that saved and original chunks of genomes are the same
    assert(genomeChunks.size() == originalChunks.size());

    for (size_t k = 0u; k < genomeChunks.size(); ++k)
        BOOST_CHECK_EQUAL(genomeChunks[k], originalChunks[k]);

    // Check that the loci values were saved correctly
    std::vector<double> locivalues = tst::readfile("locivalues2.dat");

    for (size_t i = 0u, k = 0u; i < pop.getSize(); ++i)
        for (size_t l = 0u; l < pars.nloci; ++l, ++k)
            BOOST_CHECK_EQUAL(locivalues[k], pop.getLocusValue(i, l));

}
