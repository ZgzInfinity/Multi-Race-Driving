

#include "../include/Environment.h"



/**
 * Constructor of the data type environment
 * @param
 */
Environment::Environment(){}



void Environment::configure(string pathSpeedIndicator, string pathSpeedGraphic, string fontPathSpeedPanel, int posXSpeedPanel, int posYSpeedPanel,
                            int sizeTextSpeedPanel, int posXTextSpeedPanel, int posYTextSpeedPanel,
                            string pathElapsedIndicator, string fontPathElapsedPanel, int posXElapsedPanel, int posYElapsedPanel,
                            int sizeTextElapsedPanel, int posXTextElapsedPanel, int posYTextElapsedPanel,
                            string fontPathTimeText, int sizeTimeText, int posXTimeText, int posYTimeText,
                            string fontPathTimeIndicator, int sizeTimeIndicator, int posXTimeIndicator, int posYTimeIndicator,
                            string fontPathDestinyText, int sizeDestinyText, int posXDestinyText, int posYDestinyText,
                            string fontPathDestinyIndicator, int sizeDestinyIndicator, int posXDestinyIndicator, int posYDestinyIndicator,
                            Color colorSpeedPanel, Color colorElapsedPanel, Color colorTimeText, Color colorTimeIndicator,
                            Color colorDestinyText, Color colorDestinyIndicator, int border, Color colorBorderPanel)
{
    textureSpeedPanel.loadFromFile(pathSpeedIndicator);
    spriteSpeedPanel.setTexture(textureSpeedPanel);
    pathGraphic = pathSpeedGraphic;
    posXFile = posXTextSpeedPanel;

    if (pathSpeedGraphic != ""){
         textureSpeedGraphic.loadFromFile(pathSpeedGraphic);
         spriteSpeedGraphic.setTexture(textureSpeedGraphic, true);
         spriteSpeedGraphic.setPosition(posXSpeedPanel - 125, posYSpeedPanel + 52);
    }

    textureElapsedPanel.loadFromFile(pathElapsedIndicator);
    spriteElapsedPanel.setTexture(textureElapsedPanel);

    spriteSpeedPanel.setPosition(Vector2f(posXSpeedPanel, posYSpeedPanel));
    spriteElapsedPanel.setPosition(Vector2f(posXElapsedPanel, posYElapsedPanel));

    fontSpeedIndicator.loadFromFile(fontPathSpeedPanel);
    fontElapsedIndicator.loadFromFile(fontPathElapsedPanel);
    fontTimePanel.loadFromFile(fontPathTimeText);
    fontTimeIndicator.loadFromFile(fontPathTimeIndicator);
    fontDestinyPanel.loadFromFile(fontPathDestinyText);
    fontDestinyIndicator.loadFromFile(fontPathDestinyIndicator);

    // Message used to alert the player where is the next checkpoint to pass
    message = "Next checkpoint";

    // Configuring the text speed indicator
    textSpeedIndicator.setFillColor(colorSpeedPanel);
    textSpeedIndicator.setOutlineThickness(border);
    textSpeedIndicator.setOutlineColor(colorBorderPanel);
    textSpeedIndicator.setCharacterSize(sizeTextSpeedPanel);
    textSpeedIndicator.setStyle(Text::Bold);
    textSpeedIndicator.setPosition(posXTextSpeedPanel, posYTextSpeedPanel);
    textSpeedIndicator.setFont(fontSpeedIndicator);


    // Configuring the text elapsed indicator
    textElapsedIndicator.setFillColor(colorElapsedPanel);
    textElapsedIndicator.setCharacterSize(sizeTextElapsedPanel);
    textElapsedIndicator.setStyle(Text::Bold);
    textElapsedIndicator.setPosition(posXTextElapsedPanel, posYTextElapsedPanel);
    textElapsedIndicator.setFont(fontElapsedIndicator);

    // Configuring the time text panel
    textTimePanel.setFillColor(colorTimeText);
    textTimePanel.setCharacterSize(sizeTimeText);
    textTimePanel.setStyle(Text::Bold);
    textTimePanel.setOutlineThickness(border);
    textTimePanel.setOutlineColor(colorBorderPanel);
    textTimePanel.setPosition(posXTimeText, posYTimeText);
    textTimePanel.setFont(fontTimePanel);

    // Configuring the time text indicator
    textTimeIndicator.setFillColor(colorTimeIndicator);
    textTimeIndicator.setCharacterSize(sizeTimeIndicator);
    textTimeIndicator.setStyle(Text::Bold);
    textTimeIndicator.setPosition(posXTimeIndicator, posYTimeIndicator);
    textTimeIndicator.setFont(fontTimeIndicator);
    textTimeIndicator.setOutlineThickness(border);
    textTimeIndicator.setOutlineColor(colorBorderPanel);

    // Configuring the distance text panel
    textDestinyPanel.setFillColor(colorDestinyText);
    textDestinyPanel.setCharacterSize(sizeDestinyText);
    textDestinyPanel.setStyle(Text::Bold);
    textDestinyPanel.setPosition(posXDestinyText, posYDestinyText);
    textDestinyPanel.setFont(fontDestinyPanel);
    textDestinyPanel.setString(message);
    textDestinyPanel.setOutlineThickness(border);
    textDestinyPanel.setOutlineColor(colorBorderPanel);

    // Configuring the distance text indicator
    textDestinyIndicator.setFillColor(colorDestinyIndicator);
    textDestinyIndicator.setCharacterSize(sizeDestinyIndicator);
    textDestinyIndicator.setStyle(Text::Bold);
    textDestinyIndicator.setPosition(posXDestinyIndicator, posYDestinyIndicator);
    textDestinyIndicator.setFont(fontDestinyIndicator);
    textDestinyIndicator.setOutlineThickness(border);
    textDestinyIndicator.setOutlineColor(colorBorderPanel);


}
