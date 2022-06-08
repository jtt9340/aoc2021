#ifndef __AOC_DAY_1__
#define __AOC_DAY_1__

#include "aoc_day.h"

class AocDay1 : public AocDay
{
private:
    std::vector<long> read_input(std::string &filename);

public:
    AocDay1();
    ~AocDay1();
    std::string part1(std::string &filename, std::vector<std::string> &extra_arga) override;
    std::string part2(std::string &filename, std::vector<std::string> &extra_args) override;
};

#endif
