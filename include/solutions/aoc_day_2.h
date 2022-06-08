#include <memory>

#ifndef __AOC_DAY_2__
#define __AOC_DAY_2__

#include "aoc_day.h"

struct SubmarineCoordinate
{
    unsigned horizontal_pos{0}, depth{0}, aim{0};
};

struct Instruction
{
    unsigned magnitude;

    explicit Instruction(unsigned magnitude);

    virtual const SubmarineCoordinate operator()(const SubmarineCoordinate coordinate) const;
};

struct SimpleInstruction : Instruction
{
    explicit SimpleInstruction(unsigned magnitude);

    static std::unique_ptr<SimpleInstruction> parse(const std::string &line);
};

struct SimpleForward : public SimpleInstruction
{
    explicit SimpleForward(unsigned magnitude);

    const SubmarineCoordinate operator()(const SubmarineCoordinate coordinate) const override;
};

struct SimpleDown : public SimpleInstruction
{
    explicit SimpleDown(unsigned magnitude);

    const SubmarineCoordinate operator()(const SubmarineCoordinate coordinate) const override;
};

struct SimpleUp : public SimpleInstruction
{
    explicit SimpleUp(unsigned magnitude);

    const SubmarineCoordinate operator()(const SubmarineCoordinate coordinate) const override;
};

struct AimingInstruction : Instruction
{
    explicit AimingInstruction(unsigned magnitude);

    static std::unique_ptr<AimingInstruction> parse(const std::string &line);
};

struct AimingForward : public AimingInstruction
{
    explicit AimingForward(unsigned magnitude);

    const SubmarineCoordinate operator()(const SubmarineCoordinate coordinate) const override;
};

struct AimingDown : public AimingInstruction
{
    explicit AimingDown(unsigned magnitude);

    const SubmarineCoordinate operator()(const SubmarineCoordinate coordinate) const override;
};

struct AimingUp : public AimingInstruction
{
    explicit AimingUp(unsigned magnitude);

    const SubmarineCoordinate operator()(const SubmarineCoordinate coordinate) const override;
};

class AocDay2 : public AocDay
{
public:
    AocDay2();
    ~AocDay2();
    std::string part1(std::string &filename, std::vector<std::string> &extra_args) override;
    std::string part2(std::string &filename, std::vector<std::string> &extra_args) override;
};

#endif
