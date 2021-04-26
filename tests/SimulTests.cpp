#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include "src/Simul.h"
#include "tests/TestUtilities.h"
#include <boost/test/unit_test.hpp>
#include <iostream>

// Black box (use and abuse) testing of the proper run of the main function

// Check that the program can run without arguments
BOOST_AUTO_TEST_CASE(testUseNoArgs)
{

    BOOST_CHECK_EQUAL(simulate({ "speciome_test" }), 0);

}

// Check that the program cannot run with more than one argument
BOOST_AUTO_TEST_CASE(testAbuseTooManyArgs)
{

    BOOST_CHECK_EQUAL(simulate({ "speciome_test", "arg1", "arg2" }), 1);

}

// Invalid file name
BOOST_AUTO_TEST_CASE(testAbuseInvalidFilename)
{

    BOOST_CHECK_EQUAL(simulate({ "speciome_test", "nonsense.txt" }), 1);

}

// Valid file name
BOOST_AUTO_TEST_CASE(testUseValidFilename)
{

    tst::makeValidParamFile();
    BOOST_CHECK_EQUAL(simulate({ "speciome_test", "validparamfile.txt" }), 0);

}

// Testing run with invalid parameter names
BOOST_AUTO_TEST_CASE(testAbuseInvalidParamName)
{

    tst::makeInvalidParamName();
    BOOST_CHECK_EQUAL(simulate({ "speciome_test", "invalidparamname.txt" }), 1);

}

// Testing run with invalid parameter values
BOOST_AUTO_TEST_CASE(testAbuseInvalidParamValue)
{

    tst::makeInvalidParamValue();
    BOOST_CHECK_EQUAL(simulate({"speciome_test", "invalidparamvalue.txt"}), 1);

    tst::makeInvalidParamValue2();
    BOOST_CHECK_EQUAL(simulate({"speciome_test", "invalidparamvalue2.txt"}), 1);

}
