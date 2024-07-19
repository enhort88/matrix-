.PHONY: clean test s21_matrix_oop.a check valgrind

SHELL=/bin/bash
CC=gcc -Wall -Werror -Wextra
CCFLAGS= -std=c++17# -x c++ -D_POSIX_C_SOURCE=200809L
BINFLD=./s21_matrix_plus
BINTESTFLD=./s21_matrix_gtest
LDLIBS = -lstdc++ -lm
LDTESTLIBS = -lgtest -lgtest_main $(LDLIBS)
DIRBUILD = dev_test
APPNAME=dev_test.out

CPP_FILES := $(shell find . -name "*.cpp")
BIN_CPP_FILES := $(shell find $(BINFLD) -name "*.cpp")
TEST_CPP_FILES := $(shell find $(BINTESTFLD) -name "*.cpp")
TEST_FILENAME := $(shell find $(BINTESTFLD) -name "*_test.cpp" -exec basename {} \; | sed 's/_test.cpp$$//')
H_FILES := $(shell find . -name "*.h")

GCOVFLAGS= -fprofile-arcs -ftest-coverage
OS=$(shell uname -s)
ifeq ($(OS),Linux)
CHECKFLAGS= -lgcov --coverage -lpthread# -lsubunit -lrt
endif
ifeq ($(OS),Darwin)
CHECKFLAGS= -lgcov --coverage
endif

STATICLIB=s21_matrix_oop.a
DIROBJ=./obj
DIRGCOV=./gcov
DIRFUNCTESTS=./tests
DIRGENHTML=./genhtml
DATE=$(shell date)

all: $(STATICLIB)

$(STATICLIB):
	$(CC) -c $(CCFLAGS) $(BIN_CPP_FILES) 
	ar r $(STATICLIB) *.o
	rm -f *.o

try: $(STATICLIB) # временная цель !!!УДАЛИТЬ!!!
	mkdir -p $(DIRBUILD)
	$(CC) -c $(CFLAGS) $(BINFLD)/*.cpp
	$(CC) ./*.o $(STATICLIB) $(LDLIBS) -o $(DIRBUILD)/$(APPNAME)
	$(DIRBUILD)/$(APPNAME)
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRBUILD)/$(APPNAME) 2>>valtest.txt
	grep -e "Command" -e "jump" -e "Y: " valgrep.txt| grep -v "Y: 0" | cat


test: $(STATICLIB)
	$(CC) -c $(CCFLAGS) $(BIN_CPP_FILES) $(GCOVFLAGS)
	$(CC) -c $(CCFLAGS) $(TEST_CPP_FILES)
	mkdir -p $(DIROBJ) $(DIRGCOV) $(DIRFUNCTESTS)
	mv -f *.o $(DIROBJ)/
	mv -f *.gcno $(DIRGCOV)/
	@echo
	@echo -e "\033[31mFinded files for testing: $(TEST_FILENAME)_test.cpp\033[0m"
	$(foreach file, $(TEST_FILENAME), $(CC) $(CCFLAGS) $(DIROBJ)/$(file).o $(DIROBJ)/$(file)_test.o $(STATICLIB) $(LDTESTLIBS) $(CHECKFLAGS) -o $(DIRFUNCTESTS)/$(file)_test;)

run_test: test
	@echo
	$(foreach file, $(TEST_FILENAME),$(DIRFUNCTESTS)/$(file)_test; echo;)

gcov_report: run_test
	mv -f *.gcda $(DIRGCOV)/
	@echo
	$(foreach file, $(TEST_FILENAME), gcov $(BINFLD)/$(file).cpp -o $(DIRGCOV);)
	mv -f *.gcov $(DIRGCOV)/
	mkdir -p $(DIRGENHTML)  
	lcov -d $(DIRGCOV) -c -o $(DIRGENHTML)/html.info --exclude '/usr/*'
	genhtml -o $(DIRGENHTML) $(DIRGENHTML)/html.info
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
	$(foreach file, $(TEST_FILENAME), valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/$(file)_test 2>>valgrep.txt;)
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
	rm -drf $(DIRGCOV)
	rm -drf $(DIROBJ)
	rm -drf $(DIRFUNCTESTS)
	rm -drf $(DIRGENHTML)

rebuild: clean all

pushing_to_git:
	git add .
	git commit -m "$(DATE)"
	git push origin develop