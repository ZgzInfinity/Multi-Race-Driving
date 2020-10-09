
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

#include "../include/MultiplayerCar.h"



/**
 * Default constructor of the data type
 */
 MultiplayerCar::MultiplayerCar(){}



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
MultiplayerCar::MultiplayerCar(const int idPlayer, const string name, const int numTextures, const float scaling, const float positionX,
                               const float positionY, const int vehicleSelected, const int colorCarSelected, const string &vehicle)
{
    // Assignment of the attributes
    scale = scaling;
    posX = positionX;
    posY = positionY;
    typeOfVehicle = vehicleSelected;
    colorCar = colorCarSelected;
    current_code_image = 1;
    codePlayer = idPlayer;
    namePlayer = name;
    isCrashing = false;
    soundCrash = true;
    indexLandscape = 1;
    previousX = posX;
    previousY = posY;
    minScreenX = 0;
    maxScreenX = 0;

    // Load the textures of the vehicle selected
    // Reserves memory to store all the textures of the vehicle
    textures.reserve(static_cast<unsigned long>(numTextures));

    // Iterate throughout the textures of the vehicle
    for (int i = 1; i <= numTextures; i++) {
        // Load the texture and store it in the vector
        Texture t;
        t.loadFromFile(vehicle + "/Images/c" + to_string(i) + ".png");
        t.setSmooth(true);
        t.setRepeated(false);
        textures.push_back(t);
    }
}



 /**
 * Sets the identifier code of the player
 * @param positionCode is the code of the player in the group
 */
void MultiplayerCar::setCodePlayer(const int positionCode){
    codePlayer = positionCode;
}



/**
 * Sets the name of the player
 * @param name is the name of the player
 */
void MultiplayerCar::setNamePlayer(const string name){
    namePlayer = name;
}



/**
 * Establish the vehicle in a concrete position in the landscape
 * @param pX is the position in the axis x when the vehicle must be located
 * @param pY is the position in the axis y when the vehicle must be located
 */
void MultiplayerCar::setPosition(float pX, float pY){
    posX = pX;
    posY = pY;
    previousX = pX;
    previousY = pY;
}



/**
 * Establish the code of the sprite to be drawn in the screen
 * @param codeImage is the code of the sprite to be drawn in the screen of the game
 */
void MultiplayerCar::setCurrentCodeImage(float codeImage){
    current_code_image = codeImage;
}



/**
 * Establish the index of the landscape where is now the player
 * @param codeLandscape is the index of the landscape where is now the player
 */
void MultiplayerCar::setIndexLandScape(int codeLandscape){
    indexLandscape = codeLandscape;
}



/**
 * Establish the minimum coordinate in axis X occupied by the multi player car
 * @param screenX is the minimum coordinate in axis X occupied by the multi player car
 */
void MultiplayerCar::setMinScreenX(float screenX){
    minScreenX = screenX;
}



/**
 * Establish the maximum coordinate in axis X occupied by the multi player car
 * @param screenX is the maximum coordinate in axis X occupied by the multi player car
 */
void MultiplayerCar::setMaxScreenX(float screenX){
    maxScreenX = screenX;
}



/**
 * Set if the multi player is crashing or not
 */
void MultiplayerCar::setIsCrashing(bool crash){
    isCrashing = crash;
    if (!crash){
        soundCrash = true;
    }
}



/**
 * Set if the multi player sound crash has to be reproduced
 */
void MultiplayerCar::setSoundCrash(){
    soundCrash = false;
}


/**
 * Returns the current texture of the multi player
 * @param current_code_image is the code of the sprite to be drawn
 * @return
 */
const Texture* MultiplayerCar::getCurrentTexture() const {
    return &textures[current_code_image - 1];
}



/**
 * Returns the current texture of the multi player
 * @param current_code_image is the code of the sprite to be drawn
 * @return
 */
const Texture* MultiplayerCar::getCurrentTexture(const int referenceSprite, const int offsetSprite) const {
    return &textures[referenceSprite + current_code_image % offsetSprite];
}



/**
 * Returns the scaling factor of the multi player car
 * @return
 */
float MultiplayerCar::getScalingFactor() const {
    return scale;
}



/**
 * Returns the current position of the vehicle in the axis x
 * @return
 */
float MultiplayerCar::getPosX() const {
    return posX;
}



/**
 * Returns the current position of the vehicle in the axis y
 * @return
 */
float MultiplayerCar::getPosY() const {
    return posY;
}



/**
 * Returns the minimum coordinate of the screen in axis x used by the vehicle
 * @return
 */
float MultiplayerCar::getMinScreenX() const {
    return minScreenX;
}



/**
 * Returns the maximum coordinate of the screen in axis x used by the vehicle
 * @return
 */
float MultiplayerCar::getMaxScreenX() const {
    return maxScreenX;
}



/**
 * Returns the last position of the player in axis X in multi player mode
 * @return
 */
float MultiplayerCar::getPreviousX() const {
    return previousX;
}



/**
 * Returns the last position of the player in axis Y in multi player mode
 * @return
 */
float MultiplayerCar::getPreviousY() const {
    return previousY;
}



/**
 * Returns the type of vehicle selected by the player
 * @return
 */
int MultiplayerCar::getTypeVehicle() const {
    return typeOfVehicle;
}



/**
 * Returns the type of vehicle selected by the player
 * @return
 */
int MultiplayerCar::getCurrentCodeImage() const {
    return current_code_image;
}



/**
 * Returns the code of the player in the group
 */
int MultiplayerCar::getCodePlayer() const {
    return codePlayer;
}



/**
 * Get the index of the landscape where is now the player
 * @param codeLandscape is the index of the landscape where is now the player
 */
int MultiplayerCar::getIndexLandScape() const {
    return indexLandscape;
}



/**
 * Returns if the multi player is crashing or not
 */
bool MultiplayerCar::getIsCrashing() const {
    return isCrashing;
}



/**
 * Returns if the sound collision of the multi player car has to be reproduced
 */
bool MultiplayerCar::getSoundCrash() const {
    return soundCrash;
}



/**
 * Returns the name of the player in the group
 */
string MultiplayerCar::getNickNamePlayer() const {
    return namePlayer;
}



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
bool MultiplayerCar::isVisible(const Configuration &c, float minY, float playerX, float playerY, float &distanceX, float &distanceY) const {
    // Check if the rival car is visible from the position of the player's vehicle
    if (posY < minY || posY > minY + float(c.renderLen) || minScreenX < 0 || maxScreenX > c.w.getSize().y) {
        // The rival car is not visible
        return false;
    }
    else {
        // The rival car is visible and calculate the distance in both axis with it
        distanceX = abs(playerX - posX);
        distanceY = abs(playerY - posY);
        return true;
    }
}




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
bool MultiplayerCar::hasCrashed(float prevY, float currentY, float minX, float maxX, float &crashPos) const {
    // Check if the path of the rival car is approximately the same path of the player's vehicle
    if (minScreenX != maxScreenX && ((prevY <= posY + 10.f && currentY >= posY - 10.f) ||
                                     (currentY <= posY + 10.f && prevY >= posY - 10.f)) && // y matches
        ((minX >= minScreenX && minX <= maxScreenX) ||
         (maxX >= minScreenX && maxX <= maxScreenX) ||
         (minScreenX >= minX && minScreenX <= maxX) ||
         (maxScreenX >= minX && maxScreenX <= maxX)))
    { // x matches
        // There is a crash between both cars
        crashPos = posY;
        return true;
    }
    // There is no crash
    return false;
}
