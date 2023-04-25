#!/bin/bash

# Compile the C program
gcc -o Task1 Task1.c -lpthread

# Prompt the user for the thread count
read -p "Enter the number of threads: " threads

# Run the Task1 program with the specified thread count and capture the runtime
echo "Running Task1 with $threads threads..."
echo "Thread Count: $threads" >> runtime.txt
echo "Task1:" >> runtime.txt
{ time ./Task1 $threads; } 2>> runtime.txt

# Display the runtime
echo "Runtime of Task1 and thread count have been appended to runtime.txt"


