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
 * Module Police interface file
 */

#pragma once

#ifndef POLICE_H
#define POLICE_H

#include "Vehicle.h"
#include "../include/Randomizer.h"
#include <cmath>

using namespace std;
using namespace sf;



/*
 * Properties of the police
 */
namespace Police_vehicle {
    // Inertia force of the police when it is on curves
    const int FORCE_INERTIA = 15;
    // Number of textures of the police
    const int PLAYER_TEXTURES = 74;
}



/**
 * Represents a police as an available vehicle to be
 * chosen by the player in the vehicle selection menu
 */
class Police : public Vehicle {

    // Factor to multiply the speed of the police
    float speedMul;

    // Maximum acceleration reached by the police
    float maxAcc;

    // Acceleration increment of the police
    float accInc;

    // Scaling factor of the police in axis y
    float scaleY;

    // Current acceleration of the police
    float acceleration;

    // Minimum acceleration reached when the police crashes
    float minCrashAcc;

    // Coordinate in axis x that the police must reach when it crashes
    float xDest;

    // Magnitude of the inertia force that the police experiments in the curves
    int inertia;

    // Sprite to draw the texture of the police in the screen
    sf::Sprite sprite;

    // Control if the police is crashing or not
    bool crashing;

    // Control if the police generates smoke when it is moving
    bool smoking;

    // Control if the police is skidding when it is in a curve
    bool skidding;

    // Mode type of collision
    int mode;

    // Name of the police's brand
    string brand;

    // Brand of the police's motor
    string motor;

    // Angle of turn of the police
    float angleTurning;

    // Maximum speed reached by the police
    float topSpeed;

    // Speed of the police at the moment of a collision
    float speedCollision;

    // Control if the police is inside the road or not
    bool outSideRoad;

    // Control if the police has crashed more than one time
    bool firstCrash;

    // Control if the last direction of the police was turning left
    bool firstTurnLeft;

    // Control if the last direction of the police was turning right
    bool firstTurnRight;

public:



    /**
     * Default constructor
     */
    Police();



    /**
     * Initialize the police chosen by the player
     * @param maxSpeed is the maximum speed that the police can reach
     * @param speedMul is factor number that when it is multiplied by speed obtains the real speed
     * @param accInc is the acceleration increment
     * @param scaleX is the scaling factor in the axis x
     * @param scaleY is the scaling factor in the axis y
     * @param maxCounterToChange lets to update the sprite of the police that is drawn in the screen
     * @param vehicle is the type of vehicle selected by the player
     * @param pX is the position of the player in the axis x
     * @param pY is the position of the player in the axis y
     */
    Police(float maxSpeed, float speedMul, float accInc, float scaleX, float scaleY, int maxCounterToChange,
           const std::string &vehicle, float pX, float pY, const string brandName, const float angle,
           const string motorName);



    /**
     * Returns the last position of the police in axis y
     * @return
     */
    float getPreviousY() const;



    /**
     * Updates the crash logic of the police and restores speed and acceleration
     * @param vehicleCrash true if it is a crash between vehicles
     */
    void hitControl(bool vehicleCrash);



    /**
     * Returns true if the police is crashing. Otherwise returns false
     * @return
     */
    bool isCrashing() const;



    /**
     * Returns the real speed of the police
     * @return
     */
    float getRealSpeed() const;



    /**
     * Updates the logic of the police's acceleration and braking
     * @param c is the module configuration of the game
     * @param hasGotOut indicates if it's gone off track
     * @return
     */
    Action accelerationControl(Configuration &c, bool hasGotOut);



    /**
     * Updates the logic direction turn of the police
     * @param c is the module configuration of the game
     * @param curveCoefficient is the coefficient curve
     * @param isFinalMap controls if the police is circulating in the goal landscape or not
     * @param limitMap is the size of the landscape
     * @return
     */
    Direction rotationControl(Configuration &c, float curveCoefficient, const bool& isFinalMap, const int& limitMap);



    /**
     * Updates the police's sprite and draws it in the screen
     * @param c is the module configuration of the game
     * @param r is the sound player module of the game
     * @param a is the action to be done by the police
     * @param d is the direction to be followed by the police
     * @param e is the current elevation of the police in the landscape
     * @param enableSound indicates if the motor of the police has to make noise
     */
    void draw(Configuration &c, SoundPlayer &r, const Action &a, const Direction &d, const Elevation &e, int terrain, bool enableSound = true);



    /**
     * It forces the police to be smoking or not
     * @param smoke indicates if the police has to make smoke or not
     */
    void setSmoking(bool smoke);



    /**
     * Sets the type mode of collision
     */
    void setModeCollision();



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
     * Returns the half speed that can be reached by the police
     * @return
     */
    float getHalfMaxSpeed();



    /**
     * Returns the angle of turning of the police
     * @return
     */
    float getAngle();



    /**
     * Returns the maximum speed reached by the police
     * @return
     */
    float getTopSpeed();



    /**
     * Returns the current code of the sprite of the vehicle to draw
     * @return
     */
    int getCurrentCodeImage() const;

};


#endif // POLICE_H
