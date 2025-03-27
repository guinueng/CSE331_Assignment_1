#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    // 명령줄 인자로 받은 파일 이름을 배열(벡터)에 저장
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file1> <input_file2> ... <output_file>" << std::endl;
        return 1;
    }

    // 마지막 인자는 출력 파일로 사용
    std::string outputFile = argv[argc - 1];
    std::vector<std::string> inputFiles;

    for (int i = 1; i < argc - 1; ++i) {
        inputFiles.push_back(argv[i]);
    }

    // 입력 파일에서 데이터를 읽고 처리
    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Error: Could not open output file: " << outputFile << std::endl;
        return 1;
    }

    for (const auto& fileName : inputFiles) {
        std::ifstream inFile(fileName);
        if (!inFile) {
            std::cerr << "Error: Could not open input file: " << fileName << std::endl;
            continue; // 다음 파일로 넘어감
        }

        outFile << "Contents of file: " << fileName << "\n";
        std::string line;
        while (std::getline(inFile, line)) {
            outFile << line << "\n"; // 읽은 내용을 출력 파일에 저장
        }
        outFile << "\n"; // 파일 간 구분을 위해 빈 줄 추가
        inFile.close();
    }

    outFile.close();
    std::cout << "Data has been written to " << outputFile << std::endl;

    return 0;
}