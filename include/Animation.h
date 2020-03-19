
#ifndef ANIMATION_H
#define ANIMATION_H

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
class Animation{

    private:

        // Variable to store locally the textures of the menus
        Texture t;

        // Variable to store the texture of the game's company
        Texture company;

        // Variable to store the texture of the game's presents menu
        Texture presents;

        // Vector where the textures of the menus are stored
        vector<Texture> menuTextures;

        // Sprite where the different textures are loaded
        Sprite menuSprite;

    public:


    /**
     * Constructor of the data type Animation
     * @param pathMenuFile is the path where are indicated the textures used to the menus
     */
    Animation(char* pathMenuFile);



    /**
     * Shows the different menus with the icons of Sega
     * @param app is the console where the game is displayed to the players
     */
     void loadSegaIcons(RenderWindow* app);



    /**
     * Shows the company of the game and also the presents image of the game
     * @param app is the console where the game is displayed to the players
     */
    void loadGameData(RenderWindow* app);


};

#endif // ANIMATION_H

