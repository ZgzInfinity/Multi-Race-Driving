

#include "../include/Menu.h"
#include "../include/Game.h"
#include "../include/SoundPlayer.h"

#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;

int main() {

    // Creation of the configuration module of the game
    Configuration c;

    // Creation of the reproductor module of the game
    SoundPlayer r;

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
                case PLAY_GAME: {
                    // Start the corresponding game selected by the player
                    state = engine.play(c, r);
                    break;
                }
                case CLASIFICATION: {
                    int minutes = int(engine.getMinutesTrip());
                    int secs = int(engine.getSecsTrip());
                    int cents_Second = int(engine.getCents_SecondTrip());
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
