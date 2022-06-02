#include <iostream>
#include <iomanip>
#include <cassert>

#include "aoc_day_6.h"
#include "file_utils.h"
#include "constants.h"

using namespace std;

#ifdef DEBUG_OTHER
struct report_day
{
	const size_t day;
	const vector<long> &lanternfish;

	report_day(const size_t n, const vector<long> &timers)
		: day{n}, lanternfish{timers} {}
};

template <class T>
static ostream &operator<<(ostream &os, const vector<T> &values)
{
	for (auto it = begin(values); it != end(values); it++)
	{
		os << *it;
		if (it + 2 != end(values))
			os << ',';
	}
	return os;
}

static ostream &operator<<(ostream &out, report_day curr)
{
	return out << "After" << setw(3) << curr.day
		       << (curr.day == 1 ? "day: " : " days: ")
			   << curr.lanternfish; 
}
#endif

static void next_day(vector<long> &lanternfish)
{
	const auto cur_size = lanternfish.size();
	for (auto i = 0; i < cur_size; i++)
	{
		if (lanternfish[i] == 0)
		{
			lanternfish[i] = 6;
			lanternfish.push_back(8);
		}
		else
		{
			lanternfish[i]--;
		}
	}
}

AocDay6::AocDay6():AocDay(6)
{
}

AocDay6::~AocDay6()
{
}

string AocDay6::part1(string &filename, vector<string> &extra_args)
{
	FileUtils fileutils;
	vector<vector<long>> lanternfish;

	if (!fileutils.read_as_list_of_split_longs(filename, lanternfish, TEST_INDEX_DELIM, TEST_INDEX_QUOTE, TEST_INDEX_COMMENT))
	{
		cerr << "Error reading in the data from " << filename << endl;
		return "";
	}

	assert(lanternfish.size() == 1);
	vector<long> &timers = lanternfish[0];
#ifdef DEBUG_OTHER
	cout << "Initial state: " << timers << endl;
#endif
	for (auto i = 0; i < NUM_DAYS; i++)
	{
		next_day(timers);
#ifdef DEBUG_OTHER
		cout << report_day(i + 1, timers) << '\n';
#endif
	}

	return to_string(timers.size());
}
