#include <io.h>
#include "huffman.h"
#include "MinHeap.c"
#include "huffman.c"
#include "encode.c"
#include "decode.c"

void menu()
{
  printf("To run the file correctly read the menu and give input accordingly\n");
  printf("\t\t\t\tMENU\n");
  printf("1.For Huffman Compression:\n");
  printf("Enter <./compiled-file-name><space><-hc><space><Name of the text file to compress>\n");
  printf("2.For Huffman Decompression:\n");
  printf("Enter <./compiled-file-name><space><-hd><space><Name of the file to decompress>\n");
}

int main(int argc, char *argv[])
{

  if (argc < 3)
  {
    printf("Invalid input!!\n\nRead the menu carefully and give proper input\n");
    menu();
  }
  else
  {
    if ((strcmp(argv[1], "-hc")) == 0)
    {
      FILE *encode_in = fopen(argv[2], "r");
      FILE *encode_out = fopen("encoded_output.huf", "w");
      if (access(encode_in, F_OK) == 0)
      {
        // file exists
      }
      else
      {
        // file doesn't exist
      }
      Map m[MAP_SIZE];
      create_map(encode_in, m);
      Node *hf_root = buildHuffmanTree(m);
      Codes c[MAP_SIZE];
      huffmanCodes(m, c);

      fseek(encode_in, 0, SEEK_SET);
      encoding(encode_in, encode_out, c, m);

      fclose(encode_in);
      fclose(encode_out);
    }
    if ((strcmp(argv[1], "-hd") == 0))
    {
      FILE *decode_in = fopen(argv[2], "r");
      FILE *decode_out = fopen("decoded_output.txt", "w");
      decoding(decode_in, decode_out);
      fclose(decode_in);
      fclose(decode_out);
    }
  }
  return 0;
}

/*
    At the end of the while loop what happens is that the file pointer reaches to
    the end of the file(known as EOF). The OS keeps a record of the position of the 
    pointer to keep track of where you are or what your position is in the file so 
    that it can read further from that position. All you need to do is just move 
    that file pointer to the beginning of the file. So for that use the fseek() method
    */
