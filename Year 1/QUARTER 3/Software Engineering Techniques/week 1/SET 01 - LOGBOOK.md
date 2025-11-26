For all the exercises in this week, you'll work with __bash__ in a __terminal emulator__ in your Linux environment. 

## Environment

Print the values of the following environment variables:

* `$HOME`
* `$USER`
* `$SHELL`
* `$PATH`
* `$TERM`

Copy and paste below the commands that you used to get the values of the environment variables and their output.

```bash
# TODO: Print the values of the environment variables
echo $HOME
echo $USER
echo $SHELL
echo $PATH
echo $TERM
```

## Directories and files, commands

You've already seen some commands to manipulate and inspect files and directories. Here are a few more: `touch`, `mv`, `tree`. Read the manual pages for these commands and answer the following questions:

1. What does the command `touch` do?

A: The touch command is used to create an empty file or update the timestamp of an existing file
1. Create a new empty file: touch filename.txt
2. update the timestamp of an existing file: touch existing_file.txt
3. create multiple files at once: touch file1.txt file2.txt file3.txt
4. set a specific timestamp: touch -t 202401011200 filename.txt

2: How can you use `touch` to create a new file named __hello.txt__?

A: touch hello.txt

```bash	
# Paste the command that you used to create a new file hello.txt
touch hello.txt
```

3. What does the command `mv` do?

A: The mv (move) command is used to rename or move files and directories in Linux. 
1. Rename a file: mv oldname.txt newname.txt
2. Move a file to another directory: mv file.txt /path/to/destination/
3. Move multiple files to a directory: mv file1.txt file2.txt /path/to/destination/
4. Rename a directory: mv old_directory new_directory
5. Force move without confirmation: mv -f file.txt /path/to/destination/
6. Interactive mode (asks before overwriting): mv -i file.txt /path/to/destination/

4. How can you use `mv` to rename a file __old-name.txt__ to __NewName.doc__?

A:

```bash
# Paste the command that you can use to rename a file
mv old-name.txt NewName.doc
```

5. How can you use `mv` to move the directory `~/from`, including all its contents to the location `/mnt/usb-stick/`?

A:

```bash
# Paste the command that you can use to move the directory
mv ~/from /mnt/usb-stick/
```

6. What does the command `tree` do?

A: The tree command displays the directory structure in a hierarchical format, making it easy to visualize files and subdirectories
 1. Basic usage: tree (This prints the current directory’s structure, showing files and directories in a tree-like format)
 2. Display hidden files: tree -a (This includes hidden files (those starting with .))
 3. Display only directories: tree -d (This lists only directories, excluding files)
 4. Show file sizes: tree -h (This displays file sizes in a human-readable format (e.g., KB, MB))
 5. Export output to a file: tree > directory_structure.txt (This saves the directory structure to a file); 

7. How can you use `tree` to display the contents of the directory `~/Documents`, limiting the depth of the tree to 2 levels?

A:

```bash
# Paste the command that you used to display the contents of the directory
tree ~/Documents -L 2
```

8. What does the command `file` do?

