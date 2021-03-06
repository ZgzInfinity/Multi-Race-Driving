/*
 * Copyright (c) 2020 Andres Gavin
 * Copyright (c) 2020 Ruben Rodriguez
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



/*
 * Module Button implementation file
 */

#include "../include/Button.h"


/**
 * Default constructor
 */
Button::Button(){}



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
Button::Button(float x, float y, float width, float height, Font &f,
               const string &text, Color idleColor, Color hoverColor, Color fontColor, int initialState,
               float screenScale)
{
    // Establish the position of the button in the screen
    shape.setPosition(Vector2f(x, y));

    // Establish the dimensions of the button in the screen
    shape.setSize(Vector2f(width, height));

    // Assign the border color of the button
    shape.setOutlineColor(Color::Black);

    // Fix the size border depending of the resolution
    shape.setOutlineThickness(3.0f * screenScale);

    // Assign the font and text of the button
    textButton.setString(text);
    textButton.setFont(f);

    // Assign the color of the font and the size of the text
    textButton.setFillColor(fontColor);
    textButton.setCharacterSize(static_cast<unsigned int>(int(18.0f * screenScale)));

    // Color of the font
    fontColorButton = fontColor;

    // Establish the text in the center of the button
    textButton.setPosition(
        shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - textButton.getGlobalBounds().width / 2.f,
        shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - textButton.getGlobalBounds().height / 2.f - 5
    );

    // Store the possible colors of the button
    idleColorButton = idleColor;
    hoverColorButton = hoverColor;

    // Check the initial state of the button
    switch (initialState) {
        case 0:
            shape.setFillColor(idleColorButton);
            break;
        case 1:
            shape.setFillColor(hoverColorButton);
            break;
        default:
            break;
    }
}



/**
 * Updates the state of the button
 * @param buttonState is the new state of the button to change
 */
void Button::setButtonState(button_states stateButton) {
    // Modification of the button's state
    switch (stateButton) {
        case BUTTON_IDLE:
            shape.setFillColor(idleColorButton);
            break;
        case BUTTON_HOVER:
            shape.setFillColor(hoverColorButton);
    }
}



/**
 * Draws the button
 * @param app is the console window of the game
 */
void Button::render(RenderTexture *app) {
    app->draw(shape);
    app->draw(textButton);
}



/**
 * Initialize the text content of the button
 * @param newString is the content text of the button
 */
void Button::setTextButton(const string &newString) {
    // Update the text content of the button in the center of it
    textButton.setString(newString);
    textButton.setPosition(
        shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - textButton.getGlobalBounds().width / 2.f,
        shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - textButton.getGlobalBounds().height / 2.f - 5
    );
}



/**
 * Process the description associated to the button presented
 * in the xml configuration file
 * @param child is the xml node that points to the description of the button
 */
void Button::proccessDescription(xml_node<> *child){
    string descriptionPhrase, wordRead;
    int init, last;
     // Loop in order to iterate throughout the colors of the grass
    for (xml_node<> *phrase = child->first_node(); phrase; phrase = phrase->next_sibling()){
        descriptionPhrase = (string)phrase->value();
        // Iterate character by character the phrase read
        init = 0, last = 0;
        while(last = descriptionPhrase.find(" ", init), last >= 0 ){
            // Get the actual word which has to be processed
            wordRead = descriptionPhrase.substr(init, last - init);
            descriptionButton.push_back(wordRead);
            init = last + 1;
        }
        // Last word of the phrase
        wordRead = descriptionPhrase.substr(init);
        descriptionButton.push_back(wordRead);
    }
}



/**
 * Assigns an optional description of the purpose of the button
 * @param description contains the description of the button
 */
void Button::setDescriptionButton(vector<string> description){
    descriptionButton = description;
}



/**
 * Returns the optional description of what the button is for
 * @return
 */
vector<string> Button::getDescriptionButton(){
    return descriptionButton;
}



/**
 * Returns the text of the button
 * @return
 */
string Button::getTextButton(){
    return textButton.getString();
}



/**
 * Returns the RGB color of the button when it's not hovered
 * @return
 */
Color Button::getIdleColorButton(){
    return idleColorButton;
}



/**
 * Returns the RGB color of the button when it's hovered
 * @return
 */
Color Button::getHoverColorButton(){
    return hoverColorButton;
}



/**
 * Returns the font of the button
 * @return
 */
Color Button::getFontColorButton(){
    return fontColorButton;
}


