
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace sf;
using namespace rapidxml;



/*
 * Environment data type
 */
struct Environment{

    // Variables to control the speed indicator of the player's vehicle
    Texture textureSpeedPanel;
    Sprite spriteSpeedPanel;
    Text textSpeedIndicator;
    Font fontSpeedIndicator;

    // Variables to control the elapsed indicator of the player
    Texture textureElapsedPanel;
    Sprite spriteElapsedPanel;
    Text textElapsedIndicator;
    Font fontElapsedIndicator;

    // Variables to control the time indicator of the player
    Text textTimePanel, textTimeIndicator;
    Font fontTimePanel, fontTimeIndicator;

    // Variables to control the destiny indicator of the player
    Text textDestinyPanel, textDestinyIndicator;
    Font fontDestinyPanel, fontDestinyIndicator;

    // Inform to the user the distance to the next checkpoint or goal
    string message;


    /**
     * Constructor of the data type environment
     * @param
     */
    Environment ();


    void configure(string pathSpeedIndicator, string fontPathSpeedPanel, int posXSpeedPanel, int posYSpeedPanel,
                   int sizeTextSpeedPanel, int posXTextSpeedPanel, int posYTextSpeedPanel,
                   string pathElapsedIndicator, string fontPathElapsedPanel, int posXElapsedPanel, int posYElapsedPanel,
                   int sizeTextElapsedPanel, int posXTextElapsedPanel, int posYTextElapsedPanel,
                   string fontPathTimeText, int sizeTimeText, int posXTimeText, int posYTimeText,
                   string fontPathTimeIndicator, int sizeTimeIndicator, int posXTimeIndicator, int posYTimeIndicator,
                   string fontPathDestinyText, int sizeDestinyText, int posXDestinyText, int posYDestinyText,
                   string fontPathDestinyIndicator, int sizeDestinyIndicator, int posXDestinyIndicator, int posYDestinyIndicator,
                   Color colorSpeedPanel, Color colorElapsedPanel, Color colorTimeText, Color colorTimeIndicator,
                   Color colorDestinyText, Color colorDestinyIndicator);

};

#endif // ENVIRONMENT_H
