#pragma once

/*
 * Module Button interface file
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <cstring>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "SFML/Graphics.hpp"


using namespace std;
using namespace sf;
using namespace rapidxml;



/*
 * States of the button
 */
enum button_states {
    // Normal state of the button
    BUTTON_IDLE = 0,
    // Button hovered with the mouse or with the row cursor keywords
    BUTTON_HOVER,
};



/**
 * Represents the buttons of the game's GUI
 */
class Button {

    private:

        // Rectangle of the button
        RectangleShape shape;
        // Text content of the button
        Text textButton;

        // Colors of the button
        Color idleColorButton, hoverColorButton, fontColorButton;

        // Description of the button content
        vector<string> descriptionButton;

    public:


        /**
         * Default constructor
         */
        Button();



        /**
         * Constructor of the button
         * @param x is the coordinate in axis x of the button in the screen
         * @param y is the coordinate in axis y of the button in the screen
         * @param width is the width dimension of the button
         * @param height is the height dimension of the button
         * @param f is the font of the text
         * @param text is the content of the button
         * @param idleColor is the normal color of the button
         * @param hoverColor is the color of the button hovered
         * @param activeColor is the color of the button pressed
         * @param initialState is the state code of the button
         * @param screenScale is the factor of resolution of the screen
         */
        Button(float x, float y, float width, float height, Font &f, const string &text, Color idleColor, Color hoverColor,
               Color fontColor, int initialState, float screenScale);



        /**
         * Updates the state of the button
         * @param buttonState is the new state of the button to change
         */
        void setButtonState(button_states stateButton);



        /**
         * Draws the button
         * @param app is the console window of the game
         */
        void render(RenderTexture *app);



        /**
         * Initialize the text content of the button
         * @param newString is the content text of the button
         */
        void setTextButton(const string &newString);



        /**
         * Process the description associated to the button presented
         * in the xml configuration file
         * @param child is the xml node that points to the description of the button
         */
        void proccessDescription(xml_node<> *child);



        /**
         * Assigns an optional description of the purpose of the button
         * @param description contains the description of the button
         */
        void setDescriptionButton(vector<string> description);



        /**
         * Returns the optional description of what the button is for
         * @return
         */
        vector<string> getDescriptionButton();



        /**
         * Returns the text of the button
         * @return
         */
        string getTextButton();



        /**
         * Returns the RGB color of the button when it's not hovered
         * @return
         */
        Color getIdleColorButton();



        /**
         * Returns the RGB color of the button when it's hovered
         * @return
         */
        Color getHoverColorButton();



        /**
         * Returns the font of the button
         * @return
         */
        Color getFontColorButton();

};


#endif // BUTTON_H
