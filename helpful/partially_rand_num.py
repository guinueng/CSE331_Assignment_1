import random
import sys

# Define the range for C++ int type
INT_MIN = -2147483648  # Minimum value for signed int in C++
INT_MAX = 2147483647   # Maximum value for signed int in C++

# Generate 1K random numbers in the range of -sys.maxsize to sys.maxsize
qty = int(sys.argv[1])
front_numbers = [random.randint(INT_MIN, INT_MAX) for _ in range(int(qty / 4))]
mid_numbers = [random.randint(INT_MIN, INT_MAX) for _ in range(int(qty / 2))]
back_numbers = [random.randint(INT_MIN, INT_MAX) for _ in range(int(qty / 4))]

mid_numbers.sort()

# Write numbers to a file, each on a new line
with open(sys.argv[2], "w") as file:
    for number in front_numbers:
        file.write(f"{number}\n")
    for number in mid_numbers:
        file.write(f"{number}\n")
    for number in back_numbers:
        file.write(f"{number}\n")