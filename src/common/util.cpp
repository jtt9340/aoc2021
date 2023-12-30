#include <stdexcept>

#include "util.h"

int to_digit(char byte)
{
    if (byte < '0' || byte > '9')
        throw std::invalid_argument{"invalid digit"};

    return static_cast<int>(byte) - '0';
}

char from_digit(int digit)
{
    if (digit < 0 || digit > 9)
        throw std::invalid_argument{"invalid_digit"};

    return static_cast<char>(digit + '0');
}
