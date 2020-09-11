
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
MultiplayerCar::MultiplayerCar(const int numTextures, const float scaling, const float positionX, const float positionY,
                               const int vehicleSelected, const int colorCarSelected, const string &vehicle)
{
    // Assignment of the attributes
    scale = scaling;
    posX = positionX;
    posY = positionY;
    typeOfVehicle = vehicleSelected;
    colorCar = colorCarSelected;

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
 * Establish the vehicle in a concrete position in the landscape
 * @param pX is the position in the axis x when the vehicle must be located
 * @param pY is the position in the axis y when the vehicle must be located
 */
void MultiplayerCar::setPosition(float pX, float pY){
    posX = pX;
    posY = pY;
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
 * Returns the current texture of the multi player
 * @param current_code_image is the code of the sprite to be drawn
 * @return
 */
const Texture* MultiplayerCar::getCurrentTexture(const int current_code_image) const {
    return &textures[current_code_image - 1];
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

