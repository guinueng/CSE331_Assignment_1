#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <chrono>
#include <cmath>
#include <bits/stdc++.h>

#include <vector>
#include <algorithm>
#include <iostream>

const int MIN_GALLOP = 7;

// 갤럽 서치 (오른쪽 방향)
int gallop_right(int key, const std::vector<int>& arr, int base, int len) {
    int last_offset = 0, offset = 1;
    while (offset < len && arr[base + offset] <= key) {
        last_offset = offset;
        offset = (offset << 1) + 1;
    }
    int upper = std::min(base + offset, base + len);
    auto pos = std::upper_bound(arr.begin() + base + last_offset,
                               arr.begin() + upper, key);
    return pos - (arr.begin() + base);
}

// 갤럽 서치 (왼쪽 방향)
int gallop_left(int key, const std::vector<int>& arr, int base, int len) {
    int last_offset = 0, offset = 1;
    while (offset < len && arr[base + len - offset] >= key) {
        last_offset = offset;
        offset = (offset << 1) + 1;
    }
    int lower = std::max(base, base + len - offset);
    auto pos = std::lower_bound(arr.begin() + lower,
                               arr.begin() + base + len - last_offset, key);
    return pos - (arr.begin() + base);
}

void insertion_sort(std::vector<int>& arr, int l, int r) {
    for (int i = l + 1; i <= r; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= l && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void merge(std::vector<int>& arr, int l, int m, int r) {
    int len1 = m - l + 1;
    int len2 = r - m;
    std::vector<int> left(len1), right(len2);

    std::copy(arr.begin() + l, arr.begin() + m + 1, left.begin());
    std::copy(arr.begin() + m + 1, arr.begin() + r + 1, right.begin());

    int i = 0, j = 0, k = l;
    int left_wins = 0, right_wins = 0;
    int min_gallop = MIN_GALLOP;

    while (i < len1 && j < len2) {
        if (left_wins >= min_gallop || right_wins >= min_gallop) {
            // if input qty on arr element either left or right array is bigger than gallop, go to gallop mode.
            int gallop_count = gallop_right(right[j], left, i, len1 - i);
            for (int a = 0; a < gallop_count; ++a) {
                arr[k++] = left[i++];
            }
            left_wins = 0;

            if (i >= len1) break;

            gallop_count = gallop_left(left[i], right, j, len2 - j);
            for (int b = 0; b < gallop_count; ++b) {
                arr[k++] = right[j++];
            }
            right_wins = 0;

            min_gallop += (gallop_count < MIN_GALLOP) ? 1 : -1;
            min_gallop = std::max(1, min_gallop);
            continue;
        }

        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
            ++left_wins;
            right_wins = 0;
        } else {
            arr[k++] = right[j++];
            ++right_wins;
            left_wins = 0;
        }
    }

    while (i < len1) arr[k++] = left[i++];
    while (j < len2) arr[k++] = right[j++];
}

void tim_sort(std::vector<int>& arr) {
    const int n = arr.size();
    const int run = 32;

    // 초기 런 생성
    for (int i = 0; i < n; i += run) {
        insertion_sort(arr, i, std::min(i + run - 1, n - 1));
    }

    // 병합 단계
    for (int size = run; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = std::min(left + size - 1, n - 1);
            int right = std::min(left + 2 * size - 1, n - 1);
            if (mid < right) {
                merge(arr, left, mid, right);
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
    tim_sort(numbers);

    // End measuring sort_func finish time
    auto sort_end = std::chrono::high_resolution_clock::now();

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