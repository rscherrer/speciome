#include "src/GenArch.h"
#include "src/Random.h"
#include "src/Utilities.h"
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cassert>

// Test the correct generation of a genetic architecture

// Testing correct chromosome lengths
BOOST_AUTO_TEST_CASE(ChromosomesHaveEqualLength)
{

    Param pars;
    GenArch arch = GenArch(pars);

    BOOST_CHECK_EQUAL(arch.chromosomes[0u], 1.0 / 3.0);
    BOOST_CHECK_EQUAL(arch.chromosomes[1u], 2.0 / 3.0);
    BOOST_CHECK_EQUAL(arch.chromosomes[2u], 1.0);

}

// Testing genetic encoding of traits
BOOST_AUTO_TEST_CASE(LociEncodeTheRightTraits)
{

    Param pars;
    pars.nvertices = { 10u, 2u, 2u };
    pars.nedges = {11u, 1u, 1u};
    pars.update();

    GenArch arch = GenArch(pars);

    BOOST_CHECK_EQUAL(arch.getSumTraits(), 6u);

}

// Testing locus effect sizes
BOOST_AUTO_TEST_CASE(EffectSizesAreOneIfScaleParamIsZero)
{

    Param pars;
    pars.effectscale = 0.0;

    GenArch arch = GenArch(pars);

    BOOST_CHECK_EQUAL(arch.getSumEffects(), pars.nloci);

}

// Testing dominance coefficients
BOOST_AUTO_TEST_CASE(DominancesAreOneIfVarianceIsZero)
{

    Param pars;
    pars.dominancevar = 0.0;
    GenArch arch = GenArch(pars);

    BOOST_CHECK_EQUAL(arch.getSumDominances(), pars.nloci);

}

// Testing single edge network
BOOST_AUTO_TEST_CASE(NetworkWithOneEdgeConnectsNodesZeroAndOne)
{

    Param pars;
    pars.nvertices = {2u, 2u, 2u};
    pars.nedges = { 1u, 1u, 1u };
    pars.update();

    GenArch arch = GenArch(pars);

    BOOST_CHECK_EQUAL(arch.getNetworkSize(0u), 1u);
    BOOST_CHECK_EQUAL(arch.getNetworkSize(1u), 1u);
    BOOST_CHECK_EQUAL(arch.getNetworkSize(2u), 1u);
    BOOST_CHECK_EQUAL(arch.getEdge(0u, 0u).first, 0u);
    BOOST_CHECK_EQUAL(arch.getEdge(0u, 0u).second, 1u);

}

// Test that the network is connected
BOOST_AUTO_TEST_CASE(NetworkIsConnected)
{

    Param pars;
    pars.nvertices = { 30u, 30u, 30u };
    pars.nedges = { 31u, 31u, 31u };
    pars.update();

    GenArch arch = GenArch(pars);

    for (size_t trait = 0u; trait < 3u; ++trait)
        BOOST_CHECK(arch.isConnected(trait));

}

// Testing interaction weights
BOOST_AUTO_TEST_CASE(InteractionWeightsAreOneIfScaleParamIsZero)
{

    Param pars;
    pars.interactionscale = 0.0;
    GenArch arch = GenArch(pars);

    BOOST_CHECK_EQUAL(arch.getSumWeights(0u), pars.nedges[0u]);
    BOOST_CHECK_EQUAL(arch.getSumWeights(1u), pars.nedges[1u]);
    BOOST_CHECK_EQUAL(arch.getSumWeights(2u), pars.nedges[2u]);

}

// Test making a genetic architecture, saving it, then making another one by
// reading the one we saved and check that they are identical
BOOST_AUTO_TEST_CASE(ArchitectureSavesAndLoadsProperly)
{

    Param pars;
    pars.archsave = true;
    pars.archload = false;

    GenArch archsaved = GenArch(pars);

    pars.archsave = false;
    pars.archload = true;

    GenArch archloaded = GenArch(pars);
    archloaded.load(pars);

    const double ssqeff1 = archsaved.getSsqEffects();
    const double ssqeff2 = archloaded.getSsqEffects();
    const double ssqwgt1 = archsaved.getSsqWeights(0u);
    const double ssqwgt2 = archloaded.getSsqWeights(0u);

    BOOST_CHECK_EQUAL(utl::round(ssqeff1, 4u), utl::round(ssqeff2, 4u));
    BOOST_CHECK_EQUAL(utl::round(ssqwgt1, 4u), utl::round(ssqwgt2, 4u));

}
