#include "huffman.h"

/*
this function helps to extract extension(sequence of characters after
'.'symbol) from the filename.
*/
const char *get_filename_ext(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename)
        return "";
    return dot + 1;
}

/*
For the following function,
input file pointer=decode_in
decoded/output file pointer=decode_out
*/
void decoding(FILE *decode_in, FILE *decode_out)
{
    //check if the input file is empty or not
    fseek(decode_in, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(decode_in);
    if (len == 0)
    {
        printf("File is empty !!");
        exit(0);
    }
    fseek(decode_in, 0, SEEK_SET);

    //Structure map to store characters with their frequencies from compressed file
    Map map1[MAP_SIZE];
    init_map(map1);

    char c;
    int f = 0, k;

    //From the first line of  compressed file, number of characters are stored in varaible k
    fscanf(decode_in, "%d\n", &k);
    static int j = 0;

    // k number of characters along with their frequencies are stored in map.
    for (int i = 0; i < k; i++)
    {
        fscanf(decode_in, "%d"
                          "%d\n",
               &c, &f);

        char ch = c;
        map1[j].ch = ch;
        map1[j].freq = f;

        j++;
    }
    map1->size = j;

    //Correspondig Huffman tree is build with help of map.
    Node *root = buildHuffmanTree(map1);
    Node *curr = root;

    /*
    Algorithm for decoding:
    We start from root and do following until a leaf node is found.
    1.If current bit is 0, we move to left node of the tree.
    2.If the bit is 1, we move to right node of the tree.
    3.If during traversal, we encounter a leaf node, we print character of that
    particular leaf node and then again continue the iteration of the encoded 
    data starting from step 1.
    */
    while (1)
    {
        c = fgetc(decode_in);
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
    printf("File is decoded using huffman decoding and saved as 'decoded_file.txt' in current working directory.\n");
}
