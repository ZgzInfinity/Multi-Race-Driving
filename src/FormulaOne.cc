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
 * Module FormulaOne implementation file
 */

#include "../include/FormulaOne.h"



/**
 * Default constructor
 */
FormulaOne::FormulaOne(){}



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
FormulaOne::FormulaOne(float maxSpeed, float speedMul, float accInc, float scaleX, float scaleY, int maxCounterToChange,
                       const string &vehicle, float pX, float pY, const string brandName, const float angle,
                       const string motorName) : Vehicle(maxSpeed / speedMul, scaleX, maxCounterToChange,
                                                0.0f, pX, pX, pY, pY, 0, 0, vehicle, FormulaOne_vehicle::PLAYER_TEXTURES, 1, 0),
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
 * Returns the last position of the formula one in axis y
 * @return
 */
float FormulaOne::getPreviousY() const {
    return previousY;
}



/**
 * Updates the crash logic of the formula one and restores speed and acceleration
 * @param vehicleCrash true if it is a crash between vehicles
 */
void FormulaOne::hitControl(const bool vehicleCrash) {

    // By default the formula one is crashing
    crashing = true;

    // By default the formula one is not smoking
    smoking = false;

    // By default the formula one is not skidding
    skidding = false;

    // Decrement the acceleration of the formula one depending of the speed
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

    // Control the end of the crash animation of the formula one
    if (current_code_image == 53){
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
 * Returns true if the formula one is crashing. Otherwise returns false
 * @return
 */
bool FormulaOne::isCrashing() const {
    return crashing;
}



/**
 * Returns the real speed of the formula one
 * @return
 */
float FormulaOne::getRealSpeed() const {
    return speed * speedMul;
}



/**
 * Updates the logic of the formula one's acceleration and braking
 * @param c is the module configuration of the game
 * @param hasGotOut indicates if it's gone off track
 * @return
 */
Vehicle::Action FormulaOne::accelerationControl(Configuration &c, bool hasGotOut) {

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
        // Check if the formula one is outside the road
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

        // Check if the formula one must start to smoke
        smoking = acceleration < maxAcc * 0.1f;
    } else {
        // The formula one is braking
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

    // Control if the formula one is going to boot the motor
    if (previousAcc == 0.0f && acceleration > 0.0f)
        a = BOOT;
    else if (a == NONE && acceleration > 0.0f)
        // The formula one accelerates because the rest of actions has not happened
        a = ACCELERATE;

    // Calculate the new speed of the formula one
    mainMutex.lock();
    speed = sqrt(acceleration);
    mainMutex.unlock();

    // Control the advance of the formula one in the landscape
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
 * Updates the logic direction turn of the formula one
 * @param c is the module configuration of the game
 * @param curveCoefficient is the coefficient curve
 * @param isFinalMap controls if the formula one is circulating in the goal landscape or not
 * @param limitMap is the size of the landscape
 * @return
 */
Vehicle::Direction FormulaOne::rotationControl(Configuration &c, float curveCoefficient, const bool& isFinalMap, const int& limitMap) {

    // The formula one is not skidding by default
    skidding = false;
    if (speed > 0.0f) {
        // Check if it's the final landscape and it is near the goal
        if (isFinalMap && limitMap - posY <= 150.f){
            // Check if the formula one is in the right of the road
            if (posX > 0.f){
                previousX = posX;
                posX -= 0.02f;
                if (posX < 0.0f){
                    // Centered in the middle of the road
                    posX = 0.0f;
                }
            }
            // Check if the formula one is in the left of the road
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

            // Check if the formula one has to start to skid
            if (abs(curveCoefficient) >= 0.33f && speed >= 0.66f * maxSpeed)
                skidding = true;

            // Control if the turning left control key has been pressed
            if (c.window.hasFocus() && Keyboard::isKeyPressed(c.leftKey)) {

                // Measure the effect of the inertia force
                if (inertia > -FormulaOne_vehicle::FORCE_INERTIA)
                    inertia--;

                // The inertia force makes the formula one skid
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
                if (inertia < FormulaOne_vehicle::FORCE_INERTIA)
                    inertia++;

                // The inertia force makes the formula one skid
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
    // Formula one goes right
    return RIGHT;
}



/**
 * Updates the formula one's sprite and draws it in the screen
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 * @param a is the action to be done by the formula one
 * @param d is the direction to be followed by the formula one
 * @param e is the current elevation of the formula one in the landscape
 * @param enableSound indicates if the motor of the formula one has to make noise
 */
void FormulaOne::draw(Configuration &c, SoundPlayer &r, const Action &a, const Direction &d,
                    const Elevation &e, int terrain, bool enableSound)
{
    // Sound effects
    if (a != CRASH)
        firstCrash = true;

    // Control the sounds of the formula one
    if (enableSound) {
        if (speed > 0.0f) {
            if (a == BOOT) {
                // Acceleration sound
                r.soundEffects[121]->stop();
                r.soundEffects[121]->play();
            }
            if (r.soundEffects[123]->getStatus() != SoundSource::Playing) {
                // Engine sound
                r.soundEffects[123]->stop();
                r.soundEffects[123]->play();
            }
            r.soundEffects[123]->setVolume((33.0f + 67.0f * speed / maxSpeed) * float(r.volumeEffects) / 100.f);
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
            r.soundEffects[123]->stop();
            r.soundEffects[8]->stop();
            r.soundEffects[53]->stop();
        }

        if (a == CRASH && firstCrash) {
            firstCrash = false;
            r.soundEffects[126]->stop();
            r.soundEffects[18]->stop();
            r.soundEffects[19]->stop();
            r.soundEffects[126]->play();
            r.soundEffects[rand_generator_int(18, 19)]->play();
        }
    }
    else {
        r.soundEffects[12]->stop();
        r.soundEffects[123]->stop();
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

    // Check the current action of the formula one to be drawn in the screen
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

            if (textures.size() == FormulaOne_vehicle::PLAYER_TEXTURES) {
                if (a == ACCELERATE || a == BOOT) {
                    if (e == FLAT) {
                        if (d == RIGHT) {
                            if (current_code_image < 1 || current_code_image > 2)
                                current_code_image = 1;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 3 || current_code_image > 12)
                                    current_code_image = 3;
                                if (current_code_image == 11)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 11 || current_code_image > 12)
                                    current_code_image = 11;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 13 || current_code_image > 22)
                                    current_code_image = 13;
                                if (current_code_image == 21)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 21 || current_code_image > 22)
                                    current_code_image = 21;
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
                                if (current_code_image < 3 || current_code_image > 12)
                                    current_code_image = 3;
                                if (current_code_image == 11)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 11 || current_code_image > 12)
                                    current_code_image = 11;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 13 || current_code_image > 22)
                                    current_code_image = 13;
                                if (current_code_image == 21)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 21 || current_code_image > 22)
                                    current_code_image = 21;
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
                                if (current_code_image < 3 || current_code_image > 12)
                                    current_code_image = 3;
                                if (current_code_image == 11)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 11 || current_code_image > 12)
                                    current_code_image = 11;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 13 || current_code_image > 22)
                                    current_code_image = 13;
                                if (current_code_image == 21)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 21 || current_code_image > 22)
                                    current_code_image = 21;
                            }
                        }
                    }
                } else if (a == BRAKE) {
                    if (e == FLAT) {
                        if (d == RIGHT) {
                            if (current_code_image < 23 || current_code_image > 24)
                                current_code_image = 23;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 25 || current_code_image > 34)
                                    current_code_image = 25;
                                if (current_code_image == 33)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 33 || current_code_image > 34)
                                    current_code_image = 33;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 35 || current_code_image > 44)
                                    current_code_image = 35;
                                if (current_code_image == 43)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 43 || current_code_image > 44)
                                    current_code_image = 43;
                            }
                        }
                    } else if (e == UP) {
                        if (d == RIGHT) {
                            if (current_code_image < 23 || current_code_image > 24)
                                current_code_image = 23;
                        } else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 25 || current_code_image > 34)
                                    current_code_image = 25;
                                if (current_code_image == 33)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 33 || current_code_image > 34)
                                    current_code_image = 33;
                            }
                        } else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 35 || current_code_image > 44)
                                    current_code_image = 35;
                                if (current_code_image == 43)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 43 || current_code_image > 44)
                                    current_code_image = 43;
                            }
                        }
                    } else { // Down
                        if (d == RIGHT) {
                            if (current_code_image < 23 || current_code_image > 24)
                                current_code_image = 23;
                        } else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 25 || current_code_image > 34)
                                    current_code_image = 25;
                                if (current_code_image == 33)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 33 || current_code_image > 34)
                                    current_code_image = 33;
                            }
                        } else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 35 || current_code_image > 44)
                                    current_code_image = 35;
                                if (current_code_image == 43)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 43 || current_code_image > 44)
                                    current_code_image = 43;
                            }
                        }
                    }
                }
                else {
                    // The formula one is crashing
                    if (current_code_image < 45 || current_code_image > 53)
                        current_code_image = 45;
                }
            }
        }
        else {
            // Increment the code of the formula one texture to be drawn
            counter_code_image++;
        }
    }
    else {
        // Default code when the formula one does not move
        current_code_image = 1;
    }

    multiplayerMutex.unlock();

    // Draw the formula one in the screen adapted to the current screen resolution and pixel art effect
    sprite.setTexture(textures[current_code_image - 1], true);
    sprite.setScale(scale * c.screenScale, scaleY * c.screenScale);
    minScreenX = ((float) c.w.getSize().x) / 2.0f - sprite.getGlobalBounds().width / 2.0f;
    maxScreenX = minScreenX + sprite.getGlobalBounds().width;
    if (c.isDefaultScreen){
        if (c.enablePixelArt){
            sprite.setPosition(minScreenX, ((float) c.w.getSize().y) * c.camD - sprite.getGlobalBounds().height / 2.0f + 13.f);
        }
        else {
            sprite.setPosition(minScreenX, ((float) c.w.getSize().y) * c.camD - sprite.getGlobalBounds().height / 2.0f + 25.f);
        }
    }
    else {
        if (c.enablePixelArt){
            sprite.setPosition(minScreenX, ((float) c.w.getSize().y) * c.camD - sprite.getGlobalBounds().height / 2.0f + 2.f);
        }
        else {
            sprite.setPosition(minScreenX, ((float) c.w.getSize().y) * c.camD - sprite.getGlobalBounds().height / 2.0f + 5.f);
        }
    }
    c.w.draw(sprite);

    // Check if the formula one is skidding or smoking
    if (smoking || skidding) {
        // Accelerate the counter of changing the sprite
        maxCounterToChange = COUNTER + 1;
        const float j = sprite.getPosition().y + sprite.getGlobalBounds().height;
        sprite.setTexture(textures[53 + current_code_image % 4], true);
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
    // Draw the smoke effect of the formula one
    else if (outSideRoad && speed != 0.f){
        // Must raise land
        maxCounterToChange = COUNTER;
        const float j = sprite.getPosition().y + sprite.getGlobalBounds().height;
        switch(terrain){
        case 0:
            // Grass
            sprite.setTexture(textures[64 + current_code_image % 8], true);
            break;
        case 1:
            // Land
            sprite.setTexture(textures[58 + current_code_image % 6], true);
            break;
        case 2:
            // Snow
            sprite.setTexture(textures[72 + current_code_image % 6], true);
        }
        sprite.setScale(3.f * c.screenScale, 3.5f * c.screenScale);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f - sprite.getGlobalBounds().width,
                           j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f, j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
    }
    else if (!crashing) {
        // Make the formula one change the sprite quickly
        maxCounterToChange = COUNTER;
    }
}



