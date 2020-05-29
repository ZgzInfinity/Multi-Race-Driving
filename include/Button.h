

#ifndef BUTTON_H
#define BUTTON_H


#include <iostream>
#include <cstring>
#include "SFML/Graphics.hpp"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "Word.h"

using namespace std;
using namespace sf;
using namespace rapidxml;


enum button_states {
    BUTTON_IDLE = 0,
    BUTTON_PRESSED,
    BUTTON_HOVER,
};

class Button {
    private:
        RectangleShape shape;
        Font fontButton;
        Text textButton;

        Color idleColorButton;
        Color hoverColorButton;

        bool hover, pressed;
        int buttonState;

        vector<string> descriptionButton;

    public:

        const bool isPressed() const;

        const bool isHovered() const;

        Button();

        Button (float x, float y, float width, float height, Font& f, string text,
                Color idleColor, Color hoverColor, int initialState);

        void getPressed (Button& otherButton);

        void setButtonState(button_states buttonState);

        void render (RenderWindow* app);

        void setTextButton(string newString);

        string getTextButton();

        void proccessDescription(xml_node<> *child);

        vector<string> getDescriptionButton();

};


#endif // BUTTON_H
