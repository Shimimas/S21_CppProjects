detected_OS:=$(shell uname -s)
CC = g++
GCOV_TEST = gcov_report
TARGET = 3DViewer
GTEST =`pkg-config --cflags --libs gtest`
CFLAGS = -std=c++17 -Wall -Werror -Wextra -lstdc++
BUILDTARGET = controller/*.cc model/*.cc
TESTTARGET = tests/s21_test.cc
OS=$(shell uname)

ifeq ($(OS), Linux)
	OPEN = xdg-open
	BIN_PATH = ./3DViewer
	LIBS= -lgtest -lpthread -pthread -lrt -lm -lsubunit -D_GNU_SOURCE
	LEAKS= valgrind --track-origins=yes --leak-check=full  ./$(TESTTARGET)
else
	OPEN = open
	BIN_PATH = S21_3DViewer.app/Contents/MacOS/
	LIBS=-lcheck -lgtest -pthread
	LEAKS=leaks --atExit -- ./$(TESTTARGET)
endif

GCOV = --coverage

all: clang-format $(TARGET)
	./$(TARGET)

$(TARGET):      
	cd S21_3DViewer && qmake && make && mv $(BIN_PATH) ../$(TARGET) && rm -f Makefile

install: $(TARGET)
	@mkdir -p $(HOME)/Desktop/3DViewer_v2.0/
	@cp -rf 3DViewer $(HOME)/Desktop/3DViewer_v2.0/


uninstall:
	@rm -rf $(HOME)/Desktop/3DViewer_v2.0/

dvi:
	google-chrome documentation/documentation.html

dist: clean
	cd .. && tar -cf S21_3DViewer.tar src && mv S21_3DViewer.tar src

undist: clean
	@rm -rf S21_3DViewer.tar

tests: gcov_report

clang-format:
	cp ../materials/linters/.clang-format . 
	clang-format -i  S21_3DViewer/*.cc S21_3DViewer/*.h controller/*.cc controller/*.h model/*.cc model/*.h
	clang-format -n S21_3DViewer/*.cc S21_3DViewer/*.h controller/*.cc controller/*.h model/*.cc model/*.h

gcov_report:
	$(CC) $(GCOV) $(CFLAGS) -c $(BUILDTARGET) $(LIBS)
	$(CC) $(GCOV) $(CFLAGS) $(LIBS) -c $(TESTTARGET) $(LIBS)
	$(CC) $(GCOV) $(CFLAGS) $(LIBS) *.o -o $(GCOV_TEST) $(GTEST)
	./$(GCOV_TEST)
	gcov $(TESTTARGET)
	lcov -t $(GCOV_TEST) --no-external -o $(GCOV_TEST).info -c -d .
	genhtml -o report $(GCOV_TEST).info
	$(OPEN) ./report/index.html

clean:	
	rm -Rf *.tar
	rm -rf S21_3DViewer/3DViewer 3DViewer s21_test gcov_report
	rm -rf *.o *.so *.a fizz *.gc* *.info report *.out *.gcda *.so *.gcno *.info
	rm -rf S21_3DViewer/*.o S21_3DViewer/*.so S21_3DViewer/*.a S21_3DViewer/fizz S21_3DViewer/*.gc*
	rm -rf S21_3DViewer/*.info S21_3DViewer/report S21_3DViewer/*.out S21_3DViewer/*.gcda S21_3DViewer/*.so S21_3DViewer/*.gcno S21_3DViewer/*.info

.PHONY: all re test gcov_report clean clean_gcov