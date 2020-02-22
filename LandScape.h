
#include "Step.h"
#include "IntervalCurve.h"
#include <vector>
#include <iostream>

using namespace std;

using namespace sf;

const int MIN_NUMBER = 200;
const int MAX_NUMBER = 11000;
const int MIN_DURATION = 200;
const int MAX_DURATION = 3000;
const int NUMBER_CURVES = 16;

class LandScape {

    protected:

        // List of Steps of the scene where there are sprites accessed by children classes
        vector<Step> stepsWithSprite;

        // List of interval of curves of the scene
        vector<IntervalCurve> curvesInScene;


    public:


        /**
         * Load all the sprites of the scene with their textures
         * @param t is a vector of textures empty
         * @param object is vector of sprites empty
         */
        virtual void loadSprites(Texture t[], Sprite object[]) = 0;



        /**
         * Print the sprites in the screen of the game
         * @param line is the actual step to process of the image
         * @param object is the array of sprites of the game
         * @param i is the index of the step which is going to be processed
         * Draws the a sprite in the step i of the screen game
         */
        virtual void printSpritesInScene(Step& line, Sprite object[], const int i) = 0;



        /**
         * Print the mountains in the screen of the game
         * @param line is the actual step to process of the image
         * @param object is the array of sprites of the game
         * @param i is the index of the step which is going to be processed
         * Draws mountains in the scene of the game
         */
        virtual void printMountains(Step& line, const int i) = 0;



        /**
         * Draw the curves of the game scene
         * @param line is the actual step of the scene
         * @param i is the index of the actual step of the scene
         * Draw a curve in the i step of the game scene
         */
        virtual void printCurves(Step& line, const int i) = 0;



        /**
         * Order the different sprites of the landscape using the coordinate in axis Y
         */
        void orderSpritesInLandScape(){
            // Ordenation of the vector
            sort(stepsWithSprite.begin(), stepsWithSprite.end());
        }


        /**
         * Get the element of the map which the nearest to the actual position
         * @param position_axis_Y is the actual coordinate of the player in the axis Y
         */
        Step checkingPossibleCollision(const int position_axis_Y){
            // Indexes of the binary search
            int init = 0, last = stepsWithSprite.size() - 1, medium;
            // Loop for find the sprite
            while (init != last){
                // Central sprite obtained
                medium = (init + last) / 2;
                // Check if the last sprite is on the left or on the right
                if (stepsWithSprite.at(medium).spriteY <= position_axis_Y){
                    // Right
                    init = medium + 1;
                }
                else {
                    // Left
                    last = medium;
                }
            }
            // Check if the last sprite passed is in the same position of the motorbike
            if (stepsWithSprite.at(init).spriteY == position_axis_Y){
                // Get that sprite
                return stepsWithSprite.at(init);
            }
            else {
                // Get the last found because the collision could have occurred during the movement
                return stepsWithSprite.at(init - 1);
            }
        }



        /**
         * Check if in the actual coordinate from axis Y pos there is a curve of not
         * using binary search
         * @param pos is the actual coordinate from axis Y
         * @param curve is where the possible curve will be stored
         * @param exist is a boolean which represents if there a curve or not in the coordinate pos
         */
        void lookForCurve(int& pos, IntervalCurve& curve, bool& exist){
            // Defect value of the boolean variable
            exist = false;
            // Indexes of the binary search
            int init = 0, last = curvesInScene.size() - 1, medium;
            // Loop for find the sprite
            while (init <= last){
                // Central sprite obtained
                medium = (init + last) / 2;
                // Check if the last sprite is on the left or on the right
                if (pos >= curvesInScene.at(medium).startCurvePosition &&
                    pos <= curvesInScene.at(medium).finalCurvePosition)
                {
                    // Right
                    exist = true;
                    break;
                }
                else if (pos > curvesInScene.at(medium).startCurvePosition &&
                         pos > curvesInScene.at(medium).startCurvePosition)
                {
                    // Left
                    init = medium + 1;
                }
                else if (pos < curvesInScene.at(medium).startCurvePosition &&
                         pos < curvesInScene.at(medium).finalCurvePosition)
                {
                    last = medium - 1;
                }
            }
            // Check if the last sprite passed is in the same position of the motorbike
            if (exist){
                // Get that sprite
                curve = curvesInScene.at(medium);
            }
        }

};
