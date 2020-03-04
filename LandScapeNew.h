
#pragma once

#include <vector>
#include <iostream>
#include <cstring>
#include "Step.h"
#include "IntervalCurve.h"
#include "Mountain.h"
#include "MapElement.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace sf;

using namespace rapidxml;

const int MAX_ELEMENTS = 20;



struct LandScapeNew {

        // Vector of Steps of the scene where there are sprites accessed by children classes
        vector<Step> stepsWithSprite;

        // Vector of interval of curves of the scene
        vector<IntervalCurve> curvesInScene;

        // Vector of interval of curves of the scene
        vector<IntervalCurve> curves;

        // Vector of mountains of the the scene
        vector<Mountain> mountains;

        // Vector with the paths of the sprites
        vector<string> spritePaths;

        // Texture of the background
        Texture bg;

        // Sprite where the image of the background is going to be loaded
        Sprite sBackground;

        // Name of the circuit
        string name;

        // Texture and sprite vectors
        Texture t[MAX_ELEMENTS];
        Sprite object[MAX_ELEMENTS];

        // Colors to represent the road
        vector<Color> colors_grass;

        // Colors to represent the rumble
        vector<Color> colors_rumble;

        // Colors to represent the middle of the road
        vector<Color> colors_middle;

        // Unique color of the road
        Color color_road;

        // Elements of the map
        vector<MapElement> elementsOfMap;

        // Vector of textures loaded
        vector<bool>textures = vector<bool>(MAX_ELEMENTS);

        // Number of textures loaded
        int texturesLoaded = 0;

        // Vector of steps to do
        vector<Step> lines = vector<Step>(MAX_SPACE_DIMENSION);



        /**
         *
         */
        LandScapeNew(char* path);



        /**
         * Get the sprite which contains the background
         */
        Sprite getBackGround();



        /**
         * Get the sprite which contains the background
         */
        void setBackGround(Sprite sBack);



        /**
         * Load the background of the landscape
         */
        void loadBackground(const string path, const int lowerLeft, const int upperLeft,
                            const int lowerRight, const int upperRight, const int x_center,
                            const int y_center);


        /**
         * Load all the sprites of the scene with their textures
         * @param t is a vector of textures empty
         * @param object is vector of sprites empty
         */
        void loadSprites(vector<string>& spritesPaths);



        /**
         * Get the element of the map which the nearest to the actual position
         * @param position_axis_Y is the actual coordinate of the player in the axis Y
         */
        Step checkingPossibleCollision(const int position_axis_Y);



        /**
         * Determines if there is a curve to print or not in the position of the map pos
         * @param pos is the position of the map to evaluate if there is a curve or not
         * @param curve is the possible curve in which interval of coordinates is located pos
         * @param exists is a boolean to control if there is curve to print or not in the position of the map pos
         */
        void lookForCurveToPrint(int& pos, IntervalCurve& curve, bool& exist);



        /**
         * Determines if there is a curve or not in the position of the map pos
         * @param pos is the position of the map to evaluate if there is a curve or not
         * @param curve is the possible curve in which interval of coordinates is located pos
         * @param exists is a boolean to control if there is curve or not in the position of the map pos
         */
        void lookForCurve(int& pos, IntervalCurve& curve, bool& exist);



        /**
         * Determines if there is a mountain or not in the position of the map pos
         * @param pos is the position of the map to evaluate if there is a mountain or not
         * @param m is the possible mountain in which interval of coordinates is located pos
         * @param exists is a boolean to control if there is mountain or not in the position of the map pos
         */
        void lookForMountain(int& pos, Mountain& m, bool& exist);



        /**
         * Determines if there is a mountain or not in the position of the map pos
         * @param m is a vector where all the possible sprites to print are going to be kept
         * @param exists is a boolean to control if there are sprites or not in the position of the map pos
         */
        void lookForMapElement(int& pos, vector<MapElement>& m, bool& exist);



        /**
         * Order the curves and the mountains of the map using the coordinates of the map X and Y
         */
        void orderElementsInLandScape();



        /**
         * Print the possible curve of the map which can be stored in the position of the map i
         * @param i is the step or position index of the map where is going to be evaluated if
         * there is or not curve
         */
        void printCurves(int i);



        /**
         * Print the possible mountain of the map which can be stored in the position of the map i
         * @param i is the step or position index of the map where is going to be evaluated if
         * there is or not mountain
         */
        void printMountains(int i);



        /**
         * Print the possible sprite of the map which can be stored in the position of the map i
         * @param i is the step or position index of the map where is going to be evaluated if
         * there is or not sprite
         */
        void printSprites(int i);



        /**
         * Render the landscape appearance and the step of the map
         * @param n is the index of the map position to be processed
         * @param grass is the color which is going to be used to paint the grass of the scene
         * @param rumble is the color which is going to be used to paint the rumble of the scene
         * @param middle is the color which is going to be used to paint the middle road of the scene
         * @param road is the color which is going to be used to paint the road of the scene
         */
        void paintScene(const int n, Color& grass, Color& rumble, Color& middle, Color& road);
};

