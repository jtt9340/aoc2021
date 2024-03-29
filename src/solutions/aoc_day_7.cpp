#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>

#include "aoc_day_7.h"
#include "constants.h"
#include "file_utils.h"

long median(std::vector<long> &positions)
{
    // I hope to God I can just use the naive O(n log n) median algorithm
    std::sort(std::begin(positions), std::end(positions));
    return positions[positions.size() / 2];
}

long compute_fuel_simple(const std::vector<long> &positions, const long align)
{
    std::vector<long> distances;
    for (const auto &pos : positions)
        distances.push_back(std::abs(pos - align));
    // std::transform(std::cbegin(positions), std::cend(positions), std::begin(distances), [align](long pos) { return std::abs(pos - align);
    // });
    return std::accumulate(std::cbegin(distances) + 1, std::cend(distances), distances[0]);
}

long compute_fuel(const std::vector<long> &positions, const long align)
{
    std::vector<long> distances;
    for (const auto &pos : positions)
    {
        const auto diff = std::abs(pos - align);
        distances.push_back((diff * (diff + 1)) / 2);
    }
    return std::accumulate(std::cbegin(distances) + 1, std::cend(distances), distances[0]);
}

AocDay7::AocDay7() : AocDay(7)
{
}

AocDay7::~AocDay7()
{
}

std::vector<long> AocDay7::read_input(std::string &filename)
{
    FileUtils fileutils;
    std::vector<std::vector<long>> positions;

    if (!fileutils.read_as_list_of_split_longs(filename, positions, TEST_INDEX_DELIM, TEST_INDEX_QUOTE, TEST_INDEX_COMMENT))
    {
        std::cerr << "Error reading in the data from " << filename << std::endl;
        return {};
    }

    assert(positions.size() == 1);
    return std::move(positions[0]);
}

std::string AocDay7::part1(std::string &filename, std::vector<std::string> &extra_args)
{
    auto positions = read_input(filename);
    const auto align = median(positions);
    return std::to_string(compute_fuel_simple(positions, align));
}

std::string AocDay7::part2(std::string &filename, std::vector<std::string> &extra_args)
{
    auto positions = read_input(filename);
    long fuel = std::numeric_limits<long>::max();
    const auto bounds = std::minmax_element(std::cbegin(positions), std::cend(positions));
    const auto leftmost_pos = *bounds.first;
    const auto rightmost_pos = *bounds.second;
    for (auto align = leftmost_pos; align <= rightmost_pos; align++)
    {
        const auto new_fuel = compute_fuel(positions, align);
        if (new_fuel < fuel)
            fuel = new_fuel;
    }
    return std::to_string(fuel);
}
