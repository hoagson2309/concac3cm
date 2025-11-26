#include <stdio.h>
#include "functions.h"
#include <stdbool.h> 
#include "days.h"


int main(void) {
    // Get the current date
    int current_date[3];    // day, month, year
    get_current_date(current_date);
    int current_year = current_date[0];     // the current year
    int current_month = current_date[1];    // the current month
    int current_day = current_date[2];      // the current day

    // Get the birthdate from the user
    printf("Enter de day of your birthdate: ");
    int day = read_int();
    printf("Enter the month of your birthdate: ");
    int month = read_int();
    printf("Enter the year of your birthdate: ");
    int year = read_int();

    // TODO: Calculate the number of days between the birthdate and the current date
    int days_lived = days_between_dates(day, month, year, current_day, current_month, current_year);    // FIXME: replace this with the correct calculation

    // Print the result
    printf("Today is the %dth day of your life\n", days_lived);

    return 0;
}
















