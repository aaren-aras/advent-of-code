#include <fstream>
#include <iostream>
#include <string>
#include <vector>
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

        // Check for pair of non-overlapping letters (e.g., "xyxy", but not "xxx")
        bool pairOfLetterPairs {};
        for (int i = 0; i < line.size() - 2; ++i) {
            for (int j = i + 2; j < line.size(); ++j) {
                // std::cout << std::format(
                //     "Checking {} against {}\n", 
                //     line.substr(i, 2), line.substr(j, 2)
                // );
                if (line.substr(i, 2) == line.substr(j, 2)) {
                    pairOfLetterPairs = true;
                    break;
                }
            }
        }

        // Check for repeating characters with a letter between them (e.g., "aba", "bab")
        for (int i = 0; i < line.size() - 2; ++i) {
            // std::cout << std::format(
            //     "Checking {} against {}\n", 
            //     line[i], line[i + 2]
            // );
            if (pairOfLetterPairs && (line[i] == line[i + 2])) {
                numNiceStr++;
                break;
            }
        }
    }
    std::cout << std::format("There are {} nice strings.\n", numNiceStr);
    
}