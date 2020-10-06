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
 * Module Motorbike implementation file
 */

#include "../include/Motorbike.h"



/**
 * Default constructor
 */
Motorbike::Motorbike(){}



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
Motorbike::Motorbike(float maxSpeed, float speedMul, float accInc, float scaleX, float scaleY, int maxCounterToChange,
                     const string &vehicle, float pX, float pY, const string brandName, const float angle,
                     const string motorName) : Vehicle(maxSpeed / speedMul, scaleX, maxCounterToChange,
                                                0.0f, pX, pX, pY, pY, 0, 0, vehicle, Motorbike_vehicle::PLAYER_TEXTURES, 1, 0),
                                                speedMul(speedMul), maxAcc(pow(maxSpeed / speedMul, 2.0f)), accInc(accInc),
                                                scaleY(scaleY), acceleration(0),
                                                minCrashAcc(0), xDest(1000), inertia(0), crashing(false),
                                                smoking(false), skidding(false),
                                                firstCrash(true), firstTurnLeft(true),
                                                firstTurnRight(true)
{
    topSpeed = maxSpeed;
    crashNow = false;
    brand = brandName;
    motor = motorName;
    angleTurning = angle;
    outSideRoad = false;
}



/**
 * Returns the last position of the motorbike in axis y
 * @return
 */
float Motorbike::getPreviousY() const {
    return previousY;
}



/**
 * Updates the crash logic of the motorbike and restores speed and acceleration
 * @param vehicleCrash true if it is a crash between vehicles
 */
void Motorbike::hitControl(const bool vehicleCrash) {

    // By default the motorbike is crashing
    crashing = true;

    // By default the motorbike is not smoking
    smoking = false;

    // By default the motorbike is not skidding
    skidding = false;

    // Check the speed of the motorbike when it crashes
    if (speedCollision == 0.f){
        // Get the speed of the motorbike
        speedCollision = getRealSpeed();
        // Move the motorbike while is crashing
        if (speedCollision < 60.f){
            posY = posY + 10.f;
        }
        else if (speedCollision < 140.f){
            posY = posY + 8.f;
        }
    }
    else {
        // Decrement the acceleration of the motorbike depending of the speed
        acceleration -= accInc * 2.5f;
        if (speed > 1.333f * halfMaxSpeed){
            acceleration -= accInc * 7.5f;
        }
        else if (speed > halfMaxSpeed){
            acceleration -= accInc * 5.0f;
        }
        else if (speed > 0.5f * halfMaxSpeed){
            acceleration -= accInc * 2.5f;
        }

        // Control the possible negative accelerations
        if (acceleration < 0.0f){
            acceleration = 0.0f;
        }

        // Calculation of the speed using the acceleration
        mainMutex.lock();
        speed = sqrt(acceleration);
        mainMutex.unlock();

        posY = posY + acceleration * 0.20f;
    }
    // Control the end of the crash animation of the motorbike
    if (current_code_image == 41){
        acceleration = minCrashAcc;
        speed = sqrt(acceleration);
        crashing = false;
        minCrashAcc = 0.0f;
        xDest = 1000;
        inertia = 0;
        previousY = posY;
        speedCollision = 0.0f;
        outSideRoad = false;
        posX = 0.0f;
    }
}



/**
 * Returns true if the motorbike is crashing. Otherwise returns false
 * @return
 */
bool Motorbike::isCrashing() const {
    return crashing;
}



/**
 * Returns the real speed of the motorbike
 * @return
 */
float Motorbike::getRealSpeed() const {
    return speed * speedMul;
}



/**
 * Updates the logic of the motorbike's acceleration and braking
 * @param c is the module configuration of the game
 * @param hasGotOut indicates if it's gone off track
 * @return
 */
