import random
import sys

# Generate 1K random numbers in the range of -sys.maxsize to sys.maxsize
numbers = [random.randint(-sys.maxsize, sys.maxsize) for _ in range(int(sys.argv[1]))]

# Write numbers to a file, each on a new line
with open("unsorted_numbers_inf_range.txt", "w") as file:
    for number in numbers:
        file.write(f"{number}\n")