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
 * Module Traffic implementation file
 */

#include "../include/TrafficCar.h"



/**
 * Initialize the rival vehicle.
 * @param maxSpeed is the maximum speed reached by the traffic car
 * @param speedMultiplying the speed that multiplied by speed gets the real speed
 * @param scale vehicle sprite scaling
 * @param maxCounterToChange when counter_code_image arrives at maxCounterToChange the sprite is updated
 * @param vehicle name
 * @param pY is the position of the traffic car in the axis y
 */
TrafficCar::TrafficCar(float maxSpeed, float speedMul, float scale, int maxCounterToChange, const string &vehicle, float pX, float pY, bool truck) :
        Vehicle(maxSpeed / speedMul, scale, maxCounterToChange, 0, rand_generator_float(-0.5f, 0.5f), pX,
                pY, pY, 0, 0, vehicle, Vehicle_TrafficCar::NUM_ENEMIES_TEXTURES, 1, 0), oriX(this->posX),
        currentDirection(RIGHT), calculatedPath(RIGHT), current_direction_counter(0), max_direction_counter(0),
        probAI(0), typeAI(OBSTACLE)
{
    isTruck = truck;
}



/**
 * Updates the vehicle logic automatically for the current movement
 *
 * The AI will only be activated if the distance between the vehicle and the player is less than or equal to the distance
 * of rendering (rectangles that the player sees).
 *
 * AI aggressiveness is within the class (probAI). It is a value between 0 and 1 that indicates the probability of
 * that the AI act in this movement.
 *
 * If the AI aggressiveness is 0, the movement will be as in the original game, i.e. the car will continue
 * at a constant speed without going off the road and following a straight path or with a turn (chosen
 * randomly) and without being influenced by the player.
 *
 * If the aggressiveness of the AI is 1, the movement will be controlled by the AI and its movement will depend on the type
 * of AI:
 * OBSTACLE: Attempts to collide with the player by getting in his path and trying to catch him.
 * EVASIVE: Flees to the lane furthest from the player to try to avoid him.
 * INCONSTANT: Changes lanes too often regardless of the player's position.
 *
 * If the aggressiveness of the AI is between 0 and 1, it performs one of the two actions described (original
 * or AI) with probability p that the AI will act and p' = (1 - p) that it will be as in the original.
 *
 * @param c is the module configuration of the game
 * @param playerPosX is the position of the traffic car in the axis x
 * @param playerPosY is the position of the traffic car in the axis y
 */
