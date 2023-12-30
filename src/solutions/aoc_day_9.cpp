#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <limits>
#include <numeric>
#include <queue>
#include <set>
#ifdef DEBUG_OTHER
#include <iostream>
#endif

#include "aoc_day_9.h"
#include "util.h"

constexpr HeightMap::value_type sentinel_height = 9;

struct coord_less
{
    bool operator()(const std::array<HeightMap::size_type, 2> &a, const std::array<HeightMap::size_type, 2> &b)
    {
        return a[0] == b[0] ? a[1] < b[1] : a[0] < b[0];
    }
};

using coord_set = std::set<std::array<HeightMap::size_type, 2>, coord_less>;

template <class It>
static uint32_t total_risk_level(It begin, It end)
{
    return std::accumulate(begin, end, 0, [](auto acc, auto elt) { return acc + elt + 1; });
}

static size_t basin_size(const HeightMap &matrix, HeightMap &seen, HeightMap::size_type row, HeightMap::size_type col)
{
    std::deque<std::array<HeightMap::size_type, 2>> open{1, {row, col}};
    coord_set closed;

    while (!open.empty())
    {
        const auto x = open.front();
        const auto row = x[0], col = x[1];
        open.pop_front();

        seen(row, col) = 1;

        // Top child
        if (row > 0)
        {
            const std::array<HeightMap::size_type, 2> top{{row - 1, col}};
            if (matrix(top) != sentinel_height && std::find(std::cbegin(open), std::cend(open), top) == std::cend(open) &&
                std::find(std::cbegin(closed), std::cend(closed), top) == std::cend(closed))
                open.push_back(std::move(top));
        }

        // Right child
        if (col < matrix.cols - 1)
        {
            const std::array<HeightMap::size_type, 2> right{{row, col + 1}};
            if (matrix(right) != sentinel_height && std::find(std::cbegin(open), std::cend(open), right) == std::cend(open) &&
                std::find(std::cbegin(closed), std::cend(closed), right) == std::cend(closed))
                open.push_back(std::move(right));
        }

        // Bottom child
        if (row < matrix.rows - 1)
        {
            const std::array<HeightMap::size_type, 2> bottom{{row + 1, col}};
            if (matrix(bottom) != sentinel_height && std::find(std::cbegin(open), std::cend(open), bottom) == std::cend(open) &&
                std::find(std::cbegin(closed), std::cend(closed), bottom) == std::cend(closed))
                open.push_back(std::move(bottom));
        }

        // Left child
        if (col > 0)
        {
            const std::array<HeightMap::size_type, 2> left{{row, col - 1}};
            if (matrix(left) != sentinel_height && std::find(std::cbegin(open), std::cend(open), left) == std::cend(open) &&
                std::find(std::cbegin(closed), std::cend(closed), left) == std::cend(closed))
                open.push_back(std::move(left));
        }

        closed.insert(std::move(x));
    }

    return closed.size();
}

static std::array<size_t, 3> basin_sizes(const HeightMap &matrix)
{
    std::priority_queue<size_t> sizes_queue;
    std::array<size_t, 3> sizes;
    HeightMap::size_type row = 0, col = 0;
    HeightMap seen{matrix.rows, matrix.cols};

    for (;;)
    {
        const auto size = basin_size(matrix, seen, row, col);
        sizes_queue.push(size);

        while (seen(row, col) || matrix(row, col) == sentinel_height)
        {
            if (row == matrix.rows - 1 && col == matrix.cols - 1)
            {
                goto done;
            }
            if (col == matrix.cols - 1)
            {
                row++;
                col = 0;
            }
            else
            {
                col++;
            }
        }
    }

done:
    for (auto it = std::begin(sizes); it != std::end(sizes); it++)
    {
        *it = sizes_queue.top();
        sizes_queue.pop();
    }
    return sizes;
}

bool HeightMap::is_low_point(HeightMap::size_type row, HeightMap::size_type col) const
{
    const HeightMap::value_type top = row == 0 ? std::numeric_limits<HeightMap::value_type>::max() : (*this)(row - 1, col);
    const HeightMap::value_type right = col == cols - 1 ? std::numeric_limits<HeightMap::value_type>::max() : (*this)(row, col + 1);
    const HeightMap::value_type bottom = row == rows - 1 ? std::numeric_limits<HeightMap::value_type>::max() : (*this)(row + 1, col);
    const HeightMap::value_type left = col == 0 ? std::numeric_limits<HeightMap::value_type>::max() : (*this)(row, col - 1);
    HeightMap::const_reference elt = (*this)(row, col);
    return elt < top && elt < right && elt < bottom && elt < left;
}

