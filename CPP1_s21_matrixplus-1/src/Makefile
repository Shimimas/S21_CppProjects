CC=g++
CFLAGS= -std=c++17

FLAGS= -Wall -Wextra -Werror  

all: test clean

test: test_build
	./test

test_build: s21_matrix_oop.o test.o
	$(CC) $(FLAGS) $(CFLAGS) s21_matrix_oop.o test.o -o test -lgtest

s21_matrix_oop.a: s21_matrix_oop.o s21_matrix_oop.h
	@ar -rcs s21_matrix_oop.a
	echo s21_matrix_oop.a
	@ranlib s21_matrix_oop.a
	@cp s21_matrix_oop.a libs21_matrix_oop.a

s21_matrix_oop.o:
	$(CC) $(FLAGS) $(CFLAGS) -c s21_matrix_oop.cpp

test.o:
	$(CC) $(FLAGS) $(CFLAGS) -c test.cpp

valgrind_check: test_build
	valgrind --leak-check=full --track-origins=yes ./test -n file
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./test -n file

gcov_report: 
	g++ --coverage -Wall -Wextra -Werror test.cpp s21_matrix_oop.cpp -o test -lstdc++ `pkg-config --cflags --libs gtest`
	./test
	lcov --no-external -t "test" -o test.info -c -d ./
	genhtml -o report test.info

clean:
	rm -rf *.o test report *.gcda *.gcno *.info *.a