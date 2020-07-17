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
 * Enum with the possible states of the button
 */

enum button_states {
    // Normal state of the button
    BUTTON_IDLE = 0,
    // Button hovered with the mouse or with the row cursor keywords
    BUTTON_HOVER,
};


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
        Button(float x, float y, float width, float height, sf::Font &f, const string &text,
               Color idleColor, Color hoverColor, Color fontColor, int initialState, float screenScale);



        /**
         * Updates the state of the button
         * @param buttonState is the new state of the button to change
         */
        void setButtonState(button_states buttonState);



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



        void proccessDescription(xml_node<> *child);



        vector<string> getDescriptionButton();


        void setDescriptionButton(vector<string> description);


        string getTextButton();



        Color getIdleColorButton();



        Color getHoverColorButton();


        Color getFontColorButton();

};


#endif // BUTTON_H
