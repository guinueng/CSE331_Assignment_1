#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>
#include "insertion_sort.cc"

void swap(std::vector<int>& arr, size_t l_pos, size_t r_pos){
    int tmp = arr[l_pos];
    arr[l_pos] = arr[r_pos];
    arr[r_pos] = tmp;
}

void insertion_sort(std::vector<int>& arr, size_t f, size_t b){
    for(size_t j = f; j < b; j++){
        int key = arr[j];

        size_t i = j - 1;
        while(i > 0 && arr[i] > key){
            arr[i + 1] = arr[i];
            i--;
        }

        arr[i + 1] = key;
    }
}

void introsort_loop(std::vector<int>& arr, size_t f, size_t b, size_t depth_limit){
    while(b - f > size_threshold){
        if(depth_limit == 0){
            heap_sort(arr, f, b);
            return;
        }
        depth_limit--;
        p = partition ();
        intro_sort(arr, p, b, depth_limit);
        b = p;
    }
}

void intro_sort(std::vector<int>& arr, size_t f, size_t b){
    introsort_loop(arr, f, b, 2 * log(b - f));
    insertion_sort(arr, f, b);
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
    heap_sort(numbers);

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