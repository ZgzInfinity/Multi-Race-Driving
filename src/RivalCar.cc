
#include "../include/RivalCar.h"

RivalCar::RivalCar(){}

RivalCar::RivalCar(float maxSpeed, float speedMul, float scale, int maxCounterToChange, const string &vehicle, float pX, float pY,
                   int totalTextures, int lowTextureRight, int highTextureRight, int lowTextureRightBrake, int highTextureRightBrake,
                   int lowTextureTurnleft, int highTextureTurnLeft, int lowTextureTurnLeftBrake, int highTextureTurnLeftBrake,
                   int lowTextureTurnRight, int highTextureTurnRight, int lowTextureTurnRightBrake, int highTextureTurnRightBrake,
                   int lowTextureUp, int highTextureUp, int lowTextureUpBrake, int highTextureUpBrake, int lowTextureTurnleftUp,
                   int highTextureTurnLeftUp, int lowTextureTurnLeftBrakeUp, int highTextureTurnLeftBrakeUp,  int lowTextureTurnRightUp,
                   int highTextureTurnRightUp, int lowTextureTurnRightBrakeUp, int highTextureTurnRightBrakeUp, int mediumTurnLeft,
                   int mediumTurnRight, int mediumTurnLeftUp, int mediumTurnRightUp, int mediumTurnLeftBrake, int mediumTurnRightBrake,
                   int mediumTurnLeftBrakeUp, int mediumTurnRightBrakeUp, float scaling) :
                    Vehicle(maxSpeed / speedMul, scale, maxCounterToChange, 0, pX,
                    pY, pY, 0, 0, vehicle, totalTextures, 1, 0), oriX(this->posX),
                    currentDirection(RIGHT), calculatedPath(RIGHT), current_direction_counter(0), max_direction_counter(0),
                    probAI(0), typeAI(OBSTACLE)
{
    // Assignment of the attributes
    numTextures = totalTextures; minTextureRight = lowTextureRight; maxTextureRight = highTextureRight;
    minTextureRightBrake = lowTextureRightBrake; maxTextureRightBrake = highTextureRightBrake; minTextureTurnleft = lowTextureTurnleft;
    maxTextureTurnLeft = highTextureTurnLeft; minTextureTurnLeftBrake = lowTextureTurnLeftBrake;
    maxTextureTurnLeftBrake = highTextureTurnLeftBrake; minTextureTurnRight = lowTextureTurnRight;
    maxTextureTurnRight = highTextureTurnRight; minTextureTurnRightBrake = lowTextureTurnRightBrake;
    maxTextureTurnRightBrake = highTextureTurnRightBrake; minTextureUp = lowTextureUp; maxTextureUp = highTextureUp;
    minTextureUpBrake = lowTextureUpBrake; maxTextureUpBrake = highTextureUpBrake; minTextureTurnLeftUp = lowTextureTurnleftUp;
    maxTextureTurnLeftUp = highTextureTurnLeftUp; minTextureTurnLeftBrakeUp = lowTextureTurnLeftBrakeUp;
    maxTextureTurnLeftBrakeUp = highTextureTurnLeftBrakeUp; minTextureTurnRightUp = lowTextureTurnRightUp;
    maxTextureTurnRightUp = highTextureTurnRightUp; minTextureTurnRightBrakeUp = lowTextureTurnRightBrakeUp;
    maxTextureTurnRightBrakeUp = highTextureTurnRightBrakeUp,

    medTurnLeft = mediumTurnLeft;
    medTurnRight = mediumTurnRight;
    medTurnLeftUp = mediumTurnLeftUp;
    medTurnRightUp = mediumTurnRightUp;
    medTurnLeftBrake = mediumTurnLeftBrake;
    medTurnRightBrake = mediumTurnRightBrake;
    medTurnLeftBrakeUp = mediumTurnLeftBrakeUp;
    medTurnRightBrakeUp = mediumTurnRightBrakeUp;

    scalingFactor = scaling;
}



void RivalCar::autoControl(const Configuration &c, float playerPosX, float playerPosY) {}



