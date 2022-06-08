#include <iostream>
#include <vector>

#include "aoc_test.h"
#include "aoc_tests.h"
#include "constants.h"
#include "file_utils.h"

AocTests::AocTests()
{
}

AocTests::~AocTests()
{
}

std::string AocTests::base_directory(std::string filename)
{
    size_t found;
    found = filename.find_last_of("/\\");
    if (found != std::string::npos) // found a directory character. return everything from the start through that character
    {
        return filename.substr(0, found + 1);
    }
    else // no directory character found. just return an empty string to indicate the current directory
    {
        return "";
    }
}

bool AocTests::load_tests(std::string filename)
{
    std::vector<std::vector<std::string>> test_index_contents;
    std::string basedir = base_directory(filename);
#ifdef DEBUG_RUNNER
    cout << "The base dicectory for test files is " << basedir << endl;
#endif
    FileUtils fileutils;
    if (!fileutils.read_as_list_of_split_strings(filename, test_index_contents, TEST_INDEX_DELIM, TEST_INDEX_QUOTE, TEST_INDEX_COMMENT))
    {
        std::cerr << "Error reading test index file " << filename << std::endl;
        return false;
    }

    for (std::vector<std::vector<std::string>>::iterator test_iter = test_index_contents.begin(); test_iter != test_index_contents.end();
         ++test_iter)
    {
        std::vector<std::string> test_parameters = *test_iter;
        // Skip a blank line
        if (test_parameters.size() == 1 && test_parameters[0].size() == 0)
        {
            continue;
        }

        std::vector<std::string>::iterator parm_iter = test_parameters.begin();
        // format is day,part,filename,expected[,...extra args]
        long day, part;
        std::string filename, full_filename, expected;
        std::vector<std::string> extra_args;

        day = strtol((*parm_iter).c_str(), nullptr, 10);
        ++parm_iter;

        part = strtol((*parm_iter).c_str(), nullptr, 10);
        ++parm_iter;

        filename = *parm_iter;
        full_filename = basedir + filename;
#ifdef DEBUG_RUNNER
        cout << "The full path to " << filename << " is " << full_filename << endl;
#endif
        ++parm_iter;

        expected = *parm_iter;
        ++parm_iter;
        while (parm_iter != test_parameters.end())
        {
#ifdef DEBUG_RUNNER
            cout << "Adding extra parm " << *parm_iter << endl;
#endif
            extra_args.push_back(*parm_iter);
            ++parm_iter;
        }
        m_tests.push_back(AocTest(day, part, full_filename, expected, extra_args));
    }
    return true;
}

std::vector<AocTest> AocTests::get_all_tests()
{
    return m_tests;
}

std::vector<AocTest> AocTests::filter_tests(int day, int part)
{
    std::vector<AocTest> matching_tests;

    for (std::vector<AocTest>::iterator test_iter = m_tests.begin(); test_iter != m_tests.end(); ++test_iter)
    {
        if ((*test_iter).matches(day, part))
        {
            matching_tests.push_back(*test_iter);
        }
    }

    return matching_tests;
}
