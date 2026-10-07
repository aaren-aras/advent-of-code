#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm> // for find()
#include <format>

struct Coord {
    int x;
    int y;

    // Allows == comparison between 2 Coord objects
    bool operator==(const Coord&) const = default;
};

int main() {
    
    // Read text file
    std::ifstream inputFile("perfectly-spherical-houses-in-a-vacuum.txt");

    // Check if file opened
    if (!inputFile.is_open()) {
        std::cerr << "*ERROR: Could not open file... :(\n";
        return 1;
    }

    char ch;
    int numHouses {1}; // that receive at least one present, initialized to 1 for starting house 
    
    Coord currentCoord {0, 0};
    std::vector<Coord> pastCoords;
    pastCoords.push_back(currentCoord); // pre-add starting house at x=0, y=0
    
    // Loop through file, character by character, until EOF
    while (inputFile.get(ch)) {

        // Update Santa's position
        if (ch == '^') currentCoord.y++;
        else if (ch == 'v') currentCoord.y--;
        else if (ch == '>') currentCoord.x++;
        else if (ch == '<') currentCoord.x--;

        // Check if Santa hasn't already been to the house he's currently at 
        if (std::find(pastCoords.begin(), pastCoords.end(), currentCoord) == pastCoords.end()) {
            numHouses++;
            // Add his current position to a growing bank of positions he's been to
            pastCoords.push_back(currentCoord);
            // for (Coord coord : pastCoords) {
            //     std::cout << std::format("{{{}, {}}}\n", coord.x, coord.y); // {{ prints as {
            // }
        }

    }
    std::cout << std::format("{} houses receive at least one present.\n", numHouses);

    return 0;
}