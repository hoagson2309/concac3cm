#!/bin/bash

# check if an argument was passed to the script and react accordingly
if [ -z "$1" ]; then
    echo "No file name provided. Please enter the filename:"
    read file_name
else
    file_name="$1"
fi

# check if the file exists and react accordingly
if [ ! f "$file_name" ]; then
    echo "Error: File '$file_name' does not exist"
    exit 1
fi

# extract and print the categories from the first line of the file
# tip: it is smart to save the categories in a variable, e.g. `categories`
categories=$(head -n 1 "$file_name" | cut -d ':' -f 2 | tr -d ',')
echo "Categories: $categories"

# create a variable to store the current category index
index=1

#loop through each category
for category in categories; do
    output="$categories:"

    #loop through each line in file, starting with the second line
    while IFS= read -r line; do
        #extract the value for the current category
        value=$(echo "$line" | cut -d ':' -f 2 | cut -d ',' -f "$index" | tr -d ' ')
        output+=" $value"
    done < <(tail -n +2 "$file_name")

    #print the output for the current category
    echo "$output"

    #increment the index variable
    index=$((index + 1))
done


