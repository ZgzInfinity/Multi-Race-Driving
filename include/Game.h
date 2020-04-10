
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Animation.h"
#include "Menu.h"
#include "../include/Motorbike.h"
#include "../include/Devastator.h"
#include "../include/Minivan.h"
#include "../include/Truck.h"
#include "../include/LandScape.h"
#include "../include/GameSelectorMode.h"
#include "../include/Environment.h"
#include "../include/MusicReproductor.h"
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

const int INITIAL_SECS = 100;


class Game {

    private:

        // Console window of the game
        RenderWindow* application;

        // Animation controller of the game
        Animation* animationGame;

        // Menu displayer controller of the game
        Menu* menuGame;

        // Selector of the different game modes
        GameSelectorMode gSM;

        // Controller for the different game mode configurations
        Environment e;

        // Music reproductor controller of the game
        MusicReproductor* mR;

        // Effects reproductor controller of the game
        EffectReproductor* eR;

        // Status of the state machine which compose the game
        Game_status status;

        // Control type of the game
        Type_control control = KEYBOARD;

        // Default configuration of the game
        Configuration* c;

        // Keyword mapper controller
        KeywordMapper* kM;

        // Control the player mode selected
        int modePlayerSelected;

        // Control the game mode selected
        int modeGameSelected;

        // Control the difficult level selected
        int modeDifficultLevelSelected;

        // Control the type of vehicle selected with also its color
        int typeOfVehicle, colorVehicle;


    public:



        /**
         * Constructor of the data type Game
         * @param app is the console window where it's going to be displayed
         */
        Game(RenderWindow* app);



        /**
         * Execute the game throughout its different states
         */
        void runningGame();



        /**
         * Displays the initial animations when the game starts
         */
        Game_status showStartingAnimation();



        /**
         * Show the main menu of the game
         */
        Game_status showMainMenu();



        /**
         * Show the player menu of the game
         */
        Game_status showPlayerMenu();



        /**
         * Show the different game modes when the payer
         * chooses the single player mode
         */
        Game_status showSinglePlayerMenu();



        /**
         * Show the different available difficult level
         * to play in the game mode selected
         */
        Game_status showDifficultLevelMenu();


        /**
         * Prepares all the configurations of the game mode selected
         */
        Game_status prepareGameMode();


        /**
         * Show the menu for choose the vehicle and play
         */
        Game_status showVehicleMenu();



        /**
         * Show the options menu with the game configuration
         */
        Game_status showOptionsMenu();



        void drawQuad(Color c, int x1,int y1,int w1,int x2,int y2,int w2);



        /**
         * Execute the game mode selected by the user with the difficult selected
         * and also with the vehicle chosen
         */
        Game_status playingGame();

};

#endif // GAME_H
