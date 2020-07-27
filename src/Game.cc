
#include "../include/Game.h"


void Game::storingRivalCars(Configuration& c){

    // Clear the vector of rival cars
    rivals.clear();

    RivalCar v;

    float positY, positX;

    // Control the initial position of the vehicle in the starting point
    switch(numberRacers){
        case 0:
        case 1:
            positY = 13.f;
            break;
        case 2:
        case 3:
            positY = 33.f;
            break;
        case 4:
        case 5:
            positY = 53.f;
            break;
        case 6:
        case 7:
            positY = 73.f;
            break;
        default:
            positY = 0.f;
    }

    // Initialize the position of the player
    posArrival = numberRacers + 1;

    int j;
    if (colorCarSelected == 7){
        j = 0;
    }
    else {
        j = colorCarSelected + 1;
    }


    // Store the rival cars in the vector
    for (int i = 0; i < numberRacers; i++) {

        if (i % 2 == 0){
            positX = 0.3f;
        }
        else {
            positX = -0.3f;
        }
        // Set the scale of the vehicle
        switch(typeOfVehicle){
            case 0:
                v = RivalCar(typeOfVehicle, MAX_SPEED, SPEED_FACTOR, 2.5f, COUNTER, "Data/Vehicles/Motorbikes/Motorbike" + to_string(j + 1),
                             positX, positY, Motorbike_vehicle::PLAYER_TEXTURES, 1, 2, 15, 16, 3, 8, 17, 22, 9, 14, 23, 28, 1, 2, 15, 16, 3,
                             8, 17, 22, 9, 14, 23, 28, 7, 13, 7, 13, 21, 27, 21, 27, 1.15f);

                v.setAI(c.maxAggressiveness, c.level);
                rivals.push_back(v);
                break;
            case 1:
                v = RivalCar(typeOfVehicle, MAX_SPEED, SPEED_FACTOR, 4.f, COUNTER, "Data/Vehicles/Devastators/Devastator" + to_string(j + 1),
                             positX, positY, Devastator_vehicle::PLAYER_TEXTURES, 1, 4, 19, 22, 5, 8, 23, 26, 9, 12, 27, 30, 13, 14,
                             31, 32, 15, 16, 33, 34, 17, 18, 35, 36, 6, 10, 15, 17, 24, 28, 33, 35, 1.85f);

                v.setAI(c.maxAggressiveness, c.level);
                rivals.push_back(v);
                break;
            case 2:
                v = RivalCar(typeOfVehicle, MAX_SPEED, SPEED_FACTOR, 4.f, COUNTER, "Data/Vehicles/Minivans/Minivan" + to_string(j + 1),
                             positX, positY, Minivan_vehicle::PLAYER_TEXTURES, 1, 2, 15, 16, 3, 5, 17, 19, 6, 8, 17, 19, 9, 10, 23, 24,
                             11, 12, 25, 26, 13, 14, 20, 22, 3, 6, 11, 13, 17, 20, 25, 27, 1.75f);

                v.setAI(c.maxAggressiveness, c.level);
                rivals.push_back(v);
                break;
            case 3:
                v = RivalCar(typeOfVehicle, MAX_SPEED, SPEED_FACTOR, 4.5f, COUNTER, "Data/Vehicles/Trucks/Truck" + to_string(j + 1),
                             positX, positY, Truck_vehicle::PLAYER_TEXTURES, 1, 5, 28, 32, 6, 10, 33, 37, 11, 15, 38, 42, 16, 19,
                             43, 46, 20, 23, 47, 50, 24, 27, 51, 54, 7, 12, 21, 25, 34, 39, 48, 52, 2.02f);

                v.setAI(c.maxAggressiveness, c.level);
                rivals.push_back(v);
        }
        // Update the position of the staring vehicles
        if (i % 2 != 0){
            positY -= 20.f;
        }

        j++;
        if (j == 8){
            j = 0;
        }
    }
}


void Game::loadWorldTourPolePositionLandScape(Configuration& c, const string path, const int i, int timeLandscape, const int typeOfGame,
                                              mutex tourLandScapesMutex[])
{
    // Load the landscape using the correspond path
    LandScape m(c, path + to_string(i + 1) + "/", "bg.png", timeLandscape, typeOfGame, numberRacers);

    // Check if is the turn of the thread
    tourLandScapesMutex[i].lock();

    // Store the landscape
    tourLandScapes.push_back(m);

    // If it is not the last thread wakes up the next one
    if (i != 3){
        tourLandScapesMutex[i + 1].unlock();
    }
}



void Game::loadOutRunDrivingFuryDerramageLandScape(Configuration& c, const string path, const int i, int timeLandscape,
                                                   const int typeOfGame, mutex tourLandScapesMutex[], vector<LandScape>& vm)
{
    // Load the landscape using the correspond path
    LandScape m(c, path, "bg.png", timeLandscape, typeOfGame, numberRacers);

    // Check if the threads has the permission store the landscapes
    tourLandScapesMutex[i].lock();

    // Store the landscape in the vector
    vm.push_back(m);

    // Wake up to the next thread
    if (i != 14){
        tourLandScapesMutex[i + 1].unlock();
    }
}




void Game::updateTimeElapsed(){

    // Clock counter of time
    Clock gameClockLap;

    // Time to update the clock counter lap
    Time shot_delayLap = seconds(0.01);

    gameClockLap.restart();
    elapsed3 = gameClockLap.getElapsedTime().asSeconds();

    bool arrived = false , endOfGame = false, pause = false;

    while(!arrived && !endOfGame && !pause){

        mtx.lock();
        pause = onPause;
        mtx.unlock();

        if (!pause){

            // Sleep the thread
            this_thread::sleep_for(chrono::milliseconds(50));

            // Get the actual time
            elapsed4 = gameClockLap.getElapsedTime().asSeconds();

            // Check if a tenth of second has passed between both timestamps
            if (elapsed4 - elapsed3 >= shot_delayLap.asSeconds()) {
                mtx.lock();
                cents_second += elapsed4;
                if (cents_second >= 1.f) {
                    cents_second -= 1.f;
                    secs++;
                    if (secs == 60.f) {
                        secs = 0;
                        minutes++;
                    }
                }
                cents_secondTrip += elapsed4;
                if (cents_secondTrip >= 1.f) {
                    cents_secondTrip -= 1.f;
                    secsTrip++;
                    if (secsTrip == 60.f) {
                        secsTrip = 0;
                        minutesTrip++;
                    }
                }
                gameClockLap.restart();
                mtx.unlock();
            }
            mtx.lock();
            arrived = arrival;
            endOfGame = finalGame;
            pause = onPause;
            mtx.unlock();
        }
        else {
            gameClockLap.restart();
        }
    }
}



void Game::updateTimeLandScape(){

    // Initialize the clock counters of time
    gameClockTime.restart().asSeconds();
    elapsed1 = gameClockTime.restart().asSeconds();

    // Time to update the clock counter
    Time shot_delayTime = seconds(1.0);

    bool arrived = false , endOfGame = false, pause = false;

    while(!arrived && !endOfGame && !onPause){

        mtx.lock();
        pause = onPause;
        mtx.unlock();

        if (!pause){

             // Sleep the thread
            this_thread::sleep_for(chrono::milliseconds(50));

            // Get the actual time
            elapsed2 = gameClockTime.getElapsedTime().asSeconds();

            // Check if a second has passed between both timestamps
            if (elapsed2 - elapsed1 >= shot_delayTime.asSeconds()) {
                // Draw time
                mtx.lock();
                time--;
                mtx.unlock();
                gameClockTime.restart();
            }

            mtx.lock();
            arrived = arrival;
            endOfGame = finalGame;
            pause = onPause;
            mtx.unlock();
        }
        else {
            gameClockTime.restart();
        }
    }
}



void Game::updateScore(){

    bool arrived = false , endOfGame = false, pause = false;
    float speed;

    while(!arrived && !endOfGame && !pause){

        mtx.lock();
        pause = onPause;
        mtx.unlock();

        if (!pause){

            // Sleep the thread
            this_thread::sleep_for(chrono::milliseconds(50));

            switch(typeOfVehicle){
                case 0:
                    mainMutex.lock();
                    speed = player.getRealSpeed();
                    mainMutex.unlock();
                    // Update the score of the player if the player is not stopped
                    if (speed > 0.0f) {
                        // Add score
                        mainMutex.lock();
                        score += int(player.getRealSpeed() * scoreMul);
                        mainMutex.unlock();
                    }
                    break;
                case 1:
                    mainMutex.lock();
                    speed = player2.getRealSpeed();
                    mainMutex.unlock();
                    // Update the score of the player if the player is not stopped
                    if (speed > 0.0f) {
                        // Add score
                        mainMutex.lock();
                        score += int(player2.getRealSpeed() * scoreMul);
                        mainMutex.unlock();
                    }
                    break;
                case 2:
                    mainMutex.lock();
                    speed = player3.getRealSpeed();
                    mainMutex.unlock();
                    // Update the score of the player if the player is not stopped
                    if (speed > 0.0f) {
                        // Add score
                        mainMutex.lock();
                        score += int(player3.getRealSpeed() * scoreMul);
                        mainMutex.unlock();
                    }
                    break;
                case 3:
                    mainMutex.lock();
                    speed = player4.getRealSpeed();
                    mainMutex.unlock();
                    // Update the score of the player if the player is not stopped
                    if (speed > 0.0f) {
                        // Add score
                        mainMutex.lock();
                        score += int(player4.getRealSpeed() * scoreMul);
                        mainMutex.unlock();
                    }
                    break;
                case 4:
                    mainMutex.lock();
                    speed = player5.getRealSpeed();
                    mainMutex.unlock();
                    // Update the score of the player if the player is not stopped
                    if (speed > 0.0f) {
                        // Add score
                        mainMutex.lock();
                        score += int(player5.getRealSpeed() * scoreMul);
                        mainMutex.unlock();
                    }
            }
        }
        mainMutex.lock();
        arrived = arrival;
        endOfGame = finalGame;
        pause = onPause;
        mainMutex.unlock();

    }
}



int Game::findPlayerPositionRanking(const float posYPlayer){
    bool found = false;
    int i = 0, j = rankingVehicles.size() - 1;
    while (!found && i <= j){
        if (rankingVehicles[i] > posYPlayer){
            i++;
        }
        else {
            found = true;
        }
    }
    if (!found){
        return numberRacers + 1;
    }
    else {
        return i + 1;
    }
}



/**
 * Load the Hud interface of the game
 */
void Game::loadHudGameWorldTourPolePosition(){
    // Load the elapsed time indicator with the time level indicator
    // and the speed indicator and the checkpoint
    Texture t;
    for (int i = 1; i <= 4; i++){
        // Load the textures of the three indicators
        t.loadFromFile("Data/Hud/" + to_string(i) + ".png");
        textures.push_back(t);
    }
    for (int i = 24; i <= 27; i++){
        // Load the textures of the three indicators
        t.loadFromFile("Data/Hud/" + to_string(i) + ".png");
        textures.push_back(t);
    }
}




/**
 * Load the Hud interface of the game
 */
void Game::loadHudGameOutRunDrivingFuryDerramage(){
    // Load the elapsed time indicator with the time level indicator
    // and the speed indicator and the checkpoint
    Texture t;
    for (int i = 1; i <= 8; i++){
        // Load the textures of the three indicators
        t.loadFromFile("Data/Hud/" + to_string(i) + ".png");
        textures.push_back(t);
    }
    // Code of first landscape
    int idFirstMap = 9;

    // Fill the matrix with the tree maps
    for (int i = 0; i <= 4; i++) {
        for (int j = 0; j <= i; j++) {
            t.loadFromFile("Data/Hud/" + to_string(idFirstMap) + ".png");
            treeMap[i][j] = t;
            idFirstMap++;
        }
    }
}


/**
 * Draw the bonus final animation
 * @param c is the configuration of the game
 * @param seconds are the seconds the player has left when he reaches the goal
 * @param decs_second are the hundreds of seconds the player has left when he reaches the goal
 */
void Game::drawBonus(Configuration &c, int seconds, int decs_second) {
    // Only for separation
    Sprite s;
    s.setTexture(textures[0], true);
    s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
    const float separation = s.getGlobalBounds().width / 3.0f;

    // Final score after completing all the levels
    Text bonification;
    bonification.setFont(c.fontTimeToPlay);
    bonification.setString("BONUS POINTS!");
    bonification.setCharacterSize(static_cast<unsigned int>(int(65.0f * c.screenScale)));
    bonification.setFillColor(Color::Yellow);
    bonification.setOutlineColor(Color(12, 12, 12));
    bonification.setOutlineThickness(3.0f * c.screenScale);
    float initialY = float(c.w.getSize().y) / 3.0f + float(bonification.getCharacterSize());
    float initial = (float(c.w.getSize().x) - bonification.getGlobalBounds().width) / 2.0f;
    bonification.setPosition(initial, float(c.w.getSize().y) / 3.0f - float(bonification.getCharacterSize()));
    c.w.draw(bonification);

    // Time bonus to the player
    Text timeBonus;
    timeBonus.setFont(c.fontTimeToPlay);
    timeBonus.setString("000.0");
    timeBonus.setCharacterSize(static_cast<unsigned int>(int(55.0f * c.screenScale)));
    timeBonus.setFillColor(Color::Yellow);
    timeBonus.setOutlineColor(Color(12, 12, 12));
    timeBonus.setOutlineThickness(3.0f * c.screenScale);
    initial -= timeBonus.getLocalBounds().width;
    timeBonus.setPosition(initial, initialY);
    initialY += float(timeBonus.getCharacterSize());
    initial += 1.25f * timeBonus.getLocalBounds().width;
    timeBonus.setString(to_string(seconds) + "." + to_string(decs_second));
    c.w.draw(timeBonus);

    // Seconds arrival indicator
    Text secondsIndicator;
    secondsIndicator.setFont(c.fontTimeToPlay);
    secondsIndicator.setString("SEC");
    secondsIndicator.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
    secondsIndicator.setFillColor(Color(183, 164, 190));
    secondsIndicator.setOutlineColor(Color::Black);
    secondsIndicator.setOutlineThickness(3.0f * c.screenScale);
    secondsIndicator.setPosition(initial, initialY - float(secondsIndicator.getCharacterSize()));
    initial += separation + secondsIndicator.getLocalBounds().width;
    c.w.draw(secondsIndicator);

    // Seconds arrival indicator
    Text crossSign;
    crossSign.setFont(c.fontTimeToPlay);
    crossSign.setString("x");
    crossSign.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    crossSign.setFillColor(Color(232, 191, 157));
    crossSign.setOutlineColor(Color::Black);
    crossSign.setOutlineThickness(3.0f * c.screenScale);
    crossSign.setPosition(initial, initialY - float(crossSign.getCharacterSize()));
    initial += separation + crossSign.getLocalBounds().width;
    c.w.draw(crossSign);

    // Score factor to multiply
    Text scoreMultiply;
    scoreMultiply.setFont(c.fontTimeToPlay);
    scoreMultiply.setString(to_string((long long) BONIFICATION));
    scoreMultiply.setCharacterSize(static_cast<unsigned int>(int(55.0f * c.screenScale)));
    scoreMultiply.setFillColor(Color::Yellow);
    scoreMultiply.setOutlineColor(Color(12, 12, 12));
    scoreMultiply.setOutlineThickness(3.0f * c.screenScale);
    scoreMultiply.setPosition(initial * 0.92f, initialY - float(scoreMultiply.getCharacterSize()));
    initial += separation + scoreMultiply.getLocalBounds().width;
    c.w.draw(scoreMultiply);

    // Seconds arrival indicator
    Text pointsIndicator;
    pointsIndicator.setFont(c.fontTimeToPlay);
    pointsIndicator.setString("PTS");
    pointsIndicator.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
    pointsIndicator.setFillColor(Color(183, 164, 190));
    pointsIndicator.setOutlineColor(Color::Black);
    pointsIndicator.setOutlineThickness(3.0f * c.screenScale);
    pointsIndicator.setPosition(initial * 0.90f, initialY - float(pointsIndicator.getCharacterSize()));
    c.w.draw(pointsIndicator);
}



/**
 * Draw the new lap animation
 * @param c is the configuration of the game
 * @param r is the sound reproducer of the game
 */
void Game::drawNewLap(Configuration &c){

    string lap;
    if (lapsDone == numberLaps){
        lap = " FINAL LAP!";
    }
    else {
        switch(lapsDone){
            case 2:
                lap = "SECOND LAP!";
                break;
            case 3:
                lap = " THIRD LAP!";
                break;
            case 4:
                lap = "FOURTH LAP!";
        }
    }

    // CheckPoint title
    Text lapText;
    lapText.setFont(c.fontTimeToPlay);
    lapText.setString(lap);
    lapText.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    lapText.setOutlineThickness(3.0f * c.screenScale);

    if (!onPause){
        if (!shown){
            // Control the position of the lap indicator in axis x
            if (timeElapsed != displayLapFactor){
                if (offsetLapIndicator < 1.48f){
                    // Check if the indicator is coming or returning
                    offsetLapIndicator += 0.01075;
                }
                else {
                    // Time slept increased
                    timeElapsed++;
                }
            }
            else {
                if (offsetLapIndicator > 1.f){
                    offsetLapIndicator -= 0.01075;
                    if (offsetLapIndicator < 1.f){
                        offsetLapIndicator = 1.f;
                    }
                }
                else {
                    timeElapsed = 0;
                    shown = true;
                }
            }
        }
    }
    lapText.setPosition(c.w.getSize().x / offsetLapIndicator, c.w.getSize().y / 6.1f);
    c.w.draw(lapText);
}



/**
 * Draw the HUD interface of the game
 * @param c is the configuration of the game
 */
void Game::showHudInterfaceOutRunDrivingFuryDerramage(Configuration &c) {

    // Sprite to draw the elements of the HUD interface
    Sprite s;

    // Assign positions in the game console for the game panel indicators
    const float up = float(c.w.getSize().y) / 10.0f;

    // UP
    s.setTexture(textures[0], true);
    s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
    float separation = s.getGlobalBounds().width / 5.5f;
    s.setPosition(separation, up - 0.7f * s.getGlobalBounds().height);
    float initial = separation + s.getGlobalBounds().width + separation;
    c.w.draw(s);

    // Indicator of the elapsed time
    Text elapsedTime;
    elapsedTime.setFont(c.fontElapsedTime);
    elapsedTime.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
    elapsedTime.setFillColor(Color::Green);

    // Available time to complete the level
    Text timeToPlay;
    timeToPlay.setString("000");
    timeToPlay.setFont(c.fontTimeToPlay);
    timeToPlay.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    timeToPlay.setFillColor(Color::Yellow);
    timeToPlay.setOutlineColor(Color::Black);
    timeToPlay.setOutlineThickness(3.0f * c.screenScale);
    timeToPlay.setPosition(initial * 1.41f, up - 0.5f * float(timeToPlay.getCharacterSize()));
    timeToPlay.setString(to_string(time));
    c.w.draw(timeToPlay);

    initial += elapsedTime.getGlobalBounds().width + separation;
    s.setTexture(textures[1], true);
    s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
    s.setPosition(initial * 1.15f, up - s.getGlobalBounds().height * 1.6f);
    c.w.draw(s);
    initial += s.getGlobalBounds().width + separation;

    // Initialize the HUD indicator of lap time
    // Time of lap consumed
    Text textLap;
    textLap.setFont(c.fontElapsedTime);
    textLap.setString("00:00:00");
    textLap.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));
    textLap.setFillColor(Color::Green);
    initial = float(c.w.getSize().x) - separation - textLap.getGlobalBounds().width;
    textLap.setPosition(initial / 7.5f, up - 0.6f * float(textLap.getCharacterSize()));
    textLap.setString(lap);
    c.w.draw(textLap);
    c.w.draw(s);

    // DOWN
    textures[2].loadFromFile("Data/Hud/7.png");
    s.setTexture(textures[2], true);
    s.setScale(2.f * c.screenScale, 1.5f * c.screenScale);
    const float down = float(c.w.getSize().y) - s.getGlobalBounds().height * 1.5f;
    s.setPosition(separation, float(c.w.getSize().y) - s.getGlobalBounds().height * 1.25f);
    initial = separation + s.getGlobalBounds().width / 4.0f;

    float speed = 0.f;

    switch(typeOfVehicle){
        case 0:
            speed = player.getRealSpeed();
            break;
        case 1:
            speed = player2.getRealSpeed();
            break;
        case 2:
            speed = player3.getRealSpeed();
            break;
        case 3:
            speed = player4.getRealSpeed();
            break;
        case 4:
            speed = player5.getRealSpeed();
    }

    textures[2].loadFromFile("Data/Hud/3.png",
                             IntRect(0, 0, static_cast<int>(speed * 117.0f / MAX_SPEED * c.screenScale),
                                     static_cast<int>(20.0f * c.screenScale)));


    s.setTexture(textures[2], true);
    if (speed > 0.0f)
        c.w.draw(s);

    // Text
    // HUD
    Text sText;
    sText.setFont(c.speedVehicle);
    sText.setString("0001");
    sText.setCharacterSize(static_cast<unsigned int>(int(70.0f * c.screenScale)));
    sText.setFillColor(Color(206, 73, 73));
    sText.setOutlineThickness(3.0f * c.screenScale);
    sText.setPosition(initial - (sText.getLocalBounds().width * 0.26f), down - float(sText.getCharacterSize()));
    initial += sText.getGlobalBounds().width;

    string strSpeed;

    switch(typeOfVehicle){
    case 0:
       strSpeed = to_string(player.getRealSpeed());
       break;
    case 1:
        strSpeed = to_string(player2.getRealSpeed());
        break;
    case 2:
        strSpeed = to_string(player3.getRealSpeed());
        break;
    case 3:
        strSpeed = to_string(player4.getRealSpeed());
        break;
    case 4:
        strSpeed = to_string(player5.getRealSpeed());
    }

    sText.setString(strSpeed.substr(0, strSpeed.find('.')));
    c.w.draw(sText);

    s.setTexture(textures[3], true);
    s.setScale(2.f * c.screenScale, 2.f * c.screenScale);
    s.setPosition(initial / 1.2f, down - s.getGlobalBounds().height);
    c.w.draw(s);

    // Draw the tree map label with level of the player
    s.setTexture(treeMap[mapId.first][mapId.second], true);
    s.setScale(2.f * c.screenScale, 2.f * c.screenScale);
    initial = float(c.w.getSize().x) - separation - s.getGlobalBounds().width;
    s.setPosition(initial, down - s.getGlobalBounds().height);
    c.w.draw(s);

    // Initialize the HUD stage indicator
    // Level indicator
    Text textLevel;
    textLevel.setFont(c.fontTimeToPlay);
    textLevel.setString("0");
    textLevel.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    textLevel.setFillColor(Color(146, 194, 186));
    textLevel.setOutlineColor(Color::Black);
    textLevel.setOutlineThickness(3.0f * c.screenScale);
    initial -= separation + textLevel.getGlobalBounds().width;
    textLevel.setPosition(initial, down - 1.0f * float(textLevel.getCharacterSize()));
    textLevel.setString(to_string(level));
    c.w.draw(textLevel);

    s.setTexture(textures[6], true);
    s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
    initial -= separation + s.getGlobalBounds().width;
    s.setPosition(initial * 1.03f, down - s.getGlobalBounds().height);
    c.w.draw(s);

    // Score indicator
    s.setTexture(textures[7], true);
    s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
    separation = s.getGlobalBounds().width / 5.5f;
    s.setPosition(separation * 32.0f, up - 1.55f * s.getGlobalBounds().height);
    initial = separation + s.getGlobalBounds().width + separation;
    c.w.draw(s);

    // Initialize the HUD indicator of score
    // Score of the player displayed in the panel
    Text textScore;
    textScore.setFont(c.fontTimeToPlay);
    textScore.setString(to_string(int(BONIFICATION) * 100));
    textScore.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    textScore.setFillColor(Color(183, 164, 190));
    textScore.setOutlineColor(Color::Black);
    textScore.setOutlineThickness(3.0f * c.screenScale);
    textScore.setString(to_string(score));
    textScore.setPosition(initial * 4.95f - textScore.getLocalBounds().width, up - 0.5f * float(textScore.getCharacterSize()));
    c.w.draw(textScore);

    // Add the distance tool bar if it's driving fury or Derramage mode
    if (typeOfGame == 3 || typeOfGame == 4){

        Text distanceText;
        distanceText.setFont(c.fontTimeToPlay);
        distanceText.setString(to_string(int(BONIFICATION) * 100));
        distanceText.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        distanceText.setFillColor(Color(60, 235, 102));
        distanceText.setOutlineColor(Color::Black);
        distanceText.setOutlineThickness(3.0f * c.screenScale);
        distanceText.setString("DISTANCE");
        distanceText.setPosition(initial * 5.6f - distanceText.getLocalBounds().width, up * 2.5f - 2.6f * float(distanceText.getCharacterSize()));
        c.w.draw(distanceText);

        // Draw the rectangle
        RectangleShape shape;
        shape.setPosition(initial * 5.14f, up * 2.25f);
        shape.setSize(sf::Vector2f(40.0f * c.screenScale, 420.0f * c.screenScale));
        shape.setOutlineColor(Color::Black);
        shape.setOutlineThickness(3.0f * c.screenScale);
        shape.setFillColor(Color(119, 195, 187));
        c.w.draw(shape);

        Text healthText;
        healthText.setFont(c.fontTimeToPlay);
        healthText.setString(to_string(int(BONIFICATION) * 100));
        healthText.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        healthText.setFillColor(Color(227, 17, 30));
        healthText.setOutlineColor(Color::Black);
        healthText.setOutlineThickness(3.0f * c.screenScale);
        healthText.setString("HEALTH");
        healthText.setPosition(initial / 1.1f - healthText.getLocalBounds().width, up * 2.5f - 2.6f * float(healthText.getCharacterSize()));
        c.w.draw(healthText);

        // Draw the rectangle
        shape.setPosition(initial / 2.0f, up * 2.25f);
        shape.setSize(sf::Vector2f(40.0f * c.screenScale, 420.0f * c.screenScale));
        shape.setOutlineColor(Color(43, 211, 30));
        shape.setOutlineThickness(3.0f * c.screenScale);
        shape.setFillColor(Color::Black);
        c.w.draw(shape);
    }
}




/**
 * Draw the HUD interface of the game
 * @param c is the configuration of the game
 */
void Game::showHudInterfaceWorldTourPolePosition(Configuration &c) {

    // Sprite to draw the elements of the HUD interface
    Sprite s;

    // Assign positions in the game console for the game panel indicators
    const float up = float(c.w.getSize().y) / 10.0f;

    // UP
    s.setTexture(textures[0], true);
    s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
    const float separation = s.getGlobalBounds().width / 5.5f;
    s.setPosition(separation, up - 0.7f * s.getGlobalBounds().height);
    float initial = separation + s.getGlobalBounds().width + separation;
    c.w.draw(s);

    // Indicator of the elapsed time
    Text elapsedTime;
    elapsedTime.setFont(c.fontElapsedTime);
    elapsedTime.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
    elapsedTime.setFillColor(Color::Green);

    // Available time to complete the level
    Text timeToPlay;
    timeToPlay.setString("000");
    timeToPlay.setFont(c.fontTimeToPlay);
    timeToPlay.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    timeToPlay.setFillColor(Color::Yellow);
    timeToPlay.setOutlineColor(Color::Black);
    timeToPlay.setOutlineThickness(3.0f * c.screenScale);
    timeToPlay.setPosition(initial * 1.41f, up - 0.5f * float(timeToPlay.getCharacterSize()));
    timeToPlay.setString(to_string(time));
    c.w.draw(timeToPlay);

    initial += elapsedTime.getGlobalBounds().width + separation;
    s.setTexture(textures[1], true);
    s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
    s.setPosition(initial * 1.15f, up - s.getGlobalBounds().height * 1.6f);
    c.w.draw(s);
    initial += s.getGlobalBounds().width + separation;

    // Initialize the HUD indicator of lap time
    // Time of lap consumed
    Text textLap;
    textLap.setFont(c.fontElapsedTime);
    textLap.setString("00:00:00");
    textLap.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));
    textLap.setFillColor(Color::Green);
    initial = float(c.w.getSize().x) - separation - textLap.getGlobalBounds().width;
    textLap.setPosition(initial / 7.5f, up - 0.6f * float(textLap.getCharacterSize()));
    textLap.setString(lap);
    c.w.draw(textLap);
    c.w.draw(s);

    // DOWN
    textures[2].loadFromFile("Data/Hud/7.png");
    s.setTexture(textures[2], true);
    s.setScale(2.f * c.screenScale, 1.5f * c.screenScale);
    const float down = float(c.w.getSize().y) - s.getGlobalBounds().height * 1.5f;
    s.setPosition(separation, float(c.w.getSize().y) - s.getGlobalBounds().height * 1.25f);
    initial = separation + s.getGlobalBounds().width / 4.0f;

    float speed = 0.f;

    switch(typeOfVehicle){
        case 0:
            speed = player.getRealSpeed();
            break;
        case 1:
            speed = player2.getRealSpeed();
            break;
        case 2:
            speed = player3.getRealSpeed();
            break;
        case 3:
            speed = player4.getRealSpeed();
            break;
        case 4:
            speed = player5.getRealSpeed();
    }

    textures[2].loadFromFile("Data/Hud/3.png",
                             IntRect(0, 0, static_cast<int>(speed * 117.0f / MAX_SPEED * c.screenScale),
                                     static_cast<int>(20.0f * c.screenScale)));


    s.setTexture(textures[2], true);
    if (speed > 0.0f)
        c.w.draw(s);

    // Text
    // HUD
    Text sText;
    sText.setFont(c.speedVehicle);
    sText.setString("0001");
    sText.setCharacterSize(static_cast<unsigned int>(int(70.0f * c.screenScale)));
    sText.setFillColor(Color(206, 73, 73));
    sText.setOutlineThickness(3.0f * c.screenScale);
    sText.setPosition(initial - (sText.getLocalBounds().width * 0.26f), down - float(sText.getCharacterSize()));
    initial += sText.getGlobalBounds().width;

    string strSpeed;

    switch(typeOfVehicle){
    case 0:
       strSpeed = to_string(player.getRealSpeed());
       break;
    case 1:
        strSpeed = to_string(player2.getRealSpeed());
        break;
    case 2:
        strSpeed = to_string(player3.getRealSpeed());
        break;
    case 3:
        strSpeed = to_string(player4.getRealSpeed());
        break;
    case 4:
        strSpeed = to_string(player5.getRealSpeed());
    }

    sText.setString(strSpeed.substr(0, strSpeed.find('.')));
    c.w.draw(sText);

    s.setTexture(textures[3], true);
    s.setScale(2.f * c.screenScale, 2.f * c.screenScale);
    s.setPosition(initial / 1.2f, down - s.getGlobalBounds().height);
    c.w.draw(s);

    if (numberRacers > 0){
        Text positionInRace;
        positionInRace.setFont(c.fontTimeToPlay);
        positionInRace.setCharacterSize(static_cast<unsigned int>(int(70.0f * c.screenScale)));
        positionInRace.setFillColor(Color::Red);
        positionInRace.setOutlineColor(Color::Black);
        positionInRace.setOutlineThickness(3.0f * c.screenScale);

        Text ordinalPos;
        ordinalPos.setFont(c.fontTimeToPlay);
        ordinalPos.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
        ordinalPos.setFillColor(Color::Red);
        ordinalPos.setOutlineColor(Color::Black);
        ordinalPos.setOutlineThickness(3.0f * c.screenScale);

        string index;
        switch(posArrival){
            case 1:
                index = "st";
                break;
            case 2:
                index = "nd";
                break;
            case 3:
                index = "rd";
                break;
            default:
                index = "th";
        }

        positionInRace.setString(to_string(posArrival));
        ordinalPos.setString(index);
        positionInRace.setPosition(initial * 3.9f, down - 0.95f * float(positionInRace.getCharacterSize()));
        ordinalPos.setPosition(initial * 3.9f + positionInRace.getLocalBounds().width + 5.f,
                               down - 0.66f * float(positionInRace.getCharacterSize()));

        c.w.draw(positionInRace);
        c.w.draw(ordinalPos);
    }

    // Check point indicator
    Text checkPoint;
    checkPoint.setFont(c.fontTimeToPlay);
    checkPoint.setCharacterSize(static_cast<unsigned int>(int(27.0f * c.screenScale)));
    checkPoint.setFillColor(Color::White);
    checkPoint.setOutlineColor(Color::Black);
    checkPoint.setOutlineThickness(3.0f * c.screenScale);

    int distance = 0;

    // Check if it is the last checkPoint
    if (indexCheckPoint % 4 != 0){
        checkPoint.setString("NEXT CHECKPOINT");
        checkPoint.setPosition(initial * 3.1f, up - 1.8f * float(checkPoint.getCharacterSize()));
        // Calculate the distance between the player and the checkpoint
        switch(typeOfVehicle){
            case 0:
                distance = (checkPointPositions[indexCheckPoint - 1] - player.getPosY()) / 7;
                break;
            case 1:
                distance = (checkPointPositions[indexCheckPoint - 1] - player2.getPosY()) / 7;
                break;
            case 2:
                distance = (checkPointPositions[indexCheckPoint - 1] - player3.getPosY()) / 7;
                break;
            case 3:
                distance = (checkPointPositions[indexCheckPoint - 1] - player4.getPosY()) / 7;
                break;
            case 4:
                distance = (checkPointPositions[indexCheckPoint - 1] - player5.getPosY()) / 7;
        }
    }
    else {
        checkPoint.setString("GOAL IN");
        checkPoint.setPosition(initial * 3.42f, up - 1.8f * float(checkPoint.getCharacterSize()));

        switch(typeOfVehicle){
            case 0:
                distance = (currentMap->getMaxY() - player.getPosY()) / 7;
                break;
            case 1:
                distance = (currentMap->getMaxY() - player2.getPosY()) / 7;
                break;
            case 2:
                distance = (currentMap->getMaxY() - player3.getPosY()) / 7;
                break;
            case 3:
                distance = (currentMap->getMaxY() - player4.getPosY()) / 7;
                break;
            case 4:
                distance = (currentMap->getMaxY() - player5.getPosY()) / 7;
        }
    }

    c.w.draw(checkPoint);

    // Distance to the next checkpoint
    Text distanceCheckPoint;
    distanceCheckPoint.setFont(c.fontTimeToPlay);
    distanceCheckPoint.setString(to_string(distance) + " KM");
    distanceCheckPoint.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));

    // Check the color of the distance indicator
    if (distance >= 100){
        distanceCheckPoint.setFillColor(Color::Green);
    }
    else if(distance < 100 && distance >= 50){
        distanceCheckPoint.setFillColor(Color::Yellow);
    }
    else {
        distanceCheckPoint.setFillColor(Color::Red);
    }
    distanceCheckPoint.setOutlineColor(Color::Black);
    distanceCheckPoint.setOutlineThickness(3.0f * c.screenScale);
    distanceCheckPoint.setPosition(initial * 4.0f - distanceCheckPoint.getLocalBounds().width,
                                   up - 0.5f * float(distanceCheckPoint.getCharacterSize()));
    c.w.draw(distanceCheckPoint);
}



