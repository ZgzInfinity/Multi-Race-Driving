
#ifndef FERRARI_H
#define FERRARI_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "Step.h"
#include "Player.h"
#include "IntervalCurve.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <SFML/Graphics.hpp>


const int MAX_SPINNING_TOPS = 2;

using namespace sf;

/*
 * Class which represents the player
 */
class Ferrari {

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

        // Offset added if the collision is with the second type
        int increment;

        // File path with the sprites
        char* filePath;

        // Vector of textures of the player
        vector<Texture> textures;

        // Amount of spinning tops of the car
        int spinningTopsDone = 0;

    public:

        /**
         * Constructor of the class
         */
        Ferrari(char* pathFile);



        /**
         * Load the set of sprites of the player
         */
         void loadSpritesFromPath();



        /**
         * Draw the player sprite in the console render window
         * @param app is the console window game where the sprite is going to be drawn
         */
        void drawPlayer(RenderWindow& app, int& pos);



      /**
       * Check if the player has to advance in the track
       * @param eventDetected is a boolean to control if an event has occurred
       * @param height is the actual elevation of the terrain where is the ferrari
       * @param lastHeight was the elevation of the terrain where was the ferrari
       */
       void advancePlayer(bool& eventDetected);



       /**
         * Check if the player has to advance in the track
         * @param eventDetected is a boolean to control if an event has occurred
         * @param lastHeight was the elevation of the terrain where was the ferrari
         * @param height is the actual elevation of the terrain where is the ferrari
         */
        void advancePlayer(bool& eventDetected, const int lastHeight, const int height);



        /**
         * Get the coordinate of the payer in the axis X
         * @return the position of the Ferrari in the axis X
         */
        float getPlayerX();



         /**
          * Get the mode of collision of the Ferrari
          * @return the mode to show the collision of the Ferrari
          */
         int getModeCollision();



        /**
         * Control if the user has pressed the q keyword to turn to the left
         * @param speed is the actual speed of the Ferrari of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the ferrari
         * @param height is the actual elevation of the terrain where is the ferrari
         */
        inline void controlTurningPlayerLeftKeyboard(int& speed, bool& eventDetected, RenderWindow& app,
                                                     const int lastHeight, const int height);



         /**
         * Control if the user has pressed the w keyword to turn to the right
         * @param speed is the actual speed of the Ferrari of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the ferrari
         * @param height is the actual elevation of the terrain where is the ferrari
         */
        inline void controlTurningPlayerRightKeyboard(int& speed, bool& eventDetected, RenderWindow& app,
                                                      const int lastHeight, const int height);



        /**
         * Control if the user has pressed the q keyword to turn to the left
         * @param speed is the actual speed of the Ferrari of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         */
        inline void controlTurningPlayerLeftMouse(int& speed, bool& eventDetected, RenderWindow& app);



        /**
         * Control if the user has pressed the w keyword to turn to the right
         * @param speed is the actual speed of the Ferrari of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         */
        inline void controlTurningPlayerRightMouse(int& speed, bool& eventDetected, RenderWindow& app);



        /**
         * Control if the user has pressed the q keyword to increase the speed
         * @param speed is the actual speed of the Ferrari of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the ferrari
         * @param height is the actual elevation of the terrain where is the ferrari
         */
        inline void controlPlayerSpeed(int& speed, bool& eventDetected, RenderWindow& app,
                                       const int lastHeight, const int height);



       /**
        * Control if the user has pressed the q keyword to increase the speed
        * @param speed is the actual speed of the Ferrari of the player
        * @param eventDetected is a boolean to control if an event has occurred
        * @param app is the console window game where the sprite is going to be drawn
        * @param lastHeight was the elevation of the terrain where was the ferrari
        * @param height is the actual elevation of the terrain where is the ferrari
        */
        inline void controlPlayerBraking(int& speed, bool& eventDetected, RenderWindow& app,
                                         const int lastHeight, const int height);



        /**
         * Control if the player has done any of his possible actions
         * @param speed is the actual speed of the Ferrari of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the ferrari
         * @param height is the actual elevation of the terrain where is the ferrari
         */
        void controlActionPlayer(int& speed, bool& eventDetected, RenderWindow& app, const int lastCamH, const int camH);



        /**
         * Control if the player has have collision with the nearest element of the map to him
         * @param nearestStep is the step of the scene where is located the nearest element to the player
         * @param lastPos is the last position of the Ferrari in the axis Y
         * @param pos is the current position of the Ferrari in the axis Y
         */
        bool controlPossibleCollision(Step& nearestSprite, int& lastPos, int& pos);



        /**
         * Control if there is there inertia force or not if the Ferrari is on a curve of the scene
         * @param onCurve is a boolean which represents if the Ferrari is on curve or not
         * @param curve is the possible curve of the scene where the Ferrari is currently now
         * @param speed is the actual speed of the Ferrari of the player
         */
        void controlInertiaForce(bool& onCurve, IntervalCurve& curve, int& speed);



        /**
         * Shows to the user how the Ferrari crushes
         * @param pos is the position of the ferrari in the car in the axis Y
         */
        void collisionShow();

};

#endif // FERRARI_H
