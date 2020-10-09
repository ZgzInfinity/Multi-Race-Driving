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
 * Module LandScape interface file
 */

#pragma once

#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <cmath>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <chrono>
#include "Step.h"
#include "Menu.h"
#include "TrafficCar.h"
#include "RivalCar.h"
#include "MultiplayerCar.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
using namespace rapidxml;


const float M_PI = 3.14159265358979323846;
const float BGS = 0.755F;
const float LIMIT_FORK = 0.03f;
const float FORK_RADIUS = 10.0f;

const int SEGL = 100;
const int RECTANGLES_FORK = 100;
const int RECTANGLES_LIMIT = 60;
const int INTIAL_POS = 2;
const int RECTANGLE = INTIAL_POS * 2 + 1;



/**
 * Represents a natural landscape with all its elements
 */
class LandScape {

    // Radius of the first part of the bifurcation
    float firstRadiusFork = sqrt(2.0f) * FORK_RADIUS;

    // Radius of the first part of the bifurcation
    float secondRadiusFork = FORK_RADIUS - sqrt(2.0f) * FORK_RADIUS;

    // Increment of axis X in each step of the bifurcation
    float xFork = static_cast<float>(FORK_RADIUS * sin(0.75f * M_PI));

    // Background
    Texture background;

    // Vector with the textures of the map element of the landscape
    vector<Texture> mapElementTextures;

    // Vector with the hit coefficients of the map element of the landscape
    vector<float> hittMapElementsCofs;

    // Vector with the kind of collisions coefficients of the map elements located in the map
    vector<HitThresholdObject> hitKindCofs;

    // Vector with the kind of scale coefficients of the map elements located in the map
    vector<float> scalingFactors;

    // Vector of steps of the landscape
    vector<Step> newLines;

    // Colors
    Color roadColor[2], grassColor[2], rumbleColor, dashColor;

    // Name of the landscape
    string name;

    // Coordinates of the camera
    float posCameraX, posCameraY;

    // Next map
    LandScape *nextLeft, *nextRight;

    // Control if a landScape is the initial or not
    bool startingLandScape;

    // Control if a landScape is the goal or not
    bool finalLandScape;

    // Control if a landscape is the middle or not
    bool middleLandScape;

    // Time to play in the landscape
    int timeToPlay;

    // Configurable width of the road
    int width_road;

    // Configurable width of the rumble`s road
    float limit_rumble;

    // Number of tracks of the toad
    int number_tracks;

    // Number of steps of the landscape
    int totalSteps;

    // Vector with the positions of the checkpoints
    vector<int>checkPointPositions;

    // Kind of terrain
    int terrain;

    // Texture of the goal car indicator
    Texture rowGoalCarIndicator;

    // Text indicator of the goal car
    Text goalCarIndicatorText;


    /**
     * Get the interval coordinates of any element of the scene
     * @param child is a pointer to the xml fils that points to a curve, mountain or sprite
     * @param objectCode controls what kind of element is been processed
     * @param startPos is going to store the initial interval position of the element of the scene
     * @param finalPos is going to store the initial interval position of the element of the scene
     */
    inline void getIntervalCoordinates(xml_node<> *child, int objectCode, int& startPos, int& finalPos);



