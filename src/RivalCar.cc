
#include "../include/RivalCar.h"

RivalCar::RivalCar(){}

RivalCar::RivalCar(int typeOfVehicle,float maxSpeed, float speedMul, float scale, int maxCounterToChange, const string &vehicle, float pX, float pY,
                   int totalTextures, int lowTextureRight, int highTextureRight, int lowTextureRightBrake, int highTextureRightBrake,
                   int lowTextureTurnleft, int highTextureTurnLeft, int lowTextureTurnLeftBrake, int highTextureTurnLeftBrake,
                   int lowTextureTurnRight, int highTextureTurnRight, int lowTextureTurnRightBrake, int highTextureTurnRightBrake,
                   int lowTextureUp, int highTextureUp, int lowTextureUpBrake, int highTextureUpBrake, int lowTextureTurnleftUp,
                   int highTextureTurnLeftUp, int lowTextureTurnLeftBrakeUp, int highTextureTurnLeftBrakeUp,  int lowTextureTurnRightUp,
                   int highTextureTurnRightUp, int lowTextureTurnRightBrakeUp, int highTextureTurnRightBrakeUp, int mediumTurnLeft,
                   int mediumTurnRight, int mediumTurnLeftUp, int mediumTurnRightUp, int mediumTurnLeftBrake, int mediumTurnRightBrake,
                   int mediumTurnLeftBrakeUp, int mediumTurnRightBrakeUp, float scaling) :
                    Vehicle(maxSpeed / speedMul, scale, maxCounterToChange, 0.f, pX, pX,
                    pY, pY, 0, 0, vehicle, totalTextures, 1, 0), oriX(this->posX),
                    currentDirection(RIGHT), calculatedPath(RIGHT), current_direction_counter(0), max_direction_counter(0),
                    probAI(0), typeAI(OBSTACLE)
{
    // Assignment of the attributes
    minTextureRightBrake = lowTextureRightBrake; maxTextureRightBrake = highTextureRightBrake; minTextureTurnLeft = lowTextureTurnleft;
    numTextures = totalTextures; minTextureRight = lowTextureRight; maxTextureRight = highTextureRight;
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
    angleTurning = 0.f;
    newPath = false;
    onStraight = true;
    crashing = false;
    vehicleType = typeOfVehicle;
    xDest = 1000;
    speedFactor = speedMul;
    shoutDone = false;
    smoking = false;
    firing = false;
    fireSmoking = false;
}



void RivalCar::hitControl(const bool vehicleCrash, SoundPlayer& r, float posPlayerY) {
    crashing = true;

    if (!shoutDone){
        shoutDone = true;

        if (vehicleType == 0){
            r.soundEffects[62]->stop();
            r.soundEffects[63]->stop();
            r.soundEffects[64]->stop();
            r.soundEffects[65]->stop();
            r.soundEffects[66]->stop();
            r.soundEffects[67]->stop();

            if (posPlayerY >= posY){
                // The rival car is behind
                int soundCode = rand_generator_int(62, 66);

                r.soundEffects[soundCode]->setVolume(int(posY / posPlayerY * 100.f));
                r.soundEffects[67]->setVolume(int(posY / posPlayerY * 100.f));

                r.soundEffects[soundCode]->play();
                r.soundEffects[67]->play();

            }
            else {
                // The player is behind
                int soundCode = rand_generator_int(62, 66);

                r.soundEffects[soundCode]->setVolume(int(posPlayerY / posY * 100.f));
                r.soundEffects[67]->setVolume(int(posPlayerY / posY * 100.f));

                r.soundEffects[soundCode]->play();
                r.soundEffects[67]->play();
            }
        }
        else {
            r.soundEffects[17]->stop();
            r.soundEffects[18]->stop();
            r.soundEffects[19]->stop();

            r.soundEffects[17]->play();

            if (posPlayerY >= posY){
                // The rival car is behind
                int soundCode = rand_generator_int(18, 19);

                r.soundEffects[soundCode]->setVolume(int(posY / posPlayerY * 100.f));
                r.soundEffects[17]->setVolume(int(posY / posPlayerY * 100.f));

                r.soundEffects[soundCode]->play();
                r.soundEffects[17]->play();

            }
            else {
                // The player is behind
                int soundCode = rand_generator_int(18, 19);

                r.soundEffects[soundCode]->setVolume(int(posPlayerY / posY * 100.f));
                r.soundEffects[17]->setVolume(int(posPlayerY / posY * 100.f));

                r.soundEffects[soundCode]->play();
                r.soundEffects[17]->play();
            }
        }
    }

    const float acc = getAcceleration();

    if (speedCollision == 0.f){
        speedCollision = getRealSpeed();
        if (speedCollision < 60.f)
            posY = posY + speed * 0.50f;
    }

    if (vehicleType == 0){
        mainMutex.lock();
        speed = sqrt(acc - ACCELERATION_INCREMENT);
        mainMutex.unlock();

        posY = posY + 0.1f;

        if (current_code_image == 58){
            crashing = false;
            xDest = 1000;
            previousY = posY;
            speedCollision = 0.0f;
            speed = 0.4f;
        }
    }
    else {
        if (xDest == 1000){
            xDest = posX;
        }

        if (xDest >= 0.f){
            posX -= 0.03f;
        }
        else {
            posX += 0.03f;
        }

        posY = posY - 0.04f;

        int maxCode = 0;

        switch(vehicleType){
            case 0:
                maxCode = 58;
                break;
            case 1:
                maxCode = 44;
                break;
            case 2:
                maxCode = 36;
                break;
            case 3:
                maxCode = 62;
        }

        if (current_code_image == maxCode){
            crashing = false;
            xDest = 1000;
            previousY = posY;
            speedCollision = 0.0f;
            shoutDone = false;
            speed = 0.4f;
        }
    }
}


bool RivalCar::isCrashing() const {
    return crashing;
}



float RivalCar::getRealSpeed() const {
    return speed * speedFactor;
}


void RivalCar::setSmoking(){
    smoking = true;
}


float RivalCar::getSmoking() const {
    return smoking;
}



