#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <chrono>
#include <cmath>
#include <bits/stdc++.h>

void insertion_sort(std::vector<int>& arr, int l, int r){
    // std::cout << "insertion\n";
    // for (auto i : arr){
        // std::cout << i << " ";
    // }
    // std::cout << "l: " << l << " r: " << r << "\n";
    int i = l + 1;
    while(i <= r){
        // std::cout << "\n\nnew while loop start\n";
        int tmp = arr[i];
        int j = i - 1;

        // for (auto i : arr){
            // std::cout << i << " ";
        // }
        // std::cout << "i: " << i << " j: " << j << " tmp: " << tmp << "\n";

        // std::cout << "while start\n";
        while(j >= l && arr[j] > tmp){
            // for (auto i : arr){
                // std::cout << i << " ";
            // }
            // std::cout << "i: " << i << " j: " << j << " tmp: " << tmp << "\n";
            arr[j + 1] = arr[j];
            // std::cout << 1 << std::endl;
            j--;
        }
        // std::cout << "while end\n";

        // for (auto i : arr){
            // std::cout << i << " ";
        // }
        // std::cout << "i: " << i << " j: " << j << " tmp: " << tmp << "\n";
        // std::cout << "outside j: " << j << std::endl;
        arr[j + 1] = tmp;
        i++;
    }
}

void merge(std::vector<int>& arr, int l, int m, int r){
    int x = 0, y = 0, i = 0, j = 0, k = 0;
    int len_1 = m - l + 1;
    int len_2 = r - m;
    std::vector<int> left;
    left.resize(len_1);
    std::vector<int> right;
    right.resize(len_2);

    while(x < len_1){
        left[x] = arr[l + x];
        x++;
    }

    while(y < len_2){
        right[y] = arr[m + y + 1];
        y++;
    }

    while(i < len_1 && j < len_2){
        if(left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        }
        else{
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while(i < len_1){
        arr[k++] = left[i++];
    }

    while(j < len_2){
        arr[k++] = right[j++];
    }
}

void tim_sort(std::vector<int>& arr){
    int n = arr.size();
    int run = 32;
    int i = 0;
    int left = 0;
    int size = run;
    
    while(i < n){
        int tmp = std::min(i + run -1, n - 1);
        insertion_sort(arr, i, tmp);
        i += run;
    }

    while(size < n){
        while(left < n){
            int mid = left + size - 1;
            int right = std::min(left + 2 * size - 1, n - 1);
            if(mid < right){
                merge(arr, left, mid, right);
            }
            left = 2 * size;
        }

        left = 0;
        size *= 2;
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

    // Close input file.
    inFile.close();

    // Start measuring sort_func exec time.
    auto sort_start = std::chrono::high_resolution_clock::now();

    // Pursue merge sort.
    tim_sort(numbers);

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