    /**
     * Add a new step of the landscape read from the file
     * @param x is the actual coordinate 3d of the map in the axis x
     * @param y is the actual coordinate 3d of the map in the axis y
     * @param z is the actual coordinate 3d of the map in the axis z
     * @param prevY is the coordinate 3d of the map in the axis y of the last step added
     * @param curve represents the coefficient radius of the step to add to the map
     * @param mainColor shows in which color the step is going to be painted
     * @param spriteNearLeft is the map element located near and on the left of the road
     * @param spriteNearRight is the map element located near and on the right of the road
     * @param spriteFarLeft is the map element located far and on the left of the road
     * @param spriteFarRight is the map element located far and on the right of the road
     * @param eachNearLeft represents every few steps the map element located near and on
              the left of the road has to be displayed
     * @param eachNearRight represents every few steps the map element located near and on
              the right of the road has to be displayed
     * @param eachFarLeft represents every few steps the map element located far and on
              the left of the road has to be displayed
     * @param eachFarRight represents every few steps the map element located far and on
              the right of the road has to be displayed
     * @param codeNearLeft is the code of the map element located near and on the left on the road
     * @param codeNearRight is the code of the map element located near and on the right on the road
     * @param codeFarLeft is the code of the map element located far and on the left on the road
     * @param codeFarRight is the code of the map element located far and on the right on the road
     * @param generatedRandomNearLeft controls if the map element located near and on the left of the road
              has to be displayed in a random position
     * @param generatedRandomNearRight controls if the map element located near and on the right of the road
              has to be displayed in a random position
     * @param generatedRandomFarLeft controls if the map element located far and on the left of the road
              has to be displayed in a random position
     * @param generatedRandomFarRight controls if the map element located far and on the right of the road
              has to be displayed in a random position
     * @param checkPointOffset is the distance that separates the check point of the road
     * @param checkPointPos is the position in the landscape where the check point is drawn
     * @param codeCheckPoint is the code id of the map element which corresponds to the check point
     * @param checkPointDrawn controls if the check point has been drawn or not
     * @param bgX is the background position of the map in axis x
     * @param offsetX is the controller offset to make the bifurcations
     * @param offsetInc is partial offset to increment the bifurcation direction
     */
    inline void addStepFromFile(float& x, float y, float& z, float prevY, float curve, bool mainColor, MapElement& spriteNearLeft,
                                MapElement& spriteNearRight, MapElement& spriteFarLeft, MapElement& spriteFarRight, int& stepsRead,
                                int& eachNearLeft, int& eachNearRight, int& eachFarLeft, int& eachFarRight, int& startPos, float& leftOffset,
                                int& codeNearLeft, int& codeNearRight, int& codeFarLeft, int& codeFarRight, bool& generateRandomNearLeft,
                                bool& generateRandomNearRight, bool& generateRandomFarLeft, bool& generateRandomFarRight,
                                float& checkPointOffset, int& checkPointPos, int& codeCheckPoint, bool& checkPointDrawn, float &bgX,
                                float &offsetX, float offsetInc = 0.0f);



    /**
     * Add a new step of the landscape but not from the file
     * @param x is the actual coordinate 3d of the map in the axis x
     * @param y is the actual coordinate 3d of the map in the axis y
     * @param z is the actual coordinate 3d of the map in the axis z
     * @param prevY is the coordinate 3d of the map in the axis y of the last step added
     * @param curve represents the coefficient radius of the step to add to the map
     * @param mainColor shows in which color the step is going to be painted
     * @param spriteNearLeft is the map element located near and on the left of the road
     * @param spriteNearRight is the map element located near and on the right of the road
     * @param bgX is the background position of the map in axis x
     * @param offsetX is the controller offset to make the bifurcations
     * @param offsetInc is partial offset to increment the bifurcation direction
     */
    inline void addStep(float x, float y, float &z, float prevY, float curve, bool mainColor, const MapElement &spriteNearLeft,
                        const MapElement &spriteNearRight, float &bgX, float &offsetX, float offsetInc = 0.0f);


    /**
     * Return the step of the landscape with index n
     * @param n is the index of a landscape's step
     * @return
     */
    Step *getStep(int n);



    /**
     * Return the step of the landscape with index n
     * @param n is the index of a landscape's step
     * @return
     */
    Step getStep(int n) const;



    /**
     * Returns the previous step of the landscape to the step with index n
     * @param is the index of a landscape's step
     * @return
     */
    Step *getLastStep(int n);



    /**
     * Returns the previous step of the landscape to the step with index n
     * @param is the index of a landscape's step
     * @return
     */
    Step getLastStep(int n) const;



    /**
     * Read the map element properties stored in its xml configuration file
     * @param path is the path of the xml configuration file with the properties of the map element
     * @param hitC is the collision coefficient damage of the map element
     * @param scaleC is the scaling coefficient of the map element
     * @param hitCoeffType is the type of hitting coefficient of collision
     */
    inline void readMapElementProperties(const string path, float& hitC, float& scaleC, HitThresholdObject& hitCoeffType);



    /**
     * Load all the textures of the map elements located in the landscape
     * @param path is the path of the xml file which contains the configuration of the landscape
     * @param objectIndexes is a vector which contains the code ids of the map elements
     */
    void loadMapElements(const string &path, vector<int> &objectIndexes);



