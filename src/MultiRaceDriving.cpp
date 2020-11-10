/*
 * Copyright (c) 2020 Andrés Gavín
 * Copyright (c) 2020 Rubén Rodríguez
 *
 * This file is part of Out Run.
 * Out Run is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Out Run is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Out Run.  If not, see <https://www.gnu.org/licenses/>.
 */



/*
 * ----------------------------------------------
 * Multi Race Driving: A general and customized
 * platform for 2.5D racing games
 * Author: ZgzInfinity
 * Date: 28-09-20
 * ----------------------------------------------
 */

#define _WIN32_WINNT 0x0500

#include <thread>
#include "windows.h"
#include "../include/Menu.h"
#include "../include/Game.h"
#include "../include/SoundPlayer.h"
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;



mutex mainMutex, multiplayerMutex;

// Variables to control the connection to the multi player server
string domain, port;


/**
 * Load the current configuration of the game
 * @param path is the xml file with the configuration
 * @param difficulty is the difficulty of the game
 * @param volumeSoundtracks is the volume of the music
 * @param volumeEffects is the volume of the SFX
 * @param pixelArt controls if the graphics have to be drawn with pixel art
 * @param fullScreen controls if the screen has to be drawn in completed screen
 * @param axis_x is the width of the screen
 * @param axis_y is the height of the screen
 * @param controlLeft controls the key to move the vehicle of the player to the left
 * @param controlRight controls the key to move the vehicle of the player to the right
 * @param controlAccelerate controls the key to accelerate the vehicle of the player
 * @param controlBrake controls the key to brake the vehicle of the player
 * @param controlSoundtrack controls the key to change the soundtrack of the game
 */
 void loadGameConfiguration (const string path, Difficult& difficulty, int& volumeSoundtracks,
                            int& volumeEffects, bool& pixelArt, bool& fullScreen, int& axis_x, int& axis_y, string& controlLeft,
                            string& controlRight, string& controlAccelerate, string& controlBrake,
                            string& controlSoundtrack)
{

     // Open the xml file of the scenario
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Iterate the different configuration nodes
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check if it's the node that control the difficulty of the level
        if ((string)property->name() == "Difficulty"){
            // Get the difficulty value
            if ((string)property->value() == "Easy"){
                // Level easy
                difficulty = EASY;
            }
            else if ((string)property->value() == "Normal"){
                // Level normal
                difficulty = NORMAL;
            }
            else if ((string)property->value() == "Hard"){
                // Level hard
                difficulty = HARD;
            }
        }
        // Check if it`s the node that controls the soundtracks volume
        else if ((string)property->name() == "Volume_Soundtracks"){
            // Get the volume
            volumeSoundtracks = stoi(property->value());
        }
        // Check if it's the node that controls the soundtracks volume
        else if ((string)property->name() == "Volume_Effects"){
            // Get the volume
            volumeEffects = stoi(property->value());
        }
        // Check if it's the node that controls the soundtracks volume
        else if ((string)property->name() == "PixelArt"){
            // Get if the pixelArt is enabled
            if ((string)property->value() == "Enabled"){
                pixelArt = true;
            }
            else {
                pixelArt = false;
            }
        }
        // Check if it's the node that controls the soundtracks volume
        else if ((string)property->name() == "Full_screen"){
            // Get if the pixelArt is enabled
            if ((string)property->value() == "Enabled"){
                fullScreen = true;
            }
            else {
                fullScreen = false;
            }
        }
        // Check if it's the node that controls the x resolution of the screen
        else if ((string)property->name() == "Resolution_x"){
            // Get the resolution in axis x
            axis_x = stoi(property->value());
        }
        // Check if it's the node that controls the y resolution of the screen
        else if ((string)property->name() == "Resolution_y"){
            // Get the resolution in axis y
            axis_y = stoi(property->value());
        }
        // Check if it's the node that controls the turning left control
        else if ((string)property->name() == "Controller_left"){
            // Get the turning left controller
            controlLeft = property->value();
        }
        // Check if it's the node that controls the turning right control
        else if ((string)property->name() == "Controller_right"){
            // Get the turning right controller
            controlRight = property->value();
        }
        // Check if it's the node that controls the accelerating control
        else if ((string)property->name() == "Controller_accelerate"){
            // Get the turning left controller
            controlAccelerate = property->value();
        }
        // Check if it's the node that controls the braking control
        else if ((string)property->name() == "Controller_brake"){
            // Get the turning right controller
            controlBrake = property->value();
        }
        // Check if it's the node that controls the changing soundtrack control
        else if ((string)property->name() == "Controller_soundtrack"){
            // Get the turning right controller
            controlSoundtrack = property->value();
        }
    }
}



