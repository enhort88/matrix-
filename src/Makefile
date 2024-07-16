.PHONY: clean test s21_matrix_oop.a check valgrind

SHELL=/bin/bash
CC=gcc -Wall -Werror -Wextra
CFLAGS= -x c++ -std=c++17 #-D_POSIX_C_SOURCE=200809L
BINFLD=.
BINTESTFLD=./matrix_oop
LDLIBS = -lstdc++
# LDTESTLIBS = -lm $(LDLIBS)

CPP_FILES := $(shell find . -name "*.cpp")
H_FILES := $(shell find . -name "*.h")

# OS=$(shell uname -s)
# ifeq ($(OS),Linux)
# CHECKFLAGS=-lcheck -lgcov --coverage -lsubunit -lrt -lpthread
# endif
# ifeq ($(OS),Darwin)
# CHECKFLAGS=-lcheck -lgcov --coverage
# endif
# GCOVFLAGS=-fprofile-arcs -ftest-coverage

STATICLIB=s21_matrix_oop.a
# DIROBJ=./obj
# DIRFUNCTESTS=./tests
# DIRGCOV=./gcov
# DIRGENHTML=./genhtml
DIRBUILD=./build
APPNAME=try.out

all: s21_matrix_oop.a # test

try: wash $(STATICLIB) # временная цель !!!УДАЛИТЬ!!!
	mkdir -p $(DIRBUILD)
	$(CC) -c $(CFLAGS) ./*.cpp
	$(CC) ./*.o $(STATICLIB) $(LDLIBS) -o $(DIRBUILD)/$(APPNAME)
#	$(DIRBUILD)/$(APPNAME)
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRBUILD)/$(APPNAME) 2>>valgrep.txt
	grep -e "Command" -e "jump" -e "Y: " valgrep.txt| grep -v "Y: 0" | cat

$(STATICLIB):
	$(CC) $(CFLAGS) -c $(BINFLD)/*.cpp 
	ar r $(STATICLIB) *.o
	rm -f *.o

# test: $(STATICLIB)
# 	$(CC) $(CFLAGS) -c $(BINFLD)/*.c $(GCOVFLAGS)
# 	$(CC) $(CFLAGS) -c $(BINTESTFLD)/*.c
# 	mkdir -p $(DIROBJ)
# 	mv -f *.o $(DIROBJ)
# 	mkdir -p $(DIRFUNCTESTS)
# 	$(CC) $(CFLAGS) $(DIROBJ)/tetris_test.o $(DIROBJ)/tetris.o $(STATICLIB) $(CHECKFLAGS) $(LDTESTLIBS) -o $(DIRFUNCTESTS)/tetris_test

# run_test:	
# 	$(DIRFUNCTESTS)/tetris_test

# gcov_report: test run_test
# 	mkdir -p $(DIRGCOV)
# 	gcov $(BINFLD)/*.c -o ./
# 	mv -f *.gcov $(DIRGCOV)
# 	mv -f *.gcda $(DIRGCOV)
# 	mv -f *.gcno $(DIRGCOV)
# 	lcov -d $(DIRGCOV) -c -o ./html.info
# 	genhtml -o $(DIRGENHTML) html.info
# 	open $(DIRGENHTML)/index.html
# 	@sleep 1
# 	@echo

check:
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n $(CPP_FILES) $(H_FILES)
	clang-format -style=Google -i $(CPP_FILES) $(H_FILES)
	cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ $(CPP_FILES) $(H_FILES)
	rm -f .clang-format

valgrind: test
	>valgrep.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/tetris_test 2>>valgrep.txt
	
	grep -e "Command" -e "jump" -e "Y: " valgrep.txt| grep -v "Y: 0" | cat

clean:
	rm -f $(shell find . -name "*.o")
	rm -f $(shell find . -name "*.out")
	rm -f $(shell find . -name "*.a")
	rm -f $(shell find . -name "*.gc*")
	rm -f $(shell find . -name "*.log")
	rm -f $(shell find . -name "*.info")
	rm -f $(shell find . -name "*.txt")
	rm -f $(shell find . -name "*.dat")
	rm -drf $(DIRBUILD)
#	rm -drf $(DIROBJ)
#	rm -drf $(DIRFUNCTESTS)
#	rm -drf $(DIRGCOV)
#	rm -drf $(DIRGENHTML)

wash: clean #uninstall

rebuild: wash all