    /**
     * Process an interval of the landscape whose configuration is been read
     * @param roadNode is the xml node which contains the information of a part of the landscape
     * @param curveCoeff is the coefficient of the curve
     * @param elevation is the possible elevation of the terrain
     * @param mainColor is the color which is going to be used to paint this part of landscape
     * @param elevationIndex is the threshold to know if an elevation on the terrain has to be drawn
     * @param elevationLines indicates how many steps has the change of elevation
     * @param flatTerrain controls if the actual part of the landscape is flat or not
     * @param cordX is the actual 3d coordinate of the landscape in the axis x
     * @param cordY is the actual 3d coordinate of the landscape in the axis y
     * @param cordZ is the actual 3d coordinate of the landscape in the axis z
     * @param bgX is the actual background position of the landscape
     */
    inline void processRoadPart(xml_node<> * roadNode, float& curveCoeff, float& elevation, bool& mainColor,
                                int elevationIndex, int& elevationLines, bool flatTerrain, float& cordX,
                                float& cordY, float& cordZ, float& bgX);


    /**
     * Parses all the configuration of the color of the road written in the xml
     * configuration file of the scene
     * @param child is a node of the xml file that points to the color of the grass information
     */
    inline void parseColorGrassRoadScene(xml_node<> * child);



    /**
     * Parses all the configuration of the colors of the grass, the rumble of the road and the middle of the road
     * configuration file of the scene
     * @param color is a node of the xml file that points to the color of the middle of the road information
     * @param colorRed is where is going to be stored the value of the red channel in RGB color space read from the file
     * @param colorGreen is where is going to be stored the value of the green channel in RGB color space read from the file
     * @param colorBlue is where is going to be stored the value of the blue channel in RGB color space read from the file
     */
    inline void parseColors(xml_node<> * color, int& colorRed, int& colorGreen, int& colorBlue);



    /**
     * Parses the xml configuration file of a landscape of the game
     * @param pathFile is the path of the xml configuration file of the landscape
     */
    inline void parseLandScape(const string& pathFile);



    /**
     * Load the properties configuration of the landscape's road
     * @param pathRoadFile is the path of the file which contains the properties of the road
     */
    inline void loadRoadProperties(const string& pathRoadFile);



    /**
     * Draw how many tracks in the road as there has been specified in the road file configuration
     * @param w is the console window of the game
     * @param dash is the color which is going to be used to paint the tracks in the road
     * @param x1 is the lower left corner coordinate x of the rectangle to draw
     * @param w1 is the width of the rectangle to paint
     * @param y1 is the lower left corner coordinate y of the rectangle to draw
     * @param dw1 is the the half of the rectangle's width
     * @param x2 is the upper left corner coordinate x of the rectangle to draw
     * @param w2 is the height of the rectangle to paint
     * @param y2 is the upper left corner coordinate y of the rectangle to draw
     * @param dw2 is the the half of the rectangle's height
     */
    inline void drawRoadTracks(RenderTexture& w, Color& dash, const int x1, const int w1, const int y1,
                               const int dw1, const int x2, const int w2, const int y2, const int dw2);


public:



    /**
     * Default constructor
     */
    LandScape();



    /**
     * Creates a landscape reading its xml configuration file
     * @param c is the configuration of the game
     * @param path is the path of the xml file that contains the configuration of the landscape
     * @param bgName is the path of the image that represents the background of the landscape
     * @param time is the time available to complete the landscape
     * @param typeOfGame represents the game mode selected by the player
     * @param numRivals is the number of rivals in the multi player mode
     * @param onMultiplayer controls if the game is been played in multi player mode or not
     * @param typeOfGameMultiplayer represents the game selected to play in multi player mode
     */
    LandScape(Configuration &c, const string &path, const string &bgName, int time, const int typeOfGame, const int numRivals,
              const bool onMultiplayer, const int typeOfGameMultiplayer);



    /**
     * Creates a straight flat map which represents the starting point of a landscape
     * @param landscape is the landscape to be displayed
     * @param flagger is the flagger position while is announcing the start
     * @param semaphore is the color of the semaphore in the starting
     * @param numRivals is the number of rivals in the multi player mode
     * @param onMultiplayer control if the game is in multi player mode or not
     * @param codePlayerInGroup is the identifier code of the player in the multi player group
     */
    LandScape(const LandScape &landScape, int &flagger, int &semaphore, const int typeOfGame, const int numRivals,
              const bool onMultiplayer, const int codePlayerInGroup);



