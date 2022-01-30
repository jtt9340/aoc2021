#include <array>
#include <map>

#include "aoc_days.h"

#ifndef __AOC_DAY_5__
#define __AOC_DAY_5__

using VentCoordinate = array<int, 2>;
constexpr VentCoordinate::size_type x{0};
constexpr VentCoordinate::size_type y{1};

struct VentCoordinateComparator
{
	bool operator()(const VentCoordinate &lhs, const VentCoordinate &rhs) const;
};

using Diagram = map<VentCoordinate, unsigned int, VentCoordinateComparator>;

class AocDay5 : public AocDay
{
public:
	AocDay5();
	~AocDay5();
	string part1(string &filename, vector<string> &extra_args) override;
};

#endif
