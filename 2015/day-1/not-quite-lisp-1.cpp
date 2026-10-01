#include <fstream>
#include <iostream>
#include <format>

// using std::ifstream;
// using std::cout;
// using std::format;

int main() {
    
    // Read text file
    std::ifstream inputFile("not-quite-lisp.txt");

    // Check if file opened
    if (!inputFile.is_open()) {
        std::cerr << "*ERROR: Could not open file... :(\n";
        return 1;
    }

    char ch;
    int floor_num {};
    
    // Loop through file, character by character, until EOF
    while (inputFile.get(ch)) ch == '(' ? floor_num++ : floor_num--;
    std::cout << std::format("The instructions take Santa to floor {}.\n", floor_num);

    return 0;
}