#include <iostream>
#include <fstream>
#include <cassert>

#include "aoc_day_3.h"

using namespace std;

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
