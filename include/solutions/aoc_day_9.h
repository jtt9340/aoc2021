#include <cstdint>
#include <fstream>

#include "aoc_days.h"
#include "matrix.h"

#ifndef __AOC_DAY_9__
#define __AOC_DAY_9__

class HeightMap : public DynamicMatrix<uint8_t>
{
public:
    using DynamicMatrix<uint8_t>::DynamicMatrix;

    bool is_low_point(size_type row, size_type col) const;

#ifdef DEBUG_OTHER
    friend std::ostream &operator<<(std::ostream &out, HeightMap &curr);
#endif
};

#ifdef DEBUG_OTHER
std::ostream &operator<<(std::ostream &out, HeightMap &curr);
#endif

class AocDay9 : public AocDay
{
public:
    AocDay9();
    ~AocDay9() = default;
    std::string part1(std::string &filename, std::vector<std::string> &extra_args) override;
    std::string part2(std::string &filename, std::vector<std::string> &extra_args) override;
};

#endif
