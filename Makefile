CC = gcc
CFLAGS = -Wall -g

build: sudoku

sudoku: functii.c functii_coada.c functii_sudoku.c main.c
	$(CC) $(CFLAGS) $^ -O3 -o $@

run:
	./sudoku

.PHONY: clean

clean:
	rm -f *.o *~ sudoku valgrind.txt

valgrind:
	valgrind --leak-check=yes --track-origins=yes ./sudoku > valgrind.txt 2>&1