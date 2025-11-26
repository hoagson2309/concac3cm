#!/bin/bash

# get the number passed to the script
number=$1

#check if the number is a number
if !  [[ "$number" =~ ^-?[0-9]+$ ]]; then
    echo "Error: Argument pass is not a number."
    exit 1
fi

if (( number % 2 == 0)); then
    echo "The number $number is even."
else
    echo "The number $number is odd."
fi

if ((number > 0)); then
    echo "The number $number is positive."
elif (( number < 0)); then
    echo "The number $number is negative."
else
    echo "The number $number is zero."
fi

