CC=gcc
CFLAGS=-Wall -Wextra -Werror -c -std=c11
GCOVFLAGS:=--coverage
SOURCES:= s21_matrix.c s21_test.c
OBJECTS:=$(SOURCES:.c=.o)
UNAME = $(shell uname -s)
ifeq ($(UNAME),Darwin)
	CHECK=-lcheck -lm -lpthread -fprofile-arcs
endif
ifeq ($(UNAME),Linux)
	CHECK=-lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs
endif

all: test gcov_report

.c.o:
	$(CC) $(CFLAGS) $(GCOVFLAGS) $< -o $@

s21_matrix.a: s21_verter.o
	ar rcs s21_matrix.a s21_verter.o

s21_verter.o: s21_matrix.c
	$(CC) $(CFLAGS) s21_matrix.c -o s21_verter.o

check: lint cppcheck
	
lint:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h
	clang-format -i *.c *.h
	clang-format -n *.c *.h
	rm -rf .clang-format
	
cppcheck:
	cppcheck —enable=all —suppress=missingIncludeSystem *.c *.h

test: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(CHECK)
	./$@

gcov_report:
	gcovr -r . --html --html-details -o coverage_report.html
	gcov -f s21_matrix.gcda
	open coverage_report.html

rebuild: clean all

clean:
	rm -rf a.* test s21_matrix.a *.o *.gc* *.css *.html

.PHONY: all clean check test

