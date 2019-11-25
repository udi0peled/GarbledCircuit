CC=gcc
CFLAGS=-I.
main: main.c common_printing.c circuit_parser.c
	$(CC) -g -O0 -o a.out main.c common_printing.c circuit_parser.c -lgcrypt
