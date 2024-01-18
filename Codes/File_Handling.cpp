//Write a program to write a file character by character and append the contents of input file into the output file
#include <iostream>
#include <fstream>

int main() {
    std::fstream inputFile("input.txt", std::ios::in);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open the input file." << std::endl;
        return 1;
    }
    std::fstream outputFile("output.txt", std::ios::out);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open the output file." << std::endl;
        return 1;
    }
    char character;
    while (inputFile.get(character)) {
        outputFile.put(character);
        std::cout << character;
    }
    inputFile.close();
    outputFile.close();

    return 0;
}
