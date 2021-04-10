#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lzw.h"

int main()
{
    FILE *encode_in = fopen("en-in.txt", "r");
    FILE *decode_out = fopen("de-out.txt", "w");
    Dict t[SIZE];
    int output_codes[SIZE];
    encode_lzw(t, output_codes, encode_in);
    printf("\nOutput codes:\n");
    for (int i = 0; output_codes[i] != -1; i++)
        printf("%d ", output_codes[i]);

    decode_lzw(output_codes, decode_out);

    return 0;
}