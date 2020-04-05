

#ifndef MUSIC_REPRODUCTOR_H
#define MUSIC_REPRODUCTOR_H

#include <iostream>
#include "../include/Soundtrack.h"
#include <cstring>
#include "SFML/Audio.hpp"

using namespace std;
using namespace sf;
using namespace rapidxml;


class MusicReproductor {

    private:

        // Pointer used to reproduce the soundtrack selected
        unique_ptr<sf::Music> sound;

        // Vector with all the soundtracks to reproduce
        vector<unique_ptr<Music>> themes;

        // Vector with the titles of all the soundtracks to reproduce
        vector<Soundtrack> soundtrackTitles;

        // Position in the soundtrack list of the sound which is going to be reproduced
        int positionSound;

        // Title of soundtrack displayed in the console window
        Text titleSoundtrack;

        // Font of the text
        Font font;

    public:



        /**
         * Constructor of the data type
         */
        MusicReproductor();



        /**
         * Load of the soundtrack files from the xml file configuration
         */
        void loadSoundtracksOfGame(char* soundtrackFile);



        /**
         * Reproduce a concrete sound selected by the user
         * @param path is the path of the sound to reproduce
         * @param inLoop is a boolean to control if the sound is reproduce in a loop or not
         * @param volume is the volume level of reproduction
         */
        void reproduceSound(const string path, const bool inLoop, const int volume);



        /**
         * Stop the sound which is currently been reproduced
         */
        void stopSound();



        /**
         * Add the title of a soundtrack to the list of titles
         * @param path is the title of the sound stored
         */
        void addSoundtrack(const string path);



        /**
         * Start the list of the soundtracks
         */
        void startSoundtrackList();



        /**
         * Get the actual soundtrack to be reproduced
         * @param i is the code of the soundtrack to be reproduced
         */
        Soundtrack getSoundtrack(const int i);



        /**
         * Get index of the soundtrack to be reproduced
         */
        int getIndexPosition();



        /**
         * Get the title of the soundtrack which is going to be displayed
         */
        Text getTitleSoundtrack();



        /**
         * Advance the position index to reproduce the following soundtrack
         */
         void advanceSoundtrack();



         /**
          * Advance the position index to reproduce the following soundtrack
          */
         void backSoundtrack();



         /**
          * Select one soundtrack randomly from the available soundtracks for play
          */
         void getRandomSoundtrack();



         /**
          * Reproduce soundtrack of level game
          */
         void reproduceLevelSoundtrack();



         /**
          * Stop the soundtrack of level game which is in curse
           */
         void stopLevelSoundtrack();



         /**
          * Advanced soundtrack level of game
          */
         void advanceSoundtrackLevel();

};

#endif // MUSIC_REPRODUCTOR_H
