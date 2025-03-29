#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <cassert>
#include <cmath>

void swap(std::vector<int>& arr, size_t a, size_t b) {
    std::swap(arr[a], arr[b]);
}

size_t max_tournament(std::vector<int>& arr, std::vector<int>& win, size_t len) {
    size_t cur = 0;
    size_t next = len;
    while (len > 1) {
        for (size_t i = 0; i + 1 < len; i += 2) {
            size_t left = win[cur + i];
            size_t right = win[cur + i + 1];
            win[next++] = (arr[left] > arr[right]) ? left : right;
        }
        if (len % 2 == 1) {
            win[next++] = win[cur + len - 1];
        }
        cur += len;
        len = (len + 1) / 2;
    }
    return next;
}

void tournament_sort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;

    const size_t padding = 1;
    size_t n = arr.size() - padding; // Due to exist of padding, - 1.
    size_t tree_size = 2 * (1 << static_cast<size_t>(ceil(log2(n))));
    std::vector<int> win(tree_size, -1);

    for (size_t i = arr.size() - 1; i >= padding; --i) {
        for (size_t j = 0; j < n; ++j) 
            win[j] = j + padding; 

        size_t next = max_tournament(arr, win, n);
        size_t root_index = next - 1;
        swap(arr, win[root_index], i);

        std::fill(win.begin() + n, win.end(), -1);
        --n;
    }
}

int main(int argc, char* argv[]){
    // If input on argument is not proper, send it to error handler.
    if (argc != 3){
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    // Start measuring sort_func exec time.
    auto start = std::chrono::high_resolution_clock::now();

    // Save input and output file name in string.
    std::string outputFile = argv[argc - 1];
    std::string inputFile = argv[argc - 2];

    // Open target input file.
    std::ifstream inFile(inputFile);
    if (!inFile) {
        std::cerr << "Error: Could not open input file: " << inputFile << std::endl;
    }

    // Allocate vector to store numbers read in file.
    std::vector<int> numbers;
    numbers.reserve(1000001);
    
    // Add useless value to make padding.
    numbers.push_back(0);

    // Read numbers from file.
    int number;
    while (inFile >> number){
        // Add numbers in vector.
        numbers.push_back(number);
    }

    // Print data from read file.
    // std::cout << "Numbers read from file:\n";
    // for (size_t i = 1; i < numbers.size(); ++i) {
    //     std::cout << numbers[i] << " ";
    //     if ((i + 1) % 10 == 0) {
    //         // Print 10 element and make new line.
    //         std::cout << "\n";
    //     }
    // }
    // std::cout << "\nnum size: " << numbers.size() << std::endl;

    // Close input file.
    inFile.close();

    // Start measuring sort_func exec time.
    auto sort_start = std::chrono::high_resolution_clock::now();

    // Pursue merge sort.
    tournament_sort(numbers);

    // End measuring sort_func finish time
    auto sort_end = std::chrono::high_resolution_clock::now();

    // Delete first element in vector utilized for padding.
    numbers.erase(numbers.begin());

    // Save result into new file.
    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Error: Could not open output file: " << outputFile << std::endl;
        return 1;
    }

    for (const auto& num : numbers) {
        // Save number in each line.
        outFile << num << "\n";
    }

    outFile.close();
    std::cout << "Processed data has been written to 'output.txt'.\n";

    // End measuring finish time
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate elapsed time in milliseconds
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    auto sort_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(sort_end - sort_start).count();
    std::cout << "Elapsed time: " << elapsed << " ms\n" << "Sorting time: " << sort_elapsed << " ms\n" << std::endl;

    return 0;
}