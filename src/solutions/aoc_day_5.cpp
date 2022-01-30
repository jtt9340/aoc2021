#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include "aoc_day_5.h"

using namespace std;

static int next_coordinate(istringstream &iss)
{
#ifdef DEBUG_OTHER
	cout << "Parsing: \"" << iss.str() << '"' << endl;
#endif
	string coordinate_s;

	// Advance to first digit
	while (!isdigit(iss.peek()))
		iss.seekg(1, istringstream::cur);
	
	// Read the number until we find a non-digit character
	char next_char;
	while (isdigit(next_char = iss.get()))
		coordinate_s += next_char;

#ifdef DEBUG_OTHER
	cout << "coordinate: \"" << coordinate_s << '"' << endl;
#endif
	return stoi(coordinate_s);
}

static void mark_diagram(Diagram &diagram, VentCoordinate::value_type x1,
		VentCoordinate::value_type y1, VentCoordinate::value_type x2, VentCoordinate::value_type y2)
{
	assert(x1 == x2 || y1 == y2);
	if (y1 == y2)
	{
		for (VentCoordinate::value_type x = min(x1, x2); x <= max(x1, x2); x++)
			diagram[{x, y1}]++;
	}
	else
	{
		for (VentCoordinate::value_type y = min(y1, y2); y <= max(y1, y2); y++)
			diagram[{x1, y}]++;
	}
}

static void print_diagram(const Diagram &diagram)
{
	VentCoordinate::value_type max_x{0}, max_y{0};

	for (const auto &coordinate_count_pair : diagram)
	{
		const auto coordinate{coordinate_count_pair.first};
		if (coordinate[x] > max_x)
			max_x = coordinate[x];
		if (coordinate[y] > max_y)
			max_y = coordinate[y];
	}

	for (VentCoordinate::value_type row = 0; row <= max_y; row++)
	{
		for (VentCoordinate::value_type col = 0; col <= max_x; col++)
		{
			const auto coordinate = diagram.find({col, row});
			if (coordinate == cend(diagram))
				cout << '.';
			else
				cout << coordinate->second;
		}
		cout << '\n';
	}
	cout << endl;
}

bool VentCoordinateComparator::operator()(const VentCoordinate &lhs, const VentCoordinate &rhs) const
{
	return lhs[x] == rhs[x] ? lhs[y] < rhs[y] : lhs[x] < rhs[x];
}

AocDay5::AocDay5():AocDay(5)
{
}

AocDay5::~AocDay5()
{
}

string AocDay5::part1(string &filename, vector<string> &extra_args)
{
	ifstream input{filename};
	string line_s;
	Diagram overlaps;
	Diagram::mapped_type count{0};

	while (getline(input, line_s))
	{
		istringstream iss{line_s};
		VentCoordinate::value_type x1, y1, x2, y2;
		x1 = next_coordinate(iss);
		y1 = next_coordinate(iss);
		x2 = next_coordinate(iss);
		y2 = next_coordinate(iss);
#ifdef DEBUG_OTHER
		cout << x1 << ',' << y1 << " -> " << x2 << ',' << y2 << endl;
#endif
		if (x1 == x2 || y1 == y2)
			mark_diagram(overlaps, x1, y1, x2, y2);
	}

#ifdef DEBUG_OTHER
	print_diagram(overlaps);
#endif

	for (auto &crossing : overlaps)
		if (crossing.second >= 2)
			count++;

	return to_string(count);
}
