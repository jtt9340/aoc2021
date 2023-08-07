#include <cassert>
#include <limits>
#include <numeric>

#include "aoc_day_9.h"

static Matrix::value_type todigit(std::ifstream::int_type byte)
{
    switch (byte)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    default:
        throw std::invalid_argument{"invalid digit"};
    }
}

template <class It>
static uint32_t total_risk_level(It begin, It end)
{
    return std::accumulate(begin, end, 0, [](auto acc, auto elt) { return acc + elt + 1; });
}

Matrix::Matrix(Matrix::size_type rows, Matrix::size_type cols) : arr(rows * cols), rows(rows), cols(cols)
{
}

Matrix::reference Matrix::operator()(Matrix::size_type row, Matrix::size_type col)
{
    return arr[cols * row + col];
}

Matrix::const_reference Matrix::operator()(Matrix::size_type row, Matrix::size_type col) const
{
    return arr[cols * row + col];
}

bool Matrix::is_low_point(Matrix::size_type row, Matrix::size_type col) const
{
    const Matrix::value_type top = row == 0 ? std::numeric_limits<Matrix::value_type>::max() : (*this)(row - 1, col);
    const Matrix::value_type right = col == cols - 1 ? std::numeric_limits<Matrix::value_type>::max() : (*this)(row, col + 1);
    const Matrix::value_type bottom = row == rows - 1 ? std::numeric_limits<Matrix::value_type>::max() : (*this)(row + 1, col);
    const Matrix::value_type left = col == 0 ? std::numeric_limits<Matrix::value_type>::max() : (*this)(row, col - 1);
    Matrix::const_reference elt = (*this)(row, col);
    return elt < top && elt < right && elt < bottom && elt < left;
}

#ifdef DEBUG_OTHER
std::ostream &operator<<(std::ostream &out, Matrix &curr)
{
    for (Matrix::size_type i = 0; i < curr.rows; i++)
    {
        for (Matrix::size_type j = 0; j < curr.cols; j++)
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
    std::vector<Matrix::value_type> low_points;
    Matrix::size_type i;

    // We want to read values from the input into a matrix, but we cannot know how big
    // to make the matrix until we've read the first row, which we will temporarily store
    // in a vector.
    std::vector<Matrix::value_type> elts;
    // Hardcoding a pre-allocated length of 101 for the vector upfront since
    // that's how many characters are in each line of the puzzle input.
    elts.reserve(101);
    std::ifstream::int_type elt;
    while ((elt = input.get()) != '\n')
        elts.push_back(todigit(elt));

    Matrix matrix{3, elts.size()};
    // Transfer the first row into the matrix and read characters into the second row
    for (i = 0; i < matrix.cols; i++)
    {
        matrix(0, i) = elts[i];
        elt = input.get();
        matrix(1, i) = todigit(elt);
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
            matrix(2, i) = todigit(elt);
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
