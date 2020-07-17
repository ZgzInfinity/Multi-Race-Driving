
#include "../include/Motorbike.h"


Motorbike::Motorbike(){}


Motorbike::Motorbike(float maxSpeed, float speedMul, float accInc, float scaleX, float scaleY, int maxCounterToChange,
                     const string &vehicle, float pX, float pY, const string brandName, const float angle,
                     const string motorName) : Vehicle(maxSpeed / speedMul, scaleX, maxCounterToChange,
                                                0.0f, pX, pY, pY, 0, 0, vehicle, Motorbike_vehicle::PLAYER_TEXTURES, 1, 0),
                                                speedMul(speedMul), maxAcc(pow(maxSpeed / speedMul, 2.0f)), accInc(accInc),
                                                scaleY(scaleY), acceleration(0),
                                                minCrashAcc(0), xDest(1000), inertia(0), crashing(false),
                                                smoking(false), skidding(false),
                                                firstCrash(true), firstTurnLeft(true),
                                                firstTurnRight(true)
{
    topSpeed = maxSpeed;
    crashNow = false;
    brand = brandName;
    motor = motorName;
    angleTurning = angle;
    outSideRoad = false;
}

float Motorbike::getPreviousY() const {
    return previousY;
}

void Motorbike::hitControl(const bool vehicleCrash) {
    crashing = true;
    smoking = false;
    skidding = false;

    if (speedCollision == 0.f){
        speedCollision = getRealSpeed();
        if (speedCollision < 60.f)
            posY = posY + acceleration * 0.50f;
    }

    acceleration -= accInc * 2.5f;

    if (speed > 1.333f * halfMaxSpeed){
        acceleration -= accInc * 7.5f;
    }
    else if (speed > halfMaxSpeed){
        acceleration -= accInc * 5.0f;
    }
    else if (speed > 0.5f * halfMaxSpeed){
        acceleration -= accInc * 2.5f;
    }

    if (acceleration < 0.0f){
        acceleration = 0.0f;
    }

    mainMutex.lock();
    speed = sqrt(acceleration);
    mainMutex.unlock();

    if (xDest > 0.f && posX < xDest){
        posY = posY + acceleration * 0.20f;
    }
    else if (xDest < 0.f && posX > xDest) {
        posY = posY + acceleration * 0.20f;
    }

    if (current_code_image == 41){
        acceleration = minCrashAcc;
        speed = sqrt(acceleration);
        crashing = false;
        minCrashAcc = 0.0f;
        xDest = 1000;
        inertia = 0;
        previousY = posY;
        speedCollision = 0.0f;
        outSideRoad = false;
        posX = 0.0f;
    }
}

bool Motorbike::isCrashing() const {
    return crashing;
}

float Motorbike::getRealSpeed() const {
    return speed * speedMul;
}

Vehicle::Action Motorbike::accelerationControl(Configuration &c, bool hasGotOut) {
    Action a = NONE;
    smoking = false;
    float previousAcc = acceleration;

    if (Keyboard::isKeyPressed(c.brakeKey))
        a = BRAKE;

    if (a != BRAKE && Keyboard::isKeyPressed(c.accelerateKey)) {
        if (hasGotOut) {
            outSideRoad = true;
            if (acceleration < maxAcc / 4.5f)
                acceleration += accInc / 3.0f;
            else
                acceleration -= accInc * 1.5f;
        }
        else {
            outSideRoad = false;
            if (acceleration < maxAcc)
                acceleration += accInc;
        }

        if (acceleration > maxAcc)
            acceleration = maxAcc;

        smoking = acceleration < maxAcc * 0.1f;
    } else {
        float mul = 2.0f;
        if (a == BRAKE)
            mul *= 2.0f;
        if (hasGotOut)
            mul *= 1.5f;

        if (acceleration > 0.0f)
            acceleration -= accInc * mul;

        if (acceleration < 0.0f)
            acceleration = 0.0f;
    }

    if (previousAcc == 0.0f && acceleration > 0.0f)
        a = BOOT;
    else if (a == NONE && acceleration > 0.0f)
        a = ACCELERATE;

    mainMutex.lock();
    speed = sqrt(acceleration);
    mainMutex.unlock();

    if (speed > 0.0f) {
        previousY = posY;
        posY += speed;
    }
    return a;
}

