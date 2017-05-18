//
// Created by Trystan May on 5/15/17.
//

#ifndef PASSWORD_GENERATOR_PASSWORDS_H
#define PASSWORD_GENERATOR_PASSWORDS_H

#include <vector>
#include <string>
#include <random>
#include <map>

template<typename Element>
Element randomElement(const std::vector<Element> &elements, std::default_random_engine &randomEngine);

void addLetterToPassword(const std::string &word, int index, std::string &password,
                         const std::vector<char> &alphabet, std::default_random_engine &randomEngine);

void addCharacters(std::string &str,
                   std::string::iterator pos,
                   char &character);

std::string synthesizePassword(const std::string &punctuation, const std::string &numbers, const std::string &alphabet,
                               const std::map<char, char> &replacements, std::default_random_engine &randomEngine,
                               const std::vector<char> &substitutes, std::string &word1, std::string &word2);

std::string
lengthSubstitutePassword(const std::string &punctuation, const std::string &numbers, const std::string &alphabet,
                         const std::map<char, char> &replacements, std::default_random_engine &randomEngine,
                         int length, std::string &word);

void capitalizeRandomLetter(std::string &word, std::default_random_engine &randomEngine);

void
replaceWords(std::string &word, const std::map<char, char> &replacements, std::default_random_engine &randomEngine);

std::vector<char> strToCharacterVector(const std::string &str);

void toLower(std::string &str);

void
makePassword(const std::vector<std::string> &dictionary, bool haveUserInput, std::default_random_engine &randomEngine,
             const std::string &punctuation, const std::string &numbers, const std::string &alphabet,
             const std::vector<char> &substitutes, const std::map<char, char> &replacements);

#endif //PASSWORD_GENERATOR_PASSWORDS_H
