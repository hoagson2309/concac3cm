#!/bin/bash

# get the string passed to the script
string=$1

#check if the argument is provided 
if [ -z "$string" ];then # The -z flag checks if the string that follows is empty or unset (true) if not (false).
    echo "Error: No string provided"
    exit 1;
fi

#count the number of characters in the string
# echo -n "$string" prints the string without a trailing newline
char_count=$(echo -n "$string" | wc -m) # wc -m counts the number of characters in the string

#count the number of words in the string    
word_count=$(echo -n "$string" | wc -w) # wc -w counts the number of words in the string.

#print the result
echo "Input string: '$string'"
echo "Number of characters: $char_count"
echo "Number of words: $word_count"