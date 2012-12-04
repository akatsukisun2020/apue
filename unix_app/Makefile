CC = gcc -O2

.PHONY: all clean
all:	hello_multi incrprint

hello_multi:hello_multi.c
	$(CC) $< -o $@ -lpthread
incrprint:incrprint.c
	$(CC) $< -o $@ -lpthread

clean:
	rm -f *.o
