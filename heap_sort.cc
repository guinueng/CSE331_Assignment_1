#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>

void swap(std::vector<int>& arr, size_t l_pos, size_t r_pos){
    int tmp = arr[l_pos];
    arr[l_pos] = arr[r_pos];
    arr[r_pos] = tmp;
}

void max_heapify(std::vector<int>& arr, size_t idx, size_t len){
    size_t left = idx * 2;
    size_t right = idx * 2 + 1;
    size_t largest = idx;

    // 1. Check left child elem exist and it is bigger than root.
    if(left < len && arr.at(left) > arr.at(idx)){
        largest = left;
    }
    // else{
    //     largest = idx;
    // }

    // 2. Check right child elem exist and it is bigger than bigger one btw
    //    left and target idx.
    if(right < len && arr.at(right) > arr.at(largest)){
        largest = right;
    }

    // 3. If bigger than target idx, swap it and pursue max_heapify again to
    //    make sure swapped one fits in correct position or need to go up again.
    if(largest != idx){
        swap(arr, idx, largest);
        max_heapify(arr, largest, len);
    }
}

void max_heap(std::vector<int>& arr, size_t idx){
    for(size_t i = (idx / 2); i > 0; i--){
        // Since we just need to consider non-leaf nodes, idx is bound for
        // (1, lower bound of (arr.size() / 2)).
        max_heapify(arr, i, arr.size());
    }
}

void heap_sort(std::vector<int>& arr){
    // 1. Make max_heap tree.
    max_heap(arr, arr.size() - 1);

    // 2. Since root is sorted as maximum elem, swap it into last elem,
    //    then, operate max_heapify again w/o swapped elem.
    //    Then, 2nd max elem will come to root, and keep going to make
    //    element sorted.
    for(size_t i = (arr.size() - 1); i > 0 ; i--){
        swap(arr, 1, i);
        max_heapify(arr, 1, i);
    }

}


int main(int argc, char* argv[]){
    // If input on argument is not proper, send it to error handler.
    if (argc != 3){
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

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
    std::cout << "Numbers read from file:\n";
    for (size_t i = 1; i < numbers.size(); ++i) {
        std::cout << numbers[i] << " ";
        if ((i + 1) % 10 == 0) {
            // Print 10 element and make new line.
            std::cout << "\n";
        }
    }
    // std::cout << "\nnum size: " << numbers.size() << std::endl;

    // Close input file.
    inFile.close();

    // Pursue merge sort.
    heap_sort(numbers);

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

    return 0;
}