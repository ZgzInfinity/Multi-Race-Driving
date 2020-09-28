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
 * Module Configuration interface file
 */

#pragma once

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include<vector>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "Button.h"
#include "SoundPlayer.h"
#include "KeywordMapper.h"


using namespace std;
using namespace sf;

const int DEFAULT_WIDTH = 921;
const int DEFAULT_HEIGHT = 691;
const int SCREEN_HD_WIDTH = 1280;
const int SCREEN_HD_HEIGHT = 720;
const int FPS = 60;
const int VERTICAL_OFFSET = 30;
const float IMAGE_DEFAULT_OFFSET = 1.3f;

const pair<const int ,const int> SCREEN_DEFAULT = make_pair(DEFAULT_WIDTH, DEFAULT_HEIGHT);
const pair<const int ,const int> SCREEN_1 = make_pair(SCREEN_HD_WIDTH, SCREEN_HD_HEIGHT);
const pair<const int ,const int> SCREEN_2 = make_pair(1366, 768);
const pair<const int ,const int> SCREEN_3 = make_pair(1920, 1080);
const pair<const int ,const int> SCREEN_4 = make_pair(2560, 1440);
const pair<const int ,const int> SCREEN_5 = make_pair(3840, 2160);

// Possible states of the game
enum State {
    ANIMATION,
    START,
    CREDITS,
    OPTIONS,
    PLAYER_MENU,
    MULTIPLAYER_MENU,
    GAME_MODES_MENU,
    RIVAL_TYPE_MENU,
    VEHICLE_SELECTION,
    CIRCUIT_SELECTION_MENU,
    LOAD_GAME,
    LOADING,
    PLAY_GAME,
    RANKING,
    CLASIFICATION,
    MULTIPLAYER_NAME_PLAYER,
    MULTIPLAYER_NAME_GROUP,
    SELECT_MULTIPLAYER_JOIN,
    CREATION_GROUPS_MULTIPLAYER,
    SELECTION_MODE_MULTIPLAYER,
    SELECTION_CIRCUIT_MULTIPLAYER,
    TESTTING_NETWORK,
    EXIT
};


// Levels of difficulty of the game
enum Difficult {
    EASY,
    NORMAL,
    HARD
};



/*
 * Represents the configuration module of the game
 */
struct Configuration {

    // Vector of resolutions for the game
    const vector<pair<int, int>> resolutions;

    // Texture displayed in the screen of the game
    RenderTexture w;

    // Screen of the game
    RenderWindow window;

    // Factor of screen resolution
    float screenScale;

    // Control if the game is with the default resolution or not
    bool isDefaultScreen;

    // Index of the resolution used
    int resIndex;

    // Back key
    Keyboard::Key menuKey;

    // Up key
    Keyboard::Key menuUpKey;

    // Down key
    Keyboard::Key menuDownKey;

    // Start key
    Keyboard::Key menuEnterKey;

    // Key to accelerate the vehicle
    Keyboard::Key accelerateKey;

    // Key to brake the vehicle
    Keyboard::Key brakeKey;

    // Key to move to the left the vehicle
    Keyboard::Key leftKey;

    // Key to move to the right the vehicle
    Keyboard::Key rightKey;

    // Key used to change the music soundtrack during the game
    Keyboard::Key soundtrackKey;

    // Font to write the time of the time elapsed panel
    Font fontElapsedTime;

    // Font to write the interface of the game
    Font fontTimeToPlay;

    // Font to write the animations
    Font fontMenus;

    // Font to write the speed of the vehicle driven
    Font speedVehicle;

    const float camD; // Camera depth
    int renderLen; // Length rendered

    // Difficult level
    Difficult level;

    // Control if the configuration has been changed correctly
    bool modifiedConfig;

    // Control if any parameter if the configuration has been changed
    bool changeAnyParameter;

    // max AI aggressiveness level: max probability that the ai will be activated
    float maxAggressiveness;
    bool enableAI;

    // Control the view of graphics more retro
    bool enablePixelArt;

    // Control if the options menu has been visited
    bool comeFromOptions;

    // Separation between words in the description of the buttons in axis x and y
    int thresholdDescriptionX, thresholdDescriptionY;

