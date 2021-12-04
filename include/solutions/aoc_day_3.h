#include "aoc_days.h"

#ifndef __AOC_DAY_3__
#define __AOC_DAY_3__

class AocDay3 : public AocDay
{
	public:
		AocDay3();
		~AocDay3();
		string part1(string filename, vector<string> extra_args) override;
};

#endif
