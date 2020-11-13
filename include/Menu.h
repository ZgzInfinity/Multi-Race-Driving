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



/*
 * Module Menu interface file
 */

#pragma once

#ifndef MENU_H
#define MENU_H

#include <vector>
#include <memory>
#include <iostream>
#include "Button.h"
#include "windows.h"
#include "KeywordMapper.h"
#include "Score.h"
#include "Configuration.h"
#include "SoundPlayer.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


using namespace std;
using namespace sf;
using namespace rapidxml;

const int TIME_ANIMATION = 39;
const int NUM_SOUNDTRACKS = 4;



/**
 * Shows the initial animation of the game
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 * @return
 */
State introAnimation(Configuration &c, SoundPlayer& r);



/**
 * Load the configuration of the main menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadMainMenuConfiguration(const string path, Configuration& c);



/**
 * Displays the main menu of the game
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 * @param startPressed controls if the enter key has been pressed
 * @return
 */
State startMenu(Configuration &c, SoundPlayer &r, bool startPressed = false);



/**
 * Load the configuration of the player menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadPlayerMenuConfiguration(const string path, Configuration& c);



/**
 * Load the configuration of the player menu stored in its xml configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
 State playerMenu(Configuration &c, SoundPlayer& r);



/**
 * Load the configuration of the game modes menu stored in its xml configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadGameModesMenuConfiguration(const string path, Configuration& c);



/**
 * Load the configuration of the game modes menu stored in its xml configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 * @param typeOfGame is the game mode selected by the player
 */
State gameModesMenu(Configuration &c, SoundPlayer& r, int& typeOfGame);



/**
 * Load the configuration of the sound menu stored in its xml configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadSoundMenuConfiguration(const string path, Configuration& c);



/**
 * Load the configuration of the sound menu stored in its xml configuration file
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 * @param inGame controls if the player was playing before entering to the sound menu
 */
State soundMenu(Configuration &c, SoundPlayer& r, const bool &inGame);



/**
 * Load the configuration of the options menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadOptionsMenuConfiguration(const string path, Configuration& c);



/**
 * Shows the options menu of the game
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 * @param inGame controls if the player was in game before enter in the options menu
 * @return
 */
State optionsMenu(Configuration &c, SoundPlayer& r, const bool &inGame);




/**
 * Load the configuration of the vehicle controllers menu stored in its xml configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadVehicleControllersMenuConfiguration(const string path, Configuration& c);



/**
 * Load the configuration of the vehicle controllers menu stored in its xml configuration file
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 */
State vehicleControllersMenu(Configuration &c, SoundPlayer& r);



/**
 * Shows the ranking menu with best seven players of the Out Run mode
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 * @param minutes is the number of minutes that the game has lasted
 * @param decs is the number of seconds that the game has lasted
 * @param cents_Second is the number of hundredths of second that the game has lasted
 * @param typeOfGame is the game mode selected by the player
 * @return
 */
State rankingMenu(Configuration &c, SoundPlayer& r, unsigned long scorePlayerGame,
                  int minutes, int decs, int cents_Second, const int typeOfGame);



/**
 * Updates the current configuration of the game by a new one modifying
 * the xml configuration file
 * @param path is the path the xml configuration file
 * @param difficulty is the level of difficulty selected by the player
 * @param volumeSoundtracks is the volume of the soundtracks selected by the player
 * @param volumeEffects is the volume of the sound effects selected by the player
 * @param pixelArt controls if the graphics must be rendered with pixel art effect or not
 * @param fullScreen controls if the game must be load in full screen or not
 * @param axis_x is the width of the window's game
 * @param axis_y is the height of the window's game
 * @param controlLeft is the key selected by the player to turn the vehicle to the left
 * @param controlRight is the key selected by the player to turn the vehicle to the right
 * @param controlAccelerate is the key selected by the player to accelerate the vehicle
 * @param controlBrake is the key selected by the player to brake the vehicle
 * @param controlSoundtrack is the key selected by the player to change the soundtrack of the game
 */
void updateGameConfiguration(const string path, const Difficult difficulty, const int volumeSoundtracks,
                             const int volumeEffects, const bool pixelArt, const bool fullScreen, const int axis_x,
                             const int axis_y, const string controlLeft, const string controlRight, const string controlAccelerate,
                             const string controlBrake, const string controlSoundtrack);



/**
 * Shows a loading animation with the current controllers of the game
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 * @param onMultiplayer controls if the multi player mode is been played or not
 */
State showLoadingAnimation(Configuration& c, SoundPlayer& r, const bool onMultiplayer);



/**
 * Load the configuration of the multi player menu stored in its xml configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadMultiplayerMenuConfiguration(const string path, Configuration& c);



/**
 * Shows the main multi player menu
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 * @param multiplayerMode controls how the player has selected to play in multi player mode
 */
State multiplayerMenu(Configuration& c, SoundPlayer& r, int& multiplayerMode);



/**
 * Shows the credits of the platform
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 */
State credits(Configuration& c, SoundPlayer& r);



#endif // MENU_H
