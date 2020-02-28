#include "Step.h"
#include "Tokio.h"


/**
 * Load the background of the landscape
 */
void Tokio::loadBackground(){
    bg.loadFromFile("images/Tokio/background.png");
    // Set repetition of texture active and assignation
    bg.setRepeated(true);
    sBackground.setTexture(bg);
    // Fix the dimensions of the rectangle which contains the texture
    sBackground.setTextureRect(IntRect(-2000, 0, 5000, 411));
    // Assign the position of the texture
    sBackground.setPosition(-2000, 0);
}



/**
 * Renders the landscape of the scene with all the elements
 * @param lines is a vector with all the information needed to create the scene
 */
void Tokio::renderLandScape(vector<Step>& lines, Sprite object[]){
    // For each step walked
    for(int i = 0; i <= MAX_SPACE_DIMENSION - 1; i++){
        // Creation of the line and justify its depth in the 3d dimension
       Step line;
       line.position_3d_z = i * segL;

       // Drawing the curves of the game scene
       Tokio::printCurves(line, i);

       // Drawing the possible mountain in the step i of the scene
       Tokio::printMountains(line, i);

       // Draw the possible sprites in the step i of the scene
       Tokio::printSpritesInScene(line, object, i);

       // Added vector
       lines.push_back(line);
    }
}




/**
 * Load all the sprites of the scene with their textures
 * @param t is a vector of textures empty
 * @param object is vector of sprites empty
 */
void Tokio::loadSprites(Texture t[], Sprite object[]){
    // Load textures and sprites of the game
    t[0].loadFromFile("images/Tokio/fir_tree.png");
    t[0].setSmooth(true);
    object[0].setTexture(t[0]);

    t[1].loadFromFile("images/Tokio/green_tree.png");
    t[1].setSmooth(true);
    object[1].setTexture(t[1]);

    t[4].loadFromFile("images/Tokio/bush.png");
    t[4].setSmooth(true);
    object[4].setTexture(t[4]);

    t[5].loadFromFile("images/Tokio/street_light.png");
    t[5].setSmooth(true);
    object[5].setTexture(t[5]);

    t[6].loadFromFile("images/Tokio/pagoda.png");
    t[6].setSmooth(true);
    object[6].setTexture(t[6]);

    t[7].loadFromFile("images/Tokio/pagoda2.png");
    t[7].setSmooth(true);
    object[7].setTexture(t[7]);

    t[8].loadFromFile("images/Tokio/dry_tree.png");
    t[8].setSmooth(true);
    object[8].setTexture(t[8]);

    t[9].loadFromFile("images/Tokio/signal_go.png");
    t[9].setSmooth(true);
    object[9].setTexture(t[9]);

    t[10].loadFromFile("images/Tokio/signal_bus.png");
    t[10].setSmooth(true);
    object[10].setTexture(t[10]);

    t[11].loadFromFile("images/Tokio/signal_50.png");
    t[11].setSmooth(true);
    object[11].setTexture(t[11]);

}



/**
 * Print the sprites in the screen of the game
 * @param line is the actual step to process of the image
 * @param object is the array of sprites of the game
 * @param i is the index of the step which is going to be processed
 * Draws the a sprite in the step i of the screen game
 */
