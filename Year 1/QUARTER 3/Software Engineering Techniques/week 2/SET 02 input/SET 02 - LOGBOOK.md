For all the exercises in this week, you'll work with __bash__ in a __terminal emulator__ in your Linux environment. 


## Permissions & scripts

You will need to paste **all the commands** that you entered in the terminal in this exercise, **including their output**. A placeholder for pasting the commands is provided below.

> All the steps must be done in the terminal in a Linux shell. No other tools are allowed.


1. Go to the `week1` directory in your home directory (you should have created it in the previous exercise).
2. Create a file called `hello.sh` in the `week1` directory.
3. Open the file `hello.sh` in a text editor of your choice (nano, vim, gedit, micro)
4. Type in the following content in this file, **save the changes** and exit the editor:

    ```bash
    #!/bin/bash

    echo "You are $(whoami) and today is $(date)"
    echo "You are using $(uname -s) kernel version $(uname -r)"
    ```

5. Run the script `hello.sh` in the terminal by typing:

    ```bash
    bash hello.sh
    ```

    What is the output of the script? (Copy-paste the output below in the placeholder.)

6. Try to run the the script directly by typing:

    ```bash
    ./hello.sh
    ```

    What is the output? (Copy-paste the output below in the placeholder.)

7. Change the permissions of the file `hello.sh` so that it is executable by the owner and the group, but not by others.
8. Use the `ls` command to display the permissions of the file `hello.sh`.
9. Run the script `hello.sh` in the terminal again by typing:

    ```bash
    ./hello.sh
    ```

    What is the output? (Copy-paste the output below in the placeholder.)


My commands and output:

```bash
# TODO: copy-paste the commands that you entered in the terminal and the output you got, if any
bash hello.sh
You are hoagson and today is Thu Feb 20 16:31:42 CET 2025
You are using Linux kernel version 5.15.167.4-microsoft-standard-WSL2

ls
'SET 01 - LOGBOOK.md'   hello.sh

./hello.sh 
You are hoagson and today is Thu Feb 20 16:31:49 CET 2025
You are using Linux kernel version 5.15.167.4-microsoft-standard-WSL2
```

## Environment variables & other useful information

Create a bash script that prints the following information in this order:

- The current date and time.
- The user that is executing the script.
- The path to the user's home directory.
- The path to the current working directory.
- The terminal type.
- The shell used by the user.
- The contents of the PATH variable.
- The physical memory available in the system.
- The number of CPU cores in the system.


The following commands will be useful for this exercise: `echo`, `date`, `whoami`, `id -un`, `pwd`, `free`, `nproc`.
Also, you'll need to use the following environment variables: `HOME`, `TERM`, `SHELL`, `PATH`.

When printing information, make it as clear as possible. For example, if you are printing the current date and time, you can print it like this:

```text
Current date and time: 2021-09-01 10:00:00
```

Solution:
    
```bash
#!/bin/bash

echo "Current date and time: $(date)"

# Paste the rest of your solution here
echo "User executing the script: $(whoami)"
echo "User's home directory: $HOME"
echo "Current working directory: $(pwd)"
echo "Terminal type: $TERM"
echo "User's shell: $SHELL"
echo "PATH variable: $PATH"
echo "Physical memory available: $(free -h | awk '/Mem:/ {print $7}')"
echo "Number of CPU cores: $(nproc)"
```

My output:
(Run your script and paste the output below)

```text
Current date and time: Tue Feb 11 13:44:19 CET 2025
User that is executing the script: hoagson
The path to the user's home directory: /home/hoagson
Current working directory: /home/hoagson
Terminal type: xterm-256color
hoagson@SonCao-Acer:~$ echo "User's shell: $SHELL"
User's shell: /bin/bash
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/dotnet/:/mnt/c/Program Files (x86)/IVI Foundation/VISA/WinNT/Bin/:/mnt/c/Program Files/IVI Foundation/VISA/Win64/Bin/:/mnt/c/Program Files (x86)/IVI Foundation/VISA/WinNT/Bin:/mnt/c/Users/hoang/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/hoang/AppData/Local/Programs/Microsoft VS Code/bin:/mnt/c/intelFPGA_lite/20.1/modelsim_ase/win32aloem:/mnt/c/MinGW/bin:/snap/bin
Physical memory available: 6.6Gi
Number of gpu cores: 16
```	