#ifdef DEBUG_OTHER
std::ostream &operator<<(std::ostream &out, HeightMap &curr)
{
    for (HeightMap::size_type i = 0; i < curr.rows; i++)
    {
        for (HeightMap::size_type j = 0; j < curr.cols; j++)
        {
            out << +curr(i, j);
            if (j != curr.cols - 1)
                out << ' ';
        }
        out << '\n';
    }
    return out;
}
#endif

AocDay9::AocDay9() : AocDay(9)
{
}

std::string AocDay9::part1(std::string &filename, std::vector<std::string> &extra_args)
{
    std::ifstream input{filename};
    std::vector<HeightMap::value_type> low_points;
    HeightMap::size_type i;

    // We want to read values from the input into a matrix, but we cannot know how big
    // to make the matrix until we've read the first row, which we will temporarily store
    // in a vector.
    std::vector<HeightMap::value_type> elts;
    // Hardcoding a pre-allocated length of 101 for the vector upfront since
    // that's how many characters are in each line of the puzzle input.
    elts.reserve(101);
    std::ifstream::int_type elt;
    while ((elt = input.get()) != '\n')
        elts.push_back(to_digit(elt));

    HeightMap matrix{3, elts.size()};
    // Transfer the first row into the matrix and read characters into the second row
    for (i = 0; i < matrix.cols; i++)
    {
        matrix(0, i) = elts[i];
        elt = input.get();
        matrix(1, i) = to_digit(elt);
    }

    // We don't need elts anymore
    elts.clear();

    // Find any low points in the first row
    for (i = 0; i < matrix.cols; i++)
        if (matrix.is_low_point(0, i))
            low_points.push_back(matrix(0, i));

    // Read in newline
    elt = input.get();
    assert(elt == '\n');

    // Keep reading from input until we hit EOF, scanning the second row,
    // then shifting rows up so that the second row always becomes the row just read
    for (;;)
    {
        for (i = 0; i < matrix.cols; i++)
        {
            elt = input.get();
            matrix(2, i) = to_digit(elt);
            if (matrix.is_low_point(1, i))
                low_points.push_back(matrix(1, i));
        }

        // Read in newline
        elt = input.get();
        assert(elt == '\n');

        // Break if there are no more rows to read
        if (input.peek() == std::ifstream::traits_type::eof())
            break;

        for (i = 0; i < matrix.cols; i++)
        {
            matrix(0, i) = matrix(1, i);
            matrix(1, i) = matrix(2, i);
        }
    }

    // Find any low points in the third row
    for (i = 0; i < matrix.cols; i++)
        if (matrix.is_low_point(2, i))
            low_points.push_back(matrix(2, i));

    const auto risk_level = total_risk_level(std::cbegin(low_points), std::cend(low_points));
    return std::to_string(risk_level);
}

std::string AocDay9::part2(std::string &filename, std::vector<std::string> &extra_args)
{
    std::ifstream input{filename};
    HeightMap::size_type row = 0, rows = 1, col = 0, cols = 0;

    // Get dimensions of matrix
    for (std::ifstream::int_type elt; (elt = input.get()) != '\n'; cols++)
        ;

    while (input)
        if (input.get() == '\n')
            rows++;

    input.clear();  // clear eof bit so that seekg can succeed
    input.seekg(0); // Rewind after calculating matrix dimensions to re-read numbers
    HeightMap matrix{rows, cols};

    for (std::ifstream::int_type elt; (elt = input.get()) != std::ifstream::traits_type::eof();)
    {
        if (elt == '\n')
        {
            row++;
            col = 0;
        }
        else
        {
            matrix(row, col++) = to_digit(elt);
        }
    }

#ifdef DEBUG_OTHER
    std::cout << matrix << std::endl;
#endif

    const auto sizes = basin_sizes(matrix);
    const auto sizes_multiplied = std::accumulate(std::cbegin(sizes), std::cend(sizes), 1, [](auto acc, auto elt) { return acc * elt; });
    return std::to_string(sizes_multiplied);
}
