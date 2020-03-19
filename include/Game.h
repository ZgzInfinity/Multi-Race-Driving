
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Animation.h"
#include "Menu.h"
#include "../include/Motorbike.h"
#include "../include/Ferrari.h"
#include "../include/Minivan.h"
#include "../include/Truck.h"
#include "../include/LandScape.h"
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

const int INITIAL_SECS = 100;


class Game {

    private:

        RenderWindow* application;

        Animation* animationGame;

        Menu* menuGame;

    public:

        Game(RenderWindow* app);

        void drawQuad(Color c, int x1,int y1,int w1,int x2,int y2,int w2);

        void playingGame();

};

#endif // GAME_H