    /**
     * Creates a straight flat map which represents the starting point of a landscape
     * @param landscape is the landscape to be displayed
     * @param typeOfGame is the game selected by the player
     * @param numRivals is the number of rivals that are going to compete  against the player
     * @param onMultiplayer control if the game is in multi player mode or not
     * @param codePlayerInGroup is the identifier code of the player in the multi player group
     */
    LandScape(const LandScape &landScape, const int typeOfGame, const int numRivals, const bool onMultiplayer, const int codePlayerInGroup);



    /**
     * Creates a straight flat map which represents the goal point of a landscape
     * @param landscape is the landscape to be displayed
     * @param flagger is the flagger position while is announcing the goal
     * @param semaphore is the color of the semaphore in the goal
     * @param numRivals is the number of rivals in the multi player mode
     * @param onMultiplayer control if the game is in multi player mode or not
     * @param codePlayerInGroup is the identifier code of the player in the multi player group
     */
    LandScape(int &flagger, int &goalEnd, const int typeOfGame, const int numRivals, const bool onMultiplayer, const int codePlayerInGroup);



    /**
     * Initialize the colors of the landscape
     * @param landscape is the map whose colors are going to be initialized
     */
    void setColorsLandScape(const LandScape &landScape);



    /**
     * Increase the code id of the map element of the step if it exits
     * @param step is the actual step of the landscape with the map elements
     * @param right controls if there are more map elements of the step
     * @param increment is how to code id has to be increased
     */
    void addMapElelementIndex(int line, bool right, int increment = 1);



    /**
     * Add a landscape to follow the actual
     * @param landscape is the scenario to be added
     */
    void addNewLandScape(LandScape *landScape);



    /**
     * Create a fork between the actual landscape and its neighbors
     * @param left is the left landscape of the fork
     * @param right is the right landscape of the fork
     */
    void addFork(LandScape *left, LandScape *right);



    /**
     * Adds the offset to the landscape to be displayed correctly
     * @param yOffset is the offset to add
     */
    void setOffset(float yOffset);



    /**
     * Updates the postion of the camera in the landscape
     * @param pX is the new coordinate in the axis x of the camera
     * @param pY is the new coordinate in the axis y of the camera
     */
    void updateCamera(float pX, float pY);



    /**
     * Returns the coordiante x of the camera
     * @return
     */
    float getCameraPosX() const;



    /**
     * Returns the coordinate y of the camera
     * @return
     */
    float getCameraPosY() const;



    /**
     * Returns the name of the landscape
     * @return
     */
     string getName() const;



     /**
     * Returns the kind of terrain of the landscape
     * @return
     */
     int getTerrain() const;



    /**
     * Draws the percent of landscape visible with all the traffic cars in it
     * @param c is the configuration of the player
     * @param vehicles is the vector with all the traffic cars
     * @param carRivals is the vector with all the rival cars
     * @param typeOfGame is the game mode selected by the player for only one player
     * @param goalCar represents the goal car to chase in Driving Fury and Demarrage game modes
     * @param sortedMultiplayerCars is the vector with all the multi player cars
     * @param displayGoalIndicator controls if the goal indicator in DrivingFury have to be drawn
     * @param drawGoalCar controls if the goal car to chase in Driving Fury and Demarrage game modes has to be drawn
     * @param playingMultiplayer controls if the player is playing in multi player mode
     * @param currentLandScape represents the current landscape of the player in multi player mode
     */
    void drawLandScape(Configuration &c, vector<TrafficCar> &vehicles, vector<RivalCar> &carRivals,
                       const int typeOfGame, RivalCar& goalCar, vector<MultiplayerCar*> sortedMmultiplayerCars,
                       const bool displayGoalIndicator, const bool drawGoalCar, const bool playingMultiplayer, const int currentLandScape);



