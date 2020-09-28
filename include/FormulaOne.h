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
 * Module FormulaOne interface file
 */

#pragma once

#ifndef FORMULA_ONE_H
#define FORMULA_ONE_H

#include "Vehicle.h"
#include "../include/Randomizer.h"
#include <cmath>

using namespace std;
using namespace sf;



/*
 * Properties of the formula one
 */
namespace FormulaOne_vehicle {
    // Inertia force of the formula one when it is on curves
    const int FORCE_INERTIA = 8;
    // Number of textures of the formula one
    const int PLAYER_TEXTURES = 86;
}



/**
 * Represents a formula one as an available vehicle to be
 * chosen by the player in the vehicle selection menu
 */
class FormulaOne : public Vehicle {

    // Factor to multiply the speed of the formula one
    float speedMul;

    // Maximum acceleration reached by the formula one
    float maxAcc;

    // Acceleration increment of the formula one
    float accInc;

    // Scaling factor of the formula one in axis y
    float scaleY;

    // Current acceleration of the formula one
    float acceleration;

    // Minimum acceleration reached when the formula one crashes
    float minCrashAcc;

    // Coordinate in axis x that the formula one must reach when it crashes
    float xDest;

    // Magnitude of the inertia force that the formula one experiments in the curves
    int inertia;

    // Sprite to draw the texture of the formula one in the screen
    sf::Sprite sprite;

    // Control if the formula one is crashing or not
    bool crashing;

    // Control if the formula one generates smoke when it is moving
    bool smoking;

    // Control if the formula one is skidding when it is in a curve
    bool skidding;

    // Control if the formula one has crashed now
    bool crashNow;

     // Name of the formula one's brand
    string brand;

    // Brand of the formula one's motor
    string motor;

    // Angle of turn of the formula one
    float angleTurning;

    // Maximum speed reached by the formula one
    float topSpeed;

    // Control if the formula one is inside the road or not
    bool outSideRoad;

    // Speed of the formula one at the moment of a collision
    float speedCollision;

    // Control if the formula one has crashed more than one time
    bool firstCrash;

    // Control if the last direction of the formula one was turning left
    bool firstTurnLeft;

    // Control if the last direction of the formula one was turning right
    bool firstTurnRight;

public:



    /**
     * Default constructor
     */
    FormulaOne();



    /**
     * Initialize the formula one chosen by the player
     * @param maxSpeed is the maximum speed that the formula one can reach
     * @param speedMul is factor number that when it is multiplied by speed obtains the real speed
     * @param accInc is the acceleration increment
     * @param scaleX is the scaling factor in the axis x
     * @param scaleY is the scaling factor in the axis y
     * @param maxCounterToChange lets to update the sprite of the formula one that is drawn in the screen
     * @param vehicle is the type of vehicle selected by the player
     * @param pX is the position of the player in the axis x
     * @param pY is the position of the player in the axis y
     */
    FormulaOne(float maxSpeed, float speedMul, float accInc, float scaleX, float scaleY, int maxCounterToChange,
           const std::string &vehicle, float pX, float pY, const string brandName, const float angle,
           const string motorName);



    /**
     * Returns the last position of the formula one in axis y
     * @return
     */
    float getPreviousY() const;



    /**
     * Updates the crash logic of the formula one and restores speed and acceleration
     * @param vehicleCrash true if it is a crash between vehicles
     */
    void hitControl(bool vehicleCrash);



    /**
     * Returns true if the formula one is crashing. Otherwise returns false
     * @return
     */
    bool isCrashing() const;



    /**
     * Returns the real speed of the formula one
     * @return
     */
    float getRealSpeed() const;



    /**
     * Updates the logic of the formula one's acceleration and braking
     * @param c is the module configuration of the game
     * @param hasGotOut indicates if it's gone off track
     * @return
     */
    Action accelerationControl(Configuration &c, bool hasGotOut);



    /**
     * Updates the logic direction turn of the formula one
     * @param c is the module configuration of the game
     * @param curveCoefficient is the coefficient curve
     * @param isFinalMap controls if the formula one is circulating in the goal landscape or not
     * @param limitMap is the size of the landscape
     * @return
     */
    Direction rotationControl(Configuration &c, float curveCoefficient, const bool& isFinalMap, const int& limitMap);



    /**
     * Updates the formula one's sprite and draws it in the screen
     * @param c is the module configuration of the game
     * @param r is the sound player module of the game
     * @param a is the action to be done by the formula one
     * @param d is the direction to be followed by the formula one
     * @param e is the current elevation of the formula one in the landscape
     * @param enableSound indicates if the motor of the formula one has to make noise
     */
    void draw(Configuration &c, SoundPlayer &r, const Action &a, const Direction &d, const Elevation &e, int terrain, bool enableSound = true);



    /**
     * It forces the formula one to be smoking or not
     * @param smoke indicates if the formula one has to make smoke or not
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
     * Returns the half speed that can be reached by the formula one
     * @return
     */
    float getHalfMaxSpeed();



    /**
     * Returns the brand name of the formula one
     * @return
     */
    string getBrandName();



    /**
     * Returns the angle of turning of the formula one
     * @return
     */
    float getAngle();



    /**
     * Returns the motor's name of the formula one
     * @return
     */
    string getMotorName();



    /**
     * Returns the maximum speed reached by the formula one
     * @return
     */
    float getTopSpeed();



    /**
     * Returns the current code of the sprite of the vehicle to draw
     * @return
     */
    int getCurrentCodeImage() const;

};


#endif // FORMULA_ONE_H
