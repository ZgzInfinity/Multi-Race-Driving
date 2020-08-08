#pragma once

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include "Randomizer.h"
#include "Menu.h"
#include "LandScape.h"
#include "Motorbike.h"
#include "Devastator.h"
#include "Truck.h"
#include "Minivan.h"
#include "Police.h"
#include "TrafficCar.h"
#include "RivalCar.h"
#include <SFML/Graphics.hpp>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include "Globals.h"
#include "functional"


using namespace sf;
using namespace std;
using namespace rapidxml;

const float BONIFICATION = 1000000.0f;
const float DISTANCE_TRESHOLD = 5.0f;
const float DEL_DISTANCE = 50.0f;
const float SPEED_FACTOR = 70.0f;
const float DENSITY_SPACE = 3.0f;


/**
 * Lógica del juego que contiene la información del jugador, la información de los mapas y el HUD.
 * La información de los mapas está compuesta por un conjunto de objetos Map y su jerarquía de conexión entre ellos.
 * El HUD está formado por un cuadro de texto donde aparece la velocidad del jugador.
 */
class Game {

    // Determine the game selected by the player
    int typeOfGame;

    // Vector of landscapes for World tour and pole position modes
    vector<LandScape> tourLandScapes;

    // Matrix of landscapes for Out Run Driving fury and Derramage modes
    vector<vector<LandScape>> maps;
    vector<vector<LandScape>> referencedMaps;
    pair<int, int> mapId;
    LandScape *currentMap;
    LandScape goalMap;
    LandScape *startMap;
    LandScape middleMap;
    int goalFlagger, goalEnd;

    Motorbike player;
    Devastator player2;
    Minivan player3;
    Truck player4;
    Police player5;

    mutex mtx, mtx2;

    vector<TrafficCar> cars;

    vector<RivalCar> rivals;

    RivalCar goalCar;

    float lastY;
    bool vehicleCrash;
    bool drawingGoalCar;

    // Time to play
    int time;
    float timeMul;
    float timeAI;

    // Score of the player
    long long int score;
    float scoreMul;

    // Minutes of game played
    float minutes;

    // Seconds of game played
    float secs;

    // decs of game played
    float cents_second;

    // Minutes of game played
    float minutesTrip;

    // Seconds of game played
    float secsTrip;

    // decs of game played
    float cents_secondTrip;

    // Clock counter of time
    Clock gameClockTime;

    // Clock to control the woman shout
    Clock womanShot;

    // Control the sound of the traffic
    Clock trafficCarSound;

    // Control the
    Clock blinkTime;

    // Discount time bonus
    Clock bonus;

    // Count the time to change the soundtrack
    Clock soundtrackClock;

    // Count the time to reproduce a police car sound
    Clock policeCarClock;

    // Count the time to reproduce a police car sound
    Clock policeDriverClock;

    // Time to update the clock counter lap
    Time woman_delay;

    // Time to reproduce a new traffic car sound
    Time traffic_delay;

    // Time to reproduce a new traffic car sound
    Time blink_delay;

    // Time to reproduce a discount the time bonus
    Time bonus_delay;

    // Time to change a the soundtrack
    Time soundtrack_delay;

    // Time to reproduce a new police car sound
    Time police_car_delay;

    // Time to reproduce a sound of the police driver
    Time police_driver_delay;

    // Actual level
    int level;

    // End of game
    bool finalGame;

    // Control the game
    bool inGame;

    // Pause of the game
    bool onPause;

    // Control the options menu
    bool comeFromOptions;

    // Control the checkpoint
    bool checkPoint = false;
    int timeCheck;

    bool blink;

    bool arrival;

    // Counter time to update the HUD indicators
    float elapsed1, elapsed2, elapsed3, elapsed4,
          elapsed5, elapsed6, elapsed7, elapsed8,
          elapsed9, elapsed10, elapsed11, elapsed12,
          elapsed13, elapsed14, elapsed15, elapsed16,
          elapsed17, elapsed18;

    // Vector of textures for represent the game panel
    vector<Texture> textures;

    // Tree map with levels
    Texture treeMap[5][5];

    // Texts to represent the time inverted in a lap
    string lap, lapCheckPoint;

    // Vector with the positions of the checkpoints
    vector<int>checkPointPositions;

    // Index of the next checkpoint to pass
    int indexCheckPoint;

    // Update the time of checkpoint in world tour and pole position modes
    bool updatedTimeCheck;

    // Control the type of vehicle
    int typeOfVehicle;

    // Control the indexLandScape;
    int indexLandScape;

    // Position reached by the player in a race
    int posArrival;

    // Kind of of terrain of the current landscape
    int terrain;

