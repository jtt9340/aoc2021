#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "aoc_day_0.h"
#include "file_utils.h"

AocDay0::AocDay0() : AocDay(0)
{
}

AocDay0::~AocDay0()
{
}

std::vector<long> AocDay0::read_input(std::string &filename)
{
    FileUtils fileutils;
    std::vector<std::string> raw_lines;
    std::vector<long> data;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        std::cerr << "Error reading in the data from " << filename << std::endl;
        return data;
    }
    for (std::vector<std::string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        long l;
        std::string to_convert = *iter;
        l = strtol(to_convert.c_str(), NULL, 10);
        data.push_back(l);
    }
    return data;
}

std::string AocDay0::part1(std::string &filename, std::vector<std::string> &extra_args)
{
    std::vector<long> data = read_input(filename);
    long sum = 0;
    for (std::vector<long>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        sum += *iter;
    }
    std::ostringstream out;
    out << sum;
    return out.str();
}

std::string AocDay0::part2(std::string &filename, std::vector<std::string> &extra_args)
{
    if (extra_args.size() > 0)
    {
        std::cout << "There are " << extra_args.size() << " extra arguments given:" << std::endl;
        for (std::vector<std::string>::iterator iter = extra_args.begin(); iter != extra_args.end(); ++iter)
        {
            std::cout << "[" << *iter << "]" << std::endl;
        }
    }

    std::vector<long> data = read_input(filename);
    long sum = 0;
    for (std::vector<long>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        sum -= *iter;
    }
    std::ostringstream out;
    out << sum;
    return out.str();
}