Vehicle::Direction Motorbike::rotationControl(Configuration &c, float curveCoefficient, const bool& isFinalMap, const int& limitMap) {
    skidding = false;
    if (speed > 0.0f) {
        if (isFinalMap && limitMap - posY <= 150.f){
            if (posX > 0.f){
                posX -= 0.02f;
                if (posX < 0.0f){
                    posX = 0.0f;
                }
            }
            else if (posX < 0.0f) {
                posX += 0.02f;
                if (posX > 0.0f){
                    posX = 0.0f;
                }
            }
        }
        else {
            if (speed < 0.66f * maxSpeed)
                posX -= angleTurning * curveCoefficient * sqrt(speed / 2.0f) * speed / maxSpeed;
            else
                posX -= angleTurning * curveCoefficient * sqrt(speed) * speed / maxSpeed;

            if (abs(curveCoefficient) >= 0.33f && speed >= 0.66f * maxSpeed)
                skidding = true;

            if (Keyboard::isKeyPressed(c.leftKey)) {
                if (inertia > -Motorbike_vehicle::FORCE_INERTIA)
                    inertia--;

                if (inertia < 0) {
                    if (curveCoefficient > 0.0f)
                        skidding = false;

                    if (speed < halfMaxSpeed)
                        posX -= 1.5f * angleTurning * speed / maxSpeed;
                    else if (curveCoefficient == 0.0f)
                        posX -= 1.25f * angleTurning * speed / maxSpeed;
                    else
                        posX -= angleTurning * speed / maxSpeed;

                    return TURNLEFT;
                }
            } else if (Keyboard::isKeyPressed(c.rightKey)) {
                if (inertia < Motorbike_vehicle::FORCE_INERTIA)
                    inertia++;

                if (inertia > 0) {
                    if (curveCoefficient < 0.0f)
                        skidding = false;

                    if (speed < halfMaxSpeed)
                        posX += 1.5f * angleTurning * speed / maxSpeed;
                    else if (curveCoefficient == 0.0f)
                        posX += 1.25f * angleTurning * speed / maxSpeed;
                    else
                        posX += angleTurning * speed / maxSpeed;

                    return TURNRIGHT;
                }
            } else if (inertia > 0) {
                inertia--;
            } else if (inertia < 0) {
                inertia++;
            }

            skidding = false;
        }
    }
    return RIGHT;
}

