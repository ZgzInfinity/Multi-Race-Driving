/*
 * Copyright (c) 2020 Andrés Gavín
 * Copyright (c) 2020 Rubén Rodríguez
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
 * Module Configuration implementation file
 */

#include "../include/Configuration.h"



/**
 * Assigns to the game the configuration read from the xml configuration file
 * @param difficulty is the difficulty level of the game
 * @param pixelArt controls if the graphics of the game have to be drawn with pixel art effect
 * @param fullScreen controls if the game is in full screen
 * @param axis_x is the width of the screen
 * @param axis_y is the height of the screen
 * @param controlLeft is the code of the key to move the vehicle to the left
 * @param controlLeft is the code of the key to move the vehicle to the right
 * @param controlAccelerate is the code of the key to accelerate the vehicle
 * @param controlSoundtrack is the code of the key to change the soundtrack of the game
 */
Configuration::Configuration(const Difficult difficulty, const bool pixelArt, const bool fullScreen, const int axis_x,
                             const int axis_y, const string controlLeft,const string controlRight, const string controlAccelerate,
                             const string controlBrake, const string controlSoundtrack)
                             : resolutions({SCREEN_DEFAULT, SCREEN_1, SCREEN_2, SCREEN_3, SCREEN_4, SCREEN_5}), camD(0.87), renderLen(450)
{
    // Check if the screen is in default resolution or not
    if (axis_x == DEFAULT_WIDTH && axis_y == DEFAULT_HEIGHT){
        isDefaultScreen = true;
        resIndex = 0;
    }
    else {
        isDefaultScreen = false;
    }

    // Establish the index of the resolution currently used in the vector
    if (axis_x == SCREEN_1.first && axis_y == SCREEN_1.second){
        resIndex = 1;
    }
    else if (axis_x == SCREEN_2.first && axis_y == SCREEN_2.second){
        resIndex = 2;
    }
    else if (axis_x == SCREEN_3.first && axis_y == SCREEN_3.second){
        resIndex = 3;
    }
    else if (axis_x == SCREEN_4.first && axis_y == SCREEN_5.second){
        resIndex = 4;
    }
    else if (axis_x == SCREEN_4.first && axis_y == SCREEN_5.second){
        resIndex = 5;
    }

    // Check if it's full screen or not
    if (!fullScreen){
        // Create the screen with not full screen resolution
        window.create(VideoMode(static_cast<unsigned int>(resolutions[resIndex].first),
                                static_cast<unsigned int>(resolutions[resIndex].second)), "Multi Race Driving",
                      Style::Titlebar | Style::Close);
    }
    else {
        // Create a screen with full screen resolution
        window.create(VideoMode::getFullscreenModes()[0], "Multi Race Driving", Style::Fullscreen);
        resIndex = -1;
    }

    // Set the FPS of the game
    window.setFramerateLimit(FPS);

    // Available repeated keys interruptions
    window.setKeyRepeatEnabled(false);

    // Initialize the flags that control the reading of the xml configuration files
    mainMenuRead = false;
    playerMenuRead = false;
    rivalTypeMenuRead = false;
    gameModesMenuRead = false;
    optionsMenuRead = false;
    graphicsMenuRead = false;
    soundMenuRead = false;
    comeFromOptions = false;
    comeFromGraphics = false;
    comeFromSound = false;
    vehicleControllersMenuRead = false;
    pauseMenuRead = false;
    vehicleSelectionMenuRead = false;
    circuitMenuRead = false;
    multiplayerMenuRead = false;
    multiplayerNameMenuRead = false;
    multiplayerGroupMenuRead = false;
    multiplayerJoinGroupMenuRead = false;
    multiplayerMembersGroupMenuRead = false;
    gameModesMultiplayerMenuRead = false;
    multiplayerTestConnectionMenuRead = false;

    // Creation of the view
    w.create(static_cast<unsigned int>(window.getView().getSize().x),
             static_cast<unsigned int>(window.getView().getSize().y));

    // Create the view to display the elements of the game
    window.setView(View(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f),
                          Vector2f(window.getSize().x, window.getSize().y)));
    w.create(static_cast<unsigned int>(window.getView().getSize().x),
               static_cast<unsigned int>(window.getView().getSize().y));

    // Calculate the factor of screen
    screenScale = float(w.getSize().x) / float(DEFAULT_WIDTH);

    // Check if it's default screen resolution
    if (isDefaultScreen){
        // Store the thresholds and image offsets with their default values
        imageOffset = IMAGE_DEFAULT_OFFSET;
        thresholdDescriptionX = SCREEN_HD_HEIGHT;
        thresholdDescriptionY = VERTICAL_OFFSET;
    }
    else {
        // Store the thresholds and image offsets depending of the current resolution
        thresholdDescriptionX = w.getSize().x * SCREEN_HD_HEIGHT / DEFAULT_WIDTH;
        thresholdDescriptionY = int((w.getSize().y * VERTICAL_OFFSET / DEFAULT_HEIGHT) * 1.2f);
        imageOffset = float(w.getSize().y) * IMAGE_DEFAULT_OFFSET / DEFAULT_HEIGHT;
    }

    // Assign icon to the screen of the game
    Image i;
    i.loadFromFile("Data/Icon/MultiRaceDriving.png");
    window.setIcon(i.getSize().x, i.getSize().y, i.getPixelsPtr());

    // Calculate the factor of screen
    screenScale = float(w.getSize().x) / float(DEFAULT_WIDTH);

    // Assign the key controllers
    menuKey = Keyboard::Escape;
    menuUpKey = Keyboard::Up;
    menuDownKey = Keyboard::Down;
    menuEnterKey = Keyboard::Enter;

    // Initialize the keyword mapper
    int index;
    KeywordMapper kM = KeywordMapper();

    // Look for the keyboard to control the turning left
    index = kM.lookForKeyBoard(controlLeft);
    leftKey = kM.mapperCodeKeyWord[index];

    // Look for the keyboard to control the turning right
    index = kM.lookForKeyBoard(controlRight);
    rightKey = kM.mapperCodeKeyWord[index];

    // Look for the keyboard to control the acceleration
    index = kM.lookForKeyBoard(controlAccelerate);
    accelerateKey = kM.mapperCodeKeyWord[index];

    // Look for the keyboard to control the braking
    index = kM.lookForKeyBoard(controlBrake);
    brakeKey = kM.mapperCodeKeyWord[index];

    // Look for the keyboard to control the changing soundtrack
    index = kM.lookForKeyBoard(controlSoundtrack);
    soundtrackKey = kM.mapperCodeKeyWord[index];

    // Store all the fonts of the text used by the game
    fontElapsedTime = initializeFontElapsedTime();
    fontTimeToPlay = initializeFontTimeToPlay();
    fontMenus = initializeFontMenus();
    speedVehicle = initializeFontElapsedTime();

    // Store the difficult of the game
    level = difficulty;

    // By default any aspect of the configuration has been modified
    modifiedConfig = false;
    changeAnyParameter = false;

    // Default level of AI aggressiveness
    maxAggressiveness = 0.0f;

    // AI always active
    enableAI = true;

    // Assigns the pixel art flag
    enablePixelArt = pixelArt;
}



