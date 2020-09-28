/*
 * Copyright (c) 2020 Andrés Gavín
 * Copyright (c) 2020 Rubén Rodríguez
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
 * Module Score implementation file
 */

#include "../include/Score.h"



/**
 * Create a record of a player which is going to be stored
 * @param score is the score obtained by the player during the game mode
 * @param name is the nickname introduced by the player to save the record
 * @param minutes is the quantity of minutes that the game has lasted
 * @param secs is the quantity of seconds that the game has lasted
 * @param centsSecond is the quantity of hundredths of second that the game has lasted
 */
Score::Score(unsigned long score, const string &name, int minutes, int secs, int centsSecond) : score(score),
                                                                                                name(name),
                                                                                                minutes(minutes),
                                                                                                secs(secs),
                                                                                                cents_second(
                                                                                                centsSecond) {}



/**
 * Returns all score records in order from highest to lowest score, i.e. the best record will be in
 * The size of the vector is between zero (no records) and seven (there are seven records in the
 * positions zero to six)
 * @param c is the module configuration of the game
 * @param typeOfGame is the game mode selected by the player
 * @return
 */
vector<Score> getGlobalScores(Configuration& c) {

    // Vector that will store the scores of the game mode
    vector<Score> globalScores;

    // xml file which stores the player with the highest score in the level
    string path = "Data/Records/OutRun/Scores_";

    // Control the difficulty of the game
    switch (c.level){
        case EASY:
            path += "Easy.xml";
            break;
        case NORMAL:
            path += "Normal.xml";
            break;
        case HARD:
            path += "Hard.xml";
    }

    // Open the xml file of the scenario
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node()->first_node();

    // Local variables to store the information of the players
    unsigned long score;
    string name;
    int minutes, secs, cents_second;

    // Iterate to get the information of the best players of the game mode
    for (xml_node<> *players = menuNode->first_node(); players; players = players->next_sibling()){
        // Get the information of each player
        for (xml_node<> *property = players->first_node(); property; property = property->next_sibling()){
            // Get the score of the player
            if ((string)property->name() == "Score"){
                // Get the background image of the menu
                score = stoul(property->value(), nullptr, 0);
            }
            // Get the name of the player
            else if ((string)property->name() == "Name"){
                // Get the background image of the menu
                name = (string)property->value();
            }
            // Get the minutes of the time of the player
            else if ((string)property->name() == "Minutes"){
                // Get the background image of the menu
                minutes = stoi(property->value());
            }
            // Get the seconds of the time of the player
            else if ((string)property->name() == "Seconds"){
                // Get the background image of the menu
                secs = stoi(property->value());
            }
            // Get the hundredths of second of the time of the player
            else if ((string)property->name() == "HundredthsOfSecond"){
                // Get the background image of the menu
                cents_second = stoi(property->value());

                // Add the score read from the xml file
                globalScores.emplace_back(score, name, minutes, secs, cents_second);
            }
        }
    }

    return globalScores;
}



/**
 * Given all records in order from highest to lowest score and a score, return the
 * position of the new record (0 to 6) or -1 if not a new record
 * @param globalScores is a vector which stores all the records of the game mode
 * @param score is the score which is going to be test to check if it's a new record or not
 * @return
 */
int isNewRecord(const vector<Score> &globalScores, unsigned long score) {
    // Index of the current record to be check
    int i = 0;
    // Iterate all the records until its position in the ranking is found
    for (; i < (int)globalScores.size() && i < 7; i++) {
        // If the position of the new record has been found
        if (globalScores[i].score < score)
            // Get the position
            return i;
    }
    // If the score is located in the last position of the ranking
    if (globalScores.size() < 7)
        // Get the position
        return i;

    // The new score is not between the best scores of the game mode
    return -1;
}



/**
 * Given all the records of punctuation ordered from highest to lowest punctuation and a new record, add the new record
 * of score and returns true if it has been stored successfully and false if not.
 * @param globalScores is a vector which stores all the records of the game mode
 * @param newRecord is the new record of the game mode which is going to be stored
 * @param c is the module configuration of the game
 * @return
 */
