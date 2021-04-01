#include <stdio.h>
#include <string.h>
#include "huffman.h"

void decoding(Node *root, FILE *encode_out, FILE *decode_out)
{

    Node *curr = root;
    int count = 0;

    while (1)
    {
        char c = fgetc(encode_out);
        count++;

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

    printf("\n");
}