/**
 * Change the soundtrack which is been sounding during the game
 * @param c is the configuration of the game
 * @param r is the sound reproducer of the game
 */
void Game::checkSoundtrackChanging(Configuration& c, SoundPlayer& r){

    // Check if the time to change the soundtrack has spent
    elapsed14 = soundtrackClock.getElapsedTime().asSeconds();

    //Check the time
    if (elapsed14 - elapsed13 >= soundtrack_delay.asSeconds()){
        // Check if the key to change the soundtrack has been pressed
        if (Keyboard::isKeyPressed(c.soundtrackKey)){
            // Inform that the soundtrack has been changed
            r.soundtrackChanged = true;
             // Stop the soundtrack of the game
            r.soundTracks[r.currentSoundtrack]->stop();
            // Change the soundtrack which is been reproduced
            if (r.currentSoundtrack != 11){
                // Advance to the following track
                r.currentSoundtrack++;
            }
            else {
                // Start the soundtrack list again
                r.currentSoundtrack = 2;
            }
            // Reproduce the new soundtrack
            r.soundTracks[r.currentSoundtrack]->play();

            // Restart the clock
            soundtrackClock.restart();
        }
        else {
            r.soundtrackChanged = false;
        }
    }
    else {
        // The time has not passed but could be changed before
        if (r.soundtrackChanged){
            // Display the title of the soundtrack
            Text titleSoundtrack;
            titleSoundtrack.setFont(c.fontTimeToPlay);
            titleSoundtrack.setString(r.titleSoundtracks[r.currentSoundtrack - 2]);
            titleSoundtrack.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
            titleSoundtrack.setFillColor(Color::Yellow);
            titleSoundtrack.setOutlineColor(Color(14, 29, 184));
            titleSoundtrack.setOutlineThickness(3.0f * c.screenScale);
            titleSoundtrack.setPosition((float(c.w.getSize().x) - titleSoundtrack.getGlobalBounds().width) / 2.0f,
                                 (float(c.w.getSize().y) - float(titleSoundtrack.getCharacterSize())) / 6.0f);

            c.w.draw(titleSoundtrack);
        }
    }
}



/**
 * Display the message of check point the screen of the game
 * @param c is the configuration of the game
 * @param visible controls if the check point message is visible or not
 */
void Game::showCheckpointIndications(Configuration &c, bool visible) {
    Sprite s;

    // CheckPoint title
    Text checkPointTitle;
    checkPointTitle.setFont(c.fontTimeToPlay);
    checkPointTitle.setString("CHECKPOINT!");
    checkPointTitle.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));

    checkPointTitle.setOutlineThickness(3.0f * c.screenScale);
    float initial = c.w.getSize().y / 3.0f + 0.25f * float(checkPointTitle.getCharacterSize());
    checkPointTitle.setPosition((float(c.w.getSize().x) - checkPointTitle.getGlobalBounds().width) / 2.0f,
                                c.w.getSize().y / 3.0f - float(checkPointTitle.getCharacterSize()));

    if (visible) {
        checkPointTitle.setFillColor(Color::Yellow);
        checkPointTitle.setOutlineColor(Color(14, 29, 184));
        c.w.draw(s);
        c.w.draw(checkPointTitle);

    }
    else {
        checkPointTitle.setFillColor(Color::Transparent);
        checkPointTitle.setOutlineColor(Color::Transparent);
    }

    Text textForLap;
    textForLap.setFont(c.fontElapsedTime);
    textForLap.setString("00:00:00");
    textForLap.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
    textForLap.setOutlineThickness(3.0f * c.screenScale);
    textForLap.setPosition(float(c.w.getSize().x) - s.getGlobalBounds().width / 2.0f, initial);

    Text extendTime;
    extendTime.setFont(c.fontTimeToPlay);
    extendTime.setString("EXTENDED TIME!");
    extendTime.setCharacterSize(static_cast<unsigned int>(int(25.0f * c.screenScale)));
    extendTime.setOutlineThickness(3.0f * c.screenScale);
    extendTime.setPosition((float(c.w.getSize().x) + textForLap.getGlobalBounds().width / 2.0f) / 2.8f, initial * 1.1f);

    s.setTexture(textures[4], true);
    s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
    textForLap.setPosition(
            (float(c.w.getSize().x) - textForLap.getGlobalBounds().width - s.getGlobalBounds().width) / 1.7f,
            initial + 3.4f * s.getGlobalBounds().height);
    s.setPosition((float(c.w.getSize().x) + textForLap.getGlobalBounds().width / 2.0f) / 2.4f, initial * 1.3f);

    if (visible) {
        textForLap.setFillColor(Color(146, 194, 186));
        textForLap.setOutlineColor(Color::Black);
        extendTime.setFillColor(Color(222, 42, 14));
        extendTime.setOutlineColor(Color::Black);
        c.w.draw(extendTime);
        c.w.draw(s);
    }
    else {
        textForLap.setFillColor(Color::Transparent);
        textForLap.setOutlineColor(Color::Transparent);
        extendTime.setFillColor(Color::Transparent);
        extendTime.setOutlineColor(Color::Transparent);
    }

    textForLap.setString(lapCheckPoint);
    c.w.draw(textForLap);
}



/**
 * Displays the message of game over in the console window
 * @param c is the configuration of the game
 */
void Game::showGameOver(Configuration &c) {
    // Game over text
    Text gameOver;
    gameOver.setFont(c.fontTimeToPlay);
    gameOver.setString("GAME OVER");
    gameOver.setCharacterSize(static_cast<unsigned int>(int(60.0f * c.screenScale)));
    gameOver.setFillColor(Color::Yellow);
    gameOver.setOutlineColor(Color(14, 29, 184));
    gameOver.setOutlineThickness(3.0f * c.screenScale);
    gameOver.setPosition((float(c.w.getSize().x) - gameOver.getGlobalBounds().width) / 2.0f,
                         (float(c.w.getSize().y) - float(gameOver.getCharacterSize())) / 2.0f);
    c.w.draw(gameOver);
}



/**
 * Shows the bonus message when the player arrives to the goal
 * @param c is the configuration of the game
 * @param seconds shows how many seconds the message will be shown
 * @param decs_second shows how many tenths of seconds the message will be shown
 */
void Game::showBonusIndications(Configuration &c, int seconds, int decs_second) {
    // Only for separation
    Sprite s;
    s.setTexture(textures[0], true);
    s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
    const float separation = s.getGlobalBounds().width / 3.0f;

    // Final score after completing all the levels
    Text bonification;
    bonification.setFont(c.fontTimeToPlay);
    bonification.setString("BONUS POINTS!");
    bonification.setCharacterSize(static_cast<unsigned int>(int(65.0f * c.screenScale)));
    bonification.setFillColor(Color::Yellow);
    bonification.setOutlineColor(Color(12, 12, 12));
    bonification.setOutlineThickness(3.0f * c.screenScale);
    float initialY = float(c.w.getSize().y) / 3.0f + float(bonification.getCharacterSize());
    float initial = (float(c.w.getSize().x) - bonification.getGlobalBounds().width) / 2.0f;
    bonification.setPosition(initial, float(c.w.getSize().y) / 3.0f - float(bonification.getCharacterSize()));
    c.w.draw(bonification);

    // Time bonus to the player
    Text timeBonus;
    timeBonus.setFont(c.fontTimeToPlay);
    timeBonus.setString("000.0");
    timeBonus.setCharacterSize(static_cast<unsigned int>(int(55.0f * c.screenScale)));
    timeBonus.setFillColor(Color::Yellow);
    timeBonus.setOutlineColor(Color(12, 12, 12));
    timeBonus.setOutlineThickness(3.0f * c.screenScale);
    initial -= timeBonus.getLocalBounds().width;
    timeBonus.setPosition(initial, initialY);
    initialY += float(timeBonus.getCharacterSize());
    initial += 1.25f * timeBonus.getLocalBounds().width;
    timeBonus.setString(to_string(seconds) + "." + to_string(decs_second));
    c.w.draw(timeBonus);

    // Seconds arrival indicator
    Text secondsIndicator;
    secondsIndicator.setFont(c.fontTimeToPlay);
    secondsIndicator.setString("SEC");
    secondsIndicator.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
    secondsIndicator.setFillColor(Color(183, 164, 190));
    secondsIndicator.setOutlineColor(Color::Black);
    secondsIndicator.setOutlineThickness(3.0f * c.screenScale);
    secondsIndicator.setPosition(initial, initialY - float(secondsIndicator.getCharacterSize()));
    initial += separation + secondsIndicator.getLocalBounds().width;
    c.w.draw(secondsIndicator);

    // Seconds arrival indicator
    Text crossSign;
    crossSign.setFont(c.fontTimeToPlay);
    crossSign.setString("x");
    crossSign.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    crossSign.setFillColor(Color(232, 191, 157));
    crossSign.setOutlineColor(Color::Black);
    crossSign.setOutlineThickness(3.0f * c.screenScale);
    crossSign.setPosition(initial, initialY - float(crossSign.getCharacterSize()));
    initial += separation + crossSign.getLocalBounds().width;
    c.w.draw(crossSign);

    // Score factor to multiply
    Text scoreMultiply;
    scoreMultiply.setFont(c.fontTimeToPlay);
    scoreMultiply.setString(to_string((long long) BONIFICATION));
    scoreMultiply.setCharacterSize(static_cast<unsigned int>(int(55.0f * c.screenScale)));
    scoreMultiply.setFillColor(Color::Yellow);
    scoreMultiply.setOutlineColor(Color(12, 12, 12));
    scoreMultiply.setOutlineThickness(3.0f * c.screenScale);
    scoreMultiply.setPosition(initial, initialY - float(scoreMultiply.getCharacterSize()));
    initial += separation + scoreMultiply.getLocalBounds().width;
    c.w.draw(scoreMultiply);

    // Seconds arrival indicator
    Text pointsIndicator;
    pointsIndicator.setFont(c.fontTimeToPlay);
    pointsIndicator.setString("PTS");
    pointsIndicator.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
    pointsIndicator.setFillColor(Color(183, 164, 190));
    pointsIndicator.setOutlineColor(Color::Black);
    pointsIndicator.setOutlineThickness(3.0f * c.screenScale);
    pointsIndicator.setPosition(initial, initialY - float(pointsIndicator.getCharacterSize()));
    c.w.draw(pointsIndicator);
}



/**
 * Load the properties of the different available vehicles to play
 * @param path is the path of the xml configuration file of the vehicle
 * @param name is the brand of the vehicle
 * @param max_speed is the top speed reached by the vehicle in km/h / 100
 * @param angle is the turning angle of the vehicle
 * @param motorName is the brand's motor of the vehicle
 */
 void Game::loadVehicleProperties(const string path, string& name, float& max_speed, float& angle,
                                  string& motorName){

    // Preparing the cml file to be read
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *vehicleNode = doc.first_node();

    // Iterate throughout the properties of the vehicle
    for (xml_node<> *property = vehicleNode->first_node(); property; property = property->next_sibling()){
        // Get the name brand of the vehicle
        if ((string)property->name() == "Name"){
            name = (string)property->value();
        }
        // Get the stop speed reached by the vehicle
        else if ((string)property->name() == "MaxSpeed"){
            // Get the red channel
            max_speed = stof((string)property->value());
        }
        // Get the turning angle of the vehicle
        else if ((string)property->name() == "Angle"){
            // Get the red channel
            angle = stof((string)property->value());
        }
        // Get the motor brand of the vehicle
        else if ((string)property->name() == "Motor"){
            // Get the red channel
            motorName = (string)property->value();
        }
    }
 }




/**
 * Constructor of the game
 * @param c is the configuration of the game
 */
Game::Game(Configuration &c){

    typeOfVehicle = 0;
    lastY = 0;
    vehicleCrash = false;
    timeMul = 1.0f;
    scoreMul = 1.0f;
    timeAI = 0.0f;

    // Control if the player is still playing
    finalGame = false;
    inGame = false;
    onPause = false;
    comeFromOptions = false;
    blink = false;
    arrival = false;
    updatedTimeCheck = false;
    shown = false;
    woman_delay = seconds(5.0f);
    traffic_delay = seconds(2.f);
    blink_delay = seconds(0.5f);
    bonus_delay = seconds(0.01f);

    minutesTrip = 0;
    secsTrip = 0;
    cents_secondTrip = 0;
    timeCheck = 0;
    numberLaps = 3;
    lapsDone = 1;
    timeElapsed = 0;
    offsetLapIndicator = 1.f;
    numberRacers = 7;

    lap = "00:00:00";
    typeOfGame = 1;
    colorCarSelected = 0;
}



/**
 * Load the configuration of the world tour and pole position modes
 * @param c is the configuration of the game
 */
State Game::loadWorldTourPolePositionConf(Configuration& c){
    finalGame = false;
    lastY = 0;
    vehicleCrash = false;

    onPause = false;
    comeFromOptions = false;
    blink = false;
    arrival = false;
    updatedTimeCheck = false;

    minutes = 0;
    secs = 0;
    cents_second = 0;
    minutesTrip = 0;
    secsTrip = 0;
    cents_secondTrip = 0;
    timeCheck = 0;
    lap = "00:00:00";
    indexCheckPoint = 1;

    switch(typeOfVehicle){
        case 0:
            player.setVehicle(typeOfGame);
            break;
        case 1:
            player2.setVehicle(typeOfGame);
            break;
        case 2:
            player3.setVehicle(typeOfGame);
            break;
        case 3:
            player4.setVehicle(typeOfGame);
    }

    // Times of each scenario
    vector<int> times;

    string path;
    if (typeOfGame == 0){
        times = {62, 53, 54, 55};
        path = "Data/Gamemodes/WorldTour/LandScapes/LandScape";
    }
    else {
        times = {58, 58, 59, 57};
        path = "Data/Gamemodes/PolePosition/LandScapes/LandScape";
    }

    // Array of mutex for control the storing order of the landscapes
    mutex tourLandScapesMutex[4];

    // Array of threads
    thread P[4];

    // Throw a thread for each landscape that has to be loaded
    for (int i = 0; i < 4; i++){
        // Lock all the mutex except the first one
        if (i != 0){
            tourLandScapesMutex[i].lock();
        }
        // Throw a thread to load the landscape i
        P[i] = thread(loadWorldTourPolePositionLandScape, this, ref(c), path, i , times[i], typeOfGame, ref(tourLandScapesMutex));
    }

    // Wait until all threads have finished
    for (int i = 0; i < 4; i++){
        P[i].join();
    }

    // Index of the first landscape
    indexLandScape = 0;
    // Definition of the first landScape

    if (typeOfGame == 0){
        currentMap = &tourLandScapes[indexLandScape];

        // Back door
        int bdTime = 0;
        time = int(float(currentMap->getTimeToPlay()) * timeMul) + bdTime;
        score = 0;
        level = -1;

        // Initialize the checkpoint index
        indexCheckPoint = 1;
        checkPointPositions = tourLandScapes[indexLandScape].getCheckPointPositions();
    }

    // Load the game mode hud
    loadHudGameWorldTourPolePosition();

    if (typeOfGame == 2){
        return CIRCUIT_SELECTION_MENU;
    }
    else {
        return LOADING;
    }
}



/**
 * Load the configuration of the Out Run, Driving Fury and Demarrage modes
 * @param c is the configuration of the game
 */
State Game::loadOutRunDrivingFuryDemarrageConf(Configuration& c){
    finalGame = false;
    lastY = 0;
    vehicleCrash = false;

    onPause = false;
    comeFromOptions = false;
    blink = false;
    arrival = false;
    updatedTimeCheck = false;

    minutes = 0;
    secs = 0;
    cents_second = 0;
    minutesTrip = 0;
    secsTrip = 0;
    cents_secondTrip = 0;
    timeCheck = 0;
    lap = "00:00:00";
    indexCheckPoint = 1;

    switch(typeOfVehicle){
        case 0:
            player.setVehicle(typeOfGame);
            break;
        case 1:
            player2.setVehicle(typeOfGame);
            break;
        case 2:
            player3.setVehicle(typeOfGame);
            break;
        case 3:
            player4.setVehicle(typeOfGame);
    }

    // Control the loading of the landscapes
    int nm = 0;
    // Times of each scenario
    const int times[] = {85, 58, 68, 50, 75, 69, 53, 54, 49, 48, 46, 42, 42, 41, 42};

    // Path which depends of the mode selected by the player
    string pathMode;

    switch(typeOfGame){
        case 1:
            // Out Run mode
            pathMode = "Data/Gamemodes/OutRun/LandScapes/LandScape";
            break;
        case 3:
            // Driving fury mode
            pathMode = "Data/Gamemodes/DrivingFury/LandScapes/LandScape";
            typeOfVehicle = 4;
            break;
        case 4:
            // Demarrage mode
            pathMode = "Data/Gamemodes/Derramage/LandScapes/LandScape";
            break;
        case 5:
            // Delivery mode
            pathMode = "Data/Gamemodes/Delivery/LandScapes/LandScape";
    }

    // Array of mutex to control the storing order
    mutex landScapes[15];

    for (int i = 1; i < 15; i++){
        landScapes[i].lock();
    }

    // Loop for load the maps
    for (int i = 0; i < 5; i++) {
        // Vector of landscapes
        vector<LandScape> vm;

        // Array of threads
        thread P[i + 1];

        // Load the landscapes
        for (int j = 0; j <= i; j++) {

            // Throw a thread to load the nm landscape
            P[j] = thread(loadOutRunDrivingFuryDerramageLandScape, this, ref(c), pathMode + to_string(nm + 1) + "/", nm, times[nm],
                           typeOfGame, ref(landScapes), ref(vm));

            nm++;
        }

        // Wait until all the threads have
        for (int j = 0; j <= i; j++){
            P[j].join();
        }

        // Store the map in the matrix
        maps.emplace_back(vm);
    }

    mapId = make_pair(0, 0);

    // Back door
    int bdTime = 0;
    ifstream fin("Data/backdoor.info");
    if (fin.is_open()) {
        int bdMap = 1;
        while (!fin.eof()) {
            string s;
            fin >> s;
            if (s == "MAP:" && !fin.eof()) {
                fin >> bdMap;
                if (bdMap > 0 && bdMap <= 15) {
                    for (int i = 1; i < bdMap; i++) {
                        if (mapId.second < mapId.first) {
                            mapId.second++;
                        } else {
                            mapId.second = 0;
                            mapId.first++;
                        } // Level????????????????????????
                    }
                }
            } else if (s == "TIME:" && !fin.eof()) {
                fin >> bdTime;
            }
        }
        fin.close();
    }

    currentMap = &maps[mapId.first][mapId.second];
    if (mapId.first < 4)
        currentMap->addFork(&maps[mapId.first + 1][mapId.second], &maps[mapId.first + 1][mapId.second + 1]);
    else {
        goalMap = LandScape(goalFlagger, goalEnd, typeOfGame, numberRacers);
        goalMap.setColorsLandScape(*currentMap);
        currentMap->addNewLandScape(&goalMap);
    }

    // Load the game mode hud
    loadHudGameOutRunDrivingFuryDerramage();

    score = 0;
    level = mapId.first + 1;
    time = int(float(currentMap->getTimeToPlay()) * timeMul) + bdTime;

    if (typeOfGame == 3){
        string path = "Data/Vehicles/Police/Configuration/Configuration.xml";
        string brandName, motorName;
        float max_speed, angle;

        // Load the properties of the police car
        loadVehicleProperties(path , brandName, max_speed, angle, motorName);

        // Create the properties of the police car
        player5 = Police(max_speed, SPEED_FACTOR, max_speed* ACCELERATION_INCREMENT / MAX_SPEED, 4.f, 4.f,
                         COUNTER, "Data/Vehicles/Police", 0.0f, RECTANGLE, brandName, angle, motorName);
    }

    // Start the game
    return LOADING;
}



/**
 * Check the level of difficulty and regulates the parameters
 * @param c
 */
void Game::checkDifficulty(Configuration &c) {
    int numCars = static_cast<int>(cars.size()); // Number of vehicles simultaneously
    time = int(float(time - int(timeAI)) / timeMul); // Restore original time

    float prevScoreMul = scoreMul;
    switch (c.level) {
        case PEACEFUL:
            numCars = 0;
            timeMul = 1.1f;
            scoreMul = 0.25f;
            if (c.enableAI)
                c.maxAggressiveness = 0.0f;
            break;
        case EASY:
            numCars = 5;
            timeMul = 1.1f;
            scoreMul = 0.5f;
            if (c.enableAI)
                c.maxAggressiveness = 0.25f;
            break;
        case NORMAL:
            numCars = 10;
            timeMul = 1.0f;
            scoreMul = 1.0f;
            if (c.enableAI)
                c.maxAggressiveness = 0.5f;
            break;
        case HARD:
            numCars = 15;
            timeMul = 0.9f;
            scoreMul = 1.5f;
            if (c.enableAI)
                c.maxAggressiveness = 0.75f;
            break;
        default:
            break;
    }
    if (prevScoreMul < scoreMul) // Keep the least multiplier
        scoreMul = prevScoreMul;

    if (!c.enableAI)
        c.maxAggressiveness = 0.0f;

    // Vehicles
    cars.reserve(static_cast<unsigned long>(numCars));
    if ((int)cars.size() > numCars) {
        while ((int)cars.size() > numCars)
            cars.pop_back();
    }
    else if ((int)cars.size() < numCars) {
        const int maxSprites = 6;
        const float vehicleScales[maxSprites] = {1.5f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f};
        for (int i = static_cast<int>(cars.size()); i < numCars; i++) {

            if (1 + i % maxSprites == 4){
                TrafficCar v(MAX_SPEED, SPEED_FACTOR, vehicleScales[i % maxSprites], COUNTER,
                    "Data/Vehicles/TrafficCars/Car" + to_string(1 + i % maxSprites), 0.f, -RECTANGLE * DEL_DISTANCE * 3.0f, true);
                cars.push_back(v);
            }
            else {
                TrafficCar v(MAX_SPEED, SPEED_FACTOR, vehicleScales[i % maxSprites], COUNTER,
                    "Data/Vehicles/TrafficCars/Car" + to_string(1 + i % maxSprites), 0.f, -RECTANGLE * DEL_DISTANCE * 3.0f, false);
                cars.push_back(v);
            }
        }
    }

    for (TrafficCar &v : cars){
        v.setAI(c.maxAggressiveness, c.level);
    }


    time = int(float(time) * timeMul);
    timeAI = !cars.empty() ? float(time) * c.maxAggressiveness / 3.0f : 0.0f;
    time += int(timeAI);

    if (time < 0)
        time = 0;
}



/**
 * Returns true if the player is during the game.
 * Otherwise returns false.
 * @return
 */
bool Game::isInGame() const {
    return inGame;
}



/**
 * Set the type of game selected by the player in the game modes menu
 * @param typeGame is the game selected by the player
 */
void Game::setTypeOfGame(const int typeGame){
    typeOfGame = typeGame;
}



/**
 * Returns the game mode selected by the player
 * @return
 */
int Game::typeGame() const {
    return typeOfGame;
}



/**
     * Returns the total score got by the player
     * @return
     */
unsigned long Game::getScore() const {
    return static_cast<unsigned long>(score);
}



/**
 * Returns the total minutes inverted by the player
 * @return
 */
float Game::getMinutesTrip() const {
    return minutesTrip;
}



/**
 * Returns the total seconds inverted by the player
 * @return
 */
float Game::getSecsTrip() const {
    return secsTrip;
}



/**
 * Returns the total hundredths of a second inverted by the player
 * @return
 */
float Game::getCents_SecondTrip() const {
    return cents_secondTrip;
}



/**
 * Updates the logic of the game and refreshes the screen until you leave the game.
 * @param c is the configuration of the game
 * @return
 */
State Game::playWorldTourPolePosition(Configuration &c, SoundPlayer& r) {

    if (!inGame) {
        inGame = true;
        showsInitialAnimation(c, r);
    }
    else if ((typeOfGame == 0 || typeOfGame == 2) && !comeFromOptions){
        showsInitialAnimation(c, r);
    }

    // Get the kind of terrain of the landscape
    terrain = currentMap->getTerrain();

    c.window.setKeyRepeatEnabled(false);

    // Time to change again the soundtrack
    soundtrack_delay = seconds(3.0);

    womanShot.restart();
    elapsed5 = womanShot.getElapsedTime().asSeconds();

    trafficCarSound.restart();
    elapsed7 = trafficCarSound.getElapsedTime().asSeconds();

    soundtrackClock.restart();
    elapsed13 = soundtrackClock.getElapsedTime().asSeconds();

    Vehicle::Action action;
    Vehicle::Direction direction;

    State status = PLAY_GAME;

    int localTime;

    if (!comeFromOptions){
        // Thread to control the elapsed time
        timer0 = thread(updateTimeElapsed, this);

        // Thread to control the time of the landscape
        timer1 = thread(updateTimeLandScape, this);
    }

    while (!finalGame && !arrival && c.window.isOpen()) {

        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)){
            if (e.type == Event::Closed){
                mtx.lock();
                finalGame = true;
                mtx.unlock();
                timer0.join();
                timer1.join();
                return EXIT;
            }
        }

        // Update the status of the game
        if (typeOfGame == 0){
            updateGameWorldTourStatus(c, r, action, direction, terrain);
        }
        else {
            updateGamePolePositionStatus(c, r, action, direction, terrain);
        }

        // Control the final of the game
        if (!finalGame && !arrival) {
            // Check is the game is on pause
            if (Keyboard::isKeyPressed(c.menuKey) || onPause) {
                // Pause the game
                r.soundEffects[1]->stop();
                r.soundEffects[1]->play();
                status = pause(c, r, action, direction);

                // Control the exit of the game
                if (status == OPTIONS) {
                    comeFromOptions = true;
                    mtx.lock();
                    finalGame = true;
                    mtx.unlock();
                }
                else if (status == START) {
                    mtx.lock();
                    finalGame = true;
                    mtx.unlock();
                    inGame = false;
                    r.soundTracks[r.currentSoundtrack]->stop();
                    return START;
                }
                else if (status == PLAY_GAME) {
                    r.soundTracks[r.currentSoundtrack]->play();
                    timer0 = thread(updateTimeElapsed, this);
                    timer1 = thread(updateTimeLandScape, this);
                }
                else if (status == EXIT) {
                    mtx.lock();
                    finalGame = true;
                    onPause = false;
                    mtx.unlock();
                    return EXIT;
                }
            }


            // Update the indicators
            mtx.lock();
            lap = (minutes < 10) ? "0" + to_string(int(minutes)) + ":" : to_string(int(minutes)) + ":";
            lap += (secs < 10) ? "0" + to_string(int(secs)) + ":" : to_string(int(secs)) + ":";
            int cent_sec = cents_second * 100.f;
            lap += (cent_sec < 10) ? "0" + to_string(cent_sec) : to_string(cent_sec);
            mtx.unlock();

            // Draw the HUD of the game
            showHudInterfaceWorldTourPolePosition(c);

            // Control if the music has been change by the player
            checkSoundtrackChanging(c, r);


            Sprite bufferSprite(c.w.getTexture());
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();

            localTime = time;

            if (localTime == 10) {
                r.soundEffects[26]->stop();
                r.soundEffects[26]->play();
            }

            // Check if the player has time to continue

            if (localTime == 0) {
                // Final game
                mtx.lock();
                finalGame = true;
                mtx.unlock();
            }
        }
    }

    if (!comeFromOptions){
        timer0.join();
        timer1.join();
    }

    mtx.lock();
    finalGame = false;
    if (arrival) {
        arrival = false;
        mtx.unlock();
        return CLASIFICATION;
    }
    mtx.unlock();

    if (status != OPTIONS && status != START) {
        // Draw the game over text in the console window
        showGameOver(c);
        r.soundTracks[r.currentSoundtrack]->stop();
        r.soundEffects[25]->stop();
        r.soundEffects[25]->play();
        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();
        sleep(r.soundEffects[24]->getDuration());

        bool startPressed = false;

        r.soundTracks[13]->play();
        while (!startPressed) {

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }

            startPressed = Keyboard::isKeyPressed(c.menuEnterKey);
        }
        r.soundTracks[13]->stop();
        r.soundEffects[2]->stop();
        r.soundEffects[2]->play();
        return START;
    }
    return status;
}



