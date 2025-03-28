#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

void merge_sort(std::vector<int>& arr, size_t low, size_t mid, size_t high){
    size_t l_len = mid - low + 1;
    size_t r_len = high - mid;

    // std::cout << "low: " << low << " mid: " << mid << " high: " << high << " l_len: " << l_len << " r_len: " << r_len << std::endl;

    if(low == high){ // Base case 1: Only one elem came.
        return;
    }

    if(low + 1 == high){ // Base case 2: Two elem came.
        if(arr[low] <= arr[high]){
            // std::cout << 1 << std::endl;
            return;
        }
        else{
            // std::cout << 2 << std::endl;
            int tmp = arr[high];
            arr[high] = arr[low];
            arr[low] = tmp;
            return;
        }
    }

    // Add left side of elem in tmp vector.
    std::vector<int> left;
    left.push_back(0); // Add padding.
    for(size_t i = 0; i < l_len; i++){
        left.push_back(arr[low + i]);
    }

    // Add right side of elem in tmp vector.
    std::vector<int> right;
    right.push_back(0); // Add padding.
    for(size_t i = 0; i < r_len; i++){
        right.push_back(arr[mid + i + 1]);
    }

    // Sort it make sure to pursue next step.
    merge_sort(left, 1, l_len / 2, l_len);
    merge_sort(right, 1, r_len / 2, r_len);

    size_t l_pos = 1;
    size_t r_pos = 1;
    for(size_t i = low; i <= high; i++){
        // std::cout << "l: " << l_pos << " r: " << r_pos << std::endl;
        if(!(r_pos < right.size())){
            arr[i] = left[l_pos];
            l_pos++;
        }
        else if(!(l_pos < left.size())){
            arr[i] = right[r_pos];
            r_pos++;
        }
        else if((left[l_pos] <= right[r_pos])){
            arr[i] = left[l_pos];
            l_pos++;
        }
        else{
            arr[i] = right[r_pos];
            r_pos++;
        }
    }
}

void merge_sort_init(std::vector<int>& arr){
    merge_sort(arr, 1, (arr.size() - 1)/2, arr.size() - 1);
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
    merge_sort_init(numbers);

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