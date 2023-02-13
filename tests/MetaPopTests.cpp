#define BOOST_TEST_MODULE MetapopTests

#include "../src/MetaPop.hpp"
#include "../src/Collector.hpp"
#include "../src/Utilities.hpp"
#include <boost/test/unit_test.hpp>

// Tests of the good behavior of a metapopulation object

// Simulation should reach tmax in the absence of mortality
BOOST_AUTO_TEST_CASE(ConstantPopSizeWhenNoBirthNoDeath)
{

    Param pars;
    pars.tend = 10;
    pars.tburnin = 0;
    pars.demesizes = { 10u, 10u };
    pars.dispersal = 0.0;
    pars.survival = 1.0; // no death
    pars.birth = 0.0; // no birth
    pars.sexsel = 0.0;

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);

    for (int t = 0; t < pars.tend; ++t) {

        metapop.reproduce(pars, arch);
        metapop.survive(pars);

    }

    BOOST_CHECK_EQUAL(metapop.getSize(), 20u);

}

// Mass extinction
BOOST_AUTO_TEST_CASE(InstantExtinctionIfSurvivalIsZero)
{

    Param pars;
    pars.tend = 100;
    pars.demesizes = { 10u, 10u };
    pars.survival = 0.0; // 0% chance of survival

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.exitburnin();
    metapop.survive(pars);

    BOOST_CHECK(metapop.isextinct());

}

// Simulation should end prematurely with high mortality
BOOST_AUTO_TEST_CASE(ProgressiveExtinctionWhenLowSurvival)
{

    Param pars;
    pars.tend = 1000;
    pars.demesizes = { 10u, 10u };
    pars.survival = 0.1; // 10% chance of survival

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.exitburnin();

    bool extinction = false;

    for (int t = 0; t < pars.tend; ++t) {

        metapop.survive(pars);

        if (metapop.isextinct()) {

            extinction = true;
            break;

        }
    }

    BOOST_CHECK(extinction);

}

// Test that habitats are initialized with only one resource if
// habitat symmetry is zero
BOOST_AUTO_TEST_CASE(HabitatsHaveOneResourceIfCompleteAsymmetry)
{

    Param pars;
    pars.rdynamics = 1u;
    pars.inflow = 400.0;
    pars.outflow = 100.0;
    pars.hsymmetry = 0.0; // full habitat asymmetry
    pars.demesizes = {10u, 10u};
    pars.ecosel = 0.0;

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.exitburnin();
    metapop.consume(pars);

    BOOST_CHECK_EQUAL(metapop.getResource(0u, 0u), 400.0/110.0);
    BOOST_CHECK_EQUAL(metapop.getResource(1u, 1u), 400.0/110.0);
    BOOST_CHECK_EQUAL(metapop.getResource(0u, 1u), 0.0);
    BOOST_CHECK_EQUAL(metapop.getResource(1u, 0u), 0.0);

}

// Testing no dispersal
BOOST_AUTO_TEST_CASE(NoDispersalLeavesHabitatsWithSameNumberOfIndividuals)
{

    Param pars;
    pars.demesizes = { 15u, 10u };
    pars.dispersal = 0.0;

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.exitburnin();
    metapop.disperse(pars);

    BOOST_CHECK_EQUAL(metapop.getDemeSize(0u), 15u);
    BOOST_CHECK_EQUAL(metapop.getDemeSize(1u), 10u);

}

// Complete exodus
BOOST_AUTO_TEST_CASE(AllIndividualsMigrateIfDispersalIsMax)
{

    Param pars;
    pars.demesizes = { 10u, 0u };
    pars.dispersal = 1.0; // 100% chance dispersal

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.exitburnin();
    metapop.disperse(pars);

    BOOST_CHECK_EQUAL(metapop.getDemeSize(0u), 0u);
    BOOST_CHECK_EQUAL(metapop.getDemeSize(1u), 10u);

}

// Check that a population has grown after reproduction
BOOST_AUTO_TEST_CASE(ReproductionHasProducedNewIndividuals)
{

    Param pars;
    pars.capacity = 100.0;
    pars.birth = 1000.0; // high birth rate
    pars.demesizes = { 10u, 0u };

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.exitburnin();
    metapop.consume(pars);
    metapop.reproduce(pars, arch);

    BOOST_CHECK(metapop.getSize() >= 10u);
    BOOST_CHECK(metapop.getDemeSize(0u) >= 10u);
    BOOST_CHECK_EQUAL(metapop.getDemeSize(1u), 0u);

}

// Newborns should not die (this one is annoying)
BOOST_AUTO_TEST_CASE(PopulationWipeOutLeavesOnlyNewborns)
{

    Param pars;
    pars.birth = 100.0; // relatively high birth rate
    pars.demesizes = { 10u, 0u };
    pars.survival = 0.0; // all adults should die

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.consume(pars);
    metapop.reproduce(pars, arch);
    metapop.survive(pars);

    BOOST_CHECK(metapop.getSize() > 0u);
    BOOST_CHECK(metapop.getDemeSize(0u) > 0u);
    BOOST_CHECK_EQUAL(metapop.getDemeSize(1u), 0u);

}

// After feeding, the resources should be depleted
BOOST_AUTO_TEST_CASE(ResourceIsDepletedAfterConsumption)
{

    Param pars;
    pars.hsymmetry = 1.0;
    pars.capacity = 10.0;
    pars.demesizes = { 5u, 5u };

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.exitburnin();
    metapop.consume(pars);

    BOOST_CHECK(metapop.getResource(0u, 0u) < 10.0);
    BOOST_CHECK(metapop.getResource(0u, 1u) < 10.0);
    BOOST_CHECK(metapop.getResource(1u, 0u) < 10.0);
    BOOST_CHECK(metapop.getResource(1u, 1u) < 10.0);

}


