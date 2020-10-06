
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
 * Module MultiplayerCar interface file
 */


#ifndef MULTIPLAYER_CAR_H
#define MULTIPLAYER_CAR_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Configuration.h"


using namespace std;
using namespace sf;


/**
 * Represents a multi player car that is going to compete in
 * the multi player mode
 */
 class MultiplayerCar {

    // Code of the player
    int codePlayer;

    // Name of the player
    string namePlayer;

    // Scale coefficient to be drawn on the screen depending of the resolutions
    float scale;

    // Current position in axis x
    float posX;

    // Current position in axis y
    float posY;

     // Last position in axis x
    float previousX;

    // Last position in axis y
    float previousY;

    // Minimum coefficient to draw the vehicle in the screen
    float minScreenX;

    // Maximum coefficient to draw the vehicle in the screen
    float maxScreenX;

    // Type of vehicle selected by the player
    int typeOfVehicle;

    // Color of the vehicle selected by the player
    int colorCar;

    // Vector with the textures of the vehicle
    vector<sf::Texture> textures;

    // Code of the sprite of the vehicle to be drawn
    int current_code_image;

    // Control if a multi player is crashing or not
    bool isCrashing;

    // Control the crash sound of the multi player car
    bool soundCrash;

    // Index of the current landscape of the vehicle car
    int indexLandscape;


public:



    /**
     * Default constructor of the data type
     */
     MultiplayerCar();



    /**
     * Constructor of the Multiplayer data type
     * @param numTextures is the number of textures of the multi player car selected
     * @param scaling is the scaling factor to draw the vehicle
     * @param positionX is the coordinate of the vehicle in the axis X
     * @param positionY is the coordinate of the vehicle in the axis Y
     * @param vehicleSelected is the type of vehicle selected by the player
     * @param colorCarSelected is the identifier color of the vehicle
     * @param vehicle is the name of the vehicle specified in text
     */
    MultiplayerCar(const int idPlayer, const string name, const int numTextures, const float scaling, const float positionX,
                   const float positionY, const int vehicleSelected, const int colorCarSelected, const string &vehicle);



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
     * Establish the vehicle in a concrete position in the landscape
     * @param pX is the position in the axis x when the vehicle must be located
     * @param pY is the position in the axis y when the vehicle must be located
     */
    void setPosition(float pX, float pY);



    /**
     * Establish the code of the sprite to be drawn in the screen
     * @param codeImage is the code of the sprite to be drawn in the screen of the game
     */
    void setCurrentCodeImage(float codeImage);



    /**
     * Establish the index of the landscape where is now the player
     * @param codeLandscape is the index of the landscape where is now the player
     */
    void setIndexLandScape(int codeLandscape);



    /**
     * Establish the minimum coordinate in axis X occupied by the multi player car
     * @param screenX is the minimum coordinate in axis X occupied by the multi player car
     */
    void setMinScreenX(float screenX);



    /**
     * Establish the maximum coordinate in axis X occupied by the multi player car
     * @param screenX is the maximum coordinate in axis X occupied by the multi player car
     */
    void setMaxScreenX(float screenX);



    /**
     * Set if the multi player is crashing or not
     */
    void setIsCrashing(bool crash);



    /**
     * Set if the multi player sound crash has to be reproduced
     */
    void setSoundCrash();



    /**
     * Returns the current texture of the multi player
     * @return
     */
    const sf::Texture *getCurrentTexture() const;



    /**
     * Returns the current texture of the multi player
     * @param current_code_image is the code of the sprite to be drawn
     * @return
     */
    const sf::Texture * getCurrentTexture(const int referenceSprite, const int offsetSprite) const;



    /**
     * Returns the scaling factor of the multi player car
     * @return
     */
    float getScalingFactor() const;



    /**
     * Returns the current position of the vehicle in the axis x
     * @return
     */
    float getPosX() const;



    /**
     * Returns the current position of the vehicle in the axis y
     * @return
     */
    float getPosY() const;



    /**
     * Returns the minimum coordinate of the screen in axis x used by the vehicle
     * @return
     */
    float getMinScreenX() const;



    /**
     * Returns the maximum coordinate of the screen in axis x used by the vehicle
     * @return
     */
    float getMaxScreenX() const;



    /**
     * Returns the last position of the player in axis X in multi player mode
     * @return
     */
    float getPreviousX() const;



    /**
     * Returns the last position of the player in axis Y in multi player mode
     * @return
     */
    float getPreviousY() const;



    /**
     * Returns the type of vehicle selected by the player
     * @return
     */
    int getTypeVehicle() const;



    /**
     * Returns the code of the vehicle sprite to be drawn
     * @return
     */
    int getCurrentCodeImage() const;



    /**
     * Returns the code of the player in the group
     */
    int getCodePlayer() const;



    /**
     * Get the index of the landscape where is now the player
     * @param codeLandscape is the index of the landscape where is now the player
     */
    int getIndexLandScape() const;



    /**
     * Returns if the multi player is crashing or not
     */
    bool getIsCrashing() const;



    /**
     * Returns if the sound collision of the multi player car has to be reproduced
     */
    bool getSoundCrash() const;



    /**
     * Returns the name of the player in the group
     */
    string getNickNamePlayer() const;



    /**
     * Returns true if the car is displayed on screen and the distance to the player, otherwise returns false.
     * @param c is the module configuration of the game
     * @param minY is the position of the camera in the axis y
     * @param playerX is the player position in the axis x
     * @param playerY is the player position in the axis y
     * @param distanceX is the distance between the rival car and the vehicle of the player in the axis x
     * @param distanceY is the distance between the rival car and the vehicle of the player in the axis y
     * @return
     */
    bool isVisible(const Configuration &c, float minY, float playerX, float playerY, float &distanceX, float &distanceY) const;



    /**
     * Returns true if there has been a collision between the multi player vehicle and the player's vehicle.
     * If true, it also returns the Y position where they have collided
     * @param currentY is the current position of the player's vehicle in the axis y
     * @param prevY is the last position of the player's vehicle in the axis y
     * @param minX is the minimum position in axis x occupied by the vehicle
     * @param maxX is the maximum position in axis y occupied by the vehicle
     * @param crashPos is the position in axis y where the crash has happened
     * @return
     */
    bool hasCrashed(float prevY, float currentY, float minX, float maxX, float &crashPos) const;



 };

 #endif // MULTIPLAYER_CAR_H
