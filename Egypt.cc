#include "Step.h"
#include "Egypt.h"


/**
 * Load the background of the landscape
 */
void Egypt::loadBackground(){
    bg.loadFromFile("images/Egypt/desert.jpg");
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
void Egypt::renderLandScape(vector<Step>& lines, Sprite object[]){
    // For each step walked
    for(int i = 0; i <= MAX_SPACE_DIMENSION - 1; i++){
        // Creation of the line and justify its depth in the 3d dimension
       Step line;
       line.position_3d_z = i * segL;

       // Drawing the curves of the game scene
       Egypt::printCurves(line, i);

       // Drawing the possible mountain in the step i of the scene
       Egypt::printMountains(line, i);

       // Draw the possible sprites in the step i of the scene
       Egypt::printSpritesInScene(line, object, i);

       // Added vector
       lines.push_back(line);
    }
}




/**
 * Load all the sprites of the scene with their textures
 * @param t is a vector of textures empty
 * @param object is vector of sprites empty
 */
void Egypt::loadSprites(Texture t[], Sprite object[]){
    // Load textures and sprites of the game
    t[0].loadFromFile("images/Egypt/palm_tree.png");
    t[0].setSmooth(true);
    object[0].setTexture(t[0]);

    t[1].loadFromFile("images/Egypt/palm_tree_inverted.png");
    t[1].setSmooth(true);
    object[1].setTexture(t[1]);

    t[3].loadFromFile("images/Egypt/dry_tree.png");
    t[3].setSmooth(true);
    object[3].setTexture(t[3]);

    t[4].loadFromFile("images/Egypt/dry_tree2.png");
    t[4].setSmooth(true);
    object[4].setTexture(t[4]);

    t[5].loadFromFile("images/Egypt/cactus.png");
    t[5].setSmooth(true);
    object[5].setTexture(t[5]);

    t[6].loadFromFile("images/Egypt/dry_tree3.png");
    t[6].setSmooth(true);
    object[6].setTexture(t[6]);

    t[7].loadFromFile("images/Egypt/elephant.png");
    t[7].setSmooth(true);
    object[7].setTexture(t[7]);

    t[8].loadFromFile("images/Egypt/camel.png");
    t[8].setSmooth(true);
    object[8].setTexture(t[8]);

    t[9].loadFromFile("images/Egypt/pyramid.png");
    t[9].setSmooth(true);
    object[9].setTexture(t[9]);

    t[10].loadFromFile("images/Egypt/signal_go.png");
    t[10].setSmooth(true);
    object[10].setTexture(t[10]);

    t[11].loadFromFile("images/Egypt/signal_bus.png");
    t[11].setSmooth(true);
    object[11].setTexture(t[11]);

    t[12].loadFromFile("images/Egypt/signal_50.png");
    t[12].setSmooth(true);
    object[12].setTexture(t[12]);
}



/**
 * Print the sprites in the screen of the game
 * @param line is the actual step to process of the image
 * @param object is the array of sprites of the game
 * @param i is the index of the step which is going to be processed
 * Draws the a sprite in the step i of the screen game
 */
void Egypt::printSpritesInScene(Step& line, Sprite object[], const int i){

    // Draw the oak_tree sprite and store its coordinates
    if (i > 800 && i < 11900 && i % 20 == 0) {
        // Establishing coordinates and sprite
        line.spriteX = -2.3f;
        line.spriteY = i * segL;
        line.character = object[0];
        line.offset = line.spriteX + LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    // Draw the palm_tree sprite and store its coordinates
    if (i > 800 && i < 11900 && i % 30 == 0) {
        // Establishing coordinates and sprite
        line.spriteX = +1.3f;
        line.spriteY = i * segL;
        line.character = object[1];
        line.offset = line.spriteX - LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
     // Draw the palm_tree sprite and store its coordinates
    if (i > 250 && i < 700 && i % 45 == 0){
        // Establishing coordinates and sprite
        line.spriteX = -3.3f;
        line.spriteY = i * segL;
        line.character = object[3];
        line.offset = line.spriteX + LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    // Draw the tree sprite and store its coordinates
    if ((i < 200 || i > 10500) && i % 20 == 0) {
        // Establishing coordinates and sprite
        line.spriteX = -3.8f;
        line.spriteY = i * segL;
        line.character = object[4];
        line.offset = line.spriteX + LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    // Draw the lamppost new sprite and store its coordinates
    if (((i > 50 && i < 700) || (i > 10500)) && i % 25 == 0){
        // Establishing coordinates and sprite
        line.spriteX = 4.2f;
        line.spriteY = i * segL;
        line.character = object[5];
        line.offset = line.spriteX - LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
     // Draw the petrol station sprite and store its coordinates
    if (i % 505 == 0)  {
        // Establishing coordinates and sprite
        line.spriteX = -8.6f;
        line.spriteY = i * segL;
        line.character = object[6];
        line.offset = line.spriteX + LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    // Draw the cow_up sprite and store its coordinates
    if (i >= 900 && i <= 11500 && i % 57 == 0)  {
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
        line.spriteX = -(rand() % 8 + 3.f);
        line.spriteY = i * segL;
        line.character = object[8];
        line.offset = line.spriteX + LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    // Draw the cow_up sprite and store its coordinates
    if (i % 601 == 0)  {
        // Establishing coordinates and sprite
        line.spriteX = rand() % 3 + 3.f;
        line.spriteY = i * segL;
        line.character = object[9];
        line.offset = line.spriteX - LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    if (i % 303 == 0)  {
        // Establishing coordinates and sprite
        line.spriteX = -(rand() % 3 + 3.5f);
        line.spriteY = i * segL;
        line.character = object[9];
        line.offset = line.spriteX + LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    if (i % 100 == 0)  {
        // Establishing coordinates and sprite
        line.spriteX = (rand() % 3 + 3.5f);
        line.spriteY = i * segL;
        line.character = object[9];
        line.offset = line.spriteX - LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    if (i % 300 == 0)  {
        // Establishing coordinates and sprite
        line.spriteX = -2.f;
        line.spriteY = i * segL;
        line.character = object[9];
        line.offset = line.spriteX + LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    if (i % 200 == 0)  {
        // Establishing coordinates and sprite
        line.spriteX = 1.f;
        line.spriteY = i * segL;
        line.character = object[9];
        line.offset = line.spriteX - LIMIT_BORDER;
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
        line.spriteX = -4.5f;
        line.spriteY = i * segL;
        line.character = object[11];
        line.offset = line.spriteX + LIMIT_BORDER;
        // Adding the step with the sprite and its coordinates to the list
        stepsWithSprite.push_back(line);
    }
    if (i % 500 == 0)  {
        // Establishing coordinates and sprite
        line.spriteX = 3.8f;
        line.spriteY = i * segL;
        line.character = object[12];
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
void Egypt::printMountains(Step& line, const int i){
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
void Egypt::printCurves(Step& line, const int i){
    // First curve
    if (i >= 50 && i <= 100){
        line.directionCurve = -3;
    }
    // Second and curve
    if (i >= 300 && i < 500){
        line.directionCurve = 1.5;
    }
    // Third curve
    if (i >= 500 && i < 800){
        line.directionCurve = -1.3;
    }
    // Fourth curve
    if (i >= 800 && i < 1200){
        line.directionCurve = 3;
    }
    // Fifth curve
    if (i >= 1200 && i <= 1400){
        line.directionCurve = -3;
    }
    // Sixth curve
    if (i > 1500 && i < 1800){
        line.directionCurve = 4;
    }
    // Seventh curve
    if (i >= 1800 && i <= 2050){
        line.directionCurve = -5;
    }
    // Eighth curve
    if (i >= 2200 && i < 2300){
        line.directionCurve = 0.7;
    }
    // Ninth curve
    if (i >= 2500 && i < 2800){
        line.directionCurve = 4;
    }
    // Tenth curve
    if (i >= 2900 && i < 3300){
        line.directionCurve = -0.5;
    }
    // Eleventh curve
    if (i >= 3800 && i < 4300){
        line.directionCurve = -0.5;
    }
    // Twelfth curve
    if (i >= 4500 && i < 5000){
        line.directionCurve = 5;
    }
    // Thirteenth curve
    if (i >= 5400 && i < 6000){
        line.directionCurve = -1.3;
    }
    // Fourteenth curve
    if (i >= 6300 && i < 7000){
        line.directionCurve = +1.3;
    }
    // Fifteenth curve
    if (i >= 7900 && i < 8100){
        line.directionCurve = 3;
    }
    // Sixteenth curve
    if (i >= 8500 && i < 8700){
        line.directionCurve = -4;
    }
    // Seventeenth curve
    if (i >= 8700 && i < 9000){
        line.directionCurve = 5;
    }
    // Eighteenth curve
    if (i >= 9400 && i < 9700){
        line.directionCurve = -4;
    }
    // Nineteenth curve
    if (i >= 10000 && i < 10600){
        line.directionCurve = 1;
    }
    // Twentieth curve
    if (i >= 10700 && i < 10900){
        line.directionCurve = -4;
    }
    // Penultimate curve
    if (i >= 10900 && i < 11500){
        line.directionCurve = +2;
    }
    // Ultimate curve
    if (i >= 11500 && i < 11900){
        line.directionCurve = -2.5;
    }

    // Check if the vector is empty
    if (curvesInScene.empty()){
        // Creation of all interval curves
        IntervalCurve iC1 = IntervalCurve(50 * segL, 100 * segL, -3.f);      IntervalCurve iC2 = IntervalCurve(300 * segL, 500 * segL, 1.5f);
        IntervalCurve iC3 = IntervalCurve(500 * segL, 799 * segL, -1.3f);    IntervalCurve iC4 = IntervalCurve(800 * segL, 1200 * segL, 3.f);
        IntervalCurve iC5 = IntervalCurve(1201 * segL, 1400 * segL, -3.f);  IntervalCurve iC6 = IntervalCurve(1501 * segL, 1799 * segL, 4.f);
        IntervalCurve iC7 = IntervalCurve(1800 * segL, 2050 * segL, -5.f);  IntervalCurve iC8 = IntervalCurve(2200 * segL, 2299 * segL, 0.7f);
        IntervalCurve iC9 = IntervalCurve(2500 * segL, 2799 * segL, 4.f);  IntervalCurve iC10 = IntervalCurve(2900 * segL, 3299 * segL, -0.5f);
        IntervalCurve iC11 = IntervalCurve(3800 * segL, 4299 * segL, -0.5f);    IntervalCurve iC12 = IntervalCurve(4500 * segL, 4999 * segL, 5.f);
        IntervalCurve iC13 = IntervalCurve(5400 * segL, 5999 * segL, -1.3f);  IntervalCurve iC14 = IntervalCurve(6300 * segL, 6999 * segL, 1.3f);
        IntervalCurve iC15 = IntervalCurve(7900 * segL, 8099 * segL, 3.f);      IntervalCurve iC16 = IntervalCurve(8500 * segL, 8699 * segL, -4.f);
        IntervalCurve iC17 = IntervalCurve(8700 * segL, 8999 * segL, 5.f);    IntervalCurve iC18 = IntervalCurve(9400 * segL, 9699 * segL, -4.f);
        IntervalCurve iC19 = IntervalCurve(10000 * segL, 10599 * segL, 1.f);  IntervalCurve iC20 = IntervalCurve(10700 * segL, 10899 * segL, -4.f);
        IntervalCurve iC21 = IntervalCurve(10900 * segL, 11499 * segL, 2.f);  IntervalCurve iC22 = IntervalCurve(11500 * segL, 11899 * segL, -2.5f);

        // Adding all intervals to the vector of interval of the scene
        curvesInScene.push_back(iC1);  curvesInScene.push_back(iC2);  curvesInScene.push_back(iC3);  curvesInScene.push_back(iC4);
        curvesInScene.push_back(iC5);  curvesInScene.push_back(iC6);  curvesInScene.push_back(iC7);  curvesInScene.push_back(iC8);
        curvesInScene.push_back(iC9);  curvesInScene.push_back(iC10); curvesInScene.push_back(iC11); curvesInScene.push_back(iC12);
        curvesInScene.push_back(iC13); curvesInScene.push_back(iC14); curvesInScene.push_back(iC15); curvesInScene.push_back(iC16);
        curvesInScene.push_back(iC17); curvesInScene.push_back(iC18); curvesInScene.push_back(iC19); curvesInScene.push_back(iC20);
        curvesInScene.push_back(iC21); curvesInScene.push_back(iC22);
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
void Egypt::paintScene(const int n, Color& grass, Color& rumble, Color& middle, Color& road){
    // Determination of the color to paint in the screen
    if ((n / 3) % 2){
        grass = Color(250, 217, 139);
        rumble = Color(255, 255, 255);
        middle = Color(255, 255, 255);
    }
    else {
        grass = Color(229, 193, 111);
        rumble = Color(77, 77, 77);
        middle = Color(77, 77, 77);
    }
    road = Color(77, 77, 77);
}



/**
 * Order the sprites of the scene by their coordinates in axis Y. If there
 * are more than one sprite with the same coordinate in axis Y, sprites
 * are ordered in axis X
 */
void Egypt::orderSpritesInLandScape(){
    // Order the sprites of the scene using the universal method of the father class
    LandScape::orderSpritesInLandScape();
}



/**
 * Detect which is the last sprite with the motorbike could have a collision
 * @param position_axis_Y is the coordinate in the axis Y of the motorbike
 */
Step Egypt::checkingPossibleCollision(const int position_axis_Y){
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
void Egypt::lookForCurve( int& pos, IntervalCurve& curve, bool& exist){
    // Looking for the curves using the universal method of the father class
    LandScape::lookForCurve(pos, curve, exist);
}
