

#include "../include/EffectReproductor.h"


/**
 * Constructor of the data type
 */
EffectReproductor::EffectReproductor(){}



/**
 * Load the sound effects from the xml file configuration
 * @param soundEffectFile is the file where are indicated all the sound
 * effects of the game
 */
void EffectReproductor::loadEffectsOfGame(char* soundEffectFile){
    // Read the textures used for the menus from the file

    // Document xml where the document is going to be parsed
    xml_document<> doc;
    file<> file(soundEffectFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *soundEffectNode = doc.first_node();

    // Loop in order to iterate all the children of the principal node
    for (xml_node<> *effect = soundEffectNode->first_node(); effect; effect = effect->next_sibling()){
        // Create the pointer where the music is going to be allocated
        auto soundEffect = make_unique<sf::Music>();
        // Open the sound effect file and store it in the vector of sound effects
        soundEffect->openFromFile((string)effect->value());
        effects.push_back(move(soundEffect));
    }
}



/**
 * Reproduce a concrete sound selected by the user
 * @param index is the code of the sound effect to reproduce in the list
 */
void EffectReproductor::reproduceEffect(const int index){
    effects[index]->play();
}



/**
 * Stop the sound which is currently been reproduced
 * @param index is the code of the sound effect to stop in the list
 */
void EffectReproductor::stopEffect(const int index){
    effects[index]->stop();
}

