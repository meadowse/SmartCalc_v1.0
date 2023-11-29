.PHONY: all test s21_SmartCalc.a check rebuild open gcov_report install uninstall dist clean
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
LINUX=-lsubunit -lrt
LFLAGS=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)
OBJ=$(patsubst %.c, %.o, $(SRC))
MKF = makefile.qt

FLAGS_TEST_LIBS = -lcheck -lm -lpthread
NAME=s21_calc.a
SRC = graph.c RPN.c structs.c calc.c CException.c

all: build static test

build:
	$(CC) $(CFLAGS) -c $(SRC)

static:
	@ar rc s21_calc.a $(OBJ)
	@ranlib s21_calc.a

test: build static
	$(CC) $(CFLAGS) -lcheck test.c s21_calc.a -o test
	./test

gcov_report: all
	$(CC) $(CFLAGS) --coverage test.c $(SRC) $(NAME) $(FLAGS_TEST_LIBS) -o gcov_test
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html

install:
	make clean
	mkdir build
	qmake -o $(MKF) && make -f $(MKF) && make clean -f $(MKF) && rm $(MKF) && mv SmartCalc.app build  

uninstall:
	rm -rf build*

dvi:
	open readme.md

dist:
	rm -rf Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/src
	mv ./build/SmartCalc.app Archive_calc_v1.0/src/
	tar cvzf Archive_calc_v1.0.tgz Archive_calc_v1.0/
	rm -rf Archive_calc_v1.0/

clean:
	@rm -rf $(EXECUTABLE)
	@rm -rf *.{a,o,dSYM,out}
	@rm -rf gcov_report
	@rm -rf report
	@rm -rf CPPLINT.cfg
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf *.info
	@rm -rf test
	@rm -rf Archive_calc_v1.0 
	@rm -rf *tgz
	@rm -rf build
	@rm -rf gcov_test

rebuild: clean all

check:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.cpp *.h
	clang-format -n *.c *.cpp *.h
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h
	leaks --atExit -- test

install_lcov:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

install_valgrind:
	brew install --HEAD LouisBrunner/valgrind/valgrind

install_cpch:
	brew install cppcheck

valgf: build static
ifeq ($(OS), Darwin)
	gcc $(CFLAGS) test.c s21_calc.a -o unit_test $(FLAGS_TEST_LIBS)
	CK_FORK=no valgrind --leak-check=full -s ./unit_test
else
	gcc $(CFLAGS) test.c s21_calc.a -o unit_test $(FLAGS_TEST_LIBS) $(LINUX)
	K_FORK=no valgrind --leak-check=full -s ./unit_test
endif

clean_obj:
	rm -rf *.o

valg: build static clean_obj
ifeq ($(OS), Darwin)
	gcc $(CFLAGS) test.c s21_calc.a -o unit_test $(FLAGS_TEST_LIBS)
	valgrind --leak-check=full -s ./unit_test
else
	gcc $(CFLAGS) test.c s21_calc.a -o unit_test $(FLAGS_TEST_LIBS) $(LINUX)
	valgrind --leak-check=full -s ./unit_test
endif
