
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
#include "LandScape.h"
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
class Player{

     protected:

        Texture t;

        // Code of the actual image texture
        int actual_code_image;

        // Position of the main character
        float playerX = 0, playerY = 0, previousY = 0, minScreenX = 0, maxScreenX = 0;

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
        Player(char* pathFile, Configuration* conf){
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
            c = conf;
        }



        /**
         * Load the set of sprites of the player
         */
        void loadVehicleProperties(const string path){
            // Document xml where the document is going to be parsed
            xml_document<> doc;
            const char *pch = path.c_str();
            file<> file(pch);
            // Parsing the content of file
            doc.parse<0>(file.data());

            // Get the principal node of the file
            xml_node<> *nodePlayer = doc.first_node();

            // Loop in order to iterate all the children of the principal node
            for (xml_node<> *child = nodePlayer->first_node(); child; child = child->next_sibling()){
                // Check if the actual node is the controller of the paths of the sprites
                if ((string)child->name() == "SpritePaths"){
                    // Loop for iterate throughout the path files and add then to the vector
                    for (xml_node<> * pathNode = child->first_node(); pathNode; pathNode = pathNode->next_sibling()){
                        // Add the texture to the vector
                        if (t.loadFromFile(string(filePath) + pathNode->value())){
                            // Increment the textures read
                            textures.push_back(t);
                        }
                    }
                }
                // Check if the actual node is the controller of the max speed of the vehicle
                else if ((string)child->name() == "MaxSpeed"){
                    maxSpeed = RATIO * stoi(child->value());
                }
            }
            // Initialize the medium speed of the vehicle
            mediumSpeed = INITIAL_SPEED + maxSpeed / 2;

            // Initialize the control speed of the vehicle to calculate the inertia force
            controlSpeed = INITIAL_SPEED + mediumSpeed / 2;
        }



        /**
         * Draw the player sprite in the console render window
         * @param app is the console window game where the sprite is going to be drawn
         * @param pos is the actual position of the player in the map
         */
        virtual void drawPlayer(RenderWindow* app, int pos) = 0;



        /**
         * Check if the player has to advance in the track
         * @param eventDetected is a boolean to control if an event has occurred
         * @param lastHeight was the elevation of the terrain where was the motorbike
         * @param height is the actual elevation of the terrain where is the motorbike
         */
        virtual void advancePlayer(bool& eventDetected, const int lastHeight, const int height, Elevation& e) = 0;



        /**
         * Establish the coordinate X and Y of the vehicle
         * @param pX is the coordinate of the vehicle in the axis X
         * @param pY is the coordinate of the vehicle in the axis Y
         */
        void setPosition(float pX, float pY){
            playerX = pX;
            playerY = pY;
        }



        /**
         * Get the coordinate of the payer in the axis X
         * @return the position of the motorbike in the axis X
         */
         float getPlayerX(){
            return playerX;
         }



         /**
         * Get the coordinate of the payer in the axis X
         * @return the position of the motorbike in the axis X
         */
         float getPlayerY(){
            return playerY;
         }



         /**
         * Get the coordinate of the payer in the axis X
         * @return the position of the motorbike in the axis X
         */
         float getPreviousY(){
            return previousY;
         }



         /**
          * Get the coordinate of the payer in the axis X
          * @return the position of the motorbike in the axis X
          */
         float getMinScreenX(){
            return minScreenX;
         }



         /**
          * Get the coordinate of the payer in the axis X
          * @return the position of the motorbike in the axis X
          */
         float getMaxScreenX(){
            return maxScreenX;
         }



         /**
          * Get the mode of collision of the motorbike
          * @return the mode to show the collision of the motorbike
          */
         virtual int getModeCollision() = 0;



          /**
          * Get the mode of collision of the motorbike
          * @return the mode to show the collision of the motorbike
          */
         Configuration* getConfiguration(){
            return c;
         }



         /**
          * Return the position of the vehicle in a tuple
          */
         pair<float, float> getPosition() const {
            return make_pair(playerX, playerY);
         }



         /**
          * Get the maximum speed of the vehicle
          */
         int getMaxSpeed(){
            return maxSpeed;
         }



         /**
          * Uodate the position of the vehicle
          */
         void updatePositionY(const float speed){
            previousY = playerY;
            playerY += (speed);
         }



         /**
          * Uodate the position of the vehicle
          */
         void updatePosition(const float speed){
            previousY = playerY;
            playerY += (speed / 190.f);
         }



         /**
          * Control if the user has pressed the q keyword to turn to the left
          * @param speed is the actual speed of the motorbike of the player
          * @param eventDetected is a boolean to control if an event has occurred
          * @param app is the console window game where the sprite is going to be drawn
          * @param lastHeight was the elevation of the terrain where was the motorbike
          * @param height is the actual elevation of the terrain where is the motorbike
          */
         virtual inline void controlTurningPlayerLeftKeyboard(int& speed, bool& eventDetected, RenderWindow* app,
                                                              const int lastHeight, const int height, Elevation& e) = 0;



        /**
         * Control if the user has pressed the w keyword to turn to the right
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the motorbike
         * @param height is the actual elevation of the terrain where is the motorbike
         */
         virtual inline void controlTurningPlayerRightKeyboard(int& speed, bool& eventDetected, RenderWindow* app,
                                                              const int lastHeight, const int height, Elevation& e) = 0;



        /**
         * Control if the user has pressed the q keyword to increase the speed
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the motorbike
         * @param height is the actual elevation of the terrain where is the motorbike
         */
        virtual inline void controlPlayerSpeed(int& speed, bool& eventDetected, RenderWindow* app,
                                               const int lastHeight, const int height, Elevation& e) = 0;



         /**
         * Control if the user has pressed the q keyword to increase the speed
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the player
         * @param height is the actual elevation of the terrain where is the player
         */
        virtual inline void controlPlayerBraking(int& speed, bool& eventDetected, RenderWindow* app,
                                         const int lastHeight, const int height,  Elevation& e) = 0;


        /**
         * Control if the player has done any of his possible actions
         * @param speed is the actual speed of the motorbike of the player
         * @param eventDetected is a boolean to control if an event has occurred
         * @param app is the console window game where the sprite is going to be drawn
         * @param lastHeight was the elevation of the terrain where was the player
         * @param height is the actual elevation of the terrain where is the player
         */
        virtual void controlActionPlayer(int& speed, bool& eventDetected, RenderWindow* app,
                                         const int lastHeight, const int height, Elevation& e) = 0;



        /**
         * Control if the player has have collision with the nearest element of the map to him
         * @param nearestStep is the step of the scene where is located the nearest element to the player
         * @param lastPos is the last position of the motorbike in the axis Y
         * @param pos is the current position of the motorbike in the axis Y
         */
        virtual bool controlPossibleCollision(Step& nearestSprite, int lastPos, int pos) = 0;



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



        virtual bool hasCrashed(float prevY, float currentY, float minX, float maxX, LandScape* m) = 0;



};


#endif
