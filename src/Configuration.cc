
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
    changeSoundtrackLevel = Keyboard::Tab;
    goBackKey = Keyboard::Backspace;
    startKey = Keyboard::Enter;
}


/**
 * Assign the accelerate control key
 */
void Configuration::setAccelerateKey(const Keyboard::Key key){
    accelerateKey = key;
}



/**
 * Returns the key used to accelerate the player's vehicle
 */
Keyboard::Key Configuration::getAccelerateKey(){
    return accelerateKey;
}



/**
 * Assign the brake control key
 */
void Configuration::setBrakeKey(const Keyboard::Key key){
    brakeKey = key;
}



/**
 * Returns the key used to brake the player's vehicle
 */
Keyboard::Key Configuration::getBrakeKey(){
    return brakeKey;
}



/**
 * Assign the left control key
 */
void Configuration::setLeftKey(const Keyboard::Key key){
    leftKey = key;
}



/**
 * Returns the key used to turn to the left the player's vehicle
 */
Keyboard::Key Configuration::getLeftKey(){
    return leftKey;
}



/**
 * Assign the right control key
 */
void Configuration::setRightKey(const Keyboard::Key key){
    rightKey = key;
}



/**
 * Returns the key used to turn to the right the player's vehicle
 */
Keyboard::Key Configuration::getRightKey(){
    return rightKey;
}



/**
 * Returns the key used to turn to the right the player's vehicle
 */
Keyboard::Key Configuration::getStart(){
    return startKey;
}



 /**
 * Assign the key used to change the level soundtrack
 */
void Configuration::setChangeSoundtrack(const Keyboard::Key key){
    changeSoundtrackLevel = key;
}



/**
 * Returns the key used to change the level soundtrack
 */
Keyboard::Key Configuration::getChangeSoundtrack(){
    return changeSoundtrackLevel;
}



/**
 * Check if the player has pressed the key to change the actual level
 * soundtrack
 */
bool Configuration::checkChangeMusic(){
    // Check if the keyword has been pressed or not
    return Keyboard::isKeyPressed(changeSoundtrackLevel);
}



/**
 * Check if the key that is going to be assign is already selected
 * @param key is the candidate keyword
 */
bool Configuration::isRepeated(const Keyboard::Key key){
    return (key == accelerateKey || key == brakeKey || key == leftKey ||
            key == rightKey || key == changeSoundtrackLevel);
}
