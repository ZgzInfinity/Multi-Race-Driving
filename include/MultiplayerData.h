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
struct MultiplayerData {

    // Identifier of a player in the group
    int codePlayer;

    // Nickname of the player in the group
    string nickName;

    // Vehicle type of the player
    int vehicle;

    // Color type selected by the player
    int color;



    /**
     * Create a multiplayer data structure of the new
     * player to be joined to the group
     * @param idPlayer is the numeric code to identify a player in a group
     * @param namePlayer is the nickname of a player in the multi player mode
     */
     MultiplayerData(const int idPlayer, const string namePlayer);



    /**
     * Sets the identifier code of the player
     * @param positionCode is the code of the player in the group
     */
    void setCodePlayer(const int positionCode);



    /**
     * Sets the name of the player
     * @param name is the name of the player
     */
    void setNamePlayer(const string name);



     /**
     * Sets the vehicle type selected by a rival player
     * @param vehicleType is the kind of vehicle selected by the player
     */
    void setVehicleType(const int vehicleType);



    /**
     * Sets the color of the car selected by a rival player
     * @param colorCar is the color of vehicle selected by the player
     */
    void setColorVehicle(const int colorCar);



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



     /**
      * Returns the numeric code identifier of a player in a group
      * @return
      */
     int getVehicle();



    /**
      * Returns the nickname of a player in a group
      * @return
      */
     int getColor();


};

#endif // MULTIPLAYER_DATA_H
