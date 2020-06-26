
#include "../include/Police.h"


Police::Police(){}


Police::Police(float maxSpeed, float speedMul, float accInc, float scaleX, float scaleY, int maxCounterToChange,
                       const string &vehicle, float pX, float pY, const string brandName, const float angle,
                       const string motorName) : Vehicle(maxSpeed / speedMul, scaleX, maxCounterToChange,
                                                 0.0f, pX, pY, pY, 0, 0, vehicle, Police_vehicle::PLAYER_TEXTURES, 1, 0),
                                                 speedMul(speedMul), maxAcc(pow(maxSpeed / speedMul, 2.0f)),
                                                 accInc(accInc), scaleY(scaleY), acceleration(0),
                                                 minCrashAcc(0), xDest(0), inertia(0), crashing(false),
                                                 smoking(false), skidding(false),
                                                 firstCrash(true), firstTurnLeft(true),
                                                 firstTurnRight(true)
{
    mode = -1;
    brand = brandName;
    motor = motorName;
    angleTurning = angle;
}

float Police::getPreviousY() const {
    return previousY;
}

void Police::hitControl(const bool vehicleCrash) {
    crashing = true;
    smoking = false;
    skidding = false;

    if (!vehicleCrash) {
        if (posX > angleTurning)
            posX -= angleTurning;
        else if (posX < -angleTurning)
            posX += angleTurning;
    } else {
        if (minCrashAcc <= 0.0f) { // Only first time
            minCrashAcc = (speed * 0.333f) * (speed * 0.333f); // In case of car crash, speed will be drop to 1/3. Otherwise it will be drop to 0.
            acceleration = (speed * 0.5f) * (speed * 0.5f); // At the moment of the crash, speed drops to 1/2.

            if (posX < 0.0f)
                xDest = 0.8f;
            else
                xDest = -0.8f;
        }

        if (posX > xDest)
            posX -= angleTurning;
        else if (posX < xDest)
            posX += angleTurning;

        if (posX > 0.8f)
            posX = 0.8f;
        else if (posX < -0.8f)
            posX = -0.8f;
    }

    acceleration -= accInc * 2.5f;
    if (speed > 1.333f * halfMaxSpeed) // Reduces hit time
        acceleration -= accInc * 7.5f;
    else if (speed > halfMaxSpeed)
        acceleration -= accInc * 5.0f;
    else if (speed > 0.5f * halfMaxSpeed)
        acceleration -= accInc * 2.5f;

    if (acceleration < 0.0f)
        acceleration = 0.0f;

    speed = sqrt(acceleration);

    previousY = posY;
    if (vehicleCrash && abs(posX) != 0.8f)
        posY -= speed / 2.0f;
    if (!vehicleCrash && (posX <= -angleTurning || posX >= angleTurning))
        posY -= speed / 6.0f;

    if (acceleration <= minCrashAcc ||
        current_code_image == 37 || current_code_image == 50)
    {
        acceleration = minCrashAcc;
        speed = sqrt(acceleration);
        crashing = false;
        minCrashAcc = 0.0f;
        xDest = 0.0f;
        inertia = 0;
        previousY = posY;
        mode = -1;
    }
}

bool Police::isCrashing() const {
    return crashing;
}

float Police::getRealSpeed() const {
    return speed * speedMul;
}

