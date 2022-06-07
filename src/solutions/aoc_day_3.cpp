#include <iostream>
#include <fstream>
#include <array>
#include <cassert>

#include "aoc_day_3.h"

static unsigned long get_rating(const std::vector<unsigned long> &report, const std::string::size_type line_len, const bool oxygen, const std::string::size_type col = 0)
{
	std::array<std::vector<std::remove_reference_t<decltype(report)>::value_type>, 2> criteria;
	unsigned zero_count{0}, one_count{0};
	for (auto value : report)
	{
		const auto bit = value & (1 << (line_len - col - 1));
		(bit ? one_count : zero_count)++;
		criteria.at(!!bit).push_back(value);
	}

	if (oxygen && one_count >= zero_count)
	{
		return criteria[1].size() == 1
			? criteria[1].front()
			: get_rating(criteria[1], line_len, oxygen, col + 1)
			;
	}
	else if (oxygen)
	{
		return criteria[0].size() == 1
			? criteria[0].front()
			: get_rating(criteria[0], line_len, oxygen, col + 1)
			;
	}
	else if (one_count >= zero_count)
	{
		return criteria[0].size() == 1
			? criteria[0].front()
			: get_rating(criteria[0], line_len, oxygen, col + 1)
			;
	}
	else
	{
		return criteria[1].size() == 1
			? criteria[1].front()
			: get_rating(criteria[1], line_len, oxygen, col + 1)
			;
	}
}

AocDay3::AocDay3():AocDay(3)
{
}

AocDay3::~AocDay3()
{
}

std::string AocDay3::part1(std::string &filename, std::vector<std::string> &extra_args)
{
	std::vector<bool> report;
	std::string::size_type line_len;
	std::ifstream input{filename};
	if (!input)
	{
		std::cerr << filename << " not found" << std::endl;
		return "";
	}

	std::string line;
	std::getline(input, line);
	line_len = line.size();

	do
	{
		assert(line_len == line.size());
		for (const auto bit : line)
		{
			switch (bit)
			{
				case '0':
					report.push_back(false);
					break;
				case '1':
					report.push_back(true);
					break;
				default:
					std::cerr << "Unrecognized char in report: " << bit << std::endl;
					return "";
			}
		}
	} while (std::getline(input, line));

	input.close();

	unsigned gamma{0}, epsilon{0}, zero_count{0}, one_count{0};

	for (auto col = 0; col < line_len; col++)
	{
		for (auto row = 0; row < (report.size() / line_len); row++)
		{
			const auto bit = report.at(row * line_len + col);
			(bit ? one_count : zero_count)++;
		}
#ifdef DEBUG_OTHER
		std::cout << "Encountered " << zero_count << " 0s and " << one_count << " 1s" << std::endl;
#endif
		(one_count > zero_count ? gamma : epsilon) |= (1 << (line_len - col - 1));
		zero_count = one_count = 0;
	}

#ifdef DEBUG_OTHER
	std::cout << "gamma: " << gamma << " epsilon: " << epsilon << std::endl;
#endif
	return std::to_string(gamma * epsilon);
}

std::string AocDay3::part2(std::string &filename, std::vector<std::string> &extra_args)
{
	std::vector<unsigned long> report;
	std::string::size_type line_len;
	std::ifstream input{filename};
	if (!input)
	{
		std::cerr << filename << " not found" << std::endl;
		return "";
	}
	
	std::string line;
	std::getline(input, line);
	line_len = line.size();

	do
	{
		assert(line_len == line.size());
		report.push_back(stoul(line, nullptr, 2));
	} while (std::getline(input, line));

	input.close();

	const auto o2 = get_rating(report, line_len, true);
	const auto co2 = get_rating(report, line_len, false);
	const auto life_support = o2 * co2;
	return std::to_string(life_support);
}
