
/*
 * Module Step implementation file
 */

#include "../include/Word.h"


/**
 * Construct a word that compose a description
 * @param _word is the word to be stored
 * @param _numLetters is the number of letters of the word
 */
Word::Word(const string _word, const int _numLetters){
    word = _word;
    numLetters = _numLetters;
}