/**
 * It forces the formula one to be smoking or not
 * @param smoke indicates if the formula one has to make smoke or not
 */
void FormulaOne::setSmoking(bool smoke) {
    smoking = smoke;
}



/**
 * Set the speed of the vehicle to zero
 */
void FormulaOne::setSpeed(){
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
void FormulaOne::setVehicle(const int typeOfGame, const bool onMultiplayer, const int codePlayerInGroup, const int numRivals){
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
 * Returns the half speed that can be reached by the formula one
 * @return
 */
float FormulaOne::getHalfMaxSpeed(){
    return halfMaxSpeed;
}



/**
 * Returns the brand name of the formula one
 * @return
 */
string FormulaOne::getBrandName(){
    return brand;
}



/**
 * Returns the angle of turning of the formula one
 * @return
 */
float FormulaOne::getAngle(){
    return angleTurning;
}



/**
 * Returns the motor's name of the formula one
 * @return
 */
string FormulaOne::getMotorName(){
    return motor;
}



/**
 * Returns the maximum speed reached by the formula one
 * @return
 */
float FormulaOne::getTopSpeed(){
    return topSpeed;
}



/**
 * Returns the current code of the sprite of the vehicle to draw
 * @return
 */
int FormulaOne::getCurrentCodeImage() const {
    return Vehicle::getCurrentCodeImage();
}

