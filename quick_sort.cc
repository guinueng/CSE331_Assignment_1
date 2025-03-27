#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

    int pivot = arr.at(back);

    // std::cout << "pivot: " << pivot << std::endl;

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

    quick_sort(S);
    quick_sort(H);

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
    std::cout << "Numbers read from file:\n";
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << " ";
        if ((i + 1) % 10 == 0) {
            // Print 10 element and make new line.
            std::cout << "\n";
        }
    }

    // Close input file.
    inFile.close();

    // Pursue merge sort.
    quick_sort(numbers);

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