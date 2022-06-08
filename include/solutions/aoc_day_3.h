#include "aoc_days.h"

#ifndef __AOC_DAY_3__
#define __AOC_DAY_3__

class AocDay3 : public AocDay
{
public:
    AocDay3();
    ~AocDay3();
    std::string part1(std::string &filename, std::vector<std::string> &extra_args) override;
    std::string part2(std::string &filename, std::vector<std::string> &extra_args) override;
};

#endif
