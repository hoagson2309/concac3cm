#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#include <stdbool.h>

int main(void)
{
    const int maxnumber = 10;
    int number[maxnumber];
    int count = 0;
    bool print_first = false;

    for (int i = 0; i < maxnumber; i++)
    {
        printf("Enter a number (negative to stop): ");
        int ans = read_int();
        if (ans < 0)
        {
            break;
        }

        number[count] = ans;
        count++;
    }
    bool even_found = false;
    printf("Even number: ");
    for (int i = 0; i < count; i++)
    {
        if (number[i] % 2 == 0)
        {
            if (print_first){
                printf(", ");
            }
            print_first = true;
            printf("%d ", number[i]);
            even_found = true;
        }
    }
        if (!even_found)
        {
            printf("No even numbers were entered\n");
        }
    
    return 0;
}
