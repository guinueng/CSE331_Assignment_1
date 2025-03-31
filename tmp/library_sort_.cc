#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <chrono>
#include <cmath>

const int GAP = INT_MAX;  // 실제 데이터와 겹치지 않는 값 사용

size_t find_insert_pos(int target, const std::vector<int>& sorted, size_t low, size_t high) {
    while (low < high) {
        size_t mid = low + (high - low) / 2;
        int val = sorted[mid];
        
        if (val == GAP || val > target) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

void rebalance(std::vector<int>& sorted, size_t& spacing) {
    std::vector<int> new_array;
    size_t elements = 0;
    
    // 실제 요소 개수 계산
    for (int num : sorted) {
        if (num != GAP) ++elements;
    }

    // 새로운 간격 계산
    spacing = static_cast<size_t>(std::sqrt(elements)) + 1;
    size_t new_size = elements * (spacing + 1) + spacing;
    new_size = std::max(new_size, sorted.size() * 2);
    
    new_array.resize(new_size, GAP);
    
    // 요소 재배치
    size_t pos = spacing;
    for (int num : sorted) {
        if (num != GAP) {
            new_array[pos] = num;
            pos += spacing + 1;
        }
    }
    
    sorted.swap(new_array);
}

void library_sort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;

    size_t spacing = 2;
    std::vector<int> sorted(arr.size() * 2, GAP);
    sorted[spacing] = arr[0];
    size_t inserted = 1;

    while (inserted < arr.size()) {
        if (inserted * (spacing + 1) > sorted.size()) {
            rebalance(sorted, spacing);
        }

        size_t batch_size = std::min(inserted, arr.size() - inserted);
        for (size_t i = 0; i < batch_size; ++i) {
            int element = arr[inserted + i];
            size_t pos = find_insert_pos(element, sorted, 0, sorted.size());

            // 빈 공간 탐색
            while (pos < sorted.size() && sorted[pos] != GAP) ++pos;
            
            // 공간 부족 시 재조정
            if (pos >= sorted.size()) {
                rebalance(sorted, spacing);
                pos = find_insert_pos(element, sorted, 0, sorted.size());
                while (pos < sorted.size() && sorted[pos] != GAP) ++pos;
            }

            if (pos < sorted.size()) {
                sorted[pos] = element;
                ++inserted;
            }
        }
    }

    // 결과 추출
    size_t write_idx = 0;
    for (int num : sorted) {
        if (num != GAP) {
            if (write_idx < arr.size()) {
                arr[write_idx++] = num;
            }
        }
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
    // numbers.push_back(0);

    // Read numbers from file.
    int number;
    while (inFile >> number){
        // Add numbers in vector.
        numbers.push_back(number);
    }

    // Close input file.
    inFile.close();

    // Start measuring sort_func exec time.
    auto sort_start = std::chrono::high_resolution_clock::now();

    // Pursue merge sort.
    library_sort(numbers);

    // End measuring sort_func finish time
    auto sort_end = std::chrono::high_resolution_clock::now();

    // Delete first element in vector utilized for padding.
    // numbers.erase(numbers.begin());

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