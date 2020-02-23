#include "Step.h"
#include "SherwoodForest.h"


/**
 * Load the background of the landscape
 */
void SherwoodForest::loadBackground(){
    bg.loadFromFile("images/bg.png");
    // Set repetition of texture active and assignation
    bg.setRepeated(true);
    sBackground.setTexture(bg);
    // Fix the dimensions of the rectangle which contains the texture
    sBackground.setTextureRect(IntRect(-3000, 0, 5000, 411));
    // Assign the position of the texture
    sBackground.setPosition(-2000,0);
}



/**
 * Renders the landscape of the scene with all the elements
 * @param lines is a vector with all the information needed to create the scene
 */
void SherwoodForest::renderLandScape(vector<Step>& lines, Sprite object[]){
    // For each step walked
    for(int i = 0; i <= MAX_SPACE_DIMENSION - 1; i++){
        // Creation of the line and justify its depth in the 3d dimension
       Step line;
       line.position_3d_z = i * segL;

       // Drawing the curves of the game scene
       SherwoodForest::printCurves(line, i);

       // Drawing the possible mountain in the step i of the scene
       SherwoodForest::printMountains(line, i);

       // Draw the possible sprites in the step i of the scene
       SherwoodForest::printSpritesInScene(line, object, i);

       // Added vector
       lines.push_back(line);
    }
}




/**
 * Load all the sprites of the scene with their textures
 * @param t is a vector of textures empty
 * @param object is vector of sprites empty
 */
