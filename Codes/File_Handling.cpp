/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <fstream>

int main() {
    // Open the input file
    std::fstream inputFile("input.txt", std::ios::in);

    // Check if the input file is open
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open the input file." << std::endl;
        return 1;
    }

    // Open the output file
    std::fstream outputFile("output.txt", std::ios::out);

    // Check if the output file is open
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open the output file." << std::endl;
        return 1;
    }

    // Read and write each character in the input file
    char character;
    while (inputFile.get(character)) {
        // Write the character to the output file
        outputFile.put(character);

        // Print the character to the console
        std::cout << character;
    }

    // Close both files
    inputFile.close();
    outputFile.close();

    return 0;
}
