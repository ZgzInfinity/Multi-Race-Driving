

#include "../include/Vehicle.h"

Vehicle::Vehicle(){}


Vehicle::Vehicle(const float maxSpeed, const float scale, const int maxCounterToChange, float speedVehicle, float posX,
                 float previousX, float posY, float previousY, float minScreenX, float maxScreenX, const string &vehicle,
                 int numTextures,
                 int currentCodeImage, int counterCodeImage) : maxSpeed(maxSpeed), scale(scale),
                                                               maxCounterToChange(maxCounterToChange), previousX(previousX), posX(posX), posY(posY),
                                                               previousY(previousY), minScreenX(minScreenX),
                                                               maxScreenX(maxScreenX),
                                                               current_code_image(currentCodeImage),
                                                               counter_code_image(counterCodeImage)
{
    speed = speedVehicle;
    halfMaxSpeed = maxSpeed / 2.0f;
    textures.reserve(static_cast<unsigned long>(numTextures));
    for (int i = 1; i <= numTextures; i++) {
        Texture t;
        t.loadFromFile(vehicle + "/Images/c" + to_string(i) + ".png");
        t.setSmooth(true);
        t.setRepeated(false);
        textures.push_back(t);
    }
}

void Vehicle::setPosition(float pX, float pY) {
    posX = pX;
    posY = pY;
    previousX = pX;
    previousY = pY;
}

void Vehicle::setVehicle(const int typeOfGame){
    speed = 0.0f;
    if (typeOfGame == 0 || typeOfGame == 2){
        posX = -0.3f;
    }
    else {
        posX = 0.f;
    }
    posY = 0.0f;
    previousY = 0.0f;
}

float Vehicle::getPosX() const {
    return posX;
}

float Vehicle::getPreviousX() const {
    return previousX;
}

float Vehicle::getPosY() const {
    return posY;
}

float Vehicle::getMinScreenX() const {
    return minScreenX;
}

float Vehicle::getMaxScreenX() const {
    return maxScreenX;
}

float Vehicle::getAcceleration() const {
    return speed * speed;
}


/**
 * Devuelve la posición actual X.
 * @return
 */
float Vehicle::getSpeed() const {
    return speed;
}



Vehicle::Direction randomDirection() {
    const float p = rand_generator_zero_one();
    if (p < 0.6f)
        return Vehicle::Direction::RIGHT;
    else if (p < 0.8f)
        return Vehicle::Direction::TURNRIGHT;
    else
        return Vehicle::Direction::TURNLEFT;
}

