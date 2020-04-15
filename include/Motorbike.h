
#ifndef MOTORBIKE_H
#define MOTORBIKE_H

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

using namespace sf;

/*
 * Class which represents the player
 */
class Motorbike : public Player{

    public:

        /**
         * Constructor of the class
         */
        Motorbike(char* pathFile, Configuration* c);



        /**
         * Load the set of sprites of the player
         */
         void loadVehicleProperties(const string path);



        /**
         * Draw the player sprite in the console render window
         * @param app is the console window game where the sprite is going to be drawn
         * @param pos is the actual position of the motorbike in the map
         */
        void drawPlayer(RenderWindow* app, int pos);



        /**
         * Check if the player has to advance in the track
         * @param eventDetected is a boolean to control if an event has occurred
         * @param lastHeight was the elevation of the terrain where was the motorbike
         * @param height is the actual elevation of the terrain where is the motorbike
         */
        void advancePlayer(bool& eventDetected, const int lastHeight, const int height, Elevation& e);



        /**
         * Establish the coordinate X and Y of the vehicle
         * @param pX is the coordinate of the vehicle in the axis X
         * @param pY is the coordinate of the vehicle in the axis Y
         */
        void setPosition(float pX, float pY);



        /**
         * Get the coordinate of the payer in the axis X
         * @return the position of the motorbike in the axis X
         */
         float getPlayerX();



         /**
         * Get the coordinate of the payer in the axis Y
         * @return the position of the truck in the axis Y
         */
         float getPlayerY();



        /**
         * Get the coordinate of the payer in the axis X
         * @return the position of the motorbike in the axis X
         */
         float getPreviousY();



         /**
          * Get the coordinate of the payer in the axis X
          * @return the position of the motorbike in the axis X
          */
         float getMinScreenX();



         /**
          * Get the coordinate of the payer in the axis X
          * @return the position of the motorbike in the axis X
          */
         float getMaxScreenX();



         /**
          * Get the maximum speed of the vehicle
          */
         int getMaxSpeed();



         /**
          * Uodate the position of the vehicle
          */
         void updatePositionY(const float speed);



         /**
         * Uodate the position of the vehicle
         */
        void updatePosition(const float speed);



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
         * @param lastHeight was the elevation of the terrain where was the motorbike
         * @param height is the actual elevation of the terrain where is the motorbike
         */
        inline void controlTurningPlayerLeftKeyboard(int& speed, bool& eventDetected, RenderWindow* app,
                                                     const int lastHeight, const int height, Elevation& e);



         /**
         * Control if the user has pressed the w keyword to turn to the right
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the motorbike
         * @param height is the actual elevation of the terrain where is the motorbike
         */
        inline void controlTurningPlayerRightKeyboard(int& speed, bool& eventDetected, RenderWindow* app,
                                                      const int lastHeight, const int height, Elevation& e);



        /**
         * Control if the user has pressed the q keyword to turn to the left
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         */
        inline void controlTurningPlayerLeftMouse(int& speed, bool& eventDetected, RenderWindow* app);



        /**
         * Control if the user has pressed the w keyword to turn to the right
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         */
        inline void controlTurningPlayerRightMouse(int& speed, bool& eventDetected, RenderWindow* app);



        /**
         * Control if the user has pressed the q keyword to increase the speed
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the motorbike
         * @param height is the actual elevation of the terrain where is the motorbike
         */
        inline void controlPlayerSpeed(int& speed, bool& eventDetected, RenderWindow* app,
                                       const int lastHeight, const int height, Elevation& el);



        /**
         * Control if the user has pressed the q keyword to increase the speed
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the motorbike
         * @param height is the actual elevation of the terrain where is the motorbike
         */
        inline void controlPlayerBraking(int& speed, bool& eventDetected, RenderWindow* app,
                                         const int lastHeight, const int height, Elevation& e);



        /**
         * Control if the player has done any of his possible actions
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the motorbike
         * @param height is the actual elevation of the terrain where is the motorbike
         */
        void controlActionPlayer(int& speed, bool& eventDetected, RenderWindow* app,
                                 const int lastHeight, const int height, Elevation& e);



        /**
         * Control if the player has have collision with the nearest element of the map to him
         * @param nearestStep is the step of the scene where is located the nearest element to the player
         * @param lastPos is the last position of the motorbike in the axis Y
         * @param pos is the current position of the motorbike in the axis Y
         */
        bool controlPossibleCollision(Step& nearestSprite, int lastPos, int pos);



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



        bool hasCrashed(float prevY, float currentY, float minX, float maxX, LandScape* m);



};


#endif