void SherwoodForest::loadSprites(Texture t[], Sprite object[]){
    // Load textures and sprites of the game
    t[0].loadFromFile("images/fir_tree.png");
    t[0].setSmooth(true);
    object[0].setTexture(t[0]);

    t[1].loadFromFile("images/green_tree.png");
    t[1].setSmooth(true);
    object[1].setTexture(t[1]);

    t[3].loadFromFile("images/green_tree2.png");
    t[3].setSmooth(true);
    object[3].setTexture(t[3]);

    t[4].loadFromFile("images/green_tree3.png");
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

    // Draw the tree sprite and store its coordinates
    if ((i < 200 || i > 10500) && i % 25 == 0) {
        // Establishing coordinates and sprite
        line.spriteX = -2.0f;
        line.spriteY = i * segL;
        line.character = object[4];
        line.offset = line.spriteX + LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    // Draw the lamppost new sprite and store its coordinates
    if (((i > 50 && i < 700) || (i > 10500)) && i % 25 == 0){
        // Establishing coordinates and sprite
        line.spriteX = 3.1f;
        line.spriteY = i * segL;
        line.character = object[5];
        line.offset = line.spriteX - LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    // Draw the palm_tree sprite and store its coordinates
    if (i > 250 && i < 700 && i % 45 == 0){
        // Establishing coordinates and sprite
        line.spriteX = -1.6f;
        line.spriteY = i * segL;
        line.character = object[3];
        line.offset = line.spriteX + LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    // Draw the oak_tree sprite and store its coordinates
    if (i > 800 && i < 10000 && i % 20 == 0) {
        // Establishing coordinates and sprite
        line.spriteX = -3.2f;
        line.spriteY = i * segL;
        line.character = object[0];
        line.offset = line.spriteX + LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    // Draw the palm_tree sprite and store its coordinates
    if (i > 800 && i < 10000 && i % 30 == 0) {
        // Establishing coordinates and sprite
        line.spriteX = 0.9f;
        line.spriteY = i * segL;
        line.character = object[1];
        line.offset = line.spriteX - LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    // Draw the petrol station sprite and store its coordinates
    if (i % 700 == 0)  {
        // Establishing coordinates and sprite
        line.spriteX = 2.5f;
        line.spriteY = i * segL;
        line.character = object[6];
        line.offset = line.spriteX - LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
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
    if (i >= 1698 && i < 2546){
        line.position_3d_y = sin(i / 30.0) * 1500;
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

    // Check if the vector is empty
    if (curvesInScene.empty()){
        // Creation of all interval curves
        IntervalCurve iC1 = IntervalCurve(300 * segL, 600 * segL, 0.5);       IntervalCurve iC2 = IntervalCurve(1500 * segL, 1699 * segL, 1.5);
        IntervalCurve iC3 = IntervalCurve(2301 * segL, 2399 * segL, -1.3);    IntervalCurve iC4 = IntervalCurve(3000 * segL, 3499 * segL, 2);
        IntervalCurve iC5 = IntervalCurve(3500 * segL, 3699 * segL, -0.3);    IntervalCurve iC6 = IntervalCurve(3700 * segL, 3999 * segL, 1.5);
        IntervalCurve iC7 = IntervalCurve(4000 * segL, 4499 * segL, -0.8);    IntervalCurve iC8 = IntervalCurve(5000 * segL, 5299 * segL, 0.6);
        IntervalCurve iC9 = IntervalCurve(5750 * segL, 6599 * segL, -1.5);    IntervalCurve iC10 = IntervalCurve(7900 * segL, 8099 * segL, 3);
        IntervalCurve iC11 = IntervalCurve(8100 * segL, 8299 * segL, -3);     IntervalCurve iC12 = IntervalCurve(8800 * segL, 9099 * segL, 0.9);
        IntervalCurve iC13 = IntervalCurve(9400 * segL, 9699 * segL, -4);     IntervalCurve iC14 = IntervalCurve(9700 * segL, 9899 * segL, 4);
        IntervalCurve iC15 = IntervalCurve(10200 * segL, 10999 * segL, -2);   IntervalCurve iC16 = IntervalCurve(11200 * segL, 11499 * segL, 2);
        IntervalCurve iC17 = IntervalCurve(11600 * segL, 11899 * segL, -2.5);

        // Adding all intervals to the vector of interval of the scene
        curvesInScene.push_back(iC1);  curvesInScene.push_back(iC2);  curvesInScene.push_back(iC3);  curvesInScene.push_back(iC4);
        curvesInScene.push_back(iC5);  curvesInScene.push_back(iC6);  curvesInScene.push_back(iC7);  curvesInScene.push_back(iC8);
        curvesInScene.push_back(iC9);  curvesInScene.push_back(iC10); curvesInScene.push_back(iC11); curvesInScene.push_back(iC12);
        curvesInScene.push_back(iC13); curvesInScene.push_back(iC14); curvesInScene.push_back(iC15); curvesInScene.push_back(iC16);
        curvesInScene.push_back(iC17);
    }
}


/**
 * Paint the scene in order to create the correct map
 * @param n is the step of the map which is going to be processed
 * @param grass is going to store in which color the grass is has to be painted
 * @param rumble is going to store in which color the rumble is has to be painted
 * @param middle is going to store in which color the middle is has to be painted
 * @param road is going to store in which color the road is has to be painted
 */
void SherwoodForest::paintScene(const int n, Color& grass, Color& rumble, Color& middle, Color& road){
    // Determination of the color to paint in the screen
    if ((n / 3) % 2){
        grass = Color(16, 200, 16);
        rumble = Color(255, 255, 255);
        middle = Color(255, 255, 255);
    }
    else {
        grass = Color(0, 154, 0);
        rumble = Color(255, 0, 0);
        middle = Color(77, 77, 77);
    }
    road = Color(77, 77, 77);
}



/**
 * Order the sprites of the scene by their coordinates in axis Y. If there
 * are more than one sprite with the same coordinate in axis Y, sprites
 * are ordered in axis X
 */
void SherwoodForest::orderSpritesInLandScape(){
    // Order the sprites of the scene using the universal method of the father class
    LandScape::orderSpritesInLandScape();
}



/**
 * Detect which is the last sprite with the motorbike could have a collision
 * @param position_axis_Y is the coordinate in the axis Y of the motorbike
 */
Step SherwoodForest::checkingPossibleCollision(const int position_axis_Y){
    // Checking the possible collisions using the universal method of the father class
    return LandScape::checkingPossibleCollision(position_axis_Y);
}



/**
 * Check if in the actual coordinate from axis Y pos there is a curve of not
 * using binary search
 * @param pos is the actual coordinate from axis Y
 * @param curve is where the possible curve will be stored
 * @param exist is a boolean which represents if there a curve or not in the coordinate pos
 */
void SherwoodForest::lookForCurve( int& pos, IntervalCurve& curve, bool& exist){
    // Looking for the curves using the universal method of the father class
    LandScape::lookForCurve(pos, curve, exist);
}
