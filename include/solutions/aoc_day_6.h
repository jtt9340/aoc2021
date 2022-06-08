#include <array>

#include "aoc_days.h"

#ifndef __AOC_DAY_6__
#define __AOC_DAY_6__

class lanternfish
{
    using record = std::array<size_t, 9>;
    record timers;

    void next_day();

public:
    template <class InputIt>
    lanternfish(InputIt begin, InputIt end) : timers{0, 0, 0, 0, 0, 0, 0, 0, 0}
    {
        for (auto it = begin; it != end; it++)
        {
            try
            {
                timers.at(*it)++;
            }
            catch (const std::out_of_range &e)
            {
                throw std::invalid_argument{"A fish's count cannot be outside the range [0, 8]"};
            }
        }
    }

    size_t simulate(const size_t days);
};

class AocDay6 : public AocDay
{
    std::vector<long> read_input(std::string &filename);

public:
    AocDay6();
    ~AocDay6();
    std::string part1(std::string &filename, std::vector<std::string> &extra_args) override;
    std::string part2(std::string &filename, std::vector<std::string> &extra_args) override;
};

#endif
