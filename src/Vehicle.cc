

#include "../include/Vehicle.h"

Vehicle::Vehicle(){}


Vehicle::Vehicle(const float maxSpeed, const float scale, const int maxCounterToChange, float speed, float posX,
                 float posY, float previousY, float minScreenX, float maxScreenX, const string &vehicle,
                 int numTextures,
                 int currentCodeImage, int counterCodeImage) : maxSpeed(maxSpeed), scale(scale),
                                                               maxCounterToChange(maxCounterToChange), speed(speed),
                                                               halfMaxSpeed(maxSpeed / 2.0f), posX(posX), posY(posY),
                                                               previousY(previousY), minScreenX(minScreenX),
                                                               maxScreenX(maxScreenX),
                                                               current_code_image(currentCodeImage),
                                                               counter_code_image(counterCodeImage) {
    textures.reserve(static_cast<unsigned long>(numTextures));
    for (int i = 1; i <= numTextures; i++) {
        Texture t;
        t.loadFromFile("Data/Vehicles/" + vehicle + "/Images/c" + to_string(i) + ".png");
        t.setSmooth(true);
        t.setRepeated(false);
        textures.push_back(t);
    }
}

void Vehicle::setPosition(float pX, float pY) {
    posX = pX;
    posY = pY;
    previousY = pY;
}

void Vehicle::setVehicle(){
    speed = 0.0f;
    posX = 0.0f;
    posY = 0.0f;
    previousY = 0.0f;
}

float Vehicle::getPosX() const {
    return posX;
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
