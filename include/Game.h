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



/*
 * ----------------------------------------------
 * Multi Race Driving: A general and customized
 * platform for 2.5D racing games
 * Author: ZgzInfinity
 * Date: 28-09-20
 * ----------------------------------------------
 */


#pragma once

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <random>
#include "Randomizer.h"
#include "Menu.h"
#include "LandScape.h"
#include "Motorbike.h"
#include "Devastator.h"
#include "FormulaOne.h"
#include "Truck.h"
#include "Minivan.h"
#include "Police.h"
#include "TrafficCar.h"
#include "RivalCar.h"
#include "MultiplayerCar.h"
#include "LindaDriver.h"
#include "MultiplayerData.h"
#include <SFML/Graphics.hpp>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include "Globals.h"



using namespace sf;
using namespace std;
using namespace rapidxml;
using namespace std::chrono_literals;

const float BONIFICATION = 1000000.0f;
const float DISTANCE_TRESHOLD = 5.0f;
const float DEL_DISTANCE = 50.0f;
const float SPEED_FACTOR = 70.0f;
const float DENSITY_SPACE = 3.0f;



/**
 * Class that contains all the logic of the simulator
 */
class Game {

    // Determine the game selected by the player
    int typeOfGame;

    // Determine the game selected by the player in multi player mode
    int typeOfGameMultiplayer;

    // Vector of landscapes for World tour and pole position modes
    vector<LandScape> tourLandScapes;

    // Matrix of landscapes for Out Run Driving fury and Demarrage modes
    vector<vector<LandScape>> maps;

    // Auxiliary matrix to store the landscapes
    vector<vector<LandScape>> referencedMaps;

    // Identifier of the current landscape where is playing the player
    pair<int, int> mapId;

    // Current landscape
    LandScape *currentMap;

    // Goal landscape that represents the goal point
    LandScape goalMap;

    // Start landscape that represents the starting point
    LandScape *startMap;
    LandScape middleMap;

    // Position of the flagger
    int goalFlagger, goalEnd;

    // Possible vehicles of the player
    Motorbike player;
    Devastator player2;
    Minivan player3;
    Truck player4;
    FormulaOne player5;
    Police player6;

    // Semaphores to control mutual exclusion
    mutex mtx, mtx2, mtx3, mtx4;

    // Vector that allocates the traffic cars
    vector<TrafficCar> cars;

    // Vector that allocates the rival cars
    vector<RivalCar> rivals;

    // Vector that allocates the multi player vehicles
    vector<MultiplayerCar> multiplayerCars;

    // Vector that allocates the players of team ordered by position of arrival
    vector<MultiplayerData> multiplayerCarsRanking;

    // Objective car in Driving Fury and Demarrage game modes
    RivalCar goalCar;

    // Last position in axis y registered
    float lastY;

    // Control if the player has crashed against a traffic car
    bool vehicleCrash;

    // Control if the goal car has to be drawn or not
    bool drawingGoalCar;

    // Control if the first race has been celebrated or not
    bool firstRace;

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

    // Count the time to display the player fallen
    Clock playerFallenClock;

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

    // Control if the texts of the animations have to be displayed
    bool blink;

    // Control if the player has arrived to the goal landscape
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

    // Internal threads of the game
    thread timer0, timer1, timer2, controllerPosition, capturerPlayers, capturerGroups,
    guestPulses, controlPulse, vehicleOwner, vehicleGuest, vehicleRestPlayers, controlRaceOwner,
    controlRaceGuest, controlRacerGoal, controlSenderPositions, controlReceiverPositions;

    // Offset until the lap indicator in Pole Position has to be moved
    int displayLapFactor;

    // Number of competitors of the race
    int numberRacers;

    // Color chosen of the vehicle
    int colorCarSelected;

    // Vector that allocates the vehicles in the axis y
    vector<float> rankingVehicles;

    // Control if the health of the goal car has to be displayed or not
    bool displayGoalCarIndicator;

    // Numeric value of the goal car
    int lifeGoalCar;

    // Number of hits that have to be done to the goal car
    int numCrashesGoalCar;

    // Percent of life to lose per crash
    int lifeLostPerCrash;