Vehicle::Action Motorbike::accelerationControl(Configuration &c, bool hasGotOut) {

    // Default action
    Action a = NONE;
    smoking = false;

    // Store the current acceleration
    float previousAcc = acceleration;

    // Check if the braking control key has been pressed
    if (c.window.hasFocus() && Keyboard::isKeyPressed(c.brakeKey))
        // Motorbike brakes
        a = BRAKE;

    // Check if the accelerating key has been pressed
    if (a != BRAKE && c.window.hasFocus() && Keyboard::isKeyPressed(c.accelerateKey)) {
        // Check if the motorbike is outside the road
        if (hasGotOut) {
            outSideRoad = true;
            // The acceleration increases slower
            if (acceleration < maxAcc / 4.5f)
                acceleration += accInc / 3.0f;
            else
                acceleration -= accInc * 1.5f;
        }
        else {
            // The acceleration increases quicker
            outSideRoad = false;
            if (acceleration < maxAcc)
                acceleration += accInc;
        }

        // Control the limit of the acceleration
        if (acceleration > maxAcc)
            acceleration = maxAcc;

        // Check if the motorbike must start to smoke
        smoking = acceleration < maxAcc * 0.1f;
    } else {
        // The motorbike is braking
        float mul = 2.0f;

        // Reduces acceleration
        if (a == BRAKE)
            mul *= 2.0f;
        if (hasGotOut)
            mul *= 1.5f;

        if (acceleration > 0.0f)
            acceleration -= accInc * mul;

        if (acceleration < 0.0f)
            acceleration = 0.0f;
    }

    // Control if the motorbike is going to boot the motor
    if (previousAcc == 0.0f && acceleration > 0.0f)
        a = BOOT;
    else if (a == NONE && acceleration > 0.0f)
        // The motorbike accelerates because the rest of actions has not happened
        a = ACCELERATE;

    // Calculate the new speed of the motorbike
    mainMutex.lock();
    speed = sqrt(acceleration);
    mainMutex.unlock();

    // Control the advance of the motorbike in the landscape
    if (speed > 0.0f) {
        // Store the last position in axis y
        previousY = posY;
        // Store the new position using the current speed
        posY += speed;
        absPosY += speed;
    }
    return a;
}



/**
 * Updates the logic direction turn of the motorbike
 * @param c is the module configuration of the game
 * @param curveCoefficient is the coefficient curve
 * @param isFinalMap controls if the motorbike is circulating in the goal landscape or not
 * @param limitMap is the size of the landscape
 * @return
 */
Vehicle::Direction Motorbike::rotationControl(Configuration &c, float curveCoefficient, const bool& isFinalMap, const int& limitMap) {

    // The motorbike is not skidding by default
    skidding = false;
    if (speed > 0.0f) {
        // Check if it's the final landscape and it is near the goal
        if (isFinalMap && limitMap - posY <= 150.f){
            // Check if the motorbike is in the right of the road
            if (posX > 0.f){
                previousX = posX;
                posX -= 0.02f;
                if (posX < 0.0f){
                    // Centered in the middle of the road
                    posX = 0.0f;
                }
            }
            // Check if the motorbike is in the left of the road
            else if (posX < 0.0f) {
                previousX = posX;
                posX += 0.02f;
                if (posX > 0.0f){
                    // Centered in the middle of the road
                    posX = 0.0f;
                }
            }
        }
        else {

            // Decrement the position in axis x using the maximum speed and the acceleration
            if (speed < 0.66f * maxSpeed){
                previousX = posX;
                posX -= angleTurning * curveCoefficient * sqrt(speed / 2.0f) * speed / maxSpeed;
            }
            else {
                previousX = posX;
                posX -= angleTurning * curveCoefficient * sqrt(speed) * speed / maxSpeed;
            }

            // Check if the motorbike has to start to skid
            if (abs(curveCoefficient) >= 0.33f && speed >= 0.66f * maxSpeed)
                skidding = true;

            // Control if the turning left control key has been pressed
            if (c.window.hasFocus() && Keyboard::isKeyPressed(c.leftKey)) {

                // Measure the effect of the inertia force
                if (inertia > -Motorbike_vehicle::FORCE_INERTIA)
                    inertia--;

                // The inertia force makes the motorbike skid
                if (inertia < 0) {
                    if (curveCoefficient > 0.0f)
                        skidding = false;

                    // Control the position in axis x
                    if (speed < halfMaxSpeed){
                        previousX = posX;
                        posX -= 1.5f * angleTurning * speed / maxSpeed;
                    }
                    else if (curveCoefficient == 0.0f){
                        previousX = posX;
                        posX -= 1.25f * angleTurning * speed / maxSpeed;
                    }
                    else {
                        previousX = posX;
                        posX -= angleTurning * speed / maxSpeed;
                    }

                    // Motorbike turns left
                    return TURNLEFT;
                }
            }
            // Control if the turning right control key has been pressed
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(c.rightKey)) {

                // Measure the effect of the inertia force
                if (inertia < Motorbike_vehicle::FORCE_INERTIA)
                    inertia++;

                // The inertia force makes the motorbike skid
                if (inertia > 0) {
                    if (curveCoefficient < 0.0f)
                        skidding = false;

                    // Control the position in axis x
                    if (speed < halfMaxSpeed){
                        previousX = posX;
                        posX += 1.5f * angleTurning * speed / maxSpeed;
                    }
                    else if (curveCoefficient == 0.0f){
                        previousX = posX;
                        posX += 1.25f * angleTurning * speed / maxSpeed;
                    }
                    else {
                        previousX = posX;
                        posX += angleTurning * speed / maxSpeed;
                    }

                    // Motorbike turns right
                    return TURNRIGHT;
                }
            } else if (inertia > 0) {
                inertia--;
            } else if (inertia < 0) {
                inertia++;
            }

            skidding = false;
        }
    }
    // Motorbike goes right
    return RIGHT;
}