void RivalCar::updateModeA(Configuration& c, float iniPos, float endPos, float maxAggressiveness, Action& a, float directionCurve,
                           const Difficult& difficulty, const float playerPosX, const float playerPosY, const float playerSpeed,
                           const bool vehicleDetected)
{
    // Store the current speed before updating
    lastSpeed = speed;
    currentDirection = RIGHT;

    // Check if the player is on curve
    if (directionCurve == 0.f){
        if (abs(playerPosY - posY) < 100.f && posY > 90.f){
            // AI
            if (typeAI == OBSTACLE) {
                const float acc = getAcceleration();
                if (abs(playerPosX - posX) > INCREMENT_X) { // Rotation control
                    // The vehicle is not in the player's path
                    if (speed < halfMaxSpeed){
                        speed = sqrt(acc + ACCELERATION_INCREMENT);
                    }

                    if (posX > playerPosX && posX > -0.9f) {
                        posX -= INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNLEFT;
                    }
                    else if (posX < 0.9f) {
                        posX += INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNRIGHT;
                    }
                }
                else { // Acceleration control
                    // The vehicle is in the player's path
                    if (posY <= playerPosY){
                        speed = sqrt(acc + ACCELERATION_INCREMENT);
                    }
                    else if (acc > ACCELERATION_INCREMENT){
                        speed = sqrt(acc - ACCELERATION_INCREMENT);
                    }
                    else {
                        speed = 0.0f;
                    }

                    currentDirection = RIGHT;
                }
            }
            else if (typeAI == EVASIVE) {
                if (playerPosX <= -0.5) {
                    float offsetX = INCREMENT_X * speed / maxSpeed;
                    if (posX + offsetX <= 0.7f){
                        posX += INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNRIGHT;
                    }
                    else {
                        currentDirection = RIGHT;
                    }
                }
                else if (playerPosX >= 0.5) {
                    float offsetX = INCREMENT_X * speed / maxSpeed;
                    if (posX + offsetX >= -0.7f){
                        posX -= INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNLEFT;
                    }
                    else {
                        currentDirection = RIGHT;
                    }
                }
                else {
                    if (posX > playerPosX) {
                        float offsetX = INCREMENT_X * speed / maxSpeed;
                        if (posX + offsetX <= 0.7f){
                            posX += INCREMENT_X * speed / maxSpeed;
                            currentDirection = TURNRIGHT;
                        }
                        else {
                            currentDirection = RIGHT;
                        }
                    }
                    else {
                        float offsetX = INCREMENT_X * speed / maxSpeed;
                        if (posX - offsetX >= -0.7f){
                            posX -= INCREMENT_X * speed / maxSpeed;
                            currentDirection = TURNLEFT;
                        }
                        else {
                            currentDirection = RIGHT;
                        }
                    }
                }
            }
            else if (typeAI == INCONSTANT) {
                if (currentDirection == TURNRIGHT) {
                    const float prevPosX = posX;
                    posX += INCREMENT_X * speed / maxSpeed;

                    if (posX >= 0.9f){
                        currentDirection = TURNLEFT;
                    }
                    else if (((prevPosX < -0.5f && posX >= -0.5f) || (prevPosX < 0.0f && posX >= 0.0f) ||
                              (prevPosX < 0.5f && posX >= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    {
                        currentDirection = TURNRIGHT; // Lane change
                    }
                }
                else if (currentDirection == TURNLEFT) {
                    const float prevPosX = posX;
                    posX -= INCREMENT_X * speed / maxSpeed;

                    if (posX <= -0.9f){
                        currentDirection = TURNRIGHT;
                    }
                    else if (((prevPosX > -0.5f && posX <= -0.5f) || (prevPosX > 0.0f && posX <= 0.0f) ||
                              (prevPosX > 0.5f && posX <= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    {
                        currentDirection = TURNLEFT; // Lane change
                    }
                }
                else {
                    if (rand_generator_zero_one() < 0.5f){
                        currentDirection = TURNRIGHT;
                    }
                    else {
                        currentDirection = TURNLEFT;
                    }
                }
            }
            else {
                // MANIAC
                if (vehicleDetected){
                    float p, cordX = 0.f;
                    // Check the difficulty to control the speed of changing
                    switch(c.level){
                        case EASY:
                            p = rand_generator_zero_one();
                            if (p <= 0.5f){
                                const float direction = rand_generator_zero_one();
                                if (direction <= 0.5){
                                    if (cordX < 0.f){
                                        cordX += 0.02f;
                                    }
                                    else {
                                        cordX -= 0.02f;
                                    }
                                }
                            }
                            break;
                        case NORMAL:
                            p = rand_generator_zero_one();
                            if (p <= 0.65f){
                                if (cordX < 0.f){
                                    cordX += 0.035f;
                                }
                                else {
                                    cordX -= 0.035f;
                                }
                            }
                            break;
                        case HARD:
                            p = rand_generator_zero_one();
                            if (p <= 0.8f){
                                if (cordX < 0.f){
                                    cordX += 0.05f;
                                }
                                else {
                                    cordX -= 0.05f;
                                }
                            }
                    }
                }
            }
        }
        else {
            if (posX > 0.f && !onStraight){
                posX -= rand_generator_float(0.03f, 0.06f);
                onStraight = true;
            }
            else if (posX < 0.f && !onStraight){
                posX += rand_generator_float(0.03f, 0.06f);
                onStraight = true;
            }

            if (counter_code_image < max_direction_counter){
                counter_code_image++;
            }
            else {
                currentDirection = randomDirection();
                counter_code_image = 0;
                max_direction_counter = rando_generator_zero_n(Vehicle_RivalCar::MAX_DIRECTION);
            }

            float newX = posX, offsetX;
            if (currentDirection == TURNRIGHT){
                offsetX = INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;
                if (newX + offsetX <= 0.7f){
                    newX += offsetX;
                }
            }
            else if (currentDirection == TURNLEFT){
                offsetX = INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;
                if (newX - offsetX >= -0.7f){
                    newX -= offsetX;
                }
            }

            if (newX < oriX - 0.35f || newX > oriX + 0.35f){
                currentDirection = RIGHT;
            }
            else {
                posX = newX;
            }
        }
    }
    else {
        onStraight = false;

        if (abs(playerPosY - posY) < 100.f && posY > 90.f){
            // AI
            if (typeAI == OBSTACLE) {
                const float acc = getAcceleration();
                if (abs(playerPosX - posX) > INCREMENT_X) { // Rotation control
                    // The vehicle is not in the player's path
                    if (posX > playerPosX && posX > -0.7f) {
                        posX -= INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNLEFT;
                    }
                    else if (posX < 0.7f) {
                        posX += INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNRIGHT;
                    }
                }
                else { // Acceleration control
                    // The vehicle is in the player's path
                    if (acc > ACCELERATION_INCREMENT){
                        speed = sqrt(acc - ACCELERATION_INCREMENT);
                    }
                    else {
                        speed = 0.0f;
                    }

                    currentDirection = RIGHT;
                }
            }
            else if (typeAI == EVASIVE) {
                if (playerPosX <= -0.5) {
                    float offsetX = INCREMENT_X * speed / maxSpeed;
                    if (posX + offsetX <= 0.7f){
                        posX += INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNRIGHT;
                    }
                    else {
                        if (directionCurve > 0.f){
                            currentDirection = TURNRIGHT;
                        }
                        else {
                            currentDirection = TURNLEFT;
                        }
                    }
                }
                else if (playerPosX >= 0.5) {
                    float offsetX = INCREMENT_X * speed / maxSpeed;
                    if (posX - offsetX >= -0.7f){
                        posX -= INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNLEFT;
                    }
                    else {
                        if (directionCurve > 0.f){
                            currentDirection = TURNRIGHT;
                        }
                        else {
                            currentDirection = TURNLEFT;
                        }
                    }
                }
                else {
                    if (posX > playerPosX) {
                        float offsetX = INCREMENT_X * speed / maxSpeed;
                        if (posX + offsetX <= 0.7f){
                            posX += INCREMENT_X * speed / maxSpeed;
                            currentDirection = TURNRIGHT;
                        }
                        else {
                            if (directionCurve > 0.f){
                                currentDirection = TURNRIGHT;
                            }
                            else {
                                currentDirection = TURNLEFT;
                            }
                        }
                    }
                    else {
                        float offsetX = INCREMENT_X * speed / maxSpeed;
                        if (posX - offsetX >= -0.7f){
                            posX -= INCREMENT_X * speed / maxSpeed;
                            currentDirection = TURNLEFT;
                        }
                        else {
                            if (directionCurve > 0.f){
                                currentDirection = TURNRIGHT;
                            }
                            else {
                                currentDirection = TURNLEFT;
                            }
                        }
                    }
                }
            }
            else if (typeAI == INCONSTANT){
                if (currentDirection == TURNRIGHT) {
                    const float prevPosX = posX;
                    posX += INCREMENT_X * speed / maxSpeed;

                    if (posX >= 0.7f){
                        currentDirection = TURNLEFT;
                    }
                    else if (((prevPosX < -0.5f && posX >= -0.5f) || (prevPosX < 0.0f && posX >= 0.0f) ||
                              (prevPosX < 0.5f && posX >= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    {
                        currentDirection = TURNRIGHT; // Lane change
                    }
                }
                else if (currentDirection == TURNLEFT) {
                    const float prevPosX = posX;
                    posX -= INCREMENT_X * speed / maxSpeed;

                    if (posX <= -0.7f){
                        currentDirection = TURNRIGHT;
                    }
                    else if (((prevPosX > -0.5f && posX <= -0.5f) || (prevPosX > 0.0f && posX <= 0.0f) ||
                              (prevPosX > 0.5f && posX <= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    {
                        currentDirection = TURNLEFT; // Lane change
                    }
                }
                else {
                    if (rand_generator_zero_one() <= 0.333f){
                        currentDirection = TURNRIGHT;
                    }
                    else if (rand_generator_zero_one() <= 0.666f){
                        currentDirection = TURNLEFT;
                    }
                    else {
                        currentDirection = RIGHT;
                    }
                }
            }
            else {
                // MANIAC
                if (vehicleDetected){
                    float p;
                    // Check the difficulty to control the speed of changing
                    switch(c.level){
                        case EASY:
                            p = rand_generator_zero_one();
                            if (p <= 0.5f){
                                const float direction = rand_generator_zero_one();
                                if (direction <= 0.5){
                                    if (posX < 0.f){
                                        posX += 0.01f;
                                    }
                                    else {
                                        posX -= 0.01f;
                                    }
                                }
                            }
                            break;
                        case NORMAL:
                            p = rand_generator_zero_one();
                            if (p <= 0.65f){
                                if (posX < 0.f){
                                    posX += 0.015f;
                                }
                                else {
                                    posX -= 0.015f;
                                }
                            }
                            break;
                        case HARD:
                            p = rand_generator_zero_one();
                            if (p <= 0.8f){
                                if (posX < 0.f){
                                    posX += 0.02f;
                                }
                                else {
                                    posX -= 0.02f;
                                }
                            }
                    }
                }
            }
        }
        else {
            // Set and angle of turn for the curve
            if (abs(posX >= 0.f) && abs(posX) <= 0.3f){
                angleTurning = rand_generator_float(0.007f, 0.01f);
            }
            else if (abs(posX > 0.3f) && abs(posX) <= 0.7f){
                angleTurning = rand_generator_float(0.003f, 0.007f);
            }
            else {
                angleTurning = rand_generator_float(0.001f, 0.003f);
            }

            if (directionCurve > 0.f){
                currentDirection = TURNRIGHT;
            }
            else {
                currentDirection = TURNLEFT;
            }
            if (currentDirection == TURNRIGHT){
                if (abs(posX) + angleTurning < 0.7f){
                    posX += angleTurning;
                }
            }
            else if (currentDirection == TURNLEFT){
                if (abs(posX) + angleTurning < 0.7f){
                    posX -= angleTurning;
                }
            }
        }
    }

    // Update the speed of the vehicle
    const float acc = getAcceleration();

    // At the beginning all accelerate the same
    if (posY <= 90.f || speed <= 0.8f){
        // Increment speed of the rival car
        speed = sqrt(acc + ACCELERATION_INCREMENT);
        a = BOOT;
        smoking = true;
    }
    else {
        smoking = false;
        a = BOOT;
        // Avoid to reach impossible speeds only a 20 percent superior
        if (posY - playerPosY >= c.renderLen){
            // Each vehicle accelerates in a different mode
            if (speed <= 2.0f){
                speed = sqrt(acc + rand_generator_float(0.01f, 0.05f));
                if (speed < 2.0f){
                    speed = 2.0f;
                }
            }
            a = ACCELERATE;
        }
        // Avoid to reach impossible speeds only a 20 percent superior
        else if (posY - playerPosY > 0.f){
            // Each vehicle accelerates in a different mode
            float p = rand_generator_zero_one();
            if (p > 0.7f){
                if (playerSpeed < 1.9f){
                    if (speed <= 1.9f){
                        speed = sqrt(acc + rand_generator_float(0.01f, 0.03f)) * rand_generator_float(1.0f, 1.1f);
                        if (speed < 1.9f){
                            speed = 1.9f;
                        }
                    }
                }
                else {
                    if (speed <= 1.8f){
                        speed = sqrt(acc + rand_generator_float(0.01f, 0.03f)) * rand_generator_float(1.0f, 1.1f);
                        if (speed < 1.8f){
                            speed = 1.8f;
                        }
                    }
                }
            }
            a = ACCELERATE;
        }
        else if (playerPosY - posY < 70.f) {
            // Each vehicle accelerates in a different mode
            if (speed > 2.1f){
                speed = sqrt(acc + rand_generator_float(0.01f, 0.05f));
                if (speed > 2.1f){
                    speed = 2.1f;
                }
            }
            a = ACCELERATE;
        }
        else {
            // Each vehicle accelerates in a different mode
            float p = rand_generator_zero_one();
            if (p < 0.8f){
                    if (speed > 2.5f){
                    speed = sqrt(acc + rand_generator_float(0.01f, 0.05f));
                    if (speed > 2.5f){
                        speed = 2.5f;
                    }
                }
            }
            else {
                speed = lastSpeed;
            }
            a = ACCELERATE;
        }
        if (directionCurve != 0.f){
            if (posY > playerPosY){
                float powerBraking, power;
                float option = rand_generator_int(0, 2);
                if (abs(directionCurve) >= 1.2f && abs(directionCurve) <= 1.9f){
                    if (option == 1 && acc > 0.f){
                        powerBraking = rand_generator_float(0.001f, 0.01f);
                        if (speed >= 1.5f){
                            speed = sqrt(acc - powerBraking);
                            if (!fireSmoking && !firing){
                                smoking = true;
                            }
                        }
                        else {
                            speed = 1.5f;
                            smoking = false;
                        }
                    }
                }
                else if (abs(directionCurve) >= 0.8f && abs(directionCurve) < 1.2f){
                    if (option == 1 && acc > 0.f){
                        powerBraking = rand_generator_float(0.001f, 0.01f);
                        if (speed >= 1.6f){
                            speed = sqrt(acc - powerBraking);
                            if (!fireSmoking && !firing){
                                smoking = true;
                            }
                        }
                        else {
                            speed = 1.6f;
                            smoking = false;
                        }
                    }
                    else if (option == 2){
                        power = rand_generator_float(0.001f, 0.01f);
                        if (speed <= 1.7f){
                            speed = sqrt(acc + power);
                        }
                        else {
                            speed = 1.7f;
                        }
                    }
                }
                else if (abs(directionCurve) >= 0.3f && abs(directionCurve) < 0.8f){
                    if (option == 1 && acc > 0.f){
                        powerBraking = rand_generator_float(0.001f, 0.01f);
                        if (speed >= 1.7f){
                            speed = sqrt(acc - powerBraking);
                            if (!fireSmoking && !firing){
                                smoking = true;
                            }
                        }
                        else {
                            speed = 1.7f;
                            smoking = false;
                        }
                    }
                    else if (option == 2){
                        power = rand_generator_float(0.001f, 0.01f);
                        if (speed <= 1.8f){
                            speed = sqrt(acc + power);
                        }
                        else {
                            speed = 1.8f;
                        }
                    }
                }
            }
            a = BRAKE;
        }
    }
    // Advance the vehicle
    previousY = posY;
    posY += speed;
}



void RivalCar::updateModeB(Configuration& c, float iniPos, float endPos, float maxAggressiveness, Action& a, float directionCurve,
                           const Difficult& difficulty, const float playerPosX, const float playerPosY, const float playerSpeed,
                           const bool vehicleDetected)
{
   // Store the current speed before updating
    lastSpeed = speed;
    currentDirection = RIGHT;

    // Check if the player is on curve
    if (directionCurve == 0.f){
        if (abs(playerPosY - posY) < 100.f && posY > 90.f){
            // AI
            if (typeAI == OBSTACLE) {
                const float acc = getAcceleration();
                if (abs(playerPosX - posX) > INCREMENT_X) { // Rotation control
                    // The vehicle is not in the player's path
                    if (speed < halfMaxSpeed){
                        speed = sqrt(acc + ACCELERATION_INCREMENT);
                    }

                    if (posX > playerPosX && posX > -0.9f) {
                        posX -= INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNLEFT;
                    }
                    else if (posX < 0.9f) {
                        posX += INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNRIGHT;
                    }
                }
                else { // Acceleration control
                    // The vehicle is in the player's path
                    if (posY <= playerPosY){
                        speed = sqrt(acc + ACCELERATION_INCREMENT);
                    }
                    else if (acc > ACCELERATION_INCREMENT){
                        speed = sqrt(acc - ACCELERATION_INCREMENT);
                    }
                    else {
                        speed = 0.f;
                    }

                    currentDirection = RIGHT;
                }
            }
            else if (typeAI == EVASIVE) {
                if (playerPosX <= -0.5) {
                    float offsetX = INCREMENT_X * speed / maxSpeed;
                    if (posX + offsetX <= 0.7f){
                        posX += INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNRIGHT;
                    }
                    else {
                        currentDirection = RIGHT;
                    }
                }
                else if (playerPosX >= 0.5) {
                    float offsetX = INCREMENT_X * speed / maxSpeed;
                    if (posX + offsetX >= -0.7f){
                        posX -= INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNLEFT;
                    }
                    else {
                        currentDirection = RIGHT;
                    }
                }
                else {
                    if (posX > playerPosX) {
                        float offsetX = INCREMENT_X * speed / maxSpeed;
                        if (posX + offsetX <= 0.7f){
                            posX += INCREMENT_X * speed / maxSpeed;
                            currentDirection = TURNRIGHT;
                        }
                        else {
                            currentDirection = RIGHT;
                        }
                    }
                    else {
                        float offsetX = INCREMENT_X * speed / maxSpeed;
                        if (posX - offsetX >= -0.7f){
                            posX -= INCREMENT_X * speed / maxSpeed;
                            currentDirection = TURNLEFT;
                        }
                        else {
                            currentDirection = RIGHT;
                        }
                    }
                }
            }
            else if (typeAI == INCONSTANT) {
                if (currentDirection == TURNRIGHT) {
                    const float prevPosX = posX;
                    posX += INCREMENT_X * speed / maxSpeed;

                    if (posX >= 0.9f){
                        currentDirection = TURNLEFT;
                    }
                    else if (((prevPosX < -0.5f && posX >= -0.5f) || (prevPosX < 0.0f && posX >= 0.0f) ||
                              (prevPosX < 0.5f && posX >= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    {
                        currentDirection = TURNRIGHT; // Lane change
                    }
                }
                else if (currentDirection == TURNLEFT) {
                    const float prevPosX = posX;
                    posX -= INCREMENT_X * speed / maxSpeed;

                    if (posX <= -0.9f){
                        currentDirection = TURNRIGHT;
                    }
                    else if (((prevPosX > -0.5f && posX <= -0.5f) || (prevPosX > 0.0f && posX <= 0.0f) ||
                              (prevPosX > 0.5f && posX <= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    {
                        currentDirection = TURNLEFT; // Lane change
                    }
                }
                else {
                    if (rand_generator_zero_one() < 0.5f){
                        currentDirection = TURNRIGHT;
                    }
                    else {
                        currentDirection = TURNLEFT;
                    }
                }
            }
            else {
                // MANIAC
                if (vehicleDetected){
                    float p;
                    // Check the difficulty to control the speed of changing
                    switch(c.level){
                        case EASY:
                            p = rand_generator_zero_one();
                            if (p <= 0.5f){
                                const float direction = rand_generator_zero_one();
                                if (direction <= 0.5){
                                    if (posX < 0.f){
                                        posX += 0.02f;
                                    }
                                    else {
                                        posX -= 0.02f;
                                    }
                                }
                            }
                            break;
                        case NORMAL:
                            p = rand_generator_zero_one();
                            if (p <= 0.65f){
                                if (posX < 0.f){
                                    posX += 0.035f;
                                }
                                else {
                                    posX -= 0.035f;
                                }
                            }
                            break;
                        case HARD:
                            p = rand_generator_zero_one();
                            if (p <= 0.8f){
                                if (posX < 0.f){
                                    posX += 0.05f;
                                }
                                else {
                                    posX -= 0.05f;
                                }
                            }
                    }
                }
                else {
                    if (current_direction_counter < max_direction_counter) {
                        current_direction_counter++;
                    }
                     else {
                        max_direction_counter = rando_generator_zero_n(Vehicle_RivalCar::MAX_DIRECTION);
                        current_direction_counter = 0;
                        calculatedPath = randomDirection();
                    }

                    float newX = posX;
                    if (calculatedPath == TURNRIGHT)
                        newX += INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;
                    else if (calculatedPath == TURNLEFT)
                        newX -= INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;

                    if (newX < oriX - 0.15f || newX > oriX + 0.15f){
                        calculatedPath = RIGHT;
                    }
                    else {
                        posX = newX;
                    }
                    currentDirection = calculatedPath;
                }
            }
        }
        else {
            if (posX > 0.f && !onStraight){
                posX -= rand_generator_float(0.03f, 0.06f);
                onStraight = true;
            }
            else if (posX < 0.f && !onStraight){
                posX += rand_generator_float(0.03f, 0.06f);
                onStraight = true;
            }

            if (counter_code_image < max_direction_counter){
                counter_code_image++;
            }
            else {
                currentDirection = randomDirection();
                counter_code_image = 0;
                max_direction_counter = rando_generator_zero_n(Vehicle_RivalCar::MAX_DIRECTION);
            }

            float newX = posX, offsetX;
            if (currentDirection == TURNRIGHT){
                offsetX = INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;
                if (newX + offsetX <= 0.7f){
                    newX += offsetX;
                }
            }
            else if (currentDirection == TURNLEFT){
                offsetX = INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;
                if (newX - offsetX >= -0.7f){
                    newX -= offsetX;
                }
            }

            if (newX < oriX - 0.35f || newX > oriX + 0.35f){
                currentDirection = RIGHT;
            }
            else {
                posX = newX;
            }
        }
    }
    else {
        onStraight = false;
        if (abs(playerPosY - posY) < 100.f && posY > 90.f){
            // AI
            if (typeAI == OBSTACLE) {
                const float acc = getAcceleration();
                if (abs(playerPosX - posX) > INCREMENT_X) { // Rotation control
                    // The vehicle is not in the player's path
                    if (posX > playerPosX && posX > -0.7f) {
                        posX -= INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNLEFT;
                    }
                    else if (posX < 0.7f) {
                        posX += INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNRIGHT;
                    }
                }
                else { // Acceleration control
                    // The vehicle is in the player's path
                    if (acc > ACCELERATION_INCREMENT){
                        speed = sqrt(acc - ACCELERATION_INCREMENT);
                    }
                    else {
                        speed = 0.0f;
                    }

                    currentDirection = RIGHT;
                }
            }
            else if (typeAI == EVASIVE) {
                if (playerPosX <= -0.5) {
                    float offsetX = INCREMENT_X * speed / maxSpeed;
                    if (posX + offsetX <= 0.7f){
                        posX += INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNRIGHT;
                    }
                    else {
                        if (directionCurve > 0.f){
                            currentDirection = TURNRIGHT;
                        }
                        else {
                            currentDirection = TURNLEFT;
                        }
                    }
                }
                else if (playerPosX >= 0.5) {
                    float offsetX = INCREMENT_X * speed / maxSpeed;
                    if (posX - offsetX >= -0.7f){
                        posX -= INCREMENT_X * speed / maxSpeed;
                        currentDirection = TURNLEFT;
                    }
                    else {
                        if (directionCurve > 0.f){
                            currentDirection = TURNRIGHT;
                        }
                        else {
                            currentDirection = TURNLEFT;
                        }
                    }
                }
                else {
                    if (posX > playerPosX) {
                        float offsetX = INCREMENT_X * speed / maxSpeed;
                        if (posX + offsetX <= 0.7f){
                            posX += INCREMENT_X * speed / maxSpeed;
                            currentDirection = TURNRIGHT;
                        }
                        else {
                            if (directionCurve > 0.f){
                                currentDirection = TURNRIGHT;
                            }
                            else {
                                currentDirection = TURNLEFT;
                            }
                        }
                    }
                    else {
                        float offsetX = INCREMENT_X * speed / maxSpeed;
                        if (posX - offsetX >= -0.7f){
                            posX -= INCREMENT_X * speed / maxSpeed;
                            currentDirection = TURNLEFT;
                        }
                        else {
                            if (directionCurve > 0.f){
                                currentDirection = TURNRIGHT;
                            }
                            else {
                                currentDirection = TURNLEFT;
                            }
                        }
                    }
                }
            }
            else if (typeAI == INCONSTANT){
                if (currentDirection == TURNRIGHT) {
                    const float prevPosX = posX;
                    posX += INCREMENT_X * speed / maxSpeed;

                    if (posX >= 0.7f){
                        currentDirection = TURNLEFT;
                    }
                    else if (((prevPosX < -0.5f && posX >= -0.5f) || (prevPosX < 0.0f && posX >= 0.0f) ||
                              (prevPosX < 0.5f && posX >= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    {
                        currentDirection = TURNRIGHT; // Lane change
                    }
                }
                else if (currentDirection == TURNLEFT) {
                    const float prevPosX = posX;
                    posX -= INCREMENT_X * speed / maxSpeed;

                    if (posX <= -0.7f){
                        currentDirection = TURNRIGHT;
                    }
                    else if (((prevPosX > -0.5f && posX <= -0.5f) || (prevPosX > 0.0f && posX <= 0.0f) ||
                              (prevPosX > 0.5f && posX <= 0.5f)) && (rand_generator_zero_one() < 0.5f))
                    {
                        currentDirection = TURNLEFT; // Lane change
                    }
                }
                else {
                    if (rand_generator_zero_one() <= 0.333f){
                        currentDirection = TURNRIGHT;
                    }
                    else if (rand_generator_zero_one() <= 0.666f){
                        currentDirection = TURNLEFT;
                    }
                    else {
                        currentDirection = RIGHT;
                    }
                }
            }
            else {
                // MANIAC
                if (vehicleDetected){
                    float p;
                    // Check the difficulty to control the speed of changing
                    switch(c.level){
                        case EASY:
                            p = rand_generator_zero_one();
                            if (p <= 0.5f){
                                const float direction = rand_generator_zero_one();
                                if (direction <= 0.5){
                                    if (posX < 0.f){
                                        posX += 0.01f;
                                    }
                                    else {
                                        posX -= 0.01f;
                                    }
                                }
                            }
                            break;
                        case NORMAL:
                            p = rand_generator_zero_one();
                            if (p <= 0.65f){
                                if (posX < 0.f){
                                    posX += 0.015f;
                                }
                                else {
                                    posX -= 0.015f;
                                }
                            }
                            break;
                        case HARD:
                            p = rand_generator_zero_one();
                            if (p <= 0.8f){
                                if (posX < 0.f){
                                    posX += 0.02f;
                                }
                                else {
                                    posX -= 0.02f;
                                }
                            }
                    }
                }
                else{
                    if (current_direction_counter < max_direction_counter) {
                        current_direction_counter++;
                    }
                     else {
                        max_direction_counter = rando_generator_zero_n(Vehicle_RivalCar::MAX_DIRECTION);
                        current_direction_counter = 0;
                        calculatedPath = randomDirection();
                    }

                    float newX = posX;
                    if (calculatedPath == TURNRIGHT)
                        newX += INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;
                    else if (calculatedPath == TURNLEFT)
                        newX -= INCREMENT_X * rand_generator_zero_one() * speed / maxSpeed;

                    if (newX < oriX - 0.15f || newX > oriX + 0.15f){
                        calculatedPath = RIGHT;
                    }
                    else {
                        posX = newX;
                    }
                    currentDirection = calculatedPath;
                }
            }
        }
        else {
            // Set and angle of turn for the curve
            if (abs(posX >= 0.f) && abs(posX) <= 0.3f){
                angleTurning = rand_generator_float(0.007f, 0.01f);
            }
            else if (abs(posX > 0.3f) && abs(posX) <= 0.7f){
                angleTurning = rand_generator_float(0.003f, 0.007f);
            }
            else {
                angleTurning = rand_generator_float(0.001f, 0.003f);
            }

            if (directionCurve > 0.f){
                currentDirection = TURNRIGHT;
            }
            else {
                currentDirection = TURNLEFT;
            }
            if (currentDirection == TURNRIGHT){
                if (abs(posX) + angleTurning < 0.7f){
                    posX += angleTurning;
                }
            }
            else if (currentDirection == TURNLEFT){
                if (abs(posX) + angleTurning < 0.7f){
                    posX -= angleTurning;
                }
            }
        }
    }

    // Update the speed of the vehicle
    const float acc = getAcceleration();

    // At the beginning all accelerate the same
    if (posY <= 90.f){
        // Increment speed of the rival car
        speed = sqrt(acc + ACCELERATION_INCREMENT);
        a = BOOT;
        smoking = true;
    }
    else {
        smoking = false;
        a = BOOT;
        // Avoid to reach impossible speeds only a 20 percent superior
        if (posY - playerPosY >= c.renderLen){
            // Each vehicle accelerates in a different mode
            if (speed <= 1.8f){
                speed = sqrt(acc + rand_generator_float(0.01f, 0.05f));
                if (speed < 1.8f){
                    speed = 1.8f;
                }
            }
            a = ACCELERATE;
        }
        // Avoid to reach impossible speeds only a 20 percent superior
        else if (posY - playerPosY > 0.f){
            // Each vehicle accelerates in a different mode
            float p = rand_generator_zero_one();
            if (p > 0.7f){
                if (playerSpeed < 1.6f){
                    if (speed <= 1.6f){
                        speed = sqrt(acc + rand_generator_float(0.01f, 0.03f)) * rand_generator_float(1.0f, 1.1f);
                        if (speed < 1.6f){
                            speed = 1.6f;
                        }
                    }
                }
                else {
                    if (speed <= 1.8f){
                        speed = sqrt(acc + rand_generator_float(0.01f, 0.03f)) * rand_generator_float(1.0f, 1.1f);
                        if (speed < 1.8f){
                            speed = 1.8f;
                        }
                    }
                }
            }
            a = ACCELERATE;
        }
        else if (playerPosY - posY < 100.f) {
            // Each vehicle accelerates in a different mode
            if (speed > 1.9f){
                speed = sqrt(acc + rand_generator_float(0.01f, 0.05f));
                if (speed > 1.9f){
                    speed = 1.9f;
                }
            }
            a = ACCELERATE;
        }
        else {
            // Each vehicle accelerates in a different mode
            float p = rand_generator_zero_one();
            if (p < 0.8f){
                    if (speed > 1.9f){
                    speed = sqrt(acc + rand_generator_float(0.01f, 0.05f));
                    if (speed > 1.9f){
                        speed = 1.9f;
                    }
                }
            }
            else {
                speed = lastSpeed;
            }
            a = ACCELERATE;
        }
        if (directionCurve != 0.f){
            if (posY > playerPosY){
                float powerBraking, power;
                int option = rand_generator_int(0, 2);
                if (abs(directionCurve) >= 1.2f && abs(directionCurve) <= 1.9f){
                    if (option == 1 && acc > 0.f){
                        powerBraking = rand_generator_float(0.001f, 0.01f);
                        if (speed >= 1.4f){
                            speed = sqrt(acc - powerBraking);
                            if (!fireSmoking && !firing){
                                smoking = true;
                            }
                        }
                        else {
                            speed = 1.4f;
                            smoking = false;
                        }
                    }
                }
                else if (abs(directionCurve) >= 0.8f && abs(directionCurve) < 1.2f){
                    if (option == 1 && acc > 0.f){
                        powerBraking = rand_generator_float(0.001f, 0.01f);
                        if (speed >= 1.5f){
                            speed = sqrt(acc - powerBraking);
                            if (!fireSmoking && !firing){
                                smoking = true;
                            }
                        }
                        else {
                            speed = 1.5f;
                            smoking = false;
                        }
                    }
                    else if (option == 2){
                        power = rand_generator_float(0.001f, 0.01f);
                        if (speed <= 1.6f){
                            speed = sqrt(acc + power);
                        }
                        else {
                            speed = 1.6f;
                        }
                    }
                }
                else if (abs(directionCurve) >= 0.3f && abs(directionCurve) < 0.8f){
                    if (option == 1 && acc > 0.f){
                        powerBraking = rand_generator_float(0.001f, 0.01f);
                        if (speed >= 1.7f){
                            speed = sqrt(acc - powerBraking);
                            if (!fireSmoking && !firing){
                                smoking = true;
                            }
                        }
                        else {
                            speed = 1.7f;
                            smoking = false;
                        }
                    }
                    else if (option == 2){
                        power = rand_generator_float(0.001f, 0.01f);
                        if (speed <= 1.8f){
                            speed = sqrt(acc + power);
                        }
                        else {
                            speed = 1.8f;
                        }
                    }
                }
            }
            a = BRAKE;
        }
    }
    // Advance the vehicle
    previousY = posY;
    posY += speed;
}



void RivalCar::setAI(float maxAggressiveness, const Difficult& difficulty, const int typeOfGame) {
    if (maxAggressiveness == 0.0f){
        probAI = 0.0f;
    }
    else {
        probAI = rand_generator_float(0.f, maxAggressiveness);
    }

    if (typeOfGame == 3){
        typeAI = MANIAC;
    }
    else {
        const float p = rand_generator_zero_one();
        switch(difficulty){
        case EASY:
            if (p < 0.4f) {
                typeAI = OBSTACLE;
            }
            else {
                typeAI = EVASIVE;
            }
            break;
        case NORMAL:
            if (p < 0.5f) {
                typeAI = OBSTACLE;
            }
            else {
                typeAI = EVASIVE;
            }
            break;
        case HARD:
            if (p < 0.7f) {
                typeAI = OBSTACLE;
                probAI *= 2.0f;
            }
            else {
                typeAI = EVASIVE;
            }
        }
    }
}



void RivalCar::draw(const Action &a, const Elevation &e) {

    if (smoking){
        maxCounterToChange = COUNTER + 1;
    }
    else {
        maxCounterToChange = COUNTER;
    }

    // Draw
    if (currentDirection != TURNLEFT){
        firstTurnLeft = true;
    }
    if (currentDirection != TURNRIGHT){
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
                        if (currentDirection == RIGHT) {
                            if (current_code_image < minTextureRight || current_code_image > maxTextureRight)
                                current_code_image = minTextureRight;
                        }
                        else if (currentDirection == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnLeft || current_code_image > maxTextureTurnLeft)
                                    current_code_image = minTextureTurnLeft;
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
                        if (currentDirection == RIGHT) {
                            if (current_code_image < minTextureUp || current_code_image > maxTextureUp)
                                current_code_image = minTextureUp;
                        }
                        else if (currentDirection == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnLeftUp || current_code_image > maxTextureTurnLeftUp)
                                    current_code_image = minTextureTurnLeftUp;
                                if (current_code_image == medTurnLeftUp)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < medTurnLeftUp || current_code_image > minTextureTurnLeftUp)
                                    current_code_image = medTurnLeftUp;
                            }
                        }
                        else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < minTextureTurnRightUp || current_code_image > maxTextureTurnRightUp)
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
                        if (currentDirection == RIGHT) {
                            if (current_code_image < minTextureRight || current_code_image > maxTextureRight)
                                current_code_image = minTextureRight;
                        }
                        else if (currentDirection == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnLeft || current_code_image > maxTextureTurnLeft)
                                    current_code_image = minTextureTurnLeft;
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
                        if (currentDirection == RIGHT) {
                            if (current_code_image < minTextureRightBrake || current_code_image > maxTextureRightBrake)
                                current_code_image = minTextureRightBrake;
                        }
                        else if (currentDirection == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnLeftBrake || current_code_image > maxTextureTurnLeftBrake)
                                    current_code_image = minTextureTurnLeftBrake;
                                if (current_code_image == medTurnLeftBrake)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < medTurnLeftBrake || current_code_image > maxTextureTurnLeftBrake)
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
                        if (currentDirection == RIGHT) {
                            if (current_code_image < minTextureUpBrake || current_code_image > maxTextureUpBrake)
                                current_code_image = minTextureUpBrake;
                        } else if (currentDirection == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnLeftBrakeUp || current_code_image > maxTextureTurnLeftBrakeUp)
                                    current_code_image = minTextureTurnLeftBrakeUp;
                                if (current_code_image == medTurnLeftBrakeUp)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < medTurnLeftBrakeUp || current_code_image > maxTextureTurnLeftBrakeUp)
                                    current_code_image = medTurnLeftBrakeUp;
                            }
                        } else { // Turn right
                            if (firstTurnRight) {
                                if (current_code_image < minTextureTurnRightBrakeUp || current_code_image > maxTextureTurnRightBrakeUp)
                                    current_code_image = minTextureTurnRightBrakeUp;
                                if (current_code_image == medTurnRightBrakeUp)
                                    firstTurnRight = false;
                            } else {
                                if (current_code_image < medTurnRightBrakeUp || current_code_image > maxTextureTurnRightBrakeUp)
                                    current_code_image = medTurnRightBrakeUp;
                            }
                        }
                    } else { // Down
                        if (currentDirection == RIGHT) {
                            if (current_code_image < minTextureRightBrake || current_code_image > maxTextureRightBrake)
                                current_code_image = minTextureRightBrake;
                        } else if (currentDirection == TURNLEFT) {
                            if (firstTurnLeft) {
                                if (current_code_image < minTextureTurnLeftBrake || current_code_image > maxTextureTurnLeftBrake)
                                    current_code_image = minTextureTurnLeftBrake;
                                if (current_code_image == medTurnLeftBrake)
                                    firstTurnLeft = false;
                            } else {
                                if (current_code_image < medTurnLeftBrake || current_code_image > maxTextureTurnLeftBrake)
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
                else {
                    switch(vehicleType){
                        case 0:
                            if (current_code_image < 46 || current_code_image > 58)
                                current_code_image = 46;
                            break;
                        case 1:
                            if (current_code_image < 37 || current_code_image > 44)
                                current_code_image = 37;
                            break;
                        case 2:
                            if (current_code_image < 29 || current_code_image > 36)
                                current_code_image = 29;
                            break;
                        case 3:
                            if (current_code_image < 55 || current_code_image > 62)
                                current_code_image = 55;
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



float RivalCar::getPreviousY() const {
    return previousY;
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



void RivalCar::setOnStraight(){
    onStraight = true;
}



void RivalCar::drawSmokingPlayer(Configuration& c, const float destW, const float destH, const float widthOri, const float heightOri,
                                 const float maxY)
{
    Sprite sv;
    switch(vehicleType){
        case 0:
            sv.setTexture(textures[41 + current_code_image % 4], true);
            break;
        case 1:
            sv.setTexture(textures[52 + current_code_image % 4], true);
            break;
        case 2:
            sv.setTexture(textures[44 + current_code_image % 4], true);
            break;
        case 3:
            sv.setTexture(textures[70 + current_code_image % 4], true);
    }

    sv.setScale(destW / widthOri, destH / heightOri);
    sv.setPosition(minScreenX - 5.f, maxY);
    c.w.draw(sv);
}



void RivalCar::drawFirePlayer(Configuration& c, const float destW, const float destH, const float widthOri,
                              const float heightOri, const float maxY)
{
    Sprite sv;
    switch(vehicleType){
        case 1:
            sv.setTexture(textures[77 + current_code_image % 4], true);
            break;
        case 2:
            sv.setTexture(textures[69 + current_code_image % 4], true);
            break;
        case 3:
            sv.setTexture(textures[95 + current_code_image % 4], true);
    }

    sv.setScale(destW / widthOri, destH / heightOri);
    sv.setPosition(minScreenX - 35.f, maxY);
    c.w.draw(sv);
}



void RivalCar::drawSmokingFirePlayer(Configuration& c, const float destW, const float destH, const float widthOri,
                                     const float heightOri, const float maxY)
{
    Sprite sv;
    switch(vehicleType){
        case 1:
            sv.setTexture(textures[81 + current_code_image % 4], true);
            break;
        case 2:
            sv.setTexture(textures[73 + current_code_image % 4], true);
            break;
        case 3:
            sv.setTexture(textures[99 + current_code_image % 4], true);
    }

    sv.setScale(destW / widthOri, destH / heightOri);
    sv.setPosition(minScreenX - 35.f, maxY);
    c.w.draw(sv);
}


int RivalCar::getVehicleType(){
    return vehicleType;
}



void RivalCar::setFiring(const bool fire){
    firing = fire;
}


bool RivalCar::getFiring(){
    return firing;
}


void RivalCar::setFiringSmoke(const bool fireSmoke){
    fireSmoking = fireSmoke;
}


bool RivalCar::getFiringSmoke(){
    return fireSmoking;
}



bool RivalCar::inCrash(){
    switch(vehicleType){
        case 0:
            if (current_code_image >= 46 && current_code_image <= 58){
                return true;
            }
            break;
        case 1:
            if (current_code_image >= 37 && current_code_image <= 44){
                return true;
            }
            break;
        case 2:
            if (current_code_image >= 29 && current_code_image <= 36){
                return true;
            }
            break;
        case 3:
            if (current_code_image >= 55 && current_code_image <= 62){
                return true;
            }
    }
    return false;
}