## Command-line arguments

Starting with this exercise, you'll pass arguments to the script. This is done in the usual way, for instance:

```bash
bash script.sh 5 alice
```

Passes two arguments to the script `script.sh`. The first argument is `5` and the second argument is `alice`.

To receive those arguments in the script, you use the pre-defined variables `$1`, `$2`, `$3`, etc. For instance, `$1` will contain the first argument, `$2` the second, and so on. The number of arguments passed to the script is stored in the variable `$#`.

### Task

Create a bash script that receives a number as an argument and prints the following information:
- If the number is even or odd.
- If the number is positive or negative.
- If the argument passed is not a number, print an error message and exit.

The following built-in bash commands will be useful for this exercise: `if`, `else`, `fi`, `test`.

Solution:

```bash
#!/bin/bash

# get the number passed to the script
number=$1

# Paste the rest of your solution here
#check if the number is a number
if !  [[ "$number" =~ ^-?[0-9]+$ ]]; then 
#!: The negation operator, meaning "if it does NOT match the regex".
#[[ ... ]]: This is a Bash test expression used for pattern matching.
#^-?: The ^ ensures the match starts at the beginning of the string. The -? means an optional negative sign (- can appear once or not at all).
#[0-9]+: Matches one or more digits (0-9).
#$: Ensures the match goes to the end of the string (so no extra characters).
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

```

My output when run with the number 5 and with -2:

(Paste the output of your script below)


```text
The number 5 is odd.
The number 5 is positive.

The number  is even.
The number -2 is negative.
```

## Counting strings

Create a bash script that receives a string as an argument and prints the following information:

- The number of characters in the string.
- The number of words in the string.

Again, take care to format the output in a clear way.

You'll find the following commands useful: `echo`, `wc`.

Solution:

```bash
#!/bin/bash

# get the string passed to the script
string=$1

# Paste the rest of your solution here

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
```

My output when run with the string "Hello, World! I'm doing bash!":

(Paste the output of your script below)

```text
./counting.sh "Hello, World! I'm doing bash!"
Input string: 'Hello, World! I'm doing bash!'
Number of characters: 29
Number of words: 5
```

## Reading from files and from the internet

Create a bash script that receives a file name and prints the content of the internet resource located at the URL specified in the file. The URL is the only line in the file.

> Do not save the file downloaded from the internet to the disk. Use a pipe to read the content of the file directly from the internet.

You'll find the following commands useful: `cat`, `wget`. You might also need to use `xargs`.

Solution:

(Paste your solution here)

```bash
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
url=$(cat "%file_name") #cat "$file_name": This reads the contents of the file whose name is stored in the variable file_name.

#check if the URL is empty
if [ -z "$url" ]; then #-z is a flag that checks if the string that follows is empty (i.e., has zero length).
    echo "Error: the file '$file_name' is empty or does not contain a URL."
    exit 1
fi

wget -qO- "$url" 

# -q: Quiet mode (suppresses unnecessary output from wget).
# -O-: Outputs the content to standard output (instead of saving it to a file).
```

My output when run with a file named `address.in`:

(Paste the output of your script below)

```text
**ALL YOUR BASE ARE BELONG TO US!**

See [Wikipedia](https://en.wikipedia.org/wiki/All_your_base_are_belong_to_us) for more information;).
```

## Tabular data processing (Option A)

> *You can choose to either do this exercise or the next one. You don't need to do both. Naturally, you can do both if you want to.*

> **YOU ABSOLUTELY MUST NO USE `AWK` FOR THIS EXERCISE.**

A text file has the following format:

```text
Name: category1, category2, category3,...categoryN
Person1: value11, value12, value13,...value1N
Person2: value21, value22, value23,...value2N
...
PersonM: valueM1, valueM2, valueM3,...valueMN
```

You can see an example of this file in the `favs.in` file.

Create a bash script that *receives an input file name* as an argument and:

