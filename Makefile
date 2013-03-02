CFLAGS = -Wall -ansi -pedantic -x c

all: ls1p.o

clean:
	rm -f *.o

check: test

test: ls1p_tests
	./ls1p_tests

ls1p_tests: ls1p.o ls1p_tests.o
	$(CC) $(LDFLAGS) ls1p.o ls1p_tests.o -o ls1p_tests

.PHONY: clean test check all
