#include <iostream>
#include <fstream>

#include "aoc_day_1.h"

static unsigned count_increases(const std::vector<long>::const_iterator cur,
		const std::vector<long>::const_iterator end, unsigned increases = 0)
{
	return cur == end || cur + 1 == end
		? increases
		: count_increases(cur + 1, end, increases + (cur[0] < cur[1]))
		;
}

static unsigned count_sliding_window_increases(const std::vector<long>::const_iterator cur,
		const std::vector<long>::const_iterator end, unsigned increases = 0)
{
	if (end - cur < 4)
		return increases;

	const auto cur_sum = cur[0] + cur[1] + cur[2];
	const auto next_sum = cur[1] + cur[2] + cur[3];
	return count_sliding_window_increases(cur + 1, end, increases + (cur_sum < next_sum));
}

AocDay1::AocDay1():AocDay(1)
{
}

AocDay1::~AocDay1()
{
}

std::vector<long> AocDay1::read_input(std::string &filename)
{
	std::vector<long> depths;
	std::ifstream input{filename};
	if (!input)
	{
		std::cerr << filename << " not found" << std::endl;
		return depths;
	}

	std::string depth_s;
#ifdef DEBUG_OTHER
	try
	{
		while (std::getline(input, depth_s))
			depths.push_back(stol(depth_s));
	}
	catch (const std::invalid_argument &e)
	{
		std::cerr << "Error reading in the data from " << filename << ": " << e.what() << std::endl;
		std::cerr << "on input: " << depth_s << std::endl;
	}
#else
	while (std::getline(input, depth_s))
		depths.push_back(stol(depth_s));
#endif

	if (input.bad())
		std::cerr << "Error reading in the data from " << filename << std::endl;
	
	input.close();
	return depths;
}

std::string AocDay1::part1(std::string &filename, std::vector<std::string> &extra_args)
{
	const auto depths = read_input(filename);
	return std::to_string(count_increases(std::cbegin(depths), std::cend(depths)));
}

std::string AocDay1::part2(std::string &filename, std::vector<std::string> &extra_args)
{
	const auto depths = read_input(filename);
	return std::to_string(count_sliding_window_increases(std::cbegin(depths), std::cend(depths)));
}
