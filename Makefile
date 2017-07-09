CC=gcc
CFLAGS=-ggdb -O0
LDFLAGS=-L/usr/lib -lssl -lcrypto

all:
	$(CC) $(CFLAGS) -c hhash.c
	$(CC) $(CFLAGS) -c test.c
	$(CC) -o hhash_test test.o hhash.o $(LDFLAGS) 
clean:
	rm *.o hhash_test
