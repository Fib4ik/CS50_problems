#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //variables
    int c = 0;
    float mm = get_float("Change owed: "); //input number
    int m; //round number
    //cycle
    while(mm < 0){m = get_float("Change owed: ");}
    //round
    m = round(mm * 100);
    //coins
    while(m > 0)
    {
        if(m >= 25)
        {
            m-=25;c++;
        }
        else if(m >= 10)
        {
            m-=10;c++;
        }
        else if(m >= 5)
        {
            m-=5;c++;
        }
        else
        {
            m-=1;c++;
        }
    }
    printf("%i\n", c);
}
