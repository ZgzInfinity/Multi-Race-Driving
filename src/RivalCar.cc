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
 * Module RivalCar implementation file
 */



#include "../include/RivalCar.h"



/**
 * Default constructor
 */
RivalCar::RivalCar(){}



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
RivalCar::RivalCar(int typeOfVehicle,float maxSpeed, float speedMul, float scale, int maxCounterToChange, const string &vehicle, float pX, float pY,
                   int totalTextures, int lowTextureRight, int highTextureRight, int lowTextureRightBrake, int highTextureRightBrake,
                   int lowTextureTurnleft, int highTextureTurnLeft, int lowTextureTurnLeftBrake, int highTextureTurnLeftBrake,
                   int lowTextureTurnRight, int highTextureTurnRight, int lowTextureTurnRightBrake, int highTextureTurnRightBrake,
                   int lowTextureUp, int highTextureUp, int lowTextureUpBrake, int highTextureUpBrake, int lowTextureTurnleftUp,
                   int highTextureTurnLeftUp, int lowTextureTurnLeftBrakeUp, int highTextureTurnLeftBrakeUp,  int lowTextureTurnRightUp,
                   int highTextureTurnRightUp, int lowTextureTurnRightBrakeUp, int highTextureTurnRightBrakeUp, int mediumTurnLeft,
                   int mediumTurnRight, int mediumTurnLeftUp, int mediumTurnRightUp, int mediumTurnLeftBrake, int mediumTurnRightBrake,
                   int mediumTurnLeftBrakeUp, int mediumTurnRightBrakeUp, float scaling) :
                    Vehicle(maxSpeed / speedMul, scale, maxCounterToChange, 0.f, pX, pX,
                    pY, pY, 0, 0, vehicle, totalTextures, 1, 0), oriX(this->posX),
                    currentDirection(RIGHT), calculatedPath(RIGHT), current_direction_counter(0), max_direction_counter(0),
                    probAI(0), typeAI(OBSTACLE)
{
    // Assignment of the attributes
    minTextureRightBrake = lowTextureRightBrake; maxTextureRightBrake = highTextureRightBrake; minTextureTurnLeft = lowTextureTurnleft;
    numTextures = totalTextures; minTextureRight = lowTextureRight; maxTextureRight = highTextureRight;
    maxTextureTurnLeft = highTextureTurnLeft; minTextureTurnLeftBrake = lowTextureTurnLeftBrake;
    maxTextureTurnLeftBrake = highTextureTurnLeftBrake; minTextureTurnRight = lowTextureTurnRight;
    maxTextureTurnRight = highTextureTurnRight; minTextureTurnRightBrake = lowTextureTurnRightBrake;
    maxTextureTurnRightBrake = highTextureTurnRightBrake; minTextureUp = lowTextureUp; maxTextureUp = highTextureUp;
    minTextureUpBrake = lowTextureUpBrake; maxTextureUpBrake = highTextureUpBrake; minTextureTurnLeftUp = lowTextureTurnleftUp;
    maxTextureTurnLeftUp = highTextureTurnLeftUp; minTextureTurnLeftBrakeUp = lowTextureTurnLeftBrakeUp;
    maxTextureTurnLeftBrakeUp = highTextureTurnLeftBrakeUp; minTextureTurnRightUp = lowTextureTurnRightUp;
    maxTextureTurnRightUp = highTextureTurnRightUp; minTextureTurnRightBrakeUp = lowTextureTurnRightBrakeUp;
    maxTextureTurnRightBrakeUp = highTextureTurnRightBrakeUp,

    medTurnLeft = mediumTurnLeft;
    medTurnRight = mediumTurnRight;
    medTurnLeftUp = mediumTurnLeftUp;
    medTurnRightUp = mediumTurnRightUp;
    medTurnLeftBrake = mediumTurnLeftBrake;
    medTurnRightBrake = mediumTurnRightBrake;
    medTurnLeftBrakeUp = mediumTurnLeftBrakeUp;
    medTurnRightBrakeUp = mediumTurnRightBrakeUp;

    scalingFactor = scaling;
    angleTurning = 0.f;
    newPath = false;
    onStraight = true;
    crashing = false;
    vehicleType = typeOfVehicle;
    xDest = 1000;
    speedFactor = speedMul;
    shoutDone = false;
    smoking = false;
    firing = false;
    fireSmoking = false;
}



/**
 * Returns true if the rival car is crashing.Otherwise returns false.
 * @return
 */
void RivalCar::setCrash(){
    crashing = false;
}



/**
 * Returns true if the rival car is crashing.Otherwise returns false.
 * @return
 */
bool RivalCar::isCrashing() const {
    return crashing;
}



/**
 * Return the real speed of the rival car
 * @return
 */
float RivalCar::getRealSpeed() const {
    return speed * speedFactor;
}



/**
 * Update the rival car to start to smoke
 */
void RivalCar::setSmoking(){
    smoking = true;
}



/**
 * Returns true if the rival car is smoking. Otherwise returns false
 * @return
 */
bool RivalCar::getSmoking() const {
    return smoking;
}



/**
 * Control the possible collision of the rival car with a traffic car
 * @param vehicleCrash controls if the rival car is crashing with a traffic car
 * @param r is the sound player module of the game
 * @param posPlayerY is the position of the player in the axis Y
 */
