
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <list>
#include <SFML/Graphics.hpp>
#include "Step.h"
#include "IntervalCurve.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace sf;
using namespace std;
using namespace rapidxml;

const int SPEED_INCREMENT = 50;
const int INITIAL_SPEED = 200;
const int MAX_SPEED = 1000;
const int MEDIUM_SPEED = INITIAL_SPEED + MAX_SPEED / 2;
const int CONTROL_SPEED = INITIAL_SPEED + MEDIUM_SPEED / 2;

const float BORDER_LIMIT_ROAD_LEFT = -1.4;
const float BORDER_LIMIT_ROAD_RIGHT = 1.4;


const float BORDER_ROAD_LEFT = -1.15;
const float BORDER_ROAD_RIGHT = 1.15;

/*
 * Class which represents the player
 */
class Player {

     private:

        Texture t;

        // Code of the actual image texture
        int actual_code_image;

        // Position of the main character
        float playerX;

        // How to control the motorbike
        int typeControl = 0;

        // Textures of the player while running in normal direction
        Texture playerTexture_1, playerTexture_2;

        // Textures of the motorbike player while is turned to the left
        Texture playerTexture_3, playerTexture_4, playerTexture_5,
                playerTexture_6, playerTexture_7, playerTexture_8;

        // Textures of the motorbike player while is turned to the right
        Texture playerTexture_9, playerTexture_10, playerTexture_11,
                playerTexture_12, playerTexture_13, playerTexture_14;

        // Textures of the player while running in normal direction and braking
        Texture playerTexture_15, playerTexture_16;

        // Textures of the motorbike player while is turned to the left and braking
        Texture playerTexture_17, playerTexture_18, playerTexture_19,
                playerTexture_20, playerTexture_21, playerTexture_22;

        // Textures of the motorbike player while is turned to the right and braking
        Texture playerTexture_23, playerTexture_24, playerTexture_25,
                playerTexture_26, playerTexture_27, playerTexture_28;

        // Textures of the motorbike player while is crushing A
        Texture playerTexture_29, playerTexture_30, playerTexture_31, playerTexture_32,
                playerTexture_33, playerTexture_34, playerTexture_35, playerTexture_36,
                playerTexture_37, playerTexture_38, playerTexture_39, playerTexture_40,
                playerTexture_41;

        // Textures of the motorbike player while is crushing with type B
        Texture playerTexture_42, playerTexture_43, playerTexture_44, playerTexture_45,
                playerTexture_46, playerTexture_47, playerTexture_48, playerTexture_49,
                playerTexture_50, playerTexture_51, playerTexture_52, playerTexture_53,
                playerTexture_54;

        // Sprite of the player motorbike
        Sprite playerSprite;

        // Mode to show the collision of the motorbike by default
        int mode;

        // Accumulator to the coordinate of the axis Y to make collision better
        int offset;

        // Offset added if the collision is with the second type
        int increment;

        // File path with the sprites
        char* filePath;

        // Vector of textures of the player
        vector<Texture> textures;

    public:

        /**
         * Constructor of the class
         */
        Player(char* pathFile);



        /**
         * Load the set of sprites of the player
         */
         void loadSpritesFromPath();



        /**
         * Draw the player sprite in the console render window
         * @param app is the console window game where the sprite is going to be drawn
         */
        void drawPlayer(RenderWindow& app);



        /**
         * Check if the player has to advance in the track
         * @param eventDetected is a boolean to control if an event has occurred
         */
        void advancePlayer(bool& eventDetected);



        /**
         * Get the coordinate of the payer in the axis X
         * @return the position of the motorbike in the axis X
         */
         float getPlayerX();



         /**
          * Get the mode of collision of the motorbike
          * @return the mode to show the collision of the motorbike
          */
         int getModeCollision();



        /**
         * Control if the user has pressed the q keyword to turn to the left
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         */
        inline void controlTurningPlayerLeftKeyboard(int& speed, bool& eventDetected, RenderWindow& app);



         /**
         * Control if the user has pressed the w keyword to turn to the right
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         */
        inline void controlTurningPlayerRightKeyboard(int& speed, bool& eventDetected, RenderWindow& app);



        /**
         * Control if the user has pressed the q keyword to turn to the left
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         */
        inline void controlTurningPlayerLeftMouse(int& speed, bool& eventDetected, RenderWindow& app);



        /**
         * Control if the user has pressed the w keyword to turn to the right
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         */
        inline void controlTurningPlayerRightMouse(int& speed, bool& eventDetected, RenderWindow& app);



        /**
         * Control if the user has pressed the q keyword to increase the speed
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         */
        inline void controlPlayerSpeed(int& speed, bool& eventDetected, RenderWindow& app);



        /**
         * Control if the user has pressed the q keyword to increase the speed
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         */
        inline void controlPlayerBraking(int& speed, bool& eventDetected, RenderWindow& app);



        /**
         * Control if the player has done any of his possible actions
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         */
        void controlActionPlayer(int& speed, bool& eventDetected, RenderWindow& app);



        /**
         * Control if the player has have collision with the nearest element of the map to him
         * @param nearestStep is the step of the scene where is located the nearest element to the player
         * @param lastPos is the last position of the motorbike in the axis Y
         * @param pos is the current position of the motorbike in the axis Y
         */
        bool controlPossibleCollision(Step& nearestSprite, int& lastPos, int& pos);



        /**
         * Control if there is there inertia force or not if the motorbike is on a curve of the scene
         * @param onCurve is a boolean which represents if the motorbike is on curve or not
         * @param curve is the possible curve of the scene where the motorbike is currently now
         * @param speed is the actual speed of the motorbike of the player
         */
        void controlInertiaForce(bool& onCurve, IntervalCurve& curve, int& speed);



        /**
         * Shows to the user how the motorbikes crushes
         */
        void collisionShow();



        /**
         * Starts the process to recover the motorbike
         */
        void recoverMotorbike();

};


#endif
