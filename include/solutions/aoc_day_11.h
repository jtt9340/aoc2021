#include <cstdint>
#include <iostream>

#include "aoc_days.h"
#include "matrix.h"

#ifndef __AOC_DAY_11__
#define __AOC_DAY_11__

struct DumboOctopus
{
    std::uint8_t energy_level;
    bool flashed;

    DumboOctopus() = default;
    DumboOctopus(std::uint8_t energy_level);
};

std::ostream &operator<<(std::ostream &out, DumboOctopus &octopus);

class DumboOctopuses : public Matrix<DumboOctopus, 10, 10>
{
    std::uint64_t flashes{0};

    void flash(size_type i, size_type j);

public:
    std::uint64_t step();
};

std::istream &operator>>(std::istream &in, DumboOctopuses &ocotpi);

class AocDay11 : public AocDay
{
public:
    AocDay11();
    ~AocDay11() = default;
    std::string part1(std::string &filename, std::vector<std::string> &extra_args) override;
};

#endif
