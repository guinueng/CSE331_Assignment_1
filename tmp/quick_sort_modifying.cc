#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <chrono>

void swap(std::deque<int>& arr, int l_pos, int r_pos){
    int tmp = arr[l_pos];
    arr[l_pos] = arr[r_pos];
    arr[r_pos] = tmp;
}

void quick_sort(std::deque<int>& arr, int s, int e){

    // std::cout << "\ns: " << s << " e: " << e << "\n";

    // int back = arr.size() - 1;

    if((e - s) <= 0){
        return;
    }

    // 1. Select pivot at the last point of arr.
    int pivot = arr.at(e); // Pivot can be any value. In assignment document, test it and add it.
    // std::cout << "pivot: " << pivot << "\n";
    // Pivot = back elem > can cause stack overflow. > need to increase stack

    // std::cout << "\ninput arr: ";
    // for(int i = s; i <= e; i++){
    //     std::cout << arr.at(i) << " ";
    // }
    // std::cout << "\n";

    // 2. Move integer into 3 sub-array which is designed to
    //    store less than / equal / higher than pivot.
    // std::deque<int> S, E, H;
    int k = s, h = e - 1, cnt = 0;
    while(cnt != (e - s)){
        // std::cout << "\nsorting_arr: ";
        // for(int i = s; i <= e; i++){
        //     std::cout << arr.at(i) << " ";
        // }
        // std::cout << "\n";
        if(arr.at(k) < pivot){
            // S.push_back(arr.at(i));
            k++;
        }
        else if(arr.at(k) > pivot){
            // H.push_back(arr.at(i));
            swap(arr, k, h);
            h--;
        }
        else{
            // E.push_back(arr.at(i));
            cnt++;
            swap(arr, k, e - cnt);
        }
        // arr.pop_back();
        if(k >= h){
            break;
        }
        // cnt--;
    }

    // std::cout << "\nsorted_arr: ";
    // for(int i = s; i <= e; i++){
    //     std::cout << arr.at(i) << " ";
    // }
    // std::cout << "\n";

    // std::cout << "h: " << h << std::endl;

    int pivot_idx = e, pivot_start = s;
    bool pivot_mod = false;
    bool pivot_exit = false;
    for(int i = s; i <= e - 1; i++){
        if(arr.at(i) > arr.at(pivot_idx)){
            if(arr.at(pivot_idx - 1) != pivot){
                pivot_exit = true;
            }
            swap(arr, i, pivot_idx);
            if(!pivot_mod){
                pivot_start = i;
                pivot_mod = true;
            }
            pivot_idx--;
            if(pivot_exit){ // Need to mod it. 
                pivot_idx = i;
                break;
            }
        }
    }
    // swap(arr, h, e);

    // std::cout << "\nswap_arr: ";
    // for(int i = s; i <= e; i++){
    //     std::cout << arr.at(i) << " ";
    // }
    // std::cout << "\n";

    // int pos = s;
    // while(!S.empty()){
    //     arr.at(pos) = S.front();
    //     S.pop_front();
    //     pos++;
    // }
    // while(!E.empty()){
    //     arr.at(pos) = E.front();
    //     E.pop_front();
    //     pos++;
    // }
    // while(!H.empty()){
    //     arr.at(pos) = H.front();
    //     H.pop_front();
    //     pos++;
    // }

    // S.resize(0);
    // E.resize(0);
    // H.resize(0);

    // std::cout << k << "h: " << h << "\n";

    // 3. Since arr E is already sorted(due to it is same as
    //    pivot), so we sort S and H arr.
    // if(e == 3 || s == 5){
    //     return;
    // }

    // std::cout << pivot_start << pivot_idx << std::endl;
    if(s < pivot_start - 1)
        quick_sort(arr, s, pivot_start - 1);
    if(pivot_idx + 1 < e)
        quick_sort(arr, pivot_idx + 1, e);

    // 4. Finally, combine sorted result into original array.
    // for(auto i: S){
    //     arr.push_back(i);
    // }

    // for(auto i: E){
    //     arr.push_back(i);
    // }

    // for(auto i: H){
    //     arr.push_back(i);
    // }
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

    // Allocate deque to store numbers read in file.
    std::deque<int> numbers;
    // numbers.reserve(1000001);

    // Read numbers from file.
    int number;
    while (inFile >> number){
        // Add numbers in deque.
        numbers.push_back(number);
    }

    // Print data from read file.
    // std::cout << "Numbers read from file:\n";
    // for (int i = 0; i < numbers.size(); ++i) {
    //     std::cout << numbers[i] << " ";
    //     if ((i + 1) % 10 == 0) {
    //         // Print 10 element and make new line.
    //         std::cout << "\n";
    //     }
    // }

    // Close input file.
    inFile.close();

    // Start measuring sort_func exec time.
    auto sort_start = std::chrono::high_resolution_clock::now();

    // Pursue merge sort.
    quick_sort(numbers, 0, numbers.size() - 1);

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
}