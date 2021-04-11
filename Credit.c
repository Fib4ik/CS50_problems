#include <stdio.h>
#include <cs50.h>

int main(void)
{
//Declaring Variables
    long number = get_long("Number: ");
    int sum, first_num, tmp, len = 1;

//Reflection of code
    while (number != 0)
    {
        if (number < 100 && number > 9)
        {
            tmp = number;
            first_num = (tmp % 10);
            tmp = tmp / 10;
            first_num = first_num + 10 * (tmp % 10);
        }
        tmp = (number % 10);
        number = number / 10;
        if (len % 2 == 0)
        {
            if (tmp * 2 > 9)
            {
                tmp = tmp * 2;
                sum = sum + tmp % 10;
                tmp = tmp / 10;
                sum = sum + tmp;
            }
            else
            {
                sum = sum + (tmp * 2);
            }
        }
        else
        {
            sum = sum + tmp;
        }
        len++;
    }

    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if ((first_num == 37 || first_num == 34) && len == 16)
    {
        printf("AMEX\n");
    }
    else if ((first_num < 56 && first_num > 50) && len == 17)
    {
        printf("MASTERCARD\n");
    }
    else if (first_num / 10 == 4 && (len == 14 || len == 17))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}