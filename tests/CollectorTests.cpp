#include "src/Collector.h"
#include "src/Random.h"
#include "src/Utilities.h"
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cassert>

// Test the analysis module

// Test variance partitioning
BOOST_AUTO_TEST_CASE(DivergenceIsFullIfWithinGroupVarianceIsZero)
{

    BOOST_CHECK_EQUAL(Xst({ 0.0, 0.0, 4.0 }, { 10u, 10u, 20u }), 1.0);
    BOOST_CHECK_EQUAL(Xst({ 0.0, 0.0, 2.0 }, { 10u, 10u, 20u }), 1.0);
    BOOST_CHECK_EQUAL(Xst({ 0.0, 0.0, 1.0 }, { 10u, 10u, 20u }), 1.0);

}

// Test edge-case of zero variance
BOOST_AUTO_TEST_CASE(DivergenceIsZeroIfTotalVarianceIsZero)
{

    BOOST_CHECK_EQUAL(Xst({ 0.0, 0.0, 0.0 }, { 10u, 10u, 20u }), 0.0);

}

// Test that partitioning is always positive
BOOST_AUTO_TEST_CASE(DivergenceIsAlwaysPositive)
{

    BOOST_CHECK(Xst({ 0.2, 0.1, 0.1 }, { 10u, 10u, 20u }) >= 0.0);

}

// Test that monomorphic ecotypes indeed have zero variance
BOOST_AUTO_TEST_CASE(EcologicalIsolationIsOneIfEcotypesAreMonomorphic)
{

    Param pars;
    pars.hsymmetry = 0.0; // habitats are asymmetric in resources
    pars.demesizes = { 100u, 100u };

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.resetTraits(0u, 0u, -1.0, pars); // only trait -1 in habitat 0
    metapop.resetTraits(0u, 1u, 1.0, pars); // only trait 1 in habitat 1
    metapop.exitburnin();
    metapop.consume(pars);

    Collector collector = Collector(arch);
    collector.analyze(metapop, pars, arch);

    BOOST_CHECK_EQUAL(collector.getEI(), 1.0);

}

// Test case: a population with spatial isolation = 1
BOOST_AUTO_TEST_CASE(SpatialIsolationIsOneIfEcotypesAreSeparated)
{

    Param pars;
    pars.hsymmetry = 0.0; // habitats are asymmetric in resources
    pars.demesizes = { 100u, 100u };

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.exitburnin();
    metapop.resetTraits(0u, 0u, -1.0, pars); // only trait -1 in habitat 0
    metapop.resetTraits(0u, 1u, 1.0, pars); // only trait 1 in habitat 1
    metapop.consume(pars);

    Collector collector = Collector(arch);
    collector.analyze(metapop, pars, arch);

    BOOST_CHECK_EQUAL(collector.getSI(), 1.0);

}

// Test case: a population with mating isolation = 1
BOOST_AUTO_TEST_CASE(MatingIsolationIsOneIfMatingIsAssortative)
{

    Param pars;
    pars.hsymmetry = 0.0; // habitats are asymmetric in resources
    pars.demesizes = { 100u, 100u };

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.exitburnin();
    metapop.resetTraits(0u, 0u, -1.0, pars); // only trait -1 in habitat 0
    metapop.resetTraits(0u, 1u, 1.0, pars); // only trait 1 in habitat 1
    metapop.resetTraits(1u, 1.0, pars); // assortative mating
    metapop.consume(pars);

    Collector collector = Collector(arch);
    collector.analyze(metapop, pars, arch);

    BOOST_CHECK_EQUAL(utl::round(collector.getRI(), 4u), 1.0);

}

// Test when one habitat is empty
BOOST_AUTO_TEST_CASE(SpatialIsolationIsZeroIfOneHabitatIsEmpty)
{

    Param pars;
    pars.demesizes = { 100u, 0u };
    pars.hsymmetry = 1.0;

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.exitburnin();
    metapop.consume(pars);

    Collector collector = Collector(arch);
    collector.analyze(metapop, pars, arch);

    BOOST_CHECK_EQUAL(collector.getSI(), 0.0);

}

// Test when there is only one sex
BOOST_AUTO_TEST_CASE(MatingIsolationIsZeroIfOnlyOneSex)
{

    Param pars;

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.resetGenders(true); // only females
    metapop.exitburnin();
    metapop.consume(pars);

    Collector collector = Collector(arch);
    collector.analyze(metapop, pars, arch);

    BOOST_CHECK_EQUAL(collector.getRI(), 0.0);

}

// Test if there is only one ecotype
BOOST_AUTO_TEST_CASE(AllIsolationMetricsAreZeroIfOnlyOneEcotype)
{

    Param pars;
    pars.demesizes = { 100u, 0u };
    pars.hsymmetry = 0.0;

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.resetTraits(0u, -1.0, pars); // should produce only ecotype 0
    metapop.exitburnin();
    metapop.consume(pars);

    Collector collector = Collector(arch);
    collector.analyze(metapop, pars, arch);

    BOOST_CHECK_EQUAL(collector.getEI(), 0.0);
    BOOST_CHECK_EQUAL(collector.getSI(), 0.0);
    BOOST_CHECK_EQUAL(collector.getRI(), 0.0);

}

BOOST_AUTO_TEST_CASE(NoResidualsIfFullAdditive)
{

    Param pars;
    pars.allfreq = 0.8;
    pars.ecosel = 0.0;
    pars.scaleA = {1.0, 1.0, 1.0};
    pars.scaleD = {0.0, 0.0, 0.0};
    pars.scaleI = {0.0, 0.0, 0.0};
    pars.scaleE = {0.0, 0.0, 0.0};

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.consume(pars);

    Collector collector = Collector(arch);
    collector.analyze(metapop, pars, arch);

    // For each genotype
    for (size_t zyg = 0u; zyg < 3u; ++zyg) {

        double varg = collector.calcLocusGenotypeVarG(5u, zyg, metapop,
         pars.nloci);
        assert(varg >= -0.00000001);
        varg = varg < 0.00000001 ? 0.0 : varg;

        BOOST_CHECK_EQUAL(varg, 0.0);

    }

    // For each trait
    for (size_t trait = 0u; trait < 3u; ++trait) {

        // Non-additive variance should be zero
        BOOST_CHECK_EQUAL(collector.getVarN(trait), 0.0);
        BOOST_CHECK_EQUAL(collector.getVarI(trait), 0.0);

    }

}

