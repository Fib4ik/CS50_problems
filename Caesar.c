#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>

int main(int argc, char **argv)
{
	//Checking for correctness
    if(argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }else{
        for(int i = 0; i < strlen(argv[1]); i++)
        {

            if((int)argv[1][i] > '9' || (int)argv[1][i] < '0')
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }

    //Char to int
    int key = atoi(argv[1]) % 26;

    //input a string
    string str = get_string("plaintext:  ");

    //updating text
    while(key != 0)
    {
        for(int i = 0; i < strlen(str); i++)
        {
            if((str[i] > 64 && str[i] < 91 )||(str[i] > 96 && str[i] < 123))
            {
                if(str[i] == 'z')
                {
                    str[i] = 'a';                
                }
                else if(str[i] == 'Z')
                {
                    str[i] = 'A';
                }
                else
                {
                    str[i] = (char)((int)str[i] + 1);
                }
            }
        }
        key--;
    }
    
    printf("ciphertext: %s\n", str);
    return 0;
}
