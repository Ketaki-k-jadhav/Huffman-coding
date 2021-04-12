#include "huffman.h"

void decoding(FILE *decode_in, FILE *decode_out)
{
    Map map1[MAP_SIZE];
    init_map(map1);

    char c;
    int f = 0, k;
    fscanf(decode_in, "%d\n", &k);
    static int j = 0;

    for (int i = 0; i < k; i++)
    {
        fscanf(decode_in, "%d"
                          "%d\n",
               &c, &f);

        char ch = c;
        map1[j].ch = ch;
        map1[j].freq = f;

        j++;
    }
    map1->size = j;
    Node *root = buildHuffmanTree(map1);
    Node *curr = root;
    while (1)
    {
        c = fgetc(decode_in);
        if (c == EOF)
            break;
        else
        {
            if (c == '0')
                curr = curr->left;

            if (c == '1')
                curr = curr->right;

            if (isLeaf(curr))
            {
                fprintf(decode_out, "%c", curr->c);
                curr = root;
            }
        }
    }
    printf("File is decompressed using huffman decoding and saved in current working directory.\n");
}
