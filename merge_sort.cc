#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void merge_sort(std::vector<int>& arr, size_t low, size_t mid, size_t high){
    // std::cout << "low: " << low << "mid: " << mid << "high: " << high << std::endl;
    // size_t size = high - low + 1;
    size_t l_len = mid - low + 1;
    size_t r_len = high - mid;

    if(low == high){ // Base case 1: Only one elem came.
        return;
    }

    if(low + 1 == high){ // Base case 2: Two elem came.
        if(arr[low] <= arr[high]){
            return;
        }
        else{
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

    // std::cout << "Before: " << std::endl;
    // for (size_t i : left){
    //     std::cout << i << ", ";
    // }
    // std::cout << std::endl;
    // for (size_t i : right){
    //     std::cout << i << ", ";
    // }
    // std::cout << std::endl;

    // Sort it make sure to pursue next step.
    merge_sort(left, 1, l_len / 2, l_len);
    merge_sort(right, 1, r_len / 2, r_len);

    // std::cout << "After: " << std::endl;
    // for (size_t i : left){
    //     std::cout << i << ", ";
    // }
    // std::cout << std::endl;
    // for (size_t i : right){
    //     std::cout << i << ", ";
    // }
    // std::cout << std::endl;

    size_t l_pos = 1;
    size_t r_pos = 1;
    for(size_t i = low; i <= high; i++){
        if((left[l_pos] <= right[r_pos] && (l_pos < left.size())) || !(r_pos < right.size())){
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
    // std::cout << "\nsize:" << arr.size() << std::endl;
    merge_sort(arr, 1, (arr.size() - 1)/2, arr.size()-1);
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
    merge_sort_init(numbers);

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