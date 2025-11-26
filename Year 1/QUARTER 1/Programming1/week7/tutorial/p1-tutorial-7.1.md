# Week 7 - Tutorial: Basic array algorithms

Name: SON CAO

Group: ETI1V.IA

Date: 15/10/2024

## Introduction

Algorithms are the heart of computer science, and are used to solve problems by performing a sequence of steps.
They can be used to manipulate data, search for specific values, sort data, and much more.
There are many different algorithms, each with its own strengths and weaknesses.
In this week, you'll apply some basic algorithms to arrays.

### Activity 1 - Open the workspace for this week

Open the workspace for this week that you downloaded from Brightspace by opening the `.code-workspace` file in the root of the workspace folder.
Alternatively, you can open the workspace from a WSL terminal by typing the `code week7.code-workspace` command in the folder where you extracted the workspace.

## Accumulator variables & reduction algorithms

An accumulator variable is a variable that is used to store the result of a computation that is built up over time.
For example, to calculate the sum of all elements in an array, you could use an accumulator variable to store the sum as you iterate over the array:

```c
float compute_sum(float numbers[], size_t size) {
    float sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += numbers[i];
    }
    return sum;
}
```

There are many computations that can be expressed as a reduction algorithm, which is an algorithm that reduces a list of values to a single value.
Here are some examples of reduction algorithms:

* Summing all elements in an array.
* Finding the maximum or minimum value in an array.
* Finding out if an array contains a specific value.
* Counting the number of elements in an array that satisfy a certain condition.
* Computing the average of all elements in an array.
* Concatenating all strings in an array into a single string.

### Activity 2 - Check if an array contains a specific value

Write a function that checks if an array of integers contains a specific value, by writing a reduction algorithm that uses an accumulator variable, similar to the `compute_sum` function above.
The function must have the following signature (provided in the file `week7.h`):

```c
bool contains_int(const int numbers[], size_t size, int value);
```

Write the definition of the function in `week7.c`, and use the program of `activity2.c` to test your function.
When done, include the definition of `contains_int` in the code block below.

```c
// TODO: put your definition of the function contains_int here
bool contains_int(const int numbers[], size_t size, int value) {
    for(size_t i = 0; i < size; i++){
        if(numbers[i] == value){
            return true;
        }
    }
    return false;
}
```

### Activity 3 - Check if an array contains duplicates

Write a function that checks if an array of integers contains any duplicate values, by writing a reduction algorithm that uses the function from the previous activity:

1. Initialize the accumulator variable to `false` (i.e., assume the array does not contain any duplicates).
2. Traverse the array, and for each element at index `i`:
    1. Check if the element is already in the array at an index lower than `i` (pass the correct arguments to the function from the previous activity).
    2. If it is, set the accumulator variable to `true`.
 3. Return the accumulator variable.

Test the program by using the program of `activity3.c`.
When done, include the definition of `contains_duplicates` in the code block below.

```c
// TODO: put your definition of the function contains_duplicates here
bool has_duplicates(const int numbers[], size_t size){
    bool contains_duplicates = false;
    for(size_t i = 0; i < size && !contains_duplicates; i++){
        if(contains_int(numbers, size, numbers[i])){
            contains_duplicates = true;
        } 
    }
    return contains_duplicates;
}
```

## Removing elements from an array

Arrays store a fixed number of elements in a contiguous (i.e., without any gaps) block of memory.
Although we can't really "remove" an element from an array, we can simulate this by overwriting the element with another value.
For example, the following code snippet removes the element at index 3 from the array of integers `numbers`:

```c
int numbers[] = {2, 3, 5, 7, 11, 13, 17, 19};
int size = sizeof(numbers) / sizeof(numbers[0]);
numbers[3] = numbers[4];
numbers[4] = numbers[5];
numbers[5] = numbers[6];
numbers[6] = numbers[7];
size--;
```

Although after running this code snippet the array of numbers still will have 8 elements, the last element will be a duplicate of the second-to-last element.
We could thus say that the array has been "shrunk" by one element, simply by ignoring the last element (which is what we did by decrementing the `size` variable).

Of course, shifting every element to a lower position like in the code snippet above is not very efficient - if we were to remove the first element from an array of 1000 elements, we would have to shift 999 elements.
A loop can be used to make this more efficient and readable, which is what you'll do in the next activity.

### Activity 4 - Remove an element from an array by overwriting it

File `activity4.c` contains a program that repeatedly removes an element from an array by calling the function `remove_by_index`. That function is however not yet written, only its prototype is provided.
Write the definition of the function `remove_by_index` in the file `activity4.c` so that the program works as expected.

When done, include the definition of `remove_by_index` in the code block below.

