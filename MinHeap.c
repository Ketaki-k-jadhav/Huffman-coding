#include "huffman.h"

//new node is created
Node *newNode(char ch, int freq)
{
    Node *n;
    n = (Node *)malloc(sizeof(Node));
    if (n == NULL)
    {
        printf("Memory not allocated.\n");
        exit(0);
    }
    n->c = ch;
    n->freq = freq;
    n->left = n->right = NULL;
    return n;
}

//Minimum heap is created and memory is allocated to minHeap dynamically
MinHeap *createMinHeap(int capacity)
{
    MinHeap *minHeap;
    minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    if (minHeap == NULL)
    {
        printf("Memory not allocated.\n");
        exit(0);
    }
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Node **)malloc(minHeap->capacity * sizeof(Node *));
    if (minHeap->array == NULL)
    {
        printf("Memory not allocated.\n");
        exit(0);
    }
    return minHeap;
}

//function to swap two nodes
void swap(Node **a, Node **b)
{
    Node *temp = *a;
    *a = *b;
    *b = temp;
}

//fuction to check if the size of minHeap is 1 or not
int isSizeOne(MinHeap *minHeap)
{
    return (minHeap->size == 1);
}

//function to check whether a node is leaf node or not
int isLeaf(Node *n)
{
    if (!(n->left) && !(n->right))
        return 1;
    else
        return 0;
}

//heapify function to adjust minHeap after insertion a newly allocated node
void heapify(MinHeap *minHeap, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if ((left < minHeap->size) && (minHeap->array[left]->freq < minHeap->array[smallest]->freq))
    {
        smallest = left;
    }
    if ((right < minHeap->size) && (minHeap->array[right]->freq < minHeap->array[smallest]->freq))
    {
        smallest = right;
    }
    if (smallest != i)
    {
        swap(&minHeap->array[smallest], &minHeap->array[i]);
        heapify(minHeap, smallest);
    }
}

//Function to insert a node in minHeap
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

//Utility function to build minHeap
void buildMinHeap(MinHeap *minHeap)
{
    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
    {
        heapify(minHeap, i);
    }
}

//function to create and build min heap
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

//function to remove a node from minHeap
Node *Remove(MinHeap *minHeap)
{
    Node *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    heapify(minHeap, 0);
    return temp;
}
