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

// void downheap(std::vector<int>& arr, size_t idx){
//     size_t l_pos = 2 * idx;
//     size_t r_pos = 2 * idx + 1;

//     if(l_pos > (arr.size() - 1) || r_pos > (arr.size() - 1)){
//         return;
//     }

//     bool l = false;
//     if(arr[l_pos] <= arr[r_pos]){
//         l = true;
//     }

//     if(l){
//         if(arr[idx] > arr[l_pos]){
//             swap(arr, l_pos, idx);
//             // int tmp = arr[l_pos];
//             // arr[l_pos] = arr[idx];
//             // arr[idx] = tmp;
//         }
//     }
//     else{
//         if(arr[idx] > arr[r_pos]){
//             swap(arr, idx, r_pos);
//             // int tmp = arr[r_pos];
//             // arr[r_pos] = arr[idx];
//             // arr[idx] = tmp;
//         }
//     }

//     downheap(arr, l_pos);
//     downheap(arr, r_pos);
// }

void max_heapify(std::vector<int>& arr, size_t idx, size_t len){
    size_t left = idx * 2;
    size_t right = idx * 2 + 1;
    size_t largest = idx;

    // std::cout << "info: "  << left << " " << right << " "  << largest << " " << arr.size() << std::endl;

    if(left < len && arr.at(left) > arr.at(idx)){
        largest = left;
    }
    else{
        largest = idx;
    }

    if(right < len && arr.at(right) > arr.at(largest)){
        largest = right;
    }

    // std::cout << "largest: " << largest <<std::endl;

    if(largest != idx){
        swap(arr, idx, largest);
        max_heapify(arr, largest, len);
    }

    // for(auto i : arr){
    //     std::cout << i << " ";
    // }
    // std::cout << "\n";
}

void max_heap(std::vector<int>& arr, size_t idx){
    for(size_t i = (idx / 2); i > 0; i--){
        max_heapify(arr, i, arr.size());
    }

    // size_t l_pos = 2 * idx;
    // size_t r_pos = 2 * idx + 1;

    // if(l_pos > (arr.size() - 1) || r_pos > (arr.size() - 1)){
    //     return;
    // }

    // bool l = false;
    // if(arr[l_pos] <= arr[r_pos]){
    //     l = true;
    // }

    // if(l){
    //     if(arr[idx] > arr[l_pos]){
    //         swap(arr, l_pos, idx);
    //         // int tmp = arr[l_pos];
    //         // arr[l_pos] = arr[idx];
    //         // arr[idx] = tmp;
    //     }
    // }
    // else{
    //     if(arr[idx] > arr[r_pos]){
    //         swap(arr, idx, r_pos);
    //         // int tmp = arr[r_pos];
    //         // arr[r_pos] = arr[idx];
    //         // arr[idx] = tmp;
    //     }
    // }

    // downheap(arr, l_pos);
    // downheap(arr, r_pos);
}

void heap_sort(std::vector<int>& arr){
    // downheap(arr, 1);
    max_heap(arr, arr.size() - 1);
    for(size_t i = (arr.size() - 1); i > 0 ; i--){
        swap(arr, 1, i);
        max_heapify(arr, 1, i);
    }

}

// int pop_rm_front(std::vector<int>& arr){
//     int pop_num = arr.at(0);
//     arr.at(1) = arr.at((arr.size() - 1));
//     arr.pop_back();

//     return pop_num;
// }

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