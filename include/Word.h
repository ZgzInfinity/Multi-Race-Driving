/*
 * Copyright (c) 2020 Rubén Rodríguez
 *
 * This file is part of Multi Race Driving.
 * Multi Race Driving is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Multi Race Driving is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Multi Race Driving.  If not, see <https://www.gnu.org/licenses/>.
 */



/*
 * ----------------------------------------------
 * Multi Race Driving: A general and customized
 * platform for 2.5D racing games
 * Author: ZgzInfinity
 * Date: 28-09-20
 * ----------------------------------------------
 */



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
