
/*
 * Module MultiplayerData implementation file
 */


#include "../include/MultiplayerData.h"



/**
 * Create a multiplayer data structure of the new
 * player to be joined to the group
 * @param idPlayer is the numeric code to identify a player in a group
 * @param namePlayer is the nickname of a player in the multi player mode
 */
 MultiplayerData::MultiplayerData(const int idPlayer, const string namePlayer){
    codePlayer = idPlayer;
    nickName = namePlayer;
 }



 /**
  * Returns the numeric code identifier of a player in a group
  * @return
  */
 int MultiplayerData::getCodePlayer(){
    return codePlayer;
 }



/**
  * Returns the nickname of a player in a group
  * @return
  */
 string MultiplayerData::getNickNamePlayer(){
    return nickName;
 }