    // Control if the main menu has been read before or not
    bool mainMenuRead;

    // Texture of the background
    Texture textureBackground;
    Sprite sBackground;

    // Colors of the main menu
    vector<Color> colorTexts;
    vector<Color> colorBorders;

    // Vector of the fonts of the main menu
    vector<Font> fontsMainMenu;

    // Vector of contents of the main menu
    vector<string> contents;

    // Control if the player menu has been read before or not
    bool playerMenuRead;

    // Texture of the background
    Texture playerMenuBackground;
    Sprite sPlayerMenuBackground;

    // Texture of the background panel
    Texture playerMenuPanelBack;

    // Color border of the main panel
    Color colorBorderPanelPlayerMenu;

    // Contents of the player menu title
    string contentTitlePlayerMenu;

    // Font of the title text of the menu
    Font fontPlayerMenu;

    // Colors of the main text of the player menu
    Color colorTitleTextPlayerMenu;
    Color colorTitleBorderPlayerMenu;

    // Colors of the description panel of the player menu
    Color colorDescriptionPanelInsidePlayerMenu;
    Color colorDescriptionPanelBorderPlayerMenu;

    // Font of the buttons of the menu
    Font fontMenuPlayerButtons;

    // Vector of buttons of the player menu
    vector<Button> menuPlayerButtons;

    // Color of the font buttons in the menu player
    Color colorFontMenuPlayerButtons;

    // Images that are displayed with the buttons description
    vector<Texture> texturesIconPlayerMenu;
    vector<Sprite> iconButtonsPlayerMenu;

    // Image offset to display the images in the player menu
    float imageOffset;

    // Control if the player has visited the options menu before
    bool fromOptions;

    // Control if the game modes menu has been read before or not
    bool gameModesMenuRead;

    // Texture of the background
    Texture gameModesMenuBackground;
    Sprite sGameModesBackground;

    // Texture of the background panel
    Texture gameModesMenuPanelBack;

    // Color border of the main panel
    Color colorBorderPanelGameModeMenu;

    // Contents of the game modes menu title
    string contentTitleGameModeMenu;

    // Font of the title text of the menu
    Font fontGameModeMenu;

    // Colors of the main text of the game modes menu
    Color colorTitleTextGameModeMenu;
    Color colorTitleBorderGameModeMenu;

    // Colors of the description panel of the game modes menu
    Color colorDescriptionPanelInsideGameModeMenu;
    Color colorDescriptionPanelBorderGameModeMenu;

    // Font of the buttons of the menu
    Font fontMenuGameModeButtons;

    // Vector of buttons of the game modes menu
    vector<Button> gameModeMenuButtons;

    // Color of the font buttons in the game modes menu
    Color colorFontMenuGameModesButtons;

    // Control if the xml configuration file has been read or not
    bool optionsMenuRead;

    // Texture of the background
    Texture optionsMenuBackground;
    Sprite optMenuBackground;

    // Texture of the background main panel
    Texture optionsMenuPanelBack;

    // Color border of the main panel
    Color colorBorderPanelOptionsMenu;

     // Contents of the options menu title
    string contentTitleOptionsMenu;

    // Font of the title text of the menu
    Font fontOptionsMenu;

    // Colors of the main text of the options menu
    Color colorTitleTextOptionsMenu;
    Color colorTitleBorderOptionsMenu;

    // Font of the buttons of the menu
    Font fontMenuOptionsButtons;

    // Vector of buttons of the options menu
    vector<Button> optionsMenuButtons;

    // Color of the font buttons in the options menu
    Color colorFontMenuOptionsButtons;

    // Control if the sound menu has been read before from the xml configuration file
    bool soundMenuRead;

    // Texture of the background
    Texture soundMenuBackground;
    Sprite sdMenuBackground;

    // Texture of the background main panel
    Texture soundMenuPanelBack;

    // Color border of the main panel
    Color colorBorderPanelSoundMenu;

     // Contents of the options menu title
    string contentTitleSoundMenu;

    // Font of the title text of the menu
    Font fontSoundMenu;

    // Colors of the main text of the options menu
    Color colorTitleTextSoundMenu;
    Color colorTitleBorderSoundMenu;

