//
// Created by Trystan May on 5/15/17.
//

#include <iostream>
#include <fstream>
#include "passwords.h"

template<typename Element>
Element randomElement(const std::vector<Element> &elements, std::default_random_engine &randomEngine) {
    return elements.at(randomEngine() % elements.size());
}

void addLetterToPassword(const std::string &word, int index, std::string &password,
                         const std::vector<char> &alphabet, std::default_random_engine &randomEngine) {
    if ((bool) word[index]) {
        password += word[index];
    } else {
        password += randomElement(alphabet, randomEngine);
    }
}

void addCharacters(std::string &str,
                   std::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>::iterator pos,
                   char &character) {
    str.insert(pos, character);
}

std::string synthesizePassword(const std::string &punctuation, const std::string &numbers, const std::string &alphabet,
                               const std::map<char, char> &replacements, std::default_random_engine &randomEngine,
                               const std::vector<char> &substitutes, const std::vector<std::string> &dictionary,
                               bool haveUserInput) {
    std::string word1, word2;
    if (haveUserInput) {
        std::cout << "Please input two keywords.\n";
        std::cin >> word1 >> word2;
    } else {
        word1 = dictionary[randomEngine() % dictionary.size()];
        word2 = dictionary[randomEngine() % dictionary.size()];
    }
    toLower(word1);
    toLower(word2);

    std::string password;
    for (int i = 0; i < std::max(word1.length(), word2.length()); i++) {
        addLetterToPassword(word1, i, password, substitutes, randomEngine);
        addLetterToPassword(word2, i, password, substitutes, randomEngine);
    }

    capitalizeRandomLetter(password, randomEngine);

    replaceWords(password, replacements, randomEngine);

    addCharacters(password, password.begin(), (char &) punctuation[randomEngine() % punctuation.size()]);
    addCharacters(password, password.begin(), (char &) numbers[randomEngine() % numbers.size()]);

    addCharacters(password, password.end(), (char &) punctuation[randomEngine() % punctuation.size()]);
    addCharacters(password, password.end(), (char &) numbers[randomEngine() % numbers.size()]);

    addCharacters(password, password.length() / 2 + password.begin(),
                  (char &) alphabet[randomEngine() % alphabet.size()]);
    addCharacters(password, password.length() / 2 + password.begin(),
                  (char &) alphabet[randomEngine() % alphabet.size()]);

    return password;
}

std::string
lengthSubstitutePassword(const std::string &punctuation, const std::string &numbers, const std::string &alphabet,
                         const std::map<char, char> &replacements, std::default_random_engine &randomEngine,
                         const std::vector<std::string> &dictionary, bool haveUserInput) {
    int length;
    std::string word;
    if (haveUserInput) {
        std::cout << "Provide a desired length for the password." << std::endl;
        std::cin >> length;

        std::cout << "Input a word to be used as a base." << std::endl;
        std::cin >> word;
    } else {
        length = randomEngine() % 8 + 8;

        word = dictionary[randomEngine() % dictionary.size()];
    }
    toLower(word);

    if (word.length() > length) {
        while (word.length() != length) {
            word.pop_back();
        }
    } else if (word.length() < length) {
        int counter = 0;
        for (auto i = word.begin(); word.length() != length; i++, counter++) {
            if (i >= word.end()) {
                i = word.begin();
            }
            if (randomEngine() % 5 >= 3) {
                addCharacters(word, i, (char &) alphabet[randomEngine() % alphabet.size()]);
            } else if ((counter) % 3 == 0) {
                addCharacters(word, word.begin(), (char &) alphabet[randomEngine() % alphabet.size()]);
            } else if (counter % 3 == 1) {
                addCharacters(word, word.end(), (char &) alphabet[randomEngine() % alphabet.size()]);
            } else {
                addCharacters(word, word.length() / 2 + word.begin(),
                              (char &) alphabet[randomEngine() % alphabet.size()]);
            }
        }
    }

    capitalizeRandomLetter(word, randomEngine);

    replaceWords(word, replacements, randomEngine);

    return word;

}

void capitalizeRandomLetter(std::string &word, std::default_random_engine &randomEngine) {
    int randIndex;
    do {
        randIndex = (int) (randomEngine() % word.size());
    } while (isalpha(word[randIndex]) == 0);

    word[randIndex] = (char) toupper(word[randIndex]);
}

void replaceWords(std::string &word, const std::map<char, char> &replacements,
                  std::default_random_engine &randomEngine) {
    for (char &c : word) {
        if (replacements.find(c) != replacements.end()) {
            if (randomEngine() % 2 == 1) {
                c = replacements.at(c);
            }
        }
    }
}

std::vector<char> strToCharacterVector(const std::string &str) {
    std::vector<char> out(str.length() + 1);

    std::copy(str.c_str(), str.c_str() + str.length() + 1, out.begin());

    return out;
}

void toLower(std::string &str) {
    for (char &c : str) {
        c = (char) tolower(c);
    }
}

void
makePassword(const std::vector<std::string> &dictionary, bool haveUserInput, std::default_random_engine &randomEngine) {


    std::string punctuation = "_-+=.,!@#$%^&*";
    std::string numbers = "0123456789";
    std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" + numbers + punctuation;

    std::vector<char> substitutes = strToCharacterVector(alphabet);

    std::map<char, char> replacements;

    replacements['e'] = '3';
    replacements['s'] = '$';
    replacements['o'] = '0';
    replacements['l'] = '1';
    replacements['i'] = '!';
    replacements['a'] = '@';

    std::string password;

    std::vector<std::string> generators;
    generators.emplace_back("Synthesis");
    generators.emplace_back("Length Substitute");

    int passwordGenerator;
    if (haveUserInput) {
        std::cout << "Choose a password generator by its number: " << std::endl;
        for (int i = 0; i < generators.size(); i++) {
            std::cout << i + 1 << " " << generators[i] << "\n";
        }
        std::cin >> passwordGenerator;
    } else {
        passwordGenerator = (int) (randomEngine() % generators.size());
    }

    if (passwordGenerator == 1) {
        password = synthesizePassword(punctuation, numbers, alphabet, replacements, randomEngine, substitutes,
                                      dictionary, haveUserInput);
    } else if (passwordGenerator == 2) {
        password = lengthSubstitutePassword(punctuation, numbers, alphabet, replacements, randomEngine, dictionary,
                                            haveUserInput);
    }

    if (haveUserInput)
        std::cout << password << std::endl;

    std::ofstream passwords("passwords.txt", std::ios::app);
    if (password != "")
        passwords << password << "\n";

    passwords.close();
}

