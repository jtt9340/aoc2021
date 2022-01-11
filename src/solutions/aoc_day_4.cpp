#include <algorithm>
#include <numeric>
#include <iostream>
#include <sstream>

#include "aoc_day_4.h"

using namespace std;

// Needed because std::bitset<N>::operator & takes its second operand by reference
// See https://stackoverflow.com/a/51167258
constexpr BingoBoard::board_mask BingoBoard::bitset_mask;

BingoBoard::BingoBoard()
{
	fill(board.begin(), board.end(), 0);
}

BingoBoard::reference BingoBoard::operator()(BingoBoard::size_type row, BingoBoard::size_type col)
{
	return board.at(BingoBoard::cols * row + col);
}

BingoBoard::const_reference BingoBoard::operator()(BingoBoard::size_type row, BingoBoard::size_type col) const
{
	return board.at(BingoBoard::cols * row + col);
}

bool BingoBoard::mark(BingoBoard::value_type num)
{
	for (auto i = 0; i < BingoBoard::rows; i++)
	{
		for (auto j = 0; j < BingoBoard::cols; j++)
		{
			if ((*this)(i, j) == num)
			{
				assert(!is_marked(i, j));
				marked.set(BingoBoard::cols * i + j);
				return true;
			}
		}
	}

	return false;
}

inline bool BingoBoard::is_marked(BingoBoard::size_type row, BingoBoard::size_type col) const
{
	return marked.test(BingoBoard::rows * row + col);
}

bool BingoBoard::won_rows() const
{
	for (size_t row = 0; row < BingoBoard::rows; row++)
		if (((marked << (row * BingoBoard::cols)) & BingoBoard::bitset_mask) == BingoBoard::bitset_mask)
			return true;

	return false;
}

bool BingoBoard::won_cols() const
{
	// Transpose marked and use same technique that is used in won_rows
	BingoBoard::board_mask transpose;
	for (auto j = 0; j < BingoBoard::cols; j++)
	{
		for (auto i = 0; i < BingoBoard::rows; i++)
		{
			transpose.set(BingoBoard::cols * j + i, is_marked(i, j));
		}
	}

	for (size_t row = 0; row < BingoBoard::rows; row++)
		if (((transpose << (row * BingoBoard::cols)) & BingoBoard::bitset_mask) == BingoBoard::bitset_mask)
			return true;

	return false;
}

bool BingoBoard::won() const
{
	return won_rows() || won_cols();
}

BingoBoard::value_type BingoBoard::score(BingoBoard::value_type winning_number) const
{
	BingoBoard::value_type unmarked_sum{0};

	for (auto i = 0; i < BingoBoard::rows; i++)
		for (auto j = 0; j < BingoBoard::rows; j++)
			if (!is_marked(i, j))
				unmarked_sum += (*this)(i, j);

	return unmarked_sum * winning_number;
}

ostream &operator<<(ostream &out, BingoBoard &curr)
{
	array<BingoBoard::value_type, BingoBoard::rows * BingoBoard::cols> digit_counts;
	transform(curr.board.cbegin(), curr.board.cend(), digit_counts.begin(),
			[](BingoBoard::value_type value) -> BingoBoard::value_type {
				BingoBoard::value_type count{0};
				while (value != 0)
				{
					value /= 10;
					++count;
				}
				return count;
			});
	const auto largest_digit_count{*max_element(digit_counts.begin(), digit_counts.end())};
	const auto old_width{out.width()};
	for (auto i = 0; i < BingoBoard::rows; i++)
	{
		for (auto j = 0; j < BingoBoard::cols; j++)
		{
			out << (curr.is_marked(i, j) ? '*' : ' ');
			out << setw(largest_digit_count);
			out << curr(i, j);
			out << setw(old_width);
			if (j < BingoBoard::cols - 1) out << ' ';
		}
		out << '\n';
	}
	return out;
}

istream &operator>>(istream &in, BingoBoard &curr)
{
	for (auto i = 0; i < BingoBoard::rows; i++)
	{
		for (auto j = 0; j < BingoBoard::cols; j++)
		{
			BingoBoard::value_type number;
			in >> number;
			curr(i, j) = number;
		}
	}

	return in;
}

void BingoGame::mark(BingoBoard::value_type val)
{
	for_each(begin(), end(), [val](BingoBoard &board){ board.mark(val); });
}

