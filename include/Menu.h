#pragma once

#ifndef MENU_H
#define MENU_H

#include <vector>
#include <memory>
#include <iostream>
#include "Button.h"
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
 * Animación inicial.
 * @param c
 * @return
 */
State introAnimation(Configuration &c, SoundPlayer& r);

/**
 * Menú de opciones.
 * @param c
 * @param inGame
 * @return
 */
State optionsMenu(Configuration &c, SoundPlayer& r, const bool &inGame);

/**
 * Menú para cambiar los controles.
 * @param c
 * @return
 */
State changeCarControllers(Configuration &c, SoundPlayer& r);



/**
 * Load the configuration of the main menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadMainMenuConfiguration(const string path, Configuration& c);



/**
 * Displays the main menu of the game
 * @param c is the configuration of the file
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
 * Load the configuration of the player menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
 State playerMenu(Configuration &c, SoundPlayer& r);



/**
 * Load the configuration of the game modes menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadGameModesMenuConfiguration(const string path, Configuration& c);



/**
 * Load the configuration of the game modes menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 * @param typeOfGame is the game mode selected by the player
 */
State gameModesMenu(Configuration &c, SoundPlayer& r, int& typeOfGame);



/**
 * Load the configuration of the sound menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadSoundMenuConfiguration(const string path, Configuration& c);



/**
 * Load the configuration of the sound menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
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
 * Load the configuration of the options menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
State optionsMenu(Configuration &c, SoundPlayer& r, const bool &inGame, float& offsetLapIndicator, bool& newLap);



/**
 * Load the configuration of the vehicle controllers menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadVehicleControllersMenuConfiguration(const string path, Configuration& c);



/**
 * Load the configuration of the vehicle controllers menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
State vehicleControllersMenu(Configuration &c, SoundPlayer& r);




/**
 * Pantalla del ranking.
 * @param c
 * @param scorePlayerGame
 * @param minutes
 * @param decs
 * @param cents_Second
 * @return
 */
State rankingMenu(Configuration &c, SoundPlayer& r, unsigned long scorePlayerGame,
                  int minutes, int decs, int cents_Second, const int typeOfGame);



void updateGameConfiguration(const string path, const Difficult difficulty, const int volumeSoundtracks,
                             const int volumeEffects, const bool pixelArt, const int fullScreen, const int axis_x,
                             const int axis_y, const string controlLeft, const string controlRight, const string controlAccelerate,
                             const string controlBrake, const string controlSoundtrack);


State showLoadingAnimation(Configuration& c, SoundPlayer& r);



/**
 * Load the configuration of the player menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadMultiplayerMenuConfiguration(const string path, Configuration& c);



State multiplayerMenu(Configuration& c, SoundPlayer& r, int& multiplayerMode);



#endif // MENU_H
