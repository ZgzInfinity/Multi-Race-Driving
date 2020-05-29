
#include "../include/Button.h"

Button::Button(){}

Button::Button (float x, float y, float width, float height, Font& f,
                string text, Color idleColor, Color hoverColor, int initialState)
{
    shape.setPosition(Vector2f(x, y));
    shape.setSize(Vector2f(width, height));
    shape.setOutlineColor(Color::Black);
    shape.setOutlineThickness(3);
    textButton.setString(text);
    textButton.setFont(f);
    textButton.setFillColor(Color::Blue);
    textButton.setCharacterSize(12);
    textButton.setPosition(
        shape.getPosition().x + (shape.getGlobalBounds().width / 2.f)  - textButton.getGlobalBounds().width / 2.f,
        shape.getPosition().y + (shape.getGlobalBounds().height / 2.f)  - textButton.getGlobalBounds().height / 2.f - 5
    );

    // Store the possible colors of the button
    idleColorButton = idleColor;
    hoverColorButton = hoverColor;

    // Check the initial state of the button
    switch (initialState){
        case 0:
            buttonState = BUTTON_IDLE;
            shape.setFillColor(idleColorButton);
        break;
        case 1:
            buttonState = BUTTON_HOVER;
            shape.setFillColor(hoverColorButton);
        break;
    }
}



void Button::setButtonState(button_states stateButton){
    switch(stateButton){
        case BUTTON_IDLE:
            shape.setFillColor(idleColorButton);
        break;
        case BUTTON_HOVER:
            shape.setFillColor(hoverColorButton);
    }
}


void Button::render (RenderWindow* app){
    app->draw(shape);
    app->draw(textButton);
}


void Button::setTextButton(string newString){
    textButton.setString(newString);
    textButton.setPosition(
        shape.getPosition().x + (shape.getGlobalBounds().width / 2.f)  - textButton.getGlobalBounds().width / 2.f,
        shape.getPosition().y + (shape.getGlobalBounds().height / 2.f)  - textButton.getGlobalBounds().height / 2.f - 5
    );
}


string Button::getTextButton(){
    return textButton.getString();
}


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


vector<string> Button::getDescriptionButton(){
    return descriptionButton;
}
