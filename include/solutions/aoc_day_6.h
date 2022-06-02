#include "aoc_days.h"

#ifndef __AOC_DAY_6__
#define __AOC_DAY_6__

constexpr size_t NUM_DAYS = 80;

class AocDay6 : public AocDay {
public:
	AocDay6();
	~AocDay6();
	string part1(string &filename, vector<string> &extra_args) override;
};

#endif
