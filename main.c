#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main()
{

  FILE *encode_in = fopen("en_in.txt", "r");

  FILE *encode_out = fopen("en_out.txt", "w");
  FILE *decode_in = fopen("de_in.txt", "w+");
  FILE *decode_out = fopen("de_out.txt", "w");
  Map m[MAP_SIZE];
  Codes c[MAP_SIZE];

  create_map(encode_in, m);
  Node *hf_root = buildHuffmanTree(m);

  huffmanCodes(m, c);
  /*
    At the end of the while loop what happens is that the file pointer reaches to
     the end of the file(known as EOF). The OS keeps a record of the position of the 
     pointer to keep track of where you are or what your position is in the file so 
     that it can read further from that position. All you need to do is just move 
     that file pointer to the beginning of the file. Now there are two ways for that
      you can use the rewind() method or the fseek() method
    */
  fseek(encode_in, 0, SEEK_SET);
  encoding(encode_in, encode_out, decode_in, c);
  decoding(hf_root, decode_in, decode_out);
  printf("size of map=%d\tsize of codes=%d\n", m->size, c->size);
  fclose(encode_in);
  fclose(encode_out);
  fclose(decode_in);
  fclose(decode_out);
  return 0;
}