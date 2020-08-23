
/*
 * Module MultiplayerData interface file
 */


#ifndef MULTIPLAYER_DATA_H
#define MULTIPLAYER_DATA_H


#include <iostream>
#include <cstring>


using namespace std;



/**
 * Represents the information of a player in the multi player mode
 */
class MultiplayerData {

    // Identifier of a player in the group
    int codePlayer;

    // Nickname of the player in the group
    string nickName;

public:

    /**
     * Create a multiplayer data structure of the new
     * player to be joined to the group
     * @param idPlayer is the numeric code to identify a player in a group
     * @param namePlayer is the nickname of a player in the multi player mode
     */
     MultiplayerData(const int idPlayer, const string namePlayer);



     /**
      * Returns the numeric code identifier of a player in a group
      * @return
      */
     int getCodePlayer();



    /**
      * Returns the nickname of a player in a group
      * @return
      */
     string getNickNamePlayer();

};

#endif // MULTIPLAYER_DATA_H
