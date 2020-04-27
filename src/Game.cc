
#include "../include/Game.h"



/**
 * Constructor of the data type Game
 * @param app is the console window where it's going to be displayed
 */
Game::Game(RenderWindow* app) {
    // Initializing the console window of the game
    application = app;

    // First state of the game
    status = ANIMATION;

    // Creation of the soundtrack reproductor
    mR = new MusicReproductor();

    // Creation of the sound effects reproductor
    eR = new EffectReproductor();

    // Load the default configuration of the game
    c = new Configuration();

    // Initialize the keyword mapper module
    kM = new KeywordMapper();

    // Load the soundtracks from the xml configuration file
    mR->loadSoundtracksOfGame("Configuration/Soundtracks/Soundtracks.xml");

    // Load the sound effects from the xml configuration file
    eR->loadEffectsOfGame("Configuration/SoundEffects/SoundEffects.xml");

    // Initialize the soundtrack list in the first position
    mR->startSoundtrackList();

    // Creation of the menus
    menuGame = new Menu();
}



/**
 * Execute the game throughout its different states
 */
void Game::runningGame(){
    // While the game is opened
    while (application->isOpen()) {
        // Check the status of the game and pass to the next one
        switch(status){
            case ANIMATION:
                // Starts the animation
                status = showStartingAnimation();
                break;
            case MAIN_MENU:
                // Displays the main menu
                status = showMainMenu();
                break;
            case PLAYER_MENU:
                // Displays the player menu
                status = showPlayerMenu();
                break;
            case SINGLE_GAME_MODE:
                // Display the game modes available in the single player mode
                status = showSinglePlayerMenu();
                break;
            case MULTI_GAME_MODE:
                // Display the game modes available in the multi player mode
                break;
            case LEVEL_MENU:
                // Displays the game mode selected
                status = showDifficultLevelMenu();
                break;
            case PREPARING_GAME_MODE:
                // Prepare the configuration of the game mode selected
                status = prepareGameMode();
                break;
            case VEHICLE_MENU:
                // Displays the vehicle menu
                status = showVehicleMenu();
                break;
            case OPTIONS:
                status = showOptionsMenu();
                break;
            case PLAYING:
                // Starts with the game mode execution
                status = playingGame();
        }
    }
}



/**
 * Displays the initial animations when the game starts
 */
Game_status Game::showStartingAnimation(){
    // Creation of the animation
    string animationFile = "Configuration/Animations/Animations.xml";
    char* animationF = const_cast<char*>(animationFile.c_str());
    this->animationGame = new Animation(animationF);

    // Showing the animation of the sega logo
    animationGame->loadSegaIcons(application, eR);

    // Stop the sega sound for the animation
    mR->stopSound();

    // Get the actual soundtrack
    Soundtrack s = mR->getSoundtrack(mR->getIndexPosition());

    // Reproduce the main soundtrack of the game
    mR->reproduceSound(s.getTitle(), s.isInLoop() ,s.getVolume());

    // Shwoing the company and the presents logo of the game
    animationGame->loadGameData(application);

    // Advance the soundtrack list
    mR->advanceSoundtrack();

    // Advance the state machine of the game to present the main menu of the game
    return MAIN_MENU;
}



/**
 * Show the main menu of the game
 */
Game_status Game::showMainMenu(){
    // Show the main menu
    menuGame->showMainMenu(application, eR);

    // Stop the intro sound of the main menu
    mR->stopSound();

    // Advance the state machine of the game to present the player mode menu
    return PLAYER_MENU;
}



/**
 * Show the player menu of the game
 */
Game_status Game::showPlayerMenu(){
    // Advance the soundtrack
    mR->advanceSoundtrack();

    // Get the actual soundtrack
    Soundtrack s = mR->getSoundtrack(mR->getIndexPosition());

    // Reproduce sound of the player, selection game mode and difficult level menus
    mR->reproduceSound(s.getTitle(), s.isInLoop() ,s.getVolume());

    // Show the selector menu of the players
    menuGame->showStandardMenu(application, "Configuration/Menus/PlayerMenu.xml", modePlayerSelected, status, eR);

    // Check the status of the game
    if (status == MAIN_MENU){
        // Stop the actual soundtrack
        mR->stopSound();
        mR->backSoundtrack();

        // Get the actual soundtrack
        s = mR->getSoundtrack(mR->getIndexPosition());
        mR->reproduceSound(s.getTitle(), s.isInLoop() ,s.getVolume());
        mR->advanceSoundtrack();
    }

    // Check if the backspace keyword has been modified
    return status;
}



/**
 * Show the different game modes when the payer
 * chooses the single player mode
 */