void RivalCar::update(Configuration& c, float iniPos, float endPos, float maxAggressiveness, Action& a, Direction& d, float directionCurve,
                      const Difficult& difficulty, const float playerPosX, const float playerPosY)
{
    // Get the last speed;
    lastSpeed = speed;

    // Update the speed of the car
    const float acc = getAcceleration();

    // Control the speed of the vehicle
    if (speed <= 0.4f){
        // Increase the speed slowly
        speed = sqrt(acc + ACCELERATION_INCREMENT);

        // Update the y position of the vehicle in the landscape
        previousY = posY;
        posY += speed;
        a = BOOT;
    }
    else {
        if (directionCurve != 0.f){
            if (directionCurve > 0.f){
                d = TURNRIGHT;
            }
            else if (directionCurve < 0.f){
                d = TURNLEFT;
            }
        }
        // Control the distance between the player and the vehicle
        if (abs(playerPosY - posY) > 3.0f * float(c.renderLen)){
            if (speed > 50.f){
                // Reduce speed;
                speed = 0.65f * speed;
                // Check if the vehicle has increased or reduced its speed
                a = BRAKE;
            }
        }
        else if (abs(playerPosY - posY) > 2.0f * float(c.renderLen)){
            if (speed > 50.f){
                // Reduce speed;
                speed = 0.85f * speed;
                // Check if the vehicle has increased or reduced its speed
                a = BRAKE;
            }
        }
        else {
            // Accelerate
            speed = sqrt(acc + (ACCELERATION_INCREMENT / 2.f));
            if (speed > maxSpeed){
                speed = maxSpeed;
            }
            a = ACCELERATE;
        }
        previousY = posY;
        posY += speed;
    }
}



void RivalCar::setAI(float maxAggressiveness, const Difficult& difficulty) {
    if (maxAggressiveness == 0.0f){
        probAI = 0.0f;
    }
    else {
        probAI = rand_generator_float(maxAggressiveness / 2.0f, maxAggressiveness);
    }

    const float p = rand_generator_zero_one();
    switch(difficulty){
    case PEACEFUL:
        if (p < 0.05f) {
            typeAI = INCONSTANT;
        }
        else if (p < 0.1f) {
            typeAI = OBSTACLE;
        }
        else {
            typeAI = EVASIVE;
            probAI *= 2.0f;
        }
        break;
    case EASY:
        if (p < 0.2f) {
            typeAI = INCONSTANT;
        }
        else if (p < 0.4f) {
            typeAI = OBSTACLE;
        }
        else {
            typeAI = EVASIVE;
            probAI *= 2.0f;
        }
        break;
    case NORMAL:
        if (p < 0.2f) {
            typeAI = INCONSTANT;
        }
        else if (p < 0.5f) {
            typeAI = OBSTACLE;
        }
        else {
            typeAI = EVASIVE;
            probAI *= 2.0f;
        }
        break;
    case HARD:
        if (p < 0.1f) {
            typeAI = INCONSTANT;
        }
        else if (p < 0.2f) {
            typeAI = OBSTACLE;
        }
        else {
            typeAI = EVASIVE;
            probAI *= 2.0f;
        }
    }
}



