#include "aoc_days.h"

#ifndef __AOC_DAY_10__
#define __AOC_DAY_10__

class AocDay10 : public AocDay
{
public:
    AocDay10();
    ~AocDay10() = default;
    std::string part1(std::string &filename, std::vector<std::string> &extra_args) override;
};

#endif
