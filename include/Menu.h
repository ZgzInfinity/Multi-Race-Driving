
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "../include/Button.h"
#include "../include/Slot.h"
#include "../include/Configuration.h"
#include "../include/KeywordMapper.h"
#include "../include/VehicleSpecifications.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace sf;
using namespace rapidxml;


enum Type_control {
    MOUSE = 0,
    KEYBOARD,
    JOYSTICK,
};


/*
 * Step data type
 */
class Menu{

    private:

        // Vector to keep the buttons of the menus
        vector<Button> menuButtons;

        // Vector for store the different color buttons
        vector<Color>color_buttons;

        // Panel for the menus of the game
        sf::RectangleShape rectangle;

        // Variable to store the texture of the game's presents main cover
        Texture cover;

        // Sprite where the different textures are loaded
        Sprite menuSprite;

        // Coordinates of the cover
        int positionXCover, positionYCover;

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
    inline void loadPlayerAndGameMenus(string pathFile, string& imagePath, string& textContent, string& fontPath,
                                       Font& f, int& positionXPanel, int& positionYPanel, int& width, int& height,
                                       int& border,int& positionXText, int& positionYText, int& sizeText, Color& colorText);


    /**
     * Shows the main cover of the game until the player presses start
     * @param app is the console where the game is displayed to the players
     */
    void showMainMenu(RenderWindow* app);



    /**
     * Shows the menu of selecting the number of players
     * @param app is the console where the game is displayed to the players
     * @param optionParameter is the flag where is stored the option selected by the
     * the player in the menu
     */
    void showStandardMenu(RenderWindow* app, string pathFile, int& optionParameter);



    /**
     * Shows the menu of selecting the number of players
     * @param app is the console where the game is displayed to the players
     * @param c stores the current configuration of the game
     */
    void showMenuOptions(RenderWindow* app, string pathFile, Type_control& control, Configuration* c, KeywordMapper* kM);



    void loadVehiclesMenu(Sprite& menuVehicle, Font& fontMainText, Font& fontVehicleName, Font& fontVehicleIndicator, Font& fontTitle,
                          Text& mainText, Text& propertyText, vector<Slot>& slotsMenu, vector<Text>& vehicleIndicators,
                          RectangleShape& panelIndicator);



    void readVehicleSpecifications(char* pathVehicleName, int& topSpeed, float& angle,
                                   string& motor, float& timeBraking, float& timeAcceleration);

    /**
     * Shows the menu of selecting vehicle
     * @param app is the console where the game is displayed to the players
     * @param typeOfVehicle is the kind of vehicle selected by the user in the menu
     * @param colorVehicle is the vehicle's color selected by the user in the menu
     */
    void showSelectionVehicleMenu(RenderWindow* application, int& typeOfVehicle, int& colorVehicle);



    /**
     * Change a configuration parameter of the game that it's not relative to the player
     * @param optionParameter is the code of the parameter to modify
     */
    void modifyOptionConfiguration(const int optionParameter, Type_control& control, Configuration* c, KeywordMapper* kM);



    /**
     * Change a configuration parameter of the game that it's  relative to the player
     * @param optionParameter is the code of the parameter to modify
     * @param c stores the current configuration of the game
     */
    void modifyOptionConfigurationPlayer(RenderWindow* app, const int optionParameter, Configuration* c, KeywordMapper* kM);

};

#endif // MENU_H