/**
 * Load the configuration of the graphics menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void Configuration::loadGraphicsMenuConfiguration(const string path){

    // Open the xml file of the scenario
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Local variable to store temporary the text content and the fonts of the texts
    string content, fontPath, backgroundTexture, colorKind;

    // Iterate to get the information of the graphics menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check it is the node that contains the information of the background
        if ((string)property->name() == "Background"){
            // Get the background image of the menu
            backgroundTexture = (string)property->value();
            graphicsMenuBackground.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the graphics menu
            for (xml_node<> *panelProp = property->first_node(); panelProp; panelProp = panelProp->next_sibling()){
                // Check it is the node that contains the information of the background of the panel
                if ((string)panelProp->name() == "Background"){
                    // Get the background image of the menu
                    backgroundTexture = (string)panelProp->value();
                    graphicsMenuPanelBack.loadFromFile(backgroundTexture);
                }
                // Check it is the node that contains the information of the color border of the panel
                else if ((string)panelProp->name() == "ColorBorder"){
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the graphics menu
                    for (xml_node<> *colorChannel = panelProp->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                        // Get the red color channel
                        if ((string)colorChannel->name() == "R"){
                            // Get the red channel
                            colorRed = stoi((string)colorChannel->value());
                        }
                        // Get the green color channel
                        else if ((string)colorChannel->name() == "G"){
                            // Get the red channel
                            colorGreen = stoi((string)colorChannel->value());
                        }
                        // Get the blue color channel
                        else if ((string)colorChannel->name() == "B"){
                            // Get the red channel
                            colorBlue = stoi((string)colorChannel->value());
                        }
                    }
                    // Store the color border of the panel
                    colorBorderPanelGraphicsMenu = Color(colorRed, colorGreen, colorBlue);
                }
            }
        }
        // Check if it is the node that stores the information of the main text of the menu
        else if ((string)property->name() == "Title"){
            // Iterate to get the information of the title
            for (xml_node<> *titleProp = property->first_node(); titleProp; titleProp = titleProp->next_sibling()){
                // Get the red color channel
                if ((string)titleProp->name() == "Content"){
                    // Get the content of the title
                    content = (string)titleProp->value();
                    contentTitleGraphicsMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    fontGraphicsMenu.loadFromFile(fontPath);
                }
                // Get color text of the title
                else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                    // Get the kind of color to process
                    colorKind = (string)titleProp->name();
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the player menu
                    for (xml_node<> *colorChannel = titleProp->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                        // Get the red color channel
                        if ((string)colorChannel->name() == "R"){
                            // Get the red channel
                            colorRed = stoi(colorChannel->value());
                        }
                        // Get the green color channel
                        else if ((string)colorChannel->name() == "G"){
                            // Get the red channel
                            colorGreen = stoi(colorChannel->value());
                        }
                        // Get the blue color channel
                        else if ((string)colorChannel->name() == "B"){
                            // Get the red channel
                            colorBlue = stoi(colorChannel->value());
                        }
                    }
                    // Check if it is the color of the text
                    if (colorKind == "ColorText"){
                        colorTitleTextGraphicsMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        colorTitleBorderGraphicsMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
        // Check if it is the node that the different buttons of the graphics menu
        else if ((string)property->name() == "MenuButtons"){
            // Iterate to get the information of the buttons of the graphics menu
            for (xml_node<> *buttonProp = property->first_node(); buttonProp; buttonProp = buttonProp->next_sibling()){
                // Get the font of the buttons
                if ((string)buttonProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)buttonProp->value();
                    fontMenuGraphicsButtons.loadFromFile(fontPath);
                }
                // Get the color of the font button
                else if ((string)buttonProp->name() == "ColorFont"){
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the color font channels
                    for (xml_node<> *colorChannel = buttonProp->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                        // Get the red color channel
                        if ((string)colorChannel->name() == "R"){
                            // Get the red channel
                            colorRed = stoi(colorChannel->value());
                        }
                        // Get the green color channel
                        else if ((string)colorChannel->name() == "G"){
                            // Get the red channel
                            colorGreen = stoi(colorChannel->value());
                        }
                        // Get the blue color channel
                        else if ((string)colorChannel->name() == "B"){
                            // Get the red channel
                            colorBlue = stoi(colorChannel->value());
                        }
                    }
                    // Store the color
                    colorFontMenuGraphicsButtons = Color(colorRed, colorGreen, colorBlue);
                }
                // Get the information of the buttons
                else if ((string)buttonProp->name() == "Buttons"){
                    // Local variables to store the attributes of the buttons
                    string contentButton;
                    Texture icon;
                    Sprite s;
                    // Iterate to get the information of the buttons
                    for (xml_node<> *buttonNode = buttonProp->first_node(); buttonNode; buttonNode = buttonNode->next_sibling()){
                        // Iterate to get the information of the buttons
                        for (xml_node<> *button = buttonNode->first_node(); button; button = button->next_sibling()){
                            // Get the font of the buttons
                            if ((string)button->name() == "Content"){
                                // Read the font from the file
                                contentButton = (string)button->value();
                                contentButtonsGraphics.push_back(contentButton);
                            }
                            // Get the colors of the button
                            else if ((string)button->name() == "Colors"){
                                // Read the colors of the button
                                for (xml_node<> *colorButton = button->first_node(); colorButton; colorButton = colorButton->next_sibling()){
                                    // Get the border color of the panel
                                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                                    // Iterate to get the information of the graphics menu
                                    for (xml_node<> *color = colorButton->first_node(); color; color = color->next_sibling()){
                                        // Get the red color channel
                                        if ((string)color->name() == "R"){
                                            // Get the red channel
                                            colorRed = stoi(color->value());
                                        }
                                        // Get the green color channel
                                        else if ((string)color->name() == "G"){
                                            // Get the red channel
                                            colorGreen = stoi(color->value());
                                        }
                                        // Get the blue color channel
                                        else if ((string)color->name() == "B"){
                                            // Get the red channel
                                            colorBlue = stoi(color->value());
                                        }
                                    }
                                    // Push the color of the button read
                                    colorButtons.push_back(Color(colorRed, colorGreen, colorBlue));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // The player menu has been read correctly
    graphicsMenuRead = true;
}



/**
 * Represents on the screen the graphics menu and returns to options menu
 * @return
 */