Game_status Game::showSinglePlayerMenu(){
    // Show the selector game modes available for only one player
    menuGame->showStandardMenu(application, "Configuration/Menus/GameMenu.xml", modeGameSelected, status, eR);

    // Advance the state machine of the game in order to display the menu where the player
    // must select a difficult level to play
    return status;
}



/**
 * Show the different available difficult level
 * to play in the game mode selecte
 */
Game_status Game::showDifficultLevelMenu(){
    // Show the selector difficult level of the game where the user must select one of them
    menuGame->showStandardMenu(application, "Configuration/Menus/DifficultLevelMenu.xml", modeDifficultLevelSelected, status, eR);

    // Advance the state machine of the game in order to start the loading configuration
    // from the xml file of the game selected with the difficult chosen
    return status;
}



/**
 * Prepares all the configurations of the game mode selected
 */
Game_status Game::prepareGameMode(){
    // Creation of the game selector mode controller
    gSM = GameSelectorMode(modeDifficultLevelSelected, modeGameSelected);

    // Load the game mode configuration selected by the player with the difficult selected
    gSM.loadFileConfigurationMode(e, landscapePaths);

    // Stop the intro sound
    mR->stopSound();

    // Advance the state of the game in order to display the menu where the
    // player selects a vehicle to play
    return VEHICLE_MENU;
}



/**
 * Show the menu for choose the vehicle and play
 */
Game_status Game::showVehicleMenu(){
    // Advance to the next soundtrack of the list
    mR->advanceSoundtrack();

    // Get the actual soundtrack
    Soundtrack s = mR->getSoundtrack(mR->getIndexPosition());

    // Reproduce sound of the player, selection game mode and difficult level menus
    mR->reproduceSound(s.getTitle(), s.isInLoop() ,s.getVolume());

    // Show the menu of selection vehicle where the player must select one
    menuGame->showSelectionVehicleMenu(application, typeOfVehicle, colorVehicle, status, eR);

    // Stop the music of the vehicle selector menu
    mR->stopSound();

    if (status == LEVEL_MENU){
        mR->backSoundtrack();

        // Get the actual soundtrack
        Soundtrack s = mR->getSoundtrack(mR->getIndexPosition());

        // Reproduce sound of the player, selection game mode and difficult level menus
        mR->reproduceSound(s.getTitle(), s.isInLoop() ,s.getVolume());
    }

    // Advance the state of the virtual machine in order to start the game mode
    // selected with the difficult level and the car chosen
    return status;

}



/**
 * Show the options menu with the game configuration
 */
Game_status Game::showOptionsMenu(){
    // Stop the actual sound
    mR->stopSound();

    // Back to the options soundtrack and reproduce
    mR->backSoundtrack();
    Soundtrack s = mR->getSoundtrack(mR->getIndexPosition());
    mR->reproduceSound(s.getTitle(), s.isInLoop() ,s.getVolume());

    // Show the menu of selection vehicle where the player must select one
    menuGame->showMenuOptions(application, "Configuration/Menus/OptionsMenu.xml", control, c, kM, eR);

    // Advance the state of the virtual machine in order to start the game mode
    // selected with the difficult level and the car chosen
    return PLAYER_MENU;
}



void Game::drawQuad(Color c, int x1,int y1,int w1,int x2,int y2,int w2){
    ConvexShape shape(4);
    shape.setFillColor(c);
    shape.setPoint(0, Vector2f(x1-w1,y1));
    shape.setPoint(1, Vector2f(x2-w2,y2));
    shape.setPoint(2, Vector2f(x2+w2,y2));
    shape.setPoint(3, Vector2f(x1+w1,y1));
    application->draw(shape);
}



