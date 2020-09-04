/*
 * Copyright (c) 2020 Andr�s Gav�n
 * Copyright (c) 2020 Rub�n Rodr�guez
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
 * Module Traffic interface file
 */

#ifndef TRAFFIC_CAR_H
#define TRAFFIC_CAR_H

#include "Vehicle.h"
#include "Randomizer.h"
#include <cmath>


using namespace std;
using namespace sf;



/*
 * Properties of the traffic car
 */
namespace Vehicle_TrafficCar {
    // Time that the traffic car must go in a concrete direction
    const int MAX_DIRECTION = 1000;
    // Number of textures of the traffic car
    const int NUM_ENEMIES_TEXTURES = 16;
}



/**
 * Represents a traffic car that is going to compete in some
 * game modes of the game
 */
class TrafficCar : public Vehicle {

    // Coordinate in the axis x
    const float oriX;

    // Direction that must be followed by the traffic car
    Direction currentDirection;

    // Direction that is going to be computed
    Direction calculatedPath;

    // Counter that stores the sprite of the traffic car to draw in the screen
    int current_direction_counter;

    // Counter that express how much the traffic car must maintain the current direction
    int max_direction_counter;

    // Probabilistic value of the AI
    float probAI;

    // Control if the traffic car is a truck or not
    bool isTruck;


    /**
     * Types of AI:
     * OBSTACLE: Attempts to collide with the player by getting in his path and trying to catch him.
     * EVASIVE: Flees to the lane furthest from the player to try to avoid him.
     * INCONSTANT: Changes lanes too often regardless of the player's position.
     */
    enum TypeAI {
        OBSTACLE,
        EVASIVE,
        INCONSTANT
    };

    // Ai mode of the traffic car
    TypeAI typeAI;

public:



    /**
     * Initialize the rival vehicle.
     * @param maxSpeed is the maximum speed reached by the traffic car
     * @param speedMultiplying the speed that multiplied by speed gets the real speed
     * @param scale vehicle sprite scaling
     * @param maxCounterToChange when counter_code_image arrives at maxCounterToChange the sprite is updated
     * @param vehicle name
     * @param pY is the position of the traffic car in the axis y
     */
    TrafficCar(float maxSpeed, float speedMul, float scale, int maxCounterToChange, const std::string &vehicle, float pX, float pY, bool truck);



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
    void autoControl(const Configuration &c, float playerPosX, float playerPosY);



    /**
     * Initialize the vehicle status. Updates the aggressiveness of the vehicle's AI with a random value between 0
     * and maxAggressiveness.
     * @param iniPos is the initial position of the traffic car
     * @param endPos is the new position of the traffic car
     * @param maxAggressiveness is the AI aggressiveness of the traffic cars
     * @param difficulty is the difficulty level of the game selected by the player
     */
    void update(float iniPos, float endPos, float maxAggressiveness, const Difficult& difficulty);



    /**
     * Updates the aggressiveness of the vehicle AI with a random value between 0 and maxAggressiveness
     * @param maxAggressiveness is the AI aggressiveness of the traffic cars
     * @param difficulty is the difficulty level of the game selected by the player
     */
    void setAI(float maxAggressiveness, const Difficult& difficulty);



    /**
     * Update the sprite of the enemy vehicle.
     * @param e is the current elevation of the terrain where is the camera
     * @param camX is the position of the camera in the axis x
     */
    void draw(const Elevation &e, float camX);



    /**
     * Sets the minimum X coordinate that the vehicle occupies.
     * @param screenX
     */
    void setMinScreenX(float screenX);



    /**
     * Sets the maximum X coordinate that the vehicle occupies.
     * @param screenX
     */
    void setMaxScreenX(float screenX);



    /**
     * Returns the current texture of the vehicle
     * @return
     */
    const sf::Texture *getCurrentTexture() const;



    /**
     * Returns the current scale of the vehicle.
     * @return
     */
    float getScale() const;



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
     * Returns true if the traffic car is a truck.
     * Otherwise returns false
     */
    bool getIsTruck() const;

};


#endif // TRAFFIC_CAR_H
