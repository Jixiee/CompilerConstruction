//Write a program to count the number of tokens from an input file
#include <cstdio>
#include <cctype>
#include <iostream>
bool isToken(char c) {
    return !std::isspace(c); 
}
int main() {
    FILE* file = std::fopen("input.txt", "r"); 
    if (!file) {
        std::perror("Error opening file");
        return 1;
    }
    int c;
    int tokenCount = 0;
    while ((c = std::fgetc(file)) != EOF) {
        if (isToken(c)) {
            tokenCount++;
            while ((c = std::fgetc(file)) != EOF && isToken(c)) {
            }
            std::ungetc(c, file);
        }
    }
    std::fclose(file);
    std::cout << "Number of tokens: " << tokenCount << std::endl;
    return 0;
}
