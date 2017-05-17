#include <fstream>
#include <vector>
#include <iostream>
#include "passwords.h"

int main(int argc, char *argv[]) {

    std::vector<std::string> dictionary;
    std::string word;

    std::default_random_engine randomEngine;
    randomEngine.seed((unsigned int) time(nullptr));

    std::ifstream dictionaryFile("../dict.txt");

    if (!dictionaryFile.is_open()) {
        std::cerr << "Can't open dictionary!";
        return -1;
    }


    while (std::getline(dictionaryFile, word)) {
        dictionary.push_back(word);
    }

    bool doUserInput = argc == 1;

    if (!doUserInput) {
        for (auto i = 0; i < dictionary.size(); i++) {
            makePassword(dictionary, doUserInput, randomEngine);
        }
    } else {
        makePassword(dictionary, doUserInput, randomEngine);
    }

    return 0;
}



