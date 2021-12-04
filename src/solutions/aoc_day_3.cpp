#include <iostream>
#include <fstream>
#include <array>
#include <cassert>

#include "aoc_day_3.h"

using namespace std;

static unsigned long get_rating(const vector<unsigned long> &report, const string::size_type line_len, const bool oxygen, const string::size_type col = 0)
{
	array<vector<remove_reference_t<decltype(report)>::value_type>, 2> criteria;
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
};

AocDay3::~AocDay3()
{
}

string AocDay3::part1(string filename, vector<string> extra_args)
{
	vector<bool> report;
	string::size_type line_len;
	ifstream input{filename};
	if (!input)
	{
		cerr << filename << " not found" << endl;
		return "";
	}

	string line;
	getline(input, line);
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
					cerr << "Unrecognized char in report: " << bit << endl;
					return "";
			}
		}
	} while (getline(input, line));

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
		cout << "Encountered " << zero_count << " 0s and " << one_count << " 1s" << endl;
#endif
		(one_count > zero_count ? gamma : epsilon) |= (1 << (line_len - col - 1));
		zero_count = one_count = 0;
	}

#ifdef DEBUG_OTHER
	cout << "gamma: " << gamma << " epsilon: " << epsilon << endl;
#endif
	return to_string(gamma * epsilon);
}

string AocDay3::part2(string filename, vector<string> extra_args)
{
	vector<unsigned long> report;
	string::size_type line_len;
	ifstream input{filename};
	if (!input)
	{
		cerr << filename << " not found" << endl;
		return "";
	}
	
	string line;
	getline(input, line);
	line_len = line.size();

	do
	{
		assert(line_len == line.size());
		report.push_back(stoul(line, nullptr, 2));
	} while (getline(input, line));

	input.close();

	const auto o2 = get_rating(report, line_len, true);
	const auto co2 = get_rating(report, line_len, false);
	const auto life_support = o2 * co2;
	return to_string(life_support);
}