    // Control if the player and the goal car have been updated
    bool updatedGoalCar, updatedPlayerCar;

    // Initial distance where the goal car starts
    int maxDistance;

    // Number of stages in Driving Fury and Demarrage game modes
    int totalStages;

    // Current stage where the player is currently playing
    int currentStage;

    //  Stage where the players has to appear
    int goalCarStage;

    // Counter that represents the current landscape in Driving Fury and Demarrage game modes
    int currentLandScape;

    // Distance to the goal car
    int distanceGoalCar;

    // Control if the player is near or not to the goal car
    bool goalNearCar;

    // Distance that the player has to do to make demarrage to the goal car
    int distanceAdvanced;

    // Control the method chosen by the player to play multi player mode
    int modeMultiplayer;

    // Name of the player in the multi player mode
    string nickNameMultiplayer;

    // Name of the group in the multi player mode
    string nickNameGroupMultiplayer;

    // Control if the player has chosen joining multi player mode or not
    bool randomMultiplayerJoined;

    // Number of members of the group
    int numberPlayersGroup;

    // Information of all the members of the group
    vector<MultiplayerData> groupDataPlayers;

    // Identifier of the player in the multi player mode
    int codePlayerInGroup;

    // Control if the player is in multi player mode or not
    bool onMultiplayer;

    // Type of vehicle chosen by the rivals in multi player mode
    int kindVehicle;

    // Chose the kind of submode to play in World Tour or Pole Position depending on the rival car types
    int rivalTypeMode;



    /**
     * Shows the HUD animation in the World Tour and Pole Position modes
     * @param c is the module configuration of the game
     * @param r is the sound player module of the game
     */
    State drawHudAnimationWorldTourPolePosition(Configuration& c, SoundPlayer& r);



    /**
     * Shows the HUD animation in the Out Run, Driving Fury and Demarrage game modes
     * @param c is the module configuration of the game
     * @param r is the sound player module of the game
     */
    State drawHudAnimationOutRunDrivingFuryDemarrage(Configuration& c, SoundPlayer& r);



    /**
     * Store the rival vehicles that the player has to beat
     * @param c is the module configuration of the game
     */
    void storingRivalCars(Configuration& c);



    /**
     * Load the landscapes of the World Tour and Pole Position game modes
     * @param c is the module configuration of the game
     * @param path is the route of the folder where the landscapes are stored
     * @param i is the identifier of the landscape to be processed
     * @param timeLandscape is the time to complete the landscape
     * @param typeOfGame is the type of game selected by the player
     * @param tourLandScapesMutex is a vector that controls when a landscape processed has to be stored
     */
    void loadWorldTourPolePositionLandScape(Configuration& c, const string path, const int i, int timeLandscape, const int typeOfGame,
                                            mutex tourLandScapesMutex[]);




    /**
     * Load the landscapes of the World Tour and Pole Position game modes
     * @param c is the module configuration of the game
     * @param path is the route of the folder where the landscapes are stored
     * @param i is the identifier of the landscape to be processed
     * @param timeLandscape is the time to complete the landscape
     * @param typeOfGame is the type of game selected by the player
     * @param tourLandScapesMutex is a vector that controls when a landscape processed has to be stored
     * @param vm is the matrix where all the landscapes are stored
     */
    void loadOutRunDrivingFuryDerramageLandScape(Configuration& c, const string path, const int i, int timeLandscape,
                                                 const int typeOfGame, mutex tourLandScapesMutex[], vector<LandScape>& vm);



    /**
     * Updates the time elapsed in the game
     */
    void updateTimeElapsed();



    /**
     * Updates the time of the game to complete the landscape
     */
    void updateTimeLandScape();



    /**
     * Updates the score indicator in the Out Run game mode
     */
    void updateScore();



    /**
     * Find the current position of the player in the race
     * @param posYPplayer is the position of the player in the axis y
     */
    int findPlayerPositionRanking(const float posYPlayer);



    /**
     * Load the Hud interface of the World Tour and Pole Position game modes
     */
    void loadHudGameWorldTourPolePosition();



