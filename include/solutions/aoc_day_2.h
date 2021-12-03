#include <array>
#include <memory>

#ifndef __AOC_DAY_2__
#define __AOC_DAY_2__

#include "aoc_day.h"

using Coordinate = array<unsigned, 2>;

struct Instruction
{
	Coordinate::value_type magnitude;

	explicit Instruction(Coordinate::value_type magnitude);

	virtual Coordinate operator()(Coordinate coordinate);

	static unique_ptr<Instruction> parse(string &line);
};

struct Forward : public Instruction
{
	explicit Forward(Coordinate::value_type magnitude);

	Coordinate operator()(Coordinate coordinate) override;
};

struct Down : public Instruction
{
	explicit Down(Coordinate::value_type magnitude);

	Coordinate operator()(Coordinate coordinate) override;
};

struct Up : public Instruction
{
	explicit Up(Coordinate::value_type magnitude);

	Coordinate operator()(Coordinate coordinate) override;
};

class AocDay2 : public AocDay
{
	private:
		vector<long> read_input(string filename);
	public:
		AocDay2();
		~AocDay2();
		string part1(string filename, vector<string> extra_args) override;
};

#endif
