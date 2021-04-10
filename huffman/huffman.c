#include <stdio.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
#include "huffman.h"

void init_codes(Codes *c)
{
    for (int i = 0; i < MAP_SIZE; i++)
    {
        c[i].cd = (char *)malloc(sizeof(char) * 100);
    }
}
Node *buildHuffmanTree(Map *map)
{
    Node *left, *right, *top;
    MinHeap *minHeap = CreateAndBuildMinheap(map);

    while (!isSizeOne(minHeap))
    {
        left = Remove(minHeap);
        right = Remove(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(top, minHeap);
    }
    Node *root = Remove(minHeap);

    return root;
}

Codes *printCodes(Node *root, char a[], int top_i, Codes *codes)
{

    static int j = 0;
    if (root->left)
    {
        a[top_i] = '0';

        printCodes(root->left, a, top_i + 1, codes);
    }
    if (root->right)
    {
        a[top_i] = '1';

        printCodes(root->right, a, top_i + 1, codes);
    }
    if (isLeaf(root))
    {
        printf("%c: ", root->c);
        codes[j].ch = root->c;
        codes[j].len = top_i;
        for (int i = 0; i < top_i; i++)
        {
            printf("%c ", a[i]);
            codes[j].cd[i] = a[i];
        }
        printf("\n");

        j++;
    }
    return codes;
}

void huffmanCodes(Map *map, Codes *c)
{
    Node *root = buildHuffmanTree(map);
    char a[100];
    init_codes(c);
    c = printCodes(root, a, 0, c);
    c->size = map->size;
    int bits = 0;
    for (int j = 0; j < map->size; j++)
    {
        for (int i = 0; i < c[j].len; i++)
            bits++;
    }
}