    /**
     * Load the Hud interface of the Out Run, Driving Fury and Demarrage game modes
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
     * Draw the HUD interface of the Out Run, Driving Fury and Demarrage game modes
     * @param c is the configuration of the game
     */
    void showHudInterfaceOutRunDrivingFuryDerramage(Configuration &c);



    /**
     * Draw the HUD interface of the World Tour and Pole Position game modes
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
     * @param r is the sound reproducer of the game
     */
    State showsInitialAnimation(Configuration &c, SoundPlayer& r);



    /**
     * Shows the goal animation when the player is in the start point
     * @param c is the configuration of the game
     * @param r is the sound reproducer of the game
     */
    State showsGoalAnimation(Configuration &c, SoundPlayer& r);



    /**
     * Updates the logic of the landscapes and vehicles and draws the current landscape fragment
     * with the vehicles on the screen in World Tour mode for one player
     * @param c is the configuration of the game
     * @param r is the sound reproducer of the game
     * @param a is the action of the player that is going to be processed
     * @param d is the direction of the player that is going to be processed
     * @param terrain is the kind of terrain of the landscape
     */
    void updateGameWorldTourStatus(Configuration &c, SoundPlayer& r, Vehicle::Action &action,
                                               Vehicle::Direction &direction, int& terrain);



    /**
     * Updates the logic of the landscapes and vehicles and draws the current landscape fragment
     * with the vehicles on the screen in World Tour for multi player mode
     * @param c is the configuration of the game
     * @param r is the sound reproducer of the game
     * @param a is the action of the player that is going to be processed
     * @param d is the direction of the player that is going to be processed
     * @param terrain is the kind of terrain of the landscape
     */
    void updateGameWorldTourStatusMultiplayer(Configuration &c, SoundPlayer& r, Vehicle::Action &action,
                                              Vehicle::Direction &direction, int& terrain, const int startPosition);



    /**
     * Updates the logic of the landscapes and vehicles and draws the current landscape fragment
     * with the vehicles on the screen in Pole Position mode for one player
     * @param c is the configuration of the game
     * @param r is the sound reproducer of the game
     * @param a is the action of the player that is going to be processed
     * @param d is the direction of the player that is going to be processed
     * @param terrain is the kind of terrain of the landscape
     */
    void updateGamePolePositionStatus(Configuration &c, SoundPlayer& r, Vehicle::Action &action,
                                      Vehicle::Direction &direction, int& terrain);



    /**
     * Updates the logic of the landscapes and vehicles and draws the current landscape fragment
     * with the vehicles on the screen in Pole Position mode for one player
     * @param c is the configuration of the game
     * @param r is the sound reproducer of the game
     * @param a is the action of the player that is going to be processed
     * @param d is the direction of the player that is going to be processed
     * @param terrain is the kind of terrain of the landscape
     */
    void updateGamePolePositionStatusMultiplayer(Configuration &c, SoundPlayer& r, Vehicle::Action &action,
                                                 Vehicle::Direction &direction, int& terrain, const int startPosition);



    /**
     * Updates the logic of the landscapes and vehicles and draws the current landscape fragment
     * with the vehicles on the screen in Out Run and Demarrage mode for one player
     * @param c is the configuration of the game
     * @param r is the sound reproducer of the game
     * @param a is the action of the player that is going to be processed
     * @param d is the direction of the player that is going to be processed
     * @param terrain is the kind of terrain of the landscape
     */
    void updateGameOutRunDerramageStatus(Configuration &c, SoundPlayer& r, Vehicle::Action &action,
                                         Vehicle::Direction &direction, int& terrain);



    /**
     * Updates the logic of the landscapes and vehicles and draws the current landscape fragment
     * with the vehicles on the screen in Driving Fury mode for one player
     * @param c is the configuration of the game
     * @param r is the sound reproducer of the game
     * @param a is the action of the player that is going to be processed
     * @param d is the direction of the player that is going to be processed
     * @param terrain is the kind of terrain of the landscape
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
     * @param c is the configuration of the game
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
     * @param r is the sound player module of the game
     * @return
     */
    State playWorldTourPolePosition(Configuration &c, SoundPlayer& r);



    /**
     * Control if the multi player race for the owner has finished due to the player has left it or the
     * guests members of the group have left him
     * @param canceledRace controls if all the guest members have left the group
     * @param playerFallen stores the name of the guest player that has left the group
     */
    void monitorizeRaceOwner(bool& canceledRace, string& playerFallen);



