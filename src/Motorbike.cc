
#include "../include/Motorbike.h"

Motorbike::Motorbike(char* pathFile) : Player(pathFile){};



/**
 * Draw the player sprite in the console render window
 * @param app is the console window game where the sprite is going to be drawn
 */
void Motorbike::drawPlayer(RenderWindow& app){
    this->offset = (mode == 0 && actual_code_image <= 35) ? offset += 10 : offset += 5;
    this->offset = (mode == 1 && actual_code_image <= 46) ? offset += 20 : offset;
    if (mode == -1) offset = 0;
    playerSprite.setPosition(Vector2f(465.f, HEIGHT - 190.f - offset));
    app.draw(playerSprite);
}



/**
 * Load the set of sprites of the player
 */
void Motorbike::loadSpritesFromPath(){
    // Document xml where the document is going to be parsed
    xml_document<> doc;
    file<> file("Configuration/Vehicles/Motorbike.xml");
    // Parsing the content of file
    doc.parse<0>(file.data());

    // Get the principal node of the file
    xml_node<> *nodePlayer = doc.first_node();

    // Loop in order to iterate all the children of the principal node
    for (xml_node<> *child = nodePlayer->first_node(); child; child = child->next_sibling()){
        // Check if the actual node is the controller of the paths of the sprites
        if ((string)child->name() == "SpritePaths"){
            // Loop for iterate throughout the path files and add then to the vector
            for (xml_node<> * pathNode = child->first_node(); pathNode; pathNode = pathNode->next_sibling()){
                // Add the texture to the vector
                if (t.loadFromFile(string(filePath) + pathNode->value())){
                    // Increment the textures read
                    textures.push_back(t);
                }
            }
        }
        else {
            // Error the tag has not been found
            cerr << "The file must have the tag SpritePaths defined" << endl;
            exit(12);
        }
    }
    // Load the biggest texture to display the other ones
    playerSprite.setTexture(textures[13]);
}



/**
 * Check if the player has to advance in the track
 * @param eventDetected is a boolean to control if an event has occurred
 */
void Motorbike::advancePlayer(bool& eventDetected){
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
        playerSprite.setTexture(textures[actual_code_image - 1]);
    }
    else {
        // Elimination of the last event registered
        eventDetected = false;
    }
}




/**
 * Get the coordinate of the payer in the axis X
 * @return the position of the motorbike in the axis X
 */
float Motorbike::getPlayerX(){
    return Player::getPlayerX();
}




/**
 * Get the mode of collision of the motorbike
 * @return the mode to show the collision of the motorbike
 */
int Motorbike::getModeCollision(){
    return mode;
}



/**
 * Control if the user has pressed the w keyword to turn to the right
 * @param speed is the actual speed of the motorbike of the player
 * @param eventDetected is a boolean to control if an event has occurred
 * @param app is the console window game where the sprite is going to be drawn
 */
