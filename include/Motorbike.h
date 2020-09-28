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
 * Module Motorbike interface file
 */

#pragma once

#ifndef MOTORBIKE_H
#define MOTORBIKE_H

#include "Vehicle.h"
#include "../include/Randomizer.h"
#include <cmath>

using namespace std;
using namespace sf;



/*
 * Properties of the motorbike
 */
namespace Motorbike_vehicle {
    // Inertia force of the motorbike when it is on curves
    const int FORCE_INERTIA = 8;
    // Number of textures of the motorbike
    const int PLAYER_TEXTURES = 88;
}



/**
 * Represents a motorbike as an available vehicle to be
 * chosen by the player in the vehicle selection menu
 */
class Motorbike : public Vehicle {

    // Factor to multiply the speed of the motorbike
    float speedMul;

    // Maximum acceleration reached by the motorbike
    float maxAcc;

    // Acceleration increment of the motorbike
    float accInc;

    // Scaling factor of the motorbike in axis y
    float scaleY;

    // Current acceleration of the motorbike
    float acceleration;

    // Minimum acceleration reached when the motorbike crashes
    float minCrashAcc;

    // Coordinate in axis x that the motorbike must reach when it crashes
    float xDest;

    // Magnitude of the inertia force that the motorbike experiments in the curves
    int inertia;

    // Sprite to draw the texture of the motorbike in the screen
    sf::Sprite sprite;

    // Control if the motorbike is crashing or not
    bool crashing;

    // Control if the motorbike generates smoke when it is moving
    bool smoking;

    // Control if the motorbike is skidding when it is in a curve
    bool skidding;

    // Control if the motorbike has crashed now
    bool crashNow;

     // Name of the motorbike's brand
    string brand;

    // Brand of the motorbike's motor
    string motor;

    // Angle of turn of the motorbike
    float angleTurning;

    // Maximum speed reached by the motorbike
    float topSpeed;

    // Control if the motorbike is inside the road or not
    bool outSideRoad;

    // Speed of the motorbike at the moment of a collision
    float speedCollision;

    // Control if the motorbike has crashed more than one time
    bool firstCrash;

    // Control if the last direction of the motorbike was turning left
    bool firstTurnLeft;

    // Control if the last direction of the motorbike was turning right
    bool firstTurnRight;

public:



    /**
     * Default constructor
     */
    Motorbike();



    /**
     * Initialize the motorbike chosen by the player
     * @param maxSpeed is the maximum speed that the motorbike can reach
     * @param speedMul is factor number that when it is multiplied by speed obtains the real speed
     * @param accInc is the acceleration increment
     * @param scaleX is the scaling factor in the axis x
     * @param scaleY is the scaling factor in the axis y
     * @param maxCounterToChange lets to update the sprite of the motorbike that is drawn in the screen
     * @param vehicle is the type of vehicle selected by the player
     * @param pX is the position of the player in the axis x
     * @param pY is the position of the player in the axis y
     */
    Motorbike(float maxSpeed, float speedMul, float accInc, float scaleX, float scaleY, int maxCounterToChange,
           const std::string &vehicle, float pX, float pY, const string brandName, const float angle,
           const string motorName);



    /**
     * Returns the last position of the motorbike in axis y
     * @return
     */
    float getPreviousY() const;



    /**
     * Updates the crash logic of the motorbike and restores speed and acceleration
     * @param vehicleCrash true if it is a crash between vehicles
     */
    void hitControl(bool vehicleCrash);



    /**
     * Returns true if the motorbike is crashing. Otherwise returns false
     * @return
     */
    bool isCrashing() const;



    /**
     * Returns the real speed of the motorbike
     * @return
     */
    float getRealSpeed() const;



    /**
     * Updates the logic of the motorbike's acceleration and braking
     * @param c is the module configuration of the game
     * @param hasGotOut indicates if it's gone off track
     * @return
     */
    Action accelerationControl(Configuration &c, bool hasGotOut);



    /**
     * Updates the logic direction turn of the motorbike
     * @param c is the module configuration of the game
     * @param curveCoefficient is the coefficient curve
     * @param isFinalMap controls if the motorbike is circulating in the goal landscape or not
     * @param limitMap is the size of the landscape
     * @return
     */
    Direction rotationControl(Configuration &c, float curveCoefficient, const bool& isFinalMap, const int& limitMap);



    /**
     * Updates the motorbike's sprite and draws it in the screen
     * @param c is the module configuration of the game
     * @param r is the sound player module of the game
     * @param a is the action to be done by the motorbike
     * @param d is the direction to be followed by the motorbike
     * @param e is the current elevation of the motorbike in the landscape
     * @param enableSound indicates if the motor of the motorbike has to make noise
     */
    void draw(Configuration &c, SoundPlayer &r, const Action &a, const Direction &d, const Elevation &e, int terrain, bool enableSound = true);



    /**
     * It forces the motorbike to be smoking or not
     * @param smoke indicates if the motorbike has to make smoke or not
     */
    void setSmoking(bool smoke);



    /**
     * Set the speed of the vehicle to zero
     */
    void setSpeed();



    /**
     * Initialize the properties of the devastator depending of the game mode
     * selected by the player
     * @param typeOfGame is the game mode selected by the player
     * @param onMultiplayer control if the game is in multi player mode or not
     * @param codePlayerInGroup is the identifier code of the player in the multi player group
     * @param numRivals is the number of rivals in the multi player mode
     */
    void setVehicle(const int typeOfGame, const bool onMultiplayer, const int codePlayerInGroup, const int numRivals);



    /**
     * Returns the half speed that can be reached by the motorbike
     * @return
     */
    float getHalfMaxSpeed();



    /**
     * Returns the brand name of the motorbike
     * @return
     */
    string getBrandName();



    /**
     * Returns the angle of turning of the motorbike
     * @return
     */
    float getAngle();



    /**
     * Returns the motor's name of the motorbike
     * @return
     */
    string getMotorName();



    /**
     * Returns the maximum speed reached by the motorbike
     * @return
     */
    float getTopSpeed();



    /**
     * Returns the current code of the sprite of the vehicle to draw
     * @return
     */
    int getCurrentCodeImage() const;

};


#endif // MOTORBIKE_H
