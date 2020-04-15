
#include "../include/Motorbike.h"

Motorbike::Motorbike(char* pathFile, Configuration* conf) : Player(pathFile, conf){};



/**
 * Draw the player sprite in the console render window
 * @param app is the console window game where the sprite is going to be drawn
 */
void Motorbike::drawPlayer(RenderWindow* app, int pos){
    this->offset = (mode == 0 && actual_code_image <= 35) ? offset += 10 : offset += 5;
    this->offset = (mode == 1 && actual_code_image <= 46) ? offset += 20 : offset;
    if (mode == -1) offset = 0;
    playerSprite.setPosition(Vector2f(465.f, HEIGHT - 190.f - offset));
    app->draw(playerSprite);
}



/**
 * Load the set of sprites of the player
 */
void Motorbike::loadVehicleProperties(const string path){
    Player::loadVehicleProperties(path);
}



/**
 * Check if the player has to advance in the track
 * @param eventDetected is a boolean to control if an event has occurred
 * @param lastHeight was the elevation of the terrain where was the motorbike
 * @param height is the actual elevation of the terrain where is the motorbike
 */
void Motorbike::advancePlayer(bool& eventDetected, const int lastHeight, const int height, Elevation& e){
    // Eliminate this event detection
    if (!eventDetected){
        if (actual_code_image != 1){
            // First advance sprite loaded
            actual_code_image = 1;
        }
        else {
            // Second advance sprite loaded
            actual_code_image = 2;
        }
        playerSprite.setTexture(textures[actual_code_image - 1], true);
        isAccelerating = false;
    }
    else {
        // Elimination of the last event registered
        eventDetected = false;
    }
}



/**
 * Establish the coordinate X and Y of the vehicle
 * @param pX is the coordinate of the vehicle in the axis X
 * @param pY is the coordinate of the vehicle in the axis Y
 */
void Motorbike::setPosition(float pX, float pY){
    Player::setPosition(pX, pY);
}



/**
 * Get the coordinate of the payer in the axis X
 * @return the position of the motorbike in the axis X
 */
float Motorbike::getPlayerX(){
    return Player::getPlayerX();
}



/**
 * Get the coordinate of the payer in the axis X
 * @return the position of the motorbike in the axis X
 */
float Motorbike::getPlayerY(){
    return Player::getPlayerY();
}



/**
 * Get the coordinate of the payer in the axis X
 * @return the position of the motorbike in the axis X
 */
float Motorbike::getPreviousY(){
    return Player::getPreviousY();
}



 /**
  * Get the coordinate of the payer in the axis X
  * @return the position of the motorbike in the axis X
  */
float Motorbike::getMinScreenX(){
    return Player::getMinScreenX();
}



 /**
  * Get the coordinate of the payer in the axis X
  * @return the position of the motorbike in the axis X
  */
float Motorbike::getMaxScreenX(){
    return Player::getMaxScreenX();
}



/**
 * Uodate the position of the vehicle
 */
void Motorbike::updatePositionY(const float speed){
    Player::updatePositionY(speed);
}



/**
 * Uodate the position of the vehicle
 */
void Motorbike::updatePosition(const float speed){
    Player::updatePosition(speed);
}



/**
 * Get the mode of collision of the motorbike
 * @return the mode to show the collision of the motorbike
 */
int Motorbike::getModeCollision(){
    return mode;
}



/**
 * Control if the user has pressed the q keyword to turn to the left
 * @param speed is the actual speed of the motorbike of the player
 * @param eventDetected is a boolean to control if an event has occurred
 * @param app is the console window game where the sprite is going to be drawn
 * @param lastHeight was the elevation of the terrain where was the motorbike
 * @param height is the actual elevation of the terrain where is the motorbike
 */
