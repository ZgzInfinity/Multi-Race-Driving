

#include <thread>
#include "windows.h"
#include "../include/Menu.h"
#include "../include/Game.h"
#include "../include/SoundPlayer.h"

mutex mainMutex;

#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;


void loadGameConfiguration (const string path, Difficult& difficulty, bool& activeAI, int& volumeSoundtracks,
                            int& volumeEffects, bool& pixelArt, bool& fullScreen, int& axis_x, int& axis_y, string& controlLeft,
                            string& controlRight, string& controlAccelerate, string& controlBrake,
                            string& controlSoundtrack)
{

     // Open the xml file of the scenario
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Iterate the different configuration nodes
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check if it's the node that control the difficulty of the level
        if ((string)property->name() == "Difficulty"){
            // Get the difficulty value
            if ((string)property->value() == "Peaceful"){
                // Level peaceful
                difficulty = PEACEFUL;
            }
            else if ((string)property->value() == "Easy"){
                // Level easy
                difficulty = EASY;
            }
            else if ((string)property->value() == "Normal"){
                // Level normal
                difficulty = NORMAL;
            }
            else if ((string)property->value() == "Hard"){
                // Level hard
                difficulty = HARD;
            }
        }
        // Check the AI configuration
        else if ((string)property->name() == "AI"){
            // Get if the AI is enabled
            if ((string)property->value() == "Disabled"){
                activeAI = false;
            }
            else {
                activeAI = true;
            }
        }
        // Check if it`s the node that controls the soundtracks volume
        else if ((string)property->name() == "Volume_Soundtracks"){
            // Get the volume
            volumeSoundtracks = stoi(property->value());
        }
        // Check if it's the node that controls the soundtracks volume
        else if ((string)property->name() == "Volume_Effects"){
            // Get the volume
            volumeEffects = stoi(property->value());
        }
        // Check if it's the node that controls the soundtracks volume
        else if ((string)property->name() == "PixelArt"){
            // Get if the pixelArt is enabled
            if ((string)property->value() == "Enabled"){
                pixelArt = true;
            }
            else {
                pixelArt = false;
            }
        }
        // Check if it's the node that controls the soundtracks volume
        else if ((string)property->name() == "Full_screen"){
            // Get if the pixelArt is enabled
            if ((string)property->value() == "Enabled"){
                fullScreen = true;
            }
            else {
                fullScreen = false;
            }
        }
        // Check if it's the node that controls the x resolution of the screen
        else if ((string)property->name() == "Resolution_x"){
            // Get the resolution in axis x
            axis_x = stoi(property->value());
        }
        // Check if it's the node that controls the y resolution of the screen
        else if ((string)property->name() == "Resolution_y"){
            // Get the resolution in axis y
            axis_y = stoi(property->value());
        }
        // Check if it's the node that controls the turning left control
        else if ((string)property->name() == "Controller_left"){
            // Get the turning left controller
            controlLeft = property->value();
        }
        // Check if it's the node that controls the turning right control
        else if ((string)property->name() == "Controller_right"){
            // Get the turning right controller
            controlRight = property->value();
        }
        // Check if it's the node that controls the accelerating control
        else if ((string)property->name() == "Controller_accelerate"){
            // Get the turning left controller
            controlAccelerate = property->value();
        }
        // Check if it's the node that controls the braking control
        else if ((string)property->name() == "Controller_brake"){
            // Get the turning right controller
            controlBrake = property->value();
        }
        // Check if it's the node that controls the changing soundtrack control
        else if ((string)property->name() == "Controller_soundtrack"){
            // Get the turning right controller
            controlSoundtrack = property->value();
        }
    }
}



