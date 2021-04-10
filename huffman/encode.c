#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

void encoding(FILE *encode_in, FILE *encode_out, Codes *codes)
{
    int count = 0;

    printf("writing into decode in:\n");
    while (1)
    {
        char c = fgetc(encode_in);

        if (c == EOF)
            break;
        else
        {
            int j;
            for (j = 0; j < codes->size; j++)
            {
                if (c == codes[j].ch)
                    break;
            }

            for (int k = 0; k < codes[j].len; k++)
            {
                fprintf(encode_out, "%c", codes[j].cd[k]);
            }
        }
    }
}
