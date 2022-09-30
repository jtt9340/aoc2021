#include "aoc_days.h"

#ifndef __AOC_DAY_7__
#define __AOC_DAY_7__

class AocDay7 : public AocDay
{
    std::vector<long> read_input(std::string &filename);

public:
    AocDay7();
    ~AocDay7();
    std::string part1(std::string &filename, std::vector<std::string> &extra_args) override;
};

#endif