```c
// TODO: put your definition of the function remove_by_index here
int remove_by_index(int values[], size_t size, size_t index){
    for(size_t i = index; i < size - 1; i++){
        values[i] = values[i + 1];
    }
    size--;

}
```

## Removing specific elements from an array

Sometimes you need to remove all elements from an array that satisfy a certain condition - without knowing beforehand at which indices these elements are located.
For example, suppose you have a large array of measurements, and you want to remove all measurements that are considered _outliers_, which are above a certain threshold.
You could do this by repeatedly finding the index for such a measurement, and removing it from the array in the way described in the previous activity.
This would however be very inefficient, as you would have to traverse the array multiple times.

The code snippet listed below copies all elements from the array `numbers` that are less than 10 to a new array `filtered_numbers`, traversing the array only once:

```c
int numbers[] = {2, 3, 5, 7, 11, 13, 17, 19};
int size = sizeof(numbers) / sizeof(numbers[0]);
int filtered_numbers[size];
int filtered_size = 0;

for (int i = 0; i < size; i++) {
    if (numbers[i] < 10) {
        filtered_numbers[filtered_size] = numbers[i];
        filtered_size++;
    }
}
```

At the end of the loop, `filtered_size` will contain the number of elements in the `filtered_numbers` array.
The value of `filtered_size` can of course never be greater than `size`.

There is however no need to copy the elements to a new array - we can simply overwrite the elements in the original array that we want to keep, and ignore the rest.
This works because we always overwrite elements from left to right, and we only overwrite elements that we do not want to keep.

### Activity 5 - remove all vowels from a string

Write a function that removes all vowels from a string, traversing the string only once.
The prototype for the function is already provided in the file `week7.h`:

```c
void remove_vowels(char str[]);
```

Write the definition of the function in `week7.c`, and use the program of `activity5.c` to test your function.
Make sure to make use of the provided function `isvowel` (see `week7.h`) to check if a character is a vowel.
When done, include the definition of `remove_vowels` in the code block below.

```c
// TODO: put your definition of the function remove_vowels here
void remove_vowels(char str[]){
    int new = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if(!isvowels(str[i])){
            str[new] = str[i];
            new++;
        } 
    }
    str[new] = '\0';
}
```

## Sorting by swapping

Sorting means putting elements in a certain order, such as ascending or descending.
For example, the array `{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5}` could be sorted in ascending order to `{1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 9}`.
When sorting an array, without using a temporary array to put the sorted elements in, you'll have to resort to swapping elements: you'll compare two elements, and if they are not in the correct order, you'll swap them.

There are many ways to select a pair of elements (and then compare & swap them) from an array, and the number of comparisons and swaps needed to sort an array can vary greatly depending on the algorithm used.
A simple algorithm is bubble sort, which works by repeatedly swapping adjacent elements that are in the wrong order.

For example, the following code snippet ensures that the largest number in the array is moved to the end of the array, by swapping adjacent elements that are in the wrong order:

```c
int numbers[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
int size = sizeof(numbers) / sizeof(numbers[0]);

for (int i = 0; i < size - 1; i++) {
    if (numbers[i] > numbers[i + 1]) {
        int temp = numbers[i];
        numbers[i] = numbers[i + 1];
        numbers[i + 1] = temp;
    }
}
```

The process of moving the largest number to the end of the array is often referred to as "bubbling".

### Activity 6 - Bubbling values

File `activity6.c` contains a program that bubbles the longest sentence in an array of sentences to the end of the array.
It does this by calling the function `bubble_longest_string`, which is however not yet written, only its prototype is provided in `week7.h`.:

```c
int bubble_longest_string(char sentences[][], size_t size);
```

The function must return the number of swaps that were made to bubble the longest sentence to the end of the array (note that a swap must only be made if a sentence is longer than the sentence that comes after it).
Write the definition of the function `bubble_longest_string` in the file `activity6.c` so that the program works as expected.
Make sure to use the provided function `swap_strings` (see `week7.h`) to swap two strings in the array, and the function `strlen` to compute the length of a string.

When done, include the definition of `bubble_longest_string` in the code block below.

```c
// TODO: put your definition of the function bubble_longest_string here
int bubble_longest_string(char strings[][100], size_t size){
    int swaps = 0;
    for(size_t i = 0; i < size - 1; i++){
        if(strlen(strings[i]) > strlen(strings[i + 1]) ){
            swap_strings(strings[i + 1], strings[i]);
            swaps++;
        }
    }
    return swaps;
}
```

## Bubble sort

