CFLAGS = -Wall -ansi -pedantic -x c

all: ls1p.o

clean:
	rm -fv *.o *_tests

check: test

test: ls1p_tests
	./ls1p_tests

ls1p_tests: ls1p.o ls1p_tests.o
	$(CC) $(LDFLAGS) ls1p.o ls1p_tests.o -o ls1p_tests

ax25_io_tests: ls1p.o ax25_io.o ax25_io_tests.o
	$(CC) $(LDFLAGS) ls1p.o ax25_io.o ax25_io_tests.o -lax25 -o ax25_io_tests

.PHONY: clean test check all