inline void Motorbike::controlTurningPlayerLeftKeyboard(int& speed, bool& eventDetected, RenderWindow& app){
    // Check if key left pressed
    if (Keyboard::isKeyPressed(Keyboard::Q)){
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
            playerSprite.setTexture(textures[actual_code_image - 1]);
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
            playerSprite.setTexture(textures[actual_code_image - 1]);
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
inline void Motorbike::controlTurningPlayerRightKeyboard(int& speed, bool& eventDetected, RenderWindow& app){
    // Check if key right pressed
    if (Keyboard::isKeyPressed(Keyboard::W)){
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
            playerSprite.setTexture(textures[actual_code_image - 1]);
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
            playerSprite.setTexture(textures[actual_code_image - 1]);
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
inline void Motorbike::controlTurningPlayerLeftMouse(int& speed, bool& eventDetected, RenderWindow& app){
    // Get the x coordinate of the mouse in the window
    int coordinateX = sf::Mouse::getPosition(app).x;
    // Check if key right pressed
    if (coordinateX < (int)app.getSize().x / 3  ){
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
            playerSprite.setTexture(textures[actual_code_image - 1]);
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
            playerSprite.setTexture(textures[actual_code_image - 1]);
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
inline void Motorbike::controlTurningPlayerRightMouse(int& speed, bool& eventDetected, RenderWindow& app){
    // Get the x coordinate of the mouse in the window
    int coordinateX = sf::Mouse::getPosition(app).x;
    // Check if key right pressed
    if (coordinateX > 2 * (int)(app.getSize().x / 3)){
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
            playerSprite.setTexture(textures[actual_code_image - 1]);
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
            playerSprite.setTexture(textures[actual_code_image - 1]);
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
 */
inline void Motorbike::controlPlayerSpeed(int& speed, bool& eventDetected, RenderWindow& app){
    // Check if the user is accelerating
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up))){
        // Control about not acceleration if the motorbike goes in the grass
        if (playerX >= BORDER_ROAD_LEFT && playerX <= BORDER_ROAD_RIGHT){
            // Increment the speed because it is inside the road
            if (speed <= MAX_SPEED){
                // Increment of the speed
                speed += SPEED_INCREMENT + SPEED_INCREMENT;
            }
        }
        else {
            // Increment the speed because it is outside the road
            if (speed >= INITIAL_SPEED){
                // Decrement of the speed
                speed -= SPEED_INCREMENT - SPEED_INCREMENT;
            }
        }
        // Check if the key to turn left is pressed
        if (!eventDetected){
            // Check the type of control of the motorbike
            if (typeControl == 0){
                 // Check if the key to turn to the right is pressed
                 controlTurningPlayerRightKeyboard(speed, eventDetected, app);
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
                 controlTurningPlayerLeftKeyboard(speed, eventDetected, app);
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
            playerSprite.setTexture(textures[actual_code_image - 1]);
        }
        // Change the sprite of the motorbike
        else if (actual_code_image == 1 && eventDetected){
            // Change the sprite
            actual_code_image = 2;
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1]);
        }
    }
}



/**
 * Control if the user has pressed the q keyword to increase the speed
 * @param speed is the actual speed of the motorbike of the player
 * @param eventDetected is a boolean to control if an event has occurred
 * @param app is the console window game where the sprite is going to be drawn
 */
inline void Motorbike::controlPlayerBraking(int& speed, bool& eventDetected, RenderWindow& app){
    // Check if the user is braking
    if (Keyboard::isKeyPressed(Keyboard::Down)){
        // Check more events
        if (!eventDetected){
            // Control if first the user has accelerated
            controlPlayerSpeed(speed, eventDetected, app);
        }
        // Selection of the correct sprite of the motorbike
        if (actual_code_image <= 2){
            actual_code_image = 15;
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1]);
        }
        else if (actual_code_image == 15){
            actual_code_image = 16;
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1]);
        }
        else if (actual_code_image == 16){
            actual_code_image = 15;
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1]);
        }
        else if (actual_code_image >= 3 && actual_code_image <= 8){
            actual_code_image += 14;
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1]);
        }
        else if (actual_code_image >= 9 && actual_code_image <= 14){
            actual_code_image += 14;
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1]);
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
            playerSprite.setTexture(textures[actual_code_image - 1]);
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
            playerSprite.setTexture(textures[actual_code_image - 1]);
        }
        // Reduce the speed
        if (speed > INITIAL_SPEED){
            // Increment of the speed
            speed -= SPEED_INCREMENT;
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
 */
void Motorbike::controlActionPlayer(int& speed, bool& eventDetected, RenderWindow& app){
    if (typeControl == 0){
        // Keyword
        // Check if W keyword has been pressed to turn to the right
        controlTurningPlayerRightKeyboard(speed, eventDetected, app);

        // Check if Q keyword has been pressed to turn to the left
        controlTurningPlayerLeftKeyboard(speed, eventDetected, app);
    }
    else {
        // Mouse
        // Check if the mouse has has been moved to turn to the right
        controlTurningPlayerRightMouse(speed, eventDetected, app);

        // Check if the mouse has has been moved to turn to the left
        controlTurningPlayerLeftMouse(speed, eventDetected, app);
    }

    // Check if the Up keyword has been pressed to increase the speed
    controlPlayerSpeed(speed, eventDetected, app);

    //Check if the E keyword has been pressed to brake the motorbike
    controlPlayerBraking(speed, eventDetected, app);

    // Check if any event has been registered
    if (!eventDetected){
        // Reduce the speed
        if (speed > INITIAL_SPEED){
            // Increment of the speed
            speed -= SPEED_INCREMENT;
        }
    }
}



/**
 * Control if the player has have collision with the nearest element of the map to him
 * @param nearestStep is the step of the scene where is located the nearest element to the player
 * @param lastPos is the last position of the motorbike in the axis Y
 * @param pos is the current position of the motorbike in the axis Y
 */
bool Motorbike::controlPossibleCollision(Step& nearestStep, int& lastPos, int& pos){
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
    // Check if there has to appear inertia force
    if (onCurve){
        // The motorbike is on a curve of the scene
        onCurve = false;
        // Check the direction of the curve
        if (curve.directionCurve > 0.f){
            // Check if the motorbike
            if (speed >= MEDIUM_SPEED){
                // Motorbike goes to the left when it is a right curve
                playerX -= 0.075;
            }
            else if (speed >= CONTROL_SPEED && speed < MEDIUM_SPEED) {
                playerX -= 0.045;
            }
            else {
                playerX -= 0.015;
            }
        }
        else {
            // Check if the motorbike
            if (speed >= MEDIUM_SPEED){
                // Motorbike goes to the left when it is a right curve
                playerX += 0.075;
            }
            else if (speed >= CONTROL_SPEED && speed < MEDIUM_SPEED) {
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





