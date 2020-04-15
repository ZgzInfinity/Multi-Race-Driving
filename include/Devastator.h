
#ifndef DEVASTATOR_H
#define DEVASTATOR_H

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
class Devastator : public Player {

    public:

        /**
         * Constructor of the class
         */
        Devastator(char* pathFile, Configuration* c);



        /**
         * Load the set of sprites of the player
         */
         void loadVehicleProperties(const string path);



        /**
         * Draw the player sprite in the console render windowDevastator
         * @param app is the console window game where the sprite is going to be drawn
         * @param pos is the actual position of the Devastator in the map
         */
        void drawPlayer(RenderWindow* app, int pos);



      /**
       * Check if the player has to advance in the track
       * @param eventDetected is a boolean to control if an event has occurred
       * @param height is the actual elevation of the terrain where is the Devastator
       * @param lastHeight was the elevation of the terrain where was the Devastator
       */
       void advancePlayer(bool& eventDetected);



       /**
         * Check if the player has to advance in the track
         * @param eventDetected is a boolean to control if an event has occurred
         * @param lastHeight was the elevation of the terrain where was the Devastator
         * @param height is the actual elevation of the terrain where is the Devastator
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
         * @return the position of the Devastator in the axis X
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
          * Uodate the position of the vehicle
          */
        void updatePositionY(const float speed);




        /**
         * Uodate the position of the vehicle
         */
        void updatePosition(const float speed);



         /**
          * Get the mode of collision of the Devastator
          * @return the mode to show the collision of the Devastator
          */
         int getModeCollision();



        /**
         * Control if the user has pressed the q keyword to turn to the left
         * @param speed is the actual speed of the Devastator of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the Devastator
         * @param height is the actual elevation of the terrain where is the Devastator
         */
        inline void controlTurningPlayerLeftKeyboard(int& speed, bool& eventDetected, RenderWindow* app,
                                                     const int lastHeight, const int height, Elevation& e);



         /**
         * Control if the user has pressed the w keyword to turn to the right
         * @param speed is the actual speed of the Ferrari of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the Devastator
         * @param height is the actual elevation of the terrain where is the Devastator
         */
        inline void controlTurningPlayerRightKeyboard(int& speed, bool& eventDetected, RenderWindow* app,
                                                      const int lastHeight, const int height, Elevation& e);



        /**
         * Control if the user has pressed the q keyword to turn to the left
         * @param speed is the actual speed of the Ferrari of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         */
        inline void controlTurningPlayerLeftMouse(int& speed, bool& eventDetected, RenderWindow* app);



        /**
         * Control if the user has pressed the w keyword to turn to the right
         * @param speed is the actual speed of the Ferrari of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         */
        inline void controlTurningPlayerRightMouse(int& speed, bool& eventDetected, RenderWindow* app);



        /**
         * Control if the user has pressed the q keyword to increase the speed
         * @param speed is the actual speed of the Ferrari of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the Devastator
         * @param height is the actual elevation of the terrain where is the Devastator
         */
        inline void controlPlayerSpeed(int& speed, bool& eventDetected, RenderWindow* app,
                                       const int lastHeight, const int height, Elevation& e);



       /**
        * Control if the user has pressed the q keyword to increase the speed
        * @param speed is the actual speed of the Ferrari of the player
        * @param eventDetected is a boolean to control if an event has occurred
        * @param app is the console window game where the sprite is going to be drawn
        * @param lastHeight was the elevation of the terrain where was the Devastator
        * @param height is the actual elevation of the terrain where is the Devastator
        */
        inline void controlPlayerBraking(int& speed, bool& eventDetected, RenderWindow* app,
                                         const int lastHeight, const int height, Elevation& e);



        /**
         * Control if the player has done any of his possible actionsconst int lastHeight, const int height
         * @param speed is the actual speed of the Ferrari of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the Devastator
         * @param height is the actual elevation of the terrain where is the Devastator
         */
        void controlActionPlayer(int& speed, bool& eventDetected, RenderWindow* app, const int lastHeight, const int height, Elevation& e);



        /**
         * Control if the player has have collision with the nearest element of the map to him
         * @param nearestStep is the step of the scene where is located the nearest element to the player
         * @param lastPos is the last position of the Ferrari in the axis Y
         * @param pos is the current position of the Ferrari in the axis Y
         */
        bool controlPossibleCollision(Step& nearestSprite, int lastPos, int pos);



        /**
         * Control if there is there inertia force or not if the Ferrari is on a curve of the scene
         * @param onCurve is a boolean which represents if the Ferrari is on curve or not
         * @param curve is the possible curve of the scene where the Ferrari is currently now
         * @param speed is the actual speed of the Ferrari of the player
         */
        void controlInertiaForce(bool& onCurve, IntervalCurve& curve, int& speed);



        /**
         * Shows to the user how the Ferrari crushes
         * @param pos is the position of the Devastator in the car in the axis Y
         */
        void collisionShow();



        bool hasCrashed(float prevY, float currentY, float minX, float maxX, Map* m);

};

#endif // DEVASTATOR_H