void RivalCar::draw(const Action &a, const Direction &d, const Elevation &e) {

    // Draw
    if (d != TURNLEFT){
        firstTurnLeft = true;
    }
    if (d != TURNRIGHT){
        firstTurnRight = true;
    }

    if (a != NONE) {
        if (counter_code_image >= maxCounterToChange) {
            counter_code_image = 0;

            if (speed > 0.0f)
                current_code_image++;

            if ((int)textures.size() == numTextures) {
                if (a == ACCELERATE || a == BOOT) {
                    if (e == FLAT) {
                        if (d == RIGHT) {
                            if (current_code_image < minTextureRight || current_code_image > maxTextureRight)
                                current_code_image = minTextureRight;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnleft || current_code_image > maxTextureTurnLeft)
                                    current_code_image = minTextureTurnleft;
                                if (current_code_image == medTurnLeft)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < medTurnLeft || current_code_image > maxTextureTurnLeft)
                                    current_code_image = medTurnLeft;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < minTextureTurnRight || current_code_image > maxTextureTurnRight)
                                    current_code_image = minTextureTurnRight;
                                if (current_code_image == medTurnRight)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < medTurnRight || current_code_image > maxTextureTurnRight)
                                    current_code_image = medTurnRight;
                            }
                        }
                    }
                     else if (e == UP) {
                        if (d == RIGHT) {
                            if (current_code_image < minTextureUp || current_code_image > maxTextureUp)
                                current_code_image = minTextureUp;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnLeftUp || current_code_image > maxTextureTurnLeftUp)
                                    current_code_image = minTextureTurnLeftUp;
                                if (current_code_image == medTurnLeftUp)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < medTurnLeftUp || current_code_image > maxTextureTurnLeftUp)
                                    current_code_image = medTurnLeftUp;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < minTextureTurnRightUp || current_code_image > 18)
                                    current_code_image = minTextureTurnRightUp;
                                if (current_code_image == medTurnRightUp)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < medTurnRightUp || current_code_image > maxTextureTurnRightUp)
                                    current_code_image = medTurnRightUp;
                            }
                        }
                    }
                    else { // Down
                        if (d == RIGHT) {
                            if (current_code_image < minTextureRight || current_code_image > maxTextureRight)
                                current_code_image = minTextureRight;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnleft || current_code_image > maxTextureTurnLeft)
                                    current_code_image = minTextureTurnleft;
                                if (current_code_image == medTurnLeft)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < medTurnLeft || current_code_image > maxTextureTurnLeft)
                                    current_code_image = medTurnLeft;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < minTextureTurnRight || current_code_image > maxTextureTurnRight)
                                    current_code_image = minTextureTurnRight;
                                if (current_code_image == medTurnRight)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < medTurnRight || current_code_image > maxTextureTurnRight)
                                    current_code_image = medTurnRight;
                            }
                        }
                    }
                } else if (a == BRAKE) {
                    if (e == FLAT) {
                        if (d == RIGHT) {
                            if (current_code_image < minTextureRightBrake || current_code_image > maxTextureRightBrake)
                                current_code_image = minTextureRightBrake;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnLeftBrake || current_code_image > maxTextureTurnLeftBrakeUp)
                                    current_code_image = minTextureTurnLeftBrake;
                                if (current_code_image == medTurnLeftBrake)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < medTurnLeftBrake || current_code_image > maxTextureTurnLeftBrakeUp)
                                    current_code_image = medTurnLeftBrake;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < minTextureTurnRightBrake || current_code_image > maxTextureTurnRightBrake)
                                    current_code_image = minTextureTurnRightBrake;
                                if (current_code_image == medTurnRightBrake)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < medTurnRightBrake || current_code_image > maxTextureTurnRightBrake)
                                    current_code_image = medTurnRightBrake;
                            }
                        }
                    } else if (e == UP) {
                        if (d == RIGHT) {
                            if (current_code_image < minTextureUpBrake || current_code_image > maxTextureUpBrake)
                                current_code_image = minTextureUpBrake;
                        } else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnLeftUp || current_code_image > maxTextureTurnLeftUp)
                                    current_code_image = minTextureTurnLeftUp;
                                if (current_code_image == medTurnLeftBrakeUp)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < medTurnLeftBrakeUp || current_code_image > maxTextureTurnLeftUp)
                                    current_code_image = medTurnLeftBrakeUp;
                            }
                        } else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < minTextureTurnRightUp || current_code_image > maxTextureTurnRightUp)
                                    current_code_image = minTextureTurnRightUp;
                                if (current_code_image == medTurnRightBrakeUp)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < medTurnRightBrakeUp || current_code_image > maxTextureTurnRightUp)
                                    current_code_image = medTurnRightBrakeUp;
                            }
                        }
                    } else { // Down
                        if (d == RIGHT) {
                            if (current_code_image < minTextureRightBrake || current_code_image > maxTextureRightBrake)
                                current_code_image = minTextureRightBrake;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnLeftBrake || current_code_image > maxTextureTurnLeftBrakeUp)
                                    current_code_image = minTextureTurnLeftBrake;
                                if (current_code_image == medTurnLeftBrake)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < medTurnLeftBrake || current_code_image > maxTextureTurnLeftBrakeUp)
                                    current_code_image = medTurnLeftBrake;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < minTextureTurnRightBrake || current_code_image > maxTextureTurnRightBrake)
                                    current_code_image = minTextureTurnRightBrake;
                                if (current_code_image == medTurnRightBrake)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < medTurnRightBrake || current_code_image > maxTextureTurnRightBrake)
                                    current_code_image = medTurnRightBrake;
                            }
                        }
                    }
                }
                // BE CAREFUL CRASH
            }
        }
        else {
            counter_code_image++;
        }
    }
    else {
        current_code_image = 1;
    }
}



void RivalCar::setMinScreenX(float screenX) {
    minScreenX = screenX;
}



void RivalCar::setMaxScreenX(float screenX) {
    maxScreenX = screenX;
}



const Texture *RivalCar::getCurrentTexture() const {
    return &textures[current_code_image - 1];
}



float RivalCar::getScale() const {
    return scale;
}


/**
 * Devuelve la escala actual del vehículo.
 * @return
 */
float RivalCar::getScalingFactor() const {
    return scalingFactor;
}



bool RivalCar::hasCrashed(float prevY, float currentY, float minX, float maxX, float &crashPos) const {
    if (minScreenX != maxScreenX && ((prevY <= posY + 2.5f && currentY >= posY - 2.5f) ||
                                     (currentY <= posY + 2.5f && prevY >= posY - 2.5f)) && // y matches
        ((minX >= minScreenX && minX <= maxScreenX) ||
         (maxX >= minScreenX && maxX <= maxScreenX) ||
         (minScreenX >= minX && minScreenX <= maxX) ||
         (maxScreenX >= minX && maxScreenX <= maxX))) { // x matches
        crashPos = posY;
        return true;
    }
    return false;
}



bool RivalCar::isVisible(const Configuration &c, float minY, float playerX, float playerY, float &distanceX, float &distanceY) const {
    if (posY < minY || posY > minY + float(c.renderLen) || minScreenX < 0 || maxScreenX > c.w.getSize().y) {
        return false;
    } else {
        distanceX = abs(playerX - posX);
        distanceY = abs(playerY - posY);
        return true;
    }
}
