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
 * Module Vehicle interface file
 */

#pragma once

#ifndef VEHICLE_H
#define VEHICLE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Randomizer.h"
#include "Menu.h"
#include "Globals.h"

using namespace std;
using namespace sf;

const int COUNTER = 2;

const float INCREMENT_X = 0.033f; // x increment
const float ACCELERATION_INCREMENT = 0.01f;
const float TIME_HALF_SPEED = 16.322f;
const float MAX_SPEED = 300.0f;



/**
 * The vehicle information is composed of its speed, acceleration, x-position, set of textures of the
 * vehicle, current sprite and current action and direction.
 */
class Vehicle {

public:

    // Types of elevation of the terrain
    enum Elevation {
        UP,
        FLAT,
        DOWN
    };

    // Actions that can be made with the vehicle
    enum Action {
        NONE,
        BRAKE,
        ACCELERATE,
        CRASH,
        BOOT
    };

    // Possible directions of the vehicle
    enum Direction {
        RIGHT,
        TURNLEFT,
        TURNRIGHT
    };

protected:

    // Maximum speed reached by the vehicle in KM/H
    float maxSpeed;

    // Half speed reached by the vehicle in KM/H
    float halfMaxSpeed;

    // Scale coefficient to be drawn on the screen depending of the resolutions
    float scale;

    // Counter to change the direction path of the vehicle
    int maxCounterToChange;

    // Current speed of the vehicle in KM/H
    float speed;

    // Current position in axis x
    float posX;

    // Last position in axis x
    float previousX;

     // Current position in axis y
    float posY;

    // Last position in axis y
    float previousY;

    // Absolute position of the vehicle in the axis y
    float absPosY;

    // Minimum coefficient to draw the vehicle in the screen
    float minScreenX;

    // Maximum coefficient to draw the vehicle in the screen
    float maxScreenX;

    // Vector with the textures of the vehicle
    vector<sf::Texture> textures;

    // Numeric code of the sprite to be drawn in the screen
    int current_code_image;

    // Counter to change actual_code_image
    int counter_code_image;



public:



    /**
     * Default constructor
     */
    Vehicle();


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
    Vehicle(float maxSpeed, float scale, int maxCounterToChange, float speedVehicle, float posX, float previousX, float posY, float previousY,
            float minScreenX, float maxScreenX, const string &vehicle, int numTextures, int currentCodeImage,
            int counterCodeImage);



    /**
     * Establish the vehicle in a concrete position in the landscape
     * @param pX is the position in the axis x when the vehicle must be located
     * @param pY is the position in the axis y when the vehicle must be located
     */
    void setPosition(float pX, float pY);



    /**
     * Reinitialize all the vehicle properties depending of the game mode
     * selected by the player
     * @param typeOfGame is the game mode selected by the player
     * @param onMultiplayer control if the game is in multi player mode or not
     * @param codePlayerInGroup is the identifier code of the player in the multi player group
     * @param numRivals is the number of rivals in the multi player mode
     */
    void setVehicle(const int typeOfGame, const bool onMultiplayer, const int codePlayerInGroup, const int numRivals);



    /**
     * Set the speed of the vehicle to zero
     */
    void setSpeed();


    /**
     * Returns the current position of the vehicle in the axis x
     * @return
     */
    float getPosX() const;



    /**
     * Returns the last registered position of the vehicle in the axis x
     * @return
     */
    float getPreviousX() const;



   /**
     * Returns the current position of the vehicle in the axis y
     * @return
     */
    float getPosY() const;



    /**
     * Returns the current position of the vehicle in the axis y
     * @return
     */
    float getAbsPosY() const;



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
     * Returns the acceleration of the vehicle
     * @return
     */
    float getAcceleration() const;



    /**
     * Returns the speed of the vehicle in KM/H
     * @return
     */
    float getSpeed() const;



    /**
     * Returns the current code of the sprite of the vehicle to draw
     * @return
     */
    int getCurrentCodeImage() const;


};



/**
 * Randomly choose the direction the vehicle must go
 */
Vehicle::Direction randomDirection();


#endif // VEHICLE_H
