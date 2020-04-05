
#include "../include/Truck.h"

Truck::Truck(char* pathFile, Configuration* conf) : Player(pathFile, conf){};



/**
 * Draw the player sprite in the console render window
 * @param app is the console window game where the sprite is going to be drawn
 */
void Truck::drawPlayer(RenderWindow* app, int& pos){
    // Check what is the offset to apply while is crushing
    if (mode == 0){
        // First mode
        playerX += 0.05;
        pos += 400;
    }
    if (mode == 1){
        // First mode
        playerX -= 0.05;
        pos -= 200;
    }
    // Print the truck in its actual position
    playerSprite.setPosition(Vector2f(400.f, HEIGHT - 200.f));
    app->draw(playerSprite);
}



/**
 * Load the set of sprites of the player
 */
void Truck::loadVehicleProperties(){
    // Document xml where the document is going to be parsed
    xml_document<> doc;
    file<> file("Configuration/Vehicles/Truck.xml");
    // Parsing the content of file
    doc.parse<0>(file.data());

    // Get the principal node of the file
    xml_node<> *nodePlayer = doc.first_node();

    // Loop in order to iterate all the children of the principal node
    for (xml_node<> *child = nodePlayer->first_node(); child; child = child->next_sibling()){
        // Check if the actual node is the controller of the max speed of the vehicle
        if ((string)child->name() == "MaxSpeed"){
            maxSpeed = RATIO * stoi(child->value());
        }
        // Check if the actual node is the controller of the paths of the sprites
        else if ((string)child->name() == "SpritePaths"){
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
    playerSprite.setTexture(textures[19]);

    // Initialize the medium speed of the vehicle
    mediumSpeed = INITIAL_SPEED + maxSpeed / 2;

    // Initialize the control speed of the vehicle to calculate the inertia force
    controlSpeed = INITIAL_SPEED + mediumSpeed / 2;

    cout << maxSpeed << endl;
}



/**
 * Check if the player has to advance in the track
 * @param eventDetected is a boolean to control if an event has occurred
 * @param lastHeight was the elevation of the terrain where was the truck
 * @param height is the actual elevation of the terrain where is the truck
 */
void Truck::advancePlayer(bool& eventDetected, const int lastHeight, const int height){
    // Eliminate this event detection
    if (!eventDetected){
        // Check if the car is ascending on a elevation part of the terrain
        if (((height > NORMAL_HEIGHT && height <= 2 * NORMAL_HEIGHT) ||
             (height > 0 && height <= NORMAL_HEIGHT)) && height > lastHeight)
        {
            // The car is ascending the landing
            if (actual_code_image < 13 || actual_code_image > 15){
                // The sprites do not correspond to the ascending
                actual_code_image = 13;
            }
            else {
                // The sprite corresponds to one of the landing
                if (actual_code_image != 15){
                    // Increment to the next ascending sprite
                    actual_code_image++;
                }
                else {
                    // Return to the first one
                    actual_code_image -= 2;
                }
            }
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        else {
            if (actual_code_image > 4){
                // First advance sprite loaded
                actual_code_image = 1;
            }
            else {
                if (actual_code_image != 4){
                    actual_code_image++;
                }
                else {
                    actual_code_image = 1;
                }
            }
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
    }
    else {
        // Elimination of the last event registered
        eventDetected = false;
    }
}




/**
 * Get the coordinate of the payer in the axis X
 * @return the position of the truck in the axis X
 */
float Truck::getPlayerX(){
    return playerX;
}




/**
 * Get the mode of collision of the truck
 * @return the mode to show the collision of the truck
 */
int Truck::getModeCollision(){
    return mode;
}



/**
 * Control if the user has pressed the w keyword to turn to the right
 * @param speed is the actual speed of the truck of the player
 * @param eventDetected is a boolean to control if an event has occurred
 * @param app is the console window game where the sprite is going to be drawn
 * @param lastHeight was the elevation of the terrain where was the truck
 * @param height is the actual elevation of the terrain where is the truck
 */
inline void Truck::controlTurningPlayerLeftKeyboard(int& speed, bool& eventDetected, RenderWindow* app,
                                                      const int lastHeight, const int height)
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
        // Check if the car is ascending in a elevation terrain or not
        if (((height > NORMAL_HEIGHT && height <= 2 * NORMAL_HEIGHT) ||
             (height > 0 && height <= NORMAL_HEIGHT)) && height > lastHeight)
        {
            // The car is in a elevation
            if (actual_code_image < 16 || (actual_code_image >= 19 && actual_code_image <= 25) ||
               (actual_code_image >= 29 && actual_code_image <= 42))
            {
                actual_code_image = 16;
                playerSprite.setTexture(textures[actual_code_image - 1], true);
            }
            else if (actual_code_image >= 16 && actual_code_image <= 18){
                // Increment the actual code of the sprite
                if (actual_code_image != 18){
                    // Increment the texture of the sprite
                    actual_code_image++;
                }
                else {
                    // Change sprite while the motorbike is turning to left
                    actual_code_image -= 2;
                }
                // Set the texture from the file
                playerSprite.setTexture(textures[actual_code_image - 1], true);
            }
            // Register event
            eventDetected = true;
        }
        else {
            // The car is not in a elevation Change the texture
            if (actual_code_image < 5 || (actual_code_image >= 9 && actual_code_image <= 25) ||
               (actual_code_image >= 30 && actual_code_image <= 42))
            {
                actual_code_image = 5;
                playerSprite.setTexture(textures[actual_code_image - 1], true);
            }
            else if (actual_code_image >= 5 && actual_code_image <= 8){
                // Increment the actual code of the sprite
                if (actual_code_image != 8){
                    // Increment the texture of the sprite
                    actual_code_image++;
                }
                else {
                    // Change sprite while the motorbike is turning to left
                    actual_code_image -= 3;
                }
                // Set the texture from the file
                playerSprite.setTexture(textures[actual_code_image - 1], true);
            }
            // Register event
            eventDetected = true;
        }
    }
}



/**
 * Control if the user has pressed the q keyword to turn to the left
 * @param speed is the actual speed of the motorbike of the player
 * @param eventDetected is a boolean to control if an event has occurred
 * @param app is the console window game where the sprite is going to be drawn
 * @param lastHeight was the elevation of the terrain where was the truck
 * @param height is the actual elevation of the terrain where is the truck
 */
inline void Truck::controlTurningPlayerRightKeyboard(int& speed, bool& eventDetected, RenderWindow* app,
                                                       const int lastHeight, const int height){
    // Check if key right pressed
    if (Keyboard::isKeyPressed(c->getRightKey())){
        if (!isAccelerating){
            if (speed > INITIAL_SPEED){
                speed -= int(deceleration * speed_increment);
                if (speed < INITIAL_SPEED){
                    speed = INITIAL_SPEED;
                }
            }
        }
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
        // Check if the car is ascending in a elevation terrain or not
        if (((height > NORMAL_HEIGHT && height <= 2 * NORMAL_HEIGHT) ||
             (height > 0 && height <= NORMAL_HEIGHT)) && height > lastHeight)
        {
            // The car is in a elevation
            if (actual_code_image < 19 || (actual_code_image >= 22 && actual_code_image <= 39))
            {
                actual_code_image = 19;
                playerSprite.setTexture(textures[actual_code_image - 1], true);
            }
            else if (actual_code_image >= 19 && actual_code_image <= 21){
                // Increment the actual code of the sprite
                if (actual_code_image != 21){
                    // Increment the texture of the sprite
                    actual_code_image++;
                }
                else {
                    // Change sprite while the motorbike is turning to left
                    actual_code_image -= 2;
                }
                // Set the texture from the file
                playerSprite.setTexture(textures[actual_code_image - 1], true);
            }
            // Register event
            eventDetected = true;
        }
        else {
            // Change the texture
            if (actual_code_image < 9 || (actual_code_image >= 13 && actual_code_image <= 29) ||
               (actual_code_image >= 34 && actual_code_image <= 42))
            {
                actual_code_image = 9;
                playerSprite.setTexture(textures[actual_code_image - 1], true);
            }
            else if (actual_code_image <= 12){
                // Increment the actual code of the sprite
                if (actual_code_image != 12){
                    // Increment the texture of the sprite
                    actual_code_image++;
                }
                else {
                    // Change sprite while the motorbike is turning to left
                    actual_code_image -= 3;
                }
                // Set the texture from the file
                playerSprite.setTexture(textures[actual_code_image - 1], true);
            }
            // Register event
            eventDetected = true;
        }
    }
}



/**
 * Control if the user has pressed the q keyword to increase the speed
 * @param speed is the actual speed of the truck of the player
 * @param eventDetected is a boolean to control if an event has occurred
 * @param app is the console window game where the sprite is going to be drawn
 * @param lastHeight was the elevation of the terrain where was the truck
 * @param height is the actual elevation of the terrain where is the truck
 */
inline void Truck::controlPlayerSpeed(int& speed, bool& eventDetected, RenderWindow* app,
                                        const int lastHeight, const int height){
    // Check if the user is accelerating
    if ((Keyboard::isKeyPressed(c->getAccelerateKey()))){
        isAccelerating = true;
        // Control about not acceleration if the truck goes in the grass
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
                // Increment of the speed
                speed -= int(acceleration * (speed_increment + speed_increment));
                if (speed < INITIAL_SPEED){
                    speed = INITIAL_SPEED;
                }
            }
        }
        // Check if the key to turn left is pressed
        if (!eventDetected){
            // Check if the key to turn to the right is pressed
            isAccelerating = false;
            controlTurningPlayerRightKeyboard(speed, eventDetected, app, lastHeight, height);
            return;
        }
        // Check if the key to turn left is pressed
        if (!eventDetected){
            isAccelerating = false;
            // Check if the key to turn to the left is pressed
            controlTurningPlayerLeftKeyboard(speed, eventDetected, app, lastHeight, height);
            return;
        }
        // Change the sprite;
        if (actual_code_image >= 1 && actual_code_image <= 4 && eventDetected){
            if (actual_code_image != 4){
                actual_code_image++;
            }
            else {
                actual_code_image -= 3;
            }
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
    }
    else {
        isAccelerating = false;
    }
}




/**
 * Control if the user has pressed the q keyword to increase the speed
 * @param speed is the actual speed of the truck of the player
 * @param eventDetected is a boolean to control if an event has occurred
 * @param app is the console window game where the sprite is going to be drawn
 * @param lastHeight was the elevation of the terrain where was the truck
 * @param height is the actual elevation of the terrain where is the truck
 */
inline void Truck::controlPlayerBraking(int& speed, bool& eventDetected, RenderWindow* app,
                                          const int lastHeight, const int height){
    // Check if the user is braking
    if (Keyboard::isKeyPressed(c->getBrakeKey())){
        isAccelerating = false;
        // Check more events
        if (!eventDetected){
            // Control if first the user has accelerated
            controlPlayerSpeed(speed, eventDetected, app, lastHeight, height);
        }
        // The truck goes straight
        if (actual_code_image >= 1 && actual_code_image <= 4){
            actual_code_image += 21;
        }
        // The truck was straight and brake
        else if (actual_code_image >= 22 && actual_code_image <= 25){
            if (actual_code_image != 25){
                actual_code_image++;
            }
            else {
                actual_code_image -= 3;
            }
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        // The truck goes left
        else if (actual_code_image >= 5 && actual_code_image <= 8){
            actual_code_image += 21;
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        // The truck goes right
        else if (actual_code_image >= 9 && actual_code_image <= 12){
            actual_code_image += 21;
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        //The truck was left and brake
        else if (actual_code_image >= 26 && actual_code_image <= 29){
            // Increment the actual code of the sprite
            if (actual_code_image != 29){
                // Increment the texture of the sprite
                actual_code_image++;
            }
            else {
                // Change sprite while the truck is turning left and braking
                actual_code_image -= 3;
            }
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        // The truck was right and brake
        else if (actual_code_image >= 30 && actual_code_image <= 33){
            // Increment the actual code of the sprite
            if (actual_code_image != 33){
                // Increment the texture of the sprite
                actual_code_image++;
            }
            else {
                // Change sprite while the truck is turning right and braking
                actual_code_image -= 3;
            }
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        // The truck goes ascending
        else if (actual_code_image >= 13 && actual_code_image <= 15){
            actual_code_image += 21;
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        // The truck was ascending and brake
        else if (actual_code_image >= 34 && actual_code_image <= 36){
            // Increment the actual code of the sprite
            if (actual_code_image != 36){
                // Increment the texture of the sprite
                actual_code_image++;
            }
            else {
                // Change sprite while the truck is ascending and braking
                actual_code_image -= 2;
            }
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        // The truck goes ascending and turning left
        else if (actual_code_image >= 19 && actual_code_image <= 21){
            actual_code_image += 21;
            // Set the texture from the file
            playerSprite.setTexture(textures[actual_code_image - 1], true);
        }
        // The truck was descending while it was turning left and brake
        else if (actual_code_image >= 40 && actual_code_image <= 42){
            // Increment the actual code of the sprite
            if (actual_code_image != 42){
                // Increment the texture of the sprite
                actual_code_image++;
            }
            else {
                // Change sprite while the truck is ascending while is turning left and braking
                actual_code_image -= 2;
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
 * @param speed is the actual speed of the truck of the player
 * @param eventDetected is a boolean to control if an event has occurred
 * @param app is the console window game where the sprite is going to be drawn
 * @param lastHeight was the elevation of the terrain where was the truck
 * @param height is the actual elevation of the terrain where is the truck
 */
void Truck::controlActionPlayer(int& speed, bool& eventDetected, RenderWindow* app, const int lastCamH, const int camH){
    // Keyword
    // Check if W keyword has been pressed to turn to the right
    controlTurningPlayerRightKeyboard(speed, eventDetected, app, lastCamH, camH);

    // Check if Q keyword has been pressed to turn to the left
    controlTurningPlayerLeftKeyboard(speed, eventDetected, app, lastCamH, camH);

    //Check if the E keyword has been pressed to brake the truck
    controlPlayerBraking(speed, eventDetected, app, lastCamH, camH);

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
    controlPlayerSpeed(speed, eventDetected, app, lastCamH, camH);

}



/**
 * Control if the player has have collision with the nearest element of the map to him
 * @param nearestStep is the step of the scene where is located the nearest element to the player
 * @param lastPos is the last position of the truck in the axis Y
 * @param pos is the current position of the truck in the axis Y
 */
bool Truck::controlPossibleCollision(Step& nearestStep, int& lastPos, int& pos){
    // Calculation of the distance
    float distance = nearestStep.spriteX - playerX;
    // Check the sign of the offset
    if (distance > 0){
        // Right
        // Check if the coordinates in the axis X are more less equal to have a collision
        if (distance >= nearestStep.offset - 1.2 && distance <= nearestStep.offset + 0.075){
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
 * Control if there is there inertia force or not if the truck is on a curve of the scene
 * @param onCurve is a boolean which represents if the truck is on curve or not
 * @param curve is the possible curve of the scene where the truck is currently now
 * @param speed is the actual speed of the truck of the player
 */
void Truck::controlInertiaForce(bool& onCurve, IntervalCurve& curve, int& speed){
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
 * Shows to the user how the truck crushes
 * @param pos is the position of the truck in the car in the axis Y
 */
void Truck::collisionShow(){
    // Not collision detected before
    if (mode == -1){
        // Code generated to the way of collision
        // Pseudo generator of aleatory number in order to generate randomly the way of collision
        srand(time(NULL));
        mode = rand() % 2;
        // Establish the first collision sprite
        if (mode == 0){
            // First way to collision
            actual_code_image = 43;
        }
        else if (mode == 1) {
            // Second way to collision
            actual_code_image = 44;
        }
    }
    else {
        // Collision detected in process
        // Avoid overflow of code number identifier of collision sprite
        if (mode == 1){
            // Show the sprite
            playerSprite.setTexture(textures[actual_code_image - 1], true);
            actual_code_image++;
            // Check if it's the final sprite
            if (actual_code_image == 51){
                spinningTopsDone++;
                actual_code_image -= 8;
                playerSprite.setTexture(textures[actual_code_image - 1], true);
            }
            if (spinningTopsDone == 2){
                actual_code_image = 1;
                mode = -1;
                playerX = 0.f;
                spinningTopsDone = 0;
            }
        }
        else if (mode == 0){
            if (actual_code_image == 43){
                playerSprite.setTexture(textures[actual_code_image - 1], true);
                actual_code_image += 7;
            }
            else {
                playerSprite.setTexture(textures[actual_code_image - 1], true);
                actual_code_image--;
                if (actual_code_image == 43){
                    spinningTopsDone++;
                }
                if (spinningTopsDone == 2){
                    actual_code_image = 1;
                    mode = -1;
                    playerX = 0.f;
                    spinningTopsDone = 0;
                }
            }
        }
    }
}