    /**
     * Control if the multi player race for the guest has finished due to the owner has cancel it. Also
     * controls if any of the rest of the guest players have left the race
     * @param canceledRace controls if the owner of the group has canceled the race
     * @param playerFallen stores the name of the guest player that has left the group
     */
    void monitorizeRaceGuest(bool& canceledRace, string& playerFallen);



    /**
     * Sends the position of a guest player player of the group to all the guest of the multi player group
     * @param canceledRace controls if all the owner of the group has canceled the race
     * @param nRivals is the number of rivals that started the race with the owner player
     * @param startPosition is the initial position of the owner when the race started
     */
    void senderMultiplayerPositionOwner(bool& canceledRace, const int nRivals, const int startPosition);



    /**
     * Sends the position of a guest player player of the group to the rest of the members of the multi player group
     * @param canceledRace controls if all the guest members have left the group
     * @param nRivals is the number of rivals that started the race with the owner player
     * @param startPosition is the initial position of the owner when the race started
     */
    void senderMultiplayerPositionGuest(bool& canceledRace, const int nRivals, const int startPosition);



    /**
     * Receives the position of a guest player player of the group to all the guest of the multi player group
     * @param canceledRace controls if all the owner of the group has canceled the race
     */
    void receiverMultiplayerPositionOwner(bool& canceledRace);



    /**
     * Receives the position of a guest player player of the group to the rest of the members of the multi player group
     * @param canceledRace controls if all the guest members have left the group
     */
    void receiverMultiplayerPositionGuest(bool& canceledRace);



    /**
     * Updates the logic of the World Tour and Pole Position game modes and
     * refreshes the screen until you leave the game.
     * @param c is the configuration of the game
     * @return
     */
    State playWorldTourPolePositionMultiplayer(Configuration &c, SoundPlayer& r);



    /**
     * Updates the logic of the Out Run, Driving Fury and Demarrage game modes and
     * refreshes the screen until you leave the game.
     * @param c is the configuration of the game
     * @return
     */
    State playOutRunDrivingFuryDemarrage(Configuration &c, SoundPlayer& r);



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
     * Controls all the guest of the multi player group have left it and the car selection process to be canceled
     * @param cancelledGroup controls if all the guest members have left the group
     * @param vehiclesRead is a vector that checks which players of the group have been already selected a vehicle to run
     */
    void controlVehicleOwner(bool& cancelledGroup, vector<int>& vehiclesRead);



    /**
     * Controls if the owner of the group has canceled the vehicle selection or not
     * @param cancelledVehicle controls  if the owner has canceled the selection vehicle
     * @param vehiclesRead is a vector that checks which players of the group have been already selected a vehicle to run
     */
    void controlVehicleGuest(bool& cancelledVehicle, vector<int>& vehiclesRead);



    /**
     * Controls the selection vehicle of a player and besides receives the selected
     * cars by the rest of the players of the multi player group
     * @param numPlayers is the number of players that have selected a car to run
     * @param finishedRegister controls if all the members of the group have already selected a car to run
     * @param vehiclesRead is a vector that checks which guest players have been already selected a vehicle to run
     */
    void storeRivalPlayers1(int& numPlayers, bool& finishedRegister, bool& cancelledGroup, vector<int>& vehiclesRead);



    /**
     * Store the player when arrives to the goal and waits until the rest of the players have arrived to goal too
     * @param numPlayers is the number of players that have arrived to the goal
     * @param finishedRegister controls if all the players of the group have arrived to the goal
     * @param cancelledGroup controls if all the guest members have left the group
     * @param cancelledOwner controls if the owner has canceled the race
     * @param vehiclesRead is a vector that controls which players have arrived to the goal
     * @param written controls if the player that has arrived has been written in the classification
     */
    void storeRivalPlayers2(int& numPlayers, bool& finishedRegister, bool& cancelledGroup, bool& cancelledOwner, vector<int>& vehiclesRead,
                            bool& written);



