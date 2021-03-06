/*
 * Copyright (c) 2020 Andr�s Gav�n
 * Copyright (c) 2020 Rub�n Rodr�guez
 *
 * This file is part of Out Run.
 * Out Run is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Out Run is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Out Run.  If not, see <https://www.gnu.org/licenses/>.
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
 * Module Score interface file
 */

#pragma once

#ifndef SCORE_H
#define SCORE_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Configuration.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;



/**
 * It represents a score record, with the player's name and time stamp.
 */
struct Score {

    // Score obtained by the player
    unsigned long score;

    // Name of the player
    std::string name;

    // Minutes that the game has lasted
    int minutes;

    // Seconds that the game has lasted
    int secs;

    // Hundredths of seconds that the game has lasted
    int cents_second;



    /**
     * Create a record of a player which is going to be stored
     * @param score is the score obtained by the player during the game mode
     * @param name is the nickname introduced by the player to save the record
     * @param minutes is the quantity of minutes that the game has lasted
     * @param secs is the quantity of seconds that the game has lasted
     * @param centsSecond is the quantity of hundredths of second that the game has lasted
     */
    Score(unsigned long score, const std::string &name, int minutes, int secs, int centsSecond);

};



/**
 * Returns all score records in order from highest to lowest score, i.e. the best record will be in
 * The size of the vector is between zero (no records) and seven (there are seven records in the
 * positions zero to six)
 * @param c is the module configuration of the game
 * @return
 */
std::vector<Score> getGlobalScores(Configuration& c);



/**
 * Given all records in order from highest to lowest score and a score, return the
 * position of the new record (0 to 6) or -1 if not a new record
 * @param globalScores is a vector which stores all the records of the game mode
 * @param score is the score which is going to be test to check if it's a new record or not
 * @return
 */
int isNewRecord(const std::vector<Score> &globalScores, unsigned long score);



/**
 * Given all the records of punctuation ordered from highest to lowest punctuation and a new record, add the new record
 * of score and returns true if it has been stored successfully and false if not.
 * @param globalScores is a vector which stores all the records of the game mode
 * @param newRecord is the new record of the game mode which is going to be stored
 * @param c is the module configuration of the game
 * @return
 */
bool saveNewRecord(const std::vector<Score> &globalScores, const Score &newRecord, Configuration & c);


#endif //SCORE_H