void RivalCar::hitControl(const bool vehicleCrash, SoundPlayer& r, float posPlayerY) {

    // The rival car by default is crashing
    crashing = true;

    // Check if the collision sound has sounded
    if (!shoutDone){

        // Sound takes place checking the type of vehicle
        shoutDone = true;

        if (vehicleType == 0){
            r.soundEffects[62]->stop();
            r.soundEffects[63]->stop();
            r.soundEffects[64]->stop();
            r.soundEffects[65]->stop();
            r.soundEffects[66]->stop();
            r.soundEffects[67]->stop();

            // Check if the rival car is behind or in front of the player
            if (posPlayerY >= posY){

                // The rival car is behind
                int soundCode = rand_generator_int(62, 66);

                // Reproduce the sound with a level volume low when the car that crashes is far
                // and reproduces the sound with high volume when the car is near
                r.soundEffects[soundCode]->setVolume(int(posY / posPlayerY * 100.f));
                r.soundEffects[67]->setVolume(int(posY / posPlayerY * 100.f));

                r.soundEffects[soundCode]->play();
                r.soundEffects[67]->play();

            }
            else {
                // The player is behind
                int soundCode = rand_generator_int(62, 66);

                // Reproduce the sound with a level volume low when the car that crashes is far
                // and reproduces the sound with high volume when the car is near
                r.soundEffects[soundCode]->setVolume(int(posPlayerY / posY * 100.f));
                r.soundEffects[67]->setVolume(int(posPlayerY / posY * 100.f));

                r.soundEffects[soundCode]->play();
                r.soundEffects[67]->play();
            }
        }
        else {
            // Stop the sounds
            r.soundEffects[17]->stop();
            r.soundEffects[18]->stop();
            r.soundEffects[19]->stop();

            r.soundEffects[17]->play();

            // Check if the rival car is behind or in front of the player
            if (posPlayerY >= posY){
                // The rival car is behind
                int soundCode = rand_generator_int(18, 19);

                // Reproduce the sound with a level volume low when the car that crashes is far
                // and reproduces the sound with high volume when the car is near
                r.soundEffects[soundCode]->setVolume(int(posY / posPlayerY * 60.f));
                r.soundEffects[17]->setVolume(int(posY / posPlayerY * 60.f));

                r.soundEffects[soundCode]->play();
                r.soundEffects[17]->play();

            }
            else {
                // The player is behind
                int soundCode = rand_generator_int(18, 19);

                // Reproduce the sound with a level volume low when the car that crashes is far
                // and reproduces the sound with high volume when the car is near
                r.soundEffects[soundCode]->setVolume(int(posPlayerY / posY * 60.f));
                r.soundEffects[17]->setVolume(int(posPlayerY / posY * 60.f));

                r.soundEffects[soundCode]->play();
                r.soundEffects[17]->play();
            }
        }
    }

    // Get the acceleration of the rival car
    const float acc = getAcceleration();

    // Get the speed of the rival car when starts the collision
    if (speedCollision == 0.f){
        // Get the speed
        speedCollision = getRealSpeed();
        if (speedCollision < 60.f)
            // Increment position in axis Y
            posY = posY + speed * 0.50f;
    }
    // The rival car is a motorbike
    if (vehicleType == 0){
        mainMutex.lock();
        // Reduces speed
        speed = sqrt(acc - ACCELERATION_INCREMENT);
        mainMutex.unlock();

        // Moves the vehicle in axis Y
        posY = posY + 0.1f;

        // Stop the crash animation of the motorbike when the last sprite is reached
        if (current_code_image == 58){
            // Restart the values
            crashing = false;
            shoutDone = false;
            xDest = 1000;
            previousY = posY;
            speedCollision = 0.0f;
            speed = 0.4f;
            r.soundEffects[30]->stop();
            r.soundEffects[30]->play();
            current_code_image = 1;
        }
    }
    else {
        // The rival car is not a motorbike
        if (xDest == 1000){
            // Store the position in axis X
            xDest = posX;
        }

        // The rival car moves in collision if it is not a Formula one
        if (vehicleType != 4){
            // Moves the car in axis X
            if (xDest >= 0.f){
                // The collision take place in the right track and the car goes to the left
                if (posX -= 0.01f < -0.7f){
                    posX = -0.7f;
                }
                else {
                    posX -= 0.01f;
                }
            }
            else {
                // The collision take place in the left track and the car goes to the right
                if (posX += 0.01f < 0.7f){
                    posX = 0.7f;
                }
                else {
                    posX += 0.01f;
                }
            }
            // The rival car goes back while it is crashing
            posY = posY - 0.01f;
        }

        int maxCode = 0;

        // Get the code of the last sprite depending of the type of rival car
        switch(vehicleType){
            case 0:
                // Motorbike
                maxCode = 58;
                break;
            case 1:
                // Devastator
                maxCode = 44;
                break;
            case 2:
                // Minivan
                maxCode = 36;
                break;
            case 3:
                // Truck
                maxCode = 62;
                break;
            case 4:
                // Formula one
                maxCode = 53;
                break;
            case 5:
                // Police
                maxCode = 37;
        }
        // Control if the animation has finished
        if (current_code_image == maxCode){
            crashing = false;
            xDest = 1000;
            previousY = posY;
            speedCollision = 0.0f;
            shoutDone = false;
            speed = 0.4f;
            current_code_image = 1;
            switch(vehicleType){
                case 1:
                    r.soundEffects[12]->stop();
                    r.soundEffects[12]->play();
                    break;
                case 2:
                    r.soundEffects[41]->stop();
                    r.soundEffects[41]->play();
                    break;
                case 3:
                    r.soundEffects[33]->stop();
                    r.soundEffects[33]->play();
                    break;
                case 4:
                    r.soundEffects[121]->stop();
                    r.soundEffects[121]->play();
                    break;
                case 5:
                    r.soundEffects[114]->stop();
                    r.soundEffects[114]->play();
            }
        }
    }
}



