#include <array>
#include <bitset>
#include <fstream>

#include "aoc_days.h"
#include "matrix.h"

#ifndef __AOC_DAY_4__
#define __AOC_DAY_4__

class BingoBoard : public Matrix<unsigned, 5, 5>
{
public:
    bool mark(value_type num);
    bool is_marked(size_type row, size_type col) const;

    bool won() const;

    value_type score(value_type winning_number) const;

    friend std::ostream &operator<<(std::ostream &out, BingoBoard &curr);

private:
    using board_mask = std::bitset<BingoBoard::rows * BingoBoard::cols>;
    static constexpr board_mask bitset_mask{0b11111 << (BingoBoard::rows - 1) * BingoBoard::cols};
    board_mask marked;

    bool won_rows() const;
    bool won_cols() const;
};

std::ostream &operator<<(std::ostream &out, BingoBoard &curr);

class BingoGame
{
    std::vector<BingoBoard> boards;

public:
    using iterator = decltype(boards)::iterator;
    using const_iterator = decltype(boards)::const_iterator;

    void mark(BingoBoard::value_type val);

    iterator begin();
    const_iterator cbegin() const;

    iterator end();
    const_iterator cend() const;

    const_iterator winning_board() const;

    // template <class InputIt>
    // BingoBoard::value_type play(InputIt first, InputIt last);
    BingoBoard::value_type play(const std::vector<BingoBoard::value_type> &numbers);
    BingoBoard::value_type play_until_end(const std::vector<BingoBoard::value_type> &numbers);

    friend std::ostream &operator<<(std::ostream &out, BingoGame &curr);
    friend std::istream &operator>>(std::istream &in, BingoGame &curr);
};

std::ostream &operator<<(std::ostream &out, BingoGame &curr);
std::istream &operator>>(std::istream &in, BingoGame &curr);

class AocDay4 : public AocDay
{
public:
    AocDay4();
    ~AocDay4();
    std::string part1(std::string &filename, std::vector<std::string> &extra_args) override;
    std::string part2(std::string &filename, std::vector<std::string> &extra_args) override;
};

#endif
