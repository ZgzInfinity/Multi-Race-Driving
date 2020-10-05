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
 * Module RivalCar interface file
 */

#ifndef RIVAL_CAR_H
#define RIVAL_CAR_H

#include "Step.h"
#include "Vehicle.h"
#include "Randomizer.h"
#include <cmath>


using namespace std;
using namespace sf;



/*
 * Properties of the minivan
 */
namespace Vehicle_RivalCar {
    // Control how much the current path has to be followed
    const int MAX_DIRECTION = 1000;
}



/**
 * Represents the rival car driven by the AI of the game
 */
class RivalCar : public Vehicle {

    // Initial coordinate in axis X
    float oriX;

    // Last speed stored of the vehicle
    float lastSpeed;

    // Angle of turning of the vehicle
    float angleTurning;

    // Current direction of the vehicle
    Direction currentDirection;

    // Provisional path of the vehicle
    Direction calculatedPath;

    int current_direction_counter, max_direction_counter;

    bool firstTurnLeft, firstTurnRight, newPath, crashing,
         onStraight, shoutDone, smoking, firing, fireSmoking;;

    int vehicleType;

    // Number of textures of textures of the vehicle
    int numTextures;

    // Texture thresholds to control the movements of the vehicle
    int minTextureRight, maxTextureRight,
        minTextureRightBrake, maxTextureRightBrake;

    int minTextureTurnLeft, maxTextureTurnLeft,
        minTextureTurnLeftBrake, maxTextureTurnLeftBrake;

    int minTextureTurnRight, maxTextureTurnRight,
        minTextureTurnRightBrake, maxTextureTurnRightBrake;

    int minTextureUp, maxTextureUp,
        minTextureUpBrake, maxTextureUpBrake;

    int minTextureTurnLeftUp, maxTextureTurnLeftUp,
        minTextureTurnLeftBrakeUp, maxTextureTurnLeftBrakeUp;

    int minTextureTurnRightUp, maxTextureTurnRightUp,
        minTextureTurnRightBrakeUp, maxTextureTurnRightBrakeUp;

    int medTurnLeft, medTurnRight, medTurnLeftUp, medTurnRightUp,
        medTurnLeftBrake, medTurnRightBrake, medTurnLeftBrakeUp,
        medTurnRightBrakeUp;

    // Aggressiveness of the rival car
    float probAI;

    // Scaling factor of the rival car
    float scalingFactor;

    // Speed of the rival car at the moment of a collision
    float speedCollision;

    // Destination coordinate of the vehicle when it crashes
    float xDest;

    // Multiplier factor to get the real speed of the vehicle
    float speedFactor;



    /**
     * Types of AI:
     * OBSTACLE: Attempts to collide with the player by putting himself in his path and trying to reach him.
     * EVASIVE: Flees to the lane farthest from the player to try to avoid him.
     * INCONSTANT: Changes lanes very often without taking into account the player's position.
     */
    enum TypeAI {
        OBSTACLE,
        EVASIVE,
        INCONSTANT,
        MANIAC
    };

    // AI of the vehicle
    TypeAI typeAI;

public:



    /**
     * Default constructor
     */
    RivalCar();



