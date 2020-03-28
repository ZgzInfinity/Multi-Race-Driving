
#include <vector>
#include <iostream>
#include "../include/Step.h"
#include "../include/Motorbike.h"
#include "../include/Ferrari.h"
#include "../include/Minivan.h"
#include "../include/Truck.h"
#include "../include/IntervalCurve.h"
#include "../include/LandScape.h"
#include "../include/Animation.h"
#include "../include/Menu.h"
#include "../include/Button.h"
#include "../include/Game.h"
#include <SFML/Graphics.hpp>

const int NUMBER_FPS = 60;


using namespace std;


int main(int argc, char* argv[]){

    // Creation of the screen game
    RenderWindow application(VideoMode(WIDTH, HEIGHT), "Super Hang On!");
    // Control the fotograms per second, 60 FPS more less
    application.setFramerateLimit(NUMBER_FPS);

    Game g = Game(&application);

    g.playingGame();

    return 0;
}
