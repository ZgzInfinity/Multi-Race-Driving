/*
 * Copyright (c) 2020 Andrés Gavín
 * Copyright (c) 2020 Rubén Rodríguez
 *
 * This file is part of Out Run.
 * Out Run is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Out Run is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Out Run.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

/*
 * Module SoundPlayer interface file
 */

#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#include <iostream>
#include <cstring>
#include <vector>
#include <thread>
#include <mutex>
#include "SFML/Audio.hpp"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace sf;
using namespace rapidxml;


struct SoundPlayer {

        // Code of soundtrack to reproduce
        int currentSoundtrack;

         // Control the volume of the effects and the music
        int volumeEffects, volumeMusic;

        // Vector of soundtracks of the game
        vector<unique_ptr<Music>> soundTracks;

        // Vector with all the sound effects to reproduce
        vector<unique_ptr<Music>> soundEffects;

        // Vector with the titles of the soundtracks
        string titleSoundtracks[10];

        // Control if the soundtrack has been change recently
        bool soundtrackChanged;

        // Mutex to control the load of the soundtracks and sound effects
        mutex loaderSounds;



        /**
         * Default constructor
         */
        SoundPlayer(const int volMusic, const int volEffects);



        /**
         * Load all the soundtracks of the game from the xml configuration file of the soundtracks
         * @param pathFile is the xml configuration file of the soundtracks
         */
        void loadSoundtracksOfGame(const string pathFile);



        /**
         * Load all the soundtracks of the game from the xml configuration file of the sound effects
         * @param pathFile is the xml configuration file of the sound effects
         */
        void loadSoundEffectsOfGame(const string pathFile);

};


#endif // SOUND_PLAYER_H