void Game::playGameSelectedMode(){
    int nm = 2;
    for (int i = 0; i <= 1; i++) {
        vector<LandScape> vm;
        LandScape m(landscapePaths[0], false);
        vm.push_back(m);
        // nm++; // TODO: Añadir más mapas y descomentar
        maps.emplace_back(vm);
    }
    mapId = make_pair(0, 0);
    currentMap = &maps[mapId.first][mapId.second];
    currentMap->addNextMap(&maps[mapId.first + 1][mapId.second]); // TODO: Añadir bifurcación

    // Select the kind of vehicle chosen by the player
    string pathDevastator = "images/Vehicles/Devastator/";
    char* pDevastator = const_cast<char*>(pathDevastator.c_str());
    // Devastator of the player
    Devastator d = Devastator(pDevastator, c);

    string pathMinivan = "images/Vehicles/Minivan/";
    char* pMinivan = const_cast<char*>(pathMinivan.c_str());
    // Minivan of the player
    Minivan mV = Minivan(pMinivan, c);

    string pathMotorbike = "images/Vehicles/Motorbike/";
    char* pMotorbike = const_cast<char*>(pathMotorbike.c_str());
    // Motorbike of the player
    Motorbike mB = Motorbike(pMotorbike, c);

    string pathTruck = "images/Vehicles/Truck/";
    char* pTruck = const_cast<char*>(pathTruck.c_str());
    // Truck of the player
    Truck t = Truck(pTruck, c);

    // Velocity
    int speed = INITIAL_SPEED;

    // Height position unnecessary
    int H = 1500;
    // Not elevation of terrain registered by default
    int lastCamH = H, camH = H;

    // Possible event detected
    bool eventDetected = false;

    int pos;
    string path;
    int timerMusic;
    Elevation el;

    // Select the kind of vehicle selected by the player
    switch(typeOfVehicle){
        case 0:
            // Load vehicle properties of the motorbike
            path = "Configuration/Vehicles/Motorbike.xml";
            mB.loadVehicleProperties(path);
            break;
        case 1:
            // Load vehicle properties of the devastator
            path = "Configuration/Vehicles/Devastator.xml";
            d.loadVehicleProperties(path);
            break;
        case 2:
            // Load vehicle properties of the minivan
            path = "Configuration/Vehicles/Minivan.xml";
            mV.loadVehicleProperties(path);
            break;
        case 3:
            // Load vehicle properties of the truck
            path = "Configuration/Vehicles/Truck.xml";
            t.loadVehicleProperties(path);
            break;
    }

    // Get the actual soundtrack
    mR->getRandomSoundtrack();

    // Get the actual soundtrack
    Soundtrack s = mR->getSoundtrack(mR->getIndexPosition());

    // Reproduce sound of the player, selection game mode and difficult level menus
    mR->reproduceLevelSoundtrack();

    int minutes = 0, secs = 0, decs_in_sec = 0, maxSpeed;
    int timeToPlay = INITIAL_SECS;
    Clock gameClock;
    Time shot_delay = seconds(0.1);
    Time elapsed1, elapsed2;
    elapsed1 = gameClock.getElapsedTime();
    gameClock.restart();

    // Loop of the game until the user end or the console is closed
    while (!finalGame && application->isOpen()) {
        // Clean the console window
        application->clear();

        // Update camera depending of the vehicle selected by the player
        switch(typeOfVehicle){
            case 0:
                currentMap->updateView(mB.getPosition());
                break;
            case 1:
                currentMap->updateView(d.getPosition());
                break;
            case 2:
                currentMap->updateView(mV.getPosition());
                break;
            case 3:
                currentMap->updateView(t.getPosition());
        }

        // Control the possible transitions to other maps
        if (currentMap->isOver()) {
            // TODO: Añadir bifurcación
            mapId.first++;
            if (mapId.first < maps.size()) {
                currentMap = &maps[mapId.first][mapId.second];

                if (mapId.first < maps.size() - 1)
                    currentMap->addNextMap(&maps[mapId.first + 1][mapId.second]);


                // Update the position in the map of the vehicle
                switch(typeOfVehicle){
                    case 0:
                        mB.setPosition(mB.getPosition().first, 0);
                        currentMap->updateView(mB.getPosition());
                        break;
                    case 1:
                        d.setPosition(d.getPosition().first, 0);
                        currentMap->updateView(d.getPosition());
                        break;
                    case 2:
                        mV.setPosition(mV.getPosition().first, 0);
                        currentMap->updateView(mV.getPosition());
                        break;
                    case 3:
                        t.setPosition(t.getPosition().first, 0);
                        currentMap->updateView(t.getPosition());
                }
            }
            else {
                finalGame = true;
            }
        }

        // Draw map
        if (!finalGame){
            currentMap->draw(application, c);
        }

        // Detect possible events in the console window
        Event ev{};
        while (application->pollEvent(ev)) {
            if (ev.type == Event::Closed){
                application->close();
            }
        }

        // Check the possible collision of the vehicle
        int collision;
        switch(typeOfVehicle){
            case 0:
                // Load vehicle properties of the motorbike
                collision = mB.getModeCollision();
                maxSpeed = mB.getMaxSpeed();
                break;
            case 1:
                // Load vehicle properties of the devastator
                collision = d.getModeCollision();
                maxSpeed = d.getMaxSpeed();
                break;
            case 2:
                // Load vehicle properties of the minivan
                collision = mV.getModeCollision();
                maxSpeed = mV.getMaxSpeed();
                break;
            case 3:
                // Load vehicle properties of the truck
                collision = t.getModeCollision();
                maxSpeed = t.getMaxSpeed();
                break;
        }

        // Check the time spent until now
        elapsed2 = gameClock.getElapsedTime();
        if (elapsed2 - elapsed1 >= shot_delay){
            decs_in_sec++;
            if (decs_in_sec == 10){
                decs_in_sec = 0;
                secs++;
                timeToPlay--;
                if (secs == 60){
                    secs = 0;
                    minutes++;
                }
            }
        }
        string time = "";
        time = (minutes < 10) ? time + "0" + to_string(minutes) + ":" : time + to_string(minutes) + ":";
        time = (secs < 10) ? time + "0" + to_string(secs) + ":" : time + to_string(secs) + ":";
        time = (minutes < 10) ? time + "0" + to_string(decs_in_sec) : time + to_string(decs_in_sec);


        application->draw(e.spriteSpeedPanel);
        application->draw(e.spriteElapsedPanel);
        e.textSpeedIndicator.setString(to_string(int(speed / RATIO)));
        e.textSpeedIndicator.setPosition(e.posXFile - e.textSpeedIndicator.getLocalBounds().width,
                                         e.textSpeedIndicator.getPosition().y);

        e.textureSpeedGraphic.loadFromFile(e.pathGraphic, IntRect(0, 0, (speed * 213 / maxSpeed), 20));
        e.spriteSpeedGraphic.setTexture(e.textureSpeedGraphic, true);

        application->draw(e.textSpeedIndicator);
        application->draw(e.spriteSpeedGraphic);

        e.textElapsedIndicator.setString(time);
        application->draw(e.textElapsedIndicator);

        e.textTimePanel.setString("TIME");
        application->draw(e.timeShape);
        application->draw(e.textTimePanel);

        e.textTimeIndicator.setString(to_string(timeToPlay));
        application->draw(e.textTimeIndicator);

        // Check if the player has pressed the key to change the music of the level
        if (d.getConfiguration()->checkChangeMusic()  || mV.getConfiguration()->checkChangeMusic() ||
            mB.getConfiguration()->checkChangeMusic() || t.getConfiguration()->checkChangeMusic() || timerMusic > 0)
        {
            // Check if it's now when the soundtrack has been changed
            if (timerMusic == 0){
                mR->advanceSoundtrackLevel();
            }
            if (timerMusic < 30){
                // Advance the time
                timerMusic++;
                application->draw(mR->getTitleSoundtrack());
            }
            else {
                // Change the music
                timerMusic = 0;
            }
        }

        // e.textDestinyIndicator.setString(to_string(difference) + " Km");
        application->draw(e.localizationPlayer);
        application->draw(e.textDestinyPanel);
        // application->draw(e.textDestinyIndicator);

        switch(typeOfVehicle){
            case 0:
                if (collision == -1){
                    // Get the new elevation of the terrain
                    el = currentMap->getElevation(mB.getPlayerY());
                    // Check the advance of the motorbike of the player
                    mB.advancePlayer(eventDetected, lastCamH, camH, el);
                    // Control the possible actions if the user
                    mB.controlActionPlayer(speed, eventDetected, application, lastCamH, camH, el);
                    // Update the position of the vehicle
                    mB.updatePosition(speed);

                    // Check if there is a new collision
                    if (mB.hasCrashed(mB.getPreviousY(), mB.getPlayerY(), mB.getMinScreenX(), mB.getMaxScreenX(), currentMap) || collision != -1){
                        mB.collisionShow();
                    }

                    // Check the inertia force
                    if (speed > 0) {
                        if (currentMap->getCurveCoefficient(mB.getPlayerY()) > 0.f) {
                            mB.setPosition(mB.getPlayerX() - (0.05f * speed / (mB.getMaxSpeed())) , mB.getPlayerY());
                        }
                        else if (currentMap->getCurveCoefficient(mB.getPlayerY()) < 0.f){
                            mB.setPosition(mB.getPlayerX() + (0.05f * speed / (mB.getMaxSpeed())) , mB.getPlayerY());
                        }
                    }
                }
                else {
                    mB.collisionShow();
                }
                mB.drawPlayer(application, pos);

                // Display the console window
                application->display();

                // Sleep loop
                if (mB.getModeCollision() == -1){
                     sleep(milliseconds(25));
                }
                else {
                     sleep(milliseconds(120));
                }

                break;
            case 1:
                // Get the new elevation of the terrain
                el = currentMap->getElevation(d.getPlayerY());
                // Check the advance of the motorbike of the player
                d.advancePlayer(eventDetected, lastCamH, camH, el);
                // Control the possible actions if the user
                d.controlActionPlayer(speed, eventDetected, application, lastCamH, camH, el);
                // Update the position of the vehicle
                d.updatePosition(speed);
                // Check if there is a new collision
                if (d.hasCrashed(d.getPreviousY(), d.getPlayerY(), d.getMinScreenX(), d.getMaxScreenX(), currentMap) || collision != -1){
                    d.collisionShow();
                }
                pos = (int)d.getPlayerY();
                // Check the inertia force
                if (speed > 0) {
                    if (currentMap->getCurveCoefficient(d.getPlayerY()) > 0.f) {
                        d.setPosition(d.getPlayerX() - (0.05f * speed / (d.getMaxSpeed() * 2.0f)) , d.getPlayerY());
                    }
                    else if (currentMap->getCurveCoefficient(d.getPlayerY()) < 0.f){
                        d.setPosition(d.getPlayerX() + (0.05f * speed / (d.getMaxSpeed() * 2.0f)) , d.getPlayerY());
                    }
                }
                d.drawPlayer(application, pos);
                // Display the console window
                application->display();
                // Sleep loop
                if (mB.getModeCollision() == -1){
                     sleep(milliseconds(25));
                }
                else {
                     sleep(milliseconds(120));
                }
                break;
            case 2:
                // Get the new elevation of the terrain
                el = currentMap->getElevation(mV.getPlayerY());
                // Check the advance of the motorbike of the player
                mV.advancePlayer(eventDetected, lastCamH, camH, el);
                // Control the possible actions if the user
                mV.controlActionPlayer(speed, eventDetected, application, lastCamH, camH, el);
                // Update the position of the vehicle
                mV.updatePosition(speed);
                // Check if there is a new collision
                if (mV.hasCrashed(mV.getPreviousY(), mV.getPlayerY(), mV.getMinScreenX(), mV.getMaxScreenX(), currentMap) || collision != -1){
                    mV.collisionShow();
                }
                pos = (int)mV.getPlayerY();
                // Check the inertia force
                if (speed > 0) {
                    if (currentMap->getCurveCoefficient(mV.getPlayerY()) > 0.f) {
                        mV.setPosition(mV.getPlayerX() - (0.05f * speed / (mV.getMaxSpeed() * 2.0f)) , mV.getPlayerY());
                    }
                    else if (currentMap->getCurveCoefficient(mV.getPlayerY()) < 0.f){
                        mV.setPosition(mV.getPlayerX() + (0.05f * speed / (mV.getMaxSpeed() * 2.0f)) , mV.getPlayerY());
                    }
                }
                mV.drawPlayer(application, pos);
                // Display the console window
                application->display();
                // Sleep loop
                if (mB.getModeCollision() == -1){
                     sleep(milliseconds(25));
                }
                else {
                     sleep(milliseconds(120));
                }
                break;
            case 3:
                // Get the new elevation of the terrain
                el = currentMap->getElevation(t.getPlayerY());
                // Check the advance of the motorbike of the player
                t.advancePlayer(eventDetected, lastCamH, camH, el);
                // Control the possible actions if the user
                t.controlActionPlayer(speed, eventDetected, application, lastCamH, camH, el);
                // Update the position of the vehicle
                t.updatePosition(speed);
                // Check if there is a new collision
                if (t.hasCrashed(t.getPreviousY(), t.getPlayerY(), t.getMinScreenX(), t.getMaxScreenX(), currentMap) || collision != -1){
                    t.collisionShow();
                }
                pos = (int)t.getPlayerY();
                // Check the inertia force
                if (speed > 0) {
                    if (currentMap->getCurveCoefficient(t.getPlayerY()) > 0.f) {
                        t.setPosition(t.getPlayerX() - (0.05f * speed / (t.getMaxSpeed() * 2.0f)) , t.getPlayerY());
                    }
                    else if (currentMap->getCurveCoefficient(t.getPlayerY()) < 0.f){
                        t.setPosition(t.getPlayerX() + (0.05f * speed / (t.getMaxSpeed() * 2.0f)) , t.getPlayerY());
                    }
                }
                t.drawPlayer(application, pos);
                // Display the console window
                application->display();
                // Sleep loop
                if (mB.getModeCollision() == -1){
                     sleep(milliseconds(25));
                }
                else {
                     sleep(milliseconds(120));
                }
        }
    }
}



/**
 * Execute the game mode selected by the user with the difficult selected
 * and also with the vehicle chosen
 */
inline Game_status Game::playingGame(){
    playGameSelectedMode();
}