// Test logistic resource dynamics
BOOST_AUTO_TEST_CASE(KnownLogisticResourceEquilibrium)
{

    Param pars;
    pars.rdynamics = 0u;
    pars.capacity = 1.0;
    pars.hsymmetry = 0.0;
    pars.replenish = 2000.0;
    pars.demesizes = { 10u, 0u };
    pars.ecosel = 1.0;

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.exitburnin();
    metapop.resetTraits(0u, -1.0, pars); // optimally adapted individuals
    metapop.consume(pars);

    // Predict resource equilibrium after consumption
    const double R0 = utl::round(199.0/200.0, 4u);
    const double R1 = 0.0;

    // Fitness should sum up to the amount of food consumed
    const double sumw = utl::round(10.0 * R0, 2u);

    BOOST_CHECK_EQUAL(utl::round(metapop.getResource(0u, 0u), 4u), R0);
    BOOST_CHECK_EQUAL(utl::round(metapop.getResource(0u, 1u), 4u), R1);
    BOOST_CHECK_EQUAL(utl::round(metapop.getSumFitness(), 2u), sumw);
    BOOST_CHECK_EQUAL(utl::round(metapop.getVarFitness(), 4u), 0.0);

}

// Test logistic resource dynamics
BOOST_AUTO_TEST_CASE(KnownChemostatResourceEquilibrium)
{

    Param pars;
    pars.rdynamics = 1u;
    pars.inflow = 400.0;
    pars.outflow = 100.0;
    pars.hsymmetry = 0.0;
    pars.demesizes = { 10u, 0u };
    pars.ecosel = 1.0;

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.exitburnin();
    metapop.resetTraits(0u, -1.0, pars); // optimally adapted individuals
    metapop.consume(pars);

    // Predict resource equilibrium after consumption
    const double R0 = utl::round(400.0/110.0, 4u);
    const double R1 = 0.0;

    // Fitness should sum up to the amount of food consumed
    const double sumw = utl::round(10.0 * R0, 2u);

    BOOST_CHECK_EQUAL(utl::round(metapop.getResource(0u, 0u), 4u), R0);
    BOOST_CHECK_EQUAL(utl::round(metapop.getResource(0u, 1u), 4u), R1);
    BOOST_CHECK_EQUAL(utl::round(metapop.getSumFitness(), 2u), sumw);
    BOOST_CHECK_EQUAL(utl::round(metapop.getVarFitness(), 4u), 0.0);

}

// Test correct ecotype classification
BOOST_AUTO_TEST_CASE(EcotypeClassification)
{

    Param pars;
    pars.rdynamics = 1u;
    pars.hsymmetry = 1.0;
    pars.demesizes = { 100u, 0u };
    pars.allfreq = 0.5;
    pars.ecosel = 1.0;

    GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.exitburnin();
    metapop.consume(pars);

    // Test that ecological trait values in ecotype 1 are always higher than
    // in ecotype 0

    double xmax0 = -1.0;
    double xmin1 = 1.0;

    // For each individual
    for (size_t i = 0u; i < metapop.getSize(); ++i) {

        // Record trait value and ecotype
        const double x = metapop.getTrait(i, 0u);
        const size_t e = metapop.getEcotype(i);

        if (e == 0u && x > xmax0) xmax0 = x;
        if (e == 1u && x < xmin1) xmin1 = x;

    }

    BOOST_CHECK(xmax0 < xmin1);

}

// Test expected genetic diversity
BOOST_AUTO_TEST_CASE(KnownInitialGeneticDiversityFromAlleleFreq)
{

    Param pars = Param();
    const GenArch arch = GenArch(pars);

    // First pop with low frequency
    pars.allfreq = 0.0;
    MetaPop pop0 = MetaPop(pars, arch);

    // Second pop with high frequency
    pars.allfreq = 1.0;
    MetaPop pop1 = MetaPop(pars, arch);

    BOOST_CHECK_EQUAL(pop0.getAlleleSum(), 0u);
    BOOST_CHECK_EQUAL(pop1.getAlleleSum(), pop1.getSize() * 2u * pars.nloci);

    // Pick random individual and random locus
    BOOST_CHECK_EQUAL(pop0.getZygosity(10u, 1u, pars.nloci), 0u);
    BOOST_CHECK_EQUAL(pop1.getZygosity(10u, 1u, pars.nloci), 2u);

}

// Test speciation completion by separating the sexes in the two species
BOOST_AUTO_TEST_CASE(SpeciationCompletion)
{

    Param pars = Param();
    pars.demesizes = { 10u, 10u };

    const GenArch arch = GenArch(pars);
    MetaPop metapop = MetaPop(pars, arch);
    metapop.exitburnin();

    // Spatially separate the two ecotypes
    metapop.resetTraits(0u, 0u, -1.0, pars); // only -1 in habitat 0
    metapop.resetTraits(0u, 1u, 1.0, pars); // only +1 in habitat 1

    // Separate the sexes between the two habitats / ecotypes
    metapop.resetGenders(0u, false);
    metapop.resetGenders(1u, true);

    // Impose reproductive isolation
    metapop.complete();

    // Try to make them reproduce
    metapop.consume(pars);
    metapop.reproduce(pars, arch);

    // Check that no babies were made, pop size should stay unchanged
    BOOST_CHECK_EQUAL(metapop.getSize(), 20u);

}
