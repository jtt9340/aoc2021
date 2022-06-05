#include <iostream>
#include <iomanip>
#include <cassert>
#include <numeric>

#include "aoc_day_6.h"
#include "file_utils.h"
#include "constants.h"

using namespace std;

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
	return accumulate(begin(timers) + 1, end(timers), timers[0]);
}

AocDay6::AocDay6():AocDay(6)
{
}

AocDay6::~AocDay6()
{
}

vector<long> AocDay6::read_input(string &filename)
{
	FileUtils fileutils;
	vector<vector<long>> lanternfish;

	if (!fileutils.read_as_list_of_split_longs(filename, lanternfish, TEST_INDEX_DELIM, TEST_INDEX_QUOTE, TEST_INDEX_COMMENT))
	{
		cerr << "Error reading in the data from " << filename << endl;
		return {};
	}

	assert(lanternfish.size() == 1);
	return move(lanternfish[0]);
}

string AocDay6::part1(string &filename, vector<string> &extra_args)
{
	auto timers = read_input(filename);
	lanternfish solution{begin(timers), end(timers)};
	return to_string(solution.simulate(80));
}

string AocDay6::part2(string &filename, vector<string> &extra_args)
{
	auto timers = read_input(filename);
	lanternfish solution{begin(timers), end(timers)};
	return to_string(solution.simulate(256));
}