State Configuration::graphicsMenu(SoundPlayer& r) {
        // Control if the start key is pressed or not
    bool startPressed = false;
    bool resized = false;

    // Read the options menu if it has not been read
    if (!graphicsMenuRead){
        // Read the options menu xml configuration file
        string pathFile = "Data/Menus/GraphicsMenu/Configuration/GraphicsMenu.xml";
        loadGraphicsMenuConfiguration(pathFile);
    }

    // While the start button has not been pressed
    while (!startPressed) {
        bool currentResized = false;

        // Clean the console window
        w.clear(Color(0, 0, 0));
        Sprite bufferSprite(w.getTexture());
        w.display();
        window.draw(bufferSprite);
        window.display();

        // Clean the console window
        w.clear(Color(0, 0, 0));
        bufferSprite.setTexture(w.getTexture(), true);
        w.display();
        window.draw(bufferSprite);
        window.display();

        // Set the textures of the graphics menu
        graphicsMenuBackground.setRepeated(true);
        graphicsMenuPanelBack.setRepeated(true);

        // Adapt the graphics menu to the different screen resolutions
        IntRect background(0, 0, w.getSize().x, w.getSize().y);
        Sprite sprite(graphicsMenuBackground, background);
        float axis_x = float(w.getSize().x) / DEFAULT_WIDTH;
        float axis_y = float(w.getSize().y) / DEFAULT_HEIGHT;
        sprite.setScale(axis_x, axis_y);
        ghMenuBackground = sprite;

        // Create the panel of the menu
        RectangleShape shape;
        shape.setPosition((w.getSize().x / 2.f) - 300.0f * screenScale, w.getSize().y / 2.f - 250.0f * screenScale);
        shape.setSize(sf::Vector2f(610.0f * screenScale, 500.0f * screenScale));
        shape.setOutlineColor(colorBorderPanelGraphicsMenu);
        shape.setOutlineThickness(5.0f * screenScale);
        shape.setTexture(&graphicsMenuPanelBack, true);

        // Vector with the right buttons of the menu
        vector<Button> menuButtons;

        // Main Text of the menu
        Text optionsText;
        optionsText.setString(contentTitleGraphicsMenu);
        optionsText.setCharacterSize(static_cast<unsigned int>(int(40.0f * screenScale)));
        optionsText.setFont(fontGraphicsMenu);
        optionsText.setStyle(Text::Bold | Text::Underlined);
        optionsText.setFillColor(colorTitleTextGraphicsMenu);
        optionsText.setOutlineColor(colorTitleBorderGraphicsMenu);
        optionsText.setOutlineThickness(5.0f * screenScale);
        optionsText.setPosition(w.getSize().x / 2.f - optionsText.getLocalBounds().width / 2.f,
                                w.getSize().y / 2.f - 220.0f * screenScale);

        // Option indicators
        menuButtons.emplace_back(w.getSize().x / 2.f - 270.0f * screenScale, w.getSize().y / 2.f - 70.0f * screenScale,
                                 200.0f * screenScale, 40.0f * screenScale, fontMenuGraphicsButtons,
                                 contentButtonsGraphics[0], colorButtons[0], colorButtons[1], colorFontMenuGraphicsButtons, 1, screenScale);

        menuButtons.emplace_back(w.getSize().x / 2.f - 270.0f * screenScale, w.getSize().y / 2.f, 200.0f * screenScale,
                                 40.0f * screenScale, fontMenuGraphicsButtons,
                                 contentButtonsGraphics[1], colorButtons[2], colorButtons[3], colorFontMenuGraphicsButtons, 0, screenScale);

        // Option configurations
        const string res = resIndex > -1 ? to_string(resolutions[resIndex].first) + "x" +
                                           to_string(resolutions[resIndex].second) : "FULLSCREEN";
        menuButtons.emplace_back(w.getSize().x / 2.f + 80.0f * screenScale, w.getSize().y / 2.f - 70.0f * screenScale,
                                 200.0f * screenScale, 40.0f * screenScale, fontMenuGraphicsButtons,
                                 res, colorButtons[0], colorButtons[1], colorFontMenuGraphicsButtons, 1, screenScale);

        menuButtons.emplace_back(w.getSize().x / 2.f + 80.0f * screenScale, w.getSize().y / 2.f, 200.0f * screenScale,
                                 40.0f * screenScale, fontMenuGraphicsButtons,
                                 enablePixelArt ? "Enabled" : "Disabled", colorButtons[2], colorButtons[3], colorFontMenuGraphicsButtons,
                                 0, screenScale);

        // Control the option selected by the user
        int optionSelected = 0;

        // Until the start keyword is not pressed
        while (!startPressed && !currentResized) {
            // Detect the possible events
            Event e{};
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }

            window.pollEvent(e);
            // Control if the down cursor key has been pressed
            if (window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Down)) {
                if (optionSelected != int(menuButtons.size() - 1) / 2) {
                    r.soundEffects[0]->play();
                    optionSelected++;
                    menuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    menuButtons[optionSelected - 1].setButtonState(BUTTON_IDLE);
                    menuButtons[optionSelected + 2].setButtonState(BUTTON_HOVER);
                    menuButtons[optionSelected + 1].setButtonState(BUTTON_IDLE);
                }
            }
            // Control if the up cursor key has been pressed
            else if (window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Up)) {
                if (optionSelected != 0) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->play();
                    optionSelected--;
                    menuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    menuButtons[optionSelected + 1].setButtonState(BUTTON_IDLE);
                    menuButtons[optionSelected + 2].setButtonState(BUTTON_HOVER);
                    menuButtons[optionSelected + 3].setButtonState(BUTTON_IDLE);
                }
            }

            window.pollEvent(e);

            if (optionSelected == 0) {
                // Screen resolutions

                // Check if left or right cursor keys have been pressed or not
                if (window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Left)) {
                    if (resized) {
                        // The screen has not been resized during the game before
                        resized = false;
                    }
                    else if (resIndex > -1) {
                        // Modify the resolution of the screen
                        r.soundEffects[0]->stop();
                        r.soundEffects[0]->play();
                        resIndex--;
                        menuButtons[optionSelected + 2].setTextButton(resIndex > -1 ?
                                                                      to_string(resolutions[resIndex].first) + "x" +
                                                                      to_string(resolutions[resIndex].second)
                                                                                    : "FULLSCREEN");

                        // Control if there are more resolutions on the left
                        if (resIndex > -1) {
                            window.create(VideoMode(static_cast<unsigned int>(resolutions[resIndex].first),
                                                    static_cast<unsigned int>(resolutions[resIndex].second)),
                                          "Multi Race Driving",
                                          Style::Titlebar | Style::Close);

                            // The screen is not in full screen mode
                            fullScreen = false;
                        }
                        else {
                            // Create a new screen with the new resolution
                            window.create(VideoMode::getFullscreenModes()[0], "Multi Race Driving", Style::Fullscreen);
                            // The current screen is on full screen mode
                            fullScreen = true;
                        }
                        window.setFramerateLimit(FPS);
                        window.setKeyRepeatEnabled(false);

                        isDefaultScreen = resIndex == 0;

                        // Define the screen to represent correctly the interface
                        window.setView(View(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f),
                                            Vector2f(window.getSize().x, window.getSize().y)));
                        w.create(static_cast<unsigned int>(window.getView().getSize().x),
                                 static_cast<unsigned int>(window.getView().getSize().y));

                        // Calculation of the screen factor between the current resolution and the default resolution
                        screenScale = float(w.getSize().x) / float(DEFAULT_WIDTH);
                        currentResized = true;
                        resized = true;
                    }
                    // Calculation of threshold to display correctly the description of the buttons
                    thresholdDescriptionX = w.getSize().x * SCREEN_HD_HEIGHT / DEFAULT_WIDTH;
                    thresholdDescriptionY = int((w.getSize().y * VERTICAL_OFFSET / DEFAULT_HEIGHT) * 1.2f);
                    imageOffset = float(w.getSize().y) * IMAGE_DEFAULT_OFFSET / DEFAULT_HEIGHT;
                    changeAnyParameter = true;
                }
                else if (window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Right)) {
                    // The screen has not been resized during the game before
                    if (resized) {
                        resized = false;
                    }
                    if (resIndex < int(resolutions.size()) - 1 && !resized) {
                        r.soundEffects[0]->stop();
                        r.soundEffects[0]->play();
                        resIndex++;

                        // Modify the resolution of the screen
                        menuButtons[optionSelected + 2].setTextButton(to_string(resolutions[resIndex].first) + "x" +
                                                                      to_string(resolutions[resIndex].second));

                        // Create a new screen with the new resolution
                        window.create(VideoMode(static_cast<unsigned int>(resolutions[resIndex].first),
                                                static_cast<unsigned int>(resolutions[resIndex].second)), "Multi Race Driving",
                                      Style::Titlebar | Style::Close);
                        window.setFramerateLimit(FPS);
                        window.setKeyRepeatEnabled(false);
                        isDefaultScreen = resIndex == 0;

                        // Adapt the view of the screen to the new resolution
                        window.setView(View(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f),
                                            Vector2f(window.getSize().x, window.getSize().y)));
                        w.create(static_cast<unsigned int>(window.getView().getSize().x),
                                 static_cast<unsigned int>(window.getView().getSize().y));

                        screenScale = float(w.getSize().x) / float(DEFAULT_WIDTH);
                        currentResized = true;
                        resized = true;
                    }
                    fullScreen = false;
                    changeAnyParameter = true;
                }
                // Calculation of threshold to display correctly the description of the buttons
                thresholdDescriptionX = (w.getSize().x * SCREEN_HD_HEIGHT / DEFAULT_WIDTH);
                thresholdDescriptionY = int((w.getSize().y * VERTICAL_OFFSET / DEFAULT_HEIGHT) * 1.2f);
                imageOffset = float(w.getSize().y) * IMAGE_DEFAULT_OFFSET / DEFAULT_HEIGHT;
            }
            else {
                // Pixel Art

                // Check if left or right cursor keys have been pressed or not
                if (window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Left)) {
                    if (enablePixelArt) {
                        r.soundEffects[0]->stop();
                        r.soundEffects[0]->play();
                        enablePixelArt = false;
                        menuButtons[optionSelected + 2].setTextButton("Disabled");
                        changeAnyParameter = true;
                    }
                }
                else if (window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Right)) {
                    if (!enablePixelArt) {
                        r.soundEffects[0]->stop();
                        r.soundEffects[0]->play();
                        enablePixelArt = true;
                        menuButtons[optionSelected + 2].setTextButton("Enabled");
                        changeAnyParameter = true;
                    }
                }
            }

            // Draw the elements of the menu
            w.draw(sprite);
            w.draw(shape);
            w.draw(optionsText);

            // Show the buttons of the menu
            for (auto &menuButton : menuButtons) {
                menuButton.render(&w);
            }

            // Display the menu in the screen
            bufferSprite.setTexture(w.getTexture(), true);
            w.display();
            window.draw(bufferSprite);
            window.display();
            sleep(milliseconds(120));
            r.soundEffects[0]->stop();

            // Check if left or right cursor keys have been pressed or not
            if (window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {
                // Change the controllers of the car
                startPressed = true;
                modifiedConfig = true;
                r.soundEffects[2]->stop();
                r.soundEffects[2]->play();
            }
        }
    }
    return OPTIONS;
}



/**
 * Returns the font used to write the time in the elapsed time panel
 * @return
 */
Font initializeFontElapsedTime() {
    Font f;
    if (!f.loadFromFile("Data/Fonts/digital.ttf")) exit(1);
    return f;
}



/**
 * Returns the font used to represent the HUD during the game
 * @return
 */
Font initializeFontTimeToPlay() {
    Font f;
    if (!f.loadFromFile("Data/Fonts/DisposableDroid.ttf")) exit(1);
    return f;
}



/**
 * Returns the font used to represent all the text indicators in
 * the animations of the game
 * @return
 */
Font initializeFontMenus() {
    Font f;
    if (!f.loadFromFile("Data/Fonts/Hetikademo.otf")) exit(1);
    return f;
}
