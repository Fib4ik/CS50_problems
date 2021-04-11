#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h = get_int("Input height\n");         //Getting the length of the pyramid
    while(h > 8 || h < 1)                      //Checking the correctness of the input
    {
        h = get_int("Input height\n");
    }
    for (int i = 0; i < h; i ++)               //Building a pyramid using space and #
    {
        for (int j = h - i - 1; j > 0; j --)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j ++)
        {
            printf("#");
        }
        printf("\n");
    }
}
