#include <iostream>
#include <fstream>

#include "aoc_day_1.h"

using namespace std;

static unsigned count_increases(const vector<long>::const_iterator cur,
		const vector<long>::const_iterator end, unsigned increases = 0)
{
	return cur == end || cur + 1 == end
		? increases
		: count_increases(cur + 1, end, increases + (*cur < *(cur + 1)))
		;
}

AocDay1::AocDay1():AocDay(1)
{
}

AocDay1::~AocDay1()
{
}

vector<long> AocDay1::read_input(string filename)
{
	vector<long> depths;
	ifstream input{filename};
	if (!input)
	{
		cerr << filename << " not found" << endl;
		return depths;
	}

	string depth_s;
#ifdef DEBUG_RUNNER
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
	/*
		for (long depth; input >> depth; )
			depths.push_back(depth);
	*/

	if (input.bad())
		cerr << "Error reading in the data from " << filename << endl;
	
	return depths;
}

string AocDay1::part1(string filename, vector<string> extra_args)
{
	const auto depths = read_input(filename);
	return to_string(count_increases(depths.cbegin(), depths.cend()));
}
