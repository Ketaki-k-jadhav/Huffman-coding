#include "huffman.h"

/*
For the following function,
input file pointer=encode_in
decoded/output file pointer=encode_out
*/
void encoding(FILE *encode_in, FILE *encode_out)
{
    //check if the file is empty or not
    fseek(encode_in, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(encode_in);
    if (len == 0)
    {
        printf("File is empty !!");
        exit(0);
    }
    fseek(encode_in, 0, SEEK_SET);

    //Map with characters and their frequencies :
    Map map[MAP_SIZE];
    create_map(encode_in, map);

    //Huffman tree is build:
    Node *hf_root = buildHuffmanTree(map);

    /*
    Huffman codes for characters appeared in the iput file are build and stored
    in a structure called Codes.
    */
    Codes codes[MAP_SIZE];
    huffmanCodes(map, codes);

    /*
    Characters with their frequencies are stored in compressed file
    (helps during decoding)
    */
    fprintf(encode_out, "%d\n", map->size);
    for (int i = 0; i < map->size; i++)
    {
        fprintf(encode_out, "%d %d\n", map[i].ch, map[i].freq);
    }

    /*
    At the end of the while loop what happens is that the file pointer reaches to
    the end of the file(known as EOF). The OS keeps a record of the position of the 
    pointer to keep track of where you are or what your position is in the file so 
    that it can read further from that position. 
    So for moving file pointer to the beginning of the file,fseek() method is used.
    */
    fseek(encode_in, 0, SEEK_SET);

    /*
    Characters from corresponding input file are replaced with their 
    respective huffman codes in compressed file.
    */
    int ibits = 0, ebits = 0;
    char c;
    while (1)
    {
        c = fgetc(encode_in);

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
                ebits++;
                fprintf(encode_out, "%c", codes[j].cd[k]);
            }
        }
        ibits++;
    }
    ibits *= 8;
    float res = ((ibits - ebits) * 100) / ibits;
    printf("File is encoded using Huffman Coding algorithm and"
           " saved as 'encoded_file.huf' in \t current working directory\n");
    printf("Number of bits consumed in input file=%d\n", ibits);
    printf("Number of bits consumed in encoded file=%d\n", ebits);
    printf("%.2f %% of data compression takes place after Huffman encoding\n", res);
}