void TrafficCar::autoControl(const Configuration &c, float playerPosX, float playerPosY) {
    // Default behavior
    if (abs(playerPosY - posY) > float(c.renderLen) || rand_generator_zero_one() >= probAI) {
        // Original
        if (current_direction_counter < max_direction_counter) {
            // The traffic car continues the current path
            current_direction_counter++;
        }
        else {
            // The traffic car starts a new path changing the current one
            max_direction_counter = rando_generator_zero_n(Vehicle_TrafficCar::MAX_DIRECTION);
            current_direction_counter = 0;
            calculatedPath = randomDirection();
        }

        // Change the track of the traffic car is the new path is turning left or right
        float newX = posX;
        if (calculatedPath == TURNRIGHT)
            newX += INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;
        else if (calculatedPath == TURNLEFT)
            newX -= INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;

        // Change the traffic car position in axis x
        if (newX < oriX - 0.15f || newX > oriX + 0.15f)
            calculatedPath = RIGHT;
        else
            posX = newX;

        // Store the new path to follow
        currentDirection = calculatedPath;
    }
    else {
        // AI
        // Check the types of AI and move the traffic car
        if (typeAI == OBSTACLE) {
            const float acc = getAcceleration();
            if (abs(playerPosX - posX) > INCREMENT_X) { // Rotation control
                // The vehicle is not in the player's path
                if (speed < halfMaxSpeed)
                    speed = sqrt(acc + ACCELERATION_INCREMENT);

                if (posX > playerPosX && posX > -0.9f) {
                    posX -= INCREMENT_X * speed / maxSpeed;
                    currentDirection = TURNLEFT;
                } else if (posX < 0.9f) {
                    posX += INCREMENT_X * speed / maxSpeed;
                    currentDirection = TURNRIGHT;
                }
            } else { // Acceleration control
                // The vehicle is in the player's path
                if (posY <= playerPosY)
                    speed = sqrt(acc + ACCELERATION_INCREMENT);
                else if (acc > ACCELERATION_INCREMENT)
                    speed = sqrt(acc - ACCELERATION_INCREMENT);
                else
                    speed = 0.0f;

                currentDirection = RIGHT;
            }
        } else if (typeAI == EVASIVE) {
            if (playerPosX <= -0.5) {
                posX += INCREMENT_X * speed / maxSpeed;
                currentDirection = TURNRIGHT;
            } else if (playerPosX >= 0.5) {
                posX -= INCREMENT_X * speed / maxSpeed;
                currentDirection = TURNLEFT;
            } else {
                if (posX > playerPosX) {
                    posX += INCREMENT_X * speed / maxSpeed;
                    currentDirection = TURNRIGHT;
                } else {
                    posX -= INCREMENT_X * speed / maxSpeed;
                    currentDirection = TURNLEFT;
                }
            }
        } else { // INCONSTANT
            if (currentDirection == TURNRIGHT) {
                const float prevPosX = posX;
                posX += INCREMENT_X * speed / maxSpeed;

                if (posX >= 0.9f)
                    currentDirection = TURNLEFT;
                else if (((prevPosX < -0.5f && posX >= -0.5f) || (prevPosX < 0.0f && posX >= 0.0f) ||
                          (prevPosX < 0.5f && posX >= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    currentDirection = TURNRIGHT; // Lane change
            } else if (currentDirection == TURNLEFT) {
                const float prevPosX = posX;
                posX -= INCREMENT_X * speed / maxSpeed;

                if (posX <= -0.9f)
                    currentDirection = TURNRIGHT;
                else if (((prevPosX > -0.5f && posX <= -0.5f) || (prevPosX > 0.0f && posX <= 0.0f) ||
                          (prevPosX > 0.5f && posX <= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    currentDirection = TURNLEFT; // Lane change
            } else {
                if (rand_generator_zero_one() < 0.5f)
                    currentDirection = TURNRIGHT;
                else
                    currentDirection = TURNLEFT;
            }
        }
    }

    // Control the limits of speed of the traffic car
    if (speed > maxSpeed)
        speed = maxSpeed;
    else if (speed < 0)
        speed = 0;

    // Check the new direction of the traffic car
    if (posX > 0.9f) {
        posX = 0.9f;
        currentDirection = RIGHT;
    }
    else if (posX < -0.9f) {
        posX = -0.9f;
        currentDirection = RIGHT;
    }

    // Update the position of the traffic car in the landscape
    previousY = posY;
    posY += speed;
}



/**
 * Initialize the vehicle status. Updates the aggressiveness of the vehicle's AI with a random value between 0
 * and maxAggressiveness.
 * @param iniPos is the initial position of the traffic car
 * @param endPos is the new position of the traffic car
 * @param maxAggressiveness is the AI aggressiveness of the traffic cars
 * @param difficulty is the difficulty level of the game selected by the player
 */
void TrafficCar::update(float iniPos, float endPos, float maxAggressiveness, const Difficult& difficulty, const int typeOfGame) {

    // Updating the speed of the traffic car between two thresholds
    speed = maxSpeed * rand_generator_float(0.25f, 0.75f);

    // Estimates the position of the traffic car and stores the current one
    posY = rand_generator_float(iniPos, endPos);
    previousY = posY;

    // Initialize the path counter
    current_direction_counter = 0;
    max_direction_counter = 0;
    minScreenX = 0;
    maxScreenX = 0;

    // Assign a type of AI to the traffic car
    if (typeOfGame == 1){
        setAI(maxAggressiveness, difficulty, typeOfGame);
    }
}



/**
 * Updates the aggressiveness of the vehicle AI with a random value between 0 and maxAggressiveness
 * @param maxAggressiveness is the AI aggressiveness of the traffic cars
 * @param difficulty is the difficulty level of the game selected by the player
 * @param typeOfGame is the game selected by the player
 */
void TrafficCar::setAI(float maxAggressiveness, const Difficult& difficulty, const int typeOfGame) {

    if (typeOfGame != 1){
        // Get a random number to select the type of AI for the traffic car
        const float p = rand_generator_zero_one();

        // Check the difficulty and depending of it a kind of AI is more common than the other ones
        switch(difficulty){
            case EASY:
                // More common type is EVASIVE
                if (p <= 0.25) {
                    typeAI = OBSTACLE;
                }
                else if (p <= 0.75) {
                    typeAI = EVASIVE;
                }
                else {
                    typeAI = INCONSTANT;
                    probAI *= 2.0f;
                }
                break;
            case NORMAL:
                // OBSTACLE is more common
                if (p <= 0.5f) {
                    typeAI = OBSTACLE;
                }
                else if (p <= 0.75f) {
                    typeAI = EVASIVE;
                }
                else {
                    typeAI = INCONSTANT;
                    probAI *= 2.0f;
                }
                break;
            case HARD:
                // OBSTACLE is more common
                if (p <= 0.65f) {
                    typeAI = OBSTACLE;
                }
                else if (p <= 0.75f) {
                    typeAI = EVASIVE;
                }
                else {
                    typeAI = INCONSTANT;
                    probAI *= 2.0f;
                }
        }
    }
    else {
        if (maxAggressiveness == 0.0f){
            probAI = 0.0f;
        }
        else {
            probAI = rand_generator_float(maxAggressiveness / 2.0f, maxAggressiveness);
        }
        const float p = rand_generator_zero_one();
        if (p < 0.333f) {
            typeAI = OBSTACLE;
        }
        else if (p < 0.666f) {
            typeAI = EVASIVE;
        }
        else {
            typeAI = INCONSTANT;
            probAI *= 2.0f;
        }
    }
}



/**
 * Update the sprite of the enemy vehicle.
 * @param e is the current elevation of the terrain where is the camera
 * @param camX is the position of the camera in the axis x
 */
void TrafficCar::draw(const Elevation &e, const float camX) {
    if (counter_code_image >= maxCounterToChange) {
        counter_code_image = 0;

        if (speed > 0.0f)
            current_code_image++;

        if (textures.size() == Vehicle_TrafficCar::NUM_ENEMIES_TEXTURES) {
            if (e == FLAT) {
                if (currentDirection == RIGHT) {
                    if (posX <= camX) {
                        if (current_code_image < 1 || current_code_image > 2)
                            current_code_image = 1;
                    } else {
                        if (current_code_image < 3 || current_code_image > 4)
                            current_code_image = 3;
                    }
                } else if (currentDirection == TURNLEFT) {
                    if (current_code_image < 7 || current_code_image > 8)
                        current_code_image = 7;
                } else { // Turn right
                    if (current_code_image < 5 || current_code_image > 6)
                        current_code_image = 5;
                }
            } else if (e == UP) {
                if (currentDirection == RIGHT) {
                    if (posX <= camX) {
                        if (current_code_image < 13 || current_code_image > 14)
                            current_code_image = 13;
                    } else {
                        if (current_code_image < 15 || current_code_image > 16)
                            current_code_image = 15;
                    }
                } else if (currentDirection == TURNLEFT) {
                    if (current_code_image < 15 || current_code_image > 16)
                        current_code_image = 15;
                } else { // Turn right
                    if (current_code_image < 13 || current_code_image > 14)
                        current_code_image = 13;
                }
            } else { // Down
                if (currentDirection == RIGHT) {
                    if (posX <= camX) {
                        if (current_code_image < 9 || current_code_image > 10)
                            current_code_image = 9;
                    } else {
                        if (current_code_image < 11 || current_code_image > 12)
                            current_code_image = 11;
                    }
                } else if (currentDirection == TURNLEFT) {
                    if (current_code_image < 11 || current_code_image > 12)
                        current_code_image = 11;
                } else { // Turn right
                    if (current_code_image < 9 || current_code_image > 10)
                        current_code_image = 9;
                }
            }
        }
    } else {
        counter_code_image++;
    }
}



/**
 * Sets the minimum X coordinate that the vehicle occupies.
 * @param screenX
 */
void TrafficCar::setMinScreenX(float screenX) {
    minScreenX = screenX;
}



/**
 * Sets the maximum X coordinate that the vehicle occupies.
 * @param screenX
 */
void TrafficCar::setMaxScreenX(float screenX) {
    maxScreenX = screenX;
}



/**
 * Returns the current texture of the vehicle
 * @return
 */
const Texture *TrafficCar::getCurrentTexture() const {
    return &textures[current_code_image - 1];
}



/**
 * Returns the current scale of the vehicle.
 * @return
 */
float TrafficCar::getScale() const {
    return scale;
}



/**
 * Returns true if there has been a collision between the traffic vehicle and the player's vehicle.
 * If true, it also returns the Y position where they have collided
 * @param currentY is the current position of the player's vehicle in the axis y
 * @param prevY is the last position of the player's vehicle in the axis y
 * @param minX is the minimum position in axis x occupied by the vehicle
 * @param maxX is the maximum position in axis y occupied by the vehicle
 * @param crashPos is the position in axis y where the crash has happened
 * @return
 */
bool TrafficCar::hasCrashed(float prevY, float currentY, float minX, float maxX, float &crashPos) const {
    // Check if the path of the traffic car is approximately the same path of the player's vehicle
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
 * @param distanceX is the distance between the traffic car and the vehicle of the player in the axis x
 * @param distanceY is the distance between the traffic car and the vehicle of the player in the axis y
 * @return
 */
bool TrafficCar::isVisible(const Configuration &c, float minY, float playerX, float playerY, float &distanceX, float &distanceY) const {
    // Check if the traffic car is visible from the position of the player's vehicle
    if (posY < minY || posY > minY + float(c.renderLen) || minScreenX < 0 || maxScreenX > c.w.getSize().y) {
        // The traffic car is not visible
        return false;
    }
    else {
        // The traffic car is visible and calculate the distance in both axis with it
        distanceX = abs(playerX - posX);
        distanceY = abs(playerY - posY);
        return true;
    }
}



/**
 * Returns true if the traffic car is a truck.
 * Otherwise returns false
 */
bool TrafficCar::getIsTruck() const{
    return isTruck;
}
