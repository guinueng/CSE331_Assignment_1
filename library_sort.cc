#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <chrono>
#include <cmath>
#include <bits/stdc++.h>

void swap(std::vector<int>& arr, size_t l_pos, size_t r_pos){
    int tmp = arr[l_pos];
    arr[l_pos] = arr[r_pos];
    arr[r_pos] = tmp;
}

size_t bin_search(int target, const std::vector<int>& sorted, size_t high) {
    size_t low = 0;
    while (low < high){
        size_t mid = low + (high - low) / 2;
        size_t pos = mid;

        while (pos < sorted.size() && sorted[pos] == INT_MIN){
            pos++;
        }
        if (pos >= sorted.size() || sorted[pos] > target){
            high = mid;
        }
        else{
            low = mid + 1;
        }
    }
    return low;
}

void rebalance(std::vector<int>& arr, size_t f, size_t b){
    size_t before_size = arr.size();

    arr.resize(2 * before_size);
    for(size_t i = before_size; i < 2 * before_size; i++){
        arr[i] = INT_MIN;
    }

    b--;
    while(b >= f){
        swap(arr, b, 2 * b);
        if(b == 0)
            break;
        b--;
    }
}

void library_sort(std::vector<int>& arr){
    size_t n = arr.size();
    std::vector<int> sorted(2, INT_MIN);

    size_t size = 0;
    for(size_t i = 0; i < n; i++){
        if(size >= sorted.size()){
            rebalance(sorted, 0, sorted.size());
        }

        size_t pos = bin_search(arr[size], sorted, sorted.size());

        if(pos >= sorted.size()){
            pos = sorted.size() - 1;
        }

        if(sorted[pos] != INT_MIN){
            bool solved = false;
            while(!solved){
                bool low = false, high = false;
                size_t mov_end = pos;
                if(sorted[pos] >= arr[size] || high){
                    high = false;

                    while(sorted[mov_end] != INT_MIN){
                        mov_end++;
                        if(mov_end >= sorted.size()){
                            low = true;
                            break;
                        }
                    }

                    if(!low){
                        for(size_t i = mov_end; i > pos; i--){
                            sorted[i] = sorted[i - 1];
                        }
                        solved = true;
                    }
                }
                if(sorted[pos] < arr[size] || low){
                    if(low){
                        low = false;
                        pos--;
                    }

                    size_t mov_front = pos;

                    while(sorted[mov_front] != INT_MIN){
                        if(mov_front == 0){
                            high = true;
                            break;
                        }
                        mov_front--;
                    }

                    if(!high){
                        for(size_t i = mov_front; i < pos; i++){
                            sorted[i] = sorted[i + 1];
                        }
                        solved = true;
                    }
                }
            }
        }
        sorted[pos] = arr[size];
        size++;
    }

    size_t idx = 0;
    for(auto i : sorted){
        if(i != INT_MIN){
            arr[idx++] = i;
        }
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
    library_sort(numbers);

    // End measuring sort_func finish time
    auto sort_end = std::chrono::high_resolution_clock::now();

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

    if(std::is_sorted(numbers.begin(), numbers.end())){
        std::cout << "Sorted!\n";
    }
    else{
        std::cout << "ERROR!\n";
    }

    return 0;
}