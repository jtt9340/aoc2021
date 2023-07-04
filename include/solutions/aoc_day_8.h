#include <vector>

#include "aoc_days.h"

#ifndef __AOC_DAY_8__
#define __AOC_DAY_8__

struct NotesEntry
{
    std::vector<std::string> signal_patterns, output;

    NotesEntry() = default;
    ~NotesEntry() = default;
};

class AocDay8 : public AocDay
{
public:
    AocDay8();
    ~AocDay8();
    std::string part1(std::string &filename, std::vector<std::string> &extra_args) override;
};

#endif
