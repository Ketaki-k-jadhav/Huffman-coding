#include "huffman.h"
#include "MinHeap.c"
#include "huffman.c"
#include "encode.c"
#include "decode.c"

void menu()
{

  printf("-----------------------------MENU--------------------------\n");
  printf("1.For Huffman Coding:\n");
  printf("Enter <./compiled-file-name><space><-hc><space><Name-of-the-text-file-to-encode>\n\n");
  printf("2.For Huffman Decoding:\n");
  printf("Enter <./compiled-file-name><space><-hd><space><Name-of-the-file-to-decode>\n\n");
}

int main(int argc, char *argv[])
{

  if (argc < 3)
  {
    printf("Invalid input!!\nRead the menu carefully.\n");
    menu();
  }
  else
  {
    if ((strcmp(argv[1], "-hc")) == 0)
    {
      FILE *encode_in = fopen(argv[2], "r");
      if (encode_in)
      {
        FILE *encode_out = fopen("encoded_file.huf", "w");
        encoding(encode_in, encode_out);

        fclose(encode_in);
        fclose(encode_out);
      }
      else
      {
        printf("'%s' file does not exist in current working directory.\n", argv[2]);
      }
    }
    else if ((strcmp(argv[1], "-hd") == 0))
    {
      FILE *decode_in = fopen(argv[2], "r");
      if (decode_in && (strcmp(get_filename_ext(argv[2]), "huf")) == 0)
      {
        FILE *decode_out = fopen("decoded_file.txt", "w");
        decoding(decode_in, decode_out);
        fclose(decode_in);
        fclose(decode_out);
      }
      else
      {
        if (decode_in == NULL)
          printf("'%s' file does not exist in current working directory\n", argv[2]);
        else if ((strcmp(get_filename_ext(argv[2]), "huf")) != 0)
          printf("Invalid file format !!\nIn order to decode a file using "
                 "huffman decoding algorithm, filename should have '.huf' extension\n");
        else
          printf("Invalid file input");
      }
    }
  }
  return 0;
}
