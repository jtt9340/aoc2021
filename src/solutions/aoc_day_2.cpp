#include <iostream>
#include <fstream>

#include "aoc_day_2.h"

using namespace std;

Instruction::Instruction(Coordinate::value_type magnitude):magnitude(magnitude)
{
}

Coordinate Instruction::operator()(Coordinate coordinate)
{
	return coordinate;
}

unique_ptr<Instruction> Instruction::parse(string &line)
{
	const auto space_index = line.find(' ');
	const auto cmd = line.substr(0, space_index);
	const auto mag_s = line.substr(space_index + 1);
	const auto mag = stoul(mag_s);

	if (cmd == "forward")
		return make_unique<Forward>(mag);
	else if (cmd == "down")
		return make_unique<Down>(mag);
	else if (cmd == "up")
		return make_unique<Up>(mag);
	else
	{
		cerr << "Unrecognized instruction \"" << line << '"' << endl;
		return nullptr;
	}
}

Forward::Forward(Coordinate::value_type magnitude):Instruction(magnitude)
{
}

Coordinate Forward::operator()(Coordinate coordinate)
{
	return {coordinate[0] + magnitude, coordinate[1]};
}

Down::Down(Coordinate::value_type magnitude):Instruction(magnitude)
{
}

Coordinate Down::operator()(Coordinate coordinate)
{
	return {coordinate[0], coordinate[1] + magnitude};
}

Up::Up(Coordinate::value_type magnitude):Instruction(magnitude)
{
}

Coordinate Up::operator()(Coordinate coordinate)
{
	return {coordinate[0], coordinate[1] - magnitude};
}

AocDay2::AocDay2():AocDay(2)
{
}

AocDay2::~AocDay2()
{
}

string AocDay2::part1(string filename, vector<string> extra_args)
{
	Coordinate pos{{0, 0}};
	ifstream input{filename};
	if (!input)
	{
		cerr << filename << " not found" << endl;
		return "";
	}

	string instruction_s;
	while (getline(input, instruction_s))
	{
		const auto instruction = Instruction::parse(instruction_s);
		if (!instruction)
		{
			cerr << "Unrecognized instruction " << instruction_s << endl;
			return "";
		}

		pos = (*instruction)(pos);
	}

	if (input.bad())
		cerr << "Error reading in the data from " << filename << endl;

	input.close();
	return to_string(pos[0] * pos[1]);
}
