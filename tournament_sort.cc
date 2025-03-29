#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <climits>

void swap(std::vector<int>& arr, size_t a, size_t b) {
    if (a >= arr.size() || b >= arr.size()) return;
    if (a == b) return;
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

size_t calculate_tree_size(size_t n) {
    if (n == 0) return 0;
    size_t next_pow2 = 1ULL << static_cast<size_t>(ceil(log2(n)));
    return 2 * next_pow2 - 1;
}

void update_tree(std::vector<int>& arr, std::vector<int>& win, size_t idx, size_t tree_size) {
    while (idx > 0) {
        size_t parent = (idx - 1) / 2;
        size_t left = 2 * parent + 1;
        size_t right = 2 * parent + 2;

        int left_val = (left < tree_size && win[left] != -1) ? arr[win[left]] : INT_MIN;
        int right_val = (right < tree_size && win[right] != -1) ? arr[win[right]] : INT_MIN;

        if (left_val > right_val) {
            win[parent] = win[left];
        } else {
            win[parent] = (right_val != INT_MIN) ? win[right] : win[left];
        }
        idx = parent;
    }
}

void tournament_sort(std::vector<int>& arr) {
    const size_t n = arr.size();
    if (n <= 1) return;

    const size_t tree_size = calculate_tree_size(n);
    std::vector<int> win(tree_size, -1);

    const size_t leaf_start = tree_size / 2;
    for (size_t i = 0; i < n; ++i) {
        win[leaf_start + i] = i;
    }

    for (int i = static_cast<int>(leaf_start - 1); i >= 0; --i) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;

        int left_val = (left < tree_size && win[left] != -1) ? arr[win[left]] : INT_MIN;
        int right_val = (right < tree_size && win[right] != -1) ? arr[win[right]] : INT_MIN;

        if (left_val > right_val) {
            win[i] = win[left];
        } else {
            win[i] = (right_val != INT_MIN) ? win[right] : win[left];
        }
    }

    for (size_t i = n - 1; i > 0; --i) {
        const size_t max_idx = win[0];
        swap(arr, max_idx, i);

        // 정렬된 위치(i)만 무효화
        size_t invalidate_pos = leaf_start + i;
        if (invalidate_pos < tree_size && invalidate_pos >= leaf_start && invalidate_pos < leaf_start + n) {
            win[invalidate_pos] = -1;
            update_tree(arr, win, invalidate_pos, tree_size);
        }

        // 변경된 최대값 위치 업데이트
        if (max_idx < i) { // max_idx가 유효한 범위 내에 있는지 확인
            size_t update_pos = leaf_start + max_idx;
            if (update_pos < tree_size && update_pos >= leaf_start && update_pos < leaf_start + n) {
                update_tree(arr, win, update_pos, tree_size);
            }
        }
    }
}

int main(int argc, char* argv[]) {
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
    tournament_sort(numbers);

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

    return 0;
    
    // if (argc != 3) {
    //     cerr << "Usage: " << argv[0] << " <input> <output>\n";
    //     return 1;
    // }

    // vector<int> numbers;
    // ifstream in(argv[1]);
    // int num;
    // while (in >> num) numbers.push_back(num);

    // tournament_sort(numbers);

    // ofstream out(argv[2]);
    // for (auto n : numbers) out << n << "\n";

    // return 0;
}