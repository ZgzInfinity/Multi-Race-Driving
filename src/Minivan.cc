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
 * Module Minivan implementation file
 */

#include "../include/Minivan.h"



/**
 * Default constructor
 */
Minivan::Minivan(){}



/**
 * Initialize the minivan chosen by the player
 * @param maxSpeed is the maximum speed that the minivan can reach
 * @param speedMul is factor number that when it is multiplied by speed obtains the real speed
 * @param accInc is the acceleration increment
 * @param scaleX is the scaling factor in the axis x
 * @param scaleY is the scaling factor in the axis y
 * @param maxCounterToChange lets to update the sprite of the minivan that is drawn in the screen
 * @param vehicle is the type of vehicle selected by the player
 * @param pX is the position of the player in the axis x
 * @param pY is the position of the player in the axis y
 */
Minivan::Minivan(float maxSpeed, float speedMul, float accInc, float scaleX, float scaleY, int maxCounterToChange,
                       const string &vehicle, float pX, float pY, const string brandName, const float angle,
                       const string motorName) : Vehicle(maxSpeed / speedMul, scaleX, maxCounterToChange,
                                                 0.0f, pX, pX, pY, pY, 0, 0, vehicle, Minivan_vehicle::PLAYER_TEXTURES, 1, 0),
                                                 speedMul(speedMul), maxAcc(pow(maxSpeed / speedMul, 2.0f)),
                                                 accInc(accInc), scaleY(scaleY), acceleration(0),
                                                 minCrashAcc(0), xDest(1000), inertia(0), crashing(false),
                                                 smoking(false), skidding(false),
                                                 firstCrash(true), firstTurnLeft(true),
                                                 firstTurnRight(true)
{
    topSpeed = maxSpeed;
    mode = -1;
    brand = brandName;
    motor = motorName;
    angleTurning = angle;
    speedCollision = 0.f;
    outSideRoad = false;
}



/**
 * Returns the last position of the minivan in axis y
 * @return
 */
float Minivan::getPreviousY() const {
    return previousY;
}



/**
 * Updates the crash logic of the minivan and restores speed and acceleration
 * @param vehicleCrash true if it is a crash between vehicles
 */