    // Font of the buttons of the menu
    Font fontMenuSoundButtons;

    // Vector of buttons of the sound menu
    vector<Button> soundMenuButtons;

    // Color of the font buttons in the sound menu
    Color colorFontMenuSoundButtons;

    // Control if the graphics menu has been read from its xml file or not
    bool graphicsMenuRead;

    // Texture of the background
    Texture graphicsMenuBackground;
    Sprite ghMenuBackground;

    // Texture of the background main panel
    Texture graphicsMenuPanelBack;

    // Color border of the main panel
    Color colorBorderPanelGraphicsMenu;

     // Contents of the graphics menu title
    string contentTitleGraphicsMenu;

    // Font of the title text of the menu
    Font fontGraphicsMenu;

    // Colors of the main text of the graphics menu
    Color colorTitleTextGraphicsMenu;
    Color colorTitleBorderGraphicsMenu;

    // Font of the buttons of the menu
    Font fontMenuGraphicsButtons;

    // Control of the sound menu has been visited before
    bool comeFromSound;

    // Control of the graphics menu has been visited before
    bool comeFromGraphics;

    // Vector with the fonts of the buttons
    vector<string> contentButtonsGraphics;

    // Vector with the colors of the buttons
    vector<Color> colorButtons;

    // Color of the font buttons in the graphics menu
    Color colorFontMenuGraphicsButtons;

    // Control if the vehicle controllers menu has been read from its xml file or not
    bool vehicleControllersMenuRead;

    // Texture of the background
    Texture vehicleControllersMenuBackground;
    Sprite vehControllersMenuBackground;

     // Texture of the background main panel
    Texture vehicleControllersMenuPanelBack;

    // Color border of the main panel
    Color colorBorderPanelVehicleControllersMenu;

    // Contents of the vehicle controllers menu title
    string contentTitleVehicleControllersMenu;

    // Font of the title text of the menu
    Font fontVehicleControllersMenu;

    // Colors of the main text of the vehicle controllers menu
    Color colorTitleTextVehicleControllersMenu;
    Color colorTitleBorderVehicleControllersMenu;

    // Font of the buttons of the menu
    Font fontMenuVehicleControllersButtons;

    // Vector of buttons of the vehicle controllers menu
    vector<Button> vehicleControllersMenuButtons;

    // Color of the vehicle controllers menu
    Color colorFontVehicleControllersMenu;

    // Control if the pause menu configuration has been read before
    bool pauseMenuRead;

    // Color for for inside and border of the pause menu panel
    Color colorInsidePanelPauseMenu;
    Color colorBorderPanelPauseMenu;

    // Contents of the pause menu title
    string contentTitlePauseMenu;

    // Font of the title text of the menu
    Font fontPauseMenu;

    // Colors of the main text of the pause menu
    Color colorTitleTextPauseMenu;
    Color colorTitleBorderPauseMenu;

    // Font of the buttons of the menu
    Font fontMenuPauseButtons;

    // Vector of buttons of the pause menu
    vector<Button> pauseMenuButtons;

    // Color of the pause menu
    Color colorFontPauseMenu;

    // Color of the font buttons of the pause menu
    Color colorFontMenuPauseButtons;

    // Control if the configuration of the vehicle selection menu has been read
    bool vehicleSelectionMenuRead;

    // Background of the vehicle selection menu
    Texture backgroundSelectionMenu;

    // Content of the title text of the vehicle selection menu
    string contentTitleVehicleSelectionMenu;

    // Font of the vehicle selection menu title
    Font fontVehicleSelectionMenu;

    // Color of the title vehicle selection menu
    Color colorTitleTextVehicleSelectionMenu;

    // Color of the border title vehicle selection menu
    Color colorTitleBorderVehicleSelectionMenu;

    // Font of the title of the vehicle selection menu name panel
    Font fontVehicleSelectionMenuPanelTitle;

    // Color of the vehicle selection menu name title
    Color colorTitleTextVehicleSelectionMenuName;

    // Color of the vehicle selection menu border title
    Color colorTitleBorderVehicleSelectionMenuName;

    // Color of the border of the vehicle selection menu panel
    Color colorBorderVehiclePanel;

