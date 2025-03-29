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

void max_tournamentify(std::vector<int>& arr, size_t len){
    // for(auto i : arr){
    //     std::cout << i << " ";
    // }
    // std::cout << " prev\n";
    for(size_t i = 1; i < len; i *= 2){
        if(arr.at(1) < arr.at(i)){
            swap(arr, 1, i);
        }
    }
    // for(auto i : arr){
    //     std::cout << i << " ";
    // }
    // std::cout << "after \n";
}

void max_tournament(std::vector<int>& arr, std::vector<int>& win, size_t gap, size_t len){
    // std::cout << "len: " << len << "\n";
    // for(size_t i = (len / 2); i > 0; i--){
        // Since we just need to consider non-leaf nodes, idx is bound for
        // (1, lower bound of (arr.size() / 2)).
        // max_tournamentify(arr, i, len + 1);
    // }

    size_t cur = 1;
    size_t win_len = len / 2 + len % 2;
    // size_t gap = 1;
    while(gap < len){
    // for(size_t i = gap; i < len; i *= 2){
        // for(auto i : arr){
        //     std::cout << i << " ";
        // }
        // std::cout << "\ni: " << i << "\n";

        // for(size_t j = 1; j < len; j += 2 * i){
        //     if(j + i >= len){
        //         break;
        //     }
        //     else if(arr.at(j) < arr.at(j + i)){
        //         swap(arr, j, j + i);
        //     }
        // }

        size_t pos = len + 1;
        if(cur == 1){
            for(size_t j = 1; j < len; j += 2){
                if(j + 1 >= len){
                    win.at(pos++) = j;
                }
                else if(arr.at(j) < arr.at(j + 1)){
                    win.at(pos++) = j;
                }
                else{
                    win.at(pos++) = j + 1;
                }
            }
        }
        else{
            for(size_t i = 0; i ; i /= 2){
            
            }

        
            
        }
    }
}

void tournament_sort(std::vector<int>& arr){
    // 1. Make max_tournament tree.
    std::vector<int> win = arr;
    win.reserve(arr.size());
    max_tournament(arr, win, 1, arr.size());

    // 2. Since root is sorted as maximum elem, swap it into last elem,
    //    then, operate max_tournamentify again w/o swapped elem.
    //    Then, 2nd max elem will come to root, and keep going to make
    //    element sorted.
    for(size_t i = (arr.size() - 1); i > 0 ; i--){
        // for(auto i : arr){
        //     std::cout << i << " ";
        // }
        // std::cout << "\ni: " << i << "\n";
        arr.at(i) = list.at(1);

        // swap(arr, 1, i);
        // for(auto i : arr){
        //     std::cout << i << " ";
        // }
        // std::cout << "swapped\n";
        max_tournament(arr, 1, i);
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
    tournament_sort(numbers);

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