void Motorbike::draw(Configuration &c, SoundPlayer &r, const Action &a, const Direction &d,
                    const Elevation &e, int terrain, bool enableSound)
{
    // Sound effects
    if (a != CRASH)
        firstCrash = true;

    if (enableSound) {
        if (speed > 0.0f) {
            if (a == BOOT) {
                // Acceleration sound
                r.soundEffects[30]->stop();
                r.soundEffects[30]->play();
            }
            if (r.soundEffects[31]->getStatus() != SoundSource::Playing) {
                // Engine sound
                r.soundEffects[31]->stop();
                r.soundEffects[31]->play();
            }
            r.soundEffects[31]->setVolume((33.0f + 67.0f * speed / maxSpeed) * float(r.volumeEffects) / 100.f);
            if (skidding && r.soundEffects[8]->getStatus() != SoundSource::Playing) {
                // Skidding sound
                r.soundEffects[8]->stop();
                r.soundEffects[8]->play();
            }
            if (outSideRoad && r.soundEffects[53]->getStatus() != SoundSource::Playing) {
                // Outside sound
                r.soundEffects[53]->stop();
                r.soundEffects[53]->play();
            }
            else if (!outSideRoad && r.soundEffects[53]->getStatus() == SoundSource::Playing){
                // Outside sound
                r.soundEffects[53]->stop();
            }
        }
        else {
            r.soundEffects[12]->stop();
            r.soundEffects[31]->stop();
            r.soundEffects[8]->stop();
            r.soundEffects[53]->stop();
        }

        if (a == CRASH && firstCrash) {
            firstCrash = false;
            r.soundEffects[32]->stop();
            r.soundEffects[18]->stop();
            r.soundEffects[19]->stop();
            r.soundEffects[32]->play();
            r.soundEffects[rand_generator_int(18, 19)]->play();
        }
    }
    else {
        r.soundEffects[12]->stop();
        r.soundEffects[31]->stop();
        r.soundEffects[8]->stop();
        r.soundEffects[53]->stop();
        r.soundEffects[32]->stop();
        r.soundEffects[18]->stop();
        r.soundEffects[19]->stop();
    }

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

            if (speed > 0.0f){
                if (crashing){
                    current_code_image++;
                    maxCounterToChange = 5;
                }
                else {
                    current_code_image++;
                    maxCounterToChange = COUNTER;
                }
            }
            else if (crashing){
                current_code_image++;
                maxCounterToChange = 5;
            }
            else {
                maxCounterToChange = COUNTER;
            }

            if (textures.size() == Motorbike_vehicle::PLAYER_TEXTURES) {
                if (a == ACCELERATE || a == BOOT) {
                    if (e == FLAT) {
                        if (d == RIGHT) {
                            if (current_code_image < 1 || current_code_image > 2)
                                current_code_image = 1;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 3 || current_code_image > 8)
                                    current_code_image = 3;
                                if (current_code_image == 7)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 7 || current_code_image > 8)
                                    current_code_image = 7;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 9 || current_code_image > 14)
                                    current_code_image = 9;
                                if (current_code_image == 13)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 13 || current_code_image > 14)
                                    current_code_image = 13;
                            }
                        }
                    }
                     else if (e == UP) {
                        if (d == RIGHT) {
                            if (current_code_image < 1 || current_code_image > 2)
                                current_code_image = 1;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 3 || current_code_image > 8)
                                    current_code_image = 3;
                                if (current_code_image == 7)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 7 || current_code_image > 8)
                                    current_code_image = 7;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 9 || current_code_image > 14)
                                    current_code_image = 9;
                                if (current_code_image == 13)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 13 || current_code_image > 14)
                                    current_code_image = 13;
                            }
                        }
                    }
                    else { // Down
                        if (d == RIGHT) {
                            if (current_code_image < 1 || current_code_image > 2)
                                current_code_image = 1;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 3 || current_code_image > 8)
                                    current_code_image = 3;
                                if (current_code_image == 7)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 7 || current_code_image > 8)
                                    current_code_image = 7;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 9 || current_code_image > 14)
                                    current_code_image = 9;
                                if (current_code_image == 13)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 13 || current_code_image > 14)
                                    current_code_image = 13;
                            }
                        }
                    }
                } else if (a == BRAKE) {
                    if (e == FLAT) {
                        if (d == RIGHT) {
                            if (current_code_image < 15 || current_code_image > 16)
                                current_code_image = 15;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 17 || current_code_image > 22)
                                    current_code_image = 17;
                                if (current_code_image == 21)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 21 || current_code_image > 22)
                                    current_code_image = 21;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 23 || current_code_image > 28)
                                    current_code_image = 23;
                                if (current_code_image == 27)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 27 || current_code_image > 28)
                                    current_code_image = 27;
                            }
                        }
                    } else if (e == UP) {
                        if (d == RIGHT) {
                            if (current_code_image < 15 || current_code_image > 16)
                                current_code_image = 15;
                        } else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 17 || current_code_image > 22)
                                    current_code_image = 17;
                                if (current_code_image == 21)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 21 || current_code_image > 22)
                                    current_code_image = 21;
                            }
                        } else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 23 || current_code_image > 28)
                                    current_code_image = 23;
                                if (current_code_image == 27)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 27 || current_code_image > 28)
                                    current_code_image = 27;
                            }
                        }
                    } else { // Down
                        if (d == RIGHT) {
                            if (current_code_image < 15 || current_code_image > 16)
                                current_code_image = 15;
                        } else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 17 || current_code_image > 22)
                                    current_code_image = 17;
                                if (current_code_image == 21)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 21 || current_code_image > 22)
                                    current_code_image = 21;
                            }
                        } else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 23 || current_code_image > 28)
                                    current_code_image = 23;
                                if (current_code_image == 27)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 27 || current_code_image > 28)
                                    current_code_image = 27;
                            }
                        }
                    }
                }
                else {
                    if (current_code_image < 29 || current_code_image > 41)
                        current_code_image = 29;
                }
            }
        }
        else {
            counter_code_image++;
        }
    }
    else {
        current_code_image = 1;
    }

    sprite.setTexture(textures[current_code_image - 1], true);
    sprite.setScale(scale * c.screenScale, scaleY * c.screenScale);
    minScreenX = ((float) c.w.getSize().x) / 2.0f - sprite.getGlobalBounds().width / 2.0f;
    maxScreenX = minScreenX + sprite.getGlobalBounds().width;
    if (c.isDefaultScreen){
        sprite.setPosition(minScreenX, ((float) c.w.getSize().y) * c.camD - sprite.getGlobalBounds().height / 2.0f);
    }
    else {
        sprite.setPosition(minScreenX, ((float) c.w.getSize().y) * c.camD - sprite.getGlobalBounds().height / 2.0f - 15.f);
    }
    c.w.draw(sprite);


    if (smoking || skidding) {
        maxCounterToChange = COUNTER + 1;
        const float j = sprite.getPosition().y + sprite.getGlobalBounds().height;
        sprite.setTexture(textures[41 + current_code_image % 4], true);
        sprite.setScale(3.f * c.screenScale, 3.5f * c.screenScale);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f - sprite.getGlobalBounds().width,
                           j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f, j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
    }
    else if (crashing){
        if (getRealSpeed() < 20.f){
                maxCounterToChange = COUNTER + 6;
        }
        else if (getRealSpeed() >= 20.f && getRealSpeed() < 60.f){
            maxCounterToChange = COUNTER + 5;
        }
        else if (getRealSpeed() >= 60.f && getRealSpeed() < 100.f){
            maxCounterToChange = COUNTER + 3;
        }
        else if (getRealSpeed() >= 100.f && getRealSpeed() < 120.f){
            maxCounterToChange = COUNTER + 2;
        }
        else if (getRealSpeed() >= 120.f){
            maxCounterToChange = COUNTER + 1;
        }
    }
    else if (outSideRoad){
        maxCounterToChange = COUNTER;
        const float j = sprite.getPosition().y + sprite.getGlobalBounds().height;
        switch(terrain){
        case 0:
            sprite.setTexture(textures[53 + current_code_image % 8], true);
            break;
        case 1:
            sprite.setTexture(textures[47 + current_code_image % 6], true);
            break;
        case 2:
            sprite.setTexture(textures[61 + current_code_image % 6], true);
        }
        sprite.setScale(3.f * c.screenScale, 3.5f * c.screenScale);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f - sprite.getGlobalBounds().width,
                           j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f, j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
    }
    else if (!crashing) {
        maxCounterToChange = COUNTER;
    }
}



void Motorbike::setSmoking(bool smoke) {
    smoking = smoke;
}


void Motorbike::setVehicle(const int typeOfGame){
    Vehicle::setVehicle(typeOfGame);
    acceleration = 0.0f;
    minCrashAcc = 0.0f;
    inertia = 0.0f;
    xDest = 0.0f;
    accInc = topSpeed * ACCELERATION_INCREMENT / MAX_SPEED;
    smoking = false;
    skidding = false;
    firstCrash = true;
    firstTurnLeft = true;
    firstTurnRight = true;
}


float Motorbike::getHalfMaxSpeed(){
    return halfMaxSpeed;
}


string Motorbike::getBrandName(){
    return brand;
}


float Motorbike::getAngle(){
    return angleTurning;
}


string Motorbike::getMotorName(){
    return motor;
}


float Motorbike::getTopSpeed(){
    return topSpeed;
}

