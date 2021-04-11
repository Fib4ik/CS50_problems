#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h = get_int("Input height\n");
    while(h > 8 || h < 1)
    {
        h = get_int("Input height\n");
    }
    for (int i = 0; i < h; i ++)
    {
        for (int j = h - i - 1; j > 0; j --)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j ++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j < i + 1; j ++)
        {
            printf("#");
        }
        printf("\n");
    }
}