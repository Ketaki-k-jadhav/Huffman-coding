#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

void encoding(FILE *encode_in, FILE *encode_out, FILE *decode_in, Codes *codes)
{

    while (1)
    {
        char c = fgetc(encode_in);

        if (c == EOF)
            break;
        else
        {

            for (int j = 0; j < codes->size; j++)
            {
                if (c == codes[j].ch)
                {
                    for (int k = 0; k < codes[j].len; k++)
                    {
                        fprintf(encode_out, "%c", codes[j].cd[k]);
                        fprintf(decode_in, "%c", codes[j].cd[k]);
                    }
                    break;
                }
            }
        }
    }
}
