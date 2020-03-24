
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "../include/Button.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace sf;
using namespace rapidxml;



/*
 * Step data type
 */
class Menu{

    private:

    vector<Button> menuButtons;

    vector<Color>color_buttons;

    public:


    /**
     * Constructor of the data type Animations
     * @param pathMenuFile is the path where are indicated the textures used to the menus
     */
    Menu();



    /**
     * Load the main game menu from its xml configuration file
     * @param imagePath is the path of the background's image of the menu
     * @param fontPath is the text font of the main text of the menu
     * @param textContent is the text that appears in the main menu
     * @param positionXCover is the coordinate in the axis X of the main cover image
     * @param positionYCover is the coordinate in the axis Y of the main cover image
     * @param sizeText is the size of the font
     * @param channelR is the value of the red channel color of the text
     * @param channelG is the value of the green channel color of the text
     * @param channelB is the value of the blue channel color of the text
     */
    inline void loadMainMenu(string& imagePath, string& fontPath, string& textContent,
                             int& positionXCover, int& positionYCover, int& positionXText,
                             int& positionYText, int& sizeText, int&channelR, int&channelG, int& channelB);



    /**
     * Load the configuration of the player and game menus
     * @param pathFile is the xml file configuration of the menu to load
     */
    inline void loadPlayerAndGameMenus(string pathFile);



    /**
     * Shows the main cover of the game until the player presses start
     * @param app is the console where the game is displayed to the players
     */
    void showMainMenu(RenderWindow* app);



    /**
     * Shows the menu of selecting the number of players
     * @param app is the console where the game is displayed to the players
    */
    void showPlayerMenu(RenderWindow* app);



    /**
     * Shows the menu of selecting the game modes
     * @param app is the console where the game is displayed to the players
    */
    void showGameModesMenu(RenderWindow* app);

};

#endif // ANIMATIONS_H
