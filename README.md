# Description
This program prints information about one or more running processes
on the current system, depending on the command line arguments specified

# Usage
```
$./537ps -p <pid> | -s(-) | -S(-) | -v(-) | -U(-) | -c(-)
```

If a -p flag is present and no pid is specified, the program will print
information about all running processes. Similarly, the program will print information about all running processes if it fails to print information about the desired process. 

An error will be printed and the program will terminate without printing information about any processes if an error with any command line arguments are detected. Errors are as follows:

1. Any duplicate flags
2. Detection of nonexistant flags
3. Improper pid - valid pids are positive natural numbers below 32768
4. Providing an argument to a flag which does not accept arguments

# Architecture
The code is divided into three modules listed below, which are pulled together and used by the main.c file.

1. main.c: This file pulls all of the modules together and runs the high level logic for the program. It calls on the ArgReader to fetch options, and the ProcessFetcher to provide information (if available) about any requested processes. This file also handles the printing of desired information to stdout and handles any error logic. 

2. ArgReader: This module is responsible for interpreting the provided command line arguments and indicating any errors if applicable. On success, its sole method will return a pointer to an Options struct which contains flag information and a pid if applicable. 

3. ProcessFetcher: This module is responsible for iterating over the /proc/ directory, determining ownership of files, and returning information about any owned processes to the main program. It's methods generally return pointers to Process structs or NULL on failure.

4. Parser: This module is responsible for the actual construction of Process structs and for parsing all needed information about the Processes from any relevant files. It is primarily used by the ProcessFetcher, and generally returns Process structs or NULL on failure. 