void Minivan::hitControl(const bool vehicleCrash) {

    // By default the minivan is crashing
    crashing = true;

    // By default the minivan is not smoking
    smoking = false;

    // By default the minivan is not skidding
    skidding = false;

    // Check the speed when starts the crash if has not been stored
    if (speedCollision == 0.f){
        // Store the speed
        speedCollision = getRealSpeed();
    }

    // Calculation of the position in axis x where finish the crash
    if (xDest == 1000.f){
        // Check the side of the track where the crash happens
        if (posX > 0.f){
            // The minivan goes to the left
            xDest = -(acceleration * 1.7f / maxAcc);

        }
        else {
            // The minivan goes to the right
            xDest = acceleration * 1.7f / maxAcc;
        }
    }

    // Check the destination coordinate in axis x of the crash
    if (xDest > 0.f){
        // Increment to the right depending if the speed of the minivan
        if (speedCollision <= 40.f){
            posX = posX + (acceleration * angleTurning / maxAcc) * 40.f;
        }
        else if (speedCollision > 40.f && speedCollision < 85.f){
            posX = posX + (acceleration * angleTurning / maxAcc) * 20.f;
        }
        else if (speedCollision >= 85.f && speedCollision < 100.f){
            posX = posX + (acceleration * angleTurning / maxAcc) * 10.f;
        }
        else if (speedCollision >= 100.f && speedCollision < 120.f){
            posX = posX + (acceleration * angleTurning / maxAcc) * 5.f;
        }
        else {
            posX = posX + (acceleration * angleTurning / maxAcc) * 1.5f;
        }
    }
    else {
        // Increment to the left depending if the speed of the minivan
        if (speedCollision <= 40.f){
            posX = posX - (acceleration * angleTurning / maxAcc) * 40.f;
        }
        else if (speedCollision > 40.f && speedCollision <= 85.f){
            posX = posX - (acceleration * angleTurning / maxAcc) * 20.f;
        }
        else if (speedCollision > 85.f && speedCollision < 100.f){
            posX = posX - (acceleration * angleTurning / maxAcc) * 10.f;
        }
        else if (speedCollision >= 100.f && speedCollision < 120.f){
            posX = posX - (acceleration * angleTurning / maxAcc) * 5.f;
        }
        else {
            posX = posX - (acceleration * angleTurning / maxAcc) * 1.5f;
        }
    }

    // Check if the crash is against another car
    if (vehicleCrash){
        if (minCrashAcc <= 0.f) {
            // Only first time reduces the speed and the acceleration
            minCrashAcc = (speed * 0.1555f) * (speed * 0.1555f);
            acceleration = (speed * 0.75f) * (speed * 0.75f);
        }
    }

    // Decrement the acceleration
    acceleration -= accInc * 2.5f;

    // Reduce the acceleration in minor quantities each time
    if (speed > 1.333f * halfMaxSpeed){
        acceleration -= accInc * 7.5f;
    }
    else if (speed > halfMaxSpeed){
        acceleration -= accInc * 5.0f;
    }
    else if (speed > 0.5f * halfMaxSpeed){
        acceleration -= accInc * 2.5f;
    }

    // Avoid negative acceleration
    if (acceleration < 0.0f){
        acceleration = 0.0f;
    }

    // Calculate the speed of the minivan using its acceleration
    mainMutex.lock();
    speed = sqrt(acceleration);
    mainMutex.unlock();

    // Control the movement in the axis y
    if (xDest > 0.f && posX < xDest){
        // Check the crash has been with an element of the map
        // or with another car
        if (!vehicleCrash){
            // Crash with element of map and minivan moves forward
            posY = posY + acceleration * 7.f / maxAcc;
        }
        else {
            // Crash with element of map and minivan moves backwards
            posY = posY - acceleration * 7.f / maxAcc;
        }
    }
    else if (xDest < 0.f && posX > xDest) {
        // Check the crash has been with an element of the map
        // or with another car
        if (!vehicleCrash){
            // Crash with element of map and minivan moves forward
            posY = posY + acceleration * 7.f / maxAcc;
        }
        else {
            // Crash with element of map and minivan moves backwards
            posY = posY - acceleration * 7.f / maxAcc;
        }
    }

    // Control if the crash animation has been finished
    if (acceleration <= minCrashAcc){
        acceleration = minCrashAcc;
        speed = sqrt(acceleration);
        crashing = false;
        minCrashAcc = 0.0f;
        xDest = 1000;
        inertia = 0;
        previousY = posY;
        mode = -1;
        speedCollision = 0.0f;
        outSideRoad = false;
    }
}



/**
 * Returns true if the minivan is crashing. Otherwise returns false
 * @return
 */
bool Minivan::isCrashing() const {
    return crashing;
}



/**
 * Returns the real speed of the minivan
 * @return
 */
float Minivan::getRealSpeed() const {
    return speed * speedMul;
}



/**
 * Updates the logic of the minivan's acceleration and braking
 * @param c is the module configuration of the game
 * @param hasGotOut indicates if it's gone off track
 * @return
 */