/**
 * Updates the logic of the game and refreshes the screen until you leave the game.
 * @param c is the configuration of the game
 * @return
 */
State Game::playOutRunDrivingFuryDerramage(Configuration &c, SoundPlayer& r) {

    if (!inGame) {
        inGame = true;
        showsInitialAnimation(c, r);
    }
    else if ((typeOfGame == 0 || typeOfGame == 2) && !comeFromOptions){
        showsInitialAnimation(c, r);
    }

    // Get the kind of terrain of the landscape
    terrain = currentMap->getTerrain();

    c.window.setKeyRepeatEnabled(false);

    // Time to change again the soundtrack
    soundtrack_delay = seconds(3.0);

    womanShot.restart();
    elapsed5 = womanShot.getElapsedTime().asSeconds();

    trafficCarSound.restart();
    elapsed7 = trafficCarSound.getElapsedTime().asSeconds();

    blinkTime.restart();
    elapsed9 = blinkTime.getElapsedTime().asSeconds();

    soundtrackClock.restart();
    elapsed13 = soundtrackClock.getElapsedTime().asSeconds();

    Vehicle::Action action;
    Vehicle::Direction direction;

    State status = PLAY_GAME;

    int localTime;

    if (!comeFromOptions){
        // Thread to control the elapsed time
        timer0 = thread(updateTimeElapsed, this);

        // Thread to control the time of the landscape
        timer1 = thread(updateTimeLandScape, this);

        // Thread to counter the score of the game
        timer2 = thread(updateScore, this);
    }

    while (!finalGame && !arrival && c.window.isOpen()) {
        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)){
            if (e.type == Event::Closed){
                mtx.lock();
                finalGame = true;
                mtx.unlock();
                timer0.join();
                timer1.join();
                timer2.join();
                return EXIT;
            }
        }

        // Update the status of the game
        if (typeOfGame == 3){
            updateGameDrivingFuryStatus(c, r, action, direction, terrain);
        }
        else {
            updateGameOutRunDerramageStatus(c, r, action, direction, terrain);
        }

        // Control the final of the game
        if (!finalGame && !arrival) {
            // Check is the game is on pause
            if (Keyboard::isKeyPressed(c.menuKey) || onPause) {
                // Pause the game
                r.soundEffects[1]->stop();
                r.soundEffects[1]->play();
                status = pause(c, r, action, direction);

                // Control the exit of the game
                if (status == OPTIONS) {
                    comeFromOptions = true;
                    mtx.lock();
                    finalGame = true;
                    mtx.unlock();
                }
                else if (status == START) {
                    mtx.lock();
                    finalGame = true;
                    mtx.unlock();
                    inGame = false;
                    r.soundTracks[r.currentSoundtrack]->stop();
                    return START;
                }
                else if (status == PLAY_GAME) {
                    r.soundTracks[r.currentSoundtrack]->play();
                    timer0 = thread(updateTimeElapsed, this);
                    timer1 = thread(updateTimeLandScape, this);
                    timer2 = thread(updateScore, this);
                }
                else if (status == EXIT) {
                    mtx.lock();
                    finalGame = true;
                    onPause = false;
                    mtx.unlock();
                    return EXIT;
                }
            }

            // Update the indicators
            mtx.lock();
            lap = (minutes < 10) ? "0" + to_string(int(minutes)) + ":" : to_string(int(minutes)) + ":";
            lap += (secs < 10) ? "0" + to_string(int(secs)) + ":" : to_string(int(secs)) + ":";
            int cent_sec = cents_second * 100.f;
            lap += (cent_sec < 10) ? "0" + to_string(cent_sec) : to_string(cent_sec);
            mtx.unlock();

            // Draw the HUD of the game
            showHudInterfaceOutRunDrivingFuryDerramage(c);

            // Control if the music has been change by the player
            checkSoundtrackChanging(c, r);


            Sprite bufferSprite(c.w.getTexture());
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();

            mtx.lock();
            localTime = time;
            mtx.unlock();

            if (localTime == 10) {
                r.soundEffects[26]->stop();
                r.soundEffects[26]->play();
            }

            // Check if the player has time to continue

            if (localTime == 0) {
                // Final game
                mtx.lock();
                finalGame = true;
                mtx.unlock();
            }
        }
    }

    if (!comeFromOptions){
        timer0.join();
        timer1.join();
        timer2.join();
    }

    mtx.lock();
    finalGame = false;
    if (arrival) {
        arrival = false;
        mtx.unlock();
        // World tour and Pole Position modes
        return RANKING;
    }
    mtx.unlock();

    if (status != OPTIONS && status != START) {
        // Draw the game over text in the console window
        showGameOver(c);
        r.soundTracks[r.currentSoundtrack]->stop();
        r.soundEffects[25]->stop();
        r.soundEffects[25]->play();
        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();
        sleep(r.soundEffects[24]->getDuration());

        bool startPressed = false;
        r.soundTracks[13]->play();

        while (!startPressed) {

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }

            startPressed = Keyboard::isKeyPressed(c.menuEnterKey);
        }
        r.soundTracks[13]->stop();
        r.soundEffects[2]->stop();
        r.soundEffects[2]->play();
        return START;
    }
    return status;
}



/**
 * Stops the game
 * @param c is the configuration of the game
 * @param a is the last action done by the player
 * @param d is the last direction done by the player
 * @return
 */
State Game::showsInitialAnimation(Configuration &c, SoundPlayer& r) {

    int flagger, semaphore;

    if (indexLandScape == 0){
        r.soundTracks[r.currentSoundtrack]->stop();
        startMap = new LandScape(*currentMap, flagger, semaphore, typeOfGame, numberRacers);
        startMap->addNewLandScape(currentMap);
        startMap->setColorsLandScape(*currentMap);

        if (typeOfGame == 0){
            int bdTime = 0;
            time = int(float(currentMap->getTimeToPlay()) * timeMul) + bdTime;
            goalMap = LandScape(goalFlagger, goalEnd, typeOfGame, numberRacers);
            goalMap.setColorsLandScape(*currentMap);
            currentMap->addNewLandScape(&goalMap);
        }
        else if (typeOfGame == 2){
            if (numberLaps == 1){
                goalMap = LandScape(goalFlagger, goalEnd, typeOfGame, numberRacers);
                goalMap.setColorsLandScape(*currentMap);
                currentMap->addNewLandScape(&goalMap);
            }
            else {
                middleMap = LandScape(*currentMap, typeOfGame, numberRacers);
                middleMap.setColorsLandScape(*currentMap);
                currentMap->addNewLandScape(&middleMap);
            }
        }
        currentMap = startMap;
    }
    else {
        LandScape *initMap = new LandScape(*currentMap, flagger, semaphore, typeOfGame, numberRacers);
        initMap->addNewLandScape(currentMap);
        initMap->setColorsLandScape(*currentMap);

        if (typeOfGame == 0){
            goalMap = LandScape(goalFlagger, goalEnd, typeOfGame, numberRacers);
            goalMap.setColorsLandScape(*currentMap);
            currentMap->addNewLandScape(&goalMap);
        }
        currentMap = initMap;
    }

    checkDifficulty(c);

    // Semaphore and flagger
    currentMap->addMapElelementIndex(flagger, false, -1);
    int ms = 1000;

    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

     // Creation of the panel rectangle of the menu
    RectangleShape blackShape;
    blackShape.setPosition(0, 0);
    blackShape.setSize(sf::Vector2f(c.w.getSize().x, c.w.getSize().y));

    // Draw the landscape animation
    for (int i = 255; i >= 0; i -= 15){

        // Draw the landscape
        currentMap->drawLandScape(c, cars, rivals, typeOfGame);

        // Draw the vehicle
        switch(typeOfVehicle){
            case 0:
                player.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player.getPosY()), -1);
                break;
            case 1:
                player2.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player2.getPosY()), -1);
                break;
            case 2:
                player3.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player3.getPosY()), -1);
                break;
            case 3:
                player4.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player4.getPosY()), -1);
                break;
            case 4:
                player5.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player5.getPosY()), -1);
        }

        // Draw the HUD of the game
        if (typeOfGame == 0 || typeOfGame == 2){
            showHudInterfaceWorldTourPolePosition(c);
        }
        else {
            showHudInterfaceOutRunDrivingFuryDerramage(c);
        }

        blackShape.setFillColor(Color(0, 0, 0, i));
        c.w.draw(blackShape);

        bufferSprite.setTexture(c.w.getTexture(), true);
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();
        sleep(milliseconds(30));
    }



    // Check the initial sound to reproduce
    switch(typeOfGame){
        case 0:
            r.soundEffects[39]->stop();
            r.soundEffects[39]->play();
            while (r.soundEffects[39]->getStatus() != SoundSource::Stopped){}
            break;
        case 1:
            r.soundEffects[38]->stop();
            r.soundEffects[38]->play();
            while (r.soundEffects[38]->getStatus() != SoundSource::Stopped){}
            break;
        case 2:
            r.soundEffects[57]->stop();
            r.soundEffects[57]->play();
            while (r.soundEffects[57]->getStatus() != SoundSource::Stopped){}
            break;
        case 3:
            r.soundEffects[37]->stop();
            r.soundEffects[37]->play();
            while (r.soundEffects[37]->getStatus() != SoundSource::Stopped){}
            break;
        case 4:
            r.soundEffects[58]->stop();
            r.soundEffects[58]->play();
            while (r.soundEffects[58]->getStatus() != SoundSource::Stopped){}
    }

    // Reproduce motor sounds
    if (typeOfVehicle != 0){
        r.soundEffects[28]->stop();
        r.soundEffects[28]->play();
    }
    else {
        r.soundEffects[68]->stop();
        r.soundEffects[68]->play();
    }

    // Draw the semaphore
    if (typeOfGame == 0 || (typeOfGame == 2 && numberRacers >= 1)){
        Sprite s;
        s.setTexture(textures[4], true);
        s.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
        s.setPosition((float)c.w.getSize().x / 2.f - s.getLocalBounds().width / 2.f,
                             c.w.getSize().y / 2.f - 180.0f * c.screenScale);
        c.w.draw(s);

        bufferSprite.setTexture(c.w.getTexture(), true);
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();
        sleep(milliseconds(800));
    }

    switch(typeOfVehicle){
        case 0:
            player.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player.getPosY()), -1);
            break;
        case 1:
            player2.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player2.getPosY()), -1);
            break;
        case 2:
            player3.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player3.getPosY()), -1);
            break;
        case 3:
            player4.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player4.getPosY()), -1);
            break;
        case 4:
            player5.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player5.getPosY()), -1);
    }



    // Detect the possible events
    Event e;

    for (int i = 0; i < 3; i++) {

        // Detect the possible events
        while (c.window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return EXIT;
            }
        }

        // Draw map
        c.w.clear();
        currentMap->drawLandScape(c, cars, rivals, typeOfGame);

        switch(typeOfVehicle){
            case 0:
                player.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player.getPosY()), -1);
                break;
            case 1:
                player2.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player2.getPosY()), -1);
                break;
            case 2:
                player3.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player3.getPosY()), -1);
                break;
            case 3:
                player4.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player4.getPosY()), -1);
                break;
            case 4:
                player5.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player5.getPosY()), -1);
        }


        // Draw the HUD of the game
        if (typeOfGame == 0 || typeOfGame == 2){
            showHudInterfaceWorldTourPolePosition(c);
        }
        else {
            showHudInterfaceOutRunDrivingFuryDerramage(c);
        }

        // Draw the semaphore
        if (typeOfGame == 0 || (typeOfGame == 2 && numberRacers >= 1)){
            Sprite s;
            s.setTexture(textures[4 + i], true);
            s.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
            s.setPosition((float)c.w.getSize().x / 2.f - s.getLocalBounds().width / 2.f,
                                 c.w.getSize().y / 2.f - 180.0f * c.screenScale);
            c.w.draw(s);
        }

        bufferSprite.setTexture(c.w.getTexture(), true);
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

        // Flagger
        if (i == 2) {
            for (; ms > 0; ms -= 200) {
                sleep(milliseconds(200));

                currentMap->addMapElelementIndex(flagger, false);

                // Draw map
                c.w.clear();
                currentMap->drawLandScape(c, cars, rivals, typeOfGame);

                switch(typeOfVehicle){
                    case 0:
                        player.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player.getPosY()), -1);
                        break;
                    case 1:
                        player2.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player2.getPosY()), -1);
                        break;
                    case 2:
                        player3.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player3.getPosY()), -1);
                        break;
                    case 3:
                        player4.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player4.getPosY()), -1);
                        break;
                    case 4:
                        player5.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player5.getPosY()), -1);
                }

                // Draw the HUD of the game
                if (typeOfGame == 0 || typeOfGame == 2){
                    showHudInterfaceWorldTourPolePosition(c);
                }
                else {
                    showHudInterfaceOutRunDrivingFuryDerramage(c);
                }

                // Draw the semaphore
                if (typeOfGame == 0 || (typeOfGame == 2 && numberRacers >= 1)){
                    Sprite s;
                    s.setTexture(textures[4 + i], true);
                    s.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
                    s.setPosition((float)c.w.getSize().x / 2.f - s.getLocalBounds().width / 2.f,
                                         c.w.getSize().y / 2.f - 180.0f * c.screenScale);
                    c.w.draw(s);
                }

                bufferSprite.setTexture(c.w.getTexture(), true);
                c.w.display();
                c.window.draw(bufferSprite);
                c.window.display();
            }
        }

        // Change semaphore state
        if (ms > 0) {
            sleep(milliseconds(ms));
            r.soundEffects[4]->stop();
            r.soundEffects[4]->play();
        }
        currentMap->addMapElelementIndex(semaphore, false);
        r.soundEffects[5]->stop();
        r.soundEffects[5]->play();

    }

    // Draw the semaphore
    if (typeOfGame == 0 || (typeOfGame == 2 && numberRacers >= 1)){
        Sprite s;
        s.setTexture(textures[7], true);
        s.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
        s.setPosition((float)c.w.getSize().x / 2.f - s.getLocalBounds().width / 2.f,
                             c.w.getSize().y / 2.f - 180.0f * c.screenScale);
        c.w.draw(s);

        bufferSprite.setTexture(c.w.getTexture(), true);
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();
    }


    currentMap->addMapElelementIndex(flagger, false, -1);
    r.soundTracks[r.currentSoundtrack]->play();

    // Reproduce the cars running
    if ((typeOfGame == 0 || typeOfGame == 2) && numberRacers > 0){
        switch(typeOfVehicle){
            case 0:
                r.soundEffects[30]->stop();
                r.soundEffects[30]->play();
                break;
            case 1:
                r.soundEffects[28]->stop();
                r.soundEffects[88]->stop();
                r.soundEffects[88]->play();
                break;
            case 2:
                r.soundEffects[28]->stop();
                r.soundEffects[89]->stop();
                r.soundEffects[89]->play();
                break;
            case 3:
                r.soundEffects[28]->stop();
                r.soundEffects[90]->stop();
                r.soundEffects[90]->play();
        }

        for (RivalCar rival : rivals){
            rival.setSmoking();
        }
    }

    return PLAY_GAME;
}



/**
 * Shows the goal animation when the player is in the start point
 * @param c is the configuration of the game
 */
State Game::showsGoalAnimation(Configuration &c, SoundPlayer& r) {
    // Stop music level
    r.soundTracks[r.currentSoundtrack]->stop();

    // Position of the player in the race
    string place;
    Text positionText, congratulationsText, totalTimeText;

    float elapsed1, elapsed2;
    Clock blinkClcok;
    Time blink_delay = seconds(0.5f);

    blinkClcok.restart().asSeconds();
    elapsed1 = blinkClcok.restart().asSeconds();
    bool blink = true;

    if (typeOfGame == 0 || typeOfGame == 2){

        // Get the position of the player in the race
        switch(posArrival){
            case 1:
                place = "FIRST PLACE!";
                break;
            case 2:
                place = "SECOND PLACE!";
                break;
            case 3:
                place = "THIRD PLACE!";
                break;
            case 4:
                place = "FOURTH PLACE";
                break;
            case 5:
                place = "FIFTH PLACE";
                break;
            case 6:
                place = "SIXTH PLACE";
                break;
            case 7:
                place = "SEVENTH PLACE";
                break;
            case 8:
                place = "EIGHT PLACE";
        }

        // Store the position
        positionText.setString(place);
        positionText.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
        positionText.setFont(c.fontTimeToPlay);
        positionText.setStyle(Text::Bold);
        positionText.setFillColor(Color::White);
        positionText.setOutlineColor(Color::Black);
        positionText.setOutlineThickness(5.0f * c.screenScale);
        positionText.setPosition((c.w.getSize().x / 2.f) - (positionText.getLocalBounds().width / 2.f),
                                 c.w.getSize().y / 2.f - 15.f * c.screenScale);

        // GoalSound
        switch(posArrival){
            case 1:
                r.soundEffects[43]->stop();
                r.soundEffects[43]->play();
                break;
            case 2:
            case 3:
                r.soundEffects[44]->stop();
                r.soundEffects[44]->play();
                break;
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                r.soundEffects[45]->stop();
                r.soundEffects[45]->play();
        }
    }
    else if (typeOfGame == 1){
        r.soundEffects[54]->stop();
        r.soundEffects[54]->play();

    }

    // Hide enemies
    for (TrafficCar &v : cars)
        v.setPosition(v.getPosX(), -RECTANGLE);

    int increment = 0;
    float currentTime = gameClockTime.getElapsedTime().asMilliseconds();

    // Bonus seconds
    int decsTime = time * 10;
    int seconds = decsTime / 10;
    int decs_second = decsTime % 10;

    bonus.restart();
    elapsed11 = bonus.getElapsedTime().asSeconds(); // TODO: Esta marca solo se actualiza aquí ?????

    int position = 0;

    switch(typeOfVehicle){
        case 0:
            player.setPosition(player.getPosX(), 5.f);
            position = int(player.getPosY());
            break;
        case 1:
            player2.setPosition(player2.getPosX(), 5.f);
            position = int(player2.getPosY());
            break;
        case 2:
            player3.setPosition(player3.getPosX(), 5.f);
            position = int(player3.getPosY());
            break;
        case 3:
            player4.setPosition(player4.getPosX(), 5.f);
            position = int(player4.getPosY());
            break;
        case 4:
            player5.setPosition(player5.getPosX(), 5.f);
            position = int(player5.getPosY());
    }

    // claps
    if (posArrival <= 3){
        r.soundEffects[29]->stop();
        r.soundEffects[29]->play();
    }

    float positionX = 0.f, positionY = 0.f;

    while (position < goalEnd) {

        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                mtx.lock();
                finalGame = true;
                mtx.unlock();
                timer0.join();
                timer1.join();
                if (typeOfGame != 0 && typeOfGame != 2){
                    timer2.join();
                }
                return EXIT;
            }
        }

        switch(typeOfVehicle){
            case 0:
                positionX = player.getPosX();
                positionY = player.getPosY();
                break;
            case 1:
                positionX = player2.getPosX();
                positionY = player2.getPosY();
                break;
            case 2:
                positionX = player3.getPosX();
                positionY = player3.getPosY();
                break;
            case 3:
                positionX = player4.getPosX();
                positionY = player4.getPosY();
                break;
            case 4:
                positionX = player5.getPosX();
                positionY = player5.getPosY();
        }

        // Update camera
        currentMap->updateCamera(positionX, positionY - RECTANGLE);

        // Draw map
        c.w.clear();
        currentMap->drawLandScape(c, cars, rivals, typeOfGame);

        switch(typeOfVehicle){
            case 0:
                player.setPosition(player.getPosX(), player.getPosY() + 1);
                player.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                        currentMap->getElevation(player.getPosY()), currentMap->getTerrain(), false);
                break;
            case 1:
                player2.setPosition(player2.getPosX(), player2.getPosY() + 1);
                player2.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                        currentMap->getElevation(player2.getPosY()), currentMap->getTerrain(), false);
                break;
            case 2:
                player3.setPosition(player3.getPosX(), player3.getPosY() + 1);
                player3.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                        currentMap->getElevation(player3.getPosY()), currentMap->getTerrain(), false);
                break;
            case 3:
                player4.setPosition(player4.getPosX(), player4.getPosY() + 1);
                player4.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                        currentMap->getElevation(player4.getPosY()), currentMap->getTerrain(), false);
                break;
            case 4:
                player5.setPosition(player5.getPosX(), player5.getPosY() + 1);
                player5.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                        currentMap->getElevation(player5.getPosY()), currentMap->getTerrain(), false);
        }

        if (typeOfGame == 0 || typeOfGame == 2){

            elapsed2 = blinkClcok.getElapsedTime().asSeconds();
            // Change the color of the main text
            if (elapsed2 - elapsed1 >= blink_delay.asSeconds()) {
                blink = !blink;
                blinkClcok.restart();
            }
            if (blink) {
                positionText.setFillColor(c.colorTexts[0]);
                positionText.setOutlineColor(c.colorBorders[0]);
            }
            else {
                positionText.setFillColor(Color::Transparent);
                positionText.setOutlineColor(Color::Transparent);
            }


            c.w.draw(positionText);
        }

        // Flager animation
        if (gameClockTime.getElapsedTime().asMilliseconds() - currentTime >= 200.0f) {
            if (increment >= 5) {
                increment = 0;
                currentMap->addMapElelementIndex(goalFlagger, false, -5);
            }
            else {
                currentMap->addMapElelementIndex(goalFlagger, false);
                increment++;
            }
            currentTime = gameClockTime.getElapsedTime().asMilliseconds();
        }

        if (typeOfGame == 1){

            elapsed12 = bonus.getElapsedTime().asSeconds();

            // Check if a second has passed between both timestamps
            if (elapsed12 - elapsed11 >= bonus_delay.asSeconds()) {
                // Decrement one Tenth of a second

                if (decsTime > 0) {
                    decsTime--;

                    seconds = decsTime / 10;
                    // Decs per second
                    decs_second = decsTime % 10;
                }

                score += int(scoreMul * BONIFICATION / 10.0f); // Bonif. per dec.

                bonus.restart();
            }

            // Draw the bonus points
            drawBonus(c, seconds, decs_second);
        }

        switch(typeOfVehicle){
            case 0:
                position = int(player.getPosY());
                break;
            case 1:
                position = int(player2.getPosY());
                break;
            case 2:
                position = int(player3.getPosY());
                break;
            case 3:
                position = int(player4.getPosY());
                break;
            case 4:
                position = int(player5.getPosY());
        }

        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();
    }

    // Reproduce the music soundtrack
    if (typeOfGame == 0 || typeOfGame == 2){
        r.soundTracks[15]->play();
    }

    for (int i = 0; i <= 255; i += 5){

        // Update camera
        currentMap->updateCamera(positionX, positionY - RECTANGLE);

        RectangleShape shape;
        shape.setPosition(0, 0);
        shape.setSize(sf::Vector2f(c.w.getSize().x, c.w.getSize().y));
        shape.setFillColor(Color(0, 0, 0, i));
        c.w.draw(shape);

        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

        sleep(milliseconds(20));
    }

    if (typeOfGame == 0 || typeOfGame == 2){
        return CLASIFICATION;
    }
    else {
        return RANKING;
    }
}



/**
 * Updates the logic of the landscapes and vehicles and draws the current landscape fragment
 * with the vehicles on the screen.
 * @param c is the configuration of the game
 */