    /**
     * Initialize the rival car controlled by the AI
     * @param typeOfVehicle indicates the type of vehicle of the rival car
     * @param maxSpeed is the maximum speed reached by the rival car
     * @param speedMul is the multiplier factor to get the real speed of the vehicle
     * @param scale is the scaling factor of the rival car
     * @param maxCounterToChange is the counter to be reached to chance the current path of the vehicle
     * @param pX is the position of the rival car in the axis X
     * @param pY is the position of the rival car in the axis Y
     * @param totalTextures is the number of sprites of the rival car
     * @param lowTextureRight is the identifier of the lower sprite when it goes right
     * @param highTextureRight is the identifier of the higher sprite when it goes right
     * @param lowTextureRightBrake is the identifier of the lower sprite when it goes right and it is braking
     * @param highTextureRightBrake is the identifier of the higher sprite when it goes right and it is braking
     * @param lowTextureTurnLeft is the identifier of the lower sprite when it is turning left
     * @param highTextureTurnLeft is the identifier of the higher sprite when it is turning left
     * @param lowTextureTurnLeftBrake is the identifier of the lower sprite when it is turning left and it is braking
     * @param highTextureTurnLeftBrake is the identifier of the higher sprite when it is turning left and it is braking
     * @param lowTextureTurnRight is the identifier of the lower sprite when it is turning right
     * @param highTextureTurnRight is the identifier of the higher sprite when it is turning right
     * @param lowTextureTurnRightBrake is the identifier of the lower sprite when it is turning right and it is braking
     * @param highTextureTurnRightBrake is the identifier of the higher sprite when it is turning right and it is braking
     * @param lowTextureRightUp is the identifier of the lower sprite when it goes right and it is climbing
     * @param highTextureRightUp is the identifier of the higher sprite when it goes right and it is climbing and braking
     * @param lowTextureRightBrakeUp is the identifier of the lower sprite when it goes right and it is climbing and braking
     * @param highTextureRightBrakeUp is the identifier of the higher sprite when it goes right and it is climbing and braking
     * @param lowTextureTurnLeftUp is the identifier of the lower sprite when it is turning left and climbing
     * @param highTextureTurnLeftUp is the identifier of the higher sprite when it is turning left and climbing
     * @param lowTextureTurnLeftBrakeUp is the identifier of the lower sprite when it is turning left and it is braking and climbing
     * @param highTextureTurnLeftBrakeUp is the identifier of the higher sprite when it is turning left and it is braking and climbing
     * @param lowTextureTurnRightUp is the identifier of the lower sprite when it is turning right and climbing
     * @param highTextureTurnRightUp is the identifier of the higher sprite when it is turning right and climbing
     * @param lowTextureTurnRightBrakeUp is the identifier of the lower sprite when it is turning right and it is braking and climbing
     * @param highTextureTurnRightBrakeUp is the identifier of the higher sprite when it is turning right and it is braking and climbing
     */
    RivalCar(int typeOfVehicle, float maxSpeed, float speedMul, float scale, int maxCounterToChange, const string &vehicle, float pX, float pY,
             int totalTextures, int lowTextureRight, int highTextureRight, int lowTextureRightBrake, int highTextureRightBrake,
             int lowTextureTurnleft, int highTextureTurnLeft, int lowTextureTurnLeftBrake, int highTextureTurnLeftBrake,
             int lowTextureTurnRight, int highTextureTurnRight, int lowTextureTurnRightBrake, int highTextureTurnRightBrake,
             int lowTextureUp, int highTextureUp, int lowTextureUpBrake, int highTextureUpBrake, int lowTextureTurnleftUp,
             int highTextureTurnLeftUp, int lowTextureTurnLeftBrakeUp, int highTextureTurnLeftBrakeUp,  int lowTextureTurnRightUp,
             int highTextureTurnRightUp, int lowTextureTurnRightBrakeUp, int highTextureTurnRightBrakeUp, int mediumTurnLeft,
             int mediumTurnRight, int mediumTurnLeftUp, int mediumTurnRightUp, int mediumTurnLeftBrake, int mediumTurnRightBrake,
             int mediumTurnLeftBrakeUp, int mediumTurnRightBrakeUp, float scaling);



    /**
     * Return the real speed of the rival car
     * @return
     */
    float getRealSpeed() const;



    /**
     * Update the rival car to start to smoke
     */
    void setSmoking();



    /**
     * Returns true if the rival car is smoking. Otherwise returns false
     * @return
     */
    bool getSmoking() const;



    /**
     * Control the possible collision of the rival car with a traffic car
     * @param vehicleCrash controls if the rival car is crashing with a traffic car
     * @param r is the sound player module of the game
     * @param posPlayerY is the position of the player in the axis Y
     */
    void hitControl(const bool vehicleCrash, SoundPlayer& r, float posPlayerY);



    /**
     * Returns true if the rival car is crashing.Otherwise returns false.
     * @return
     */
    void setCrash();



    /**
     * Returns true if the rival car is crashing.Otherwise returns false.
     * @return
     */
    bool isCrashing() const;




    void updateModeA(Configuration& c, float iniPos, float endPos, float maxAggressiveness, Action& a, float directionCurve,
                     const Difficult& difficulty, const float playerPosX, const float playerPosY, const float playerSpeed,
                     const bool vehicleDetected);



    void updateModeB(Configuration& c, float iniPos, float endPos, float maxAggressiveness, Action& a, float directionCurve,
                     const Difficult& difficulty, const float playerPosX, const float playerPosY, const float playerSpeed,
                     const bool vehicleDetected);



    /**
     * Assign the type of AI depending of the difficult level
     * @param is the aggressiveness of the rival car
     * @param difficulty is the difficult level of the game
     * @param typeOfGame is the type of vehicle selected by the player
     */
    void setAI(float maxAggressiveness, const Difficult& difficulty, const int typeOfGame);



    /**
     * Updates the sprite of the rival car
     * @param a is the last action registered of the rival car
     * @param e is the elevation of the terrain where is located the rival car
     */
    void draw(const Action &a, const Elevation &e);



