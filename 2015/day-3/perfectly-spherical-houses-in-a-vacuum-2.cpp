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
    int numHouses {1}; // that receive at least one present, initialized to 2 for starting house 
    
    Coord santaCoord {0, 0};
    Coord roboSantaCoord {0, 0};

    std::vector<Coord> pastCoords;
    pastCoords.push_back(santaCoord); // pre-add starting house at x=0, y=0

    bool santaTurn = true; // Santa starts first 
    // int iteration {};

    // Loop through file, character by character, until EOF
    while (inputFile.get(ch)) {
        if (santaTurn) {
            // Update position
            if (ch == '^') santaCoord.y++;
            else if (ch == 'v') santaCoord.y--;
            else if (ch == '>') santaCoord.x++;
            else if (ch == '<') santaCoord.x--;
            // std::cout << std::format("Santa is now at {{{}, {}}}.\n", santaCoord.x, santaCoord.y);

            // Check if Santa or Robo-Santa haven't already been to the house Santa's currently at 
            if (std::find(pastCoords.begin(), pastCoords.end(), santaCoord) == pastCoords.end()) {
                numHouses++;
                // Add his current position to a growing bank of positions he's been to
                pastCoords.push_back(santaCoord);
                // for (Coord coord : pastCoords) {
                //     std::cout << std::format("Santa: {{{}, {}}}\n", coord.x, coord.y); // {{ prints as {
                // }
            }
            santaTurn = false;
        // Robo-Santa's turn 
        } else {
            // Update position
            if (ch == '^') roboSantaCoord.y++;
            else if (ch == 'v') roboSantaCoord.y--;
            else if (ch == '>') roboSantaCoord.x++;
            else if (ch == '<') roboSantaCoord.x--;
            // std::cout << std::format("Robo-Santa is now at {{{}, {}}}.\n", roboSantaCoord.x, roboSantaCoord.y);

            // Check if Santa or Robo-Santa haven't already been to the house Robo-Santa's currently at 
            if (std::find(pastCoords.begin(), pastCoords.end(), roboSantaCoord) == pastCoords.end()) {
                numHouses++;
                // Add his current position to a growing bank of positions he's been to
                pastCoords.push_back(roboSantaCoord);
                // for (Coord coord : pastCoords) {
                //     std::cout << std::format("Robo-Santa: {{{}, {}}}\n", coord.x, coord.y); // {{ prints as {
                // }
            }
            santaTurn = true;
        }
        // iteration++;
        // if (iteration == 3) break;
    }
    std::cout << std::format("{} houses receive at least one present.\n", numHouses);

    return 0;
}