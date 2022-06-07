#include <string>
#include <sstream>
#include <iostream>
#include <unistd.h> // getopt

#include "aoc_days.h"
#include "aoc_tests.h"
#include "file_utils.h"

#define DASH_D 0x01
#define DASH_P 0x02
#define DASH_F 0x04
#define DASH_T 0x08
#define DASH_R 0x10

#define OPTS_RUN_FILE (DASH_D | DASH_P | DASH_F)
#define OPTS_RUN_TEST (DASH_D | DASH_P | DASH_T)
#define OPTS_RUN_REGRESSION (DASH_R)

void usage(std::string prog_name)
{
	std::cerr << "Usage for " << prog_name << std::endl;
    std::cerr << "   Run one file: " << prog_name << " -d day -p part -f filename [extra_args...]" << std::endl;
    std::cerr << "   Run one day/part tests: " << prog_name << " -d day -p part -t test_index_filename" << std::endl;
    std::cerr << "   Run full regression test: " << prog_name << " -r test_index_filename" << std::endl;
}

int main (int argc, char * argv[])
{
    AocDays days;
    AocTests tests;
    FileUtils fileutils;
    
    long day = 0;
    long part = 0;
    bool regression = false;
	std::string filename = "";
    std::string test_filename = "";
    std::string result = "";
    std::vector<std::string> extra_args;
    std::ostringstream test_summary;
    
    int given_opts = 0;
    int opt;
    
    // getopt parsing of command line parameters
    while ((opt = getopt(argc, argv, "d:p:f:t:r:")) != -1)
    {
        switch (opt)
        {
            case 'd':
                day = std::strtol(optarg, nullptr, 10);
                given_opts |= DASH_D;
                break;
            case 'p':
                part = std::strtol(optarg, nullptr, 10);
                given_opts |= DASH_P;
                break;
            case 'f':
                filename = std::string(optarg);
                given_opts |= DASH_F;
                break;
            case 't':
                test_filename = std::string(optarg);
                given_opts |= DASH_T;
                break;
            case 'r':
                test_filename = std::string(optarg);
                regression = true;
                given_opts |= DASH_R;
                break;
            default:
				std::cerr << "Invalid option " << opt << " given" << std::endl;
                usage(argv[0]);
				std::exit(8);
                break;
        }
    }
    
    // check for valid option combination and get any extra arguments if running from a file
    if (given_opts == OPTS_RUN_FILE)
    {
        for (int i=optind; i<argc; i++)
        {
            extra_args.push_back(std::string(argv[i]));
        }
    }
    else if (given_opts != OPTS_RUN_TEST && given_opts != OPTS_RUN_REGRESSION)
    {
		std::cerr << "Invalid set of options given" << std::endl;
        usage(argv[0]);
		std::exit(8);
    }
    
    // Actually do stuff
    if (filename != "")
    {
        AocDay * aoc_day = days.get_day(day);
        if (!aoc_day)
        {
			std::cerr << "Program for day " << day << " not found!!!" << std::endl;
            exit(8);
        }
        if (part == 1)
        {
            result = aoc_day->part1(filename, extra_args);
        }
        else if (part == 2)
        {
            result = aoc_day->part2(filename, extra_args);
        }
        else
        {
			std::cerr << "Invalid part" << part << " specified!!!" << std::endl;
            exit(8);
        }
		std::cout << "***Day " << day << " Part " << part << " for file " << filename << " has result " << result << std::endl;
    }
    else // no filename; assume some type of testing mode
    {
		std::vector<AocTest> tests_to_run;
        if (!tests.load_tests(test_filename))
        {
			std::cerr << "Error loading from test indext file " << test_filename << std::endl;
			std::exit(8);
        }
        if (regression)
        {
			std::cout << "Running full regression test for all days and parts!" << std::endl;
            tests_to_run = tests.get_all_tests();
        }
        else
        {
			std::cout << "Running tests for day " << day << " part " << part << std::endl;
            tests_to_run = tests.filter_tests(day, part);
        }
        for (std::vector<AocTest>::iterator test_iter = tests_to_run.begin(); test_iter != tests_to_run.end(); ++test_iter)
        {
            AocTest test = *test_iter;
            AocDay * aoc_day = days.get_day(test.get_day());
            if (!aoc_day)
            {
				std::cerr << "Program for day " << test.get_day() << " not found!!!" << std::endl;
                std::exit(8);
            }
            if (test.get_part() == 1)
            {
				filename = test.get_filename();
				extra_args = test.get_extra_args();
                result = aoc_day->part1(filename, extra_args);
            }
            else if (test.get_part() == 2)
            {
				filename = test.get_filename();
				extra_args = test.get_extra_args();
                result = aoc_day->part2(filename, extra_args);
            }
            else
            {
				std::cerr << "Invalid part" << test.get_part() << " specified!!!" << std::endl;
                std::exit(8);
            }
            if (result == test.get_expected_result())
            {
                test_summary << "++Day " << test.get_day() << " Part " << test.get_part() << "-" << test.get_filename() << " passed with result " << result << std::endl;
            }
            else
            {
                test_summary << "--Day " << test.get_day() << " Part " << test.get_part() << "-" << test.get_filename() << " FAILED expected=" << test.get_expected_result() << " actual=" << result << std::endl;
            }
        }
		std::cout << test_summary.str();
    }
    return 0;
}
