
#include "../include/TrafficCar.h"

TrafficCar::TrafficCar(float maxSpeed, float speedMul, float scale, int maxCounterToChange, const string &vehicle, float pX, float pY, bool truck) :
        Vehicle(maxSpeed / speedMul, scale, maxCounterToChange, 0, rand_generator_float(-0.5f, 0.5f), pX,
                pY, pY, 0, 0, vehicle, Vehicle_TrafficCar::NUM_ENEMIES_TEXTURES, 1, 0), oriX(this->posX),
        currentDirection(RIGHT), calculatedPath(RIGHT), current_direction_counter(0), max_direction_counter(0),
        probAI(0), typeAI(OBSTACLE)
    {
        isTruck = truck;
    }


void TrafficCar::autoControl(const Configuration &c, float playerPosX, float playerPosY) {
    if (abs(playerPosY - posY) > float(c.renderLen) || rand_generator_zero_one() >= probAI) {
        // Original
        if (current_direction_counter < max_direction_counter) {
            current_direction_counter++;
        } else {
            max_direction_counter = rando_generator_zero_n(Vehicle_TrafficCar::MAX_DIRECTION);
            current_direction_counter = 0;
            calculatedPath = randomDirection();
        }

        float newX = posX;
        if (calculatedPath == TURNRIGHT)
            newX += INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;
        else if (calculatedPath == TURNLEFT)
            newX -= INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;

        if (newX < oriX - 0.15f || newX > oriX + 0.15f)
            calculatedPath = RIGHT;
        else
            posX = newX;

        currentDirection = calculatedPath;
    } else {
        // AI
        if (typeAI == OBSTACLE) {
            const float acc = getAcceleration();
            if (abs(playerPosX - posX) > INCREMENT_X) { // Rotation control
                // The vehicle is not in the player's path
                if (speed < halfMaxSpeed)
                    speed = sqrt(acc + ACCELERATION_INCREMENT);

                if (posX > playerPosX && posX > -0.9f) {
                    posX -= INCREMENT_X * speed / maxSpeed;
                    currentDirection = TURNLEFT;
                } else if (posX < 0.9f) {
                    posX += INCREMENT_X * speed / maxSpeed;
                    currentDirection = TURNRIGHT;
                }
            } else { // Acceleration control
                // The vehicle is in the player's path
                if (posY <= playerPosY)
                    speed = sqrt(acc + ACCELERATION_INCREMENT);
                else if (acc > ACCELERATION_INCREMENT)
                    speed = sqrt(acc - ACCELERATION_INCREMENT);
                else
                    speed = 0.0f;

                currentDirection = RIGHT;
            }
        } else if (typeAI == EVASIVE) {
            if (playerPosX <= -0.5) {
                posX += INCREMENT_X * speed / maxSpeed;
                currentDirection = TURNRIGHT;
            } else if (playerPosX >= 0.5) {
                posX -= INCREMENT_X * speed / maxSpeed;
                currentDirection = TURNLEFT;
            } else {
                if (posX > playerPosX) {
                    posX += INCREMENT_X * speed / maxSpeed;
                    currentDirection = TURNRIGHT;
                } else {
                    posX -= INCREMENT_X * speed / maxSpeed;
                    currentDirection = TURNLEFT;
                }
            }
        } else { // INCONSTANT
            if (currentDirection == TURNRIGHT) {
                const float prevPosX = posX;
                posX += INCREMENT_X * speed / maxSpeed;

                if (posX >= 0.9f)
                    currentDirection = TURNLEFT;
                else if (((prevPosX < -0.5f && posX >= -0.5f) || (prevPosX < 0.0f && posX >= 0.0f) ||
                          (prevPosX < 0.5f && posX >= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    currentDirection = TURNRIGHT; // Lane change
            } else if (currentDirection == TURNLEFT) {
                const float prevPosX = posX;
                posX -= INCREMENT_X * speed / maxSpeed;

                if (posX <= -0.9f)
                    currentDirection = TURNRIGHT;
                else if (((prevPosX > -0.5f && posX <= -0.5f) || (prevPosX > 0.0f && posX <= 0.0f) ||
                          (prevPosX > 0.5f && posX <= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    currentDirection = TURNLEFT; // Lane change
            } else {
                if (rand_generator_zero_one() < 0.5f)
                    currentDirection = TURNRIGHT;
                else
                    currentDirection = TURNLEFT;
            }
        }
    }

    if (speed > maxSpeed)
        speed = maxSpeed;
    else if (speed < 0)
        speed = 0;

    if (posX > 0.9f) {
        posX = 0.9f;
        currentDirection = RIGHT;
    } else if (posX < -0.9f) {
        posX = -0.9f;
        currentDirection = RIGHT;
    }

    previousY = posY;
    posY += speed;
}

void TrafficCar::update(float iniPos, float endPos, float maxAggressiveness, const Difficult& difficulty) {
    speed = maxSpeed * rand_generator_float(0.25f, 0.75f);

    posY = rand_generator_float(iniPos, endPos);
    previousY = posY;

    current_direction_counter = 0;
    max_direction_counter = 0;

    minScreenX = 0;
    maxScreenX = 0;

    setAI(maxAggressiveness, difficulty);
}

void TrafficCar::setAI(float maxAggressiveness, const Difficult& difficulty) {
    if (maxAggressiveness == 0.0f){
        probAI = 0.0f;
    }
    else {
        probAI = rand_generator_float(maxAggressiveness / 2.0f, maxAggressiveness);
    }

    const float p = rand_generator_zero_one();
    switch(difficulty){
        case EASY:
            if (p <= 0.25) {
                typeAI = OBSTACLE;
            }
            else if (p <= 0.75) {
                typeAI = EVASIVE;
            }
            else {
                typeAI = INCONSTANT;
                probAI *= 2.0f;
            }
            break;
        case NORMAL:
            if (p <= 0.5f) {
                typeAI = OBSTACLE;
            }
            else if (p <= 0.75f) {
                typeAI = EVASIVE;
            }
            else {
                typeAI = INCONSTANT;
                probAI *= 2.0f;
            }
            break;
        case HARD:
            if (p <= 0.65f) {
                typeAI = OBSTACLE;
            }
            else if (p <= 0.75f) {
                typeAI = EVASIVE;
            }
            else {
                typeAI = INCONSTANT;
                probAI *= 2.0f;
            }
    }
}

void TrafficCar::draw(const Elevation &e, const float camX) {
    if (counter_code_image >= maxCounterToChange) {
        counter_code_image = 0;

        if (speed > 0.0f)
            current_code_image++;

        if (textures.size() == Vehicle_TrafficCar::NUM_ENEMIES_TEXTURES) {
            if (e == FLAT) {
                if (currentDirection == RIGHT) {
                    if (posX <= camX) {
                        if (current_code_image < 1 || current_code_image > 2)
                            current_code_image = 1;
                    } else {
                        if (current_code_image < 3 || current_code_image > 4)
                            current_code_image = 3;
                    }
                } else if (currentDirection == TURNLEFT) {
                    if (current_code_image < 7 || current_code_image > 8)
                        current_code_image = 7;
                } else { // Turn right
                    if (current_code_image < 5 || current_code_image > 6)
                        current_code_image = 5;
                }
            } else if (e == UP) {
                if (currentDirection == RIGHT) {
                    if (posX <= camX) {
                        if (current_code_image < 13 || current_code_image > 14)
                            current_code_image = 13;
                    } else {
                        if (current_code_image < 15 || current_code_image > 16)
                            current_code_image = 15;
                    }
                } else if (currentDirection == TURNLEFT) {
                    if (current_code_image < 15 || current_code_image > 16)
                        current_code_image = 15;
                } else { // Turn right
                    if (current_code_image < 13 || current_code_image > 14)
                        current_code_image = 13;
                }
            } else { // Down
                if (currentDirection == RIGHT) {
                    if (posX <= camX) {
                        if (current_code_image < 9 || current_code_image > 10)
                            current_code_image = 9;
                    } else {
                        if (current_code_image < 11 || current_code_image > 12)
                            current_code_image = 11;
                    }
                } else if (currentDirection == TURNLEFT) {
                    if (current_code_image < 11 || current_code_image > 12)
                        current_code_image = 11;
                } else { // Turn right
                    if (current_code_image < 9 || current_code_image > 10)
                        current_code_image = 9;
                }
            }
        }
    } else {
        counter_code_image++;
    }
}

void TrafficCar::setMinScreenX(float screenX) {
    minScreenX = screenX;
}

void TrafficCar::setMaxScreenX(float screenX) {
    maxScreenX = screenX;
}

const Texture *TrafficCar::getCurrentTexture() const {
    return &textures[current_code_image - 1];
}

float TrafficCar::getScale() const {
    return scale;
}

bool TrafficCar::hasCrashed(float prevY, float currentY, float minX, float maxX, float &crashPos) const {
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

bool TrafficCar::isVisible(const Configuration &c, float minY, float playerX, float playerY, float &distanceX, float &distanceY) const {
    if (posY < minY || posY > minY + float(c.renderLen) || minScreenX < 0 || maxScreenX > c.w.getSize().y) {
        return false;
    } else {
        distanceX = abs(playerX - posX);
        distanceY = abs(playerY - posY);
        return true;
    }
}


bool TrafficCar::getIsTruck() const{
    return isTruck;
}
