#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED
#define MAP_SIZE 256
#define EMPTY_STRING ""

typedef struct Map
{
    int size;
    char ch;
    int freq;

} Map;

typedef struct Codes
{
    int size;
    char ch;
    char *cd;
    int len;

} Codes;
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

void init_map(Map *m);
void create_map(FILE *fp, Map *map);
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

Node *buildHuffmanTree(Map *map);
Codes *printCodes(Node *root, char a[], int i, Codes *codes);
void init_codes(Codes *codes);
void huffmanCodes(Map *map, Codes *c);

void encoding(FILE *encode_in, FILE *encode_out, Codes *codes);
void decoding(Node *root, FILE *encode_out, FILE *decode_out);

#endif