Vehicle::Action Minivan::accelerationControl(Configuration &c, bool hasGotOut) {

    // Default action
    Action a = NONE;
    smoking = false;

    // Store the current acceleration
    float previousAcc = acceleration;

    // Check if the braking control key has been pressed
    if (c.window.hasFocus() && Keyboard::isKeyPressed(c.brakeKey))
        // Minivan brakes
        a = BRAKE;

    // Check if the accelerating key has been pressed
    if (a != BRAKE && c.window.hasFocus() && Keyboard::isKeyPressed(c.accelerateKey)) {
        // Check if the minivan is outside the road
        if (hasGotOut) {
            outSideRoad = true;
            // The acceleration increases slower
            if (acceleration < maxAcc / 4.5f)
                acceleration += accInc / 3.0f;
            else
                acceleration -= accInc * 1.5f;
        } else {
            // The acceleration increases quicker
            outSideRoad = false;
            if (acceleration < maxAcc)
                acceleration += accInc;
        }

        // Control the limit of the acceleration
        if (acceleration > maxAcc)
            acceleration = maxAcc;

        // Check if the minivan must start to smoke
        smoking = acceleration < maxAcc * 0.1f;
    }
    else {
        // The minivan is braking
        float mul = 2.0f;
        if (a == BRAKE)
            mul *= 2.0f;
        if (hasGotOut)
            mul *= 1.5f;

        if (acceleration > 0.0f)
            acceleration -= accInc * mul;

        if (acceleration < 0.0f)
            acceleration = 0.0f;
    }

    // Control if the minivan is going to boot the motor
    if (previousAcc == 0.0f && acceleration > 0.0f)
        a = BOOT;
    else if (a == NONE && acceleration > 0.0f)
        // The minivan accelerates because the rest of actions has not happened
        a = ACCELERATE;

    // Calculate the new speed of the minivan
    mainMutex.lock();
    speed = sqrt(acceleration);
    mainMutex.unlock();

    // Control the advance of the minivan in the landscape
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
 * Updates the logic direction turn of the minivan
 * @param c is the module configuration of the game
 * @param curveCoefficient is the coefficient curve
 * @param isFinalMap controls if the minivan is circulating in the goal landscape or not
 * @param limitMap is the size of the landscape
 * @return
 */
Vehicle::Direction Minivan::rotationControl(Configuration &c, float curveCoefficient, const bool& isFinalMap, const int& limitMap) {

    // The minivan is not skidding by default
    skidding = false;

    if (speed > 0.0f) {
        // Check if it's the final landscape and it is near the goal
        if (isFinalMap && limitMap - posY <= 150.f){
            // Check if the minivan is in the right of the road
            if (posX > 0.f){
                posX -= 0.02f;
                if (posX < 0.0f){
                    // Centered in the middle of the road
                    posX = 0.0f;
                }
            }
            // Check if the minivan is in the right of the road
            else if (posX < 0.0f) {
                posX += 0.02f;
                if (posX > 0.0f){
                    // Centered in the middle of the road
                    posX = 0.0f;
                }
            }
        }
        else {

            // Decrement the position in axis x using the maximum speed and the acceleration
            if (speed < 0.66f * maxSpeed)
                posX -= angleTurning * curveCoefficient * sqrt(speed / 2.0f) * speed / maxSpeed;
            else
                posX -= angleTurning * curveCoefficient * sqrt(speed) * speed / maxSpeed;

            // Check if the minivan has to start to skid
            if (abs(curveCoefficient) >= 0.33f && speed >= 0.66f * maxSpeed)
                skidding = true;

            // Control if the turning left control key has been pressed
            if (c.window.hasFocus() && Keyboard::isKeyPressed(c.leftKey)) {

                // Measure the effect of the inertia force
                if (inertia > -Minivan_vehicle::FORCE_INERTIA)
                    inertia--;

                // The inertia force makes the minivan skid
                if (inertia < 0) {
                    if (curveCoefficient > 0.0f)
                        skidding = false;

                    // Control the position in axis x
                    if (speed < halfMaxSpeed)
                        posX -= 1.5f * angleTurning * speed / maxSpeed;
                    else if (curveCoefficient == 0.0f)
                        posX -= 1.25f * angleTurning * speed / maxSpeed;
                    else
                        posX -= angleTurning * speed / maxSpeed;

                    // Minivan turns left
                    return TURNLEFT;
                }
            }
            // Control if the turning right control key has been pressed
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(c.rightKey)) {

                // Measure the effect of the inertia force
                if (inertia < Minivan_vehicle::FORCE_INERTIA)
                    inertia++;

                // The inertia force makes the minivan skid
                if (inertia > 0) {
                    if (curveCoefficient < 0.0f)
                        skidding = false;

                    // Control the position in axis x
                    if (speed < halfMaxSpeed)
                        posX += 1.5f * angleTurning * speed / maxSpeed;
                    else if (curveCoefficient == 0.0f)
                        posX += 1.25f * angleTurning * speed / maxSpeed;
                    else
                        posX += angleTurning * speed / maxSpeed;

                    // Minivan turns right
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
    // Minivan goes right
    return RIGHT;
}



/**
 * Updates the minivan's sprite and draws it in the screen
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 * @param a is the action to be done by the minivan
 * @param d is the direction to be followed by the minivan
 * @param e is the current elevation of the minivan in the landscape
 * @param enableSound indicates if the motor of the minivan has to make noise
 */
void Minivan::draw(Configuration &c, SoundPlayer &r, const Action &a, const Direction &d,
                  const Elevation &e, int terrain, bool enableSound)
{
    // Sound effects
    if (a != CRASH)
        firstCrash = true;

    // Control the sounds of the minivan
    if (enableSound) {
        if (speed > 0.0f) {
            if (a == BOOT) {
                // Acceleration sound
                r.soundEffects[41]->stop();
                r.soundEffects[41]->play();
            }
            if (r.soundEffects[42]->getStatus() != SoundSource::Playing) {
                // Engine sound
                r.soundEffects[42]->stop();
                r.soundEffects[42]->play();
            }
            r.soundEffects[42]->setVolume((33.0f + 67.0f * speed / maxSpeed) * float(r.volumeEffects) / 100.f);
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
            r.soundEffects[41]->stop();
            r.soundEffects[42]->stop();
            r.soundEffects[8]->stop();
            r.soundEffects[53]->stop();
        }

        if (a == CRASH && firstCrash) {
            firstCrash = false;
            r.soundEffects[17]->stop();
            r.soundEffects[18]->stop();
            r.soundEffects[19]->stop();
            r.soundEffects[17]->play();
            r.soundEffects[rand_generator_int(18, 19)]->play();
            if (r.soundEffects[52]->getStatus() != SoundSource::Playing) {
                // Engine sound
                r.soundEffects[52]->stop();
                r.soundEffects[52]->play();
            }
        }
    }
    else {
        r.soundEffects[41]->stop();
        r.soundEffects[42]->stop();
        r.soundEffects[8]->stop();
        r.soundEffects[53]->stop();
        r.soundEffects[17]->stop();
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

    // Check the current action of the minivan to be drawn in the screen
    if (a != NONE) {
        if (counter_code_image >= maxCounterToChange) {
            counter_code_image = 0;

            // Increment the texture counter only if it moves
            if (speed > 0.0f)
                current_code_image++;

            if (textures.size() == Minivan_vehicle::PLAYER_TEXTURES) {
                if (a == ACCELERATE || a == BOOT) {
                    if (e == FLAT) {
                        if (d == RIGHT) {
                            if (current_code_image < 1 || current_code_image > 2)
                                current_code_image = 1;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 3 || current_code_image > 5)
                                    current_code_image = 3;
                                if (current_code_image == 3)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 3 || current_code_image > 5)
                                    current_code_image = 3;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 6 || current_code_image > 8)
                                    current_code_image = 6;
                                if (current_code_image == 6)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 6 || current_code_image > 8)
                                    current_code_image = 6;
                            }
                        }
                    }
                     else if (e == UP) {
                        if (d == RIGHT) {
                            if (current_code_image < 9 || current_code_image > 10)
                                current_code_image = 9;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 11 || current_code_image > 12)
                                    current_code_image = 11;
                                if (current_code_image == 11)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 11 || current_code_image > 12)
                                    current_code_image = 11;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 13 || current_code_image > 14)
                                    current_code_image = 13;
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
                                if (current_code_image < 3 || current_code_image > 5)
                                    current_code_image = 3;
                                if (current_code_image == 3)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 3 || current_code_image > 5)
                                    current_code_image = 3;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 6 || current_code_image > 8)
                                    current_code_image = 6;
                                if (current_code_image == 6)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 6 || current_code_image > 8)
                                    current_code_image = 6;
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
                                if (current_code_image < 17 || current_code_image > 19)
                                    current_code_image = 17;
                                if (current_code_image == 17)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 17 || current_code_image > 19)
                                    current_code_image = 17;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 20 || current_code_image > 22)
                                    current_code_image = 20;
                                if (current_code_image == 20)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 20 || current_code_image > 22)
                                    current_code_image = 20;
                            }
                        }
                    } else if (e == UP) {
                        if (d == RIGHT) {
                            if (current_code_image < 23 || current_code_image > 24)
                                current_code_image = 23;
                        } else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 25 || current_code_image > 26)
                                    current_code_image = 25;
                                if (current_code_image == 25)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 25 || current_code_image > 26)
                                    current_code_image = 25;
                            }
                        } else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 27 || current_code_image > 28)
                                    current_code_image = 27;
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
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 17 || current_code_image > 19)
                                    current_code_image = 17;
                                if (current_code_image == 17)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 17 || current_code_image > 19)
                                    current_code_image = 17;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 20 || current_code_image > 22)
                                    current_code_image = 20;
                                if (current_code_image == 20)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 20 || current_code_image > 22)
                                    current_code_image = 20;
                            }
                        }
                    }
                }
                else {
                    // The minivan is crashing
                    if (mode == 0) {
                        // First type of animation
                        if (current_code_image < 29 || current_code_image > 36)
                            current_code_image = 29;
                    }
                    else if (mode == 1) {
                        // Second type of animation
                        if (current_code_image < 37 || current_code_image > 44)
                            current_code_image = 37;
                    }
                }
            }
        }
        else {
            // Increment the code of the minivan texture to be drawn
            counter_code_image++;
        }
    }
    else {
        // Default code when the minivan does not move
        current_code_image = 1;
    }

    multiplayerMutex.unlock();

    // Draw the minivan in the screen adapted to the current screen resolution and pixel art effect
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

    // Check if the minivan is crashing or skidding or smoking
    if (smoking || skidding || crashing) {
        if (!crashing){
            // Accelerate the counter of changing the sprite
            maxCounterToChange = COUNTER + 1;
        }
        else {
            // Give it a value depending of the speed of the minivan
            if (getRealSpeed() < 20.f){
                maxCounterToChange = COUNTER + 4;
            }
            else if (getRealSpeed() >= 20.f && getRealSpeed() < 60.f){
                maxCounterToChange = COUNTER + 3;
            }
            else if (getRealSpeed() >= 60.f && getRealSpeed() < 100.f){
                maxCounterToChange = COUNTER + 2;
            }
            else if (getRealSpeed() >= 100.f && getRealSpeed() < 120.f){
                maxCounterToChange = COUNTER + 1;
            }
            else if (getRealSpeed() >= 120.f){
                maxCounterToChange = COUNTER;
            }
        }
        // Draw the smoke effect of the minivan
        const float j = sprite.getPosition().y + sprite.getGlobalBounds().height;
        sprite.setTexture(textures[44 + current_code_image % 4], true);
        sprite.setScale(3.f * c.screenScale, 3.5f * c.screenScale);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f - sprite.getGlobalBounds().width,
                           j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f, j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
    }
    // Check if the minivan is outside the road and it is moving
    else if (outSideRoad && speed != 0.f){
        // Must raise land
        maxCounterToChange = COUNTER;
        const float j = sprite.getPosition().y + sprite.getGlobalBounds().height;
        // Check the kind of terrain of the landscape and draw it
        switch(terrain){
        case 0:
            // Grass
            sprite.setTexture(textures[54 + current_code_image % 8], true);
            break;
        case 1:
            // Land
            sprite.setTexture(textures[49 + current_code_image % 6], true);
            break;
        case 2:
            // Snow
            sprite.setTexture(textures[63 + current_code_image % 6], true);
        }
        sprite.setScale(3.f * c.screenScale, 3.5f * c.screenScale);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f - sprite.getGlobalBounds().width,
                           j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f, j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
    }
    else if (!crashing) {
        // Make the minivan change the sprite quickly
        maxCounterToChange = COUNTER;
    }
}



