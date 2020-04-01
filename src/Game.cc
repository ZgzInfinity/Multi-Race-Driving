
#include "../include/Game.h"

Game::Game(RenderWindow* app) {

    application = app;

    // Creation of the animation
    string animationFile = "Configuration/Animations/Animations.xml";
    char* animationF = const_cast<char*>(animationFile.c_str());
    animationGame = new Animation(animationF);

    // Creation of the menus
    menuGame = new Menu();

    // Showing the animation of the sega logo
    animationGame->loadSegaIcons(application);

    // Shwoing the company and the presents logo of the game
    animationGame->loadGameData(application);

    // Show the main menu
    menuGame->showMainMenu(application);

    // Control the player mode selected
    int modePlayerSelected;

    // Control the game mode selected
    int modeGameSelected;

    // Control the difficult level selected
    int modeDifficultLevelSelected;

    // Show the selector menu of the players
    menuGame->showStandardMenu(application, "Configuration/Menus/PlayerMenu.xml", modePlayerSelected);

    // Show the selector game modes
    menuGame->showStandardMenu(application, "Configuration/Menus/GameMenu.xml", modeGameSelected);

    // Show the selector difficult level of the game
    menuGame->showStandardMenu(application, "Configuration/Menus/DifficultLevelMenu.xml", modeDifficultLevelSelected);

    // Creation of the game selector mode controller
    gSM = GameSelectorMode(modeDifficultLevelSelected, modeGameSelected);

    // Load the game mode configuration selected by the player
    gSM.loadFileConfigurationMode(e);

    // Control the type of vehicle selected with also its color
    int typeOfVehicle, colorVehicle;

    // Show the menu of selection vehicle
    menuGame->showSelectionVehicleMenu(application, typeOfVehicle, colorVehicle);

    // Play the game
    playingGame();
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



inline void Game::playingGame(){

    int minutes = 0, secs = 0, decs_in_sec = 0;
    int timeToPlay = INITIAL_SECS;
    Clock gameClock;
    Time shot_delay = seconds(0.1);
    Time elapsed1, elapsed2;
    elapsed1 = gameClock.getElapsedTime();
    gameClock.restart();

    string path = "images/Vehicles/Devastator/";
    char* p = const_cast<char*>(path.c_str());
    // Motorbike of the player
    Devastator h = Devastator(p);

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


