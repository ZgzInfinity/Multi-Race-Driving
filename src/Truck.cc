
#include "../include/Truck.h"


Truck::Truck(){}


Truck::Truck(float maxSpeed, float speedMul, float accInc, float scaleX, float scaleY, int maxCounterToChange,
                       const string &vehicle, float pX, float pY, const string brandName, const float angle,
                       const string motorName) : Vehicle(maxSpeed / speedMul, scaleX, maxCounterToChange,
                                                 0.0f, pX, pY, pY, 0, 0, vehicle, Truck_vehicle::PLAYER_TEXTURES, 1, 0),
                                                 speedMul(speedMul), maxAcc(pow(maxSpeed / speedMul, 2.0f)),
                                                 accInc(accInc), scaleY(scaleY), acceleration(0),
                                                 minCrashAcc(0), xDest(1000), inertia(0), crashing(false),
                                                 smoking(false), skidding(false),
                                                 firstCrash(true), firstTurnLeft(true),
                                                 firstTurnRight(true)
{
    topSpeed = maxSpeed;
    mode = -1;
    brand = brandName;
    angleTurning = angle;
    motor = motorName;
    speedCollision = 0.f;
    outSideRoad = false;
}

float Truck::getPreviousY() const {
    return previousY;
}

void Truck::hitControl(const bool vehicleCrash) {
    crashing = true;
    smoking = false;
    skidding = false;

    if (speedCollision == 0.f){
        speedCollision = getRealSpeed();
    }

    if (xDest == 1000){
        if (posX > 0.0f){
            xDest = -(acceleration * 1.7f / maxAcc);
        }
        else {
            xDest = acceleration * 1.7f / maxAcc;
        }
    }

    if (xDest > 0.0f){
        if (speedCollision <= 40.f){
            posX = posX + (acceleration * angleTurning / maxAcc) * 40.f;
        }
        else if (speedCollision > 40.f && speedCollision < 85.f){
            posX = posX + (acceleration * angleTurning / maxAcc) * 20.f;
        }
        else if (speedCollision >= 85.f && speedCollision < 100.f){
            posX = posX + (acceleration * angleTurning / maxAcc) * 10.f;
        }
        else if (speedCollision >= 100.f && speedCollision < 120.f){
            posX = posX + (acceleration * angleTurning / maxAcc) * 5.f;
        }
        else {
            posX = posX + (acceleration * angleTurning / maxAcc) * 1.5f;
        }
    }
    else {
        if (speedCollision <= 40.f){
            posX = posX - (acceleration * angleTurning / maxAcc) * 40.f;
        }
        else if (speedCollision > 40.f && speedCollision <= 85.f){
            posX = posX - (acceleration * angleTurning / maxAcc) * 20.f;
        }
        else if (speedCollision > 85.f && speedCollision < 100.f){
            posX = posX - (acceleration * angleTurning / maxAcc) * 10.f;
        }
        else if (speedCollision >= 100.f && speedCollision < 120.f){
            posX = posX - (acceleration * angleTurning / maxAcc) * 5.f;
        }
        else {
            posX = posX - (acceleration * angleTurning / maxAcc) * 1.5f;
        }

    }

    if (vehicleCrash){
        if (minCrashAcc <= 0.0f) { // Only first time
            minCrashAcc = (speed * 0.1555f) * (speed * 0.1555f);
            acceleration = (speed * 0.75f) * (speed * 0.75f);
        }
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

    speed = sqrt(acceleration);

    if (xDest > 0.f && posX < xDest){
        if (!vehicleCrash){
            posY = posY + acceleration * 7.f / maxAcc;
        }
        else {
            posY = posY - acceleration * 7.f / maxAcc;
        }
    }
    else if (xDest < 0.f && posX > xDest) {
        if (!vehicleCrash){
            posY = posY + acceleration * 7.f / maxAcc;
        }
        else {
            posY = posY - acceleration * 7.f / maxAcc;
        }
    }

    if (acceleration <= minCrashAcc){
        acceleration = minCrashAcc;
        speed = sqrt(acceleration);
        crashing = false;
        minCrashAcc = 0.0f;
        xDest = 1000;
        inertia = 0;
        previousY = posY;
        mode = -1;
        speedCollision = 0.0f;
        outSideRoad = false;
    }
}

bool Truck::isCrashing() const {
    return crashing;
}

float Truck::getRealSpeed() const {
    return speed * speedMul;
}

Vehicle::Action Truck::accelerationControl(Configuration &c, bool hasGotOut) {
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
        } else {
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

    speed = sqrt(acceleration);
    if (speed > 0.0f) {
        previousY = posY;
        posY += speed;
    }
    return a;
}

Vehicle::Direction Truck::rotationControl(Configuration &c, float curveCoefficient, const bool& isFinalMap, const int& limitMap) {
    skidding = false;

    if (speed > 0.0f) {
        if (isFinalMap && limitMap - posY <= 130.f){
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
                if (inertia > -Truck_vehicle::FORCE_INERTIA)
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
                if (inertia < Truck_vehicle::FORCE_INERTIA)
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

void Truck::draw(Configuration &c, SoundPlayer &r, const Action &a, const Direction &d,
                  const Elevation &e, int terrain, bool enableSound)
{
    // Sound effects
    if (a != CRASH)
        firstCrash = true;

    if (enableSound) {
        if (speed > 0.0f) {
            if (a == BOOT) {
                // Acceleration sound
                r.soundEffects[33]->stop();
                r.soundEffects[33]->play();
            }
            if (r.soundEffects[34]->getStatus() != SoundSource::Playing) {
                // Engine sound
                r.soundEffects[34]->stop();
                r.soundEffects[34]->play();
            }
            r.soundEffects[34]->setVolume((33.0f + 67.0f * speed / maxSpeed) * float(r.volumeEffects) / 100.f);
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
            r.soundEffects[34]->stop();
            r.soundEffects[8]->stop();
            r.soundEffects[53]->stop();
        }

        if (a == CRASH && firstCrash) {
            firstCrash = false;
            r.soundEffects[17]->stop();
            r.soundEffects[18]->stop();
            r.soundEffects[19]->stop();
            r.soundEffects[17]->play();
            r.soundEffects[rand_generator_int(18, 19)]->play();
            if (r.soundEffects[52]->getStatus() != SoundSource::Playing) {
                // Engine sound
                r.soundEffects[52]->stop();
                r.soundEffects[52]->play();
            }
        }
    }
    else {
        r.soundEffects[12]->stop();
        r.soundEffects[34]->stop();
        r.soundEffects[8]->stop();
        r.soundEffects[53]->stop();
        r.soundEffects[17]->stop();
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

            if (speed > 0.0f)
                current_code_image++;

            if (textures.size() == Truck_vehicle::PLAYER_TEXTURES) {
                if (a == ACCELERATE || a == BOOT) {
                    if (e == FLAT) {
                        if (d == RIGHT) {
                            if (current_code_image < 1 || current_code_image > 5)
                                current_code_image = 1;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 6 || current_code_image > 10)
                                    current_code_image = 6;
                                if (current_code_image == 7)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 7 || current_code_image > 10)
                                    current_code_image = 7;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 11 || current_code_image > 15)
                                    current_code_image = 11;
                                if (current_code_image == 12)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 12 || current_code_image > 15)
                                    current_code_image = 12;
                            }
                        }
                    }
                     else if (e == UP) {
                        if (d == RIGHT) {
                            if (current_code_image < 16 || current_code_image > 19)
                                current_code_image = 16;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 20 || current_code_image > 23)
                                    current_code_image = 20;
                                if (current_code_image == 21)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 21 || current_code_image > 23)
                                    current_code_image = 21;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 24 || current_code_image > 27)
                                    current_code_image = 24;
                                if (current_code_image == 25)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 25 || current_code_image > 27)
                                    current_code_image = 25;
                            }
                        }
                    }
                    else { // Down
                        if (d == RIGHT) {
                            if (current_code_image < 1 || current_code_image > 5)
                                current_code_image = 1;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 6 || current_code_image > 6)
                                    current_code_image = 6;
                                if (current_code_image == 7)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 7 || current_code_image > 10)
                                    current_code_image = 7;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 11 || current_code_image > 15)
                                    current_code_image = 11;
                                if (current_code_image == 12)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 12 || current_code_image > 15)
                                    current_code_image = 12;
                            }
                        }
                    }
                } else if (a == BRAKE) {
                    if (e == FLAT) {
                        if (d == RIGHT) {
                            if (current_code_image < 28 || current_code_image > 32)
                                current_code_image = 28;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 33 || current_code_image > 37)
                                    current_code_image = 33;
                                if (current_code_image == 34)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 34 || current_code_image > 37)
                                    current_code_image = 34;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 38 || current_code_image > 42)
                                    current_code_image = 38;
                                if (current_code_image == 39)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 39 || current_code_image > 42)
                                    current_code_image = 39;
                            }
                        }
                    } else if (e == UP) {
                        if (d == RIGHT) {
                            if (current_code_image < 43 || current_code_image > 46)
                                current_code_image = 43;
                        } else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 47 || current_code_image > 50)
                                    current_code_image = 47;
                                if (current_code_image == 48)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 48 || current_code_image > 50)
                                    current_code_image = 48;
                            }
                        } else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 51 || current_code_image > 54)
                                    current_code_image = 51;
                                if (current_code_image == 52)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 52 || current_code_image > 54)
                                    current_code_image = 52;
                            }
                        }
                    }
                    else { // Down
                                                if (d == RIGHT) {
                            if (current_code_image < 28 || current_code_image > 32)
                                current_code_image = 28;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 33 || current_code_image > 37)
                                    current_code_image = 33;
                                if (current_code_image == 34)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 34 || current_code_image > 37)
                                    current_code_image = 34;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 38 || current_code_image > 42)
                                    current_code_image = 38;
                                if (current_code_image == 39)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 39 || current_code_image > 42)
                                    current_code_image = 39;
                            }
                        }
                    }
                }
                else {
                    // Crash
                    if (mode == 0) {
                        if (current_code_image < 55 || current_code_image > 62)
                            current_code_image = 55;
                    }
                    else if (mode == 1) {
                        if (current_code_image < 63 || current_code_image > 70)
                            current_code_image = 63;
                    }
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


    if (smoking || skidding || crashing) {
        if (!crashing){
            maxCounterToChange = COUNTER + 2;
        }
        else {
            if (getRealSpeed() < 20.f){
                maxCounterToChange = COUNTER + 4;
            }
            else if (getRealSpeed() >= 20.f && getRealSpeed() < 60.f){
                maxCounterToChange = COUNTER + 3;
            }
            else if (getRealSpeed() >= 60.f && getRealSpeed() < 100.f){
                maxCounterToChange = COUNTER + 2;
            }
            else if (getRealSpeed() >= 100.f && getRealSpeed() < 120.f){
                maxCounterToChange = COUNTER + 1;
            }
            else if (getRealSpeed() >= 120.f){
                maxCounterToChange = COUNTER;
            }
        }
        const float j = sprite.getPosition().y + sprite.getGlobalBounds().height;
        sprite.setTexture(textures[70 + current_code_image % 4], true);
        sprite.setScale(3.f * c.screenScale, 3.5f * c.screenScale);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f - sprite.getGlobalBounds().width,
                           j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f, j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
    }
    else if (outSideRoad){
        maxCounterToChange = COUNTER;
        const float j = sprite.getPosition().y + sprite.getGlobalBounds().height;
        switch(terrain){
        case 0:
            sprite.setTexture(textures[81 + current_code_image % 8], true);
            break;
        case 1:
            sprite.setTexture(textures[75 + current_code_image % 6], true);
            break;
        case 2:
            sprite.setTexture(textures[89 + current_code_image % 6], true);
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



void Truck::setSmoking(bool smoke) {
    smoking = smoke;
}


void Truck::setVehicle(){
    Vehicle::setVehicle();
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


void Truck::setModeCollision(){
    if (mode == -1){
        mode = rand_generator_int(0, 1);
    }
}


float Truck::getHalfMaxSpeed(){
    return halfMaxSpeed;
}


string Truck::getBrandName(){
    return brand;
}


string Truck::getMotorName(){
    return motor;
}


float Truck::getAngle(){
    return angleTurning;
}


float Truck::getTopSpeed(){
    return topSpeed;
}
