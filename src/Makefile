.PHONY: clean test s21_matrix_oop.a check valgrind

SHELL=/bin/bash
CC=gcc -Wall -Werror -Wextra
CFLAGS= -x c++ -std=c++17
BINFLD=s21_matrix_plus
BINTESTFLD=./s21_matrix_gtest
LDLIBS = -lstdc++ -lm


CPP_FILES := $(shell find . -name "*.cpp")
H_FILES := $(shell find . -name "*.h")

OS=$(shell uname -s)
ifeq ($(OS),Linux)
	GFLAGS=-lgtest --coverage -lsubunit -lpthread
endif
ifeq ($(OS),Darwin)
	GFLAGS=-lgtest --coverage
endif
COVFLAGS=-fprofile-arcs -ftest-coverage


STATICLIB=s21_matrix_oop.a
DIROBJ=./obj
DIRFUNCTESTS=./tests
DIRGCOV=./gcov
DIRGENHTML=./genhtml
DIRBUILD=./build
APPNAME=s21_matrix_plus
APPTEST=s21_matrix_test_run

all: s21_matrix_oop.a 

try: wash $(STATICLIB) # временная цель !!!УДАЛИТЬ!!!
	mkdir -p $(DIRBUILD)
	$(CC) -c $(CFLAGS) $(BINFLD)/*.cpp
	$(CC) ./*.o $(STATICLIB) $(LDLIBS) -o $(DIRBUILD)/$(APPNAME)
	$(DIRBUILD)/$(APPNAME)
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRBUILD)/$(APPNAME) 2>>valtest.txt
	grep -e "Command" -e "jump" -e "Y: " valgrep.txt| grep -v "Y: 0" | cat

$(STATICLIB):
	$(CC) $(CFLAGS) -c $(BINFLD)/*.cpp 
	ar r $(STATICLIB) *.o
	rm -f *.o

test: $(STATICLIB)
	$(CC) $(CFLAGS) -c $(BINFLD)/*.cpp $(COVFLAGS)
	$(CC) $(CFLAGS) -c $(BINTESTFLD)/*.cpp
	mkdir -p $(DIROBJ)
	mv -f *.o $(DIROBJ)
	mkdir -p $(DIRFUNCTESTS)
	rm $(DIROBJ)/main.o
	$(CC) $(DIROBJ)/*.o $(STATICLIB) $(GFLAGS) $(LDLIBS) -o $(DIRFUNCTESTS)/$(APPTEST)

run_test: 	
	$(DIRFUNCTESTS)/$(APPTEST)

gcov_report: test run_test
	mkdir -p $(DIRGCOV)
	gcov $(BINFLD)/*.cpp -o ./
	mv -f *.gcov $(DIRGCOV)
	mv -f *.gcda $(DIRGCOV)
	mv -f *.gcno $(DIRGCOV)
	lcov -d $(DIRGCOV) -c -o ./html.info --exclude '/usr/*' --exclude '*/test/*'
	genhtml -o $(DIRGENHTML) html.info
	open $(DIRGENHTML)/index.html
	@sleep 1
	@echo


check:
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n $(CPP_FILES) $(H_FILES)
	clang-format -style=Google -i $(CPP_FILES) $(H_FILES)
	cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ $(CPP_FILES) $(H_FILES)
	rm -f .clang-format

valgrind: test
	>valgrep.txt
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/$(APPTEST) 2>>valgrep.txt
	
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
	rm -drf $(DIROBJ)
	rm -drf $(DIRFUNCTESTS)
	rm -drf $(DIRGCOV)
	rm -drf $(DIRGENHTML)

wash: clean #uninstall

rebuild: wash all

pushing_to_git:
	git add .
	git commit -m "$(shell date)"
	git push origin develop