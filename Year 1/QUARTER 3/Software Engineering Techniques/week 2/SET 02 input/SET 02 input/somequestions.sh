#!/bin/bash

# get the file name passed to the script
file=$1

#check if the file exists
if [ ! -f "$file" ]; then
    echo "Error: File '$file' does not exist."
    exist 1
fi

# create a variable to store the text to be printed at the end of the script
text=""

# read the file line by line
while IFS= read -r line; do #read -r reads the line without interpreting backslashes as escape characters.
#   - extract the category name from the line using `cut`, and save it in the `name` variable
    name=$(echo "$line" | cut -d: -f1 | tr -d ' ') #tr -d ' ' removes any spaces around the category name.
#   - extract the values from the line using `cut` and then `tr` to split the values into rows
    values=$(echo "$line" | cut -d: -f2 | tr -d ',' | tr -s ' ') #tr -s ' ' reduces multiple spaces to a single space.

    #convert the values into an array
    IFS=' ' read -r -a value_array <<< "$values"

#   - ask the user for the favorite value of the category using `select`
    echo "What is your favorite $name?"
    select value in "${value_array[@]}"; do #creates an interactive menu for the user.
        if [[ -n "$value" ]]; then #ensures that the value variable is not empty (i.e., the user selected a valid option from the list).

#       * append the answer to the `text` variable, like this: `text="$text Your favorite $name is $value."`
        text="$text Your favorite $name is $value."
        break
        else
        echo "Invalid selection. Please try again."
        fi
    done
done < "$file" #This marks the end of the while loop that reads the file line by line.
#print the final message
echo "$text"