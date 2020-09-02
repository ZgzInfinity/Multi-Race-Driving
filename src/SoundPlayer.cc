
/*
 * Module SoundPlayer implementation file
 */


#include "../include/SoundPlayer.h"


/**
 * Default constructor
 */
SoundPlayer::SoundPlayer(const int volMusic, const int volEffects){

    // Initialize the default soundtrack of the game
    currentSoundtrack = 2;

    // Default volume for the sound effects
    volumeEffects = volEffects;

    // Default volume for the soundtracks
    volumeMusic = volMusic;

    // Soundtrack not changed by default
    soundtrackChanged = false;

    // Store the titles of the soundtracks
    titleSoundtracks[0] = "REDLINE SHUFFLE";   titleSoundtracks[5] = "EGYPTIAN CROSSING";
    titleSoundtracks[1] = "HOUSE SPECIAL";     titleSoundtracks[6] = "SPRINTER";
    titleSoundtracks[2] = "WINNING ROAD";      titleSoundtracks[7] = "FUNKY SEA";
    titleSoundtracks[3] = "BLUEGRASS BOGGIE";  titleSoundtracks[8] = "BOOTY SHAKER";
    titleSoundtracks[4] = "ROADKILL JAM";      titleSoundtracks[9] = "EURO HOUSE";

    // Path of the xml configuration file of the soundtracks
    string path = "Data/Soundtracks/Configuration/Configuration.xml";

    // Load the soundtracks of the game
    thread soundtracksLoader = thread(loadSoundtracksOfGame, this, path);

    // Path of the xml configuration file of the sound effects
    path = "Data/SoundEffects/Configuration/Configuration.xml";

    // Load the sound effects of the game
    thread effecsLoader = thread(loadSoundEffectsOfGame, this, path);

    // Wait until threads have finished
    soundtracksLoader.join();
    effecsLoader.join();
}



/**
 * Load all the soundtracks of the game from the xml configuration file of the soundtracks
 * @param pathFile is the xml configuration file of the soundtracks
 */
void SoundPlayer::loadSoundtracksOfGame(const string pathFile){

    // Open the xml file of the soundtracks or sound effects
    char* pFile = const_cast<char*>(pathFile.c_str());
    xml_document<> doc;
    file<> file(pFile);

    // Parsing the content of file
    doc.parse<0>(file.data());

    // Get the principal node of the file
    xml_node<> *nodeSoundTrack = doc.first_node();

    // Loop in order to iterate all the children of the principal node
    for (xml_node<> *soundtrack = nodeSoundTrack->first_node(); soundtrack; soundtrack = soundtrack->next_sibling()){
        // Create the pointer where the music is going to be allocated
        loaderSounds.lock();
        auto soundTrack = make_unique<sf::Music>();
        // Open the soundtrack file and store it in the vector of soundtracks
        soundTrack->openFromFile((string)soundtrack->value());
        // Reproduce the soundtracks in loop and with the level music read in the xml file
        soundTrack->setLoop(true);
        soundTrack->setVolume(volumeMusic);
        // Check if ir is or nor a soundtrack reproduced during the game
        soundTracks.push_back(move(soundTrack));
        loaderSounds.unlock();
    }
}



/**
 * Load all the soundtracks of the game from the xml configuration file of the sound effects
 * @param pathFile is the xml configuration file of the sound effects
 */
void SoundPlayer::loadSoundEffectsOfGame(const string pathFile){

    // Open the xml file of the soundtracks or sound effects
    char* pFile = const_cast<char*>(pathFile.c_str());
    xml_document<> doc;
    file<> file(pFile);

    // Parsing the content of file
    doc.parse<0>(file.data());

    // Get the principal node of the file
    xml_node<> *nodeSoundEffect = doc.first_node();

    // Loop in order to iterate all the children of the principal node
    for (xml_node<> *effect = nodeSoundEffect->first_node(); effect; effect = effect->next_sibling()){

        // Create the pointer where the music is going to be allocated
        loaderSounds.lock();
        auto soundEffect = make_unique<sf::Music>();
        // Open the sound effect file and store it in the vector of sound effects
        soundEffect->openFromFile((string)effect->value());
        // Store the level volume of the sound effects
        soundEffect->setVolume(volumeEffects);
        soundEffects.push_back(move(soundEffect));
        loaderSounds.unlock();
    }
}



