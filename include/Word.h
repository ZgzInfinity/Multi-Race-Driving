
#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <cstring>

using namespace std;

struct Word {

    // Attribute that stores the word
    string word;

    // Number of letters of the word
    int numLetters;


    Word(const string _word, const int _numLetters);

};

#endif // WORD