Vehicle::Action Police::accelerationControl(Configuration &c, bool hasGotOut) {
    Action a = NONE;
    smoking = false;
    float previousAcc = acceleration;

    if (Keyboard::isKeyPressed(c.brakeKey))
        a = BRAKE;

    if (a != BRAKE && Keyboard::isKeyPressed(c.accelerateKey)) {
        if (hasGotOut) {
            if (acceleration < maxAcc / 4.5f)
                acceleration += accInc / 3.0f;
            else
                acceleration -= accInc * 1.5f;
        } else {
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

Vehicle::Direction Police::rotationControl(Configuration &c, float curveCoefficient) {
    skidding = false;
    if (speed > 0.0f) {
        if (speed < 0.66f * maxSpeed)
            posX -= angleTurning * curveCoefficient * sqrt(speed / 2.0f) * speed / maxSpeed;
        else
            posX -= angleTurning * curveCoefficient * sqrt(speed) * speed / maxSpeed;

        if (abs(curveCoefficient) >= 0.33f && speed >= 0.66f * maxSpeed)
            skidding = true;

        if (Keyboard::isKeyPressed(c.leftKey)) {
            if (inertia > -Police_vehicle::FORCE_INERTIA)
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
            if (inertia < Police_vehicle::FORCE_INERTIA)
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

    return RIGHT;
}

void Police::draw(Configuration &c, SoundPlayer &r, const Action &a, const Direction &d,
                  const Elevation &e, bool enableSound)
{
    // Sound effects
    if (a != CRASH)
        firstCrash = true;

    if (enableSound) {
        if (speed > 0.0f) {
            if (a == BOOT) {
                // Acceleration sound
                r.soundEffects[12]->stop();
                r.soundEffects[12]->play();
            }
            if (r.soundEffects[35]->getStatus() != SoundSource::Playing) {
                // Siren sound
                r.soundEffects[35]->stop();
                r.soundEffects[35]->play();
            }
            if (r.soundEffects[6]->getStatus() != SoundSource::Playing) {
                // Engine sound
                r.soundEffects[6]->stop();
                r.soundEffects[6]->play();
            }
            r.soundEffects[6]->setVolume((33.0f + 67.0f * speed / maxSpeed) * float(r.volumeEffects) / 100.f);
            if (skidding && r.soundEffects[8]->getStatus() != SoundSource::Playing) {
                // Skidding sound
                r.soundEffects[8]->stop();
                r.soundEffects[8]->play();
            }
        }
        else {
            r.soundEffects[12]->stop();
            r.soundEffects[6]->stop();
            r.soundEffects[35]->stop();
            r.soundEffects[8]->stop();
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
        r.soundEffects[6]->stop();
        r.soundEffects[35]->stop();
        r.soundEffects[8]->stop();
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

            if (textures.size() == Police_vehicle::PLAYER_TEXTURES) {
                if (a == ACCELERATE || a == BOOT) {
                    if (e == FLAT) {
                        if (d == RIGHT) {
                            if (current_code_image < 1 || current_code_image > 4)
                                current_code_image = 1;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 5 || current_code_image > 8)
                                    current_code_image = 5;
                                if (current_code_image == 5)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 5 || current_code_image > 8)
                                    current_code_image = 5;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 9 || current_code_image > 12)
                                    current_code_image = 9;
                                if (current_code_image == 9)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 9 || current_code_image > 12)
                                    current_code_image = 9;
                            }
                        }
                    }
                     else if (e == UP) {
                        if (d == RIGHT) {
                            if (current_code_image < 1 || current_code_image > 4)
                                current_code_image = 1;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 5 || current_code_image > 8)
                                    current_code_image = 5;
                                if (current_code_image == 5)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 5 || current_code_image > 8)
                                    current_code_image = 5;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 9 || current_code_image > 12)
                                    current_code_image = 9;
                                if (current_code_image == 9)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 9 || current_code_image > 12)
                                    current_code_image = 9;
                            }
                        }
                    }
                    else { // Down
                        if (d == RIGHT) {
                            if (current_code_image < 1 || current_code_image > 4)
                                current_code_image = 1;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 5 || current_code_image > 8)
                                    current_code_image = 5;
                                if (current_code_image == 5)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 5 || current_code_image > 8)
                                    current_code_image = 5;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 9 || current_code_image > 12)
                                    current_code_image = 9;
                                if (current_code_image == 9)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 9 || current_code_image > 12)
                                    current_code_image = 9;
                            }
                        }
                    }
                } else if (a == BRAKE) {
                    if (e == FLAT) {
                        if (d == RIGHT) {
                            if (current_code_image < 13 || current_code_image > 16)
                                current_code_image = 13;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 17 || current_code_image > 20)
                                    current_code_image = 17;
                                if (current_code_image == 17)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 17 || current_code_image > 20)
                                    current_code_image = 17;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 21 || current_code_image > 24)
                                    current_code_image = 21;
                                if (current_code_image == 21)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 21 || current_code_image > 24)
                                    current_code_image = 21;
                            }
                        }
                    } else if (e == UP) {
                        if (d == RIGHT) {
                            if (current_code_image < 13 || current_code_image > 16)
                                current_code_image = 13;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 17 || current_code_image > 20)
                                    current_code_image = 17;
                                if (current_code_image == 17)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 17 || current_code_image > 20)
                                    current_code_image = 17;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 21 || current_code_image > 24)
                                    current_code_image = 21;
                                if (current_code_image == 21)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 21 || current_code_image > 24)
                                    current_code_image = 21;
                            }
                        }
                    } else { // Down
                        if (d == RIGHT) {
                            if (current_code_image < 13 || current_code_image > 16)
                                current_code_image = 13;
                        }
                        else if (d == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < 17 || current_code_image > 20)
                                    current_code_image = 17;
                                if (current_code_image == 17)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < 17 || current_code_image > 20)
                                    current_code_image = 17;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < 21 || current_code_image > 24)
                                    current_code_image = 21;
                                if (current_code_image == 21)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < 21 || current_code_image > 24)
                                    current_code_image = 21;
                            }
                        }
                    }
                }
                else {
                    // Crash
                    if (mode == 0) {
                        if (current_code_image < 25 || current_code_image > 37)
                            current_code_image = 25;
                    }
                    else if (mode == 1) {
                        if (current_code_image < 38 || current_code_image > 50)
                            current_code_image = 38;
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
    sprite.setPosition(minScreenX, ((float) c.w.getSize().y) * c.camD - sprite.getGlobalBounds().height / 2.0f);
    c.w.draw(sprite);


    if (smoking || skidding || crashing) {
        if (!crashing){
            maxCounterToChange = COUNTER + 4;
        }
        const float j = sprite.getPosition().y + sprite.getGlobalBounds().height;
        sprite.setTexture(textures[50 + current_code_image % 4], true);
        sprite.setScale(3.f * c.screenScale, 3.5f * c.screenScale);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f - sprite.getGlobalBounds().width,
                           j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
        sprite.setPosition(((float) c.w.getSize().x) / 2.0f, j - sprite.getGlobalBounds().height);
        c.w.draw(sprite);
    }
}

void Police::drawInitialAnimation(Configuration &c, float x, bool &end) {
    if (textures.size() == Police_vehicle::PLAYER_TEXTURES) {
        if (counter_code_image >= maxCounterToChange) {
            current_code_image++;
            counter_code_image = 0;
        }
        if (current_code_image < 132 || current_code_image > 135)
            current_code_image = 132;

        int index = 125;
        if (x < ((float) c.w.getSize().x) * 0.45f)
            index = 124;
        end = x < ((float) c.w.getSize().x) * 0.4f || x >= c.w.getSize().x;

        // Vehicle
        sprite.setTexture(textures[index], true);
        sprite.setScale(scale * c.screenScale, scaleY * c.screenScale);
        sprite.setPosition(x, ((float) c.w.getSize().y) * c.camD - sprite.getGlobalBounds().height / 2.0f);
        c.w.draw(sprite);

        // Smoke
        float i = x - sprite.getGlobalBounds().width / 3, j = sprite.getPosition().y + sprite.getGlobalBounds().height;
        while (i < (float) c.w.getSize().x) {
            index = current_code_image;
            sprite.setTexture(textures[index], true);
            sprite.setScale(4.0f * c.screenScale, 4.0f * c.screenScale);
            sprite.setPosition(i, j - sprite.getGlobalBounds().height);
            c.w.draw(sprite);

            i += sprite.getGlobalBounds().width;
        }

        if (end) {
            current_code_image = 0;
            counter_code_image = 0;
        } else {
            counter_code_image++;
        }
    }
}

void Police::drawGoalAnimation(Configuration &c, int &step, bool &end, bool smoke) {
    if (textures.size() == Police_vehicle::PLAYER_TEXTURES) {
        if (counter_code_image >= maxCounterToChange) {
            current_code_image++;
            counter_code_image = 0;
            step++;
        }
        if (current_code_image < 132 || current_code_image > 135)
            current_code_image = 132;

        int index = 126;
        if (step < 2)
            index = 124;
        else if (step < 4)
            index = 125;

        // Vehicle
        sprite.setTexture(textures[index], true);
        sprite.setScale(scale * c.screenScale, scaleY * c.screenScale);
        minScreenX = ((float) c.w.getSize().x) / 2.0f - sprite.getGlobalBounds().width / 2.0f;
        maxScreenX = minScreenX + sprite.getGlobalBounds().width;
        sprite.setPosition(minScreenX, ((float) c.w.getSize().y) * c.camD - sprite.getGlobalBounds().height / 2.0f);
        c.w.draw(sprite);

        // Smoke
        if (smoke) {
            float i = minScreenX - sprite.getGlobalBounds().width / 3, j =
                    sprite.getPosition().y + sprite.getGlobalBounds().height;
            while (i < (float) c.w.getSize().x) {
                index = current_code_image;
                sprite.setTexture(textures[index], true);
                sprite.setScale(4.0f * c.screenScale, 4.0f * c.screenScale);
                sprite.setPosition(i, j - sprite.getGlobalBounds().height);
                c.w.draw(sprite);

                i += sprite.getGlobalBounds().width;
            }
        }

        if (step >= 6)
            end = true;

        if (end) {
            current_code_image = 0;
            counter_code_image = 0;
        } else {
            counter_code_image++;
        }
    }
}

void Police::setSmoking(bool smoke) {
    smoking = smoke;
}



void Police::setModeCollision(){
    if (mode == -1){
        mode = rand_generator_int(0, 1);
    }
}


float Police::getHalfMaxSpeed(){
    return halfMaxSpeed;
}
