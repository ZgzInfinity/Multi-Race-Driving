
#include "../include/Button.h"


Button::Button (float x, float y, float width, float height, Font f,
                string text, Color idleColor, Color hoverColor, Color activeColor)
{
    shape.setPosition(Vector2f(x, y));
    shape.setSize(Vector2f(width, height));
    fontButton = f;
    textButton.setFont(fontButton);
    textButton.setString(text);
    textButton.setFillColor(Color::Blue);
    textButton.setCharacterSize(12);
    textButton.setPosition(
        shape.getPosition().x + (shape.getGlobalBounds().width / 2.f)  - textButton.getGlobalBounds().width / 2.f,
        shape.getPosition().y + (shape.getGlobalBounds().height / 2.f)  - textButton.getGlobalBounds().height / 2.f
    );

    idleColorButton = idleColor;
    hoverColorButton = hoverColor;
    activeColorButton = activeColor;

    shape.setFillColor(idleColor);

}

const bool Button::isPressed() const {
    if (buttonState == BUTTON_PRESSED){
        return true;
    }
    else {
        return false;
    }
}


void Button::getPressed (Vector2i mousePosition){

    if (shape.getGlobalBounds().contains((Vector2f)mousePosition)){
        cout << "DENTRO" << endl;
        buttonState = BUTTON_HOVER;

        if (Mouse::isButtonPressed(Mouse::Left)){
            buttonState = BUTTON_PRESSED;
        }
    }

    switch(buttonState){
        case BUTTON_IDLE:
            shape.setFillColor(idleColorButton);
        break;
        case BUTTON_HOVER:
            shape.setFillColor(hoverColorButton);
        break;
        case BUTTON_PRESSED:
            shape.setFillColor(activeColorButton);
    }
}


void Button::render (RenderWindow& app){
    app.draw(shape);
    app.draw(textButton);
}
