//Write a program to categorize the tokens in cpp
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

bool isKeyword(const string& word) {
    static const unordered_set<string> keywords = {
        "int", "double", "float", "char", "string", "if", "else", "for", "while", "do", "return", "void"
    };
    return keywords.find(word) != keywords.end();
}
bool isOperator(char c) {
    static const unordered_set<char> operators = {'+', '-', '*', '/', '=', '<', '>', '&', '|', '!', '%', '^', '~'};
    return operators.find(c) != operators.end();
}
bool isValidIdentifierChar(char c) {
    return isalnum(c) || c == '_';
}
vector<string> categorizeCodeBlock(const string& code) {
    vector<string> categorized;
    string currentToken;
    string tempCode = code; 
    for (char c : tempCode) {
        if (isspace(c)) {
            if (!currentToken.empty()) {
                categorized.push_back(currentToken);
                currentToken.clear();
            }
        } else if (isOperator(c)) {
            if (!currentToken.empty()) {
                categorized.push_back(currentToken);
                currentToken.clear();
            }
            currentToken.push_back(c);
            categorized.push_back(currentToken);
            currentToken.clear();
        } else if (isValidIdentifierChar(c)) {
            currentToken.push_back(c);
        } else if (c == '"') {
            if (!currentToken.empty()) {
                categorized.push_back(currentToken);
                currentToken.clear();
            }
            currentToken.push_back('"');
            size_t pos = tempCode.find('"', tempCode.find('"') + 1);
            if (pos != string::npos) {
                currentToken += tempCode.substr(tempCode.find('"'), pos - tempCode.find('"') + 1);
                categorized.push_back(currentToken);
                currentToken.clear();
                tempCode.erase(0, pos + 1); 
            } else {
            }
        }
    }
    if (!currentToken.empty()) {
        categorized.push_back(currentToken);
    }
    return categorized;
}
int main() {
    string codeBlock = "int main() {\n\tint a = 5;\n\tfloat b = 3.14;\n\tstring message = \"Hello, world!\";\n\tif (a > 0) {\n\t\tcout << message << endl;\n\t}\n\treturn 0;\n}";
    vector<string> categorized = categorizeCodeBlock(codeBlock);
    cout << "Identifiers:" << endl;
    for (const string& token : categorized) {
        if (!isKeyword(token) && !isOperator(token[0]) && token[0] != '"') {
            cout << token << endl;
        }
    }
    cout << "\nKeywords:" << endl;
    for (const string& token : categorized) {
        if (isKeyword(token)) {
            cout << token << endl;
        }
    }
    cout << "\nOperators:" << endl;
    for (const string& token : categorized) {
        if (isOperator(token[0])) {
            cout << token << endl;
        }
    }
    cout << "\nString Constants:" << endl;
    for (const string& token : categorized) {
        if (token[0] == '"') {
            cout << token << endl;
        }
    }
    return 0;
}