1. Checks if a file name was passed as an argument. If not, asks the user for the file name.
2. Checks if the file exists. If not, print an error message and exit.
3. Processes the file and outputs the following information in this order:

    ```text
    Categories: category1 category2 category3...categoryN

    category1: value11 value21 value31...valueM1
    category2: value12 value22 value32...valueM2
    category3: value13 value23 value33...valueM3
    ...
    categoryN: value1N value2N value3N...valueMN
    ```

For the example input file, you can see the expected output in the `favs.out` file.

> You already have almost all the tools to do this exercise. It's mostly `cut` and `tr` commands, perhaps `sed` or `grep`.
 
> Tip: to concatenate strings in bash, you can use the `+=` operator. For instance, `text+="$fragment"` will append the value stored in `fragment` to the `text` variable.

> `echo -n` will print a string without a newline at the end.


Solution:

(Paste your solution here)

```bash
#!/bin/bash

# check if an argument was passed to the script and react accordingly
if [ -z "$1" ]; then
    read -p "Please enter the file name: " file_name #ask user for a filename
else
    file_name=$1
fi


# check if the file exists and react accordingly
if [ ! -f "$file_name" ]; then
    echo "Error: File '$file_name' does not exist."
    exit 1
fi


# extract and print the categories from the first line of the file
# tip: it is smart to save the categories in a variable, e.g. `categories`
catagories=$(head -n 1 "$file_name" | cut -d: -f2 | tr -d ',' | tr -s ' ') #The first line of the file is read using head -n 1, the categories are extracted using cut -d: -f2 (splitting by : and taking the second field). Commas are removed using tr -d ',', and extra spaces are trimmed using tr -s ' '
echo "Categories: $categories"



# create a variable to store the current category index
index=1


# for each category in the categories variable, do the following:
#   - for each line in the file, starting with the second:
#      * extract the value of the category and either print it or concatenate it to an output variable
#   - print the output variable (if you have it)
#   - increment the index variable

#loop through each category
for category in $categories; do
    #Initialize an output variable for the current category
    output="$category:"

    #loop through each line in the file, starting with the second line
    tail -n +2 "$file_name" | while IFS= read -r line; do
        #extract value for current category
        value=$(echo "$line" | cut -d: -f2 | cut -d, -f$index | tr -d ' ')
        #append the value to the output variable
        output+=" $value"
    done

    #print the output for the current category
    echo "$output"

    #increment the index variable
    index=$((index + 1))
done
```

The biggest challenge in this exercise is probably to read the file line-by-line starting with the second line only. If you struggle with it, either skip it or ask for help.

### What do you like?

> *You can choose to either do this exercise or the next one. You don't need to do both. Naturally, you can do both if you want to.*

> **YOU ABSOLUTELY MUST NO USE `AWK` FOR THIS EXERCISE.**

Create a bash script that receives a file name as an argument and asks the user some questions based on the content of the file. The file will have the following structure:

```
Color: Red, Green, Blue
Animal: Dog, Cat, Fish, Spider
```

Do not assume that there will be only two lines and that the values will be the same as in the example above. The file can have any number of lines and the values can be anything.

With the file above, the script should first ask the user what is they favorite color and then what is their favorite animal. Like this:

```text
What is your favorite Color?
1) Red
2) Green
3) Blue
#? 
1
What is your favorite Animal?
1) Dog
2) Cat
3) Fish
4) Spider
#?
1
```

After the user answers both questions, the script should print a message like this:

```text
Your favorite color is Red. Your favorite animal is Dog.
```

To do this exercise, you'll need to read the file [line-by-line, as explained in this SO answer](https://stackoverflow.com/a/10929511). 

You'll also need to cut and parse the lines to get the name (the part before the `:`) and the values (the part after the `:`). You can use the `cut` with `-d` and `-f` options command to do this.

You can also use the `tr` command to remove commas, you'll need it to be able to use the `select` command.

To get this exercise done, you'll have to combine `cut` and `tr` using pipes. 

> Input to this exercise is in the `select.in` file.


Sketch of the solution:

(Paste your finished solution here)

```bash
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
```