    // Number of laps in Pole Position
    int numberLaps;

    // Laps done in Pole Position
    int lapsDone;

    // LandScape selected in Pole Position
    int landScapeSelected;

    // Control when the players increments the number of laps done
    bool newLap;

    // Lap indicator of lap
    float offsetLapIndicator;

    // Control the time to show new lap indicator
    int timeElapsed;

    // Control the new lap animation in Pole Position
    bool shown;

    // Threads of the game
    thread timer0, timer1, timer2, controllerPosition;


    int displayLapFactor;


    int numberRacers;


    int colorCarSelected;


    vector<float> rankingVehicles;


    bool displayGoalCarIndicator;


    int lifeGoalCar;


    int numCrashesGoalCar;


    int lifeLostPerCrash;


    bool updatedGoalCar, updatedPlayerCar;


    int maxDistance;


    int totalStages;


    int currentStage;


    int goalCarStage;


    int currentLandScape;


    int distanceGoalCar;


    bool goalNearCar;


    int distanceAdvanced;


    void storingRivalCars(Configuration& c);


    void loadWorldTourPolePositionLandScape(Configuration& c, const string path, const int i, int timeLandscape, const int typeOfGame,
                                            mutex tourLandScapesMutex[]);

    void loadOutRunDrivingFuryDerramageLandScape(Configuration& c, const string path, const int i, int timeLandscape,
                                                 const int typeOfGame, mutex tourLandScapesMutex[], vector<LandScape>& vm);

    void updateTimeElapsed();


    void updateTimeLandScape();


    void updateScore();


    int findPlayerPositionRanking(const float posYPlayer);


    /**
     * Load the Hud interface of the game
     */
    void loadHudGameWorldTourPolePosition();


    /**
     * Load the Hud interface of the game
     */
    void loadHudGameOutRunDrivingFuryDerramage();



    /**
     * Draw the bonus final animation
     * @param c is the configuration of the game
     * @param seconds are the seconds the player has left when he reaches the goal
     * @param decs_second are the hundreds of seconds the player has left when he reaches the goal
     */
    void drawBonus(Configuration &c, int seconds, int decs_second);



    /**
     * Draw the new lap animation
     * @param c is the configuration of the game
     * @param r is the sound reproducer of the game
     */
    void drawNewLap(Configuration &c);



    /**
     * Draw the HUD interface of the game
     * @param c is the configuration of the game
     */
    void showHudInterfaceOutRunDrivingFuryDerramage(Configuration &c);



    /**
     * Draw the HUD interface of the game
     * @param c is the configuration of the game
     */
    void showHudInterfaceWorldTourPolePosition(Configuration &c);



    /**
     * Change the soundtrack which is been sounding during the game
     * @param c is the configuration of the game
     * @param r is the sound reproducer of the game
     */
    void checkSoundtrackChanging(Configuration& c, SoundPlayer& r);



    /**
     * Display the message of check point the screen of the game
     * @param c is the configuration of the game
     * @param visible controls if the check point message is visible or not
     */
    void showCheckpointIndications(Configuration &c, bool visible);



    /**
     * Displays the message of game over in the console window
     * @param c is the configuration of the game
     */
    static void showGameOver(Configuration &c);



    /**
     * Shows the bonus message when the player arrives to the goal
     * @param c is the configuration of the game
     * @param seconds shows how many seconds the message will be shown
     * @param decs_second shows how many tenths of seconds the message will be shown
     */
    void showBonusIndications(Configuration &c, int seconds, int decs_second);



    /**
     * Shows the initial animation when the player is in the start point
     * @param c is the configuration of the game
     */
    State showsInitialAnimation(Configuration &c, SoundPlayer& r);



    /**
     * Shows the goal animation when the player is in the start point
     * @param c is the configuration of the game
     */
    State showsGoalAnimation(Configuration &c, SoundPlayer& r);



    /**
     * Updates the logic of the landscapes and vehicles and draws the current landscape fragment
     * with the vehicles on the screen.
     * @param c is the configuration of the game
     */
    void updateGameWorldTourStatus(Configuration &c, SoundPlayer& r, Vehicle::Action &action,
                                               Vehicle::Direction &direction, int& terrain);



    /**
     * Updates the logic of the landscapes and vehicles and draws the current landscape fragment
     * with the vehicles on the screen.
     * @param c is the configuration of the game
     */
    void updateGamePolePositionStatus(Configuration &c, SoundPlayer& r, Vehicle::Action &action,
                                      Vehicle::Direction &direction, int& terrain);