void Tokio::printSpritesInScene(Step& line, Sprite object[], const int i){

    // Draw the oak_tree sprite and store its coordinates
    if (i > 100 && i < 10500 && i % 54 == 0) {
        // Establishing coordinates and sprite
        line.spriteX = -3.2f;
        line.spriteY = i * segL;
        line.character = object[0];
        line.offset = line.spriteX + LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    // Draw the palm_tree sprite and store its coordinates
    if (i > 800 && i < 11900 && i % 30 == 0) {
        // Establishing coordinates and sprite
        line.spriteX = 1.1f;
        line.spriteY = i * segL;
        line.character = object[1];
        line.offset = line.spriteX - LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    // Draw the tree sprite and store its coordinates
    if ((i < 200 || i > 10500) && i % 30 == 0) {
        // Establishing coordinates and sprite
        line.spriteX = -3.8f;
        line.spriteY = i * segL;
        line.character = object[4];
        line.offset = line.spriteX + LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    // Draw the lamppost new sprite and store its coordinates
    if (i > 75 && i < 10400 && i % 25 == 0){
        // Establishing coordinates and sprite
        line.spriteX = 0.7f;
        line.spriteY = i * segL;
        line.character = object[5];
        line.offset = line.spriteX - LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
     // Draw the petrol station sprite and store its coordinates
    if (i % 250 == 0)  {
        // Establishing coordinates and sprite
        line.spriteX = -3.f;
        line.spriteY = i * segL;
        line.character = object[6];
        line.offset = line.spriteX + LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    // Draw the cow_up sprite and store its coordinates
    if (i >= 900 && i <= 11500 && i % 45 == 0)  {
        // Establishing coordinates and sprite
        line.spriteX = rand() % 8 + 3.f;
        line.spriteY = i * segL;
        line.character = object[7];
        line.offset = line.spriteX - LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    // Draw the cow_up sprite and store its coordinates
    if (i >= 500 && i <= 1000 && i % 63 == 0)  {
        // Establishing coordinates and sprite
        line.spriteX = -(rand() % 8 + 3.f);
        line.spriteY = i * segL;
        line.character = object[8];
        line.offset = line.spriteX + LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    // Draw the cow_up sprite and store its coordinates
    if (i >= 750 && i <= 10500 && i % 47 == 0)  {
        // Establishing coordinates and sprite
        line.spriteX = -(rand() % 8 + 4.f);
        line.spriteY = i * segL;
        line.character = object[8];
        line.offset = line.spriteX + LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    if (i % 300 == 0)  {
        // Establishing coordinates and sprite
        line.spriteX = 4.f;
        line.spriteY = i * segL;
        line.character = object[9];
        line.offset = line.spriteX + LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    if (i % 370 == 0)  {
        // Establishing coordinates and sprite
        line.spriteX = 3.8f;
        line.spriteY = i * segL;
        line.character = object[10];
        line.offset = line.spriteX - LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    if (i % 350 == 0)  {
        // Establishing coordinates and sprite
        line.spriteX = -4.8f;
        line.spriteY = i * segL;
        line.character = object[11];
        line.offset = line.spriteX + LIMIT_BORDER;
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
void Tokio::printMountains(Step& line, const int i){
    // Drawing mountains with different pending
    // Drawing mountains with different pending
    if (i >= 504 && i < 2640){
        line.position_3d_y = sin(i / 40.0) * 1500;
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
    else if (i >= 9990 && i <= 11876){
        line.position_3d_y = sin(i / 60.0) * 2500;
    }
}



/**
 * Draw the curves of the game scene
 * @param line is the actual step of the scene
 * @param i is the index of the actual step of the scene
 * Draw a curve in the i step of the game scene
 */
void Tokio::printCurves(Step& line, const int i){
    // First curve
    if (i >= 203 && i <= 456){
        line.directionCurve = -2.f;
    }
    // Second curve
    else if (i > 456 && i < 800){
        line.directionCurve = +2.f;
    }
    // Third curve
    else if (i >= 800 && i <= 900){
        line.directionCurve = -3.f;
    }
    // Fourth curve
    else if (i >= 1000 && i <= 1200){
        line.directionCurve = -2.5f;
    }
    // Fifth curve
    else if (i > 1200 && i <= 1500){
        line.directionCurve = 4.f;
    }
    // Sixth curve
    else if (i > 1800 && i <= 2100){
        line.directionCurve = 0.7f;
    }
    // Seventh curve
    else if (i > 2300 && i <= 2400){
        line.directionCurve = +0.7f;
    }
    // Eighth curve
    else if (i > 2400 && i <= 3000){
        line.directionCurve = -1.5f;
    }
    // Ninth curve
    else if (i >= 3000 && i < 3200){
        line.directionCurve = 1.5f;
    }
    // Tenth curve
    else if (i >= 3200 && i < 4000){
        line.directionCurve = 0.3f;
    }
    // Eleventh curve
    else if (i >= 4000 && i < 4700){
        line.directionCurve = -0.3f;
    }
    // Twelfth curve
    else if (i >= 5000 && i < 5400){
        line.directionCurve = -1.2f;
    }
    // Thirteenth curve
    else if (i >= 5600 && i <= 5800){
        line.directionCurve = 1.2f;
    }
    // Fourteenth curve
    else if (i >= 6000 && i <= 6500){
        line.directionCurve = -0.5f;
    }
    // Fifteenth curve
    else if (i >= 7000 && i <= 8000){
        line.directionCurve = 1.f;
    }
    // Sixteenth curve
    else if (i >= 8200 && i <= 8500){
        line.directionCurve = -1.2f;
    }
    // Seventeenth curve
    else if (i > 9000 && i <= 9300){
        line.directionCurve = -3.5f;
    }
    // Eighteenth curve
    else if (i > 9600 && i <= 10000){
        line.directionCurve = 2.5f;
    }
    // Penultimate curve
    else if (i >= 10400 && i < 11000){
        line.directionCurve = 1.f;
    }
    // Ultimate curve
    else if (i >= 11000 && i < 11800){
        line.directionCurve = -1.f;
    }

    /*
    // Check if the vector is empty
    if (curvesInScene.empty()){
        // Creation of all interval curves
        IntervalCurve iC1 = IntervalCurve(203 * segL, 456 * segL, 2.f);       IntervalCurve iC2 = IntervalCurve(457 * segL, 799 * segL, -2.f);
        IntervalCurve iC3 = IntervalCurve(800 * segL, 900 * segL, 3.f);       IntervalCurve iC4 = IntervalCurve(1000 * segL, 1200 * segL, -2.5f);
        IntervalCurve iC5 = IntervalCurve(1201 * segL, 1500 * segL, 4.f);     IntervalCurve iC6 = IntervalCurve(1801 * segL, 2100 * segL, -0.7f);
        IntervalCurve iC7 = IntervalCurve(2301 * segL, 2400 * segL, -0.7f);   IntervalCurve iC8 = IntervalCurve(2401 * segL, 2700 * segL, -3.5f);
        IntervalCurve iC9 = IntervalCurve(3000 * segL, 3199 * segL, 3.5f);    IntervalCurve iC10 = IntervalCurve(3300 * segL, 3999 * segL, 0.8f);
        IntervalCurve iC11 = IntervalCurve(4000 * segL, 4699 * segL, 0.8f);   IntervalCurve iC12 = IntervalCurve(5000 * segL, 5399 * segL, -1.2f);
        IntervalCurve iC13 = IntervalCurve(5600 * segL, 5800 * segL, 1.2f);   IntervalCurve iC14 = IntervalCurve(6000 * segL, 6500 * segL, -0.5f);
        IntervalCurve iC15 = IntervalCurve(7000 * segL, 8000 * segL, 0.3f);   IntervalCurve iC16 = IntervalCurve(8200 * segL, 8500 * segL, 3.5f);
        IntervalCurve iC17 = IntervalCurve(9001 * segL, 9300 * segL, 3.5f);   IntervalCurve iC18 = IntervalCurve(9601 * segL, 10000 * segL, -2.5f);
        IntervalCurve iC19 = IntervalCurve(10400 * segL, 10799 * segL, 1.f);  IntervalCurve iC20 = IntervalCurve(11000 * segL, 10799 * segL, -0.5f);

        // Adding all intervals to the vector of interval of the scene
        curvesInScene.push_back(iC1);  curvesInScene.push_back(iC2);  curvesInScene.push_back(iC3);  curvesInScene.push_back(iC4);
        curvesInScene.push_back(iC5);  curvesInScene.push_back(iC6);  curvesInScene.push_back(iC7);  curvesInScene.push_back(iC8);
        curvesInScene.push_back(iC9);  curvesInScene.push_back(iC10); curvesInScene.push_back(iC11); curvesInScene.push_back(iC12);
        curvesInScene.push_back(iC13); curvesInScene.push_back(iC14); curvesInScene.push_back(iC15); curvesInScene.push_back(iC16);
        curvesInScene.push_back(iC17); curvesInScene.push_back(iC18); curvesInScene.push_back(iC19); curvesInScene.push_back(iC20);
    }
    */
}


/**
 * Paint the scene in order to create the correct map
 * @param n is the step of the map which is going to be processed
 * @param grass is going to store in which color the grass is has to be painted
 * @param rumble is going to store in which color the rumble is has to be painted
 * @param middle is going to store in which color the middle is has to be painted
 * @param road is going to store in which color the road is has to be painted
 */
void Tokio::paintScene(const int n, Color& grass, Color& rumble, Color& middle, Color& road){
    // Determination of the color to paint in the screen
    if ((n / 5) % 2){
        grass = Color(0, 0, 102);
        rumble = Color(255, 255, 255);
        middle = Color(255, 255, 255);
    }
    else {
        grass = Color(0, 0, 179);
        rumble = Color(0, 0, 26);
        middle = Color(0, 0, 26);
    }
    road = Color(0, 0, 26);
}



/**
 * Order the sprites of the scene by their coordinates in axis Y. If there
 * are more than one sprite with the same coordinate in axis Y, sprites
 * are ordered in axis X
 */
void Tokio::orderSpritesInLandScape(){
    // Order the sprites of the scene using the universal method of the father class
    LandScape::orderSpritesInLandScape();
}



/**
 * Detect which is the last sprite with the motorbike could have a collision
 * @param position_axis_Y is the coordinate in the axis Y of the motorbike
 */
Step Tokio::checkingPossibleCollision(const int position_axis_Y){
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
void Tokio::lookForCurve( int& pos, IntervalCurve& curve, bool& exist){
    // Looking for the curves using the universal method of the father class
    LandScape::lookForCurve(pos, curve, exist);
}
