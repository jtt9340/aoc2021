#include <algorithm>
#include <array>
#include <cassert>
#ifdef DEBUG_OTHER
#include <iostream>
#endif

#include "aoc_day_11.h"
#include "util.h"

constexpr size_t num_iterations = 100;

DumboOctopus::DumboOctopus(std::uint8_t energy_level) : energy_level{energy_level}, flashed{false}
{
}

std::ostream &operator<<(std::ostream &out, DumboOctopus &octopus)
{
    return out << from_digit(octopus.energy_level) << (octopus.flashed ? '*' : ' ') << ' ';
}

void DumboOctopuses::flash(DumboOctopuses::size_type i, DumboOctopuses::size_type j)
{
    bool &flashed = (*this)(i, j).flashed;
    assert(!flashed);
    flashed = true;
    flashes++;

    // Top left
    if (i > 0 && j > 0 && !(*this)(i - 1, j - 1).flashed && ++(*this)(i - 1, j - 1).energy_level > 9)
        flash(i - 1, j - 1);

    // Top
    if (i > 0 && !(*this)(i - 1, j).flashed && ++(*this)(i - 1, j).energy_level > 9)
        flash(i - 1, j);

    // Top right
    if (i > 0 && j < DumboOctopuses::cols - 1 && !(*this)(i - 1, j + 1).flashed && ++(*this)(i - 1, j + 1).energy_level > 9)
        flash(i - 1, j + 1);

    // Left
    if (j > 0 && !(*this)(i, j - 1).flashed && ++(*this)(i, j - 1).energy_level > 9)
        flash(i, j - 1);

    // Right
    if (j < DumboOctopuses::cols - 1 && !(*this)(i, j + 1).flashed && ++(*this)(i, j + 1).energy_level > 9)
        flash(i, j + 1);

    // Bottom left
    if (i < DumboOctopuses::rows - 1 && j > 0 && !(*this)(i + 1, j - 1).flashed && ++(*this)(i + 1, j - 1).energy_level > 9)
        flash(i + 1, j - 1);

    // Bottom
    if (i < DumboOctopuses::rows - 1 && !(*this)(i + 1, j).flashed && ++(*this)(i + 1, j).energy_level > 9)
        flash(i + 1, j);

    // Bottom right
    if (i < DumboOctopuses::rows - 1 && j < DumboOctopuses::cols - 1 && !(*this)(i + 1, j + 1).flashed &&
        ++(*this)(i + 1, j + 1).energy_level > 9)
        flash(i + 1, j + 1);
}

std::pair<std::uint64_t, bool> DumboOctopuses::step()
{
    for (auto i = 0; i < DumboOctopuses::rows; i++)
    {
        for (auto j = 0; j < DumboOctopuses::cols; j++)
        {
            DumboOctopus &octopus = (*this)(i, j);
            if (++octopus.energy_level > 9 && !octopus.flashed)
                flash(i, j);
        }
    }

    bool all_flashed = true;

    // "Any octopus that flashed during this step has its energy level set to 0"
    std::for_each(std::begin(arr),
                  std::end(arr),
                  [&all_flashed](DumboOctopus &octopus)
                  {
                      if (octopus.flashed)
                      {
                          octopus.flashed = false;
                          octopus.energy_level = 0;
                      }
                      else
                      {
                          all_flashed = false;
                      }
                  });

    return std::make_pair(flashes, all_flashed);
}

std::istream &operator>>(std::istream &in, DumboOctopuses &octopi)
{
    for (auto i = 0; i < DumboOctopuses::rows; i++)
    {
        for (auto j = 0; j < DumboOctopuses::cols; j++)
            octopi(i, j) = to_digit(in.get());
        const auto newline = in.get();
        assert(newline == '\n');
    }

    return in;
}

AocDay11::AocDay11() : AocDay(11)
{
}

std::string AocDay11::part1(std::string &filename, std::vector<std::string> &extra_args)
{
    std::ifstream input{filename};
    DumboOctopuses octopi;
    input >> octopi;

#ifdef DEBUG_OTHER
    std::cout << octopi << std::endl;
#endif

    std::uint64_t flash_count;
    for (auto i = 0; i < num_iterations; i++)
    {
        flash_count = octopi.step().first;
#ifdef DEBUG_OTHER
        std::cout << octopi << std::endl;
#endif
    }

    return std::to_string(flash_count);
}

std::string AocDay11::part2(std::string &filename, std::vector<std::string> &extra_args)
{
    std::ifstream input{filename};
    DumboOctopuses octopi;
    input >> octopi;

    for (auto i = 1;; i++)
        if (octopi.step().second)
            return std::to_string(i);

    return "";
}