/**
 * Updates the motorbike's sprite and draws it in the screen
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 * @param a is the action to be done by the motorbike
 * @param d is the direction to be followed by the motorbike
 * @param e is the current elevation of the motorbike in the landscape
 * @param enableSound indicates if the motor of the motorbike has to make noise
 */
void Motorbike::draw(Configuration &c, SoundPlayer &r, const Action &a, const Direction &d,
                    const Elevation &e, int terrain, bool enableSound)
{
    // Sound effects
    if (a != CRASH)
        firstCrash = true;

    // Control the sounds of the motorbike
    if (enableSound) {
        if (speed > 0.0f) {
            if (a == BOOT) {
                // Acceleration sound
                r.soundEffects[30]->stop();
                r.soundEffects[30]->play();
            }
            if (r.soundEffects[31]->getStatus() != SoundSource::Playing) {
                // Engine sound
                r.soundEffects[31]->stop();
                r.soundEffects[31]->play();
            }
            r.soundEffects[31]->setVolume((33.0f + 67.0f * speed / maxSpeed) * float(r.volumeEffects) / 100.f);
            if (skidding && r.soundEffects[8]->getStatus() != SoundSource::Playing) {
                // Skidding sound
                r.soundEffects[8]->stop();
                r.soundEffects[8]->play();
            }
            if (outSideRoad && r.soundEffects[53]->getStatus() != SoundSource::Playing) {
                // Outside sound
                r.soundEffects[53]->stop();
                r.soundEffects[53]->play();
            }
            else if (!outSideRoad && r.soundEffects[53]->getStatus() == SoundSource::Playing){
                // Outside sound
                r.soundEffects[53]->stop();
            }
        }
        else {
            r.soundEffects[12]->stop();
            r.soundEffects[31]->stop();
            r.soundEffects[8]->stop();
            r.soundEffects[53]->stop();
        }

        if (a == CRASH && firstCrash) {
            firstCrash = false;
            r.soundEffects[32]->stop();
            r.soundEffects[18]->stop();
            r.soundEffects[19]->stop();
            r.soundEffects[32]->play();
            r.soundEffects[rand_generator_int(18, 19)]->play();
        }
    }
    else {
        r.soundEffects[12]->stop();
        r.soundEffects[31]->stop();
        r.soundEffects[8]->stop();
        r.soundEffects[53]->stop();
        r.soundEffects[32]->stop();
        r.soundEffects[18]->stop();
        r.soundEffects[19]->stop();
    }

    // Draw
    if (d != TURNLEFT){
        firstTurnLeft = true;
    }
    if (d != TURNRIGHT){
        firstTurnRight = true;
    }


    multiplayerMutex.lock();

    // Check the current action of the motorbike to be drawn in the screen
    if (a != NONE) {
        if (counter_code_image >= maxCounterToChange) {
            counter_code_image = 0;

            // Increment the texture counter only if it moves
            if (speed > 0.0f){
                if (crashing){
                    // Change the number of textures to display the sprite slower
                    current_code_image++;
                    maxCounterToChange = 5;
                }
                else {
                    // Change the number of textures to display the sprite quicker
                    current_code_image++;
                    maxCounterToChange = COUNTER;
                }
            }
            else if (crashing){
                // Change the number of textures to display the sprite slower
                current_code_image++;
                maxCounterToChange = 5;
            }
            else {
                // Change the number of textures to display the sprite quicker
                maxCounterToChange = COUNTER;
            }

            if (textures.size() == Motorbike_vehicle::PLAYER_TEXTURES) {
                if (a == ACCELERATE || a == BOOT) {
                    if (e == FLAT) {
                        if (d == RIGHT) {
                            if (current_code_image < 1 || current_code_image > 2)
                                current_code_image = 1;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 3 || current_code_image > 8)
                                    current_code_image = 3;
                                if (current_code_image == 7)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 7 || current_code_image > 8)
                                    current_code_image = 7;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 9 || current_code_image > 14)
                                    current_code_image = 9;
                                if (current_code_image == 13)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 13 || current_code_image > 14)
                                    current_code_image = 13;
                            }
                        }
                    }
                     else if (e == UP) {
                        if (d == RIGHT) {
                            if (current_code_image < 1 || current_code_image > 2)
                                current_code_image = 1;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 3 || current_code_image > 8)
                                    current_code_image = 3;
                                if (current_code_image == 7)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 7 || current_code_image > 8)
                                    current_code_image = 7;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 9 || current_code_image > 14)
                                    current_code_image = 9;
                                if (current_code_image == 13)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 13 || current_code_image > 14)
                                    current_code_image = 13;
                            }
                        }
                    }
                    else { // Down
                        if (d == RIGHT) {
                            if (current_code_image < 1 || current_code_image > 2)
                                current_code_image = 1;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 3 || current_code_image > 8)
                                    current_code_image = 3;
                                if (current_code_image == 7)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 7 || current_code_image > 8)
                                    current_code_image = 7;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 9 || current_code_image > 14)
                                    current_code_image = 9;
                                if (current_code_image == 13)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 13 || current_code_image > 14)
                                    current_code_image = 13;
                            }
                        }
                    }
                } else if (a == BRAKE) {
                    if (e == FLAT) {
                        if (d == RIGHT) {
                            if (current_code_image < 15 || current_code_image > 16)
                                current_code_image = 15;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 17 || current_code_image > 22)
                                    current_code_image = 17;
                                if (current_code_image == 21)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 21 || current_code_image > 22)
                                    current_code_image = 21;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 23 || current_code_image > 28)
                                    current_code_image = 23;
                                if (current_code_image == 27)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 27 || current_code_image > 28)
                                    current_code_image = 27;
                            }
                        }
                    } else if (e == UP) {
                        if (d == RIGHT) {
                            if (current_code_image < 15 || current_code_image > 16)
                                current_code_image = 15;
                        } else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 17 || current_code_image > 22)
                                    current_code_image = 17;
                                if (current_code_image == 21)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 21 || current_code_image > 22)
                                    current_code_image = 21;
                            }
                        } else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 23 || current_code_image > 28)
                                    current_code_image = 23;
                                if (current_code_image == 27)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 27 || current_code_image > 28)
                                    current_code_image = 27;
                            }
                        }
                    } else { // Down
                        if (d == RIGHT) {
                            if (current_code_image < 15 || current_code_image > 16)
                                current_code_image = 15;
                        } else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 17 || current_code_image > 22)
                                    current_code_image = 17;
                                if (current_code_image == 21)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 21 || current_code_image > 22)
                                    current_code_image = 21;
                            }
                        } else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 23 || current_code_image > 28)
                                    current_code_image = 23;
                                if (current_code_image == 27)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 27 || current_code_image > 28)
                                    current_code_image = 27;
                            }
                        }
                    }
                }
                else {
                    // The motorbike is crashing
                    if (current_code_image < 29 || current_code_image > 41)
                        current_code_image = 29;
                }
            }
        }
        else {
            // Increment the code of the motorbike texture to be drawn
            counter_code_image++;
        }
    }
    else {
        // Default code when the motorbike does not move
        current_code_image = 1;
    }

    multiplayerMutex.unlock();

    // Draw the motorbike in the screen adapted to the current screen resolution and pixel art effect
    sprite.setTexture(textures[current_code_image - 1], true);
    sprite.setScale(scale * c.screenScale, scaleY * c.screenScale);
    minScreenX = ((float) c.w.getSize().x) / 2.0f - sprite.getGlobalBounds().width / 2.0f;
    maxScreenX = minScreenX + sprite.getGlobalBounds().width;
    if (c.isDefaultScreen){
        sprite.setPosition(minScreenX, ((float) c.w.getSize().y) * c.camD - sprite.getGlobalBounds().height / 2.0f);
    }
    else {
        if (c.enablePixelArt){
            sprite.setPosition(minScreenX, ((float) c.w.getSize().y) * c.camD - sprite.getGlobalBounds().height / 2.0f - 15.f);
        }
        else {
            sprite.setPosition(minScreenX, ((float) c.w.getSize().y) * c.camD - sprite.getGlobalBounds().height / 2.0f - 30.f);
        }
    }
    c.w.draw(sprite);


    // Check if the motorbike is skidding or smoking
    if (smoking || skidding) {
        // Accelerate the counter of changing the sprite
        maxCounterToChange = COUNTER + 1;
        const float j = sprite.getPosition().y + sprite.getGlobalBounds().height;
        sprite.setTexture(textures[41 + current_code_image % 4], true);
        sprite.setScale(3.f * c.screenScale, 3.5f * c.screenScale);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f - sprite.getGlobalBounds().width,
                           j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f, j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
    }
    else if (crashing){
        // Give it a value depending of the speed of the devastator
        if (getRealSpeed() < 20.f){
            maxCounterToChange = COUNTER + 6;
        }
        else if (getRealSpeed() >= 20.f && getRealSpeed() < 60.f){
            maxCounterToChange = COUNTER + 5;
        }
        else if (getRealSpeed() >= 60.f && getRealSpeed() < 100.f){
            maxCounterToChange = COUNTER + 3;
        }
        else if (getRealSpeed() >= 100.f && getRealSpeed() < 120.f){
            maxCounterToChange = COUNTER + 2;
        }
        else if (getRealSpeed() >= 120.f){
            maxCounterToChange = COUNTER + 1;
        }
    }
    // Draw the smoke effect of the motorbike
    else if (outSideRoad && speed != 0.f){
        // Must raise land
        maxCounterToChange = COUNTER;
        const float j = sprite.getPosition().y + sprite.getGlobalBounds().height;
        switch(terrain){
        case 0:
            // Grass
            sprite.setTexture(textures[66 + current_code_image % 8], true);
            break;
        case 1:
            // Land
            sprite.setTexture(textures[60 + current_code_image % 6], true);
            break;
        case 2:
            // Snow
            sprite.setTexture(textures[74 + current_code_image % 6], true);
        }
        sprite.setScale(3.f * c.screenScale, 3.5f * c.screenScale);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f - sprite.getGlobalBounds().width,
                           j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f, j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
    }
    else if (!crashing) {
        // Make the motorbike change the sprite quickly
        maxCounterToChange = COUNTER;
    }
}



