
#ifndef SHER_WOOD_FOREST_H
#define SHER_WOOD_FOREST_H

#include "Step.h"
#include "Landscape.h"

using namespace sf;

class SherwoodForest : public LandScape {

    public:

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
};


#endif // SHER_WOORD_FOREST_H