A: The file command determines and displays the type of a file based on its contents, rather than just its extension
1. Basic usage: file filename (file document.pdf) => Output: document.pdf: PDF document, version 1.7
2. Check multiple files: file file1.txt file2.jpg (This will show the type of each file)
3. Check a directory: file directory_name(It will indicate that it's a directory)
4. Force MIME type output: file --mime-type filename (Ex output: filename: text/plain)
5. Identify a symbolic link’s target: file -L symlink (This follows a symlink and tells what the actual file is.)

9. Use the `file` command on the file `~/.bashrc`. What is the output?

```bash	
# Paste the command that you used to display the file type
~$ file ~/.bashrc
/home/hoagson/.bashrc: ASCII text
```

10. What does the command `stat` do?

A: The stat command displays detailed information about a file or directory, including its size, permissions, timestamps, and more. 
1. Basic usage: stat filename (stat document.txt)
2. Check a directory: stat my_directory/
3. Display only specific details: stat --format="%s %y" filename (This outputs just the size and last modification time.)

11. Use the `stat` command on the file `~/.bashrc`. What is the output?

```bash	
# Paste the command that you used
~$ stat ~/.bashrc
File: /home/hoagson/.bashrc
Size: 3882            Blocks: 8          IO Block: 4096   regular file
Device: 8,32    Inode: 1227        Links: 1
Access: (0644/-rw-r--r--)  Uid: ( 1000/ hoagson)   Gid: ( 1000/ hoagson)
Access: 2025-02-08 20:57:21.396610772 +0100
Modify: 2024-11-13 15:56:22.866763960 +0100
Change: 2024-11-13 15:56:22.866763960 +0100
Birth: 2024-10-07 23:37:54.284896248 +0200
```

## Directories and files in practice

You will need to paste **all the commands** that you entered in the terminal in this exercise, **including their output**. A placeholder for pasting the commands is provided below.

> All the steps must be done in the terminal in a Linux shell. No other tools are allowed. **You must stay all the time in your home directory in the terminal, do not `cd` to other directories.**

1. Go to your home directory. 
2. Create a sub-directory in your home called `week1`.
3. Create two sub-directories in `week1`: `src` and `include`.
4. Create a file called `lib.c` in the `src` directory.
5. Create a file called `lib.h` in the `week1` directory.
6. Move the file `lib.h` to the `include` directory.
7. Rename the file `lib.c` to `lib.cpp`.
8. Display the whole contents of the `week1` directory using the `tree` command.
9. Use the `file` command to display the type of the file `lib.h`.
10. Remove the whole `week1` directory, including all its contents.
11. List the contents of your home directory to verify that the `week1` directory was removed.

```bash
# TODO: copy-paste the commands that you entered in the terminal and the output you got, if any
mkdir week1
mkdir week1/src week1/include
touch week1/src/lib.c
touch week1/lib.h
mv week1/lib.h week1/include
mv week1/src/lib.c week1/src/lib.cpp

tree week1
week1
├── include
│   └── lib.h
└── src
    └── lib.cpp

file week1/include/lib.h
week1/include/lib.h: empty

rm -r week1

ls
PROJECT  hello.txt  pico

```

## grep
0. What does the command grep do?
- The grep command in Linux is used to search for a specific pattern in a file or output. It prints the lines that match the given pattern. The name grep stands for "Global Regular Expression Print.

"A". Basic Usage: grep "pattern" filename (This searches for "pattern" in filename and prints matching lines). Example: 
1. Search for a word in a file: grep "error" log.txt (Displays all lines containing "error" in log.txt) 
2. Search in multiple files: grep "TODO" *.c
(Finds "TODO" in all .c files in the directory)
3. Case-insensitive search (-i option): grep -i "hello" file.txt (Matches "hello", "Hello", or "HELLO")
4. Search recursively in directories (-r option): grep -r "function" my_project/ (Searches for "function" in all files inside my_project/)
5. Show line numbers (-n option): grep -n "main" program.c (Prints matching lines with line numbers)
6. Invert match (-v option): grep -v "DEBUG" logs.txt ( Shows lines that do not contain "DEBUG"). 

"B". Using grep with Pipes (|): grep is often used with pipes to filter command output: ls -l | grep ".txt" (Lists only .txt files from the ls -l output)


In this exercise, you'll use the `grep` command to search for patterns in the file `~/.bashrc`. The `~/.bashrc` file is a configuration file for the `bash` shell and it is present in the home directory of the user. (If you don't have a `~/.bashrc` file because you are using `zsh`, you can use the file `~/.zshrc` instead.)

1. Use the `grep` command to search for the word `alias` in the file `~/.bashrc`. How many lines contain the word `alias`?

```bash
# Paste the command that you used to search for the word `alias` in the file `~/.bashrc` and the output
grep "alias" ~/.bashrc (grep -c "alias" ~/.bashrc (the -c option counts the number of matching lines instead of displaying them))
ouput: 16
//=> there are 16 alias
``` 

2. Use the `grep` command to search for the comment lines in the file `~/.bashrc`. Comment lines always start with the `#` character. How many comment lines are there in the file `~/.bashrc`?

```bash
# Paste the command that you used to search for the comment lines in the file `~/.bashrc` and the output
grep "^#" ~/.bashrc
output: 34
// => there are 34 lines that begin with "#"
```

3. Use the `grep` command to search for the lines that contain the word `if` in the file `~/.bashrc`. **Be careful not to include the lines that contain the word `elif` or similar.**. Print only the first 5 lines that contain the word `if`. You might need to use the pipe operator `|` to combine commands.

```bash
# Paste the command that you used to search for the lines that contain the word `if` in the file `~/.bashrc` and the output
grep -w "if" ~/.bashrc | head -n 5
output: # check the window size after each command and, if necessary,
        if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
        # uncomment for a colored prompt, if the terminal has the capability; turned
        if [ -n "$force_color_prompt" ]; then
        if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then

// -w ensures that only whole words are matched, avoiding partial matches like elif
// The head -n 5 command takes only the first 5 lines from the grep output.
```

## Pipes

In this exercise you'll use the ``wget`` command, which is used to download files from the web. Because you'll be piping the output of it to another command, you'll need to use the ``-qO-`` option to write the contents of downloaded files to the standard output, instead of saving them to disk. Like this:
- -q (quiet mode) hides unnecessary messages.
- -O- outputs the downloaded content to the terminal instead of saving it.
```bash
wget -qO- http://example.com
```

