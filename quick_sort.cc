#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

void swap(std::vector<int>& arr, size_t l_pos, size_t r_pos){
    int tmp = arr[l_pos];
    arr[l_pos] = arr[r_pos];
    arr[r_pos] = tmp;
}

void quick_sort(std::vector<int>& arr){
    size_t back = arr.size() - 1;

    if(arr.size() < 2){
        return;
    }

    // 1. Select pivot at the last point of arr.
    int pivot = arr.at(back); // Pivot can be any value. In assignment document, test it and add it.

    // 2. Move integer into 3 sub-array which is designed to
    //    store less than / equal / higher than pivot.
    std::vector<int> S, E, H;
    while(!arr.empty()){
        int i = arr.at(back);
        if(i < pivot){
            S.push_back(i);
        }
        else if(i > pivot){
            H.push_back(i);
        }
        else{
            E.push_back(i);
        }
        arr.pop_back();
        back--;
    }

    // 3. Since arr E is already sorted(due to it is same as
    //    pivot), so we sort S and H arr.
    quick_sort(S);
    quick_sort(H);

    // 4. Finally, combine sorted result into original array.
    for(auto i: S){
        arr.push_back(i);
    }

    for(auto i: E){
        arr.push_back(i);
    }

    for(auto i: H){
        arr.push_back(i);
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
    quick_sort(numbers);

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

    return 0;
}