    // Font of the title of the vehicle name panel
    Font fontVehicleSelectionMenuPanelTitleProp;

    // Color of the vehicle selection menu name title
    Color colorTitleTextVehicleSelectionMenuProp;

    // Color of the vehicle border title
    Color colorTitleBorderVehicleSelectionMenuNameProp;

    // Color of the border of the properties panel of the vehicle selection menu
    Color colorBorderPropertiesPanel;

    // Color of the vehicle selection menu panel properties
    Font fontVehicleSelectionMenuPanelProp;

    // Color of the text vehicle selection properties
    Color colorTextVehicleSelectionProp;

    // Color of the border vehicle selection properties
    Color colorBorderVehicleSelectionProp;

    // Color of the inside of the vehicle properties panel
    Color colorInsideVehicleSelectionMenuPanelProp;

    // Color of the buttons of the vehicle selection menu
    vector<Color> vehicleSelectionMenuColorButtons;

    // Control if the screen is in full
    bool fullScreen;

    // Control if the xml configuration file of the circuit menu has been read
    bool circuitMenuRead;

    // Background of the circuit selection menu
    Texture backgroundCircuitMenu;

    // Title of the circuit menu
    string contentTitleCircuitMenu;

    // Font of the circuit menu's title
    Font fontTitleCircuitMenu;

    // Color of the title text of the circuit selection menu
    Color colorTitleTextCircuitMenu;

    // Color of the title border of the circuit selection menu
    Color colorTitleBorderCircuitMenu;

    // Background of the circuit selection menu
    Texture backgroundCircuitPanel;

    // Font of the circuit menu's title
    Font fontTitleCircuitPanel;

    // Color of the title text of the circuit selection menu
    Color colorTitleTextCircuitPanel;

    // Color of the title border of the circuit selection menu
    Color colorTitleBorderCircuitPanel;

    // Color of the panel border of the circuit selection menu
    Color colorBorderCircuitPanel;

    // Color of the triangle indicator of the circuit selection menu
    Color colorInsideIndicator;

    // Color of the triangle's border indicator of the circuit selection menu
    Color colorBorderIndicator;

    // Control if the multi player menu has been read
    bool multiplayerMenuRead;

    // Background of the multi player menu
    Texture backgroundMultiplayerMenu;
    Sprite multiPlayerMenuBackground;

    // Title of the multi player menu
    string contentTitleMultiplayerMenu;

    // Font of the multi player menu's title
    Font fontTitleMultiplayerMenu;

    // Color of the title text of the multi player menu
    Color colorTitleTextMultiplayerMenu;

    // Color of the title border of the multi player menu
    Color colorTitleBorderMultiplayerMenu;

    // Background of the multi player menu
    Texture backgroundMultiplayerPanel;

    // Color border of the panel of the multi player menu
    Color colorBorderPanelMultiplayerMenu;

    // Font of the buttons of the multi player menu
    Font fontMenuMultiplayerButtons;

    // Vector of buttons of the multi player menu
    vector<Button> multiplayerMenuButtons;

    // Color of the buttons of the multi player menu
    vector<Color> multiplayerMenuColorButtons;

    // Control if the multi player asking name menu configuration has been read
    bool multiplayerNameMenuRead;

    // Texture of the multi player asking name menu
    Texture backgroundMultiplayerNameMenu;

    // Texture of the multi player asking name menu's panel
    Texture backgroundMultiplayerNamePanel;
    Sprite multiPlayerNameMenuBackground;

    // Color of the border's panel of the multi player asking menu
    Color colorBorderPanelMultiplayerNameMenu;

    // Content title of the multi player asking name menu
    string contentTitleMultiplayerNameMenu;

    // Font title of the multi player asking name menu
    Font fontTitleMultiplayerNameMenu;

    // Color text of the multi player asking name menu
    Color colorTitleTextMultiplayerNameMenu;

    // Color border of the multi player asking name menu
    Color colorTitleBorderMultiplayerNameMenu;

    // Control if the multi player asking name menu configuration has been read
    bool multiplayerGroupMenuRead;

    // Texture of the multi player asking name menu
    Texture backgroundMultiplayerGroupMenu;