    /**
     * Returns true if the vehicle has crashed with any element of the landscape or with its borders
     * @param c is the configuration of the player
     * @param prevY is the previous position of the player in the axis y of the landscape
     * @param currentY is the actual position of the player in the axis y of the landscape
     * @param currentX is the actual position of the player in the axis x of the landscape
     * @param minX is the minimum threshold to detect a collision
     * @param maxX is the maximum threshold to detect a collision
     * @param crashPos is the possible position of crash detected
     * @return
     */
    bool hasCrashed(Configuration &c, float prevY, float currentY, float currentX, float minX, float maxX,
                    float &crashPos, const int typeOfGame) const;



    /**
     * Returns true if the actual position in axis x is outside the road.
     * Otherwise returns false
     * @param currentX is the position on axis x
     * @param currentY is the position on axis y
     * @return
     */
    bool isOutSideRoad(float currentX, float currentY) const;



    /**
     * Returns the curvature coefficient corresponding to the currentY rectangle. The coefficient is positive if the
     * curve is to the right, negative if it's to the left and 0 if it's a straight line
     * @param currentY currentY is the current of the landscape where is the player
     * @return
     */
    float getCurveCoefficient(float currentY) const;



    /**
     * Returns the elevation corresponding to the currentY rectangle based on the previous rectangle.
     * @param currentY is the current of the landscape where is the player
     * @return
     */
    Vehicle::Elevation getElevation(float currentY) const;



    /**
     * Returns true  if the landscae has been finished.
     * Otherwise returns false
     * @return
     */
    bool isOutSideLandScape() const;



    /**
     * Returns the height of the landscape
     * @return
     */
    float getMaxY() const;



    /**
     * Returns the offset of the road in the axis x.
     * @return
     */
    float getOffsetX() const;



    /**
     * Returns true if the player is on a fork. Otherwise returns false
     * @param currentY is the coordinate in axis y which to be tested to know
     *        if the player is on a fork or not
     * @return
     */
    bool inFork(float currentY) const;



    /**
     * Returns the next landscape or null if it is the last one
     * @return
     */
    LandScape *getNextLeft() const;



    /**
     * Returns true if is the init landscape. Otherwise returns false
     * @return
     */
    bool isStartingLandScape() const;



    /**
     * Returns true if is the goal landscape. Otherwise returns false
     * @return
     */
    bool isFinalLandScape() const;



    bool isMiddleMap() const;



    /**
     * Returns the time to complete the map
     * @return
     */
    int getTimeToPlay() const;



    /**
     * Returns the coordinates of the checkpoints
     * @return
     */
     vector<int> getCheckPointPositions() const;

};



/**
 * Draw a rectangle with a width and height in the screen console
 * @param w is the console window of the game
 * @param c is the color with the rectangle is going to be painted
 * @param x1 is the lower bound vertex coordinate in axis x of the rectangle
 * @param y1 is the lower bound vertex coordinate in axis y of the rectangle
 * @param w1 is the width of the rectangle
 * @param x2 is the upper bound vertex coordinate in axis x of the rectangle
 * @param y2 is the upper bound vertex coordinate in axis y of the rectangle
 * @param w2 is the height of the rectangle
 */
void drawQuad(RenderTexture &w, Color c, int x1, int y1, int w1, int x2, int y2, int w2);



/**
 * Returns true is the traffic car v1 is lower than the traffic car v2.
 * @param v1 is a traffic car
 * @param v2 is another traffic car
 * Otherwise returns false
 */
bool ascendingSortTrafficCars(const TrafficCar *v1, const TrafficCar *v2);



/**
 * Returns true is the traffic car v1 is lower than the traffic car v2.
 * @param v1 is a rival car
 * @param v2 is another rival car
 * Otherwise returns false
 */
bool ascendingSortRivalCars(const RivalCar *v1, const RivalCar *v2);



/**
 * Returns true is the traffic car v1 is lower than the traffic car v2.
 * @param v1 is a multi player rival car
 * @param v2 is another rival car
 * Otherwise returns false
 */
bool ascendingSortMultiplayerCars(const MultiplayerCar *v1, const MultiplayerCar *v2);



/**
 * Returns true is the position p1 in axis y is higher or equal to the position p2 in axis y
 * @param p1 is a concrete position in the axis y
 * @param p2 is a concrete position in the axis y
 * Otherwise returns false
 */
bool ascendingRanking(const float p1, const float p2);



#endif //OUTRUN_MAP_HPP
