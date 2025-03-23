 #************************************************************************
 #
 #	Makefile for CS2401 Planner Project (singly linked list)
 #	Made by Kyle Chiasson
 #  Edited by Patricia Lindner
 #	Last updated 2/26/2025
 #	For automatic grading to work, do not change this file.
 #	Students are encouraged to read through to understand project requirements, however.
 #
 # ***********************************************************************

CFLAGS = -Wall -std=c++11
CDFLAGS = -Wall -std=c++11 -g
CC = g++

a.out: assignment.o date_time.o planner.o main.cc
	$(CC) $(CFLAGS) $^ -o $@

assignment.o: assignment.cc assignment.h
	$(CC) $(CFLAGS) -c $< -o $@

date_time.o: date_time.cc date_time.h
	$(CC) $(CFLAGS) -c $< -o $@

planner.o: planner.cc planner.h
	$(CC) $(CFLAGS) -c $< -o $@

test: run_tests
tests: run_tests
run_test: run_tests
run_tests: assignment.o date_time.o planner.o _TEST/TEST_cases.cc
	$(CC) $(CFLAGS) $^ -o _TEST/run_tests
	./_TEST/run_tests

# if you are on MacOS, change gdb to lldb on the following 3 lines
debug: gdb.out
	gdb ./gdb.out
gdb.out: assignment.o date_time.o planner.o main.cc
	$(CC) $(CDFLAGS) $^ -o $@

#note: this test requires the installation of valgrind
valgrind: assignment.o date_time.o planner.o _TEST/TEST_cases.cc
	$(CC) $(CDFLAGS) $^ -o _TEST/run_tests
	valgrind -s ./_TEST/run_tests

clean:
	rm -f *.o *.out _TEST/run_tests
