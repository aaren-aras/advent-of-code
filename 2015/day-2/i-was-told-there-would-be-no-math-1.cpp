#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <format>

int main() {

    // Read text file
    std::ifstream inputFile("i-was-told-there-would-be-no-math.txt");

    // Check if file opened
    if (!inputFile.is_open()) {
        std::cerr << "*ERROR: Could not open file... :(\n";
        return 1;
    }

    // Loop through file, line by line, until EOF 
    std::string line {};
    int totalWrappingPaper {};
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        
        int dims[3];
        char delimiter;

        iss >> dims[0] >> delimiter >> dims[1] >> delimiter >> dims[2];
        int l = dims[0];
        int w = dims[1];
        int h = dims[2];
        // std::cout << std::format("Length: {}, Width: {}, Height: {}\n", l, w, h); 

        int surfaceArea = 2*l*w + 2*w*h + 2*h*l;
        totalWrappingPaper += (surfaceArea + std::min({l*w, w*h, h*l}));
    }
    std::cout << std::format("They should order {} square feet of wrapping paper.\n", totalWrappingPaper);

    return 0;
}