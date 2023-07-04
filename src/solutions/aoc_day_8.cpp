#include <cassert>
#include <cstdint>
#include <fstream>

#include "aoc_day_8.h"

uint32_t count_unique_segments(const std::vector<NotesEntry> &notes)
{
    uint32_t num_unique_segments = 0;

    for (auto entry = std::cbegin(notes); entry != std::cend(notes); entry++)
    {
        const auto &output = entry->output;
        for (auto output_val = std::cbegin(output); output_val != std::cend(output); output_val++)
        {
            switch (output_val->size())
            {
            case 2:
            case 3:
            case 4:
            case 7:
                num_unique_segments++;
            }
        }
    }

    return num_unique_segments;
}

AocDay8::AocDay8() : AocDay(8)
{
}

AocDay8::~AocDay8()
{
}

std::string AocDay8::part1(std::string &filename, std::vector<std::string> &extra_args)
{
    std::ifstream input{filename};

    std::vector<NotesEntry> notes;
    NotesEntry entry;
    auto signal_seq = &entry.signal_patterns;

    char cur, *signal;
    auto n = 0;
    while ((cur = input.peek()) != std::ifstream::traits_type::eof())
    {
        switch (cur)
        {
        case ' ':
            input.seekg(-n, std::ios_base::cur);
            signal = new char[n];
            if (input.read(signal, n))
                signal_seq->emplace_back(signal, n);
            delete[] signal;
            assert(input.get() == ' ');
            n = 0;
            break;
        case '\n':
            input.seekg(-n, std::ios_base::cur);
            signal = new char[n];
            if (input.read(signal, n))
                signal_seq->emplace_back(signal, n);
            delete[] signal;
            assert(input.get() == '\n');
            notes.emplace_back(entry);
            entry.signal_patterns.clear();
            entry.output.clear();
            signal_seq = &entry.signal_patterns;
            n = 0;
            break;
        case '|':
            signal_seq = &entry.output;
            input.seekg(2, std::ios_base::cur);
            break;
        default:
            input.seekg(1, std::ios_base::cur);
            n++;
        }
    }

    const auto answer = count_unique_segments(notes);
    return std::to_string(answer);
}
