# File and Directory Operations in Linux
CS214 Recreating Linux Commands

## Description
This project involves the implementation of three C programs for performing various file and directory operations in a Linux environment. The programs include:
1. `ls`: Lists the contents of a directory.
2. `find`: Searches for files/directories matching a pattern.
3. `tree`: Prints files/directories as a tree.

## Features
- `ls` Command
    - Lists all files/directories in the current working directory
    - Sorts files/directories in case-insensitive lexicographic order
    - Supports the `-l` command-line option to display a "long format" with extra information about each file
- `find` Command
    - Takes a pattern as a command-line argument and recursively searches through directories to find files/directories matching the pattern
    - Prints a relative path starting with `./` for every matching file/directory
    - Supports pattern matching in a case-sensitive manner
    - Output does not need to be sorted
- `tree` Command
    - Prints all files/directories contained in the current directory as a tree-like structure
    - Recursively prints subdirectories with two spaces of indentation for each level
    - Sorts files/directories within each subdirectory in case-insensitive lexicographic order

## Authors
Harshith Samayamantula  
Adam Trabelsi  
Jamil Bitar  
