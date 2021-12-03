#include <iostream>
#include <fstream>

#include "aoc_day_2.h"

using namespace std;

template <class T>
static string run_submarine_program(string &filename, vector<string> &extra_args)
{
	Coordinate pos;
	ifstream input{filename};
	if (!input)
	{
		cerr << filename << " not found" << endl;
		return "";
	}

	string instruction_s;
	while (getline(input, instruction_s))
	{
		const auto instruction = T::parse(instruction_s);
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
	return to_string(pos.horizontal_pos * pos.depth);
}

Instruction::Instruction(unsigned magnitude):magnitude(magnitude)
{
}

const Coordinate Instruction::operator()(const Coordinate coordinate) const
{
	return coordinate;
}

SimpleInstruction::SimpleInstruction(unsigned magnitude):Instruction(magnitude)
{
}

unique_ptr<SimpleInstruction> SimpleInstruction::parse(const string &line)
{
	const auto space_index = line.find(' ');
	const auto cmd = line.substr(0, space_index);
	const auto mag_s = line.substr(space_index + 1);
	const auto mag = stoul(mag_s);

	if (cmd == "forward")
		return make_unique<SimpleForward>(mag);
	else if (cmd == "down")
		return make_unique<SimpleDown>(mag);
	else if (cmd == "up")
		return make_unique<SimpleUp>(mag);
	else
	{
		cerr << "Unrecognized instruction \"" << line << '"' << endl;
		return nullptr;
	}
}

AimingInstruction::AimingInstruction(unsigned magnitude):Instruction(magnitude)
{
}

unique_ptr<AimingInstruction> AimingInstruction::parse(const string &line)
{
	// Is there a way to make this more DRY so I am not literally copying the
	// code from SimpleInstruction::parse? Using templates perhaps?
	const auto space_index = line.find(' ');
	const auto cmd = line.substr(0, space_index);
	const auto mag_s = line.substr(space_index + 1);
	const auto mag = stoul(mag_s);

	if (cmd == "forward")
		return make_unique<AimingForward>(mag);
	else if (cmd == "down")
		return make_unique<AimingDown>(mag);
	else if (cmd == "up")
		return make_unique<AimingUp>(mag);
	else
	{
		cerr << "Unrecognized instruction \"" << line << '"' << endl;
		return nullptr;
	}
}

SimpleForward::SimpleForward(unsigned magnitude):SimpleInstruction(magnitude)
{
}

const Coordinate SimpleForward::operator()(const Coordinate coordinate) const
{
	Coordinate new_coordinate{coordinate};
	new_coordinate.horizontal_pos += magnitude;
	return new_coordinate;
}

SimpleDown::SimpleDown(unsigned magnitude):SimpleInstruction(magnitude)
{
}

const Coordinate SimpleDown::operator()(const Coordinate coordinate) const
{
	Coordinate new_coordinate{coordinate};
	new_coordinate.depth += magnitude;
	return new_coordinate;
}

SimpleUp::SimpleUp(unsigned magnitude):SimpleInstruction(magnitude)
{
}

const Coordinate SimpleUp::operator()(const Coordinate coordinate) const
{
	Coordinate new_coordinate{coordinate};
	new_coordinate.depth -= magnitude;
	return new_coordinate;
}

AimingForward::AimingForward(unsigned magnitude):AimingInstruction(magnitude)
{
}

const Coordinate AimingForward::operator()(const Coordinate coordinate) const
{
	Coordinate new_coordinate{coordinate};
	new_coordinate.horizontal_pos += magnitude;
	new_coordinate.depth += coordinate.aim * magnitude;
	return new_coordinate;
}

AimingDown::AimingDown(unsigned magnitude):AimingInstruction(magnitude)
{
}

const Coordinate AimingDown::operator()(const Coordinate coordinate) const
{
	Coordinate new_coordinate{coordinate};
	new_coordinate.aim += magnitude;
	return new_coordinate;
}

AimingUp::AimingUp(unsigned magnitude):AimingInstruction(magnitude)
{
}

const Coordinate AimingUp::operator()(const Coordinate coordinate) const
{
	Coordinate new_coordinate{coordinate};
	new_coordinate.aim -= magnitude;
	return new_coordinate;
}

AocDay2::AocDay2():AocDay(2)
{
}

AocDay2::~AocDay2()
{
}

string AocDay2::part1(string filename, vector<string> extra_args)
{
	return run_submarine_program<SimpleInstruction>(filename, extra_args);
}

string AocDay2::part2(string filename, vector<string> extra_args)
{
	return run_submarine_program<AimingInstruction>(filename, extra_args);
}