/**
 * It forces the minivan to be smoking or not
 * @param smoke indicates if the minivan has to make smoke or not
 */
void Minivan::setSmoking(bool smoke) {
    smoking = smoke;
}



/**
 * Initialize the properties of the devastator depending of the game mode
 * selected by the player
 * @param typeOfGame is the game mode selected by the player
 * @param onMultiplayer control if the game is in multi player mode or not
 * @param codePlayerInGroup is the identifier code of the player in the multi player group
 * @param numRivals is the number of rivals in the multi player mode
 */
void Minivan::setVehicle(const int typeOfGame, const bool onMultiplayer, const int codePlayerInGroup, const int numRivals){
    // Reinitialize the properties of the minivan
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
 * Sets the type mode of collision
 */
void Minivan::setModeCollision(){
    // Check if the type of crash animation has been chosen
    if (mode == -1){
        // Get randomly the type of crash animation
        mode = rand_generator_int(0, 1);
    }
}



/**
 * Set the speed of the vehicle to zero
 */
void Minivan::setSpeed(){
    Vehicle::setSpeed();
}


/**
 * Returns the half speed that can be reached by the minivan
 * @return
 */
float Minivan::getHalfMaxSpeed(){
    return halfMaxSpeed;
}



/**
 * Returns the brand name of the minivan
 * @return
 */
string Minivan::getBrandName(){
    return brand;
}



/**
 * Returns the angle of turning of the minivan
 * @return
 */
string Minivan::getMotorName(){
    return motor;
}



/**
 * Returns the motor's name of the minivan
 * @return
 */
float Minivan::getAngle(){
    return angleTurning;
}



/**
 * Returns the maximum speed reached by the minivan
 * @return
 */
float Minivan::getTopSpeed(){
    return topSpeed;
}



/**
 * Returns the current code of the sprite of the vehicle to draw
 * @return
 */
int Minivan::getCurrentCodeImage() const {
    return Vehicle::getCurrentCodeImage();
}
