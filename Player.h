
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Step.h"
#include "IntervalCurve.h"

using namespace sf;
using namespace std;

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

        // Code of the actual image texture
        int actual_code_image;

        // Position of the main character
        float playerX;

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

        // Sprite of the player motorbike
        Sprite playerSprite;

    public:

        /**
         * Constructor of the class
         */
        Player();


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
         */
         float getPlayerX();



        /**
         * Control if the user has pressed the w keyword to turn to the right
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         */
        inline void controlTurningPlayerRight(int& speed, bool& eventDetected);



        /**
         * Control if the user has pressed the q keyword to turn to the left
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         */
        inline void controlTurningPlayerLeft(int& speed, bool& eventDetected);



        /**
         * Control if the user has pressed the q keyword to increase the speed
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         */
        inline void controlPlayerSpeed(int& speed, bool& eventDetected);



        /**
         * Control if the user has pressed the q keyword to increase the speed
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         */
        inline void controlPlayerBraking(int& speed, bool& eventDetected);



        /**
         * Control if the player has done any of his possible actions
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         */
        void controlActionPlayer(int& speed, bool& eventDetected);



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

};


#endif
