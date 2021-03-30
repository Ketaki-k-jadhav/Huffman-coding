#include <stdio.h>
#include "huffman.h"

void decoding(Node *root, FILE *decode_in, FILE *decode_out)
{

    Node *curr = root;
    while (1)
    {
        char c = fgetc(decode_in);
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
}
