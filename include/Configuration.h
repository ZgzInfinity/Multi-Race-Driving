
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Configuration {

    private:

        // Acceleration of the player's vehicle
        Keyboard::Key accelerateKey;

        // Braking of the player's vehicle
        Keyboard::Key brakeKey;

        // Turning left of the player's vehicle
        Keyboard::Key leftKey;

        // Turning right of the player's vehicle
        Keyboard::Key rightKey;

        // Change the soundtrack level
        Keyboard::Key changeSoundtrackLevel;

        // Go back keyword
        Keyboard::Key goBackKey;

        // Start keyword
        Keyboard::Key startKey;

    public:

        /**
         * Default constructor of the data type configuration
         */
        Configuration();



        /**
         * Assign the accelerate control key
         */
        void setAccelerateKey(const Keyboard::Key key);



        /**
         * Returns the key used to accelerate the player's vehicle
         */
        Keyboard::Key getAccelerateKey();



        /**
         * Assign the brake control key
         */
        void setBrakeKey(const Keyboard::Key key);



        /**
         * Returns the key used to brake the player's vehicle
         */
        Keyboard::Key getBrakeKey();



        /**
         * Assign the left control key
         */
        void setLeftKey(const Keyboard::Key key);



        /**
         * Returns the key used to turn to the left the player's vehicle
         */
        Keyboard::Key getLeftKey();



        /**
         * Assign the right control key
         */
        void setRightKey(const Keyboard::Key key);



        /**
         * Returns the key used to turn to the right the player's vehicle
         */
        Keyboard::Key getRightKey();



        /**
         * Returns the key used to turn to the right the player's vehicle
         */
        Keyboard::Key getStart();



         /**
         * Assign the key used to change the level soundtrack
         */
         void setChangeSoundtrack(const Keyboard::Key key);



        /**
         * Returns the key used to change the level soundtrack
         */
        Keyboard::Key getChangeSoundtrack();



        /**
         * Check if the player has pressed the key to change the actual level
         * soundtrack
         */
        bool checkChangeMusic();



        /**
         * Check if the key that is going to be assign is already selected
         * @param key is the candidate keyword
         */
        bool isRepeated(const Keyboard::Key key);

};


#endif