void RivalCar::updateModeA(Configuration& c, float iniPos, float endPos, float maxAggressiveness, Action& a, float directionCurve,
                           const Difficult& difficulty, const float playerPosX, const float playerPosY, const float playerSpeed,
                           const bool vehicleDetected)
{
    // Store the current speed before updating
    lastSpeed = speed;
    currentDirection = RIGHT;

    // Check if the player is on curve
    if (directionCurve == 0.f){
        if (abs(playerPosY - posY) < 100.f && posY > 90.f){
            // AI
            if (typeAI == OBSTACLE) {
                const float acc = getAcceleration();
                if (abs(playerPosX - posX) > INCREMENT_X) { // Rotation control
                    // The vehicle is not in the player's path
                    if (speed < halfMaxSpeed){
                        speed = sqrt(acc + ACCELERATION_INCREMENT);
                    }

                    // Calculate the path depending of the position of the player car
                    if (posX > playerPosX && posX > -0.9f) {
                        // Moves to left to obstacle the player car that is on the left
                        posX -= INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNLEFT;
                    }
                    else if (posX < 0.9f) {
                        // Moves to right to obstacle the player car that is on the right
                        posX += INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNRIGHT;
                    }
                }
                else { // Acceleration control
                    // The vehicle is in the player's path
                    if (posY <= playerPosY){
                        speed = sqrt(acc + ACCELERATION_INCREMENT);
                    }
                    else if (acc > ACCELERATION_INCREMENT){
                        speed = sqrt(acc - ACCELERATION_INCREMENT);
                    }
                    else {
                        speed = 0.0f;
                    }
                    // The direction is right
                    currentDirection = RIGHT;
                }
            }
            else if (typeAI == EVASIVE) {
                // Check the player is axis X
                if (playerPosX <= -0.5) {
                    float offsetX = INCREMENT_X * speed / maxSpeed;
                    // Moves in the opponent direction
                    if (posX + offsetX <= 0.7f){
                        // The player car is left and the rival car goes to the right
                        posX += INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNRIGHT;
                    }
                    else {
                        // The rival car goes right
                        currentDirection = RIGHT;
                    }
                }
                // Check the player is axis X
                else if (playerPosX >= 0.5) {
                    float offsetX = INCREMENT_X * speed / maxSpeed;
                    // The player car is right and the rival car goes to the left
                    if (posX + offsetX >= -0.7f){
                        posX -= INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNLEFT;
                    }
                    else {
                        // The rival car goes right
                        currentDirection = RIGHT;
                    }
                }
                else {
                    // Check the player position in axis y and goes in the opponent direction
                    if (posX > playerPosX) {
                        float offsetX = INCREMENT_X * speed / maxSpeed;
                        if (posX + offsetX <= 0.7f){
                            posX += INCREMENT_X * speed / maxSpeed;
                            currentDirection = TURNRIGHT;
                        }
                        else {
                            currentDirection = RIGHT;
                        }
                    }
                    else {
                        float offsetX = INCREMENT_X * speed / maxSpeed;
                        if (posX - offsetX >= -0.7f){
                            posX -= INCREMENT_X * speed / maxSpeed;
                            currentDirection = TURNLEFT;
                        }
                        else {
                            currentDirection = RIGHT;
                        }
                    }
                }
            }
            else if (typeAI == INCONSTANT) {
                // The rival car moves ignoring the player car
                if (currentDirection == TURNRIGHT) {
                    const float prevPosX = posX;
                    posX += INCREMENT_X * speed / maxSpeed;

                    if (posX >= 0.9f){
                        currentDirection = TURNLEFT;
                    }
                    else if (((prevPosX < -0.5f && posX >= -0.5f) || (prevPosX < 0.0f && posX >= 0.0f) ||
                              (prevPosX < 0.5f && posX >= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    {
                        currentDirection = TURNRIGHT; // Lane change
                    }
                }
                else if (currentDirection == TURNLEFT) {
                    const float prevPosX = posX;
                    posX -= INCREMENT_X * speed / maxSpeed;

                    if (posX <= -0.9f){
                        currentDirection = TURNRIGHT;
                    }
                    else if (((prevPosX > -0.5f && posX <= -0.5f) || (prevPosX > 0.0f && posX <= 0.0f) ||
                              (prevPosX > 0.5f && posX <= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    {
                        currentDirection = TURNLEFT; // Lane change
                    }
                }
                else {
                    if (rand_generator_zero_one() < 0.5f){
                        currentDirection = TURNRIGHT;
                    }
                    else {
                        currentDirection = TURNLEFT;
                    }
                }
            }
            else {
                // MANIAC
                if (vehicleDetected){
                    float p, cordX = 0.f;
                    // Check the difficulty to control the speed of changing
                    switch(c.level){
                        case EASY:
                            p = rand_generator_zero_one();
                            if (p <= 0.5f){
                                const float direction = rand_generator_zero_one();
                                if (direction <= 0.5){
                                    if (cordX < 0.f){
                                        cordX += 0.02f;
                                    }
                                    else {
                                        cordX -= 0.02f;
                                    }
                                }
                            }
                            break;
                        case NORMAL:
                            p = rand_generator_zero_one();
                            if (p <= 0.65f){
                                if (cordX < 0.f){
                                    cordX += 0.035f;
                                }
                                else {
                                    cordX -= 0.035f;
                                }
                            }
                            break;
                        case HARD:
                            p = rand_generator_zero_one();
                            if (p <= 0.8f){
                                if (cordX < 0.f){
                                    cordX += 0.05f;
                                }
                                else {
                                    cordX -= 0.05f;
                                }
                            }
                    }
                }
            }
        }
        // Goes right and maintain the direction until the counter expires
        else {
            if (posX > 0.f && !onStraight){
                posX -= rand_generator_float(0.03f, 0.06f);
                onStraight = true;
            }
            else if (posX < 0.f && !onStraight){
                posX += rand_generator_float(0.03f, 0.06f);
                onStraight = true;
            }

            if (counter_code_image < max_direction_counter){
                counter_code_image++;
            }
            else {
                currentDirection = randomDirection();
                counter_code_image = 0;
                max_direction_counter = rando_generator_zero_n(Vehicle_RivalCar::MAX_DIRECTION);
            }

            float newX = posX, offsetX;
            if (currentDirection == TURNRIGHT){
                offsetX = INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;
                if (newX + offsetX <= 0.7f){
                    newX += offsetX;
                }
            }
            else if (currentDirection == TURNLEFT){
                offsetX = INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;
                if (newX - offsetX >= -0.7f){
                    newX -= offsetX;
                }
            }

            if (newX < oriX - 0.35f || newX > oriX + 0.35f){
                currentDirection = RIGHT;
            }
            else {
                posX = newX;
            }
        }
    }
    else {
        onStraight = false;

        if (abs(playerPosY - posY) < 100.f && posY > 90.f){
            // AI
            if (typeAI == OBSTACLE) {
                const float acc = getAcceleration();
                if (abs(playerPosX - posX) > INCREMENT_X) { // Rotation control
                    // The vehicle is not in the player's path
                    if (posX > playerPosX && posX > -0.7f) {
                        posX -= INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNLEFT;
                    }
                    else if (posX < 0.7f) {
                        posX += INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNRIGHT;
                    }
                }
                else { // Acceleration control
                    // The vehicle is in the player's path
                    if (acc > ACCELERATION_INCREMENT){
                        speed = sqrt(acc - ACCELERATION_INCREMENT);
                    }
                    else {
                        speed = 0.0f;
                    }

                    currentDirection = RIGHT;
                }
            }
            else if (typeAI == EVASIVE) {
                if (playerPosX <= -0.5) {
                    float offsetX = INCREMENT_X * speed / maxSpeed;
                    if (posX + offsetX <= 0.7f){
                        posX += INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNRIGHT;
                    }
                    else {
                        if (directionCurve > 0.f){
                            currentDirection = TURNRIGHT;
                        }
                        else {
                            currentDirection = TURNLEFT;
                        }
                    }
                }
                else if (playerPosX >= 0.5) {
                    float offsetX = INCREMENT_X * speed / maxSpeed;
                    if (posX - offsetX >= -0.7f){
                        posX -= INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNLEFT;
                    }
                    else {
                        if (directionCurve > 0.f){
                            currentDirection = TURNRIGHT;
                        }
                        else {
                            currentDirection = TURNLEFT;
                        }
                    }
                }
                else {
                    if (posX > playerPosX) {
                        float offsetX = INCREMENT_X * speed / maxSpeed;
                        if (posX + offsetX <= 0.7f){
                            posX += INCREMENT_X * speed / maxSpeed;
                            currentDirection = TURNRIGHT;
                        }
                        else {
                            if (directionCurve > 0.f){
                                currentDirection = TURNRIGHT;
                            }
                            else {
                                currentDirection = TURNLEFT;
                            }
                        }
                    }
                    else {
                        float offsetX = INCREMENT_X * speed / maxSpeed;
                        if (posX - offsetX >= -0.7f){
                            posX -= INCREMENT_X * speed / maxSpeed;
                            currentDirection = TURNLEFT;
                        }
                        else {
                            if (directionCurve > 0.f){
                                currentDirection = TURNRIGHT;
                            }
                            else {
                                currentDirection = TURNLEFT;
                            }
                        }
                    }
                }
            }
            else if (typeAI == INCONSTANT){
                if (currentDirection == TURNRIGHT) {
                    const float prevPosX = posX;
                    posX += INCREMENT_X * speed / maxSpeed;

                    if (posX >= 0.7f){
                        currentDirection = TURNLEFT;
                    }
                    else if (((prevPosX < -0.5f && posX >= -0.5f) || (prevPosX < 0.0f && posX >= 0.0f) ||
                              (prevPosX < 0.5f && posX >= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    {
                        currentDirection = TURNRIGHT; // Lane change
                    }
                }
                else if (currentDirection == TURNLEFT) {
                    const float prevPosX = posX;
                    posX -= INCREMENT_X * speed / maxSpeed;

                    if (posX <= -0.7f){
                        currentDirection = TURNRIGHT;
                    }
                    else if (((prevPosX > -0.5f && posX <= -0.5f) || (prevPosX > 0.0f && posX <= 0.0f) ||
                              (prevPosX > 0.5f && posX <= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    {
                        currentDirection = TURNLEFT; // Lane change
                    }
                }
                else {
                    if (rand_generator_zero_one() <= 0.333f){
                        currentDirection = TURNRIGHT;
                    }
                    else if (rand_generator_zero_one() <= 0.666f){
                        currentDirection = TURNLEFT;
                    }
                    else {
                        currentDirection = RIGHT;
                    }
                }
            }
            else {
                // MANIAC
                if (vehicleDetected){
                    float p;
                    // Check the difficulty to control the speed of changing
                    switch(c.level){
                        case EASY:
                            p = rand_generator_zero_one();
                            if (p <= 0.5f){
                                const float direction = rand_generator_zero_one();
                                if (direction <= 0.5){
                                    if (posX < 0.f){
                                        posX += 0.01f;
                                    }
                                    else {
                                        posX -= 0.01f;
                                    }
                                }
                            }
                            break;
                        case NORMAL:
                            p = rand_generator_zero_one();
                            if (p <= 0.65f){
                                if (posX < 0.f){
                                    posX += 0.015f;
                                }
                                else {
                                    posX -= 0.015f;
                                }
                            }
                            break;
                        case HARD:
                            p = rand_generator_zero_one();
                            if (p <= 0.8f){
                                if (posX < 0.f){
                                    posX += 0.02f;
                                }
                                else {
                                    posX -= 0.02f;
                                }
                            }
                    }
                }
            }
        }
        else {
            // Set and angle of turn for the curve
            if (abs(posX >= 0.f) && abs(posX) <= 0.3f){
                angleTurning = rand_generator_float(0.007f, 0.01f);
            }
            else if (abs(posX > 0.3f) && abs(posX) <= 0.7f){
                angleTurning = rand_generator_float(0.003f, 0.007f);
            }
            else {
                angleTurning = rand_generator_float(0.001f, 0.003f);
            }

            if (directionCurve > 0.f){
                currentDirection = TURNRIGHT;
            }
            else {
                currentDirection = TURNLEFT;
            }
            if (currentDirection == TURNRIGHT){
                if (abs(posX) + angleTurning < 0.7f){
                    posX += angleTurning;
                }
            }
            else if (currentDirection == TURNLEFT){
                if (abs(posX) + angleTurning < 0.7f){
                    posX -= angleTurning;
                }
            }
        }
    }

    // Update the speed of the vehicle
    const float acc = getAcceleration();

    // At the beginning all accelerate the same
    if (posY <= 90.f || speed <= 0.8f){
        // Increment speed of the rival car
        speed = sqrt(acc + ACCELERATION_INCREMENT);
        a = BOOT;
        smoking = true;
    }
    else {
        smoking = false;
        a = BOOT;
        // Avoid to reach impossible speeds only a 20 percent superior
        if (posY - playerPosY >= c.renderLen){
            // Each vehicle accelerates in a different mode
            if (speed <= 2.0f){
                speed = sqrt(acc + rand_generator_float(0.01f, 0.05f));
                if (speed < 2.0f){
                    speed = 2.0f;
                }
            }
            a = ACCELERATE;
        }
        // Avoid to reach impossible speeds only a 20 percent superior
        else if (posY - playerPosY > 0.f){
            // Each vehicle accelerates in a different mode
            float p = rand_generator_zero_one();
            if (p > 0.7f){
                if (playerSpeed < 1.9f){
                    if (speed <= 1.9f){
                        speed = sqrt(acc + rand_generator_float(0.01f, 0.03f)) * rand_generator_float(1.0f, 1.1f);
                        if (speed < 1.9f){
                            speed = 1.9f;
                        }
                    }
                }
                else {
                    if (speed <= 1.8f){
                        speed = sqrt(acc + rand_generator_float(0.01f, 0.03f)) * rand_generator_float(1.0f, 1.1f);
                        if (speed < 1.8f){
                            speed = 1.8f;
                        }
                    }
                }
            }
            a = ACCELERATE;
        }
        else if (playerPosY - posY < 70.f) {
            // Each vehicle accelerates in a different mode
            if (speed > 2.1f){
                speed = sqrt(acc + rand_generator_float(0.01f, 0.05f));
                if (speed > 2.1f){
                    speed = 2.1f;
                }
            }
            a = ACCELERATE;
        }
        else {
            // Each vehicle accelerates in a different mode
            float p = rand_generator_zero_one();
            if (p < 0.8f){
                    if (speed > 2.5f){
                    speed = sqrt(acc + rand_generator_float(0.01f, 0.05f));
                    if (speed > 2.5f){
                        speed = 2.5f;
                    }
                }
            }
            else {
                speed = lastSpeed;
            }
            a = ACCELERATE;
        }
        if (directionCurve != 0.f){
            if (posY > playerPosY){
                float powerBraking, power;
                float option = rand_generator_int(0, 2);
                if (abs(directionCurve) >= 1.2f && abs(directionCurve) <= 1.9f){
                    if (option == 1 && acc > 0.f){
                        powerBraking = rand_generator_float(0.001f, 0.01f);
                        if (speed >= 1.5f){
                            speed = sqrt(acc - powerBraking);
                            if (!fireSmoking && !firing){
                                smoking = true;
                            }
                        }
                        else {
                            speed = 1.5f;
                            smoking = false;
                        }
                    }
                }
                else if (abs(directionCurve) >= 0.8f && abs(directionCurve) < 1.2f){
                    if (option == 1 && acc > 0.f){
                        powerBraking = rand_generator_float(0.001f, 0.01f);
                        if (speed >= 1.6f){
                            speed = sqrt(acc - powerBraking);
                            if (!fireSmoking && !firing){
                                smoking = true;
                            }
                        }
                        else {
                            speed = 1.6f;
                            smoking = false;
                        }
                    }
                    else if (option == 2){
                        power = rand_generator_float(0.001f, 0.01f);
                        if (speed <= 1.7f){
                            speed = sqrt(acc + power);
                        }
                        else {
                            speed = 1.7f;
                        }
                    }
                }
                else if (abs(directionCurve) >= 0.3f && abs(directionCurve) < 0.8f){
                    if (option == 1 && acc > 0.f){
                        powerBraking = rand_generator_float(0.001f, 0.01f);
                        if (speed >= 1.7f){
                            speed = sqrt(acc - powerBraking);
                            if (!fireSmoking && !firing){
                                smoking = true;
                            }
                        }
                        else {
                            speed = 1.7f;
                            smoking = false;
                        }
                    }
                    else if (option == 2){
                        power = rand_generator_float(0.001f, 0.01f);
                        if (speed <= 1.8f){
                            speed = sqrt(acc + power);
                        }
                        else {
                            speed = 1.8f;
                        }
                    }
                }
            }
            a = BRAKE;
        }
    }
    // Advance the vehicle
    previousY = posY;
    posY += speed;
}



void RivalCar::updateModeB(Configuration& c, float iniPos, float endPos, float maxAggressiveness, Action& a, float directionCurve,
                           const Difficult& difficulty, const float playerPosX, const float playerPosY, const float playerSpeed,
                           const bool vehicleDetected)
{
   // Store the current speed before updating
    lastSpeed = speed;
    currentDirection = RIGHT;

    // Check if the player is on curve
    if (directionCurve == 0.f){
        if (abs(playerPosY - posY) < 100.f && posY > 90.f){
            // AI
            if (typeAI == OBSTACLE) {
                const float acc = getAcceleration();
                if (abs(playerPosX - posX) > INCREMENT_X) { // Rotation control
                    // The vehicle is not in the player's path
                    if (speed < halfMaxSpeed){
                        speed = sqrt(acc + ACCELERATION_INCREMENT);
                    }

                    if (posX > playerPosX && posX > -0.9f) {
                        posX -= INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNLEFT;
                    }
                    else if (posX < 0.9f) {
                        posX += INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNRIGHT;
                    }
                }
                else { // Acceleration control
                    // The vehicle is in the player's path
                    if (posY <= playerPosY){
                        speed = sqrt(acc + ACCELERATION_INCREMENT);
                    }
                    else if (acc > ACCELERATION_INCREMENT){
                        speed = sqrt(acc - ACCELERATION_INCREMENT);
                    }
                    else {
                        speed = 0.f;
                    }

                    currentDirection = RIGHT;
                }
            }
            else if (typeAI == EVASIVE) {
                if (playerPosX <= -0.5) {
                    float offsetX = INCREMENT_X * speed / maxSpeed;
                    if (posX + offsetX <= 0.7f){
                        posX += INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNRIGHT;
                    }
                    else {
                        currentDirection = RIGHT;
                    }
                }
                else if (playerPosX >= 0.5) {
                    float offsetX = INCREMENT_X * speed / maxSpeed;
                    if (posX + offsetX >= -0.7f){
                        posX -= INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNLEFT;
                    }
                    else {
                        currentDirection = RIGHT;
                    }
                }
                else {
                    if (posX > playerPosX) {
                        float offsetX = INCREMENT_X * speed / maxSpeed;
                        if (posX + offsetX <= 0.7f){
                            posX += INCREMENT_X * speed / maxSpeed;
                            currentDirection = TURNRIGHT;
                        }
                        else {
                            currentDirection = RIGHT;
                        }
                    }
                    else {
                        float offsetX = INCREMENT_X * speed / maxSpeed;
                        if (posX - offsetX >= -0.7f){
                            posX -= INCREMENT_X * speed / maxSpeed;
                            currentDirection = TURNLEFT;
                        }
                        else {
                            currentDirection = RIGHT;
                        }
                    }
                }
            }
            else if (typeAI == INCONSTANT) {
                if (currentDirection == TURNRIGHT) {
                    const float prevPosX = posX;
                    posX += INCREMENT_X * speed / maxSpeed;

                    if (posX >= 0.9f){
                        currentDirection = TURNLEFT;
                    }
                    else if (((prevPosX < -0.5f && posX >= -0.5f) || (prevPosX < 0.0f && posX >= 0.0f) ||
                              (prevPosX < 0.5f && posX >= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    {
                        currentDirection = TURNRIGHT; // Lane change
                    }
                }
                else if (currentDirection == TURNLEFT) {
                    const float prevPosX = posX;
                    posX -= INCREMENT_X * speed / maxSpeed;

                    if (posX <= -0.9f){
                        currentDirection = TURNRIGHT;
                    }
                    else if (((prevPosX > -0.5f && posX <= -0.5f) || (prevPosX > 0.0f && posX <= 0.0f) ||
                              (prevPosX > 0.5f && posX <= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    {
                        currentDirection = TURNLEFT; // Lane change
                    }
                }
                else {
                    if (rand_generator_zero_one() < 0.5f){
                        currentDirection = TURNRIGHT;
                    }
                    else {
                        currentDirection = TURNLEFT;
                    }
                }
            }
            else {
                // MANIAC
                if (vehicleDetected){
                    float p;
                    // Check the difficulty to control the speed of changing
                    switch(c.level){
                        case EASY:
                            p = rand_generator_zero_one();
                            if (p <= 0.5f){
                                const float direction = rand_generator_zero_one();
                                if (direction <= 0.5){
                                    if (posX < 0.f){
                                        posX += 0.02f;
                                    }
                                    else {
                                        posX -= 0.02f;
                                    }
                                }
                            }
                            break;
                        case NORMAL:
                            p = rand_generator_zero_one();
                            if (p <= 0.65f){
                                if (posX < 0.f){
                                    posX += 0.035f;
                                }
                                else {
                                    posX -= 0.035f;
                                }
                            }
                            break;
                        case HARD:
                            p = rand_generator_zero_one();
                            if (p <= 0.8f){
                                if (posX < 0.f){
                                    posX += 0.05f;
                                }
                                else {
                                    posX -= 0.05f;
                                }
                            }
                    }
                }
                else {
                    if (current_direction_counter < max_direction_counter) {
                        current_direction_counter++;
                    }
                     else {
                        max_direction_counter = rando_generator_zero_n(Vehicle_RivalCar::MAX_DIRECTION);
                        current_direction_counter = 0;
                        calculatedPath = randomDirection();
                    }

                    float newX = posX;
                    if (calculatedPath == TURNRIGHT)
                        newX += INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;
                    else if (calculatedPath == TURNLEFT)
                        newX -= INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;

                    if (newX < oriX - 0.15f || newX > oriX + 0.15f){
                        calculatedPath = RIGHT;
                    }
                    else {
                        posX = newX;
                    }
                    currentDirection = calculatedPath;
                }
            }
        }
        else {
            if (posX > 0.f && !onStraight){
                posX -= rand_generator_float(0.03f, 0.06f);
                onStraight = true;
            }
            else if (posX < 0.f && !onStraight){
                posX += rand_generator_float(0.03f, 0.06f);
                onStraight = true;
            }

            if (counter_code_image < max_direction_counter){
                counter_code_image++;
            }
            else {
                currentDirection = randomDirection();
                counter_code_image = 0;
                max_direction_counter = rando_generator_zero_n(Vehicle_RivalCar::MAX_DIRECTION);
            }

            float newX = posX, offsetX;
            if (currentDirection == TURNRIGHT){
                offsetX = INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;
                if (newX + offsetX <= 0.7f){
                    newX += offsetX;
                }
            }
            else if (currentDirection == TURNLEFT){
                offsetX = INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;
                if (newX - offsetX >= -0.7f){
                    newX -= offsetX;
                }
            }

            if (newX < oriX - 0.35f || newX > oriX + 0.35f){
                currentDirection = RIGHT;
            }
            else {
                posX = newX;
            }
        }
    }
    else {
        onStraight = false;
        if (abs(playerPosY - posY) < 100.f && posY > 90.f){
            // AI
            if (typeAI == OBSTACLE) {
                const float acc = getAcceleration();
                if (abs(playerPosX - posX) > INCREMENT_X) { // Rotation control
                    // The vehicle is not in the player's path
                    if (posX > playerPosX && posX > -0.7f) {
                        posX -= INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNLEFT;
                    }
                    else if (posX < 0.7f) {
                        posX += INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNRIGHT;
                    }
                }
                else { // Acceleration control
                    // The vehicle is in the player's path
                    if (acc > ACCELERATION_INCREMENT){
                        speed = sqrt(acc - ACCELERATION_INCREMENT);
                    }
                    else {
                        speed = 0.0f;
                    }

                    currentDirection = RIGHT;
                }
            }
            else if (typeAI == EVASIVE) {
                if (playerPosX <= -0.5) {
                    float offsetX = INCREMENT_X * speed / maxSpeed;
                    if (posX + offsetX <= 0.7f){
                        posX += INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNRIGHT;
                    }
                    else {
                        if (directionCurve > 0.f){
                            currentDirection = TURNRIGHT;
                        }
                        else {
                            currentDirection = TURNLEFT;
                        }
                    }
                }
                else if (playerPosX >= 0.5) {
                    float offsetX = INCREMENT_X * speed / maxSpeed;
                    if (posX - offsetX >= -0.7f){
                        posX -= INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNLEFT;
                    }
                    else {
                        if (directionCurve > 0.f){
                            currentDirection = TURNRIGHT;
                        }
                        else {
                            currentDirection = TURNLEFT;
                        }
                    }
                }
                else {
                    if (posX > playerPosX) {
                        float offsetX = INCREMENT_X * speed / maxSpeed;
                        if (posX + offsetX <= 0.7f){
                            posX += INCREMENT_X * speed / maxSpeed;
                            currentDirection = TURNRIGHT;
                        }
                        else {
                            if (directionCurve > 0.f){
                                currentDirection = TURNRIGHT;
                            }
                            else {
                                currentDirection = TURNLEFT;
                            }
                        }
                    }
                    else {
                        float offsetX = INCREMENT_X * speed / maxSpeed;
                        if (posX - offsetX >= -0.7f){
                            posX -= INCREMENT_X * speed / maxSpeed;
                            currentDirection = TURNLEFT;
                        }
                        else {
                            if (directionCurve > 0.f){
                                currentDirection = TURNRIGHT;
                            }
                            else {
                                currentDirection = TURNLEFT;
                            }
                        }
                    }
                }
            }
            else if (typeAI == INCONSTANT){
                if (currentDirection == TURNRIGHT) {
                    const float prevPosX = posX;
                    posX += INCREMENT_X * speed / maxSpeed;

                    if (posX >= 0.7f){
                        currentDirection = TURNLEFT;
                    }
                    else if (((prevPosX < -0.5f && posX >= -0.5f) || (prevPosX < 0.0f && posX >= 0.0f) ||
                              (prevPosX < 0.5f && posX >= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    {
                        currentDirection = TURNRIGHT; // Lane change
                    }
                }
                else if (currentDirection == TURNLEFT) {
                    const float prevPosX = posX;
                    posX -= INCREMENT_X * speed / maxSpeed;

                    if (posX <= -0.7f){
                        currentDirection = TURNRIGHT;
                    }
                    else if (((prevPosX > -0.5f && posX <= -0.5f) || (prevPosX > 0.0f && posX <= 0.0f) ||
                              (prevPosX > 0.5f && posX <= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    {
                        currentDirection = TURNLEFT; // Lane change
                    }
                }
                else {
                    if (rand_generator_zero_one() <= 0.333f){
                        currentDirection = TURNRIGHT;
                    }
                    else if (rand_generator_zero_one() <= 0.666f){
                        currentDirection = TURNLEFT;
                    }
                    else {
                        currentDirection = RIGHT;
                    }
                }
            }
            else {
                // MANIAC
                if (vehicleDetected){
                    float p;
                    // Check the difficulty to control the speed of changing
                    switch(c.level){
                        case EASY:
                            p = rand_generator_zero_one();
                            if (p <= 0.5f){
                                const float direction = rand_generator_zero_one();
                                if (direction <= 0.5){
                                    if (posX < 0.f){
                                        posX += 0.01f;
                                    }
                                    else {
                                        posX -= 0.01f;
                                    }
                                }
                            }
                            break;
                        case NORMAL:
                            p = rand_generator_zero_one();
                            if (p <= 0.65f){
                                if (posX < 0.f){
                                    posX += 0.015f;
                                }
                                else {
                                    posX -= 0.015f;
                                }
                            }
                            break;
                        case HARD:
                            p = rand_generator_zero_one();
                            if (p <= 0.8f){
                                if (posX < 0.f){
                                    posX += 0.02f;
                                }
                                else {
                                    posX -= 0.02f;
                                }
                            }
                    }
                }
                else{
                    if (current_direction_counter < max_direction_counter) {
                        current_direction_counter++;
                    }
                     else {
                        max_direction_counter = rando_generator_zero_n(Vehicle_RivalCar::MAX_DIRECTION);
                        current_direction_counter = 0;
                        calculatedPath = randomDirection();
                    }

                    float newX = posX;
                    if (calculatedPath == TURNRIGHT)
                        newX += INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;
                    else if (calculatedPath == TURNLEFT)
                        newX -= INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;

                    if (newX < oriX - 0.15f || newX > oriX + 0.15f){
                        calculatedPath = RIGHT;
                    }
                    else {
                        posX = newX;
                    }
                    currentDirection = calculatedPath;
                }
            }
        }
        else {
            // Set and angle of turn for the curve
            if (abs(posX >= 0.f) && abs(posX) <= 0.3f){
                angleTurning = rand_generator_float(0.007f, 0.01f);
            }
            else if (abs(posX > 0.3f) && abs(posX) <= 0.7f){
                angleTurning = rand_generator_float(0.003f, 0.007f);
            }
            else {
                angleTurning = rand_generator_float(0.001f, 0.003f);
            }

            if (directionCurve > 0.f){
                currentDirection = TURNRIGHT;
            }
            else {
                currentDirection = TURNLEFT;
            }
            if (currentDirection == TURNRIGHT){
                if (abs(posX) + angleTurning < 0.7f){
                    posX += angleTurning;
                }
            }
            else if (currentDirection == TURNLEFT){
                if (abs(posX) + angleTurning < 0.7f){
                    posX -= angleTurning;
                }
            }
        }
    }

    // Update the speed of the vehicle
    const float acc = getAcceleration();

    // At the beginning all accelerate the same
    if (posY <= 90.f){
        // Increment speed of the rival car
        speed = sqrt(acc + ACCELERATION_INCREMENT);
        a = BOOT;
        smoking = true;
    }
    else {
        smoking = false;
        a = BOOT;
        // Avoid to reach impossible speeds only a 20 percent superior
        if (posY - playerPosY >= c.renderLen){
            // Each vehicle accelerates in a different mode
            if (speed <= 1.8f){
                speed = sqrt(acc + rand_generator_float(0.01f, 0.05f));
                if (speed < 1.8f){
                    speed = 1.8f;
                }
            }
            a = ACCELERATE;
        }
        // Avoid to reach impossible speeds only a 20 percent superior
        else if (posY - playerPosY > 0.f){
            // Each vehicle accelerates in a different mode
            float p = rand_generator_zero_one();
            if (p > 0.7f){
                if (playerSpeed < 1.6f){
                    if (speed <= 1.6f){
                        speed = sqrt(acc + rand_generator_float(0.01f, 0.03f)) * rand_generator_float(1.0f, 1.1f);
                        if (speed < 1.6f){
                            speed = 1.6f;
                        }
                    }
                }
                else {
                    if (speed <= 1.8f){
                        speed = sqrt(acc + rand_generator_float(0.01f, 0.03f)) * rand_generator_float(1.0f, 1.1f);
                        if (speed < 1.8f){
                            speed = 1.8f;
                        }
                    }
                }
            }
            a = ACCELERATE;
        }
        else if (playerPosY - posY < 100.f) {
            // Each vehicle accelerates in a different mode
            if (speed > 1.9f){
                speed = sqrt(acc + rand_generator_float(0.01f, 0.05f));
                if (speed > 1.9f){
                    speed = 1.9f;
                }
            }
            a = ACCELERATE;
        }
        else {
            // Each vehicle accelerates in a different mode
            float p = rand_generator_zero_one();
            if (p < 0.8f){
                    if (speed > 1.9f){
                    speed = sqrt(acc + rand_generator_float(0.01f, 0.05f));
                    if (speed > 1.9f){
                        speed = 1.9f;
                    }
                }
            }
            else {
                speed = lastSpeed;
            }
            a = ACCELERATE;
        }
        if (directionCurve != 0.f){
            if (posY > playerPosY){
                float powerBraking, power;
                int option = rand_generator_int(0, 2);
                if (abs(directionCurve) >= 1.2f && abs(directionCurve) <= 1.9f){
                    if (option == 1 && acc > 0.f){
                        powerBraking = rand_generator_float(0.001f, 0.01f);
                        if (speed >= 1.4f){
                            speed = sqrt(acc - powerBraking);
                            if (!fireSmoking && !firing){
                                smoking = true;
                            }
                        }
                        else {
                            speed = 1.4f;
                            smoking = false;
                        }
                    }
                }
                else if (abs(directionCurve) >= 0.8f && abs(directionCurve) < 1.2f){
                    if (option == 1 && acc > 0.f){
                        powerBraking = rand_generator_float(0.001f, 0.01f);
                        if (speed >= 1.5f){
                            speed = sqrt(acc - powerBraking);
                            if (!fireSmoking && !firing){
                                smoking = true;
                            }
                        }
                        else {
                            speed = 1.5f;
                            smoking = false;
                        }
                    }
                    else if (option == 2){
                        power = rand_generator_float(0.001f, 0.01f);
                        if (speed <= 1.6f){
                            speed = sqrt(acc + power);
                        }
                        else {
                            speed = 1.6f;
                        }
                    }
                }
                else if (abs(directionCurve) >= 0.3f && abs(directionCurve) < 0.8f){
                    if (option == 1 && acc > 0.f){
                        powerBraking = rand_generator_float(0.001f, 0.01f);
                        if (speed >= 1.7f){
                            speed = sqrt(acc - powerBraking);
                            if (!fireSmoking && !firing){
                                smoking = true;
                            }
                        }
                        else {
                            speed = 1.7f;
                            smoking = false;
                        }
                    }
                    else if (option == 2){
                        power = rand_generator_float(0.001f, 0.01f);
                        if (speed <= 1.8f){
                            speed = sqrt(acc + power);
                        }
                        else {
                            speed = 1.8f;
                        }
                    }
                }
            }
            a = BRAKE;
        }
    }
    // Advance the vehicle
    previousY = posY;
    posY += speed;
}



/**
 * Assign the type of AI depending of the difficult level
 * @param is the aggressiveness of the rival car
 * @param difficulty is the difficult level of the game
 * @param typeOfGame is the type of vehicle selected by the player
 */
void RivalCar::setAI(float maxAggressiveness, const Difficult& difficulty, const int typeOfGame) {
    // Control the level of aggressiveness of the rival car
    if (maxAggressiveness == 0.0f){
        probAI = 0.0f;
    }
    else {
        probAI = rand_generator_float(0.f, maxAggressiveness);
    }
    // Check if the mode is Driving Fury or Demarrage
    if (typeOfGame == 3 || typeOfGame == 4){
        // Maniac mode
        typeAI = MANIAC;
    }
    else {
        // The mode is World Tour or Pole Position
        const float p = rand_generator_zero_one();
        // Check the difficulty and choose a type or AI
        switch(difficulty){
        case EASY:
            if (p <= 0.4f) {
                typeAI = OBSTACLE;
            }
            else {
                typeAI = EVASIVE;
            }
            break;
        case NORMAL:
            if (p <= 0.5f) {
                typeAI = OBSTACLE;
            }
            else {
                typeAI = EVASIVE;
            }
            break;
        case HARD:
            if (p <= 0.7f) {
                typeAI = OBSTACLE;
                probAI *= 2.0f;
            }
            else {
                typeAI = EVASIVE;
            }
        }
    }
}



/**
 * Updates the sprite of the rival car
 * @param a is the last action registered of the rival car
 * @param e is the elevation of the terrain where is located the rival car
 */
void RivalCar::draw(const Action &a, const Elevation &e) {
    // Assign the counter to maintain the path
    if (smoking){
        maxCounterToChange = COUNTER + 1;
    }
    else {
        maxCounterToChange = COUNTER;
    }

    // Draw
    if (currentDirection != TURNLEFT){
        firstTurnLeft = true;
    }
    if (currentDirection != TURNRIGHT){
        firstTurnRight = true;
    }

    if (a != NONE) {
        if (counter_code_image >= maxCounterToChange) {
            counter_code_image = 0;

            if (speed > 0.0f || crashing)
                current_code_image++;

            if ((int)textures.size() == numTextures) {
                if (a == ACCELERATE || a == BOOT) {
                    if (e == FLAT) {
                        if (currentDirection == RIGHT) {
                            if (current_code_image < minTextureRight || current_code_image > maxTextureRight)
                                current_code_image = minTextureRight;
                        }
                        else if (currentDirection == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnLeft || current_code_image > maxTextureTurnLeft)
                                    current_code_image = minTextureTurnLeft;
                                if (current_code_image == medTurnLeft)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < medTurnLeft || current_code_image > maxTextureTurnLeft)
                                    current_code_image = medTurnLeft;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < minTextureTurnRight || current_code_image > maxTextureTurnRight)
                                    current_code_image = minTextureTurnRight;
                                if (current_code_image == medTurnRight)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < medTurnRight || current_code_image > maxTextureTurnRight)
                                    current_code_image = medTurnRight;
                            }
                        }
                    }
                     else if (e == UP) {
                        if (currentDirection == RIGHT) {
                            if (current_code_image < minTextureUp || current_code_image > maxTextureUp)
                                current_code_image = minTextureUp;
                        }
                        else if (currentDirection == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnLeftUp || current_code_image > maxTextureTurnLeftUp)
                                    current_code_image = minTextureTurnLeftUp;
                                if (current_code_image == medTurnLeftUp)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < medTurnLeftUp || current_code_image > minTextureTurnLeftUp)
                                    current_code_image = medTurnLeftUp;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < minTextureTurnRightUp || current_code_image > maxTextureTurnRightUp)
                                    current_code_image = minTextureTurnRightUp;
                                if (current_code_image == medTurnRightUp)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < medTurnRightUp || current_code_image > maxTextureTurnRightUp)
                                    current_code_image = medTurnRightUp;
                            }
                        }
                    }
                    else { // Down
                        if (currentDirection == RIGHT) {
                            if (current_code_image < minTextureRight || current_code_image > maxTextureRight)
                                current_code_image = minTextureRight;
                        }
                        else if (currentDirection == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnLeft || current_code_image > maxTextureTurnLeft)
                                    current_code_image = minTextureTurnLeft;
                                if (current_code_image == medTurnLeft)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < medTurnLeft || current_code_image > maxTextureTurnLeft)
                                    current_code_image = medTurnLeft;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < minTextureTurnRight || current_code_image > maxTextureTurnRight)
                                    current_code_image = minTextureTurnRight;
                                if (current_code_image == medTurnRight)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < medTurnRight || current_code_image > maxTextureTurnRight)
                                    current_code_image = medTurnRight;
                            }
                        }
                    }
                } else if (a == BRAKE) {
                    if (e == FLAT) {
                        if (currentDirection == RIGHT) {
                            if (current_code_image < minTextureRightBrake || current_code_image > maxTextureRightBrake)
                                current_code_image = minTextureRightBrake;
                        }
                        else if (currentDirection == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnLeftBrake || current_code_image > maxTextureTurnLeftBrake)
                                    current_code_image = minTextureTurnLeftBrake;
                                if (current_code_image == medTurnLeftBrake)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < medTurnLeftBrake || current_code_image > maxTextureTurnLeftBrake)
                                    current_code_image = medTurnLeftBrake;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < minTextureTurnRightBrake || current_code_image > maxTextureTurnRightBrake)
                                    current_code_image = minTextureTurnRightBrake;
                                if (current_code_image == medTurnRightBrake)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < medTurnRightBrake || current_code_image > maxTextureTurnRightBrake)
                                    current_code_image = medTurnRightBrake;
                            }
                        }
                    } else if (e == UP) {
                        if (currentDirection == RIGHT) {
                            if (current_code_image < minTextureUpBrake || current_code_image > maxTextureUpBrake)
                                current_code_image = minTextureUpBrake;
                        } else if (currentDirection == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnLeftBrakeUp || current_code_image > maxTextureTurnLeftBrakeUp)
                                    current_code_image = minTextureTurnLeftBrakeUp;
                                if (current_code_image == medTurnLeftBrakeUp)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < medTurnLeftBrakeUp || current_code_image > maxTextureTurnLeftBrakeUp)
                                    current_code_image = medTurnLeftBrakeUp;
                            }
                        } else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < minTextureTurnRightBrakeUp || current_code_image > maxTextureTurnRightBrakeUp)
                                    current_code_image = minTextureTurnRightBrakeUp;
                                if (current_code_image == medTurnRightBrakeUp)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < medTurnRightBrakeUp || current_code_image > maxTextureTurnRightBrakeUp)
                                    current_code_image = medTurnRightBrakeUp;
                            }
                        }
                    } else { // Down
                        if (currentDirection == RIGHT) {
                            if (current_code_image < minTextureRightBrake || current_code_image > maxTextureRightBrake)
                                current_code_image = minTextureRightBrake;
                        } else if (currentDirection == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnLeftBrake || current_code_image > maxTextureTurnLeftBrake)
                                    current_code_image = minTextureTurnLeftBrake;
                                if (current_code_image == medTurnLeftBrake)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < medTurnLeftBrake || current_code_image > maxTextureTurnLeftBrake)
                                    current_code_image = medTurnLeftBrake;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < minTextureTurnRightBrake || current_code_image > maxTextureTurnRightBrake)
                                    current_code_image = minTextureTurnRightBrake;
                                if (current_code_image == medTurnRightBrake)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < medTurnRightBrake || current_code_image > maxTextureTurnRightBrake)
                                    current_code_image = medTurnRightBrake;
                            }
                        }
                    }
                }
                else {
                    // Crash
                    switch(vehicleType){
                        case 0:
                            if (current_code_image < 46 || current_code_image > 58)
                                current_code_image = 46;
                            break;
                        case 1:
                            if (current_code_image < 37 || current_code_image > 44)
                                current_code_image = 37;
                            break;
                        case 2:
                            if (current_code_image < 29 || current_code_image > 36)
                                current_code_image = 29;
                            break;
                        case 3:
                            if (current_code_image < 55 || current_code_image > 62)
                                current_code_image = 55;
                            break;
                        case 4:
                            if (current_code_image < 45 || current_code_image > 53)
                                current_code_image = 45;
                            break;
                        case 5:
                            if (current_code_image < 25 || current_code_image > 37)
                                current_code_image = 25;
                    }
                }
            }
        }
        else {
            counter_code_image++;
        }
    }
    else {
        current_code_image = 1;
    }
}