void Game::updateGameWorldTourStatus(Configuration &c, SoundPlayer& r, Vehicle::Action &action,
                                     Vehicle::Direction &direction, int& terrain)
{

    // Update camera
    switch(typeOfVehicle){
        case 0:
            currentMap->updateCamera(player.getPosX(), player.getPosY() - RECTANGLE);
            break;
        case 1:
            currentMap->updateCamera(player2.getPosX(), player2.getPosY() - RECTANGLE);
            break;
        case 2:
            currentMap->updateCamera(player3.getPosX(), player3.getPosY() - RECTANGLE);
            break;
        case 3:
            currentMap->updateCamera(player4.getPosX(), player4.getPosY() - RECTANGLE);
    }

    // World tour and pole position modes
    if (currentMap->isOutSideLandScape()) {
        // Update player and vehicle positions
        switch(typeOfVehicle){
            case 0:
                player.setPosition(player.getPosX() + currentMap->getOffsetX(), player.getPosY() - currentMap->getMaxY());
                break;
            case 1:
                player2.setPosition(player2.getPosX() + currentMap->getOffsetX(), player2.getPosY() - currentMap->getMaxY());
                break;
            case 2:
                player3.setPosition(player3.getPosX() + currentMap->getOffsetX(), player3.getPosY() - currentMap->getMaxY());
                break;
            case 3:
                player4.setPosition(player4.getPosX() + currentMap->getOffsetX(), player4.getPosY() - currentMap->getMaxY());
        }

        for (TrafficCar &v : cars)
            v.setPosition(v.getPosX(), v.getPosY() - currentMap->getMaxY());

        for (RivalCar &v : rivals)
            v.setPosition(v.getPosX(), v.getPosY() - currentMap->getMaxY());

        // Update to the map
        if (level < 0){
            level++;
            currentMap = currentMap->getNextLeft();
            checkPointPositions = currentMap->getCheckPointPositions();
        }
        else {
            currentMap = &goalMap;
        }
    }
    else {
        // The player is still inside the landscape
        float pos = 0.f, halfspeed = 0.f;

        switch(typeOfVehicle){
            case 0:
                pos = player.getPosY();
                halfspeed = player.getHalfMaxSpeed();
                break;
            case 1:
                pos = player2.getPosY();
                halfspeed = player2.getHalfMaxSpeed();
                break;
            case 2:
                pos = player3.getPosY();
                halfspeed = player3.getHalfMaxSpeed();
                break;
            case 3:
                pos = player4.getPosY();
                halfspeed = player4.getHalfMaxSpeed();
        }

        if (pos >= checkPointPositions[indexCheckPoint - 1]){
            // Increment the next checkpoint to pass
            if (indexCheckPoint % 4 != 0){
                indexCheckPoint++;
                // Initialize the clock again

                // Reproduce checkpoint sound effect
                r.soundEffects[24]->stop();
                r.soundEffects[24]->play();

                // Add the time to complete the landscape
                if (indexCheckPoint != 4){
                    time += ((checkPointPositions[indexCheckPoint - 1] - pos) / (halfspeed * 65.f)) ;
                }
                else {
                    time += ((currentMap->getMaxY() - pos) / (halfspeed * 60.f));
                }
            }
        }
    }
    if (currentMap->isFinalLandScape()) {
        State status = showsGoalAnimation(c, r);
        if (status == EXIT) {
            exit(1);
        }
        mtx.lock();
        arrival = true;
        mtx.unlock();
    }

    if (!finalGame && !arrival) {
        // Update and prepare cars to draw
        if (lastY <= currentMap->getCameraPosY() + float(c.renderLen)){
            lastY = currentMap->getCameraPosY() + float(c.renderLen);
        }
        for (TrafficCar &v : cars) {
            if (currentMap->inFork(v.getPosY())) {
                v.setPosition(v.getPosX(), -RECTANGLE * DEL_DISTANCE * 3.0f);
            }
            else if (v.getPosY() + DEL_DISTANCE < currentMap->getCameraPosY()) {
                v.update(lastY, lastY + float(c.renderLen) / DENSITY_SPACE, c.maxAggressiveness, c.level);
                lastY = v.getPosY() + DISTANCE_TRESHOLD * RECTANGLE;
            }

            float posY = v.getPosY();
            v.draw(currentMap->getElevation(posY), currentMap->getCameraPosX());
        }

        Vehicle::Action a = Vehicle::CRASH;

        float positionX = 0.f, positionY = 0.f, speedPlayer = 0.f;

        switch(typeOfVehicle){
            case 0:
                positionX = player.getPosX();
                positionY = player.getPosY();
                speedPlayer = player.getSpeed();
                break;
            case 1:
                positionX = player2.getPosX();
                positionY = player2.getPosY();
                speedPlayer = player2.getSpeed();
                break;
            case 2:
                positionX = player3.getPosX();
                positionY = player3.getPosY();
                speedPlayer = player3.getSpeed();
                break;
            case 3:
                positionX = player4.getPosX();
                positionY = player4.getPosY();
                speedPlayer = player4.getSpeed();
        }

        // Clear the ranking of the rivals for updating
        rankingVehicles.clear();

        // Update and prepare racers to draw
        for (RivalCar &v : rivals) {
            float directionCurve = currentMap->getCurveCoefficient(v.getPosY());

            v.update(c, lastY, lastY + float(c.renderLen) / DENSITY_SPACE, c.maxAggressiveness, a, directionCurve,
                     c.level, positionX, positionY, speedPlayer);


            lastY = v.getPosY() + DISTANCE_TRESHOLD * RECTANGLE;

            float posY = v.getPosY();

            vehicleCrash = false;
            float crashPos;

            // Store the new position of the vehicle
            rankingVehicles.push_back(posY);

            // Check if the current rival car has crashed with a traffic car
            for (int i = 0; !vehicleCrash && i < (int)rivals.size(); i++){
                vehicleCrash = cars[i].hasCrashed(v.getPreviousY(), posY,
                                                  v.getMinScreenX(), v.getMaxScreenX(), crashPos);
            }

            if (vehicleCrash) {
                // Determine the type of collision
                v.setPosition(v.getPosX(), crashPos);
                v.hitControl(vehicleCrash, r);
                a = Vehicle::CRASH;
            }

            // Draw the vehicle
            v.draw(a, currentMap->getElevation(posY));

            vehicleCrash = false;

        // Check if the player has crash with any rival car
            switch(typeOfVehicle){
                case 0:

                    vehicleCrash = v.hasCrashed(player.getPosY(), player.getPreviousY(),
                                                player.getMinScreenX(), player.getMaxScreenX(), crashPos);

                    // Check it has been crash between player and rival
                    if (vehicleCrash){
                        if (player.getPreviousX() > v.getPreviousX()){
                            player.setPosition(player.getPosX() + 1.5f * player.getAngle(), player.getPosY() - 10.f);
                        }
                        else if (player.getPreviousX() < v.getPreviousX()){
                            player.setPosition(player.getPosX() - 1.5f * player.getAngle(), player.getPosY() - 10.f);
                        }
                    }

                    // Reproduce sounds of collision
                    if (vehicleCrash){
                        // Voice sound
                        r.soundEffects[69]->stop();
                        r.soundEffects[70]->stop();
                        r.soundEffects[71]->stop();
                        r.soundEffects[72]->stop();
                        r.soundEffects[73]->stop();
                        r.soundEffects[74]->stop();
                        r.soundEffects[75]->stop();
                        r.soundEffects[rand_generator_int(69, 75)]->play();

                        // Collision sound
                        r.soundEffects[76]->stop();
                        r.soundEffects[77]->stop();
                        r.soundEffects[78]->stop();
                        r.soundEffects[79]->stop();
                        r.soundEffects[80]->stop();
                        r.soundEffects[81]->stop();
                        r.soundEffects[rand_generator_int(76, 81)]->play();
                    }
                    break;
                case 1:
                    vehicleCrash = v.hasCrashed(player2.getPosY(), player2.getPreviousY(),
                                                player2.getMinScreenX(), player2.getMaxScreenX(), crashPos);

                    if (vehicleCrash){
                        if (player2.getPreviousX() > v.getPreviousX()){
                            player2.setPosition(player.getPosX() + 1.5f * player2.getAngle(), player2.getPosY() - 10.f);
                        }
                        else if (player.getPreviousX() < v.getPreviousX()){
                            player2.setPosition(player.getPosX() - 1.5f * player2.getAngle(), player2.getPosY() - 10.f);
                        }
                        r.soundEffects[87]->stop();
                        r.soundEffects[87]->play();
                    }
                    break;
                case 2:
                    vehicleCrash = v.hasCrashed(player3.getPosY(), player3.getPreviousY(),
                                                player3.getMinScreenX(), player3.getMaxScreenX(), crashPos);

                    if (vehicleCrash){
                        if (player3.getPreviousX() > v.getPreviousX()){
                            player3.setPosition(player.getPosX() + 1.5f * player3.getAngle(), player3.getPosY() - 10.f);
                        }
                        else if (player.getPreviousX() < v.getPreviousX()){
                            player3.setPosition(player.getPosX() - 1.5f * player3.getAngle(), player3.getPosY() - 10.f);
                        }
                        r.soundEffects[87]->stop();
                        r.soundEffects[87]->play();
                    }
                    break;
                case 3:
                    vehicleCrash = v.hasCrashed(player4.getPosY(), player4.getPreviousY(),
                                                player4.getMinScreenX(), player4.getMaxScreenX(), crashPos);

                    if (vehicleCrash){
                        if (player4.getPreviousX() > v.getPreviousX()){
                            player4.setPosition(player.getPosX() + 1.5f * player4.getAngle(), player4.getPosY() - 10.f);
                        }
                        else if (player.getPreviousX() < v.getPreviousX()){
                            player4.setPosition(player.getPosX() - 1.5f * player4.getAngle(), player4.getPosY() - 10.f);
                        }
                        r.soundEffects[87]->stop();
                        r.soundEffects[87]->play();
                    }
            }
        }

        // Order the rivals cars of the race to build a temporary ranking
        sort(rankingVehicles.begin(), rankingVehicles.end(), ascendingRanking);

        // Get the new position of the player in the race
        posArrival = findPlayerPositionRanking(positionY);

        // Draw map with cars
        c.w.clear();
        currentMap->drawLandScape(c, cars, rivals, typeOfGame);

        // Player update and draw
        action = Vehicle::CRASH;
        direction = Vehicle::RIGHT;

        switch(typeOfVehicle){
            case 0:
                if (!player.isCrashing()) { // If not has crashed
                    action = player.accelerationControl(c, currentMap->isOutSideRoad(player.getPosX(), player.getPosY()));
                    direction = player.rotationControl(c, currentMap->getCurveCoefficient(player.getPosY()),
                                                          currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                }
                else {
                    player.hitControl(vehicleCrash);
                }

                player.draw(c, r, action, direction, currentMap->getElevation(player.getPosY()), terrain);

                if (!player.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player.getPreviousY(), player.getPosY(), player.getPosX(),
                                                        player.getMinScreenX(), player.getMaxScreenX(), crashPos, typeOfGame);
                    if (!crash)
                        for (int i = 0; !vehicleCrash && i < (int)cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player.getPreviousY(), player.getPosY(),
                                                              player.getMinScreenX(), player.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        player.setPosition(player.getPosX(), crashPos);
                        player.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player.draw(c, r, action, direction, currentMap->getElevation(player.getPosY()), terrain);
                    }
                }

                for (TrafficCar &v : cars)
                    v.autoControl(c, player.getPosX(), player.getPosY());

                break;
            case 1:
                if (!player2.isCrashing()) { // If not has crashed
                    action = player2.accelerationControl(c, currentMap->isOutSideRoad(player2.getPosX(), player2.getPosY()));
                    direction = player2.rotationControl(c, currentMap->getCurveCoefficient(player2.getPosY()),
                                                           currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                }
                else {
                    player2.hitControl(vehicleCrash);
                }

                player2.draw(c, r, action, direction, currentMap->getElevation(player2.getPosY()), terrain);

                if (!player2.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player2.getPreviousY(), player2.getPosY(), player2.getPosX(),
                                                        player2.getMinScreenX(), player2.getMaxScreenX(), crashPos, typeOfGame);
                    if (!crash)
                        for (int i = 0; !vehicleCrash && i < (int)cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player2.getPreviousY(), player2.getPosY(),
                                                              player2.getMinScreenX(), player2.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        player2.setModeCollision();
                        player2.setPosition(player2.getPosX(), crashPos);
                        player2.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player2.draw(c, r, action, direction, currentMap->getElevation(player2.getPosY()), terrain);
                    }
                }

                for (TrafficCar &v : cars)
                    v.autoControl(c, player2.getPosX(), player2.getPosY());

                for (RivalCar &v : rivals)
                    v.autoControl(c, player.getPosX(), player.getPosY());
                break;
            case 2:
                if (!player3.isCrashing()) { // If not has crashed
                    action = player3.accelerationControl(c, currentMap->isOutSideRoad(player3.getPosX(), player3.getPosY()));
                    direction = player3.rotationControl(c, currentMap->getCurveCoefficient(player3.getPosY()),
                                                           currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                }
                else {
                    player3.hitControl(vehicleCrash);
                }

                player3.draw(c, r, action, direction, currentMap->getElevation(player3.getPosY()), terrain);

                if (!player3.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player3.getPreviousY(), player3.getPosY(), player3.getPosX(),
                                                        player3.getMinScreenX(), player3.getMaxScreenX(), crashPos, typeOfGame);
                    if (!crash)
                        for (int i = 0; !vehicleCrash && i < (int)cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player3.getPreviousY(), player3.getPosY(),
                                                              player3.getMinScreenX(), player3.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        player3.setModeCollision();
                        player3.setPosition(player3.getPosX(), crashPos);
                        player3.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player3.draw(c, r, action, direction, currentMap->getElevation(player3.getPosY()), terrain);
                    }
                }

                for (TrafficCar &v : cars)
                    v.autoControl(c, player3.getPosX(), player3.getPosY());

                for (RivalCar &v : rivals)
                    v.autoControl(c, player.getPosX(), player.getPosY());
                break;
            case 3:
                if (!player4.isCrashing()) { // If not has crashed
                    action = player4.accelerationControl(c, currentMap->isOutSideRoad(player4.getPosX(), player4.getPosY()));
                    direction = player4.rotationControl(c, currentMap->getCurveCoefficient(player4.getPosY()),
                                                           currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                }
                else {
                    player4.hitControl(vehicleCrash);
                }

                player4.draw(c, r, action, direction, currentMap->getElevation(player4.getPosY()), terrain);

                if (!player4.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player4.getPreviousY(), player4.getPosY(), player4.getPosX(),
                                                        player4.getMinScreenX(), player4.getMaxScreenX(), crashPos, typeOfGame);
                    if (!crash)
                        for (int i = 0; !vehicleCrash && i < (int)cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player4.getPreviousY(), player4.getPosY(),
                                                              player4.getMinScreenX(), player4.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        player4.setModeCollision();
                        player4.setPosition(player4.getPosX(), crashPos);
                        player4.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player4.draw(c, r, action, direction, currentMap->getElevation(player4.getPosY()), terrain);
                    }
                }

                for (TrafficCar &v : cars)
                    v.autoControl(c, player4.getPosX(), player4.getPosY());

                for (RivalCar &v : rivals)
                    v.autoControl(c, player.getPosX(), player.getPosY());
        }
        if (!finalGame && !arrival){
            // Check if enemies are displayed on the screen
            for (TrafficCar &v : cars) {
                float distX, distY;

                bool visible = true;

                switch(typeOfVehicle){
                    case 0:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player.getPosX(), player.getPosY(), distX, distY);
                        break;
                    case 1:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player2.getPosX(), player2.getPosY(), distX, distY);
                        break;
                    case 2:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player3.getPosX(), player3.getPosY(), distX, distY);
                        break;
                    case 3:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player4.getPosX(), player4.getPosY(), distX, distY);
                }

                if (visible) {
                    if (distY <= 20.f && distX <= 0.3f) {
                        // Thread with sound of the woman
                        elapsed6 = womanShot.getElapsedTime().asSeconds();
                        if (elapsed6 - elapsed5 >= woman_delay.asSeconds()) {
                            // WomanSound
                            r.soundEffects[13]->stop();
                            r.soundEffects[14]->stop();
                            r.soundEffects[15]->stop();
                            r.soundEffects[rand_generator_int(13, 15)]->play();
                            womanShot.restart();
                        }
                    }
                    if (distY <= 30.f && distX <= 1.2f) {
                        // Thread with sound of the woman
                        elapsed8 = trafficCarSound.getElapsedTime().asSeconds();
                        if (elapsed8 - elapsed7 >= traffic_delay.asSeconds()) {
                            if (v.getIsTruck()){
                                // Truck sound
                                r.soundEffects[85]->stop();
                                r.soundEffects[86]->stop();
                                r.soundEffects[rand_generator_int(85, 86)]->play();
                            }
                            else {
                                // Traffic car sound
                                r.soundEffects[20]->stop();
                                r.soundEffects[21]->stop();
                                r.soundEffects[22]->stop();
                                r.soundEffects[rand_generator_int(20, 22)]->play();

                                r.soundEffects[59]->stop();
                                r.soundEffects[60]->stop();
                                r.soundEffects[61]->stop();
                                r.soundEffects[rand_generator_int(59, 61)]->play();
                            }
                            trafficCarSound.restart();
                        }
                    }
                }
            }
            // Check if enemies are displayed on the screen
            for (RivalCar &v : rivals) {
                float distX, distY;

                bool visible = true;

                switch(typeOfVehicle){
                    case 0:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player.getPosX(), player.getPosY(), distX, distY);
                        break;
                    case 1:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player2.getPosX(), player2.getPosY(), distX, distY);
                        break;
                    case 2:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player3.getPosX(), player3.getPosY(), distX, distY);
                        break;
                    case 3:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player4.getPosX(), player4.getPosY(), distX, distY);
                }

                if (visible) {
                    if (distY <= 30.f && distX <= 1.2f) {
                        // Thread with sound of the woman
                        elapsed8 = trafficCarSound.getElapsedTime().asSeconds();
                        if (elapsed8 - elapsed7 >= traffic_delay.asSeconds()) {
                            // makeCarTrafficSound
                            r.soundEffects[82]->stop();
                            r.soundEffects[83]->stop();
                            r.soundEffects[84]->stop();
                            r.soundEffects[rand_generator_int(82, 84)]->play();
                            trafficCarSound.restart();
                        }
                    }
                }
            }
            if (newLap) {
                drawNewLap(c);
                if (lapsDone < numberLaps){
                    if (r.soundEffects[55]->getStatus() != SoundSource::Playing){
                        newLap = false;
                    }
                }
                else {
                    if (r.soundEffects[56]->getStatus() != SoundSource::Playing){
                        r.soundTracks[r.currentSoundtrack]->play();
                        newLap = false;
                    }
                }
            }
        }
    }
}




/**
 * Updates the logic of the landscapes and vehicles and draws the current landscape fragment
 * with the vehicles on the screen.
 * @param c is the configuration of the game
 */
void Game::updateGamePolePositionStatus(Configuration &c, SoundPlayer& r, Vehicle::Action &action,
                                        Vehicle::Direction &direction, int& terrain)
{

    // Update camera
    switch(typeOfVehicle){
        case 0:
            currentMap->updateCamera(player.getPosX(), player.getPosY() - RECTANGLE);
            break;
        case 1:
            currentMap->updateCamera(player2.getPosX(), player2.getPosY() - RECTANGLE);
            break;
        case 2:
            currentMap->updateCamera(player3.getPosX(), player3.getPosY() - RECTANGLE);
            break;
        case 3:
            currentMap->updateCamera(player4.getPosX(), player4.getPosY() - RECTANGLE);
    }

    // World tour and pole position modes
    if (currentMap->isOutSideLandScape()) {
        // Update player and vehicle positions
        switch(typeOfVehicle){
            case 0:
                player.setPosition(player.getPosX() + currentMap->getOffsetX(), player.getPosY() - currentMap->getMaxY());
                break;
            case 1:
                player2.setPosition(player2.getPosX() + currentMap->getOffsetX(), player2.getPosY() - currentMap->getMaxY());
                break;
            case 2:
                player3.setPosition(player3.getPosX() + currentMap->getOffsetX(), player3.getPosY() - currentMap->getMaxY());
                break;
            case 3:
                player4.setPosition(player4.getPosX() + currentMap->getOffsetX(), player4.getPosY() - currentMap->getMaxY());
        }

        for (RivalCar &v : rivals)
            v.setPosition(v.getPosX(), v.getPosY() - currentMap->getMaxY());

        // Update to the map
        if (level < 0){
            level++;
            currentMap = currentMap->getNextLeft();
            checkPointPositions = currentMap->getCheckPointPositions();
        }
        else {
            currentMap = currentMap->getNextLeft();
            if (!currentMap->isFinalLandScape()){
                if (currentMap->isMiddleMap()){
                    lapsDone++;
                }
                if (typeOfGame == 2){
                    if (lapsDone <= numberLaps){
                        if (currentMap->isMiddleMap()){
                            currentMap->addNewLandScape(&tourLandScapes[landScapeSelected]);
                            checkPointPositions = tourLandScapes[landScapeSelected].getCheckPointPositions();
                            newLap = true;
                            time += 25;
                            if (lapsDone < numberLaps){
                                // New lap sound
                                r.soundEffects[55]->stop();
                                r.soundEffects[55]->play();
                                displayLapFactor = 70;
                            }
                            else {
                                // Final lap sound
                                r.soundTracks[r.currentSoundtrack]->pause();
                                r.soundEffects[56]->stop();
                                r.soundEffects[56]->play();
                                displayLapFactor = 130;
                            }
                        }
                        else {
                            if (lapsDone == numberLaps){
                                 goalMap = LandScape(goalFlagger, goalEnd, typeOfGame, numberRacers);
                                 goalMap.setColorsLandScape(*currentMap);
                                 currentMap->addNewLandScape(&goalMap);
                            }
                            else {
                                middleMap = LandScape(*currentMap, typeOfGame, numberRacers);
                                middleMap.setColorsLandScape(*currentMap);
                                currentMap->addNewLandScape(&middleMap);
                                checkPointPositions = currentMap->getCheckPointPositions();
                            }
                        }
                        indexCheckPoint = 1;
                    }
                }
            }
        }
    }
    else {
        // The player is still inside the landscape
        float pos = 0.f, halfspeed = 0.f;

        switch(typeOfVehicle){
            case 0:
                pos = player.getPosY();
                halfspeed = player.getHalfMaxSpeed();
                break;
            case 1:
                pos = player2.getPosY();
                halfspeed = player2.getHalfMaxSpeed();
                break;
            case 2:
                pos = player3.getPosY();
                halfspeed = player3.getHalfMaxSpeed();
                break;
            case 3:
                pos = player4.getPosY();
                halfspeed = player4.getHalfMaxSpeed();
        }

        if (pos >= checkPointPositions[indexCheckPoint - 1]){
            // Increment the next checkpoint to pass
            if (indexCheckPoint % 4 != 0){
                indexCheckPoint++;
                // Activate the checkPoint animation
                checkPoint = true;
                // Initialize the clock again
                updatedTimeCheck = true;

                // Add the time to complete the landscape
                if (indexCheckPoint != 4){
                    time += ((checkPointPositions[indexCheckPoint - 1] - pos) / (halfspeed * 65.f)) ;
                }
                else {
                    time += ((currentMap->getMaxY() - pos) / (halfspeed * 60.f));
                }
                // Update the checkpoint time
                timeCheck = time;
            }
        }

        if (!checkPoint){
            // Update the time
            lapCheckPoint = (minutes < 10) ? "0" + to_string(int(minutes)) + ":" : to_string(int(minutes)) + ":";
            lapCheckPoint += (secs < 10) ? "0" + to_string(int(secs)) + ":" : to_string(int(secs)) + ":";
            int cent_sec = cents_second * 100.f;
            lapCheckPoint += (cent_sec < 10) ? "0" + to_string(cent_sec) : to_string(cent_sec);
        }
        else if (updatedTimeCheck){
            // Initialize the clock again to zero one time
            updatedTimeCheck = false;

            // Reproduce checkpoint sound effect
            r.soundEffects[24]->stop();
            r.soundEffects[24]->play();
        }
    }
    if (currentMap->isFinalLandScape()) {
        State status = showsGoalAnimation(c, r);
        if (status == EXIT) {
            exit(1);
        }
        mtx.lock();
        arrival = true;
        mtx.unlock();
    }

    if (!finalGame && !arrival) {
        // Update and prepare cars to draw
        if (lastY <= currentMap->getCameraPosY() + float(c.renderLen)){
            lastY = currentMap->getCameraPosY() + float(c.renderLen);
        }

        Vehicle::Action a;

        float positionX = 0.f, positionY = 0.f, speedPlayer = 0.f;

        switch(typeOfVehicle){
            case 0:
                positionX = player.getPosX();
                positionY = player.getPosY();
                speedPlayer = player.getSpeed();
                break;
            case 1:
                positionX = player2.getPosX();
                positionY = player2.getPosY();
                speedPlayer = player2.getSpeed();
                break;
            case 2:
                positionX = player3.getPosX();
                positionY = player3.getPosY();
                speedPlayer = player3.getSpeed();
                break;
            case 3:
                positionX = player4.getPosX();
                positionY = player4.getPosY();
                speedPlayer = player4.getSpeed();
        }

        if (numberRacers > 0){
            // Clear the ranking of the rivals for updating
            rankingVehicles.clear();

            // Update and prepare racers to draw
            for (RivalCar &v : rivals) {
                float directionCurve = currentMap->getCurveCoefficient(v.getPosY());

                v.update(c, lastY, lastY + float(c.renderLen) / DENSITY_SPACE, c.maxAggressiveness, a, directionCurve,
                         c.level, positionX, positionY, speedPlayer);

                lastY = v.getPosY() + DISTANCE_TRESHOLD * RECTANGLE;

                // Get the new position of the vehicle
                float posY = v.getPosY();

                // Check if the vehicle is or not in a curve
                if (directionCurve != 0.f){
                    // Check if the vehicle has finished the curve
                    if (currentMap->getCurveCoefficient(posY)){
                        // Vehicle goes straight on
                        v.setOnStraight();
                    }
                }

                // Store the new position of the vehicle
                rankingVehicles.push_back(posY);

                // Draw the vehicle
                v.draw(a, currentMap->getElevation(posY));
                vehicleCrash = false;
                float crashPos;

                // Check if the player has crash with any rival car
                switch(typeOfVehicle){
                    case 0:

                        vehicleCrash = v.hasCrashed(player.getPosY(), player.getPreviousY(),
                                                    player.getMinScreenX(), player.getMaxScreenX(), crashPos);

                        // Check it has been crash between player and rival
                        if (vehicleCrash){
                            if (player.getPreviousX() > v.getPreviousX()){
                                player.setPosition(player.getPosX() + 1.5f * player.getAngle(), player.getPosY() - 10.f);
                            }
                            else if (player.getPreviousX() < v.getPreviousX()){
                                player.setPosition(player.getPosX() - 1.5f * player.getAngle(), player.getPosY() - 10.f);
                            }
                        }

                        // Reproduce sounds of collision
                        if (vehicleCrash){
                            // Voice sound
                            r.soundEffects[69]->stop();
                            r.soundEffects[70]->stop();
                            r.soundEffects[71]->stop();
                            r.soundEffects[72]->stop();
                            r.soundEffects[73]->stop();
                            r.soundEffects[74]->stop();
                            r.soundEffects[75]->stop();
                            r.soundEffects[rand_generator_int(69, 75)]->play();

                            // Collision sound
                            r.soundEffects[76]->stop();
                            r.soundEffects[77]->stop();
                            r.soundEffects[78]->stop();
                            r.soundEffects[79]->stop();
                            r.soundEffects[80]->stop();
                            r.soundEffects[81]->stop();
                            r.soundEffects[rand_generator_int(76, 81)]->play();
                        }
                        break;
                    case 1:
                        vehicleCrash = v.hasCrashed(player2.getPosY(), player2.getPreviousY(),
                                                    player2.getMinScreenX(), player2.getMaxScreenX(), crashPos);

                        if (vehicleCrash){
                            if (player2.getPreviousX() > v.getPreviousX()){
                                player2.setPosition(player.getPosX() + 1.5f * player2.getAngle(), player2.getPosY() - 10.f);
                            }
                            else if (player.getPreviousX() < v.getPreviousX()){
                                player2.setPosition(player.getPosX() - 1.5f * player2.getAngle(), player2.getPosY() - 10.f);
                            }
                            r.soundEffects[87]->stop();
                            r.soundEffects[87]->play();
                        }
                        break;
                    case 2:
                        vehicleCrash = v.hasCrashed(player3.getPosY(), player3.getPreviousY(),
                                                    player3.getMinScreenX(), player3.getMaxScreenX(), crashPos);

                        if (vehicleCrash){
                            if (player3.getPreviousX() > v.getPreviousX()){
                                player3.setPosition(player.getPosX() + 1.5f * player3.getAngle(), player3.getPosY() - 10.f);
                            }
                            else if (player.getPreviousX() < v.getPreviousX()){
                                player3.setPosition(player.getPosX() - 1.5f * player3.getAngle(), player3.getPosY() - 10.f);
                            }
                            r.soundEffects[87]->stop();
                            r.soundEffects[87]->play();
                        }
                        break;
                    case 3:
                        vehicleCrash = v.hasCrashed(player4.getPosY(), player4.getPreviousY(),
                                                    player4.getMinScreenX(), player4.getMaxScreenX(), crashPos);

                        if (vehicleCrash){
                            if (player4.getPreviousX() > v.getPreviousX()){
                                player4.setPosition(player.getPosX() + 1.5f * player4.getAngle(), player4.getPosY() - 10.f);
                            }
                            else if (player.getPreviousX() < v.getPreviousX()){
                                player4.setPosition(player.getPosX() - 1.5f * player4.getAngle(), player4.getPosY() - 10.f);
                            }
                            r.soundEffects[87]->stop();
                            r.soundEffects[87]->play();
                        }
                }
                v.setAI(c.maxAggressiveness, c.level);
            }

            // Order the rivals cars of the race to build a temporary ranking
            sort(rankingVehicles.begin(), rankingVehicles.end(), ascendingRanking);

            // Get the new position of the player in the race
            posArrival = findPlayerPositionRanking(positionY);
        }

        // Draw map with cars
        c.w.clear();
        currentMap->drawLandScape(c, cars, rivals, typeOfGame);

        // Player update and draw
        action = Vehicle::CRASH;
        direction = Vehicle::RIGHT;

        switch(typeOfVehicle){
            case 0:
                if (!player.isCrashing()) { // If not has crashed
                    action = player.accelerationControl(c, currentMap->isOutSideRoad(player.getPosX(), player.getPosY()));
                    direction = player.rotationControl(c, currentMap->getCurveCoefficient(player.getPosY()),
                                                          currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                }
                else {
                    player.hitControl(vehicleCrash);
                }

                player.draw(c, r, action, direction, currentMap->getElevation(player.getPosY()), terrain);

                if (!player.isCrashing()) {
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player.getPreviousY(), player.getPosY(), player.getPosX(),
                                                        player.getMinScreenX(), player.getMaxScreenX(), crashPos, typeOfGame);

                    if (crash) {
                        // Determine the type of collision
                        player.setPosition(player.getPosX(), crashPos);
                        player.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player.draw(c, r, action, direction, currentMap->getElevation(player.getPosY()), terrain);
                    }
                }

                for (RivalCar &v : rivals)
                    v.autoControl(c, player.getPosX(), player.getPosY());

                break;
            case 1:
                if (!player2.isCrashing()) { // If not has crashed
                    action = player2.accelerationControl(c, currentMap->isOutSideRoad(player2.getPosX(), player2.getPosY()));
                    direction = player2.rotationControl(c, currentMap->getCurveCoefficient(player2.getPosY()),
                                                           currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                }
                else {
                    player2.hitControl(vehicleCrash);
                }

                player2.draw(c, r, action, direction, currentMap->getElevation(player2.getPosY()), terrain);

                if (!player2.isCrashing()) {
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player2.getPreviousY(), player2.getPosY(), player2.getPosX(),
                                                        player2.getMinScreenX(), player2.getMaxScreenX(), crashPos, typeOfGame);

                    if (crash) {
                        // Determine the type of collision
                        player2.setModeCollision();
                        player2.setPosition(player2.getPosX(), crashPos);
                        player2.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player2.draw(c, r, action, direction, currentMap->getElevation(player2.getPosY()), terrain);
                    }
                }

                for (RivalCar &v : rivals)
                    v.autoControl(c, player2.getPosX(), player2.getPosY());

                break;
            case 2:
                if (!player3.isCrashing()) { // If not has crashed
                    action = player3.accelerationControl(c, currentMap->isOutSideRoad(player3.getPosX(), player3.getPosY()));
                    direction = player3.rotationControl(c, currentMap->getCurveCoefficient(player3.getPosY()),
                                                           currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                }
                else {
                    player3.hitControl(vehicleCrash);
                }

                player3.draw(c, r, action, direction, currentMap->getElevation(player3.getPosY()), terrain);

                if (!player3.isCrashing()) {
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player3.getPreviousY(), player3.getPosY(), player3.getPosX(),
                                                        player3.getMinScreenX(), player3.getMaxScreenX(), crashPos, typeOfGame);

                    if (crash) {
                        // Determine the type of collision
                        player3.setModeCollision();
                        player3.setPosition(player3.getPosX(), crashPos);
                        player3.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player3.draw(c, r, action, direction, currentMap->getElevation(player3.getPosY()), terrain);
                    }
                }

                for (RivalCar &v : rivals)
                    v.autoControl(c, player3.getPosX(), player3.getPosY());

                break;
            case 3:
                if (!player4.isCrashing()) { // If not has crashed
                    action = player4.accelerationControl(c, currentMap->isOutSideRoad(player4.getPosX(), player4.getPosY()));
                    direction = player4.rotationControl(c, currentMap->getCurveCoefficient(player4.getPosY()),
                                                           currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                }
                else {
                    player4.hitControl(vehicleCrash);
                }

                player4.draw(c, r, action, direction, currentMap->getElevation(player4.getPosY()), terrain);

                if (!player4.isCrashing()) {
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player4.getPreviousY(), player4.getPosY(), player4.getPosX(),
                                                        player4.getMinScreenX(), player4.getMaxScreenX(), crashPos, typeOfGame);

                    if (crash) {
                        // Determine the type of collision
                        player4.setModeCollision();
                        player4.setPosition(player4.getPosX(), crashPos);
                        player4.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player4.draw(c, r, action, direction, currentMap->getElevation(player4.getPosY()), terrain);
                    }
                }

                for (RivalCar &v : rivals)
                    v.autoControl(c, player3.getPosX(), player3.getPosY());
        }
        if (!finalGame && !arrival){
            // Check if enemies are displayed on the screen
            for (RivalCar &v : rivals) {
                float distX, distY;

                bool visible = true;

                switch(typeOfVehicle){
                    case 0:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player.getPosX(), player.getPosY(), distX, distY);
                        break;
                    case 1:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player2.getPosX(), player2.getPosY(), distX, distY);
                        break;
                    case 2:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player3.getPosX(), player3.getPosY(), distX, distY);
                        break;
                    case 3:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player4.getPosX(), player4.getPosY(), distX, distY);
                }

                if (visible) {
                    if (distY <= 30.f && distX <= 1.2f) {
                        // Thread with sound of the woman
                        elapsed8 = trafficCarSound.getElapsedTime().asSeconds();
                        if (elapsed8 - elapsed7 >= traffic_delay.asSeconds()) {
                            // makeCarTrafficSound
                            r.soundEffects[82]->stop();
                            r.soundEffects[83]->stop();
                            r.soundEffects[84]->stop();
                            r.soundEffects[rand_generator_int(82, 84)]->play();
                            trafficCarSound.restart();
                        }
                    }
                }
            }
            if (newLap) {
                drawNewLap(c);
                if (lapsDone < numberLaps){
                    if (r.soundEffects[55]->getStatus() != SoundSource::Playing){
                        newLap = false;
                        shown = false;
                    }
                }
                else {
                    if (r.soundEffects[56]->getStatus() != SoundSource::Playing){
                        r.soundTracks[r.currentSoundtrack]->play();
                        newLap = false;
                        shown = false;
                    }
                }
            }
        }
    }
}



/**
 * Updates the logic of the landscapes and vehicles and draws the current landscape fragment
 * with the vehicles on the screen.
 * @param c is the configuration of the game
 */
