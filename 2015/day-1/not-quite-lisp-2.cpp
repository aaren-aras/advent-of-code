#include <iostream>
#include <fstream>
#include <format>

using std::cout;
using std::format;

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
    int position {};
    
    // Loop through file character by character until EOF
    while (inputFile.get(ch)) {
        ch == '(' ? floor_num++ : floor_num--;
        position++;

        if (floor_num == -1) break;
    }
    cout << format("The first position that gets Santa to enter the basement is {}.\n", position);

    return 0;
}