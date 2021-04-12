#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAP_SIZE 256
#define EMPTY_STRING ""

typedef struct Map
{
    int size;
    char ch;
    int freq;
} Map;

typedef struct Node
{
    char c;
    int freq;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct MinHeap
{
    int size;
    int capacity;
    Node **array;
} MinHeap;

typedef struct Codes
{
    int size;
    char ch;
    int *cd;
    int len;
} Codes;

//functions to create map of characters and their frequencies
void init_map(Map *m);
void create_map(FILE *fp, Map *map);

//functions to build minimum heap
Node *newNode(char ch, int freq);
MinHeap *createMinHeap(int capacity);
void swap(Node **a, Node **b);
int isSizeOne(MinHeap *minHeap);
int isLeaf(Node *n);
void print(int array[], int n);
void heapify(MinHeap *minHeap, int i);
void insertMinHeap(Node *n, MinHeap *minHeap);
void buildMinHeap(MinHeap *minHeap);
MinHeap *CreateAndBuildMinheap(Map *map);
Node *Remove(MinHeap *minHeap);

//functions to build huffman tree and huffman codes
Node *buildHuffmanTree(Map *map);
void init_codes(Codes *codes);
Codes *buildCodes(Node *root, int a[], int i, Codes *codes);
int huffmanCodes(Map *map, Codes *c);

//functions for encoding and decoding
void encoding(FILE *encode_in, FILE *encode_out, Codes *codes, Map *map);
void decoding(FILE *decode_in, FILE *decode_out);

void test(FILE *decode_in);

#endif