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
 * Module Devastator implementation file
 */

#include "../include/Devastator.h"



/**
 * Default constructor
 */
Devastator::Devastator(){}




/**
 * Initialize the devastator chosen by the player
 * @param maxSpeed is the maximum speed that the devastator can reach
 * @param speedMul is factor number that when it is multiplied by speed obtains the real speed
 * @param accInc is the acceleration increment
 * @param scaleX is the scaling factor in the axis x
 * @param scaleY is the scaling factor in the axis y
 * @param maxCounterToChange lets to update the sprite of the devastator that is drawn in the screen
 * @param vehicle is the type of vehicle selected by the player
 * @param pX is the position of the player in the axis x
 * @param pY is the position of the player in the axis y
 */
Devastator::Devastator(float maxSpeed, float speedMul, float accInc, float scaleX, float scaleY, int maxCounterToChange,
                       const string &vehicle, float pX, float pY, const string brandName, const float angle,
                       const string motorName) : Vehicle(maxSpeed / speedMul, scaleX, maxCounterToChange,
                                                 0.0f, pX, pX, pY, pY, 0, 0, vehicle, Devastator_vehicle::PLAYER_TEXTURES, 1, 0),
                                                 speedMul(speedMul), maxAcc(pow(maxSpeed / speedMul, 2.0f)),
                                                 accInc(accInc), scaleY(scaleY), acceleration(0),
                                                 minCrashAcc(0), xDest(1000.f), inertia(0), crashing(false),
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
 * Returns the last position of the devastator in axis y
 * @return
 */
float Devastator::getPreviousY() const {
    return previousY;
}



/**
 * Updates the crash logic of the devastator and restores speed and acceleration
 * @param vehicleCrash true if it is a crash between vehicles
 */
