

#ifndef GAME_SELECTOR_MODE_H
#define GAME_SELECTOR_MODE_H


#include <iostream>
#include <cstring>
#include "SFML/Graphics.hpp"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "../include/Environment.h"


using namespace std;
using namespace sf;
using namespace rapidxml;


enum game_selector_state {
    WORLD_TOUR = 0,
    OUT_RUN,
    POLE_POSITION,
    DRIVING_FURY,
    DELIVERY,
    DEMARRAGE,
};


class GameSelectorMode {

    private:

        // Difficult level selected by the player
        int difficultMode;

        // Game mode selected by the player
        int gameMode;

        // Control the available vehicles of the game mode
        bool motorbikeIsOn, minivanIsOn, truckIsOn, ferrariIsOn;

        // Status of the game in curse
        game_selector_state gameStatus;

        // Path from the xml configuration file game mode
        char* pathFile;

        // Vector of the possible paths with the files
        vector<string> pathLandScapeFiles;


    public:


        /**
         * Constructor by default
         */
         GameSelectorMode();



        /**
         * Constructor of the data type Game mode selector
         * @param difficult is the difficult level validated by the player
         * @param game is the game mode selected by the user
         */
         GameSelectorMode(const int& difficult, const int& game);



         /**
          * Get the vector with the different paths of the landscapes
          */
         vector<string> getVectorOfLandScapes();



        /**
         * Load the game mode from the correspondent xml file of configuration
         * @param gameMode is the mode selected by the player to play
         * @param e is the environment of the game which is going to be configured
         */
         void loadFileConfigurationMode(Environment& e);



         inline void controlAvailableVehicles(xml_node<> *worldTourNode);


         inline void processTextPanel(xml_node<> *panelNode, string& fontPath, int& sizeText, int& posXTest, int& posYText, Color& colorText);


         inline void processFirstPanel(xml_node<> *panel, string& pathSpeedIndicator, int& posX, int& posY,
                                       string& fontPath, int& sizeText, int& posXText, int& posYText, Color& colorText);


         inline void processSecondPanel(xml_node<> *panel, string& fontPathTimeText, int& sizeTimeText,
                                        int& posXTimeText, int& posYTimeText, string& fontPathTimeIndicator,
                                        int& sizeTimeIndicator, int& posXTimeIndicator, int& posYTimeIndicator,
                                        string& fontPathDestinyText, int& sizeDestinyText, int& posXDestinyText,
                                        int& posYDestinyText, string& fontPathDistanceText, int& sizeDistanceText,
                                        int& posXDistanceText, int& posYDistanceText, Color& colorTimeText,
                                        Color& colorTimeIndicator, Color& colorDestinyText, Color& colorDistanceText);


         /**
          * Load the configuration xml file from the world tour game mode
          * @param e is the environment of the game which is going to be configured
          */
          void loadWorldTourMode(char* pathFile, Environment& e);



         /**
          * Load the configuration xml file from the out run game mode
          */
          void loadOutRun(char* pathFile, Environment& e);



         /**
          * Load the configuration xml file from the pole position game mode
          */
          void loadPolePosition();



         /**
          * Load the configuration xml file from the driving fury game mode
          */
          void loadDrivingFury();



         /**
          * Load the configuration xml file from the delivery game mode
          */
          void loadDelivery();



         /**
          * Load the configuration xml file from the demarrage game mode
          */
          void loadDemarrage();

};


#endif // GAME_SELECTOR_MODE_H