    // Texture of the multi player asking name menu's panel
    Texture backgroundMultiplayerGroupPanel;
    Sprite multiPlayerGroupMenuBackground;

    // Color of the border's panel of the multi player asking menu
    Color colorBorderPanelMultiplayerGroupMenu;

    // Content title of the multi player asking name menu
    string contentTitleMultiplayerGroupMenu;

    // Font title of the multi player asking name menu
    Font fontTitleMultiplayerGroupMenu;

    // Color text of the multi player asking name menu
    Color colorTitleTextMultiplayerGroupMenu;

    // Color border of the multi player asking name menu
    Color colorTitleBorderMultiplayerGroupMenu;

    // Control if the multi player join group menu has been read
    bool multiplayerJoinGroupMenuRead;

    // Background of th  join group menu
    Texture backgroundMultiplayerJoinGroupMenu;
    Sprite multiPlayerMenuJoinGroupBackground;

    // Title of the join group menu
    string contentTitleMultiplayerJoinGroupMenu;

    // Font of the join group menu's title
    Font fontTitleMultiplayerJoinGroupMenu;

    // Color of the title text of the join group menu
    Color colorTitleTextMultiplayerJoinGroupMenu;

    // Color of the title border of the join group menu
    Color colorTitleBorderMultiplayerJoinGroupMenu;

    // Background of the join group menu panel
    Texture backgroundMultiplayerJoinGroupPanel;

    // Color border of the main panel of the join group menu
    Color colorBorderPanelMultiplayerJoinGroupMenu;

    // Font of the buttons of the join group menu
    Font fontMenuMultiplayerJoinGroupButtons;

    // Vector of buttons of the join group menu
    vector<Button> multiplayerJoinGroupMenuButtons;

    // Color of the buttons of the join group menu
    vector<Color> multiplayerMenuJoinGroupColorButtons;


    // Control if the multi player joined members group menu has been read
    bool multiplayerMembersGroupMenuRead;

    // Background of the joined members group menu
    Texture backgroundMultiplayerMembersGroupMenu;
    Sprite multiPlayerMenuMembersGroupBackground;

    // Title of the joined members group menu
    string contentTitleMultiplayerMembersGroupMenu;

    // Font of the joined members group menu's title
    Font fontTitleMultiplayerMembersGroupMenu;

    // Color of the title text of the joined members group menu
    Color colorTitleTextMultiplayerMembersGroupMenu;

    // Color of the title border of the joined members group menu
    Color colorTitleBorderMultiplayerMembersGroupMenu;

    // Background of the joined members group menu panel
    Texture backgroundMultiplayerMembersGroupPanel;

    // Color border of the main panel of the joined members group menu
    Color colorBorderPanelMultiplayerMembersGroupMenu;

    // Color of the inside player joined indicator
    Color colorIndicatorInsideMultiplayerMembersGroupMenu;

    // Color border of the player joined indicator
    Color colorIndicatorBorderMultiplayerMembersGroupMenu;


    // Control if the player menu has been read before or not
    bool rivalTypeMenuRead;

    // Texture of the background
    Texture rivalTypeMenuBackground;
    Sprite sRivalTypeMenuBackground;

    // Texture of the background panel
    Texture rivalTypeMenuPanelBack;

    // Color border of the main panel
    Color colorBorderPanelRivalTypeMenu;

    // Contents of the player menu title
    string contentTitleRivalTypeMenu;

    // Font of the title text of the menu
    Font fontRivalTypeMenu;

    // Colors of the main text of the player menu
    Color colorTitleTextRivalTypeMenu;
    Color colorTitleBorderRivalTypeMenu;

    // Colors of the description panel of the player menu
    Color colorDescriptionPanelInsideRivalTypeMenu;
    Color colorDescriptionPanelBorderRivalTypeMenu;

    // Font of the buttons of the menu
    Font fontMenuRivalTypeButtons;

    // Vector of buttons of the player menu
    vector<Button> menuRivalTypeButtons;

    // Color of the font buttons in the menu player
    Color colorFontMenuRivalTypeButtons;

    // Control if the game modes multi player menu has been read before or not
    bool gameModesMultiplayerMenuRead;

