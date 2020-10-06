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
 * Module Vehicle implementation file
 */

#include "../include/Vehicle.h"



/**
 * Default constructor
 */
Vehicle::Vehicle(){}



/**
 * Initialize a vehicle with all its properties
 * @param maxSpeed is the maximum speed reached by the vehicle in KM/H
 * @param scale is the scaling factor to draw the vehicle in the screen with different resolutions
 * @param maxCounterToChange is limit to change the direction of the vehicle
 * @param speed is the speed of the vehicle in KM/H
 * @param posX is the position of the vehicle in the axis x
 * @param posY is the position of the vehicle in the axis y
 * @param previousY is the last position of the vehicle in the axis y
 * @param minScreenX is the minimum coefficient to draw the vehicle in the screen
 * @param maxScreenX is the maximum coefficient to draw the vehicle in the screen
 * @param vehicle is the type of vehicle selected by the player in the selection vehicle menu
 * @param numTextures is the number of textures of the vehicle selected
 * @param currentCodeImage is the code of the sprite to be drawn in the screen
 * @param counterCodeImage is a counter that change the sprite to be drawn in the screen
 */
Vehicle::Vehicle(const float maxSpeed, const float scale, const int maxCounterToChange, float speedVehicle, float posX,
                 float previousX, float posY, float previousY, float minScreenX, float maxScreenX, const string &vehicle,
                 int numTextures,
                 int currentCodeImage, int counterCodeImage) : maxSpeed(maxSpeed), scale(scale),
                                                               maxCounterToChange(maxCounterToChange),
                                                               previousX(previousX), posX(posX), posY(posY),
                                                               previousY(previousY), minScreenX(minScreenX),
                                                               maxScreenX(maxScreenX),
                                                               current_code_image(currentCodeImage),
                                                               counter_code_image(counterCodeImage)
{
    // Assign the maximum speed reached by the vehicle
    speed = speedVehicle;
    // Calculation of the half sped reached
    halfMaxSpeed = maxSpeed / 2.0f;

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
void Vehicle::setPosition(float pX, float pY) {
    posX = pX;
    posY = pY;
    previousX = pX;
    previousY = pY;
}



/**
 * Reinitialize all the vehicle properties depending of the game mode
 * selected by the player
 * @param typeOfGame is the game mode selected by the player
 * @param onMultiplayer control if the game is in multi player mode or not
 * @param codePlayerInGroup is the identifier code of the player in the multi player group
 * @param numRivals is the number of rivals in the multi player mode
 */
void Vehicle::setVehicle(const int typeOfGame, const bool onMultiplayer, const int codePlayerInGroup, const int numRivals){
    // Initialize the speed of the vehicle to zero
    speed = 0.0f;
    // Check if the mode selected by the layer was World Tour or Pole Position
    if (onMultiplayer){
        if (codePlayerInGroup % 2 != 0){
            posX = -0.3f;
        }
        else {
            posX = 0.3f;
        }
        // Initialize the vehicle at the beginning of the landscape
        if (numRivals <= 2){
            posY = 0.f;
        }
        else {
            if (codePlayerInGroup <= 2){
                posY = 20.f;
            }
            else {
                posY = 0.f;
            }
        }
        absPosY = posY;
    }
    else {
        if (typeOfGame == 0 || typeOfGame == 2){
            // Camera on the left of the screen
            posX = -0.3f;
        }
        else {
            // Camera on the center of the screen
            posX = 0.f;
        }
        posY = 0.f;
        previousY = 0.f;
    }
}



/**
 * Set the speed of the vehicle to zero
 */
void Vehicle::setSpeed(){
    speed = 0.f;
}



/**
 * Returns the current position of the vehicle in the axis x
 * @return
 */
float Vehicle::getPosX() const {
    return posX;
}



/**
 * Returns the last registered position of the vehicle in the axis x
 * @return
 */
float Vehicle::getPreviousX() const {
    return previousX;
}



/**
 * Returns the current position of the vehicle in the axis y
 * @return
 */
float Vehicle::getPosY() const {
    return posY;
}



/**
 * Returns the current absolute position of the vehicle in the axis y
 * @return
 */
float Vehicle::getAbsPosY() const {
    return absPosY;
}



/**
 * Returns the minimum coordinate of the screen in axis x used by the vehicle
 * @return
 */
float Vehicle::getMinScreenX() const {
    return minScreenX;
}



/**
 * Returns the maximum coordinate of the screen in axis x used by the vehicle
 * @return
 */
float Vehicle::getMaxScreenX() const {
    return maxScreenX;
}



/**
 * Returns the acceleration of the vehicle
 * @return
 */
float Vehicle::getAcceleration() const {
    return speed * speed;
}



/**
 * Returns the speed of the vehicle in KM/H
 * @return
 */
float Vehicle::getSpeed() const {
    return speed;
}



/**
 * Returns the current code of the sprite of the vehicle to draw
 * @return
 */
int Vehicle::getCurrentCodeImage() const {
    return current_code_image;
}



/**
 * Randomly choose the direction the vehicle must go
 */
Vehicle::Direction randomDirection() {
    // Get a probabilistic number between zero and one
    const float p = rand_generator_zero_one();
    // Check the value of the number obtained
    if (p < 0.6f){
        // Straight direction
        return Vehicle::Direction::RIGHT;
    }
    else if (p < 0.8f){
        // Turn right
        return Vehicle::Direction::TURNRIGHT;
    }
    else {
        // Turn left
        return Vehicle::Direction::TURNLEFT;
    }
}

