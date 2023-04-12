#!/bin/bash

# Compile the code
gcc -pthread Task1.c -o Task1

# Set the number of threads
threads=$1

# Run the code with x threads and time it
{ time ./Task1 $threads; } 2> runtime.txt

# Clean up
rm Task1
