# Week XX - Assignments

Name: SON CAO

Group: ETI1V.IA

Date: 6/10/2024

**NOTE**: if you'd like to have syntax highlighting in your markdown file, install the "Markdown Preview Github Styling" extension in VS Code.

## First assignment

The first assignment I completed is assignment 1 - Dice sums .
This is the code I wrote:

```c
// TODO: Write your code here
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

```

## Second assignment

The second assignment I completed is assignment 2 - Mean removal.
This is the code I wrote:

```c
// TODO: Write your code here
#include <stdio.h>
#include "functions.h"

/// @brief Fill an array with random floating point numbers between -10 and 10.
/// @param array The array to fill.
/// @param size The size of the array.
void fill_array(float array[], int size){
    float a = size;
    for(int i=0; i<size; i++){
        array[i] = random_float(-a,a);
    }
}

/// @brief Print an array of floating point numbers, comma-separated.
/// @param array The array to print.
/// @param size The size of the array.
void print_array(const float array[], int size){
    bool printed_first = false;
    for(int i=0; i<size; i++){
        if(printed_first) printf(", ");
        printed_first = true;
        printf("%.2f", array[i]);
    }
    printf(".\n");
}

/// @brief Compute the mean of an array of floating point numbers.
/// @param array The array to compute the mean of.
/// @param size The size of the array.
/// @return The mean of the array.
float mean(const float array[], int size){
    float total = 0;
    for(int i=0; i<size; i++){
        total += array[i];
    }
    float mean = total / size;
    return mean;
}

/// @brief Remove the mean from an array of floating point numbers.
/// @param array The array to remove the mean from.
/// @param size The size of the array.
/// @param mean The mean to remove.
void remove_mean(float array[], int size, float mean){
    for(int i=0; i<size; i++){
        array[i] -= mean;
    }
}

int main(void) {
    printf("Give the size: ");
    int size = read_int();
    float array[size];
    float Mean = 0.00f;

    fill_array(array, size);
    Mean = mean(array, size);

    printf("Before: ");
    print_array(array, size);

    printf("Mean: ");
    printf("%.2f", Mean);

    remove_mean(array, size, Mean);

    printf("\nAfter: ");
    print_array(array, size);
    
    return 0;
}
```

## Third assignment (optional)

I've actually made three assignments this week! The third assignment I completed is assignment ZZZ.
This is the code I wrote:

```c
// TODO: Write your code here
```
