#include "Step.h"
#include "SherwoodForest.h"


/**
 * Load all the sprites of the scene with their textures
 * @param t is a vector of textures empty
 * @param object is vector of sprites empty
 */
void SherwoodForest::loadSprites(Texture t[], Sprite object[]){
    // Load textures and sprites of the game
    t[0].loadFromFile("images/oak_tree.png");
    t[0].setSmooth(true);
    object[0].setTexture(t[0]);

    t[1].loadFromFile("images/mini_palm_tree.png");
    t[1].setSmooth(true);
    object[1].setTexture(t[1]);

    t[3].loadFromFile("images/palm_tree.png");
    t[3].setSmooth(true);
    object[3].setTexture(t[3]);

    t[4].loadFromFile("images/tree.png");
    t[4].setSmooth(true);
    object[4].setTexture(t[4]);

    t[5].loadFromFile("images/bush.png");
    t[5].setSmooth(true);
    object[5].setTexture(t[5]);

    t[6].loadFromFile("images/petrol_station.png");
    t[6].setSmooth(true);
    object[6].setTexture(t[6]);

}



/**
 * Print the sprites in the screen of the game
 * @param line is the actual step to process of the image
 * @param object is the array of sprites of the game
 * @param i is the index of the step which is going to be processed
 * Draws the a sprite in the step i of the screen game
 */
void SherwoodForest::printSpritesInScene(Step& line, Sprite object[], const int i){

    // Draw the tree sprite
    if ((i < 200  || i > 10500) && i % 15 == 0) {
        line.spriteX = -1.5;
        line.character = object[4];
    }
    // Draw the lamppost new sprite
    if (((i > 50 && i < 700) || (i > 10500)) && i % 20 == 0){
        line.spriteX = 0.5;
        line.character = object[5];
    }
    // Draw the palm_tree sprite
    if (i > 250 && i < 700 && i % 30 == 0){
        line.spriteX = -1;
        line.character = object[3];
    }
    // Draw the oak_tree sprite
    if (i > 800 && i < 10000 && i % 20 == 0) {
        line.spriteX = -1.2;
        line.character = object[0];
    }
    if (i > 800 && i < 10000 && i % 30 == 0) {
        line.spriteX = 0.5;
        line.character = object[1];
    }
    // Draw the petrol station sprite
    if (i % 400 == 0)  {
        line.spriteX = -1.5;
        line.character = object[6];
    }
    // Draw the petrol station sprite
    if (i % 700 == 0)  {
        line.spriteX = 0.5;
        line.character = object[6];
    }
}



/**
 * Print the mountains in the screen of the game
 * @param line is the actual step to process of the image
 * @param object is the array of sprites of the game
 * @param i is the index of the step which is going to be processed
 * Draws mountains in the scene of the game
 */
void SherwoodForest::printMountains(Step& line, const int i){
    // Drawing mountains with different pending
    if (i >= 1698 && i < 2388){
        line.position_3d_y = sin(i / 20.0) * 1500;
    }
    else if ((i > 754 && i <= 1600) ||
             (i >= 4618 && i <= 5277) ||
             (i >= 5750 && i < 6600))
    {
        line.position_3d_y = sin(i / 30.0) * 1500;
    }
    else if (i >= 7790 && i <= 8290){
        line.position_3d_y = sin(i / 80.0) * 2000;
    }
    else if (i >= 8295 && i <= 8798){
        line.position_3d_y = sin(i / 80.0) * -2000;
    }
    else if (i >= 9330 && i <= 9896){
        line.position_3d_y = sin(i / 90.0) * 2500;
    }
}



/**
 * Draw the curves of the game scene
 * @param line is the actual step of the scene
 * @param i is the index of the actual step of the scene
 * Draw a curve in the i step of the game scene
 */
void SherwoodForest::printCurves(Step& line, const int i){
    // First curve
    if (i >= 300 && i <= 600){
           line.directionCurve = 0.5;
    }
    // Second and sixth curves
    if ((i >= 1500 && i < 1700) || (i >= 3700 && i < 4000)){
        line.directionCurve = 1.5;
    }
    // Third curve
    if (i > 2300 && i < 2400){
        line.directionCurve = -1.3;
    }
    // Fourth curve
    if (i >= 3000 && i < 3500){
        line.directionCurve = 2.0;
    }
    // Fifth curve
    if (i >= 3500 && i < 3700){
        line.directionCurve = -0.3;
    }
    // Seventh curve
    if (i >= 4000 && i < 4500){
        line.directionCurve = -0.8;
    }
    // Eighth curve
    if (i >= 5000 && i < 5300){
        line.directionCurve = 0.6;
    }
    // Ninth curve
    if (i >= 5750 && i < 6600){
        line.directionCurve = -1.5;
    }
    // Tenth curve
    if (i >= 7900 && i < 8100){
        line.directionCurve = 3;
    }
    // Eleventh curve
    if (i >= 8100 && i < 8300){
        line.directionCurve = -3;
    }
    // Twelfth curve
    if (i >= 8800 && i < 9100){
        line.directionCurve = 0.9;
    }
    // Thirteenth curve
    if (i >= 9400 && i < 9700){
        line.directionCurve = -4;
    }
    // Thirteenth curve
    if (i >= 9700 && i < 9900){
        line.directionCurve = +4;
    }
    // Fourteenth curve
    if (i >= 10200 && i < 11000){
        line.directionCurve = -2;
    }
    // Penultimate curve
    if (i >= 11200 && i < 11500){
        line.directionCurve = +2;
    }
    // Ultimate curve
    if (i >= 11600 && i < 11900){
        line.directionCurve = -2.5;
    }
}
