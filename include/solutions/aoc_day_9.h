#include <cstdint>
#include <fstream>

#include "aoc_days.h"

#ifndef __AOC_DAY_9__
#define __AOC_DAY_9__

class Matrix final
{
public:
    using value_type = uint8_t;
    using size_type = size_t;
    using reference = value_type &;
    using const_reference = const value_type &;

    const size_type rows, cols;

    Matrix(size_type rows, size_type cols);

    reference operator()(size_type row, size_type col);
    const_reference operator()(size_type row, size_type col) const;

    bool is_low_point(size_type row, size_type col) const;
#ifdef DEBUG_OTHER
    friend std::ostream &operator<<(std::ostream &out, Matrix &curr);
#endif
private:
    std::vector<value_type> arr;
};

#ifdef DEBUG_OTHER
std::ostream &operator<<(std::ostream &out, Matrix &curr);
#endif

class AocDay9 : public AocDay
{
public:
    AocDay9();
    ~AocDay9() = default;
    std::string part1(std::string &filename, std::vector<std::string> &extra_args) override;
};

#endif
