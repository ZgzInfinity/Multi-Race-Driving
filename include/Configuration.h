
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

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

    public:

        /**
         * Default constructor of the data type configuration
         */
        Configuration();



        /**
         * Returns the key used to accelerate the player's vehicle
         */
        Keyboard::Key getAccelerateKey();



        /**
         * Returns the key used to brake the player's vehicle
         */
        Keyboard::Key getBrakeKey();



        /**
         * Returns the key used to turn to the left the player's vehicle
         */
        Keyboard::Key getLeftKey();



        /**
         * Returns the key used to turn to the right the player's vehicle
         */
        Keyboard::Key getRightKey();



        /**
         * Change the configuration of the
         */
        void changeConfiguration();

};


#endif