    /**
     * Load the configuration of the vehicle selection menu in its xml
     * configuration file
     * @param path contains the path of the xml configuration file
     * @param c is the configuration of the game
     */
    State selectionVehicleMenu(Configuration& c, SoundPlayer& r);




    /**
     * Load the configuration of the rival type selection menu in its xml file
     * @param path contains the path of the xml configuration file
     * @param c is the configuration of the game
     */
    void loadRivalTypeSelectionMenuConfiguration(const string path, Configuration& c);



    /**
     * Load the configuration of the rival type selection menu in its xml
     * configuration file
     * @param path contains the path of the xml configuration file
     * @param c is the configuration of the game
     */
    State selectionRivalTypeMenu(Configuration& c, SoundPlayer& r);



    /**
     * Write a new record of the game in the correspond file depending on the difficulty level
     * @param path is the route of the file where the record has to be written
     * @param namePlayer is the name of the player that has done a new record
     * @param minutesLap are the minutes of the record time
     * @param secondsLap are the seconds of the record time
     * @param centsSecondLap are the hundredths of seconds of the record time
     */
    void writeRecordFromLandScape(const string path, string namePlayer, int minutesLap, int secondsLap, int centsSecondLap);



    /**
     * Read the current record of the game in the correspond file depending on the difficulty level
     * @param path is the route of the file where the record has to be written
     * @param namePlayer is the name of the player that has done a new record
     * @param minutesLap are the minutes of the record time
     * @param secondsLap are the seconds of the record time
     * @param centsSecondLap are the hundredths of seconds of the record time
     */
    void readRecordFromLandScape(const string path, string& namePlayer, int& minutesLap, int& secondsLap, int& centsSecondLap);



    /**
     * Shows to the player the classification race animation after the finishing of a race in
     * World Tour and Pole Position game modes for one player
     * @param c is the module configuration of the game
     * @param r is the sound player module of the game
     */
    State classificationRace(Configuration& c, SoundPlayer& r);



    /**
     * Load the configuration of the circuit selection menu in its xml file
     * @param path contains the path of the xml configuration file
     * @param c is the configuration of the game
     */
    void loadCircuitMenuConfiguration(const string path, Configuration& c);



    /**
     * Controls the pulses received by the guest players to the owner to check if they are alived
     * @param itemSelected controls if the game mode or the circuit have been selected
     * @param cancelledGroup controls if all the guest members of the group have left it
     * @param escape controls if the owner has canceled the game mode or circuit selection
     */
    void controlGuestPulses(bool& itemSelected, bool& cancelledGroup, bool& escape);



    /**
     * Controls the pulses sended by a guest player to the owner to alarm that is still alive
     * @param itemSelected controls if the game mode or the circuit have been selected by the owner
     * @param finishedGroup controls if the group has been canceled by the owner
     * @param itemCanceled controls if the owner has canceled the game mode or circuit selection
     */
    void sendGuestPulses(bool& itemSelected, bool& finishedGroup, bool &itemCanceled);



    /**
     * Displays the circuit selection menu and lets to the player select in which circuit run
     * and also how many laps to do and with how many racers compete if it is not the multi player mode
     * @param c is the module configuration of the game
     * @param r is the sound player module of the game
     */
    State selectionCircuitMenu(Configuration& c, SoundPlayer& r);



    /**
     * Displays the goal animation when a level of the Driving Fury or Demarrage game modes
     * have been completed
     * @param c is the module configuration of the game
     * @param r is the sound player module of the game
     */
    void showsDerramageDrivingFuryAnimation(Configuration& c, SoundPlayer& r);



    /**
     * Sets how a player is going to play in multi player mode. Like a owner of group or
     * like a guest player of a group
     * @param multiPlayerMode represents the mode to play in multi player mode
     */
    void setMultiplayerMode(const int multiPlayerMode);



    /**
     * Load the configuration of the multi player name player menu
     * @param path is the route of the xml file that contains its configuration
     * @param c is the module configuration of the game
     */
    void loadMultiplayerNameConfiguration(const string path, Configuration& c);



    /**
     * Displays the menu where the players have to introduce their aliases in multi player mode
     * @param c is the module configuration of the game
     * @param r is the sound player module of the game
     */
    State introduceNameMultiplayer(Configuration& c, SoundPlayer& r);



