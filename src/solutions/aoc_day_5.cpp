#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

#include "aoc_day_5.h"

static int next_coordinate(std::istringstream &iss)
{
#ifdef DEBUG_OTHER
    std::cout << "Parsing: \"" << iss.str() << '"' << std::endl;
#endif
    std::string coordinate_s;

    // Advance to first digit
    while (!isdigit(iss.peek()))
        iss.seekg(1, std::istringstream::cur);

    // Read the number until we find a non-digit character
    char next_char;
    while (std::isdigit(next_char = iss.get()))
        coordinate_s += next_char;

#ifdef DEBUG_OTHER
    std::cout << "coordinate: \"" << coordinate_s << '"' << std::endl;
#endif
    return std::stoi(coordinate_s);
}

static void mark_diagram(Diagram &diagram,
                         VentCoordinate::value_type x1,
                         VentCoordinate::value_type y1,
                         VentCoordinate::value_type x2,
                         VentCoordinate::value_type y2)
{
    assert(x1 == x2 || y1 == y2);
    if (y1 == y2)
    {
        for (VentCoordinate::value_type x{std::min(x1, x2)}; x <= std::max(x1, x2); x++)
            diagram[{x, y1}]++;
    }
    else
    {
        for (VentCoordinate::value_type y{std::min(y1, y2)}; y <= std::max(y1, y2); y++)
            diagram[{x1, y}]++;
    }
}

static void mark_diagram_diagonal(Diagram &diagram,
                                  VentCoordinate::value_type x1,
                                  VentCoordinate::value_type y1,
                                  VentCoordinate::value_type x2,
                                  VentCoordinate::value_type y2)
{
    const auto dx{x2 - x1}, dy{y2 - y1};
    if (y1 == y2)
    {
        for (VentCoordinate::value_type x{std::min(x1, x2)}; x <= std::max(x1, x2); x++)
            diagram[{x, y1}]++;
    }
    else if (x1 == x2)
    {
        for (VentCoordinate::value_type y{std::min(y1, y2)}; y <= std::max(y1, y2); y++)
            diagram[{x1, y}]++;
    }
    else if (std::abs(dx) == std::abs(dy))
    {
        // Slope is 1 / line is at 45 degree angle
        if (x1 < x2)
        {
            for (VentCoordinate::value_type x{x1}, y{y1}; x <= x2; x++)
            {
                diagram[{x, y}]++;
                if (y1 < y2)
                    y++;
                else
                    y--;
            }
        }
        else
        {
            for (VentCoordinate::value_type x{x1}, y{y1}; x >= x2; x--)
            {
                diagram[{x, y}]++;
                if (y1 < y2)
                    y++;
                else
                    y--;
            }
        }
    }
}

static void print_diagram(const Diagram &diagram)
{
    VentCoordinate::value_type max_x{0}, max_y{0};

    for (const auto &coordinate_count_pair : diagram)
    {
        const auto coordinate{coordinate_count_pair.first};
        if (coordinate[x] > max_x)
            max_x = coordinate[x];
        if (coordinate[y] > max_y)
            max_y = coordinate[y];
    }

    for (VentCoordinate::value_type row = 0; row <= max_y; row++)
    {
        for (VentCoordinate::value_type col = 0; col <= max_x; col++)
        {
            const auto coordinate = diagram.find({col, row});
            if (coordinate == std::cend(diagram))
                std::cout << '.';
            else
                std::cout << coordinate->second;
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

bool VentCoordinateComparator::operator()(const VentCoordinate &lhs, const VentCoordinate &rhs) const
{
    return lhs[x] == rhs[x] ? lhs[y] < rhs[y] : lhs[x] < rhs[x];
}

AocDay5::AocDay5() : AocDay(5)
{
}

AocDay5::~AocDay5()
{
}

std::string AocDay5::part1(std::string &filename, std::vector<std::string> &extra_args)
{
    std::ifstream input{filename};
    std::string line_s;
    Diagram overlaps;
    Diagram::mapped_type count{0};

    while (std::getline(input, line_s))
    {
        std::istringstream iss{line_s};
        VentCoordinate::value_type x1, y1, x2, y2;
        x1 = next_coordinate(iss);
        y1 = next_coordinate(iss);
        x2 = next_coordinate(iss);
        y2 = next_coordinate(iss);
#ifdef DEBUG_OTHER
        std::cout << x1 << ',' << y1 << " -> " << x2 << ',' << y2 << std::endl;
#endif
        if (x1 == x2 || y1 == y2)
            mark_diagram(overlaps, x1, y1, x2, y2);
    }

#ifdef DEBUG_OTHER
    print_diagram(overlaps);
#endif

    for (auto &crossing : overlaps)
        if (crossing.second >= 2)
            count++;

    return std::to_string(count);
}

std::string AocDay5::part2(std::string &filename, std::vector<std::string> &extra_args)
{
    std::ifstream input{filename};
    std::string line_s;
    Diagram overlaps;
    Diagram::mapped_type count{0};

    while (std::getline(input, line_s))
    {
        std::istringstream iss{line_s};
        VentCoordinate::value_type x1, y1, x2, y2;
        x1 = next_coordinate(iss);
        y1 = next_coordinate(iss);
        x2 = next_coordinate(iss);
        y2 = next_coordinate(iss);
#ifdef DEBUG_OTHER
        std::cout << x1 << ',' << y1 << " -> " << x2 << ',' << y2 << std::endl;
#endif
        mark_diagram_diagonal(overlaps, x1, y1, x2, y2);
    }

#ifdef DEBUG_OTHER
    print_diagram(overlaps);
#endif

    for (auto &crossing : overlaps)
        if (crossing.second >= 2)
            count++;

    return std::to_string(count);
}