int main() {

    // Throw the application with hight priority
    SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

    // Load the properties of the game
    const string path = "Data/Settings/Configuration.xml";

    // Variables to control the configuration of the game
    Difficult difficulty;
    bool activeAI, pixelArt, fullScreen;
    int volumeSoundtracks, volumeEffects, axis_x, axis_y;
    string controlLeft, controlRight, controlAccelerate, controlBrake, controlSoundtrack;

    loadGameConfiguration(path, difficulty, activeAI, volumeSoundtracks, volumeEffects, pixelArt, fullScreen, axis_x, axis_y,
                          controlLeft, controlRight, controlAccelerate, controlBrake, controlSoundtrack);

    // Creation of the configuration module of the game
    Configuration c(difficulty, activeAI, pixelArt, fullScreen, axis_x, axis_y, controlLeft, controlRight, controlAccelerate,
                    controlBrake, controlSoundtrack);

    // Creation of the reproductor module of the game
    SoundPlayer r(volumeSoundtracks, volumeEffects);

    State state = ANIMATION;

    while (c.window.isOpen() && state != EXIT) {
        Game engine(c);

        sleep(milliseconds(500));
        if (state == START)
            state = startMenu(c, r);

        while (c.window.isOpen() && state != START) {
            switch (state) {
                case ANIMATION: {
                    state = introAnimation(c, r);
                    break;
                }
                case OPTIONS: {
                    sleep(milliseconds(500));
                    bool inGame = engine.isInGame();
                    state = optionsMenu(c, r, inGame);
                    engine.checkDifficulty(c);
                    break;
                }
                case PLAYER_MENU: {
                    state = playerMenu(c, r);
                    break;
                }
                case GAME_MODES_MENU: {
                    // Get the type of game selected by the user
                    int typeOfGame = engine.typeGame();
                    state = gameModesMenu(c, r, typeOfGame);

                    // Assign the type of game selected by the user
                    engine.setTypeOfGame(typeOfGame);
                    break;
                }
                case VEHICLE_SELECTION: {
                    // Select the vehicle by the player
                    state = engine.selectionVehicleMenu(c, r);
                    break;
                }
                case CIRCUIT_SELECTION_MENU: {
                    // Select the circuit to run in Pole Position
                    state = engine.selectionCircuitMenu(c, r);
                    break;
                }
                case LOAD_GAME: {
                    // Get the type of game selected by the user
                    int typeOfGame = engine.typeGame();

                    // Load the configuration depending of the game
                    switch(typeOfGame){
                        case 0:
                            // World tour mode
                            state = engine.loadWorldTourPolePositionConf(c);
                            break;
                        case 1:
                            // Out Run mode
                            state = engine.loadOutRunDrivingFuryDemarrageConf(c);
                            break;
                        case 2:
                            // Pole Position mode
                            state = engine.loadWorldTourPolePositionConf(c);
                            break;
                        case 3:
                            // Driving fury mode
                            state = engine.loadOutRunDrivingFuryDemarrageConf(c);
                            break;
                        case 4:
                            // Derramage mode
                            state = engine.loadOutRunDrivingFuryDemarrageConf(c);
                            break;
                        case 5:
                            // Delivery mode
                            cerr << "Temporary error" << endl;
                    }
                    break;
                }
                case LOADING: {
                    // Show the loading animation
                    state = showLoadingAnimation(c, r);
                    break;
                }
                case PLAY_GAME: {
                    // Start the corresponding game selected by the player
                    int typeOfGame = engine.typeGame();
                    if (typeOfGame == 0 || typeOfGame == 2){
                        state = engine.playWorldTourPolePosition(c, r);
                    }
                    else {
                        state = engine.playOutRunDrivingFuryDerramage(c, r);
                    }
                    break;
                }
                case CLASIFICATION: {
                    state = engine.classificationRace(c, r);
                    break;
                }
                case RANKING: {
                    unsigned long scorePlayer = engine.getScore();
                    int minutes = int(engine.getMinutesTrip());
                    int secs = int(engine.getSecsTrip());
                    int cents_Second = int(engine.getCents_SecondTrip());
                    int typeOfGame = engine.typeGame();
                    state = rankingMenu(c, r, scorePlayer, minutes, secs, cents_Second, typeOfGame);
                    break;
                }
                default: {
                    c.window.close();
                    break;
                }
            }
        }
    }
}
