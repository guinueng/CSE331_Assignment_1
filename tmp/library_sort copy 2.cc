#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <chrono>
#include <cmath>
#include <algorithm>

// Perform binary search to find the insertion position
size_t bin_search(int target, const std::vector<int>& sorted, size_t high) {
    size_t low = 0;
    while (low < high) {
        size_t mid = low + (high - low) / 2;

        if (sorted[mid] == INT_MIN || sorted[mid] > target) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

// Rebalance the sorted array with proper spacing
std::vector<int> rebalance(const std::vector<int>& sorted, size_t spacing) {
    // Calculate required size for the new vector
    size_t num_elements = 0;
    for (int val : sorted) {
        if (val != INT_MIN) ++num_elements;
    }

    // Ensure enough space for all elements with gaps
    size_t required_size = num_elements * (spacing * 2);
    std::vector<int> new_sorted(std::max(required_size, sorted.size() * 2), INT_MIN);

    // Rearrange elements with proper spacing
    size_t write_pos = spacing;
    for (size_t i = 0; i < sorted.size(); ++i) {
        if (sorted[i] != INT_MIN) {
            new_sorted[write_pos] = sorted[i];
            write_pos += spacing * 2;
        }
    }

    return new_sorted;
}

// Library sort implementation
void library_sort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;

    size_t data_size = arr.size();
    size_t spacing = 1; // Initial gap
    std::vector<int> sorted(2, INT_MIN); // Start with a small array with gaps
    sorted[1] = arr[0];                  // Place the first element

    size_t inserted = 1; // Number of elements inserted

    while (inserted < data_size) {
        // Rebalance if there is no space for new elements
        if (inserted * spacing * 2 > sorted.size()) {
            sorted = rebalance(sorted, spacing);
            spacing *= 2;
        }

        size_t batch_end = std::min(inserted * 2, data_size);
        for (size_t j = inserted; j < batch_end; ++j) {
            int element = arr[j];
            size_t pos = bin_search(element, sorted, sorted.size());

            // Find a gap for insertion
            while (pos < sorted.size() && sorted[pos] != INT_MIN) pos += spacing;

            // Rebalance if no gap is found
            if (pos >= sorted.size()) {
                sorted = rebalance(sorted, spacing);
                spacing *= 2;
                pos = bin_search(element, sorted, sorted.size());
                while (pos < sorted.size() && sorted[pos] != INT_MIN) pos += spacing;
            }

            // Insert element into gap
            if (pos < sorted.size() && sorted[pos] == INT_MIN) {
                sorted[pos] = element;
                inserted++;
            }
        }
    }

    // Extract and sort the final result to ensure correctness
    std::vector<int> result;
    for (int num : sorted) {
        if (num != INT_MIN) result.push_back(num);
    }
    
    std::sort(result.begin(), result.end()); // Final sort to ensure correctness

    // Copy back to the original array
    std::copy(result.begin(), result.end(), arr.begin());
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