//Write a program to remove ambiguity and left recursion from the given grammar
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
using namespace std;

class Grammar {
private:
    unordered_set<char> nonTerminals;
    unordered_set<char> terminals;
    unordered_multimap<char, string> productions;
public:
    void addProduction(char nonTerminal, string production) {
        nonTerminals.insert(nonTerminal);
        stringstream ss(production);
        string token;
        while (getline(ss, token, '|')) {
            productions.insert({nonTerminal, token});
        }
    }
    void printGrammar() {
        cout << "Grammar:\n";
        for (auto nt : nonTerminals) {
            cout << nt << " -> ";
            auto range = productions.equal_range(nt);
            for (auto it = range.first; it != range.second; ++it) {
                cout << it->second << " | ";
            }
            cout << endl;
        }
    }
    bool isAmbiguous() {
        for (auto nt : nonTerminals) {
            auto range = productions.equal_range(nt);
            unordered_set<string> productionSet;
            for (auto it = range.first; it != range.second; ++it) {
                if (!productionSet.insert(it->second).second) {
                    return true;
                }
            }
        }
        return false;
    }
    void removeLeftRecursion() {
        for (auto A : nonTerminals) {
            vector<string> alpha, beta;
            auto range = productions.equal_range(A);
            for (auto it = range.first; it != range.second; ++it) {
                if (it->second[0] == A) {
                    alpha.push_back(it->second.substr(1));
                } else {
                    beta.push_back(it->second);
                }
            }
            if (!alpha.empty()) {
                char newNonTerminal = getNewNonTerminal();
                nonTerminals.insert(newNonTerminal);
                for (string b : beta) {
                    productions.insert({A, b + newNonTerminal});
                }
                productions.insert({newNonTerminal, ""});
                for (string a : alpha) {
                    productions.insert({newNonTerminal, a + newNonTerminal});
                }
                productions.insert({newNonTerminal, ""});
                productions.erase(range.first, range.second);
            }
        }
    }
private:
    char getNewNonTerminal() {
        char newNonTerminal = 'A';
        while (nonTerminals.find(newNonTerminal) != nonTerminals.end()) {
            newNonTerminal++;
        }
        return newNonTerminal;
    }
};
int main() {
    Grammar grammar;
    char nonTerminal;
    string production;
    cout << "Enter the grammar (enter 'end' to finish):\n";
    while (true) {
        cout << "Non-terminal: ";
        cin >> nonTerminal;
        if (nonTerminal == 'e') {
            break;
        }
        cout << "Production (separate alternatives with '|'): ";
        cin >> production;
        grammar.addProduction(nonTerminal, production);
    }
    cout << "\nOriginal Grammar:\n";
    grammar.printGrammar();

    if (grammar.isAmbiguous()) {
        cout << "\nAmbiguity detected in the grammar.\n";
    } else {
        cout << "\nNo ambiguity detected in the grammar.\n";
    }
    grammar.removeLeftRecursion();
    cout << "\nGrammar after removing left recursion:\n";
    grammar.printGrammar();
    return 0;
}
