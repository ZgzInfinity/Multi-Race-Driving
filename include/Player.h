
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "../include/Configuration.h"
#include "../include/Step.h"
#include "../include/IntervalCurve.h"
#include "../include/rapidxml.hpp"
#include "../include/rapidxml_utils.hpp"
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;
using namespace rapidxml;

const int INITIAL_SPEED = 250;

const float BORDER_LIMIT_ROAD_LEFT = -1.4;
const float BORDER_LIMIT_ROAD_RIGHT = 1.4;


const float BORDER_ROAD_LEFT = -1.15;
const float BORDER_ROAD_RIGHT = 1.15;

const float RATIO = 6.25f;


/*
 * Class which represents the player
 */
class Player {

     protected:

        Texture t;

        // Code of the actual image texture
        int actual_code_image;

        // Position of the main character
        float playerX;

        // How to control the motorbike
        int typeControl = 0;

        // Sprite of the player motorbike
        Sprite playerSprite;

        // Mode to show the collision of the motorbike by default
        int mode;

        // Accumulator to the coordinate of the axis Y to make collision better
        int offset;

        // File path with the sprites
        char* filePath;

        // Vector of textures of the player
        vector<Texture> textures;

        // Configuration of the player
        Configuration* c;

        // Control if the player is accelerating
        bool isAccelerating = false;

        // Variable increment of speed
        int speed_increment = 2;

        // Control the acceleration frequency of the vehicle
        float acceleration = 5.f;

        // Control the deceleration frequency of the vehicle
        float deceleration = 10.f;

        // Maximum speed of the vehicle
        int maxSpeed;

        // Medium speed of the vehicle
        int mediumSpeed;

        // Control speed of the vehicle to calculate the inertia force
        int controlSpeed;

        // Number of spinning tops done after collision
        int spinningTopsDone = 0;

    public:



        /**
         * Constructor of the class
         */
        Player(char* pathFile){
            // Assign principal variables
            filePath = pathFile;
            // Store actual code of the image
            actual_code_image = 1;
            // Initializing the position of the player in the axis X
            playerX = 0.f;
            // Mode to show the collision of the motorbike by default
            mode = -1;
            // Accumulator to the coordinate of the axis Y to make collision better
            offset = 0;
            // Load the default configuration to control the vehicle
            c = new Configuration();
        }



        /**
         * Load the set of sprites of the player
         */
         virtual void loadVehicleProperties() = 0;



        /**
         * Draw the player sprite in the console render window
         * @param app is the console window game where the sprite is going to be drawn
         * @param pos is the actual position of the player in the map
         */
        virtual void drawPlayer(RenderWindow* app, int& pos) = 0;



        /**
         * Check if the player has to advance in the track
         * @param eventDetected is a boolean to control if an event has occurred
         * @param lastHeight was the elevation of the terrain where was the motorbike
         * @param height is the actual elevation of the terrain where is the motorbike
         */
        virtual void advancePlayer(bool& eventDetected, const int lastHeight, const int height) = 0;



        /**
         * Get the coordinate of the payer in the axis X
         * @return the position of the motorbike in the axis X
         */
         float getPlayerX(){
            return playerX;
         }



         /**
          * Get the mode of collision of the motorbike
          * @return the mode to show the collision of the motorbike
          */
         virtual int getModeCollision() = 0;



        /**
         * Control if the user has pressed the q keyword to turn to the left
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the motorbike
         * @param height is the actual elevation of the terrain where is the motorbike
         */
        virtual inline void controlTurningPlayerLeftKeyboard(int& speed, bool& eventDetected, RenderWindow* app,
                                                             const int lastHeight, const int height) = 0;



         /**
         * Control if the user has pressed the w keyword to turn to the right
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the motorbike
         * @param height is the actual elevation of the terrain where is the motorbike
         */
        virtual inline void controlTurningPlayerRightKeyboard(int& speed, bool& eventDetected, RenderWindow* app,
                                                              const int lastHeight, const int height) = 0;



        /**
         * Control if the user has pressed the q keyword to increase the speed
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the motorbike
         * @param height is the actual elevation of the terrain where is the motorbike
         */
        virtual inline void controlPlayerSpeed(int& speed, bool& eventDetected, RenderWindow* app,
                                               const int lastHeight, const int height) = 0;



         /**
         * Control if the user has pressed the q keyword to increase the speed
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the player
         * @param height is the actual elevation of the terrain where is the player
         */
        virtual inline void controlPlayerBraking(int& speed, bool& eventDetected, RenderWindow* app,
                                         const int lastHeight, const int height) = 0;


        /**
         * Control if the player has done any of his possible actions
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the player
         * @param height is the actual elevation of the terrain where is the player
         */
        virtual void controlActionPlayer(int& speed, bool& eventDetected, RenderWindow* app,
                                         const int lastHeight, const int height) = 0;



        /**
         * Control if the player has have collision with the nearest element of the map to him
         * @param nearestStep is the step of the scene where is located the nearest element to the player
         * @param lastPos is the last position of the motorbike in the axis Y
         * @param pos is the current position of the motorbike in the axis Y
         */
        virtual bool controlPossibleCollision(Step& nearestSprite, int& lastPos, int& pos) = 0;



        /**
         * Control if there is there inertia force or not if the motorbike is on a curve of the scene
         * @param onCurve is a boolean which represents if the motorbike is on curve or not
         * @param curve is the possible curve of the scene where the motorbike is currently now
         * @param speed is the actual speed of the motorbike of the player
         */
        virtual void controlInertiaForce(bool& onCurve, IntervalCurve& curve, int& speed) = 0;



        /**
         * Shows to the user how the motorbikes crushes
         */
        virtual void collisionShow() = 0;

};


#endif
