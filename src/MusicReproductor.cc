

#include "../include/MusicReproductor.h"



/**
 * Constructor of the data type
 */
MusicReproductor::MusicReproductor(){
    sound = unique_ptr<Music>(new Music());
}



/**
 * Load of the soundtrack files from the xml file configuration
 * @param soundtrakFile is the xml configuration file of the audios
 */
void MusicReproductor::loadSoundtracksOfGame(char* soundtrackFile){
    // Read the textures used for the menus from the file

    // Document xml where the document is going to be parsed
    xml_document<> doc;
    file<> file(soundtrackFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *soundtrackNode = doc.first_node();

    // Loop in order to iterate all the children of the principal node
    for (xml_node<> *soundtrack = soundtrackNode->first_node(); soundtrack; soundtrack = soundtrack->next_sibling()){
        // Check if the actual node control the animation at the beginning
        if ((string)soundtrack->name() == "headAnimationMainMenu" || (string)soundtrack->name() == "PlayerGameDifficultMenu" ||
            (string)soundtrack->name() == "VehicleMenu" || (string)soundtrack->name() == "ResultsMenu" ||
            (string)soundtrack->name() == "Options")
        {
            // Variables to control the attributes of the soundtrack
            string name; int volume, loop; bool inLoop;
            // Load the music properties
            for (xml_node<> *property = soundtrack->first_node(); property; property = property->next_sibling()){
                // Check the attributes of the soundtrack
                if ((string)property->name() == "Path"){
                    // Get the path
                    name = property->value();
                    continue;
                }
                // Check if the attribute of the loop
                else if ((string)property->name() == "Loop"){
                    // Get the volume
                    loop = stoi(property->value());
                    // Check the loop flag
                    if (loop == 1){
                        inLoop = true;
                    }
                    else {
                        inLoop = false;
                    }
                    continue;
                }
                // Check if the attribute of the volume
                else if ((string)property->name() == "Volume"){
                    // Get the volume
                    volume = stoi(property->value());

                    // Creation of the soundtrack
                    Soundtrack s = Soundtrack(name, volume, inLoop);
                    // Add the soundtrack in the soundtrack list of the reproductor
                    soundtrackTitles.push_back(s);

                }
            }
        }
        else if ((string)soundtrack->name() == "GameSoundtracks"){
            // Variables to control the attributes of the soundtrack
            int volume; bool inLoop;
            // Load the music properties
            for (xml_node<> *property = soundtrack->first_node(); property; property = property->next_sibling()){
                // Check if the attribute of the loop
                if ((string)property->name() == "Loop"){
                    // Get the volume
                    int loop = stoi(property->value());
                    // Check the loop flag
                    if (loop == 1){
                        inLoop = true;
                    }
                    else {
                        inLoop = false;
                    }
                    continue;
                }
                // Check if the attribute of the volume
                else if ((string)property->name() == "Volume"){
                    // Get the volume
                    volume = stoi(property->value());
                    continue;
                }
                // Check if the attribute is the list of the soundtrack titles
                else if ((string)property->name() == "List"){
                    // Get the music titles
                    string title;
                    for (xml_node<> *name = property->first_node(); name; name = name->next_sibling()){
                        // Get the title of the soundtrack
                        title = name->value();
                        // Creation of the soundtrack
                        Soundtrack s = Soundtrack(title, volume, inLoop);
                        // Add the soundtrack in the soundtrack list of the reproductor
                        soundtrackTitles.push_back(s);

                        // Create smart pointer and open it in order to reproduce it only
                        unique_ptr<Music> music = unique_ptr<Music>(new Music());
                        // Only once time the music file is opened
                        music->openFromFile(title);
                        // Add to the pointer vector of music pointer
                        themes.push_back(move(music));
                    }
                }
            }
        }
        // Check if it's the node that control the text of the soundtrack
        else if ((string)soundtrack->name() == "SoundtrackTitle"){
            // Iterate all the attributes of the text
            int sizeText, positionXText, positionYText, border;
            Color colorText, colorBorder;
            for (xml_node<> *textProperty = soundtrack->first_node(); textProperty; textProperty = textProperty->next_sibling()){
                // Check if it's the node that controls the main menu of the game
                if ((string)textProperty->name() == "Font"){
                    // Path of the main text font
                    font.loadFromFile(textProperty->value());
                    continue;
                }
                // Check the size of the main text
                else if ((string)textProperty->name() == "Size"){
                    // Size of the main text
                    sizeText = stoi(textProperty->value());
                    continue;
                }
                // Check the x coordinate of the main text
                else if ((string)textProperty->name() == "PositionX"){
                    // Get x coordinate of the cover
                    positionXText = stoi(textProperty->value());
                    continue;
                }
                // Check the y coordinate of the main text
                else if ((string)textProperty->name() == "PositionY"){
                    // Get y coordinate of the cover
                    positionYText = stoi(textProperty->value());
                    continue;
                }
                // Check the y coordinate of the main text
                else if ((string)textProperty->name() == "Border"){
                    // Get y coordinate of the cover
                    border = stoi(textProperty->value());
                    continue;
                }
                // Check if it's the node that controls the text of the speed panel
                else if ((string)textProperty->name() == "ColorInside" || (string)textProperty->name() == "ColorBorder"){
                    // Variables to define the color of the text
                    int channelR, channelG, channelB;
                    // Loop in order to iterate all the children nodes of the text's color
                    for (xml_node<> *colorNode = textProperty->first_node(); colorNode; colorNode = colorNode->next_sibling()){
                        // Check the value of the red channel
                        if ((string)colorNode->name() == "R"){
                            // Get y coordinate of the cover
                            channelR = stoi(colorNode->value());
                            continue;
                        }
                        // Check the value of the green channel
                        else if ((string)colorNode->name() == "G"){
                            // Get y coordinate of the cover
                            channelG = stoi(colorNode->value());
                            continue;
                        }
                        // Check the value of the blue channel
                        else if ((string)colorNode->name() == "B"){
                            // Get y coordinate of the cover
                            channelB = stoi(colorNode->value());
                            // Store the color in the correct color field
                            if ((string)textProperty->name() == "ColorInside"){
                                // Store the color of the text when the slot is selected
                                colorText = Color(channelR, channelG, channelB);
                            }
                            else if ((string)textProperty->name() == "ColorBorder"){
                                // Store the color of the border when the slot is selected
                                colorBorder = Color(channelR, channelG, channelB);
                            }
                        }
                    }
                    titleSoundtrack.setPosition(positionXText, positionYText);
                    titleSoundtrack.setCharacterSize(sizeText);
                    titleSoundtrack.setFont(font);
                    titleSoundtrack.setFillColor(colorText);
                    titleSoundtrack.setOutlineColor(colorBorder);
                    titleSoundtrack.setOutlineThickness(border);
                }
            }
        }
    }
}



/**
 * Reproduce a concrete sound selected by the user
 * @param path is the path of the sound to reproduce
 * @param inLoop is a boolean to control if the sound is reproduce in a loop or not
 * @param volume is the volume level of reproduction
 */
void MusicReproductor::reproduceSound(const string path, const bool inLoop, const int volume){
    sound->openFromFile(path);
    sound->setVolume(volume);
    if (inLoop){
        sound->setLoop(true);
    }
    sound->play();
}



/**
 * Stop the sound which is currently been reproduced
 */
void MusicReproductor::stopSound(){
    sound->stop();
}



/**
 * Add the title of a soundtrack to the list of titles
 * @param path is the title of the sound stored
 */
void MusicReproductor::addSoundtrack(const string path){
    auto ptr = std::make_unique<sf::Music>();
    ptr->openFromFile(path);
    themes.push_back(std::move(ptr));
}



/**
 * Start the list of the soundtracks
 */
void MusicReproductor::startSoundtrackList(){
    positionSound = 0;
}



/**
 * Get the actual soundtrack to be reproduced
 * @param i is the code of the soundtrack to be reproduced
 */
Soundtrack MusicReproductor::getSoundtrack(const int i){
    return soundtrackTitles[i];
}



/**
 * Get index of the soundtrack to be reproduced
 */
int MusicReproductor::getIndexPosition(){
    return positionSound;
}



/**
 * Get the title of the soundtrack which is going to be displayed
 */
Text MusicReproductor::getTitleSoundtrack(){
    return titleSoundtrack;
}



/**
 * Advance the position index to reproduce the following soundtrack
 */
void MusicReproductor::advanceSoundtrack(){
    positionSound++;
}



/**
 * Advance the position index to reproduce the following soundtrack
 */
void MusicReproductor::backSoundtrack(){
    positionSound--;
}



/**
 * Select one soundtrack randomly from the available soundtracks for play
 */
void MusicReproductor::getRandomSoundtrack(){
    srand(time(NULL));
    positionSound = rand() % (soundtrackTitles.size() - 5);
}



/**
 * Reproduce soundtrack of level game
 */
void MusicReproductor::reproduceLevelSoundtrack(){
    // Get the actual soundtrack
    Soundtrack s = getSoundtrack(getIndexPosition());
    // Update the title of the new soundtrack to play
    titleSoundtrack.setString(soundtrackTitles[positionSound + 3].getTitle().
                    substr(11 , soundtrackTitles[positionSound + 3].getTitle().find('.') - 11));

    // Control the configuration to reproduce the new soundtrack
    themes[positionSound]->setLoop(s.isInLoop());
    themes[positionSound]->setVolume(s.getVolume());
    themes[positionSound]->play();
}



/**
 * Stop the soundtrack of level game which is in curse
 */
void MusicReproductor::stopLevelSoundtrack(){
    themes[positionSound]->stop();
}



/**
 * Advanced soundtrack level of game
 */
void MusicReproductor::advanceSoundtrackLevel(){
    // Stop the actual level soundtrack
    stopLevelSoundtrack();
    // Advance the soundtrack list to the next
    positionSound = (positionSound != (int)themes.size() -1) ? positionSound + 1 : 0;
    // Reproduce the new soundtrack
    reproduceLevelSoundtrack();
}


