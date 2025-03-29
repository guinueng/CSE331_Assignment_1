#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>

void swap(std::vector<int>& arr, size_t l_pos, size_t r_pos){
    int tmp = arr[l_pos];
    arr[l_pos] = arr[r_pos];
    arr[r_pos] = tmp;
}

void comb_sort(std::vector<int>& arr, long len){
    // Base case. If length is smaller than 1, it contains it self,
    // thus it is already sorted state. Therefore, return.
    if(len < 2){
        return;
    }

    size_t inc = len / 2;
    for(size_t i = 1; i <= size_t(log2(len)); i++){
        // std::cout << inc << "\n";
        for(size_t j = 1; j <= len - inc; j++){
            // if(j + inc < len){
            if(arr.at(j) > arr.at(j + inc)){
                swap(arr, j, j + inc);
            }
            // else{
            //     break;
            // }
        // }
        }
        inc = 3 * inc / 4;
        if(inc <= 1)
            break;
    }

    // Pursue compare i and next elem and if condition satisfies(arr[i]
    // > arr[i + 1]) execute swap operation.
    while(len > 0){
        // std::cout << len << "\n";
        long k = 0;
        for(size_t i = 1; i < len; i++){
            if(arr.at(i) > arr.at(i + 1)){
                swap(arr, i, i+ 1);
                k = i;
            }
        }
        len = k;
    }

    // Recursively do process until first one left.
    // comb_sort(arr, len - 1);
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
    // for (size_t i = 0; i < numbers.size(); ++i) {
    //     std::cout << numbers[i] << " ";
    //     if ((i + 1) % 10 == 0) {
    //         // Print 10 element and make new line.
    //         std::cout << "\n";
    //     }
    // }

    // Close input file.
    inFile.close();

    // Start measuring sort_func exec time.
    auto sort_start = std::chrono::high_resolution_clock::now();

    // Pursue merge sort.
    comb_sort(numbers, (numbers.size() - 1));

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