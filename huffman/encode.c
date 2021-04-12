#include "huffman.h"

void encoding(FILE *encode_in, FILE *encode_out, Codes *codes, Map *map)
{
    fprintf(encode_out, "%d\n", map->size);
    for (int i = 0; i < map->size; i++)
    {
        fprintf(encode_out, "%d %d\n", map[i].ch, map[i].freq);
    }

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
                fprintf(encode_out, "%d", codes[j].cd[k]);
            }
        }
    }
    printf("File is compressed using Huffman Compression algorithm and saved in current working directory\n");
}
