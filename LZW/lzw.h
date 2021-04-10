#ifndef LZW_H_INCLUDED
#define LZW_H_INCLUDED
#define SIZE 2000

typedef struct Dict
{
    char *str;
    int code;
    int dict_len;
} Dict;

void init_dict(Dict *table, int output_codes[]);
void encode_lzw(Dict *table, int output_codes[], FILE *encode_in);
void decode_lzw(int output_codes[], FILE *decode_out);

#endif