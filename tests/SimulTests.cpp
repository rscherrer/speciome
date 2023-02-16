#define BOOST_TEST_MODULE SimulTests

#include "../src/Simul.hpp"
#include "../src/TestUtilities.hpp"
#include <boost/test/unit_test.hpp>
#include <iostream>

// Black box (use and abuse) testing of the proper run of the main function

// Check that the program can run without arguments
BOOST_AUTO_TEST_CASE(TestUseNoArgs)
{

    BOOST_CHECK_EQUAL(simulate({ "speciome_test" }), 0);

}

// Check that the program cannot run with more than one argument
BOOST_AUTO_TEST_CASE(TestAbuseTooManyArgs)
{

    BOOST_CHECK_EQUAL(simulate({ "speciome_test", "arg1", "arg2" }), 1);

}

// Invalid file name
BOOST_AUTO_TEST_CASE(TestAbuseInvalidFilename)
{

    BOOST_CHECK_EQUAL(simulate({ "speciome_test", "nonsense.txt" }), 1);

}

// Valid file name
BOOST_AUTO_TEST_CASE(TestUseValidFilename)
{

    tst::makeValidParamFile();
    BOOST_CHECK_EQUAL(simulate({ "speciome_test", "validparamfile.txt" }), 0);

}

// Testing run with invalid parameter names
BOOST_AUTO_TEST_CASE(TestAbuseInvalidParamName)
{

    tst::makeInvalidParamName();
    BOOST_CHECK_EQUAL(simulate({ "speciome_test", "invalidparamname.txt" }), 1);

}

// Testing run with invalid parameter values
BOOST_AUTO_TEST_CASE(TestAbuseInvalidParamValue)
{

    tst::makeInvalidParamValue();
    BOOST_CHECK_EQUAL(simulate({"speciome_test", "invalidparamvalue.txt"}), 1);

    tst::makeInvalidParamValue2();
    BOOST_CHECK_EQUAL(simulate({"speciome_test", "invalidparamvalue2.txt"}), 1);

}

// Test frequency of data saving
BOOST_AUTO_TEST_CASE(DataSavingFrequency)
{

    tst::makeValidParamFile2();
    BOOST_CHECK_EQUAL(simulate({ "speciome_test", "validparamfile2.txt" }), 0);

    // Read output files
    std::vector<double> time = tst::readfile("time.dat");

    // Check that the right number of time points were saved (including 0)
    BOOST_CHECK_EQUAL(time.size(), 3u);

}
