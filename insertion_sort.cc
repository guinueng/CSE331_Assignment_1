#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
    numbers.push_back(-1);

    // Read numbers from file.
    int number;
    while (inFile >> number){
        // Add numbers in vector.
        numbers.push_back(number);
    }

    // 배열에 저장된 데이터 출력
    std::cout << "Numbers read from file:\n";
    for (size_t i = 1; i < numbers.size(); ++i) {
        std::cout << numbers[i] << " ";
        if ((i + 1) % 10 == 0) { // 줄바꿈 (10개씩 출력)
            std::cout << "\n";
        }
    }
    std::cout << "\n";

    inFile.close();

    for(size_t j = 2; j < numbers.size(); j++){
        int key = numbers[j];

        size_t i = j - 1;
        while(i > 0 && numbers[i] > key){
            numbers[i + 1] = numbers[i];
            i--;
        }

        numbers[i + 1] = key;
    }

    // 결과를 새로운 파일에 저장
    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Error: Could not open output file: " << outputFile << std::endl;
        return 1;
    }

    if (!outFile) {
        std::cerr << "Error: Could not create output file.\n";
        return 1;
    }

    for (const auto& num : numbers) {
        outFile << num << "\n"; // 한 줄에 하나의 숫자 저장
    }

    outFile.close();
    std::cout << "Processed data has been written to 'output.txt'.\n";

    return 0;
}