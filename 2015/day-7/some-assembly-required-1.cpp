#include <vector>
#include <fstream>
#include <iostream>
#include <string> // std::string, std::stoi
#include <cstdint> // uint16_t
#include <utility> // std::pair
#include <sstream>
#include <algorithm> // std::count
#include <cctype> // std::isdigit
#include <stdexcept> // std::runtime_error
#include <format>

uint16_t parseInputFile(
    std::string outputToGrab, 
    std::vector<std::pair<std::string, uint16_t>>& solvedValues
) {
    
    // Read text file
    std::ifstream inputFile("some-assembly-required.txt");

    std::string line {};

    std::string firstInput, secondInput, operation, arrow, output, nextOutput {};
    uint16_t firstInputVal, secondInputVal, outputSignal {};

    /* Loop through file recursively, line by line, until all 
    gates/wires are evaluated to signals (uint16_t) */
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);

        // Extract circuit information while accounting for all 3 formats 
        if (line.starts_with("NOT")) iss >> operation >> firstInput >> arrow >> output; // e.g., 'NOT gw -> gx'
        else if (std::count(line.begin(), line.end(), ' ') == 2) iss >> firstInput >> arrow >> output; // e.g., 'lx -> a' 
        else iss >> firstInput >> operation >> secondInput >> arrow >> output; // e.g., 'lf AND lq -> ls'
        
        // std::cout << std::format(
        //     "firstInput: {}, operation: {}, "
        //     "secondInput: {}, arrow: {}, output: {}\n", 
        //     firstInput, operation, secondInput, arrow, output
        // );

        // std::cout << std::format("output: {}, outputToGrab: {}\n", output, outputToGrab);
        if (output == outputToGrab) {
            // Check if signal already found, then return cached value 
            auto it = std::find_if(solvedValues.begin(), solvedValues.end(),
                [&output](const auto& pair) { return pair.first == output; });

            if (it != solvedValues.end()) {
                // std::cout << std::format("Already solved for '{}'! Signal is {}\n", output, it->second);
                return it->second;
            }

            // Continue recursing file until firstInput is a signal (uint16_t)
            if (firstInput != "" && !std::isdigit(static_cast<unsigned char>(firstInput[0]))) {
                // std::cout << std::format("Oh! '{}' isn't a signal. Recursing...\n", firstInput);
                nextOutput = firstInput;
                firstInputVal = parseInputFile(nextOutput, solvedValues);
            } else firstInputVal = std::stoi(firstInput);
            
            // Continue recursing file until secondInput is a signal (uint16_t) or empty ("")
            if (secondInput != "" && !std::isdigit(static_cast<unsigned char>(secondInput[0]))) { 
                // std::cout << std::format("Oh! '{}' isn't a signal. Recursing...\n", secondInput);
                nextOutput = secondInput;
                secondInputVal = parseInputFile(nextOutput, solvedValues);
            } else if (secondInput != "") secondInputVal = std::stoi(secondInput);
           
            // std::cout << std::format("Yay! '{}' is a signal and '{}' is a signal or empty\n", firstInputVal, secondInputVal);

            // Calculate output signal
            if (std::count(line.begin(), line.end(), ' ') == 2) outputSignal = firstInputVal; // e.g., '16076 -> a' 
            else if (operation == "NOT") outputSignal = ~firstInputVal;
            else if (operation == "AND") outputSignal = firstInputVal & secondInputVal;
            else if (operation == "OR") outputSignal = firstInputVal | secondInputVal;
            else if (operation == "LSHIFT") outputSignal = firstInputVal << secondInputVal;
            else if (operation == "RSHIFT") outputSignal = firstInputVal >> secondInputVal;
            
            // Store evaulated gates/wires to reference for later recursions
            solvedValues.push_back({output, outputSignal});
            // std::cout << std::format("{}={} saved for reference.\n", output, outputSignal);
            // std::cout << std::format("Output of '{}' for line '{}' is '{}'.\n", output, line, outputSignal);
            return outputSignal;
        }
        firstInput = operation = secondInput = arrow = output = ""; // reset variables
    }
    throw std::runtime_error(std::format("*ERROR: Wire '{}' not found...", outputToGrab));
}

int main() {
    
    uint16_t signal {};
    std::vector<std::pair<std::string, uint16_t>> solvedValues; // e.g., { {"b", 19138}, {...}, ... }

    /* Loop through file until all dependencies are traced starting at wire 'a',
    i.e., all input gates/wires given values, and all output gates/wires evaluated */
    signal = parseInputFile("a", solvedValues);
    std::cout << std::format("A signal of {} is provided to wire 'a'.\n", signal);
}