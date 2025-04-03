#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <chrono>
#include <cmath>
#include <bits/stdc++.h>
#include <algorithm>
#include <stack>

const int MIN_GALLOP = 7;

// 최소 런 길이 계산 (Python 구현 방식)
int calc_min_run(int n) {
    int r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

// 자연스러운 런 탐지 및 역전
void find_and_reverse_run(std::vector<int>& arr, int& start, int& end) {
    bool increasing = true;
    if (start >= arr.size() - 1) return;

    // 증가/감소 방향 탐지
    int i = start;
    while (i < arr.size() - 1 && arr[i] == arr[i+1]) i++;
    if (i < arr.size() - 1) increasing = (arr[i] < arr[i+1]);

    // 런 끝까지 탐색
    end = start;
    while (true) {
        if (increasing) {
            while (end < arr.size()-1 && arr[end] <= arr[end+1]) end++;
        } else {
            while (end < arr.size()-1 && arr[end] >= arr[end+1]) end++;
        }
        if (++end >= arr.size()) break;
        if (increasing != (arr[end-1] < arr[end])) break;
    }

    // 감소 런 역전
    if (!increasing) {
        std::reverse(arr.begin() + start, arr.begin() + end);
    }
}

// 갤럽 서치 (오른쪽 방향)
int gallop_right(int key, const std::vector<int>& arr, int base, int len) {
    int last_offset = 0, offset = 1;
    while (offset < len && arr[base + offset] <= key) {
        last_offset = offset;
        offset = (offset << 1) + 1;
    }
    int upper = std::min(base + offset, base + len);
    auto pos = std::upper_bound(arr.begin() + base + last_offset,
                               arr.begin() + upper, key); // Need to impl as bin search.
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
                               arr.begin() + base + len - last_offset, key); // Need to impl as bin search.
    return pos - (arr.begin() + base);
}

void insertion_sort(std::vector<int>& arr, int l, int r) { // bin insertion sort 적용시키기
    for (int i = l + 1; i <= r; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= l && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
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
            int gallop_count = gallop_right(right[j], left, i, len1 - i); // Gallop 수정 필요.
            for (int a = 0; a < gallop_count; ++a) { // 넣을 때도 gallop 적용 필요.
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
    if (arr.size() <= 1) return;

    const int n = arr.size();
    const int min_run = calc_min_run(n);
    // const int min_run = 64;
    // std::vector<std::pair<int, int>> runs;
    std::stack<std::pair<int, int>> runs;
    int current = 0;

    // 1단계: 자연스러운 런 생성
    while (current < n) {
        int start = current;
        int end = current;

        // 자연스러운 런 탐지
        find_and_reverse_run(arr, start, end);

        // 최소 런 길이 확장
        if (end - start + 1 < min_run) {
            end = std::min(start + min_run - 1, n-1);
            insertion_sort(arr, start, end);
        }

        runs.push(std::pair<int, int>(start, end));

        // 2. 스택 기반 병합
        // 지역성 유지를 위해 런이 생길 때 마다 조건을 검사
        // 병합 조건 검사 (Z > Y + X && Y > X)
        while (runs.size() >= 3) {
            auto z = runs.top(); runs.pop();
            auto y = runs.top(); runs.pop();
            auto x = runs.top(); runs.pop();

            const int len_z = z.second - z.first + 1;
            const int len_y = y.second - y.first + 1;
            const int len_x = x.second - x.first + 1;

            if (len_x <= len_y + len_z) { // Case 1. X < Y + Z
                if (len_x < len_z) { // Case 1-1. X < Z
                    merge(arr, x.first, x.second, y.second);
                    runs.emplace(x.first, y.second);
                    runs.push(z);
                } else { // Case 1-2. X > Z
                    merge(arr, y.first, y.second, z.second);
                    runs.push(x);
                    runs.emplace(y.first, z.second);
                }
                // Case 1 에서 X > Y 는 보장 되어 있기 때문에 고려할 필요가 없음.
            }
            else if(len_y <= len_z){ // Case 2. X > Y + Z, Y < Z
                merge(arr, y.first, y.second, z.second);
                runs.push(x);
                runs.emplace(y.first, z.second);
            }
            else { // Case 3. X > Y > Z
                runs.push(x);
                runs.push(y);
                runs.push(z);
                break;
            }
        }

        if(runs.size() == 2){
            auto y = runs.top(); runs.pop();
            auto x = runs.top(); runs.pop();

            const int len_y = y.second - y.first + 1;
            const int len_x = x.second - x.first + 1;
            if(len_x < len_y){ // Case 4. X < Y
                merge(arr, x.first, x.second, y.second);
                runs.emplace(x.first, y.second);
            }
            else{ // Case 5. X > Y
                runs.push(x);
                runs.push(y);
            }
        }

        current = end + 1;
    }

    // 병합 조건 검사 (Z > Y + X && Y > X)
    while (runs.size() >= 3) {
        auto z = runs.top(); runs.pop();
        auto y = runs.top(); runs.pop();
        auto x = runs.top(); runs.pop();

        const int len_z = z.second - z.first + 1;
        const int len_y = y.second - y.first + 1;
        const int len_x = x.second - x.first + 1;

        if (len_x <= len_y + len_z) {
            if (len_x < len_z) {
                merge(arr, x.first, x.second, y.second);
                runs.emplace(x.first, y.second);
                runs.push(z);
            } else {
                merge(arr, y.first, y.second, z.second);
                runs.push(x);
                runs.emplace(y.first, z.second);
            }
        }
        else if(len_y <= len_z){
            merge(arr, y.first, y.second, z.second);
            runs.push(x);
            runs.emplace(y.first, z.second);
        }
        else {
            runs.push(x);
            runs.push(y);
            runs.push(z);
            break;
        }
    }

    if(runs.size() == 2){
        auto y = runs.top(); runs.pop();
        auto x = runs.top(); runs.pop();

        const int len_y = y.second - y.first + 1;
        const int len_x = x.second - x.first + 1;
        if(len_x < len_y){
            merge(arr, x.first, x.second, y.second);
            runs.emplace(x.first, y.second);
        }
        else{
            runs.push(x);
            runs.push(y);
        }
    }

    // 잔여 런 병합
    while (runs.size() > 1) {
        auto b = runs.top(); runs.pop();
        auto a = runs.top(); runs.pop();
        merge(arr, a.first, a.second, b.second);
        runs.emplace(a.first, b.second);
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