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
#include <cassert>

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

int gallop_right(int key, const std::vector<int>& arr, int start, int length) {
    int low = start;
    int high = start + length;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] <= key) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

int gallop_left(int key, const std::vector<int>& arr, int start, int length) {
    int low = start;
    int high = start + length;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

void insertion_sort(std::vector<int>& arr, int l, int r) { // bin insertion sort 적용시키기
    for (int i = l + 1; i <= r; i++) {
        int key = arr[i];

        int j = i - 1;
        while (j >= l && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// for(size_t j = 2; j < numbers.size(); j++){
//     int key = numbers[j];

//     size_t i = j - 1;
//     while(i > 0 && numbers[i] > key){
//         numbers[i + 1] = numbers[i];
//         i--;
//     }

//     numbers[i + 1] = key;
// }

// Binary search to find the correct position for the key
// int binary_search(const std::vector<int>& arr, int l, int r, int key) {
//     int left = l;
//     int right = r;

//     while (left <= right) {
//         int mid = left + (right - left) / 2;

//         if (arr[mid] == key) {
//             return mid; // Exact match (rare in sorting)
//         } else if (arr[mid] < key) {
//             left = mid + 1; // Search in the right half
//         } else {
//             right = mid - 1; // Search in the left half
//         }
//     }

//     return left; // Return the position where `key` should be inserted
// }

// // Binary insertion sort algorithm
// void insertion_sort(std::vector<int>& arr, int l, int r) {
//     std::cout << "insert\n";
//     for (int i = l + 1; i <= r; ++i) {
//         int key = arr[i];
//         // Find the position to insert the key using binary search
//         int pos = binary_search(arr, l, i - 1, key);

//         // Shift elements to make space for the key
//         for (int j = i - 1; j >= pos; --j) {
//             arr[j + 1] = arr[j];
//         }

//         // Insert the key at the correct position
//         arr[pos] = key;
//     }
// }


void merge(std::vector<int>& arr, int l, int m, int r) {
    int len1 = m - l + 1;
    int len2 = r - m;

    int i = 0, j = 0, k = l, original = 0;
    int left_wins = 0, right_wins = 0;
    int min_gallop = MIN_GALLOP;
    original = len1;
    int left_limit = 0;
    int right_limit = 0;

    std::cout << "l: " << l << " m: " << m << " r: " << r << "\n";

    if(len1 < len2){ // Input small one first to use one array(in-place) method.
        std::cout << "small one is left\n";
        std::vector<int> left(len1);
        std::copy(arr.begin() + l, arr.begin() + m + 1, left.begin());

        for(size_t tmp = l; tmp <= r; tmp++){
            std::cout << arr[tmp] << " ";
            // cnt++;
            if(tmp == m){
                std::cout << "\n\n";
            }
            if((tmp - l + 1) % 12 == 0){
                std::cout << "\n";
            }
        }
        std::cout << "left[0]: " << left[0] << " arr[m + 1]: " << arr[m + 1];

        if(arr[m + 1] > left[0]){ // 넘기다 un-necessary part of front.
            std::cout << " !! right big\n";
            left_limit = gallop_right(arr[m + 1], left, 0, len1);
            i = left_limit;
            k += i;
        }
        else{
            std::cout << "!! left big\n";
            right_limit = gallop_right(left[0], arr, m + 1, len2) - (m + 1);
            j = right_limit;
            for (int a = 0; a < j; a++) { // 넣을 때도 gallop 적용 필요.
                arr[k++] = arr[m + 1 + a];
            }
        }

        // std::cout << "left[len1 - 1]: " << left[len1 - 1] << " arr[r]: " << arr[r];

        // if(arr[r] > left[len1 - 1]){ // 넘기다 un-necessary part of front.
        //     std::cout << "!! right big\n";
        //     len2 = gallop_left(left[len1 - 1], arr, m + 1 + j, len2) - (m + 1);
        // }
        // else{
        //     std::cout << "!! left big\n";
        //     original = len1;
        //     len1 = gallop_left(arr[r], left, i, len1);
        // }

        std::cout << "len1: " << len1 << " len2: " << len2 << "\n";
        std::cout << "i: " << i << " j: " << j << "\n";
        size_t trial = 1;
        while (i < len1 && j < len2) {
            std::cout << "\n\nwhile_loop " << trial++ <<"th\n\narray:\n";
            for(size_t tmp = l; tmp <= r; tmp++){
                std::cout << arr[tmp] << " ";
                // cnt++;
                if((tmp - l + 1) % 12 == 0){
                    std::cout << "\n";
                }
            }
            std::cout << "\nleft number on left: \n";
            for(size_t tmp = left_limit + i; tmp < len1; tmp++){
                std::cout << tmp << ": " << left[tmp] << " ";
                if((tmp - left_limit + 1) % 12 == 0){
                    std::cout << "\n";
                }
            }
            std::cout << "\nl: " << l << " m: " << m << " r: " << r << "\n";
            std::cout << "\ni: " << i << " j: " << j << " m + j + 1: " << m + j + 1 << "\n";
            std::cout << "len1: " << len1 << " len2: " << len2 << " original: " << original <<"\n";
            std::cout << "left wins: " << left_wins << " right wins: " << right_wins << "\n";
            // if (left_wins >= min_gallop) {
            //     // if input qty on arr element either left or right array is bigger than gallop, go to gallop mode.
            //     int gallop_count = gallop_right(arr[m + 1 + j], left, i, len1 - i) - i; // Gallop 수정 필요.
            //     std::cout << "gallop: " << gallop_count << "\n";
            //     for (int a = 0; a < gallop_count; ++a) { // 넣을 때도 gallop 적용 필요.
            //         arr[k++] = left[i++];
            //     }
            //     left_wins = 0;

            //     if (i >= len1) break;

            //     min_gallop += (gallop_count < MIN_GALLOP) ? 1 : -1;
            //     min_gallop = std::max(1, min_gallop);
            //     continue;
            // }

            // if (right_wins >= min_gallop) {
            //     // if input qty on arr element either left or right array is bigger than gallop, go to gallop mode.
            //     int gallop_count = gallop_right(left[i], arr, m + 1 + j, len2 - j) - (m + j);
            //     std::cout << "gallop: " << gallop_count << "\n";
            //     for (int b = 0; b < gallop_count; ++b) {
            //         arr[k++] = arr[m + 1 + j]; j++;
            //     }
            //     right_wins = 0;
    
            //     min_gallop += (gallop_count < MIN_GALLOP) ? 1 : -1;
            //     min_gallop = std::max(1, min_gallop);
            //     continue;
            // }

            if (left[i] < arr[m + 1 + j]) {
                arr[k++] = left[i++];
                ++left_wins;
                right_wins = 0;
            } else {
                arr[k++] = arr[m + 1 + j]; j++;
                ++right_wins;
                left_wins = 0;
            }
            // return;
        }
        
        std::cout << "END LOOP\n";
        while (original > i)
            arr[k++] = left[i++];
        std::cout << "REAL END\n";
    }
    else{ // Input bigger one first to use one array(in-place) method.-------------------------------------------------------------------------------->
        std::cout << "small one is right\n";
        std::vector<int> right(len2);
        std::copy(arr.begin() + m + 1, arr.begin() + r + 1, right.begin());
        k = r;
        original = len2;

        std::cout << "right[0]: " << right[0] << " arr[l]: " << arr[l] << "\n";
        for(size_t tmp = l; tmp <= r; tmp++){
            std::cout << arr[tmp] << " ";
            // cnt++;
            if(tmp == m){
                std::cout << "\n\n";
            }
            if((tmp - l + 1) % 12 == 0 ){
                std::cout << "\n";
            }
        }

        if(right[0] >= arr[l]){ // pass consideration of sorting un-necessary part of front.
            // Case 1. Right arr first is bigger than left arr first. > do not merge some of left part.
            std::cout << "1\n";
            left_limit = gallop_right(right[0], arr, l, len1) - l;
            std::cout << "left_limit: " << left_limit << std::endl;
            len1 -= left_limit;
        }
        else{
            // Case 2. Left arr first is bigger than right part arr first. > do not merge some of right part.
            // Need to deal it last part.
            std::cout << "2\n";
            right_limit = gallop_right(arr[l], right, 0, len2);
            std::cout << "right_limit: " << right_limit << std::endl;
            len2 -= right_limit;
        }

        if(right[len2 - 1] >= arr[m]){ // pass consideration of sorting un-necessary part of back.
            // Case 3. Right arr final is bigger than left arr final. > stay right part.
            std::cout << "3\n";
            j = (len2 + right_limit) - gallop_left(arr[m], right, right_limit, len2);
            k -= j;
        }
        // else{
        //     // Case 4. Left arr final is bigger than right arr final. > copy left part one into right part.
        //     std::cout << "Case 4.\n";
        //     size_t tmp_pos = gallop_left(right[len2 - 1], arr, l + left_limit, len1) - l;
        //     std::cout << len1 << " <- len1 m: " << m << " tmp_pos: " << tmp_pos << "\n";
        //     for(size_t tmp = tmp_pos; tmp < (len1 + left_limit); tmp++){
        //         std::cout << tmp << " ";
        //         arr[k--] = arr[m - i];
        //         i++;
        //     }
        //     std::cout << "\n";
        // }

        std::cout << "len1: " << len1 << " len2: " << len2 << "\n";
        std::cout << "i: " << i << " j: " << j << "\n";
        std::cout << "left limit: " << left_limit << " right limit: " << right_limit;
        size_t cnt = 0;
        size_t trial = 1;
        while (i < len1 && j < len2) {
            std::cout << "\n\nwhile_loop " << trial++ <<"th\n\narray:\n";
            for(size_t tmp = l; tmp <= r; tmp++){
                std::cout << arr[tmp] << " ";
                // cnt++;
                if(tmp == m){
                    std::cout << "\n\n";
                }
                if((tmp - l + 1) % 12 == 0){
                    std::cout << "\n";
                }
            }
            std::cout << "\nleft number on right: \n";
            for(size_t tmp = right_limit; tmp < original - j; tmp++){
                std::cout << right[tmp] << " ";
                if((tmp - right_limit + 1) % 12 == 0){
                    std::cout << "\n";
                }
            }
            std::cout << "\ni: " << i << " j: " << j << "\n";
            std::cout << "len1: " << len1 << " len2: " << len2 << "\n";
            // if (left_wins >= min_gallop) {
            //     std::cout << "\ngallop" << std::endl;
            //     // if input qty on arr element either left or right array is bigger than gallop, go to gallop mode.
            //     std::cout << "right[len2 - j - 1]: " << right[len2 - j - 1] << " \n";
            //     int gallop_count = (len1 + left_limit) - (gallop_left(right[len2 - j - 1], arr, l + left_limit, len1 - i) - j) + 1; // Gallop 수정 필요.
            //     std::cout << "left count: " << gallop_count << "len1 - i: " << len1 - i << std::endl;
            //     for (int a = 0; a < gallop_count; a++) { // 넣을 때도 gallop 적용 필요.
            //         arr[k--] = arr[m - i]; i++;
            //     }
            //     left_wins = 0;

            //     min_gallop += (gallop_count < MIN_GALLOP) ? 1 : -1;
            //     min_gallop = std::max(1, min_gallop);
            //     std::cout << "\ni: " << i << " j: " << j << " m + j + 1: " << m + j + 1 << "\n";
            //     continue;
                
            // }

            // if(right_wins >= min_gallop){
            //     int gallop_count = (len2 + right_limit) - gallop_left(arr[m - i], right, right_limit, len2 - j) + 1;
            //     std::cout << "right gallop count: " << gallop_count << std::endl;
            //     for (int b = 0; b < gallop_count; b++) {
            //         arr[k--] = right[len2 - j - 1]; j++;
            //     }
            //     right_wins = 0;

            //     min_gallop += (gallop_count < MIN_GALLOP) ? 1 : -1;
            //     min_gallop = std::max(1, min_gallop);
            //     std::cout << "\ni: " << i << " j: " << j << " m + j + 1: " << m + j + 1 << "\n";
            //     continue;
            // }

            if (arr[m - i] >= right[original - j - 1]) {
                arr[k--] = arr[m - i];
                i++;
                ++left_wins;
                right_wins = 0;
            } else {
                arr[k--] = right[original - j - 1];
                j++;
                ++right_wins;
                left_wins = 0;
            }
        }
        std::cout << "END\noriginal: " << original << " j: " << j << "\n";
        while(len1 > i){
            arr[k--] = arr[m - i];
            i++;
        }
        while(original > j){
            std::cout << original << "calc: " << original - j - 1 << std::endl;
            arr[k--] = right.at(original - j - 1);
            j++;
        }
        std::cout << "REAL END\n";
        for(size_t tmp = l; tmp <= r; tmp++){
            std::cout << arr[tmp] << " ";
            // cnt++;
            if(tmp == m){
                std::cout << "\n\n";
            }
            if((tmp - l + 1) % 12 == 0){
                std::cout << "\n";
            }
        }
        std::cout << "sorted\n";
    }
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

        std::cout << "start: " << start << " end: " << end << "\n";

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

    std::cout << "\n\nsorted:\n";
    size_t cnt = 1;
    for(auto i : arr){
        std::cout << i << " ";
        cnt++;
        if(cnt % 12 == 1){
            std::cout << "\n";
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