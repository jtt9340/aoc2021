#include <cassert>
#include <iomanip>
#include <iostream>
#include <numeric>

#include "aoc_day_6.h"
#include "constants.h"
#include "file_utils.h"

void lanternfish::next_day()
{
    lanternfish::record transaction{timers};
    for (int8_t i = timers.size() - 1; i >= 0; i--)
    {
        const auto count = timers[i];
        if (i == 0)
        {
            transaction[i] -= count;
            transaction[6] += count;
            transaction[8] += count;
        }
        else
        {
            transaction[i] -= count;
            transaction[i - 1] += count;
        }
    }
    timers = transaction;
}

size_t lanternfish::simulate(const size_t days)
{
    for (auto i = 0; i < days; i++)
        next_day();
    return std::accumulate(std::begin(timers) + 1, std::end(timers), timers[0]);
}

AocDay6::AocDay6() : AocDay(6)
{
}

AocDay6::~AocDay6()
{
}

std::vector<long> AocDay6::read_input(std::string &filename)
{
    FileUtils fileutils;
    std::vector<std::vector<long>> lanternfish;

    if (!fileutils.read_as_list_of_split_longs(filename, lanternfish, TEST_INDEX_DELIM, TEST_INDEX_QUOTE, TEST_INDEX_COMMENT))
    {
        std::cerr << "Error reading in the data from " << filename << std::endl;
        return {};
    }

    assert(lanternfish.size() == 1);
    return std::move(lanternfish[0]);
}

std::string AocDay6::part1(std::string &filename, std::vector<std::string> &extra_args)
{
    auto timers = read_input(filename);
    lanternfish solution{std::begin(timers), std::end(timers)};
    return std::to_string(solution.simulate(80));
}

std::string AocDay6::part2(std::string &filename, std::vector<std::string> &extra_args)
{
    auto timers = read_input(filename);
    lanternfish solution{std::begin(timers), std::end(timers)};
    return std::to_string(solution.simulate(256));
}
