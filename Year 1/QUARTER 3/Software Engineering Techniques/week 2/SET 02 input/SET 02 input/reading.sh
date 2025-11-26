#!/bin/bash

#check if a file name is provided as an argument
if [ -z "$1" ]; then # The -z flag checks if the string that follows is empty or unset.
    echo "Error: No file name provide."
    exit 1
fi

#Read file name from the first argument
file_name=$1

#check if the file exists
if [ ! -f "$file_name" ]; then #The -f flag checks if the file exists and is a regular file (not a directory or special file) if correct return true, else false.
    echo "Error: File '$file_name' does not exist."
    exit 1
fi

#Read the URL from the file (assuming the URL is the only line in the file)
url=$(cat "$file_name") #cat "$file_name": This reads the contents of the file whose name is stored in the variable file_name.

#check if the URL is empty
if [ -z "$url" ]; then #-z is a flag that checks if the string that follows is empty (i.e., has zero length).
    echo "Error: the file '$file_name' is empty or does not contain a URL."
    exit 1
fi
# Fetch the content of the URL using wget and print it to the terminal
wget -qO- "$url" wget -qO- "$url" 

# -q: Quiet mode (suppresses unnecessary output from wget).
# -O-: Outputs the content to standard output (instead of saving it to a file).