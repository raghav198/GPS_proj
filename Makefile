CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror -Wunreachable-code
OBJS = map.o hash.o
HEADERS = map.h hash.h

test: $(OBJS)
	gcc -DTEST $(CFLAGS) *.o -o test

clean:
	/bin/rm -rf *.o
	/bin/rm -rf *.c~
	/bin/rm -rf *.h~

%.o: %.c $(HEADERS)
	gcc -c $< -o $@ $(CFLAGS) $(tests)
