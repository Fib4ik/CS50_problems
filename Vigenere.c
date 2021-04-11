#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, char **argv)
{
//variables
    int i = 0, key = 0;

//corectly
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    for (int j = 0; j < strlen(argv[1]); j++)
    {
        if (!((argv[1][j] > 64 && argv[1][j] < 91) || (argv[1][j] > 96 && argv[1][j] < 123)))
        {
            printf("Usage: ./vigenere keyword\n");
            return 1;
        }
    }

//input string
    string str = get_string("plaintext:  ");
    char res[32];
    printf("ciphertext: ");

//cycle of brute
    while (i < strlen(str))
    {
        if ((str[i] > 64 && str[i] < 91) || (str[i] > 96 && str[i] < 123))
        {
//coding
            if ((tolower(str[i]) + (tolower(argv[1][key])) - 193) % 26 == 0)
            {
                res[i] = (str[i] - (tolower(str[i]) - 96)) + 26;
            }
            else
            {
                res[i] = (str[i] - (tolower(str[i]) - 96)) + ((tolower(str[i]) + (tolower(argv[1][key])) - 193) % 26);
            }
//setting key
            key++;
            key = (key == strlen(argv[1]))?0:key;
        }
        else
        {
            res[i] = str[i];
        }
        printf("%c", res[i]);
        i++;
    }
    printf("\n");
    return 0;
}
