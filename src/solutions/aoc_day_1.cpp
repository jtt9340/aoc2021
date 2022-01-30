#include <iostream>
#include <fstream>

#include "aoc_day_1.h"

using namespace std;

static unsigned count_increases(const vector<long>::const_iterator cur,
		const vector<long>::const_iterator end, unsigned increases = 0)
{
	return cur == end || cur + 1 == end
		? increases
		: count_increases(cur + 1, end, increases + (cur[0] < cur[1]))
		;
}

static unsigned count_sliding_window_increases(const vector<long>::const_iterator cur,
		const vector<long>::const_iterator end, unsigned increases = 0)
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

vector<long> AocDay1::read_input(string &filename)
{
	vector<long> depths;
	ifstream input{filename};
	if (!input)
	{
		cerr << filename << " not found" << endl;
		return depths;
	}

	string depth_s;
#ifdef DEBUG_OTHER
	try
	{
		while (getline(input, depth_s))
			depths.push_back(stol(depth_s));
	}
	catch (const invalid_argument &e)
	{
		cerr << "Error reading in the data from " << filename << ": " << e.what() << endl;
		cerr << "on input: " << depth_s << endl;
	}
#else
	while (getline(input, depth_s))
		depths.push_back(stol(depth_s));
#endif

	if (input.bad())
		cerr << "Error reading in the data from " << filename << endl;
	
	input.close();
	return depths;
}

string AocDay1::part1(string &filename, vector<string> &extra_args)
{
	const auto depths = read_input(filename);
	return to_string(count_increases(depths.cbegin(), depths.cend()));
}

string AocDay1::part2(string &filename, vector<string> &extra_args)
{
	const auto depths = read_input(filename);
	return to_string(count_sliding_window_increases(depths.cbegin(), depths.cend()));
}