bool saveNewRecord(const vector<Score> &globalScores, const Score &newRecord, Configuration & c) {

    // xml file which stores the player with the highest score in the level
    string path = "Data/Records/OutRun/Scores_";

    // Control the difficulty of the game to store the record
    switch (c.level){
        case EASY:
            path += "Easy.xml";
            break;
        case NORMAL:
            path += "Normal.xml";
            break;
        case HARD:
            path += "Hard.xml";
    }

    // Writing flow to write the information
    ofstream theFile (path);
    xml_document<> doc;

    // Add the headers to the file
    xml_node<>* decl = doc.allocate_node(node_declaration);
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "UTF-8"));
    doc.append_node(decl);

     // Create the node record
    string nameNode = "RecordsOutRun";

    // Add the main node of the xml file
    xml_node<>* root = doc.allocate_node(node_element, nameNode.c_str());
    doc.append_node(root);

     // Create the node of the players
    xml_node<>* players = doc.allocate_node(node_element, "Players");
    root->append_node(players);

    // Control the position where the player must be stored in the ranking
    bool foundPosition = false;

    // Number of players checked
    int numPlayers = 0;

    // Tags in order to identify the players
    string tags[7] = {"P1", "P2", "P3", "P4", "P5", "P6", "P7"};

    // While the position has not been found
    while (!foundPosition){
        // Check the actual player
        if (globalScores[numPlayers].score >= newRecord.score){

            // The actual player goes first
            xml_node<>* player = doc.allocate_node(node_element, tags[numPlayers].c_str());
            players->append_node(player);

            // Create the score node
            xml_node<>* score = doc.allocate_node(node_element, "Score");
            player->append_node(score);
            score->value(to_string(globalScores[numPlayers].score).c_str());

            // Create the name node
            xml_node<>* name = doc.allocate_node(node_element, "Name");
            player->append_node(name);
            name->value(globalScores[numPlayers].name.c_str());

            // Create the minutes node
            xml_node<>* minutes = doc.allocate_node(node_element, "Minutes");
            player->append_node(minutes);
            minutes->value(to_string(globalScores[numPlayers].minutes).c_str());

            // Create the seconds node
            xml_node<>* seconds = doc.allocate_node(node_element, "Seconds");
            player->append_node(seconds);
            seconds->value(to_string(globalScores[numPlayers].secs).c_str());

            // Create the Hundredths of second node
            xml_node<>* hundredthsOfSecond = doc.allocate_node(node_element, "HundredthsOfSecond");
            player->append_node(hundredthsOfSecond);
            hundredthsOfSecond->value(to_string(globalScores[numPlayers].cents_second).c_str());

            // Increment the number of players processed
            numPlayers++;
        }
        else {
            foundPosition = true;
        }
    }

    // Add the new record
    string idNode = "P" + to_string(numPlayers + 1);

    // The actual player goes first
    xml_node<>* player = doc.allocate_node(node_element, idNode.c_str());
    players->append_node(player);

    // Create the score node
    xml_node<>* score = doc.allocate_node(node_element, "Score");
    player->append_node(score);
    score->value(to_string(newRecord.score).c_str());

    // Create the name node
    xml_node<>* name = doc.allocate_node(node_element, "Name");
    player->append_node(name);
    name->value(newRecord.name.c_str());

    // Create the minutes node
    xml_node<>* minutes = doc.allocate_node(node_element, "Minutes");
    player->append_node(minutes);
    minutes->value(to_string(newRecord.minutes).c_str());

    // Create the seconds node
    xml_node<>* seconds = doc.allocate_node(node_element, "Seconds");
    player->append_node(seconds);
    seconds->value(to_string(newRecord.secs).c_str());

    // Create the Hundredths of second node
    xml_node<>* hundredthsOfSecond = doc.allocate_node(node_element, "HundredthsOfSecond");
    player->append_node(hundredthsOfSecond);
    hundredthsOfSecond->value(to_string(newRecord.cents_second).c_str());

    numPlayers++;

    // While the position has not been found
    for (int j = numPlayers; j < 7; j++){

        // The actual player goes first
        xml_node<>* lastPlayer = doc.allocate_node(node_element, tags[j].c_str());
        players->append_node(lastPlayer);

        // Create the score node
        xml_node<>* lastScore = doc.allocate_node(node_element, "Score");
        lastPlayer->append_node(lastScore);
        lastScore->value(to_string(globalScores[j - 1].score).c_str());

        // Create the name node
        xml_node<>* lastName = doc.allocate_node(node_element, "Name");
        lastPlayer->append_node(lastName);
        lastName->value(globalScores[j - 1].name.c_str());

        // Create the minutes node
        xml_node<>* lastMinutes = doc.allocate_node(node_element, "Minutes");
        lastPlayer->append_node(lastMinutes);
        lastMinutes->value(to_string(globalScores[j - 1].minutes).c_str());

        // Create the seconds node
        xml_node<>* lastSeconds = doc.allocate_node(node_element, "Seconds");
        lastPlayer->append_node(lastSeconds);
        lastSeconds->value(to_string(globalScores[j - 1].secs).c_str());

        // Create the Hundredths of second node
        xml_node<>* lastHundredthsOfSecond = doc.allocate_node(node_element, "HundredthsOfSecond");
        lastPlayer->append_node(lastHundredthsOfSecond);
        lastHundredthsOfSecond->value(to_string(globalScores[j - 1].cents_second).c_str());
    }

    // Store the new xml file configuration
    theFile << doc;
    theFile.close();
    doc.clear();

    // The record has been stored successfully
    return true;
}
