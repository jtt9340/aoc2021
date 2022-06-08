#ifndef __AOC_DAY_0__
#define __AOC_DAY_0__

#include "aoc_day.h"

class AocDay0 : public AocDay
{
private:
    std::vector<long> read_input(std::string &filename);

public:
    AocDay0();
    ~AocDay0();
    std::string part1(std::string &filename, std::vector<std::string> &extra_args) override;
    std::string part2(std::string &filename, std::vector<std::string> &extra_args) override;
};

#endif