    // Texture of the background
    Texture gameModesMultiplayerMenuBackground;
    Sprite sGameModesMultiplayerBackground;

    // Texture of the background panel
    Texture gameModesMultiplayerMenuPanelBack;

    // Color border of the main panel
    Color colorBorderPanelGameModeMultiplayerMenu;

    // Contents of the game modes menu title
    string contentTitleGameModeMultiplayerMenu;

    // Font of the title text of the menu
    Font fontGameModeMultiplayerMenu;

    // Colors of the main text of the game modes multi player menu
    Color colorTitleTextGameModeMultiplayerMenu;
    Color colorTitleBorderGameModeMultiplayerMenu;

    // Colors of the description panel of the game modes multi player  menu
    Color colorDescriptionPanelInsideGameModeMultiplayerMenu;
    Color colorDescriptionPanelBorderGameModeMultiplayerMenu;

    // Font of the buttons of the menu
    Font fontMenuGameModeMultiplayerButtons;

    // Vector of buttons of the game modes multi player menu
    vector<Button> gameModeMenuMultiplayerButtons;

    // Color of the font buttons in the game modes multi player menu
    Color colorFontMenuGameModesMultiplayerButtons;

    // Control if the multi player test connection menu has been read
    bool multiplayerTestConnectionMenuRead;

    // Background of the multi player test connection menu
    Texture backgroundMultiplayerTestConnectionMenu;
    Sprite multiPlayerTestConnectionMenuBackground;

    // Title of the multi player test connection menu
    string contentTitleMultiplayerTestConnectionMenu;

    // Font of the multi player test connection menu's title
    Font fontTitleMultiplayerTestConnectionMenu;

    // Color of the title text of the multi player test connection menu
    Color colorTitleTextMultiplayerTestConnectionMenu;

    // Color of the title border of the multi player test connection menu
    Color colorTitleBorderMultiplayerTestConnectionMenu;

    // Color of the font of the buttons
    Color colorFontMenuPlayerTestConnectionButtons;

    // Background of the multi player test connection menu
    Texture backgroundMultiplayerTestConnectionPanel;

    // Color border of the panel of the multi player test connection menu
    Color colorBorderPanelMultiplayerTestConnectionMenu;

    // Font of the buttons of the multi player test connection menu
    Font fontMenuMultiplayerTestConnectionButtons;

    // Vector of buttons of the multi player test connection menu
    vector<Button> multiplayerTestConnectionMenuButtons;

    // Color of the buttons of the multi player test connection menu
    vector<Color> multiplayerTestConnectionMenuColorButtons;



    /**
     * Assigns to the game the configuration read from the xml configuration file
     * @param difficulty is the difficulty level of the game
     * @param pixelArt controls if the graphics of the game have to be drawn with pixel art effect
     * @param fullScreen controls if the game is in full screen
     * @param axis_x is the width of the screen
     * @param axis_y is the height of the screen
     * @param controlLeft is the code of the key to move the vehicle to the left
     * @param controlLeft is the code of the key to move the vehicle to the right
     * @param controlAccelerate is the code of the key to accelerate the vehicle
     * @param controlSoundtrack is the code of the key to change the soundtrack of the game
     */
    Configuration(const Difficult difficulty, const bool pixelArt, const bool fullScreen, const int axis_x,
                  const int axis_y, const string controlLeft,const string controlRight, const string controlAccelerate,
                  const string controlBrake, const string controlSoundtrack);



    /**
     * Load the configuration of the graphics menu stored in its xml
     * configuration file
     * @param path contains the path of the xml configuration file
     * @param c is the configuration of the game
     */
    void loadGraphicsMenuConfiguration(const string path);



    /**
     * Represents on the screen the graphics menu and returns to options menu
     * @return
     */
    State graphicsMenu(SoundPlayer& r);
};



/**
 * Returns the font used to write the time in the elapsed time panel
 * @return
 */
Font initializeFontElapsedTime();



/**
 * Returns the font used to represent the HUD during the game
 * @return
 */
Font initializeFontTimeToPlay();



/**
 * Returns the font used to represent all the text indicators in
 * the animations of the game
 * @return
 */
Font initializeFontMenus();


#endif // CONFIGURATION_H


