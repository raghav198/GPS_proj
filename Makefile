CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror -Wunreachable-code
OBJS = map.o hash.o queue.o
HEADERS = map.h hash.h queue.h
TEST = QUEUE

test: $(OBJS)
	gcc -DTEST_$(TEST) $(CFLAGS) *.o -o test

clean:
	/bin/rm -rf *.o
	/bin/rm -rf *.c~
	/bin/rm -rf *.h~
	/bin/rm -rf test

%.o: %.c $(HEADERS)
	gcc -DTEST_$(TEST) -c $< -o $@ $(CFLAGS) $(tests)