void Game::updateGameOutRunDerramageStatus(Configuration &c, SoundPlayer& r, Vehicle::Action &action,
                                           Vehicle::Direction &direction, int& terrain)
{
    // Update camera
    switch(typeOfVehicle){
        case 0:
            currentMap->updateCamera(player.getPosX(), player.getPosY() - RECTANGLE);
            break;
        case 1:
            currentMap->updateCamera(player2.getPosX(), player2.getPosY() - RECTANGLE);
            break;
        case 2:
            currentMap->updateCamera(player3.getPosX(), player3.getPosY() - RECTANGLE);
            break;
        case 3:
            currentMap->updateCamera(player4.getPosX(), player4.getPosY() - RECTANGLE);
    }

    // Out Run and Driving Fury and Demarrage modes
    if (currentMap->isOutSideLandScape()) {
        if (currentMap->getNextLeft() != nullptr) {
            // Update player and vehicle positions
            switch(typeOfVehicle){
                case 0:
                    player.setPosition(player.getPosX() + currentMap->getOffsetX(), player.getPosY() - currentMap->getMaxY());
                    break;
                case 1:
                    player2.setPosition(player2.getPosX() + currentMap->getOffsetX(), player2.getPosY() - currentMap->getMaxY());
                    break;
                case 2:
                    player3.setPosition(player3.getPosX() + currentMap->getOffsetX(), player3.getPosY() - currentMap->getMaxY());
                    break;
                case 3:
                    player4.setPosition(player4.getPosX() + currentMap->getOffsetX(), player4.getPosY() - currentMap->getMaxY());
            }

            for (TrafficCar &v : cars)
                v.setPosition(v.getPosX(), v.getPosY() - currentMap->getMaxY());

            const bool isInitMap = currentMap->isStartingLandScape();
            currentMap = currentMap->getNextLeft();
            terrain = currentMap->getTerrain();
            if (!isInitMap && !currentMap->isFinalLandScape()) {
                level++;
                    // Update fork maps
                if (currentMap == &maps[mapId.first + 1][mapId.second + 1])
                    mapId.second++;
                mapId.first++;

                if (mapId.first < 4)
                    currentMap->addFork(&maps[mapId.first + 1][mapId.second], &maps[mapId.first + 1][mapId.second + 1]);
                else {
                    goalMap = LandScape(goalFlagger, goalEnd, typeOfGame, numberRacers);
                    goalMap.setColorsLandScape(*currentMap);
                    currentMap->addNewLandScape(&goalMap);
                }

                // Update time when map changes
                time += int(float(currentMap->getTimeToPlay()) * timeMul);

                // Update the indicators
                if (!checkPoint) {
                    lapCheckPoint = (minutes < 10) ? "0" + to_string(int(minutes)) + ":" : to_string(int(minutes)) + ":";
                    lapCheckPoint += (secs < 10) ? "0" + to_string(int(secs)) + ":" : to_string(int(secs)) + ":";
                    int cent_sec = cents_second * 100.f;
                    lapCheckPoint += (cent_sec < 10) ? "0" + to_string(cent_sec) : to_string(cent_sec);

                    // Initialize to zero the time
                    cents_second = 0;
                    secs = 0;
                    minutes = 0;
                }
                checkPoint = true;
                timeCheck = time;

                // CheckPointEffect
                r.soundEffects[23]->stop();
                r.soundEffects[23]->play();
            }

            switch(typeOfVehicle){
                case 0:
                    currentMap->updateCamera(player.getPosX(), player.getPosY() - RECTANGLE);
                    break;
                case 1:
                    currentMap->updateCamera(player2.getPosX(), player2.getPosY() - RECTANGLE);
                    break;
                case 2:
                    currentMap->updateCamera(player3.getPosX(), player3.getPosY() - RECTANGLE);
                    break;
                case 3:
                    currentMap->updateCamera(player4.getPosX(), player4.getPosY() - RECTANGLE);
            }

            lastY = currentMap->getCameraPosY();
        }
        else {
            finalGame = true;
        }
    }
    if (currentMap->isFinalLandScape()) {
        State status = showsGoalAnimation(c, r);
        if (status == EXIT) {
            exit(1);
        }
        mtx.lock();
        arrival = true;
        mtx.unlock();
    }

    if (!finalGame && !arrival) {
        // Update and prepare cars to draw
        if (lastY <= currentMap->getCameraPosY() + float(c.renderLen)){
            lastY = currentMap->getCameraPosY() + float(c.renderLen);
        }

        for (TrafficCar &v : cars) {
            if (currentMap->inFork(v.getPosY())) {
                v.setPosition(v.getPosX(), -RECTANGLE * DEL_DISTANCE * 3.0f);
            }
            else if (v.getPosY() + DEL_DISTANCE < currentMap->getCameraPosY()) {
                v.update(lastY, lastY + float(c.renderLen) / DENSITY_SPACE, c.maxAggressiveness, c.level);
                lastY = v.getPosY() + DISTANCE_TRESHOLD * RECTANGLE;
            }

            float posY = v.getPosY();
            v.draw(currentMap->getElevation(posY), currentMap->getCameraPosX());
        }

        // Draw map with cars
        c.w.clear();
        currentMap->drawLandScape(c, cars, rivals, typeOfGame);

        // Player update and draw
        action = Vehicle::CRASH;
        direction = Vehicle::RIGHT;

        switch(typeOfVehicle){
            case 0:
                if (!player.isCrashing()) { // If not has crashed
                    action = player.accelerationControl(c, currentMap->isOutSideRoad(player.getPosX(), player.getPosY()));
                    direction = player.rotationControl(c, currentMap->getCurveCoefficient(player.getPosY()),
                                                          currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                }
                else {
                    player.hitControl(vehicleCrash);
                }

                player.draw(c, r, action, direction, currentMap->getElevation(player.getPosY()), terrain);

                if (!player.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player.getPreviousY(), player.getPosY(), player.getPosX(),
                                                        player.getMinScreenX(), player.getMaxScreenX(), crashPos, typeOfGame);
                    if (!crash)
                        for (int i = 0; !vehicleCrash && i < (int)cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player.getPreviousY(), player.getPosY(),
                                                              player.getMinScreenX(), player.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        player.setPosition(player.getPosX(), crashPos);
                        player.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player.draw(c, r, action, direction, currentMap->getElevation(player.getPosY()), terrain);
                    }
                }

                for (TrafficCar &v : cars)
                    v.autoControl(c, player.getPosX(), player.getPosY());
                break;
            case 1:
                if (!player2.isCrashing()) { // If not has crashed
                    action = player2.accelerationControl(c, currentMap->isOutSideRoad(player2.getPosX(), player2.getPosY()));
                    direction = player2.rotationControl(c, currentMap->getCurveCoefficient(player2.getPosY()),
                                                           currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                }
                else {
                    player2.hitControl(vehicleCrash);
                }

                player2.draw(c, r, action, direction, currentMap->getElevation(player2.getPosY()), terrain);

                if (!player2.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player2.getPreviousY(), player2.getPosY(), player2.getPosX(),
                                                        player2.getMinScreenX(), player2.getMaxScreenX(), crashPos, typeOfGame);
                    if (!crash)
                        for (int i = 0; !vehicleCrash && i < (int)cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player2.getPreviousY(), player2.getPosY(),
                                                              player2.getMinScreenX(), player2.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        player2.setModeCollision();
                        player2.setPosition(player2.getPosX(), crashPos);
                        player2.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player2.draw(c, r, action, direction, currentMap->getElevation(player2.getPosY()), terrain);
                    }
                }

                for (TrafficCar &v : cars)
                    v.autoControl(c, player2.getPosX(), player2.getPosY());
                break;
            case 2:
                if (!player3.isCrashing()) { // If not has crashed
                    action = player3.accelerationControl(c, currentMap->isOutSideRoad(player3.getPosX(), player3.getPosY()));
                    direction = player3.rotationControl(c, currentMap->getCurveCoefficient(player3.getPosY()),
                                                           currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                }
                else {
                    player3.hitControl(vehicleCrash);
                }

                player3.draw(c, r, action, direction, currentMap->getElevation(player3.getPosY()), terrain);

                if (!player3.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player3.getPreviousY(), player3.getPosY(), player3.getPosX(),
                                                        player3.getMinScreenX(), player3.getMaxScreenX(), crashPos, typeOfGame);
                    if (!crash)
                        for (int i = 0; !vehicleCrash && i < (int)cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player3.getPreviousY(), player3.getPosY(),
                                                              player3.getMinScreenX(), player3.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        player3.setModeCollision();
                        player3.setPosition(player3.getPosX(), crashPos);
                        player3.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player3.draw(c, r, action, direction, currentMap->getElevation(player3.getPosY()), terrain);
                    }
                }
                for (TrafficCar &v : cars)
                    v.autoControl(c, player3.getPosX(), player3.getPosY());
                break;
            case 3:
                if (!player4.isCrashing()) { // If not has crashed
                    action = player4.accelerationControl(c, currentMap->isOutSideRoad(player4.getPosX(), player4.getPosY()));
                    direction = player4.rotationControl(c, currentMap->getCurveCoefficient(player4.getPosY()),
                                                           currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                }
                else {
                    player4.hitControl(vehicleCrash);
                }

                player4.draw(c, r, action, direction, currentMap->getElevation(player4.getPosY()), terrain);

                if (!player4.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player4.getPreviousY(), player4.getPosY(), player4.getPosX(),
                                                        player4.getMinScreenX(), player4.getMaxScreenX(), crashPos, typeOfGame);
                    if (!crash)
                        for (int i = 0; !vehicleCrash && i < (int)cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player4.getPreviousY(), player4.getPosY(),
                                                              player4.getMinScreenX(), player4.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        player4.setModeCollision();
                        player4.setPosition(player4.getPosX(), crashPos);
                        player4.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player4.draw(c, r, action, direction, currentMap->getElevation(player4.getPosY()), terrain);
                    }
                }

                for (TrafficCar &v : cars)
                    v.autoControl(c, player4.getPosX(), player4.getPosY());
        }
        if (!finalGame && !arrival){
            // Check if enemies are displayed on the screen
            for (TrafficCar &v : cars) {
                float distX, distY;

                bool visible = true;

                switch(typeOfVehicle){
                    case 0:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player.getPosX(), player.getPosY(), distX, distY);
                        break;
                    case 1:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player2.getPosX(), player2.getPosY(), distX, distY);
                        break;
                    case 2:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player3.getPosX(), player3.getPosY(), distX, distY);
                        break;
                    case 3:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player4.getPosX(), player4.getPosY(), distX, distY);
                }

                if (visible) {
                    if (distY <= 20.f && distX <= 0.3f) {
                        // Thread with sound of the woman
                        elapsed6 = womanShot.getElapsedTime().asSeconds();
                        if (elapsed6 - elapsed5 >= woman_delay.asSeconds()) {
                            // WomanSound
                            r.soundEffects[13]->stop();
                            r.soundEffects[14]->stop();
                            r.soundEffects[15]->stop();
                            r.soundEffects[rand_generator_int(13, 15)]->play();
                            womanShot.restart();
                        }
                    }
                    if (distY <= 30.f && distX <= 1.2f) {
                        // Thread with sound of the woman
                        elapsed8 = trafficCarSound.getElapsedTime().asSeconds();
                        if (elapsed8 - elapsed7 >= traffic_delay.asSeconds()) {
                            if (v.getIsTruck()){
                                // Truck sound
                                r.soundEffects[85]->stop();
                                r.soundEffects[86]->stop();
                                r.soundEffects[rand_generator_int(85, 86)]->play();
                            }
                            else {
                                // Traffic car sound
                                r.soundEffects[20]->stop();
                                r.soundEffects[21]->stop();
                                r.soundEffects[22]->stop();
                                r.soundEffects[rand_generator_int(20, 22)]->play();

                                r.soundEffects[59]->stop();
                                r.soundEffects[60]->stop();
                                r.soundEffects[61]->stop();
                                r.soundEffects[rand_generator_int(59, 61)]->play();
                            }
                            trafficCarSound.restart();
                        }
                    }
                }
            }
            if (checkPoint) {
                elapsed10 = blinkTime.getElapsedTime().asSeconds();
                if (elapsed10 - elapsed9 >= blink_delay.asSeconds()) {
                    blink = !blink;
                    blinkTime.restart();
                }
                if (blink) {
                    showCheckpointIndications(c, true);
                    // BeepSound
                    r.soundEffects[48]->stop();
                    r.soundEffects[48]->play();
                }
                else {
                    showCheckpointIndications(c, false);
                }
                if (timeCheck - time > 5) {
                    checkPoint = false;
                }
            }
            if (newLap) {
                drawNewLap(c);
                if (lapsDone < numberLaps){
                    if (r.soundEffects[55]->getStatus() != SoundSource::Playing){
                        newLap = false;
                    }
                }
                else {
                    if (r.soundEffects[56]->getStatus() != SoundSource::Playing){
                        r.soundTracks[r.currentSoundtrack]->play();
                        newLap = false;
                    }
                }
            }
        }
    }
}



/**
 * Updates the logic of the landscapes and vehicles and draws the current landscape fragment
 * with the vehicles on the screen.
 * @param c is the configuration of the game
 */
void Game::updateGameDrivingFuryStatus(Configuration &c, SoundPlayer& r, Vehicle::Action &action,
                                       Vehicle::Direction &direction, int& terrain)
{

    currentMap->updateCamera(player5.getPosX(), player5.getPosY() - RECTANGLE);

    // Out Run and Driving Fury and Demarrage modes
    if (currentMap->isOutSideLandScape()) {
        if (currentMap->getNextLeft() != nullptr) {

            player5.setPosition(player5.getPosX() + currentMap->getOffsetX(), player5.getPosY() - currentMap->getMaxY());

            for (TrafficCar &v : cars)
                v.setPosition(v.getPosX(), v.getPosY() - currentMap->getMaxY());

            const bool isInitMap = currentMap->isStartingLandScape();
            currentMap = currentMap->getNextLeft();
            terrain = currentMap->getTerrain();
            if (!isInitMap && !currentMap->isFinalLandScape()) {
                level++;
                    // Update fork maps
                if (currentMap == &maps[mapId.first + 1][mapId.second + 1])
                    mapId.second++;
                mapId.first++;

                if (mapId.first < 4)
                    currentMap->addFork(&maps[mapId.first + 1][mapId.second], &maps[mapId.first + 1][mapId.second + 1]);
                else {
                    goalMap = LandScape(goalFlagger, goalEnd, typeOfGame, numberRacers);
                    goalMap.setColorsLandScape(*currentMap);
                    currentMap->addNewLandScape(&goalMap);
                }

                // Update time when map changes
                time += int(float(currentMap->getTimeToPlay()) * timeMul);

                // Update the indicators
                if (!checkPoint) {
                    lapCheckPoint = (minutes < 10) ? "0" + to_string(int(minutes)) + ":" : to_string(int(minutes)) + ":";
                    lapCheckPoint += (secs < 10) ? "0" + to_string(int(secs)) + ":" : to_string(int(secs)) + ":";
                    int cent_sec = cents_second * 100.f;
                    lapCheckPoint += (cent_sec < 10) ? "0" + to_string(cent_sec) : to_string(cent_sec);

                    // Initialize to zero the time
                    cents_second = 0;
                    secs = 0;
                    minutes = 0;
                }
                checkPoint = true;
                timeCheck = time;

                // CheckPointEffect
                r.soundEffects[23]->stop();
                r.soundEffects[23]->play();
            }

            currentMap->updateCamera(player5.getPosX(), player5.getPosY() - RECTANGLE);

            lastY = currentMap->getCameraPosY();
        }
        else {
            finalGame = true;
        }
    }
    if (currentMap->isFinalLandScape()) {
        State status = showsGoalAnimation(c, r);
        if (status == EXIT) {
            exit(1);
        }
        mtx.lock();
        arrival = true;
        mtx.unlock();
    }

    if (!finalGame && !arrival) {
        // Update and prepare cars to draw
        if (lastY <= currentMap->getCameraPosY() + float(c.renderLen)){
            lastY = currentMap->getCameraPosY() + float(c.renderLen);
        }

        for (TrafficCar &v : cars) {
            if (currentMap->inFork(v.getPosY())) {
                v.setPosition(v.getPosX(), -RECTANGLE * DEL_DISTANCE * 3.0f);
            }
            else if (v.getPosY() + DEL_DISTANCE < currentMap->getCameraPosY()) {
                v.update(lastY, lastY + float(c.renderLen) / DENSITY_SPACE, c.maxAggressiveness, c.level);
                lastY = v.getPosY() + DISTANCE_TRESHOLD * RECTANGLE;
            }

            float posY = v.getPosY();
            v.draw(currentMap->getElevation(posY), currentMap->getCameraPosX());
        }

        // Draw map with cars
        c.w.clear();
        currentMap->drawLandScape(c, cars, rivals, typeOfGame);

        // Player update and draw
        action = Vehicle::CRASH;
        direction = Vehicle::RIGHT;

        if (!player5.isCrashing()) { // If not has crashed
            action = player5.accelerationControl(c, currentMap->isOutSideRoad(player5.getPosX(), player5.getPosY()));
            direction = player5.rotationControl(c, currentMap->getCurveCoefficient(player5.getPosY()),
                                                   currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
        }
        else {
            player5.hitControl(vehicleCrash);
        }

        player5.draw(c, r, action, direction, currentMap->getElevation(player5.getPosY()), terrain);

        if (!player5.isCrashing()) {
            vehicleCrash = false;
            float crashPos;
            bool crash = currentMap->hasCrashed(c, player5.getPreviousY(), player5.getPosY(), player5.getPosX(),
                                                player5.getMinScreenX(), player5.getMaxScreenX(), crashPos, typeOfGame);
            if (!crash && typeOfGame != 2)
                for (int i = 0; !vehicleCrash && i < (int)cars.size(); i++)
                    vehicleCrash = cars[i].hasCrashed(player5.getPreviousY(), player5.getPosY(),
                                                      player5.getMinScreenX(), player5.getMaxScreenX(),
                                                      crashPos);

            if (crash || vehicleCrash) {
                // Determine the type of collision
                player5.setModeCollision();
                player5.setPosition(player5.getPosX(), crashPos);
                player5.hitControl(vehicleCrash);
                action = Vehicle::CRASH;
                direction = Vehicle::RIGHT;

                player5.draw(c, r, action, direction, currentMap->getElevation(player5.getPosY()), terrain);
            }
        }

        for (TrafficCar &v : cars)
            v.autoControl(c, player5.getPosX(), player5.getPosY());


        if (!finalGame && !arrival){
            // Check if enemies are displayed on the screen
            for (TrafficCar &v : cars) {
                float distX, distY;

                bool visible = true;

                switch(typeOfVehicle){
                    case 0:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player.getPosX(), player.getPosY(), distX, distY);
                        break;
                    case 1:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player2.getPosX(), player2.getPosY(), distX, distY);
                        break;
                    case 2:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player3.getPosX(), player3.getPosY(), distX, distY);
                        break;
                    case 3:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player4.getPosX(), player4.getPosY(), distX, distY);
                        break;
                    case 4:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player5.getPosX(), player5.getPosY(), distX, distY);
                }

                if (visible) {
                    if (distY <= 20.f && distX <= 0.3f) {
                        // Thread with sound of the woman
                        elapsed6 = womanShot.getElapsedTime().asSeconds();
                        if (elapsed6 - elapsed5 >= woman_delay.asSeconds()) {
                            // WomanSound
                            r.soundEffects[13]->stop();
                            r.soundEffects[14]->stop();
                            r.soundEffects[15]->stop();
                            r.soundEffects[rand_generator_int(13, 15)]->play();
                            womanShot.restart();
                        }
                    }
                    if (distY <= 30.f && distX <= 1.2f) {
                        // Thread with sound of the woman
                        elapsed8 = trafficCarSound.getElapsedTime().asSeconds();
                        if (elapsed8 - elapsed7 >= traffic_delay.asSeconds()) {
                            if (v.getIsTruck()){
                                // Truck sound
                                r.soundEffects[85]->stop();
                                r.soundEffects[86]->stop();
                                r.soundEffects[rand_generator_int(85, 86)]->play();
                            }
                            else {
                                // Traffic car sound
                                r.soundEffects[20]->stop();
                                r.soundEffects[21]->stop();
                                r.soundEffects[22]->stop();
                                r.soundEffects[rand_generator_int(20, 22)]->play();

                                r.soundEffects[59]->stop();
                                r.soundEffects[60]->stop();
                                r.soundEffects[61]->stop();
                                r.soundEffects[rand_generator_int(59, 61)]->play();
                            }
                            trafficCarSound.restart();
                        }
                    }
                }
            }
            if (checkPoint) {
                elapsed10 = blinkTime.getElapsedTime().asSeconds();
                if (elapsed10 - elapsed9 >= blink_delay.asSeconds()) {
                    blink = !blink;
                    blinkTime.restart();
                }
                if (blink) {
                    showCheckpointIndications(c, true);
                    // BeepSound
                    r.soundEffects[48]->stop();
                    r.soundEffects[48]->play();
                }
                else {
                    showCheckpointIndications(c, false);
                }
                if (timeCheck - time > 5) {
                    checkPoint = false;
                }
            }
            if (newLap) {
                drawNewLap(c);
                if (lapsDone < numberLaps){
                    if (r.soundEffects[55]->getStatus() != SoundSource::Playing){
                        newLap = false;
                    }
                }
                else {
                    if (r.soundEffects[56]->getStatus() != SoundSource::Playing){
                        r.soundTracks[r.currentSoundtrack]->play();
                        newLap = false;
                    }
                }
            }
        }
    }
}



/**
 * Load the configuration of the pause menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void Game::loadPauseMenuConfiguration(const string path, Configuration& c){
    // Open the xml file of the scenario
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Local variable to store temporary the text content and the fonts of the texts
    string content, fontPath, backgroundTexture, colorKind;

    // Iterate to get the information of the player menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check it is the node that contains the information of the main panel
        if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the player menu
            for (xml_node<> *panelProp = property->first_node(); panelProp; panelProp = panelProp->next_sibling()){
                // Get the name of the node
                content = (string)panelProp->name();
                // Check it is the node that contains the information of the color border of the panel
                if ((string)panelProp->name() == "ColorPanel" || (string)panelProp->name() == "ColorBorder"){
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the player menu
                    for (xml_node<> *colorChannel = panelProp->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                        // Get the red color channel
                        if ((string)colorChannel->name() == "R"){
                            // Get the red channel
                            colorRed = stoi((string)colorChannel->value());
                        }
                        // Get the green color channel
                        else if ((string)colorChannel->name() == "G"){
                            // Get the red channel
                            colorGreen = stoi((string)colorChannel->value());
                        }
                        // Get the blue color channel
                        else if ((string)colorChannel->name() == "B"){
                            // Get the red channel
                            colorBlue = stoi((string)colorChannel->value());
                        }
                    }
                    //Store the color correctly
                    if (content == "ColorPanel"){
                        c.colorInsidePanelPauseMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    else if (content == "ColorBorder"){
                        c.colorBorderPanelPauseMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
        // Check if it is the node that stores the information of the main text of the menu
        else if ((string)property->name() == "Title"){
            // Iterate to get the information of the title
            for (xml_node<> *titleProp = property->first_node(); titleProp; titleProp = titleProp->next_sibling()){
                // Get the red color channel
                if ((string)titleProp->name() == "Content"){
                    // Get the content of the title
                    content = (string)titleProp->value();
                    c.contentTitlePauseMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontPauseMenu.loadFromFile(fontPath);
                }
                // Get color text of the title
                else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                    // Get the kind of color to process
                    colorKind = (string)titleProp->name();
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the player menu
                    for (xml_node<> *colorChannel = titleProp->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                        // Get the red color channel
                        if ((string)colorChannel->name() == "R"){
                            // Get the red channel
                            colorRed = stoi(colorChannel->value());
                        }
                        // Get the green color channel
                        else if ((string)colorChannel->name() == "G"){
                            // Get the red channel
                            colorGreen = stoi(colorChannel->value());
                        }
                        // Get the blue color channel
                        else if ((string)colorChannel->name() == "B"){
                            // Get the red channel
                            colorBlue = stoi(colorChannel->value());
                        }
                    }
                    // Check if it is the color of the text
                    if (colorKind == "ColorText"){
                        c.colorTitleTextPauseMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderPauseMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
        // Check if it is the node that the different buttons of the menu
        else if ((string)property->name() == "MenuButtons"){
            // Iterate to get the information of the buttons of the player menu
            for (xml_node<> *buttonProp = property->first_node(); buttonProp; buttonProp = buttonProp->next_sibling()){
                // Get the font of the buttons
                if ((string)buttonProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)buttonProp->value();
                    c.fontMenuPauseButtons.loadFromFile(fontPath);
                }
                // Get the color font of the buttons
                else if ((string)buttonProp->name() == "ColorFont"){
                    // Read the font from the file
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the player menu
                    for (xml_node<> *color = buttonProp->first_node(); color; color = color->next_sibling()){
                        // Get the red color channel
                        if ((string)color->name() == "R"){
                            // Get the red channel
                            colorRed = stoi(color->value());
                        }
                        // Get the green color channel
                        else if ((string)color->name() == "G"){
                            // Get the red channel
                            colorGreen = stoi(color->value());
                        }
                        // Get the blue color channel
                        else if ((string)color->name() == "B"){
                            // Get the red channel
                            colorBlue = stoi(color->value());
                        }
                    }
                    // Push the color of the button read
                    c.colorFontMenuPauseButtons = Color(colorRed, colorGreen, colorBlue);
                }
                // Get the information of the buttons
                else if ((string)buttonProp->name() == "Buttons"){
                    // Local variables to store the attributes of the buttons
                    string contentButton;
                    int buttonState = 0;
                    vector<Color> colorButtons;
                    Texture icon;
                    Sprite s;
                    int idButton = 0, posX, posY, widthButton, heightButton;
                    // Iterate to get the information of the buttons
                    for (xml_node<> *buttonNode = buttonProp->first_node(); buttonNode; buttonNode = buttonNode->next_sibling()){
                        // Iterate to get the information of the buttons
                        for (xml_node<> *button = buttonNode->first_node(); button; button = button->next_sibling()){
                            // Get the font of the buttons
                            if ((string)button->name() == "Content"){
                                // Read the font from the file
                                contentButton = (string)button->value();
                            }
                            // Get the state of the button
                            else if ((string)button->name() == "InitialState"){
                                // Read the font from the file
                                buttonState = stoi(button->value());
                            }
                            // Get the colors of the button
                            else if ((string)button->name() == "Colors"){
                                // Read the colors of the button
                                for (xml_node<> *colorButton = button->first_node(); colorButton; colorButton = colorButton->next_sibling()){
                                    // Get the border color of the panel
                                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                                    // Iterate to get the information of the player menu
                                    for (xml_node<> *color = colorButton->first_node(); color; color = color->next_sibling()){
                                        // Get the red color channel
                                        if ((string)color->name() == "R"){
                                            // Get the red channel
                                            colorRed = stoi(color->value());
                                        }
                                        // Get the green color channel
                                        else if ((string)color->name() == "G"){
                                            // Get the red channel
                                            colorGreen = stoi(color->value());
                                        }
                                        // Get the blue color channel
                                        else if ((string)color->name() == "B"){
                                            // Get the red channel
                                            colorBlue = stoi(color->value());
                                        }
                                    }
                                    // Push the color of the button read
                                    colorButtons.push_back(Color(colorRed, colorGreen, colorBlue));
                                }
                                // Creation of the button and addition to the vector
                                posX = c.w.getSize().x / 2.f - 95.0f * c.screenScale;
                                posY = c.w.getSize().y / 2.f - (70.0f - idButton * 70.0f) * c.screenScale;
                                widthButton = 200.0f * c.screenScale;
                                heightButton = 30.0f * c.screenScale;

                                // Creation of the button
                                Button b = Button(posX, posY, widthButton, heightButton, c.fontMenuPauseButtons,
                                                  contentButton, colorButtons[0], colorButtons[1], c.colorFontMenuPauseButtons,
                                                  buttonState, c.screenScale);

                                // Process the description text of the button
                                c.pauseMenuButtons.push_back(b);
                                idButton++;
                            }
                        }
                    }
                }
            }
        }
    }
    // The pause menu has been read correctly
    c.pauseMenuRead = true;
}


/**
 * Display the pause menu of the game
 */
State Game::pause(Configuration &c, SoundPlayer& r,const Vehicle::Action &a, const Vehicle::Direction &d) {
    c.w.clear();

    // Draw the map
    currentMap->drawLandScape(c, cars, rivals, typeOfGame);

    switch(typeOfVehicle){
        case 0:
            player.draw(c, r, a, d, currentMap->getElevation(player.getPosY()), terrain, false);
            break;
        case 1:
            player2.draw(c, r, a, d, currentMap->getElevation(player2.getPosY()), terrain, false);
            break;
        case 2:
            player3.draw(c, r, a, d, currentMap->getElevation(player3.getPosY()), terrain, false);
            break;
        case 3:
            player4.draw(c, r, a, d, currentMap->getElevation(player4.getPosY()), terrain, false);
            break;
        case 4:
            player5.draw(c, r, a, d, currentMap->getElevation(player5.getPosY()), terrain, false);
    }

    // Draw the vehicle of the player
    if (typeOfGame == 0 || typeOfGame == 2){
        showHudInterfaceWorldTourPolePosition(c);
    }
    else {
        showHudInterfaceOutRunDrivingFuryDerramage(c);
    }

    if (newLap){
        if (lapsDone < numberLaps){
            r.soundEffects[55]->pause();
        }
        else {
            r.soundEffects[56]->pause();
        }
        drawNewLap(c);
    }

    c.w.display();
    const Texture bgTexture(c.w.getTexture());
    Sprite bgSprite(bgTexture);
    bgSprite.setScale(float(c.window.getSize().x) / float(c.w.getSize().x),
                      float(c.window.getSize().y) / float(c.w.getSize().y));

    c.w.clear();
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));
    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Game in pause
    mtx.lock();
    onPause = true;
    mtx.unlock();

    // Wait until all threads are death
    if (!comeFromOptions){
        timer0.join();
        timer1.join();
        if (typeOfGame != 0 && typeOfGame != 2){
            timer2.join();
        }
    }

    // Control if the pause menu configuration file has been read or not
    if (!c.pauseMenuRead){
        // Read the pause menu xml configuration file
        string pathFile = "Data/Menus/PauseMenu/Configuration/PauseMenu.xml";
        loadPauseMenuConfiguration(pathFile, c);
    }
    else {
        // Restart all the buttons to its initial state
        Button b = Button(c.w.getSize().x / 2.f - 95.0f * c.screenScale, c.w.getSize().y / 2.f - 70.0f * c.screenScale,
                          200.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenuPauseButtons, c.pauseMenuButtons[0].getTextButton(),
                          c.pauseMenuButtons[0].getIdleColorButton(), c.pauseMenuButtons[0].getHoverColorButton(),
                          c.pauseMenuButtons[0].getFontColorButton(), 1, c.screenScale);

        c.pauseMenuButtons[0] = b;

        for (int i = 1; i < int(c.pauseMenuButtons.size()); i++){
            // Change the state of the first color
            Button b = Button(c.w.getSize().x / 2.f - 95.0f * c.screenScale, c.w.getSize().y / 2.f - (70.0f - i * 70.f) * c.screenScale,
                              200.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenuPauseButtons, c.pauseMenuButtons[i].getTextButton(),
                              c.pauseMenuButtons[i].getIdleColorButton(), c.pauseMenuButtons[i].getHoverColorButton(),
                              c.pauseMenuButtons[i].getFontColorButton(), 0, c.screenScale);

            c.pauseMenuButtons[i] = b;
        }
    }

    // Stop the music of the level
    r.soundTracks[r.currentSoundtrack]->pause();

    RectangleShape shape;
    shape.setPosition(0, 0);
    shape.setSize(Vector2f(c.w.getSize().x, c.w.getSize().y));
    shape.setFillColor(Color(0, 0, 0, 200));

    RectangleShape pauseShape;
    pauseShape.setPosition(c.w.getSize().x / 2.f - 120.0f * c.screenScale, c.w.getSize().y / 2.f - 180.0f * c.screenScale);
    pauseShape.setSize(sf::Vector2f(250.0f * c.screenScale, 400.0f * c.screenScale));
    pauseShape.setFillColor(c.colorInsidePanelPauseMenu);
    pauseShape.setOutlineColor(c.colorBorderPanelPauseMenu);
    pauseShape.setOutlineThickness(5.0f * c.screenScale);

    Text textMenu;
    textMenu.setFont(c.fontPauseMenu);
    textMenu.setFillColor(c.colorTitleTextPauseMenu);
    textMenu.setOutlineColor(c.colorTitleBorderPauseMenu);
    textMenu.setOutlineThickness(2.0f * c.screenScale);
    textMenu.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));
    textMenu.setString(c.contentTitlePauseMenu);
    textMenu.setPosition(c.w.getSize().x / 2.f - textMenu.getLocalBounds().width / 2.f,
                         c.w.getSize().y / 2.f - 150.0f * c.screenScale);

    // Control if the start key is pressed or not
    bool startPressed = false;

    // Control the option selected by the user
    int optionSelected = 0;

    // While the start button has not been pressed
    while (!startPressed) {
        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return EXIT;
            }
        }

        // Check if the up or down cursor keys have been pressed or not
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            // Up cursor pressed and change the soundtrack selected in the list
            if (optionSelected != int(c.pauseMenuButtons.size() - 1)) {
                // Change the color appearance of both buttons
                r.soundEffects[0]->stop();
                r.soundEffects[0]->play();
                optionSelected++;
                c.pauseMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                c.pauseMenuButtons[optionSelected - 1].setButtonState(BUTTON_IDLE);
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::Up)) {
            // Down cursor pressed and change the soundtrack selected in the list
            if (optionSelected != 0) {
                r.soundEffects[0]->stop();
                r.soundEffects[0]->play();
                optionSelected--;
                // Change the color appearance of both buttons
                c.pauseMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                c.pauseMenuButtons[optionSelected + 1].setButtonState(BUTTON_IDLE);
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            if (comeFromOptions) {
                comeFromOptions = false;
            } else {
                startPressed = true;
            }
        }

        c.w.draw(bgSprite);

        c.w.draw(shape);

        c.w.draw(pauseShape);
        c.w.draw(textMenu);

        for (Button b : c.pauseMenuButtons) {
            b.render(&c.w);
        }

        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();
        sleep(milliseconds(100));
    }

    r.soundEffects[2]->stop();
    r.soundEffects[2]->play();

    if (c.enablePixelArt) {
        if (c.isDefaultScreen)
            c.window.setView(View(Vector2f(DEFAULT_WIDTH / 4.0f, DEFAULT_HEIGHT / 4.0f),
                                  Vector2f(DEFAULT_WIDTH / 2.0f, DEFAULT_HEIGHT / 2.0f)));
        else
            c.window.setView(View(Vector2f(SCREEN_HD_WIDTH / 4.0f, SCREEN_HD_HEIGHT / 4.0f),
                                  Vector2f(SCREEN_HD_WIDTH / 2.0f, SCREEN_HD_HEIGHT / 2.0f)));
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));
        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);
    }

    // Check the option selected by the user
    switch (optionSelected) {
        case 0:
            // Resume button selected and reanudate the music
            mtx.lock();
            onPause = false;
            mtx.unlock();
            if (newLap){
                if (lapsDone < numberLaps){
                    r.soundEffects[55]->play();
                }
                else {
                    r.soundEffects[56]->play();
                }
            }
            return PLAY_GAME;
        case 1:
            // Options button selected
            return OPTIONS;
        case 2:
            // Quit button selected
            mtx.lock();
            onPause = false;
            finalGame = true;
            arrival = false;
            mtx.unlock();
            return START;
        default:
            return EXIT;
    }
}



