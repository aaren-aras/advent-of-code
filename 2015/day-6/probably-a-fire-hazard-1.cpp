#include <fstream>
#include <iostream>
#include <sstream>
#include <format>

int main() {

    // Read text file
    std::ifstream inputFile("probably-a-fire-hazard.txt");

    // Check if file opened
    if (!inputFile.is_open()) {
        std::cerr << "*ERROR: Could not open file... :(\n";
        return 1;
    }

    std::string line {};
    bool grid[1000][1000] {};
    int litLights {};

    // Loop through file, line by line, until EOF
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);

        std::string firstWord {}; 
        std::string foobar {}; // "on"/"off" (ln 32), "through" (ln 33)
        int a, b, x, y {};
        char delimiter; // ','

        // Remove second word if needed, then parse for ranges
        iss >> firstWord;
        if (firstWord == "turn") iss >> foobar;
        iss >> a >> delimiter >> x >> foobar >> b >> delimiter >> y; 
        // std::cout << std::format("a: {}, b {}, x {}, y {}\n", a, b, x, y);

        for (int i = a; i <= b; ++i) { // ranges are inclusive
            for (int j = x; j <= y; ++j) {
                if (line.contains("turn on")) grid[i][j] = true;
                else if (line.contains("turn off")) grid[i][j] = false;
                else if (line.contains("toggle")) grid[i][j] = !grid[i][j];
            }
        }
    }

    // Loop through entire grid and count lit lights
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 1000; ++j) {
            if (grid[i][j]) litLights++;
        }
    }

    std::cout << std::format("{} lights are lit.\n", litLights);
}