/**
 * Establish the minimum coordinate in axis X occupied by the rival car
 * @param screenX is the minimum coordinate in axis X occupied by the rival car
 */
void RivalCar::setMinScreenX(float screenX) {
    minScreenX = screenX;
}



/**
 * Establish the maximum coordinate in axis X occupied by the rival car
 * @param screenX is the maximum coordinate in axis X occupied by the rival car
 */
void RivalCar::setMaxScreenX(float screenX) {
    maxScreenX = screenX;
}



/**
 * Returns the current texture of the rival car
 * @return
 */
const Texture *RivalCar::getCurrentTexture() const {
    return &textures[current_code_image - 1];
}



/**
 * Returns the scale factor of the rival car
 * @return
 */
float RivalCar::getScale() const {
    return scale;
}



/**
 * Returns the last position of the rival car in axis Y
 * @return
 */
float RivalCar::getPreviousY() const {
    return previousY;
}



/**
 * Returns the scaling factor of the rival car
 * @return
 */
float RivalCar::getScalingFactor() const {
    return scalingFactor;
}



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
bool RivalCar::hasCrashed(float prevY, float currentY, float minX, float maxX, float &crashPos) const {
    // Check if the path of the rival car is approximately the same path of the player's vehicle
    if (minScreenX != maxScreenX && ((prevY <= posY + 10.f && currentY >= posY - 10.f) ||
                                     (currentY <= posY + 10.f && prevY >= posY - 10.f)) && // y matches
        ((minX >= minScreenX && minX <= maxScreenX) ||
         (maxX >= minScreenX && maxX <= maxScreenX) ||
         (minScreenX >= minX && minScreenX <= maxX) ||
         (maxScreenX >= minX && maxScreenX <= maxX))) { // x matches
        // There is a crash between both cars
        crashPos = posY;
        return true;
    }
    // There is no crash
    return false;
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
bool RivalCar::isVisible(const Configuration &c, float minY, float playerX, float playerY, float &distanceX, float &distanceY) const {
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
 * Sets the rival car in straight direction
 */
void RivalCar::setOnStraight(){
    onStraight = true;
}



/**
 * Draw the smoking in the rival car
 * @param c is the configuration module of the game
 * @param destW is coordinate where the smoking is going to be drawn in axis X
 * @param destH s coordinate where the smoking is going to be drawn in axis Y
 * @param widthOri is the width dimension scaled of the image if the smoking
 * @param heightOri is the width dimension scaled of the image if the smoking
 * @param maxY is the destination coordinate in axis Y where the smoking
 */
void RivalCar::drawSmokingPlayer(Configuration& c, const float destW, const float destH, const float widthOri, const float heightOri,
                                 const float maxY)
{
    Sprite sv;
    switch(vehicleType){
        case 0:
            // Motorbike
            sv.setTexture(textures[41 + current_code_image % 4], true);
            break;
        case 1:
            // Devastator
            sv.setTexture(textures[52 + current_code_image % 4], true);
            break;
        case 2:
            // Minivan
            sv.setTexture(textures[44 + current_code_image % 4], true);
            break;
        case 3:
            // Truck
            sv.setTexture(textures[70 + current_code_image % 4], true);
            break;
        case 4:
            // Formula one
            sv.setTexture(textures[53 + current_code_image % 4], true);
            break;
        case 5:
            // Police
            sv.setTexture(textures[50 + current_code_image % 4], true);
    }
    // Calculate the scaled dimensions and draw in the screen
    sv.setScale(destW / widthOri, destH / heightOri);
    sv.setPosition(minScreenX - 5.f, maxY);
    c.w.draw(sv);
}



/**
 * Draw the fire in the rival car
 * @param c is the configuration module of the game
 * @param destW is coordinate where the fire is going to be drawn in axis X
 * @param destH s coordinate where the fire is going to be drawn in axis Y
 * @param widthOri is the width dimension scaled of the image if the fire
 * @param heightOri is the width dimension scaled of the image if the fire
 * @param maxY is the destination coordinate in axis Y where the fire
 */
void RivalCar::drawFirePlayer(Configuration& c, const float destW, const float destH, const float widthOri,
                              const float heightOri, const float maxY)
{
    Sprite sv;
    // Draw the texture depending of the rival car type
    switch(vehicleType){
        case 0:
            // Motorbike
            sv.setTexture(textures[80 + current_code_image % 4], true);
            break;
        case 1:
            // Devastator
            sv.setTexture(textures[77 + current_code_image % 4], true);
            break;
        case 2:
            // Minivan
            sv.setTexture(textures[69 + current_code_image % 4], true);
            break;
        case 3:
            // Truck
            sv.setTexture(textures[95 + current_code_image % 4], true);
            break;
        case 4:
            // Formula one
            sv.setTexture(textures[78 + current_code_image % 4], true);
            break;
    }
    // Calculate the scaled dimensions and draw in the screen
    sv.setScale(destW / widthOri, destH / heightOri);
    sv.setPosition(minScreenX - 35.f, maxY);
    c.w.draw(sv);
}



/**
 * Draw the smoking fire in the rival car
 * @param c is the configuration module of the game
 * @param destW is coordinate where the smoking fire is going to be drawn in axis X
 * @param destH s coordinate where the smoking fire is going to be drawn in axis Y
 * @param widthOri is the width dimension scaled of the image if the smoking fire
 * @param heightOri is the width dimension scaled of the image if the smoking fire
 * @param maxY is the destination coordinate in axis Y where the smoking fire
 */
void RivalCar::drawSmokingFirePlayer(Configuration& c, const float destW, const float destH, const float widthOri,
                                     const float heightOri, const float maxY)
{
    Sprite sv;
    // Draw the texture depending of the rival car type
    switch(vehicleType){
        case 0:
            // Motorbike
            sv.setTexture(textures[84 + current_code_image % 4], true);
            break;
        case 1:
            // Devastator
            sv.setTexture(textures[81 + current_code_image % 4], true);
            break;
        case 2:
            // Minivan
            sv.setTexture(textures[73 + current_code_image % 4], true);
            break;
        case 3:
            // Truck
            sv.setTexture(textures[99 + current_code_image % 4], true);
            break;
        case 4:
            // Formula One
            sv.setTexture(textures[82 + current_code_image % 4], true);
    }
    // Calculate the scaled dimensions and draw in the screen
    sv.setScale(destW / widthOri, destH / heightOri);
    sv.setPosition(minScreenX - 35.f, maxY);
    c.w.draw(sv);
}



/**
 * Get the type of vehicle of the rival car
 * @return
 */
int RivalCar::getVehicleType(){
    return vehicleType;
}



/**
 * Ser the rival car on fire
 * @param fire indicates if the rival is going to be on fired or not
 */
void RivalCar::setFiring(const bool fire){
    firing = fire;
}



/**
 * Returns if the rival car is on fire.
 * Otherwise returns false
 * @return
 */
bool RivalCar::getFiring(){
    return firing;
}



/**
 * Sets the smoking fire in the rival car
 * @param fireSmoke controls if the smoking fire has to be drawn or not
 */
void RivalCar::setFiringSmoke(const bool fireSmoke){
    fireSmoking = fireSmoke;
}



/**
 * Returns true if the rival car is starting to smoke and fire.
 * Otherwise returns false.
 * @return
 */
bool RivalCar::getFiringSmoke(){
    return fireSmoking;
}



/**
 * Returns if the rival is in the middle on the crash animation
 * @return
 */
bool RivalCar::inCrash(){
    // Check the type of vehicle
    switch(vehicleType){
        case 0:
            // Check if the current sprite of the rival car which is a motorbike
            // is in the middle of the crash animation
            if (current_code_image >= 46 && current_code_image <= 58){
                return true;
            }
            break;
        case 1:
            // Check if the current sprite of the rival car which is a devastator
            // is in the middle of the crash animation
            if (current_code_image >= 37 && current_code_image <= 44){
                return true;
            }
            break;
        case 2:
            // Check if the current sprite of the rival car which is a minivan
            // is in the middle of the crash animation
            if (current_code_image >= 29 && current_code_image <= 36){
                return true;
            }
            break;
        case 3:
            // Check if the current sprite of the rival car which is a truck
            // is in the middle of the crash animation
            if (current_code_image >= 55 && current_code_image <= 62){
                return true;
            }
            break;
        case 4:
            // Check if the current sprite of the rival car which is a Formula one
            // is in the middle of the crash animation
            if (current_code_image >= 45 && current_code_image <= 53){
                return true;
            }
            break;
        case 5:
            // Check if the current sprite of the rival car which is a police car
            // is in the middle of the crash animation
            if (current_code_image >= 25 && current_code_image <= 37){
                return true;
            }
    }
    return false;
}




