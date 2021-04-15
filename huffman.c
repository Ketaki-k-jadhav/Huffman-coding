#include "huffman.h"

//Initialise codes
void init_codes(Codes *c)
{
    for (int i = 0; i < MAP_SIZE; i++)
    {
        c[i].cd = (char *)malloc(sizeof(char) * 100);
    }
}

//Initialise map
void init_map(Map *map)
{
    map->size = 0;
    for (int i = 0; i < MAP_SIZE; i++)
    {
        map[i].freq = 0;
    }
}

/*
In this fuction, input file is read character by character and characters
along with their frequencies are stored in a map
*/
void create_map(FILE *fp, Map *map)
{
    init_map(map);
    char c;
    while (1)
    {
        int flag = 0;
        static int count = 0;
        c = fgetc(fp);
        if (c == EOF)
            break;
        else
        {
            for (int i = 0; i < count; i++)
            {
                if (c == map[i].ch)
                {
                    map[i].freq += 1;
                    flag = 1;
                    break;
                }
            }
            if (flag != 1)
            {
                map[count].ch = c;
                map[count].freq += 1;
                count += 1;
            }
        }
        map->size = count;
    }
}

/*
In following function, Huffman tree is build.
Data structure used is minimum heap (frequency of a node will always be less than
both of its children)

So two nodes of minimum frequency are removed from minHeap and a new node is formed 
with frequency equal to sum of the frequencies of two removed nodes. These nodes are 
then assigned as left and right child of new node.This new node is now again 
inserted in min heap.

Above step is repeated until only one node is left.
This is the root node of Huffman tree that we build. 
*/
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

/*
In following function we traverse from root of Huffman tree.
For a given node, left child is assigned with value '0' and 
right child is assigned with value '1'.
In this tree, all characters are present at leaf nodes of the tree.
So the path from root node to a particular leaf node(i.e. a particular character)
is the huffman code for that charcater.
These huffman codes are stored in codes structure.
*/
Codes *buildCodes(Node *root, char a[], int top_i, Codes *codes)
{
    static int j = 0;
    if (root->left)
    {
        a[top_i] = '0';
        buildCodes(root->left, a, top_i + 1, codes);
    }
    if (root->right)
    {
        a[top_i] = '1';
        buildCodes(root->right, a, top_i + 1, codes);
    }
    if (isLeaf(root))
    {
        codes[j].ch = root->c;
        codes[j].len = top_i;
        for (int i = 0; i < top_i; i++)
            codes[j].cd[i] = a[i];
        j++;
    }
    return codes;
}

int huffmanCodes(Map *map, Codes *c)
{
    Node *root = buildHuffmanTree(map);
    char a[100];

    init_codes(c);
    c = buildCodes(root, a, 0, c);
    c->size = map->size;

    int bits = 0;
    for (int j = 0; j < map->size; j++)
    {
        for (int i = 0; i < c[j].len; i++)
            bits++;
    }
    return bits;
}
