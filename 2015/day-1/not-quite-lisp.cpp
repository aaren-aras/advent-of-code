#include <iostream>
#include <fstream>
#include <format>

using std::cout;
using std::format;

int main() {
    // Read text file
    std::ifstream inputFile("not-quite-lisp.txt");

    // Check file opened
    if (!inputFile.is_open()) {
        std::cerr << "*ERROR: Could not open file... :(\n";
        return 1;
    }

    char ch;
    int floor_num {};
    
    // Loop through file character by character until EOF
    while (inputFile.get(ch)) ch == '(' ? floor_num++ : floor_num--;
    cout << format("The instructions take Santa to floor {}.\n", floor_num);
}