#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <chrono>

void swap(std::deque<int>& arr, size_t l_pos, size_t r_pos){
    int tmp = arr[l_pos];
    arr[l_pos] = arr[r_pos];
    arr[r_pos] = tmp;
}

void quick_sort(std::deque<int>& arr, size_t s, size_t e){

    // std::cout << "s: " << s << " e: " << e << "\n";

    // size_t back = arr.size() - 1;

    if((e - s) <= 0){
        return;
    }

    // 1. Select pivot at the last point of arr.
    int pivot = arr.at(e); // Pivot can be any value. In assignment document, test it and add it.

    // Pivot = back elem > can cause stack overflow. > need to increase stack

    // 2. Move integer into 3 sub-array which is designed to
    //    store less than / equal / higher than pivot.
    std::deque<int> S, E, H;
    size_t k = 0, h = 0;
    for(size_t i = s; i <= e; i++){
        if(arr.at(i) < pivot){
            S.push_back(arr.at(i));
            k++;
        }
        else if(arr.at(i) > pivot){
            H.push_back(arr.at(i));
            h++;
        }
        else{
            E.push_back(arr.at(i));
        }
        // arr.pop_back();
    }

    // std::cout << "\nS: ";
    // for(auto i: S){
    //     std::cout << i << " ";
    // }
    // std::cout << "\nE: ";
    // for(auto i: E){
    //     std::cout << i << " ";
    // }
    // std::cout << "\nH: ";
    // for(auto i: H){
    //     std::cout << i << " ";
    // }
    // std::cout << "\n";

    size_t pos = s;
    while(!S.empty()){
        arr.at(pos) = S.front();
        S.pop_front();
        pos++;
    }
    while(!E.empty()){
        arr.at(pos) = E.front();
        E.pop_front();
        pos++;
    }
    while(!H.empty()){
        arr.at(pos) = H.front();
        H.pop_front();
        pos++;
    }

    S.resize(0);
    E.resize(0);
    H.resize(0);

    // std::cout << k << "h: " << h << "\n";

    // 3. Since arr E is already sorted(due to it is same as
    //    pivot), so we sort S and H arr.
    // if(e == 3 || s == 5){
    //     return;
    // }
    if(s < s + k - 1)
        quick_sort(arr, s, s + k - 1);
    if(e - h + 1 < e)
        quick_sort(arr, e - h + 1, e);

    // 4. Finally, combine sorted result into original array.
    // for(auto i: S){
    //     arr.push_back(i);
    // }

    // for(auto i: E){
    //     arr.push_back(i);
    // }

    // for(auto i: H){
    //     arr.push_back(i);
    // }
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

    // Allocate deque to store numbers read in file.
    std::deque<int> numbers;
    // numbers.reserve(1000001);

    // Read numbers from file.
    int number;
    while (inFile >> number){
        // Add numbers in deque.
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
    quick_sort(numbers, 0, numbers.size() - 1);

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