#include "huffman.h"

void init_codes(Codes *c)
{
    for (int i = 0; i < MAP_SIZE; i++)
    {
        c[i].cd = (int *)malloc(sizeof(int) * 100);
    }
}

void init_map(Map *map)
{
    map->size = 0;
    for (int i = 0; i < MAP_SIZE; i++)
    {
        map[i].freq = 0;
    }
}

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

Codes *buildCodes(Node *root, int a[], int top_i, Codes *codes)
{
    static int j = 0;
    if (root->left)
    {
        a[top_i] = 0;
        buildCodes(root->left, a, top_i + 1, codes);
    }
    if (root->right)
    {
        a[top_i] = 1;
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
    int a[100];

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
