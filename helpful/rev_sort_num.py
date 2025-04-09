import random
import sys

# Define the range for C++ int type
INT_MIN = -2147483648  # Minimum value for signed int in C++
INT_MAX = 2147483647   # Maximum value for signed int in C++

# Generate 1K random numbers in the range of -sys.maxsize to sys.maxsize
numbers = [random.randint(INT_MIN, INT_MAX) for _ in range(int(sys.argv[1]))]

numbers.sort(reverse=True)

# Write numbers to a file, each on a new line
with open(sys.argv[2], "w") as file:
    for number in numbers:
        file.write(f"{number}\n")