/**
 * It forces the motorbike to be smoking or not
 * @param smoke indicates if the motorbike has to make smoke or not
 */
void Motorbike::setSmoking(bool smoke) {
    smoking = smoke;
}



/**
 * Set the speed of the vehicle to zero
 */
void Motorbike::setSpeed(){
    Vehicle::setSpeed();
}



/**
 * Initialize the properties of the devastator depending of the game mode
 * selected by the player
 * @param typeOfGame is the game mode selected by the player
 * @param onMultiplayer control if the game is in multi player mode or not
 * @param codePlayerInGroup is the identifier code of the player in the multi player group
 * @param numRivals is the number of rivals in the multi player mode
 */
void Motorbike::setVehicle(const int typeOfGame, const bool onMultiplayer, const int codePlayerInGroup, const int numRivals){
    Vehicle::setVehicle(typeOfGame, onMultiplayer, codePlayerInGroup, numRivals);
    acceleration = 0.0f;
    minCrashAcc = 0.0f;
    inertia = 0.0f;
    accInc = topSpeed * ACCELERATION_INCREMENT / MAX_SPEED;
    smoking = false;
    skidding = false;
    firstCrash = true;
    firstTurnLeft = true;
    firstTurnRight = true;
}



/**
 * Returns the half speed that can be reached by the motorbike
 * @return
 */
float Motorbike::getHalfMaxSpeed(){
    return halfMaxSpeed;
}



/**
 * Returns the brand name of the motorbike
 * @return
 */
string Motorbike::getBrandName(){
    return brand;
}



/**
 * Returns the angle of turning of the motorbike
 * @return
 */
float Motorbike::getAngle(){
    return angleTurning;
}



/**
 * Returns the motor's name of the motorbike
 * @return
 */
string Motorbike::getMotorName(){
    return motor;
}



/**
 * Returns the maximum speed reached by the motorbike
 * @return
 */
float Motorbike::getTopSpeed(){
    return topSpeed;
}



/**
 * Returns the current code of the sprite of the vehicle to draw
 * @return
 */
int Motorbike::getCurrentCodeImage() const {
    return Vehicle::getCurrentCodeImage();
}

