#include <memory>

#ifndef __AOC_DAY_2__
#define __AOC_DAY_2__

#include "aoc_day.h"

struct Coordinate
{
	unsigned horizontal_pos{0}, depth{0}, aim{0};
};

struct Instruction
{
	unsigned magnitude;

	explicit Instruction(unsigned magnitude);

	virtual const Coordinate operator()(const Coordinate coordinate) const;
};

struct SimpleInstruction : Instruction
{
	explicit SimpleInstruction(unsigned magnitude);

	static unique_ptr<SimpleInstruction> parse(const string &line);
};

struct SimpleForward : public SimpleInstruction
{
	explicit SimpleForward(unsigned magnitude);

	const Coordinate operator()(const Coordinate coordinate) const override;
};

struct SimpleDown : public SimpleInstruction
{
	explicit SimpleDown(unsigned magnitude);

	const Coordinate operator()(const Coordinate coordinate) const override;
};

struct SimpleUp : public SimpleInstruction
{
	explicit SimpleUp(unsigned magnitude);

	const Coordinate operator()(const Coordinate coordinate) const override;
};

struct AimingInstruction : Instruction
{
	explicit AimingInstruction(unsigned magnitude);

	static unique_ptr<AimingInstruction> parse(const string &line);
};

struct AimingForward : public AimingInstruction
{
	explicit AimingForward(unsigned magnitude);

	const Coordinate operator()(const Coordinate coordinate) const override;
};

struct AimingDown : public AimingInstruction
{
	explicit AimingDown(unsigned magnitude);

	const Coordinate operator()(const Coordinate coordinate) const override;
};

struct AimingUp : public AimingInstruction
{
	explicit AimingUp(unsigned magnitude);

	const Coordinate operator()(const Coordinate coordinate) const override;
};

class AocDay2 : public AocDay
{
	public:
		AocDay2();
		~AocDay2();
		string part1(string filename, vector<string> extra_args) override;
		string part2(string filename, vector<string> extra_args) override;
};

#endif
