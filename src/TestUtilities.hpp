#ifndef SPECIOME_TESTUTILITIES_HPP
#define SPECIOME_TESTUTILITIES_HPP

// This is a header for some utility functions used in testing

#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>

namespace tst
{

  void makeValidParamFile();
  void makeValidParamFile2();
  void makeInvalidParamName();
  void makeInvalidParamValue();
  void makeInvalidParamValue2();
  void makeParamFileEmptyFreezer();
  void makeParamFileWithArchitecture();
  void makeParamFileWithMissingArchitecture();
  std::vector<double> readfile(const std::string&);
  std::vector<size_t> readfile2(const std::string&);
  size_t getFileSize(const std::string&);
  bool isFileEmpty(const std::string&);

}

#endif
