
#ifndef NEPAL_H
#define NEPAL_H

#include "Step.h"
#include "Landscape.h"
#include "IntervalCurve.h"


using namespace sf;

class Vancouver : public LandScape {

    public:


        /**
         * Load the background of the landscape
         */
        void loadBackground();



        /**
         * Renders the landscape of the scene with all the elements
         * @param lines is a vector with all the information needed to create the scene
         */
        void renderLandScape(vector<Step>& lines, Sprite object[]);



        /**
         * Load all the sprites of the scene with their textures
         * @param t is a vector of textures empty
         * @param object is vector of sprites empty
         */
        void loadSprites(Texture t[], Sprite object[]);



        /**
         * Print the sprites in the screen of the game
         * @param line is the actual step to process of the image
         * @param object is the array of sprites of the game
         * @param i is the index of the step which is going to be processed
         * Draws the a sprite in the step i of the screen game
         */
        void printSpritesInScene(Step& line, Sprite object[], const int i);



        /**
         * Print the mountains in the screen of the game
         * @param line is the actual step to process of the image
         * @param object is the array of sprites of the game
         * @param i is the index of the step which is going to be processed
         * Draws mountains in the scene of the game
         */
        void printMountains(Step& line, const int i);



        /**
         * Draw the curves of the game scene
         * @param line is the actual step of the scene
         * @param i is the index of the actual step of the scene
         * Draw a curve in the i step of the game scene
         */
        void printCurves(Step& line, const int i);



        /**
         * Paint the scene in order to create the correct map
         * @param n is the step of the map which is going to be processed
         * @param grass is going to store in which color the grass is has to be painted
         * @param rumble is going to store in which color the rumble is has to be painted
         * @param middle is going to store in which color the middle is has to be painted
         * @param road is going to store in which color the road is has to be painted
         */
        void paintScene(const int n, Color& grass, Color& rumble, Color& middle, Color& road);



        /**
         * Order the different sprites of the landscape using the coordinate in axis Y
         */
        void orderSpritesInLandScape();



        /**
         * Get the element of the map which the nearest to the actual position
         * @param position_axis_Y is the actual coordinate of the player in the axis Y
         */
        Step checkingPossibleCollision(const int position_axis_Y);



        /**
         * Check if in the actual coordinate from axis Y pos there is a curve of not
         * using binary search
         * @param pos is the actual coordinate from axis Y
         * @param curve is where the possible curve will be stored
         * @param exist is a boolean which represents if there a curve or not in the coordinate pos
         */
        void lookForCurve(int& pos, IntervalCurve& curve, bool& exist);


};


#endif // NEPAL_H