    /**
     * Load the configuration of the multi player group player menu
     * @param path is the route of the xml file that contains its configuration
     * @param c is the module configuration of the game
     */
    void loadMultiplayerGroupConfiguration(const string path, Configuration& c);



    /**
     * Displays the menu where the players have to introduce the alias of the group to be created
     * or to be joined depending of how they decided to play multi player mode
     * @param c is the module configuration of the game
     * @param r is the sound player module of the game
     */
    State introduceGroupMultiplayer(Configuration& c, SoundPlayer& r);



    /**
     * Load the configuration menu where the players that are going to be joined to a group
     * have to select if the want to be joined to a concrete group or randomly
     * @param path is the route of the xml file that contains its configuration
     * @param c is the module configuration of the game
     */
    void loadMultiplayerJoinGroupMenuConfiguration(const string path, Configuration& c);



    /**
     * Displays the menu where the players select how to join to a multi player group
     * @param c is the module configuration of the game
     * @param r is the sound player module of the game
     */
    State selectJoiningMode(Configuration& c, SoundPlayer& r);



    /**
     * Controls the petitions of player to be joined to the group created by the owner player
     * @param fullGroup controls if the group is full of members or if the owner has closed it
     * pressing Enter
     */
    void capturerOfPlayers(bool& fullGroup);



    /**
     * Controls the process that consists in joining a player to a multi player group
     * @param success controls if the group where the player has been joined has been fulled or closed correctly by the owner
     * @param fail controls if the petition of join of group has resulted in a fail attempt
     * @param oartialSuccess controls if the petition has been accepted by the owner of the group
     */
    void capturerOfGroups(bool& success, bool& fail, bool& partialSuccess);



    /**
     * Displays the menu with all the members that form a multi player group
     * @param c is the module configuration of the game
     * @param r is the sound player module of the game
     */
    State creationOfGroups(Configuration& c, SoundPlayer& r);



    /**
     * Load the configuration of the menu that shows all the members that compose a multi player group
     * @param path is the route of the xml file that contains its configuration
     * @param c is the module configuration of the game
     */
    void loadMultiplayerMemberGroupMenuConfiguration(const string path, Configuration& c);



    /**
     * Load the configuration of the game modes multi player menu stored in its xml configuration file
     * @param path contains the path of the xml configuration file
     * @param c is the configuration of the game
     */
    void loadGameModesMultiplayerMenuConfiguration(const string path, Configuration& c);



    /**
     * Displays the selection game mode multi player menu to the owner player of a group
     * @param c is the module configuration of the game
     * @param r is the sound player module of the game
     */
    State selectionModeMultiplayer(Configuration& c, SoundPlayer& r);



    /**
     * Displays the selection circuit multi player menu to the owner player of a group
     * @param c is the module configuration of the game
     * @param r is the sound player module of the game
     */
    State selectionCircuitMultiplayer(Configuration& c, SoundPlayer& r);



    /**
     * Parses the test connection result after making ping command to the remote server
     * @param testFinished controls if the test connection has finished successfully
     * @param mininumLatency is the minimum latency obtained in the ping command
     * @param mediumLatency is the average latency obtained in the ping command
     * @param maxLantency is the maximum latency obtained in the ping command
     */
    void testConnection(bool& testFinished, string& mininumLatency, string& mediumLatency, string& maxLantency);



    /**
     * Load the configuration of the multi player test configuration menu stored in its xml configuration file
     * @param path contains the path of the xml configuration file
     * @param c is the configuration of the game
     */
    void loadMultiplayerMenuTestingNetworkConfiguration(const string path, Configuration& c);



    /**
     * Makes a test speed connection to the server to check the quality of the network
     * @param c is the module configuration of the game
     * @param r is the sound player module of the game
     */
    State makeConnectionServerTest(Configuration& c, SoundPlayer& r);



    /**
     * Store all the multi player cars that are going to compete with the player
     */
    void storingMultiplayerCars();



    /**
     * Get how a player has decided to play the multi player mode
     */
    bool getOnMultiplayerMode();



    /**
     * Set that the player has started to play in multi player mode
     */
    void setMultiplayer();

};


#endif //GAME_H
