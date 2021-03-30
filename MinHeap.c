#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

void init_map(Map *map)
{
    map->size = 0;

    for (int i = 0; i < MAP_SIZE; i++)
        map[i].freq = 0;
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

Node *newNode(char ch, int freq)
{
    Node *n;
    n = (Node *)malloc(sizeof(Node));
    n->c = ch;
    n->freq = freq;
    n->left = n->right = NULL;

    return n;
}

MinHeap *createMinHeap(int capacity)
{
    MinHeap *minHeap;
    minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Node **)malloc(minHeap->capacity * sizeof(Node *));

    return minHeap;
}

void swap(Node **a, Node **b)
{
    Node *temp = *a;
    *a = *b;
    *b = temp;
}

int isSizeOne(MinHeap *minHeap)
{

    return (minHeap->size == 1);
}

int isLeaf(Node *n)
{
    if (!(n->left) && !(n->right))
        return 1;
    return 0;
}

void print(int array[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void heapify(MinHeap *minHeap, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if ((left < minHeap->size) && (minHeap->array[left]->freq < minHeap->array[smallest]->freq))
        smallest = left;

    if ((right < minHeap->size) && (minHeap->array[right]->freq < minHeap->array[smallest]->freq))
        smallest = right;

    if (smallest != i)
    {
        swap(&minHeap->array[smallest], &minHeap->array[i]);
        heapify(minHeap, smallest);
    }
}

void insertMinHeap(Node *n, MinHeap *minHeap)
{
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && n->freq < minHeap->array[(i - 1) / 2]->freq)
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = n;
}

void buildMinHeap(MinHeap *minHeap)
{
    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
    {
        heapify(minHeap, i);
    }
}

MinHeap *CreateAndBuildMinheap(Map *map)
{
    MinHeap *minHeap = createMinHeap(map->size);
    for (int i = 0; i < map->size; ++i)
    {
        minHeap->array[i] = newNode(map[i].ch, map[i].freq);
    }
    minHeap->size = map->size;
    buildMinHeap(minHeap);

    return minHeap;
}

Node *Remove(MinHeap *minHeap)
{
    Node *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;

    heapify(minHeap, 0);

    return temp;
}
