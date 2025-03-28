#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // For std::system
#include <fstream> // For file handling

// Function to run a program with arguments and capture its output
void runProgram(const std::string& program, const std::string& input_arg, const std::string& output_arg) {
    // Construct the command string
    std::string command = program + " ./test_case/" + input_arg + " ./test_case/" + output_arg; // Redirect output to a file

    // Print the results
    std::cout << "Results from " << program << " w/ input file: " << input_arg << ":" << std::endl;

    // Execute the command
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Error running program: " << program << std::endl;
        return;
    }

    // std::cout << std::endl;

    // Read the output from the file
    std::ifstream outputFile("./test_case/" + output_arg);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return;
    }

    // Print the results
    std::cout << "Results from " << program << " w/ input file: " << input_arg;
    bool stat = true;

    // Read numbers from file.
    int number;
    int prev_number;
    bool first = true;
    while (outputFile >> number){
        std::cout << number << "\n";
        if(first){
            prev_number = number;
            first = false;
        }
        else{
            if(prev_number > number){
                stat = false;
                break;
            }
        }
    }

    if(stat){
        std::cout << " is Valid." << std::endl;
    }
    else{
        std::cout << " is Failed." << std::endl;
    }

    outputFile.close();
}

int main() {
    // List of programs and their arguments
    std::vector<std::string> progs = {
        // "./merge_sort",
        "./heap_sort",
        // "./bubble_sort",
        // "./insertion_sort",
        // "./selection_sort",
        // "./quick_sort"
    };

    std::vector<std::pair<std::string, std::string>> args = {
        // {"input.txt", "output.txt"},
        {"unsorted_1k.txt", "1k_output.txt"},
        // {"sorted_1k.txt", "1k_output.txt"},
        // {"unsorted_1m.txt", "1m_output.txt"},
        // {"sorted_1m.txt", "1m_output.txt"},
        // {"unsorted_1m_2.txt", "1m_output_2.txt"},
        // {"sorted_1m_2.txt", "1m_output_2.txt"},
        // {"partially_sorted_1m.txt", "partially_1m_output.txt"},
        // {"dup_1m.txt", "dup_1m_output.txt"},
        // {"descend_1m.txt", "descend_1m_output.txt"}
    };

    // Run each program in sequence
    for (const auto& prog : progs) {
        for(const auto& [input_arg, output_arg] : args){
            runProgram(prog, input_arg, output_arg);
            std::cout << "------------------------------------" << std::endl;
        }
    }

    return 0;
}
