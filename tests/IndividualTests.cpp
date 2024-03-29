#define BOOST_TEST_MODULE IndividualTests

#include "../src/Individual.hpp"
#include "../src/Utilities.hpp"
#include <boost/test/unit_test.hpp>
#include <iostream>

// Test functions associated with individual

// Test genome generation
BOOST_AUTO_TEST_CASE(GenerateOnlyZeroAlleles)
{

    Param pars;
    pars.allfreq = 0.0;

    GenArch arch = GenArch(pars);
    Individual ind = Individual(pars, arch);

    BOOST_CHECK_EQUAL(ind.getAlleleSum(), 0u);
    BOOST_CHECK_EQUAL(ind.getZygosity(0u, pars.nloci), 0u); // pick random locus

}

// Testing 1-only genome generation
BOOST_AUTO_TEST_CASE(GenerateOnlyOneAlleles)
{

    Param pars;
    pars.allfreq = 1.0;

    GenArch arch = GenArch(pars);
    Individual ind = Individual(pars, arch);

    BOOST_CHECK_EQUAL(ind.getAlleleSum(), 2u * pars.nloci);
    BOOST_CHECK_EQUAL(ind.getZygosity(0u, pars.nloci), 2u); // pick random locus

}

// Test homogamous mate choice
BOOST_AUTO_TEST_CASE(HomogamousFemaleAcceptsIdenticalMale)
{

    Param pars;
    pars.allfreq = 0.5;
    pars.sexsel = 1.0;

    GenArch arch = GenArch(pars);

    Individual ind = Individual(pars, arch);
    ind.resetTrait(0u, 0.0, pars);
    ind.resetTrait(1u, 1.0, pars); // full assortative mating

    BOOST_CHECK_EQUAL(ind.mate(0.0, pars), 1.0);

}

// Heterogamous mate choice
BOOST_AUTO_TEST_CASE(HeterogamousFemaleRejectsIdenticalMale)
{

    Param pars;
    pars.allfreq = 0.5;
    pars.sexsel = 1.0;

    GenArch arch = GenArch(pars);

    Individual ind = Individual(pars, arch);
    ind.resetTrait(0u, 0.0, pars);
    ind.resetTrait(1u, -1.0, pars); // full disassortative mating

    BOOST_CHECK_EQUAL(ind.mate(0.0, pars), 0.0);

}

// Test random mating
BOOST_AUTO_TEST_CASE(RandomMatingFemaleAcceptsAnyone)
{

    Param pars;
    pars.allfreq = 0.5;
    pars.sexsel = 1.0;

    GenArch arch = GenArch(pars);

    Individual ind = Individual(pars, arch);
    ind.resetTrait(0u, 0.0, pars);
    ind.resetTrait(1u, 0.0, pars); // random mating

    BOOST_CHECK_EQUAL(ind.mate(0.0, pars), 1.0);
    BOOST_CHECK_EQUAL(ind.mate(1.0, pars), 1.0);
    BOOST_CHECK_EQUAL(ind.mate(-1.0, pars), 1.0);

}

// Test fecundation (this is also a test of no mutation)
BOOST_AUTO_TEST_CASE(MatingBetweenAlternativeHomozygotesGivesHeterozygoteNoMut)
{

    Param pars;
    pars.mutation = 0.0; // no mutation

    GenArch arch = GenArch(pars);

    // Make mom
    pars.allfreq = 0.0;
    Individual mom = Individual(pars, arch);

    // Make dad
    pars.allfreq = 1.0;
    Individual dad = Individual(pars, arch);

    // Make baby
    Individual baby = Individual(pars, arch, mom, dad);

    BOOST_CHECK_EQUAL(baby.getAlleleSum(), pars.nloci);

}

// Test mutation
BOOST_AUTO_TEST_CASE(MutationAltersTheGenome)
{

    Param pars;
    pars.mutation = 0.99; // high mutation
    pars.allfreq = 0.0;

    GenArch arch = GenArch(pars);

    Individual mom = Individual(pars, arch);
    Individual dad = Individual(pars, arch);
    Individual baby = Individual(pars, arch, mom, dad);

    BOOST_CHECK(baby.getAlleleSum() > 0u);

}

// Test recombination
BOOST_AUTO_TEST_CASE(BackcrossPredictableIfNoRecombination)
{

    Param pars;
    pars.nchrom = 1u; // one chromosome to avoid free recombination
    pars.mutation = 0.0; // no mutation
    pars.recombination = 0.0; // no recombination

    GenArch arch = GenArch(pars);

    // Make mom
    pars.allfreq = 0.0;
    Individual mom = Individual(pars, arch); // aa

    // Make dad
    pars.allfreq = 1.0;
    Individual dad = Individual(pars, arch); // AA

    // Make baby
    Individual f1 = Individual(pars, arch, mom, dad); // Aa

    // Make backcross
    Individual backcross = Individual(pars, arch, mom, f1);

    // Backcross should be either full aa or full Aa if no recombination
    const size_t allsum = backcross.getAlleleSum();

    BOOST_CHECK(allsum == 0u || allsum == pars.nloci);

}

// Unpredictable backcross
BOOST_AUTO_TEST_CASE(BackcrossUnpredictableIfRecombination)
{

    Param pars;
    pars.mutation = 0.0; // no mutation
    pars.recombination = 10.0; // high recombination

    GenArch arch = GenArch(pars);

    // Make mom
    pars.allfreq = 0.0;
    Individual mom = Individual(pars, arch); // aa

    // Make dad
    pars.allfreq = 1.0;
    Individual dad = Individual(pars, arch); // AA

    // Make baby
    Individual f1 = Individual(pars, arch, mom, dad); // Aa

    // Make backcross
    Individual backcross = Individual(pars, arch, mom, f1);

    // Backcross should be either full aa or full Aa if no recombination
    const size_t allsum = backcross.getAlleleSum();

    BOOST_CHECK(allsum > 0u && allsum != pars.nloci);

}

// Inhibited gene expression
BOOST_AUTO_TEST_CASE(AlleleZeroInhibitsGeneExpression)
{

    Param pars;
    pars.allfreq = 0.0;

    GenArch arch = GenArch(pars);
    Individual ind = Individual(pars, arch);

    BOOST_CHECK_EQUAL(ind.getExpression(), -1.0 * pars.nloci);

}

// Enhanced gene expression
BOOST_AUTO_TEST_CASE(AlleleOneEnhancesGeneExpression)
{

    Param pars;
    pars.allfreq = 1.0;

    GenArch arch = GenArch(pars);
    Individual ind = Individual(pars, arch);

    BOOST_CHECK_EQUAL(ind.getExpression(), pars.nloci);

}

// Test development
BOOST_AUTO_TEST_CASE(HybridDevelopsWithZeroTraitValuesIfCodominance)
{

    Param pars;
    pars.mutation = 0.0;
    pars.dominancevar = 0.0; // codominance

    GenArch arch = GenArch(pars);

    // Make mom
    pars.allfreq = 0.0;
    Individual mom = Individual(pars, arch);

    // Make dad
    pars.allfreq = 1.0;
    Individual dad = Individual(pars, arch);

    // Make baby
    Individual baby = Individual(pars, arch, mom, dad);

    // Without dominance the expression of each trait should be zero
    BOOST_CHECK_EQUAL(baby.getTraitValue(0u), 0.0);
    BOOST_CHECK_EQUAL(baby.getTraitValue(1u), 0.0);
    BOOST_CHECK_EQUAL(baby.getTraitValue(2u), 0.0);

}






