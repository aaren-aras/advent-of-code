#include <fstream>
#include <iostream>
#include <vector>
#include <cctype>
#include <cstdint>
#include <utility>
#include <sstream>
#include <string>
#include <algorithm>
#include <format>

uint16_t parseInputFile(std::string outputToGrab, std::vector<std::pair<std::string, uint16_t>>& solvedValues) {
    // Read text file
    std::ifstream inputFile("some-assembly-required.txt");

    std::string line {};
    // std::vector<std::pair<std::string, uint16_t>> solvedValues;

    std::string firstInput, secondInput, nextOutput {};
        int firstInputVal, secondInputVal, iteration {};
        uint16_t outputSignal {};
        std::string operation, arrow, output {};



    // Loop through file, line by line, until all dependencies of wire 'a' reached 

    // while input isnt a constant (e.g., 123123 -> b breaks?)
    while (true) { 

    
        inputFile.clear();
        inputFile.seekg(0);

        // Loop through file, line by line, until EOF
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);


            // parse string: lf AND lq -> ls
            // iss >> firstInput >> operation >> secondInput >> "->" >> output
            
            // parse string: NOT kt -> ku
            // iss >> operation >> firstInput >> "->" >> output

            // parse string: lx -> a
            // iss >> firstInput  >> "->" >> output

            if (line.starts_with("NOT")) iss >> operation >> firstInput >> arrow >> output; 
            // even cleaner way of checking for lines like "lx -> a" and "19138 -> b" ???
            else if (std::count(line.begin(), line.end(), ' ') == 2) iss >> firstInput >> arrow >> output;
            else iss >> firstInput >> operation >> secondInput >> arrow >> output; 
            // std::cout << std::format(
            //     "firstInput: {}, operation: {}, "
            //     "secondInput: {}, arrow: {}, output: {}\n", 
            //     firstInput, operation, secondInput, arrow, output
            // );

            if (output == outputToGrab) {
                // Check if already solved
                auto it = std::find_if(solvedValues.begin(), solvedValues.end(),
                    [&output](const auto& pair) {
                        return pair.first == output;
                    });

                if (it != solvedValues.end()) {
                    std::cout << std::format("Already solved for {}!\n", output);
                    return it->second; // return cached value
                }

                if (firstInput != "" && !std::isdigit(static_cast<unsigned char>(firstInput[0]))) {
                    // std::cout << std::format("Oh! '{}' isn't a signal. Recursing...\n", firstInput);
                    
                    nextOutput = firstInput;

                    firstInputVal = parseInputFile(nextOutput, solvedValues);
                    // firstInput = secondInput = arrow = ""; // reset variables
                } else firstInputVal = std::stoi(firstInput);
                
                if (secondInput != "" && !std::isdigit(static_cast<unsigned char>(secondInput[0]))) { 
                    // std::cout << std::format("Oh! '{}' isn't a signal. Recursing...\n", secondInput);
                    
                    nextOutput = secondInput;

                    secondInputVal = parseInputFile(nextOutput, solvedValues);
                    // firstInput = secondInput = arrow = ""; // reset variables
                } else if (secondInput != "") secondInputVal = std::stoi(secondInput);
                // else {
                //     outputSignal = firstInputVal;
                //     std::cout << std::format("Output of '{}' for line '{}' is '{}'\n", output, line, outputSignal);
                //     return outputSignal;
                // }
                // if firstInput and secondInput are indeed constants like "3423" or "3"
                // firstInputVal = std::stoi(firstInput);
                // secondInputVal = std::stoi(secondInput);
                
                // std::cout << std::format("Yay! '{}' is a signal and '{}' is a signal or empty\n", firstInputVal, secondInputVal);

                // if smth like "234 -> a":
                if (std::count(line.begin(), line.end(), ' ') == 2) outputSignal = firstInputVal;
                // if smth like "2343 OR 2343" -> lx":
                else if (operation == "NOT") outputSignal = ~firstInputVal;
                else if (operation == "AND") outputSignal = firstInputVal & secondInputVal;
                else if (operation == "OR") outputSignal = firstInputVal | secondInputVal;
                else if (operation == "LSHIFT") outputSignal = firstInputVal << secondInputVal;
                else if (operation == "RSHIFT") outputSignal = firstInputVal >> secondInputVal;
                
                // Store solved values in a vector to reference later
                solvedValues.push_back({output, outputSignal});
                std::cout << std::format("{}={} stored into solvedValues\n", output, outputSignal);

                std::cout << std::format("Output of '{}' for line '{}' is '{}'\n", output, line, outputSignal);
                return outputSignal;


                // std::cout << std::format("output: {}, outputToGrabNext: {}\n", output, outputToGrabNext);
            }
            firstInput = operation = secondInput = arrow = output = ""; // reset variables
        }
        iteration++;
    }
}

int main() {
    
    // Read text file
    std::ifstream inputFile("some-assembly-required.txt");

    int iteration {};
    std::string line {};
    std::vector<std::string> dependencies {}; 
    
    // Loop through file, line by line, until all dependencies of wire 'a' reached 
    std::string firstInput, secondInput {};
    std::string outputToGrabNext {"a"};
    
    std::string value {};
    uint16_t signal {};

    std::vector<std::pair<std::string, uint16_t>> solvedValues;


    // loop through file until all paths traced (all inputs taken to their starts as constants)
    signal = parseInputFile("a", solvedValues);
    std::cout << std::format("A signal of {} is provided to wire 'a'.\n", signal);

    // while(!std::isdigit(input[0])) {
    //     input = parseInputFile();
    // }

    // while secondInput isnt a constant (e.g., 123123 -> b breaks?)
    // while (!std::isdigit(firstInput[0])) { 
    //     inputFile.clear();
    //     inputFile.seekg(0);
    //     // Loop through file, line by line, until EOF
    //     while (std::getline(inputFile, line)) {
    //         std::istringstream iss(line);
    //         std::string operation, arrow, output {};

    //         if (line.starts_with("NOT")) {
    //             iss >> operation >> firstInput >> arrow >> output; 
    //         // even cleaner way of checking for lines like "lx -> a" and "19138 -> b" ???
    //         } else if (std::count(line.begin(), line.end(), ' ') == 2) {
    //             iss >> firstInput >> arrow >> output;
    //         } else iss >> firstInput >> operation >> secondInput >> arrow >> output; 

    //         std::cout << std::format(
    //             "firstInput: {}, operation: {}, "
    //             "secondInput: {}, arrow: {}, output: {}\n", 
    //             firstInput, operation, secondInput, arrow, output
    //         );

    //         if (output == outputToGrabNext) {
    //             dependencies.push_back(line);
    //             outputToGrabNext = firstInput;
    //             // std::cout << std::format("output: {}, outputToGrabNext: {}\n", output, outputToGrabNext);

    //             // iteration++;
    //             // if (iteration = 5) break;

    //             // reset variables

    //             break;
    //             // continue;
    //         }
    //         firstInput = operation = secondInput = arrow = output = "";

    //     }
    // }
}