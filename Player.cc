
#include "Player.h"

Player::Player(){

    // Loading all the textures of the motorbike
    playerTexture_1.loadFromFile("images/player/p1.png");    playerTexture_2.loadFromFile("images/player/p2.png");
    playerTexture_3.loadFromFile("images/player/p3.png");    playerTexture_4.loadFromFile("images/player/p4.png");
    playerTexture_5.loadFromFile("images/player/p5.png");    playerTexture_6.loadFromFile("images/player/p6.png");
    playerTexture_7.loadFromFile("images/player/p7.png");    playerTexture_8.loadFromFile("images/player/p8.png");
    playerTexture_9.loadFromFile("images/player/p9.png");    playerTexture_10.loadFromFile("images/player/p10.png");
    playerTexture_11.loadFromFile("images/player/p11.png");  playerTexture_12.loadFromFile("images/player/p12.png");
    playerTexture_13.loadFromFile("images/player/p13.png");  playerTexture_14.loadFromFile("images/player/p14.png");
    playerTexture_15.loadFromFile("images/player/p15.png");  playerTexture_16.loadFromFile("images/player/p16.png");
    playerTexture_17.loadFromFile("images/player/p17.png");  playerTexture_18.loadFromFile("images/player/p18.png");
    playerTexture_19.loadFromFile("images/player/p19.png");  playerTexture_20.loadFromFile("images/player/p20.png");
    playerTexture_21.loadFromFile("images/player/p21.png");  playerTexture_22.loadFromFile("images/player/p22.png");
    playerTexture_23.loadFromFile("images/player/p23.png");  playerTexture_24.loadFromFile("images/player/p24.png");
    playerTexture_25.loadFromFile("images/player/p25.png");  playerTexture_26.loadFromFile("images/player/p26.png");
    playerTexture_27.loadFromFile("images/player/p27.png");  playerTexture_28.loadFromFile("images/player/p28.png");

    // Application of smooth filter to make the pixels lees noticeable
    playerTexture_1.setSmooth(true);   playerTexture_2.setSmooth(true);   playerTexture_3.setSmooth(true);   playerTexture_4.setSmooth(true);
    playerTexture_5.setSmooth(true);   playerTexture_6.setSmooth(true);   playerTexture_7.setSmooth(true);   playerTexture_8.setSmooth(true);
    playerTexture_9.setSmooth(true);   playerTexture_10.setSmooth(true);  playerTexture_11.setSmooth(true);  playerTexture_12.setSmooth(true);
    playerTexture_13.setSmooth(true);  playerTexture_14.setSmooth(true);  playerTexture_15.setSmooth(true);  playerTexture_16.setSmooth(true);
    playerTexture_17.setSmooth(true);  playerTexture_18.setSmooth(true);  playerTexture_19.setSmooth(true);  playerTexture_20.setSmooth(true);
    playerTexture_21.setSmooth(true);  playerTexture_22.setSmooth(true);  playerTexture_23.setSmooth(true);  playerTexture_24.setSmooth(true);
    playerTexture_25.setSmooth(true);  playerTexture_26.setSmooth(true);  playerTexture_27.setSmooth(true);  playerTexture_28.setSmooth(true);

    // Loading the texture with more dimension
    // to have space to the other ones
    playerSprite.setTexture(playerTexture_14);

    // Store actual code of the image
    actual_code_image = 1;

    // Initializing the position of the player in the axis X
    playerX = 0.f;
}



/**
 * Draw the player sprite in the console render window
 * @param app is the console window game where the sprite is going to be drawn
 */
void Player::drawPlayer(RenderWindow& app){
    playerSprite.setPosition(Vector2f(465.f, HEIGHT - 230.f));
    app.draw(playerSprite);
}



/**
 * Check if the player has to advance in the track
 * @param eventDetected is a boolean to control if an event has occurred
 */