    /**
     * Establish the minimum coordinate in axis X occupied by the rival car
     * @param screenX is the minimum coordinate in axis X occupied by the rival car
     */
    void setMinScreenX(float screenX);



    /**
     * Establish the maximum coordinate in axis X occupied by the rival car
     * @param screenX is the maximum coordinate in axis X occupied by the rival car
     */
    void setMaxScreenX(float screenX);



    /**
     * Returns the current texture of the rival car
     * @return
     */
    const sf::Texture *getCurrentTexture() const;



    /**
     * Returns the scale factor of the rival car
     * @return
     */
    float getScale() const;



    /**
     * Returns the last position of the rival car in axis Y
     * @return
     */
    float getPreviousY() const;



    /**
     * Returns the scaling factor of the rival car
     * @return
     */
    float getScalingFactor() const;



    /**
     * Returns true if there has been a collision between the rival vehicle and the player's vehicle.
     * If true, it also returns the Y position where they have collided
     * @param currentY is the current position of the player's vehicle in the axis y
     * @param prevY is the last position of the player's vehicle in the axis y
     * @param minX is the minimum position in axis x occupied by the vehicle
     * @param maxX is the maximum position in axis y occupied by the vehicle
     * @param crashPos is the position in axis y where the crash has happened
     * @return
     */
    bool hasCrashed(float prevY, float currentY, float minX, float maxX, float &crashPos) const;



    /**
     * Returns true if the car is displayed on screen and the distance to the player, otherwise returns false.
     * @param c is the module configuration of the game
     * @param minY is the position of the camera in the axis y
     * @param playerX is the player position in the axis x
     * @param playerY is the player position in the axis y
     * @param distanceX is the distance between the traffic car and the vehicle of the player in the axis x
     * @param distanceY is the distance between the traffic car and the vehicle of the player in the axis y
     * @return
     */
    bool isVisible(const Configuration &c, float minY, float playerX, float playerY, float &distanceX, float &distanceY) const;



    /**
     * Sets the rival car in straight direction
     */
    void setOnStraight();



    /**
     * Draw the smoking in the rival car
     * @param c is the configuration module of the game
     * @param destW is coordinate where the smoking is going to be drawn in axis X
     * @param destH s coordinate where the smoking is going to be drawn in axis Y
     * @param widthOri is the width dimension scaled of the image if the smoking
     * @param heightOri is the width dimension scaled of the image if the smoking
     * @param maxY is the destination coordinate in axis Y where the smoking
     */
    void drawSmokingPlayer(Configuration& c, const float destW, const float destH, const float widthOri,
                           const float heightOri, const float maxY);



    /**
     * Get the type of vehicle of the rival car
     * @return
     */
    int getVehicleType();



    /**
     * Ser the rival car on fire
     * @param fire indicates if the rival is going to be on fired or not
     */
    void setFiring(const bool fire);



    /**
     * Returns true if the rival car is on fire.
     * Otherwise returns false
     * @return
     */
    bool getFiring();



    /**
     * Sets the smoking fire in the rival car
     * @param fireSmoke controls if the smoking fire has to be drawn or not
     */
    void setFiringSmoke(const bool fireSmoke);



    /**
     * Draw the fire in the rival car
     * @param c is the configuration module of the game
     * @param destW is coordinate where the fire is going to be drawn in axis X
     * @param destH s coordinate where the fire is going to be drawn in axis Y
     * @param widthOri is the width dimension scaled of the image if the fire
     * @param heightOri is the width dimension scaled of the image if the fire
     * @param maxY is the destination coordinate in axis Y where the fire
     */
    void drawFirePlayer(Configuration& c, const float destW, const float destH, const float widthOri,
                        const float heightOri, const float maxY);



    /**
     * Draw the smoking fire in the rival car
     * @param c is the configuration module of the game
     * @param destW is coordinate where the smoking fire is going to be drawn in axis X
     * @param destH s coordinate where the smoking fire is going to be drawn in axis Y
     * @param widthOri is the width dimension scaled of the image if the smoking fire
     * @param heightOri is the width dimension scaled of the image if the smoking fire
     * @param maxY is the destination coordinate in axis Y where the smoking fire
     */
    void drawSmokingFirePlayer(Configuration& c, const float destW, const float destH, const float widthOri,
                               const float heightOri, const float maxY);



    /**
     * Returns true if the rival car is starting to smoke and fire.
     * Otherwise returns false.
     * @return
     */
    bool getFiringSmoke();



    /**
     * Returns if the rival is in the middle on the crash animation
     * @return
     */
    bool inCrash();

};


#endif // RIVAL_CAR_H
