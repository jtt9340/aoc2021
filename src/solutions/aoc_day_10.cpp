#include <algorithm>
#include <iostream>
#include <stack>

#include "aoc_day_10.h"
#include "file_utils.h"

enum class Bracket : unsigned int
{
    Round = 3,
    Square = 57,
    Curly = 1197,
    Pointy = 25137,
};

static unsigned long int get_completion_score(std::stack<Bracket> &brackets)
{
    unsigned long int score = 0;

    for (; brackets.size() > 0; brackets.pop())
    {
        score *= 5;
        switch (brackets.top())
        {
        case Bracket::Pointy:
            score++;
        case Bracket::Curly:
            score++;
        case Bracket::Square:
            score++;
        case Bracket::Round:
            score++;
        }
    }

    return score;
}

static bool is_corrupted(const std::string &line, unsigned long int &found)
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
            if (top_bracket == Bracket::Round)
            {
                brackets.pop();
            }
            else
            {
                found = static_cast<unsigned long int>(Bracket::Round);
                return true;
            }
            break;
        case ']':
            top_bracket = brackets.top();
            if (top_bracket == Bracket::Square)
            {
                brackets.pop();
            }
            else
            {
                found = static_cast<unsigned long int>(Bracket::Square);
                return true;
            }
            break;
        case '}':
            top_bracket = brackets.top();
            if (top_bracket == Bracket::Curly)
            {
                brackets.pop();
            }
            else
            {
                found = static_cast<unsigned long int>(Bracket::Curly);
                return true;
            }
            break;
        case '>':
            top_bracket = brackets.top();
            if (top_bracket == Bracket::Pointy)
            {
                brackets.pop();
            }
            else
            {
                found = static_cast<unsigned long int>(Bracket::Pointy);
                return true;
            }
        }
    }

    found = get_completion_score(brackets);
    return false;
}

template <class It>
static unsigned int get_corrupted_score(It begin, It end)
{
    unsigned int score = 0;
    unsigned long int found;

    for (auto it = begin; it != end; it++)
        if (is_corrupted(*it, found))
            score += found;

    return score;
}

template <class It>
static unsigned long int get_incomplete_score(It begin, It end, std::size_t size_hint)
{
    std::vector<unsigned long int> scores;
    unsigned long int score;

    scores.reserve(size_hint);

    for (auto it = begin; it != end; it++)
        if (!is_corrupted(*it, score))
            scores.push_back(score);

    std::sort(std::begin(scores), std::end(scores));
    return scores.at(scores.size() / 2);
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

    const auto score = get_corrupted_score(std::cbegin(lines), std::cend(lines));
    return std::to_string(score);
}

std::string AocDay10::part2(std::string &filename, std::vector<std::string> &extra_args)
{
    FileUtils fileutils;
    std::vector<std::string> lines;
    if (!fileutils.read_as_list_of_strings(filename, lines))
    {
        std::cerr << "Error reading in the data from " << filename << std::endl;
        return {};
    }

    const auto score = get_incomplete_score(std::cbegin(lines), std::cend(lines), lines.size());
    return std::to_string(score);
}