void Player::advancePlayer(bool& eventDetected){
    // Eliminate this event detection
    if (!eventDetected){
        if (actual_code_image != 1){
            actual_code_image = 1;
            // Load the seventh sprite
            playerSprite.setTexture(playerTexture_1);
        }
        else {
            actual_code_image = 2;
            // Load the seventh sprite
            playerSprite.setTexture(playerTexture_2);
        }
    }
    else {
        // Elimination of the last event registered
        eventDetected = false;
    }
}



/**
 * Get the coordinate of the payer in the axis X
 */
float Player::getPlayerX(){
    return playerX;
}



/**
 * Control if the user has pressed the w keyword to turn to the right
 * @param speed is the actual speed of the motorbike of the player
 * @param eventDetected is a boolean to control if an event has occurred
 * @param app is the console window game where the sprite is going to be drawn
 */
inline void Player::controlTurningPlayerLeftKeyboard(int& speed, bool& eventDetected, RenderWindow& app){
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
            playerSprite.setTexture(playerTexture_3);
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
            switch (actual_code_image){
                // Select the correct sprite
                case 4:
                    // Load the fourth sprite
                    playerSprite.setTexture(playerTexture_4);
                    break;
                case 5:
                    // Load the fifth sprite
                    playerSprite.setTexture(playerTexture_5);
                    break;
                case 6:
                    // Load the sixth sprite
                    playerSprite.setTexture(playerTexture_6);
                    break;
                case 7:
                    // Load the seventh sprite
                    playerSprite.setTexture(playerTexture_7);
                    break;
                case 8:
                    // Load the seventh sprite
                    playerSprite.setTexture(playerTexture_8);
                    break;
            }
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
inline void Player::controlTurningPlayerRightKeyboard(int& speed, bool& eventDetected, RenderWindow& app){
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
            playerSprite.setTexture(playerTexture_9);
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
            switch (actual_code_image){
                // Select the correct sprite
                case 10:
                    // Load the fourth sprite
                    playerSprite.setTexture(playerTexture_10);
                    break;
                case 11:
                    // Load the fifth sprite
                    playerSprite.setTexture(playerTexture_11);
                    break;
                case 12:
                    // Load the sixth sprite
                    playerSprite.setTexture(playerTexture_12);
                    break;
                case 13:
                    // Load the seventh sprite
                    playerSprite.setTexture(playerTexture_13);
                    break;
                case 14:
                    // Load the seventh sprite
                    playerSprite.setTexture(playerTexture_14);
                    break;
            }
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
inline void Player::controlTurningPlayerLeftMouse(int& speed, bool& eventDetected, RenderWindow& app){
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
            playerSprite.setTexture(playerTexture_3);
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
            switch (actual_code_image){
                // Select the correct sprite
                case 4:
                    // Load the fourth sprite
                    playerSprite.setTexture(playerTexture_4);
                    break;
                case 5:
                    // Load the fifth sprite
                    playerSprite.setTexture(playerTexture_5);
                    break;
                case 6:
                    // Load the sixth sprite
                    playerSprite.setTexture(playerTexture_6);
                    break;
                case 7:
                    // Load the seventh sprite
                    playerSprite.setTexture(playerTexture_7);
                    break;
                case 8:
                    // Load the seventh sprite
                    playerSprite.setTexture(playerTexture_8);
                    break;
            }
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
inline void Player::controlTurningPlayerRightMouse(int& speed, bool& eventDetected, RenderWindow& app){
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
            playerSprite.setTexture(playerTexture_9);
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
            switch (actual_code_image){
                // Select the correct sprite
                case 10:
                    // Load the fourth sprite
                    playerSprite.setTexture(playerTexture_10);
                    break;
                case 11:
                    // Load the fifth sprite
                    playerSprite.setTexture(playerTexture_11);
                    break;
                case 12:
                    // Load the sixth sprite
                    playerSprite.setTexture(playerTexture_12);
                    break;
                case 13:
                    // Load the seventh sprite
                    playerSprite.setTexture(playerTexture_13);
                    break;
                case 14:
                    // Load the seventh sprite
                    playerSprite.setTexture(playerTexture_14);
                    break;
            }
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
inline void Player::controlPlayerSpeed(int& speed, bool& eventDetected, RenderWindow& app){
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
            playerSprite.setTexture(playerTexture_1);
        }
        // Change the sprite of the motorbike
        else if (actual_code_image == 1 && eventDetected){
            // Change the sprite
            actual_code_image = 2;
            playerSprite.setTexture(playerTexture_2);
        }
    }
}




/**
 * Control if the user has pressed the q keyword to increase the speed
 * @param speed is the actual speed of the motorbike of the player
 * @param eventDetected is a boolean to control if an event has occurred
 * @param app is the console window game where the sprite is going to be drawn
 */
inline void Player::controlPlayerBraking(int& speed, bool& eventDetected, RenderWindow& app){
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
            playerSprite.setTexture(playerTexture_15);
        }
        else if (actual_code_image == 15){
            actual_code_image = 16;
            playerSprite.setTexture(playerTexture_16);
        }
        else if (actual_code_image == 16){
            actual_code_image = 15;
            playerSprite.setTexture(playerTexture_15);
        }
        else if (actual_code_image >= 3 && actual_code_image <= 8){
            actual_code_image += 14;
            switch(actual_code_image){
                case 17:
                    playerSprite.setTexture(playerTexture_17);
                    break;
                case 18:
                    playerSprite.setTexture(playerTexture_18);
                    break;
                case 19:
                    playerSprite.setTexture(playerTexture_19);
                    break;
                case 20:
                    playerSprite.setTexture(playerTexture_20);
                    break;
                case 21:
                    playerSprite.setTexture(playerTexture_21);
                    break;
                case 22:
                    playerSprite.setTexture(playerTexture_22);
                }
            }
        else if (actual_code_image >= 9 && actual_code_image <= 14){
            actual_code_image += 14;
            switch(actual_code_image){
                case 23:
                    playerSprite.setTexture(playerTexture_23);
                    break;
                case 24:
                    playerSprite.setTexture(playerTexture_24);
                    break;
                case 25:
                    playerSprite.setTexture(playerTexture_25);
                    break;
                case 26:
                    playerSprite.setTexture(playerTexture_26);
                    break;
                case 27:
                    playerSprite.setTexture(playerTexture_27);
                    break;
                case 28:
                    playerSprite.setTexture(playerTexture_28);
            }
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
            switch (actual_code_image){
                // Select the correct sprite
                case 18:
                    // Load the fourth sprite
                    playerSprite.setTexture(playerTexture_18);
                    break;
                case 19:
                    // Load the fifth sprite
                    playerSprite.setTexture(playerTexture_19);
                    break;
                case 20:
                    // Load the sixth sprite
                    playerSprite.setTexture(playerTexture_20);
                    break;
                case 21:
                    // Load the seventh sprite
                    playerSprite.setTexture(playerTexture_21);
                    break;
                case 22:
                    // Load the seventh sprite
                    playerSprite.setTexture(playerTexture_22);
                    break;
            }
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
            switch (actual_code_image){
                // Select the correct sprite
                case 24:
                    // Load the fourth sprite
                    playerSprite.setTexture(playerTexture_24);
                    break;
                case 25:
                    // Load the fifth sprite
                    playerSprite.setTexture(playerTexture_25);
                    break;
                case 26:
                    // Load the sixth sprite
                    playerSprite.setTexture(playerTexture_26);
                    break;
                case 27:
                    // Load the seventh sprite
                    playerSprite.setTexture(playerTexture_27);
                    break;
                    case 28:
                    // Load the seventh sprite
                    playerSprite.setTexture(playerTexture_28);
                    break;
            }
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
void Player::controlActionPlayer(int& speed, bool& eventDetected, RenderWindow& app){
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
bool Player::controlPossibleCollision(Step& nearestStep, int& lastPos, int& pos){
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
void Player::controlInertiaForce(bool& onCurve, IntervalCurve& curve, int& speed){
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

