"# Operating-Systems" 
### How to Compile & Run Project 1 - Copy File Command-Line Utility
**NOTE: Recommended. Run on UNIX or Linux Distribution.** 
```bash
# First check gcc version:
gcc -v
# If Error occurs (not found), please install gcc compiler or equivalent.

# Else.
gcc filecopy.c -o filecopy

# To Run Properly
./filecopy source_file.txt destination_file.txt

# If needed
./filecopy --help

# =========================================================

# NOT Necessary, but for ease of use.
alias mpycp='./filecopy'

# Then run as shown previously...
mycp source_file.txt destination_file.txt

mycp --help
```