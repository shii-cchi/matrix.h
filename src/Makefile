CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
GCOV_FLAG = -fprofile-arcs -ftest-coverage -fPIC -O0
GCOV_FLAG_TEST = --coverage
TEST_FLAG = -lcheck
LINUX_FLAG = -lm -lsubunit -lrt -lpthread
ifeq ($(shell uname), Linux)
	TEST_FLAG += $(LINUX_FLAG)
endif
SOURCES_1 = _matrix.c
SOURCES_2 = _matrix.o
SOURCES_3 = test/test.c 
SOURCES_4 = test.o

all: clean matrix.a

matrix.a:
	$(CC) $(CFLAGS) -c $(SOURCES_1)
	ar rc _matrix.a $(SOURCES_2)
	ranlib _matrix.a
	-rm -rf *.o

test_matrix.a:
	$(CC) $(CFLAGS) $(GCOV_FLAG) -c $(SOURCES_1)
	ar rc _matrix.a $(SOURCES_2)
	ranlib _matrix.a

test: clean test_matrix.a
	$(CC) $(CFLAGS) -c $(SOURCES_3)
	$(CC) $(CFLAGS) $(GCOV_FLAG_TEST) -o tests $(SOURCES_4) _matrix.a $(TEST_FLAG)
	-rm -rf *.o
	./tests

gcov_report: clean test
	gcovr -r . --html-details -o report_matrix.html

clean:
	-rm -rf *.o *.a *.out *.gcda *.gcno *.html *.css *.log
	-rm -f tests