    /**
     * Updates the logic of the landscapes and vehicles and draws the current landscape fragment
     * with the vehicles on the screen.
     * @param c is the configuration of the game
     */
    void updateGameOutRunDerramageStatus(Configuration &c, SoundPlayer& r, Vehicle::Action &action,
                                         Vehicle::Direction &direction, int& terrain);




    /**
     * Updates the logic of the landscapes and vehicles and draws the current landscape fragment
     * with the vehicles on the screen.
     * @param c is the configuration of the game
     */
    void updateGameDrivingFuryStatus(Configuration &c, SoundPlayer& r, Vehicle::Action &action,
                                     Vehicle::Direction &direction, int& terrain);



     /**
     * Load the properties of the different available vehicles to play
     * @param path is the path of the xml configuration file of the vehicle
     * @param name is the brand of the vehicle
     * @param max_speed is the top speed reached by the vehicle in km/h / 100
     * @param angle is the turning angle of the vehicle
     * @param motorName is the brand's motor of the vehicle
     */
     void loadVehicleProperties(const string path, string& name, float& max_speed, float& angle, string& motorName);



public:



    /**
     * Constructor of the game
     * @param c is the configuration of the game
     */
    explicit Game(Configuration &c);



    /**
     * Load the configuration of the World Tour and Pole Position modes
     * @param c is the configuration of the game
     */
    State loadWorldTourPolePositionConf(Configuration& c);



    /**
     * Load the configuration of the Out Run, Driving Fury and Demarrage modes
     * @param c is the configuration of the game
     */
    State loadOutRunDrivingFuryDemarrageConf(Configuration& c);



    /**
     * Check the level of difficulty and regulates the parameters
     * @param c
     */
    void checkDifficulty(Configuration &c);



    /**
     * Returns true if the player is during the game.
     * Otherwise returns false.
     * @return
     */
    bool isInGame() const;



    /**
     * Set the type of game selected by the player in the game modes menu
     * @param typeGame is the game selected by the player
     */
    void setTypeOfGame(const int typeGame);



    /**
     * Returns the game mode selected by the player
     * @return
     */
    int typeGame() const;



    /**
     * Returns the total score got by the player
     * @return
     */
    unsigned long getScore() const;



    /**
     * Returns the total minutes inverted by the player
     * @return
     */
    float getMinutesTrip() const;



    /**
     * Returns the total seconds inverted by the player
     * @return
     */
    float getSecsTrip() const;



    /**
     * Returns the total hundredths of a second inverted by the player
     * @return
     */
    float getCents_SecondTrip() const;



    /**
     * Updates the logic of the game and refreshes the screen until you leave the game.
     * @param c is the configuration of the game
     * @return
     */
    State playWorldTourPolePosition(Configuration &c, SoundPlayer& r);



    /**
     * Updates the logic of the game and refreshes the screen until you leave the game.
     * @param c is the configuration of the game
     * @return
     */
    State playOutRunDrivingFuryDerramage(Configuration &c, SoundPlayer& r);



    /**
     * Load the configuration of the pause menu stored in its xml
     * configuration file
     * @param path contains the path of the xml configuration file
     * @param c is the configuration of the game
     */
    void loadPauseMenuConfiguration(const string path, Configuration& c);



    /**
     * Stops the game
     * @param c is the configuration of the game
     * @param a is the last action done by the player
     * @param d is the last direction done by the player
     * @return
     */
    State pause(Configuration &c, SoundPlayer& r, const Vehicle::Action &a, const Vehicle::Direction &d);



    /**
     * Load the configuration of the vehicle selection menu in its xml file
     * @param path contains the path of the xml configuration file
     * @param c is the configuration of the game
     */
    void loadVehicleSelectionMenuConfiguration(const string path, Configuration& c);



    /**
     * Load the configuration of the vehicle selection menu in its xml
     * configuration file
     * @param path contains the path of the xml configuration file
     * @param c is the configuration of the game
     */
    State selectionVehicleMenu(Configuration& c, SoundPlayer& r);


    void writeRecordFromLandScape(const string path, string namePlayer, int minutesLap, int secondsLap, int centsSecondLap);


    void readRecordFromLandScape(const string path, string& namePlayer, int& minutesLap, int& secondsLap, int& centsSecondLap);


    State classificationRace(Configuration& c, SoundPlayer& r);


    /**
     * Load the configuration of the circuit selection menu in its xml file
     * @param path contains the path of the xml configuration file
     * @param c is the configuration of the game
     */
    void loadCircuitMenuConfiguration(const string path, Configuration& c);



    State selectionCircuitMenu(Configuration& c, SoundPlayer& r);


    void showsDerramageDrivingFuryAnimation(Configuration& c, SoundPlayer& r);
};


#endif //GAME_H
