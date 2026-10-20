#include <fstream>
#include <iostream>
#include <string>
#include <format>

int main() {
    
    // Read text file
    std::ifstream inputFile("doesnt-he-have-intern-elves-for-this.txt");

    // Check if file opened
    if (!inputFile.is_open()) {
        std::cerr << "*ERROR: Could not open file... :(\n";
        return 1;
    }

    std::string line {};
    int numNiceStr {};

    while(std::getline(inputFile, line)) {

        // Check for 'ab', 'cd', 'pq', 'xy' first
        if (line.contains("ab") || line.contains("cd") || line.contains("pq") || line.contains("xy"))
            continue;

        // Count vowels
        int vowelCount {};
        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] == 'a' || line[i] == 'e' || line[i] == 'i' || line[i] == 'o' || line[i] == 'u')
                vowelCount++;
        }
        
        // Check for repeating letters (e.g., "aa", "bb")
        for (size_t i = 0; i < line.size(); ++i) {
            if ((line[i] == line[i + 1]) && vowelCount >= 3) {
                numNiceStr++;
                break;
            }
        }
    }
    std::cout << std::format("There are {} nice strings.\n", numNiceStr);
    
}