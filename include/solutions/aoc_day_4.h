#include <array>
#include <bitset>
#include <fstream>

#ifndef __AOC_DAY_4__
#define __AOC_DAY_4__

#include "aoc_days.h"

class BingoBoard
{
public:
	static constexpr size_t rows = 5;
	static constexpr size_t cols = 5;
	using value_type = unsigned;
	using size_type = size_t; 
	using reference = value_type &;
	using const_reference = const value_type &;

	BingoBoard();

	reference operator()(size_type row, size_type col);
	const_reference operator()(size_type row, size_type col) const;

	bool mark(value_type num);
	bool is_marked(size_type row, size_type col) const;

	bool won() const;

	value_type score(value_type winning_number) const;

	friend ostream &operator<<(ostream &out, BingoBoard &curr);
private:
	using board_mask = bitset<BingoBoard::rows * BingoBoard::cols>;
	static constexpr board_mask bitset_mask{0b11111 << (BingoBoard::rows - 1) * BingoBoard::cols};
	// Board has 5x5 squares
	array<BingoBoard::value_type, BingoBoard::rows * BingoBoard::cols> board;
	board_mask marked;

	bool won_rows() const;
	bool won_cols() const;
};

ostream &operator<<(ostream &out, BingoBoard &curr);
istream &operator>>(istream &in, BingoBoard &curr);

class BingoGame
{
	vector<BingoBoard> boards;
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
	BingoBoard::value_type play(const vector<BingoBoard::value_type> &numbers);
	BingoBoard::value_type play_until_end(const vector<BingoBoard::value_type> &numbers);

	friend ostream &operator<<(ostream &out, BingoGame &curr);
	friend istream &operator>>(istream &in, BingoGame &curr);
};

ostream &operator<<(ostream &out, BingoGame &curr);
istream &operator>>(istream &in, BingoGame &curr);

class AocDay4 : public AocDay
{
public:
	AocDay4();
	~AocDay4();
	string part1(string &filename, vector<string> &extra_args) override;
	string part2(string &filename, vector<string> &extra_args) override;
};

#endif