/**
 * Load the configuration of the vehicle selection menu in its xml file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void Game::loadVehicleSelectionMenuConfiguration(const string path, Configuration& c){

    // Open the xml file of the configuration
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Local variables to store the information
    string backgroundTexture, content, fontPath, colorKind;

    // Iterate to get the information of the vehicle selection menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check if its the node of the background information
        if ((string)property->name() == "Background"){
            // Get the background image of the menu
            backgroundTexture = (string)property->value();
            c.backgroundSelectionMenu.loadFromFile(backgroundTexture);
        }
        // Check if its the node of the title
        else if ((string)property->name() == "Title"){
            // Iterate to get the information of the title
            for (xml_node<> *titleProp = property->first_node(); titleProp; titleProp = titleProp->next_sibling()){
                // Get the red color channel
                if ((string)titleProp->name() == "Content"){
                    // Get the content of the title
                    content = (string)titleProp->value();
                    c.contentTitleVehicleSelectionMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontVehicleSelectionMenu.loadFromFile(fontPath);
                }
                // Get color text of the title
                else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                    // Get the kind of color to process
                    colorKind = (string)titleProp->name();
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the player menu
                    for (xml_node<> *colorChannel = titleProp->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                        // Get the red color channel
                        if ((string)colorChannel->name() == "R"){
                            // Get the red channel
                            colorRed = stoi(colorChannel->value());
                        }
                        // Get the green color channel
                        else if ((string)colorChannel->name() == "G"){
                            // Get the red channel
                            colorGreen = stoi(colorChannel->value());
                        }
                        // Get the blue color channel
                        else if ((string)colorChannel->name() == "B"){
                            // Get the red channel
                            colorBlue = stoi(colorChannel->value());
                        }
                    }
                    // Check if it is the color of the text
                    if (colorKind == "ColorText"){
                        c.colorTitleTextVehicleSelectionMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderVehicleSelectionMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
        // Check if its the node of the vehicle panel
        else if ((string)property->name() == "VehiclePanel"){
            // Iterate throughout the information of the vehicle panel
            for (xml_node<> *vehiclePanel = property->first_node(); vehiclePanel; vehiclePanel = vehiclePanel->next_sibling()){
                // Check if its the node of the title
                if ((string)vehiclePanel->name() == "Title"){
                    // Iterate to get the information of the title
                    for (xml_node<> *titleProp = vehiclePanel->first_node(); titleProp; titleProp = titleProp->next_sibling()){
                        // Get the green color channel
                        if ((string)titleProp->name() == "Font"){
                            // Read the font from the file
                            fontPath = (string)titleProp->value();
                            c.fontVehicleSelectionMenuPanelTitle.loadFromFile(fontPath);
                        }
                        // Get color text of the title
                        else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                            // Get the kind of color to process
                            colorKind = (string)titleProp->name();
                            // Get the border color of the panel
                            int colorRed = 0, colorGreen = 0, colorBlue = 0;
                            // Iterate to get the information of the player menu
                            for (xml_node<> *colorChannel = titleProp->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                                // Get the red color channel
                                if ((string)colorChannel->name() == "R"){
                                    // Get the red channel
                                    colorRed = stoi(colorChannel->value());
                                }
                                // Get the green color channel
                                else if ((string)colorChannel->name() == "G"){
                                    // Get the red channel
                                    colorGreen = stoi(colorChannel->value());
                                }
                                // Get the blue color channel
                                else if ((string)colorChannel->name() == "B"){
                                    // Get the red channel
                                    colorBlue = stoi(colorChannel->value());
                                }
                            }
                            // Check if it is the color of the text
                            if (colorKind == "ColorText"){
                                c.colorTitleTextVehicleSelectionMenuName = Color(colorRed, colorGreen, colorBlue);
                            }
                            // Check if it is the color of the border
                            else if (colorKind == "ColorBorder"){
                                c.colorTitleBorderVehicleSelectionMenuName = Color(colorRed, colorGreen, colorBlue);
                            }
                        }
                    }
                }
                // Check if its the node of the border color of the panel
                else if ((string)vehiclePanel->name() == "ColorBorder"){
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the background menu color
                    for (xml_node<> *colorChannel = vehiclePanel->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                        // Get the red color channel
                        if ((string)colorChannel->name() == "R"){
                            // Get the red channel
                            colorRed = stoi((string)colorChannel->value());
                        }
                        // Get the green color channel
                        else if ((string)colorChannel->name() == "G"){
                            // Get the red channel
                            colorGreen = stoi((string)colorChannel->value());
                        }
                        // Get the blue color channel
                        else if ((string)colorChannel->name() == "B"){
                            // Get the red channel
                            colorBlue = stoi((string)colorChannel->value());
                        }
                    }
                    // Store the color border of the panel
                    c.colorBorderVehiclePanel = Color(colorRed, colorGreen, colorBlue);
                }
            }
        }
         // Check if its the node of the description panel
        else if ((string)property->name() == "DescriptionPanel"){
            // Iterate throughout the information of the vehicle panel
            for (xml_node<> *vehiclePanel = property->first_node(); vehiclePanel; vehiclePanel = vehiclePanel->next_sibling()){
                // Check if its the node of the title
                if ((string)vehiclePanel->name() == "Title"){
                    // Iterate to get the information of the title
                    for (xml_node<> *titleProp = vehiclePanel->first_node(); titleProp; titleProp = titleProp->next_sibling()){
                        // Get the green color channel
                        if ((string)titleProp->name() == "Font"){
                            // Read the font from the file
                            fontPath = (string)titleProp->value();
                            c.fontVehicleSelectionMenuPanelTitleProp.loadFromFile(fontPath);
                        }
                        // Get color text of the title
                        else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                            // Get the kind of color to process
                            colorKind = (string)titleProp->name();
                            // Get the border color of the panel
                            int colorRed = 0, colorGreen = 0, colorBlue = 0;
                            // Iterate to get the information of the player menu
                            for (xml_node<> *colorChannel = titleProp->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                                // Get the red color channel
                                if ((string)colorChannel->name() == "R"){
                                    // Get the red channel
                                    colorRed = stoi(colorChannel->value());
                                }
                                // Get the green color channel
                                else if ((string)colorChannel->name() == "G"){
                                    // Get the red channel
                                    colorGreen = stoi(colorChannel->value());
                                }
                                // Get the blue color channel
                                else if ((string)colorChannel->name() == "B"){
                                    // Get the red channel
                                    colorBlue = stoi(colorChannel->value());
                                }
                            }
                            // Check if it is the color of the text
                            if (colorKind == "ColorText"){
                                c.colorTitleTextVehicleSelectionMenuProp = Color(colorRed, colorGreen, colorBlue);
                            }
                            // Check if it is the color of the border
                            else if (colorKind == "ColorBorder"){
                                c.colorTitleBorderVehicleSelectionMenuNameProp = Color(colorRed, colorGreen, colorBlue);
                            }
                        }
                    }
                }
                 // Check if its the node of the vehicle properties
                if ((string)vehiclePanel->name() == "Properties"){
                    // Iterate to get the information of the vehicle properties
                    for (xml_node<> *vehicleProp = vehiclePanel->first_node(); vehicleProp; vehicleProp = vehicleProp->next_sibling()){
                        // Check if it is the node of the content information
                        if ((string)vehicleProp->name() == "Content"){
                            // Iterate to get the information of the vehicle properties
                            for (xml_node<> *prop = vehicleProp->first_node(); prop; prop = prop->next_sibling()){
                                // Get the green color channel
                                if ((string)prop->name() == "Font"){
                                    // Read the font from the file
                                    fontPath = (string)prop->value();
                                    c.fontVehicleSelectionMenuPanelProp.loadFromFile(fontPath);
                                }
                                // Get color text of the title
                                else if ((string)prop->name() == "ColorText" || (string)prop->name() == "ColorBorder" ||
                                         (string)prop->name() == "ColorInside")
                                {
                                    // Get the kind of color to process
                                    colorKind = (string)prop->name();
                                    // Get the border color of the panel
                                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                                    // Iterate to get the information of the player menu
                                    for (xml_node<> *colorChannel = prop->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                                        // Get the red color channel
                                        if ((string)colorChannel->name() == "R"){
                                            // Get the red channel
                                            colorRed = stoi(colorChannel->value());
                                        }
                                        // Get the green color channel
                                        else if ((string)colorChannel->name() == "G"){
                                            // Get the red channel
                                            colorGreen = stoi(colorChannel->value());
                                        }
                                        // Get the blue color channel
                                        else if ((string)colorChannel->name() == "B"){
                                            // Get the red channel
                                            colorBlue = stoi(colorChannel->value());
                                        }
                                    }
                                    // Check if it is the color of the text
                                    if (colorKind == "ColorText"){
                                        c.colorTextVehicleSelectionProp = Color(colorRed, colorGreen, colorBlue);
                                    }
                                    // Check if it is the color of the border
                                    else if (colorKind == "ColorBorder"){
                                        c.colorBorderVehicleSelectionProp = Color(colorRed, colorGreen, colorBlue);
                                    }
                                    // Check if it is the inside color of the vehicle properties panel
                                    else if (colorKind == "ColorInside"){
                                        c.colorInsideVehicleSelectionMenuPanelProp = Color(colorRed, colorGreen, colorBlue);
                                    }
                                }
                            }
                        }
                        // Check if it is the node of the border color
                        else if ((string)vehicleProp->name() == "ColorBorder"){
                            int colorRed = 0, colorGreen = 0, colorBlue = 0;
                            // Iterate to get the information of the background menu color
                            for (xml_node<> *colorChannel = vehicleProp->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                                // Get the red color channel
                                if ((string)colorChannel->name() == "R"){
                                    // Get the red channel
                                    colorRed = stoi((string)colorChannel->value());
                                }
                                // Get the green color channel
                                else if ((string)colorChannel->name() == "G"){
                                    // Get the red channel
                                    colorGreen = stoi((string)colorChannel->value());
                                }
                                // Get the blue color channel
                                else if ((string)colorChannel->name() == "B"){
                                    // Get the red channel
                                    colorBlue = stoi((string)colorChannel->value());
                                }
                            }
                            // Store the color border of the panel
                            c.colorBorderPropertiesPanel = Color(colorRed, colorGreen, colorBlue);
                        }
                    }
                }
            }
        }
        // Check the color buttons of the menu
        else if ((string)property->name() == "Buttons"){
            int colorRed = 0, colorGreen = 0, colorBlue = 0;
            // Iterate to get the information of the color buttons
            for (xml_node<> *colorChannel = property->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                // Iterate to get the information of the background menu color
                for (xml_node<> *color = colorChannel->first_node(); color; color = color->next_sibling()){
                    // Get the red color channel
                    if ((string)color->name() == "R"){
                        // Get the red channel
                        colorRed = stoi((string)color->value());
                    }
                    // Get the green color channel
                    else if ((string)color->name() == "G"){
                        // Get the red channel
                        colorGreen = stoi((string)color->value());
                    }
                    // Get the blue color channel
                    else if ((string)color->name() == "B"){
                        // Get the red channel
                        colorBlue = stoi((string)color->value());
                    }
                }
                // Store the color border of the panel
                c.vehicleSelectionMenuColorButtons.push_back(Color(colorRed, colorGreen, colorBlue));
            }
        }
    }
    // Tge file has been read correctly
    c.vehicleSelectionMenuRead = true;
}



/**
 * Load the configuration of the vehicle selection menu in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
State Game::selectionVehicleMenu(Configuration& c, SoundPlayer& r){

    c.w.clear();
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));
    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Check if the vehicle selection menu has been read
    if (!c.vehicleSelectionMenuRead){
        // Read the configuration of the xml file
        string path = "Data/Menus/VehicleSelectionMenu/Configuration/VehicleSelectionMenu.xml";
        loadVehicleSelectionMenuConfiguration(path, c);
    }

    // Loading the background texture
    Texture carTexture;
    carTexture.loadFromFile("Data/Menus/VehicleSelectionMenu/Images/image.png");
    carTexture.setRepeated(true);
    c.backgroundSelectionMenu.setRepeated(true);

    r.soundTracks[16]->play();

    // Control if the player presses the start key or not
    bool startPressed = false;

    // Control if the player presses the backspace key or not
    bool backSpacePressed = false;

    // Control the vehicle selected by the player
    int optionSelected, colorSelected;

    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Load the textures of the vehicles to show
    Texture t;
    Texture vehicleTextures[4][8];

    string path = "", imageCode = "";

    // Array of the vehicle's names
    string vehicleNames[4][8];

    // Array of the  motor types of the vehicles
    string motorNames[4][8];

    // Array of the  maximum speed of the vehicles
    float speedVehicles[4][8];

    // Array of the angle of the vehicles
    float angleVehicles[4][8];

    // Variables to store the vehicle properties
    string brandName, motorName, pathFile;
    float max_speed, angle;

    for (int i = 0; i < 4; i++){
        if (i == 0){
            path = "Data/Vehicles/Motorbikes/Motorbike";
            imageCode = "c59.png";
        }
        else if (i == 1){
            path = "Data/Vehicles/Devastators/Devastator";
            imageCode = "c57.png";
        }
        else if (i == 2){
            path = "Data/Vehicles/Minivans/Minivan";
            imageCode = "c49.png";
        }
        else {
            path = "Data/Vehicles/Trucks/Truck";
            imageCode = "c75.png";
        }
        for (int j = 0; j < 8; j++){
            t.loadFromFile(path + to_string(j + 1) + "/Images/" + imageCode);
            vehicleTextures[i][j] = t;

            loadVehicleProperties(path + to_string(j + 1) + "/Configuration/Configuration.xml", brandName, max_speed, angle, motorName);
            vehicleNames[i][j] = brandName;
            motorNames[i][j] = motorName;
            angleVehicles[i][j] = angle;
            speedVehicles[i][j] = max_speed;
        }
    }

    // Show the vehicle selected
    Sprite vehicleCar;

    vehicleCar.setTexture(vehicleTextures[0][0], true);
    vehicleCar.setScale(1.6f * c.screenScale, 1.6f * c.screenScale);
    vehicleCar.setPosition((c.w.getSize().x / 2.f) + 160.0f * c.screenScale, c.w.getSize().y / 2.f - 25.f * c.screenScale);

    // While start and backspace have not been pressed
    while (!startPressed && !backSpacePressed) {

        optionSelected = 0;
        colorSelected = 0;

        IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
        Sprite sprite(c.backgroundSelectionMenu, background);
        float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
        float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
        sprite.setScale(axis_x, axis_y);

        Sprite garage;
        garage.setTexture(carTexture, true);

        if (c.w.getSize().x != DEFAULT_WIDTH && c.w.getSize().y != DEFAULT_HEIGHT){
            garage.setScale(float(c.w.getSize().x) / DEFAULT_WIDTH, float(c.w.getSize().y) / DEFAULT_HEIGHT * 1.34f);
        }
        garage.setPosition((c.w.getSize().x / 2.f) + 80.0f * c.screenScale, c.w.getSize().y / 2.f - 163.0f * c.screenScale);

        RectangleShape vehicleShape;
        vehicleShape.setPosition((c.w.getSize().x / 2.f) + 80.0f * c.screenScale, c.w.getSize().y / 2.f - 163.0f * c.screenScale);
        vehicleShape.setSize(sf::Vector2f(318.0f * c.screenScale, 350.0f * c.screenScale));
        vehicleShape.setOutlineColor(c.colorBorderVehiclePanel);
        vehicleShape.setOutlineThickness(5.0f * c.screenScale);

        RectangleShape descriptionShape;
        descriptionShape.setPosition((c.w.getSize().x / 2.f) - 400.0f * c.screenScale, c.w.getSize().y / 2.f - 163.0f * c.screenScale);
        descriptionShape.setSize(sf::Vector2f(360.0f * c.screenScale, 350.0f * c.screenScale));
        descriptionShape.setOutlineColor(c.colorBorderPropertiesPanel);
        descriptionShape.setOutlineThickness(5.0f * c.screenScale);
        descriptionShape.setFillColor(c.colorInsideVehicleSelectionMenuPanelProp);

        // Main Text of the menu
        Text selectionVehicleText;
        selectionVehicleText.setString(c.contentTitleVehicleSelectionMenu);
        selectionVehicleText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        selectionVehicleText.setFont(c.fontVehicleSelectionMenu);
        selectionVehicleText.setStyle(Text::Bold | Text::Underlined);
        selectionVehicleText.setFillColor(c.colorTitleTextVehicleSelectionMenu);
        selectionVehicleText.setOutlineColor(c.colorTitleBorderVehicleSelectionMenu);
        selectionVehicleText.setOutlineThickness(5.0f * c.screenScale);
        selectionVehicleText.setPosition(c.w.getSize().x / 2.f - selectionVehicleText.getLocalBounds().width / 2.f,
                                         c.w.getSize().y / 2.f - 240.0f * c.screenScale);

        // Main Text of the menu
        Text vehiclePropertiesText;
        vehiclePropertiesText.setString("PROPERTIES");
        vehiclePropertiesText.setPosition(c.w.getSize().x / 2.f - 295.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);
        vehiclePropertiesText.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
        vehiclePropertiesText.setFont(c.fontVehicleSelectionMenuPanelTitleProp);
        vehiclePropertiesText.setStyle(Text::Bold | Text::Underlined);
        vehiclePropertiesText.setFillColor(c.colorTitleTextVehicleSelectionMenuProp);
        vehiclePropertiesText.setOutlineColor(c.colorTitleBorderVehicleSelectionMenuNameProp);
        vehiclePropertiesText.setOutlineThickness(3.0f * c.screenScale);

        // Vehicle Properties
        Text speedVehicleText;
        speedVehicleText.setString("TOP SPEED: ");
        speedVehicleText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale, c.w.getSize().y / 2.f - 75.0f * c.screenScale);
        speedVehicleText.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        speedVehicleText.setFont(c.fontVehicleSelectionMenuPanelProp);
        speedVehicleText.setStyle(Text::Bold);
        speedVehicleText.setFillColor(c.colorTextVehicleSelectionProp);
        speedVehicleText.setOutlineColor(c.colorBorderVehicleSelectionProp);
        speedVehicleText.setOutlineThickness(2.0f * c.screenScale);

        Text angleTurnText;
        angleTurnText.setString("ANGLE OF TURN: ");
        angleTurnText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale, c.w.getSize().y / 2.f  - 5.f * c.screenScale);
        angleTurnText.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        angleTurnText.setFont(c.fontVehicleSelectionMenuPanelProp);
        angleTurnText.setStyle(Text::Bold);
        angleTurnText.setFillColor(c.colorTextVehicleSelectionProp);
        angleTurnText.setOutlineColor(c.colorBorderVehicleSelectionProp);
        angleTurnText.setOutlineThickness(2.0f * c.screenScale);

        Text motorText;
        motorText.setString("MOTOR: ");
        motorText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale, c.w.getSize().y / 2.f + 65.0f * c.screenScale);
        motorText.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        motorText.setFont(c.fontVehicleSelectionMenuPanelProp);
        motorText.setStyle(Text::Bold);
        motorText.setFillColor(c.colorTextVehicleSelectionProp);
        motorText.setOutlineColor(c.colorBorderVehicleSelectionProp);
        motorText.setOutlineThickness(2.0f * c.screenScale);

        Text accelerationText;
        accelerationText.setString("0 - " + to_string(int(player.getTopSpeed()) / 2) + " KM/H:");
        accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale, c.w.getSize().y / 2.f + 135.0f * c.screenScale);
        accelerationText.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        accelerationText.setFont(c.fontVehicleSelectionMenuPanelProp);
        accelerationText.setStyle(Text::Bold);
        accelerationText.setFillColor(c.colorTextVehicleSelectionProp);
        accelerationText.setOutlineColor(c.colorBorderVehicleSelectionProp);
        accelerationText.setOutlineThickness(2.0f * c.screenScale);

        // Main Text of the menu
        Text vehicleName;
        vehicleName.setString(vehicleNames[0][0]);
        vehicleName.setPosition(c.w.getSize().x / 2.f + 143.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);
        vehicleName.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
        vehicleName.setFont(c.fontVehicleSelectionMenuPanelTitle);
        vehicleName.setStyle(Text::Bold | Text::Underlined);
        vehicleName.setFillColor(c.colorTitleTextVehicleSelectionMenuName);
        vehicleName.setOutlineColor(c.colorTitleBorderVehicleSelectionMenuName);
        vehicleName.setOutlineThickness(3.0f * c.screenScale);

        Text speed;
        speed.setString(to_string(int(speedVehicles[0][0])) + " KM/H");
        speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                     c.w.getSize().y / 2.f - 75.0f * c.screenScale);
        speed.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        speed.setFont(c.fontVehicleSelectionMenuPanelProp);
        speed.setStyle(Text::Bold);
        speed.setFillColor(c.colorTextVehicleSelectionProp);
        speed.setOutlineColor(c.colorBorderVehicleSelectionProp);
        speed.setOutlineThickness(2.0f * c.screenScale);

        Text angle;
        string value = to_string(angleVehicles[0][0]);
        angle.setString(value.substr(0, value.find(".") + 3) + " RAD/S");
        angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                          c.w.getSize().y / 2.f - 5.0f * c.screenScale);
        angle.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        angle.setFont(c.fontVehicleSelectionMenuPanelProp);
        angle.setStyle(Text::Bold);
        angle.setFillColor(c.colorTextVehicleSelectionProp);
        angle.setOutlineColor(c.colorBorderVehicleSelectionProp);
        angle.setOutlineThickness(2.0f * c.screenScale);

        Text motor;
        motor.setString(motorNames[0][0]);
        motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                          c.w.getSize().y / 2.f + 65.0f * c.screenScale);
        motor.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        motor.setFont(c.fontVehicleSelectionMenuPanelProp);
        motor.setStyle(Text::Bold);
        motor.setFillColor(c.colorTextVehicleSelectionProp);
        motor.setOutlineColor(c.colorBorderVehicleSelectionProp);
        motor.setOutlineThickness(2.0f * c.screenScale);

        Text acceleration;
        value = to_string((speedVehicles[0][0] / 2.f) / TIME_HALF_SPEED);
        acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
        acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                 c.w.getSize().y / 2.f + 135.0f * c.screenScale);
        acceleration.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        acceleration.setFont(c.fontVehicleSelectionMenuPanelProp);
        acceleration.setStyle(Text::Bold);
        acceleration.setFillColor(c.colorTextVehicleSelectionProp);
        acceleration.setOutlineColor(c.colorBorderVehicleSelectionProp);
        acceleration.setOutlineThickness(2.0f * c.screenScale);

        CircleShape triangle(30 * c.screenScale, 3);
        triangle.setFillColor(c.vehicleSelectionMenuColorButtons[0]);
        triangle.setOutlineColor(c.vehicleSelectionMenuColorButtons[3]);
        triangle.setOutlineThickness(2.0f * c.screenScale);
        triangle.setRotation(30);
        triangle.setPosition(c.w.getSize().x / 2.f - 20.0f * c.screenScale, c.w.getSize().y / 2.f + 185.0f * c.screenScale);

        CircleShape triangle2(30 * c.screenScale, 3);
        triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[1]);
        triangle2.setOutlineColor(c.vehicleSelectionMenuColorButtons[3]);
        triangle2.setOutlineThickness(2.0f * c.screenScale);
        triangle2.setRotation(90);
        triangle2.setPosition(c.w.getSize().x / 2.f + 75.0f * c.screenScale, c.w.getSize().y / 2.f + 196.0f * c.screenScale);

        // Reproduce the sound effect
        r.soundEffects[40]->play();

        // Until the start keyword is not pressed
        while (!startPressed && !backSpacePressed) {

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)){
                if (e.type == Event::Closed){
                    return EXIT;
                }
            }

            // Check if the up or down cursor keys have been pressed or not
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                // Up cursor pressed and change the soundtrack selected in the list
                if (optionSelected != 3) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected++;

                    switch(optionSelected){
                        case 1:

                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 105.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 5.f * c.screenScale);

                            vehicleName.setString(vehicleNames[optionSelected][colorSelected]);
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 143.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(speedVehicles[optionSelected][colorSelected])) + " KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(angleVehicles[optionSelected][colorSelected]);
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(motorNames[optionSelected][colorSelected]);
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((speedVehicles[optionSelected][colorSelected] / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                            break;
                        case 2:

                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(2.7f * c.screenScale, 3.2f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 100.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 30.f * c.screenScale);

                            vehicleName.setString(vehicleNames[optionSelected][colorSelected]);
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 153.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(speedVehicles[optionSelected][colorSelected])) + " KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(angleVehicles[optionSelected][colorSelected]);
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(motorNames[optionSelected][colorSelected]);
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((speedVehicles[optionSelected][colorSelected] / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                            break;
                        case 3:

                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(2.7f * c.screenScale, 3.5f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 90.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 55.f * c.screenScale);

                            vehicleName.setString(vehicleNames[optionSelected][colorSelected]);
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 158.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(speedVehicles[optionSelected][colorSelected])) + " KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(angleVehicles[optionSelected][colorSelected]);
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(motorNames[optionSelected][colorSelected]);
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((speedVehicles[optionSelected][colorSelected] / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                    }
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Left)) {
                // Down cursor pressed and change the soundtrack selected in the list
                if (optionSelected != 0) {
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected--;

                    switch(optionSelected){
                        case 0:
                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(1.6f * c.screenScale, 1.6f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 160.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 25.f * c.screenScale);

                            vehicleName.setString(vehicleNames[optionSelected][colorSelected]);
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 143.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(speedVehicles[optionSelected][colorSelected])) + " KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(angleVehicles[optionSelected][colorSelected]);
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(motorNames[optionSelected][colorSelected]);
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((speedVehicles[optionSelected][colorSelected] / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                            break;
                        case 1:

                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 105.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 5.f * c.screenScale);

                            vehicleName.setString(vehicleNames[optionSelected][colorSelected]);
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 137.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(speedVehicles[optionSelected][colorSelected])) + " KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(angleVehicles[optionSelected][colorSelected]);
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(motorNames[optionSelected][colorSelected]);
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((angleVehicles[optionSelected][colorSelected] / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                            break;
                        case 2:

                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(2.7f * c.screenScale, 3.2f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 100.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 30.f * c.screenScale);

                            vehicleName.setString(vehicleNames[optionSelected][colorSelected]);
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 153.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(speedVehicles[optionSelected][colorSelected])) + " KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(angleVehicles[optionSelected][colorSelected]);
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(motorNames[optionSelected][colorSelected]);
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((speedVehicles[optionSelected][colorSelected] / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                            break;
                        case 3:

                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(2.7f * c.screenScale, 3.5f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 90.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 55.f * c.screenScale);

                            vehicleName.setString(vehicleNames[optionSelected][colorSelected]);
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 158.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(speedVehicles[optionSelected][colorSelected])) + " KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(angleVehicles[optionSelected][colorSelected]);
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(motorNames[optionSelected][colorSelected]);
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((speedVehicles[optionSelected][colorSelected] / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                    }
                }
            }
            // Check if the up or down cursor keys have been pressed or not
            else if (Keyboard::isKeyPressed(Keyboard::Up)) {
                // Up cursor pressed and change the soundtrack selected in the list
                if (colorSelected != 7) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    colorSelected++;

                    switch(optionSelected){
                                                case 0:
                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(1.6f * c.screenScale, 1.6f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 160.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 25.f * c.screenScale);

                            vehicleName.setString(vehicleNames[optionSelected][colorSelected]);
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 143.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(speedVehicles[optionSelected][colorSelected])) + " KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(angleVehicles[optionSelected][colorSelected]);
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(motorNames[optionSelected][colorSelected]);
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((speedVehicles[optionSelected][colorSelected] / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                            break;
                        case 1:

                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 105.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 5.f * c.screenScale);

                            vehicleName.setString(vehicleNames[optionSelected][colorSelected]);
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 143.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(speedVehicles[optionSelected][colorSelected])) + " KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(angleVehicles[optionSelected][colorSelected]);
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(motorNames[optionSelected][colorSelected]);
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((speedVehicles[optionSelected][colorSelected] / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                            break;
                        case 2:

                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(2.7f * c.screenScale, 3.2f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 100.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 30.f * c.screenScale);

                            vehicleName.setString(vehicleNames[optionSelected][colorSelected]);
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 153.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(speedVehicles[optionSelected][colorSelected])) + " KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(angleVehicles[optionSelected][colorSelected]);
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(motorNames[optionSelected][colorSelected]);
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((speedVehicles[optionSelected][colorSelected] / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                            break;
                        case 3:

                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(2.7f * c.screenScale, 3.5f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 90.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 55.f * c.screenScale);

                            vehicleName.setString(vehicleNames[optionSelected][colorSelected]);
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 158.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(speedVehicles[optionSelected][colorSelected])) + " KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(angleVehicles[optionSelected][colorSelected]);
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(motorNames[optionSelected][colorSelected]);
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((speedVehicles[optionSelected][colorSelected] / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                    }
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Down)) {
                // Up cursor pressed and change the soundtrack selected in the list
                if (colorSelected != 0) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    colorSelected--;

                    switch(optionSelected){
                        case 0:
                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(1.6f * c.screenScale, 1.6f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 160.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 25.f * c.screenScale);

                            vehicleName.setString(vehicleNames[optionSelected][colorSelected]);
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 143.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(speedVehicles[optionSelected][colorSelected])) + " KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(angleVehicles[optionSelected][colorSelected]);
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(motorNames[optionSelected][colorSelected]);
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((speedVehicles[optionSelected][colorSelected] / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                            break;
                        case 1:

                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 105.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 5.f * c.screenScale);

                            vehicleName.setString(vehicleNames[optionSelected][colorSelected]);
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 137.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(speedVehicles[optionSelected][colorSelected])) + " KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(angleVehicles[optionSelected][colorSelected]);
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(motorNames[optionSelected][colorSelected]);
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((angleVehicles[optionSelected][colorSelected] / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                            break;
                        case 2:

                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(2.7f * c.screenScale, 3.2f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 100.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 30.f * c.screenScale);

                            vehicleName.setString(vehicleNames[optionSelected][colorSelected]);
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 153.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(speedVehicles[optionSelected][colorSelected])) + " KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(angleVehicles[optionSelected][colorSelected]);
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(motorNames[optionSelected][colorSelected]);
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((speedVehicles[optionSelected][colorSelected] / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                            break;
                        case 3:

                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(2.7f * c.screenScale, 3.5f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 90.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 55.f * c.screenScale);

                            vehicleName.setString(vehicleNames[optionSelected][colorSelected]);
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 158.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(speedVehicles[optionSelected][colorSelected])) + " KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(angleVehicles[optionSelected][colorSelected]);
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(motorNames[optionSelected][colorSelected]);
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((speedVehicles[optionSelected][colorSelected] / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                    }
                }
            }



            c.w.draw(sprite);
            c.w.draw(selectionVehicleText);
            c.w.draw(vehicleShape);
            c.w.draw(garage);
            c.w.draw(descriptionShape);
            c.w.draw(vehiclePropertiesText);
            c.w.draw(vehicleName);
            c.w.draw(speedVehicleText);
            c.w.draw(angleTurnText);
            c.w.draw(motorText);
            c.w.draw(accelerationText);
            c.w.draw(speed);
            c.w.draw(angle);
            c.w.draw(motor);
            c.w.draw(acceleration);
            c.w.draw(vehicleCar);
            c.w.draw(triangle);
            c.w.draw(triangle2);

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
            sleep(milliseconds(160));

            // Check if start has been pressed
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                // Change the controllers of the car
                startPressed = true;
                r.soundEffects[2]->stop();
                r.soundEffects[2]->play();
            }
            // Check if backspace has been pressed
            else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                // Change the controllers of the car
                backSpacePressed = true;
                r.soundEffects[11]->stop();
                r.soundEffects[11]->play();
            }

            switch(optionSelected){
                case 0:
                    triangle.setFillColor(c.vehicleSelectionMenuColorButtons[0]);
                    triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[1]);
                    break;
                case 1:
                case 2:
                    triangle.setFillColor(c.vehicleSelectionMenuColorButtons[1]);
                    triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[1]);
                    break;
                case 3:
                    triangle.setFillColor(c.vehicleSelectionMenuColorButtons[1]);
                    triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[0]);
            }
        }
    }

    r.soundTracks[16]->stop();
    r.soundEffects[40]->stop();

    if (c.enablePixelArt) {
        if (c.isDefaultScreen)
            c.window.setView(View(Vector2f(DEFAULT_WIDTH / 4.0f, DEFAULT_HEIGHT / 4.0f),
                                  Vector2f(DEFAULT_WIDTH / 2.0f, DEFAULT_HEIGHT / 2.0f)));
        else
            c.window.setView(View(Vector2f(SCREEN_HD_WIDTH / 4.0f, SCREEN_HD_HEIGHT / 4.0f),
                                  Vector2f(SCREEN_HD_WIDTH / 2.0f, SCREEN_HD_HEIGHT / 2.0f)));
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));
        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);
    }

    if (backSpacePressed){
        r.soundTracks[1]->play();
        if (typeOfGame == 2){
            return CIRCUIT_SELECTION_MENU;
        }
        else {
            return GAME_MODES_MENU;
        }
    }
    else if (startPressed){

        // Store the car selected by the player
        typeOfVehicle = optionSelected;
        colorCarSelected = colorSelected;

        if (typeOfGame != 3){

            switch(typeOfVehicle){
            case 0:
                // Create the motorbike vehicle
                player = Motorbike(speedVehicles[optionSelected][colorSelected], SPEED_FACTOR,
                         speedVehicles[optionSelected][colorSelected] * ACCELERATION_INCREMENT / MAX_SPEED, 2.5f, 2.5f,
                         COUNTER, "Data/Vehicles/Motorbikes/Motorbike" + to_string(colorSelected + 1), 0.0f, RECTANGLE,
                         vehicleNames[optionSelected][colorSelected], angleVehicles[optionSelected][colorSelected],
                         motorNames[optionSelected][colorSelected]);
                break;
            case 1:
                // Create the Devastator vehicle
                player2 = Devastator(speedVehicles[optionSelected][colorSelected], SPEED_FACTOR,
                          speedVehicles[optionSelected][colorSelected] * ACCELERATION_INCREMENT / MAX_SPEED, 4.f, 4.f,
                          COUNTER,  "Data/Vehicles/Devastators/Devastator" + to_string(colorSelected + 1), 0.0f, RECTANGLE,
                          vehicleNames[optionSelected][colorSelected], angleVehicles[optionSelected][colorSelected],
                          motorNames[optionSelected][colorSelected]);
                break;
            case 2:
                // Create the minivan vehicle
                player3 = Minivan(speedVehicles[optionSelected][colorSelected], SPEED_FACTOR,
                          speedVehicles[optionSelected][colorSelected] * ACCELERATION_INCREMENT / MAX_SPEED, 4.f, 4.f,
                          COUNTER,  "Data/Vehicles/Minivans/Minivan" + to_string(colorSelected + 1), 0.0f, RECTANGLE,
                          vehicleNames[optionSelected][colorSelected], angleVehicles[optionSelected][colorSelected],
                          motorNames[optionSelected][colorSelected]);
                break;
            case 3:
                // Load the properties of the Truck
                player4 = Truck(speedVehicles[optionSelected][colorSelected], SPEED_FACTOR,
                          speedVehicles[optionSelected][colorSelected] * ACCELERATION_INCREMENT / MAX_SPEED, 4.5f, 4.5f,
                          COUNTER, "Data/Vehicles/Trucks/Truck" + to_string(colorSelected + 1), 0.0f, RECTANGLE,
                          vehicleNames[optionSelected][colorSelected], angleVehicles[optionSelected][colorSelected],
                          motorNames[optionSelected][colorSelected]);
            }
        }
        // Store the rival cars
        if (typeOfGame == 0 || typeOfGame == 2){
            // Store the rival cars in the vector
            storingRivalCars(c);
        }

        if (typeOfGame == 2){
            return LOADING;
        }
        else {
            return LOAD_GAME;
        }
    }
    return EXIT;
}



void Game::readRecordFromLandScape(const string path, string& namePlayer, int& minutesLap, int& secondsLap, int& centsSecondLap){

    // Open the xml file of the scenario
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Iterate to get the information of the player menu
    for (xml_node<> *record = menuNode->first_node(); record; record = record->next_sibling()){
        // Check it is the node that contains the information of the player's name
        if ((string)record->name() == "NamePlayer"){
            // Get the background image of the menu
            namePlayer = (string)record->value();
        }
        else if ((string)record->name() == "Minutes"){
            // Get the minutes of the record time
            minutesLap = stoi(record->value());
        }
        else if ((string)record->name() == "Seconds"){
            // Get the seconds of the record time
            secondsLap = stoi(record->value());
        }
        else if ((string)record->name() == "HundredthsOfSecond"){
            // Get the hundredths of second of the record time
            centsSecondLap = stoi(record->value());
        }
    }
}



void Game::writeRecordFromLandScape(const string path, string namePlayer, int minutesLap, int secondsLap, int centsSecondLap){
    // xml file which stores the player with the highest score in the level
    ofstream theFile (path);
    xml_document<> doc;

    // Add the headers to the file
    xml_node<>* decl = doc.allocate_node(node_declaration);
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "UTF-8"));
    doc.append_node(decl);

    // Create the node record
    xml_node<>* root = doc.allocate_node(node_element, "Record");
    doc.append_node(root);

    // Create a node with the new name of the player
    xml_node<>* name = doc.allocate_node(node_element, "NamePlayer");
    root->append_node(name);
    name->value(namePlayer.c_str());

    // Create a new node with the minutes of the time's player
    xml_node<>* minutes = doc.allocate_node(node_element, "Minutes");
    root->append_node(minutes);
    minutes->value(to_string(minutesLap).c_str());

    // Create a new node with the seconds of the time's player
    xml_node<>* seconds = doc.allocate_node(node_element, "Seconds");
    root->append_node(seconds);
    seconds->value(to_string(secondsLap).c_str());

    // Create a new node with the hundredths of seconds of the time's player
    xml_node<>* hundredtsOfSeconds = doc.allocate_node(node_element, "HundredthsOfSecond");
    root->append_node(hundredtsOfSeconds);
    hundredtsOfSeconds->value(to_string(centsSecondLap).c_str());

    // Store the new xml file configuration
    theFile << doc;
    theFile.close();
    doc.clear();
}



State Game::classificationRace(Configuration& c, SoundPlayer& r){

    // Clean the cars
    cars.clear();

    // Loads enemies and time
    checkDifficulty(c);

    // Update the rival cars
    if (typeOfGame == 0) {
        storingRivalCars(c);
    }

    // Set the scale of the console window
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));
    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    Texture t;
    t.loadFromFile("Data/Animations/ClassificationRaceAnimation/cover.png");
    t.setRepeated(true);
    t.setSmooth(true);

    // Global rectangle of the background
    IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
    Sprite sprite(t, background);
    float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
    float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
    sprite.setScale(axis_x, axis_y);

    // Control if the start key is pressed
    bool startPressed = false;

    // Offset of the rectangle shape
    float offsetY = 700.f;

    float offsetTitleText = -1.0f;

    float offsetTimeLapTexts = 3.0f;

    float carOffset = 1.f;

    Text recordText;
    recordText.setString("NEW RECORD");
    recordText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    recordText.setFont(c.fontMenus);
    recordText.setStyle(Text::Bold);
    recordText.setFillColor(Color(64, 147, 225));
    recordText.setOutlineColor(Color::Black);
    recordText.setOutlineThickness(3.0f * c.screenScale);
    recordText.setPosition((c.w.getSize().x / 2.f) - (recordText.getLocalBounds().width / 2.f), c.w.getSize().y / 2.f + 175.0f * c.screenScale);

    // Vehicle sprite
    Sprite vehicle;
    Texture vehicleTexture;

    bool soundMap = false;

    r.soundEffects[47]->stop();
    r.soundEffects[47]->play();

    bool mainTextArrived = false;
    bool lapTextsArrived = false;
    bool carSpriteArrived = false;



    // Until start key is pressed
    while(!mainTextArrived && !lapTextsArrived && !carSpriteArrived){

        // Creation of the panel rectangle of the menu
        RectangleShape shape;
        shape.setPosition((c.w.getSize().x / 2.f) - 350.0f * c.screenScale, c.w.getSize().y / 2.f - offsetY * c.screenScale);
        shape.setSize(sf::Vector2f(710.0f * c.screenScale, 490.0f * c.screenScale));
        shape.setOutlineColor(Color::Green);
        shape.setOutlineThickness(5.0f * c.screenScale);
        shape.setFillColor(Color(0, 0, 0, 200));

        // Main Text of the menu
        Text titleText;

        if (typeOfGame == 0){
            titleText.setString(tourLandScapes[indexLandScape].getName());
        }
        else {
            titleText.setString(tourLandScapes[landScapeSelected].getName());
        }

        titleText.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
        titleText.setFont(c.fontMenus);
        titleText.setStyle(Text::Bold);
        titleText.setFillColor(Color::White);
        titleText.setOutlineColor(Color::Black);
        titleText.setOutlineThickness(3.0f * c.screenScale);
        titleText.setPosition(((c.w.getSize().x / 2.f) - (titleText.getLocalBounds().width / 2.f)) * offsetTitleText,
                                c.w.getSize().y / 2.f - 230.0f * c.screenScale);

        // Main Text of the menu
        Text totalTime;
        totalTime.setString("TOTAL TIME");
        totalTime.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        totalTime.setFont(c.fontMenus);
        totalTime.setStyle(Text::Bold);
        totalTime.setFillColor(Color(64, 147, 225));
        totalTime.setOutlineColor(Color::Black);
        totalTime.setOutlineThickness(3.0f * c.screenScale);
        totalTime.setPosition(((c.w.getSize().x / 2.f) - (totalTime.getLocalBounds().width / 2.f)) * offsetTimeLapTexts,
                                c.w.getSize().y / 2.f - 140.0f * c.screenScale);

        // Update the indicators
        string lapTime;
        lapTime = (minutesTrip < 10) ? "0" + to_string(int(minutesTrip)) + ":" : to_string(int(minutesTrip)) + ":";
        lapTime += (secsTrip < 10) ? "0" + to_string(int(secsTrip)) + ":" : to_string(int(secsTrip)) + ":";
        int cent_sec = cents_secondTrip * 100.f;
        lapTime += (cent_sec < 10) ? "0" + to_string(cent_sec) : to_string(cent_sec);

        Text timeLap;
        timeLap.setString(lapTime);
        timeLap.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        timeLap.setFont(c.fontMenus);
        timeLap.setStyle(Text::Bold);
        timeLap.setFillColor(Color(64, 147, 225));
        timeLap.setOutlineColor(Color::Black);
        timeLap.setOutlineThickness(3.0f * c.screenScale);
        timeLap.setPosition(((c.w.getSize().x / 2.f) - (timeLap.getLocalBounds().width / 2.f)) * offsetTimeLapTexts,
                              c.w.getSize().y / 2.f - 80.0f * c.screenScale);

        switch(typeOfVehicle){
            case 0:
                vehicleTexture.loadFromFile("Data/Vehicles/Motorbikes/Motorbike" + to_string(colorCarSelected + 1) + "/Images/c60.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(1.6f * c.screenScale, 1.6f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 90.0f * c.screenScale, c.w.getSize().y / carOffset - 2.f * c.screenScale);
                break;
            case 1:
                vehicleTexture.loadFromFile("Data/Vehicles/Devastators/Devastator" + to_string(colorCarSelected + 1) + "/Images/c38.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset + 17.f * c.screenScale);
                break;
            case 2:
                vehicleTexture.loadFromFile("Data/Vehicles/Minivans/Minivan" + to_string(colorCarSelected + 1) + "/Images/c30.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(2.7f * c.screenScale, 3.2f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset - 14.f * c.screenScale);
                break;
            case 3:
                vehicleTexture.loadFromFile("Data/Vehicles/Trucks/Truck" + to_string(colorCarSelected + 1) + "/Images/c56.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(2.7f * c.screenScale, 3.5f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset - 20.f * c.screenScale);
        }

        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return EXIT;
            }
        }

        c.w.draw(sprite);
        c.w.draw(shape);

        if (offsetTitleText < 1.f){
            offsetTitleText += 0.1;
        }
        else {
            mainTextArrived = true;
        }

        if (offsetTimeLapTexts > 1.1f){
            offsetTimeLapTexts -= 0.1;
        }
        else {
            lapTextsArrived = true;
        }

        if (carOffset < 2.0f){
            carOffset += 0.04705;
        }
        else {
            carSpriteArrived = true;
        }

        if (offsetY > 250.f){
            offsetY -= 35.f;
        }
        else {
            if (!soundMap){
                soundMap = true;
                r.soundEffects[46]->stop();
                r.soundEffects[46]->play();
            }
        }

        c.w.draw(titleText);
        c.w.draw(totalTime);
        c.w.draw(timeLap);
        c.w.draw(vehicle);

        bufferSprite.setTexture(c.w.getTexture(), true);
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

         // Check if the start keyword has been pressed
        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            // Pass to the second menu
            startPressed = true;
            r.soundEffects[1]->stop();
            r.soundEffects[1]->play();
        }

        sleep(milliseconds(50));
    }


    // Creation of the panel rectangle of the menu
    RectangleShape shape;
    shape.setPosition((c.w.getSize().x / 2.f) - 350.0f * c.screenScale, c.w.getSize().y / 2.f - offsetY * c.screenScale);
    shape.setSize(sf::Vector2f(710.0f * c.screenScale, 490.0f * c.screenScale));
    shape.setOutlineColor(Color::Green);
    shape.setOutlineThickness(5.0f * c.screenScale);
    shape.setFillColor(Color(0, 0, 0, 200));

    // Main Text of the menu
    Text titleText;

    if (typeOfGame == 0){
        titleText.setString(tourLandScapes[indexLandScape].getName());
    }
    else {
        titleText.setString(tourLandScapes[landScapeSelected].getName());
    }

    titleText.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
    titleText.setFont(c.fontMenus);
    titleText.setStyle(Text::Bold);
    titleText.setFillColor(Color::White);
    titleText.setOutlineColor(Color::Black);
    titleText.setOutlineThickness(3.0f * c.screenScale);
    titleText.setPosition(((c.w.getSize().x / 2.f) - (titleText.getLocalBounds().width / 2.f)) * offsetTitleText,
                            c.w.getSize().y / 2.f - 230.0f * c.screenScale);

    // Main Text of the menu
    Text totalTime;
    totalTime.setString("TOTAL TIME");
    totalTime.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    totalTime.setFont(c.fontMenus);
    totalTime.setStyle(Text::Bold);
    totalTime.setFillColor(Color(64, 147, 225));
    totalTime.setOutlineColor(Color::Black);
    totalTime.setOutlineThickness(3.0f * c.screenScale);
    totalTime.setPosition(((c.w.getSize().x / 2.f) - (totalTime.getLocalBounds().width / 2.f)) * offsetTimeLapTexts,
                            c.w.getSize().y / 2.f - 140.0f * c.screenScale);

    // Update the indicators
    string lapTime;
    lapTime = (minutesTrip < 10) ? "0" + to_string(int(minutesTrip)) + ":" : to_string(int(minutesTrip)) + ":";
    lapTime += (secsTrip < 10) ? "0" + to_string(int(secsTrip)) + ":" : to_string(int(secsTrip)) + ":";
    int cent_sec = cents_secondTrip * 100.f;
    lapTime += (cent_sec < 10) ? "0" + to_string(cent_sec) : to_string(cent_sec);

    Text timeLap;
    timeLap.setString(lapTime);
    timeLap.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    timeLap.setFont(c.fontMenus);
    timeLap.setStyle(Text::Bold);
    timeLap.setFillColor(Color(64, 147, 225));
    timeLap.setOutlineColor(Color::Black);
    timeLap.setOutlineThickness(3.0f * c.screenScale);
    timeLap.setPosition(((c.w.getSize().x / 2.f) - (timeLap.getLocalBounds().width / 2.f)) * offsetTimeLapTexts,
                          c.w.getSize().y / 2.f - 80.0f * c.screenScale);

    switch(typeOfVehicle){
        case 0:
            vehicleTexture.loadFromFile("Data/Vehicles/Motorbikes/Motorbike" + to_string(colorCarSelected + 1) + "/Images/c60.png");
            vehicle.setTexture(vehicleTexture, true);
            vehicle.setScale(1.6f * c.screenScale, 1.6f * c.screenScale);
            vehicle.setPosition((c.w.getSize().x / 2.f) - 90.0f * c.screenScale, c.w.getSize().y / carOffset - 2.f * c.screenScale);
            break;
        case 1:
            vehicleTexture.loadFromFile("Data/Vehicles/Devastators/Devastator" + to_string(colorCarSelected + 1) + "/Images/c38.png");
            vehicle.setTexture(vehicleTexture, true);
            vehicle.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
            vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset + 17.f * c.screenScale);
            break;
        case 2:
            vehicleTexture.loadFromFile("Data/Vehicles/Minivans/Minivan" + to_string(colorCarSelected + 1) + "/Images/c30.png");
            vehicle.setTexture(vehicleTexture, true);
            vehicle.setScale(2.7f * c.screenScale, 3.2f * c.screenScale);
            vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset - 14.f * c.screenScale);
            break;
        case 3:
            vehicleTexture.loadFromFile("Data/Vehicles/Trucks/Truck" + to_string(colorCarSelected + 1) + "/Images/c56.png");
            vehicle.setTexture(vehicleTexture, true);
            vehicle.setScale(2.7f * c.screenScale, 3.5f * c.screenScale);
            vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset - 20.f * c.screenScale);
    }


    float elapsed1, elapsed2;
    Clock blinkClcok;
    Time blink_delay = seconds(0.5f);

    blinkClcok.restart().asSeconds();
    elapsed1 = blinkClcok.restart().asSeconds();
    bool blink = true;

    // Read the file with the best time
    string path;

    if (typeOfGame == 0){
        path = "Data/Records/WorldTour/LandScape" + to_string(indexLandScape + 1) + "_";
    }
    else {
        path = "Data/Records/PolePosition/LandScape" + to_string(indexLandScape + 1) + "_";
    }

    // Control if the game has been played with the AI enabled or not
    if (c.enableAI){
        // Record with AI active
        path += "Enabled_";
    }
    else {
        // Record with AI disabled
        path += "Disabled_";
    }

    // Control the difficulty of the game
    switch (c.level){
        case PEACEFUL:
            path += "Peaceful.xml";
            break;
        case EASY:
            path += "Easy.xml";
            break;
        case NORMAL:
            path += "Normal.xml";
            break;
        case HARD:
            path += "Hard.xml";
    }

    string namePlayer;
    int minutesLap, secondsLap, centsSecondLap;

    // Read the record of the land scape
    readRecordFromLandScape(path, namePlayer, minutesLap, secondsLap, centsSecondLap);

    // Control if there is a new record or not
    bool record = false;

    if (minutesTrip < minutesLap){
        // There is a new record
        record = true;
    }
    else if (minutesTrip == minutesLap){
        // Both have the same minutes
        if (secsTrip < secondsLap){
            // Same minutes but less seconds
            record = true;
        }
        else if (secsTrip == secondsLap){
            // Both have the same minutes and seconds
            if (cents_secondTrip < centsSecondLap){
                // Same minutes and seconds but less hundredths of seconds
                record = true;
            }
        }
    }

    // Reproduce sound effect of record
    if (record){
        r.soundEffects[50]->stop();
        r.soundEffects[50]->play();

        // Until start key is pressed
        for (int j = 0; j <= 150; j++){

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }

            c.w.draw(sprite);
            c.w.draw(shape);
            c.w.draw(titleText);

            elapsed2 = blinkClcok.getElapsedTime().asSeconds();

            // Change the color of the main text
            if (elapsed2 - elapsed1 >= blink_delay.asSeconds()) {
                blink = !blink;
                blinkClcok.restart();
            }

            if (blink) {
                totalTime.setFillColor(Color(64, 147, 225));
                totalTime.setOutlineColor(Color::Black);
                timeLap.setFillColor(Color(64, 147, 225));
                timeLap.setOutlineColor(Color::Black);
                recordText.setFillColor(Color(64, 147, 225));
                recordText.setOutlineColor(Color::Black);
            }
            else {
                totalTime.setFillColor(Color::Transparent);
                totalTime.setOutlineColor(Color::Transparent);
                timeLap.setFillColor(Color::Transparent);
                timeLap.setOutlineColor(Color::Transparent);
                recordText.setFillColor(Color::Transparent);
                recordText.setOutlineColor(Color::Transparent);
            }

            c.w.draw(totalTime);
            c.w.draw(timeLap);
            c.w.draw(vehicle);
            c.w.draw(recordText);

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
            sleep(milliseconds(50));
        }
        // Ask the player to introduce his name
        int lettersIntroduced = 0;

        recordText.setString("ENTER YOUR NAME: ");
        recordText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        recordText.setFont(c.fontMenus);
        recordText.setStyle(Text::Bold);
        recordText.setFillColor(Color(64, 147, 225));
        recordText.setOutlineColor(Color::Black);
        recordText.setOutlineThickness(3.0f * c.screenScale);
        recordText.setPosition((c.w.getSize().x / 2.f) - 190.f * c.screenScale, c.w.getSize().y / 2.f + 175.0f * c.screenScale);

        string name = "_";

        Text playerName;
        playerName.setString(name);
        playerName.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        playerName.setFont(c.fontMenus);
        playerName.setStyle(Text::Bold);
        playerName.setFillColor(Color(64, 147, 225));
        playerName.setOutlineColor(Color::Black);
        playerName.setOutlineThickness(3.0f * c.screenScale);
        playerName.setPosition((c.w.getSize().x / 2.f) - 190.f * c.screenScale + recordText.getLocalBounds().width + 10.f,
                                c.w.getSize().y / 2.f + 175.0f * c.screenScale);

        KeywordMapper kM = KeywordMapper();

        // The player have to introduce all the letters
        while (lettersIntroduced != 3) {

            // while there are pending events...
            Event event;
            while (c.window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    return EXIT;
                }
                else if (event.type == Event::KeyPressed) {
                    // Get code of the key
                    int code = event.key.code;
                    // Check if the key pressed is a letter or not
                    if (code >= 0 && code <= 25) {
                        lettersIntroduced++;
                        string keyLetter = kM.mapperIdKeyWord[code];
                        if (name == "_") {
                            name = keyLetter + "_";
                            r.soundEffects[1]->stop();
                            r.soundEffects[1]->play();
                        }
                        else {
                            if (lettersIntroduced == 3) {
                                name = name.substr(0, name.size() - 1);
                                name += keyLetter;
                                r.soundEffects[2]->stop();
                                r.soundEffects[2]->play();
                            }
                            else {
                                name = name.substr(0, name.size() - 1);
                                name += keyLetter + "_";
                                r.soundEffects[1]->stop();
                                r.soundEffects[1]->play();
                            }
                        }
                    }
                    else {
                        r.soundEffects[3]->stop();
                        r.soundEffects[3]->play();
                    }
                }
            }

            playerName.setString(name);
            playerName.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
            playerName.setFont(c.fontMenus);
            playerName.setStyle(Text::Bold);
            playerName.setFillColor(Color(64, 147, 225));
            playerName.setOutlineColor(Color::Black);
            playerName.setOutlineThickness(3.0f * c.screenScale);
            playerName.setPosition((c.w.getSize().x / 2.f) - 190.f * c.screenScale + recordText.getLocalBounds().width + 10.f,
                                    c.w.getSize().y / 2.f + 175.0f * c.screenScale);

            elapsed2 = blinkClcok.getElapsedTime().asSeconds();

            // Change the color of the main text
            if (elapsed2 - elapsed1 >= blink_delay.asSeconds()) {
                blink = !blink;
                blinkClcok.restart();
            }

            if (blink) {
                totalTime.setFillColor(Color(64, 147, 225));
                totalTime.setOutlineColor(Color::Black);
                timeLap.setFillColor(Color(64, 147, 225));
                timeLap.setOutlineColor(Color::Black);
            }
            else {
                totalTime.setFillColor(Color::Transparent);
                totalTime.setOutlineColor(Color::Transparent);
                timeLap.setFillColor(Color::Transparent);
                timeLap.setOutlineColor(Color::Transparent);
            }

            // Draw the elements of the menu
            c.w.draw(sprite);
            c.w.draw(shape);
            c.w.draw(titleText);
            c.w.draw(totalTime);
            c.w.draw(timeLap);
            c.w.draw(vehicle);
            c.w.draw(recordText);
            c.w.draw(playerName);

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();

            sleep(milliseconds(50));
        }

        // Store the name in the file
        writeRecordFromLandScape(path, name, minutesTrip, secsTrip, int(cents_secondTrip * 100.f));
    }
    else {

        string record = "";

        record = (minutesLap < 10) ? "0" + to_string(int(minutesLap)) + ":" : to_string(int(minutesLap)) + ":";
        record += (secondsLap < 10) ? "0" + to_string(int(secondsLap)) + ":" : to_string(int(secondsLap)) + ":";
        record += (cent_sec < 10) ? "0" + to_string(centsSecondLap) : to_string(centsSecondLap);

        recordText.setString("CURRENT RECORD: " + record);
        recordText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        recordText.setFont(c.fontMenus);
        recordText.setStyle(Text::Bold);
        recordText.setFillColor(Color(64, 147, 225));
        recordText.setOutlineColor(Color::Black);
        recordText.setOutlineThickness(3.0f * c.screenScale);
        recordText.setPosition((c.w.getSize().x / 2.f) - (recordText.getLocalBounds().width / 2.f), c.w.getSize().y / 2.f + 175.0f * c.screenScale);

        for (int j = 0; j <= 150; j++){

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }

            c.w.draw(sprite);
            c.w.draw(shape);
            c.w.draw(titleText);

            elapsed2 = blinkClcok.getElapsedTime().asSeconds();

            // Change the color of the main text
            if (elapsed2 - elapsed1 >= blink_delay.asSeconds()) {
                blink = !blink;
                blinkClcok.restart();
            }

            if (blink) {
                totalTime.setFillColor(Color(64, 147, 225));
                totalTime.setOutlineColor(Color::Black);
                timeLap.setFillColor(Color(64, 147, 225));
                timeLap.setOutlineColor(Color::Black);
                recordText.setFillColor(Color(64, 147, 225));
                recordText.setOutlineColor(Color::Black);
            }
            else {
                totalTime.setFillColor(Color::Transparent);
                totalTime.setOutlineColor(Color::Transparent);
                timeLap.setFillColor(Color::Transparent);
                timeLap.setOutlineColor(Color::Transparent);
                recordText.setFillColor(Color::Transparent);
                recordText.setOutlineColor(Color::Transparent);
            }

            c.w.draw(totalTime);
            c.w.draw(timeLap);
            c.w.draw(vehicle);
            c.w.draw(recordText);

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
            sleep(milliseconds(50));
        }
    }

    // Main Text of the menu
    Text startText;
    startText.setString("PRESS START");
    startText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    startText.setFont(c.fontMenus);
    startText.setStyle(Text::Bold);
    startText.setFillColor(Color::Green);
    startText.setOutlineColor(Color::Black);
    startText.setOutlineThickness(3.0f * c.screenScale);
    startText.setPosition((c.w.getSize().x / 2.f) - (startText.getLocalBounds().width / 2.f), c.w.getSize().y / 2.f + 175.0f * c.screenScale);


    while(!startPressed){
        // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }

            c.w.draw(sprite);
            c.w.draw(shape);
            c.w.draw(titleText);

            elapsed2 = blinkClcok.getElapsedTime().asSeconds();

            // Change the color of the main text
            if (elapsed2 - elapsed1 >= blink_delay.asSeconds()) {
                blink = !blink;
                blinkClcok.restart();
            }

            if (blink) {
                totalTime.setFillColor(Color(64, 147, 225));
                totalTime.setOutlineColor(Color::Black);
                timeLap.setFillColor(Color(64, 147, 225));
                timeLap.setOutlineColor(Color::Black);
                startText.setFillColor(Color::Green);
                startText.setOutlineColor(Color::Black);
            }
            else {
                totalTime.setFillColor(Color::Transparent);
                totalTime.setOutlineColor(Color::Transparent);
                timeLap.setFillColor(Color::Transparent);
                timeLap.setOutlineColor(Color::Transparent);
                startText.setFillColor(Color::Transparent);
                startText.setOutlineColor(Color::Transparent);
            }

            c.w.draw(totalTime);
            c.w.draw(timeLap);
            c.w.draw(vehicle);
            c.w.draw(startText);

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();

             // Check if the start keyword has been pressed
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                // Pass to the second menu
                startPressed = true;
                r.soundEffects[1]->stop();
                r.soundEffects[1]->play();
                r.soundEffects[49]->stop();
                r.soundEffects[49]->play();
            }

            sleep(milliseconds(50));
    }

    mainTextArrived = false;
    lapTextsArrived = false;
    carSpriteArrived = false;
    soundMap = false;

    // Until start key is pressed
    while(!mainTextArrived && !lapTextsArrived && !carSpriteArrived){

        // Creation of the panel rectangle of the menu
        RectangleShape shape;
        shape.setPosition((c.w.getSize().x / 2.f) - 350.0f * c.screenScale, c.w.getSize().y / 2.f - offsetY * c.screenScale);
        shape.setSize(sf::Vector2f(710.0f * c.screenScale, 490.0f * c.screenScale));
        shape.setOutlineColor(Color::Green);
        shape.setOutlineThickness(5.0f * c.screenScale);
        shape.setFillColor(Color(0, 0, 0, 200));

        // Main Text of the menu
        Text titleText;

        if (typeOfGame == 0){
            titleText.setString(tourLandScapes[indexLandScape].getName());
        }
        else {
            titleText.setString(tourLandScapes[landScapeSelected].getName());
        }

        titleText.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
        titleText.setFont(c.fontMenus);
        titleText.setStyle(Text::Bold);
        titleText.setFillColor(Color::White);
        titleText.setOutlineColor(Color::Black);
        titleText.setOutlineThickness(3.0f * c.screenScale);
        titleText.setPosition(((c.w.getSize().x / 2.f) - (titleText.getLocalBounds().width / 2.f)) * offsetTitleText,
                                c.w.getSize().y / 2.f - 230.0f * c.screenScale);

        // Main Text of the menu
        Text totalTime;
        totalTime.setString("TOTAL TIME");
        totalTime.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        totalTime.setFont(c.fontMenus);
        totalTime.setStyle(Text::Bold);
        totalTime.setFillColor(Color(64, 147, 225));
        totalTime.setOutlineColor(Color::Black);
        totalTime.setOutlineThickness(3.0f * c.screenScale);
        totalTime.setPosition(((c.w.getSize().x / 2.f) - (totalTime.getLocalBounds().width / 2.f)) * offsetTimeLapTexts,
                                c.w.getSize().y / 2.f - 140.0f * c.screenScale);

        // Update the indicators
        string lapTime;
        lapTime = (minutesTrip < 10) ? "0" + to_string(int(minutesTrip)) + ":" : to_string(int(minutesTrip)) + ":";
        lapTime += (secsTrip < 10) ? "0" + to_string(int(secsTrip)) + ":" : to_string(int(secsTrip)) + ":";
        int cent_sec = cents_secondTrip * 100.f;
        lapTime += (cent_sec < 10) ? "0" + to_string(cent_sec) : to_string(cent_sec);

        Text timeLap;
        timeLap.setString(lapTime);
        timeLap.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        timeLap.setFont(c.fontMenus);
        timeLap.setStyle(Text::Bold);
        timeLap.setFillColor(Color(64, 147, 225));
        timeLap.setOutlineColor(Color::Black);
        timeLap.setOutlineThickness(3.0f * c.screenScale);
        timeLap.setPosition(((c.w.getSize().x / 2.f) - (timeLap.getLocalBounds().width / 2.f)) * offsetTimeLapTexts,
                              c.w.getSize().y / 2.f - 80.0f * c.screenScale);

        switch(typeOfVehicle){
            case 0:
                vehicleTexture.loadFromFile("Data/Vehicles/Motorbikes/Motorbike" + to_string(colorCarSelected + 1) + "/Images/c60.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(1.6f * c.screenScale, 1.6f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 90.0f * c.screenScale, c.w.getSize().y / carOffset - 2.f * c.screenScale);
                break;
            case 1:
                vehicleTexture.loadFromFile("Data/Vehicles/Devastators/Devastator" + to_string(colorCarSelected + 1) + "/Images/c38.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset + 17.f * c.screenScale);
                break;
            case 2:
                vehicleTexture.loadFromFile("Data/Vehicles/Minivans/Minivan" + to_string(colorCarSelected + 1) + "/Images/c30.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(2.7f * c.screenScale, 3.2f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset - 14.f * c.screenScale);
                break;
            case 3:
                vehicleTexture.loadFromFile("Data/Vehicles/Trucks/Truck" + to_string(colorCarSelected + 1) + "/Images/c56.png");
                vehicleTexture.loadFromFile("Data/Vehicles/Truck/Images/c56.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(2.7f * c.screenScale, 3.5f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset - 20.f * c.screenScale);
        }

        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return EXIT;
            }
        }

        c.w.draw(sprite);
        c.w.draw(shape);

        if (offsetTitleText > -1.f){
            offsetTitleText -= 0.1;
        }
        else {
            mainTextArrived = true;
        }

        if (offsetTimeLapTexts < 3.0f){
            offsetTimeLapTexts += 0.1;
        }
        else {
            lapTextsArrived = true;
        }

        if (carOffset > 1.0f){
            carOffset -= 0.03705;
        }
        else {
            carSpriteArrived = true;
        }

        if (offsetY < 800.f){
            offsetY += 25.f;
        }

        c.w.draw(titleText);
        c.w.draw(totalTime);
        c.w.draw(timeLap);
        c.w.draw(vehicle);

        bufferSprite.setTexture(c.w.getTexture(), true);
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

        sleep(milliseconds(50));
    }

    c.w.draw(sprite);

     // Creation of the panel rectangle of the menu
    RectangleShape blackShape;
    blackShape.setPosition(0, 0);
    blackShape.setSize(sf::Vector2f(c.w.getSize().x, c.w.getSize().y));

    for (int i = 0; i <= 70; i++){
        blackShape.setFillColor(Color(0, 0, 0, i));
        c.w.draw(blackShape);
        bufferSprite.setTexture(c.w.getTexture(), true);
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();
        sleep(milliseconds(20));
    }

    if (c.enablePixelArt) {
        if (c.isDefaultScreen)
            c.window.setView(View(Vector2f(DEFAULT_WIDTH / 4.0f, DEFAULT_HEIGHT / 4.0f),
                                  Vector2f(DEFAULT_WIDTH / 2.0f, DEFAULT_HEIGHT / 2.0f)));
        else
            c.window.setView(View(Vector2f(SCREEN_HD_WIDTH / 4.0f, SCREEN_HD_HEIGHT / 4.0f),
                                  Vector2f(SCREEN_HD_WIDTH / 2.0f, SCREEN_HD_HEIGHT / 2.0f)));
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));
        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);
    }

    // Start with the initial map again
    level = -1;

    if (typeOfGame == 0){
        indexLandScape++;
        currentMap = &tourLandScapes[indexLandScape];
        int bdTime = 0;
        time = int(float(tourLandScapes[indexLandScape].getTimeToPlay()) * timeMul) + bdTime;
    }

    finalGame = false;

    lastY = 0;
    vehicleCrash = false;

    onPause = false;
    comeFromOptions = false;
    blink = false;
    arrival = false;
    updatedTimeCheck = false;

    minutes = 0;
    secs = 0;
    cents_second = 0;
    minutesTrip = 0;
    secsTrip = 0;
    cents_secondTrip = 0;
    timeCheck = 0;
    lap = "00:00:00";
    indexCheckPoint = 1;

    switch(typeOfVehicle){
        case 0:
            player.setVehicle(typeOfGame);
            break;
        case 1:
            player2.setVehicle(typeOfGame);
            break;
        case 2:
            player3.setVehicle(typeOfGame);
            break;
        case 3:
            player4.setVehicle(typeOfGame);
    }

    r.soundTracks[15]->stop();

    if (typeOfGame == 2){
        r.soundTracks[1]->play();
        return CIRCUIT_SELECTION_MENU;
    }
    else {
        return PLAY_GAME;
    }
}



/**
 * Load the configuration of the circuit selection menu in its xml file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void Game::loadCircuitMenuConfiguration(const string path, Configuration& c){

    // Open the xml file of the scenario
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Local variable to store temporary the text content and the fonts of the texts
    string content, fontPath, backgroundTexture, colorKind;

    // Iterate to get the information of the player menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check it is the node that contains the information of the background
        if ((string)property->name() == "Background"){
            // Get the background image of the menu
            backgroundTexture = (string)property->value();
            c.backgroundCircuitMenu.loadFromFile(backgroundTexture);
        }
        // Check if it is the node that stores the information of the main text of the menu
        else if ((string)property->name() == "Title"){
            // Iterate to get the information of the title
            for (xml_node<> *titleProp = property->first_node(); titleProp; titleProp = titleProp->next_sibling()){
                // Get the red color channel
                if ((string)titleProp->name() == "Content"){
                    // Get the content of the title
                    content = (string)titleProp->value();
                    c.contentTitleCircuitMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontTitleCircuitMenu.loadFromFile(fontPath);
                }
                // Get color text of the title
                else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                    // Get the kind of color to process
                    colorKind = (string)titleProp->name();
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the player menu
                    for (xml_node<> *colorChannel = titleProp->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                        // Get the red color channel
                        if ((string)colorChannel->name() == "R"){
                            // Get the red channel
                            colorRed = stoi(colorChannel->value());
                        }
                        // Get the green color channel
                        else if ((string)colorChannel->name() == "G"){
                            // Get the red channel
                            colorGreen = stoi(colorChannel->value());
                        }
                        // Get the blue color channel
                        else if ((string)colorChannel->name() == "B"){
                            // Get the red channel
                            colorBlue = stoi(colorChannel->value());
                        }
                    }
                    // Check if it is the color of the text
                    if (colorKind == "ColorText"){
                        c.colorTitleTextCircuitMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderCircuitMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
        // Check if it is the node that stores the information of the main text of the menu
        else if ((string)property->name() == "CircuitPanel"){
            // Iterate to get the information of the title
            for (xml_node<> *panelProp = property->first_node(); panelProp; panelProp = panelProp->next_sibling()){
                // Get the red color channel
                if ((string)panelProp->name() == "Background"){
                    // Get the background image of the menu
                    backgroundTexture = (string)panelProp->value();
                    c.backgroundCircuitPanel.loadFromFile(backgroundTexture);
                }
                // Check if it is the node that stores the information of the main text of the menu
                else if ((string)panelProp->name() == "Text"){
                    // Iterate to get the information of the title
                    for (xml_node<> *textProp = panelProp->first_node(); textProp; textProp = textProp->next_sibling()){
                        // Get the green color channel
                        if ((string)textProp->name() == "Font"){
                            // Read the font from the file
                            fontPath = (string)textProp->value();
                            c.fontTitleCircuitPanel.loadFromFile(fontPath);
                        }
                        // Get color text of the title
                        else if ((string)textProp->name() == "ColorText" || (string)textProp->name() == "ColorBorder"){
                            // Get the kind of color to process
                            colorKind = (string)textProp->name();
                            // Get the border color of the panel
                            int colorRed = 0, colorGreen = 0, colorBlue = 0;
                            // Iterate to get the information of the player menu
                            for (xml_node<> *colorChannel = textProp->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                                // Get the red color channel
                                if ((string)colorChannel->name() == "R"){
                                    // Get the red channel
                                    colorRed = stoi(colorChannel->value());
                                }
                                // Get the green color channel
                                else if ((string)colorChannel->name() == "G"){
                                    // Get the red channel
                                    colorGreen = stoi(colorChannel->value());
                                }
                                // Get the blue color channel
                                else if ((string)colorChannel->name() == "B"){
                                    // Get the red channel
                                    colorBlue = stoi(colorChannel->value());
                                }
                            }
                            // Check if it is the color of the text
                            if (colorKind == "ColorText"){
                                c.colorTitleTextCircuitPanel = Color(colorRed, colorGreen, colorBlue);
                            }
                            // Check if it is the color of the border
                            else if (colorKind == "ColorBorder"){
                                c.colorTitleBorderCircuitPanel = Color(colorRed, colorGreen, colorBlue);
                            }
                        }
                    }
                }
                // Check if it is the node that stores the information of the main text of the menu
                else if ((string)panelProp->name() == "ColorBorder"){
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the player menu
                    for (xml_node<> *colorChannel = panelProp->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                        // Get the red color channel
                        if ((string)colorChannel->name() == "R"){
                            // Get the red channel
                            colorRed = stoi(colorChannel->value());
                        }
                        // Get the green color channel
                        else if ((string)colorChannel->name() == "G"){
                            // Get the red channel
                            colorGreen = stoi(colorChannel->value());
                        }
                        // Get the blue color channel
                        else if ((string)colorChannel->name() == "B"){
                            // Get the red channel
                            colorBlue = stoi(colorChannel->value());
                        }
                    }
                    // Store the border color
                    c.colorBorderCircuitPanel = Color(colorRed, colorGreen, colorBlue);
                }
            }
        }
        // Check if it is the node that stores the information of the main text of the menu
        else if ((string)property->name() == "Indicators"){
            // Get the border color of the panel
            int colorRed = 0, colorGreen = 0, colorBlue = 0;
            // Iterate to get the information of the player menu
            for (xml_node<> *color = property->first_node(); color; color = color->next_sibling()){
                // Get the kind of color to process
                colorKind = (string)color->name();
                // Iterate to get the information of the player menu
                for (xml_node<> *colorChannel = color->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                    // Get the red color channel
                    if ((string)colorChannel->name() == "R"){
                        // Get the red channel
                        colorRed = stoi(colorChannel->value());
                    }
                    // Get the green color channel
                    else if ((string)colorChannel->name() == "G"){
                        // Get the red channel
                        colorGreen = stoi(colorChannel->value());
                    }
                    // Get the blue color channel
                    else if ((string)colorChannel->name() == "B"){
                        // Get the red channel
                        colorBlue = stoi(colorChannel->value());
                    }
                }
                // Check if it is the color of the text
                if (colorKind == "ColorInside"){
                    c.colorInsideIndicator = Color(colorRed, colorGreen, colorBlue);
                }
                // Check if it is the color of the border
                else if (colorKind == "ColorBorder"){
                    c.colorBorderIndicator = Color(colorRed, colorGreen, colorBlue);
                }
            }
        }
    }
    c.circuitMenuRead = true;
}


State Game::selectionCircuitMenu(Configuration& c, SoundPlayer& r){

    // Initialize the number of laps to do
    lapsDone = 1;

    // The xml configuration file of the player menu has been read
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));

    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Check if the xml configuration file of the menu has been read or not
    if (!c.circuitMenuRead){
        string path = "Data/Menus/CircuitSelectionMenu/Configuration/CircuitSelectionMenu.xml";
        loadCircuitMenuConfiguration(path, c);
    }


    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Load the background of the animation
    c.backgroundCircuitMenu.setRepeated(true);
    IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
    Sprite sprite(c.backgroundCircuitMenu, background);

    // Adapting the resolution of the screen
    float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
    float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
    sprite.setScale(axis_x, axis_y);

    // Main rectangle of the menu
    RectangleShape shape;
    shape.setSize(sf::Vector2f(610.0f * c.screenScale, 485.0f * c.screenScale));
    shape.setOutlineColor(Color::Black);
    shape.setOutlineThickness(5.0f * c.screenScale);
    shape.setPosition(c.w.getSize().x / 2.f - shape.getLocalBounds().width / 2.f,
                      c.w.getSize().y / 2.f - shape.getLocalBounds().height / 2.f);
    // Current circuit selected to run
    landScapeSelected = 0;

    // Main text of the menu
    Text mainText;
    mainText.setString(c.contentTitleCircuitMenu);
    mainText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    mainText.setFont(c.fontTitleCircuitMenu);
    mainText.setStyle(Text::Bold | Text::Underlined);
    mainText.setFillColor(c.colorTitleTextCircuitMenu);
    mainText.setOutlineColor(c.colorTitleBorderCircuitMenu);
    mainText.setOutlineThickness(5.0f * c.screenScale);
    mainText.setPosition((c.w.getSize().x / 2.f) - mainText.getLocalBounds().width / 2.f,
                          c.w.getSize().y / 2.f - 200.0f * c.screenScale);

    // Main text of the menu
    Text circuitName;
    circuitName.setString(tourLandScapes[landScapeSelected].getName());
    circuitName.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    circuitName.setFont(c.fontTitleCircuitPanel);
    circuitName.setStyle(Text::Bold);
    circuitName.setFillColor(c.colorTitleTextCircuitPanel);
    circuitName.setOutlineColor(c.colorTitleBorderCircuitPanel);
    circuitName.setOutlineThickness(5.0f * c.screenScale);
    circuitName.setPosition((c.w.getSize().x / 2.f) - circuitName.getLocalBounds().width / 2.f,
                             c.w.getSize().y / 2.f - 120.0f * c.screenScale);

    // Vector of textures with the circuit textures
    vector<Texture> circuits;

    // Add the textures to the vector
    Texture circuit;
    for (int i = 1; i <= 4; i++){
        circuit.loadFromFile("Data/Menus/CircuitSelectionMenu/Images/c" + to_string(i) + ".png");
        circuits.push_back(circuit);
    }

    c.backgroundCircuitPanel.setRepeated(true);
    shape.setTexture(&c.backgroundCircuitPanel, true);
    shape.setFillColor(Color(45, 81, 112));

    // Control if the player presses the start key or not
    bool startPressed = false;

    // Control if the player presses the backspace key or not
    bool backSpacePressed = false;

    // Control the option currently selected
    int optionSelected = 0;

    // Show the vehicle selected
    Sprite circuitRoute;
    circuitRoute.setTexture(circuits[0], true);
    circuitRoute.setScale(3.0f * c.screenScale, 3.0f * c.screenScale);
    circuitRoute.setPosition(shape.getPosition().x + (float(shape.getSize().x) / 2.f) -
                            (float(circuitRoute.getLocalBounds().width ) / 2.f) * 3.0f * c.screenScale,
                             c.w.getSize().y / 2.f - 70.f * c.screenScale);

    // While start and backspace have not been pressed
    while (!startPressed && !backSpacePressed) {

        // Laps indicators text
        Text circuitIndicatorText;
        circuitIndicatorText.setString("CIRCUIT: ");
        circuitIndicatorText.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
        circuitIndicatorText.setFont(c.fontTitleCircuitPanel);
        circuitIndicatorText.setStyle(Text::Bold);
        circuitIndicatorText.setFillColor(c.colorTitleTextCircuitPanel);
        circuitIndicatorText.setOutlineColor(c.colorTitleBorderCircuitPanel);
        circuitIndicatorText.setOutlineThickness(5.0f * c.screenScale);
        circuitIndicatorText.setPosition(c.w.getSize().x / 2.f - 80.0f * c.screenScale,
                                         c.w.getSize().y / 2.f + 100.0f * c.screenScale);

        // Laps indicators text
        Text lapsIndicatorText;
        lapsIndicatorText.setString("LAPS: ");
        lapsIndicatorText.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
        lapsIndicatorText.setFont(c.fontTitleCircuitPanel);
        lapsIndicatorText.setStyle(Text::Bold);
        lapsIndicatorText.setFillColor(c.colorTitleTextCircuitPanel);
        lapsIndicatorText.setOutlineColor(c.colorTitleBorderCircuitPanel);
        lapsIndicatorText.setOutlineThickness(5.0f * c.screenScale);
        lapsIndicatorText.setPosition(c.w.getSize().x / 2.f - 80.0f * c.screenScale,
                                      c.w.getSize().y / 2.f + 140.0f * c.screenScale);

        // Racers indicators text
        Text racersIndicatorText;
        racersIndicatorText.setString("RACERS: ");
        racersIndicatorText.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
        racersIndicatorText.setFont(c.fontTitleCircuitPanel);
        racersIndicatorText.setStyle(Text::Bold);
        racersIndicatorText.setFillColor(c.colorTitleTextCircuitPanel);
        racersIndicatorText.setOutlineColor(c.colorTitleBorderCircuitPanel);
        racersIndicatorText.setOutlineThickness(5.0f * c.screenScale);
        racersIndicatorText.setPosition(c.w.getSize().x / 2.f - 80.0f * c.screenScale,
                                        c.w.getSize().y / 2.f + 180.0f * c.screenScale);

        CircleShape triangle2(14 * c.screenScale, 3);
        triangle2.setFillColor(c.colorInsideIndicator);
        triangle2.setOutlineColor(c.colorBorderIndicator);
        triangle2.setOutlineThickness(2.0f * c.screenScale);
        triangle2.setRotation(90);
        triangle2.setPosition(c.w.getSize().x / 2.f - 80.f * c.screenScale - 11.f, c.w.getSize().y / 2.f + 106.0f * c.screenScale);

        Text circuitText;
        circuitText.setString(to_string(landScapeSelected + 1));
        circuitText.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
        circuitText.setFont(c.fontTitleCircuitPanel);
        circuitText.setStyle(Text::Bold);
        circuitText.setFillColor(c.colorTitleTextCircuitPanel);
        circuitText.setOutlineColor(c.colorTitleBorderCircuitPanel);
        circuitText.setOutlineThickness(5.0f * c.screenScale);
        circuitText.setPosition(c.w.getSize().x / 2.f - 80.0f * c.screenScale + circuitIndicatorText.getLocalBounds().width + 5.f ,
                                c.w.getSize().y / 2.f + 100.0f * c.screenScale);

        Text lapsText;
        lapsText.setString(to_string(numberLaps));
        lapsText.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
        lapsText.setFont(c.fontTitleCircuitPanel);
        lapsText.setStyle(Text::Bold);
        lapsText.setFillColor(c.colorTitleTextCircuitPanel);
        lapsText.setOutlineColor(c.colorTitleBorderCircuitPanel);
        lapsText.setOutlineThickness(5.0f * c.screenScale);
        lapsText.setPosition(c.w.getSize().x / 2.f - 80.0f * c.screenScale + lapsIndicatorText.getLocalBounds().width + 5.f ,
                             c.w.getSize().y / 2.f + 140.0f * c.screenScale);

        // Racers indicators text
        Text racersText;
        racersText.setString(to_string(numberRacers));
        racersText.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
        racersText.setFont(c.fontTitleCircuitPanel);
        racersText.setStyle(Text::Bold);
        racersText.setFillColor(c.colorTitleTextCircuitPanel);
        racersText.setOutlineColor(c.colorTitleBorderCircuitPanel);
        racersText.setOutlineThickness(5.0f * c.screenScale);
        racersText.setPosition(c.w.getSize().x / 2.f - 80.0f * c.screenScale + racersIndicatorText.getLocalBounds().width + 5.f,
                               c.w.getSize().y / 2.f + 180.0f * c.screenScale);

        // While start and backspace have not been pressed
        while (!startPressed && !backSpacePressed) {

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)){
                if (e.type == Event::Closed){
                    return EXIT;
                }
            }

            // Check if the up or down cursor keys have been pressed or not
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                // Up cursor pressed and change the soundtrack selected in the list
                if (optionSelected != 2) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected++;

                    switch(optionSelected){
                        case 0:
                            triangle2.setPosition(c.w.getSize().x / 2.f - 80.f * c.screenScale - 11.f,
                                                  c.w.getSize().y / 2.f + 106.0f * c.screenScale);
                            break;
                        case 1:
                            triangle2.setPosition(c.w.getSize().x / 2.f - 80.f * c.screenScale - 11.f,
                                                  c.w.getSize().y / 2.f + 146.0f * c.screenScale);
                            break;
                        case 2:
                            triangle2.setPosition(c.w.getSize().x / 2.f - 80.f * c.screenScale - 11.f,
                                                  c.w.getSize().y / 2.f + 186.0f * c.screenScale);
                    }
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Up)) {
                // Down cursor pressed and change the soundtrack selected in the list
                if (optionSelected != 0) {
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected--;

                    switch(optionSelected){
                        case 0:
                            triangle2.setPosition(c.w.getSize().x / 2.f - 80.f * c.screenScale - 11.f,
                                                  c.w.getSize().y / 2.f + 106.0f * c.screenScale);
                            break;
                        case 1:
                            triangle2.setPosition(c.w.getSize().x / 2.f - 80.f * c.screenScale - 11.f,
                                                  c.w.getSize().y / 2.f + 146.0f * c.screenScale);
                            break;
                        case 2:
                            triangle2.setPosition(c.w.getSize().x / 2.f - 80.f * c.screenScale - 11.f,
                                                  c.w.getSize().y / 2.f + 186.0f * c.screenScale);
                    }
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Left)) {
                // Up cursor pressed and change the soundtrack selected in the list
                switch(optionSelected){
                    case 0:
                        if (landScapeSelected != 0){
                            // Change to the left circuit
                            landScapeSelected--;

                            // Get the name of the circuit
                            circuitName.setString(tourLandScapes[landScapeSelected].getName());
                            circuitName.setPosition((c.w.getSize().x / 2.f) - circuitName.getLocalBounds().width / 2.f,
                                                     c.w.getSize().y / 2.f - 120.0f * c.screenScale);

                            // Change the circuit texture to display
                            circuitRoute.setTexture(circuits[landScapeSelected], true);
                            circuitRoute.setScale(3.0f * c.screenScale, 3.0f * c.screenScale);
                            circuitRoute.setPosition(shape.getPosition().x + (float(shape.getSize().x) / 2.f) -
                                                    (float(circuitRoute.getLocalBounds().width ) / 2.f) * 3.0f * c.screenScale,
                                                     c.w.getSize().y / 2.f - 70.f * c.screenScale);

                            r.soundEffects[0]->stop();
                            r.soundEffects[0]->play();
                        }
                        break;
                    case 1:
                        if (numberLaps != 1){
                            // Decrement one lap
                            numberLaps--;
                            r.soundEffects[0]->stop();
                            r.soundEffects[0]->play();
                        }
                        break;
                    case 2:
                        if (numberRacers != 0){
                            // Decrement one lap
                            numberRacers--;
                            r.soundEffects[0]->stop();
                            r.soundEffects[0]->play();
                        }
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Right)) {
                switch(optionSelected){
                    case 0:
                        if (landScapeSelected != 3){
                            // Change to the left circuit
                            landScapeSelected++;

                            // Get the name of the circuit
                            circuitName.setString(tourLandScapes[landScapeSelected].getName());
                            circuitName.setPosition((c.w.getSize().x / 2.f) - circuitName.getLocalBounds().width / 2.f,
                                                     c.w.getSize().y / 2.f - 120.0f * c.screenScale);

                            // Change the circuit texture to display
                            circuitRoute.setTexture(circuits[landScapeSelected], true);
                            circuitRoute.setScale(3.0f * c.screenScale, 3.0f * c.screenScale);
                            circuitRoute.setPosition(shape.getPosition().x + (float(shape.getSize().x) / 2.f) -
                                                    (float(circuitRoute.getLocalBounds().width ) / 2.f) * 3.0f * c.screenScale,
                                                     c.w.getSize().y / 2.f - 70.f * c.screenScale);

                            r.soundEffects[0]->stop();
                            r.soundEffects[0]->play();
                        }
                        break;
                    case 1:
                        if (numberLaps != 5){
                            // Increment one lap
                            numberLaps++;
                            r.soundEffects[0]->stop();
                            r.soundEffects[0]->play();
                        }
                        break;
                    case 2:
                        if (numberRacers != 7){
                            // Decrement one lap
                            numberRacers++;
                            r.soundEffects[0]->stop();
                            r.soundEffects[0]->play();
                        }
                }
            }

            // Circuit identifier
            circuitText.setString(to_string(landScapeSelected + 1));
            circuitText.setPosition(c.w.getSize().x / 2.f - 80.0f * c.screenScale + circuitIndicatorText.getLocalBounds().width + 5.f ,
                                    c.w.getSize().y / 2.f + 100.0f * c.screenScale);

            // Laps to run in the circuit
            lapsText.setString(to_string(numberLaps));
            lapsText.setPosition(c.w.getSize().x / 2.f - 80.0f * c.screenScale + lapsIndicatorText.getLocalBounds().width + 5.f ,
                                 c.w.getSize().y / 2.f + 140.0f * c.screenScale);

            // Racers indicators text
            racersText.setString(to_string(numberRacers));
            racersText.setPosition(c.w.getSize().x / 2.f - 80.0f * c.screenScale + racersIndicatorText.getLocalBounds().width + 5.f,
                                   c.w.getSize().y / 2.f + 180.0f * c.screenScale);

            // Draw the elements of the menu
            c.w.draw(sprite);
            c.w.draw(shape);
            c.w.draw(mainText);
            c.w.draw(circuitName);
            c.w.draw(circuitRoute);
            c.w.draw(circuitIndicatorText);
            c.w.draw(lapsIndicatorText);
            c.w.draw(racersIndicatorText);
            c.w.draw(lapsText);
            c.w.draw(racersText);
            c.w.draw(circuitText);
            c.w.draw(triangle2);

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();

            sleep(milliseconds(120));

            // Check if start key has been pressed
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                // Change the controllers of the car
                startPressed = true;
                r.soundEffects[2]->stop();
                r.soundEffects[2]->play();
            }
            // Check if backspace key has been pressed
            else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                // Change the controllers of the car
                backSpacePressed = true;
                r.soundEffects[11]->stop();
                r.soundEffects[11]->play();
            }
        }
    }

    if (startPressed){
        r.soundTracks[1]->stop();
        currentMap = &tourLandScapes[landScapeSelected];

        // Back door
        int bdTime = 0;
        time = int(float(currentMap->getTimeToPlay()) * timeMul) + bdTime;
        score = 0;
        level = -1;

        // Initialize the checkpoint index
        indexCheckPoint = 1;
        checkPointPositions = tourLandScapes[landScapeSelected].getCheckPointPositions();

        return VEHICLE_SELECTION;

    }
    else if (backSpacePressed){
        return GAME_MODES_MENU;
    }
    return EXIT;
}
