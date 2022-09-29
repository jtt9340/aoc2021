DEBUG =
# Uncomment the below line to display the runner debug
# DEBUG+= -DDEBUG_RUNNER
# Template for other debug flags to be added later
# DEBUG+- -DDEBUG_OTHER

CXX = g++
AR = ar
#If adding another include directory, be sure to add it here
CPPFLAGS=-g -std=c++14 ${DEBUG} -Iinclude/common -Iinclude/runner -Iinclude/solutions

SRCSROOT = src/solutions
TARGETDIR = ${subst src,build,${SRCSROOT}}
SOLUTION_SRCS = ${wildcard ${SRCSROOT}/*.cpp}
SOLUTION_OBJS = ${SOLUTION_SRCS:.cpp=.o}

.DEFAULT_GOAL := all

# Runner library; contains a lot of common code for file parsing and handling test files
build/runner/aoc_test.o: src/runner/aoc_test.cpp  \
	include/runner/aoc_test.h  \
	include/common/constants.h
	${CXX} ${CPPFLAGS} -o build/runner/aoc_test.o -c src/runner/aoc_test.cpp

build/runner/aoc_tests.o: src/runner/aoc_tests.cpp  \
	include/runner/aoc_tests.h  \
	include/runner/aoc_test.h  \
	include/common/constants.h
	${CXX} ${CPPFLAGS} -o build/runner/aoc_tests.o -c src/runner/aoc_tests.cpp

build/runner/file_utils.o: src/runner/file_utils.cpp  \
	include/runner/file_utils.h  \
	include/common/constants.h
	${CXX} ${CPPFLAGS} -o build/runner/file_utils.o -c src/runner/file_utils.cpp

bin/lib/librunner.a: build/runner/aoc_test.o  \
	build/runner/aoc_tests.o  \
	build/runner/file_utils.o
	${AR} rcs bin/lib/librunner.a build/runner/aoc_test.o build/runner/aoc_tests.o build/runner/file_utils.o

# Solutions - These are the programs for the daily solutions
build/solutions/%.o: src/solutions/%.cpp \
	include/solutions/%.h        \
	include/solutions/aoc_day.h  \
	include/common/constants.h
	${CXX} ${CPPFLAGS} -o $@ -c $<

bin/lib/libsolutions.a: ${SOLUTION_OBJS}
	${AR} rcs bin/lib/libsolutions.a $^

# The aoc executable
build/aoc.o: src/aoc.cpp  \
	include/solutions/aoc_days.h  \
	include/runner/aoc_tests.h  \
	include/runner/file_utils.h  \
	include/common/constants.h
	${CXX} ${CPPFLAGS} -o build/aoc.o -c src/aoc.cpp

#If adding a new library, be sure to add it in the correct order in the compile line
bin/aoc: build/aoc.o  \
	bin/lib/librunner.a  \
	bin/lib/libsolutions.a
	${CXX} ${CPPFLAGS} -o bin/aoc build/aoc.o -Lbin/lib -lsolutions -lrunner

.PHONY: clean
clean:
	rm -f build/runner/aoc_test.o  \
	build/runner/aoc_tests.o  \
	build/runner/file_utils.o  \
	${SOLUTION_OBJS} \
	build/aoc.o  \
	bin/lib/librunner.a  \
	bin/lib/libsolutions.a  \
	bin/aoc

.PHONY: all
all: build/runner/aoc_test.o  \
	build/runner/aoc_tests.o  \
	build/runner/file_utils.o  \
	${SOLUTION_OBJS} \
	build/aoc.o  \
	bin/lib/librunner.a  \
	bin/lib/libsolutions.a  \
	bin/aoc

.PHONY: fmt
fmt:
	clang-format -i -style=file ${SOLUTION_SRCS} src/aoc.cpp src/runner/*.cpp include/*/*.h
	command -v nixfmt && nixfmt -w 80 shell.nix
