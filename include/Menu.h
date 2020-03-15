
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
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

        // Variable to store the texture of the game's presents main cover
        Texture cover;

        // Sprite where the different textures are loaded
        Sprite menuSprite;

        // Initial text shown in the main cover of the game
        Text coverText;

    public:


    /**
     * Constructor of the data type Animations
     * @param pathMenuFile is the path where are indicated the textures used to the menus
     */
    Menu(char* pathMenuFile);



    /**
     * Shows the main cover of the game until the player presses start
     * @param app is the console where the game is displayed to the players
     */
    void showMainMenu(RenderWindow& app);

};

#endif // ANIMATIONS_H
