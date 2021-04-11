#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("Your name\n"); //Entering text
    printf("hello, %s\n", name);             //Text output
}