1. Use the ``wget`` command to download the file ``https://www.gutenberg.org/cache/epub/11/pg11.txt`` and pipe the output to `wc` to count the number of words and lines in the text. What is the number of words and of lines in the text? Use the manual or help of `wc` to see how to count words.

```bash
# Paste the command that you used to count the number of words in the text
# and the output
wget -qO- https://www.gutenberg.org/cache/epub/11/pg11.txt | wc -lw
output: 3757  29564
- wc -l to count the number of the lines
- wc -w  counts the number of words
```

2. Use the ``wget`` command to download the file ``https://www.gutenberg.org/cache/epub/11/pg11.txt`` and pipe the output to `grep` to find all the lines that **begin with the word** "Alice". How many lines begin with the word "Alice"?

Tip: Use the manual or help of `grep` to see how to to count lines that match a pattern. You may also need to search how to match the beginning of a line.

```bash
# Paste the command that you used to find all the lines that contain the word "Alice"
# and the output
wget -qO- https://www.gutenberg.org/cache/epub/11/pg11.txt | grep -c "^Alice" 
output: 64
- grep "^Alice": Searches for lines that begin with "Alice" (^ denotes the start of a line).
- -c: Counts the number of matching lines instead of displaying them.
```

3. Use the ``wget`` command to download the file `https://www.gutenberg.org/cache/epub/11/pg11.txt``. Use the pipe and the `grep` and `wc` commands to count how many times the word "Rabbit" appears in the text. What is the number of times the word "Rabbit" appears in the text?

Tip: You are counting the occurrences of the word "Rabbit" in the text, not the number of lines that contain the word "Rabbit". You'll need to find out how to combine the `grep` and `wc` commands to do it. `grep` has an option to output only the matching part of the lines, which you can use to count the occurrences.

```bash
# Paste the command that you used to count the number of times the word "Rabbit" appears in the text
# and the output
wget -qO- https://www.gutenberg.org/cache/epub/11/pg11.txt | grep -o "Rabbit" | wc -l
output: 47
//=> there are 47 times that the word "Rabbit" appears
// grep -o "Rabbit" to extract only occurences of "Rabbit"(one per line)
// wc -l to count the number lines output by grep, which equals the number of times "Rabbit" appears

```

4. Use the `wget` and `grep` commands to download and search for the character `(` in the file `[https://raw.githubusercontent.com/bminor/glibc/master/stdio-common/vfprintf-internal.c](https://raw.githubusercontent.com/bminor/glibc/master/stdio-common/vfprintf-internal.c)`. How many times does the character `(` occur in this file? Do not save any files to disk!
 
Tip: `(` is a special character in regular expressions. You'll also need to combine `grep` with another command to count the occurrences.

```bash
# Paste the command that you used to search for the character `[` in the file `~/.bashrc` and the output
wget -qO- https://raw.githubusercontent.com/bminor/glibc/master/stdio-common/vfprintf-internal.c | grep -o "(" | wc -l
output: 693
// => there are 693 times
```

## apt package manager

In this exercise, you'll use the `apt` package manager to search for and install software.

1. Use `apt` to update your package list.

```bash	
# Paste the command that you used to update the package list
sudo apt update
```

2. Use `apt` to search for all packages that contain the text `clang` in their name. 

```bash
# Paste the command that you used to search for packages that contain the text `clang` (DO NOT PASTE THE OUTPUT)
apt search clang
```

3. Do the same as in the previous step but this time search for packages that contain the text `clang` in their name followed by `-18`. There might be some extra characters between `clang` and `-18`, also `-18` might be followed by more text.  For instance, you should find packages like `oh-my-clang-18`, `clang-for-pros-18` and `big-library-of-clang-18-dev`, etc. but not packages like `clang-17` or `clang-11-dev`.

Tip: You can either use `grep` to filter the output of the `apt` command or use the `apt` command with the *regex* pattern to search for the packages directly.	
Tip: Passing `--names-only` to `apt` will make it search only in the package names, not in the descriptions.

```bash
# Paste the command that you used to search for packages that contain the text `clang` followed by `-18` AND ITS OUTPUT
apt search --names-only '^.*clang.*-18.*$'
// apt search: Searches for packages.
// --names-only: Ensures the search is limited to package names only.
// ^: Matches the start of the string.
// .*: Matches any number of characters (including none).
// clang: Matches the literal text clang
// $: Matches the end of the string.
```

4. Use `apt` to install the packages found in the previous step, **skipping the packages that have `-rt-` as a part of their name**. You can install multiple packages at once by separating them with a space.

```bash
# Paste the command that you used to install the packages found in the previous step
    apt install $(apt search --names-only '^.*clang.*-18.*$' | awk '/^clang/ && !/-rt-/ {print $1}')
```