void Devastator::hitControl(const bool vehicleCrash) {

    // By default the devastator is crashing
    crashing = true;

    // By default the devastator is not smoking
    smoking = false;

    // By default the devastator is not skidding
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
            // The devastator goes to the left
            xDest = -(acceleration * 1.7f / maxAcc);

        }
        else {
            // The devastator goes to the right
            xDest = acceleration * 1.7f / maxAcc;
        }
    }

    // Check the destination coordinate in axis x of the crash
    if (xDest > 0.f){
        // Increment to the right depending if the speed of the devastator
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
        // Increment to the left depending if the speed of the devastator
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

    // Calculate the speed of the devastator using its acceleration
    mainMutex.lock();
    speed = sqrt(acceleration);
    mainMutex.unlock();

    // Control the movement in the axis y
    if (xDest > 0.f && posX < xDest){
        // Check the crash has been with an element of the map
        // or with another car
        if (!vehicleCrash){
            // Crash with element of map and devastator moves forward
            posY = posY + acceleration * 7.f / maxAcc;
        }
        else {
            // Crash with element of map and devastator moves backwards
            posY = posY - acceleration * 7.f / maxAcc;
        }
    }
    else if (xDest < 0.f && posX > xDest) {
        // Check the crash has been with an element of the map
        // or with another car
        if (!vehicleCrash){
            // Crash with element of map and devastator moves forward
            posY = posY + acceleration * 7.f / maxAcc;
        }
        else {
            // Crash with element of map and devastator moves backwards
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
 * Returns true if the devastator is crashing. Otherwise returns false
 * @return
 */
bool Devastator::isCrashing() const {
    return crashing;
}



/**
 * Returns the real speed of the devastator
 * @return
 */
float Devastator::getRealSpeed() const {
    return speed * speedMul;
}



/**
 * Updates the logic of the devastator's acceleration and braking
 * @param c is the module configuration of the game
 * @param hasGotOut indicates if it's gone off track
 * @return
 */
Vehicle::Action Devastator::accelerationControl(Configuration &c, bool hasGotOut) {

    // Default action
    Action a = NONE;
    smoking = false;

    // Store the current acceleration
    float previousAcc = acceleration;

    // Check if the braking control key has been pressed
    if (c.window.hasFocus() && Keyboard::isKeyPressed(c.brakeKey))
        // Devastator brakes
        a = BRAKE;

    // Check if the accelerating key has been pressed
    if (a != BRAKE && c.window.hasFocus() && Keyboard::isKeyPressed(c.accelerateKey)) {
        // Check if the devastator is outside the road
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

        // Check if the devastator must start to smoke
        smoking = acceleration < maxAcc * 0.1f;
    }
    else {
        // The devastator is braking
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

    // Control if the devastator is going to boot the motor
    if (previousAcc == 0.0f && acceleration > 0.0f)
        a = BOOT;
    else if (a == NONE && acceleration > 0.0f)
        // The devastator accelerates because the rest of actions has not happened
        a = ACCELERATE;

    // Calculate the new speed of the devastator
    mainMutex.lock();
    speed = sqrt(acceleration);
    mainMutex.unlock();

    // Control the advance of the devastator in the landscape
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
 * Updates the logic direction turn of the devastator
 * @param c is the module configuration of the game
 * @param curveCoefficient is the coefficient curve
 * @param isFinalMap controls if the devastator is circulating in the goal landscape or not
 * @param limitMap is the size of the landscape
 * @return
 */
Vehicle::Direction Devastator::rotationControl(Configuration &c, float curveCoefficient, const bool& isFinalMap, const int& limitMap) {

    // The devastator is not skidding by default
    skidding = false;

    if (speed > 0.0f) {
        // Check if it's the final landscape and it is near the goal
        if (isFinalMap && limitMap - posY <= 130.f){
            // Check if the devastator is in the right of the road
            if (posX > 0.f){
                posX -= 0.02f;
                if (posX < 0.0f){
                    // Centered in the middle of the road
                    posX = 0.0f;
                }
            }
            // Check if the devastator is in the left of the road
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

            // Check if the devastator has to start to skid
            if (abs(curveCoefficient) >= 0.33f && speed >= 0.66f * maxSpeed)
                skidding = true;

            // Control if the turning left control key has been pressed
            if (c.window.hasFocus() && Keyboard::isKeyPressed(c.leftKey)) {

                // Measure the effect of the inertia force
                if (inertia > -Devastator_vehicle::FORCE_INERTIA)
                    inertia--;

                // The inertia force makes the devastator skid
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

                    // Devastator turns left
                    return TURNLEFT;
                }
            }
            // Control if the turning right control key has been pressed
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(c.rightKey)) {

                // Measure the effect of the inertia force
                if (inertia < Devastator_vehicle::FORCE_INERTIA)
                    inertia++;

                // The inertia force makes the devastator skid
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

                    // Devastator turns right
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
    // Devastator goes right
    return RIGHT;
}



/**
 * Updates the devastator's sprite and draws it in the screen
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 * @param a is the action to be done by the devastator
 * @param d is the direction to be followed by the devastator
 * @param e is the current elevation of the devastator in the landscape
 * @param enableSound indicates if the motor of the devastator has to make noise
 */
void Devastator::draw(Configuration &c, SoundPlayer &r, const Action &a, const Direction &d,
                  const Elevation &e, int terrain, bool enableSound)
{
    // Sound effects
    if (a != CRASH)
        firstCrash = true;

    // Control the sounds of the devastator
    if (enableSound) {
        if (speed > 0.0f) {
            if (a == BOOT) {
                // Acceleration sound
                r.soundEffects[12]->stop();
                r.soundEffects[12]->play();
            }
            if (r.soundEffects[6]->getStatus() != SoundSource::Playing) {
                // Engine sound
                r.soundEffects[6]->stop();
                r.soundEffects[6]->play();
            }
            r.soundEffects[6]->setVolume((33.0f + 67.0f * speed / maxSpeed) * float(r.volumeEffects) / 100.f);
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
            r.soundEffects[6]->stop();
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
        r.soundEffects[12]->stop();
        r.soundEffects[6]->stop();
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

    // Check the current action of the devastator to be drawn in the screen
    if (a != NONE) {
        if (counter_code_image >= maxCounterToChange) {
            counter_code_image = 0;

            // Increment the texture counter only if it moves
            if (speed > 0.0f)
                current_code_image++;

            if (textures.size() == Devastator_vehicle::PLAYER_TEXTURES) {
                if (a == ACCELERATE || a == BOOT) {
                    if (e == FLAT) {
                        if (d == RIGHT) {
                            if (current_code_image < 1 || current_code_image > 4)
                                current_code_image = 1;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 5 || current_code_image > 8)
                                    current_code_image = 5;
                                if (current_code_image == 6)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 6 || current_code_image > 8)
                                    current_code_image = 6;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 9 || current_code_image > 12)
                                    current_code_image = 9;
                                if (current_code_image == 10)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 10 || current_code_image > 12)
                                    current_code_image = 10;
                            }
                        }
                    }
                     else if (e == UP) {
                        if (d == RIGHT) {
                            if (current_code_image < 13 || current_code_image > 14)
                                current_code_image = 13;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 15 || current_code_image > 16)
                                    current_code_image = 15;
                                if (current_code_image == 15)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 15 || current_code_image > 16)
                                    current_code_image = 15;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 17 || current_code_image > 18)
                                    current_code_image = 17;
                                if (current_code_image == 17)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 17 || current_code_image > 18)
                                    current_code_image = 17;
                            }
                        }
                    }
                    else { // Down
                        if (d == RIGHT) {
                            if (current_code_image < 1 || current_code_image > 4)
                                current_code_image = 1;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 5 || current_code_image > 8)
                                    current_code_image = 5;
                                if (current_code_image == 6)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 6 || current_code_image > 8)
                                    current_code_image = 6;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 9 || current_code_image > 12)
                                    current_code_image = 9;
                                if (current_code_image == 10)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 10 || current_code_image > 12)
                                    current_code_image = 10;
                            }
                        }
                    }
                } else if (a == BRAKE) {
                    if (e == FLAT) {
                        if (d == RIGHT) {
                            if (current_code_image < 19 || current_code_image > 22)
                                current_code_image = 19;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 23 || current_code_image > 26)
                                    current_code_image = 23;
                                if (current_code_image == 24)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 24 || current_code_image > 26)
                                    current_code_image = 24;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 27 || current_code_image > 30)
                                    current_code_image = 27;
                                if (current_code_image == 28)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 28 || current_code_image > 30)
                                    current_code_image = 28;
                            }
                        }
                    } else if (e == UP) {
                        if (d == RIGHT) {
                            if (current_code_image < 31 || current_code_image > 32)
                                current_code_image = 31;
                        } else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 33 || current_code_image > 34)
                                    current_code_image = 33;
                                if (current_code_image == 33)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 33 || current_code_image > 34)
                                    current_code_image = 33;
                            }
                        } else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 35 || current_code_image > 36)
                                    current_code_image = 35;
                                if (current_code_image == 35)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 35 || current_code_image > 36)
                                    current_code_image = 35;
                            }
                        }
                    } else { // Down
                        if (d == RIGHT) {
                            if (current_code_image < 19 || current_code_image > 22)
                                current_code_image = 19;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 23 || current_code_image > 26)
                                    current_code_image = 23;
                                if (current_code_image == 24)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 24 || current_code_image > 26)
                                    current_code_image = 24;
                            }
                        }
                        else {
                            if (firstTurnRight) {
                                if (current_code_image < 27 || current_code_image > 30)
                                    current_code_image = 27;
                                if (current_code_image == 28)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 28 || current_code_image > 30)
                                    current_code_image = 28;
                            }
                        }
                    }
                }
                else {
                    // The devastator is crashing
                    if (mode == 0) {
                        // First type of animation
                        if (current_code_image < 37 || current_code_image > 44)
                            current_code_image = 37;
                    }
                    else if (mode == 1) {
                        // Second type of animation
                        if (current_code_image < 45 || current_code_image > 52)
                            current_code_image = 45;
                    }
                }
            }
        }
        else {
            // Increment the code of the devastator texture to be drawn
            counter_code_image++;
        }
    }
    else {
        // Default code when the devastator does not move
        current_code_image = 1;
    }

    multiplayerMutex.unlock();

    // Draw the devastator in the screen adapted to the current screen resolution and pixel art effect
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

    // Check if the devastator is crashing or skidding or smoking
    if (smoking || skidding || crashing) {
        if (!crashing){
            // Accelerate the counter of changing the sprite
            maxCounterToChange = COUNTER + 1;
        }
        else {
            // Give it a value depending of the speed of the devastator
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
        // Draw the smoke effect of the devastator
        const float j = sprite.getPosition().y + sprite.getGlobalBounds().height;
        sprite.setTexture(textures[52 + current_code_image % 4], true);
        sprite.setScale(3.f * c.screenScale, 3.5f * c.screenScale);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f - sprite.getGlobalBounds().width,
                           j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f, j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
    }
    // Check if the devastator is outside the road and it is moving
    else if (outSideRoad && speed != 0.f){
        // Must raise land
        maxCounterToChange = COUNTER;
        const float j = sprite.getPosition().y + sprite.getGlobalBounds().height;
        // Check the kind of terrain of the landscape and draw it
        switch(terrain){
        case 0:
            // Grass
            sprite.setTexture(textures[63 + current_code_image % 8], true);
            break;
        case 1:
            // Land
            sprite.setTexture(textures[57 + current_code_image % 6], true);
            break;
        case 2:
            // Snow
            sprite.setTexture(textures[71 + current_code_image % 6], true);
        }
        sprite.setScale(3.f * c.screenScale, 3.5f * c.screenScale);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f - sprite.getGlobalBounds().width,
                           j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f, j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
    }
    else if (!crashing) {
        // Make the devastator change the sprite quickly
        maxCounterToChange = COUNTER;
    }
}



