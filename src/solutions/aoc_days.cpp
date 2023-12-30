#include <map>

#include "aoc_day.h"
#include "aoc_days.h"
// includes for each day will go here
// Disable clang-format because otherwise it will reorder the imports
// lexicographically (i.e. day 1 -> day 10 -> day 2) and I want them in
// number order
// clang-format off
#include "aoc_day_0.h"
#include "aoc_day_1.h"
#include "aoc_day_2.h"
#include "aoc_day_3.h"
#include "aoc_day_4.h"
#include "aoc_day_5.h"
#include "aoc_day_6.h"
#include "aoc_day_7.h"
#include "aoc_day_8.h"
#include "aoc_day_9.h"
#include "aoc_day_10.h"
#include "aoc_day_11.h"
// clang-format on

AocDays::AocDays()
{
    // adding each member to the map goes here
    m_days[0] = new AocDay0();
    m_days[1] = new AocDay1();
    m_days[2] = new AocDay2();
    m_days[3] = new AocDay3();
    m_days[4] = new AocDay4();
    m_days[5] = new AocDay5();
    m_days[6] = new AocDay6();
    m_days[7] = new AocDay7();
    m_days[8] = new AocDay8();
    m_days[9] = new AocDay9();
    m_days[10] = new AocDay10();
    m_days[11] = new AocDay11();
}

AocDays::~AocDays()
{
    // delete all of the days solutions
    for (std::map<int, AocDay *>::iterator days_iter = m_days.begin(); days_iter != m_days.end(); ++days_iter)
    {
        delete days_iter->second;
    }
    m_days.clear();
}

AocDay *AocDays::get_day(int day)
{
    return m_days[day];
}
