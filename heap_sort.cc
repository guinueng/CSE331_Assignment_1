#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void heap_sort(std::vector<int>& arr, size_t idx){
    size_t l_pos = 2 * idx;
    size_t r_pos = 2 * idx + 1;

    if(l_pos > (arr.size() - 1) || r_pos > (arr.size() - 1)){
        return;
    }

    bool l = false;
    if(arr[l_pos] <= arr[r_pos]){
        l = true;
    }

    if(l){
        if(arr[idx] > arr[l_pos]){
            int tmp = arr[l_pos];
            arr[l_pos] = arr[idx];
            arr[idx] = tmp;
        }
    }
    else{
        if(arr[idx] > arr[r_pos]){
            int tmp = arr[r_pos];
            arr[r_pos] = arr[idx];
            arr[idx] = tmp;
        }
    }

    heap_sort(arr, l_pos);
    heap_sort(arr, r_pos);
}

void heap_sort_init(std::vector<int>& arr){
    heap_sort(arr, 1);
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
    heap_sort_init(numbers);

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