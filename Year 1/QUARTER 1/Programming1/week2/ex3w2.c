#include <stdio.h>
#include "functions.h"

int main(void)
{
    printf("Please enter the number of hours: ");
    float hours = read_float();
    int totalseconds = hours * 3600;   
    int totalhours = totalseconds / 3600;  
    int remainingseconds = totalseconds % 3600;   
    int totalminutes = remainingseconds / 60;      
    remainingseconds = remainingseconds % 60; 
    printf("%.2f hours is %d hours, %d minutes and %d seconds.\n", hours, totalhours, totalminutes, remainingseconds);
    return 0;
}
