#include <stdio.h>
#include "functions.h"
#include <stdbool.h>

bool is_leap_year(int year)
{
    if (year % 400 == 0)
    {
        return true;
    }
    else if (year % 100 == 0)
    {
        return false;
    }
    else if (year % 4 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int days_in_month(int month, int year)
{
    int days;
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        days = 31;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        days = 30;
    }

    else if (is_leap_year(year))
    {
        days = 29;
    }
    else
    {
        days = 28;
    }
    return days;
}

int day_in_year(int day, int month, int year){

    int count = 1, x = 0;
    while (count < month){
        x += days_in_month(count, year);
        count++;
    }   
    x += day;
    return x;
}

int remaining_days_in_year(int day, int month, int year){
    int x = day_in_year(day, month, year);
    int remaindays;
   if (is_leap_year(year)){
        remaindays = 366 - x;     
    } else{
        remaindays = 365 - x;
    }
    return remaindays;
}

int days_between_dates(int day1, int month1, int year1, int day2, int month2, int year2){ 
    int count = year1;
    int days = 0;
    while(count <= year2){
        if(is_leap_year(count)){
            days += 366;
        }
        else{
            days += 365;
        }
        count++;
    }
    days -= day_in_year(day1, month1, year1);
    days -= remaining_days_in_year(day2, month2, year2);
    return days;
}