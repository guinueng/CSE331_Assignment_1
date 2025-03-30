#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>
#include <bits/stdc++.h>

#define SIZE_THRESHOLD 16

void swap(std::vector<int>& arr, size_t l_pos, size_t r_pos){
    int tmp = arr[l_pos];
    arr[l_pos] = arr[r_pos];
    arr[r_pos] = tmp;
}

void max_heapify(std::vector<int>& arr, size_t idx, size_t len) {
    size_t left = idx * 2 + 1; // 수정: 배열 인덱스는 0 기반
    size_t right = idx * 2 + 2;
    size_t largest = idx;

    if (left < len && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < len && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != idx) {
        swap(arr, idx, largest);
        max_heapify(arr, largest, len);
    }
}

void max_heap(std::vector<int>& arr, size_t f, size_t len) {
    for (size_t i = (len / 2); i-- > f;) { // 수정: i-- 조건 변경
        max_heapify(arr, i, len);
    }
}

void heap_sort(std::vector<int>& arr, size_t f, size_t b) {
    max_heap(arr, f, b);

    for (size_t i = b; i-- > f;) { // 수정: i-- 조건 변경
        swap(arr, f, i);
        max_heapify(arr, f, i);
    }
}

void insertion_sort(std::vector<int>& arr, size_t f, size_t b) {
    for (size_t j = f + 1; j < b; j++) { // 수정: j는 f+1부터 시작
        int key = arr[j];
        size_t i = j;

        while (i > f && arr[i - 1] > key) { // 수정: 범위 조건 변경
            arr[i] = arr[i - 1];
            i--;
        }

        arr[i] = key;
    }
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void introsort_loop(std::vector<int>& arr, size_t f, size_t b, size_t depth_limit) {
    while (b - f > SIZE_THRESHOLD) {
        if (depth_limit == 0) {
            heap_sort(arr, f, b);
            return;
        }
        depth_limit--;
        size_t p = partition(arr, f, b - 1); // 수정: 범위 전달 오류 수정
        introsort_loop(arr, p + 1, b, depth_limit);
        b = p;
    }
}

void intro_sort(std::vector<int>& arr, size_t f, size_t b) {
    introsort_loop(arr, f, b, 2 * static_cast<size_t>(log(b - f)));
    insertion_sort(arr, f, b);
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

    // Close input file.
    inFile.close();

    // Start measuring sort_func exec time.
    auto sort_start = std::chrono::high_resolution_clock::now();

    // Pursue merge sort.
    intro_sort(numbers, 1, numbers.size());

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

    if(std::is_sorted(numbers.begin(), numbers.end())){
        std::cout << "Sorted!\n";
    }
    else{
        std::cout << "ERROR!\n";
    }

    return 0;
}