/**
 * Load the current of the multi player server
 * @param path is the xml file with the configuration
 */
void loadServerConfiguration (const string path){
    // Open the xml file of the scenario
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Iterate the different configuration nodes
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check if it's the node that controls the domain of the server
        if ((string)property->name() == "Domain"){
            // Get the resolution in axis x
            domain = string(property->value());
        }
        // Check if it's the node that controls the port of the server
        else if ((string)property->name() == "Port"){
            // Get the resolution in axis y
            port = string(property->value());
        }
    }
}



/**
 * Main program that controls Multi Race Driving
 */
int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show){

    // Calling sell to execute ping command to make the tests

    AllocConsole();
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    // Throw the application with hight priority
    SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

    // Load the properties of the game
    string path = "Data/Settings/Configuration.xml";

    // Variables to control the configuration of the game
    Difficult difficulty;
    bool pixelArt, fullScreen;
    int volumeSoundtracks, volumeEffects, axis_x, axis_y;
    string controlLeft, controlRight, controlAccelerate, controlBrake, controlSoundtrack;

    loadGameConfiguration(path, difficulty, volumeSoundtracks, volumeEffects, pixelArt, fullScreen, axis_x, axis_y,
                          controlLeft, controlRight, controlAccelerate, controlBrake, controlSoundtrack);

    // Creation of the configuration module of the game
    Configuration c(difficulty, pixelArt, fullScreen, axis_x, axis_y, controlLeft, controlRight, controlAccelerate,
                    controlBrake, controlSoundtrack);

    // Load the properties of the multi player server
    path = "Data/Settings/Multiplayer.xml";

    // Load the multi player configuration server
    loadServerConfiguration(path);

    // Creation of the reproductor module of the game
    SoundPlayer r(volumeSoundtracks, volumeEffects);

    State state = ANIMATION;

    while (c.window.isOpen() && state != EXIT) {
        Game engine(c);

        sleep(milliseconds(500));
        if (state == START)
            state = startMenu(c, r);

        while (c.window.isOpen() && state != START) {
            switch (state) {
                case ANIMATION: {
                    state = introAnimation(c, r);
                    break;
                }
                case CREDITS: {
                    state = credits(c, r);
                    break;
                }
                case OPTIONS: {
                    sleep(milliseconds(500));
                    bool inGame = engine.isInGame();
                    state = optionsMenu(c, r, inGame);
                    engine.checkDifficulty(c);
                    break;
                }
                case PLAYER_MENU: {
                    engine.setMultiplayer();
                    state = playerMenu(c, r);
                    break;
                }
                case TESTTING_NETWORK: {
                    state = engine.makeConnectionServerTest(c, r);
                    break;
                }
                case MULTIPLAYER_MENU: {
                    int multiPlayerMode;
                    state = multiplayerMenu(c, r, multiPlayerMode);
                    if (state == MULTIPLAYER_NAME_PLAYER){
                        engine.setMultiplayerMode(multiPlayerMode);
                    }
                    break;
                }
                case MULTIPLAYER_NAME_PLAYER: {
                    // Ask the name of the player in multi player mode
                    state = engine.introduceNameMultiplayer(c, r);
                    break;
                }
                case MULTIPLAYER_NAME_GROUP: {
                    // Ask the name of the player in multi player mode
                    state = engine.introduceGroupMultiplayer(c, r);
                    break;
                }
                case SELECT_MULTIPLAYER_JOIN: {
                    // Select how to join to a group in multi player mode
                    state = engine.selectJoiningMode(c, r);
                    break;
                }
                case CREATION_GROUPS_MULTIPLAYER: {
                    // Play the multi player mode
                    state = engine.creationOfGroups(c, r);
                    break;
                }
                case SELECTION_MODE_MULTIPLAYER: {
                    // Selection of the game to play in multi player mode
                    state = engine.selectionModeMultiplayer(c, r);
                    break;
                }
                case SELECTION_CIRCUIT_MULTIPLAYER: {
                    // Select the circuit in multi player mode
                    state = engine.selectionCircuitMultiplayer(c, r);
                    break;
                }
                case GAME_MODES_MENU: {
                    // Get the type of game selected by the user
                    int typeOfGame = engine.typeGame();
                    state = gameModesMenu(c, r, typeOfGame);

                    // Assign the type of game selected by the user
                    engine.setTypeOfGame(typeOfGame);
                    break;
                }
                case RIVAL_TYPE_MENU: {
                    // Select the rival type vehicle
                    state = engine.selectionRivalTypeMenu(c, r);
                    break;
                }
                case VEHICLE_SELECTION: {
                    // Select the vehicle by the player
                    state = engine.selectionVehicleMenu(c, r);
                    break;
                }
                case CIRCUIT_SELECTION_MENU: {
                    // Select the circuit to run in Pole Position
                    state = engine.selectionCircuitMenu(c, r);
                    break;
                }
                case LOAD_GAME: {
                    // Get the type of game selected by the user
                    int typeOfGame = engine.typeGame();

                    // Load the configuration depending of the game
                    switch(typeOfGame){
                        case 0:
                            // World tour mode
                            state = engine.loadWorldTourPolePositionConf(c);
                            break;
                        case 1:
                            // Out Run mode
                            state = engine.loadOutRunDrivingFuryDemarrageConf(c);
                            break;
                        case 2:
                            // Pole Position mode
                            state = engine.loadWorldTourPolePositionConf(c);
                            break;
                        case 3:
                            // Driving fury mode
                            state = engine.loadOutRunDrivingFuryDemarrageConf(c);
                            break;
                        case 4:
                            // Demarrage mode
                            state = engine.loadOutRunDrivingFuryDemarrageConf(c);
                    }
                    break;
                }
                case LOADING: {
                    // Show the loading animation
                    bool multiplayer = engine.getOnMultiplayerMode();
                    state = showLoadingAnimation(c, r, multiplayer);
                    break;
                }
                case PLAY_GAME: {
                    // Start the corresponding game selected by the player
                    bool onMultiplayer = engine.getOnMultiplayerMode();
                    if (onMultiplayer){
                        state = engine.playWorldTourPolePositionMultiplayer(c, r);
                    }
                    else {
                        int typeOfGame = engine.typeGame();
                        if (typeOfGame == 0 || typeOfGame == 2){
                            state = engine.playWorldTourPolePosition(c, r);
                        }
                        else {
                            state = engine.playOutRunDrivingFuryDemarrage(c, r);
                        }
                    }
                    break;
                }
                case CLASIFICATION: {
                    state = engine.classificationRace(c, r);
                    break;
                }
                case RANKING: {
                    unsigned long scorePlayer = engine.getScore();
                    int minutes = int(engine.getMinutesTrip());
                    int secs = int(engine.getSecsTrip());
                    int cents_Second = int(engine.getCents_SecondTrip());
                    int typeOfGame = engine.typeGame();
                    state = rankingMenu(c, r, scorePlayer, minutes, secs, cents_Second, typeOfGame);
                    break;
                }
                default: {
                    c.window.close();
                    break;
                }
            }
        }
    }
}
