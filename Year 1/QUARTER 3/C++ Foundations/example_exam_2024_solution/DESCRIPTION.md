# Introduction

This example exam represents typical expectations for C++ programming mastery at the end of this course. Neither the workload nor the difficulty of the tasks are necessarily representative of the actual exam. However, the real exam is also divided into three tasks that cover similar topics (strings, file I/O, classes, standard library, indirection, dynamic memory, RAII).

There are three tasks in this examination. For all of them, the starter code is provided.
The directory with the project you will work with is located on the U: drive. Your work is saved automatically. There is only one project, but it contains two targets/ executables (task_1_2, task_3). Open the whole project in CLion and switch between the targets/ executables by selecting the one you are working on in the box next to the green Run button. 

* All tasks in the project compile and run without errors.
* Warnings are enabled for all tasks/ executables.
* Each task description ends with a Hints section. Read it before you start.


## Task 1

The program task_1_2, implemented in task_1_2.cpp, is supposed to search integer numbers in multiple text files. If numbers are found, they are printed to the standard output. The program takes its arguments from the command line:

First, optional flags are passed to the program. The flags are:

* -h or --help to display a help message.
* -u or --unique to find only unique numbers.
* -s or --sorted to print numbers sorted.

Then, one or more file names are passed to the program. The program searches for numbers in each file.

The program invocation can look as follows:

```text
./task_1_2 -su file1.txt file2.txt
```

Here, the program searches for numbers in the files *file1.txt* and *file2.txt*, collecting only unique numbers and sorting them before printing. Notice that the short flags can be combined, so -su is equivalent to -s -u.

### Task

The program is far from complete. Specifically, parsing of the command-line arguments is not implemented. Your task is to implement the `parse` function in* Options.cpp* to parse the command-line arguments. The function should return an `Options` object containing the parsed flags and the file names. The `Options` `struct` is defined in *Options.h*.

### Hints

1.	To pass command-line arguments to the program in CLion, go to Run -> Edit Configurations… and add the arguments in the Program arguments field.

2. The `Options` `struct` can be printed using the stream output operator `<<`. You can use this to check if the `parse` function works correctly.


## Task 2

### Introduction

The class `NumberFinder` defined in the header [*NumberFinder.h*](.task_1_2/NumberFinder.h) is used to find integers in a text file. Once an object of this class is created with search options passed to the constructor, the method `NumberFinder::find` can be called repeatedly to search for integers in multiple files. The integers that are found are stored in an internal vector of a `NumberFinder` object. This vector can be accessed using the method `NumberFinder::numbers`. 

The options search passed to the `NumberFinder` constructor determine how the integers are stored in the vector. Particularly, numbers can be stored in the ascending order and/or only unique integers can be stored. 

The class `NumberFinder` is implemented in the source file [*NumberFinder.cpp*](./task_1_2/NumberFinder.cpp).


Example code using the `NumberFinder` class:

```cpp
#include "finder.h"

// Create a NumberFinder object that searches for integers (including duplicates - false)
// and stores them in ascending order (true)
exam::NumberFinder nf(false, true);

for(const auto& file: {"file1.txt", "file2.txt"}){
    
    nf.find(file);
}

for(const auto& number: nf.numbers()){
    std::cout << number << '\n';
}
```

### Task

The `main` function in the file [*task_1_2.cpp*](./task_1_2/task_1_2.cpp) makes use of the `NumberFinder` class to search for numbers in text files. However, the class `NumberFinder` is not yet implemented. Your task is to complete `NumberFinder`'s implementation in the header and the source file. 

***Note***: You may add any private member functions or variables to the class `Finder` if you think they are necessary.

The class has three member functions that need to be implemented:

1. `NumberFinder(unique, sorted)`, constructor that takes two boolean values that determine how numbers are searched and stored (unique and sorted).

2. `numbers()`, method that returns the vector of numbers found so far in the files.

3. `find(file_name)`, method that searches for numbers in a file. The method returns `true` if any integers were found in the file, and `false` otherwise.

### Example

Assuming the following text file:

```
hello 123 programmers
alice has 3 cats
bob has 7.2 kilograms of a beer belly
the year is now 2042, welcome to the future
3 little pigs went to the market
42 is the answer to everything
the earth has the radius of exactly 6371 +/- a margin of 10 km
10 is the number of fingers on a human hand
dingo is a wild dog that lives in australia
```

The following code:

```cpp
exam::NumberFinder nf(true, true);

nf.find("file.txt");

for(const auto& number: nf.numbers()){
    std::cout << number << '\n';
}
```

Should print:

```text
3
10
42
123
2042
6371
```

Notice that all duplicates are removed and that 7.2 is not included in the output (it is not an integer).

### Hints

1. You can use the `std::ifstream` class to read from a file. Remember to include the `<fstream>` header.

2. To read a file line by line, you can use the `std::getline` function.

3. To check if a string contains a digit and find the index of the first digit, you can use the `std::string::find_first_of` function. E.g.: 

    ```cpp
    std::string str = "hello 123 programmers";
    auto pos = str.find_first_of("0123456789");
    if (pos != std::string::npos)
    {
        std::cout << "First digit found at position " << pos << std::endl;
    }
    ```

## Task 3

### Introduction

The `IntVector` class defined in *IntVector.h* manages a list of `long` integers. The `IntVector` class provides minimal dynamic array functionality. It also has extra functions to sort the stored array and to remove duplicates. The idea is to use `IntVector` in `NumberFinder` to simplify its implementation. The `IntVector` class uses a dynamic array `double * data_` to store the numbers. Two additional data members, `count_` and `capacity_`, are used to keep track of the number of items and the total capacity of the dynamic array, respectively. 

### Task

The `IntVector` class initializes the `data_` array with a default capacity of 16. This capacity never changes, and the array is never resized. If a new number is added and the array is full, the `IntVector::push_back` function simply throws an exception. Moreover, despite managing dynamic memory, the `IntVector` class does not implement the *rule of three*, which can lead to memory leaks and undefined behavior. Your task is to fix the `IntVector` class to address these issues:

1. Implement the RAII idiom in the `IntVector` class to clean-up the dynamic memory used by the `data_` array.

2. Implement the two additional special member functions that are part of the *rule of three*, so that a `IntVector` object can be safely copied and assigned.

3. Add and implement a function that resizes the `data_` array when it is full. Use this new function in `IntVector::push_back` to ensure that the array is resized when necessary.

### Hints

1. You may add any `private` member functions or variables to the class `IntVector` if you think they are necessary. In fact, this could simplify your task.