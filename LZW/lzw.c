#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lzw.h"

void init_dict(Dict *table, int output_codes[])
{
    table[SIZE];
    table->dict_len = 0;
    for (int i = 0; i < SIZE; i++)
        table[i].str = (char *)malloc(sizeof(char) * 50);

    output_codes[SIZE];
    for (int i = 0; i < SIZE; i++)
        output_codes[i] = -1;
}

void encode_lzw(Dict *table, int output_codes[], FILE *encode_in)
{

    init_dict(table, output_codes);
    for (int i = 0; i < 256; i++)
    {
        char ch = i;
        strncat(table[i].str, &ch, 1);
        table[i].code = i;
        table->dict_len++;
    }
    static int j = 0;
    int count = table->dict_len;
    int next_code = 256;

    char p[50], c[50], temp[50];
    strcpy(p, "");
    strcpy(c, "");
    strcpy(temp, "");

    char ch = fgetc(encode_in);

    strncat(p, &ch, 1);

    while (1)
    {
        int flag = 0;

        ch = fgetc(encode_in);
        if (ch == EOF)
            break;
        else
        {
            strncat(c, &ch, 1);
            strcat(temp, p);
            strcat(temp, c);

            for (int i = 0; i < table->dict_len; i++)
            {
                if (!(strcmp(table[i].str, temp)))
                {
                    strncat(p, c, 1);
                    flag = 1;
                }
            }
            if (flag != 1)
            {
                int i;
                for (i = 0; i < table->dict_len; i++)
                {
                    if (!(strcmp(table[i].str, p)))
                    {
                        break;
                    }
                }

                strcpy(table[count].str, temp);
                table[count].code = next_code;

                output_codes[j++] = table[i].code;
                next_code++;
                table->dict_len++;
                count++;
                strcpy(p, "");
                strcpy(temp, "");
                strcpy(p, c);
            }
            strcpy(temp, "");
        }
        strcpy(c, "");
    }

    int i;
    for (i = 0; i < table->dict_len; i++)
    {
        if (!(strcmp(table[i].str, p)))
            break;
    }
    output_codes[j++] = table[i].code;
}

void decode_lzw(int output_codes[], FILE *decode_out)
{
    Dict t[SIZE];
    t->dict_len = 0;
    for (int i = 0; i < SIZE; i++)
        t[i].str = (char *)malloc(sizeof(char) * 50);

    for (int i = 0; i < 256; i++)
    {
        char ch = i;
        strncat(t[i].str, &ch, 1);
        t[i].code = i;
        t->dict_len++;
    }

    int len = 0;
    int count = t->dict_len;

    int old = output_codes[0], n;
    char s[50], c[50], temp[50];

    int i;
    for (i = 0; i < t->dict_len; i++)
    {
        if (t[i].code == old)
            break;
    }
    strcpy(s, "");
    strcpy(s, t[i].str);
    strcpy(c, "");
    char ch = s[0];

    strncat(c, &ch, 1);
    fprintf(decode_out, "%s", s);

    for (int i = 0; output_codes[i] != -1; i++)
        len++;

    for (int i = 0; i < len - 1; i++)
    {
        int flag = 0;
        n = output_codes[i + 1];

        for (int j = 0; j < count; j++)
        {
            if (!(strcmp(t[j].str, t[n].str)))
            {
                flag = 1;
                break;
            }
        }
        if (flag)
        {
            int k;
            for (k = 0; k < count; k++)
            {
                if (!(strcmp(t[k].str, t[n].str)))
                    break;
            }
            strcpy(s, t[k].str);
        }
        if (!flag)
        {
            int k;
            for (k = 0; k < count; k++)
            {
                if (!(strcmp(t[k].str, t[old].str)))
                    break;
            }
            strcpy(s, t[k].str);
            strcat(s, c);
        }
        fprintf(decode_out, "%s", s);
        strcpy(c, "");
        char ch = s[0];

        strncat(c, &ch, 1);
        int k;
        for (k = 0; k < count; k++)
        {
            if (!(strcmp(t[k].str, t[old].str)))
                break;
        }
        //table[count] = table[old] + c;
        strcpy(temp, "");
        strcpy(temp, t[k].str);
        strcat(temp, c);
        strcpy(t[count].str, temp);

        count++;
        t->dict_len++;
        old = n;
    }
}