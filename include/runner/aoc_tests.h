#ifndef __AOC_TESTS_H__
#define __AOC_TESTS_H__

#include <string>
#include <vector>

#include "aoc_test.h"

class AocTests
{
private:
    std::vector<AocTest> m_tests;
    std::string base_directory(std::string filename);

public:
    AocTests();
    ~AocTests();
    bool load_tests(std::string filename);
    std::vector<AocTest> get_all_tests();
    std::vector<AocTest> filter_tests(int day, int part);
};

#endif
