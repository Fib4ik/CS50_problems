//Hacking_Simple_Hash.c
//C language
//Repository on git "C_Language"

//Importing all libraries
#define _XOPEN_SOURCE    //So it was written in the documentation, this is an addition to the bottom line
#include <unistd.h>      //Hashing library
#include <crypt.h>       //Crypting library
#include <stdio.h>       //Standard library (input / output)
#include <string.h>      //Library for working with strings

int main(int argc, char **argv) //Function with data entry via command line
{
    if (argc != 2)       //If there are not two arguments, then we shout about errors
    {
        printf("Syntax ERROR!\n");
        return 1;
    }


//Dictionary of Symbols
    char alf[52] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
// Variables for further work (password - password storage, salt - salt storage,
// num - number of the current character in the password array,
// j - copy of i in the main loop, rest - remainder of division)
    char password[6], salt[2];
    int num, j, rest;
//Getting salt
    salt[0] = argv[1][0];
    salt[1] = argv[1][1];


//Fix code, loop skips "q"
    if (strcmp(crypt("q", salt), argv[1]) == 0)
    {
        printf("Password cracking complete\nThe password is: q\nGoodbye\n");
        return 0;
    }


//Main loop
    for (int i = 1; i < 380204033; i++)
    {
//Zeroing Variables
        num = 0;
        j = i;
//Converting a decimal number to a character code
        while (j != 0)
        {
            rest = j % 52;             //Get the remainder of the division
            j = j / 52;                //Decrease the number
            password[num] = alf[rest]; //Assigning a symbol to a password
            num++;                     //Add the next character
        }
        printf("%s - %s\n", crypt(password, salt), password);
        if (strcmp(crypt(password, salt), argv[1]) == 0) //If the encrypted text and the input match, stop and output
        {
            printf("Password cracking complete\nThe password is: %s\nGoodbye\n", password);
            return 0;
        }
    }
}