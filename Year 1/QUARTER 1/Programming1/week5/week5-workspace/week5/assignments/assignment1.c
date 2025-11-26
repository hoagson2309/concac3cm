#include <stdio.h>
#include "functions.h"

void roll_dice(int result[], int num_roll) {
    for (int i = 0; i < num_roll; i++) {
        int dice1 = random_int(1, 6);
        int dice2 = random_int(1, 6);
        int sum = dice1 + dice2;
        result[sum - 2]++; //increment count for the sum (2-12) ex: sum=2=[0], sum=3=[1], sum=4=[2],...
    }
}

void print_results(int result[], int num_roll) {
    printf("Results after %d rolls:\n", num_roll);
    for (int i = 0; i < 11; i++) {
        int outcome = i + 2; //adjust each element to the sum (2-12)
        int count = result[i];
        float percentage = (count / (float)num_roll) * 100; //calculate percentage
        printf("%2d: %6d (%.1f%%)\n", outcome, count, percentage); 
    }
}

int main(void) {
    int result[11] = {0}; 
    printf("How many times should the dice be rolled?: ");
    int num_roll = read_int();
    if (num_roll <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    roll_dice(result, num_roll); 
    print_results(result, num_roll);

    return 0;
}
