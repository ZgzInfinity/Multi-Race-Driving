
#include "../include/Configuration.h"


/**
 * Default constructor of the data type configuration
 */
Configuration::Configuration(){
    // Assignment of a default configuration
    accelerateKey = Keyboard::Up;
    brakeKey = Keyboard::Down;
    leftKey = Keyboard::Q;
    rightKey = Keyboard::W;
}



/**
 * Returns the key used to accelerate the player's vehicle
 */
Keyboard::Key Configuration::getAccelerateKey(){
    return accelerateKey;
}



/**
 * Returns the key used to brake the player's vehicle
 */
Keyboard::Key Configuration::getBrakeKey(){
    return brakeKey;
}



/**
 * Returns the key used to turn to the left the player's vehicle
 */
Keyboard::Key Configuration::getLeftKey(){
    return leftKey;
}



/**
 * Returns the key used to turn to the right the player's vehicle
 */
Keyboard::Key Configuration::getRightKey(){
    return rightKey;
}



/**
 * Default constructor of the data type configuration
 */
void Configuration::changeConfiguration(){

}
