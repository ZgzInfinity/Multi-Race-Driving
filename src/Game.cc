
#include "../include/Game.h"


int cmd(char *cmd, char *output, DWORD maxbuffer)
{
    HANDLE readHandle;
    HANDLE writeHandle;
    HANDLE stdHandle;
    DWORD bytesRead;
    DWORD retCode;
    SECURITY_ATTRIBUTES sa;
    PROCESS_INFORMATION pi;
    STARTUPINFO si;

    ZeroMemory(&sa,sizeof(SECURITY_ATTRIBUTES));
    ZeroMemory(&pi,sizeof(PROCESS_INFORMATION));
    ZeroMemory(&si,sizeof(STARTUPINFO));

    sa.bInheritHandle=true;
    sa.lpSecurityDescriptor=NULL;
    sa.nLength=sizeof(SECURITY_ATTRIBUTES);
    si.cb=sizeof(STARTUPINFO);
    si.dwFlags=STARTF_USESHOWWINDOW;
    si.wShowWindow=SW_HIDE;

    if (!CreatePipe(&readHandle,&writeHandle,&sa,NULL))
    {
        OutputDebugString("cmd: CreatePipe failed!\n");
        return 0;
    }

    stdHandle=GetStdHandle(STD_OUTPUT_HANDLE);

    if (!SetStdHandle(STD_OUTPUT_HANDLE,writeHandle))
    {
        OutputDebugString("cmd: SetStdHandle(writeHandle) failed!\n");
        return 0;
    }

    if (!CreateProcess(NULL,cmd,NULL,NULL,TRUE,0,NULL,NULL,&si,&pi))
    {
        OutputDebugString("cmd: CreateProcess failed!\n");
        return 0;
    }

    GetExitCodeProcess(pi.hProcess,&retCode);
    while (retCode==STILL_ACTIVE)
    {
        GetExitCodeProcess(pi.hProcess,&retCode);
    }

    if (!ReadFile(readHandle,output,maxbuffer,&bytesRead,NULL))
    {
        OutputDebugString("cmd: ReadFile failed!\n");
        return 0;
    }
    output[bytesRead]='\0';

    if (!SetStdHandle(STD_OUTPUT_HANDLE,stdHandle))
    {
        OutputDebugString("cmd: SetStdHandle(stdHandle) failed!\n");
        return 0;
    }

    if (!CloseHandle(readHandle))
    {
        OutputDebugString("cmd: CloseHandle(readHandle) failed!\n");
    }
    if (!CloseHandle(writeHandle))
    {
        OutputDebugString("cmd: CloseHandle(writeHandle) failed!\n");
    }

    return 1;
}


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

    if (typeOfVehicle == 5){
        j = 0;
    }

    int vehicleKind = rand_generator_int(1, 4);

    // Store the rival cars in the vector
    for (int i = 0; i < numberRacers; i++) {

        if (i % 2 == 0){
            positX = 0.3f;
        }
        else {
            positX = -0.3f;
        }

        if (rivalTypeMode == 0){
           if (typeOfGame == 0){
                v = RivalCar(0, MAX_SPEED, SPEED_FACTOR, 2.5f, COUNTER, "Data/Vehicles/Motorbikes/Motorbike" + to_string(j + 1),
                                 positX, positY, Motorbike_vehicle::PLAYER_TEXTURES, 1, 2, 15, 16, 3, 8, 17, 22, 9, 14, 23, 28, 1, 2, 15, 16, 3,
                                 8, 17, 22, 9, 14, 23, 28, 7, 13, 7, 13, 21, 27, 21, 27, 1.15f);

                v.setAI(c.maxAggressiveness, c.level, typeOfGame);
                rivals.push_back(v);
           }
           else if (typeOfGame == 2){
                v = RivalCar(4, MAX_SPEED, SPEED_FACTOR, 4.5f, COUNTER, "Data/Vehicles/FormulaOnes/FormulaOne" +
                        to_string(j + 1), positX, positY, FormulaOne_vehicle::PLAYER_TEXTURES, 1, 2, 23, 24, 3, 12, 25, 34,
                        13, 22, 35, 44, 1, 2, 23, 24, 3, 12, 25, 34, 13, 22, 35, 44, 11, 21, 11, 21, 33, 43, 33, 43, 1.80f);

                v.setAI(c.maxAggressiveness, c.level, typeOfGame);
                rivals.push_back(v);
           }
        }
        else if (rivalTypeMode == 1) {
            // Set the scale of the vehicle
            switch(typeOfVehicle){
                case 0:
                    v = RivalCar(typeOfVehicle, MAX_SPEED, SPEED_FACTOR, 2.5f, COUNTER, "Data/Vehicles/Motorbikes/Motorbike" + to_string(j + 1),
                                 positX, positY, Motorbike_vehicle::PLAYER_TEXTURES, 1, 2, 15, 16, 3, 8, 17, 22, 9, 14, 23, 28, 1, 2, 15, 16, 3,
                                 8, 17, 22, 9, 14, 23, 28, 7, 13, 7, 13, 21, 27, 21, 27, 1.15f);

                    v.setAI(c.maxAggressiveness, c.level, typeOfGame);
                    rivals.push_back(v);
                    break;
                case 1:
                    v = RivalCar(typeOfVehicle, MAX_SPEED, SPEED_FACTOR, 4.f, COUNTER, "Data/Vehicles/Devastators/Devastator" + to_string(j + 1),
                                 positX, positY, Devastator_vehicle::PLAYER_TEXTURES, 1, 4, 19, 22, 5, 8, 23, 26, 9, 12, 27, 30, 13, 14,
                                 31, 32, 15, 16, 33, 34, 17, 18, 35, 36, 6, 10, 15, 17, 24, 28, 33, 35, 1.85f);

                    v.setAI(c.maxAggressiveness, c.level, typeOfGame);
                    rivals.push_back(v);
                    break;
                case 2:
                    v = RivalCar(typeOfVehicle, MAX_SPEED, SPEED_FACTOR, 4.f, COUNTER, "Data/Vehicles/Minivans/Minivan" + to_string(j + 1),
                                 positX, positY, Minivan_vehicle::PLAYER_TEXTURES, 1, 2, 15, 16, 3, 5, 17, 19, 6, 8, 17, 19, 9, 10, 23, 24,
                                 11, 12, 25, 26, 13, 14, 20, 22, 3, 6, 11, 13, 17, 20, 25, 27, 1.75f);

                    v.setAI(c.maxAggressiveness, c.level, typeOfGame);
                    rivals.push_back(v);
                    break;
                case 3:
                    v = RivalCar(typeOfVehicle, MAX_SPEED, SPEED_FACTOR, 4.5f, COUNTER, "Data/Vehicles/Trucks/Truck" + to_string(j + 1),
                                 positX, positY, Truck_vehicle::PLAYER_TEXTURES, 1, 5, 28, 32, 6, 10, 33, 37, 11, 15, 38, 42, 16, 19,
                                 43, 46, 20, 23, 47, 50, 24, 27, 51, 54, 7, 12, 21, 25, 34, 39, 48, 52, 2.02f);

                    v.setAI(c.maxAggressiveness, c.level, typeOfGame);
                    rivals.push_back(v);
                    break;
                case 4:
                    v = RivalCar(typeOfVehicle, MAX_SPEED, SPEED_FACTOR, 4.5f, COUNTER, "Data/Vehicles/FormulaOnes/FormulaOne" + to_string(j + 1),
                                 positX, positY, FormulaOne_vehicle::PLAYER_TEXTURES, 1, 2, 23, 24, 3, 12, 25, 34, 13, 22, 35, 44,
                                 1, 2, 23, 24, 3, 12, 25, 34, 13, 22, 35, 44, 11, 21, 11, 21, 33, 43, 33, 43, 1.80f);

                    v.setAI(c.maxAggressiveness, c.level, typeOfGame);
                    rivals.push_back(v);
                    break;
                case 5:
                    v = RivalCar(typeOfVehicle, MAX_SPEED, SPEED_FACTOR, 4.5f, COUNTER, "Data/Vehicles/Police",
                                 positX, positY, Police_vehicle::PLAYER_TEXTURES, 1, 4, 13, 16, 5, 8, 17, 20, 9, 12, 21, 24, 1, 4, 13, 16,
                                 5, 8, 17, 20, 9, 12, 21, 24, 5, 9, 5, 9, 17, 21, 17, 21, 1.85f);

                    v.setAI(c.maxAggressiveness, c.level, typeOfGame);
                    rivals.push_back(v);
            }
        }
        else {
            // The car is randomly chosen
            vehicleKind = rand_generator_int(0, 5);

            if (vehicleKind != 5){
                switch (vehicleKind){
                    case 0:
                        v = RivalCar(vehicleKind, MAX_SPEED, SPEED_FACTOR, 2.5f, COUNTER, "Data/Vehicles/Motorbikes/Motorbike" + to_string(j + 1),
                                 positX, positY, Motorbike_vehicle::PLAYER_TEXTURES, 1, 2, 15, 16, 3, 8, 17, 22, 9, 14, 23, 28, 1, 2, 15, 16, 3,
                                 8, 17, 22, 9, 14, 23, 28, 7, 13, 7, 13, 21, 27, 21, 27, 1.15f);

                        v.setAI(c.maxAggressiveness, c.level, typeOfGame);
                        rivals.push_back(v);
                        break;
                    case 1:
                        v = RivalCar(vehicleKind, MAX_SPEED, SPEED_FACTOR, 4.f, COUNTER, "Data/Vehicles/Devastators/Devastator" + to_string(j + 1),
                                 positX, positY, Devastator_vehicle::PLAYER_TEXTURES, 1, 4, 19, 22, 5, 8, 23, 26, 9, 12, 27, 30, 13, 14,
                                 31, 32, 15, 16, 33, 34, 17, 18, 35, 36, 6, 10, 15, 17, 24, 28, 33, 35, 1.85f);

                        v.setAI(c.maxAggressiveness, c.level, typeOfGame);
                        rivals.push_back(v);
                        break;
                    case 2:
                         v = RivalCar(vehicleKind, MAX_SPEED, SPEED_FACTOR, 4.f, COUNTER, "Data/Vehicles/Minivans/Minivan" + to_string(j + 1),
                                 positX, positY, Minivan_vehicle::PLAYER_TEXTURES, 1, 2, 15, 16, 3, 5, 17, 19, 6, 8, 17, 19, 9, 10, 23, 24,
                                 11, 12, 25, 26, 13, 14, 20, 22, 3, 6, 11, 13, 17, 20, 25, 27, 1.75f);

                        v.setAI(c.maxAggressiveness, c.level, typeOfGame);
                        rivals.push_back(v);
                        break;
                    case 3:
                        v = RivalCar(vehicleKind, MAX_SPEED, SPEED_FACTOR, 4.5f, COUNTER, "Data/Vehicles/Trucks/Truck" + to_string(j + 1),
                                 positX, positY, Truck_vehicle::PLAYER_TEXTURES, 1, 5, 28, 32, 6, 10, 33, 37, 11, 15, 38, 42, 16, 19,
                                 43, 46, 20, 23, 47, 50, 24, 27, 51, 54, 7, 12, 21, 25, 34, 39, 48, 52, 2.02f);

                        v.setAI(c.maxAggressiveness, c.level, typeOfGame);
                        rivals.push_back(v);
                        break;
                    case 4:
                        v = RivalCar(vehicleKind, MAX_SPEED, SPEED_FACTOR, 4.5f, COUNTER, "Data/Vehicles/FormulaOnes/FormulaOne" + to_string(j + 1),
                                 positX, positY, FormulaOne_vehicle::PLAYER_TEXTURES, 1, 2, 23, 24, 3, 12, 25, 34, 13, 22, 35, 44,
                                 1, 2, 23, 24, 3, 12, 25, 34, 13, 22, 35, 44, 11, 21, 11, 21, 33, 43, 33, 43, 1.80f);

                        v.setAI(c.maxAggressiveness, c.level, typeOfGame);
                        rivals.push_back(v);
                }
            }
            else {
                // The vehicle selected is a police car
                v = RivalCar(vehicleKind, MAX_SPEED, SPEED_FACTOR, 4.5f, COUNTER, "Data/Vehicles/Police",
                             positX, positY, Police_vehicle::PLAYER_TEXTURES, 1, 4, 13, 16, 5, 8, 17, 20, 9, 12, 21, 24, 1, 4, 13, 16,
                             5, 8, 17, 20, 9, 12, 21, 24, 5, 9, 5, 9, 17, 21, 17, 21, 1.85f);

                v.setAI(c.maxAggressiveness, c.level, typeOfGame);
                rivals.push_back(v);
            }
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
                    break;
                case 5:
                    mainMutex.lock();
                    speed = player6.getRealSpeed();
                    mainMutex.unlock();
                    // Update the score of the player if the player is not stopped
                    if (speed > 0.0f) {
                        // Add score
                        mainMutex.lock();
                        score += int(player6.getRealSpeed() * scoreMul);
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
    textures.clear();

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
    textures.clear();

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
    lapText.setCharacterSize(static_cast<unsigned int>(int(38.0f * c.screenScale)));
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
    timeToPlay.setCharacterSize(static_cast<unsigned int>(int(38.0f * c.screenScale)));
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
            break;
        case 5:
            speed = player6.getRealSpeed();
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
            break;
        case 5:
            strSpeed = to_string(player6.getRealSpeed());
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
    textLevel.setPosition(initial, down - 1.05f * float(textLevel.getCharacterSize()));
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

    if (typeOfGame == 1){
        // Score of the player displayed in the panel
        c.w.draw(s);
        Text textScore;
        textScore.setFont(c.fontTimeToPlay);
        textScore.setString(to_string(int(BONIFICATION) * 100));
        textScore.setCharacterSize(static_cast<unsigned int>(int(38.0f * c.screenScale)));
        textScore.setFillColor(Color(183, 164, 190));
        textScore.setOutlineColor(Color::Black);
        textScore.setOutlineThickness(3.0f * c.screenScale);
        textScore.setString(to_string(score));
        textScore.setPosition(initial * 4.95f - textScore.getLocalBounds().width, up - 0.5f * float(textScore.getCharacterSize()));
        c.w.draw(textScore);
    }
    else {
        // Check point indicator
        Text checkPoint;
        checkPoint.setFont(c.fontTimeToPlay);
        checkPoint.setCharacterSize(static_cast<unsigned int>(int(38.0f * c.screenScale)));
        checkPoint.setFillColor(Color::White);
        checkPoint.setOutlineColor(Color::Black);
        checkPoint.setOutlineThickness(3.0f * c.screenScale);

        if (typeOfGame == 3){
            // Driving Fury
            checkPoint.setString("DISTANCE TO CRIMINAL");
            checkPoint.setPosition(initial * 3.6f, up - 1.5f * float(checkPoint.getCharacterSize()));
        }
        else {
            // Derramage
            if (distanceGoalCar > 0){
                // Goal car goes in front of the player
                checkPoint.setString("DISTANCE TO RIVAL");
                checkPoint.setPosition(initial * 3.8f, up - 1.5f * float(checkPoint.getCharacterSize()));
            }
            else {
                // The player goes first and the goal car goes behind
                checkPoint.setString("LEAD DISTANCE");
                checkPoint.setPosition(initial * 4.0f, up - 1.5f * float(checkPoint.getCharacterSize()));
            }
        }
        c.w.draw(checkPoint);

        Text distanceCheckPoint;
        distanceCheckPoint.setFont(c.fontTimeToPlay);
        distanceCheckPoint.setCharacterSize(static_cast<unsigned int>(int(38.0f * c.screenScale)));

        // Check the color of the distance indicator
        if (distanceGoalCar >= 100){
            distanceCheckPoint.setFillColor(Color::Green);
        }
        else if (distanceGoalCar < 100 && distanceGoalCar >= 50){
            distanceCheckPoint.setFillColor(Color::Yellow);
        }
        else if (distanceGoalCar < 0){
            distanceCheckPoint.setFillColor(Color(30, 159, 211));
        }
        else if (distanceGoalCar < 50){
            distanceCheckPoint.setFillColor(Color::Red);
        }

        if (typeOfGame == 3){
            if (updatedGoalCar || updatedPlayerCar){
                distanceCheckPoint.setString("CALCULATING");
                distanceCheckPoint.setFillColor(Color(183, 164, 190));
                distanceCheckPoint.setPosition(initial * 5.2f - distanceCheckPoint.getLocalBounds().width,
                                               up - 0.5f * float(distanceCheckPoint.getCharacterSize()));

            }
            else {
                distanceCheckPoint.setString(" " + to_string(distanceGoalCar) + " M");
                distanceCheckPoint.setPosition(initial * 5.0f - distanceCheckPoint.getLocalBounds().width,
                                               up - 0.5f * float(distanceCheckPoint.getCharacterSize()));
            }
        }
        else if (typeOfGame == 4){
            if (updatedGoalCar || updatedPlayerCar){
                distanceCheckPoint.setString("CALCULATING");
                distanceCheckPoint.setFillColor(Color(183, 164, 190));
                if (distanceGoalCar > 0){
                    distanceCheckPoint.setPosition(initial * 5.32f - distanceCheckPoint.getLocalBounds().width,
                                                   up - 0.5f * float(distanceCheckPoint.getCharacterSize()));
                }
                else {
                    distanceCheckPoint.setPosition(initial * 5.32f - distanceCheckPoint.getLocalBounds().width,
                                                   up - 0.5f * float(distanceCheckPoint.getCharacterSize()));
                }
            }
            else {
                if (distanceGoalCar > 0){
                    distanceCheckPoint.setString( " " + to_string(distanceGoalCar) + " M");
                }
                else {
                    distanceCheckPoint.setString(" " + to_string(abs(distanceGoalCar)) + " M");
                }
                distanceCheckPoint.setPosition(initial * 5.0f - distanceCheckPoint.getLocalBounds().width,
                                           up - 0.5f * float(distanceCheckPoint.getCharacterSize()));
            }
        }

        distanceCheckPoint.setOutlineColor(Color::Black);
        distanceCheckPoint.setOutlineThickness(3.0f * c.screenScale);
        c.w.draw(distanceCheckPoint);
    }

    bool drawHealthIndicator = false;

    if (typeOfGame == 3){
        if (c.enablePixelArt){
            if (distanceGoalCar <= 30.f && !updatedGoalCar && !updatedPlayerCar){
                drawHealthIndicator = true;
            }
        }
        else {
            if (distanceGoalCar <= 120.f && !updatedGoalCar && !updatedPlayerCar){
                drawHealthIndicator = true;
            }
        }

        if (drawHealthIndicator){
            Text healthText;
            healthText.setFont(c.fontTimeToPlay);
            healthText.setString(to_string(int(BONIFICATION) * 100));
            healthText.setCharacterSize(static_cast<unsigned int>(int(28.0f * c.screenScale)));
            healthText.setFillColor(Color(227, 17, 30));
            healthText.setOutlineColor(Color::Black);
            healthText.setOutlineThickness(3.0f * c.screenScale);
            healthText.setString("HEALTH");
            healthText.setPosition(initial / 1.1f - healthText.getLocalBounds().width, up * 2.5f - 2.2f * float(healthText.getCharacterSize()));
            c.w.draw(healthText);

            // Draw the rectangle
            RectangleShape shape;
            shape.setPosition(initial / 2.0f, up * 2.25f);
            if (c.isDefaultScreen){
                shape.setSize(sf::Vector2f(40.0f * c.screenScale, 420.0f * float(c.w.getSize().y) / DEFAULT_HEIGHT));
            }
            else {
                shape.setSize(sf::Vector2f(40.0f * c.screenScale, 420.0f * float(c.w.getSize().y) / DEFAULT_HEIGHT * 0.95f));
            }

            shape.setOutlineColor(Color::Black);
            shape.setOutlineThickness(3.0f * c.screenScale);

            if (lifeGoalCar <= 50 && lifeGoalCar >= 25){
                shape.setFillColor(Color::Yellow);
            }
            else if (lifeGoalCar < 25){
                shape.setFillColor(Color::Red);
            }
            else {
                shape.setFillColor(Color::Green);
            }

            c.w.draw(shape);

            // Draw the rectangle of the life
            shape.setPosition(initial / 2.0f, up * 2.25f);

            if (c.isDefaultScreen){
                shape.setSize(sf::Vector2f(40.0f * c.screenScale,
                                           (100 - lifeGoalCar) * (420.0f * float(c.w.getSize().y) / DEFAULT_HEIGHT) / 100));
            }
            else {
                shape.setSize(sf::Vector2f(40.0f * c.screenScale,
                                            (100 - lifeGoalCar) * (420.0f * float(c.w.getSize().y) / DEFAULT_HEIGHT * 0.95f) / 100));
            }
            shape.setOutlineThickness(0.0f * c.screenScale);
            shape.setFillColor(Color::Black);
            c.w.draw(shape);
        }
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
    timeToPlay.setCharacterSize(static_cast<unsigned int>(int(38.0f * c.screenScale)));
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
            break;
        case 5:
            speed = player6.getRealSpeed();
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
            break;
        case 5:
            strSpeed = to_string(player6.getRealSpeed());
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
    checkPoint.setCharacterSize(static_cast<unsigned int>(int(38.0f * c.screenScale)));
    checkPoint.setFillColor(Color::White);
    checkPoint.setOutlineColor(Color::Black);
    checkPoint.setOutlineThickness(3.0f * c.screenScale);

    int distance = 0;

    // Check if it is the last checkPoint
    if (indexCheckPoint % 4 != 0){
        checkPoint.setString("NEXT CHECKPOINT");
        checkPoint.setPosition(initial * 3.1f, up - 1.5f * float(checkPoint.getCharacterSize()));

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
                break;
            case 5:
                distance = (checkPointPositions[indexCheckPoint - 1] - player6.getPosY()) / 7;
        }
    }
    else {
        checkPoint.setString("GOAL IN");
        checkPoint.setPosition(initial * 3.49f, up - 1.5f * float(checkPoint.getCharacterSize()));

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
                break;
            case 5:
                distance = (currentMap->getMaxY() - player6.getPosY()) / 7;
        }
    }

    c.w.draw(checkPoint);

    // Distance to the next checkpoint
    Text distanceCheckPoint;
    distanceCheckPoint.setFont(c.fontTimeToPlay);
    distanceCheckPoint.setString(" " + to_string(distance) + " M");
    distanceCheckPoint.setCharacterSize(static_cast<unsigned int>(int(38.0f * c.screenScale)));

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
        if (c.window.hasFocus() && Keyboard::isKeyPressed(c.soundtrackKey)){
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
            titleSoundtrack.setCharacterSize(static_cast<unsigned int>(int(38.0f * c.screenScale)));
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
    textForLap.setString(lapCheckPoint);
    textForLap.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
    textForLap.setOutlineThickness(3.0f * c.screenScale);
    textForLap.setPosition(float(c.w.getSize().x / 2.f) - textForLap.getGlobalBounds().width / 2.0f, initial);

    Text extendTime;
    extendTime.setFont(c.fontTimeToPlay);
    extendTime.setString("EXTENDED TIME!");
    extendTime.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));
    extendTime.setOutlineThickness(3.0f * c.screenScale);
    extendTime.setPosition(float(c.w.getSize().x /2.f) - extendTime.getLocalBounds().width / 2.f, initial);

    s.setTexture(textures[4], true);
    s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
    textForLap.setPosition(float(c.w.getSize().x / 2.f) - textForLap.getGlobalBounds().width / 2.f,
                           initial + 3.4f * s.getGlobalBounds().height);

    if (c.enablePixelArt){
        s.setPosition(float(c.w.getSize().x / 2.f) - s.getLocalBounds().width / 2.0f, initial * 1.3f);
    }
    else {
        s.setPosition(float(c.w.getSize().x / 2.f) - s.getLocalBounds().width / 0.9f, initial * 1.3f);
    }

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
    time = 0;
    numberPlayersGroup = 0;
    codePlayerInGroup = 0;
    kindVehicle = 0;

    // Control if the player is still playing
    finalGame = false;
    randomMultiplayerJoined = false;
    inGame = false;
    onPause = false;
    blink = false;
    arrival = false;
    updatedTimeCheck = false;
    comeFromOptions = false;
    shown = false;
    onMultiplayer = false;
    woman_delay = seconds(5.0f);
    traffic_delay = seconds(2.f);
    blink_delay = seconds(0.5f);
    bonus_delay = seconds(0.01f);
    police_car_delay = seconds(10.f);
    police_driver_delay = seconds(5.f);

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
            break;
         case 4:
            player5.setVehicle(typeOfGame);
            break;
        case 5:
            player6.setVehicle(typeOfGame);
    }

    // Times of each scenario
    vector<int> times;

    string path;
    if (typeOfGame == 0){
        times = {50, 53, 51, 52};
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

    // Delete the possible landscapes loaded in last attempts
    tourLandScapes.clear();

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
        time = int(float(currentMap->getTimeToPlay()) * timeMul);
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
    drawingGoalCar = false;

    minutes = 0;
    secs = 0;
    cents_second = 0;
    minutesTrip = 0;
    secsTrip = 0;
    cents_secondTrip = 0;
    timeCheck = 0;
    lap = "00:00:00";
    indexCheckPoint = 1;
    posArrival = 1;

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
            break;
        case 4:
            player5.setVehicle(typeOfGame);
            break;
        case 5:
            player6.setVehicle(typeOfGame);
    }

    // Control the loading of the landscapes
    int nm = 0;

    // Times of each scenario
    vector<int> times;

    if (typeOfGame == 1){
        times = {68, 65, 63, 62, 62, 59, 59, 55, 55, 53, 53, 48, 47, 47, 48};
    }
    else {
        times = {68, 65, 63, 62, 62, 59, 59, 55, 55, 53, 53, 48, 47, 47, 48};
    }

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
            break;
        case 4:
            // Demarrage mode
            pathMode = "Data/Gamemodes/Demarrage/LandScapes/LandScape";
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
    // Store the initial matrix
    referencedMaps = maps;

    // Load the game mode hud
    loadHudGameOutRunDrivingFuryDerramage();

    score = 0;
    level = mapId.first + 1;
    time = int(float(currentMap->getTimeToPlay()) * timeMul) + bdTime;

    if (typeOfGame == 3){
        updatedGoalCar = false;
        updatedPlayerCar = false;
        maxDistance = 1000;
        distanceGoalCar = maxDistance;

        totalStages = 3;
        currentStage = 1;
        goalCarStage = 2;
        currentLandScape = 0;

        // Code to generate randomly a vehicle to chase which cant be a motorbike
        int vehicle = rand_generator_int(0, 4);

        // Select a color to the type of vehicle chosen
        int colorVehicle = rand_generator_int(0, 7);

        // Set the scale of the vehicle
        switch(vehicle){
            case 0:
                RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 2.5f, COUNTER, "Data/Vehicles/Motorbikes/Motorbike" +
                                   to_string(colorVehicle + 1), 0.f, maxDistance, Motorbike_vehicle::PLAYER_TEXTURES, 1, 2, 15, 16,
                                   3, 8, 17, 22, 9, 14, 23, 28, 1, 2, 15, 16, 3, 8, 17, 22, 9, 14, 23, 28, 7, 13, 7, 13, 21, 27,
                                   21, 27, 1.15f);
                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
                break;
            case 1:
                goalCar = RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 4.f, COUNTER, "Data/Vehicles/Devastators/Devastator" +
                             to_string(colorVehicle + 1), 0.f, maxDistance, Devastator_vehicle::PLAYER_TEXTURES, 1, 4, 19, 22,
                             5, 8, 23, 26, 9, 12, 27, 30, 13, 14, 31, 32, 15, 16, 33, 34, 17, 18, 35, 36, 6, 10, 15, 17, 24,
                             28, 33, 35, 1.55f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
                break;
            case 2:
                goalCar = RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 4.f, COUNTER, "Data/Vehicles/Minivans/Minivan" + to_string(colorVehicle + 1),
                             0.f, maxDistance, Minivan_vehicle::PLAYER_TEXTURES, 1, 2, 15, 16, 3, 5, 17, 19, 6, 8, 17, 19, 9, 10, 23, 24,
                             11, 12, 25, 26, 13, 14, 20, 22, 3, 6, 11, 13, 17, 20, 25, 27, 1.45f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
                break;
            case 3:
                goalCar = RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 4.5f, COUNTER, "Data/Vehicles/Trucks/Truck" + to_string(colorVehicle + 1),
                             0.f, maxDistance, Truck_vehicle::PLAYER_TEXTURES, 1, 5, 28, 32, 6, 10, 33, 37, 11, 15, 38, 42, 16, 19,
                             43, 46, 20, 23, 47, 50, 24, 27, 51, 54, 7, 12, 21, 25, 34, 39, 48, 52, 1.50f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
                break;
            case 4:
                goalCar = RivalCar(typeOfVehicle, MAX_SPEED, SPEED_FACTOR, 4.5f, COUNTER, "Data/Vehicles/FormulaOnes/FormulaOne"
                                   + to_string(colorVehicle + 1), 0.f, maxDistance, FormulaOne_vehicle::PLAYER_TEXTURES, 1, 2, 23,
                                   24, 3, 12, 25, 34, 13, 22, 35, 44, 1, 2, 23, 24, 3, 12, 25, 34, 13, 22, 35, 44, 11, 21, 11, 21,
                                   33, 43, 33, 43, 1.80f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
        }

        displayGoalCarIndicator = true;
        lifeGoalCar = 100;
        goalCar.setSmoking();
    }
    else if (typeOfGame == 4) {
        updatedGoalCar = false;
        updatedPlayerCar = false;
        maxDistance = 1000;
        distanceGoalCar = maxDistance;
        distanceAdvanced = 400;

        totalStages = 3;
        currentStage = 1;
        goalCarStage = 2;
        currentLandScape = 0;

        // Code to generate randomly a vehicle to chase which cant be a motorbike
        int vehicle = rand_generator_int(0, 4);

        // Select a color to the type of vehicle chosen
        int colorVehicle = rand_generator_int(0, 7);

        // Set the scale of the vehicle
        switch(vehicle){
            case 0:
                goalCar = RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 2.5f, COUNTER, "Data/Vehicles/Motorbikes/Motorbike" +
                                   to_string(colorVehicle + 1), 0.f, maxDistance, Motorbike_vehicle::PLAYER_TEXTURES, 1, 2, 15, 16,
                                   3, 8, 17, 22, 9, 14, 23, 28, 1, 2, 15, 16, 3, 8, 17, 22, 9, 14, 23, 28, 7, 13, 7, 13, 21, 27,
                                   21, 27, 1.15f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
                break;
            case 1:
                goalCar = RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 4.f, COUNTER, "Data/Vehicles/Devastators/Devastator" +
                             to_string(colorVehicle + 1), 0.f, maxDistance, Devastator_vehicle::PLAYER_TEXTURES, 1, 4, 19, 22,
                             5, 8, 23, 26, 9, 12, 27, 30, 13, 14, 31, 32, 15, 16, 33, 34, 17, 18, 35, 36, 6, 10, 15, 17, 24,
                             28, 33, 35, 1.55f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
                break;
            case 2:
                goalCar = RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 4.f, COUNTER, "Data/Vehicles/Minivans/Minivan" + to_string(colorVehicle + 1),
                             0.f, maxDistance, Minivan_vehicle::PLAYER_TEXTURES, 1, 2, 15, 16, 3, 5, 17, 19, 6, 8, 17, 19, 9, 10, 23, 24,
                             11, 12, 25, 26, 13, 14, 20, 22, 3, 6, 11, 13, 17, 20, 25, 27, 1.45f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
                break;
            case 3:
                goalCar = RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 4.5f, COUNTER, "Data/Vehicles/Trucks/Truck" + to_string(colorVehicle + 1),
                             0.f, maxDistance, Truck_vehicle::PLAYER_TEXTURES, 1, 5, 28, 32, 6, 10, 33, 37, 11, 15, 38, 42, 16, 19,
                             43, 46, 20, 23, 47, 50, 24, 27, 51, 54, 7, 12, 21, 25, 34, 39, 48, 52, 1.50f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
                break;
            case 4:
                goalCar = RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 4.5f, COUNTER, "Data/Vehicles/FormulaOnes/FormulaOne"
                                   + to_string(colorVehicle + 1), 0.f, maxDistance, FormulaOne_vehicle::PLAYER_TEXTURES, 1, 2, 23,
                                   24, 3, 12, 25, 34, 13, 22, 35, 44, 1, 2, 23, 24, 3, 12, 25, 34, 13, 22, 35, 44, 11, 21, 11, 21,
                                   33, 43, 33, 43, 1.80f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
        }

        displayGoalCarIndicator = true;
        goalCar.setSmoking();
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
        case EASY:
            numCars = 5;
            timeMul = 1.1f;
            scoreMul = 0.5f;
            numCrashesGoalCar = 8;
            lifeLostPerCrash = int(100 / numCrashesGoalCar);
            if (c.enableAI){
                c.maxAggressiveness = 0.25f;
            }
            break;
        case NORMAL:
            numCars = 10;
            timeMul = 1.0f;
            scoreMul = 1.0f;
            numCrashesGoalCar = 10;
            lifeLostPerCrash = int(100 / numCrashesGoalCar);
            if (c.enableAI){
                c.maxAggressiveness = 0.5f;
            }
            break;
        case HARD:
            numCars = 15;
            timeMul = 0.9f;
            scoreMul = 1.5f;
            numCrashesGoalCar = 15;
            lifeLostPerCrash = int(100 / numCrashesGoalCar);
            if (c.enableAI){
                c.maxAggressiveness = 0.75f;
            }
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
        if (typeOfGame != 0 && typeOfGame != 2){
            const float vehicleScales[maxSprites] = {1.3f, 1.8f, 1.8f, 1.8f, 1.8f, 1.8f};
            for (int i = static_cast<int>(cars.size()); i < numCars; i++) {
                if (1 + i % maxSprites == 4){
                    TrafficCar v(MAX_SPEED, SPEED_FACTOR, vehicleScales[i % maxSprites], COUNTER,
                        "Data/Vehicles/TrafficCars/TrafficCar" + to_string(1 + i % maxSprites), 0.f, -RECTANGLE * DEL_DISTANCE * 3.0, true);
                    cars.push_back(v);
                }
                else {
                    TrafficCar v(MAX_SPEED, SPEED_FACTOR, vehicleScales[i % maxSprites], COUNTER,
                        "Data/Vehicles/TrafficCars/TrafficCar" + to_string(1 + i % maxSprites), 0.f, -RECTANGLE * DEL_DISTANCE * 3.0f, false);
                    cars.push_back(v);
                }
            }
        }
        else {
            const float vehicleScales[maxSprites] = {1.9f, 2.4f, 2.4f, 2.4f, 2.4f, 2.4f};
            for (int i = static_cast<int>(cars.size()); i < numCars; i++) {
                if (1 + i % maxSprites == 4){
                    TrafficCar v(MAX_SPEED, SPEED_FACTOR, vehicleScales[i % maxSprites], COUNTER,
                        "Data/Vehicles/TrafficCars/TrafficCar" + to_string(1 + i % maxSprites), 0.f, -RECTANGLE * DEL_DISTANCE * 3.0f, true);
                    cars.push_back(v);
                }
                else {
                    TrafficCar v(MAX_SPEED, SPEED_FACTOR, vehicleScales[i % maxSprites], COUNTER,
                        "Data/Vehicles/TrafficCars/TrafficCar" + to_string(1 + i % maxSprites), 0.f, -RECTANGLE * DEL_DISTANCE * 3.0f, false);
                    cars.push_back(v);
                }
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
            if ((c.window.hasFocus() && Keyboard::isKeyPressed(c.menuKey)) || onPause) {
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
                    r.soundTracks[0]->play();
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

            startPressed = c.window.hasFocus() && Keyboard::isKeyPressed(c.menuEnterKey);
        }
        r.soundTracks[13]->stop();
        r.soundEffects[2]->stop();
        r.soundEffects[2]->play();
        r.soundTracks[0]->play();
        return START;
    }
    return status;
}



/**
 * Updates the logic of the game and refreshes the screen until you leave the game.
 * @param c is the configuration of the game
 * @return
 */
State Game::playOutRunDrivingFuryDemarrage(Configuration &c, SoundPlayer& r) {

    if (!inGame) {
        inGame = true;
        showsInitialAnimation(c, r);
    }
    else if ((typeOfGame == 3 || typeOfGame == 4) && !comeFromOptions){
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

    policeCarClock.restart();
    elapsed15 = policeCarClock.getElapsedTime().asSeconds();

    policeDriverClock.restart();
    elapsed17 = policeDriverClock.getElapsedTime().asSeconds();

    int localTime;

    if (!comeFromOptions){
        // Thread to control the elapsed time
        timer0 = thread(updateTimeElapsed, this);

        // Thread to control the time of the landscape
        timer1 = thread(updateTimeLandScape, this);

        if (typeOfGame == 1){
            // Thread to counter the score of the game
            timer2 = thread(updateScore, this);
        }
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
                if (typeOfGame == 1){
                    timer2.join();
                }
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
            if ((c.window.hasFocus() && Keyboard::isKeyPressed(c.menuKey)) || onPause) {
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
                    r.soundTracks[0]->play();
                    return START;
                }
                else if (status == PLAY_GAME) {
                    r.soundTracks[r.currentSoundtrack]->play();
                    timer0 = thread(updateTimeElapsed, this);
                    timer1 = thread(updateTimeLandScape, this);
                    if (typeOfGame == 1){
                        timer2 = thread(updateScore, this);
                    }
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

            float posY = 0.f;

            switch(typeOfVehicle){
                case 0:
                    posY = player.getPosY();
                    break;
                case 1:
                    posY = player2.getPosY();
                    break;
                case 2:
                    posY = player3.getPosY();
                    break;
                case 3:
                    posY = player4.getPosY();
                    break;
                case 4:
                    posY = player5.getPosY();
                    break;
                case 5:
                    posY = player6.getPosY();
            }

            // Draw the goal indicator
            if ((typeOfGame == 3 || typeOfGame == 4)){
                // Check if a tenth of second has passed between both timestamps
                if (c.enablePixelArt){
                    if  (goalCar.getPosY() - posY <= 30.f && currentLandScape >= goalCarStage){
                        // Dont display the goal car indicator
                        displayGoalCarIndicator = false;

                        if (!updatedGoalCar && !updatedPlayerCar &&
                            !goalNearCar && typeOfGame == 3)
                        {
                            goalNearCar = true;
                            r.soundEffects[105]->stop();
                            r.soundEffects[105]->play();
                        }
                    }
                    else {
                        // Dont display the goal car indicator
                        displayGoalCarIndicator = true;
                        goalNearCar = false;
                    }
                }
                else {
                    if (goalCar.getPosY() - posY <= 120.f && currentLandScape >= goalCarStage){
                        // Dont display the goal car indicator
                        displayGoalCarIndicator = false;

                        if (!updatedGoalCar && !updatedPlayerCar &&
                            !goalNearCar && typeOfGame == 3)
                        {
                            goalNearCar = true;
                            r.soundEffects[105]->stop();
                            r.soundEffects[105]->play();
                        }
                    }
                    else {
                        // Dont display the goal car indicator
                        displayGoalCarIndicator = true;
                        goalNearCar = false;
                    }
                }
            }

            // Check the possible police car sounds
            if (!updatedGoalCar && !updatedPlayerCar && goalNearCar &&
                typeOfGame == 3 && currentLandScape >= goalCarStage && typeOfVehicle == 5)
            {
                // Check if the police car sound has to be reproduced
                elapsed16 = policeCarClock.getElapsedTime().asSeconds();

                // Check if a second has passed between both timestamps
                if (elapsed16 - elapsed15 >= police_car_delay.asSeconds()) {

                    // WomanSound
                    r.soundEffects[91]->stop();
                    r.soundEffects[92]->stop();
                    r.soundEffects[93]->stop();
                    r.soundEffects[94]->stop();
                    r.soundEffects[95]->stop();
                    r.soundEffects[rand_generator_int(91, 95)]->play();

                    // Reproduce the police car sound
                    policeCarClock.restart();
                }
            }

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
        if (typeOfGame == 1){
            timer2.join();
        }
    }

    mtx.lock();
    if (finalGame){
        finalGame = false;
        mtx.unlock();
        if (typeOfGame == 3 || typeOfGame == 4){
            if (status == OPTIONS){
                return OPTIONS;
            }
            else if (status == START){
                r.soundTracks[0]->play();
                return START;
            }
        }
    }
    if (arrival) {
        arrival = false;
        mtx.unlock();
        // World tour and Pole Position modes

        if (typeOfGame == 1){
            return RANKING;
        }
        else {
            // Stop the current soundtrack
            r.soundTracks[r.currentSoundtrack]->stop();

            // Reproduce goal animation
            showsDerramageDrivingFuryAnimation(c, r);

            r.soundTracks[15]->play();
            return CLASIFICATION;
        }
    }
    mtx.unlock();

    if (status != OPTIONS && status != START && time <= 0) {
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

            startPressed = c.window.hasFocus() && Keyboard::isKeyPressed(c.menuEnterKey);
        }
        r.soundTracks[13]->stop();
        r.soundEffects[2]->stop();
        r.soundEffects[2]->play();
        r.soundTracks[0]->play();
        return START;
    }
    else if (typeOfGame == 3 || typeOfGame  == 4){
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
        currentMap->drawLandScape(c, cars, rivals, typeOfGame, goalCar, displayGoalCarIndicator, false);

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
                break;
            case 5:
                player6.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player6.getPosY()), -1);
        }

        // Draw the HUD of the game
        if (typeOfGame == 0 || typeOfGame == 2){
            showHudInterfaceWorldTourPolePosition(c);
        }
        else {
            showHudInterfaceOutRunDrivingFuryDerramage(c);
        }

        if (typeOfGame == 0){
            Text titleLandScape;
            titleLandScape.setFont(c.fontTimeToPlay);
            titleLandScape.setString(currentMap->getName());
            titleLandScape.setCharacterSize(static_cast<unsigned int>(int(45.0f * c.screenScale)));
            titleLandScape.setFillColor(Color::Yellow);
            titleLandScape.setOutlineColor(Color(14, 29, 184));
            titleLandScape.setOutlineThickness(3.0f * c.screenScale);
            titleLandScape.setPosition((float(c.w.getSize().x) - titleLandScape.getGlobalBounds().width) / 2.0f,
                                       (float(c.w.getSize().y) + float(titleLandScape.getCharacterSize())) / 1.4f);

            c.w.draw(titleLandScape);
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

    // Detect the possible events
    Event e;

    if (typeOfGame == 4){

        Font f;
        f.loadFromFile("Data/Fonts/Hetikademo.otf");

        // Store the position
        Text reasonDetentionText1;
        reasonDetentionText1.setString("GET " + to_string(distanceAdvanced) + " METERS");
        reasonDetentionText1.setCharacterSize(static_cast<unsigned int>(int(45.0f * c.screenScale)));
        reasonDetentionText1.setFont(f);
        reasonDetentionText1.setStyle(Text::Bold);
        reasonDetentionText1.setFillColor(Color::Green);
        reasonDetentionText1.setOutlineColor(Color::Black);
        reasonDetentionText1.setOutlineThickness(5.0f * c.screenScale);
        reasonDetentionText1.setPosition((c.w.getSize().x / 2.f) - (reasonDetentionText1.getLocalBounds().width / 2.f),
                                         c.w.getSize().y / 2.f - 75.f * c.screenScale);

        // Store the position
        Text reasonDetentionText2;
        reasonDetentionText2.setString("AHEAD OF YOUR RIVAL");
        reasonDetentionText2.setCharacterSize(static_cast<unsigned int>(int(45.0f * c.screenScale)));
        reasonDetentionText2.setFont(f);
        reasonDetentionText2.setStyle(Text::Bold);
        reasonDetentionText2.setFillColor(Color::Green);
        reasonDetentionText2.setOutlineColor(Color::Black);
        reasonDetentionText2.setOutlineThickness(5.0f * c.screenScale);
        reasonDetentionText2.setPosition((c.w.getSize().x / 2.f) - (reasonDetentionText2.getLocalBounds().width / 2.f),
                                         c.w.getSize().y / 2.f - 15.f * c.screenScale);

        for (int i = 0; i < 200; i++){

            // Detect the possible events
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }

            // Draw map
            c.w.clear();
            currentMap->drawLandScape(c, cars, rivals, typeOfGame, goalCar, displayGoalCarIndicator, false);

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
                    break;
                case 5:
                    player6.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player6.getPosY()), -1);
            }

            showHudInterfaceOutRunDrivingFuryDerramage(c);

            c.w.draw(reasonDetentionText1);
            c.w.draw(reasonDetentionText2);
            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
        }
    }

    // Reproduce motor sounds
    if (typeOfVehicle == 4){
        r.soundEffects[125]->stop();
        r.soundEffects[125]->play();
    }
    else if (typeOfVehicle == 5){
        r.soundEffects[115]->stop();
        r.soundEffects[115]->play();
    }
    else if (typeOfVehicle != 0){
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
            break;
        case 5:
            player6.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player6.getPosY()), -1);
    }

    if (typeOfGame != 3){
        for (int i = 0; i < 3; i++) {

            // Detect the possible events
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }

            // Draw map
            c.w.clear();
            currentMap->drawLandScape(c, cars, rivals, typeOfGame, goalCar, displayGoalCarIndicator, false);

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
                    break;
                case 5:
                    player6.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player6.getPosY()), -1);
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
                    currentMap->drawLandScape(c, cars, rivals, typeOfGame, goalCar, displayGoalCarIndicator, false);

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
                            break;
                        case 5:
                            player6.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player6.getPosY()), -1);
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
    }
    else if (typeOfGame == 3){
        Text indicatorStart;
        indicatorStart.setFont(c.fontTimeToPlay);
        indicatorStart.setString("READY");
        indicatorStart.setCharacterSize(static_cast<unsigned int>(int(65.0f * c.screenScale)));
        indicatorStart.setFillColor(Color::Green);
        indicatorStart.setOutlineColor(Color(12, 12, 12));
        indicatorStart.setOutlineThickness(3.0f * c.screenScale);

        for (int i = 0; i < 3; i++){
            // Detect the possible events
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }

            if (i == 0){
                r.soundEffects[111]->stop();
                r.soundEffects[111]->play();
            }
            else if (i == 1){
                indicatorStart.setString("SET");
                r.soundEffects[112]->stop();
                r.soundEffects[112]->play();
            }
            else if (i == 2){
                indicatorStart.setString("GO!");
                r.soundEffects[113]->stop();
                r.soundEffects[113]->play();
            }

            indicatorStart.setPosition(c.w.getSize().x / 2.f - indicatorStart.getLocalBounds().width / 2.f,
                                       c.w.getSize().y / 2.f - indicatorStart.getLocalBounds().height / 2.f);

            // Draw map
            c.w.clear();
            currentMap->drawLandScape(c, cars, rivals, typeOfGame, goalCar, displayGoalCarIndicator, false);

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
                    break;
                case 5:
                    player6.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player6.getPosY()), -1);
            }

            showHudInterfaceOutRunDrivingFuryDerramage(c);

            c.w.draw(indicatorStart);
            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();

            if (i == 0){
                while (r.soundEffects[111]->getStatus() != SoundSource::Stopped){}
            }
            else if (i == 1){
                while (r.soundEffects[112]->getStatus() != SoundSource::Stopped){}
            }
            else if (i == 2){
                while (r.soundEffects[113]->getStatus() != SoundSource::Stopped){}
            }
        }
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
                break;
            case 4:
                r.soundEffects[28]->stop();
                r.soundEffects[122]->stop();
                r.soundEffects[122]->play();
                break;
            case 5:
                switch(kindVehicle){
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
                        break;
                    case 4:
                        r.soundEffects[28]->stop();
                        r.soundEffects[122]->stop();
                        r.soundEffects[122]->play();
                }
        }

        for (RivalCar rival : rivals){
            rival.setSmoking();
        }
    }

    // Reproduce police car sound
    if (typeOfGame == 3){
        r.soundEffects[115]->stop();
        r.soundEffects[99]->stop();
        r.soundEffects[100]->stop();
        r.soundEffects[rand_generator_int(99, 100)]->play();
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


        positionText.setString(place);
        positionText.setFont(c.fontTimeToPlay);
        positionText.setCharacterSize(static_cast<unsigned int>(int(65.0f * c.screenScale)));
        positionText.setStyle(Text::Bold);
        positionText.setFillColor(Color::White);
        positionText.setOutlineColor(Color::Black);
        positionText.setOutlineThickness(5.0f * c.screenScale);
        positionText.setPosition((c.w.getSize().x / 2.f) - (positionText.getLocalBounds().width / 2.f),
                                 (c.w.getSize().y / 2.f) - (positionText.getLocalBounds().height / 2.f));

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
    else if (typeOfGame == 3 || typeOfGame == 4){
        r.soundEffects[45]->stop();
        r.soundEffects[45]->play();

        positionText.setString("MISSION FAILED");
        positionText.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
        positionText.setFont(c.fontTimeToPlay);
        positionText.setStyle(Text::Bold);
        positionText.setFillColor(Color::White);
        positionText.setOutlineColor(Color::Black);
        positionText.setOutlineThickness(5.0f * c.screenScale);
        positionText.setPosition((c.w.getSize().x / 2.f) - (positionText.getLocalBounds().width / 2.f),
                                 (c.w.getSize().y / 2.f) - (positionText.getLocalBounds().height / 2.f));
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
    elapsed11 = bonus.getElapsedTime().asSeconds(); // TODO: Esta marca solo se actualiza aqu� ?????

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
            break;
        case 5:
            player6.setPosition(player6.getPosX(), 5.f);
            position = int(player6.getPosY());
    }

    // claps
    if (posArrival <= 3 && (typeOfGame == 0 || typeOfGame == 2)){
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
                if (typeOfGame == 1){
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
                break;
            case 5:
                positionX = player6.getPosX();
                positionY = player6.getPosY();
        }

        // Update camera
        currentMap->updateCamera(positionX, positionY - RECTANGLE);

        // Draw map
        c.w.clear();
        currentMap->drawLandScape(c, cars, rivals, typeOfGame, goalCar, displayGoalCarIndicator, false);

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
                break;
            case 5:
                player6.setPosition(player6.getPosX(), player6.getPosY() + 1);
                player6.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                        currentMap->getElevation(player6.getPosY()), currentMap->getTerrain(), false);
        }

        if (typeOfGame != 1){

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

            // Move all the rivals
            for (RivalCar& r :rivals){
                r.setPosition(r.getPosX(), r.getPosY() + 1);
                r.draw(Vehicle::ACCELERATE, currentMap->getElevation(r.getPosY()));
            }
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
                break;
            case 5:
                position = int(player6.getPosY());
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
    else if (typeOfGame == 1){
        return RANKING;
    }
    else {
        r.soundTracks[0]->play();
        return START;
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
            break;
        case 4:
            currentMap->updateCamera(player5.getPosX(), player5.getPosY() - RECTANGLE);
            break;
        case 5:
            currentMap->updateCamera(player6.getPosX(), player6.getPosY() - RECTANGLE);
            break;
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
                break;
            case 4:
                player5.setPosition(player5.getPosX() + currentMap->getOffsetX(), player5.getPosY() - currentMap->getMaxY());
                break;
            case 5:
                player6.setPosition(player6.getPosX() + currentMap->getOffsetX(), player6.getPosY() - currentMap->getMaxY());
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
                break;
            case 4:
                pos = player5.getPosY();
                halfspeed = player5.getHalfMaxSpeed();
                break;
            case 5:
                pos = player6.getPosY();
                halfspeed = player6.getHalfMaxSpeed();
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
            if (v.getPosY() + DEL_DISTANCE < currentMap->getCameraPosY()) {
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
                break;
            case 4:
                positionX = player5.getPosX();
                positionY = player5.getPosY();
                speedPlayer = player5.getSpeed();
                break;
            case 5:
                positionX = player6.getPosX();
                positionY = player6.getPosY();
                speedPlayer = player6.getSpeed();
        }

        // Clear the ranking of the rivals for updating
        rankingVehicles.clear();

        int i = 0;

        // Update and prepare racers to draw
        for (RivalCar &v : rivals) {
            float directionCurve = currentMap->getCurveCoefficient(v.getPosY());

            if (!v.isCrashing() && !v.inCrash()){
                v.updateModeA(c, lastY, lastY + float(c.renderLen) / DENSITY_SPACE, c.maxAggressiveness, a, directionCurve,
                              c.level, positionX, positionY, speedPlayer, false);
            }

            vehicleCrash = false;
            float crashPos;

            if (!v.isCrashing() && !v.inCrash()){
                // Check if the current rival car has crashed with a traffic car
                if (abs(v.getPosY() - positionY) <= c.renderLen){
                    for (int i = 0; !vehicleCrash && i < (int)cars.size(); i++){
                        vehicleCrash = cars[i].hasCrashed(v.getPreviousY(), v.getPosY(),
                                                          v.getMinScreenX(), v.getMaxScreenX(), crashPos);
                    }
                }
            }

            if (vehicleCrash || v.isCrashing()) {
                // Determine the type of collision
                v.setPosition(v.getPosX(), v.getPosY());
                v.hitControl(vehicleCrash, r, positionY);
                a = Vehicle::CRASH;
            }

            if (vehicleCrash || v.isCrashing()) {
                // Determine the type of collision
                v.setPosition(v.getPosX(), v.getPosY());
                v.hitControl(vehicleCrash, r, positionY);
                a = Vehicle::CRASH;
            }

            float posY = v.getPosY();

            // Store the new position of the vehicle
            rankingVehicles.push_back(posY);

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
                            player.setPosition(player.getPosX() + 0.3f, player.getPosY() - 10.f);
                        }
                        else if (player.getPreviousX() < v.getPreviousX()){
                            player.setPosition(player.getPosX() - 0.3f, player.getPosY() - 10.f);
                        }
                        else {
                            player.setPosition(player.getPosX(), player.getPosY() - 20.f);
                        }

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
                            player2.setPosition(player2.getPosX() + 0.3f, player2.getPosY() - 20.f);
                        }
                        else if (player.getPreviousX() < v.getPreviousX()){
                            player2.setPosition(player2.getPosX() - 0.3f, player2.getPosY() - 20.f);
                        }
                        else {
                            player2.setPosition(player2.getPosX(), player2.getPosY() - 20.f);
                        }
                        r.soundEffects[87]->stop();
                        r.soundEffects[87]->play();
                    }
                    break;
                case 2:
                    vehicleCrash = v.hasCrashed(player3.getPosY(), player3.getPreviousY(),
                                                player3.getMinScreenX(), player3.getMaxScreenX(), crashPos);

                    if (vehicleCrash){
                        if (player3.getPreviousX() >= v.getPreviousX()){
                            player3.setPosition(player3.getPosX() + 0.3f, player3.getPosY() - 20.f);
                        }
                        else if (player.getPreviousX() < v.getPreviousX()){
                            player3.setPosition(player3.getPosX() - 0.3f, player3.getPosY() - 20.f);
                        }
                        else {
                            player3.setPosition(player3.getPosX(), player3.getPosY() - 20.f);
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
                            player4.setPosition(player4.getPosX() + 0.3f, player4.getPosY() - 20.f);
                        }
                        else if (player.getPreviousX() < v.getPreviousX()){
                            player4.setPosition(player4.getPosX() - 0.3f, player4.getPosY() - 20.f);
                        }
                        else {
                            player4.setPosition(player4.getPosX(), player4.getPosY() - 20.f);
                        }
                        r.soundEffects[87]->stop();
                        r.soundEffects[87]->play();
                    }
                    break;
                case 4:
                    vehicleCrash = v.hasCrashed(player5.getPosY(), player5.getPreviousY(),
                                                player5.getMinScreenX(), player5.getMaxScreenX(), crashPos);

                    if (vehicleCrash){
                        if (player5.getPreviousX() > v.getPreviousX()){
                            player5.setPosition(player5.getPosX() + 0.3f, player5.getPosY() - 20.f);
                        }
                        else if (player.getPreviousX() < v.getPreviousX()){
                            player5.setPosition(player5.getPosX() - 0.3f, player5.getPosY() - 20.f);
                        }
                        else {
                            player4.setPosition(player5.getPosX(), player5.getPosY() - 20.f);
                        }
                        r.soundEffects[87]->stop();
                        r.soundEffects[87]->play();
                    }
                    break;
                case 5:
                    vehicleCrash = v.hasCrashed(player6.getPosY(), player6.getPreviousY(),
                                                player6.getMinScreenX(), player6.getMaxScreenX(), crashPos);

                    if (vehicleCrash){
                        if (player6.getPreviousX() > v.getPreviousX()){
                            player6.setPosition(player6.getPosX() + 0.3f, player6.getPosY() - 20.f);
                        }
                        else if (player.getPreviousX() < v.getPreviousX()){
                            player5.setPosition(player6.getPosX() - 0.3f, player6.getPosY() - 20.f);
                        }
                        else {
                            player4.setPosition(player6.getPosX(), player6.getPosY() - 20.f);
                        }
                        r.soundEffects[87]->stop();
                        r.soundEffects[87]->play();
                    }
            }
            i++;
        }

        // Order the rivals cars of the race to build a temporary ranking
        sort(rankingVehicles.begin(), rankingVehicles.end(), ascendingRanking);

        // Get the new position of the player in the race
        posArrival = findPlayerPositionRanking(positionY);

        // Draw map with cars
        c.w.clear();
        currentMap->drawLandScape(c, cars, rivals, typeOfGame, goalCar, displayGoalCarIndicator, false);

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
                break;
            case 4:
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
                    if (!crash)
                        for (int i = 0; !vehicleCrash && i < (int)cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player5.getPreviousY(), player5.getPosY(),
                                                              player5.getMinScreenX(), player5.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        // player5.setModeCollision();
                        player5.setPosition(player5.getPosX(), crashPos);
                        player5.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player5.draw(c, r, action, direction, currentMap->getElevation(player5.getPosY()), terrain);
                    }
                }

                for (TrafficCar &v : cars)
                    v.autoControl(c, player5.getPosX(), player5.getPosY());
                break;
            case 5:
                if (!player6.isCrashing()) { // If not has crashed
                    action = player6.accelerationControl(c, currentMap->isOutSideRoad(player6.getPosX(), player6.getPosY()));
                    direction = player6.rotationControl(c, currentMap->getCurveCoefficient(player6.getPosY()),
                                                           currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                }
                else {
                    player6.hitControl(vehicleCrash);
                }

                player6.draw(c, r, action, direction, currentMap->getElevation(player6.getPosY()), terrain);

                if (!player6.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player6.getPreviousY(), player6.getPosY(), player6.getPosX(),
                                                        player6.getMinScreenX(), player6.getMaxScreenX(), crashPos, typeOfGame);
                    if (!crash)
                        for (int i = 0; !vehicleCrash && i < (int)cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player6.getPreviousY(), player6.getPosY(),
                                                              player6.getMinScreenX(), player6.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        player6.setModeCollision();
                        player6.setPosition(player6.getPosX(), crashPos);
                        player6.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player6.draw(c, r, action, direction, currentMap->getElevation(player6.getPosY()), terrain);
                    }
                }

                for (TrafficCar &v : cars)
                    v.autoControl(c, player6.getPosX(), player6.getPosY());
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
                        break;
                    case 4:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player5.getPosX(), player5.getPosY(), distX, distY);
                        break;
                    case 5:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player6.getPosX(), player6.getPosY(), distX, distY);
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
                        break;
                    case 4:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player5.getPosX(), player5.getPosY(), distX, distY);
                        break;
                    case 5:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player6.getPosX(), player6.getPosY(), distX, distY);
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
            break;
        case 4:
            currentMap->updateCamera(player5.getPosX(), player5.getPosY() - RECTANGLE);
            break;
        case 5:
            currentMap->updateCamera(player6.getPosX(), player6.getPosY() - RECTANGLE);
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
                break;
            case 4:
                player5.setPosition(player5.getPosX() + currentMap->getOffsetX(), player5.getPosY() - currentMap->getMaxY());
                break;
            case 5:
                player6.setPosition(player6.getPosX() + currentMap->getOffsetX(), player6.getPosY() - currentMap->getMaxY());
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
                break;
            case 4:
                pos = player5.getPosY();
                halfspeed = player5.getHalfMaxSpeed();
                break;
            case 5:
                pos = player6.getPosY();
                halfspeed = player6.getHalfMaxSpeed();
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

        float positionX, positionY, speedPlayer;

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
                break;
            case 4:
                positionX = player5.getPosX();
                positionY = player5.getPosY();
                speedPlayer = player5.getSpeed();
                break;
            case 5:
                positionX = player6.getPosX();
                positionY = player6.getPosY();
                speedPlayer = player6.getSpeed();
        }

        if (numberRacers > 0){
            // Clear the ranking of the rivals for updating
            rankingVehicles.clear();

            // Update and prepare racers to draw
            for (RivalCar &v : rivals) {
                float directionCurve = currentMap->getCurveCoefficient(v.getPosY());

                v.updateModeB(c, lastY, lastY + float(c.renderLen) / DENSITY_SPACE, c.maxAggressiveness, a, directionCurve,
                              c.level, positionX, positionY, speedPlayer, false);

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

                switch(typeOfVehicle){
                    case 0:
                        vehicleCrash = v.hasCrashed(player.getPosY(), player.getPreviousY(),
                                            player.getMinScreenX(), player.getMaxScreenX(), crashPos);

                        // Check it has been crash between player and rival
                        if (vehicleCrash){
                            if (player.getPreviousX() > v.getPreviousX()){
                                player.setPosition(player.getPosX() + 0.3f, player.getPosY() - 20.f);
                            }
                            else if (player.getPreviousX() < v.getPreviousX()){
                                player.setPosition(player.getPosX() - 0.3f, player.getPosY() - 20.f);
                            }
                            else {
                                player.setPosition(player.getPosX(), player.getPosY() - 20.f);
                            }
                            r.soundEffects[87]->stop();
                            r.soundEffects[87]->play();
                        }
                        break;
                    case 1:
                        vehicleCrash = v.hasCrashed(player2.getPosY(), player2.getPreviousY(),
                                            player5.getMinScreenX(), player5.getMaxScreenX(), crashPos);

                        // Check it has been crash between player and rival
                        if (vehicleCrash){
                            if (player2.getPreviousX() > v.getPreviousX()){
                                player2.setPosition(player5.getPosX() + 0.3f, player2.getPosY() - 20.f);
                            }
                            else if (player.getPreviousX() < v.getPreviousX()){
                                player2.setPosition(player2.getPosX() - 0.3f, player2.getPosY() - 20.f);
                            }
                            else {
                                player2.setPosition(player2.getPosX(), player2.getPosY() - 20.f);
                            }
                            r.soundEffects[87]->stop();
                            r.soundEffects[87]->play();
                        }
                        break;
                    case 2:
                        vehicleCrash = v.hasCrashed(player3.getPosY(), player3.getPreviousY(),
                                            player3.getMinScreenX(), player3.getMaxScreenX(), crashPos);

                        // Check it has been crash between player and rival
                        if (vehicleCrash){
                            if (player3.getPreviousX() > v.getPreviousX()){
                                player3.setPosition(player3.getPosX() + 0.3f, player3.getPosY() - 20.f);
                            }
                            else if (player3.getPreviousX() < v.getPreviousX()){
                                player3.setPosition(player3.getPosX() - 0.3f, player3.getPosY() - 20.f);
                            }
                            else {
                                player3.setPosition(player3.getPosX(), player3.getPosY() - 20.f);
                            }
                            r.soundEffects[87]->stop();
                            r.soundEffects[87]->play();
                        }
                        break;
                    case 3:
                        vehicleCrash = v.hasCrashed(player4.getPosY(), player4.getPreviousY(),
                                            player4.getMinScreenX(), player4.getMaxScreenX(), crashPos);

                        // Check it has been crash between player and rival
                        if (vehicleCrash){
                            if (player4.getPreviousX() > v.getPreviousX()){
                                player4.setPosition(player4.getPosX() + 0.3f, player4.getPosY() - 20.f);
                            }
                            else if (player.getPreviousX() < v.getPreviousX()){
                                player4.setPosition(player4.getPosX() - 0.3f, player4.getPosY() - 20.f);
                            }
                            else {
                                player4.setPosition(player4.getPosX(), player4.getPosY() - 20.f);
                            }
                            r.soundEffects[87]->stop();
                            r.soundEffects[87]->play();
                        }
                        break;
                    case 4:
                        vehicleCrash = v.hasCrashed(player5.getPosY(), player5.getPreviousY(),
                                            player5.getMinScreenX(), player5.getMaxScreenX(), crashPos);

                        // Check it has been crash between player and rival
                        if (vehicleCrash){
                            if (player5.getPreviousX() > v.getPreviousX()){
                                player5.setPosition(player5.getPosX() + 0.3f, player5.getPosY() - 20.f);
                            }
                            else if (player.getPreviousX() < v.getPreviousX()){
                                player5.setPosition(player5.getPosX() - 0.3f, player5.getPosY() - 20.f);
                            }
                            else {
                                player5.setPosition(player5.getPosX(), player5.getPosY() - 20.f);
                            }
                            r.soundEffects[87]->stop();
                            r.soundEffects[87]->play();
                        }
                        break;
                    case 5:
                        vehicleCrash = v.hasCrashed(player6.getPosY(), player6.getPreviousY(),
                                            player6.getMinScreenX(), player6.getMaxScreenX(), crashPos);

                        // Check it has been crash between player and rival
                        if (vehicleCrash){
                            if (player6.getPreviousX() > v.getPreviousX()){
                                player6.setPosition(player6.getPosX() + 0.3f, player6.getPosY() - 20.f);
                            }
                            else if (player.getPreviousX() < v.getPreviousX()){
                                player6.setPosition(player6.getPosX() - 0.3f, player6.getPosY() - 20.f);
                            }
                            else {
                                player6.setPosition(player6.getPosX(), player6.getPosY() - 20.f);
                            }
                            r.soundEffects[87]->stop();
                            r.soundEffects[87]->play();
                        }
                }

                // Order the rivals cars of the race to build a temporary ranking
                sort(rankingVehicles.begin(), rankingVehicles.end(), ascendingRanking);

                // Get the new position of the player in the race
                posArrival = findPlayerPositionRanking(positionY);
            }

            // Draw map with cars
            c.w.clear();
            currentMap->drawLandScape(c, cars, rivals, typeOfGame, goalCar, displayGoalCarIndicator, false);

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
                    break;
                case 4:
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
                        if (!crash)
                            for (int i = 0; !vehicleCrash && i < (int)cars.size(); i++)
                                vehicleCrash = cars[i].hasCrashed(player5.getPreviousY(), player5.getPosY(),
                                                                  player5.getMinScreenX(), player5.getMaxScreenX(),
                                                                  crashPos);

                        if (crash || vehicleCrash) {
                            // Determine the type of collision
                            // player5.setModeCollision();
                            player5.setPosition(player5.getPosX(), crashPos);
                            player5.hitControl(vehicleCrash);
                            action = Vehicle::CRASH;
                            direction = Vehicle::RIGHT;

                            player5.draw(c, r, action, direction, currentMap->getElevation(player5.getPosY()), terrain);
                        }
                    }

                    for (TrafficCar &v : cars)
                        v.autoControl(c, player5.getPosX(), player5.getPosY());
                    break;
                case 5:
                    if (!player6.isCrashing()) { // If not has crashed
                        action = player6.accelerationControl(c, currentMap->isOutSideRoad(player6.getPosX(), player6.getPosY()));
                        direction = player6.rotationControl(c, currentMap->getCurveCoefficient(player6.getPosY()),
                                                               currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                    }
                    else {
                        player6.hitControl(vehicleCrash);
                    }

                    player6.draw(c, r, action, direction, currentMap->getElevation(player6.getPosY()), terrain);

                    if (!player6.isCrashing()) {
                        vehicleCrash = false;
                        float crashPos;
                        bool crash = currentMap->hasCrashed(c, player6.getPreviousY(), player6.getPosY(), player6.getPosX(),
                                                            player6.getMinScreenX(), player6.getMaxScreenX(), crashPos, typeOfGame);
                        if (!crash)
                            for (int i = 0; !vehicleCrash && i < (int)cars.size(); i++)
                                vehicleCrash = cars[i].hasCrashed(player6.getPreviousY(), player6.getPosY(),
                                                                  player6.getMinScreenX(), player6.getMaxScreenX(),
                                                                  crashPos);

                        if (crash || vehicleCrash) {
                            // Determine the type of collision
                            player6.setModeCollision();
                            player6.setPosition(player6.getPosX(), crashPos);
                            player6.hitControl(vehicleCrash);
                            action = Vehicle::CRASH;
                            direction = Vehicle::RIGHT;

                            player6.draw(c, r, action, direction, currentMap->getElevation(player6.getPosY()), terrain);
                        }
                    }

                    for (TrafficCar &v : cars)
                        v.autoControl(c, player6.getPosX(), player6.getPosY());
            }
            if (!finalGame && !arrival){
                // Check if enemies are displayed on the screen
                for (RivalCar &v : rivals) {
                    float distX, distY;

                    bool visible = true;

                    visible = v.isVisible(c, currentMap->getCameraPosY(), player5.getPosX(), player5.getPosY(), distX, distY);

                    if (visible) {
                        if (distY <= 40.f && distX <= 1.2f) {
                            // Thread with sound of the woman
                            elapsed8 = trafficCarSound.getElapsedTime().asSeconds();
                            if (elapsed8 - elapsed7 >= traffic_delay.asSeconds()) {
                                // makeCarTrafficSound
                                r.soundEffects[124]->stop();
                                r.soundEffects[124]->play();
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
            break;
        case 4:
            currentMap->updateCamera(player5.getPosX(), player5.getPosY() - RECTANGLE);
            break;
        case 5:
            currentMap->updateCamera(player6.getPosX(), player6.getPosY() - RECTANGLE);
    }

    // Out Run and Driving Fury and Demarrage modes
    if (currentMap->isOutSideLandScape()) {

        if (typeOfGame != 1){
            // Increment the landscape
            currentLandScape++;
        }

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
                    break;
                case 4:
                    player5.setPosition(player5.getPosX() + currentMap->getOffsetX(), player5.getPosY() - currentMap->getMaxY());
                    break;
                case 5:
                    player6.setPosition(player6.getPosX() + currentMap->getOffsetX(), player6.getPosY() - currentMap->getMaxY());
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
                    break;
                case 4:
                    currentMap->updateCamera(player5.getPosX(), player5.getPosY() - RECTANGLE);
                    break;
                case 5:
                    currentMap->updateCamera(player6.getPosX(), player6.getPosY() - RECTANGLE);
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
        if (typeOfGame == 1){
            arrival = true;
        }
        else {
            finalGame = true;
        }
        mtx.unlock();
    }
    if (typeOfGame == 4 && !updatedGoalCar && !updatedPlayerCar && distanceGoalCar < 0)
    {
        // Check the distance
        if (abs(distanceGoalCar) >= distanceAdvanced){
            mtx.lock();
            arrival = true;
            mtx.unlock();
        }
    }
    if (!finalGame && !arrival) {

        // Update and prepare cars to draw
        if (lastY <= currentMap->getCameraPosY() + float(c.renderLen)){
            lastY = currentMap->getCameraPosY() + float(c.renderLen);
        }

        if (typeOfGame == 4 && currentLandScape >= goalCarStage){
            Vehicle::Action a;

            float positionX = player6.getPosX();
            float positionY = player6.getPosY();
            float speedPlayer = player6.getSpeed();

            float directionCurve = currentMap->getCurveCoefficient(goalCar.getPosY());

            bool vehicleDetected = false;

            if (typeOfGame == 4){
                float goalCarCordX = goalCar.getPosX();

                // Check if the rival car
                for (int i = 0; !vehicleDetected && i < (int)cars.size(); i++){
                    float cordX = cars[i].getPosX();
                    // Check if the vehicle is near or not
                    if (abs(goalCarCordX - cordX) <= 0.3f &&
                        abs(goalCar.getPosY() - cars[i].getPosY()) <= 20.f)
                    {
                        vehicleDetected = true;
                    }
                }
            }

            goalCar.updateModeB(c, lastY, lastY + float(c.renderLen) / DENSITY_SPACE, c.maxAggressiveness, a,
                                directionCurve, c.level, positionX, positionY, speedPlayer, vehicleDetected);

            // Get the new position of the vehicle
            float posY = goalCar.getPosY();

            // Check if the vehicle is or not in a curve
            if (directionCurve != 0.f){
                // Check if the vehicle has finished the curve
                if (currentMap->getCurveCoefficient(posY)){
                    // Vehicle goes straight on
                    goalCar.setOnStraight();
                }
            }

            // Draw the vehicle
            goalCar.draw(a, currentMap->getElevation(posY));
            vehicleCrash = false;
            float crashPos;

            // Check if the player has crash with any rival car
            switch(typeOfVehicle){
                case 0:

                    vehicleCrash = goalCar.hasCrashed(player.getPosY(), player.getPreviousY(),
                                                player.getMinScreenX(), player.getMaxScreenX(), crashPos);

                    // Check it has been crash between player and rival
                    if (vehicleCrash){
                        if (player.getPreviousX() > goalCar.getPreviousX()){
                            player.setPosition(player.getPosX() + 0.3f, player.getPosY() - 20.f);
                        }
                        else if (player.getPreviousX() < goalCar.getPreviousX()){
                            player.setPosition(player.getPosX() - 0.3f, player.getPosY() - 20.f);
                        }
                        else {
                            player.setPosition(player.getPosX(), player.getPosY() - 20.f);
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
                    vehicleCrash = goalCar.hasCrashed(player2.getPosY(), player2.getPreviousY(),
                                                player2.getMinScreenX(), player2.getMaxScreenX(), crashPos);

                    if (vehicleCrash){
                        if (player2.getPreviousX() > goalCar.getPreviousX()){
                            player2.setPosition(player2.getPosX() + 0.3f, player2.getPosY() - 20.f);
                        }
                        else if (player.getPreviousX() < goalCar.getPreviousX()){
                            player2.setPosition(player2.getPosX() - 0.3f, player2.getPosY() - 20.f);
                        }
                        else {
                            player2.setPosition(player2.getPosX(), player2.getPosY() - 20.f);
                        }
                        r.soundEffects[87]->stop();
                        r.soundEffects[87]->play();
                    }
                    break;
                case 2:
                    vehicleCrash = goalCar.hasCrashed(player3.getPosY(), player3.getPreviousY(),
                                                player3.getMinScreenX(), player3.getMaxScreenX(), crashPos);

                    if (vehicleCrash){
                        if (player3.getPreviousX() > goalCar.getPreviousX()){
                            player3.setPosition(player3.getPosX() + 0.3f, player3.getPosY() - 20.f);
                        }
                        else if (player.getPreviousX() < goalCar.getPreviousX()){
                            player3.setPosition(player3.getPosX() - 0.3f, player3.getPosY() - 20.f);
                        }
                        else {
                            player3.setPosition(player3.getPosX(), player3.getPosY() - 20.f);
                        }
                        r.soundEffects[87]->stop();
                        r.soundEffects[87]->play();
                    }
                    break;
                case 3:
                    vehicleCrash = goalCar.hasCrashed(player4.getPosY(), player4.getPreviousY(),
                                                player4.getMinScreenX(), player4.getMaxScreenX(), crashPos);

                    if (vehicleCrash){
                        if (player4.getPreviousX() > goalCar.getPreviousX()){
                            player4.setPosition(player4.getPosX() + 0.3f, player4.getPosY() - 10.f);
                        }
                        else if (player.getPreviousX() < goalCar.getPreviousX()){
                            player4.setPosition(player4.getPosX() - 0.3f, player4.getPosY() - 10.f);
                        }
                        else {
                            player4.setPosition(player4.getPosX(), player4.getPosY() - 10.f);
                        }
                        r.soundEffects[87]->stop();
                        r.soundEffects[87]->play();
                    }
                    break;
                case 4:
                    vehicleCrash = goalCar.hasCrashed(player5.getPosY(), player5.getPreviousY(),
                                                player5.getMinScreenX(), player5.getMaxScreenX(), crashPos);

                    if (vehicleCrash){
                        if (player5.getPreviousX() > goalCar.getPreviousX()){
                            player2.setPosition(player5.getPosX() + 0.3f, player5.getPosY() - 20.f);
                        }
                        else if (player5.getPreviousX() < goalCar.getPreviousX()){
                            player5.setPosition(player5.getPosX() - 0.3f, player5.getPosY() - 20.f);
                        }
                        else {
                            player5.setPosition(player5.getPosX(), player5.getPosY() - 20.f);
                        }
                        r.soundEffects[87]->stop();
                        r.soundEffects[87]->play();
                    }
                    break;
                case 5:
                    vehicleCrash = goalCar.hasCrashed(player6.getPosY(), player6.getPreviousY(),
                                                player6.getMinScreenX(), player6.getMaxScreenX(), crashPos);

                    if (vehicleCrash){
                        if (player6.getPreviousX() > goalCar.getPreviousX()){
                            player6.setPosition(player6.getPosX() + 0.3f, player6.getPosY() - 20.f);
                        }
                        else if (player.getPreviousX() < goalCar.getPreviousX()){
                            player6.setPosition(player6.getPosX() - 0.3f, player6.getPosY() - 20.f);
                        }
                        else {
                            player6.setPosition(player6.getPosX(), player6.getPosY() - 20.f);
                        }
                        r.soundEffects[87]->stop();
                        r.soundEffects[87]->play();
                    }
            }
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

        if (currentMap->inFork(goalCar.getPosY())) {
            if (!updatedGoalCar){
                goalCar.setPosition(goalCar.getPosX(), -2.f * DEL_DISTANCE * 3.0f);
                updatedGoalCar = true;
            }
        }
        else {
            if (updatedPlayerCar){
                updatedGoalCar = false;
            }
        }

        // Draw map with cars
        c.w.clear();
        currentMap->drawLandScape(c, cars, rivals, typeOfGame, goalCar, displayGoalCarIndicator, (currentLandScape >= goalCarStage));

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

                if (currentLandScape >= goalCarStage){
                    distanceGoalCar = goalCar.getPosY() - player.getPosY();
                }
                else {
                    distanceGoalCar = maxDistance;
                }

                if (currentLandScape >= goalCarStage && currentMap->inFork(player.getPosY())){
                    if (!updatedPlayerCar){
                        updatedPlayerCar = true;
                    }
                }
                else {
                    updatedPlayerCar = false;
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

                if (currentLandScape >= goalCarStage){
                    distanceGoalCar = goalCar.getPosY() - player2.getPosY();
                }
                else {
                    distanceGoalCar = maxDistance;
                }

                if (currentLandScape >= goalCarStage && currentMap->inFork(player2.getPosY())){
                    if (!updatedPlayerCar){
                        updatedPlayerCar = true;
                    }
                }
                else {
                    updatedPlayerCar = false;
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

                if (currentLandScape >= goalCarStage){
                    distanceGoalCar = goalCar.getPosY() - player3.getPosY();
                }
                else {
                    distanceGoalCar = maxDistance;
                }

                if (currentLandScape >= goalCarStage && currentMap->inFork(player3.getPosY())){
                    if (!updatedPlayerCar){
                        updatedPlayerCar = true;
                    }
                }
                else {
                    updatedPlayerCar = false;
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

                if (currentLandScape >= goalCarStage){
                    distanceGoalCar = goalCar.getPosY() - player4.getPosY();
                }
                else {
                    distanceGoalCar = maxDistance;
                }

                if (currentLandScape >= goalCarStage && currentMap->inFork(player4.getPosY())){
                    if (!updatedPlayerCar){
                        updatedPlayerCar = true;
                    }
                }
                else {
                    updatedPlayerCar = false;
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
                break;
            case 4:
                if (!player5.isCrashing()) { // If not has crashed
                    action = player5.accelerationControl(c, currentMap->isOutSideRoad(player5.getPosX(), player5.getPosY()));
                    direction = player5.rotationControl(c, currentMap->getCurveCoefficient(player5.getPosY()),
                                                           currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                }
                else {
                    player5.hitControl(vehicleCrash);
                }

                if (currentLandScape >= goalCarStage){
                    distanceGoalCar = goalCar.getPosY() - player5.getPosY();
                }
                else {
                    distanceGoalCar = maxDistance;
                }

                if (currentLandScape >= goalCarStage && currentMap->inFork(player5.getPosY())){
                    if (!updatedPlayerCar){
                        updatedPlayerCar = true;
                    }
                }
                else {
                    updatedPlayerCar = false;
                }

                player5.draw(c, r, action, direction, currentMap->getElevation(player5.getPosY()), terrain);

                if (!player5.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player5.getPreviousY(), player5.getPosY(), player5.getPosX(),
                                                        player5.getMinScreenX(), player5.getMaxScreenX(), crashPos, typeOfGame);
                    if (!crash)
                        for (int i = 0; !vehicleCrash && i < (int)cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player5.getPreviousY(), player5.getPosY(),
                                                              player5.getMinScreenX(), player5.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        player5.setPosition(player5.getPosX(), crashPos);
                        player5.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player5.draw(c, r, action, direction, currentMap->getElevation(player5.getPosY()), terrain);
                    }
                }
                for (TrafficCar &v : cars)
                    v.autoControl(c, player5.getPosX(), player5.getPosY());
                break;
            case 5:
                if (!player6.isCrashing()) { // If not has crashed
                    action = player6.accelerationControl(c, currentMap->isOutSideRoad(player6.getPosX(), player6.getPosY()));
                    direction = player6.rotationControl(c, currentMap->getCurveCoefficient(player6.getPosY()),
                                                           currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                }
                else {
                    player6.hitControl(vehicleCrash);
                }

                if (currentLandScape >= goalCarStage){
                    distanceGoalCar = goalCar.getPosY() - player6.getPosY();
                }
                else {
                    distanceGoalCar = maxDistance;
                }

                if (currentLandScape >= goalCarStage && currentMap->inFork(player6.getPosY())){
                    if (!updatedPlayerCar){
                        updatedPlayerCar = true;
                    }
                }
                else {
                    updatedPlayerCar = false;
                }

                player6.draw(c, r, action, direction, currentMap->getElevation(player6.getPosY()), terrain);

                if (!player6.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player6.getPreviousY(), player6.getPosY(), player6.getPosX(),
                                                        player6.getMinScreenX(), player6.getMaxScreenX(), crashPos, typeOfGame);
                    if (!crash)
                        for (int i = 0; !vehicleCrash && i < (int)cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player6.getPreviousY(), player6.getPosY(),
                                                              player6.getMinScreenX(), player6.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        player6.setModeCollision();
                        player6.setPosition(player6.getPosX(), crashPos);
                        player6.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player6.draw(c, r, action, direction, currentMap->getElevation(player6.getPosY()), terrain);
                    }
                }
                for (TrafficCar &v : cars)
                    v.autoControl(c, player6.getPosX(), player6.getPosY());
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
                        break;
                    case 4:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player5.getPosX(), player5.getPosY(), distX, distY);
                        break;
                    case 5:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player6.getPosX(), player6.getPosY(), distX, distY);
                        break;
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
            break;
        case 4:
            currentMap->updateCamera(player5.getPosX(), player5.getPosY() - RECTANGLE);
            break;
        case 5:
            currentMap->updateCamera(player6.getPosX(), player6.getPosY() - RECTANGLE);
    }

    // Out Run and Driving Fury and Demarrage modes
    if (currentMap->isOutSideLandScape()) {

        // Increment the landscape
        currentLandScape++;

        if (currentMap->getNextLeft() != nullptr) {

            updatedGoalCar = false;

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
                    break;
                case 4:
                    player5.setPosition(player5.getPosX() + currentMap->getOffsetX(), player5.getPosY() - currentMap->getMaxY());
                    break;
                case 5:
                    player6.setPosition(player6.getPosX() + currentMap->getOffsetX(), player6.getPosY() - currentMap->getMaxY());
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

            currentMap->updateCamera(player6.getPosX(), player6.getPosY() - RECTANGLE);

            lastY = currentMap->getCameraPosY();
        }
        else {
            finalGame = true;
        }
    }
    if (lifeGoalCar <= 0){
        // Criminal goal car has been defeated
        mtx.lock();
        arrival = true;
        mtx.unlock();
    }
    if (currentMap->isFinalLandScape()) {
        State status = showsGoalAnimation(c, r);
        if (status == EXIT) {
            exit(1);
        }
        mtx.lock();
        finalGame = true;
        mtx.unlock();
    }
    if (!finalGame && !arrival) {
        // Control if the car is the player is inside the fork

        if (lastY <= currentMap->getCameraPosY() + float(c.renderLen)){
            lastY = currentMap->getCameraPosY() + float(c.renderLen);
        }

        if (currentLandScape >= goalCarStage){
            Vehicle::Action a;

            float positionX, positionY, speedPlayer;

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
                    break;
                case 4:
                    positionX = player5.getPosX();
                    positionY = player5.getPosY();
                    speedPlayer = player5.getSpeed();
                    break;
                case 5:
                    positionX = player6.getPosX();
                    positionY = player6.getPosY();
                    speedPlayer = player6.getSpeed();
            }


            float directionCurve = currentMap->getCurveCoefficient(goalCar.getPosY());

            float goalCarCordX = goalCar.getPosX();
            bool vehicleDetected = false;

            // Check if the rival car
            for (int i = 0; !vehicleDetected && i < (int)cars.size(); i++){
                float cordX = cars[i].getPosX();
                // Check if the vehicle is near or not
                if (abs(goalCarCordX - cordX) <= 0.3f &&
                    abs(goalCar.getPosY() - cars[i].getPosY()) <= 20.f)
                {
                    vehicleDetected = true;
                }
            }

            goalCar.updateModeB(c, lastY, lastY + float(c.renderLen) / DENSITY_SPACE, c.maxAggressiveness, a,
                                directionCurve, c.level, positionX, positionY, speedPlayer, vehicleDetected);

            // Get the new position of the vehicle
            float posY = goalCar.getPosY();

            // Check if the vehicle is or not in a curve
            if (directionCurve != 0.f){
                // Check if the vehicle has finished the curve
                if (currentMap->getCurveCoefficient(posY)){
                    // Vehicle goes straight on
                    goalCar.setOnStraight();
                }
            }

            // Draw the vehicle
            goalCar.draw(a, currentMap->getElevation(posY));
            vehicleCrash = false;
            float crashPos;

            switch(typeOfVehicle){
                case 0:
                    // Check if the player has crash with any rival car
                    vehicleCrash = goalCar.hasCrashed(player.getPosY(), player.getPreviousY(),
                                              player.getMinScreenX(), player.getMaxScreenX(), crashPos);
                    break;
                case 1:
                   // Check if the player has crash with any rival car
                    vehicleCrash = goalCar.hasCrashed(player2.getPosY(), player2.getPreviousY(),
                                              player2.getMinScreenX(), player2.getMaxScreenX(), crashPos);
                    break;
                case 2:
                    // Check if the player has crash with any rival car
                    vehicleCrash = goalCar.hasCrashed(player3.getPosY(), player3.getPreviousY(),
                                              player3.getMinScreenX(), player3.getMaxScreenX(), crashPos);
                    break;
                case 3:
                    // Check if the player has crash with any rival car
                    vehicleCrash = goalCar.hasCrashed(player4.getPosY(), player4.getPreviousY(),
                                              player4.getMinScreenX(), player4.getMaxScreenX(), crashPos);
                    break;
                case 4:
                    // Check if the player has crash with any rival car
                    vehicleCrash = goalCar.hasCrashed(player5.getPosY(), player5.getPreviousY(),
                                              player5.getMinScreenX(), player5.getMaxScreenX(), crashPos);
                    break;
                case 5:
                    // Check if the player has crash with any rival car
                    vehicleCrash = goalCar.hasCrashed(player6.getPosY(), player6.getPreviousY(),
                                              player6.getMinScreenX(), player6.getMaxScreenX(), crashPos);
            }

            // Check it has been crash between player and rival
            if (vehicleCrash){

                r.soundEffects[87]->stop();
                r.soundEffects[87]->play();

                switch(typeOfVehicle){
                    case 0:
                        if (player.getPreviousX() >= goalCar.getPreviousX()){
                            player.setPosition(player.getPosX() + 0.3f, player.getPosY() - 20.f);
                        }
                        else if (player.getPreviousX() < goalCar.getPreviousX()){
                            player.setPosition(player.getPosX() - 0.3f, player.getPosY() - 20.f);
                        }
                        else {
                            player.setPosition(player.getPosX(), player.getPosY() - 20.f);
                        }
                        break;
                    case 1:
                        if (player2.getPreviousX() >= goalCar.getPreviousX()){
                            player2.setPosition(player2.getPosX() + 0.3f, player2.getPosY() - 20.f);
                        }
                        else if (player2.getPreviousX() < goalCar.getPreviousX()){
                            player2.setPosition(player2.getPosX() - 0.3f, player2.getPosY() - 20.f);
                        }
                        else {
                            player2.setPosition(player2.getPosX(), player2.getPosY() - 20.f);
                        }
                        break;
                    case 2:
                        if (player3.getPreviousX() >= goalCar.getPreviousX()){
                            player3.setPosition(player3.getPosX() + 0.3f, player3.getPosY() - 20.f);
                        }
                        else if (player3.getPreviousX() < goalCar.getPreviousX()){
                            player3.setPosition(player3.getPosX() - 0.3f, player3.getPosY() - 20.f);
                        }
                        else {
                            player3.setPosition(player3.getPosX(), player3.getPosY() - 20.f);
                        }
                        break;
                    case 3:
                        if (player4.getPreviousX() >= goalCar.getPreviousX()){
                            player4.setPosition(player4.getPosX() + 0.3f, player4.getPosY() - 20.f);
                        }
                        else if (player4.getPreviousX() < goalCar.getPreviousX()){
                            player4.setPosition(player4.getPosX() - 0.3f, player4.getPosY() - 20.f);
                        }
                        else {
                            player4.setPosition(player4.getPosX(), player4.getPosY() - 20.f);
                        }
                        break;
                    case 4:
                        if (player5.getPreviousX() >= goalCar.getPreviousX()){
                            player5.setPosition(player5.getPosX() + 0.3f, player5.getPosY() - 20.f);
                        }
                        else if (player6.getPreviousX() < goalCar.getPreviousX()){
                            player5.setPosition(player5.getPosX() - 0.3f, player5.getPosY() - 20.f);
                        }
                        else {
                            player5.setPosition(player5.getPosX(), player5.getPosY() - 20.f);
                        }
                        break;
                    case 5:
                        if (player6.getPreviousX() >= goalCar.getPreviousX()){
                            player6.setPosition(player6.getPosX() + 0.3f, player6.getPosY() - 20.f);
                        }
                        else if (player6.getPreviousX() < goalCar.getPreviousX()){
                            player6.setPosition(player6.getPosX() - 0.3f, player6.getPosY() - 20.f);
                        }
                        else {
                            player6.setPosition(player6.getPosX(), player6.getPosY() - 20.f);
                        }
                }

                // Reduce the life of the goal car
                if (goalCar.getVehicleType() == 3){
                    // Reduce life per impact
                    lifeGoalCar -= lifeLostPerCrash;
                }
                else {
                    // Reduce the half of life per impact
                    lifeGoalCar -= (lifeLostPerCrash / 2);
                }

                elapsed18 = policeDriverClock.getElapsedTime().asSeconds();

                if (elapsed18 - elapsed17 >= police_driver_delay.asSeconds()){
                    r.soundEffects[101]->stop();
                    r.soundEffects[102]->stop();
                    r.soundEffects[103]->stop();
                    r.soundEffects[104]->stop();
                    r.soundEffects[rand_generator_int(101, 104)]->play();

                    policeDriverClock.restart();
                }
            }

            // Check if the fire has to be drawn or not
            if (lifeGoalCar <= 50 && lifeGoalCar >= 25){
                // The goalCar starts to smoke
                goalCar.setFiringSmoke(true);
            }
            else if (lifeGoalCar < 25){
                // The goalCar starts to smoke
                goalCar.setFiringSmoke(false);

                // The goalCar starts to fire
                goalCar.setFiring(true);
            }
        }

        // Update all the traffic vehicles
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

        if (currentMap->inFork(goalCar.getPosY())) {
            if (!updatedGoalCar){
                goalCar.setPosition(goalCar.getPosX(), -2.f * DEL_DISTANCE * 3.0f);
                updatedGoalCar = true;
            }
        }
        else {
            if (updatedPlayerCar){
                updatedGoalCar = false;
            }
        }

        // Draw map with cars
        c.w.clear();
        currentMap->drawLandScape(c, cars, rivals, typeOfGame, goalCar, displayGoalCarIndicator, currentLandScape >= goalCarStage);

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

                if (currentLandScape >= goalCarStage && currentMap->inFork(player.getPosY())){
                    if (!updatedPlayerCar){
                        updatedPlayerCar = true;
                    }
                }
                else {
                    updatedPlayerCar = false;
                }

                if (currentLandScape >= goalCarStage){
                    distanceGoalCar = goalCar.getPosY() - player.getPosY();
                    if (distanceGoalCar < 0){
                        distanceGoalCar = 0;
                    }
                }
                else {
                    distanceGoalCar = maxDistance;
                }

                player.draw(c, r, action, direction, currentMap->getElevation(player.getPosY()), terrain);

                if (!player.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player.getPreviousY(), player.getPosY(), player.getPosX(),
                                                        player.getMinScreenX(), player.getMaxScreenX(), crashPos, typeOfGame);
                    if (!crash && typeOfGame != 2)
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

                if (currentLandScape >= goalCarStage && currentMap->inFork(player2.getPosY())){
                    if (!updatedPlayerCar){
                        updatedPlayerCar = true;
                    }
                }
                else {
                    updatedPlayerCar = false;
                }

                if (currentLandScape >= goalCarStage){
                    distanceGoalCar = goalCar.getPosY() - player2.getPosY();
                    if (distanceGoalCar < 0){
                        distanceGoalCar = 0;
                    }
                }
                else {
                    distanceGoalCar = maxDistance;
                }

                player2.draw(c, r, action, direction, currentMap->getElevation(player2.getPosY()), terrain);

                if (!player2.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player2.getPreviousY(), player2.getPosY(), player2.getPosX(),
                                                        player2.getMinScreenX(), player2.getMaxScreenX(), crashPos, typeOfGame);
                    if (!crash && typeOfGame != 2)
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

                if (currentLandScape >= goalCarStage && currentMap->inFork(player3.getPosY())){
                    if (!updatedPlayerCar){
                        updatedPlayerCar = true;
                    }
                }
                else {
                    updatedPlayerCar = false;
                }

                if (currentLandScape >= goalCarStage){
                    distanceGoalCar = goalCar.getPosY() - player3.getPosY();
                    if (distanceGoalCar < 0){
                        distanceGoalCar = 0;
                    }
                }
                else {
                    distanceGoalCar = maxDistance;
                }

                player3.draw(c, r, action, direction, currentMap->getElevation(player3.getPosY()), terrain);

                if (!player3.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player3.getPreviousY(), player3.getPosY(), player3.getPosX(),
                                                        player3.getMinScreenX(), player3.getMaxScreenX(), crashPos, typeOfGame);
                    if (!crash && typeOfGame != 2)
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

                if (currentLandScape >= goalCarStage && currentMap->inFork(player4.getPosY())){
                    if (!updatedPlayerCar){
                        updatedPlayerCar = true;
                    }
                }
                else {
                    updatedPlayerCar = false;
                }

                if (currentLandScape >= goalCarStage){
                    distanceGoalCar = goalCar.getPosY() - player4.getPosY();
                    if (distanceGoalCar < 0){
                        distanceGoalCar = 0;
                    }
                }
                else {
                    distanceGoalCar = maxDistance;
                }

                player4.draw(c, r, action, direction, currentMap->getElevation(player4.getPosY()), terrain);

                if (!player4.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player4.getPreviousY(), player4.getPosY(), player4.getPosX(),
                                                        player4.getMinScreenX(), player4.getMaxScreenX(), crashPos, typeOfGame);
                    if (!crash && typeOfGame != 2)
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
                break;
            case 4:
                if (!player5.isCrashing()) { // If not has crashed
                    action = player5.accelerationControl(c, currentMap->isOutSideRoad(player5.getPosX(), player5.getPosY()));
                    direction = player5.rotationControl(c, currentMap->getCurveCoefficient(player5.getPosY()),
                                                           currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                }
                else {
                    player5.hitControl(vehicleCrash);
                }

                if (currentLandScape >= goalCarStage && currentMap->inFork(player5.getPosY())){
                    if (!updatedPlayerCar){
                        updatedPlayerCar = true;
                    }
                }
                else {
                    updatedPlayerCar = false;
                }

                if (currentLandScape >= goalCarStage){
                    distanceGoalCar = goalCar.getPosY() - player5.getPosY();
                    if (distanceGoalCar < 0){
                        distanceGoalCar = 0;
                    }
                }
                else {
                    distanceGoalCar = maxDistance;
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
                        player5.setPosition(player5.getPosX(), crashPos);
                        player5.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player5.draw(c, r, action, direction, currentMap->getElevation(player5.getPosY()), terrain);
                    }
                }
                break;
            case 5:
                if (!player6.isCrashing()) { // If not has crashed
                    action = player6.accelerationControl(c, currentMap->isOutSideRoad(player6.getPosX(), player6.getPosY()));
                    direction = player6.rotationControl(c, currentMap->getCurveCoefficient(player6.getPosY()),
                                                           currentMap->getNextLeft()->isFinalLandScape(), currentMap->getMaxY());
                }
                else {
                    player6.hitControl(vehicleCrash);
                }

                if (currentLandScape >= goalCarStage && currentMap->inFork(player6.getPosY())){
                    if (!updatedPlayerCar){
                        updatedPlayerCar = true;
                    }
                }
                else {
                    updatedPlayerCar = false;
                }

                if (currentLandScape >= goalCarStage){
                    distanceGoalCar = goalCar.getPosY() - player6.getPosY();
                    if (distanceGoalCar < 0){
                        distanceGoalCar = 0;
                    }
                }
                else {
                    distanceGoalCar = maxDistance;
                }

                player6.draw(c, r, action, direction, currentMap->getElevation(player6.getPosY()), terrain);

                if (!player6.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player6.getPreviousY(), player6.getPosY(), player6.getPosX(),
                                                        player6.getMinScreenX(), player6.getMaxScreenX(), crashPos, typeOfGame);
                    if (!crash && typeOfGame != 2)
                        for (int i = 0; !vehicleCrash && i < (int)cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player6.getPreviousY(), player6.getPosY(),
                                                              player6.getMinScreenX(), player6.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        player6.setModeCollision();
                        player6.setPosition(player6.getPosX(), crashPos);
                        player6.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player6.draw(c, r, action, direction, currentMap->getElevation(player6.getPosY()), terrain);
                    }
                }
        }

        for (TrafficCar &v : cars)
            v.autoControl(c, player6.getPosX(), player6.getPosY());


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
                        break;
                    case 5:
                        visible = v.isVisible(c, currentMap->getCameraPosY(), player6.getPosX(), player6.getPosY(), distX, distY);
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
                                heightButton = 40.0f * c.screenScale;

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
    if (typeOfGame < 3 || typeOfGame > 4){
        currentMap->drawLandScape(c, cars, rivals, typeOfGame, goalCar, displayGoalCarIndicator, false);
    }
    else {
        currentMap->drawLandScape(c, cars, rivals, typeOfGame, goalCar, displayGoalCarIndicator, (currentLandScape >= goalCarStage));
    }

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
            break;
        case 5:
            player6.draw(c, r, a, d, currentMap->getElevation(player6.getPosY()), terrain, false);
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
        if (typeOfGame == 1){
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
                          200.0f * c.screenScale, 40.0f * c.screenScale, c.fontMenuPauseButtons, c.pauseMenuButtons[0].getTextButton(),
                          c.pauseMenuButtons[0].getIdleColorButton(), c.pauseMenuButtons[0].getHoverColorButton(),
                          c.pauseMenuButtons[0].getFontColorButton(), 1, c.screenScale);

        c.pauseMenuButtons[0] = b;

        for (int i = 1; i < int(c.pauseMenuButtons.size()); i++){
            // Change the state of the first color
            Button b = Button(c.w.getSize().x / 2.f - 95.0f * c.screenScale, c.w.getSize().y / 2.f - (70.0f - i * 70.f) * c.screenScale,
                              200.0f * c.screenScale, 40.0f * c.screenScale, c.fontMenuPauseButtons, c.pauseMenuButtons[i].getTextButton(),
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
        if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Down)) {
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
        else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Up)) {
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
        else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
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
            if (typeOfGame == 2 && newLap){
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
            comeFromOptions = false;
            r.soundTracks[0]->play();
            return START;
        default:
            sleep(r.soundEffects[1]->getDuration());
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



void Game::controlVehicleOwner(bool& cancelledGroup){

    // Create a Linda driver compatible with Windows to make communicate with the Linda server
    LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");

    // Control the group is not canceled
    bool canceled, stopped = false;;

    mtx3.lock();
    canceled = cancelledGroup;
    mtx3.unlock();

    // While not canceled
    while (!canceled && !stopped){
        // Wait the tuple of canceled
        Tuple t = Tuple("?A", nickNameGroupMultiplayer, "?B", "?C", nickNameMultiplayer);
        Tuple r = winLindadriver.removeNote(t);
        if (r.get(1) == "VEHICLE_CLOSED"){
            stopped = true;
        }
        else if (r.get(1) == "CANCEL_CAR"){
            winLindadriver.postNote(r);
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        else if (r.get(1) == "VEHICLE_DONE"){
            stopped = true;
        }
        else if (r.get(1) == "LEAVE_GROUP"){
            mtx3.lock();
            int i = stoi(r.get(3));

            // The petition is received
            for (int j = i; j < (int)groupDataPlayers.size(); j++){
                groupDataPlayers[j].codePlayer--;
            }

            groupDataPlayers.erase(groupDataPlayers.begin() + i - 1);
            numberPlayersGroup--;
            mtx3.unlock();

            if (numberPlayersGroup == 1){
                canceled = true;
            }
            else {
                // Alert to the rest of the members that this member must be deleted
                for (int i = 2; i <= numberPlayersGroup; i++){

                    int idCode = groupDataPlayers[i - 1].getCodePlayer();
                    string namePlayer = groupDataPlayers[i - 1].getNickNamePlayer();

                    // Inform that the group is cancelled
                    Tuple t = Tuple("DELETE_PLAYER", nickNameGroupMultiplayer, to_string(i), namePlayer, nickNameMultiplayer);
                    winLindadriver.postNote(t);
                }
            }
        }
        mtx3.lock();
        cancelledGroup = canceled;
        mtx3.unlock();
    }
}


void Game::controlVehicleGuest(bool& cancelledVehicle){

    // Create a Linda driver compatible with Windows to make communicate with the Linda server
    LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");

    // Control the group is not canceled
    bool canceled, stopped = false;;

    mtx3.lock();
    canceled = cancelledVehicle;
    mtx3.unlock();

    while (!canceled && !stopped){
        Tuple t = Tuple("?A", nickNameGroupMultiplayer, "?B", nickNameMultiplayer, "?C");
        Tuple r = winLindadriver.removeNote(t);
        if (r.get(1) == "PLAYER_CLOSED"){
            canceled = true;
        }
        else if (r.get(1) == "CANCEL_CAR"){
            canceled = true;
        }
        else if (r.get(1) == "VEHICLE_DONE"){
            stopped = true;
        }
        else if (r.get(1) == "DELETE_PLAYER") {

            mtx3.lock();
            int i = stoi(r.get(3));

            // The petition is received
            for (int j = i; j < (int)groupDataPlayers.size(); j++){
                groupDataPlayers[j].codePlayer--;
            }

            // Decrement our id
            if (i < codePlayerInGroup){
                codePlayerInGroup--;
            }

            groupDataPlayers.erase(groupDataPlayers.begin() + i - 1);
            numberPlayersGroup--;
            mtx3.unlock();
        }

        mtx3.lock();
        cancelledVehicle = canceled;
        mtx3.unlock();
    }
}



void Game::storeRivalPlayers(int& numPlayers, bool& finishedRegister, bool& cancelledGroup){

    // Local variables to store the information
    bool finished = false, cancelled = false;
    int playersRegistered = 1, totalPlayers;

    // Tuple with the car selection information
    Tuple t = Tuple("VEHICLE_SELECTED", nickNameGroupMultiplayer, to_string(codePlayerInGroup), nickNameMultiplayer,
                        to_string(typeOfVehicle), to_string(colorCarSelected));

    // Create a Linda driver compatible with Windows to make communicate with the Linda server
    LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");


    mtx3.lock();
    totalPlayers = groupDataPlayers.size();
    mtx3.unlock();

    // Send to all the rivals the vehicle that i have chosen
    for (int i = 1; i <= totalPlayers; i++){
        // Postnote the tuple with the car selected for each player
        if (i != codePlayerInGroup){
            winLindadriver.postNote(t);
        }
    }

    // Wait until the rest of players have sent their vehicles
    mtx3.lock();
    totalPlayers = groupDataPlayers.size();
    cancelled = cancelledGroup;
    mtx3.unlock();

    bool found;

    while (!cancelled && playersRegistered != totalPlayers){
        // Check if any of the players has sent his vehicle
        for (int i = 1; i <= totalPlayers; i++){
            if (i != codePlayerInGroup){
                Tuple t = Tuple("VEHICLE_SELECTED", nickNameGroupMultiplayer, to_string(i), "?A", "?B", "?C");
                Tuple r = winLindadriver.readNoteX(t, found);

                // Check if the tuple has been found
                if (found && r.get(1) != NF){
                    // Increment the number of players registered and store the car with the color
                    mtx3.lock();
                    numPlayers++;
                    groupDataPlayers[i].setVehicleType(stoi(r.get(5)));
                    groupDataPlayers[i].setColorVehicle(stoi(r.get(6)));
                    playersRegistered = numPlayers;
                    mtx3.unlock();
                }
            }
            // Check the values again if the
            mtx3.lock();
            totalPlayers = groupDataPlayers.size();
            cancelled = cancelledGroup;
            mtx3.unlock();
        }
        // All the cars are stored
    }
    winLindadriver.stop();
    mtx3.lock();
    finishedRegister = true;
    cancelled = cancelledGroup;
    mtx3.unlock();
}




/**
 * Load the configuration of the vehicle selection menu in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
State Game::selectionVehicleMenu(Configuration& c, SoundPlayer& r){

    if (onMultiplayer){
        r.soundTracks[18]->stop();
    }

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
    Texture vehicleTextures[6][8];

    string path = "", imageCode = "";

    // Array of the vehicle's names
    string vehicleNames[6][8];

    // Array of the  motor types of the vehicles
    string motorNames[6][8];

    // Array of the  maximum speed of the vehicles
    float speedVehicles[6][8];

    // Array of the angle of the vehicles
    float angleVehicles[6][8];

    // Vector with the current color selected for each car
    int colorCars[6];

    for (int i = 0; i < 6; i++){
        colorCars[i] = 0;
    }

    // Variables to store the vehicle properties
    string brandName, motorName, pathFile;
    float max_speed, angleVehicle;

    for (int i = 0; i < 6; i++){
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
        else if (i == 3){
            path = "Data/Vehicles/Trucks/Truck";
            imageCode = "c75.png";
        }
        else if (i == 4) {
            path = "Data/Vehicles/FormulaOnes/FormulaOne";
            imageCode = "c58.png";
        }
        else {
            path = "Data/Vehicles/Police";
            imageCode = "c46.png";
        }
        for (int j = 0; j < 8; j++){
            if (i == 5){
                if (j == 0){
                    t.loadFromFile(path + "/Images/" + imageCode);
                    vehicleTextures[i][j] = t;
                    loadVehicleProperties(path + "/Configuration/Configuration.xml", brandName, max_speed, angleVehicle, motorName);
                    vehicleNames[i][j] = brandName;
                    motorNames[i][j] = motorName;
                    angleVehicles[i][j] = angleVehicle;
                    speedVehicles[i][j] = max_speed;
                }
            }
            else {
                t.loadFromFile(path + to_string(j + 1) + "/Images/" + imageCode);
                vehicleTextures[i][j] = t;
                loadVehicleProperties(path + to_string(j + 1) + "/Configuration/Configuration.xml", brandName, max_speed, angleVehicle, motorName);
                vehicleNames[i][j] = brandName;
                motorNames[i][j] = motorName;
                angleVehicles[i][j] = angleVehicle;
                speedVehicles[i][j] = max_speed;
            }
        }
    }

    // Show the vehicle selected
    Sprite vehicleCar;

    vehicleCar.setTexture(vehicleTextures[0][0], true);
    vehicleCar.setScale(1.6f * c.screenScale, 1.6f * c.screenScale);
    vehicleCar.setPosition((c.w.getSize().x / 2.f) + 160.0f * c.screenScale, c.w.getSize().y / 2.f - 25.f * c.screenScale);

    // Control if the group has been canceled
    bool cancelledGroup = false, checkingGroup = false;

    // Control if the vehicle selection has been canceled
    bool cancelledVehicle = false, checkingVehicle = false;

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
    selectionVehicleText.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));
    selectionVehicleText.setFont(c.fontVehicleSelectionMenu);
    selectionVehicleText.setStyle(Text::Bold | Text::Underlined);
    selectionVehicleText.setFillColor(c.colorTitleTextVehicleSelectionMenu);
    selectionVehicleText.setOutlineColor(c.colorTitleBorderVehicleSelectionMenu);
    selectionVehicleText.setOutlineThickness(5.0f * c.screenScale);
    selectionVehicleText.setPosition(c.w.getSize().x / 2.f - selectionVehicleText.getLocalBounds().width / 2.f,
                                     c.w.getSize().y / 2.f - 260.0f * c.screenScale);

    // Main Text of the menu
    Text colorDescription;
    colorDescription.setString("PRESS UP OR DOWN KEYS TO CHANGE THE COLOR OF THE CAR");
    colorDescription.setCharacterSize(static_cast<unsigned int>(int(25.0f * c.screenScale)));
    colorDescription.setFont(c.fontVehicleSelectionMenu);
    colorDescription.setStyle(Text::Bold | Text::Underlined);
    colorDescription.setFillColor(c.colorTitleTextVehicleSelectionMenu);
    colorDescription.setOutlineColor(c.colorTitleBorderVehicleSelectionMenu);
    colorDescription.setOutlineThickness(5.0f * c.screenScale);
    colorDescription.setPosition(c.w.getSize().x / 2.f - colorDescription.getLocalBounds().width / 2.f,
                                 c.w.getSize().y / 2.f - 210.0f * c.screenScale);

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
    accelerationText.setString("0 - " + to_string(int(speedVehicles[0][0]) / 2) + " KM/H:");
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
    angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
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

    // While start and backspace have not been pressed
    while (!startPressed && !backSpacePressed) {

        optionSelected = 0;
        colorSelected = colorCars[optionSelected];

        // Reproduce the sound effect
        r.soundEffects[40]->play();

        // Throw the threads
        if (onMultiplayer){
            if (modeMultiplayer == 0){
                // Owner
                vehicleOwner = thread(controlVehicleOwner, this, ref(cancelledGroup));
            }
            else {
                // Guest
                vehicleGuest = thread(controlVehicleGuest, this, ref(cancelledVehicle));
            }
        }

        // Until the start keyword is not pressed
        while (!startPressed && !backSpacePressed) {

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)){
                if (e.type == Event::Closed){
                    if (onMultiplayer){
                        Text complainText;
                        complainText.setString("THIS BUTTON CANT'T BE USED NOW ");
                        complainText.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
                        complainText.setFont(c.fontTitleMultiplayerMenu);
                        complainText.setStyle(Text::Bold);
                        complainText.setFillColor(c.colorTitleTextMultiplayerMenu);
                        complainText.setOutlineColor(c.colorTitleBorderMultiplayerMenu);
                        complainText.setOutlineThickness(5.0f * c.screenScale);
                        complainText.setPosition((c.w.getSize().x / 2.f) - complainText.getLocalBounds().width / 2.f,
                                                  c.w.getSize().y / 2.f + 190.f * c.screenScale);

                        for (int i = 0; i <= 120; i++){

                            Event e;
                            c.window.pollEvent(e);

                            c.w.clear();
                            c.w.draw(sprite);
                            c.w.draw(selectionVehicleText);

                            if (optionSelected != 5){
                                c.w.draw(colorDescription);
                            }

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
                            c.w.draw(complainText);

                            bufferSprite.setTexture(c.w.getTexture(), true);
                            c.w.display();
                            c.window.draw(bufferSprite);
                            c.window.display();
                        }
                    }
                    else {
                        return EXIT;
                    }
                }
            }

            if (onMultiplayer){
                if (modeMultiplayer == 0){
                    mtx3.lock();
                    checkingGroup = cancelledGroup;
                    mtx3.unlock();
                    if (checkingGroup){
                        backSpacePressed = true;
                    }
                }
                else {
                    mtx3.lock();
                    checkingVehicle = cancelledVehicle;
                    mtx3.unlock();
                    if (checkingVehicle){
                        backSpacePressed = true;
                    }
                }
            }


            // Check if the up or down cursor keys have been pressed or not
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Right)) {
                // Up cursor pressed and change the soundtrack selected in the list
                if (optionSelected != 5) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected++;

                    colorSelected = colorCars[optionSelected];

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
                            break;
                        case 4:
                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(2.8f * c.screenScale, 2.8f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 148.0f * c.screenScale,
                                                   c.w.getSize().y / 2.f + 45.f * c.screenScale);

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
                            break;
                        case 5:
                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(2.8f * c.screenScale, 2.8f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 118.0f * c.screenScale,
                                                   c.w.getSize().y / 2.f + 5.f * c.screenScale);

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
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Left)) {
                // Down cursor pressed and change the soundtrack selected in the list
                if (optionSelected != 0) {
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected--;

                    colorSelected = colorCars[optionSelected];

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

                            triangle.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                            break;
                        case 4:
                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(2.8f * c.screenScale, 2.8f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 148.0f * c.screenScale,
                                                   c.w.getSize().y / 2.f + 45.f * c.screenScale);

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

                            triangle.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                    }
                }
            }
            // Check if the up or down cursor keys have been pressed or not
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Up) && optionSelected != 5) {
                // Up cursor pressed and change the soundtrack selected in the list
                if (colorSelected != 7) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();

                    colorSelected++;
                    colorCars[optionSelected] = colorSelected;

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
                            break;
                        case 4:
                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(2.8f * c.screenScale, 2.8f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 148.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f + 45.f * c.screenScale);

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
                    }
                }
            }
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Down) && optionSelected != 5) {
                // Up cursor pressed and change the soundtrack selected in the list
                if (colorSelected != 0) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();

                    colorSelected--;
                    colorCars[optionSelected] = colorSelected;

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
                            break;
                        case 4:
                            accelerationText.setString("0 - " + to_string(int(speedVehicles[optionSelected][colorSelected]) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[optionSelected][colorSelected], true);
                            vehicleCar.setScale(2.8f * c.screenScale, 2.8f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 148.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f + 45.f * c.screenScale);

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
                    }
                }
            }

            c.w.draw(sprite);
            c.w.draw(selectionVehicleText);

            if (optionSelected != 5){
                c.w.draw(colorDescription);
            }

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
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
                // Change the controllers of the car
                startPressed = true;
                r.soundEffects[2]->stop();
                r.soundEffects[2]->play();
            }
            // Check if backspace has been pressed
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {
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
                case 3:
                case 4:
                    triangle.setFillColor(c.vehicleSelectionMenuColorButtons[1]);
                    triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[1]);
                    break;
                case 5:
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
        if (onMultiplayer){
            // The player is in multi player mode
            if (modeMultiplayer == 0){
                // Owner of the group

                if (checkingGroup){
                    r.soundTracks[16]->stop();
                    r.soundTracks[18]->play();
                    vehicleOwner.join();
                    return MULTIPLAYER_NAME_GROUP;
                }

                // Create a Linda driver compatible with Windows to make communicate with the Linda server
                LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");

                mtx3.lock();
                int numPlayers = groupDataPlayers.size();
                mtx3.unlock();

                if (numPlayers > 1){
                    for (int i = 2; i <= numPlayers; i++){

                        mtx3.lock();
                        int idCode = groupDataPlayers[i - 1].getCodePlayer();
                        string name = groupDataPlayers[i - 1].getNickNamePlayer();
                        mtx3.unlock();

                        // Inform that the group is cancelled
                        Tuple t = Tuple("CANCEL_CAR", nickNameGroupMultiplayer, to_string(idCode), name, nickNameMultiplayer);

                        winLindadriver.postNote(t);
                    }
                }

                r.soundTracks[16]->stop();
                r.soundTracks[18]->play();

                 // Inform that the group is cancelled
                Tuple t = Tuple("VEHICLE_CLOSED", nickNameGroupMultiplayer, "?A", "?B", nickNameMultiplayer);
                winLindadriver.postNote(t);
                vehicleOwner.join();

                winLindadriver.stop();

                // Control the end point
                if (typeOfGameMultiplayer == 0){
                    return SELECTION_MODE_MULTIPLAYER;
                }
                else {
                    return SELECTION_CIRCUIT_MULTIPLAYER;
                }
            }
            else {

                if (cancelledVehicle){

                    vehicleGuest.join();

                    r.soundTracks[16]->stop();
                    r.soundTracks[18]->play();

                    // Control the end point
                    if (typeOfGameMultiplayer == 0){
                        return SELECTION_MODE_MULTIPLAYER;
                    }
                    else {
                        return SELECTION_CIRCUIT_MULTIPLAYER;
                    }
                }

                // Create a Linda driver compatible with Windows to make communicate with the Linda server
                LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");

                // Get the owner nickname
                string name = groupDataPlayers[0].getNickNamePlayer();

                Tuple t = Tuple("LEAVE_GROUP", nickNameGroupMultiplayer, to_string(codePlayerInGroup), nickNameMultiplayer, name);
                winLindadriver.postNote(t);

                t = Tuple("PLAYER_CLOSED", nickNameGroupMultiplayer, "?A", nickNameMultiplayer, "?B");
                winLindadriver.postNote(t);
                vehicleGuest.join();

                // Close connection
                winLindadriver.stop();

                r.soundTracks[16]->stop();
                r.soundTracks[18]->play();

                if (randomMultiplayerJoined){
                    return SELECT_MULTIPLAYER_JOIN;
                }
                else {
                     return MULTIPLAYER_NAME_GROUP;
                }
            }
        }
        else {
            r.soundTracks[1]->play();
            if (typeOfGame == 2){
                return CIRCUIT_SELECTION_MENU;
            }
            else if (typeOfGame == 0){
                return RIVAL_TYPE_MENU;
            }
            else {
                return GAME_MODES_MENU;
            }
        }
    }
    else if (startPressed){

        // Store the car selected by the player
        typeOfVehicle = optionSelected;
        colorCarSelected = colorSelected;

        if (onMultiplayer){

            // Counter of players registered
            int numPlayers = 1, localPlayers = 1;

            // Control that all the players are registered
            bool finishedRegister = false, checkingRegister = false;
            int players = groupDataPlayers.size();

            mtx3.lock();
            groupDataPlayers[codePlayerInGroup].setVehicleType(typeOfVehicle);
            groupDataPlayers[codePlayerInGroup].setColorVehicle(colorCarSelected);
            mtx3.unlock();

            Text multiplayerIndicator;
            multiplayerIndicator.setString("WAITING FOR THE REST OF PLAYERS 1 / " + to_string(players));
            multiplayerIndicator.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
            multiplayerIndicator.setFont(c.fontVehicleSelectionMenuPanelProp);
            multiplayerIndicator.setStyle(Text::Bold);
            multiplayerIndicator.setFillColor(c.colorTextVehicleSelectionProp);
            multiplayerIndicator.setOutlineColor(c.colorBorderVehicleSelectionProp);
            multiplayerIndicator.setOutlineThickness(2.0f * c.screenScale);
            multiplayerIndicator.setPosition(c.w.getSize().x / 2.f - multiplayerIndicator.getLocalBounds().width / 2.f,
                                             c.w.getSize().y / 2.f + 190.0f * c.screenScale);


            // Control the vehicle selected by the other rivals
            vehicleRestPlayers = thread(storeRivalPlayers, this, ref(numPlayers), ref(finishedRegister), ref(cancelledGroup));

            // Wait until all players have selected their cars
            while (!checkingRegister && !checkingGroup){

                // Detect the possible events
                Event e{};
                while (c.window.pollEvent(e)){
                    if (e.type == Event::Closed){
                        Text complainText;
                        complainText.setString("THIS BUTTON CANT'T BE USED NOW ");
                        complainText.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
                        complainText.setFont(c.fontTitleMultiplayerMenu);
                        complainText.setStyle(Text::Bold);
                        complainText.setFillColor(c.colorTitleTextMultiplayerMenu);
                        complainText.setOutlineColor(c.colorTitleBorderMultiplayerMenu);
                        complainText.setOutlineThickness(5.0f * c.screenScale);
                        complainText.setPosition((c.w.getSize().x / 2.f) - complainText.getLocalBounds().width / 2.f,
                                                  c.w.getSize().y / 2.f + 190.f * c.screenScale);

                        for (int i = 0; i <= 120; i++){

                            Event e;
                            c.window.pollEvent(e);

                            c.w.clear();
                            c.w.draw(sprite);
                            c.w.draw(selectionVehicleText);

                            if (optionSelected != 5){
                                c.w.draw(colorDescription);
                            }

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
                            c.w.draw(complainText);

                            bufferSprite.setTexture(c.w.getTexture(), true);
                            c.w.display();
                            c.window.draw(bufferSprite);
                            c.window.display();
                        }
                    }
                }

                // Check if all rivals have selected their cars
                mtx3.lock();
                localPlayers = numPlayers;
                checkingRegister = finishedRegister;
                checkingGroup = cancelledGroup;
                mtx3.unlock();

                // Display the menu
                c.w.clear();

                c.w.draw(sprite);
                c.w.draw(selectionVehicleText);

                if (optionSelected != 5){
                    c.w.draw(colorDescription);
                }

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

                players = groupDataPlayers.size();
                multiplayerIndicator.setString("WAITING FOR THE REST OF PLAYERS " + to_string(localPlayers) + " / " + to_string(players));
                multiplayerIndicator.setPosition(c.w.getSize().x / 2.f - multiplayerIndicator.getLocalBounds().width / 2.f,
                                                 c.w.getSize().y / 2.f + 190.0f * c.screenScale);


                c.w.draw(multiplayerIndicator);

                // Display the counter
                bufferSprite.setTexture(c.w.getTexture(), true);
                c.w.display();
                c.window.draw(bufferSprite);
                c.window.display();
            }

            if (checkingGroup){
                vehicleOwner.join();
                vehicleRestPlayers.join();
                return MULTIPLAYER_NAME_GROUP;
            }


            // Create the connection with the Linda server
            LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");

            if (modeMultiplayer == 0){
                // Inform that the group is cancelled
                Tuple t = Tuple("VEHICLE_DONE", nickNameGroupMultiplayer, "?A", "?B", nickNameMultiplayer);
                winLindadriver.postNote(t);
            }
            else {
                Tuple t = Tuple("VEHICLE_DONE", nickNameGroupMultiplayer, "?A", nickNameMultiplayer, "?B");
                winLindadriver.postNote(t);
            }

            winLindadriver.stop();

            if (modeMultiplayer == 0){
                vehicleOwner.join();
            }
            else {
                vehicleGuest.join();
            }
        }

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
                break;
            case 4:
                // Load the properties of the Formula one
                player5 = FormulaOne(speedVehicles[optionSelected][colorSelected], SPEED_FACTOR,
                          speedVehicles[optionSelected][colorSelected] * ACCELERATION_INCREMENT / MAX_SPEED, 4.f, 4.f,
                          COUNTER, "Data/Vehicles/FormulaOnes/FormulaOne" + to_string(colorSelected + 1), 0.0f, RECTANGLE,
                          vehicleNames[optionSelected][colorSelected], angleVehicles[optionSelected][colorSelected],
                          motorNames[optionSelected][colorSelected]);
                break;
            case 5:
                // Load the properties if the Police
                // Create the properties of the police car
                player6 = Police(max_speed, SPEED_FACTOR, speedVehicles[optionSelected][colorSelected] * ACCELERATION_INCREMENT / MAX_SPEED,
                                 4.f, 4.f, COUNTER, "Data/Vehicles/Police", 0.0f, RECTANGLE, vehicleNames[optionSelected][colorSelected],
                                 angleVehicles[optionSelected][colorSelected], motorNames[optionSelected][colorSelected]);
        }

        if (onMultiplayer){
            while (1){
                cout << "AQUI ESTAMOS" << endl;
            }
        }
        else {
            // Store the rival cars
            if (typeOfGame == 0 || typeOfGame == 2){
                // Store the rival cars in the vector
                storingRivalCars(c);
            }
            if (typeOfGame == 2){
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
                        break;
                    case 4:
                        player5.setVehicle(typeOfGame);
                        break;
                    case 5:
                        player6.setVehicle(typeOfGame);
                }
                return LOADING;
            }
            else {
                return LOAD_GAME;
            }
        }
    }
    return EXIT;
}




/**
 * Load the configuration of the rival type selection menu in its xml file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void Game::loadRivalTypeSelectionMenuConfiguration(const string path, Configuration& c){

    // Open the xml file of the rival type menu
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Local variable to store temporary the text content and the fonts of the texts
    string content, fontPath, backgroundTexture, colorKind;

    // Iterate to get the information of the rival type menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check it is the node that contains the information of the background
        if ((string)property->name() == "Background"){
            // Get the background image of the menu
            backgroundTexture = (string)property->value();
            c.rivalTypeMenuBackground.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the rival type menu
            for (xml_node<> *panelProp = property->first_node(); panelProp; panelProp = panelProp->next_sibling()){
                // Check it is the node that contains the information of the background of the panel
                if ((string)panelProp->name() == "Background"){
                    // Get the background image of the menu
                    backgroundTexture = (string)panelProp->value();
                    c.rivalTypeMenuPanelBack.loadFromFile(backgroundTexture);
                }
                // Check it is the node that contains the information of the color border of the panel
                else if ((string)panelProp->name() == "ColorBorder"){
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the rival type menu
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
                    // Store the color border of the panel
                    c.colorBorderPanelRivalTypeMenu = Color(colorRed, colorGreen, colorBlue);
                }
            }
        }
        // Check if it is the node that stores the information of the main text of the rival type menu
        else if ((string)property->name() == "Title"){
            // Iterate to get the information of the title
            for (xml_node<> *titleProp = property->first_node(); titleProp; titleProp = titleProp->next_sibling()){
                // Get the red color channel
                if ((string)titleProp->name() == "Content"){
                    // Get the content of the title
                    content = (string)titleProp->value();
                    c.contentTitleRivalTypeMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontRivalTypeMenu.loadFromFile(fontPath);
                }
                // Get color text of the title
                else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                    // Get the kind of color to process
                    colorKind = (string)titleProp->name();
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the rival type menu
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
                        c.colorTitleTextRivalTypeMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderRivalTypeMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
        // Check if it is the node that stores the information panel of the buttons
        else if ((string)property->name() == "DescriptionPanel"){
            // Iterate to get the information of the description panel
            for (xml_node<> *descriptionProp = property->first_node(); descriptionProp; descriptionProp = descriptionProp->next_sibling()){
                // Get the kind of color to process
                colorKind = (string)descriptionProp->name();
                // Get the border color of the panel
                int colorRed = 0, colorGreen = 0, colorBlue = 0;
                // Iterate to get the information of the rival type menu
                for (xml_node<> *colorChannel = descriptionProp->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
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
                if (colorKind == "ColorPanelInside"){
                    c.colorDescriptionPanelInsideRivalTypeMenu = Color(colorRed, colorGreen, colorBlue);
                }
                // Check if it is the color of the border
                else if (colorKind == "ColorPanelBorder"){
                    c.colorDescriptionPanelBorderRivalTypeMenu = Color(colorRed, colorGreen, colorBlue);
                }
            }
        }
         // Check if it is the node that the different buttons of the menu
        else if ((string)property->name() == "MenuButtons"){
            Color colorFont;
            // Iterate to get the information of the buttons of the rival type type menu
            for (xml_node<> *buttonProp = property->first_node(); buttonProp; buttonProp = buttonProp->next_sibling()){
                // Get the font of the buttons
                if ((string)buttonProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)buttonProp->value();
                    c.fontMenuRivalTypeButtons.loadFromFile(fontPath);
                }
                // Get the color font of the buttons
                else if ((string)buttonProp->name() == "ColorFont"){
                    // Read the font from the file
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the rival rival type menu
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
                    c.colorFontMenuRivalTypeButtons = Color(colorRed, colorGreen, colorBlue);
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
                                    // Iterate to get the information of the rival type menu
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
                            }
                            else if ((string)button->name() == "Description"){
                                // Creation of the button and addition to the vector
                                posX = c.w.getSize().x / 2.f - 280.0f * c.screenScale;
                                posY = c.w.getSize().y / 2.f - (149.0f - idButton * 133.f) * c.screenScale;
                                widthButton = 200.0f * c.screenScale;
                                heightButton = 50.0f * c.screenScale;

                                // Creation of the button
                                Button b = Button(posX, posY, widthButton, heightButton, c.fontMenuRivalTypeButtons,
                                                  contentButton, colorButtons[0], colorButtons[1], c.colorFontMenuRivalTypeButtons,
                                                  buttonState, c.screenScale);

                                // Process the description text of the button
                                b.proccessDescription(button);
                                c.menuRivalTypeButtons.push_back(b);
                                idButton++;
                            }
                        }
                    }
                }
            }
        }
    }
    // The rival type menu has been read correctly
    c.rivalTypeMenuRead = true;
}



/**
 * Load the configuration of the rival type selection menu in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
State Game::selectionRivalTypeMenu(Configuration& c, SoundPlayer& r){

    // Prepare the screen to display the rival type menu with high quality
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));

    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Read the rival type menu if it has not been read
    if (!c.rivalTypeMenuRead){
        // Read the rival type menu xml configuration file
        string pathFile = "Data/Menus/RivalTypeMenu/Configuration/RivalTypeMenu.xml";
        loadRivalTypeSelectionMenuConfiguration(pathFile, c);
    }
    else {
        int numButtons = int(c.menuRivalTypeButtons.size());

        // Description of the button
        vector<string> descriptionButton;

        // Change the state of the first color
        Button b = Button(c.w.getSize().x / 2.f - 280.0f * c.screenScale, c.w.getSize().y / 2.f - 149.0f * c.screenScale,
                          200.0f * c.screenScale, 50.0f * c.screenScale, c.fontMenuRivalTypeButtons, c.menuRivalTypeButtons[0].getTextButton(),
                          c.menuRivalTypeButtons[0].getIdleColorButton(), c.menuRivalTypeButtons[0].getHoverColorButton(),
                          c.menuRivalTypeButtons[0].getFontColorButton(), 1, c.screenScale);

        // Get the description of the button
        descriptionButton = c.menuRivalTypeButtons[0].getDescriptionButton();
        b.setDescriptionButton(descriptionButton);

        c.menuRivalTypeButtons[0] = b;

        // Eliminate the buttons of the right column
        for (int i = 1; i < numButtons; i++){

            // Change the state of the first color
            Button b = Button(c.w.getSize().x / 2.f - 280.0f * c.screenScale, c.w.getSize().y / 2.f - (149.0f - i * 133.f) * c.screenScale,
                              200.0f * c.screenScale, 50.0f * c.screenScale, c.fontMenuRivalTypeButtons, c.menuRivalTypeButtons[i].getTextButton(),
                              c.menuRivalTypeButtons[i].getIdleColorButton(), c.menuRivalTypeButtons[i].getHoverColorButton(),
                              c.menuRivalTypeButtons[i].getFontColorButton(), 0, c.screenScale);

            // Get the description of the button
            descriptionButton = c.menuRivalTypeButtons[i].getDescriptionButton();
            b.setDescriptionButton(descriptionButton);

            c.menuRivalTypeButtons[i] = b;
        }
    }

    // Control if the start key is pressed or not
    bool startPressed = false;

    // Control if the escape key has been pressed
    bool escapePressed = false;

    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Control the option selected by the user
    int optionSelected = 0;

    // While start and backspace have not been pressed
    while (!startPressed && !escapePressed) {

        // Make the textures repeated
        c.rivalTypeMenuBackground.setRepeated(true);
        c.rivalTypeMenuPanelBack.setRepeated(true);

        // Global rectangle of the background
        IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
        Sprite sprite(c.rivalTypeMenuBackground, background);

        float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
        float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
        sprite.setScale(axis_x, axis_y);
        c.sRivalTypeMenuBackground = sprite;

        // Creation of the panel rectangle of the menu
        RectangleShape shape;
        shape.setPosition((c.w.getSize().x / 2.f) - 350.0f * c.screenScale, c.w.getSize().y / 2.f - 250.0f * c.screenScale);
        shape.setSize(sf::Vector2f(710.0f * c.screenScale, 500.0f * c.screenScale));
        shape.setOutlineColor(c.colorBorderPanelRivalTypeMenu);
        shape.setOutlineThickness(5.0f * c.screenScale);
        shape.setTexture(&c.rivalTypeMenuPanelBack, true);

        // Creation of the description panel of the buttons
        RectangleShape panelButton;
        panelButton.setPosition((c.w.getSize().x / 2.f) + 20.0f * c.screenScale, c.w.getSize().y / 2.f - 149.0f * c.screenScale);
        panelButton.setSize(sf::Vector2f(300.0f * c.screenScale, 314.0f * c.screenScale));
        panelButton.setFillColor(c.colorDescriptionPanelInsideRivalTypeMenu);
        panelButton.setOutlineColor(c.colorDescriptionPanelBorderRivalTypeMenu);
        panelButton.setOutlineThickness(3.0f * c.screenScale);

        // Main Text of the menu
        Text mainText;
        mainText.setString(c.contentTitleRivalTypeMenu);
        mainText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        mainText.setFont(c.fontRivalTypeMenu);
        mainText.setStyle(Text::Bold | Text::Underlined);
        mainText.setFillColor(c.colorTitleTextRivalTypeMenu);
        mainText.setOutlineColor(c.colorTitleBorderRivalTypeMenu);
        mainText.setOutlineThickness(5.0f * c.screenScale);
        mainText.setPosition((c.w.getSize().x / 2.f) - mainText.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f - 230.0f * c.screenScale);

        // Text description of the buttons
        Text descriptionText;
        descriptionText.setStyle(Text::Bold);
        descriptionText.setFillColor(c.colorFontMenuRivalTypeButtons);
        descriptionText.setCharacterSize(25 * c.screenScale);
        descriptionText.setFont(c.fontMenuRivalTypeButtons);

        // Until start and escape are not pressed
        while (!startPressed && !escapePressed) {

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)){
                if (e.type == Event::Closed){
                    return EXIT;
                }
            }

            // Check if the up or down cursor keys have been pressed or not
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Down)) {
                if (optionSelected != int(c.menuRivalTypeButtons.size() - 1)) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected++;
                    c.menuRivalTypeButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    c.menuRivalTypeButtons[optionSelected - 1].setButtonState(BUTTON_IDLE);
                }
            }
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Up)) {
                if (optionSelected != 0) {
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected--;
                    // Change the color appearance of both buttons
                    c.menuRivalTypeButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    c.menuRivalTypeButtons[optionSelected + 1].setButtonState(BUTTON_IDLE);
                }
            }


            c.w.draw(c.sRivalTypeMenuBackground);
            c.w.draw(shape);
            c.w.draw(panelButton);
            c.w.draw(mainText);

            // Show the buttons of the menu
            for (int i = 0; i < (int)c.menuRivalTypeButtons.size(); i++) {

                c.menuRivalTypeButtons.at(i).render(&c.w);

                // Draw the button description in the panel
                if (i == optionSelected){

                    int posXDescriptionOffset = panelButton.getPosition().x + 10;
                    int posYDescriptionOffset = panelButton.getPosition().y + 10;

                    // Draw the button description
                    // Display the description of the button
                    vector<string> wordsButton =  c.menuRivalTypeButtons.at(i).getDescriptionButton();

                    for (string s : wordsButton){
                        descriptionText.setString(s);
                        if (posXDescriptionOffset + descriptionText.getLocalBounds().width <= c.thresholdDescriptionX){
                            descriptionText.setPosition(posXDescriptionOffset, posYDescriptionOffset);
                            c.w.draw(descriptionText);
                            posXDescriptionOffset += descriptionText.getLocalBounds().width + 10;
                        }
                        else {
                            posXDescriptionOffset = panelButton.getPosition().x + 10;
                            posYDescriptionOffset += c.thresholdDescriptionY;
                            descriptionText.setPosition(posXDescriptionOffset, posYDescriptionOffset);
                            c.w.draw(descriptionText);
                            posXDescriptionOffset += descriptionText.getLocalBounds().width + 10;
                        }
                    }
                }
            }

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
            sleep(milliseconds(120));

            // Check if start has been pressed
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
                startPressed = true;
                r.soundEffects[2]->stop();
                r.soundEffects[2]->play();
            }
            // Check if escape has been pressed
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {
                escapePressed = true;
                r.soundEffects[11]->stop();
                r.soundEffects[11]->play();
            }
        }
    }

    // Control the pixel art flag to create the view of the screen
    if (c.enablePixelArt) {
        if (c.isDefaultScreen){
            c.window.setView(View(Vector2f(DEFAULT_WIDTH / 4.0f, DEFAULT_HEIGHT / 4.0f),
                                  Vector2f(DEFAULT_WIDTH / 2.0f, DEFAULT_HEIGHT / 2.0f)));
        }
        else {
            c.window.setView(View(Vector2f(SCREEN_HD_WIDTH / 4.0f, SCREEN_HD_HEIGHT / 4.0f),
                                  Vector2f(SCREEN_HD_WIDTH / 2.0f, SCREEN_HD_HEIGHT / 2.0f)));
        }
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));
        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);
    }

    // Check the option selected
    switch(optionSelected){
        case 0:
            // Original rivals
            rivalTypeMode = 0;
            break;
        case 1:
            // User type rivals
            rivalTypeMode = 1;
            break;
        case 2:
            // Random rivals
            rivalTypeMode = 2;
    }

    // Control the escape key
    if (startPressed){
        if (typeOfGame == 2){
            return LOAD_GAME;
        }
        else {
            r.soundTracks[1]->stop();
            return VEHICLE_SELECTION;
        }
    }
    else if (escapePressed){
        return GAME_MODES_MENU;
    }
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
        else if (typeOfGame == 2) {
            titleText.setString(tourLandScapes[landScapeSelected].getName());
        }
        else if (typeOfGame == 3) {
            titleText.setString("CRIMINAL ARRESTED");
        }
        else if (typeOfGame == 4) {
            titleText.setString("STAGE CLEARED");
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
                break;
            case 4:
                vehicleTexture.loadFromFile("Data/Vehicles/FormulaOnes/FormulaOne" + to_string(colorCarSelected + 1) + "/Images/c1.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(2.8f * c.screenScale, 2.8f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 75.0f * c.screenScale, c.w.getSize().y / carOffset + 17.f * c.screenScale);
                break;
            case 5:
                vehicleTexture.loadFromFile("Data/Vehicles/Police/Images/c46.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset + 17.f * c.screenScale);
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
        if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
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
    else if (typeOfGame == 2) {
        titleText.setString(tourLandScapes[landScapeSelected].getName());
    }
    else if (typeOfGame == 3) {
        titleText.setString("CRIMINAL ARRESTED");
    }
    else if (typeOfGame == 4) {
        titleText.setString("STAGE CLEARED");
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
            break;
        case 4:
            vehicleTexture.loadFromFile("Data/Vehicles/FormulaOnes/FormulaOne" + to_string(colorCarSelected + 1) + "/Images/c1.png");
            vehicle.setTexture(vehicleTexture, true);
            vehicle.setScale(2.8f * c.screenScale, 2.8f * c.screenScale);
            vehicle.setPosition((c.w.getSize().x / 2.f) - 75.0f * c.screenScale, c.w.getSize().y / carOffset + 17.f * c.screenScale);
            break;
        case 5:
            vehicleTexture.loadFromFile("Data/Vehicles/Police/Images/c46.png");
            vehicle.setTexture(vehicleTexture, true);
            vehicle.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
            vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset + 17.f * c.screenScale);
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
    else if (typeOfGame == 2){
        path = "Data/Records/PolePosition/LandScape" + to_string(indexLandScape + 1) + "_";
    }
    else if (typeOfGame == 3){
        path = "Data/Records/DrivingFury/LevelScore" + to_string(currentStage) + "_";
    }
    else if (typeOfGame == 4){
        path = "Data/Records/Demarrage/LevelScore" + to_string(currentStage) + "_";
    }

    // Control the difficulty of the game
    switch (c.level){
        case EASY:
            path += "Easy.xml";
            break;
        case NORMAL:
            path += "Normal.xml";
            break;
        case HARD:
            path += "Hard.xml";
    }

    // Read the score
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
            if (cent_sec < centsSecondLap){
                // Same minutes and seconds but less hundredths of seconds
                record = true;
            }
        }
    }

    // Reproduce sound effect of record
    if ((record && typeOfGame != 0 && typeOfGame != 2) ||
        (record && (typeOfGame == 0 || typeOfGame == 2) && posArrival == 1))
    {
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
                            r.soundEffects[116]->stop();
                            r.soundEffects[116]->play();
                        }
                        else {
                            if (lettersIntroduced == 3) {
                                name = name.substr(0, name.size() - 1);
                                name += keyLetter;
                                r.soundEffects[116]->stop();
                                r.soundEffects[116]->play();
                            }
                            else {
                                name = name.substr(0, name.size() - 1);
                                name += keyLetter + "_";
                                r.soundEffects[116]->stop();
                                r.soundEffects[116]->play();
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
    Text levelPromotion;
    startText.setString("PRESS START");
    startText.setFont(c.fontMenus);

    levelPromotion.setString("TO PROMOTE TO THE NEXT LEVEL");
    levelPromotion.setFont(c.fontMenus);

    startText.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));
    startText.setPosition((c.w.getSize().x / 2.f) - (startText.getLocalBounds().width / 2.f),
                           c.w.getSize().y / 2.f + 150.0f * c.screenScale);

    levelPromotion.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));
    levelPromotion.setPosition((c.w.getSize().x / 2.f) - (levelPromotion.getLocalBounds().width / 2.f),
                                c.w.getSize().y / 2.f + 185.0f * c.screenScale);

    levelPromotion.setStyle(Text::Bold);
    levelPromotion.setFillColor(Color::Green);
    levelPromotion.setOutlineColor(Color::Black);
    levelPromotion.setOutlineThickness(3.0f * c.screenScale);

    startText.setStyle(Text::Bold);
    startText.setFillColor(Color::Green);
    startText.setOutlineColor(Color::Black);
    startText.setOutlineThickness(3.0f * c.screenScale);

    if ((posArrival == 1 && (typeOfGame == 0 || typeOfGame == 2)) || (typeOfGame == 3 || typeOfGame == 4)){
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
                levelPromotion.setFillColor(Color::Green);
                levelPromotion.setOutlineColor(Color::Black);
            }
            else {
                totalTime.setFillColor(Color::Transparent);
                totalTime.setOutlineColor(Color::Transparent);
                timeLap.setFillColor(Color::Transparent);
                timeLap.setOutlineColor(Color::Transparent);
                startText.setFillColor(Color::Transparent);
                startText.setOutlineColor(Color::Transparent);
                levelPromotion.setFillColor(Color::Transparent);
                levelPromotion.setOutlineColor(Color::Transparent);
            }

            c.w.draw(totalTime);
            c.w.draw(timeLap);
            c.w.draw(vehicle);
            c.w.draw(startText);

            if ((typeOfGame == 0 && indexLandScape != 3) ||
               ((typeOfGame == 3 || typeOfGame == 4) && currentStage <= totalStages))
            {
                c.w.draw(levelPromotion);
            }

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();

             // Check if the start keyword has been pressed
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
                // Pass to the second menu
                startPressed = true;
                r.soundEffects[1]->stop();
                r.soundEffects[1]->play();
                r.soundEffects[49]->stop();
                r.soundEffects[49]->play();
            }

            sleep(milliseconds(50));
        }
    }
    else {
        // Ask to the player repeat the game

        Texture tex;
        tex.loadFromFile("Data/Animations/RepeatingGame/crono.png");

        RectangleShape shape2;
        shape2.setPosition((c.w.getSize().x / 2.f) - 287.0f * c.screenScale, c.w.getSize().y / 2.f - 210.f * c.screenScale);
        shape2.setSize(sf::Vector2f(590.0f * c.screenScale, 420.0f * c.screenScale));
        shape2.setOutlineColor(Color(30, 159, 211));
        shape2.setOutlineThickness(5.0f * c.screenScale);
        shape2.setTexture(&tex, true);

        Text continueText;
        continueText.setString("CONTINUE?");
        continueText.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
        continueText.setFont(c.fontMenus);
        continueText.setStyle(Text::Bold);
        continueText.setFillColor(Color::White);
        continueText.setOutlineColor(Color::Black);
        continueText.setOutlineThickness(3.0f * c.screenScale);
        continueText.setPosition((c.w.getSize().x / 2.f) - (continueText.getLocalBounds().width / 2.f),
                                  c.w.getSize().y / 2.f - 180.0f * c.screenScale);

        Text yesText;
        yesText.setString("YES");
        yesText.setCharacterSize(static_cast<unsigned int>(int(48.0f * c.screenScale)));
        yesText.setFont(c.fontMenus);
        yesText.setStyle(Text::Bold);
        yesText.setFillColor(Color::Green);
        yesText.setOutlineColor(Color::Black);
        yesText.setOutlineThickness(3.0f * c.screenScale);
        yesText.setPosition((c.w.getSize().x / 2.f) - (yesText.getLocalBounds().width / 2.f),
                                  c.w.getSize().y / 2.f - 70.0f * c.screenScale);

        Text noText;
        noText.setString("NO");
        noText.setCharacterSize(static_cast<unsigned int>(int(48.0f * c.screenScale)));
        noText.setFont(c.fontMenus);
        noText.setStyle(Text::Bold);
        noText.setFillColor(Color::Green);
        noText.setOutlineColor(Color::Black);
        noText.setOutlineThickness(3.0f * c.screenScale);
        noText.setPosition((c.w.getSize().x / 2.f) - (noText.getLocalBounds().width / 2.f),
                                  c.w.getSize().y / 2.f + 70.0f * c.screenScale);

        CircleShape triangle(20 * c.screenScale, 3);
        triangle.setFillColor(Color::Yellow);
        triangle.setOutlineColor(Color::Black);
        triangle.setOutlineThickness(2.0f * c.screenScale);
        triangle.setRotation(90);
        triangle.setPosition(c.w.getSize().x / 2.f - 37.f * c.screenScale - 15.f, c.w.getSize().y / 2.f - 58.0f * c.screenScale);

        bool startPressed = false;

        bool sound = false;

        int optionSelected = 0;

        while (!startPressed){

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }

            // Check if the up or down cursor keys have been pressed or not
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Down)) {
                if (optionSelected != 1){
                    optionSelected++;
                    triangle.setPosition(c.w.getSize().x / 2.f - 37.f * c.screenScale - 15.f,
                                         c.w.getSize().y / 2.f + 80.0f * c.screenScale);

                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                }
            }
            // Check if the up or down cursor keys have been pressed or not
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Up)) {
                if (optionSelected != 0){
                    optionSelected--;
                    triangle.setPosition(c.w.getSize().x / 2.f - 37.f * c.screenScale - 15.f,
                                         c.w.getSize().y / 2.f - 58.0f * c.screenScale);

                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                }
            }

            c.w.draw(sprite);
            c.w.draw(shape);
            c.w.draw(titleText);
            c.w.draw(totalTime);
            c.w.draw(timeLap);
            c.w.draw(vehicle);
            c.w.draw(shape2);
            c.w.draw(continueText);
            c.w.draw(yesText);
            c.w.draw(noText);
            c.w.draw(triangle);

            if (!sound){
                sound = true;
                r.soundEffects[110]->stop();
                r.soundEffects[110]->play();
            }

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();

            sleep(milliseconds(50));

            // Check if start has been pressed
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
                // Change the controllers of the car
                startPressed = true;
                r.soundEffects[2]->stop();
                r.soundEffects[2]->play();
            }
        }

        // Control the option selected by the user
        if (optionSelected == 1){
            r.soundTracks[15]->stop();
            r.soundTracks[0]->stop();
            r.soundTracks[0]->play();
            return START;
        }
        else {
            r.soundEffects[49]->stop();
            r.soundEffects[49]->play();
        }
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
        else if (typeOfGame == 2) {
            titleText.setString(tourLandScapes[landScapeSelected].getName());
        }
        else if (typeOfGame == 3) {
            titleText.setString("CRIMINAL ARRESTED");
        }
        else if (typeOfGame == 4) {
            titleText.setString("STAGE CLEARED");
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
                break;
            case 4:
                vehicleTexture.loadFromFile("Data/Vehicles/FormulaOnes/FormulaOne" + to_string(colorCarSelected + 1) + "/Images/c1.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(2.8f * c.screenScale, 2.8f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 75.0f * c.screenScale, c.w.getSize().y / carOffset + 17.f * c.screenScale);
                break;
            case 5:
                vehicleTexture.loadFromFile("Data/Vehicles/Police/Images/c46.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset + 17.f * c.screenScale);
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
        if (posArrival == 1){
            if (indexLandScape == 3){
                r.soundTracks[15]->stop();
                r.soundTracks[0]->play();
                return START;
            }
            else {
                indexLandScape++;
            }
        }
        currentMap = &tourLandScapes[indexLandScape];
        time = int(float(tourLandScapes[indexLandScape].getTimeToPlay()) * timeMul);
        storingRivalCars(c);
    }

    finalGame = false;

    lastY = 0;
    vehicleCrash = false;

    onPause = false;
    comeFromOptions = false;
    blink = false;
    arrival = false;
    updatedTimeCheck = false;
    checkPoint = false;

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
        case 4:
            player4.setVehicle(typeOfGame);
            break;
        case 5:
            player5.setVehicle(typeOfGame);
            break;
        case 6:
            player6.setVehicle(typeOfGame);
    }

    r.soundTracks[15]->stop();

    // Reload a new rival
    if (typeOfGame == 3){

        // Increment the stage where the player plays
        currentStage++;

        if (currentStage > totalStages){
            // Finish the game mode
            r.soundTracks[15]->stop();
            r.soundTracks[0]->play();
            return START;
        }
        else {
            currentLandScape = 0;
            goalCarStage++;
        }

        string path = "Data/Vehicles/Police/Configuration/Configuration.xml";
        string brandName, motorName;
        float max_speed, angle;
        updatedGoalCar = false;
        updatedPlayerCar = false;

        // Load the properties of the police car
        loadVehicleProperties(path , brandName, max_speed, angle, motorName);

        // Code to generate randomly a vehicle to chase which cant be a motorbike
        int vehicle = rand_generator_int(0, 4);

        // Select a color to the type of vehicle chosen
        int colorVehicle = rand_generator_int(0, 7);

        // Set the scale of the vehicle
        switch(vehicle){
            case 0:
                goalCar = RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 2.5f, COUNTER, "Data/Vehicles/Motorbikes/Motorbike" +
                                   to_string(colorVehicle + 1), 0.f, maxDistance, Motorbike_vehicle::PLAYER_TEXTURES, 1, 2, 15, 16,
                                   3, 8, 17, 22, 9, 14, 23, 28, 1, 2, 15, 16, 3, 8, 17, 22, 9, 14, 23, 28, 7, 13, 7, 13, 21, 27,
                                   21, 27, 1.15f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
                break;
            case 1:
                goalCar = RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 4.f, COUNTER, "Data/Vehicles/Devastators/Devastator" +
                             to_string(colorVehicle + 1), 0.f, maxDistance, Devastator_vehicle::PLAYER_TEXTURES, 1, 4, 19, 22,
                             5, 8, 23, 26, 9, 12, 27, 30, 13, 14, 31, 32, 15, 16, 33, 34, 17, 18, 35, 36, 6, 10, 15, 17, 24,
                             28, 33, 35, 1.55f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
                break;
            case 2:
                goalCar = RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 4.f, COUNTER, "Data/Vehicles/Minivans/Minivan" + to_string(colorVehicle + 1),
                             0.f, maxDistance, Minivan_vehicle::PLAYER_TEXTURES, 1, 2, 15, 16, 3, 5, 17, 19, 6, 8, 17, 19, 9, 10, 23, 24,
                             11, 12, 25, 26, 13, 14, 20, 22, 3, 6, 11, 13, 17, 20, 25, 27, 1.45f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
                break;
            case 3:
                goalCar = RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 4.5f, COUNTER, "Data/Vehicles/Trucks/Truck" + to_string(colorVehicle + 1),
                             0.f, maxDistance, Truck_vehicle::PLAYER_TEXTURES, 1, 5, 28, 32, 6, 10, 33, 37, 11, 15, 38, 42, 16, 19,
                             43, 46, 20, 23, 47, 50, 24, 27, 51, 54, 7, 12, 21, 25, 34, 39, 48, 52, 1.50f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
                break;
            case 4:
                goalCar = RivalCar(typeOfVehicle, MAX_SPEED, SPEED_FACTOR, 4.5f, COUNTER, "Data/Vehicles/FormulaOnes/FormulaOne"
                                   + to_string(colorVehicle + 1), 0.f, maxDistance, FormulaOne_vehicle::PLAYER_TEXTURES, 1, 2, 23,
                                   24, 3, 12, 25, 34, 13, 22, 35, 44, 1, 2, 23, 24, 3, 12, 25, 34, 13, 22, 35, 44, 11, 21, 11, 21,
                                   33, 43, 33, 43, 1.80f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
        }

        maps = referencedMaps;
        displayGoalCarIndicator = true;
        lifeGoalCar = 100;
        distanceGoalCar = maxDistance;
        mapId = make_pair(0, 0);
        currentMap = &maps[mapId.first][mapId.second];
        level = mapId.first + 1;
        time = int(float(currentMap->getTimeToPlay()) * timeMul);
    }
    else if (typeOfGame == 4){
        // Increment the stage where the player plays
        currentStage++;
        distanceAdvanced = 400;

        if (currentStage > totalStages){
            // Finish the game mode
            r.soundTracks[15]->stop();
            r.soundTracks[0]->play();
            return START;
        }
        else {
            currentLandScape = 0;
            goalCarStage++;
        }

        updatedGoalCar = false;
        updatedPlayerCar = false;

        // Code to generate randomly a vehicle to chase which cant be a motorbike
        int vehicle = rand_generator_int(0, 4);

        // Select a color to the type of vehicle chosen
        int colorVehicle = rand_generator_int(0, 7);

        // Set the scale of the vehicle
        switch(vehicle){
            case 0:
                goalCar = RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 2.5f, COUNTER, "Data/Vehicles/Motorbikes/Motorbike" +
                                   to_string(colorVehicle + 1), 0.f, maxDistance, Motorbike_vehicle::PLAYER_TEXTURES, 1, 2, 15, 16,
                                   3, 8, 17, 22, 9, 14, 23, 28, 1, 2, 15, 16, 3, 8, 17, 22, 9, 14, 23, 28, 7, 13, 7, 13, 21, 27,
                                   21, 27, 1.15f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
                break;
            case 1:
                goalCar = RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 4.f, COUNTER, "Data/Vehicles/Devastators/Devastator" +
                             to_string(colorVehicle + 1), 0.f, maxDistance, Devastator_vehicle::PLAYER_TEXTURES, 1, 4, 19, 22,
                             5, 8, 23, 26, 9, 12, 27, 30, 13, 14, 31, 32, 15, 16, 33, 34, 17, 18, 35, 36, 6, 10, 15, 17, 24,
                             28, 33, 35, 1.55f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
                break;
            case 2:
                goalCar = RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 4.f, COUNTER, "Data/Vehicles/Minivans/Minivan" + to_string(colorVehicle + 1),
                             0.f, maxDistance, Minivan_vehicle::PLAYER_TEXTURES, 1, 2, 15, 16, 3, 5, 17, 19, 6, 8, 17, 19, 9, 10, 23, 24,
                             11, 12, 25, 26, 13, 14, 20, 22, 3, 6, 11, 13, 17, 20, 25, 27, 1.45f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
                break;
            case 3:
                goalCar = RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 4.5f, COUNTER, "Data/Vehicles/Trucks/Truck" + to_string(colorVehicle + 1),
                             0.f, maxDistance, Truck_vehicle::PLAYER_TEXTURES, 1, 5, 28, 32, 6, 10, 33, 37, 11, 15, 38, 42, 16, 19,
                             43, 46, 20, 23, 47, 50, 24, 27, 51, 54, 7, 12, 21, 25, 34, 39, 48, 52, 1.50f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
                break;
            case 4:
                goalCar = RivalCar(vehicle, MAX_SPEED, SPEED_FACTOR, 4.5f, COUNTER, "Data/Vehicles/FormulaOnes/FormulaOne"
                                   + to_string(colorVehicle + 1), 0.f, maxDistance, FormulaOne_vehicle::PLAYER_TEXTURES, 1, 2, 23,
                                   24, 3, 12, 25, 34, 13, 22, 35, 44, 1, 2, 23, 24, 3, 12, 25, 34, 13, 22, 35, 44, 11, 21, 11, 21,
                                   33, 43, 33, 43, 1.80f);

                goalCar.setAI(c.maxAggressiveness, c.level, typeOfGame);
        }

        maps = referencedMaps;
        displayGoalCarIndicator = true;
        mapId = make_pair(0, 0);
        currentMap = &maps[mapId.first][mapId.second];
        distanceGoalCar = maxDistance;
        level = mapId.first + 1;
        time = int(float(currentMap->getTimeToPlay()) * timeMul);
    }
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




void Game::controlGuestPulses(bool& circuitSelected, bool& cancelledGroup, bool& escape){

    bool pathSelected, cancelled, escaped;

    // Check if the pulses have been received
    bool found;

    // Store locally if the circuit has been selected
    mtx3.lock();
    pathSelected = circuitSelected;
    cancelled = cancelledGroup;
    escaped = escape;
    mtx3.unlock();

    // Max attempts to delete a member of the group
    const int MAX_ATTEMPTS = 100;

    // Vector with the number of attempts of contacting to each member of the group
    vector<int> attemptsPerMember(numberPlayersGroup);

    // Initialize the vector
    for (int i = 0; i < numberPlayersGroup; i++){
        // Default attempts
        attemptsPerMember.push_back(0);
    }

    // Create the connection with the Linda server
    LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");

    // Until the circuit has been selected
    while (!pathSelected && !cancelled && !escaped){

        // Iterate the members
        for (int i = 2; i <= groupDataPlayers.size(); i++){

            // Getting the attributes of the player
            int idCode = groupDataPlayers[i - 1].getCodePlayer();
            string name = groupDataPlayers[i - 1].getNickNamePlayer();

            // Create the tuple that represents the pulse
            Tuple t = Tuple("PULSE_SENDED", nickNameGroupMultiplayer, name, to_string(idCode));
            Tuple r = winLindadriver.readNoteX(t, found);

            // Check if the pulse has been received
            if (!found && r.get(1) == NF){
                // Increment the failed attempts
                attemptsPerMember[i - 1]++;

                // Check if the player must be deleted or not
                if (attemptsPerMember[i - 1] == MAX_ATTEMPTS){

                    // Eliminate the player of the local list
                    for (int j = i; j < (int)groupDataPlayers.size(); j++){
                        groupDataPlayers[j].codePlayer--;
                    }
                    groupDataPlayers.erase(groupDataPlayers.begin() + i - 1);

                    numberPlayersGroup--;

                    if (numberPlayersGroup == 1){
                        mtx3.lock();
                        cancelledGroup = true;
                        mtx3.unlock();
                    }

                    // Alert to the rest of the members that this member must be deleted
                    for (int i = 1; i <= numberPlayersGroup; i++){

                        int idCode = groupDataPlayers[i - 1].getCodePlayer();
                        string namePlayer = groupDataPlayers[i - 1].getNickNamePlayer();

                        // Inform that the group is cancelled
                        Tuple t = Tuple("DELETE_PLAYER", nickNameGroupMultiplayer, namePlayer, to_string(idCode));
                        winLindadriver.postNote(t);
                    }
                }
            }
            else {
                // The player has responded with his pulse
                Tuple r = winLindadriver.removeNote(t);

                // The to the member that the pulse has been received
                Tuple t = Tuple("PULSE_RECEIVED", nickNameGroupMultiplayer, name, to_string(idCode));
                winLindadriver.postNote(t);

                // Restart the possible attempts
                attemptsPerMember[i - 1] = 0;
            }
        }
        // Store locally if the circuit has been selected
        mtx3.lock();
        pathSelected = circuitSelected;
        cancelled = cancelledGroup;
        escaped = escape;
        mtx3.unlock();
    }
    // Close connection with Linda server
    winLindadriver.stop();
}




void Game::sendGuestPulses(bool& circuitSelected, bool& finishedGroup, bool &cancelledCicruit){

    bool pathSelected = false, pulseReceived = false, found;
    bool fail = false;

    // Create the connection with the Linda server
    LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");

    // Send first pulse
    Tuple t = Tuple("PULSE_SENDED", nickNameGroupMultiplayer, nickNameMultiplayer, to_string(codePlayerInGroup));
    winLindadriver.postNote(t);

    // Code of the circuit selected by the user
    string codeCircuit;

    mtx3.lock();
    circuitSelected = pathSelected;
    fail = finishedGroup;
    mtx3.unlock();

    // Until the circuit has been selected
    while (!pathSelected && !fail && !cancelledCicruit){

        // Tuple that represents the pulse received
        t = Tuple("PULSE_RECEIVED", nickNameGroupMultiplayer, nickNameMultiplayer, to_string(codePlayerInGroup));

        // Check if the pulse has been received by the owner or not
        while (!pulseReceived){

            // Check if the pulse has been received
            Tuple r = winLindadriver.readNoteX(t, found);

            if (found && r.get(1) != NF){
                // Remove the ack pulse received
                winLindadriver.removeNote(r);
                pulseReceived = true;
            }
        }
        pulseReceived = false;

        // Tuple that represents the pulse received
        t = Tuple("CIRCUIT_SELECTED", nickNameGroupMultiplayer, nickNameMultiplayer, "?X");

        // Check if the pulse has been received
        Tuple r = winLindadriver.readNoteX(t, found);
        if (found && r.get(1) != NF){
            // Remove the ack pulse received
            winLindadriver.removeNote(r);
            pathSelected = true;

            mtx3.lock();
            circuitSelected = pathSelected;
            landScapeSelected = stoi(r.get(4));
            mtx3.unlock();
        }

        // Tuple that represents the pulse received
        t = Tuple("GAME_MODE_SELECTED", nickNameGroupMultiplayer, nickNameMultiplayer, "?X");
        // Check if the pulse has been received
        r = winLindadriver.readNoteX(t, found);
        if (found && r.get(1) != NF){
            // Remove the ack pulse received
            winLindadriver.removeNote(r);
            pathSelected = true;

            mtx3.lock();
            circuitSelected = pathSelected;
            typeOfGameMultiplayer = stoi(r.get(4));
            mtx3.unlock();
        }

        string codePlayer;

        // Check if any player of the group has been deleted or not
        t = Tuple("DELETE_PLAYER", nickNameGroupMultiplayer, nickNameMultiplayer, "?C");
        r = winLindadriver.readNoteX(t, found);
        if (found && r.get(1) != NF){
            // Remove the ack pulse received
            winLindadriver.removeNote(r);

            codePlayer = r.get(4);

            // Delete the player of the list
            int code = stoi(codePlayer);

            // Decrement our id
            if (code < codePlayerInGroup){
                codePlayerInGroup--;
            }

            // Eliminate the player of the local list
            for (int j = code; j < (int)groupDataPlayers.size(); j++){
                groupDataPlayers[j].codePlayer--;
            }
            groupDataPlayers.erase(groupDataPlayers.begin() + code - 1);

            // Decrement the number of members of your group
            numberPlayersGroup--;
        }

        // Check if any player of the group has been deleted or not
        t = Tuple("CANCELLED_CIRCUIT", nickNameGroupMultiplayer, "?Z", "?A", nickNameMultiplayer);
        r = winLindadriver.readNoteX(t, found);
        if (found && r.get(1) != NF){
            winLindadriver.removeNote(r);
            mtx3.lock();
            cancelledCicruit = true;
            mtx3.unlock();
        }

        // Check if any player of the group has been deleted or not
        t = Tuple("CANCELLED_GROUP", nickNameGroupMultiplayer, "?Z", "?A", nickNameMultiplayer);
        r = winLindadriver.readNoteX(t, found);

        if (found && r.get(1) != NF){
            winLindadriver.removeNote(r);

            fail = true;

            mtx3.lock();
            finishedGroup = true;
            mtx3.unlock();
        }

        mtx3.lock();
        fail = finishedGroup;
        mtx3.unlock();

        if (!pathSelected && !fail){
            // Send another pulse
            t = Tuple("PULSE_SENDED", nickNameGroupMultiplayer, nickNameMultiplayer, to_string(codePlayerInGroup));
            winLindadriver.postNote(t);
        }
    }
    // Close connection with Linda server
    winLindadriver.stop();
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

    if (onMultiplayer){

        // Times of each scenario
        vector<int> times;

        string path;
        if (typeOfGame == 0){
            times = {50, 53, 51, 52};
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

        // Delete the possible landscapes loaded in last attempts
        tourLandScapes.clear();

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

    // Control if the circuit has been selected
    bool circuitSelected = false;

    // Canceled group
    bool cancelledGroup = false;

    bool escape = false;

    // Show the vehicle selected
    Sprite circuitRoute;
    circuitRoute.setTexture(circuits[0], true);
    circuitRoute.setScale(3.0f * c.screenScale, 3.0f * c.screenScale);
    circuitRoute.setPosition(shape.getPosition().x + (float(shape.getSize().x) / 2.f) -
                            (float(circuitRoute.getLocalBounds().width ) / 2.f) * 3.0f * c.screenScale,
                             c.w.getSize().y / 2.f - 70.f * c.screenScale);

    if (onMultiplayer){
        // Throw the thread that control the pulses of the group guests
        guestPulses = thread(controlGuestPulses, this, ref(circuitSelected), ref(cancelledGroup), ref(escape));
    }

    // While start and backspace have not been pressed
    while (!startPressed && !backSpacePressed){

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
        while (!startPressed && !backSpacePressed){

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)){
                if (e.type == Event::Closed){
                    if (onMultiplayer){
                        Text complainText;
                        complainText.setString("THIS BUTTON CANT'T BE USED NOW ");
                        complainText.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));
                        complainText.setFont(c.fontTitleMultiplayerMenu);
                        complainText.setStyle(Text::Bold);
                        complainText.setFillColor(c.colorTitleTextMultiplayerMenu);
                        complainText.setOutlineColor(c.colorTitleBorderMultiplayerMenu);
                        complainText.setOutlineThickness(5.0f * c.screenScale);
                        complainText.setPosition((c.w.getSize().x / 2.f) - complainText.getLocalBounds().width / 2.f,
                                                  c.w.getSize().y / 2.f + 180.f * c.screenScale);

                        for (int i = 0; i <= 120; i++){

                            Event e;
                            c.window.pollEvent(e);

                            // Draw the elements of the menu
                            c.w.draw(sprite);
                            c.w.draw(shape);
                            c.w.draw(mainText);
                            c.w.draw(circuitName);
                            c.w.draw(circuitRoute);
                            c.w.draw(circuitIndicatorText);
                            c.w.draw(lapsIndicatorText);
                            c.w.draw(lapsText);
                            c.w.draw(circuitText);
                            c.w.draw(triangle2);
                            c.w.draw(complainText);

                            bufferSprite.setTexture(c.w.getTexture(), true);
                            c.w.display();
                            c.window.draw(bufferSprite);
                            c.window.display();
                        }
                    }
                    else {
                        return EXIT;
                    }
                }
            }

            // Check if the up or down cursor keys have been pressed or not
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Down)){
                // Up cursor pressed and change the soundtrack selected in the list
                if ((onMultiplayer && optionSelected < 1) || (!onMultiplayer && optionSelected != 2)){
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
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Up)){
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
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Left)){
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
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Right)){
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

            if (!onMultiplayer){
                // Racers indicators text
                racersText.setString(to_string(numberRacers));
                racersText.setPosition(c.w.getSize().x / 2.f - 80.0f * c.screenScale + racersIndicatorText.getLocalBounds().width + 5.f,
                                       c.w.getSize().y / 2.f + 180.0f * c.screenScale);
            }

            // Draw the elements of the menu
            c.w.draw(sprite);
            c.w.draw(shape);
            c.w.draw(mainText);
            c.w.draw(circuitName);
            c.w.draw(circuitRoute);
            c.w.draw(circuitIndicatorText);
            c.w.draw(lapsIndicatorText);
            c.w.draw(lapsText);

            if (!onMultiplayer){
                c.w.draw(racersIndicatorText);
                c.w.draw(racersText);
            }

            c.w.draw(circuitText);
            c.w.draw(triangle2);

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();

            sleep(milliseconds(120));

            // Check if start key has been pressed
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)){
                // Change the controllers of the car
                startPressed = true;
                r.soundEffects[2]->stop();
                r.soundEffects[2]->play();

                mtx3.lock();
                circuitSelected = true;
                mtx3.unlock();
                guestPulses.join();
            }
            // Check if backspace key has been pressed
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)){
                // Change the controllers of the car
                backSpacePressed = true;
                r.soundEffects[11]->stop();
                r.soundEffects[11]->play();
                mtx3.lock();
                escape = true;
                mtx3.unlock();
                guestPulses.join();
            }
            else if (cancelledGroup){
                backSpacePressed = true;
                r.soundEffects[11]->stop();
                r.soundEffects[11]->play();
                guestPulses.join();
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

        // Check if the player is on multi player mode
        if (onMultiplayer){

            // Create the connection with the Linda server
            LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");

            // Iterate the members of the group
            for (int i = 2; i <= numberPlayersGroup; i++){

                int idCode = groupDataPlayers[i - 1].getCodePlayer();
                string name = groupDataPlayers[i - 1].getNickNamePlayer();

                // Inform that the group is cancelled
                Tuple t = Tuple("CIRCUIT_SELECTED", nickNameGroupMultiplayer, name, to_string(landScapeSelected));
                winLindadriver.postNote(t);

                t = Tuple("PULSE_RECEIVED", nickNameGroupMultiplayer, name, to_string(idCode));
                winLindadriver.postNote(t);
            }

            mtx3.lock();
            circuitSelected = true;
            mtx3.unlock();

            winLindadriver.stop();
        }
        return VEHICLE_SELECTION;
    }
    else if (backSpacePressed){

        if (onMultiplayer){

            // Create a Linda driver compatible with Windows to make communicate with the Linda server
            LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");

            if (numberPlayersGroup > 1){
                for (int i = 2; i <= numberPlayersGroup; i++){

                    int idCode = groupDataPlayers[i - 1].getCodePlayer();
                    string name = groupDataPlayers[i - 1].getNickNamePlayer();

                    // Inform that the group is cancelled
                    Tuple t = Tuple("CANCELLED_CIRCUIT", nickNameGroupMultiplayer, to_string(idCode), nickNameMultiplayer, name);
                    winLindadriver.postNote(t);

                    // The to the member that the pulse has been received
                    t = Tuple("PULSE_RECEIVED", nickNameGroupMultiplayer, name, to_string(idCode));
                    winLindadriver.postNote(t);
                }
            }
            if (cancelledGroup){
                return MULTIPLAYER_NAME_GROUP;
            }
            else {
                return SELECTION_MODE_MULTIPLAYER;
            }
        }
        else {
            return RIVAL_TYPE_MENU;
        }
    }
    return EXIT;
}



void Game::showsDerramageDrivingFuryAnimation(Configuration& c, SoundPlayer& r){
    // Check if the game is Driving Fury or Demarrage
    if (typeOfGame == 3){

        // Store the position
        Text congratulationsText;
        congratulationsText.setString("MISSION COMPLETED!");
        congratulationsText.setCharacterSize(static_cast<unsigned int>(int(65.0f * c.screenScale)));
        congratulationsText.setFont(c.fontTimeToPlay);
        congratulationsText.setStyle(Text::Bold);
        congratulationsText.setFillColor(Color::White);
        congratulationsText.setOutlineColor(Color::Black);
        congratulationsText.setOutlineThickness(5.0f * c.screenScale);
        congratulationsText.setPosition((c.w.getSize().x / 2.f) - (congratulationsText.getLocalBounds().width / 2.f),
                                         c.w.getSize().y / 2.f - 15.f * c.screenScale);

        float elapsed1, elapsed2;
        Clock blinkClcok;
        Time blink_delay = seconds(0.5f);

        blinkClcok.restart().asSeconds();
        elapsed1 = blinkClcok.restart().asSeconds();
        bool blink = true;

        // Driving Fury
        r.soundEffects[96]->stop();
        r.soundEffects[96]->play();

        switch(typeOfVehicle){
            case 0:
                if (goalCar.getPosX() >= 0.7f){
                    player.setPosition(goalCar.getPosX() - 0.3f, player.getPosY() + 1);
                }
                else if (goalCar.getPosX() <= -0.7f) {
                    player.setPosition(goalCar.getPosX() + 0.3f, player.getPosY() + 1);
                }
                else {
                    player.setPosition(goalCar.getPosX() + 0.3f, player.getPosY() + 1);
                }
                break;
            case 1:
                if (goalCar.getPosX() >= 0.7f){
                    player2.setPosition(goalCar.getPosX() - 0.3f, player2.getPosY() + 1);
                }
                else if (goalCar.getPosX() <= -0.7f) {
                    player2.setPosition(goalCar.getPosX() + 0.3f, player2.getPosY() + 1);
                }
                else {
                    player2.setPosition(goalCar.getPosX() + 0.3f, player2.getPosY() + 1);
                }
                break;
            case 2:
                if (goalCar.getPosX() >= 0.7f){
                    player3.setPosition(goalCar.getPosX() - 0.3f, player3.getPosY() + 1);
                }
                else if (goalCar.getPosX() <= -0.7f) {
                    player3.setPosition(goalCar.getPosX() + 0.3f, player3.getPosY() + 1);
                }
                else {
                    player3.setPosition(goalCar.getPosX() + 0.3f, player3.getPosY() + 1);
                }
                break;
            case 3:
                if (goalCar.getPosX() >= 0.7f){
                    player4.setPosition(goalCar.getPosX() - 0.3f, player4.getPosY() + 1);
                }
                else if (goalCar.getPosX() <= -0.7f) {
                    player4.setPosition(goalCar.getPosX() + 0.3f, player4.getPosY() + 1);
                }
                else {
                    player4.setPosition(goalCar.getPosX() + 0.3f, player4.getPosY() + 1);
                }
                break;
            case 4:
                if (goalCar.getPosX() >= 0.7f){
                    player5.setPosition(goalCar.getPosX() - 0.3f, player5.getPosY() + 1);
                }
                else if (goalCar.getPosX() <= -0.7f) {
                    player5.setPosition(goalCar.getPosX() + 0.3f, player5.getPosY() + 1);
                }
                else {
                    player5.setPosition(goalCar.getPosX() + 0.3f, player5.getPosY() + 1);
                }
                break;
            case 5:
                if (goalCar.getPosX() >= 0.7f){
                    player6.setPosition(goalCar.getPosX() - 0.3f, player6.getPosY() + 1);
                }
                else if (goalCar.getPosX() <= -0.7f) {
                    player6.setPosition(goalCar.getPosX() + 0.3f, player6.getPosY() + 1);
                }
                else {
                    player6.setPosition(goalCar.getPosX() + 0.3f, player6.getPosY() + 1);
                }
        }

        // Until the sound stops
        while (r.soundEffects[96]->getStatus() != SoundSource::Stopped){

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    mtx.lock();
                    finalGame = true;
                    mtx.unlock();
                    timer0.join();
                    timer1.join();
                    exit(1);
                }
            }

            float positionX = player6.getPosX();
            float positionY = player6.getPosY();

            // Update camera
            currentMap->updateCamera(positionX, positionY - RECTANGLE);

            // Draw map
            c.w.clear();
            currentMap->drawLandScape(c, cars, rivals, typeOfGame, goalCar, displayGoalCarIndicator, (currentLandScape >= goalCarStage));

            switch(typeOfVehicle){
                case 0:
                    player.setPosition(player.getPosX(), player.getPosY() + 1);
                    break;
                case 1:
                    player2.setPosition(player2.getPosX(), player2.getPosY() + 1);
                    break;
                case 2:
                    player3.setPosition(player3.getPosX(), player3.getPosY() + 1);
                    break;
                case 3:
                    player4.setPosition(player4.getPosX(), player4.getPosY() + 1);
                    break;
                case 4:
                    player5.setPosition(player5.getPosX(), player5.getPosY() + 1);
                    break;
                case 5:
                    player6.setPosition(player6.getPosX(), player6.getPosY() + 1);
            }


            goalCar.setPosition(goalCar.getPosX(), goalCar.getPosY() + 1);

            switch(typeOfVehicle){
                case 0:
                    player.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                         currentMap->getElevation(player.getPosY()), currentMap->getTerrain(), false);
                    break;
                case 1:
                    player2.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                         currentMap->getElevation(player2.getPosY()), currentMap->getTerrain(), false);
                    break;
                case 2:
                    player3.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                         currentMap->getElevation(player3.getPosY()), currentMap->getTerrain(), false);
                    break;
                case 3:
                    player4.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                         currentMap->getElevation(player4.getPosY()), currentMap->getTerrain(), false);
                    break;
                case 4:
                    player5.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                         currentMap->getElevation(player5.getPosY()), currentMap->getTerrain(), false);
                    break;
                case 5:
                    player6.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                         currentMap->getElevation(player6.getPosY()), currentMap->getTerrain(), false);

            }

            goalCar.draw(Vehicle::Action::ACCELERATE, currentMap->getElevation(goalCar.getPosY()));


            elapsed2 = blinkClcok.getElapsedTime().asSeconds();

            // Change the color of the main text
            if (elapsed2 - elapsed1 >= blink_delay.asSeconds()) {
                blink = !blink;
                blinkClcok.restart();
            }
            if (blink) {
                congratulationsText.setFillColor(c.colorTexts[0]);
                congratulationsText.setOutlineColor(c.colorBorders[0]);
            }
            else {
                congratulationsText.setFillColor(Color::Transparent);
                congratulationsText.setOutlineColor(Color::Transparent);
            }

            c.w.draw(congratulationsText);

            Sprite bufferSprite(c.w.getTexture());
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
        }

        // Reproduce the reason of detention
        r.soundEffects[106]->stop();
        r.soundEffects[107]->stop();
        r.soundEffects[108]->stop();
        r.soundEffects[109]->stop();

        // Select a reason of detention
        int codeSound = rand_generator_int(106, 109);

        string reasonDetection1, reasonDetection2;

        switch(codeSound){
            case 106:
                reasonDetection1 = "OKAY YOU ARE UNDER ARREST ON";
                reasonDetection2 = "SUSPICION OF FIRST DEGREE MURDER";
                break;
            case 107:
                reasonDetection1 = "OKAY YOU ARE UNDER ARREST ON";
                reasonDetection2 = "SUSPICION OF SELLING DRUGS";
                break;
            case 108:
                reasonDetection1 = "OKAY YOU ARE UNDER ARREST ON";
                reasonDetection2 = "SUSPICION OF ARMED ROBBERY AND MURDER";
                break;
            case 109:
                reasonDetection1 = "OKAY YOU ARE UNDER ARREST ON SUSPICION";
                reasonDetection2 = "OF ESPIONAGE AND FIRST DEGREE MURDER";
        }

        // Store the position
        Text reasonDetentionText1;
        reasonDetentionText1.setString(reasonDetection1);
        reasonDetentionText1.setFont(c.fontTimeToPlay);
        reasonDetentionText1.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
        reasonDetentionText1.setStyle(Text::Bold);
        reasonDetentionText1.setFillColor(Color::White);
        reasonDetentionText1.setOutlineColor(Color::Black);
        reasonDetentionText1.setOutlineThickness(5.0f * c.screenScale);
        reasonDetentionText1.setPosition((c.w.getSize().x / 2.f) - (reasonDetentionText1.getLocalBounds().width / 2.f),
                                         c.w.getSize().y / 2.f - 75.f * c.screenScale);

        // Store the position
        Text reasonDetentionText2;
        reasonDetentionText2.setString(reasonDetection2);
        reasonDetentionText2.setFont(c.fontTimeToPlay);
        reasonDetentionText2.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
        reasonDetentionText2.setStyle(Text::Bold);
        reasonDetentionText2.setFillColor(Color::White);
        reasonDetentionText2.setOutlineColor(Color::Black);
        reasonDetentionText2.setOutlineThickness(5.0f * c.screenScale);
        reasonDetentionText2.setPosition((c.w.getSize().x / 2.f) - (reasonDetentionText2.getLocalBounds().width / 2.f),
                                         c.w.getSize().y / 2.f - 15.f * c.screenScale);

        for (int i = 0; i < 20; i++){

             // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    mtx.lock();
                    finalGame = true;
                    mtx.unlock();
                    timer0.join();
                    timer1.join();
                    exit(1);
                }
            }

            float positionX = 0.f, positionY = 0.f;

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
                    break;
                case 5:
                    positionX = player6.getPosX();
                    positionY = player6.getPosY();
            }

            // Update camera
            currentMap->updateCamera(positionX, positionY - RECTANGLE);

            // Draw map
            c.w.clear();
            currentMap->drawLandScape(c, cars, rivals, typeOfGame, goalCar, displayGoalCarIndicator, currentLandScape >= goalCarStage);

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
                    break;
                case 5:
                    player6.setPosition(player6.getPosX(), player6.getPosY() + 1);
                    player6.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                                 currentMap->getElevation(player6.getPosY()), currentMap->getTerrain(), false);
            }

            elapsed2 = blinkClcok.getElapsedTime().asSeconds();

            // Change the color of the main text
            if (elapsed2 - elapsed1 >= blink_delay.asSeconds()) {
                blink = !blink;
                blinkClcok.restart();
            }
            if (blink) {
                congratulationsText.setFillColor(c.colorTexts[0]);
                congratulationsText.setOutlineColor(c.colorBorders[0]);
            }
            else {
                congratulationsText.setFillColor(Color::Transparent);
                congratulationsText.setOutlineColor(Color::Transparent);
            }

            c.w.draw(congratulationsText);

            Sprite bufferSprite(c.w.getTexture());
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
        }

        // Reset the police car
        player6.setVehicle(typeOfGame);

        r.soundEffects[codeSound]->play();

        // Wait until the sound finishes
        // Until the sound stops
        while (r.soundEffects[codeSound]->getStatus() != SoundSource::Stopped){

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    mtx.lock();
                    finalGame = true;
                    mtx.unlock();
                    timer0.join();
                    timer1.join();
                    exit(1);
                }
            }

            // Draw map
            c.w.clear();
            currentMap->drawLandScape(c, cars, rivals, typeOfGame, goalCar, displayGoalCarIndicator, (currentLandScape >= goalCarStage));

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
                    break;
                case 5:
                    player6.setPosition(player6.getPosX(), player6.getPosY() + 1);
                    player6.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                                 currentMap->getElevation(player6.getPosY()), currentMap->getTerrain(), false);
            }

            goalCar.draw(Vehicle::Action::ACCELERATE, currentMap->getElevation(goalCar.getPosY()));

            c.w.draw(reasonDetentionText1);
            c.w.draw(reasonDetentionText2);

            Sprite bufferSprite(c.w.getTexture());
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
        }
    }
    else if (typeOfGame == 4){
        // Demarrage
        r.soundEffects[97]->stop();
        r.soundEffects[97]->play();

        // Store the position
        Text congratulationsText;
        congratulationsText.setString("MISSION COMPLETED!");
        congratulationsText.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
        congratulationsText.setFont(c.fontTimeToPlay);
        congratulationsText.setStyle(Text::Bold);
        congratulationsText.setFillColor(Color::White);
        congratulationsText.setOutlineColor(Color::Black);
        congratulationsText.setOutlineThickness(5.0f * c.screenScale);
        congratulationsText.setPosition((c.w.getSize().x / 2.f) - (congratulationsText.getLocalBounds().width / 2.f),
                                         c.w.getSize().y / 2.f - 15.f * c.screenScale);

        float elapsed1, elapsed2;
        Clock blinkClcok;
        Time blink_delay = seconds(0.5f);

        blinkClcok.restart().asSeconds();
        elapsed1 = blinkClcok.restart().asSeconds();
        bool blink = true;

        float positionX = 0.f, positionY = 0.f;

        // Until the sound stops
        while (r.soundEffects[97]->getStatus() != SoundSource::Stopped){

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    mtx.lock();
                    finalGame = true;
                    mtx.unlock();
                    timer0.join();
                    timer1.join();
                    exit(1);
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
                    break;
                case 5:
                    positionX = player6.getPosX();
                    positionY = player6.getPosY();
            }

            // Update camera
            currentMap->updateCamera(positionX, positionY - RECTANGLE);

            // Draw map
            c.w.clear();
            currentMap->drawLandScape(c, cars, rivals, typeOfGame, goalCar, displayGoalCarIndicator, (currentLandScape >= goalCarStage));

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
                    break;
                case 5:
                    player6.setPosition(player6.getPosX(), player6.getPosY() + 1);
                    player6.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                            currentMap->getElevation(player6.getPosY()), currentMap->getTerrain(), false);
            }

            elapsed2 = blinkClcok.getElapsedTime().asSeconds();

            // Change the color of the main text
            if (elapsed2 - elapsed1 >= blink_delay.asSeconds()) {
                blink = !blink;
                blinkClcok.restart();
            }
            if (blink) {
                congratulationsText.setFillColor(c.colorTexts[0]);
                congratulationsText.setOutlineColor(c.colorBorders[0]);
            }
            else {
                congratulationsText.setFillColor(Color::Transparent);
                congratulationsText.setOutlineColor(Color::Transparent);
            }

            c.w.draw(congratulationsText);

            Sprite bufferSprite(c.w.getTexture());
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
        }
    }
}



void Game::setMultiplayerMode(const int multiPlayerMode){
    modeMultiplayer = multiPlayerMode;
}




/**
 * Load the configuration of the player menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void Game::loadMultiplayerNameConfiguration(const string path, Configuration& c){

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
            c.backgroundMultiplayerNameMenu.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the player menu
            for (xml_node<> *panelProp = property->first_node(); panelProp; panelProp = panelProp->next_sibling()){
                // Check it is the node that contains the information of the background of the panel
                if ((string)panelProp->name() == "Background"){
                    // Get the background image of the menu
                    backgroundTexture = (string)panelProp->value();
                    c.backgroundMultiplayerNamePanel.loadFromFile(backgroundTexture);
                }
                // Check it is the node that contains the information of the color border of the panel
                else if ((string)panelProp->name() == "ColorBorder"){
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
                    // Store the color border of the panel
                    c.colorBorderPanelMultiplayerNameMenu = Color(colorRed, colorGreen, colorBlue);
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
                    c.contentTitleMultiplayerNameMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontTitleMultiplayerNameMenu.loadFromFile(fontPath);
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
                        c.colorTitleTextMultiplayerNameMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderMultiplayerNameMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
    }
    // The configuration file has been read
    c.multiplayerNameMenuRead = true;
}



State Game::introduceNameMultiplayer(Configuration& c, SoundPlayer& r){


    nickNameMultiplayer = "_";

    Event e;
    while(c.window.pollEvent(e));

     // The xml configuration file of the player menu has been read
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));

    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Read the player menu if it has not been read
    if (!c.multiplayerNameMenuRead){
        // Read the player menu xml configuration file
        string pathFile = "Data/Menus/MultiplayerNameMenu/Configuration/MultiplayerNameMenu.xml";
        loadMultiplayerNameConfiguration(pathFile, c);
    }

    // Control if the start key is pressed or not
    bool startPressed = false;

    // Control if the escape key has been pressed
    bool escapePressed = false;

    // Control if the nickname is valid or not
    bool nameValid = false;

    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Create a Linda driver compatible with Windows to make communicate with the Linda server
    LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");

    // While start and backspace have not been pressed
    while (!startPressed && !escapePressed) {

        // Make the textures repeated
        c.backgroundMultiplayerNameMenu.setRepeated(true);
        c.backgroundMultiplayerNamePanel.setRepeated(true);

        // Global rectangle of the background
        IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
        Sprite sprite(c.backgroundMultiplayerNameMenu, background);

        float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
        float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
        sprite.setScale(axis_x, axis_y);
        c.multiPlayerNameMenuBackground = sprite;

        // Creation of the panel rectangle of the menu
        RectangleShape shape;
        shape.setPosition((c.w.getSize().x / 2.f) - 250.0f * c.screenScale, c.w.getSize().y / 2.f - 170.0f * c.screenScale);
        shape.setSize(sf::Vector2f(492.0f * c.screenScale, 340.0f * c.screenScale));
        shape.setOutlineColor(c.colorBorderPanelMultiplayerNameMenu);
        shape.setOutlineThickness(5.0f * c.screenScale);
        shape.setTexture(&c.backgroundMultiplayerNamePanel, true);

        // Main Text of the menu
        Text mainText;
        mainText.setString(c.contentTitleMultiplayerNameMenu);
        mainText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        mainText.setFont(c.fontTitleMultiplayerNameMenu);
        mainText.setStyle(Text::Bold | Text::Underlined);
        mainText.setFillColor(c.colorTitleTextMultiplayerNameMenu);
        mainText.setOutlineColor(c.colorTitleBorderMultiplayerNameMenu);
        mainText.setOutlineThickness(5.0f * c.screenScale);
        mainText.setPosition((c.w.getSize().x / 2.f) - mainText.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f - 140.0f * c.screenScale);

        // Informative indjcators about how to change a controller
        Text info1;
        info1.setString("ENTER A NICKNAME OF UP TO EIGHT");
        info1.setFillColor(Color(10, 201, 235));
        info1.setOutlineColor(Color(3, 39, 8));
        info1.setOutlineThickness(3.0f * c.screenScale);
        info1.setCharacterSize(static_cast<unsigned int>(int(25.0f * c.screenScale)));
        info1.setStyle(Text::Bold);
        info1.setFont(c.fontTitleMultiplayerNameMenu);
        info1.setPosition(c.w.getSize().x / 2.f - info1.getLocalBounds().width / 2.f, c.w.getSize().y / 2.f - 60.0f * c.screenScale);
        c.w.draw(info1);

        Text info2;
        info2.setString("CHARACTERS AND PRESS START");
        info2.setFillColor(Color(10, 201, 235));
        info2.setOutlineColor(Color(3, 39, 8));
        info2.setCharacterSize(static_cast<unsigned int>(int(25.0f * c.screenScale)));
        info2.setOutlineThickness(3.0f * c.screenScale);
        info2.setStyle(Text::Bold);
        info2.setFont(c.fontTitleMultiplayerNameMenu);
        info2.setPosition(c.w.getSize().x / 2.f - info2.getLocalBounds().width / 2.f, c.w.getSize().y / 2.f - 30.0f * c.screenScale);
        c.w.draw(info2);

        // Number of letters introduced
        int lettersIntroduced = 0;

        Text playerName;
        playerName.setString(nickNameMultiplayer);
        playerName.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        playerName.setFont(c.fontTitleMultiplayerNameMenu);
        playerName.setStyle(Text::Bold);
        playerName.setFillColor(Color(64, 147, 225));
        playerName.setOutlineColor(Color::Black);
        playerName.setOutlineThickness(3.0f * c.screenScale);

        KeywordMapper kM = KeywordMapper();

        // Until the nickname of the player is not valid
        while(!nameValid && !escapePressed){

            // Until the start or escape keyword is not pressed
            while (!startPressed && !escapePressed) {

                // while there are pending events...
                if (c.window.pollEvent(e)) {
                    // Detect the possible events
                    if (e.type == Event::Closed){
                        // Complaining text
                        Text complainText;
                        complainText.setString("THIS BUTTON CANT'T BE USED NOW ");
                        complainText.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
                        complainText.setFont(c.fontTitleMultiplayerMenu);
                        complainText.setStyle(Text::Bold);
                        complainText.setFillColor(c.colorTitleTextMultiplayerMenu);
                        complainText.setOutlineColor(c.colorTitleBorderMultiplayerMenu);
                        complainText.setOutlineThickness(5.0f * c.screenScale);
                        if (c.isDefaultScreen){
                            complainText.setPosition(c.w.getSize().x / 2.f - complainText.getLocalBounds().width / 2.f,
                                                             c.w.getSize().y / 2.f + 220.0f * c.screenScale);
                        }
                        else {
                            complainText.setPosition((c.w.getSize().x / 2.f) - complainText.getLocalBounds().width / 2.f,
                                                      c.w.getSize().y / 2.f + 180.0f * c.screenScale);
                        }

                        for (int i = 0; i <= 120; i++){

                            Event e;
                            c.window.pollEvent(e);

                            // Draw the elements of the menu
                            c.w.draw(c.multiPlayerMenuBackground);
                            c.w.draw(shape);
                            c.w.draw(mainText);
                            c.w.draw(info1);
                            c.w.draw(info2);

                            playerName.setString(nickNameMultiplayer);
                            playerName.setPosition((c.w.getSize().x / 2.f) - playerName.getLocalBounds().width / 2.f,
                                                    c.w.getSize().y / 2.f + 80.0f * c.screenScale);

                            c.w.draw(playerName);
                            c.w.draw(complainText);

                            bufferSprite.setTexture(c.w.getTexture(), true);
                            c.w.display();
                            c.window.draw(bufferSprite);
                            c.window.display();
                        }
                    }
                    else if (e.type == Event::KeyPressed) {

                        if (lettersIntroduced < 8){
                            // Get code of the key
                            int code = e.key.code;
                            // Check if the key pressed is a letter or not
                            if (code >= 0 && code <= 35) {
                                lettersIntroduced++;
                                string keyLetter = kM.mapperIdKeyWord[code];
                                if (nickNameMultiplayer == "_") {
                                    nickNameMultiplayer = keyLetter + "_";
                                    r.soundEffects[116]->stop();
                                    r.soundEffects[116]->play();
                                }
                                else {
                                    if (lettersIntroduced == 8) {
                                        nickNameMultiplayer = nickNameMultiplayer.substr(0, nickNameMultiplayer.size() - 1);
                                        nickNameMultiplayer += keyLetter;
                                        r.soundEffects[116]->stop();
                                        r.soundEffects[116]->play();
                                    }
                                    else {
                                        nickNameMultiplayer = nickNameMultiplayer.substr(0, nickNameMultiplayer.size() - 1);
                                        nickNameMultiplayer += keyLetter + "_";
                                        r.soundEffects[116]->stop();
                                        r.soundEffects[116]->play();
                                    }
                                }
                            }
                            else {
                                r.soundEffects[3]->stop();
                                r.soundEffects[3]->play();
                            }
                        }
                        else {
                            r.soundEffects[3]->stop();
                            r.soundEffects[3]->play();
                        }
                    }
                }

                playerName.setString(nickNameMultiplayer);
                playerName.setPosition((c.w.getSize().x / 2.f) - playerName.getLocalBounds().width / 2.f,
                                        c.w.getSize().y / 2.f + 80.0f * c.screenScale);

                c.w.draw(c.multiPlayerMenuBackground);
                c.w.draw(shape);
                c.w.draw(mainText);
                c.w.draw(info1);
                c.w.draw(info2);
                c.w.draw(playerName);

                bufferSprite.setTexture(c.w.getTexture(), true);
                c.w.display();
                c.window.draw(bufferSprite);
                c.window.display();
                sleep(milliseconds(120));

                // Check if start has been pressed
                if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
                    // Check the name is not empty
                    if (lettersIntroduced > 0){
                        // Change the controllers of the car
                        startPressed = true;
                    }
                    else {
                        r.soundEffects[3]->stop();
                        r.soundEffects[3]->play();
                    }
                }
                // Check if backspace has been pressed
                else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {
                    // Change the controllers of the car
                    escapePressed = true;
                    r.soundEffects[11]->stop();
                    r.soundEffects[11]->play();
                }
            }
            if (startPressed){
                // Check if the nickname is used by another player
                bool found;

                // Eliminate the last character if it is not a full name
                if ((nickNameMultiplayer.size() < 8) ||
                    (nickNameMultiplayer.size() == 8 && nickNameMultiplayer.back() == '_'))
                {
                    nickNameMultiplayer.pop_back();
                }

                Tuple t = Tuple("NAME_PLAYER", nickNameMultiplayer);

                // Get in a tuple if the tuple desired exists
                Tuple s = winLindadriver.readNoteX(t, found);

                if (!found && s.get(1) == NF){
                    // The name id valid and is post noted
                    winLindadriver.postNote(t);
                    nameValid = true;

                    r.soundEffects[2]->stop();
                    r.soundEffects[2]->play();

                }
                else {
                    // Restart the name because it's invalid
                    lettersIntroduced = 0;
                    nickNameMultiplayer = "_";
                    startPressed = false;

                    // Display to the player that the name is invalid
                    Text invalidNickName;
                    invalidNickName.setString("INVALID PLAYER NICKNAME");
                    invalidNickName.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
                    invalidNickName.setFont(c.fontTitleMultiplayerNameMenu);
                    invalidNickName.setStyle(Text::Bold);
                    invalidNickName.setFillColor(Color::Red);
                    invalidNickName.setOutlineColor(Color::Black);
                    invalidNickName.setOutlineThickness(3.0f * c.screenScale);
                    invalidNickName.setPosition(c.w.getSize().x / 2.f - invalidNickName.getLocalBounds().width / 2.f,
                                                c.w.getSize().y / 2.f + 80.f * c.screenScale);

                    // Draw in the screen a few time
                    for (int i = 0; i <= 50; i++){
                        // Display the menu
                        c.w.draw(c.multiPlayerMenuBackground);
                        c.w.draw(shape);
                        c.w.draw(mainText);
                        c.w.draw(info1);
                        c.w.draw(info2);
                        c.w.draw(invalidNickName);

                        bufferSprite.setTexture(c.w.getTexture(), true);
                        c.w.display();
                        c.window.draw(bufferSprite);
                        c.window.display();
                        sleep(milliseconds(120));
                    }
                }
            }
        }
    }
    // Close connection with Linda server
    winLindadriver.stop();

    if (c.enablePixelArt) {
        if (c.isDefaultScreen){
            c.window.setView(View(Vector2f(DEFAULT_WIDTH / 4.0f, DEFAULT_HEIGHT / 4.0f),
                                  Vector2f(DEFAULT_WIDTH / 2.0f, DEFAULT_HEIGHT / 2.0f)));
        }
        else {
            c.window.setView(View(Vector2f(SCREEN_HD_WIDTH / 4.0f, SCREEN_HD_HEIGHT / 4.0f),
                                  Vector2f(SCREEN_HD_WIDTH / 2.0f, SCREEN_HD_HEIGHT / 2.0f)));
        }
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));
        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);
    }

    if(startPressed){

        // Store how to start the multiplayer game
        if (modeMultiplayer == 0){
            // Select create a group
            return MULTIPLAYER_NAME_GROUP;
        }
        else {
            // Select to join a group
            return SELECT_MULTIPLAYER_JOIN;
        }
    }
    else if (escapePressed) {
        return MULTIPLAYER_MENU;
    }
    return EXIT;
}



/**
 * Load the configuration of the player menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void Game::loadMultiplayerGroupConfiguration(const string path, Configuration& c){

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
            c.backgroundMultiplayerGroupMenu.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the player menu
            for (xml_node<> *panelProp = property->first_node(); panelProp; panelProp = panelProp->next_sibling()){
                // Check it is the node that contains the information of the background of the panel
                if ((string)panelProp->name() == "Background"){
                    // Get the background image of the menu
                    backgroundTexture = (string)panelProp->value();
                    c.backgroundMultiplayerGroupPanel.loadFromFile(backgroundTexture);
                }
                // Check it is the node that contains the information of the color border of the panel
                else if ((string)panelProp->name() == "ColorBorder"){
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
                    // Store the color border of the panel
                    c.colorBorderPanelMultiplayerGroupMenu = Color(colorRed, colorGreen, colorBlue);
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
                    c.contentTitleMultiplayerGroupMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontTitleMultiplayerGroupMenu.loadFromFile(fontPath);
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
                        c.colorTitleTextMultiplayerGroupMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderMultiplayerGroupMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
    }
    // The configuration file has been read
    c.multiplayerGroupMenuRead = true;
}



State Game::introduceGroupMultiplayer(Configuration& c, SoundPlayer& r){

    nickNameGroupMultiplayer = "_";

    Event e;
    while(c.window.pollEvent(e));

     // The xml configuration file of the player menu has been read
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));

    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Read the player menu if it has not been read
    if (!c.multiplayerGroupMenuRead){
        // Read the player menu xml configuration file
        string pathFile = "Data/Menus/MultiplayerGroupMenu/Configuration/MultiplayerGroupMenu.xml";
        loadMultiplayerGroupConfiguration(pathFile, c);
    }

    // Clear the data of possible players of old games
    groupDataPlayers.clear();

    // Control if the start key is pressed or not
    bool startPressed = false;

    // Control if the backspace key has been pressed
    bool escapePressed = false;

    // Control if the nickname is valid or not
    bool nameValid = false;

    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Create a Linda driver compatible with Windows to make communicate with the Linda server
    LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");

    // While start and backspace have not been pressed
    while (!startPressed && !escapePressed) {

        // Make the textures repeated
        c.backgroundMultiplayerGroupMenu.setRepeated(true);
        c.backgroundMultiplayerGroupPanel.setRepeated(true);

        // Global rectangle of the background
        IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
        Sprite sprite(c.backgroundMultiplayerGroupMenu, background);

        float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
        float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
        sprite.setScale(axis_x, axis_y);
        c.multiPlayerGroupMenuBackground = sprite;

        // Creation of the panel rectangle of the menu
        RectangleShape shape;
        shape.setPosition((c.w.getSize().x / 2.f) - 280.0f * c.screenScale, c.w.getSize().y / 2.f - 170.0f * c.screenScale);
        shape.setSize(sf::Vector2f(552.0f * c.screenScale, 340.0f * c.screenScale));
        shape.setOutlineColor(c.colorBorderPanelMultiplayerNameMenu);
        shape.setOutlineThickness(5.0f * c.screenScale);
        shape.setTexture(&c.backgroundMultiplayerGroupPanel, true);

        // Main Text of the menu
        Text mainText;
        mainText.setString(c.contentTitleMultiplayerGroupMenu);
        mainText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        mainText.setFont(c.fontTitleMultiplayerGroupMenu);
        mainText.setStyle(Text::Bold | Text::Underlined);
        mainText.setFillColor(c.colorTitleTextMultiplayerGroupMenu);
        mainText.setOutlineColor(c.colorTitleBorderMultiplayerGroupMenu);
        mainText.setOutlineThickness(5.0f * c.screenScale);
        mainText.setPosition((c.w.getSize().x / 2.f) - mainText.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f - 140.0f * c.screenScale);

        // Informative indjcators about how to change a controller
        Text info1;
        if (modeMultiplayer == 0){
            info1.setString("ENTER THE NICKNAME OF THE GROUP TO CREATE");
        }
        else {
            info1.setString("ENTER THE NICKNAME OF THE GROUP");
        }
        info1.setFillColor(Color(10, 201, 235));
        info1.setOutlineColor(Color(3, 39, 8));
        info1.setOutlineThickness(3.0f * c.screenScale);
        info1.setCharacterSize(static_cast<unsigned int>(int(25.0f * c.screenScale)));
        info1.setStyle(Text::Bold);
        info1.setFont(c.fontTitleMultiplayerGroupMenu);
        info1.setPosition(c.w.getSize().x / 2.f - info1.getLocalBounds().width / 2.f, c.w.getSize().y / 2.f - 60.0f * c.screenScale);
        c.w.draw(info1);

        Text info2;
        if (modeMultiplayer == 0){
            info2.setString("OF EIGHT CHARACTERS MAXIMUN AND PRESS START");
        }
        else {
            info2.setString("YOU WANT TO JOIN AND PRESS START");
        }
        info2.setFillColor(Color(10, 201, 235));
        info2.setOutlineColor(Color(3, 39, 8));
        info2.setCharacterSize(static_cast<unsigned int>(int(25.0f * c.screenScale)));
        info2.setOutlineThickness(3.0f * c.screenScale);
        info2.setStyle(Text::Bold);
        info2.setFont(c.fontTitleMultiplayerGroupMenu);
        info2.setPosition(c.w.getSize().x / 2.f - info2.getLocalBounds().width / 2.f, c.w.getSize().y / 2.f - 30.0f * c.screenScale);
        c.w.draw(info2);

        // Number of letters introduced
        int lettersIntroduced = 0;

        Text playerName;
        playerName.setString(nickNameGroupMultiplayer);
        playerName.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        playerName.setFont(c.fontTitleMultiplayerGroupMenu);
        playerName.setStyle(Text::Bold);
        playerName.setFillColor(Color(64, 147, 225));
        playerName.setOutlineColor(Color::Black);
        playerName.setOutlineThickness(3.0f * c.screenScale);

        KeywordMapper kM = KeywordMapper();

        // Until the nickname of the player is not valid
        while(!nameValid && !escapePressed){

            // Until the start keyword is not pressed
            while (!startPressed && !escapePressed) {

                // while there are pending events...
                if (c.window.pollEvent(e)) {
                    // Detect the possible events
                    if (e.type == Event::Closed){
                        // Complaining text
                        Text complainText;
                        complainText.setString("THIS BUTTON CANT'T BE USED NOW ");
                        complainText.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
                        complainText.setFont(c.fontTitleMultiplayerMenu);
                        complainText.setStyle(Text::Bold);
                        complainText.setFillColor(c.colorTitleTextMultiplayerMenu);
                        complainText.setOutlineColor(c.colorTitleBorderMultiplayerMenu);
                        complainText.setOutlineThickness(5.0f * c.screenScale);
                        if (c.isDefaultScreen){
                            complainText.setPosition(c.w.getSize().x / 2.f - complainText.getLocalBounds().width / 2.f,
                                                             c.w.getSize().y / 2.f + 220.0f * c.screenScale);
                        }
                        else {
                            complainText.setPosition((c.w.getSize().x / 2.f) - complainText.getLocalBounds().width / 2.f,
                                                      c.w.getSize().y / 2.f + 180.0f * c.screenScale);
                        }

                        for (int i = 0; i <= 120; i++){

                            Event e;
                            c.window.pollEvent(e);

                            // Draw the elements of the menu
                            c.w.draw(c.multiPlayerMenuBackground);
                            c.w.draw(shape);
                            c.w.draw(mainText);
                            c.w.draw(info1);
                            c.w.draw(info2);
                            c.w.draw(playerName);

                            playerName.setString(nickNameGroupMultiplayer);
                            playerName.setPosition((c.w.getSize().x / 2.f) - playerName.getLocalBounds().width / 2.f,
                                                    c.w.getSize().y / 2.f + 80.0f * c.screenScale);

                            c.w.draw(playerName);
                            c.w.draw(complainText);

                            bufferSprite.setTexture(c.w.getTexture(), true);
                            c.w.display();
                            c.window.draw(bufferSprite);
                            c.window.display();
                        }
                    }
                    else if (e.type == Event::KeyPressed) {

                        if (lettersIntroduced < 8){
                            // Get code of the key
                            int code = e.key.code;
                            // Check if the key pressed is a letter or not
                            if (code >= 0 && code <= 35) {
                                lettersIntroduced++;
                                string keyLetter = kM.mapperIdKeyWord[code];
                                if (nickNameGroupMultiplayer == "_") {
                                    nickNameGroupMultiplayer = keyLetter + "_";
                                    r.soundEffects[116]->stop();
                                    r.soundEffects[116]->play();
                                }
                                else {
                                    if (lettersIntroduced == 8) {
                                        nickNameGroupMultiplayer = nickNameGroupMultiplayer.substr(0, nickNameGroupMultiplayer.size() - 1);
                                        nickNameGroupMultiplayer += keyLetter;
                                        r.soundEffects[116]->stop();
                                        r.soundEffects[116]->play();
                                    }
                                    else {
                                        nickNameGroupMultiplayer = nickNameGroupMultiplayer.substr(0, nickNameGroupMultiplayer.size() - 1);
                                        nickNameGroupMultiplayer += keyLetter + "_";
                                        r.soundEffects[116]->stop();
                                        r.soundEffects[116]->play();
                                    }
                                }
                            }
                            else {
                                r.soundEffects[3]->stop();
                                r.soundEffects[3]->play();
                            }
                        }
                        else {
                            r.soundEffects[3]->stop();
                            r.soundEffects[3]->play();
                        }
                    }
                }

                playerName.setString(nickNameGroupMultiplayer);
                playerName.setPosition((c.w.getSize().x / 2.f) - playerName.getLocalBounds().width / 2.f,
                                        c.w.getSize().y / 2.f + 80.0f * c.screenScale);

                c.w.draw(c.multiPlayerMenuBackground);
                c.w.draw(shape);
                c.w.draw(mainText);
                c.w.draw(info1);
                c.w.draw(info2);
                c.w.draw(playerName);

                bufferSprite.setTexture(c.w.getTexture(), true);
                c.w.display();
                c.window.draw(bufferSprite);
                c.window.display();
                sleep(milliseconds(120));

                // Check if start has been pressed
                if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
                    // Change the controllers of the car
                    // Check the name is not empty
                    if (lettersIntroduced > 0){
                        // Change the controllers of the car
                        startPressed = true;
                    }
                    else {
                        r.soundEffects[3]->stop();
                        r.soundEffects[3]->play();
                    }
                }
                // Check if backspace has been pressed
                else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {
                    // Change the controllers of the car
                    escapePressed = true;
                    r.soundEffects[11]->stop();
                    r.soundEffects[11]->play();
                }
            }
            if (startPressed){
                // Check if the nickname is used by another player
                bool found;

                // Eliminate the last character if it is not a full name
                if (nickNameGroupMultiplayer.size() < 8 ||
                    (nickNameGroupMultiplayer.size() == 8 && nickNameGroupMultiplayer.back() == '_'))
                {
                    nickNameGroupMultiplayer.pop_back();
                }

                // Check if the player has selected to be joined
                if (modeMultiplayer != 1){

                    Tuple t = Tuple("NAME_GROUP", nickNameGroupMultiplayer);

                    // Get in a tuple if the tuple desired exists
                    Tuple s = winLindadriver.readNoteX(t, found);

                    if (!found && s.get(1) == NF){
                        // The name id valid and is post noted
                        winLindadriver.postNote(t);
                        nameValid = true;

                        r.soundEffects[2]->stop();
                        r.soundEffects[2]->play();
                    }
                    else {
                        // Restart the name because it's invalid
                        lettersIntroduced = 0;
                        nickNameGroupMultiplayer = "_";
                        startPressed = false;

                        // Display to the player that the name is invalid
                        Text invalidNickName;
                        invalidNickName.setString("INVALID GROUP NICKNAME");
                        invalidNickName.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
                        invalidNickName.setFont(c.fontTitleMultiplayerNameMenu);
                        invalidNickName.setStyle(Text::Bold);
                        invalidNickName.setFillColor(Color::Red);
                        invalidNickName.setOutlineColor(Color::Black);
                        invalidNickName.setOutlineThickness(3.0f * c.screenScale);
                        invalidNickName.setPosition(c.w.getSize().x / 2.f - invalidNickName.getLocalBounds().width / 2.f,
                                                    c.w.getSize().y / 2.f + 80.f * c.screenScale);

                        // Draw in the screen a few time
                        for (int i = 0; i <= 50; i++){
                            // Display the menu
                            c.w.draw(c.multiPlayerMenuBackground);
                            c.w.draw(shape);
                            c.w.draw(mainText);
                            c.w.draw(info1);
                            c.w.draw(info2);
                            c.w.draw(invalidNickName);

                            bufferSprite.setTexture(c.w.getTexture(), true);
                            c.w.display();
                            c.window.draw(bufferSprite);
                            c.window.display();
                            sleep(milliseconds(120));
                        }
                    }
                }
                else {
                    nameValid = true;
                }
            }
        }
    }

    if (c.enablePixelArt) {
        if (c.isDefaultScreen){
            c.window.setView(View(Vector2f(DEFAULT_WIDTH / 4.0f, DEFAULT_HEIGHT / 4.0f),
                                  Vector2f(DEFAULT_WIDTH / 2.0f, DEFAULT_HEIGHT / 2.0f)));
        }
        else {
            c.window.setView(View(Vector2f(SCREEN_HD_WIDTH / 4.0f, SCREEN_HD_HEIGHT / 4.0f),
                                  Vector2f(SCREEN_HD_WIDTH / 2.0f, SCREEN_HD_HEIGHT / 2.0f)));
        }
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));
        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);
    }

    if(startPressed){
        return CREATION_GROUPS_MULTIPLAYER;
    }
    else if (escapePressed) {
        // Store how to start the multi player game
        if (modeMultiplayer == 0){

            // Eliminate the group
            Tuple t = Tuple("NAME_PLAYER", nickNameMultiplayer);
            winLindadriver.removeNote(t);

            // Close connection with Linda server
            winLindadriver.stop();

            return MULTIPLAYER_NAME_PLAYER;
        }
        else {
            // Close connection with Linda server
            winLindadriver.stop();

            return SELECT_MULTIPLAYER_JOIN;
        }
    }
    return EXIT;
}




/**
 * Load the configuration of the player menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void Game::loadMultiplayerJoinGroupMenuConfiguration(const string path, Configuration& c){

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
            c.backgroundMultiplayerJoinGroupMenu.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the player menu
            for (xml_node<> *panelProp = property->first_node(); panelProp; panelProp = panelProp->next_sibling()){
                // Check it is the node that contains the information of the background of the panel
                if ((string)panelProp->name() == "Background"){
                    // Get the background image of the menu
                    backgroundTexture = (string)panelProp->value();
                    c.backgroundMultiplayerJoinGroupPanel.loadFromFile(backgroundTexture);
                }
                // Check it is the node that contains the information of the color border of the panel
                else if ((string)panelProp->name() == "ColorBorder"){
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
                    // Store the color border of the panel
                    c.colorBorderPanelMultiplayerJoinGroupMenu = Color(colorRed, colorGreen, colorBlue);
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
                    c.contentTitleMultiplayerJoinGroupMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontTitleMultiplayerJoinGroupMenu.loadFromFile(fontPath);
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
                        c.colorTitleTextMultiplayerJoinGroupMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderMultiplayerJoinGroupMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
        // Check if it is the node that the different buttons of the menu
        else if ((string)property->name() == "MenuButtons"){
            Color colorFont;
            // Iterate to get the information of the buttons of the player menu
            for (xml_node<> *buttonProp = property->first_node(); buttonProp; buttonProp = buttonProp->next_sibling()){
                // Get the font of the buttons
                if ((string)buttonProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)buttonProp->value();
                    c.fontMenuMultiplayerJoinGroupButtons.loadFromFile(fontPath);
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
                    c.colorFontMenuPlayerButtons = Color(colorRed, colorGreen, colorBlue);
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
                                    c.multiplayerMenuJoinGroupColorButtons.push_back(Color(colorRed, colorGreen, colorBlue));
                                }

                                // Creation of the button and addition to the vector
                                posX = c.w.getSize().x / 2.f - 110.0f * c.screenScale;
                                posY = c.w.getSize().y / 2.f - (53.0f - idButton * 123.f) * c.screenScale;
                                widthButton = 200.0f * c.screenScale;
                                heightButton = 50.0f * c.screenScale;

                                // Creation of the button
                                Button b = Button(posX, posY, widthButton, heightButton, c.fontMenuMultiplayerButtons,
                                                  contentButton, c.multiplayerMenuColorButtons[0], c.multiplayerMenuColorButtons[1],
                                                  c.colorFontMenuPlayerButtons, buttonState, c.screenScale);

                                c.multiplayerJoinGroupMenuButtons.push_back(b);
                                idButton++;
                            }
                        }
                    }
                }
            }
        }
    }
    // The player menu has been read correctly
    c.multiplayerJoinGroupMenuRead = true;
}



State Game::selectJoiningMode(Configuration& c, SoundPlayer& r){

    // The xml configuration file of the player menu has been read
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));

    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Read the player menu if it has not been read
    if (!c.multiplayerJoinGroupMenuRead){
        // Read the player menu xml configuration file
        string pathFile = "Data/Menus/MultiplayerJoinGroupMenu/Configuration/MultiplayerJoinGroupMenu.xml";
        loadMultiplayerJoinGroupMenuConfiguration(pathFile, c);
    }
    else {
        int numButtons = int(c.multiplayerJoinGroupMenuButtons.size());

        // Change the state of the first color
        Button b = Button(c.w.getSize().x / 2.f - 110.0f * c.screenScale, c.w.getSize().y / 2.f - 53.0f * c.screenScale,
                          200.0f * c.screenScale, 50.0f * c.screenScale, c.fontMenuMultiplayerButtons,
                          c.multiplayerJoinGroupMenuButtons[0].getTextButton(), c.multiplayerJoinGroupMenuButtons[0].getIdleColorButton(),
                          c.multiplayerJoinGroupMenuButtons[0].getHoverColorButton(), c.multiplayerJoinGroupMenuButtons[0].getFontColorButton(), 1,
                          c.screenScale);

        c.multiplayerJoinGroupMenuButtons[0] = b;

        // Eliminate the buttons of the right column
        for (int i = 1; i < numButtons; i++){
            // Change the state of the first color
            Button b = Button(c.w.getSize().x / 2.f - 110.0f * c.screenScale, c.w.getSize().y / 2.f - (53.0f - i * 123.f) * c.screenScale,
                              200.0f * c.screenScale, 50.0f * c.screenScale, c.fontMenuMultiplayerButtons,
                              c.multiplayerJoinGroupMenuButtons[i].getTextButton(), c.multiplayerJoinGroupMenuButtons[i].getIdleColorButton(),
                              c.multiplayerJoinGroupMenuButtons[i].getHoverColorButton(), c.multiplayerJoinGroupMenuButtons[i].getFontColorButton(), 0,
                              c.screenScale);

            c.multiplayerJoinGroupMenuButtons[i] = b;
        }
    }

    // Clear the data of possible players of old games
    groupDataPlayers.clear();

    // Control if the start key is pressed or not
    bool startPressed = false;

    // Control if the backspace key has been pressed
    bool backSpacePressed = false;

    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Control the option selected by the user
    int optionSelected = 0;

    // While start and backspace have not been pressed
    while (!startPressed && !backSpacePressed) {

        // Make the textures repeated
        c.backgroundMultiplayerJoinGroupMenu.setRepeated(true);
        c.backgroundMultiplayerJoinGroupPanel.setRepeated(true);

        // Global rectangle of the background
        IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
        Sprite sprite(c.backgroundMultiplayerJoinGroupMenu, background);

        float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
        float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
        sprite.setScale(axis_x, axis_y);
        c.multiPlayerMenuJoinGroupBackground = sprite;

        // Creation of the panel rectangle of the menu
        RectangleShape shape;
        shape.setPosition((c.w.getSize().x / 2.f) - 180.0f * c.screenScale, c.w.getSize().y / 2.f - 170.0f * c.screenScale);
        shape.setSize(sf::Vector2f(350.0f * c.screenScale, 340.0f * c.screenScale));
        shape.setOutlineColor(c.colorBorderPanelMultiplayerMenu);
        shape.setOutlineThickness(5.0f * c.screenScale);
        shape.setTexture(&c.backgroundMultiplayerJoinGroupPanel, true);

        // Main Text of the menu
        Text mainText;
        mainText.setString(c.contentTitleMultiplayerJoinGroupMenu);
        mainText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        mainText.setFont(c.fontTitleMultiplayerMenu);
        mainText.setStyle(Text::Bold | Text::Underlined);
        mainText.setFillColor(c.colorTitleTextMultiplayerJoinGroupMenu);
        mainText.setOutlineColor(c.colorTitleBorderMultiplayerJoinGroupMenu);
        mainText.setOutlineThickness(5.0f * c.screenScale);
        mainText.setPosition((c.w.getSize().x / 2.f) - mainText.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f - 140.0f * c.screenScale);

        // Until the start keyword is not pressed
        while (!startPressed && !backSpacePressed) {

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)){
                if (e.type == Event::Closed){
                    // Complaining text
                    Text complainText;
                    complainText.setString("THIS BUTTON CANT'T BE USED NOW ");
                    complainText.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
                    complainText.setFont(c.fontTitleMultiplayerMenu);
                    complainText.setStyle(Text::Bold);
                    complainText.setFillColor(c.colorTitleTextMultiplayerMenu);
                    complainText.setOutlineColor(c.colorTitleBorderMultiplayerMenu);
                    complainText.setOutlineThickness(5.0f * c.screenScale);
                    if (c.isDefaultScreen){
                            complainText.setPosition(c.w.getSize().x / 2.f - complainText.getLocalBounds().width / 2.f,
                                                             c.w.getSize().y / 2.f + 220.0f * c.screenScale);
                        }
                        else {
                            complainText.setPosition((c.w.getSize().x / 2.f) - complainText.getLocalBounds().width / 2.f,
                                                      c.w.getSize().y / 2.f + 180.0f * c.screenScale);
                        }

                    for (int i = 0; i <= 120; i++){

                        Event e;
                        c.window.pollEvent(e);

                        // Draw the elements of the menu
                        c.w.draw(c.multiPlayerMenuJoinGroupBackground);
                        c.w.draw(shape);
                        c.w.draw(mainText);
                        c.w.draw(complainText);

                         // Show the buttons of the menu
                        for (int i = 0; i < (int)c.multiplayerJoinGroupMenuButtons.size(); i++) {
                            c.multiplayerJoinGroupMenuButtons.at(i).render(&c.w);
                        }

                        bufferSprite.setTexture(c.w.getTexture(), true);
                        c.w.display();
                        c.window.draw(bufferSprite);
                        c.window.display();
                    }
                }
            }

            // Check if the up or down cursor keys have been pressed or not
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Down)) {
                // Up cursor pressed and change the soundtrack selected in the list
                if (optionSelected != int(c.multiplayerJoinGroupMenuButtons.size() - 1)) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected++;
                    c.multiplayerJoinGroupMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    c.multiplayerJoinGroupMenuButtons[optionSelected - 1].setButtonState(BUTTON_IDLE);
                }
            }
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Up)) {
                // Down cursor pressed and change the soundtrack selected in the list
                if (optionSelected != 0) {
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected--;
                    // Change the color appearance of both buttons
                    c.multiplayerJoinGroupMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    c.multiplayerJoinGroupMenuButtons[optionSelected + 1].setButtonState(BUTTON_IDLE);
                }
            }

            c.w.draw(c.multiPlayerMenuJoinGroupBackground);
            c.w.draw(shape);
            c.w.draw(mainText);

             // Show the buttons of the menu
            for (int i = 0; i < (int)c.multiplayerJoinGroupMenuButtons.size(); i++) {
                c.multiplayerJoinGroupMenuButtons.at(i).render(&c.w);
            }

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
            sleep(milliseconds(120));

            // Check if start has been pressed
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
                // Change the controllers of the car
                startPressed = true;
                r.soundEffects[2]->stop();
                r.soundEffects[2]->play();
            }
            // Check if backspace has been pressed
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {
                // Change the controllers of the car
                backSpacePressed = true;
                r.soundEffects[11]->stop();
                r.soundEffects[11]->play();
            }
        }
    }

    if (c.enablePixelArt) {
        if (c.isDefaultScreen){
            c.window.setView(View(Vector2f(DEFAULT_WIDTH / 4.0f, DEFAULT_HEIGHT / 4.0f),
                                  Vector2f(DEFAULT_WIDTH / 2.0f, DEFAULT_HEIGHT / 2.0f)));
        }
        else {
            c.window.setView(View(Vector2f(SCREEN_HD_WIDTH / 4.0f, SCREEN_HD_HEIGHT / 4.0f),
                                  Vector2f(SCREEN_HD_WIDTH / 2.0f, SCREEN_HD_HEIGHT / 2.0f)));
        }
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));
        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);
    }

    if(startPressed){
        // Store how to start the multiplayer game
        if (optionSelected == 0){
            // The player joins to a particular group
            randomMultiplayerJoined = false;

            return MULTIPLAYER_NAME_GROUP;
        }
        else {
            // The player joins to a random group
            randomMultiplayerJoined = true;
            return CREATION_GROUPS_MULTIPLAYER;
        }
    }
    else if (backSpacePressed) {

        // Create a Linda driver compatible with Windows to make communicate with the Linda server
        LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");

        Tuple t = Tuple("NAME_PLAYER", nickNameMultiplayer);
        winLindadriver.removeNote(t);

        // Close connection with Linda server
        winLindadriver.stop();

        return MULTIPLAYER_NAME_PLAYER;
    }
    return EXIT;
}



void Game::capturerOfPlayers(bool& fullGroup){

    // Store locally the number of players of the group created by the player
    int numPlayers;

    // Store locally the names of the players
    string namePlayer;

    // Create a Linda driver compatible with Windows to make communicate with the Linda server
    LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");

    // Until the group is full or start key is not pressed
    while (!fullGroup){

        // Receive possible tuples of the players
        mtx3.lock();
        numPlayers = numberPlayersGroup;
        mtx3.unlock();

        string newNickName;

        // Check if there is any player that wants to be joined to the group
        Tuple t = Tuple("JOIN_GROUP", nickNameGroupMultiplayer, "?B", "?C");
        Tuple r = winLindadriver.removeNote(t);

        // Increment the number of players in the group
        mtx3.lock();
        numberPlayersGroup++;
        numPlayers = numberPlayersGroup;
        mtx3.unlock();

        newNickName = r.get(4);

        // Send confirmation to enter in the group
        t = Tuple("ACCEPTED_PLAYER", nickNameGroupMultiplayer, to_string(numberPlayersGroup), newNickName);
        winLindadriver.postNote(t);

        // Insert the data of the new player of the group
        MultiplayerData m = MultiplayerData(numPlayers, newNickName);
        mtx3.lock();
        groupDataPlayers.push_back(m);
        mtx3.unlock();

        // Send to the rest of the players all the members in the group
        for (int i = 2; i <= numPlayers; i++){

            mtx3.lock();
            string name = groupDataPlayers[i - 1].getNickNamePlayer();
            mtx3.unlock();

            // Post note each member of the group
            Tuple t = Tuple("CLEAR_PLAYERS", nickNameGroupMultiplayer, to_string(i), nickNameMultiplayer, name);
            winLindadriver.postNote(t);

            // Iterate throughout the players
            for (int j = 1; j <= numPlayers; j++){

                mtx3.lock();
                namePlayer = groupDataPlayers[j - 1].getNickNamePlayer();
                mtx3.unlock();

                // Post note each member of the group
                Tuple t = Tuple("PLAYER_GROUP", nickNameGroupMultiplayer, to_string(j), namePlayer, name);
                winLindadriver.postNote(t);
            }
        }

        // Check if the group is completed or not
        if (numPlayers < 8){
            // Create the tuple that represents the creation of a new group
            t = Tuple("CREATE_GROUP", nickNameGroupMultiplayer, to_string(numPlayers), "TRUE");
            winLindadriver.postNote(t);
        }
        else {
            // Alert that the group is closed
            Tuple t = Tuple("CREATE_GROUP", nickNameGroupMultiplayer, to_string(numPlayers), "FALSE");
            winLindadriver.postNote(t);

            // Alarm to the rest of the members that the group is completed
            mtx3.lock();
            for (MultiplayerData m : groupDataPlayers){
                int idCode = m.getCodePlayer();
                string name = m.getNickNamePlayer();

                // Inform that the group is cancelled
                Tuple t = Tuple("COMPLETED_GROUP", nickNameGroupMultiplayer, to_string(idCode), nickNameMultiplayer, name);
                winLindadriver.postNote(t);
            }
            fullGroup = true;
            mtx3.unlock();
        }
    }
    // Close connection between thread and Linda server
    winLindadriver.stop();
}



void Game::capturerOfGroups(bool& success, bool& fail){

    // Create a Linda driver compatible with Windows to make communicate with the Linda server
    LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");

    // Control if a player can join to the group that he wants
    bool canBeJoined;

    // Control if the join process has ended correctly
    bool joinedWell = false;

    // Control if the escape pressed has been pressed
    while (!joinedWell && !fail){

        Tuple t;

        if (randomMultiplayerJoined){
            // Create the tuple that represents an attempt to join to a group
            t = Tuple("CREATE_GROUP", "?Z", "?X", "TRUE");
        }
        else {
            // Create the tuple that represents an attempt to join to a group
            t = Tuple("CREATE_GROUP", nickNameGroupMultiplayer, "?X", "?H");
        }

        // Remove note the tuple that represents the group to be joined
        Tuple r = winLindadriver.removeNote(t);

        // Check if the players has joined randomly and store the nickname of the group
        if (randomMultiplayerJoined){
            nickNameGroupMultiplayer = r.get(2);
            canBeJoined = true;
        }
        else {
            // Check if the new player can be joined
            if (r.get(4) == "TRUE"){
                canBeJoined = true;
            }
            else {
                canBeJoined = false;
            }
        }

        if (canBeJoined){
            // Get the number of players
            string numPlayers = r.get(3);

            // Receives the tuple to be joined to the group and sends a solicitation
            t = Tuple("JOIN_GROUP", nickNameGroupMultiplayer, numPlayers, nickNameMultiplayer);

            // Post note the solicitation to join to the group
            winLindadriver.postNote(t);

            // Wait until the permission is conceded
            t = Tuple("ACCEPTED_PLAYER", nickNameGroupMultiplayer, "?Y", nickNameMultiplayer);
            r = winLindadriver.removeNote(t);

            mtx3.lock();
            numberPlayersGroup = stoi(r.get(3));
            codePlayerInGroup = numberPlayersGroup;
            mtx3.unlock();

            // Success join
            joinedWell = true;
        }
        else {
            // Fail join
            mtx3.lock();
            fail = true;
            mtx3.unlock();

            // Post note the group
            winLindadriver.postNote(r);
        }
    }
    // Ask to the owner of the group the rest of members until the group in closed
    if (!fail){
        while (!success){
            Tuple t = Tuple("?X", nickNameGroupMultiplayer, "?Z", "?A", nickNameMultiplayer);
            Tuple r = winLindadriver.removeNote(t);

            if (r.get(1) == "PLAYER_GROUP"){
                // Get the id code and the nick name of each player
                int codePlayer = stoi(r.get(3));
                string namePlayer = r.get(4);

                // Insert the data of the new player of the group
                MultiplayerData m = MultiplayerData(codePlayer, namePlayer);
                mtx3.lock();
                groupDataPlayers.push_back(m);
                mtx3.unlock();
            }
            else if (r.get(1) == "CLOSED_GROUP" || r.get(1) == "COMPLETED_GROUP"){
                mtx3.lock();
                success = true;
                mtx3.unlock();
            }
            else if (r.get(1) == "CANCELLED_GROUP"){
                mtx3.lock();
                fail = true;
                mtx3.unlock();
            }
            else if (r.get(1) == "CLEAR_PLAYERS"){
                mtx3.lock();
                groupDataPlayers.clear();
                mtx3.unlock();
            }
        }
    }
    // Close connection between thread and Linda server
    winLindadriver.stop();
}



State Game::creationOfGroups(Configuration& c, SoundPlayer& r){

    // Control the players in the group
    int localPlayersGroup = 0;

    // Create a Linda driver compatible with Windows to make communicate with the Linda server
    LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");

    // Check if the player has selected create or join to a group
    if (modeMultiplayer == 0){

        numberPlayersGroup = 1;

     // The xml configuration file of the player menu has been read
        c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                              Vector2f(c.window.getSize().x, c.window.getSize().y)));
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));

        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

        // Read the player menu if it has not been read
        if (!c.multiplayerMembersGroupMenuRead){
            // Read the player menu xml configuration file
            string pathFile = "Data/Menus/MultiplayerMembersGroupMenu/Configuration/MultiplayerMembersGroupMenu.xml";
            loadMultiplayerMemberGroupMenuConfiguration(pathFile, c);
        }

        c.w.clear(Color(0, 0, 0));
        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

        // Make the textures repeated
        c.backgroundMultiplayerMembersGroupMenu.setRepeated(true);
        c.backgroundMultiplayerMembersGroupPanel.setRepeated(true);

        // Global rectangle of the background
        IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
        Sprite sprite(c.backgroundMultiplayerMembersGroupMenu, background);

        float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
        float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
        sprite.setScale(axis_x, axis_y);
        c.multiPlayerMenuMembersGroupBackground = sprite;

        // Creation of the panel rectangle of the menu
        RectangleShape shape;
        shape.setPosition((c.w.getSize().x / 2.f) - 250.0f * c.screenScale, c.w.getSize().y / 2.f - 240.0f * c.screenScale);
        shape.setSize(sf::Vector2f(494.0f * c.screenScale, 480.0f * c.screenScale));
        shape.setOutlineColor(c.colorBorderPanelMultiplayerMenu);
        shape.setOutlineThickness(5.0f * c.screenScale);
        shape.setTexture(&c.backgroundMultiplayerMembersGroupPanel, true);

        // Main Text of the menu
        Text mainText;
        mainText.setString(c.contentTitleMultiplayerMembersGroupMenu + " " + nickNameGroupMultiplayer);
        mainText.setCharacterSize(static_cast<unsigned int>(int(37.0f * c.screenScale)));
        mainText.setFont(c.fontTitleMultiplayerMembersGroupMenu);
        mainText.setStyle(Text::Bold | Text::Underlined);
        mainText.setFillColor(c.colorTitleTextMultiplayerMembersGroupMenu);
        mainText.setOutlineColor(c.colorTitleBorderMultiplayerMembersGroupMenu);
        mainText.setOutlineThickness(5.0f * c.screenScale);
        mainText.setPosition((c.w.getSize().x / 2.f) - mainText.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f - 225.0f * c.screenScale);

        Text playerName;
        playerName.setCharacterSize(static_cast<unsigned int>(int(28.0f * c.screenScale)));
        playerName.setFont(c.fontTitleMultiplayerMembersGroupMenu);
        playerName.setStyle(Text::Bold);
        playerName.setFillColor(c.colorTitleTextMultiplayerMembersGroupMenu);
        playerName.setOutlineColor(c.colorTitleBorderMultiplayerMembersGroupMenu);
        playerName.setOutlineThickness(5.0f * c.screenScale);


        Text info1;
        info1.setString("PRESS START TO CREATE THE GROUP OR");
        info1.setFillColor(Color(10, 201, 235));
        info1.setOutlineColor(Color(3, 39, 8));
        info1.setOutlineThickness(3.0f * c.screenScale);
        info1.setCharacterSize(static_cast<unsigned int>(int(27.0f * c.screenScale)));
        info1.setStyle(Text::Bold);
        info1.setFont(c.fontTitleMultiplayerMembersGroupMenu);
        info1.setPosition(c.w.getSize().x / 2.f - info1.getLocalBounds().width / 2.f, c.w.getSize().y / 2.f - 170.0f * c.screenScale);

        Text info2;
        info2.setString("PRESS ESC TO CANCEL THE GROUP");
        info2.setFillColor(Color(10, 201, 235));
        info2.setOutlineColor(Color(3, 39, 8));
        info2.setOutlineThickness(3.0f * c.screenScale);
        info2.setCharacterSize(static_cast<unsigned int>(int(27.0f * c.screenScale)));
        info2.setStyle(Text::Bold);
        info2.setFont(c.fontTitleMultiplayerMembersGroupMenu);
        info2.setPosition(c.w.getSize().x / 2.f - info2.getLocalBounds().width / 2.f, c.w.getSize().y / 2.f - 140.0f * c.screenScale);

        // Draw the rectangle indicator
        CircleShape square(10 * c.screenScale, 4);
        square.setFillColor(c.colorIndicatorInsideMultiplayerMembersGroupMenu);
        square.setOutlineColor(c.colorIndicatorBorderMultiplayerMembersGroupMenu);
        square.setOutlineThickness(2.0f * c.screenScale);
        square.setRotation(90);


        codePlayerInGroup = 1;

        // Create the tuple that represents the creation of a new group
        Tuple t = Tuple("CREATE_GROUP", nickNameGroupMultiplayer, to_string(numberPlayersGroup), "TRUE");

        MultiplayerData m = MultiplayerData(numberPlayersGroup, nickNameMultiplayer);
        groupDataPlayers.push_back(m);

        // Post note in the Linda server a new group
        winLindadriver.postNote(t);

        // Control if the owner of the group presses start or not
        bool startPressed = false;

        // Control if the owner of the group presses escape or not
        bool escapePressed = false;

        // Control the reproduction of the challenge sound
        bool soundChallenge = false;

        // Control if the group is full of members
        bool fullGroup = false, checkingFullGroup = false;

        // Throw a thread that controls the incorporation of new players
        capturerPlayers = thread(capturerOfPlayers, this, ref(fullGroup));
        capturerPlayers.detach();

        r.soundEffects[117]->stop();
        r.soundEffects[117]->play();

        // Permit to the other players join to the group
        while (!startPressed && !escapePressed && !checkingFullGroup){
            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)){
                if (e.type == Event::Closed){
                    // Complaining text
                    Text complainText;
                    complainText.setString("THIS BUTTON CANT'T BE USED NOW ");
                    complainText.setCharacterSize(static_cast<unsigned int>(int(45.0f * c.screenScale)));
                    complainText.setFont(c.fontTitleMultiplayerMenu);
                    complainText.setStyle(Text::Bold);
                    complainText.setFillColor(c.colorTitleTextMultiplayerMenu);
                    complainText.setOutlineColor(c.colorTitleBorderMultiplayerMenu);
                    complainText.setOutlineThickness(5.0f * c.screenScale);
                    if (c.isDefaultScreen){
                        complainText.setPosition(c.w.getSize().x / 2.f - complainText.getLocalBounds().width / 2.f,
                                                         c.w.getSize().y / 2.f + 220.0f * c.screenScale);
                    }
                    else {
                        complainText.setPosition((c.w.getSize().x / 2.f) - complainText.getLocalBounds().width / 2.f,
                                                  c.w.getSize().y / 2.f + 180.0f * c.screenScale);
                    }

                    mtx3.lock();
                    vector<MultiplayerData> players(groupDataPlayers);
                    mtx3.unlock();

                    int numPlayers = players.size();

                    for (int i = 0; i <= 120; i++){

                        Event e;
                        c.window.pollEvent(e);

                        c.w.draw(c.multiPlayerMenuMembersGroupBackground);
                        c.w.draw(shape);
                        c.w.draw(mainText);
                        c.w.draw(info1);
                        c.w.draw(info2);
                        c.w.draw(complainText);

                        if (numPlayers > 0){
                            for (int i = 1; i <= numPlayers; i++){

                                playerName.setString(players[i - 1].getNickNamePlayer());
                                playerName.setPosition((c.w.getSize().x / 2.f) - 80.f * c.screenScale,
                                                       (c.w.getSize().y / 2.f - 125.0f) + (40.f * i) * c.screenScale);

                                square.setPosition((c.w.getSize().x / 2.f) - 95.f * c.screenScale,
                                                       (c.w.getSize().y / 2.f - 113.0f) + (40.f * i) * c.screenScale);

                                c.w.draw(playerName);
                                c.w.draw(square);
                            }
                        }

                        bufferSprite.setTexture(c.w.getTexture(), true);
                        c.w.display();
                        c.window.draw(bufferSprite);
                        c.window.display();
                    }
                }
            }

            mtx3.lock();
            checkingFullGroup = fullGroup;
            mtx3.unlock();

            // Check if start has been pressed
            if ((c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) || checkingFullGroup) {

                startPressed = true;

                r.soundEffects[2]->stop();
                r.soundEffects[2]->play();

                // Force kill of the thread that captures more players to be joined in the group
                capturerPlayers.~thread();

                // Create the tuple that represents the creation of a new group
                Tuple t = Tuple("CREATE_GROUP", nickNameGroupMultiplayer, to_string(numberPlayersGroup), "?X");
                Tuple r = winLindadriver.removeNote(t);

                // Alert that the group is closed
                r = Tuple("CREATE_GROUP", nickNameGroupMultiplayer, to_string(numberPlayersGroup), "FALSE");
                winLindadriver.postNote(r);


                if (numberPlayersGroup == 1){

                    Tuple t = Tuple("NAME_GROUP", nickNameGroupMultiplayer);
                    winLindadriver.removeNote(t);

                    return MULTIPLAYER_NAME_GROUP;
                }

                if (!checkingFullGroup){
                    // Alert to the members of the group that the group is completed
                    for (int i = 2; i <= numberPlayersGroup; i++){
                        int idCode = groupDataPlayers[i - 1].getCodePlayer();
                        string name = groupDataPlayers[i - 1].getNickNamePlayer();

                        // Inform that the group is cancelled
                        Tuple t = Tuple("CLOSED_GROUP", nickNameGroupMultiplayer, to_string(idCode), nickNameMultiplayer, name);
                        winLindadriver.postNote(t);
                    }
                }
            }
            // Check if escape has been pressed
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {

                escapePressed = true;

                r.soundEffects[11]->stop();
                r.soundEffects[11]->play();

                // Force kill of the thread that captures more players to be joined in the group
                capturerPlayers.~thread();

                // Create the tuple that represents the creation of a new group
                Tuple t = Tuple("CREATE_GROUP", nickNameGroupMultiplayer, to_string(numberPlayersGroup), "?X");
                Tuple r = winLindadriver.removeNote(t);

                if (numberPlayersGroup > 1){
                    for (int i = 2; i <= numberPlayersGroup; i++){

                        int idCode = groupDataPlayers[i - 1].getCodePlayer();
                        string name = groupDataPlayers[i - 1].getNickNamePlayer();

                        // Inform that the group is cancelled
                        Tuple t = Tuple("CANCELLED_GROUP", nickNameGroupMultiplayer, to_string(idCode), nickNameMultiplayer, name);
                        winLindadriver.postNote(t);
                    }
                }
            }

            // Display the menu on the screen
            c.w.clear();
            c.w.draw(c.multiPlayerMenuMembersGroupBackground);
            c.w.draw(shape);
            c.w.draw(mainText);
            c.w.draw(info1);
            c.w.draw(info2);

            mtx3.lock();
            vector<MultiplayerData> players(groupDataPlayers);
            mtx3.unlock();

            int numPlayers = players.size();

            // Check if the number of players has increased
            if (localPlayersGroup < numPlayers){
                // Reproduce the sound of a new player joined and store the current players
                localPlayersGroup = numPlayers;
                r.soundEffects[120]->stop();
                r.soundEffects[120]->play();
            }

            if (numPlayers > 0){
                for (int i = 1; i <= numPlayers; i++){

                    playerName.setString(players[i - 1].getNickNamePlayer());
                    playerName.setPosition((c.w.getSize().x / 2.f) - 80.f * c.screenScale,
                                           (c.w.getSize().y / 2.f - 125.0f) + (40.f * i) * c.screenScale);

                    square.setPosition((c.w.getSize().x / 2.f) - 95.f * c.screenScale,
                                           (c.w.getSize().y / 2.f - 113.0f) + (40.f * i) * c.screenScale);

                    c.w.draw(playerName);
                    c.w.draw(square);
                }
                if (!soundChallenge && numPlayers != 1){
                    soundChallenge = true;
                    r.soundEffects[118]->stop();
                    r.soundEffects[118]->play();
                }
            }

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
            sleep(milliseconds(120));
        }
        if (escapePressed){

            Tuple t = Tuple("NAME_GROUP", nickNameGroupMultiplayer);
            winLindadriver.removeNote(t);

            // Close connection with Linda server
            winLindadriver.stop();

            return MULTIPLAYER_NAME_GROUP;
        }
    }
    else {

        // Join to a group
        if (!randomMultiplayerJoined){

            // Throw a thread to capture a group to be joined
            bool escapePressed = false;

            // Control if the join has ended bad
            bool fail = false;

            // Control if the join has ended bad
            bool success = false;

            // Local variables to control the result of join
            bool checkingFail;

            // The xml configuration file of the player menu has been read
            c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                                  Vector2f(c.window.getSize().x, c.window.getSize().y)));
            c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                       static_cast<unsigned int>(c.window.getView().getSize().y));

            c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

            // Read the player menu if it has not been read
            if (!c.multiplayerMembersGroupMenuRead){
                // Read the player menu xml configuration file
                string pathFile = "Data/Menus/MultiplayerMembersGroupMenu/Configuration/MultiplayerMembersGroupMenu.xml";
                loadMultiplayerMemberGroupMenuConfiguration(pathFile, c);
            }

            c.w.clear(Color(0, 0, 0));
            Sprite bufferSprite(c.w.getTexture());
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();

            // Make the textures repeated
            c.backgroundMultiplayerMembersGroupMenu.setRepeated(true);
            c.backgroundMultiplayerMembersGroupPanel.setRepeated(true);

            // Global rectangle of the background
            IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
            Sprite sprite(c.backgroundMultiplayerMembersGroupMenu, background);

            float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
            float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
            sprite.setScale(axis_x, axis_y);
            c.multiPlayerMenuMembersGroupBackground = sprite;

            // Creation of the panel rectangle of the menu
            RectangleShape shape;
            shape.setPosition((c.w.getSize().x / 2.f) - 250.0f * c.screenScale, c.w.getSize().y / 2.f - 240.0f * c.screenScale);
            shape.setSize(sf::Vector2f(494.0f * c.screenScale, 480.0f * c.screenScale));
            shape.setOutlineColor(c.colorBorderPanelMultiplayerMenu);
            shape.setOutlineThickness(5.0f * c.screenScale);
            shape.setTexture(&c.backgroundMultiplayerMembersGroupPanel, true);

            // Main Text of the menu
            Text mainText;
            mainText.setCharacterSize(static_cast<unsigned int>(int(37.0f * c.screenScale)));
            mainText.setFont(c.fontTitleMultiplayerMembersGroupMenu);
            mainText.setStyle(Text::Bold | Text::Underlined);
            mainText.setFillColor(c.colorTitleTextMultiplayerMembersGroupMenu);
            mainText.setOutlineColor(c.colorTitleBorderMultiplayerMembersGroupMenu);
            mainText.setOutlineThickness(5.0f * c.screenScale);

            Text playerName;
            playerName.setCharacterSize(static_cast<unsigned int>(int(28.0f * c.screenScale)));
            playerName.setFont(c.fontTitleMultiplayerMembersGroupMenu);
            playerName.setStyle(Text::Bold);
            playerName.setFillColor(c.colorTitleTextMultiplayerMembersGroupMenu);
            playerName.setOutlineColor(c.colorTitleBorderMultiplayerMembersGroupMenu);
            playerName.setOutlineThickness(5.0f * c.screenScale);

            Text info;
            info.setString("PRESS ESCAPE TO LEAVE THE GROUP");
            info.setFillColor(Color(10, 201, 235));
            info.setOutlineColor(Color(3, 39, 8));
            info.setOutlineThickness(3.0f * c.screenScale);
            info.setCharacterSize(static_cast<unsigned int>(int(27.0f * c.screenScale)));
            info.setStyle(Text::Bold);
            info.setFont(c.fontTitleMultiplayerMembersGroupMenu);
            info.setPosition(c.w.getSize().x / 2.f - info.getLocalBounds().width / 2.f, c.w.getSize().y / 2.f - 150.0f * c.screenScale);

            // Draw the rectangle indicator
            CircleShape square(10 * c.screenScale, 4);
            square.setFillColor(c.colorIndicatorInsideMultiplayerMembersGroupMenu);
            square.setOutlineColor(c.colorIndicatorBorderMultiplayerMembersGroupMenu);
            square.setOutlineThickness(2.0f * c.screenScale);
            square.setRotation(90);

            // Throw a thread that controls the incorporation of new players
            capturerGroups = thread(capturerOfGroups, this, ref(success), ref(fail));
            capturerGroups.detach();

            // Permit to the other players join to the group
            while (!escapePressed && !success){

                // Detect the possible events
                Event e{};
                while (c.window.pollEvent(e)){
                    if (e.type == Event::Closed){
                                                // Complaining text
                        Text complainText;
                        complainText.setString("THIS BUTTON CANT'T BE USED NOW ");
                        complainText.setCharacterSize(static_cast<unsigned int>(int(45.0f * c.screenScale)));
                        complainText.setFont(c.fontTitleMultiplayerMenu);
                        complainText.setStyle(Text::Bold);
                        complainText.setFillColor(c.colorTitleTextMultiplayerMenu);
                        complainText.setOutlineColor(c.colorTitleBorderMultiplayerMenu);
                        complainText.setOutlineThickness(5.0f * c.screenScale);
                        if (c.isDefaultScreen){
                            complainText.setPosition(c.w.getSize().x / 2.f - complainText.getLocalBounds().width / 2.f,
                                                             c.w.getSize().y / 2.f + 220.0f * c.screenScale);
                        }
                        else {
                            complainText.setPosition((c.w.getSize().x / 2.f) - complainText.getLocalBounds().width / 2.f,
                                                      c.w.getSize().y / 2.f + 180.0f * c.screenScale);
                        }

                        mtx3.lock();
                        vector<MultiplayerData> players(groupDataPlayers);
                        mtx3.unlock();

                        int numPlayers = players.size();

                        for (int i = 0; i <= 120; i++){

                            Event e;
                            c.window.pollEvent(e);

                            c.w.draw(c.multiPlayerMenuMembersGroupBackground);
                            c.w.draw(shape);
                            c.w.draw(mainText);
                            c.w.draw(info);
                            c.w.draw(complainText);

                            if (numPlayers > 0){
                                for (int i = 1; i <= numPlayers; i++){

                                    playerName.setString(players[i - 1].getNickNamePlayer());
                                    playerName.setPosition((c.w.getSize().x / 2.f) - 80.f * c.screenScale,
                                                           (c.w.getSize().y / 2.f - 125.0f) + (40.f * i) * c.screenScale);

                                    square.setPosition((c.w.getSize().x / 2.f) - 95.f * c.screenScale,
                                                           (c.w.getSize().y / 2.f - 113.0f) + (40.f * i) * c.screenScale);

                                    c.w.draw(playerName);
                                    c.w.draw(square);
                                }
                            }

                            bufferSprite.setTexture(c.w.getTexture(), true);
                            c.w.display();
                            c.window.draw(bufferSprite);
                            c.window.display();
                        }
                    }
                }

                mtx3.lock();
                checkingFail = fail;
                mtx3.unlock();

                if (checkingFail){
                    return MULTIPLAYER_NAME_GROUP;
                }

                // Check if start has been pressed
                if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {

                    escapePressed = true;

                    r.soundEffects[11]->stop();
                    r.soundEffects[11]->play();

                    capturerPlayers.~thread();
                }

                mainText.setString(c.contentTitleMultiplayerMembersGroupMenu + " " + nickNameGroupMultiplayer);
                mainText.setPosition((c.w.getSize().x / 2.f) - mainText.getLocalBounds().width / 2.f,
                                      c.w.getSize().y / 2.f - 225.0f * c.screenScale);

                // Display the menu on the screen
                c.w.clear();
                c.w.draw(c.multiPlayerMenuMembersGroupBackground);
                c.w.draw(shape);
                c.w.draw(mainText);
                c.w.draw(info);

                mtx3.lock();
                vector<MultiplayerData> players(groupDataPlayers);
                mtx3.unlock();

                int numPlayers = players.size();

                // Check if the number of players has increased
                if (localPlayersGroup < numPlayers){
                    // Reproduce the sound of a new player joined and store the current players
                    localPlayersGroup = numPlayers;
                    r.soundEffects[119]->stop();
                    r.soundEffects[119]->play();
                }

                if (numPlayers > 0){
                    for (int i = 1; i <= numPlayers; i++){

                        playerName.setString(players[i - 1].getNickNamePlayer());
                        playerName.setPosition((c.w.getSize().x / 2.f) - 80.f * c.screenScale,
                                               (c.w.getSize().y / 2.f - 125.0f) + (40.f * i) * c.screenScale);

                        square.setPosition((c.w.getSize().x / 2.f) - 95.f * c.screenScale,
                                               (c.w.getSize().y / 2.f - 113.0f) + (40.f * i) * c.screenScale);

                        c.w.draw(playerName);
                        c.w.draw(square);
                    }
                }

                bufferSprite.setTexture(c.w.getTexture(), true);
                c.w.display();
                c.window.draw(bufferSprite);
                c.window.display();
                sleep(milliseconds(120));
            }
            // Check the reason of leaving the loop
            if (escapePressed){
                return MULTIPLAYER_NAME_GROUP;
            }
        }
        else {

            // Control if the join has ended bad
            bool fail = false, success = false;

            // Control if the escape key has been pressed
            bool escapePressed = false;

            // The xml configuration file of the player menu has been read
            c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                                  Vector2f(c.window.getSize().x, c.window.getSize().y)));
            c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                       static_cast<unsigned int>(c.window.getView().getSize().y));

            c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

            // Read the player menu if it has not been read
            if (!c.multiplayerMembersGroupMenuRead){
                // Read the player menu xml configuration file
                string pathFile = "Data/Menus/MultiplayerMembersGroupMenu/Configuration/MultiplayerMembersGroupMenu.xml";
                loadMultiplayerMemberGroupMenuConfiguration(pathFile, c);
            }

            c.w.clear(Color(0, 0, 0));
            Sprite bufferSprite(c.w.getTexture());
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();

            // Make the textures repeated
            c.backgroundMultiplayerMembersGroupMenu.setRepeated(true);
            c.backgroundMultiplayerMembersGroupPanel.setRepeated(true);

            // Global rectangle of the background
            IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
            Sprite sprite(c.backgroundMultiplayerMembersGroupMenu, background);

            float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
            float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
            sprite.setScale(axis_x, axis_y);
            c.multiPlayerMenuMembersGroupBackground = sprite;

            // Creation of the panel rectangle of the menu
            RectangleShape shape;
            shape.setPosition((c.w.getSize().x / 2.f) - 250.0f * c.screenScale, c.w.getSize().y / 2.f - 240.0f * c.screenScale);
            shape.setSize(sf::Vector2f(494.0f * c.screenScale, 480.0f * c.screenScale));
            shape.setOutlineColor(c.colorBorderPanelMultiplayerMenu);
            shape.setOutlineThickness(5.0f * c.screenScale);
            shape.setTexture(&c.backgroundMultiplayerMembersGroupPanel, true);

            // Main Text of the menu
            Text mainText;
            mainText.setString(c.contentTitleMultiplayerMembersGroupMenu + " " + nickNameGroupMultiplayer);
            mainText.setCharacterSize(static_cast<unsigned int>(int(37.0f * c.screenScale)));
            mainText.setFont(c.fontTitleMultiplayerMembersGroupMenu);
            mainText.setStyle(Text::Bold | Text::Underlined);
            mainText.setFillColor(c.colorTitleTextMultiplayerMembersGroupMenu);
            mainText.setOutlineColor(c.colorTitleBorderMultiplayerMembersGroupMenu);
            mainText.setOutlineThickness(5.0f * c.screenScale);
            mainText.setPosition((c.w.getSize().x / 2.f) - mainText.getLocalBounds().width / 2.f,
                                  c.w.getSize().y / 2.f - 225.0f * c.screenScale);

            Text playerName;
            playerName.setCharacterSize(static_cast<unsigned int>(int(28.0f * c.screenScale)));
            playerName.setFont(c.fontTitleMultiplayerMembersGroupMenu);
            playerName.setStyle(Text::Bold);
            playerName.setFillColor(c.colorTitleTextMultiplayerMembersGroupMenu);
            playerName.setOutlineColor(c.colorTitleBorderMultiplayerMembersGroupMenu);
            playerName.setOutlineThickness(5.0f * c.screenScale);

            Text info;
            info.setString("PRESS ESCAPE TO LEAVE THE GROUP");
            info.setFillColor(Color(10, 201, 235));
            info.setOutlineColor(Color(3, 39, 8));
            info.setOutlineThickness(3.0f * c.screenScale);
            info.setCharacterSize(static_cast<unsigned int>(int(27.0f * c.screenScale)));
            info.setStyle(Text::Bold);
            info.setFont(c.fontTitleMultiplayerMembersGroupMenu);
            info.setPosition(c.w.getSize().x / 2.f - info.getLocalBounds().width / 2.f, c.w.getSize().y / 2.f - 150.0f * c.screenScale);

            // Draw the rectangle indicator
            CircleShape square(10 * c.screenScale, 4);
            square.setFillColor(c.colorIndicatorInsideMultiplayerMembersGroupMenu);
            square.setOutlineColor(c.colorIndicatorBorderMultiplayerMembersGroupMenu);
            square.setOutlineThickness(2.0f * c.screenScale);
            square.setRotation(90);

            // Throw a thread that controls the incorporation of new players
            capturerGroups = thread(capturerOfGroups, this, ref(success), ref(fail));
            capturerGroups.detach();

            // Permit to the other players join to the group
            while (!escapePressed && !success && !fail){

                // Detect the possible events
                Event e{};
                while (c.window.pollEvent(e)){
                    if (e.type == Event::Closed){
                        Text complainText;
                        complainText.setString("THIS BUTTON CANT'T BE USED NOW ");
                        complainText.setCharacterSize(static_cast<unsigned int>(int(45.0f * c.screenScale)));
                        complainText.setFont(c.fontTitleMultiplayerMenu);
                        complainText.setStyle(Text::Bold);
                        complainText.setFillColor(c.colorTitleTextMultiplayerMenu);
                        complainText.setOutlineColor(c.colorTitleBorderMultiplayerMenu);
                        complainText.setOutlineThickness(5.0f * c.screenScale);
                        complainText.setPosition((c.w.getSize().x / 2.f) - complainText.getLocalBounds().width / 2.f,
                                                  c.w.getSize().y / 2.f + 260.f * c.screenScale);

                        for (int i = 0; i <= 120; i++){

                            Event e;
                            c.window.pollEvent(e);

                            // Draw the elements of the menu
                            c.w.draw(c.multiPlayerMenuMembersGroupBackground);
                            c.w.draw(shape);
                            c.w.draw(mainText);
                            c.w.draw(info);
                            c.w.draw(complainText);

                            mtx3.lock();
                            vector<MultiplayerData> players(groupDataPlayers);
                            mtx3.unlock();

                            int numPlayers = players.size();

                            if (numPlayers > 0){
                                for (int i = 1; i <= numPlayers; i++){

                                    playerName.setString(players[i - 1].getNickNamePlayer());
                                    playerName.setPosition((c.w.getSize().x / 2.f) - 80.f * c.screenScale,
                                                           (c.w.getSize().y / 2.f - 125.0f) + (40.f * i) * c.screenScale);

                                    square.setPosition((c.w.getSize().x / 2.f) - 95.f * c.screenScale,
                                                           (c.w.getSize().y / 2.f - 113.0f) + (40.f * i) * c.screenScale);

                                    c.w.draw(playerName);
                                    c.w.draw(square);
                                }
                            }

                            bufferSprite.setTexture(c.w.getTexture(), true);
                            c.w.display();
                            c.window.draw(bufferSprite);
                            c.window.display();
                        }
                    }
                }

                // Check if start has been pressed
                if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {

                    escapePressed = true;

                    r.soundEffects[11]->stop();
                    r.soundEffects[11]->play();

                    capturerGroups.~thread();
                }

                mainText.setString(c.contentTitleMultiplayerMembersGroupMenu + " " + nickNameGroupMultiplayer);
                mainText.setPosition((c.w.getSize().x / 2.f) - mainText.getLocalBounds().width / 2.f,
                                      c.w.getSize().y / 2.f - 225.0f * c.screenScale);

                // Display the menu on the screen
                c.w.clear();
                c.w.draw(c.multiPlayerMenuMembersGroupBackground);
                c.w.draw(shape);
                c.w.draw(mainText);
                c.w.draw(info);

                mtx3.lock();
                vector<MultiplayerData> players(groupDataPlayers);
                mtx3.unlock();

                int numPlayers = players.size();

                // Check if the number of players has increased
                if (localPlayersGroup < numPlayers){
                    // Reproduce the sound of a new player joined and store the current players
                    localPlayersGroup = numPlayers;
                    r.soundEffects[119]->stop();
                    r.soundEffects[119]->play();
                }

                if (numPlayers > 0){
                    for (int i = 1; i <= numPlayers; i++){

                        playerName.setString(players[i - 1].getNickNamePlayer());
                        playerName.setPosition((c.w.getSize().x / 2.f) - 80.f * c.screenScale,
                                               (c.w.getSize().y / 2.f - 125.0f) + (40.f * i) * c.screenScale);

                        square.setPosition((c.w.getSize().x / 2.f) - 95.f * c.screenScale,
                                               (c.w.getSize().y / 2.f - 113.0f) + (40.f * i) * c.screenScale);

                        c.w.draw(playerName);
                        c.w.draw(square);
                    }
                }

                bufferSprite.setTexture(c.w.getTexture(), true);
                c.w.display();
                c.window.draw(bufferSprite);
                c.window.display();
                sleep(milliseconds(120));
            }
            // Check the reason of leaving the loop
            if (escapePressed){
                return SELECT_MULTIPLAYER_JOIN;
            }
        }
    }
    // Close connection between thread and Linda server
    winLindadriver.stop();

    // Control the pixel art flag to construct the view of the screen
    if (c.enablePixelArt) {
        if (c.isDefaultScreen){
            c.window.setView(View(Vector2f(DEFAULT_WIDTH / 4.0f, DEFAULT_HEIGHT / 4.0f),
                                  Vector2f(DEFAULT_WIDTH / 2.0f, DEFAULT_HEIGHT / 2.0f)));
        }
        else {
            c.window.setView(View(Vector2f(SCREEN_HD_WIDTH / 4.0f, SCREEN_HD_HEIGHT / 4.0f),
                                  Vector2f(SCREEN_HD_WIDTH / 2.0f, SCREEN_HD_HEIGHT / 2.0f)));
        }
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));
        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);
    }
    // The group has been formed correctly
    onMultiplayer = true;
    return SELECTION_MODE_MULTIPLAYER;
}



/**
 * Load the configuration of the game modes multi player menu stored in its xml configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void Game::loadGameModesMultiplayerMenuConfiguration(const string path, Configuration& c){

    // Open the xml file of the game modes menu
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
            c.gameModesMultiplayerMenuBackground.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the player menu
            for (xml_node<> *panelProp = property->first_node(); panelProp; panelProp = panelProp->next_sibling()){
                // Check it is the node that contains the information of the background of the panel
                if ((string)panelProp->name() == "Background"){
                    // Get the background image of the menu
                    backgroundTexture = (string)panelProp->value();
                    c.gameModesMultiplayerMenuPanelBack.loadFromFile(backgroundTexture);
                }
                // Check it is the node that contains the information of the color border of the panel
                else if ((string)panelProp->name() == "ColorBorder"){
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
                    // Store the color border of the panel
                    c.colorBorderPanelGameModeMultiplayerMenu = Color(colorRed, colorGreen, colorBlue);
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
                    c.contentTitleGameModeMultiplayerMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontGameModeMultiplayerMenu.loadFromFile(fontPath);
                }
                // Get color text of the title
                else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                    // Get the kind of color to process
                    colorKind = (string)titleProp->name();
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the game modes menu
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
                        c.colorTitleTextGameModeMultiplayerMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderGameModeMultiplayerMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
        // Check if it is the node that stores the information panel of the buttons
        else if ((string)property->name() == "DescriptionPanel"){
            // Iterate to get the information of the description panel
            for (xml_node<> *descriptionProp = property->first_node(); descriptionProp; descriptionProp = descriptionProp->next_sibling()){
                // Get the kind of color to process
                colorKind = (string)descriptionProp->name();
                // Get the border color of the panel
                int colorRed = 0, colorGreen = 0, colorBlue = 0;
                // Iterate to get the information of the game modes menu
                for (xml_node<> *colorChannel = descriptionProp->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
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
                if (colorKind == "ColorPanelInside"){
                    c.colorDescriptionPanelInsideGameModeMultiplayerMenu = Color(colorRed, colorGreen, colorBlue);
                }
                // Check if it is the color of the border
                else if (colorKind == "ColorPanelBorder"){
                    c.colorDescriptionPanelBorderGameModeMultiplayerMenu = Color(colorRed, colorGreen, colorBlue);
                }
            }
        }
         // Check if it is the node that the different buttons of the menu
        else if ((string)property->name() == "MenuButtons"){
            // Iterate to get the information of the buttons of the game modes menu
            for (xml_node<> *buttonProp = property->first_node(); buttonProp; buttonProp = buttonProp->next_sibling()){
                // Get the font of the buttons
                if ((string)buttonProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)buttonProp->value();
                    c.fontMenuGameModeMultiplayerButtons.loadFromFile(fontPath);
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
                    c.colorFontMenuGameModesMultiplayerButtons = Color(colorRed, colorGreen, colorBlue);
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
                                    // Iterate to get the information of the game modes menu
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
                            }
                            else if ((string)button->name() == "Description"){
                                // Creation of the button and addition to the vector
                                // Creation of the button and addition to the vector
                                posX = c.w.getSize().x / 2.f - 280.0f * c.screenScale;
                                posY = c.w.getSize().y / 2.f - (149.0f - idButton * 150.f) * c.screenScale;
                                widthButton = 200.0f * c.screenScale;
                                heightButton = 40.0f * c.screenScale;

                                // Creation of the button
                                Button b = Button(posX, posY, widthButton, heightButton, c.fontGameModeMultiplayerMenu,
                                                  contentButton, colorButtons[0], colorButtons[1], c.colorFontMenuGameModesMultiplayerButtons,
                                                  buttonState, c.screenScale);

                                // Process the description text of the button
                                b.proccessDescription(button);
                                c.gameModeMenuMultiplayerButtons.push_back(b);
                                idButton++;
                            }
                        }
                    }
                }
            }
        }
    }
    // The game nodes menu has been read correctly
    c.gameModesMultiplayerMenuRead = true;
}



State Game::selectionModeMultiplayer(Configuration& c, SoundPlayer& r){
    if (modeMultiplayer == 0){

        // Prepare the screen to display the game modes menu
        c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                              Vector2f(c.window.getSize().x, c.window.getSize().y)));
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));
        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

        // Read the game modes menu if it has not been read
        if (!c.gameModesMultiplayerMenuRead){
            string path = "Data/Menus/GameModesMultiplayerMenu/Configuration/GameModesMultiplayerMenu.xml";
            loadGameModesMultiplayerMenuConfiguration(path, c);
        }
        else {
            int numButtons = int(c.gameModeMenuMultiplayerButtons.size());

            // Description of the button
            vector<string> descriptionButton;

            // Change the state of the first color
            Button b = Button(c.w.getSize().x / 2.f - 280.0f * c.screenScale, c.w.getSize().y / 2.f - 149.0f * c.screenScale,
                              200.0f * c.screenScale, 40.0f * c.screenScale, c.fontMenuGameModeMultiplayerButtons, c.gameModeMenuMultiplayerButtons[0].getTextButton(),
                              c.gameModeMenuMultiplayerButtons[0].getIdleColorButton(), c.gameModeMenuMultiplayerButtons[0].getHoverColorButton(),
                              c.gameModeMenuMultiplayerButtons[0].getFontColorButton(), 1, c.screenScale);

            // Get the description of the button
            descriptionButton = c.gameModeMenuMultiplayerButtons[0].getDescriptionButton();
            b.setDescriptionButton(descriptionButton);

            c.gameModeMenuMultiplayerButtons[0] = b;

            // Eliminate the buttons of the right column
            for (int i = 1; i < numButtons; i++){
                // Change the state of the first color
                Button b = Button(c.w.getSize().x / 2.f - 280.0f * c.screenScale, c.w.getSize().y / 2.f - (149.0f - i * 150.f) * c.screenScale,
                                  200.0f * c.screenScale, 40.0f * c.screenScale, c.fontMenuGameModeMultiplayerButtons, c.gameModeMenuMultiplayerButtons[i].getTextButton(),
                                  c.gameModeMenuMultiplayerButtons[i].getIdleColorButton(), c.gameModeMenuMultiplayerButtons[i].getHoverColorButton(),
                                  c.gameModeMenuMultiplayerButtons[i].getFontColorButton(), 0, c.screenScale);

                // Get the description of the button
                descriptionButton = c.gameModeMenuMultiplayerButtons[i].getDescriptionButton();
                b.setDescriptionButton(descriptionButton);

                c.gameModeMenuMultiplayerButtons[i] = b;
            }
        }


        // Control if the circuit has been selected
        bool gameModeSelected = false;

        // Canceled group
        bool cancelledGroup = false;

        bool escape = false;

        // Throw the thread that control the pulses of the group guests
        guestPulses = thread(controlGuestPulses, this, ref(gameModeSelected), ref(cancelledGroup), ref(escape));

        // Control if the start key is pressed or not
        bool startPressed = false;

        // Control if the escape key is pressed or not
        bool escapePressed = false;

        c.w.clear(Color(0, 0, 0));
        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

        // Game selected by the user
        int optionSelected;

        // While start and escape are not been pressed
        while (!startPressed && !escapePressed) {

            // Make the textures repeated
            c.gameModesMultiplayerMenuBackground.setRepeated(true);
            c.gameModesMultiplayerMenuPanelBack.setRepeated(true);

            // Global rectangle of the background
            IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
            Sprite sprite(c.gameModesMultiplayerMenuBackground, background);
            float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
            float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
            sprite.setScale(axis_x, axis_y);
            c.sGameModesMultiplayerBackground = sprite;

            // Creation of the panel rectangle of the menu
            RectangleShape shape;
            shape.setPosition((c.w.getSize().x / 2.f) - 350.0f * c.screenScale, c.w.getSize().y / 2.f - 250.0f * c.screenScale);
            shape.setSize(sf::Vector2f(710.0f * c.screenScale, 500.0f * c.screenScale));
            shape.setOutlineColor(c.colorBorderPanelGameModeMultiplayerMenu);
            shape.setOutlineThickness(5.0f * c.screenScale);
            shape.setTexture(&c.gameModesMultiplayerMenuPanelBack, true);

            // Creation of the description panel of the buttons
            RectangleShape panelButton;
            panelButton.setPosition((c.w.getSize().x / 2.f) + 20.0f * c.screenScale, c.w.getSize().y / 2.f - 149.0f * c.screenScale);
            panelButton.setSize(sf::Vector2f(300.0f * c.screenScale, 339.0f * c.screenScale));
            panelButton.setFillColor(c.colorDescriptionPanelInsideGameModeMultiplayerMenu);
            panelButton.setOutlineColor(c.colorDescriptionPanelBorderGameModeMultiplayerMenu);
            panelButton.setOutlineThickness(3.0f * c.screenScale);

            // Main Text of the menu
            Text mainText;
            mainText.setString(c.contentTitleGameModeMultiplayerMenu);
            mainText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
            mainText.setFont(c.fontGameModeMultiplayerMenu);
            mainText.setStyle(Text::Bold | Text::Underlined);
            mainText.setFillColor(c.colorTitleTextGameModeMultiplayerMenu);
            mainText.setOutlineColor(c.colorTitleBorderGameModeMultiplayerMenu);
            mainText.setOutlineThickness(5.0f * c.screenScale);
            mainText.setPosition((c.w.getSize().x / 2.f) - mainText.getLocalBounds().width / 2.f,
                                  c.w.getSize().y / 2.f - 230.0f * c.screenScale);

            // Text description of the buttons
            Text descriptionText;
            descriptionText.setStyle(Text::Bold);
            descriptionText.setFillColor(c.colorFontMenuGameModesMultiplayerButtons);
            descriptionText.setCharacterSize(25 * c.screenScale);
            descriptionText.setFont(c.fontMenuGameModeMultiplayerButtons);

            // All buttons of the menu have been created correctly

            // Control the option selected by the user
            optionSelected = 0;

            // Until the start keyword or escape keyword are not pressed
            while (!startPressed && !escapePressed) {

                // Detect the possible events
                Event e{};
                while (c.window.pollEvent(e)){
                    if (e.type == Event::Closed){
                        // Complaining text
                        Text complainText;
                        complainText.setString("THIS BUTTON CANT'T BE USED NOW ");
                        complainText.setCharacterSize(static_cast<unsigned int>(int(45.0f * c.screenScale)));
                        complainText.setFont(c.fontTitleMultiplayerMenu);
                        complainText.setStyle(Text::Bold);
                        complainText.setFillColor(c.colorTitleTextMultiplayerMenu);
                        complainText.setOutlineColor(c.colorTitleBorderMultiplayerMenu);
                        complainText.setOutlineThickness(5.0f * c.screenScale);
                        complainText.setPosition((c.w.getSize().x / 2.f) - complainText.getLocalBounds().width / 2.f,
                                                  c.w.getSize().y / 2.f + 260.0f * c.screenScale);

                        for (int i = 0; i <= 120; i++){

                            Event e;
                            c.window.pollEvent(e);

                            // Draw the elements of the menu
                            c.w.draw(c.sGameModesMultiplayerBackground);
                            c.w.draw(shape);
                            c.w.draw(panelButton);
                            c.w.draw(mainText);
                            c.w.draw(complainText);

                            // Show the buttons of the menu
                            for (int i = 0; i < (int)c.gameModeMenuMultiplayerButtons.size(); i++) {

                                c.gameModeMenuMultiplayerButtons.at(i).render(&c.w);

                                // Draw the button description in the panel
                                if (i == optionSelected){

                                    int posXDescriptionOffset = panelButton.getPosition().x + 10;
                                    int posYDescriptionOffset = panelButton.getPosition().y + 10;

                                    // Draw the button description
                                    // Display the description of the button
                                    vector<string> wordsButton =  c.gameModeMenuMultiplayerButtons.at(i).getDescriptionButton();

                                    for (string s : wordsButton){
                                        descriptionText.setString(s);
                                        if (posXDescriptionOffset + descriptionText.getLocalBounds().width <= c.thresholdDescriptionX){
                                            descriptionText.setPosition(posXDescriptionOffset, posYDescriptionOffset);
                                            c.w.draw(descriptionText);
                                            posXDescriptionOffset += descriptionText.getLocalBounds().width + 10;
                                        }
                                        else {
                                            posXDescriptionOffset = panelButton.getPosition().x + 10;
                                            posYDescriptionOffset += c.thresholdDescriptionY * 1.15f;
                                            descriptionText.setPosition(posXDescriptionOffset, posYDescriptionOffset);
                                            c.w.draw(descriptionText);
                                            posXDescriptionOffset += descriptionText.getLocalBounds().width + 10;
                                        }
                                    }
                                }
                            }

                            bufferSprite.setTexture(c.w.getTexture(), true);
                            c.w.display();
                            c.window.draw(bufferSprite);
                            c.window.display();
                        }
                    }
                }

                // Check if the up or down cursor keys have been pressed or not
                if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Down)) {
                    if (optionSelected != int(c.gameModeMenuMultiplayerButtons.size() - 1)) {
                        // Change the color appearance of both buttons
                        r.soundEffects[0]->stop();
                        r.soundEffects[0]->play();
                        optionSelected++;
                        c.gameModeMenuMultiplayerButtons[optionSelected].setButtonState(BUTTON_HOVER);
                        c.gameModeMenuMultiplayerButtons[optionSelected - 1].setButtonState(BUTTON_IDLE);
                    }
                }
                else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Up)) {
                    if (optionSelected != 0) {
                        r.soundEffects[0]->stop();
                        r.soundEffects[0]->play();
                        optionSelected--;
                        // Change the color appearance of both buttons
                        c.gameModeMenuMultiplayerButtons[optionSelected].setButtonState(BUTTON_HOVER);
                        c.gameModeMenuMultiplayerButtons[optionSelected + 1].setButtonState(BUTTON_IDLE);
                    }
                }
                // Draw the elements of the menu
                c.w.draw(c.sGameModesMultiplayerBackground);
                c.w.draw(shape);
                c.w.draw(panelButton);
                c.w.draw(mainText);

                // Show the buttons of the menu
                for (int i = 0; i < (int)c.gameModeMenuMultiplayerButtons.size(); i++) {

                    c.gameModeMenuMultiplayerButtons.at(i).render(&c.w);

                    // Draw the button description in the panel
                    if (i == optionSelected){

                        int posXDescriptionOffset = panelButton.getPosition().x + 10;
                        int posYDescriptionOffset = panelButton.getPosition().y + 10;

                        // Draw the button description
                        // Display the description of the button
                        vector<string> wordsButton =  c.gameModeMenuMultiplayerButtons.at(i).getDescriptionButton();

                        for (string s : wordsButton){
                            descriptionText.setString(s);
                            if (posXDescriptionOffset + descriptionText.getLocalBounds().width <= c.thresholdDescriptionX){
                                descriptionText.setPosition(posXDescriptionOffset, posYDescriptionOffset);
                                c.w.draw(descriptionText);
                                posXDescriptionOffset += descriptionText.getLocalBounds().width + 10;
                            }
                            else {
                                posXDescriptionOffset = panelButton.getPosition().x + 10;
                                posYDescriptionOffset += c.thresholdDescriptionY * 1.15f;
                                descriptionText.setPosition(posXDescriptionOffset, posYDescriptionOffset);
                                c.w.draw(descriptionText);
                                posXDescriptionOffset += descriptionText.getLocalBounds().width + 10;
                            }
                        }
                    }
                }

                bufferSprite.setTexture(c.w.getTexture(), true);
                c.w.display();
                c.window.draw(bufferSprite);
                c.window.display();
                sleep(milliseconds(120));

                // Check if start key has been pressed
                if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
                    startPressed = true;
                    r.soundEffects[2]->stop();
                    r.soundEffects[2]->play();

                    mtx3.lock();
                    gameModeSelected = true;
                    mtx3.unlock();
                    guestPulses.join();
                }
                // Check if escape key has been pressed
                else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)){
                    escapePressed = true;
                    r.soundEffects[11]->stop();
                    r.soundEffects[11]->play();
                    mtx3.lock();
                    escape = escapePressed;
                    mtx3.unlock();
                    guestPulses.join();
                }
                else if (cancelledGroup){
                    escapePressed = true;
                    r.soundEffects[11]->stop();
                    r.soundEffects[11]->play();
                    guestPulses.join();
                }
            }
        }

        // Control the pixel art flag to set the view of the screen
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

        if (escapePressed){

            // Create a Linda driver compatible with Windows to make communicate with the Linda server
            LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");

            if (numberPlayersGroup > 1){
                for (int i = 2; i <= numberPlayersGroup; i++){

                    int idCode = groupDataPlayers[i - 1].getCodePlayer();
                    string name = groupDataPlayers[i - 1].getNickNamePlayer();

                    // Inform that the group is cancelled
                    Tuple t = Tuple("CANCELLED_GROUP", nickNameGroupMultiplayer, to_string(idCode), nickNameMultiplayer, name);
                    winLindadriver.postNote(t);

                    // The to the member that the pulse has been received
                    t = Tuple("PULSE_RECEIVED", nickNameGroupMultiplayer, name, to_string(idCode));
                    winLindadriver.postNote(t);
                }
            }
            Tuple t = Tuple("NAME_GROUP", nickNameGroupMultiplayer);
            winLindadriver.removeNote(t);
            winLindadriver.stop();


            return MULTIPLAYER_NAME_GROUP;
        }

        // Create the connection with the Linda server
        LD winLindadriver = LD("onlinda.zgzinfinity.tech", "11777");

        // Iterate the members of the group
        for (int i = 2; i <= numberPlayersGroup; i++){

            int idCode = groupDataPlayers[i - 1].getCodePlayer();
            string name = groupDataPlayers[i - 1].getNickNamePlayer();

            // Inform that the group is cancelled
            Tuple t = Tuple("GAME_MODE_SELECTED", nickNameGroupMultiplayer, name, to_string(optionSelected));
            winLindadriver.postNote(t);

            // The to the member that the pulse has been received
            t = Tuple("PULSE_RECEIVED", nickNameGroupMultiplayer, name, to_string(idCode));
            winLindadriver.postNote(t);
        }

        mtx3.lock();
        gameModeSelected = true;
        mtx3.unlock();

        winLindadriver.stop();

        // Store the multi player mode selected
        typeOfGameMultiplayer = optionSelected;
    }
    else {

        // The player is a guest of the and must wait until the owner has selected the circuit
        bool circuitSelected = false, checkingCircuit = false, fail = false, checkingFail = false;

        bool cancelledCircuit = false;

        // Throw the thread that control if the circuit has been selected or not
        controlPulse = thread(sendGuestPulses, this, ref(circuitSelected), ref(fail), ref(cancelledCircuit));

        // Read the menu of circuit selection menu
        if (!c.gameModesMultiplayerMenuRead){
            string path = "Data/Menus/GameModesMultiplayerMenu/Configuration/GameModesMultiplayerMenu.xml";
            loadGameModesMultiplayerMenuConfiguration(path, c);
        }

         // Number of points to display depending of the resolution
        int totalPoints, offsetText;
        if (c.isDefaultScreen){
            totalPoints = 11;
            offsetText = 255;
        }
        else {
            totalPoints = 35;
            offsetText = 205;
        }

        // Prepare the screen to display the loading animation
        c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                              Vector2f(c.window.getSize().x, c.window.getSize().y)));
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));

        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

        // Load the background of the animation
        Texture t;
        t.loadFromFile("Data/Animations/LoadingAnimation/cover.png");
        IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
        Sprite sprite(t, background);

        float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
        float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
        sprite.setScale(axis_x, axis_y);

        // Menu text
        Text loadingText;
        loadingText.setString("WAITING FOR GAME MODE");
        loadingText.setCharacterSize(static_cast<unsigned int>(int(25.0f * c.screenScale)));
        loadingText.setFont(c.fontMenus);
        loadingText.setStyle(Text::Bold);
        loadingText.setFillColor(Color::White);
        loadingText.setOutlineColor(Color::Black);
        loadingText.setOutlineThickness(5.0f * c.screenScale);
        loadingText.setPosition((c.w.getSize().x / 5.f) - loadingText.getLocalBounds().width / 2.f,
                                     c.w.getSize().y / 2.0f + offsetText * c.screenScale);

        // Vector of loafing points
        string points[totalPoints];

        // Fill the vector with the points
        for (int i = 0; i < totalPoints; i++){
            points[i] = ".";
        }

        c.w.clear(Color(0, 0, 0));
        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

        int i = 0;

        while(!checkingCircuit && !checkingFail){

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)){
                if (e.type == Event::Closed){

                    Text complainText;
                    complainText.setString("THIS BUTTON CANT'T BE USED NOW ");
                    complainText.setCharacterSize(static_cast<unsigned int>(int(45.0f * c.screenScale)));
                    complainText.setFont(c.fontTitleMultiplayerMenu);
                    complainText.setStyle(Text::Bold);
                    complainText.setFillColor(c.colorTitleTextMultiplayerMenu);
                    complainText.setOutlineColor(c.colorTitleBorderMultiplayerMenu);
                    complainText.setOutlineThickness(5.0f * c.screenScale);
                    complainText.setPosition((c.w.getSize().x / 2.f) - complainText.getLocalBounds().width / 2.f,
                                              c.w.getSize().y / 2.f - complainText.getLocalBounds().height / 2.f);

                    for (int i = 0; i <= 120; i++){

                        Event e;
                        c.window.pollEvent(e);

                        // Draw the elements of the menu
                        c.w.draw(sprite);
                        c.w.draw(complainText);

                        bufferSprite.setTexture(c.w.getTexture(), true);
                        c.w.display();
                        c.window.draw(bufferSprite);
                        c.window.display();
                    }
                }
            }

            // Check if start has been pressed
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {

                r.soundEffects[11]->stop();
                r.soundEffects[11]->play();

                mtx3.lock();
                fail = true;
                mtx3.unlock();
            }

            c.w.clear(Color(0, 0, 0));

            // Draw the elements of the menu
            c.w.draw(sprite);
            c.w.draw(loadingText);

            // Draw the loading points
            for (int j = 0; j <= i; j++){

                // Detect the possible events
                Event e{};
                while (c.window.pollEvent(e)){
                    if (e.type == Event::Closed){
                        Text complainText;
                        complainText.setString("THIS BUTTON CANT'T BE USED NOW ");
                        complainText.setCharacterSize(static_cast<unsigned int>(int(45.0f * c.screenScale)));
                        complainText.setFont(c.fontTitleMultiplayerMenu);
                        complainText.setStyle(Text::Bold);
                        complainText.setFillColor(c.colorTitleTextMultiplayerMenu);
                        complainText.setOutlineColor(c.colorTitleBorderMultiplayerMenu);
                        complainText.setOutlineThickness(5.0f * c.screenScale);
                        complainText.setPosition((c.w.getSize().x / 2.f) - complainText.getLocalBounds().width / 2.f,
                                                  c.w.getSize().y / 2.f - complainText.getLocalBounds().height / 2.f);

                        for (int i = 0; i <= 120; i++){

                            Event e;
                            c.window.pollEvent(e);

                            // Draw the elements of the menu
                            c.w.draw(sprite);
                            c.w.draw(complainText);

                            bufferSprite.setTexture(c.w.getTexture(), true);
                            c.w.display();
                            c.window.draw(bufferSprite);
                            c.window.display();
                        }
                    }
                }

                Text pointText;
                pointText.setString(points[j]);
                pointText.setCharacterSize(static_cast<unsigned int>(int(25.0f * c.screenScale)));
                pointText.setFont(c.fontMenus);
                pointText.setStyle(Text::Bold);
                pointText.setFillColor(Color::White);
                pointText.setOutlineColor(Color::Black);
                pointText.setOutlineThickness(5.0f * c.screenScale);
                pointText.setPosition((c.w.getSize().x / 6.0f) + loadingText.getLocalBounds().width / 2.f + 50.f * (j + 1),
                                       c.w.getSize().y / 2.f + offsetText * c.screenScale);
                c.w.draw(pointText);
            }

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();

            sleep(milliseconds(120));

            i++;

            if (i == totalPoints){
                i = 0;
            }

            mtx3.lock();
            checkingCircuit = circuitSelected;
            checkingFail = fail;
            mtx3.unlock();
        }
        if (fail){
            // All goes ok
            controlPulse.join();

            if (randomMultiplayerJoined){
                return SELECT_MULTIPLAYER_JOIN;
            }
            else {
                return MULTIPLAYER_NAME_GROUP;
            }
        }
        // All goes ok
        controlPulse.join();
    }
    if (typeOfGameMultiplayer == 0){
        return VEHICLE_SELECTION;
    }
    else {
        return SELECTION_CIRCUIT_MULTIPLAYER;
    }
}



State Game::selectionCircuitMultiplayer(Configuration& c, SoundPlayer& r){
    if (modeMultiplayer == 0){
        // The player is the creator of the group and must selected a circuit
        State status = selectionCircuitMenu(c, r);
        return status;
    }
    else {
        // The player is a guest of the and must wait until the owner has selected the circuit
        bool circuitSelected = false, checkingCircuit = false, fail = false, checkingFail = false, checkingCancelled = false;

        bool cancelledCircuit = false;

        // Throw the thread that control if the circuit has been selected or not
        controlPulse = thread(sendGuestPulses, this, ref(circuitSelected), ref(fail), ref(cancelledCircuit));

        // Read the menu of circuit selection menu
        if (!c.circuitMenuRead){
            string path = "Data/Menus/CircuitSelectionMenu/Configuration/CircuitSelectionMenu.xml";
            loadCircuitMenuConfiguration(path, c);
        }

         // Number of points to display depending of the resolution
        int totalPoints, offsetText;
        if (c.isDefaultScreen){
            totalPoints = 11;
            offsetText = 255;
        }
        else {
            totalPoints = 16;
            offsetText = 205;
        }

        // Prepare the screen to display the loading animation
        c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                              Vector2f(c.window.getSize().x, c.window.getSize().y)));
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));

        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

        // Load the background of the animation
        Texture t;
        t.loadFromFile("Data/Animations/LoadingAnimation/cover.png");
        IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
        Sprite sprite(t, background);

        float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
        float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
        sprite.setScale(axis_x, axis_y);

        // Menu text
        Text loadingText;
        loadingText.setString("WAITING FOR CIRCUIT");
        loadingText.setCharacterSize(static_cast<unsigned int>(int(25.0f * c.screenScale)));
        loadingText.setFont(c.fontMenus);
        loadingText.setStyle(Text::Bold);
        loadingText.setFillColor(Color::White);
        loadingText.setOutlineColor(Color::Black);
        loadingText.setOutlineThickness(5.0f * c.screenScale);
        loadingText.setPosition((c.w.getSize().x / 5.f) - loadingText.getLocalBounds().width / 2.f,
                                     c.w.getSize().y / 2.f + offsetText * c.screenScale);

        // Vector of loafing points
        string points[totalPoints];

        // Fill the vector with the points
        for (int i = 0; i < totalPoints; i++){
            points[i] = ".";
        }

        c.w.clear(Color(0, 0, 0));
        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

        int i = 0;

        while(!checkingCircuit && !checkingFail && !checkingCancelled){

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)){
                if (e.type == Event::Closed){

                    Text complainText;
                    complainText.setString("THIS BUTTON CANT'T BE USED NOW ");
                    complainText.setCharacterSize(static_cast<unsigned int>(int(45.0f * c.screenScale)));
                    complainText.setFont(c.fontTitleMultiplayerMenu);
                    complainText.setStyle(Text::Bold);
                    complainText.setFillColor(c.colorTitleTextMultiplayerMenu);
                    complainText.setOutlineColor(c.colorTitleBorderMultiplayerMenu);
                    complainText.setOutlineThickness(5.0f * c.screenScale);
                    complainText.setPosition((c.w.getSize().x / 2.f) - complainText.getLocalBounds().width / 2.f,
                                              c.w.getSize().y / 2.f - complainText.getLocalBounds().height / 2.f);

                    for (int i = 0; i <= 120; i++){

                        Event e;
                        c.window.pollEvent(e);

                        // Draw the elements of the menu
                        c.w.draw(sprite);
                        c.w.draw(complainText);

                        bufferSprite.setTexture(c.w.getTexture(), true);
                        c.w.display();
                        c.window.draw(bufferSprite);
                        c.window.display();
                    }
                }
            }

            // Check if start has been pressed
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {

                r.soundEffects[11]->stop();
                r.soundEffects[11]->play();

                mtx3.lock();
                fail = true;
                mtx3.unlock();

                controlPulse.join();
            }

            c.w.clear(Color(0, 0, 0));

            // Draw the elements of the menu
            c.w.draw(sprite);
            c.w.draw(loadingText);

            // Draw the loading points
            for (int j = 0; j <= i; j++){

                // Detect the possible events
                Event e{};
                while (c.window.pollEvent(e)){
                    if (e.type == Event::Closed){
                        Text complainText;
                        complainText.setString("THIS BUTTON CANT'T BE USED NOW ");
                        complainText.setCharacterSize(static_cast<unsigned int>(int(45.0f * c.screenScale)));
                        complainText.setFont(c.fontTitleMultiplayerMenu);
                        complainText.setStyle(Text::Bold);
                        complainText.setFillColor(c.colorTitleTextMultiplayerMenu);
                        complainText.setOutlineColor(c.colorTitleBorderMultiplayerMenu);
                        complainText.setOutlineThickness(5.0f * c.screenScale);
                        complainText.setPosition((c.w.getSize().x / 2.f) - complainText.getLocalBounds().width / 2.f,
                                                  c.w.getSize().y / 2.f - complainText.getLocalBounds().height / 2.f);

                        for (int i = 0; i <= 120; i++){

                            Event e;
                            c.window.pollEvent(e);

                            // Draw the elements of the menu
                            c.w.draw(sprite);
                            c.w.draw(complainText);

                            bufferSprite.setTexture(c.w.getTexture(), true);
                            c.w.display();
                            c.window.draw(bufferSprite);
                            c.window.display();
                        }
                    }
                }

                Text pointText;
                pointText.setString(points[j]);
                pointText.setCharacterSize(static_cast<unsigned int>(int(25.0f * c.screenScale)));
                pointText.setFont(c.fontMenus);
                pointText.setStyle(Text::Bold);
                pointText.setFillColor(Color::White);
                pointText.setOutlineColor(Color::Black);
                pointText.setOutlineThickness(5.0f * c.screenScale);
                pointText.setPosition((c.w.getSize().x / 5.5f) + loadingText.getLocalBounds().width / 2.f + 50.f * (j + 1),
                                       c.w.getSize().y / 2.f + offsetText * c.screenScale);
                c.w.draw(pointText);
            }

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();

            sleep(milliseconds(120));

            i++;

            if (i == totalPoints){
                i = 0;
            }

            mtx3.lock();
            checkingCircuit = circuitSelected;
            checkingFail = fail;
            checkingCancelled = cancelledCircuit;
            mtx3.unlock();
        }
        if (fail){
            if (randomMultiplayerJoined){
                return SELECT_MULTIPLAYER_JOIN;
            }
            else {
                return MULTIPLAYER_NAME_GROUP;
            }
        }
        if (cancelledCircuit){
            // All goes ok
            controlPulse.join();
            return SELECTION_MODE_MULTIPLAYER;
        }
        // All goes ok
        return VEHICLE_SELECTION;
    }
}




void Game::loadMultiplayerMemberGroupMenuConfiguration(const string path, Configuration& c){

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
            c.backgroundMultiplayerMembersGroupMenu.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the player menu
            for (xml_node<> *panelProp = property->first_node(); panelProp; panelProp = panelProp->next_sibling()){
                // Check it is the node that contains the information of the background of the panel
                if ((string)panelProp->name() == "Background"){
                    // Get the background image of the menu
                    backgroundTexture = (string)panelProp->value();
                    c.backgroundMultiplayerMembersGroupPanel.loadFromFile(backgroundTexture);
                }
                // Check it is the node that contains the information of the color border of the panel
                else if ((string)panelProp->name() == "ColorBorder"){
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
                    // Store the color border of the panel
                    c.colorBorderPanelMultiplayerMembersGroupMenu = Color(colorRed, colorGreen, colorBlue);
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
                    c.contentTitleMultiplayerMembersGroupMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontTitleMultiplayerMembersGroupMenu.loadFromFile(fontPath);
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
                        c.colorTitleTextMultiplayerMembersGroupMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderMultiplayerMembersGroupMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
         // Check if it is the node that stores the information of the main text of the menu
        else if ((string)property->name() == "MemberIndicator"){
            // Iterate to get the information of the title
            for (xml_node<> *titleProp = property->first_node(); titleProp; titleProp = titleProp->next_sibling()){
                if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
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
                        // Check if it is the color of inside
                        if (colorKind == "ColorText"){
                            c.colorIndicatorInsideMultiplayerMembersGroupMenu = Color(colorRed, colorGreen, colorBlue);
                        }
                        // Check if it is the color of the border
                        else if (colorKind == "ColorBorder"){
                            c.colorIndicatorBorderMultiplayerMembersGroupMenu = Color(colorRed, colorGreen, colorBlue);
                        }
                }
            }
        }
    }
    // The player menu has been read correctly
    c.multiplayerMembersGroupMenuRead = true;
}




void Game::testConnection(bool& testFinished, string& mininumLatency, string& mediumLatency, string& maxLantency){
    // Make connection test using ping command
    char pingCommandOutput[2048];
    cmd("ping onlinda.zgzinfinity.tech", pingCommandOutput, 2048);

    // Index of the buffer character
    int i = 0;

    // Counter of new line characters found
    int counter = 0;

    // Number of latencies processed
    int latenciesProccessed = 0;

    // Iterate the output of ping command until the last line is reached
    while (counter != 11 && pingCommandOutput[i] != '\0'){
        // Check if is a new line
        if (pingCommandOutput[i] == '\n'){
            // Last line obtained
            counter++;
        }
        // Increment the index
        i++;
    }

    // Check the final buffer
    while (pingCommandOutput[i] != '\0'){
        // Check if the character is a number
        if (isdigit(pingCommandOutput[i])){
            // Select in which latency the number must be stored
            switch(latenciesProccessed){
                case 0:
                    // Minimum latency of the ping command
                    mininumLatency += pingCommandOutput[i];
                    break;
                case 1:
                    // Medium latency of the ping command
                    maxLantency += pingCommandOutput[i];
                    break;
                case 2:
                    // Maximum latency of the ping command
                    mediumLatency += pingCommandOutput[i];
            }
        }
        // Check if the character is a comma
        else if (pingCommandOutput[i] == ','){
            // A new latency has been processed
            latenciesProccessed++;
        }
        // Increment the index
        i++;
    }
    // Alert that the test has been finished
    mtx3.lock();
    testFinished = true;
    mtx3.unlock();
}



/**
 * Load the configuration of the multi player test configuration menu stored in its xml configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void Game::loadMultiplayerMenuTestingNetworkConfiguration(const string path, Configuration& c){

    // Open the xml file of the multi player
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Local variable to store temporary the text content and the fonts of the texts
    string content, fontPath, backgroundTexture, colorKind;

    // Iterate to get the information of the multi player menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check it is the node that contains the information of the background
        if ((string)property->name() == "Background"){
            // Get the background image of the menu
            backgroundTexture = (string)property->value();
            c.backgroundMultiplayerTestConnectionMenu.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the multi player menu
            for (xml_node<> *panelProp = property->first_node(); panelProp; panelProp = panelProp->next_sibling()){
                // Check it is the node that contains the information of the background of the panel
                if ((string)panelProp->name() == "Background"){
                    // Get the background image of the menu
                    backgroundTexture = (string)panelProp->value();
                    c.backgroundMultiplayerTestConnectionPanel.loadFromFile(backgroundTexture);
                }
                // Check it is the node that contains the information of the color border of the panel
                else if ((string)panelProp->name() == "ColorBorder"){
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the multi player menu
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
                    // Store the color border of the panel
                    c.colorBorderPanelMultiplayerTestConnectionMenu = Color(colorRed, colorGreen, colorBlue);
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
                    c.contentTitleMultiplayerTestConnectionMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontTitleMultiplayerTestConnectionMenu.loadFromFile(fontPath);
                }
                // Get color text of the title
                else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                    // Get the kind of color to process
                    colorKind = (string)titleProp->name();
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the multi player menu
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
                        c.colorTitleTextMultiplayerTestConnectionMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderMultiplayerTestConnectionMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
        // Check if it is the node that the different buttons of the menu
        else if ((string)property->name() == "MenuButtons"){
            Color colorFont;
            // Iterate to get the information of the buttons of the player menu
            for (xml_node<> *buttonProp = property->first_node(); buttonProp; buttonProp = buttonProp->next_sibling()){
                // Get the font of the buttons
                if ((string)buttonProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)buttonProp->value();
                    c.fontMenuMultiplayerTestConnectionButtons.loadFromFile(fontPath);
                }
                // Get the color font of the buttons
                else if ((string)buttonProp->name() == "ColorFont"){
                    // Read the font from the file
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the multi player menu
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
                    c.colorFontMenuPlayerTestConnectionButtons = Color(colorRed, colorGreen, colorBlue);
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
                                    // Iterate to get the information of the multi player menu
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
                                    c.multiplayerTestConnectionMenuColorButtons.push_back(Color(colorRed, colorGreen, colorBlue));
                                }

                                // Creation of the button and addition to the vector
                                posX = c.w.getSize().x / 2.f - 110.0f * c.screenScale;
                                posY = c.w.getSize().y / 2.f - (-93.0f - idButton * 103.f) * c.screenScale;
                                widthButton = 200.0f * c.screenScale;
                                heightButton = 50.0f * c.screenScale;

                                // Creation of the button
                                Button b = Button(posX, posY, widthButton, heightButton, c.fontMenuMultiplayerTestConnectionButtons,
                                                  contentButton, c.multiplayerTestConnectionMenuColorButtons[0],
                                                  c.multiplayerTestConnectionMenuColorButtons[1],
                                                  c.colorFontMenuPlayerTestConnectionButtons, buttonState, c.screenScale);

                                c.multiplayerTestConnectionMenuButtons.push_back(b);
                                idButton++;
                            }
                        }
                    }
                }
            }
        }
    }
    // The player menu has been read correctly
    c.multiplayerTestConnectionMenuRead = true;
}




State Game::makeConnectionServerTest(Configuration& c, SoundPlayer& r){

    // Variables to store the latencies of the test
    string mininumLatency = "", mediumLatency = "", maxLantency = "";

    // Control locally if the test has been finished or not
    bool testFinished = false, testCompleted = false;

    // Throw a thread with that process the speed connection test
    thread testerServerConnection(testConnection, this, ref(testFinished), ref(mininumLatency), ref(mediumLatency), ref(maxLantency));
    testerServerConnection.detach();

    mtx3.lock();
    testCompleted = testFinished;
    mtx3.unlock();

    // Check if the xml configuration file has been read or not
    if (!c.multiplayerTestConnectionMenuRead){
        string pathFile = "Data/Menus/TestingNetworkMenu/Configuration/TestingNetworkMenu.xml";
        loadMultiplayerMenuTestingNetworkConfiguration(pathFile, c);
    }
    else {
        int numButtons = int(c.multiplayerTestConnectionMenuButtons.size());

        // Change the state of the first color
        Button b = Button(c.w.getSize().x / 2.f - 110.0f * c.screenScale, c.w.getSize().y / 2.f + 93.0f * c.screenScale,
                          200.0f * c.screenScale, 50.0f * c.screenScale, c.fontMenuMultiplayerTestConnectionButtons,
                          c.multiplayerTestConnectionMenuButtons[0].getTextButton(), c.multiplayerTestConnectionMenuButtons[0].getIdleColorButton(),
                          c.multiplayerTestConnectionMenuButtons[0].getHoverColorButton(), c.multiplayerTestConnectionMenuButtons[0].getFontColorButton(), 1,
                          c.screenScale);

        c.multiplayerTestConnectionMenuButtons[0] = b;

        // Eliminate the buttons of the right column
        for (int i = 1; i < numButtons; i++){
            // Change the state of the first color
            Button b = Button(c.w.getSize().x / 2.f - 110.0f * c.screenScale, c.w.getSize().y / 2.f - (-93.0f - i * 103.f) * c.screenScale,
                              200.0f * c.screenScale, 50.0f * c.screenScale, c.fontMenuMultiplayerTestConnectionButtons,
                              c.multiplayerTestConnectionMenuButtons[i].getTextButton(), c.multiplayerTestConnectionMenuButtons[i].getIdleColorButton(),
                              c.multiplayerTestConnectionMenuButtons[i].getHoverColorButton(), c.multiplayerTestConnectionMenuButtons[i].getFontColorButton(), 0,
                              c.screenScale);

            c.multiplayerTestConnectionMenuButtons[i] = b;
        }
    }

    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Make the textures repeated
    c.backgroundMultiplayerTestConnectionMenu.setRepeated(true);
    c.backgroundMultiplayerTestConnectionPanel.setRepeated(true);

    // Global rectangle of the background
    IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
    Sprite sprite(c.backgroundMultiplayerTestConnectionMenu, background);

    float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
    float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
    sprite.setScale(axis_x, axis_y);

    // Creation of the panel rectangle of the menu
    RectangleShape shape;
    shape.setPosition((c.w.getSize().x / 2.f) - 350.0f * c.screenScale, c.w.getSize().y / 2.f - 230.0f * c.screenScale);
    shape.setSize(sf::Vector2f(710.0f * c.screenScale, 520.0f * c.screenScale));
    shape.setOutlineColor(c.colorBorderPanelMultiplayerTestConnectionMenu);
    shape.setOutlineThickness(5.0f * c.screenScale);
    shape.setTexture(&c.backgroundMultiplayerTestConnectionPanel, true);

    // Main Text of the menu
    Text mainText;
    mainText.setString(c.contentTitleMultiplayerTestConnectionMenu);
    mainText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    mainText.setFont(c.fontTitleMultiplayerTestConnectionMenu);
    mainText.setStyle(Text::Bold | Text::Underlined);
    mainText.setFillColor(c.colorTitleTextMultiplayerTestConnectionMenu);
    mainText.setOutlineColor(c.colorTitleBorderMultiplayerTestConnectionMenu);
    mainText.setOutlineThickness(5.0f * c.screenScale);
    mainText.setPosition((c.w.getSize().x / 2.f) - mainText.getLocalBounds().width / 2.f,
                          c.w.getSize().y / 2.f - 215.0f * c.screenScale);

    Text testingText;
    testingText.setString("TESTING CONNECTION SPEED, WAIT");
    testingText.setCharacterSize(static_cast<unsigned int>(int(45.0f * c.screenScale)));
    testingText.setFont(c.fontTitleMultiplayerTestConnectionMenu);
    testingText.setStyle(Text::Bold);
    testingText.setFillColor(c.colorTitleTextMultiplayerTestConnectionMenu);
    testingText.setOutlineColor(c.colorTitleBorderMultiplayerTestConnectionMenu);
    testingText.setOutlineThickness(5.0f * c.screenScale);
    testingText.setPosition((c.w.getSize().x / 2.f) - testingText.getLocalBounds().width / 2.f,
                             c.w.getSize().y / 2.f - testingText.getLocalBounds().height / 2.f);

    Text minLatency;
    minLatency.setString("MINIMUN LATENCY: ");
    minLatency.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    minLatency.setFont(c.fontTitleMultiplayerTestConnectionMenu);
    minLatency.setStyle(Text::Bold);
    minLatency.setFillColor(c.colorTitleTextMultiplayerTestConnectionMenu);
    minLatency.setOutlineColor(c.colorTitleBorderMultiplayerTestConnectionMenu);
    minLatency.setOutlineThickness(5.0f * c.screenScale);
    minLatency.setPosition((c.w.getSize().x / 2.f) - minLatency.getLocalBounds().width / 1.6f,
                                c.w.getSize().y / 2.f - 150.f * c.screenScale);

    Text medLatency;
    medLatency.setString("MEDIUM LATENCY: ");
    medLatency.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    medLatency.setFont(c.fontTitleMultiplayerTestConnectionMenu);
    medLatency.setStyle(Text::Bold);
    medLatency.setFillColor(c.colorTitleTextMultiplayerTestConnectionMenu);
    medLatency.setOutlineColor(c.colorTitleBorderMultiplayerTestConnectionMenu);
    medLatency.setOutlineThickness(5.0f * c.screenScale);
    medLatency.setPosition((c.w.getSize().x / 2.f) - medLatency.getLocalBounds().width / 1.52f,
                                c.w.getSize().y / 2.f - 90.f * c.screenScale);

    Text maxLatency;
    maxLatency.setString("MAXIMUM LATENCY: ");
    maxLatency.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    maxLatency.setFont(c.fontTitleMultiplayerTestConnectionMenu);
    maxLatency.setStyle(Text::Bold);
    maxLatency.setFillColor(c.colorTitleTextMultiplayerTestConnectionMenu);
    maxLatency.setOutlineColor(c.colorTitleBorderMultiplayerTestConnectionMenu);
    maxLatency.setOutlineThickness(5.0f * c.screenScale);
    maxLatency.setPosition((c.w.getSize().x / 2.f) - maxLatency.getLocalBounds().width / 1.61f,
                                c.w.getSize().y / 2.f - 30.f * c.screenScale);

    // Check if the testing network has finished or not
    mtx3.lock();
    testCompleted = testFinished;
    mtx3.unlock();

    while (!testCompleted){
        // Detect the possible events
        Event e;
        c.window.pollEvent(e);

        // Draw the elements of the menu
        c.w.draw(sprite);
        c.w.draw(testingText);

        bufferSprite.setTexture(c.w.getTexture(), true);
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

         // Check if the testing network has finished or not
        mtx3.lock();
        testCompleted = testFinished;
        mtx3.unlock();
    }

    Text minLatencyValue;
    minLatencyValue.setString(mininumLatency + " MS");
    minLatencyValue.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    minLatencyValue.setFont(c.fontTitleMultiplayerTestConnectionMenu);
    minLatencyValue.setStyle(Text::Bold);
    minLatencyValue.setFillColor(Color::Green);
    minLatencyValue.setOutlineColor(c.colorTitleBorderMultiplayerTestConnectionMenu);
    minLatencyValue.setOutlineThickness(5.0f * c.screenScale);
    minLatencyValue.setPosition((c.w.getSize().x / 2.f) + 80.f * c.screenScale,
                                c.w.getSize().y / 2.f - 150.f * c.screenScale);

    Text medLatencyValue;
    medLatencyValue.setString(mediumLatency + " MS");
    medLatencyValue.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    medLatencyValue.setFont(c.fontTitleMultiplayerTestConnectionMenu);
    medLatencyValue.setStyle(Text::Bold);
    medLatencyValue.setFillColor(Color::Yellow);
    medLatencyValue.setOutlineColor(c.colorTitleBorderMultiplayerTestConnectionMenu);
    medLatencyValue.setOutlineThickness(5.0f * c.screenScale);
    medLatencyValue.setPosition((c.w.getSize().x / 2.f) + 80.f * c.screenScale,
                                c.w.getSize().y / 2.f - 90.f * c.screenScale);

    Text maxLatencyValue;
    maxLatencyValue.setString(maxLantency + " MS");
    maxLatencyValue.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    maxLatencyValue.setFont(c.fontTitleMultiplayerTestConnectionMenu);
    maxLatencyValue.setStyle(Text::Bold);
    maxLatencyValue.setFillColor(Color::Red);
    maxLatencyValue.setOutlineColor(c.colorTitleBorderMultiplayerTestConnectionMenu);
    maxLatencyValue.setOutlineThickness(5.0f * c.screenScale);
    maxLatencyValue.setPosition((c.w.getSize().x / 2.f) + 90.f * c.screenScale,
                                c.w.getSize().y / 2.f - 30.f * c.screenScale);

    string indicator;
    int latency = stoi(mediumLatency);

    Text playerAlarm;
    playerAlarm.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    playerAlarm.setFont(c.fontTitleMultiplayerTestConnectionMenu);
    playerAlarm.setStyle(Text::Bold);
    playerAlarm.setFillColor(Color(10, 201, 235));
    playerAlarm.setOutlineColor(Color(3, 39, 8));
    playerAlarm.setOutlineThickness(5.0f * c.screenScale);

    if (latency <= 40){
        indicator = "YOUR CLIENT WILL GO LIKE A ROCKET";
    }
    else if (latency <= 70) {
        indicator = "YOUR CLIENTE WILL GO DECENTLY";
    }
    else if (latency <= 100){
        indicator = "YOUR CLIENTE WILL GO A LITTLE LAGGED";
    }
    else {
        indicator = "YOUR CLIENTE WILL GO VERY LAGGED";
    }

    playerAlarm.setString(indicator);
    playerAlarm.setPosition((c.w.getSize().x / 2.f) - playerAlarm.getLocalBounds().width / 2.f,
                             c.w.getSize().y / 2.f + 25.f * c.screenScale);

    // Control if the start key is pressed or not
    bool startPressed = false;

    // Control if the escape key has been pressed
    bool escapePressed = false;

    // Control the option selected by the user
    int optionSelected = 0;

    // While start and escape have not been pressed
    while (!startPressed && !escapePressed) {

        // Detect the possible events
        Event e;
        while (c.window.pollEvent(e)){
            if (e.type == Event::Closed){
                return EXIT;
            }
        }

        // Check if the up or down cursor keys have been pressed or not
        if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Down)) {
            if (optionSelected != int(c.multiplayerTestConnectionMenuButtons.size() - 1)) {
                // Change the color appearance of both buttons
                r.soundEffects[0]->stop();
                r.soundEffects[0]->play();
                optionSelected++;
                c.multiplayerTestConnectionMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                c.multiplayerTestConnectionMenuButtons[optionSelected - 1].setButtonState(BUTTON_IDLE);
            }
        }
        else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Up)) {
            if (optionSelected != 0) {
                r.soundEffects[0]->stop();
                r.soundEffects[0]->play();
                optionSelected--;
                // Change the color appearance of both buttons
                c.multiplayerTestConnectionMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                c.multiplayerTestConnectionMenuButtons[optionSelected + 1].setButtonState(BUTTON_IDLE);
            }
        }

        // Draw the elements of the menu
        c.w.clear(Color(0, 0, 0));
        c.w.draw(sprite);
        c.w.draw(shape);
        c.w.draw(mainText);
        c.w.draw(minLatency);
        c.w.draw(medLatency);
        c.w.draw(maxLatency);
        c.w.draw(minLatencyValue);
        c.w.draw(medLatencyValue);
        c.w.draw(maxLatencyValue);
        c.w.draw(playerAlarm);

        // Show the buttons of the menu
        for (int i = 0; i < (int)c.multiplayerTestConnectionMenuButtons.size(); i++) {
            c.multiplayerTestConnectionMenuButtons.at(i).render(&c.w);
        }

        bufferSprite.setTexture(c.w.getTexture(), true);
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();
        sleep(milliseconds(120));

        // Check if start has been pressed
        if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
            startPressed = true;
            r.soundEffects[2]->stop();
            r.soundEffects[2]->play();
        }
        // Check if escape has been pressed
        else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {
            escapePressed = true;
            r.soundEffects[11]->stop();
            r.soundEffects[11]->play();
        }
    }

    // Control the pixel art flag to construct the view of the screen
    if (c.enablePixelArt) {
        if (c.isDefaultScreen){
            c.window.setView(View(Vector2f(DEFAULT_WIDTH / 4.0f, DEFAULT_HEIGHT / 4.0f),
                                  Vector2f(DEFAULT_WIDTH / 2.0f, DEFAULT_HEIGHT / 2.0f)));
        }
        else {
            c.window.setView(View(Vector2f(SCREEN_HD_WIDTH / 4.0f, SCREEN_HD_HEIGHT / 4.0f),
                                  Vector2f(SCREEN_HD_WIDTH / 2.0f, SCREEN_HD_HEIGHT / 2.0f)));
        }
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));
        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);
    }


    if(startPressed){
        switch (optionSelected){
            case 0:
                return MULTIPLAYER_MENU;
            case 1:
                r.soundTracks[18]->stop();
                r.soundTracks[1]->play();
                return PLAYER_MENU;
        }
    }
    else if (escapePressed) {
        r.soundTracks[18]->stop();
        r.soundTracks[1]->play();
        return PLAYER_MENU;
    }
    return EXIT;
}