BingoGame::iterator BingoGame::begin()
{
	return boards.begin();
}

BingoGame::const_iterator BingoGame::cbegin() const
{
	return boards.cbegin();
}

BingoGame::iterator BingoGame::end()
{
	return boards.end();
}

BingoGame::const_iterator BingoGame::cend() const
{
	return boards.cend();
}

BingoGame::const_iterator BingoGame::winning_board() const
{
	return find_if(cbegin(), cend(), [](const BingoBoard &b){ return b.won(); });
}

// template <class InputIt>
// BingoBoard::value_type BingoGame::play(InputIt first, InputIt last)
BingoBoard::value_type BingoGame::play(const vector<BingoBoard::value_type> &numbers)
{
	// for (auto it = first; first != last; first++)
	for (auto &num : numbers)
	{
#ifdef DEBUG_OTHER
		// cout << "Called " << *it << '\n'
		cout << "Called " << num << '\n'
		     << *this << "\n=====================\n\n";
#endif
		// mark(*it);
		mark(num);
		const auto won = winning_board();
		if (won != cend())
		{
			// return won->score(*it);
			return won->score(num);
		}
	}

	return -1; // Intentionally wraps around to large number
}

BingoBoard::value_type BingoGame::play_until_end(const vector<BingoBoard::value_type> &numbers)
{
	BingoBoard::value_type score = -1; // Intentionally wraps around to large number
	for (auto &num : numbers)
	{
#ifdef DEBUG_OTHER
		cout << "Called " << num << '\n'
		     << *this << "\n=====================\n\n";
#endif
		mark(num);
		for (auto board = begin(); board != end();)
		{
			if (board->won())
			{
				score = board->score(num);
				board = boards.erase(board);
			}
			else
			{
				board++;
			}
		}
	}

	return score;
}

ostream &operator<<(ostream &out, BingoGame &curr)
{
	for (auto it = curr.boards.begin(); it != curr.boards.end(); it++)
	{
		out << *it;
		if (it != curr.boards.cend() - 1) out << "\n\n";
	}
	return out;
}

istream &operator>>(istream &in, BingoGame &curr)
{
	for (BingoBoard board; in >> board;)
		curr.boards.push_back(board);

	return in;
}

AocDay4::AocDay4():AocDay(4)
{
}

AocDay4::~AocDay4()
{
}

string AocDay4::part1(string filename, vector<string> extra_args)
{
#ifdef DEBUG_OTHER
	cout << "Hello Day 4 Part 1" << endl;
#endif
	ifstream input{filename};
	string numbers_s;
	vector<BingoBoard::value_type> bingo_numbers;

	getline(input, numbers_s);
#ifdef DEBUG_OTHER
	cout << "Read in " << numbers_s << endl;
#endif
	string::size_type pos = 0;
	for (;;)
	{
		const auto comma_index = numbers_s.find(',', pos);
		if (comma_index == string::npos)
			break;
		bingo_numbers.push_back(stoi(numbers_s.substr(pos, comma_index)));
#ifdef DEBUG_OTHER
		cout << "Bingo number " << bingo_numbers.back() << " (pos is " << pos << ')' << endl;
#endif
		pos = comma_index + 1;
	}

	BingoGame game;
	input >> game;
	// return to_string(game.play(bingo_numbers.begin(), bingo_numbers.end()));
	return to_string(game.play(bingo_numbers));
}

string AocDay4::part2(string filename, vector<string> extra_args)
{
	ifstream input{filename};
	string numbers_s;
	vector<BingoBoard::value_type> bingo_numbers;

	getline(input, numbers_s);
#ifdef DEBUG_OTHER
	cout << "Read in " << numbers_s << endl;
#endif
	string::size_type pos = 0;
	for (;;)
	{
		const auto comma_index = numbers_s.find(',', pos);
		if (comma_index == string::npos)
			break;
		bingo_numbers.push_back(stoi(numbers_s.substr(pos, comma_index)));
#ifdef DEBUG_OTHER
		cout << "Bingo number " << bingo_numbers.back() << " (pos is " << pos << ')' << endl;
#endif
		pos = comma_index + 1;
	}

	BingoGame game;
	input >> game;
	return to_string(game.play_until_end(bingo_numbers));
}
