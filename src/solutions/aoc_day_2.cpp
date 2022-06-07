#include <iostream>
#include <fstream>

#include "aoc_day_2.h"

template <class T>
static std::string run_submarine_program(std::string &filename, std::vector<std::string> &extra_args)
{
	SubmarineCoordinate pos;
	std::ifstream input{filename};
	if (!input)
	{
		std::cerr << filename << " not found" << std::endl;
		return "";
	}

	std::string instruction_s;
	while (std::getline(input, instruction_s))
	{
		const auto instruction = T::parse(instruction_s);
		if (!instruction)
		{
			std::cerr << "Unrecognized instruction " << instruction_s << std::endl;
			return "";
		}

		pos = (*instruction)(pos);
	}

	if (input.bad())
		std::cerr << "Error reading in the data from " << filename << std::endl;

	input.close();
	return std::to_string(pos.horizontal_pos * pos.depth);
}

Instruction::Instruction(unsigned magnitude):magnitude(magnitude)
{
}

const SubmarineCoordinate Instruction::operator()(const SubmarineCoordinate coordinate) const
{
	return coordinate;
}

SimpleInstruction::SimpleInstruction(unsigned magnitude):Instruction(magnitude)
{
}

std::unique_ptr<SimpleInstruction> SimpleInstruction::parse(const std::string &line)
{
	const auto space_index = line.find(' ');
	const auto cmd = line.substr(0, space_index);
	const auto mag_s = line.substr(space_index + 1);
	const auto mag = stoul(mag_s);

	if (cmd == "forward")
		return std::make_unique<SimpleForward>(mag);
	else if (cmd == "down")
		return std::make_unique<SimpleDown>(mag);
	else if (cmd == "up")
		return std::make_unique<SimpleUp>(mag);
	else
	{
		std::cerr << "Unrecognized instruction \"" << line << '"' << std::endl;
		return nullptr;
	}
}

AimingInstruction::AimingInstruction(unsigned magnitude):Instruction(magnitude)
{
}

std::unique_ptr<AimingInstruction> AimingInstruction::parse(const std::string &line)
{
	// Is there a way to make this more DRY so I am not literally copying the
	// code from SimpleInstruction::parse? Using templates perhaps?
	const auto space_index = line.find(' ');
	const auto cmd = line.substr(0, space_index);
	const auto mag_s = line.substr(space_index + 1);
	const auto mag = stoul(mag_s);

	if (cmd == "forward")
		return std::make_unique<AimingForward>(mag);
	else if (cmd == "down")
		return std::make_unique<AimingDown>(mag);
	else if (cmd == "up")
		return std::make_unique<AimingUp>(mag);
	else
	{
		std::cerr << "Unrecognized instruction \"" << line << '"' << std::endl;
		return nullptr;
	}
}

SimpleForward::SimpleForward(unsigned magnitude):SimpleInstruction(magnitude)
{
}

const SubmarineCoordinate SimpleForward::operator()(const SubmarineCoordinate coordinate) const
{
	SubmarineCoordinate new_coordinate{coordinate};
	new_coordinate.horizontal_pos += magnitude;
	return new_coordinate;
}

SimpleDown::SimpleDown(unsigned magnitude):SimpleInstruction(magnitude)
{
}

const SubmarineCoordinate SimpleDown::operator()(const SubmarineCoordinate coordinate) const
{
	SubmarineCoordinate new_coordinate{coordinate};
	new_coordinate.depth += magnitude;
	return new_coordinate;
}

SimpleUp::SimpleUp(unsigned magnitude):SimpleInstruction(magnitude)
{
}

const SubmarineCoordinate SimpleUp::operator()(const SubmarineCoordinate coordinate) const
{
	SubmarineCoordinate new_coordinate{coordinate};
	new_coordinate.depth -= magnitude;
	return new_coordinate;
}

AimingForward::AimingForward(unsigned magnitude):AimingInstruction(magnitude)
{
}

const SubmarineCoordinate AimingForward::operator()(const SubmarineCoordinate coordinate) const
{
	SubmarineCoordinate new_coordinate{coordinate};
	new_coordinate.horizontal_pos += magnitude;
	new_coordinate.depth += coordinate.aim * magnitude;
	return new_coordinate;
}

AimingDown::AimingDown(unsigned magnitude):AimingInstruction(magnitude)
{
}

const SubmarineCoordinate AimingDown::operator()(const SubmarineCoordinate coordinate) const
{
	SubmarineCoordinate new_coordinate{coordinate};
	new_coordinate.aim += magnitude;
	return new_coordinate;
}

AimingUp::AimingUp(unsigned magnitude):AimingInstruction(magnitude)
{
}

const SubmarineCoordinate AimingUp::operator()(const SubmarineCoordinate coordinate) const
{
	SubmarineCoordinate new_coordinate{coordinate};
	new_coordinate.aim -= magnitude;
	return new_coordinate;
}

AocDay2::AocDay2():AocDay(2)
{
}

AocDay2::~AocDay2()
{
}

std::string AocDay2::part1(std::string &filename, std::vector<std::string> &extra_args)
{
	return run_submarine_program<SimpleInstruction>(filename, extra_args);
}

std::string AocDay2::part2(std::string &filename, std::vector<std::string> &extra_args)
{
	return run_submarine_program<AimingInstruction>(filename, extra_args);
}
