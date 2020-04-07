
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

    // Reproduce sega sound for the animation
    mR = new MusicReproductor();

    // Load the default configuration of the game
    c = new Configuration();

    // Initialize the keyword mapper module
    kM = new KeywordMapper();

    // Load the soundtracks from the xml configuration file
    mR->loadSoundtracksOfGame("Configuration/Soundtracks/Soundtracks.xml");

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
    animationGame->loadSegaIcons(application);

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
    menuGame->showMainMenu(application);

    // Stop the intro sound of the main menu
    mR->stopSound();

    // Advance the state machine of the game to present the player mode menu
    return PLAYER_MENU;
}



/**
 * Show the player menu of the game
 */
Game_status Game::showPlayerMenu(){
    // Get the actual soundtrack
    Soundtrack s = mR->getSoundtrack(mR->getIndexPosition());

    // Reproduce sound of the player, selection game mode and difficult level menus
    mR->reproduceSound(s.getTitle(), s.isInLoop() ,s.getVolume());

    // Show the selector menu of the players
    menuGame->showStandardMenu(application, "Configuration/Menus/PlayerMenu.xml", modePlayerSelected, status);

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
    menuGame->showStandardMenu(application, "Configuration/Menus/GameMenu.xml", modeGameSelected, status);

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
    menuGame->showStandardMenu(application, "Configuration/Menus/DifficultLevelMenu.xml", modeDifficultLevelSelected, status);

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
    gSM.loadFileConfigurationMode(e);

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
    menuGame->showSelectionVehicleMenu(application, typeOfVehicle, colorVehicle, status);

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
    // Show the menu of selection vehicle where the player must select one
    menuGame->showMenuOptions(application, "Configuration/Menus/OptionsMenu.xml", control, c, kM);

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



/**
 * Execute the game mode selected by the user with the difficult selected
 * and also with the vehicle chosen
 */
inline Game_status Game::playingGame(){
    // Get the actual soundtrack
    mR->getRandomSoundtrack();

    // Get the actual soundtrack
    Soundtrack s = mR->getSoundtrack(mR->getIndexPosition());

    // Reproduce sound of the player, selection game mode and difficult level menus
    mR->reproduceLevelSoundtrack();

    int minutes = 0, secs = 0, decs_in_sec = 0;
    int timeToPlay = INITIAL_SECS;
    Clock gameClock;
    Time shot_delay = seconds(0.1);
    Time elapsed1, elapsed2;
    elapsed1 = gameClock.getElapsedTime();
    gameClock.restart();

    // Select the kind of vehicle selected by the player
    switch(typeOfVehicle){
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
    }

    string path = "images/Vehicles/Devastator/";
    char* p = const_cast<char*>(path.c_str());
    // Motorbike of the player
    Devastator h = Devastator(p, c);

    h.loadVehicleProperties();

    vector<string> landscapes = gSM.getVectorOfLandScapes();
    char* n = const_cast<char*>(landscapes[0].c_str());
    LandScape L = LandScape(n);

    // Number of steps done
    int pos = 0, lastPos = 0;
    // Height position unnecessary
    int H = 1500;

    // Next checkpoint to arrive
    int indexCheckpoint = 0;

    // Position of the next checkpoint to arrive
    int posCheckPoint = L.checkpointsScene.at(indexCheckpoint).stepPosition * segL;

    // Not elevation of terrain registered by default
    int lastCamH = H, camH = H;

    // Possible event detected
    bool eventDetected = false;

    // Colors of the map
    Color grass, rumble, middle, road;

    // Possible event detected
    bool onCurve = false;

    // Velocity
    int speed = INITIAL_SPEED;

    // Variable to control the different possible curves
    IntervalCurve curve;

    // Controller displayer of the title music
    int timerMusic;

    // Controlling possible events in the console of the game
    Event ev;

    // While the game console is opened
    while (application->isOpen()){

        // Detect possible actions of the user on the console game
        if (application->pollEvent(ev) && ev.type == Event::Closed){
                application->close();
        }

        // New speed updated
        if (h.getModeCollision() == -1){
            // Check the advance of the motorbike of the player
            h.advancePlayer(eventDetected, lastCamH, camH);

            // Control the possible actions if the user
            h.controlActionPlayer(speed, eventDetected, application, lastCamH, camH);

            // Store my the actual position before the move
            lastPos = pos;

            pos += speed;

            // Store the actual elevation of the terrain
            lastCamH = camH;
        }

        // Get the nearest sprite found to the actual position
        Step nearestStep;

        // Checking of the motorbike is in a curve of the scene
        nearestStep = L.checkingPossibleCollision(pos);

        // Check possible collisions of the motorbike or if there is a collision been processed now
        if (h.controlPossibleCollision(nearestStep, lastPos, pos) || h.getModeCollision() != -1){
            // There is collision
            h.collisionShow();
            speed = INITIAL_SPEED;
        }

        // Control if the player passes the checkpoint
        if (pos >= posCheckPoint){
            // Increment the index to the next checkpoint
            if (indexCheckpoint >= (int)L.checkpointsScene.size() - 1){
                posCheckPoint = L.goalPoint.stepPosition * segL;
            }
            else {
                // Get the position of the next checkpoint to arrive
                indexCheckpoint++;
                posCheckPoint = L.checkpointsScene.at(indexCheckpoint).stepPosition * segL;
            }
            // Restarted the time to arrive to the next checkpoint
            timeToPlay = INITIAL_SECS;
        }

        L.lookForCurve(pos, curve, onCurve);

        // Control the inertia force of the motorbike
        h.controlInertiaForce(onCurve, curve, speed);

        // Check the upper bound limit
        while (pos >=  MAX_SPACE_DIMENSION * segL){
            pos -= MAX_SPACE_DIMENSION * segL;
        }

        // Check the lower bound limit
        while (pos < 0){
            pos += MAX_SPACE_DIMENSION * segL;
        }

        // Rendering the landscape of Sherwood forest
        application->clear(Color(105, 205, 4));
        application->draw(L.getBackGround());

        // Preparing to draw the new elements of the map
        int startPos = pos / segL;
        camH = L.lines[startPos].position_3d_y + H;

        // Check if advance
        if (speed > 0 && h.getModeCollision() == -1){
            // Advance
            // Checking of the motorbike is in a curve of the scene
            Sprite newBack;
            newBack = L.getBackGround();
            newBack.move(-(L.lines[startPos].directionCurve) * 2, 0);
            L.setBackGround(newBack);
        }

        // Variables
        int maxy = HEIGHT;
        float x = 0, dx = 0;

        // Drawing the road
        for(int n = startPos; n < startPos + 300; n++){
            // Create a new line
            Step &l = L.lines[n % MAX_SPACE_DIMENSION];
            // Project the 3d coordinates in 2d coordinates image
            l.project(h.getPlayerX() * WIDTH_ROAD - x, camH, startPos * segL - (n>= MAX_SPACE_DIMENSION ? MAX_SPACE_DIMENSION * segL : 0));

            x += dx;
            dx += l.directionCurve;

            l.clip = maxy;
            if (l.position_2d_y < maxy){
                maxy = l.position_2d_y;

                // Paint the scene
                L.paintScene(n, grass, rumble, middle, road);
                Step p = L.lines[(n - 1)% MAX_SPACE_DIMENSION];

                // Draw the grass and the road
                drawQuad(grass, 0, p.position_2d_y, WIDTH, 0, l.position_2d_y, WIDTH);
                drawQuad(rumble, p.position_2d_x, p.position_2d_y, p.position_2d_w * 1.2, l.position_2d_x, l.position_2d_y, l.position_2d_w * 1.2);
                drawQuad(road,  p.position_2d_x, p.position_2d_y, p.position_2d_w, l.position_2d_x, l.position_2d_y, l.position_2d_w);
                drawQuad(middle, p.position_2d_x, p.position_2d_y, p.position_2d_w * 0.05, l.position_2d_x, l.position_2d_y, l.position_2d_w * 0.05);
            }
       }
       // Drawing the objects of the map
       for(int n = startPos + 300; n > startPos; n--){
          // Draw sprite in that position
          L.lines[n % MAX_SPACE_DIMENSION].drawSprite(application);
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

       //Show all the elements in the console game
       h.drawPlayer(application, pos);
       application->draw(e.spriteSpeedPanel);
       application->draw(e.spriteElapsedPanel);
       e.textSpeedIndicator.setString(to_string(int(speed / RATIO)));
       application->draw( e.textSpeedIndicator);

       e.textElapsedIndicator.setString(time);
       application->draw(e.textElapsedIndicator);

       e.textTimePanel.setString("TIME");
       application->draw(e.textTimePanel);

       e.textTimeIndicator.setString(to_string(timeToPlay));
       application->draw(e.textTimeIndicator);

       int difference = (posCheckPoint - pos) / 1000;
       if (indexCheckpoint <= (int)L.checkpointsScene.size() - 1){
            // Shows information to the user
            // Calculation of the distance to arrive
            if (difference > 250){
                e.textDestinyIndicator.setFillColor(Color::Green);
            }
            else if (difference >= 100){
                e.textDestinyIndicator.setFillColor(Color::Yellow);
            }
            else {
                e.textDestinyIndicator.setFillColor(Color::Red);
            }
       }
       else {
            e.message = "GOAL";
            e.textDestinyPanel.setPosition(e.textDestinyPanel.getPosition().x + 50 , e.textDestinyPanel.getPosition().y);
            e.textDestinyPanel.setString(e.message);
       }


       // Check if the player has pressed the key to change the music of the level
       if (h.getConfiguration()->checkChangeMusic() || timerMusic > 0){
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

       e.textDestinyIndicator.setString(to_string(difference) + " Km");
       application->draw(e.textDestinyPanel);
       application->draw(e.textDestinyIndicator);
       application->display();

       // Sleep loop
       if (h.getModeCollision() == -1){
            sleep(milliseconds(70));
       }
       else {
            sleep(milliseconds(120));
       }
    }
}