After bubbling the largest element to the end of the array, the array is not yet sorted - we're only sure that the largest element is at the end.
Repeating the bubbling process will put the second-largest element at the second-to-last position, the third-largest element at the third-to-last position, and so on.
To generalize, after `n` iterations of the bubbling process, the `n` largest elements will be in the last `n` positions of the array.
If our array has `size` elements, we need to repeat the bubbling process `size - 1` times to sort the array, because after `size - 1` iterations, the smallest element is guaranteed to be at the first position.

### Activity 7 - Applying bubble sort

Write the function `bubble_sort_strings` (prototype is already in `week7.h`) that sorts an array of strings by their length, from shortest to longest.
The function must make use of the function `bubble_longest_string` from the previous activity, and it must return the total number of swaps made during the entire sorting process.

Use the program of `activity7.c` to test your function.

When done, include the definition of `bubble_sort_strings` in the code block below.

```c
// TODO: put your definition of the function bubble_sort_strings here
int bubble_sort_strings(char strings[][100], size_t size){
    int total_swaps = 0;
    int swaps;
    for (size_t i = 0; i < size - 1; i++) {
        swaps = bubble_longest_string(strings, size - i);
        total_swaps += swaps;
    }
    return total_swaps;
}
```

### Activity 8 - Bubble sort swap efficiency

Write down the number of swaps made by the function `bubble_sort_strings` when sorting the array of sentences in the previous activity.

> TODO: Enter the number of swaps here: 22 swaps were made while sorting. 


## Selection sort

Selection sort is another simple sorting algorithm that works by repeatedly selecting the smallest (or largest) element from the unsorted part of the array and moving it to the end of the sorted part.
Compared to bubble sort, it requires fewer swaps, which is an advantage because swapping elements is often more expensive than comparing them, especially given that we're swapping strings on a character-by-character basis.

Selection sort works as follows:

1. Find the smallest element in the array, and swap it with the first element.
2. Find the second-smallest element in the array (excluding the first element), and swap it with the second element.
3. Find the third-smallest element in the array (excluding the first two elements), and swap it with the third element.
4. etc.

This means that to implement selection sort, we'll need to write a function that finds the smallest element in an array, and a function that swaps two elements in an array.
Since we'll be sorting strings based on the number of vowels they contain, we'll need to write a function that finds the string with the fewest vowels in an array of strings.

### Activity 9 - Finding the sentence with the fewest vowels

Write a function that finds the string that contains the fewest vowels among all strings in an array.
The function must return the _index_ of that strings. It can assume that `size` is always greater than 0.
The prototype for the function is already provided in the file `week7.h`:

```c
size_t find_string_with_fewest_vowels(const char strings[][], size_t size);
```

Write the definition of the function in `week7.c`, and use the program of `activity9.c` to test your function.

When done, include the definition of `find_string_with_fewest_vowels` in the code block below.

```c
// TODO: put your definition of the function find_string_with_fewest_vowels here
size_t find_string_with_fewest_vowels(const char strings[][100], size_t start, size_t size){
    int min_index = start;
    for(int i = start + 1; i < size; i++){
        if(count_vowels(strings[i]) < count_vowels(strings[min_index]) ){
            min_index = i;
        }
    }
    return min_index;      
}
```

### Activity 10 - Applying selection sort

Write a function that sorts an array of strings by the number of vowels they contain, from fewest to most, using selection sort.
That is:

1. Find the sentence with the fewest vowels in the array, and swap it with the first sentence.
2. Find the sentence with the second-fewest vowels in the array (excluding the first sentence), and swap it with the second sentence.
3. Find the sentence with the third-fewest vowels in the array (excluding the first two sentences), and swap it with the third sentence.
4. etc.

The prototype for the function is already provided in the file `week7.h`:

```c
size_t selection_sort_strings(char sentences[][], size_t size);
```

The function must return the total number of swaps made during the entire sorting process, just like you did earlier for bubble sort.

Use the program of `activity10.c` to test your function.

When done, include the definition of `selection_sort_strings` in the code block below.

```c
// TODO: put your definition of the function selection_sort_strings here
int selection_sort_strings(char strings[][100], size_t size){
    size_t total_swaps = 0;

    for(int i = 0; i < size - 1; i++){
        int fewest_vowels_strings = find_string_with_fewest_vowels(strings, size, i);
        swap_strings(strings[fewest_vowels_strings], strings[i]);
        total_swaps++;
    }
    return total_swaps;
}
```

### Activity 11 - Selection sort swap efficiency

Write down the number of swaps made by the function `selection_sort_strings` when sorting the array of sentences in the previous activity.

> TODO: Enter the number of swaps here

## Sign off

To sign off this tutorial, you will need to demonstrate the following things:

* The code you wrote works correctly and produces the expected output.
* You have answered all questions in the markdown file, and have submitted it at the correct submit point in Brightspace

Once you've successfully demonstrated the items listed above, your lab teacher will mark the assignment as completed.
