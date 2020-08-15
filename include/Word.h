
/*
 * Module Step interface file
 */

#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <cstring>

using namespace std;



/**
 * Represent a word that is used in the description of the buttons
 */
struct Word {

    // Attribute that stores the word
    string word;

    // Number of letters of the word
    int numLetters;



    /**
     * Construct a word that compose a description
     * @param _word is the word to be stored
     * @param _numLetters is the number of letters of the word
     */
    Word(const string _word, const int _numLetters);

};

#endif // WORD
