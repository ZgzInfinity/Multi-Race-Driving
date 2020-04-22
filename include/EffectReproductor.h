

#ifndef EFFECT_REPRODUCTOR_H
#define EFFECT_REPRODUCTOR_H

#include <iostream>
#include "SoundEffect.h"
#include <cstring>
#include "SFML/Audio.hpp"

using namespace std;
using namespace sf;
using namespace rapidxml;


class EffectReproductor {

    private:

        // Vector with all the sound effects to reproduce
        vector<unique_ptr<Music>> effects;

    public:


        /**
         * Constructor of the data type
         */
        EffectReproductor();



        /**
         * Load of the soundtrack files from the xml file configuration
         * @param soundEffectFile is the file where are indicated all the sound
         * effects of the game
         */
        void loadEffectsOfGame(char* soundEffectFile);



        /**
         * Reproduce a concrete sound selected by the user
         * @param index is the code of the sound effect to reproduce in the list
         */
        void reproduceEffect(const int index);



        /**
         * Stop the sound which is currently been reproduced
         * @param index is the code of the sound effect to stop in the list
         */
        void stopEffect(const int index);

};

#endif // EFFECT_REPRODUCTOR_H
