#include <iostream>
#include <stack>

#include "aoc_day_10.h"
#include "file_utils.h"

enum class Bracket: unsigned int
{
    Round = 3,
    Square = 57,
    Curly = 1197,
    Pointy = 25137,
};

static bool is_corrupted(const std::string &line, Bracket &found)
{
    std::stack<Bracket> brackets;
    Bracket top_bracket;
    for (const char &c : line)
    {
        switch (c)
        {
        case '(':
            brackets.push(Bracket::Round);
            break;
        case '[':
            brackets.push(Bracket::Square);
            break;
        case '{':
            brackets.push(Bracket::Curly);
            break;
        case '<':
            brackets.push(Bracket::Pointy);
            break;
        case ')':
            top_bracket = brackets.top();
            if (top_bracket == Bracket::Round) {
                brackets.pop();
            } else {
                found = Bracket::Round;
                return true;
            }
            break;
        case ']':
            top_bracket = brackets.top();
            if (top_bracket == Bracket::Square) {
                brackets.pop();
            } else {
                found = Bracket::Square;
                return true;
            }
            break;
        case '}':
            top_bracket = brackets.top();
            if (top_bracket == Bracket::Curly) {
                brackets.pop();
            } else {
                found = Bracket::Curly;
                return true;
            }
            break;
        case '>':
            top_bracket = brackets.top();
            if (top_bracket == Bracket::Pointy) {
                brackets.pop();
            } else {
                found = Bracket::Pointy;
                return true;
            }
        }
    }

    return false;
}

template <class It>
static unsigned int get_score(It begin, It end)
{
    unsigned int score = 0;
    Bracket found;

    for (auto it = begin; it != end; it++)
        if (is_corrupted(*it, found))
            score += static_cast<unsigned int>(found);

    return score;
}

AocDay10::AocDay10() : AocDay(10)
{
}

std::string AocDay10::part1(std::string &filename, std::vector<std::string> &extra_args)
{
    FileUtils fileutils;
    std::vector<std::string> lines;
    if (!fileutils.read_as_list_of_strings(filename, lines))
    {
        std::cerr << "Error reading in the data from " << filename << std::endl;
        return {};
    }

    const auto score = get_score(std::cbegin(lines), std::cend(lines));
    return std::to_string(score);
}
