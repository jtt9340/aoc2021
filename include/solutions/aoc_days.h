#ifndef __AOC_DAYS_H__
#define __AOC_DAYS_H__

#include <map>

#include "aoc_day.h"

class AocDays
{
protected:
    std::map<int, AocDay *> m_days;

public:
    AocDays();
    ~AocDays();
    AocDay *get_day(int day);
};

#endif