/**
 * It forces the devastator to be smoking or not
 * @param smoke indicates if the devastator has to make smoke or not
 */
void Devastator::setSmoking(bool smoke) {
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
void Devastator::setVehicle(const int typeOfGame, const bool onMultiplayer, const int codePlayerInGroup, const int numRivals){
    // Reinitialize the properties of the devastator
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
void Devastator::setModeCollision(){
    // Check if the type of crash animation has been chosen
    if (mode == -1){
        // Get randomly the type of crash animation
        mode = rand_generator_int(0, 1);
    }
}



/**
 * Set the speed of the vehicle to zero
 */
void Devastator::setSpeed(){
    Vehicle::setSpeed();
}



/**
 * Returns the half speed that can be reached by the devastator
 * @return
 */
float Devastator::getHalfMaxSpeed(){
    return halfMaxSpeed;
}



/**
 * Returns the brand name of the devastator
 * @return
 */
string Devastator::getBrandName(){
    return brand;
}



/**
 * Returns the angle of turning of the devastator
 * @return
 */
string Devastator::getMotorName(){
    return motor;
}



/**
 * Returns the motor's name of the devastator
 * @return
 */
float Devastator::getAngle(){
    return angleTurning;
}



/**
 * Returns the maximum speed reached by the devastator
 * @return
 */
float Devastator::getTopSpeed(){
    return topSpeed;
}



/**
 * Returns the current code of the sprite of the vehicle to draw
 * @return
 */
int Devastator::getCurrentCodeImage() const {
    return Vehicle::getCurrentCodeImage();
}

