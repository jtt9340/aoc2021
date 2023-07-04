#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>

#include "aoc_day_4.h"

// Needed because std::bitset<N>::operator & takes its second operand by reference
// See https://stackoverflow.com/a/51167258
constexpr BingoBoard::board_mask BingoBoard::bitset_mask;

BingoBoard::BingoBoard()
{
    std::fill(std::begin(board), std::end(board), 0);
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

std::ostream &operator<<(std::ostream &out, BingoBoard &curr)
{
    std::array<BingoBoard::value_type, BingoBoard::rows * BingoBoard::cols> digit_counts;
    std::transform(std::cbegin(curr.board),
                   std::cend(curr.board),
                   std::begin(digit_counts),
                   [](BingoBoard::value_type value) -> BingoBoard::value_type {
                       BingoBoard::value_type count{0};
                       while (value != 0)
                       {
                           value /= 10;
                           ++count;
                       }
                       return count;
                   });
    const auto largest_digit_count{*std::max_element(std::begin(digit_counts), std::end(digit_counts))};
    const auto old_width{out.width()};
    for (auto i = 0; i < BingoBoard::rows; i++)
    {
        for (auto j = 0; j < BingoBoard::cols; j++)
        {
            out << (curr.is_marked(i, j) ? '*' : ' ');
            out << std::setw(largest_digit_count);
            out << curr(i, j);
            out << std::setw(old_width);
            if (j < BingoBoard::cols - 1)
                out << ' ';
        }
        out << '\n';
    }
    return out;
}

std::istream &operator>>(std::istream &in, BingoBoard &curr)
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
    std::for_each(begin(), end(), [val](BingoBoard &board) { board.mark(val); });
}

BingoGame::iterator BingoGame::begin()
{
    return std::begin(boards);
}

BingoGame::const_iterator BingoGame::cbegin() const
{
    return std::cbegin(boards);
}

BingoGame::iterator BingoGame::end()
{
    return std::end(boards);
}

BingoGame::const_iterator BingoGame::cend() const
{
    return std::cend(boards);
}

BingoGame::const_iterator BingoGame::winning_board() const
{
    return std::find_if(cbegin(), cend(), [](const BingoBoard &b) { return b.won(); });
}

// template <class InputIt>
// BingoBoard::value_type BingoGame::play(InputIt first, InputIt last)
BingoBoard::value_type BingoGame::play(const std::vector<BingoBoard::value_type> &numbers)
{
    // for (auto it = first; first != last; first++)
    for (auto &num : numbers)
    {
#ifdef DEBUG_OTHER
        // cout << "Called " << *it << '\n'
        std::cout << "Called " << num << '\n' << *this << "\n=====================\n\n";
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

BingoBoard::value_type BingoGame::play_until_end(const std::vector<BingoBoard::value_type> &numbers)
{
    BingoBoard::value_type score = -1; // Intentionally wraps around to large number
    for (auto &num : numbers)
    {
#ifdef DEBUG_OTHER
        std::cout << "Called " << num << '\n' << *this << "\n=====================\n\n";
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

std::ostream &operator<<(std::ostream &out, BingoGame &curr)
{
    for (auto it = std::begin(curr.boards); it != std::end(curr.boards); it++)
    {
        out << *it;
        if (it != curr.boards.cend() - 1)
            out << "\n\n";
    }
    return out;
}

std::istream &operator>>(std::istream &in, BingoGame &curr)
{
    for (BingoBoard board; in >> board;)
        curr.boards.push_back(board);

    return in;
}

AocDay4::AocDay4() : AocDay(4)
{
}

AocDay4::~AocDay4()
{
}

std::string AocDay4::part1(std::string &filename, std::vector<std::string> &extra_args)
{
#ifdef DEBUG_OTHER
    std::cout << "Hello Day 4 Part 1" << std::endl;
#endif
    std::ifstream input{filename};
    std::string numbers_s;
    std::vector<BingoBoard::value_type> bingo_numbers;

    std::getline(input, numbers_s);
#ifdef DEBUG_OTHER
    std::cout << "Read in " << numbers_s << std::endl;
#endif
    std::string::size_type pos = 0;
    for (;;)
    {
        const auto comma_index = numbers_s.find(',', pos);
        if (comma_index == std::string::npos)
            break;
        bingo_numbers.push_back(std::stoi(numbers_s.substr(pos, comma_index)));
#ifdef DEBUG_OTHER
        std::cout << "Bingo number " << bingo_numbers.back() << " (pos is " << pos << ')' << std::endl;
#endif
        pos = comma_index + 1;
    }

    BingoGame game;
    input >> game;
    // return to_string(game.play(bingo_numbers.begin(), bingo_numbers.end()));
    return std::to_string(game.play(bingo_numbers));
}

std::string AocDay4::part2(std::string &filename, std::vector<std::string> &extra_args)
{
    std::ifstream input{filename};
    std::string numbers_s;
    std::vector<BingoBoard::value_type> bingo_numbers;

    std::getline(input, numbers_s);
#ifdef DEBUG_OTHER
    std::cout << "Read in " << numbers_s << std::endl;
#endif
    std::string::size_type pos = 0;
    for (;;)
    {
        const auto comma_index = numbers_s.find(',', pos);
        if (comma_index == std::string::npos)
            break;
        bingo_numbers.push_back(std::stoi(numbers_s.substr(pos, comma_index)));
#ifdef DEBUG_OTHER
        std::cout << "Bingo number " << bingo_numbers.back() << " (pos is " << pos << ')' << std::endl;
#endif
        pos = comma_index + 1;
    }

    BingoGame game;
    input >> game;
    return std::to_string(game.play_until_end(bingo_numbers));
}
