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
    vehicle = -1;
    color = -1;
 }




/**
 * Sets the identifier code of the player
 * @param positionCode is the code of the player in the group
 */
void MultiplayerData::setCodePlayer(const int positionCode){
    codePlayer = positionCode;
}



/**
 * Sets the name of the player
 * @param name is the name of the player
 */
void MultiplayerData::setNamePlayer(const string name){
    nickName = name;
}



/**
 * Sets the vehicle type selected by a rival player
 * @param vehicleType is the kind of vehicle selected by the player
 */
void MultiplayerData::setVehicleType(const int vehicleType){
    vehicle = vehicleType;
}



/**
 * Sets the color of the car selected by a rival player
 * @param colorCar is the color of vehicle selected by the player
 */
void MultiplayerData::setColorVehicle(const int colorCar){
    color = colorCar;
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



/**
  * Returns the numeric code identifier of a player in a group
  * @return
  */
 int MultiplayerData::getVehicle(){
    return vehicle;
 }



/**
  * Returns the nickname of a player in a group
  * @return
  */
 int MultiplayerData::getColor(){
    return color;
 }
