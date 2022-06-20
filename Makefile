CC=gcc
CF=-c -Wall -Wextra -pedantic -std=c99
F=-Wall -Wextra -pedantic -std=c99

all: huffman

force:main.c huffman.c MinHeap.c encode.c decode.c
	$(CC) $(F) main.c huffman.c MinHeap.c encode.c decode.c -o output

huffman:main.o huffman.o MinHeap.o encode.o decode.o
	$(CC) main.o huffman.o MinHeap.o encode.o decode.o -o output

main.o: main.c
	$(CC) $(CF) main.c

huffman.o: huffman.c
	$(CC) $(CF) huffman.c

MinHeap.o: MinHeap.c
	$(CC) $(CF) MinHeap.c

encode.o: encode.c
	$(CC) $(CF) encode.c

decode.o: decode.c
	$(CC) $(CF) decode.c
clean:
	rm -rf *.o editorl