inline void Motorbike::controlTurningPlayerLeftKeyboard(int& speed, bool& eventDetected, RenderWindow* app,
                                             const int lastHeight, const int height, Elevation& e)
{
    // Check if key left pressed
    if (Keyboard::isKeyPressed(c->getLeftKey())){
        if (!isAccelerating){
            if (speed > INITIAL_SPEED){
                speed -= int(deceleration * speed_increment);
                if (speed < INITIAL_SPEED){
                    speed = INITIAL_SPEED;
                }
            }
        }
        // Check if the motorbike can be moved or not spite of pressing the key
        if (playerX - 0.1 >= BORDER_LIMIT_ROAD_LEFT){
            // Check if the motorbike is outside the road
            if (playerX >= BORDER_ROAD_LEFT && playerX <= BORDER_ROAD_RIGHT){
                // Advance more
                playerX -= 0.1;
            }
            else {
                 playerX -= 0.035;
            }
        }
        // Change the texture
        if (actual_code_image < 3 || (actual_code_image >= 9 && actual_code_image <= 16) ||
           (actual_code_image >= 23 && actual_code_image <= 28))
        {
            actual_code_image = 3;
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        else if (actual_code_image >= 3 && actual_code_image <= 8){
            // Increment the actual code of the sprite
            if (actual_code_image != 8){
                // Increment the texture of the sprite
                actual_code_image++;
            }
            else {
                // Change sprite while the motorbike is turning to left
                actual_code_image--;
            }
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        // Register event
        eventDetected = true;
    }
}



 /**
 * Control if the user has pressed the w keyword to turn to the right
 * @param speed is the actual speed of the motorbike of the player
 * @param eventDetected is a boolean to control if an event has occurred
 * @param app is the console window game where the sprite is going to be drawn
 * @param lastHeight was the elevation of the terrain where was the motorbike
 * @param height is the actual elevation of the terrain where is the motorbike
 */
inline void Motorbike::controlTurningPlayerRightKeyboard(int& speed, bool& eventDetected, RenderWindow* app,
                                              const int lastHeight, const int height, Elevation& e)
{
    // Check if key right pressed
    if (Keyboard::isKeyPressed(c->getRightKey())){
        // Check if the motorbike can be moved or not spite of pressing the key
        if (!isAccelerating){
            if (speed > INITIAL_SPEED){
                speed -= int(deceleration * speed_increment);
                if (speed < INITIAL_SPEED){
                    speed = INITIAL_SPEED;
                }
            }
        }
        if (playerX + 0.1 <= BORDER_LIMIT_ROAD_RIGHT){
            // Check if the motorbike is outside the road
            if (playerX >= BORDER_ROAD_LEFT && playerX <= BORDER_ROAD_RIGHT){
                // Advance more
                playerX += 0.1;
            }
            else {
                 playerX += 0.035;
            }
        }
        // Change the texture
        if (actual_code_image < 9 || (actual_code_image >= 15 && actual_code_image <= 22)){
            actual_code_image = 9;
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        else if (actual_code_image <= 14){
            // Increment the actual code of the sprite
            if (actual_code_image != 14){
                // Increment the texture of the sprite
                actual_code_image++;
            }
            else {
                // Change sprite while the motorbike is turning to left
                actual_code_image--;
            }
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        // Register event
        eventDetected = true;
    }
}



/**
 * Control if the user has pressed the q keyword to turn to the left
 * @param speed is the actual speed of the motorbike of the player
 * @param eventDetected is a boolean to control if an event has occurred
 * @param app is the console window game where the sprite is going to be drawn
 */
inline void Motorbike::controlTurningPlayerLeftMouse(int& speed, bool& eventDetected, RenderWindow* app){
    // Get the x coordinate of the mouse in the window
    int coordinateX = sf::Mouse::getPosition(*app).x;
    // Check if key right pressed
    if (coordinateX < (int)app->getSize().x / 3  ){
        // Check if the motorbike can be moved or not spite of pressing the key
        if (playerX - 0.1 >= BORDER_LIMIT_ROAD_LEFT){
            // Check if the motorbike is outside the road
            if (playerX >= BORDER_ROAD_LEFT && playerX <= BORDER_ROAD_RIGHT){
                // Advance more
                playerX -= 0.1;
            }
            else {
                 playerX -= 0.035;
            }
        }
        // Change the texture
        if (actual_code_image < 3 || (actual_code_image >= 9 && actual_code_image <= 16) ||
           (actual_code_image >= 23 && actual_code_image <= 28))
        {
            actual_code_image = 3;
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        else if (actual_code_image >= 3 && actual_code_image <= 8){
            // Increment the actual code of the sprite
            if (actual_code_image != 8){
                // Increment the texture of the sprite
                actual_code_image++;
            }
            else {
                // Change sprite while the motorbike is turning to left
                actual_code_image--;
            }
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        // Register event
        eventDetected = true;
    }
}



/**
 * Control if the user has pressed the w keyword to turn to the right
 * @param speed is the actual speed of the motorbike of the player
 * @param eventDetected is a boolean to control if an event has occurred
 * @param app is the console window game where the sprite is going to be drawn
 */
inline void Motorbike::controlTurningPlayerRightMouse(int& speed, bool& eventDetected, RenderWindow* app){
    // Get the x coordinate of the mouse in the window
    int coordinateX = sf::Mouse::getPosition(*app).x;
    // Check if key right pressed
    if (coordinateX > 2 * (int)(app->getSize().x / 3)){
        // Check if the motorbike can be moved or not spite of pressing the key
        if (playerX + 0.1 <= BORDER_LIMIT_ROAD_RIGHT){
            // Check if the motorbike is outside the road
            if (playerX >= BORDER_ROAD_LEFT && playerX <= BORDER_ROAD_RIGHT){
                // Advance more
                playerX += 0.1;
            }
            else {
                 playerX += 0.035;
            }
        }
        // Change the texture
        if (actual_code_image < 9 || (actual_code_image >= 15 && actual_code_image <= 22)){
            actual_code_image = 9;
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        else if (actual_code_image <= 14){
            // Increment the actual code of the sprite
            if (actual_code_image != 14){
                // Increment the texture of the sprite
                actual_code_image++;
            }
            else {
                // Change sprite while the motorbike is turning to left
                actual_code_image--;
            }
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        // Register event
        eventDetected = true;
    }
}



/**
 * Control if the user has pressed the q keyword to increase the speed
 * @param speed is the actual speed of the motorbike of the player
 * @param eventDetected is a boolean to control if an event has occurred
 * @param app is the console window game where the sprite is going to be drawn
 * @param lastHeight was the elevation of the terrain where was the motorbike
 * @param height is the actual elevation of the terrain where is the motorbike
 */
inline void Motorbike::controlPlayerSpeed(int& speed, bool& eventDetected, RenderWindow* app,
                                          const int lastHeight, const int height, Elevation& e)
{
    // Check if the user is accelerating
    if ((sf::Keyboard::isKeyPressed(c->getAccelerateKey()))){
        isAccelerating = true;
        // Control about not acceleration if the motorbike goes in the grass
        if (playerX >= BORDER_ROAD_LEFT && playerX <= BORDER_ROAD_RIGHT){
            // Increment the speed because it is inside the road
            if (speed <= maxSpeed){
                // Increment of the speed
                speed += int(acceleration * (speed_increment + speed_increment));
                if (speed > maxSpeed){
                    speed = maxSpeed;
                }
            }
        }
        else {
            // Increment the speed because it is outside the road
            if (speed >= INITIAL_SPEED){
                // Decrement of the speed
                speed -= int(deceleration * (speed_increment + speed_increment));
                if (speed < INITIAL_SPEED){
                    speed = INITIAL_SPEED;
                }
            }
        }
        // Check if the key to turn left is pressed
        if (!eventDetected){
            // Check the type of control of the motorbike
            if (typeControl == 0){
                 // Check if the key to turn to the right is pressed
                 isAccelerating = false;
                 controlTurningPlayerRightKeyboard(speed, eventDetected, app, lastHeight, height, e);
            }
            else {
                // Check if the mouse has been moved to turn to the right
                controlTurningPlayerRightMouse(speed, eventDetected, app);
            }
            return;
        }
        // Check if the key to turn left is pressed
        if (!eventDetected){
            // Check the type of control of the motorbike
            if (typeControl == 0){
                 // Check if the key to turn to the left is pressed
                 isAccelerating = false;
                 controlTurningPlayerLeftKeyboard(speed, eventDetected, app, lastHeight, height, e);
            }
            else {
                // Check if the mouse has been moved to turn to the left
                controlTurningPlayerLeftMouse(speed, eventDetected, app);
            }
            return;
        }
        // Change the sprite of the motorbike
        if (actual_code_image == 2 && eventDetected){
            // Change the sprite;
            actual_code_image = 1;
            // Set the texture from the file
            isAccelerating = false;
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        // Change the sprite of the motorbike
        else if (actual_code_image == 1 && eventDetected){
            // Change the sprite
            actual_code_image = 2;
            // Set the texture from the file
            isAccelerating = false;
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
    }
    else {
        isAccelerating = false;
    }
}



/**
 * Control if the user has pressed the q keyword to increase the speed
 * @param speed is the actual speed of the motorbike of the player
 * @param eventDetected is a boolean to control if an event has occurred
 * @param app is the console window game where the sprite is going to be drawn
 * @param lastHeight was the elevation of the terrain where was the motorbike
 * @param height is the actual elevation of the terrain where is the motorbike
 */
inline void Motorbike::controlPlayerBraking(int& speed, bool& eventDetected, RenderWindow* app,
                                            const int lastHeight, const int height, Elevation& e)
{
    // Check if the user is braking
    if (Keyboard::isKeyPressed(c->getBrakeKey())){
        isAccelerating = false;
        // Check more events
        if (!eventDetected){
            // Control if first the user has accelerated
            controlPlayerSpeed(speed, eventDetected, app, lastHeight, height, e);
        }
        // Selection of the correct sprite of the motorbike
        if (actual_code_image <= 2){
            actual_code_image = 15;
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        else if (actual_code_image == 15){
            actual_code_image = 16;
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        else if (actual_code_image == 16){
            actual_code_image = 15;
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        else if (actual_code_image >= 3 && actual_code_image <= 8){
            actual_code_image += 14;
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        else if (actual_code_image >= 9 && actual_code_image <= 14){
            actual_code_image += 14;
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        else if (actual_code_image >= 17 && actual_code_image <= 22){
            // Increment the actual code of the sprite
            if (actual_code_image != 22){
                // Increment the texture of the sprite
                actual_code_image++;
            }
            else {
                // Change sprite while the motorbike is turning to left
                actual_code_image--;
            }
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        else if (actual_code_image >= 23 && actual_code_image <= 28){
            // Increment the actual code of the sprite
            if (actual_code_image != 28){
                // Increment the texture of the sprite
                actual_code_image++;
            }
            else {
                // Change sprite while the motorbike is turning to left
                actual_code_image--;
            }
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        // Reduce the speed
        if (speed > INITIAL_SPEED){
            // Increment of the speed
            speed -= int(deceleration * (speed_increment + speed_increment));
            if (speed < INITIAL_SPEED){
                speed = INITIAL_SPEED;
            }
        }
        // Detect event
        eventDetected = true;
    }
}



/**
 * Control if the player has done any of his possible actions
 * @param speed is the actual speed of the motorbike of the player
 * @param eventDetected is a boolean to control if an event has occurred
 * @param app is the console window game where the sprite is going to be drawn
 * @param lastHeight was the elevation of the terrain where was the motorbike
 * @param height is the actual elevation of the terrain where is the motorbike
 */
void Motorbike::controlActionPlayer(int& speed, bool& eventDetected, RenderWindow* app,
                                    const int lastHeight, const int height, Elevation& e)
{
    if (typeControl == 0){
        // Keyword
        // Check if W keyword has been pressed to turn to the right
        controlTurningPlayerRightKeyboard(speed, eventDetected, app, lastHeight, height, e);

        // Check if Q keyword has been pressed to turn to the left
        controlTurningPlayerLeftKeyboard(speed, eventDetected, app, lastHeight, height, e);
    }
    else {
        // Check if the mouse has has been moved to turn to the right
        controlTurningPlayerRightMouse(speed, eventDetected, app);

        // Check if the mouse has has been moved to turn to the left
        controlTurningPlayerLeftMouse(speed, eventDetected, app);
    }

    //Check if the E keyword has been pressed to brake the motorbike
    controlPlayerBraking(speed, eventDetected, app, lastHeight, height, e);

    // Check if any event has been registered
    if (!eventDetected){
        // Reduce the speed
        if (speed > INITIAL_SPEED){
            // Increment of the speed
            speed -= int(deceleration);
            if (speed < INITIAL_SPEED){
                speed = INITIAL_SPEED;
            }
        }
    }

    // Check if the Up keyword has been pressed to increase the speed
    controlPlayerSpeed(speed, eventDetected, app, lastHeight, height, e);
}



/**
 * Control if the player has have collision with the nearest element of the map to him
 * @param nearestStep is the step of the scene where is located the nearest element to the player
 * @param lastPos is the last position of the motorbike in the axis Y
 * @param pos is the current position of the motorbike in the axis Y
 */
bool Motorbike::controlPossibleCollision(Step& nearestStep, int lastPos, int pos){
    // Calculation of the distance
    float distance = nearestStep.spriteX - playerX;
    // Check the sign of the offset
    if (distance > 0){
        // Right
        // Check if the coordinates in the axis X are more less equal to have a collision
        if (distance >= nearestStep.offset - 0.2 && distance <= nearestStep.offset + 0.075){
            // Check if there is a direct collision or indirect collision in axis Y
            if ((pos == nearestStep.spriteY) || (lastPos <= nearestStep.spriteY && nearestStep.spriteY <= pos)){
                // Collision
                return true;
            }
            else {
                // There is not collision in spite the coordinates in axis X are equal
                return false;
            }
        }
        // There is not collision because the coordinates in axis X are different
        return false;
    }
    else {
        // Left
        // Check if the coordinates in the axis X are more less equal to have a collision
        if (distance >= nearestStep.offset - 0.075 && distance <= nearestStep.offset + 0.2){
            // Check if there is a direct collision or indirect collision in axis Y
            if ((pos == nearestStep.spriteY) || (lastPos <= nearestStep.spriteY && nearestStep.spriteY <= pos)){
                // Collision
                return true;
            }
            else {
                // There is not collision in spite the coordinates in axis X are equal
                return false;
            }
        }
        // There is not collision because the coordinates in axis X are different
        return false;
    }
}



/**
 * Control if there is there inertia force or not if the motorbike is on a curve of the scene
 * @param onCurve is a boolean which represents if the motorbike is on curve or not
 * @param curve is the possible curve of the scene where the motorbike is currently now
 * @param speed is the actual speed of the motorbike of the player
 */
void Motorbike::controlInertiaForce(bool& onCurve, IntervalCurve& curve, int& speed){
    if (onCurve){
        // The Ferrari is on a curve of the scene
        onCurve = false;
        // Check the direction of the curve
        if (curve.directionCurve > 0.f){
            // Check if the Ferrari
            if (speed >= mediumSpeed){
                // Ferrari goes to the left when it is a right curve
                playerX -= 0.075;
            }
            else if (speed >= controlSpeed && speed < mediumSpeed) {
                playerX -= 0.045;
            }
            else {
                playerX -= 0.015;
            }
        }
        else {
            // Check if the Ferrari
            if (speed >= mediumSpeed){
                // Ferrari goes to the left when it is a right curve
                playerX += 0.075;
            }
            else if (speed >= controlSpeed && speed < mediumSpeed) {
                playerX += 0.045;
            }
            else {
                playerX += 0.015;
            }
        }
    }
}



/**
 * Shows to the user how the motorbikes crushes
 */
void Motorbike::collisionShow(){
    // Not collision detected before
    if (mode == -1){
        // Code generated to the way of collision
        // Pseudo generator of aleatory number in order to generate randomly the way of collision
        srand(time(NULL));
        mode = rand() % 2;
        // Establish the first collision sprite
        if (mode == 0){
            // First way to collision
            actual_code_image = 28;
        }
        else if (mode == 1) {
            // Second way to collision
            actual_code_image = 42;
        }
    }
    else {
        // Collision detected in process
        // Avoid overflow of code number identifier of collision sprite
        if (actual_code_image != 41 && actual_code_image != 52){
            // Add to have the sprite in the range of collision
            actual_code_image++;
            // Check what is the way to see the collision
            if (mode == 0){
                // Set the texture from the file
                playerSprite.setTexture(textures[actual_code_image - 1]);
                if (actual_code_image == 41){
                    actual_code_image = 1;
                    mode = -1;
                    playerX = 0.f;
                }
            }
            else if (mode == 1) {
                // Change the actual sprite of the collision with the second mode
                playerSprite.setTexture(textures[actual_code_image - 1]);
                if (actual_code_image == 52){
                    actual_code_image = 1;
                    mode = -1;
                    playerX = 0.f;
                }
            }
        }
    }
}



bool Motorbike::hasCrashed(float prevY, float currentY, float minX, float maxX, Map* m)  {
    Step* l;
    for (int n = int(m->getPosY()); n < int(m->getPosY()) + 300; n++) {
        l = m->getLine(n);
        if (l->spriteLeft.spriteNum != -1 && l->spriteLeft.spriteMinX != l->spriteLeft.spriteMaxX && // l has an object that can crash
                prevY <= float(n) && currentY >= float(n) && // y matches
                ((minX >= l->spriteLeft.spriteMinX && minX <= l->spriteLeft.spriteMaxX) ||
                 (maxX >= l->spriteLeft.spriteMinX && maxX <= l->spriteLeft.spriteMaxX) ||
                 (l->spriteLeft.spriteMinX >= minX && l->spriteLeft.spriteMinX <= maxX) ||
                 (l->spriteLeft.spriteMaxX >= minX && l->spriteLeft.spriteMaxX <= maxX)))
            {
                mode = 1;
                return true;
            }
        if (l->spriteRight.spriteNum != -1 && l->spriteRight.spriteMinX != l->spriteRight.spriteMaxX && // l has an object that can crash
                prevY <= float(n) && currentY >= float(n) && // y matches
                ((minX >= l->spriteRight.spriteMinX && minX <= l->spriteRight.spriteMaxX) ||
                 (maxX >= l->spriteRight.spriteMinX && maxX <= l->spriteRight.spriteMaxX) ||
                 (l->spriteRight.spriteMinX >= minX && l->spriteRight.spriteMinX <= maxX) ||
                 (l->spriteRight.spriteMaxX >= minX && l->spriteRight.spriteMaxX <= maxX)))
            {
                mode = 0;
                return true;
            }
    }
    return false;
}





