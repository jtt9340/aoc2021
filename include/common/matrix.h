#include <algorithm>
#include <array>
#include <fstream>

#ifndef __MATRIX__
#define __MATRIX__

template <class T, size_t R, size_t C>
class Matrix;
template <class T, size_t R, size_t C>
std::ostream &operator<<(std::ostream &out, Matrix<T, R, C> &m);

template <class T, size_t R, size_t C>
class Matrix
{
protected:
    std::array<T, R * C> arr;
    using arr_type = decltype(arr);

public:
    static constexpr size_t rows = R;
    static constexpr size_t cols = C;
    using value_type = typename arr_type::value_type;
    using size_type = typename arr_type::size_type;
    using reference = typename arr_type::reference;
    using const_reference = typename arr_type::const_reference;

    Matrix()
    {
        std::fill(std::begin(arr), std::end(arr), T());
    }

    reference operator()(size_type row, size_type col)
    {
        return arr[C * row + col];
    }

    reference at(size_type row, size_type col)
    {
        return arr.at(C * row + col);
    }

    const_reference operator()(size_type row, size_type col) const
    {
        return arr[C * row + col];
    }

    const_reference at(size_type row, size_type col) const
    {
        return arr.at(C * row + col);
    }

    friend std::ostream &operator<< <T, R, C>(std::ostream &out, Matrix<T, R, C> &m);
};

template <class T, size_t R, size_t C>
std::ostream &operator<<(std::ostream &out, Matrix<T, R, C> &m)
{
    for (auto i = 0; i < R; i++)
    {
        for (auto j = 0; j < C; j++)
            out << m(i, j);
        out << '\n';
    }

    return out;
}

template <class T, size_t R, size_t C>
std::istream &operator>>(std::istream &in, Matrix<T, R, C> &m)
{
    for (auto i = 0; i < R; i++)
    {
        for (auto j = 0; j < C; j++)
        {
            T x;
            in >> x;
            m(i, j) = x;
        }
    }

    return in;
}

template <class T>
class DynamicMatrix
{
protected:
    std::vector<T> arr;
    using arr_type = decltype(arr);

public:
    using value_type = typename arr_type::value_type;
    using size_type = typename arr_type::size_type;
    using reference = typename arr_type::reference;
    using const_reference = typename arr_type::const_reference;

    const size_type rows, cols;

    // Normally I would use the brace { } initializer syntax but arr{rows * cols} will invoke
    // std::vector(std::initializer_list<T>) but I want std::vector(size_type)
    DynamicMatrix(size_type rows, size_type cols) : arr(rows * cols), rows(rows), cols(cols)
    {
    }

    reference operator()(size_type row, size_type col)
    {
        return arr[cols * row + col];
    }

    template <class Coordinate>
    reference operator()(const Coordinate &c)
    {
        return (*this)(c[0], c[1]);
    }

    reference at(size_type row, size_type col)
    {
        return arr.at(cols * row + col);
    }

    template <class Coordinate>
    reference at(const Coordinate &c)
    {
        return at(c[0], c[1]);
    }

    const_reference operator()(size_type row, size_type col) const
    {
        return arr[cols * row + col];
    }

    template <class Coordinate>
    const_reference operator()(const Coordinate &c) const
    {
        return (*this)(c[0], c[1]);
    }

    const_reference at(size_type row, size_type col) const
    {
        return arr.at(cols * row + col);
    }

    template <class Coordinate>
    const_reference at(const Coordinate &c) const
    {
        return at(c[0], c[1]);
    }
};

#endif
