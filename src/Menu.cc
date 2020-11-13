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
 * Module Menu implementation file
 */


#include "../include/Menu.h"



/**
 * Shows the initial animation of the game
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 * @return
 */
State introAnimation(Configuration &c, SoundPlayer& r) {

    r.soundTracks[0]->play();

    // Vector of images with the logo of Sega
    Texture t;
    Sprite icon;

    // Loading the icon texture
    t.loadFromFile("Data/Animations/IntroAnimation/Icon.png");

    // Load the texture in the sprite reseting the last texture
    icon.setTexture(t, true);
    icon.setScale(0.5f, 0.5f);

    // Locate the icon in the center of the screen
    icon.setPosition((c.w.getSize().x - icon.getGlobalBounds().width) / 2.0f,
                     (c.w.getSize().y - icon.getGlobalBounds().height) / 2.0f);

    // Wait until the time expires
    for (int i = 1; i < TIME_ANIMATION; i++) {

        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return EXIT;
            }
        }

        // Clear the screen and draw the icon
        c.w.clear();
        c.w.draw(icon);

        // Show the logos in the console
        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

        // Sleep the process to see the menu icons correctly
        sleep(milliseconds(55));
    }


    // Loading the icon texture
    t.loadFromFile("Data/Animations/IntroAnimation/Presents.png");

    // Load the texture in the sprite reseting the last texture
    icon.setTexture(t, true);
    icon.setScale(0.5f, 0.5f);

    // Locate the logo in the center of the screen
    icon.setPosition((c.w.getSize().x - icon.getGlobalBounds().width) / 2.0f,
                             (c.w.getSize().y - icon.getGlobalBounds().height) / 2.0f);

    // Iterate until the time expires
    for (int i = 1; i < TIME_ANIMATION; i++) {

        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return EXIT;
            }
        }

        c.w.clear();
        c.w.draw(icon);
        // Show the logos in the console
        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

        // Sleep the process to see the menu icons correctly
        sleep(milliseconds(55));
    }
    return START;
}



/**
 * Load the configuration of the main menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
inline void loadMainMenuConfiguration(const string path, Configuration& c){

    // Open the xml file of the main menu
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Local variable to store temporary the text content and the fonts of the texts
    string content, fontPath, backgroundTexture, colorKind;

    // Iterate to get the information of the main menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check if it's the node that control the possible curve coefficient
        if ((string)property->name() == "Background"){
           backgroundTexture = (string)property->value();
           c.textureBackground.loadFromFile(backgroundTexture);
        }
        else if ((string)property->name() == "Texts"){
            // Iterate the different texts of the main menu
            for (xml_node<> *text = property->first_node(); text; text = text->next_sibling()){
                // Iterate the different properties of the text
                for (xml_node<> *propertyText = text->first_node(); propertyText; propertyText = propertyText->next_sibling()){
                    // Read the content of the text
                    if ((string)propertyText->name() == "Content"){
                        content = (string)propertyText->value();
                        c.contents.push_back(content);
                    }
                    // Read the font of the texts
                    else if ((string)propertyText->name() == "Font"){
                        // Load the font of the texts
                        fontPath = (string)propertyText->value();
                        Font f;
                        f.loadFromFile(fontPath);
                        c.fontsMainMenu.push_back(f);
                    }
                    // Read the color of the text
                    else if ((string)propertyText->name() == "ColorText" || (string)propertyText->name() == "ColorBorder"){
                        colorKind = (string)propertyText->name();
                        // Channels of the RGB color
                        int colorRed = 0, colorGreen = 0, colorBlue = 0;
                        // Iterate the different colors of the text
                        for (xml_node<> *color = propertyText->first_node(); color; color = color->next_sibling()){
                            // Red color channel
                            if ((string)color->name() == "R"){
                                colorRed = stoi(color->value());
                            }
                            // Green color channel
                            else if ((string)color->name() == "G"){
                                colorGreen = stoi(color->value());
                            }
                            // Blue color channel
                            else if ((string)color->name() == "B"){
                                colorBlue = stoi(color->value());
                            }
                        }
                        // Control if it is a text color or a border color
                        if (colorKind == "ColorText"){
                            // Push the text color
                            c.colorTexts.push_back(Color(colorRed, colorGreen, colorBlue));
                        }
                        else if (colorKind == "ColorBorder"){
                            // Push the text color
                            c.colorBorders.push_back(Color(colorRed, colorGreen, colorBlue));
                        }
                    }
                }
            }
        }
    }
    // The main menu configuration has been read
    c.mainMenuRead = true;
}



/**
 * Displays the main menu of the game
 * @param c is the configuration of the file
 * @param startPressed controls if the enter key has been pressed
 * @return
 */
State startMenu(Configuration &c, SoundPlayer &r, bool startPressed) {

    // Set the scale of the console window
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));
    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Number of elements of the menu
    const int NUM_TEXTS = 8;

    // Clean the console window of the game
    c.w.clear();
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Vector of textures and sprites of the main menu
    vector<Sprite> nameGames;

    // Control if the main menu configuration has been read
    if (!c.mainMenuRead){
        // Path of the file with the configuration of the main menu
        string path = "Data/Menus/MainMenu/Configuration/MainMenu.xml";

        // Load the properties of the main menu
        loadMainMenuConfiguration(path, c);
    }

    // Global rectangle of the background
    IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
    Sprite sprite(c.textureBackground, background);
    float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
    float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
    sprite.setScale(axis_x, axis_y);
    c.sBackground = sprite;

    // Options of the main menu
    Text textElements[NUM_TEXTS];

    Text titleGame1;
    titleGame1.setString("MULTI RACE");
    titleGame1.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
    titleGame1.setFont(c.fontsMainMenu[0]);
    titleGame1.setFillColor(Color::White);
    titleGame1.setOutlineColor(Color::Black);
    titleGame1.setOutlineThickness(5.0f * c.screenScale);
    titleGame1.setStyle(Text::Bold);
    titleGame1.setPosition((c.w.getSize().x - titleGame1.getGlobalBounds().width) / 2.f,
                            c.w.getSize().y / 2.f - 200.0f * c.screenScale);

    Text titleGame2;
    titleGame2.setString("DRIVING");
    titleGame2.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
    titleGame2.setFont(c.fontsMainMenu[0]);
    titleGame2.setFillColor(Color::White);
    titleGame2.setOutlineColor(Color::Black);
    titleGame2.setOutlineThickness(5.0f * c.screenScale);
    titleGame2.setStyle(Text::Bold);
    titleGame2.setPosition((c.w.getSize().x - titleGame2.getGlobalBounds().width) / 2.f,
                            c.w.getSize().y / 2.f - 150.0f * c.screenScale);

    // Fill the vector with the information read in the
    // configuration file of the menu
    textElements[0].setString(c.contents[0]);
    textElements[0].setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    textElements[0].setFont(c.fontsMainMenu[0]);
    textElements[0].setFillColor(c.colorTexts[0]);
    textElements[0].setOutlineColor(c.colorBorders[0]);
    textElements[0].setOutlineThickness(3.0f * c.screenScale);
    textElements[0].setPosition((c.w.getSize().x - textElements[0].getGlobalBounds().width) / 2.f,
                                c.w.getSize().y / 2.f + 30.0f * c.screenScale);

    textElements[1].setString(c.contents[1]);
    textElements[1].setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    textElements[1].setFont(c.fontsMainMenu[1]);
    textElements[1].setFillColor(c.colorTexts[1]);
    textElements[1].setOutlineColor(c.colorBorders[1]);
    textElements[1].setOutlineThickness(3.0f * c.screenScale);
    float initialX = c.w.getSize().x - 1.1f * textElements[1].getGlobalBounds().width, initialY =
            c.w.getSize().y - 2.0f * float(textElements[1].getCharacterSize());
    textElements[1].setPosition(initialX, initialY);
    float refY = initialY;

    textElements[2].setString(c.contents[2]);
    textElements[2].setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    textElements[2].setFont(c.fontsMainMenu[2]);
    textElements[2].setFillColor(c.colorTexts[2]);
    textElements[2].setOutlineColor(c.colorBorders[2]);
    textElements[2].setOutlineThickness(3.0f * c.screenScale);
    textElements[2].setPosition(initialX + textElements[2].getGlobalBounds().width * 1.3f, initialY - 40.f * c.screenScale);

    initialX = textElements[1].getGlobalBounds().width;
    textElements[3].setString(c.contents[3]);
    textElements[3].setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    textElements[3].setFont(c.fontsMainMenu[3]);
    textElements[3].setFillColor(c.colorTexts[3]);
    textElements[3].setOutlineColor(c.colorBorders[4]);
    textElements[3].setOutlineThickness(3.0f * c.screenScale);
    textElements[3].setPosition(initialX / 6.5f, initialY);

    initialY -= 2.0f * textElements[3].getGlobalBounds().height;
    textElements[4].setString(c.contents[4]);
    textElements[4].setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    textElements[4].setFont(c.fontsMainMenu[4]);
    textElements[4].setFillColor(c.colorTexts[4]);
    textElements[4].setOutlineColor(c.colorBorders[4]);
    textElements[4].setOutlineThickness(3.0f * c.screenScale);
    textElements[4].setPosition(initialX / 6.5f, initialY);

    initialY -= 2.0f * textElements[4].getGlobalBounds().height;
    textElements[5].setString(c.contents[5]);
    textElements[5].setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    textElements[5].setFont(c.fontsMainMenu[5]);
    textElements[5].setFillColor(c.colorTexts[5]);
    textElements[5].setOutlineColor(c.colorBorders[5]);
    textElements[5].setOutlineThickness(3.0f * c.screenScale);
    textElements[5].setPosition(initialX / 6.5f, initialY);

    initialY -= 2.0f * textElements[4].getGlobalBounds().height;
    textElements[6].setString(c.contents[6]);
    textElements[6].setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    textElements[6].setFont(c.fontsMainMenu[6]);
    textElements[6].setFillColor(c.colorTexts[6]);
    textElements[6].setOutlineColor(c.colorBorders[6]);
    textElements[6].setOutlineThickness(3.0f * c.screenScale);
    textElements[6].setPosition(c.w.getSize().x / 2.f - textElements[6].getLocalBounds().width / 2.f, initialY + 122.f * c.screenScale);

    initialY -= 2.0f * textElements[4].getGlobalBounds().height;
    textElements[7].setString(c.contents[7]);
    textElements[7].setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    textElements[7].setFont(c.fontsMainMenu[7]);
    textElements[7].setFillColor(c.colorTexts[7]);
    textElements[7].setOutlineColor(c.colorBorders[7]);
    textElements[7].setOutlineThickness(3.0f * c.screenScale);
    textElements[7].setPosition(c.w.getSize().x / 2.f - textElements[7].getLocalBounds().width / 2.f, refY);

    // Partial state of the game
    State state = START;

    // Change the background texture
    c.w.draw(c.sBackground);

    float elapsed1, elapsed2;
    Clock blinkClcok;
    Time blink_delay = seconds(1.0);

    blinkClcok.restart().asSeconds();
    elapsed1 = blinkClcok.restart().asSeconds();
    bool blink = true;

    // Control if the space key has been pressed
    bool spacePressed = false;

    // While the console window is opened
    while (c.window.isOpen()) {
        // While the ENTER keyword is not pressed
        while (!startPressed && !spacePressed) {
            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }


            elapsed2 = blinkClcok.getElapsedTime().asSeconds();

            // Change the color of the main text
            if (elapsed2 - elapsed1 >= blink_delay.asSeconds()) {
                blink = !blink;
                blinkClcok.restart();
            }
            if (blink) {
                textElements[0].setFillColor(c.colorTexts[0]);
                textElements[0].setOutlineColor(c.colorBorders[0]);
            }
            else {
                textElements[0].setFillColor(Color::Transparent);
                textElements[0].setOutlineColor(Color::Transparent);
            }

            // Show the press start title in the menu
            c.w.draw(c.sBackground);

            c.w.draw(titleGame1);
            c.w.draw(titleGame2);

            c.w.draw(textElements[0]);
            c.w.draw(textElements[1]);
            c.w.draw(textElements[2]);
            c.w.draw(textElements[3]);
            c.w.draw(textElements[4]);
            c.w.draw(textElements[5]);
            c.w.draw(textElements[6]);
            c.w.draw(textElements[7]);


            bufferSprite.setTexture(c.w.getTexture(), true);

            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();

            // Check if the start keyword has been pressed
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
                // Pass to the second menu
                startPressed = true;
                // Stop the soundtrack of the main menu
                r.soundTracks[0]->stop();
                r.soundEffects[1]->stop();
                r.soundEffects[1]->play();
                state = PLAYER_MENU;
            }
            // Check if the space keyword has been pressed
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Space)) {
                // Pass to the second menu
                spacePressed = true;
                // Stop the soundtrack of the main menu
                r.soundTracks[0]->stop();
                r.soundEffects[1]->stop();
                r.soundEffects[1]->play();
                state = CREDITS;
            }
            // Check if the escape keyword has been pressed
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)){
                return EXIT;
            }
        }

        // Control if the pixel art is active and draw the interface with better quality
        if (c.enablePixelArt) {
            if (c.isDefaultScreen)
                c.window.setView(View(Vector2f(DEFAULT_WIDTH / 4.0f, DEFAULT_HEIGHT / 4.0f),
                                      Vector2f(DEFAULT_WIDTH / 2.0f, DEFAULT_HEIGHT / 2.0f)));
            else
                c.window.setView(View(Vector2f(SCREEN_HD_WIDTH / 4.0f, SCREEN_HD_HEIGHT / 4.0f),
                                      Vector2f(SCREEN_HD_WIDTH / 2.0f, SCREEN_HD_HEIGHT / 2.0f)));
            c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                       static_cast<unsigned int>(c.window.getView().getSize().y));
            c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);
        }

        // Wait until the sound has finished
        while (r.soundEffects[1]->getStatus() == SoundSource::Playing){
            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }
        }
        // Start the soundtrack of the player menu
        if (state == PLAYER_MENU){
            r.soundTracks[1]->play();
        }
        return state;
    }
    return EXIT;
}




/**
 * Load the configuration of the player menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadPlayerMenuConfiguration(const string path, Configuration& c){

    // Open the xml file of the player menu
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Local variable to store temporary the text content and the fonts of the texts
    string content, fontPath, backgroundTexture, colorKind;

    // Iterate to get the information of the player menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check it is the node that contains the information of the background
        if ((string)property->name() == "Background"){
            // Get the background image of the menu
            backgroundTexture = (string)property->value();
            c.playerMenuBackground.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the player menu
            for (xml_node<> *panelProp = property->first_node(); panelProp; panelProp = panelProp->next_sibling()){
                // Check it is the node that contains the information of the background of the panel
                if ((string)panelProp->name() == "Background"){
                    // Get the background image of the menu
                    backgroundTexture = (string)panelProp->value();
                    c.playerMenuPanelBack.loadFromFile(backgroundTexture);
                }
                // Check it is the node that contains the information of the color border of the panel
                else if ((string)panelProp->name() == "ColorBorder"){
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the player menu
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
                    c.colorBorderPanelPlayerMenu = Color(colorRed, colorGreen, colorBlue);
                }
            }
        }
        // Check if it is the node that stores the information of the main text of the player menu
        else if ((string)property->name() == "Title"){
            // Iterate to get the information of the title
            for (xml_node<> *titleProp = property->first_node(); titleProp; titleProp = titleProp->next_sibling()){
                // Get the red color channel
                if ((string)titleProp->name() == "Content"){
                    // Get the content of the title
                    content = (string)titleProp->value();
                    c.contentTitlePlayerMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontPlayerMenu.loadFromFile(fontPath);
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
                        c.colorTitleTextPlayerMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderPlayerMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
        // Check if it is the node that stores the information panel of the buttons
        else if ((string)property->name() == "DescriptionPanel"){
            // Iterate to get the information of the description panel
            for (xml_node<> *descriptionProp = property->first_node(); descriptionProp; descriptionProp = descriptionProp->next_sibling()){
                // Get the kind of color to process
                colorKind = (string)descriptionProp->name();
                // Get the border color of the panel
                int colorRed = 0, colorGreen = 0, colorBlue = 0;
                // Iterate to get the information of the player menu
                for (xml_node<> *colorChannel = descriptionProp->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
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
                if (colorKind == "ColorPanelInside"){
                    c.colorDescriptionPanelInsidePlayerMenu = Color(colorRed, colorGreen, colorBlue);
                }
                // Check if it is the color of the border
                else if (colorKind == "ColorPanelBorder"){
                    c.colorDescriptionPanelBorderPlayerMenu = Color(colorRed, colorGreen, colorBlue);
                }
            }
        }
         // Check if it is the node that the different buttons of the menu
        else if ((string)property->name() == "MenuButtons"){
            Color colorFont;
            // Iterate to get the information of the buttons of the player menu
            for (xml_node<> *buttonProp = property->first_node(); buttonProp; buttonProp = buttonProp->next_sibling()){
                // Get the font of the buttons
                if ((string)buttonProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)buttonProp->value();
                    c.fontMenuPlayerButtons.loadFromFile(fontPath);
                }
                // Get the color font of the buttons
                else if ((string)buttonProp->name() == "ColorFont"){
                    // Read the font from the file
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the player menu
                    for (xml_node<> *color = buttonProp->first_node(); color; color = color->next_sibling()){
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
                    c.colorFontMenuPlayerButtons = Color(colorRed, colorGreen, colorBlue);
                }
                // Get the information of the buttons
                else if ((string)buttonProp->name() == "Buttons"){
                    // Local variables to store the attributes of the buttons
                    string contentButton;
                    int buttonState = 0;
                    vector<Color> colorButtons;
                    Texture icon;
                    Sprite s;
                    int idButton = 0, posX, posY, widthButton, heightButton;
                    // Iterate to get the information of the buttons
                    for (xml_node<> *buttonNode = buttonProp->first_node(); buttonNode; buttonNode = buttonNode->next_sibling()){
                        // Iterate to get the information of the buttons
                        for (xml_node<> *button = buttonNode->first_node(); button; button = button->next_sibling()){
                            // Get the font of the buttons
                            if ((string)button->name() == "Content"){
                                // Read the font from the file
                                contentButton = (string)button->value();
                            }
                            // Get the state of the button
                            else if ((string)button->name() == "InitialState"){
                                // Read the font from the file
                                buttonState = stoi(button->value());
                            }
                            // Get the colors of the button
                            else if ((string)button->name() == "Colors"){
                                // Read the colors of the button
                                for (xml_node<> *colorButton = button->first_node(); colorButton; colorButton = colorButton->next_sibling()){
                                    // Get the border color of the panel
                                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                                    // Iterate to get the information of the player menu
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
                            // Control the image to display with the description
                            else if ((string)button->name() == "Image"){
                                icon.loadFromFile((string)button->value());
                                c.texturesIconPlayerMenu.push_back(icon);
                                Sprite s;
                                c.iconButtonsPlayerMenu.push_back(s);
                            }
                            else if ((string)button->name() == "Description"){
                                // Creation of the button and addition to the vector
                                posX = c.w.getSize().x / 2.f - 280.0f * c.screenScale;
                                posY = c.w.getSize().y / 2.f - (149.0f - idButton * 133.f) * c.screenScale;
                                widthButton = 200.0f * c.screenScale;
                                heightButton = 50.0f * c.screenScale;

                                // Creation of the button
                                Button b = Button(posX, posY, widthButton, heightButton, c.fontMenuPlayerButtons,
                                                  contentButton, colorButtons[0], colorButtons[1], c.colorFontMenuPlayerButtons,
                                                  buttonState, c.screenScale);

                                // Process the description text of the button
                                b.proccessDescription(button);
                                c.menuPlayerButtons.push_back(b);
                                idButton++;
                            }
                        }
                    }
                }
            }
        }
    }
    // The player menu has been read correctly
    c.playerMenuRead = true;
}



/**
 * Load the configuration of the player menu stored in its xml configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
State playerMenu(Configuration &c, SoundPlayer& r){

    // Prepare the screen to display the player menu with high quality
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));

    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Read the player menu if it has not been read
    if (!c.playerMenuRead){
        // Read the player menu xml configuration file
        string pathFile = "Data/Menus/PlayerMenu/Configuration/PlayerMenu.xml";
        loadPlayerMenuConfiguration(pathFile, c);
    }
    else {
        int numButtons = int(c.menuPlayerButtons.size());

        // Description of the button
        vector<string> descriptionButton;

        // Change the state of the first color
        Button b = Button(c.w.getSize().x / 2.f - 280.0f * c.screenScale, c.w.getSize().y / 2.f - 149.0f * c.screenScale,
                          200.0f * c.screenScale, 50.0f * c.screenScale, c.fontMenuPlayerButtons, c.menuPlayerButtons[0].getTextButton(),
                          c.menuPlayerButtons[0].getIdleColorButton(), c.menuPlayerButtons[0].getHoverColorButton(),
                          c.menuPlayerButtons[0].getFontColorButton(), 1, c.screenScale);

        // Get the description of the button
        descriptionButton = c.menuPlayerButtons[0].getDescriptionButton();
        b.setDescriptionButton(descriptionButton);

        c.menuPlayerButtons[0] = b;

        // Eliminate the buttons of the right column
        for (int i = 1; i < numButtons; i++){

            // Change the state of the first color
            Button b = Button(c.w.getSize().x / 2.f - 280.0f * c.screenScale, c.w.getSize().y / 2.f - (149.0f - i * 133.f) * c.screenScale,
                              200.0f * c.screenScale, 50.0f * c.screenScale, c.fontMenuPlayerButtons, c.menuPlayerButtons[i].getTextButton(),
                              c.menuPlayerButtons[i].getIdleColorButton(), c.menuPlayerButtons[i].getHoverColorButton(),
                              c.menuPlayerButtons[i].getFontColorButton(), 0, c.screenScale);

            // Get the description of the button
            descriptionButton = c.menuPlayerButtons[i].getDescriptionButton();
            b.setDescriptionButton(descriptionButton);

            c.menuPlayerButtons[i] = b;
        }
    }

    // Control if the start key is pressed or not
    bool startPressed = false;

    // Control if the escape key has been pressed
    bool escapePressed = false;

    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Control the option selected by the user
    int optionSelected = 0;

    // While start and backspace have not been pressed
    while (!startPressed && !escapePressed) {

        // Make the textures repeated
        c.playerMenuBackground.setRepeated(true);
        c.playerMenuPanelBack.setRepeated(true);

        // Global rectangle of the background
        IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
        Sprite sprite(c.playerMenuBackground, background);

        float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
        float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
        sprite.setScale(axis_x, axis_y);
        c.sPlayerMenuBackground = sprite;

        // Creation of the panel rectangle of the menu
        RectangleShape shape;
        shape.setPosition((c.w.getSize().x / 2.f) - 350.0f * c.screenScale, c.w.getSize().y / 2.f - 250.0f * c.screenScale);
        shape.setSize(sf::Vector2f(710.0f * c.screenScale, 500.0f * c.screenScale));
        shape.setOutlineColor(c.colorBorderPanelPlayerMenu);
        shape.setOutlineThickness(5.0f * c.screenScale);
        shape.setTexture(&c.playerMenuPanelBack, true);

        // Creation of the description panel of the buttons
        RectangleShape panelButton;
        panelButton.setPosition((c.w.getSize().x / 2.f) + 20.0f * c.screenScale, c.w.getSize().y / 2.f - 149.0f * c.screenScale);
        panelButton.setSize(sf::Vector2f(300.0f * c.screenScale, 314.0f * c.screenScale));
        panelButton.setFillColor(c.colorDescriptionPanelInsidePlayerMenu);
        panelButton.setOutlineColor(c.colorDescriptionPanelBorderPlayerMenu);
        panelButton.setOutlineThickness(3.0f * c.screenScale);

        // Main Text of the menu
        Text mainText;
        mainText.setString(c.contentTitlePlayerMenu);
        mainText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        mainText.setFont(c.fontPlayerMenu);
        mainText.setStyle(Text::Bold | Text::Underlined);
        mainText.setFillColor(c.colorTitleTextPlayerMenu);
        mainText.setOutlineColor(c.colorTitleBorderPlayerMenu);
        mainText.setOutlineThickness(5.0f * c.screenScale);
        mainText.setPosition((c.w.getSize().x / 2.f) - mainText.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f - 230.0f * c.screenScale);

        // Text description of the buttons
        Text descriptionText;
        descriptionText.setStyle(Text::Bold);
        descriptionText.setFillColor(c.colorFontMenuPlayerButtons);
        descriptionText.setCharacterSize(25 * c.screenScale);
        descriptionText.setFont(c.fontMenuPlayerButtons);

        // Until start and escape are not pressed
        while (!startPressed && !escapePressed) {

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)){
                if (e.type == Event::Closed){
                    return EXIT;
                }
            }

            // Check if the up or down cursor keys have been pressed or not
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Down)) {
                if (optionSelected != int(c.menuPlayerButtons.size() - 1)) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected++;
                    c.menuPlayerButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    c.menuPlayerButtons[optionSelected - 1].setButtonState(BUTTON_IDLE);
                }
            }
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Up)) {
                if (optionSelected != 0) {
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected--;
                    // Change the color appearance of both buttons
                    c.menuPlayerButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    c.menuPlayerButtons[optionSelected + 1].setButtonState(BUTTON_IDLE);
                }
            }


            c.w.draw(c.sPlayerMenuBackground);
            c.w.draw(shape);
            c.w.draw(panelButton);
            c.w.draw(mainText);

            // Show the buttons of the menu
            for (int i = 0; i < (int)c.menuPlayerButtons.size(); i++) {

                c.menuPlayerButtons.at(i).render(&c.w);

                // Draw the button description in the panel
                if (i == optionSelected){

                    int posXDescriptionOffset = panelButton.getPosition().x + 10;
                    int posYDescriptionOffset = panelButton.getPosition().y + 10;

                    // Draw the button description
                    // Display the description of the button
                    vector<string> wordsButton =  c.menuPlayerButtons.at(i).getDescriptionButton();

                    for (string s : wordsButton){
                        descriptionText.setString(s);
                        if (posXDescriptionOffset + descriptionText.getLocalBounds().width <= c.thresholdDescriptionX){
                            descriptionText.setPosition(posXDescriptionOffset, posYDescriptionOffset);
                            c.w.draw(descriptionText);
                            posXDescriptionOffset += descriptionText.getLocalBounds().width + 10;
                        }
                        else {
                            posXDescriptionOffset = panelButton.getPosition().x + 10;
                            posYDescriptionOffset += c.thresholdDescriptionY;
                            descriptionText.setPosition(posXDescriptionOffset, posYDescriptionOffset);
                            c.w.draw(descriptionText);
                            posXDescriptionOffset += descriptionText.getLocalBounds().width + 10;
                        }
                    }

                    // Display the icon of the button
                    c.iconButtonsPlayerMenu[i].setTexture(c.texturesIconPlayerMenu[i], true);
                    c.iconButtonsPlayerMenu[i].setScale(float(c.w.getSize().x) / DEFAULT_WIDTH, float(c.w.getSize().y) / DEFAULT_HEIGHT);
                    posXDescriptionOffset = panelButton.getPosition().x +
                                            (panelButton.getLocalBounds().width / 2.f) - (c.iconButtonsPlayerMenu[i].getLocalBounds().width / 2.f);
                    posYDescriptionOffset += c.thresholdDescriptionY * c.imageOffset;
                    c.iconButtonsPlayerMenu[i].setScale(Vector2f(c.w.getSize().x / DEFAULT_WIDTH, c.w.getSize().y / DEFAULT_HEIGHT));
                    c.iconButtonsPlayerMenu[i].setPosition(posXDescriptionOffset, posYDescriptionOffset * 1.05f);
                    c.w.draw(c.iconButtonsPlayerMenu[i]);
                }
            }

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
            sleep(milliseconds(120));

            // Check if start has been pressed
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
                startPressed = true;
                r.soundEffects[2]->stop();
                r.soundEffects[2]->play();
            }
            // Check if escape has been pressed
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {
                escapePressed = true;
                r.soundEffects[11]->stop();
                r.soundEffects[11]->play();
            }
        }
    }

    // Control the pixel art flag to create the view of the screen
    if (c.enablePixelArt) {
        if (c.isDefaultScreen){
            c.window.setView(View(Vector2f(DEFAULT_WIDTH / 4.0f, DEFAULT_HEIGHT / 4.0f),
                                  Vector2f(DEFAULT_WIDTH / 2.0f, DEFAULT_HEIGHT / 2.0f)));
        }
        else {
            c.window.setView(View(Vector2f(SCREEN_HD_WIDTH / 4.0f, SCREEN_HD_HEIGHT / 4.0f),
                                  Vector2f(SCREEN_HD_WIDTH / 2.0f, SCREEN_HD_HEIGHT / 2.0f)));
        }
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));
        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);
    }

    // Default option
    State status = PLAYER_MENU;

    // Check the option selected
    switch(optionSelected){
        case 0:
            // Single player modes
            status = GAME_MODES_MENU;
            break;
        case 1:
            // Multi player mode
            r.soundTracks[1]->stop();
            r.soundTracks[18]->play();
            status = TESTTING_NETWORK;
            break;
        case 2:
            // Options menu
            status = OPTIONS;
    }

    // Control the escape key
    if (escapePressed){
        r.soundTracks[1]->stop();
        r.soundTracks[0]->play();
        status = START;
    }

    return status;
}




/**
 * Load the configuration of the game modes menu stored in its xml configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadGameModesMenuConfiguration(const string path, Configuration& c){

    // Open the xml file of the game modes menu
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Local variable to store temporary the text content and the fonts of the texts
    string content, fontPath, backgroundTexture, colorKind;

    // Iterate to get the information of the player menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check it is the node that contains the information of the background
        if ((string)property->name() == "Background"){
            // Get the background image of the menu
            backgroundTexture = (string)property->value();
            c.gameModesMenuBackground.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the player menu
            for (xml_node<> *panelProp = property->first_node(); panelProp; panelProp = panelProp->next_sibling()){
                // Check it is the node that contains the information of the background of the panel
                if ((string)panelProp->name() == "Background"){
                    // Get the background image of the menu
                    backgroundTexture = (string)panelProp->value();
                    c.gameModesMenuPanelBack.loadFromFile(backgroundTexture);
                }
                // Check it is the node that contains the information of the color border of the panel
                else if ((string)panelProp->name() == "ColorBorder"){
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the player menu
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
                    c.colorBorderPanelGameModeMenu = Color(colorRed, colorGreen, colorBlue);
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
                    c.contentTitleGameModeMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontGameModeMenu.loadFromFile(fontPath);
                }
                // Get color text of the title
                else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                    // Get the kind of color to process
                    colorKind = (string)titleProp->name();
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the game modes menu
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
                        c.colorTitleTextGameModeMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderGameModeMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
        // Check if it is the node that stores the information panel of the buttons
        else if ((string)property->name() == "DescriptionPanel"){
            // Iterate to get the information of the description panel
            for (xml_node<> *descriptionProp = property->first_node(); descriptionProp; descriptionProp = descriptionProp->next_sibling()){
                // Get the kind of color to process
                colorKind = (string)descriptionProp->name();
                // Get the border color of the panel
                int colorRed = 0, colorGreen = 0, colorBlue = 0;
                // Iterate to get the information of the game modes menu
                for (xml_node<> *colorChannel = descriptionProp->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
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
                if (colorKind == "ColorPanelInside"){
                    c.colorDescriptionPanelInsideGameModeMenu = Color(colorRed, colorGreen, colorBlue);
                }
                // Check if it is the color of the border
                else if (colorKind == "ColorPanelBorder"){
                    c.colorDescriptionPanelBorderGameModeMenu = Color(colorRed, colorGreen, colorBlue);
                }
            }
        }
         // Check if it is the node that the different buttons of the menu
        else if ((string)property->name() == "MenuButtons"){
            // Iterate to get the information of the buttons of the game modes menu
            for (xml_node<> *buttonProp = property->first_node(); buttonProp; buttonProp = buttonProp->next_sibling()){
                // Get the font of the buttons
                if ((string)buttonProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)buttonProp->value();
                    c.fontMenuGameModeButtons.loadFromFile(fontPath);
                }
                // Get the color font of the buttons
                else if ((string)buttonProp->name() == "ColorFont"){
                    // Read the font from the file
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the player menu
                    for (xml_node<> *color = buttonProp->first_node(); color; color = color->next_sibling()){
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
                    c.colorFontMenuGameModesButtons = Color(colorRed, colorGreen, colorBlue);
                }
                // Get the information of the buttons
                else if ((string)buttonProp->name() == "Buttons"){
                    // Local variables to store the attributes of the buttons
                    string contentButton;
                    int buttonState = 0;
                    vector<Color> colorButtons;
                    Texture icon;
                    Sprite s;
                    int idButton = 0, posX, posY, widthButton, heightButton;
                    // Iterate to get the information of the buttons
                    for (xml_node<> *buttonNode = buttonProp->first_node(); buttonNode; buttonNode = buttonNode->next_sibling()){
                        // Iterate to get the information of the buttons
                        for (xml_node<> *button = buttonNode->first_node(); button; button = button->next_sibling()){
                            // Get the font of the buttons
                            if ((string)button->name() == "Content"){
                                // Read the font from the file
                                contentButton = (string)button->value();
                            }
                            // Get the state of the button
                            else if ((string)button->name() == "InitialState"){
                                // Read the font from the file
                                buttonState = stoi(button->value());
                            }
                            // Get the colors of the button
                            else if ((string)button->name() == "Colors"){
                                // Read the colors of the button
                                for (xml_node<> *colorButton = button->first_node(); colorButton; colorButton = colorButton->next_sibling()){
                                    // Get the border color of the panel
                                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                                    // Iterate to get the information of the game modes menu
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
                            else if ((string)button->name() == "Description"){
                                // Creation of the button and addition to the vector
                                // Creation of the button and addition to the vector
                                posX = c.w.getSize().x / 2.f - 280.0f * c.screenScale;
                                posY = c.w.getSize().y / 2.f - (149.0f - idButton * 75.f) * c.screenScale;
                                widthButton = 200.0f * c.screenScale;
                                heightButton = 40.0f * c.screenScale;

                                // Creation of the button
                                Button b = Button(posX, posY, widthButton, heightButton, c.fontGameModeMenu,
                                                  contentButton, colorButtons[0], colorButtons[1], c.colorFontMenuGameModesButtons,
                                                  buttonState, c.screenScale);

                                // Process the description text of the button
                                b.proccessDescription(button);
                                c.gameModeMenuButtons.push_back(b);
                                idButton++;
                            }
                        }
                    }
                }
            }
        }
    }
    // The game nodes menu has been read correctly
    c.gameModesMenuRead = true;
}



/**
 * Load the configuration of the game modes menu stored in its xml configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 * @param typeOfGame is the game mode selected by the player
 */
State gameModesMenu(Configuration &c, SoundPlayer& r, int& typeOfGame){

    // Prepare the screen to display the game modes menu
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));
    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Read the game modes menu if it has not been read
    if (!c.gameModesMenuRead){
        // Read the game modes menu xml configuration file
        string pathFile = "Data/Menus/GameModesMenu/Configuration/GameModesMenu.xml";
        loadGameModesMenuConfiguration(pathFile, c);
    }
    else {
        int numButtons = int(c.gameModeMenuButtons.size());

        // Description of the button
        vector<string> descriptionButton;

        // Change the state of the first color
        Button b = Button(c.w.getSize().x / 2.f - 280.0f * c.screenScale, c.w.getSize().y / 2.f - 149.0f * c.screenScale,
                          200.0f * c.screenScale, 40.0f * c.screenScale, c.fontMenuGameModeButtons, c.gameModeMenuButtons[0].getTextButton(),
                          c.gameModeMenuButtons[0].getIdleColorButton(), c.gameModeMenuButtons[0].getHoverColorButton(),
                          c.gameModeMenuButtons[0].getFontColorButton(), 1, c.screenScale);

        // Get the description of the button
        descriptionButton = c.gameModeMenuButtons[0].getDescriptionButton();
        b.setDescriptionButton(descriptionButton);

        c.gameModeMenuButtons[0] = b;

        // Eliminate the buttons of the right column
        for (int i = 1; i < numButtons; i++){
            // Change the state of the first color
            Button b = Button(c.w.getSize().x / 2.f - 280.0f * c.screenScale, c.w.getSize().y / 2.f - (149.0f - i * 75.f) * c.screenScale,
                              200.0f * c.screenScale, 40.0f * c.screenScale, c.fontMenuGameModeButtons, c.gameModeMenuButtons[i].getTextButton(),
                              c.gameModeMenuButtons[i].getIdleColorButton(), c.gameModeMenuButtons[i].getHoverColorButton(),
                              c.gameModeMenuButtons[i].getFontColorButton(), 0, c.screenScale);

            // Get the description of the button
            descriptionButton = c.gameModeMenuButtons[i].getDescriptionButton();
            b.setDescriptionButton(descriptionButton);

            c.gameModeMenuButtons[i] = b;
        }
    }

    // Control if the start key is pressed or not
    bool startPressed = false;

    // Control if the escape key is pressed or not
    bool escapePressed = false;

    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Game selected by the user
    int optionSelected;

    // While start and escape are not been pressed
    while (!startPressed && !escapePressed) {

        // Make the textures repeated
        c.gameModesMenuBackground.setRepeated(true);
        c.gameModesMenuPanelBack.setRepeated(true);

        // Global rectangle of the background
        IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
        Sprite sprite(c.gameModesMenuBackground, background);
        float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
        float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
        sprite.setScale(axis_x, axis_y);
        c.sGameModesBackground = sprite;

        // Creation of the panel rectangle of the menu
        RectangleShape shape;
        shape.setPosition((c.w.getSize().x / 2.f) - 350.0f * c.screenScale, c.w.getSize().y / 2.f - 250.0f * c.screenScale);
        shape.setSize(sf::Vector2f(710.0f * c.screenScale, 500.0f * c.screenScale));
        shape.setOutlineColor(c.colorBorderPanelGameModeMenu);
        shape.setOutlineThickness(5.0f * c.screenScale);
        shape.setTexture(&c.gameModesMenuPanelBack, true);

        // Creation of the description panel of the buttons
        RectangleShape panelButton;
        panelButton.setPosition((c.w.getSize().x / 2.f) + 20.0f * c.screenScale, c.w.getSize().y / 2.f - 149.0f * c.screenScale);
        panelButton.setSize(sf::Vector2f(300.0f * c.screenScale, 339.0f * c.screenScale));
        panelButton.setFillColor(c.colorDescriptionPanelInsideGameModeMenu);
        panelButton.setOutlineColor(c.colorDescriptionPanelBorderGameModeMenu);
        panelButton.setOutlineThickness(3.0f * c.screenScale);

        // Main Text of the menu
        Text mainText;
        mainText.setString(c.contentTitleGameModeMenu);
        mainText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        mainText.setFont(c.fontGameModeMenu);
        mainText.setStyle(Text::Bold | Text::Underlined);
        mainText.setFillColor(c.colorTitleTextGameModeMenu);
        mainText.setOutlineColor(c.colorTitleBorderGameModeMenu);
        mainText.setOutlineThickness(5.0f * c.screenScale);
        mainText.setPosition((c.w.getSize().x / 2.f) - mainText.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f - 230.0f * c.screenScale);

        // Text description of the buttons
        Text descriptionText;
        descriptionText.setStyle(Text::Bold);
        descriptionText.setFillColor(c.colorFontMenuGameModesButtons);
        descriptionText.setCharacterSize(25 * c.screenScale);
        descriptionText.setFont(c.fontMenuGameModeButtons);

        // All buttons of the menu have been created correctly

        // Control the option selected by the user
        optionSelected = 0;

        // Until the start keyword or escape keyword are not pressed
        while (!startPressed && !escapePressed) {

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)){
                if (e.type == Event::Closed){
                    return EXIT;
                }
            }

            // Check if the up or down cursor keys have been pressed or not
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Down)) {
                if (optionSelected != int(c.gameModeMenuButtons.size() - 1)) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected++;
                    c.gameModeMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    c.gameModeMenuButtons[optionSelected - 1].setButtonState(BUTTON_IDLE);
                }
            }
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Up)) {
                if (optionSelected != 0) {
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected--;
                    // Change the color appearance of both buttons
                    c.gameModeMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    c.gameModeMenuButtons[optionSelected + 1].setButtonState(BUTTON_IDLE);
                }
            }
            // Draw the elements of the menu
            c.w.draw(c.sGameModesBackground);
            c.w.draw(shape);
            c.w.draw(panelButton);
            c.w.draw(mainText);

            // Show the buttons of the menu
            for (int i = 0; i < (int)c.gameModeMenuButtons.size(); i++) {

                c.gameModeMenuButtons.at(i).render(&c.w);

                // Draw the button description in the panel
                if (i == optionSelected){

                    int posXDescriptionOffset = panelButton.getPosition().x + 10;
                    int posYDescriptionOffset = panelButton.getPosition().y + 10;

                    // Draw the button description
                    // Display the description of the button
                    vector<string> wordsButton =  c.gameModeMenuButtons.at(i).getDescriptionButton();

                    for (string s : wordsButton){
                        descriptionText.setString(s);
                        if (posXDescriptionOffset + descriptionText.getLocalBounds().width <= c.thresholdDescriptionX){
                            descriptionText.setPosition(posXDescriptionOffset, posYDescriptionOffset);
                            c.w.draw(descriptionText);
                            posXDescriptionOffset += descriptionText.getLocalBounds().width + 10;
                        }
                        else {
                            posXDescriptionOffset = panelButton.getPosition().x + 10;
                            posYDescriptionOffset += c.thresholdDescriptionY * 1.15f;
                            descriptionText.setPosition(posXDescriptionOffset, posYDescriptionOffset);
                            c.w.draw(descriptionText);
                            posXDescriptionOffset += descriptionText.getLocalBounds().width + 10;
                        }
                    }
                }
            }

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
            sleep(milliseconds(120));

            // Check if start key has been pressed
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
                startPressed = true;
                r.soundEffects[2]->stop();
                r.soundEffects[2]->play();
            }
            // Check if escape key has been pressed
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {
                escapePressed = true;
                r.soundEffects[11]->stop();
                r.soundEffects[11]->play();
            }
        }
    }

    // Control the escape key has been pressed
    if (escapePressed){
        return PLAYER_MENU;
    }
    // Store the game selected by the player
    typeOfGame = optionSelected;

    // Control the pixel art flag to set the view of the screen
    if (c.enablePixelArt) {
        if (c.isDefaultScreen)
            c.window.setView(View(Vector2f(DEFAULT_WIDTH / 4.0f, DEFAULT_HEIGHT / 4.0f),
                                  Vector2f(DEFAULT_WIDTH / 2.0f, DEFAULT_HEIGHT / 2.0f)));
        else
            c.window.setView(View(Vector2f(SCREEN_HD_WIDTH / 4.0f, SCREEN_HD_HEIGHT / 4.0f),
                                  Vector2f(SCREEN_HD_WIDTH / 2.0f, SCREEN_HD_HEIGHT / 2.0f)));
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));
        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);
    }

    if (typeOfGame == 2){
        // Stop the soundtrack of the menu
        return RIVAL_TYPE_MENU;
    }
    else if (typeOfGame == 0) {
        return RIVAL_TYPE_MENU;
    }
    else {
        r.soundTracks[1]->stop();
        // Vehicle selection menu
        return VEHICLE_SELECTION;
    }
}



/**
 * Load the configuration of the sound menu stored in its xml configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadSoundMenuConfiguration(const string path, Configuration& c){

    // Open the xml file of the sound menu
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Local variable to store temporary the text content and the fonts of the texts
    string content, fontPath, backgroundTexture, colorKind;

    // Iterate to get the information of the sound menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check it is the node that contains the information of the background
        if ((string)property->name() == "Background"){
            // Get the background image of the menu
            backgroundTexture = (string)property->value();
            c.soundMenuBackground.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the sound menu
            for (xml_node<> *panelProp = property->first_node(); panelProp; panelProp = panelProp->next_sibling()){
                // Check it is the node that contains the information of the background of the panel
                if ((string)panelProp->name() == "Background"){
                    // Get the background image of the menu
                    backgroundTexture = (string)panelProp->value();
                    c.soundMenuPanelBack.loadFromFile(backgroundTexture);
                }
                // Check it is the node that contains the information of the color border of the panel
                else if ((string)panelProp->name() == "ColorBorder"){
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the sound menu
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
                    c.colorBorderPanelSoundMenu = Color(colorRed, colorGreen, colorBlue);
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
                    c.contentTitleSoundMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontSoundMenu.loadFromFile(fontPath);
                }
                // Get color text of the title
                else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                    // Get the kind of color to process
                    colorKind = (string)titleProp->name();
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the sound menu
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
                        c.colorTitleTextSoundMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderSoundMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
        // Check if it is the node that the different buttons of the menu
        else if ((string)property->name() == "MenuButtons"){
            // Iterate to get the information of the buttons of the sound menu
            for (xml_node<> *buttonProp = property->first_node(); buttonProp; buttonProp = buttonProp->next_sibling()){
                // Get the font of the buttons
                if ((string)buttonProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)buttonProp->value();
                    c.fontMenuSoundButtons.loadFromFile(fontPath);
                }
                // Get the color font of the buttons
                else if ((string)buttonProp->name() == "ColorFont"){
                    // Read the font from the file
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the sound menu
                    for (xml_node<> *color = buttonProp->first_node(); color; color = color->next_sibling()){
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
                    c.colorFontMenuSoundButtons = Color(colorRed, colorGreen, colorBlue);
                }
                // Get the information of the buttons
                else if ((string)buttonProp->name() == "Buttons"){
                    // Local variables to store the attributes of the buttons
                    string contentButton;
                    int buttonState = 0;
                    vector<Color> colorButtons;
                    Texture icon;
                    Sprite s;
                    int idButton = 0, posX, posY, widthButton, heightButton;
                    // Iterate to get the information of the buttons
                    for (xml_node<> *buttonNode = buttonProp->first_node(); buttonNode; buttonNode = buttonNode->next_sibling()){
                        // Iterate to get the information of the buttons
                        for (xml_node<> *button = buttonNode->first_node(); button; button = button->next_sibling()){
                            // Get the font of the buttons
                            if ((string)button->name() == "Content"){
                                // Read the font from the file
                                contentButton = (string)button->value();
                            }
                            // Get the state of the button
                            else if ((string)button->name() == "InitialState"){
                                // Read the font from the file
                                buttonState = stoi(button->value());
                            }
                            // Get the colors of the button
                            else if ((string)button->name() == "Colors"){
                                // Read the colors of the button
                                for (xml_node<> *colorButton = button->first_node(); colorButton; colorButton = colorButton->next_sibling()){
                                    // Get the border color of the panel
                                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                                    // Iterate to get the information of the sound menu
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
                                // Creation of the button and addition to the vector
                                posX = c.w.getSize().x / 2.f - 270.0f * c.screenScale;
                                posY = c.w.getSize().y / 2.f - (70.0f - idButton * 70.0f) * c.screenScale;
                                widthButton = 200.0f * c.screenScale;
                                heightButton = 40.0f * c.screenScale;

                                // Creation of the button
                                Button b = Button(posX, posY, widthButton, heightButton, c.fontMenuOptionsButtons,
                                                  contentButton, colorButtons[0], colorButtons[1], c.colorFontMenuSoundButtons,
                                                  buttonState, c.screenScale);

                                // Process the description text of the button
                                c.soundMenuButtons.push_back(b);
                                idButton++;
                            }
                        }
                    }
                }
            }
        }
    }
    // The sound menu has been read correctly
    c.soundMenuRead = true;
}



/**
 * Load the configuration of the sound menu stored in its xml configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
State soundMenu(Configuration &c, SoundPlayer& r, const bool &inGame) {

    // Clean the console window
    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Clean the console window
    c.w.clear(Color(0, 0, 0));
    bufferSprite.setTexture(c.w.getTexture(), true);
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Prepare the window to display the sound menu
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));
    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Read the sound menu if it has not been read
    if (!c.soundMenuRead){
        // Read the sound menu xml configuration file
        string pathFile = "Data/Menus/SoundMenu/Configuration/SoundMenu.xml";
        loadSoundMenuConfiguration(pathFile, c);
    }
    else {
        int numButtons = int(c.soundMenuButtons.size()) / 2;

        // Eliminate the buttons of the right column
        for (int i = 0; i < numButtons; i++){
            // Delete the last one
            c.soundMenuButtons.pop_back();
        }
        // Change the state of the first color
        Button b = Button(c.w.getSize().x / 2.f - 270.0f * c.screenScale, c.w.getSize().y / 2.f - 70.0f * c.screenScale,
                          200.0f * c.screenScale, 40.0f * c.screenScale, c.fontMenuOptionsButtons, c.soundMenuButtons[0].getTextButton(),
                          c.soundMenuButtons[0].getIdleColorButton(), c.soundMenuButtons[0].getHoverColorButton(),
                          c.soundMenuButtons[0].getFontColorButton(), 1, c.screenScale);

        c.soundMenuButtons[0] = b;

        // Eliminate the buttons of the right column
        for (int i = 1; i < int(c.soundMenuButtons.size()); i++){
            // Change the state of the first color
            Button b = Button(c.w.getSize().x / 2.f - 270.0f * c.screenScale, c.w.getSize().y / 2.f - (70.0f - i * 70.f) * c.screenScale,
                              200.0f * c.screenScale, 40.0f * c.screenScale, c.fontMenuOptionsButtons, c.soundMenuButtons[i].getTextButton(),
                              c.soundMenuButtons[i].getIdleColorButton(), c.soundMenuButtons[i].getHoverColorButton(),
                              c.soundMenuButtons[i].getFontColorButton(), 0, c.screenScale);

            c.soundMenuButtons[i] = b;
        }
    }

    // Make repeated the background textures of the sound menu
    c.soundMenuBackground.setRepeated(true);
    c.soundMenuPanelBack.setRepeated(true);

    IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
    Sprite sprite(c.soundMenuBackground, background);
    float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
    float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
    sprite.setScale(axis_x, axis_y);
    c.sdMenuBackground = sprite;

    RectangleShape shape;
    shape.setPosition((c.w.getSize().x / 2.f) - 300.0f * c.screenScale, c.w.getSize().y / 2.f - 250.0f * c.screenScale);
    shape.setSize(sf::Vector2f(610.0f * c.screenScale, 500.0f * c.screenScale));
    shape.setOutlineColor(c.colorBorderPanelSoundMenu);
    shape.setOutlineThickness(5.0f * c.screenScale);
    shape.setTexture(&c.soundMenuPanelBack, true);

    // Main Text of the menu
    Text soundText;
    soundText.setString(c.contentTitleSoundMenu);
    soundText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    soundText.setFont(c.fontSoundMenu);
    soundText.setStyle(Text::Bold | Text::Underlined);
    soundText.setFillColor(c.colorTitleTextSoundMenu);
    soundText.setOutlineColor(c.colorTitleBorderSoundMenu);
    soundText.setOutlineThickness(5.0f * c.screenScale);
    soundText.setPosition((c.w.getSize().x / 2.f) - soundText.getLocalBounds().width / 2.f,
                           c.w.getSize().y / 2.f - 220.0f * c.screenScale);

    // Option configurations
    c.soundMenuButtons.emplace_back(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                             c.w.getSize().y / 2.f - 70.0f * c.screenScale, 200.0f * c.screenScale,
                             40.0f * c.screenScale, c.fontMenuSoundButtons,
                             to_string(r.volumeMusic), c.soundMenuButtons[0].getIdleColorButton(), c.soundMenuButtons[0].getHoverColorButton(),
                             c.soundMenuButtons[0].getFontColorButton(), 1, c.screenScale);


    c.soundMenuButtons.emplace_back(c.w.getSize().x / 2.f + 80.0f * c.screenScale, c.w.getSize().y / 2.f,
                             200.0f * c.screenScale, 40.0f * c.screenScale, c.fontMenuSoundButtons,
                             to_string(r.volumeEffects), c.soundMenuButtons[1].getIdleColorButton(), c.soundMenuButtons[1].getHoverColorButton(),
                             c.soundMenuButtons[1].getFontColorButton(), 0, c.screenScale);

    // Control if the escape key is pressed or not
    bool escapePressed = false;

    // Control the option selected by the user
    int optionSelected = 0;

    // Until the escape keyword is not pressed
    while (!escapePressed) {
        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return EXIT;
            }
        }

        if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Down)) {
            if (optionSelected != int(c.soundMenuButtons.size() - 1) / 2) {
                // Change the color appearance of both buttons
                r.soundEffects[0]->play();
                optionSelected++;
                c.soundMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                c.soundMenuButtons[optionSelected - 1].setButtonState(BUTTON_IDLE);
                c.soundMenuButtons[optionSelected + 2].setButtonState(BUTTON_HOVER);
                c.soundMenuButtons[optionSelected + 1].setButtonState(BUTTON_IDLE);
            }
        }
        else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Up)) {
            if (optionSelected != 0) {
                // Change the color appearance of both buttons
                r.soundEffects[0]->play();
                optionSelected--;
                c.soundMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                c.soundMenuButtons[optionSelected + 1].setButtonState(BUTTON_IDLE);
                c.soundMenuButtons[optionSelected + 2].setButtonState(BUTTON_HOVER);
                c.soundMenuButtons[optionSelected + 3].setButtonState(BUTTON_IDLE);
            }
        }

        if (optionSelected == 0) {
            // Volume music

            // Check if left or right cursor keys have been pressed or not
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Left)) {
                // Check the volume before descend
                if (r.volumeMusic != 0) {
                    r.volumeMusic--;
                    // Iterate the soundtracks and reduce the level volume
                    for (int i = 0; i <= 22; i++) {
                        r.soundTracks[i]->setVolume(float(r.volumeMusic));
                        if (i == 14) {
                            // Listen the changes in the options soundtrack
                            r.soundTracks[i]->pause();
                            r.soundTracks[i]->play();
                        }
                    }
                    // Store the changes
                    c.soundMenuButtons[optionSelected + 2].setTextButton((to_string(r.volumeMusic)));
                    c.changeAnyParameter = true;
                }
            }
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Right)) {
                // Check the volume before ascend
                if (r.volumeMusic != 100) {
                    r.volumeMusic++;
                    // Iterate the soundtracks and ascend the level volume
                    for (int i = 0; i <= 22; i++) {
                        r.soundTracks[i]->setVolume(float(r.volumeMusic));
                        if (i == 14) {
                            // Listen the changes in the options soundtrack
                            r.soundTracks[i]->pause();
                            r.soundTracks[i]->play();
                        }
                    }
                    // Store the changes
                    c.soundMenuButtons[optionSelected + 2].setTextButton((to_string(r.volumeMusic)));
                    c.changeAnyParameter = true;
                }
            }
        }
        else {
            // Volume effects
            // Check if left or right cursor keys have been pressed or not
            if (c.window.hasFocus() && c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Left)) {
                if (r.volumeEffects != 0) {
                    // Check the volume before descend
                    r.volumeEffects--;
                    // Iterate the sound effects and ascend the level volume
                    for (int i = 0; i <= 127; i++) {
                        r.soundEffects[i]->setVolume(float(r.volumeEffects));
                    }
                    // Test the changes and store then
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    c.soundMenuButtons[optionSelected + 2].setTextButton((to_string(r.volumeEffects)));
                    c.changeAnyParameter = true;
                }
            }
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Right)) {
                // Check the volume before ascend
                if (r.volumeEffects != 100) {
                    r.volumeEffects++;
                    // Iterate the effects and ascend the level volume
                    for (int i = 0; i <= 127; i++) {
                        r.soundEffects[i]->setVolume(float(r.volumeEffects));
                    }
                    // Test the changes and store then
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    c.soundMenuButtons[optionSelected + 2].setTextButton((to_string(r.volumeEffects)));
                    c.changeAnyParameter = true;
                }
            }
        }
        // Display the elements in the screen
        c.w.draw(c.sdMenuBackground);
        c.w.draw(shape);
        c.w.draw(soundText);

        // Show the buttons of the menu
        for (auto &menuButton : c.soundMenuButtons) {
            menuButton.render(&c.w);
        }

        bufferSprite.setTexture(c.w.getTexture(), true);
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();
        sleep(milliseconds(120));
        r.soundEffects[0]->stop();

        // Check if escape key has been pressed
        if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {
            // Change the controllers of the car
            escapePressed = true;
            c.modifiedConfig = true;
            r.soundEffects[2]->stop();
            r.soundEffects[2]->play();
        }
    }
    c.comeFromSound = true;
    return OPTIONS;
}



/**
 * Load the configuration of the options menu stored in its xml configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadOptionsMenuConfiguration(const string path, Configuration& c){

    // Open the xml file of the options menu
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Local variable to store temporary the text content and the fonts of the texts
    string content, fontPath, backgroundTexture, colorKind;

    // Iterate to get the information of the options menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check it is the node that contains the information of the background
        if ((string)property->name() == "Background"){
            // Get the background image of the menu
            backgroundTexture = (string)property->value();
            c.optionsMenuBackground.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the options menu
            for (xml_node<> *panelProp = property->first_node(); panelProp; panelProp = panelProp->next_sibling()){
                // Check it is the node that contains the information of the background of the panel
                if ((string)panelProp->name() == "Background"){
                    // Get the background image of the menu
                    backgroundTexture = (string)panelProp->value();
                    c.optionsMenuPanelBack.loadFromFile(backgroundTexture);
                }
                // Check it is the node that contains the information of the color border of the panel
                else if ((string)panelProp->name() == "ColorBorder"){
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the options menu
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
                    c.colorBorderPanelOptionsMenu = Color(colorRed, colorGreen, colorBlue);
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
                    c.contentTitleOptionsMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontOptionsMenu.loadFromFile(fontPath);
                }
                // Get color text of the title
                else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                    // Get the kind of color to process
                    colorKind = (string)titleProp->name();
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the options menu
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
                        c.colorTitleTextOptionsMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderOptionsMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
        // Check if it is the node that the different buttons of the menu
        else if ((string)property->name() == "MenuButtons"){
            // Iterate to get the information of the buttons of the options menu
            for (xml_node<> *buttonProp = property->first_node(); buttonProp; buttonProp = buttonProp->next_sibling()){
                // Get the font of the buttons
                if ((string)buttonProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)buttonProp->value();
                    c.fontMenuOptionsButtons.loadFromFile(fontPath);
                }
                // Get the color font of the buttons
                else if ((string)buttonProp->name() == "ColorFont"){
                    // Read the font from the file
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the options menu
                    for (xml_node<> *color = buttonProp->first_node(); color; color = color->next_sibling()){
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
                    c.colorFontMenuOptionsButtons = Color(colorRed, colorGreen, colorBlue);
                }
                // Get the information of the buttons
                else if ((string)buttonProp->name() == "Buttons"){
                    // Local variables to store the attributes of the buttons
                    string contentButton;
                    int buttonState = 0;
                    vector<Color> colorButtons;
                    Texture icon;
                    Sprite s;
                    int idButton = 0, posX, posY, widthButton, heightButton;
                    // Iterate to get the information of the buttons
                    for (xml_node<> *buttonNode = buttonProp->first_node(); buttonNode; buttonNode = buttonNode->next_sibling()){
                        // Iterate to get the information of the buttons
                        for (xml_node<> *button = buttonNode->first_node(); button; button = button->next_sibling()){
                            // Get the font of the buttons
                            if ((string)button->name() == "Content"){
                                // Read the font from the file
                                contentButton = (string)button->value();
                            }
                            // Get the state of the button
                            else if ((string)button->name() == "InitialState"){
                                // Read the font from the file
                                buttonState = stoi(button->value());
                            }
                            // Get the colors of the button
                            else if ((string)button->name() == "Colors"){
                                // Read the colors of the button
                                for (xml_node<> *colorButton = button->first_node(); colorButton; colorButton = colorButton->next_sibling()){
                                    // Get the border color of the panel
                                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                                    // Iterate to get the information of the options menu
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
                                // Creation of the button and addition to the vector
                                posX = c.w.getSize().x / 2.f - 270.0f * c.screenScale;
                                posY = c.w.getSize().y / 2.f - (100.0f - idButton * 70.0f) * c.screenScale;
                                widthButton = 200.0f * c.screenScale;
                                heightButton = 40.0f * c.screenScale;

                                // Creation of the button
                                Button b = Button(posX, posY, widthButton, heightButton, c.fontMenuOptionsButtons,
                                                  contentButton, colorButtons[0], colorButtons[1], c.colorFontMenuOptionsButtons,
                                                  buttonState, c.screenScale);

                                // Process the description text of the button
                                c.optionsMenuButtons.push_back(b);
                                idButton++;
                            }
                        }
                    }
                }
            }
        }
    }
    // The options menu has been read correctly
    c.optionsMenuRead = true;
}



/**
 * Shows the options menu of the game
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 * @param inGame controls if the player was in game before enter in the options menu
 * @return
 */
State optionsMenu(Configuration &c, SoundPlayer& r, const bool &inGame){

    // Stop the soundtrack of the player menu
    r.soundTracks[1]->stop();

    // Prepare the window to display the options menu
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));
    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Read the options menu if it has not been read
    if (!c.optionsMenuRead){
        // Read the options menu xml configuration file
        string pathFile = "Data/Menus/OptionsMenu/Configuration/OptionsMenu.xml";
        loadOptionsMenuConfiguration(pathFile, c);
    }
    else {
        int numButtons = int(c.optionsMenuButtons.size()) / 2;
        // Eliminate the buttons of the right column
        for (int i = 0; i < numButtons; i++){
            // Delete the last one
            c.optionsMenuButtons.pop_back();
        }

        // Change the state of the first color
        Button b = Button(c.w.getSize().x / 2.f - 270.0f * c.screenScale, c.w.getSize().y / 2.f - 100.0f * c.screenScale,
                          200.0f * c.screenScale, 40.0f * c.screenScale, c.fontMenuOptionsButtons, c.optionsMenuButtons[0].getTextButton(),
                          c.optionsMenuButtons[0].getIdleColorButton(), c.optionsMenuButtons[0].getHoverColorButton(),
                          c.optionsMenuButtons[0].getFontColorButton(), 1, c.screenScale);

        c.optionsMenuButtons[0] = b;

        // Eliminate the buttons of the right column
        for (int i = 1; i < int(c.optionsMenuButtons.size()); i++){
            // Change the state of the first color
            Button b = Button(c.w.getSize().x / 2.f - 270.0f * c.screenScale, c.w.getSize().y / 2.f - (100.0f - i * 70.f) * c.screenScale,
                              200.0f * c.screenScale, 40.0f * c.screenScale, c.fontMenuOptionsButtons, c.optionsMenuButtons[i].getTextButton(),
                              c.optionsMenuButtons[i].getIdleColorButton(), c.optionsMenuButtons[i].getHoverColorButton(),
                              c.optionsMenuButtons[i].getFontColorButton(), 0, c.screenScale);

            c.optionsMenuButtons[i] = b;
        }
    }

    // Control if the escape key is pressed or not
    bool escapePressed = false;

    // Control the option selected by the user
    int optionSelected = 0;

    // While the escape key is not pressed
    while (!escapePressed) {

        // Clean the console window
        c.w.clear(Color(0, 0, 0));
        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

        // Reproduce the options soundtrack
        r.soundTracks[14]->play();

        // Loading the background texture
        c.optionsMenuBackground.setRepeated(true);
        c.optionsMenuPanelBack.setRepeated(true);

        IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
        Sprite sprite(c.optionsMenuBackground, background);
        float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
        float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
        sprite.setScale(axis_x, axis_y);
        c.optMenuBackground = sprite;

        // Panel of the options menu
        RectangleShape shape;
        shape.setPosition((c.w.getSize().x / 2.f) - 350.0f * c.screenScale, c.w.getSize().y / 2.f - 198.0f * c.screenScale);
        shape.setSize(sf::Vector2f(710.0f * c.screenScale, 400.0f * c.screenScale));
        shape.setOutlineColor(c.colorBorderPanelOptionsMenu);
        shape.setOutlineThickness(5.0f * c.screenScale);
        shape.setTexture(&c.optionsMenuPanelBack, true);

        // Main Text of the menu
        Text optionsText;
        optionsText.setString(c.contentTitleOptionsMenu);
        optionsText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        optionsText.setFont(c.fontOptionsMenu);
        optionsText.setStyle(Text::Bold | Text::Underlined);
        optionsText.setFillColor(c.colorTitleTextOptionsMenu);
        optionsText.setOutlineColor(c.colorTitleBorderOptionsMenu);
        optionsText.setOutlineThickness(5.0f * c.screenScale);
        optionsText.setPosition((c.w.getSize().x / 2.f) - optionsText.getLocalBounds().width / 2.f,
                                 c.w.getSize().y / 2.f - 180.0f * c.screenScale);

        // Option configurations
        string difficulty;
        switch (c.level) {
            case EASY:
                difficulty = "Easy";
                break;
            case HARD:
                difficulty = "Hard";
                break;
            default:
                difficulty = "Normal";
                break;
        }

        // Possible contents of the menu buttons text
        const string submenu = "Menu", access = "Press Enter", saved = "Saved!";

        // Menu buttons located of the right of the menu

        c.optionsMenuButtons.emplace_back(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                          c.w.getSize().y / 2.f - 100.0f * c.screenScale, 200.0f * c.screenScale,
                                          40.0f * c.screenScale, c.fontMenuPlayerButtons,
                                          difficulty, c.optionsMenuButtons[0].getIdleColorButton(),
                                          c.optionsMenuButtons[0].getHoverColorButton(),
                                          c.optionsMenuButtons[0].getFontColorButton(), 1, c.screenScale);

        c.optionsMenuButtons.emplace_back(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                          c.w.getSize().y / 2.f - 30.0f * c.screenScale, 200.0f * c.screenScale,
                                          40.0f * c.screenScale, c.fontMenuPlayerButtons,
                                          submenu, c.optionsMenuButtons[2].getIdleColorButton(),
                                          c.optionsMenuButtons[2].getHoverColorButton(),
                                          c.optionsMenuButtons[2].getFontColorButton(), 0, c.screenScale);

        c.optionsMenuButtons.emplace_back(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                          c.w.getSize().y / 2.f + 40.0f * c.screenScale, 200.0f * c.screenScale,
                                          40.0f * c.screenScale, c.fontMenuPlayerButtons,
                                          submenu, c.optionsMenuButtons[3].getIdleColorButton(),
                                          c.optionsMenuButtons[3].getHoverColorButton(),
                                          c.optionsMenuButtons[3].getFontColorButton(), 0, c.screenScale);

        c.optionsMenuButtons.emplace_back(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                          c.w.getSize().y / 2.f + 110.0f * c.screenScale, 200.0f * c.screenScale,
                                          40.0f * c.screenScale, c.fontMenuPlayerButtons,
                                          submenu, c.optionsMenuButtons[4].getIdleColorButton(),
                                          c.optionsMenuButtons[4].getHoverColorButton(),
                                          c.optionsMenuButtons[4].getFontColorButton(), 0, c.screenScale);

        // Until the escape keyword is not pressed
        while (!escapePressed) {

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)){
                if (e.type == Event::Closed){
                    return EXIT;
                }
            }

            // Check if the up or down cursor keys have been pressed or not
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Down)) {
                if (optionSelected != int(c.optionsMenuButtons.size() - 1) / 2) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected++;
                    c.optionsMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    c.optionsMenuButtons[optionSelected - 1].setButtonState(BUTTON_IDLE);
                    c.optionsMenuButtons[optionSelected + 4].setButtonState(BUTTON_HOVER);
                    c.optionsMenuButtons[optionSelected + 3].setButtonState(BUTTON_IDLE);
                }
            }
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Up)) {
                if (optionSelected != 0) {
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected--;
                    // Change the color appearance of both buttons
                    c.optionsMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    c.optionsMenuButtons[optionSelected + 1].setButtonState(BUTTON_IDLE);
                    c.optionsMenuButtons[optionSelected + 4].setButtonState(BUTTON_HOVER);
                    c.optionsMenuButtons[optionSelected + 5].setButtonState(BUTTON_IDLE);
                }
            }


            // Modify the option parameter if it's necessary
            switch (optionSelected) {
                // Change the level of difficulty
                case 0:
                    // Check if left or right cursor keys have been pressed or not
                    if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Left)) {
                        if (c.level != EASY) {

                            r.soundEffects[0]->stop();
                            r.soundEffects[0]->play();

                            if (c.level == NORMAL) {
                                c.level = EASY;
                                c.optionsMenuButtons[optionSelected + 4].setTextButton("Easy");
                            }
                            else if (c.level == HARD) {
                                c.level = NORMAL;
                                c.optionsMenuButtons[optionSelected + 4].setTextButton("Normal");
                            }
                            c.changeAnyParameter = true;
                        }
                    }
                    else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Right)) {
                        if (c.level != HARD) {

                            r.soundEffects[0]->stop();
                            r.soundEffects[0]->play();

                            // Change the difficult level
                            if (c.level == EASY) {
                                c.level = NORMAL;
                                c.optionsMenuButtons[optionSelected + 4].setTextButton("Normal");
                            }
                            else if (c.level == NORMAL) {
                                c.level = HARD;
                                c.optionsMenuButtons[optionSelected + 4].setTextButton("Hard");
                            }
                            c.changeAnyParameter = true;
                        }
                    }
                    c.optionsMenuButtons[optionSelected + 5].setTextButton(submenu);
                    break;
                // Change the volume of the soundtracks and the sound effects
                case 1:
                    // Change the volume of the game
                    c.optionsMenuButtons[optionSelected + 4].setTextButton(access);

                    // Check if left or right cursor keys have been pressed or not
                    if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
                        r.soundEffects[1]->stop();
                        r.soundEffects[1]->play();
                        State status = soundMenu(c, r, inGame);
                        if (status == EXIT) {
                            return status;
                        }
                        if (c.modifiedConfig) {
                            c.optionsMenuButtons[optionSelected + 4].setTextButton(saved);
                        }
                    }

                    c.optionsMenuButtons[optionSelected + 5].setTextButton(submenu);
                    break;
                // Change the graphics of the game
                case 2:
                    c.optionsMenuButtons[optionSelected + 4].setTextButton(access);

                    // Check if left or right cursor keys have been pressed or not
                    if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
                        r.soundEffects[1]->stop();
                        r.soundEffects[1]->play();
                        State status = c.graphicsMenu(r);
                        if (status == EXIT) {
                            return status;
                        }
                        if (c.modifiedConfig) {

                            float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
                            float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
                            sprite.setScale(axis_x, axis_y);
                            c.optMenuBackground = sprite;

                            shape.setPosition((c.w.getSize().x / 2.f) - 350.0f * c.screenScale, c.w.getSize().y / 2.f - 250.0f * c.screenScale);
                            shape.setSize(sf::Vector2f(710.0f * c.screenScale, 500.0f * c.screenScale));
                            shape.setOutlineColor(c.colorBorderPanelOptionsMenu);
                            shape.setOutlineThickness(5.0f * c.screenScale);
                            shape.setTexture(&c.optionsMenuPanelBack, true);

                            optionsText.setString(c.contentTitleOptionsMenu);
                            optionsText.setFont(c.fontOptionsMenu);
                            optionsText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
                            optionsText.setStyle(Text::Bold | Text::Underlined);
                            optionsText.setFillColor(c.colorTitleTextOptionsMenu);
                            optionsText.setOutlineColor(c.colorTitleBorderOptionsMenu);
                            optionsText.setOutlineThickness(5.0f * c.screenScale);
                            optionsText.setPosition((c.w.getSize().x / 2.f) - optionsText.getLocalBounds().width / 2.f,
                                                     c.w.getSize().y / 2.f - 180.0f * c.screenScale);

                            c.optionsMenuButtons[optionSelected + 4].setTextButton(saved);

                            shape.setPosition((c.w.getSize().x / 2.f) - 350.0f * c.screenScale,
                                              c.w.getSize().y / 2.f - 250.0f * c.screenScale);
                            shape.setSize(sf::Vector2f(710.0f * c.screenScale, 500.0f * c.screenScale));

                            // Local variables to store the attributes of the buttons
                            string contentButton;
                            vector<Color> colorButtons;
                            Texture icon;
                            Sprite s;
                            int i, idButton = 0, posX = 0, posY = 0, widthButton = 0, heightButton = 0;
                            Button b;

                            // Add the buttons with the new resolution
                            for (i = 0; i <= ((int)c.optionsMenuButtons.size() / 2) - 2; i++){
                                posX = c.w.getSize().x / 2.f - 270.0f * c.screenScale;
                                posY = c.w.getSize().y / 2.f - (100.0f - idButton * 70.0f) * c.screenScale;
                                widthButton = 200.0f * c.screenScale;
                                heightButton = 40.0f * c.screenScale;

                                // Create a new button with the new resolution properties
                                b = Button(posX, posY, widthButton, heightButton, c.fontMenuPlayerButtons,
                                           c.optionsMenuButtons[i].getTextButton(), c.optionsMenuButtons[i].getIdleColorButton(),
                                           c.optionsMenuButtons[i].getHoverColorButton(), c.optionsMenuButtons[i].getFontColorButton(),
                                           0, c.screenScale);

                                // Replace the all button by the new one
                                c.optionsMenuButtons[i] = b;
                                idButton++;

                            }

                            i--;
                            // Create a new button with the new resolution properties
                            b = Button(posX, posY, widthButton, heightButton, c.fontMenuPlayerButtons,
                                       c.optionsMenuButtons[i].getTextButton(), c.optionsMenuButtons[i].getIdleColorButton(),
                                       c.optionsMenuButtons[i].getHoverColorButton(), c.optionsMenuButtons[i].getFontColorButton(),
                                       1, c.screenScale);

                            // Replace the all button by the new one
                            c.optionsMenuButtons[i] = b;

                            i++;

                            posX = c.w.getSize().x / 2.f - 270.0f * c.screenScale;
                            posY = c.w.getSize().y / 2.f - (100.0f - idButton * 70.0f) * c.screenScale;
                            widthButton = 200.0f * c.screenScale;
                            heightButton = 40.0f * c.screenScale;

                            b = Button(posX, posY, widthButton, heightButton, c.fontMenuPlayerButtons,
                                           c.optionsMenuButtons[i].getTextButton(), c.optionsMenuButtons[i].getIdleColorButton(),
                                           c.optionsMenuButtons[i].getHoverColorButton(),
                                           c.optionsMenuButtons[i].getFontColorButton(), 0, c.screenScale);

                            // Replace the all button by the new one
                            c.optionsMenuButtons[i] = b;

                            i++;
                            b = Button(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                       c.w.getSize().y / 2.f - 100.0f * c.screenScale,
                                       200.0f * c.screenScale,
                                       40.0f * c.screenScale, c.fontMenuPlayerButtons,
                                       difficulty, c.optionsMenuButtons[i - 4].getIdleColorButton(),
                                       c.optionsMenuButtons[i - 4].getHoverColorButton(),
                                       c.optionsMenuButtons[i - 4].getFontColorButton(), 0, c.screenScale);
                            c.optionsMenuButtons[i] = b;

                            i++;
                            b = Button(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                       c.w.getSize().y / 2.f - 30.0f * c.screenScale,
                                       200.0f * c.screenScale,
                                       40.0f * c.screenScale, c.fontMenuPlayerButtons,
                                       submenu, c.optionsMenuButtons[i - 4].getIdleColorButton(),
                                       c.optionsMenuButtons[i - 4].getHoverColorButton(),
                                       c.optionsMenuButtons[i - 4].getFontColorButton(), 0, c.screenScale);
                            c.optionsMenuButtons[i] = b;

                            i++;
                            b = Button(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                       c.w.getSize().y / 2.f + 40.0f * c.screenScale,
                                       200.0f * c.screenScale,
                                       40.0f * c.screenScale, c.fontMenuPlayerButtons,
                                       submenu, c.optionsMenuButtons[i - 4].getIdleColorButton(),
                                       c.optionsMenuButtons[i - 4].getHoverColorButton(),
                                       c.optionsMenuButtons[i - 4].getFontColorButton(), 1, c.screenScale);
                            c.optionsMenuButtons[i] = b;

                            i++;
                            b = Button(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                       c.w.getSize().y / 2.f + 110.0f * c.screenScale,
                                       200.0f * c.screenScale,
                                       40.0f * c.screenScale, c.fontMenuPlayerButtons,
                                       submenu, c.optionsMenuButtons[i - 4].getIdleColorButton(),
                                       c.optionsMenuButtons[i - 4].getHoverColorButton(),
                                       c.optionsMenuButtons[i - 4].getFontColorButton(), 0, c.screenScale);
                            c.optionsMenuButtons[i] = b;


                            // Resize all the buttons of the menus
                            idButton = 0;

                            for (i = 0; i < int(c.menuPlayerButtons.size() - 1); i++){
                                // Creation of the button and addition to the vector
                                // Creation of the button and addition to the vector
                                posX = c.w.getSize().x / 2.f - 280.0f * c.screenScale;
                                posY = c.w.getSize().y / 2.f - (149.0f - idButton * 133.f) * c.screenScale;
                                widthButton = 200.0f * c.screenScale;
                                heightButton = 50.0f * c.screenScale;

                                // Create a new button with the new resolution properties
                                Button b = Button(posX, posY, widthButton, heightButton, c.fontMenuPlayerButtons,
                                                  c.menuPlayerButtons[i].getTextButton(), c.menuPlayerButtons[i].getIdleColorButton(),
                                                  c.menuPlayerButtons[i].getHoverColorButton(),
                                                  c.menuPlayerButtons[i].getFontColorButton(), 0, c.screenScale);

                                b.setDescriptionButton(c.menuPlayerButtons[i].getDescriptionButton());

                                // Replace the all button by the new one
                                c.menuPlayerButtons[i] = b;
                                idButton++;
                            }

                            // Creation of the button and addition to the vector
                            // Creation of the button and addition to the vector
                            posX = c.w.getSize().x / 2.f - 280.0f * c.screenScale;
                            posY = c.w.getSize().y / 2.f - (149.0f - idButton * 133.f) * c.screenScale;
                            widthButton = 200.0f * c.screenScale;
                            heightButton = 50.0f * c.screenScale;

                            // Create a new button with the new resolution properties
                            b = Button(posX, posY, widthButton, heightButton, c.fontMenuPlayerButtons,
                                       c.menuPlayerButtons[i].getTextButton(), c.menuPlayerButtons[i].getIdleColorButton(),
                                       c.menuPlayerButtons[i].getHoverColorButton(),
                                       c.menuPlayerButtons[i].getFontColorButton(), 1, c.screenScale);

                            b.setDescriptionButton(c.menuPlayerButtons[i].getDescriptionButton());

                            // Replace the all button by the new one
                            c.menuPlayerButtons[i] = b;

                            if (!c.gameModesMenuRead){
                                loadGameModesMenuConfiguration("Data/Menus/GameModesMenu/Configuration/GameModesMenu.xml", c);
                            }

                            idButton = 0;
                            posX = c.w.getSize().x / 2.f - 280.0f * c.screenScale;
                            posY = c.w.getSize().y / 2.f - (149.0f - idButton * 62.f) * c.screenScale;
                            widthButton = 200.0f * c.screenScale;
                            heightButton = 30.0f * c.screenScale;


                            b = Button(posX, posY, widthButton, heightButton, c.fontMenuPlayerButtons,
                                       c.gameModeMenuButtons[0].getTextButton(), c.gameModeMenuButtons[0].getIdleColorButton(),
                                       c.gameModeMenuButtons[0].getHoverColorButton(),
                                       c.gameModeMenuButtons[0].getFontColorButton(), 1, c.screenScale);

                            b.setDescriptionButton(c.gameModeMenuButtons[0].getDescriptionButton());

                            // Replace the all button by the new one
                            c.gameModeMenuButtons[0] = b;
                            idButton++;

                            // Resize all the buttons of the menus
                            for (i = 1; i < int(c.gameModeMenuButtons.size()); i++){
                                // Creation of the button and addition to the vector
                                posX = c.w.getSize().x / 2.f - 280.0f * c.screenScale;
                                posY = c.w.getSize().y / 2.f - (149.0f - idButton * 62.f) * c.screenScale;
                                widthButton = 200.0f * c.screenScale;
                                heightButton = 30.0f * c.screenScale;

                                // Create a new button with the new resolution properties
                                Button b = Button(posX, posY, widthButton, heightButton, c.fontMenuPlayerButtons,
                                                  c.gameModeMenuButtons[i].getTextButton(), c.gameModeMenuButtons[i].getIdleColorButton(),
                                                  c.gameModeMenuButtons[i].getHoverColorButton(),
                                                  c.gameModeMenuButtons[i].getFontColorButton(), 0, c.screenScale);

                                b.setDescriptionButton(c.gameModeMenuButtons[i].getDescriptionButton());

                                c.gameModeMenuButtons[i] = b;
                                idButton++;
                            }
                        }
                    }

                    c.optionsMenuButtons[optionSelected + 3].setTextButton(submenu);
                    c.optionsMenuButtons[optionSelected + 5].setTextButton(submenu);
                    break;
                // Change the game controllers
                case 3:
                    c.optionsMenuButtons[optionSelected + 4].setTextButton(access);

                    // Check if left or right cursor keys have been pressed or not
                    if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
                        // Change the controllers of the car
                        r.soundEffects[1]->stop();
                        r.soundEffects[1]->play();
                        State status = vehicleControllersMenu(c, r);
                        if (status == EXIT) {
                            return status;
                        }
                        if (c.modifiedConfig) {
                            c.optionsMenuButtons[optionSelected + 4].setTextButton(saved);
                        }
                    }

                    c.optionsMenuButtons[optionSelected + 3].setTextButton(submenu);
            }

            // Draw the elements of the menu
            c.w.draw(sprite);
            c.w.draw(shape);
            c.w.draw(optionsText);

            // Show the buttons of the menu
            for (auto &menuButton : c.optionsMenuButtons) {
                menuButton.render(&c.w);
            }

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
            sleep(milliseconds(120));
            r.soundEffects[0]->stop();

            // Check if the escape key has been pressed
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {
                // Change the controllers of the car
                escapePressed = true;
                r.soundEffects[2]->stop();
                r.soundEffects[2]->play();
            }
        }
        r.soundTracks[14]->stop();

        // Check the pixel art to construct the view of the screen
        if (c.enablePixelArt) {
            if (c.isDefaultScreen)
                c.window.setView(View(Vector2f(DEFAULT_WIDTH / 4.0f, DEFAULT_HEIGHT / 4.0f),
                                      Vector2f(DEFAULT_WIDTH / 2.0f, DEFAULT_HEIGHT / 2.0f)));
            else
                c.window.setView(View(Vector2f(SCREEN_HD_WIDTH / 4.0f, SCREEN_HD_HEIGHT / 4.0f),
                                      Vector2f(SCREEN_HD_WIDTH / 2.0f, SCREEN_HD_HEIGHT / 2.0f)));
            c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                       static_cast<unsigned int>(c.window.getView().getSize().y));
            c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);
        }
    }
    // The options have been stored
    c.comeFromOptions = true;

    // Update the xml configuration file
    if (c.changeAnyParameter){
        const string path = "Data/Settings/Configuration.xml";

        KeywordMapper kM = KeywordMapper();

        // Get the keyword to control the turn to the left
        int index = kM.lookForKeyBoardId(c.leftKey);
        string controlLeft = kM.mapperIdKeyWord[index];

        // Get the keyword to control the turn to the right
        index = kM.lookForKeyBoardId(c.rightKey);
        string controlRight = kM.mapperIdKeyWord[index];

        // Get the keyword to control the acceleration
        index = kM.lookForKeyBoardId(c.accelerateKey);
        string controlAccelerate = kM.mapperIdKeyWord[index];

        // Get the keyword to control the brake
        index = kM.lookForKeyBoardId(c.brakeKey);
        string controlBrake = kM.mapperIdKeyWord[index];

        // Get the keyword to control the change of soundtrack
        index = kM.lookForKeyBoardId(c.soundtrackKey);
        string controlSoundtrack = kM.mapperIdKeyWord[index];

        // Update the file with the new configuration
        updateGameConfiguration(path, c.level, r.volumeMusic, r.volumeEffects, c.enablePixelArt, c.fullScreen,
                                c.resolutions[c.resIndex].first, c.resolutions[c.resIndex].second, controlLeft, controlRight,
                                controlAccelerate, controlBrake, controlSoundtrack);

        // Make possible more modifications
        c.changeAnyParameter = false;
    }

    if (inGame) {
        // Return to the game
        return PLAY_GAME;
    }
    else {
        // Reproduce the soundtrack of the player menu
        r.soundTracks[1]->play();
        return playerMenu(c, r);
    }
}



/**
 * Load the configuration of the vehicle controllers menu stored in its xml configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadVehicleControllersMenuConfiguration(const string path, Configuration& c){

    // Open the xml file of the controllers menu
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Local variable to store temporary the text content and the fonts of the texts
    string content, fontPath, backgroundTexture, colorKind;

    // Iterate to get the information of the controllers menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check it is the node that contains the information of the background
        if ((string)property->name() == "Background"){
            // Get the background image of the menu
            backgroundTexture = (string)property->value();
            c.vehicleControllersMenuBackground.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the controllers menu
            for (xml_node<> *panelProp = property->first_node(); panelProp; panelProp = panelProp->next_sibling()){
                // Check it is the node that contains the information of the background of the panel
                if ((string)panelProp->name() == "Background"){
                    // Get the background image of the menu
                    backgroundTexture = (string)panelProp->value();
                    c.vehicleControllersMenuPanelBack.loadFromFile(backgroundTexture);
                }
                // Check it is the node that contains the information of the color border of the panel
                else if ((string)panelProp->name() == "ColorBorder"){
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the controllers menu
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
                    c.colorBorderPanelVehicleControllersMenu = Color(colorRed, colorGreen, colorBlue);
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
                    c.contentTitleVehicleControllersMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontVehicleControllersMenu.loadFromFile(fontPath);
                }
                // Get color text of the title
                else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                    // Get the kind of color to process
                    colorKind = (string)titleProp->name();
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the controllers menu
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
                        c.colorTitleTextVehicleControllersMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderVehicleControllersMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
        // Check if it is the node that the different buttons of the menu
        else if ((string)property->name() == "MenuButtons"){
            // Iterate to get the information of the buttons of the controllers menu
            for (xml_node<> *buttonProp = property->first_node(); buttonProp; buttonProp = buttonProp->next_sibling()){
                // Get the font of the buttons
                if ((string)buttonProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)buttonProp->value();
                    c.fontMenuVehicleControllersButtons.loadFromFile(fontPath);
                }
                // Get the color font of the buttons
                else if ((string)buttonProp->name() == "ColorFont"){
                    // Read the font from the file
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the controllers menu
                    for (xml_node<> *color = buttonProp->first_node(); color; color = color->next_sibling()){
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
                    c.colorFontVehicleControllersMenu = Color(colorRed, colorGreen, colorBlue);
                }
                // Get the information of the buttons
                else if ((string)buttonProp->name() == "Buttons"){
                    // Local variables to store the attributes of the buttons
                    string contentButton;
                    int buttonState = 0;
                    vector<Color> colorButtons;
                    Texture icon;
                    Sprite s;
                    int idButton = 0, posX, posY, widthButton, heightButton;
                    // Iterate to get the information of the buttons
                    for (xml_node<> *buttonNode = buttonProp->first_node(); buttonNode; buttonNode = buttonNode->next_sibling()){
                        // Iterate to get the information of the buttons
                        for (xml_node<> *button = buttonNode->first_node(); button; button = button->next_sibling()){
                            // Get the font of the buttons
                            if ((string)button->name() == "Content"){
                                // Read the font from the file
                                contentButton = (string)button->value();
                            }
                            // Get the state of the button
                            else if ((string)button->name() == "InitialState"){
                                // Read the font from the file
                                buttonState = stoi(button->value());
                            }
                            // Get the colors of the button
                            else if ((string)button->name() == "Colors"){
                                // Read the colors of the button
                                for (xml_node<> *colorButton = button->first_node(); colorButton; colorButton = colorButton->next_sibling()){
                                    // Get the border color of the panel
                                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                                    // Iterate to get the information of the controllers menu
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
                                // Creation of the button and addition to the vector
                                posX = c.w.getSize().x / 2.f - 270.0f * c.screenScale;
                                posY = c.w.getSize().y / 2.f - (85.0f - idButton * 70.0f) * c.screenScale;
                                widthButton = 260.0f * c.screenScale;
                                heightButton = 30.0f * c.screenScale;

                                // Creation of the button
                                Button b = Button(posX, posY, widthButton, heightButton, c.fontMenuOptionsButtons,
                                                  contentButton, colorButtons[0], colorButtons[1], c.colorFontVehicleControllersMenu,
                                                  buttonState, c.screenScale);

                                // Process the description text of the button
                                c.vehicleControllersMenuButtons.push_back(b);
                                idButton++;
                            }
                        }
                    }
                }
            }
        }
    }
    // The controllers menu has been read correctly
    c.vehicleControllersMenuRead = true;
}



/**
 * Shows the vehicle controllers menu of the game
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 */
State vehicleControllersMenu(Configuration &c, SoundPlayer& r){

    // Clean the console window
    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    KeywordMapper kM = KeywordMapper();

    // Check if the xml configuration of the menu has been read
    if (!c.vehicleControllersMenuRead){
        // Read the vehicle controllers menu xml configuration file
        string pathFile = "Data/Menus/VehicleControllersMenu/Configuration/VehicleControllersMenu.xml";
        loadVehicleControllersMenuConfiguration(pathFile, c);
    }
    else {
        int numButtons = int(c.vehicleControllersMenuButtons.size()) / 2;
        // Eliminate the buttons of the right column
        for (int i = 0; i < numButtons; i++){
            // Delete the last one
            c.vehicleControllersMenuButtons.pop_back();
        }
        // Change the state of the first color
        Button b = Button(c.w.getSize().x / 2.f - 270.0f * c.screenScale, c.w.getSize().y / 2.f - 85.0f * c.screenScale,
                          260.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenuOptionsButtons, c.vehicleControllersMenuButtons[0].getTextButton(),
                          c.vehicleControllersMenuButtons[0].getIdleColorButton(), c.vehicleControllersMenuButtons[0].getHoverColorButton(),
                          c.vehicleControllersMenuButtons[0].getFontColorButton(), 1, c.screenScale);

        c.vehicleControllersMenuButtons[0] = b;

        // Eliminate the buttons of the right column
        for (int i = 1; i < int(c.vehicleControllersMenuButtons.size()); i++){
            // Change the state of the first color
            Button b = Button(c.w.getSize().x / 2.f - 270.0f * c.screenScale, c.w.getSize().y / 2.f - (85.0f - i * 70.f) * c.screenScale,
                              260.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenuOptionsButtons,
                              c.vehicleControllersMenuButtons[i].getTextButton(), c.vehicleControllersMenuButtons[i].getIdleColorButton(),
                              c.vehicleControllersMenuButtons[i].getHoverColorButton(),
                              c.vehicleControllersMenuButtons[i].getFontColorButton(), 0, c.screenScale);

            c.vehicleControllersMenuButtons[i] = b;
        }
    }

    // Clean the console window
    c.w.clear(Color(0, 0, 0));
    bufferSprite.setTexture(c.w.getTexture(), true);
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    c.vehicleControllersMenuBackground.setRepeated(true);
    c.vehicleControllersMenuPanelBack.setRepeated(true);

    IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
    Sprite sprite(c.vehicleControllersMenuBackground, background);
    float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
    float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
    sprite.setScale(axis_x, axis_y);
    c.vehControllersMenuBackground = sprite;

    RectangleShape shape;
    shape.setPosition((c.w.getSize().x / 2.f) - 300.0f * c.screenScale, c.w.getSize().y / 2.f - 240.0f * c.screenScale);
    shape.setSize(sf::Vector2f(610.0f * c.screenScale, 480.0f * c.screenScale));
    shape.setOutlineColor(c.colorBorderPanelVehicleControllersMenu);
    shape.setOutlineThickness(5.0f * c.screenScale);
    shape.setTexture(&c.vehicleControllersMenuPanelBack, true);

    // Main Text of the menu
    Text controllersText;
    controllersText.setString(c.contentTitleVehicleControllersMenu);
    controllersText.setPosition(c.w.getSize().x / 2.f - 160.0f * c.screenScale, c.w.getSize().y / 2.f - 240.0f * c.screenScale);
    controllersText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    controllersText.setFont(c.fontVehicleControllersMenu);
    controllersText.setStyle(Text::Bold | Text::Underlined);
    controllersText.setFillColor(c.colorTitleTextVehicleControllersMenu);
    controllersText.setOutlineColor(c.colorTitleBorderVehicleControllersMenu);
    controllersText.setOutlineThickness(5.0f * c.screenScale);
    controllersText.setPosition((c.w.getSize().x / 2.f) - controllersText.getLocalBounds().width / 2.f,
                                 c.w.getSize().y / 2.f - 210.0f * c.screenScale);

    // Informative indjcators about how to change a controller
    Text info1;
    info1.setString("Hold down Space to select a controller");
    info1.setFillColor(Color(10, 201, 235));
    info1.setOutlineColor(Color(3, 39, 8));
    info1.setOutlineThickness(3.0f * c.screenScale);
    info1.setCharacterSize(static_cast<unsigned int>(int(25.0f * c.screenScale)));
    info1.setStyle(Text::Bold);
    info1.setFont(c.fontMenuOptionsButtons);
    info1.setPosition(c.w.getSize().x / 2.f - info1.getLocalBounds().width / 2.f, c.w.getSize().y / 2.f - 160.0f * c.screenScale);
    c.w.draw(info1);

    Text info2;
    info2.setString("Then press a key to change its configuration");
    info2.setFillColor(Color(10, 201, 235));
    info2.setOutlineColor(Color(3, 39, 8));
    info2.setCharacterSize(static_cast<unsigned int>(int(25.0f * c.screenScale)));
    info2.setOutlineThickness(3.0f * c.screenScale);
    info2.setStyle(Text::Bold);
    info2.setFont(c.fontMenuOptionsButtons);
    info2.setPosition(c.w.getSize().x / 2.f - info2.getLocalBounds().width / 2.f, c.w.getSize().y / 2.f - 130.0f * c.screenScale);
    c.w.draw(info2);

    // Option configurations

    // Buttons with the current controllers
    int code;
    code = kM.mapperCodeKeyWord[c.leftKey];
    c.vehicleControllersMenuButtons.emplace_back(c.w.getSize().x / 2.f + 20.0f * c.screenScale,
                                                 c.w.getSize().y / 2.f - 85.0f * c.screenScale, 260.0f * c.screenScale,
                                                 30.0f * c.screenScale, c.fontMenuOptionsButtons,
                                                 kM.mapperIdKeyWord[code], c.vehicleControllersMenuButtons[0].getIdleColorButton(),
                                                 c.vehicleControllersMenuButtons[0].getHoverColorButton(),
                                                 c.vehicleControllersMenuButtons[0].getFontColorButton(), 1, c.screenScale);

    code = kM.mapperCodeKeyWord[c.rightKey];
    c.vehicleControllersMenuButtons.emplace_back(c.w.getSize().x / 2.f + 20.0f * c.screenScale,
                                                 c.w.getSize().y / 2.f - 15.f * c.screenScale, 260.0f * c.screenScale, 30.0f * c.screenScale,
                                                 c.fontMenuOptionsButtons, kM.mapperIdKeyWord[code], c.vehicleControllersMenuButtons[1].getIdleColorButton(),
                                                 c.vehicleControllersMenuButtons[1].getHoverColorButton(),
                                                 c.vehicleControllersMenuButtons[1].getFontColorButton(), 0, c.screenScale);

    code = kM.mapperCodeKeyWord[c.accelerateKey];
    c.vehicleControllersMenuButtons.emplace_back(c.w.getSize().x / 2.f + 20.0f * c.screenScale, c.w.getSize().y / 2.f + 55.0f * c.screenScale,
                                                 260.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenuOptionsButtons, kM.mapperIdKeyWord[code],
                                                 c.vehicleControllersMenuButtons[2].getIdleColorButton(),
                                                 c.vehicleControllersMenuButtons[2].getHoverColorButton(),
                                                 c.vehicleControllersMenuButtons[2].getFontColorButton(), 0, c.screenScale);

    code = kM.mapperCodeKeyWord[c.brakeKey];
    c.vehicleControllersMenuButtons.emplace_back(c.w.getSize().x / 2.f + 20.0f * c.screenScale, c.w.getSize().y / 2.f + 125.0f * c.screenScale,
                                                 260.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenuOptionsButtons, kM.mapperIdKeyWord[code],
                                                 c.vehicleControllersMenuButtons[3].getIdleColorButton(),
                                                 c.vehicleControllersMenuButtons[3].getHoverColorButton(),
                                                 c.vehicleControllersMenuButtons[3].getFontColorButton(), 0, c.screenScale);

    code = kM.mapperCodeKeyWord[c.soundtrackKey];
    c.vehicleControllersMenuButtons.emplace_back(c.w.getSize().x / 2.f + 20.0f * c.screenScale, c.w.getSize().y / 2.f + 195.0f * c.screenScale,
                                                 260.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenuOptionsButtons, kM.mapperIdKeyWord[code],
                                                 c.vehicleControllersMenuButtons[4].getIdleColorButton(),
                                                 c.vehicleControllersMenuButtons[4].getHoverColorButton(),
                                                 c.vehicleControllersMenuButtons[4].getFontColorButton(), 0, c.screenScale);


    // Control if the escape key is pressed or not
    bool escapePressed = false;

    // Control the option selected by the user
    int optionSelected = 0;

    // Until the escape keyword is not pressed
    while (!escapePressed) {

        // Draw the elements of the menu
        c.w.draw(c.vehControllersMenuBackground);
        c.w.draw(shape);
        c.w.draw(controllersText);
        c.w.draw(info1);
        c.w.draw(info2);

        // Show the buttons of the menu
        for (auto &menuButton : c.vehicleControllersMenuButtons) {
            menuButton.render(&c.w);
        }

        bufferSprite.setTexture(c.w.getTexture(), true);
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();
        sleep(milliseconds(120));
        r.soundEffects[0]->stop();

        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return EXIT;
            }
        }
        // Check if up or down cursor keys have been pressed
        if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Down)) {
            if (optionSelected != int(c.vehicleControllersMenuButtons.size() - 1) / 2) {
                // Change the color appearance of both buttons
                r.soundEffects[0]->play();
                optionSelected++;
                c.vehicleControllersMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                c.vehicleControllersMenuButtons[optionSelected - 1].setButtonState(BUTTON_IDLE);
                c.vehicleControllersMenuButtons[optionSelected + 5].setButtonState(BUTTON_HOVER);
                c.vehicleControllersMenuButtons[optionSelected + 4].setButtonState(BUTTON_IDLE);
            }
        }
        else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Up)) {
            if (optionSelected != 0) {
                // Change the color appearance of both buttons
                r.soundEffects[0]->play();
                optionSelected--;
                c.vehicleControllersMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                c.vehicleControllersMenuButtons[optionSelected + 1].setButtonState(BUTTON_IDLE);
                c.vehicleControllersMenuButtons[optionSelected + 5].setButtonState(BUTTON_HOVER);
                c.vehicleControllersMenuButtons[optionSelected + 6].setButtonState(BUTTON_IDLE);
            }
        }
        // Ignore space and enter keywords
        while (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Space) && !Keyboard::isKeyPressed(Keyboard::Enter)) {
            // Check if any keyword has been pressed or not
            c.window.waitEvent(e);
            if (e.type == Event::KeyPressed && e.key.code != -1 && e.key.code != Keyboard::Enter &&
                e.key.code != Keyboard::Space) {
                // Modify the option parameter if it's necessary
                switch (optionSelected) {
                    case 0:
                        // Check if the new controller is already selected
                        if (kM.mapperCodeKeyWord[e.key.code] == c.rightKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.accelerateKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.brakeKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.soundtrackKey) {
                            r.soundEffects[3]->stop();
                            r.soundEffects[3]->play();
                        }
                        else {
                            // Change the controller
                            c.vehicleControllersMenuButtons[optionSelected + 5].setTextButton(kM.mapperIdKeyWord[e.key.code]);
                            c.leftKey = kM.mapperCodeKeyWord[e.key.code];
                            r.soundEffects[1]->stop();
                            r.soundEffects[1]->play();
                            c.changeAnyParameter = true;
                        }
                        break;
                    case 1:
                        // Check if the new controller is already selected
                        if (kM.mapperCodeKeyWord[e.key.code] == c.leftKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.accelerateKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.brakeKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.soundtrackKey) {
                            r.soundEffects[3]->stop();
                            r.soundEffects[3]->play();
                        }
                        else {
                            // Change the controller
                            c.vehicleControllersMenuButtons[optionSelected + 5].setTextButton(kM.mapperIdKeyWord[e.key.code]);
                            c.rightKey = kM.mapperCodeKeyWord[e.key.code];
                            r.soundEffects[1]->stop();
                            r.soundEffects[1]->play();
                            c.changeAnyParameter = true;
                        }
                        break;
                    case 2:
                        // Check if the new controller is already selected
                        if (kM.mapperCodeKeyWord[e.key.code] == c.leftKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.rightKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.brakeKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.soundtrackKey) {
                            r.soundEffects[3]->stop();
                            r.soundEffects[3]->play();
                        }
                        else {
                            // Change the controller
                            c.vehicleControllersMenuButtons[optionSelected + 5].setTextButton(kM.mapperIdKeyWord[e.key.code]);
                            c.accelerateKey = kM.mapperCodeKeyWord[e.key.code];
                            r.soundEffects[1]->stop();
                            r.soundEffects[1]->play();
                            c.changeAnyParameter = true;
                        }
                        break;
                    case 3:
                        // Check if the new controller is already selected
                        if (kM.mapperCodeKeyWord[e.key.code] == c.leftKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.rightKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.accelerateKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.soundtrackKey) {
                            r.soundEffects[3]->stop();
                            r.soundEffects[3]->play();
                        }
                        else {
                            // Change the controller
                            c.vehicleControllersMenuButtons[optionSelected + 5].setTextButton(kM.mapperIdKeyWord[e.key.code]);
                            c.brakeKey = kM.mapperCodeKeyWord[e.key.code];
                            r.soundEffects[1]->stop();
                            r.soundEffects[1]->play();
                            c.changeAnyParameter = true;
                        }
                        break;
                    case 4:
                        // Check if the new controller is already selected
                        if (kM.mapperCodeKeyWord[e.key.code] == c.leftKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.rightKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.accelerateKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.brakeKey) {
                            r.soundEffects[3]->stop();
                            r.soundEffects[3]->play();
                        }
                        else {
                            // Change the controller
                            c.vehicleControllersMenuButtons[optionSelected + 5].setTextButton(kM.mapperIdKeyWord[e.key.code]);
                            c.soundtrackKey = kM.mapperCodeKeyWord[e.key.code];
                            r.soundEffects[1]->stop();
                            r.soundEffects[1]->play();
                            c.changeAnyParameter = true;
                        }
                }
            }
        }
        // Check if the escape key has been pressed
        if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {
            // Change the controllers of the car
            escapePressed = true;
            c.modifiedConfig = true;
            r.soundEffects[2]->stop();
            r.soundEffects[2]->play();
        }
    }
    return OPTIONS;
}



/**
 * Shows the ranking menu with best seven players of the Out Run mode
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 * @param minutes is the number of minutes that the game has lasted
 * @param decs is the number of seconds that the game has lasted
 * @param cents_Second is the number of hundredths of second that the game has lasted
 * @param typeOfGame is the game mode selected by the player
 * @return
 */
State rankingMenu(Configuration &c, SoundPlayer& r, const unsigned long scorePlayerGame, const int minutes, const int secs,
                  const int cents_Second, const int typeOfGame)
{
    // Prepare the screen to display the ranking menu
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));
    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    r.soundEffects[6]->stop();

    // Clean the console window
    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Keyword detector
    KeywordMapper kM = KeywordMapper();

    r.soundTracks[r.currentSoundtrack]->stop();

    Clock rankingTime, blinkStart;

    Time ranking_delay = seconds(1.f);

    int time = 28;
    float elapsed1, elapsed2, elapsed3, elapsed4;

    // Play ranking music
    r.soundTracks[12]->play();

    // Texts of the menu

    Text rankingTitle;
    rankingTitle.setFont(c.fontMenus);
    rankingTitle.setPosition(c.w.getSize().x / 4.f, c.w.getSize().y / 17.f);
    rankingTitle.setString("BEST OUTRUNNERS");
    rankingTitle.setCharacterSize(static_cast<unsigned int>(int(49.0f * c.screenScale)));
    rankingTitle.setFillColor(Color::Yellow);
    rankingTitle.setOutlineColor(Color(12, 12, 12));
    rankingTitle.setOutlineThickness(3.0f * c.screenScale);

    Text scoreIndicator;
    scoreIndicator.setFont(c.fontMenus);
    scoreIndicator.setPosition(c.w.getSize().x / 6.7f, c.w.getSize().y / 6.0f);
    scoreIndicator.setString("SCORE");
    scoreIndicator.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    scoreIndicator.setFillColor(Color(146, 194, 186));
    scoreIndicator.setOutlineColor(Color(12, 12, 12));
    scoreIndicator.setOutlineThickness(3.0f * c.screenScale);

    Text playerIndicator;
    playerIndicator.setFont(c.fontMenus);
    playerIndicator.setPosition(c.w.getSize().x / 2.12f, c.w.getSize().y / 6.0f);
    playerIndicator.setString("NAME");
    playerIndicator.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    playerIndicator.setFillColor(Color(146, 194, 186));
    playerIndicator.setOutlineColor(Color(12, 12, 12));
    playerIndicator.setOutlineThickness(3.0f * c.screenScale);

    Text recordIndicator;
    recordIndicator.setFont(c.fontMenus);
    recordIndicator.setPosition((c.w.getSize().x / 2.f) * 1.55f, c.w.getSize().y / 6.0f);
    recordIndicator.setString("RECORD");
    recordIndicator.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    recordIndicator.setFillColor(Color(146, 194, 186));
    recordIndicator.setOutlineColor(Color(12, 12, 12));
    recordIndicator.setOutlineThickness(3.0f * c.screenScale);

    Text timeCounter;
    timeCounter.setFont(c.fontMenus);
    timeCounter.setCharacterSize(static_cast<unsigned int>(int(48.0f * c.screenScale)));
    timeCounter.setString(to_string(time));
    timeCounter.setPosition(c.w.getSize().x / 4.f + rankingTitle.getLocalBounds().width + 30.f, c.w.getSize().y / 15.7f);
    timeCounter.setFillColor(Color::Red);
    timeCounter.setOutlineColor(Color(12, 12, 12));
    timeCounter.setOutlineThickness(3.0f * c.screenScale);

    Text scorePlayer;
    scorePlayer.setFont(c.fontMenus);
    scorePlayer.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    scorePlayer.setFillColor(Color(146, 194, 186));
    scorePlayer.setOutlineColor(Color::Black);
    scorePlayer.setOutlineThickness(3.0f * c.screenScale);

    Text namePlayer;
    namePlayer.setFont(c.fontMenus);
    namePlayer.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    namePlayer.setFillColor(Color(146, 194, 186));
    namePlayer.setOutlineColor(Color(12, 12, 12));
    namePlayer.setOutlineThickness(3.0f * c.screenScale);

    Text minutesPlayer;
    minutesPlayer.setFont(c.fontMenus);
    minutesPlayer.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    minutesPlayer.setFillColor(Color(146, 194, 186));
    minutesPlayer.setOutlineColor(Color::Black);
    minutesPlayer.setOutlineThickness(3.0f * c.screenScale);

    Text secondsPlayer;
    secondsPlayer.setFont(c.fontMenus);
    secondsPlayer.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    secondsPlayer.setFillColor(Color(146, 194, 186));
    secondsPlayer.setOutlineColor(Color::Black);
    secondsPlayer.setOutlineThickness(3.0f * c.screenScale);

    Text centsPlayer;
    centsPlayer.setFont(c.fontMenus);
    centsPlayer.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    centsPlayer.setFillColor(Color(146, 194, 186));
    centsPlayer.setOutlineColor(Color::Black);
    centsPlayer.setOutlineThickness(3.0f * c.screenScale);

    Text index;
    index.setFont(c.fontMenus);
    index.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    index.setFillColor(Color(180, 130, 211));
    index.setOutlineColor(Color::Black);
    index.setOutlineThickness(3.0f * c.screenScale);

    Text start;
    start.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    start.setFont(c.fontMenus);
    start.setFillColor(Color::Green);
    start.setOutlineColor(Color::Black);
    start.setOutlineThickness(3.0f * c.screenScale);

    // Loading the background texture
    Texture rankingBackground;
    rankingBackground.loadFromFile("Data/Animations/RankingAnimation/bg.png");
    Sprite palm_trees(rankingBackground);
    palm_trees.setScale((float) c.w.getSize().x / rankingBackground.getSize().x,
                        (float) c.w.getSize().y / rankingBackground.getSize().y);

    // Get the best seventh out runners
    vector<Score> scoreRankingPlayer = getGlobalScores(c);

    // Check if there is a new record
    int record = isNewRecord(scoreRankingPlayer, scorePlayerGame);
    bool startPressed = false;
    bool blink = false;

    // Number of letters introduced
    int lettersIntroduced = 0;

    // Name of the player
    string name = "_";

    // Counter clock to control the time of the menu and the blink texts
    rankingTime.restart();
    elapsed1 = rankingTime.getElapsedTime().asSeconds();
    elapsed3 = blinkStart.getElapsedTime().asSeconds();

    r.soundEffects[29]->play();
    Event e{};

    // Until time expires or start key is pressed
    while (time > 0 && !startPressed) {

        // Get the actual time
        elapsed2 = rankingTime.getElapsedTime().asSeconds();

        // Check if a second has passed between both timestamps
        if (elapsed2 - elapsed1 >= ranking_delay.asSeconds()) {
            // Draw time
            time--;
            rankingTime.restart();
            timeCounter.setString(to_string(time));
            timeCounter.setPosition(c.w.getSize().x / 4.f + rankingTitle.getLocalBounds().width + 30.f,
                                    c.w.getSize().y / 15.7f);
        }

        c.w.draw(palm_trees);
        c.w.draw(rankingTitle);
        c.w.draw(timeCounter);
        c.w.draw(scoreIndicator);
        c.w.draw(playerIndicator);
        c.w.draw(recordIndicator);

        // There is no new record
        if (record == -1) {

            start.setString("PRESS START");
            start.setPosition(c.w.getSize().x / 2.f - start.getLocalBounds().width / 2.f,
                             (c.w.getSize().y / 4.5f) + 400.0f);

            // There is not a new record
            for (int i = 1; i <= 7; i++) {

                index.setString(to_string(i) + ".");
                index.setPosition((c.w.getSize().x / 13.f) - index.getLocalBounds().width,
                                  (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * float(i));

                scorePlayer.setString(to_string(scoreRankingPlayer[i - 1].score));
                scorePlayer.setPosition((c.w.getSize().x / 3.9f) - scorePlayer.getLocalBounds().width,
                                        (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * float(i));

                namePlayer.setString(scoreRankingPlayer[i - 1].name);
                namePlayer.setPosition((c.w.getSize().x / 2.f) * 1.13f - namePlayer.getLocalBounds().width,
                                       (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * float(i));

                minutesPlayer.setString(to_string(scoreRankingPlayer[i - 1].minutes) + ":  ");
                minutesPlayer.setPosition((c.w.getSize().x / 2.f) * 1.57f - minutesPlayer.getLocalBounds().width,
                                          (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * float(i));

                if (scoreRankingPlayer[i - 1].secs >= 10) {
                    secondsPlayer.setString(to_string(scoreRankingPlayer[i - 1].secs) + " : ");
                } else {
                    secondsPlayer.setString("0" + to_string(scoreRankingPlayer[i - 1].secs) + " : ");
                }
                secondsPlayer.setPosition((c.w.getSize().x / 2.f) * 1.7f - secondsPlayer.getLocalBounds().width,
                                          (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * float(i));


                if (scoreRankingPlayer[i - 1].cents_second >= 10) {
                    centsPlayer.setString(to_string(scoreRankingPlayer[i - 1].cents_second));
                } else {
                    centsPlayer.setString("0" + to_string(scoreRankingPlayer[i - 1].cents_second));
                }
                centsPlayer.setPosition((c.w.getSize().x / 2.f) * 1.8f - centsPlayer.getLocalBounds().width,
                                        (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * float(i));

                c.w.draw(index);
                c.w.draw(scorePlayer);
                c.w.draw(namePlayer);
                c.w.draw(minutesPlayer);
                c.w.draw(secondsPlayer);
                c.w.draw(centsPlayer);
            }
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }
        } else {

            if (lettersIntroduced != 3) {
                start.setString("ENTER YOUR NAME");
            }
            else {
                start.setString("PRESS START");
            }
            start.setPosition(c.w.getSize().x / 2.f - start.getLocalBounds().width / 2.f,
                             (c.w.getSize().y / 4.5f) + 400.0f);


            // There is a new record
            // Show all the out runners with a higher score

            for (int i = 0; i <= record - 1; i++) {

                index.setString(to_string(i) + ".");
                index.setPosition((c.w.getSize().x / 13.f) - index.getLocalBounds().width,
                                  (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * (float) i);

                scorePlayer.setString(to_string(scoreRankingPlayer[i].score));
                scorePlayer.setPosition((c.w.getSize().x / 3.9f) - scorePlayer.getLocalBounds().width,
                                        (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * (float) (i + 1));

                namePlayer.setString(scoreRankingPlayer[i].name);
                namePlayer.setPosition((c.w.getSize().x / 2.f) * 1.13f - namePlayer.getLocalBounds().width,
                                       (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * (float) (i + 1));

                minutesPlayer.setString(to_string(scoreRankingPlayer[i].minutes) + " :  ");
                minutesPlayer.setPosition((c.w.getSize().x / 2.f) * 1.57f - minutesPlayer.getLocalBounds().width,
                                          (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * (float) (i + 1));

                if (scoreRankingPlayer[i].secs >= 10) {
                    secondsPlayer.setString(to_string(scoreRankingPlayer[i].secs) + " : ");
                } else {
                    secondsPlayer.setString("0" + to_string(scoreRankingPlayer[i].secs) + " : ");
                }
                secondsPlayer.setPosition((c.w.getSize().x / 2.f) * 1.7f - secondsPlayer.getLocalBounds().width,
                                          (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * (float) (i + 1));


                if (scoreRankingPlayer[i].cents_second >= 10) {
                    centsPlayer.setString(to_string(scoreRankingPlayer[i].cents_second));
                } else {
                    centsPlayer.setString("0" + to_string(scoreRankingPlayer[i].cents_second));
                }
                centsPlayer.setPosition((c.w.getSize().x / 2.f) * 1.8f - centsPlayer.getLocalBounds().width,
                                        (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * (float) (i + 1));

                c.w.draw(scorePlayer);
                c.w.draw(namePlayer);
                c.w.draw(minutesPlayer);
                c.w.draw(secondsPlayer);
                c.w.draw(centsPlayer);
            }

            int offset = (record == 0) ? 1 : record + 1;

            // Show the actual player
            scorePlayer.setString(to_string(scorePlayerGame));
            scorePlayer.setPosition((c.w.getSize().x / 3.9f) - scorePlayer.getLocalBounds().width,
                                    (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * (float) offset);

            namePlayer.setString(name);
            namePlayer.setPosition((c.w.getSize().x / 2.f) * 1.13f - namePlayer.getLocalBounds().width,
                                   (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * (float) offset);

            minutesPlayer.setString(to_string(minutes) + " :  ");
            minutesPlayer.setPosition((c.w.getSize().x / 2.f) * 1.57f - minutesPlayer.getLocalBounds().width,
                                      (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * (float) offset);

            if (secs >= 10) {
                secondsPlayer.setString(to_string(secs) + " : ");
            } else {
                secondsPlayer.setString("0" + to_string(secs) + " : ");
            }
            secondsPlayer.setPosition((c.w.getSize().x / 2.f) * 1.7f - secondsPlayer.getLocalBounds().width,
                                      (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * (float) offset);


            if (cents_Second >= 10) {
                centsPlayer.setString(to_string(cents_Second));
            } else {
                centsPlayer.setString("0" + to_string(cents_Second));
            }
            centsPlayer.setPosition((c.w.getSize().x / 2.f) * 1.8f - centsPlayer.getLocalBounds().width,
                                    (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * (float) offset);

            c.w.draw(scorePlayer);
            c.w.draw(namePlayer);
            c.w.draw(minutesPlayer);
            c.w.draw(secondsPlayer);
            c.w.draw(centsPlayer);

            // Show the rest of out runners

            for (int i = record; i < 6 && i < (int)scoreRankingPlayer.size(); i++) {
                scorePlayer.setString(to_string(scoreRankingPlayer[i].score));
                scorePlayer.setPosition((c.w.getSize().x / 3.9f) - scorePlayer.getLocalBounds().width,
                                        (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * (float) (i + 2));

                namePlayer.setString(scoreRankingPlayer[i].name);
                namePlayer.setPosition((c.w.getSize().x / 2.f) * 1.13f - namePlayer.getLocalBounds().width,
                                       (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * (float) (i + 2));

                minutesPlayer.setString(to_string(scoreRankingPlayer[i].minutes) + " :  ");
                minutesPlayer.setPosition((c.w.getSize().x / 2.f) * 1.57f - minutesPlayer.getLocalBounds().width,
                                          (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * (float) (i + 2));

                if (scoreRankingPlayer[i].secs >= 10) {
                    secondsPlayer.setString(to_string(scoreRankingPlayer[i].secs) + " : ");
                } else {
                    secondsPlayer.setString("0" + to_string(scoreRankingPlayer[i].secs) + " : ");
                }
                secondsPlayer.setPosition((c.w.getSize().x / 2.f) * 1.7f - secondsPlayer.getLocalBounds().width,
                                          (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * (float) (i + 2));


                if (scoreRankingPlayer[i].cents_second >= 10) {
                    centsPlayer.setString(to_string(scoreRankingPlayer[i].cents_second));
                } else {
                    centsPlayer.setString("0" + to_string(scoreRankingPlayer[i].cents_second));
                }
                centsPlayer.setPosition((c.w.getSize().x / 2.f) * 1.8f - centsPlayer.getLocalBounds().width,
                                        (c.w.getSize().y / 4.5f) + 50.0f * c.screenScale * (float) (i + 2));

                c.w.draw(scorePlayer);
                c.w.draw(namePlayer);
                c.w.draw(minutesPlayer);
                c.w.draw(secondsPlayer);
                c.w.draw(centsPlayer);
            }
        }
        elapsed4 = blinkStart.getElapsedTime().asSeconds();
        if (elapsed4 - elapsed3 >= ranking_delay.asSeconds()) {
            blink = !blink;
            blinkStart.restart();
        }
        if (blink) {
            start.setFillColor(Color::Green);
            start.setOutlineColor(Color::Black);
        } else {
            start.setFillColor(Color::Transparent);
            start.setOutlineColor(Color::Transparent);
        }

        c.w.draw(start);
        bufferSprite.setTexture(c.w.getTexture(), true);
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

        if (lettersIntroduced != 3 && record != -1) {
            // while there are pending events...
            Event event{};
            while (c.window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    return EXIT;
                } else if (c.window.hasFocus()&& event.type == Event::KeyPressed) {
                    // Get code of the key
                    int code = event.key.code;
                    // Check if the key pressed is a letter or not
                    if (code >= 0 && code <= 25) {
                        lettersIntroduced++;
                        string keyLetter = kM.mapperIdKeyWord[code];
                        if (name == "_") {
                            name = keyLetter;
                            r.soundEffects[116]->stop();
                            r.soundEffects[116]->play();
                        } else {
                            if (lettersIntroduced == 3) {
                                name = name.substr(0, name.size() - 1);
                                name += keyLetter;
                                r.soundEffects[116]->stop();
                                r.soundEffects[116]->play();
                            } else {
                                name += keyLetter + "_";
                                r.soundEffects[116]->stop();
                                r.soundEffects[116]->play();
                            }
                        }
                    } else {
                        r.soundEffects[3]->stop();
                        r.soundEffects[3]->play();
                    }
                }
            }
        }
        if (c.window.hasFocus() && Keyboard::isKeyPressed(c.menuEnterKey)) {
            if (lettersIntroduced == 3){
                startPressed = true;
            }
            else {
                r.soundEffects[3]->stop();
                r.soundEffects[3]->play();
            }
        }
    }

    // Control if the exit of the loop was by the time
    if (time == 0){
        // Check if the name was completed or not
        if (lettersIntroduced != 3){
            // Default name
            name = "SER";
        }
    }

    // Store the record
    if (record != -1) {
        // If the was record and the name is uncompleted
        Score s = Score(scorePlayerGame, name, minutes, secs, cents_Second);
        saveNewRecord(scoreRankingPlayer, s, c);
    }

    r.soundEffects[2]->stop();
    r.soundEffects[2]->play();
    r.soundEffects[29]->stop();
    r.soundTracks[12]->stop();

    // Control the pixel art to construct the view of the screen
    if (c.enablePixelArt) {
        if (c.isDefaultScreen)
            c.window.setView(View(Vector2f(DEFAULT_WIDTH / 4.0f, DEFAULT_HEIGHT / 4.0f),
                                  Vector2f(DEFAULT_WIDTH / 2.0f, DEFAULT_HEIGHT / 2.0f)));
        else
            c.window.setView(View(Vector2f(SCREEN_HD_WIDTH / 4.0f, SCREEN_HD_HEIGHT / 4.0f),
                                  Vector2f(SCREEN_HD_WIDTH / 2.0f, SCREEN_HD_HEIGHT / 2.0f)));
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));
        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);
    }
    r.soundTracks[0]->play();
    return START;
}



/**
 * Updates the current configuration of the game by a new one modifying
 * the xml configuration file
 * @param path is the path the xml configuration file
 * @param difficulty is the level of difficulty selected by the player
 * @param volumeSoundtracks is the volume of the soundtracks selected by the player
 * @param volumeEffects is the volume of the sound effects selected by the player
 * @param pixelArt controls if the graphics must be rendered with pixel art effect or not
 * @param fullScreen controls if the game must be load in full screen or not
 * @param axis_x is the width of the window's game
 * @param axis_y is the height of the window's game
 * @param controlLeft is the key selected by the player to turn the vehicle to the left
 * @param controlRight is the key selected by the player to turn the vehicle to the right
 * @param controlAccelerate is the key selected by the player to accelerate the vehicle
 * @param controlBrake is the key selected by the player to brake the vehicle
 * @param controlSoundtrack is the key selected by the player to change the soundtrack of the game
 */
void updateGameConfiguration(const string path, const Difficult difficulty, const int volumeSoundtracks,
                             const int volumeEffects, const bool pixelArt, const bool fullScreen, const int axis_x, const int axis_y,
                             const string controlLeft, const string controlRight, const string controlAccelerate, const string controlBrake,
                             const string controlSoundtrack)
{
    // xml file which stores the player with the highest score in the level
    ofstream theFile (path);
    string activePixelArt, level, activeFullScreen;
    xml_document<> doc;

    // Add the headers to the file
    xml_node<>* decl = doc.allocate_node(node_declaration);
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "UTF-8"));
    doc.append_node(decl);

    // Create the node record
    xml_node<>* root = doc.allocate_node(node_element, "Settings");
    doc.append_node(root);

    // Create a node with the level difficulty
    xml_node<>* levelDifficulty = doc.allocate_node(node_element, "Difficulty");
    root->append_node(levelDifficulty);
    switch(difficulty){
        case EASY:
            level = "Easy";
            break;
        case NORMAL:
            level = "Normal";
            break;
        case HARD:
            level = "Hard";
    }
    levelDifficulty->value(level.c_str());

    // Create the node with the volume of the soundtracks
    xml_node<>* musicSoundtrack = doc.allocate_node(node_element, "Volume_Soundtracks");
    root->append_node(musicSoundtrack);
    musicSoundtrack->value(to_string(volumeSoundtracks).c_str());

    // Create the node with the volume of the sound effects
    xml_node<>* musicSoundEffects = doc.allocate_node(node_element, "Volume_Effects");
    root->append_node(musicSoundEffects);
    musicSoundEffects->value(to_string(volumeEffects).c_str());

    // Create the node of the pixelart control
    xml_node<>* nodePixelArt = doc.allocate_node(node_element, "PixelArt");
    root->append_node(nodePixelArt);
    if (pixelArt){
        activePixelArt = "Enabled";
    }
    else {
        activePixelArt = "Disabled";
    }
    nodePixelArt->value(activePixelArt.c_str());

    // Create the node of the full screen controller
    xml_node<>* fullScreenNode = doc.allocate_node(node_element, "Full_screen");
    root->append_node(fullScreenNode);
    if (fullScreen){
        activeFullScreen = "Enabled";
    }
    else {
        activeFullScreen = "Disabled";
    }
    fullScreenNode->value(activeFullScreen.c_str());

    // Create a new node with the screen resolution in axis x
    xml_node<>* resolution_x = doc.allocate_node(node_element, "Resolution_x");
    root->append_node(resolution_x);
    resolution_x->value(to_string(axis_x).c_str());

    // Create a new node with the screen resolution in axis y
    xml_node<>* resolution_y = doc.allocate_node(node_element, "Resolution_y");
    root->append_node(resolution_y);
    resolution_y->value(to_string(axis_y).c_str());

    // Create a new node with the turning left controller
    xml_node<>* left = doc.allocate_node(node_element, "Controller_left");
    root->append_node(left);
    left->value(controlLeft.c_str());

    // Create a new node with the turning right controller
    xml_node<>* right = doc.allocate_node(node_element, "Controller_right");
    root->append_node(right);
    right->value(controlRight.c_str());

    // Create a new node with the acceleration controller
    xml_node<>* accelerate = doc.allocate_node(node_element, "Controller_accelerate");
    root->append_node(accelerate);
    accelerate->value(controlAccelerate.c_str());

    // Create a new node with the brake controller
    xml_node<>* brake = doc.allocate_node(node_element, "Controller_brake");
    root->append_node(brake);
    brake->value(controlBrake.c_str());

    // Create a new node with the changing soundtrack controller
    xml_node<>* soundtrack = doc.allocate_node(node_element, "Controller_soundtrack");
    root->append_node(soundtrack);
    soundtrack->value(controlSoundtrack.c_str());

    // Store the new xml file configuration
    theFile << doc;
    theFile.close();
    doc.clear();
}



/**
 * Shows a loading animation with the current controllers of the game
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 * @param onMultiplayer controls if the multi player mode is been played or not
 */
State showLoadingAnimation(Configuration& c, SoundPlayer& r, const bool onMultiplayer){

    // Prepare the screen to display the loading animation
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));

    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Load the background of the animation
    Texture t;
    t.loadFromFile("Data/Animations/LoadingAnimation/cover.png");
    IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
    Sprite sprite(t, background);

    float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
    float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
    sprite.setScale(axis_x, axis_y);

    Texture t2;
    t2.loadFromFile("Data/Animations/LoadingAnimation/crono.png");

    RectangleShape shape;
    shape.setPosition((c.w.getSize().x / 2.f) - 300.0f * c.screenScale, c.w.getSize().y / 2.f - 240.0f * c.screenScale);
    shape.setSize(sf::Vector2f(610.0f * c.screenScale, 425.0f * c.screenScale));
    shape.setOutlineColor(Color::Black);
    shape.setOutlineThickness(5.0f * c.screenScale);
    shape.setTexture(&t2, true);

    // Main Text of the menu
    Text controllersText;
    controllersText.setString("CONTROLLERS");
    controllersText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    controllersText.setFont(c.fontMenus);
    controllersText.setStyle(Text::Bold | Text::Underlined);
    controllersText.setFillColor(Color::White);
    controllersText.setOutlineColor(Color::Black);
    controllersText.setOutlineThickness(5.0f * c.screenScale);
    controllersText.setPosition((c.w.getSize().x / 2.f) - controllersText.getLocalBounds().width / 2.f,
                                 c.w.getSize().y / 2.f - 210.0f * c.screenScale);

    // Number of points to display depending of the resolution
    int totalPoints, offsetText;
    if (c.isDefaultScreen){
        totalPoints = 25;
        offsetText = 235;
    }
    else {
        totalPoints = 35;
        offsetText = 205;
    }

    // Menu text
    Text loadingText;
    loadingText.setString("NOW LOADING");
    loadingText.setCharacterSize(static_cast<unsigned int>(int(25.0f * c.screenScale)));
    loadingText.setFont(c.fontMenus);
    loadingText.setStyle(Text::Bold);
    loadingText.setFillColor(Color::White);
    loadingText.setOutlineColor(Color::Black);
    loadingText.setOutlineThickness(5.0f * c.screenScale);
    loadingText.setPosition((c.w.getSize().x / 7.f) - loadingText.getLocalBounds().width / 2.f,
                                 c.w.getSize().y / 2.f + offsetText * c.screenScale);

    // Buttons of the controllers
    vector<Button> controllerButtons;

    // Left buttons
    Button b = Button(c.w.getSize().x / 2.f - 270.0f * c.screenScale, c.w.getSize().y / 2.f - 145.0f * c.screenScale,
                      260.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenus, "Turn left", Color(249, 54, 46),
                      Color(255, 255, 255), Color(0, 0, 0), 0, c.screenScale);
    // Add the button in the vector of buttons of the menu
    controllerButtons.push_back(b);

    b = Button(c.w.getSize().x / 2.f - 270.0f * c.screenScale, c.w.getSize().y / 2.f - 75.0f * c.screenScale,
                      260.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenus, "Turn right", Color(249, 54, 46),
                      Color(255, 255, 255), Color(0, 0, 0), 0, c.screenScale);
    // Add the button in the vector of buttons of the menu
    controllerButtons.push_back(b);

    b = Button(c.w.getSize().x / 2.f - 270.0f * c.screenScale, c.w.getSize().y / 2.f -5.0f * c.screenScale,
                      260.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenus, "Accelerating", Color(249, 54, 46),
                      Color(255, 255, 255), Color(0, 0, 0), 0, c.screenScale);
    // Add the button in the vector of buttons of the menu
    controllerButtons.push_back(b);

        // Change the state of the first color
    b = Button(c.w.getSize().x / 2.f - 270.0f * c.screenScale, c.w.getSize().y / 2.f + 65.0f * c.screenScale,
                      260.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenus, "Braking", Color(249, 54, 46),
                      Color(255, 255, 255), Color(0, 0, 0), 0, c.screenScale);
    // Add the button in the vector of buttons of the menu
    controllerButtons.push_back(b);

        // Change the state of the first color
    b = Button(c.w.getSize().x / 2.f - 270.0f * c.screenScale, c.w.getSize().y / 2.f + 135.0f * c.screenScale,
                      260.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenus, "Change soundtrack", Color(249, 54, 46),
                      Color(255, 255, 255), Color(0, 0, 0), 0, c.screenScale);
    // Add the button in the vector of buttons of the menu
    controllerButtons.push_back(b);

    // Right buttons
    KeywordMapper kM = KeywordMapper();

    // Right buttons with the current controllers
    int code;
    code = kM.mapperCodeKeyWord[c.leftKey];
    controllerButtons.emplace_back(c.w.getSize().x / 2.f + 20.0f * c.screenScale,
                                   c.w.getSize().y / 2.f - 145.0f * c.screenScale, 260.0f * c.screenScale,
                                   30.0f * c.screenScale, c.fontMenus, kM.mapperIdKeyWord[code], Color(249, 54, 46),
                                   Color(255, 255, 255), Color(0, 0, 0), 0, c.screenScale);

    code = kM.mapperCodeKeyWord[c.rightKey];
    controllerButtons.emplace_back(c.w.getSize().x / 2.f + 20.0f * c.screenScale,
                                   c.w.getSize().y / 2.f - 75.0f * c.screenScale, 260.0f * c.screenScale,
                                   30.0f * c.screenScale, c.fontMenus, kM.mapperIdKeyWord[code], Color(249, 54, 46),
                                   Color(255, 255, 255), Color(0, 0, 0), 0, c.screenScale);

    code = kM.mapperCodeKeyWord[c.accelerateKey];
    controllerButtons.emplace_back(c.w.getSize().x / 2.f + 20.0f * c.screenScale,
                                   c.w.getSize().y / 2.f - 5.0f * c.screenScale, 260.0f * c.screenScale,
                                   30.0f * c.screenScale, c.fontMenus, kM.mapperIdKeyWord[code], Color(249, 54, 46),
                                   Color(255, 255, 255), Color(0, 0, 0), 0, c.screenScale);

    code = kM.mapperCodeKeyWord[c.brakeKey];
    controllerButtons.emplace_back(c.w.getSize().x / 2.f + 20.0f * c.screenScale,
                                   c.w.getSize().y / 2.f + 65.0f * c.screenScale, 260.0f * c.screenScale,
                                   30.0f * c.screenScale, c.fontMenus, kM.mapperIdKeyWord[code], Color(249, 54, 46),
                                   Color(255, 255, 255), Color(0, 0, 0), 0, c.screenScale);

    code = kM.mapperCodeKeyWord[c.soundtrackKey];
    controllerButtons.emplace_back(c.w.getSize().x / 2.f + 20.0f * c.screenScale,
                                   c.w.getSize().y / 2.f + 135.0f * c.screenScale, 260.0f * c.screenScale,
                                   30.0f * c.screenScale, c.fontMenus, kM.mapperIdKeyWord[code], Color(249, 54, 46),
                                   Color(255, 255, 255), Color(0, 0, 0), 0, c.screenScale);

    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Vector of loafing points
    string points[totalPoints];

    // Fill the vector with the points
    for (int i = 0; i < totalPoints; i++){
        points[i] = ".";
    }

    // Reproduce the soundtrack of the game
    r.soundTracks[17]->play();

    for (int i = 0; i < totalPoints; i++){

        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)){
            if (e.type == Event::Closed && !onMultiplayer){
                return EXIT;
            }
        }

        // Draw the elements of the menu
        c.w.draw(sprite);
        c.w.draw(shape);
        c.w.draw(controllersText);

        // Show the buttons of the menu
        for (auto &menuButton : controllerButtons) {
            menuButton.render(&c.w);
        }

        c.w.draw(loadingText);

        // Draw the loading points
        for (int j = 0; j <= i; j++){

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)){
                if (e.type == Event::Closed){
                    return EXIT;
                }
            }

            Text pointText;
            pointText.setString(points[j]);
            pointText.setCharacterSize(static_cast<unsigned int>(int(25.0f * c.screenScale)));
            pointText.setFont(c.fontMenus);
            pointText.setStyle(Text::Bold);
            pointText.setFillColor(Color::White);
            pointText.setOutlineColor(Color::Black);
            pointText.setOutlineThickness(5.0f * c.screenScale);
            pointText.setPosition((c.w.getSize().x / 7.f) + loadingText.getLocalBounds().width / 2.f + 25.f * (j + 1),
                                   c.w.getSize().y / 2.f + offsetText * c.screenScale);
            c.w.draw(pointText);
        }

        bufferSprite.setTexture(c.w.getTexture(), true);
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

        sleep(milliseconds(150));
    }

    // Reproduce the soundtrack of the game
    r.soundTracks[17]->stop();

    // Control the pixel art flag to construct the view of the screen
    if (c.enablePixelArt) {
        if (c.isDefaultScreen)
            c.window.setView(View(Vector2f(DEFAULT_WIDTH / 4.0f, DEFAULT_HEIGHT / 4.0f),
                                  Vector2f(DEFAULT_WIDTH / 2.0f, DEFAULT_HEIGHT / 2.0f)));
        else
            c.window.setView(View(Vector2f(SCREEN_HD_WIDTH / 4.0f, SCREEN_HD_HEIGHT / 4.0f),
                                  Vector2f(SCREEN_HD_WIDTH / 2.0f, SCREEN_HD_HEIGHT / 2.0f)));
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));
        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);
    }
    return PLAY_GAME;
}




/**
 * Load the configuration of the multi player menu stored in its xml configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadMultiplayerMenuConfiguration(const string path, Configuration& c){

    // Open the xml file of the multi player
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Local variable to store temporary the text content and the fonts of the texts
    string content, fontPath, backgroundTexture, colorKind;

    // Iterate to get the information of the multi player menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check it is the node that contains the information of the background
        if ((string)property->name() == "Background"){
            // Get the background image of the menu
            backgroundTexture = (string)property->value();
            c.backgroundMultiplayerMenu.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the multi player menu
            for (xml_node<> *panelProp = property->first_node(); panelProp; panelProp = panelProp->next_sibling()){
                // Check it is the node that contains the information of the background of the panel
                if ((string)panelProp->name() == "Background"){
                    // Get the background image of the menu
                    backgroundTexture = (string)panelProp->value();
                    c.backgroundMultiplayerPanel.loadFromFile(backgroundTexture);
                }
                // Check it is the node that contains the information of the color border of the panel
                else if ((string)panelProp->name() == "ColorBorder"){
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the multi player menu
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
                    c.colorBorderPanelMultiplayerMenu = Color(colorRed, colorGreen, colorBlue);
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
                    c.contentTitleMultiplayerMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontTitleMultiplayerMenu.loadFromFile(fontPath);
                }
                // Get color text of the title
                else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                    // Get the kind of color to process
                    colorKind = (string)titleProp->name();
                    // Get the border color of the panel
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the multi player menu
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
                        c.colorTitleTextMultiplayerMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderMultiplayerMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
        // Check if it is the node that the different buttons of the menu
        else if ((string)property->name() == "MenuButtons"){
            Color colorFont;
            // Iterate to get the information of the buttons of the player menu
            for (xml_node<> *buttonProp = property->first_node(); buttonProp; buttonProp = buttonProp->next_sibling()){
                // Get the font of the buttons
                if ((string)buttonProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)buttonProp->value();
                    c.fontMenuMultiplayerButtons.loadFromFile(fontPath);
                }
                // Get the color font of the buttons
                else if ((string)buttonProp->name() == "ColorFont"){
                    // Read the font from the file
                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                    // Iterate to get the information of the multi player menu
                    for (xml_node<> *color = buttonProp->first_node(); color; color = color->next_sibling()){
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
                    c.colorFontMenuPlayerButtons = Color(colorRed, colorGreen, colorBlue);
                }
                // Get the information of the buttons
                else if ((string)buttonProp->name() == "Buttons"){
                    // Local variables to store the attributes of the buttons
                    string contentButton;
                    int buttonState = 0;
                    vector<Color> colorButtons;
                    Texture icon;
                    Sprite s;
                    int idButton = 0, posX, posY, widthButton, heightButton;
                    // Iterate to get the information of the buttons
                    for (xml_node<> *buttonNode = buttonProp->first_node(); buttonNode; buttonNode = buttonNode->next_sibling()){
                        // Iterate to get the information of the buttons
                        for (xml_node<> *button = buttonNode->first_node(); button; button = button->next_sibling()){
                            // Get the font of the buttons
                            if ((string)button->name() == "Content"){
                                // Read the font from the file
                                contentButton = (string)button->value();
                            }
                            // Get the state of the button
                            else if ((string)button->name() == "InitialState"){
                                // Read the font from the file
                                buttonState = stoi(button->value());
                            }
                            // Get the colors of the button
                            else if ((string)button->name() == "Colors"){
                                // Read the colors of the button
                                for (xml_node<> *colorButton = button->first_node(); colorButton; colorButton = colorButton->next_sibling()){
                                    // Get the border color of the panel
                                    int colorRed = 0, colorGreen = 0, colorBlue = 0;
                                    // Iterate to get the information of the multi player menu
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
                                    c.multiplayerMenuColorButtons.push_back(Color(colorRed, colorGreen, colorBlue));
                                }

                                // Creation of the button and addition to the vector
                                posX = c.w.getSize().x / 2.f - 110.0f * c.screenScale;
                                posY = c.w.getSize().y / 2.f - (53.0f - idButton * 123.f) * c.screenScale;
                                widthButton = 200.0f * c.screenScale;
                                heightButton = 50.0f * c.screenScale;

                                // Creation of the button
                                Button b = Button(posX, posY, widthButton, heightButton, c.fontMenuMultiplayerButtons,
                                                  contentButton, c.multiplayerMenuColorButtons[0], c.multiplayerMenuColorButtons[1],
                                                  c.colorFontMenuPlayerButtons, buttonState, c.screenScale);

                                c.multiplayerMenuButtons.push_back(b);
                                idButton++;
                            }
                        }
                    }
                }
            }
        }
    }
    // The player menu has been read correctly
    c.multiplayerMenuRead = true;
}




/**
 * Shows the main multi player menu
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 * @param multiplayerMode controls how the player has selected to play in multi player mode
 */
State multiplayerMenu(Configuration& c, SoundPlayer& r, int& multiplayerMode){

    // Prepare the screen to display the main multi player menu
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));

    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Read the multi player menu if it has not been read
    if (!c.multiplayerMenuRead){
        // Read the multi player menu xml configuration file
        string pathFile = "Data/Menus/MultiplayerMenu/Configuration/MultiplayerMenu.xml";
        loadMultiplayerMenuConfiguration(pathFile, c);
    }
    else {
        int numButtons = int(c.multiplayerMenuButtons.size());

        // Change the state of the first color
        Button b = Button(c.w.getSize().x / 2.f - 110.0f * c.screenScale, c.w.getSize().y / 2.f - 53.0f * c.screenScale,
                          200.0f * c.screenScale, 50.0f * c.screenScale, c.fontMenuMultiplayerButtons,
                          c.multiplayerMenuButtons[0].getTextButton(), c.multiplayerMenuButtons[0].getIdleColorButton(),
                          c.multiplayerMenuButtons[0].getHoverColorButton(), c.multiplayerMenuButtons[0].getFontColorButton(), 1,
                          c.screenScale);

        c.multiplayerMenuButtons[0] = b;

        // Eliminate the buttons of the right column
        for (int i = 1; i < numButtons; i++){
            // Change the state of the first color
            Button b = Button(c.w.getSize().x / 2.f - 110.0f * c.screenScale, c.w.getSize().y / 2.f - (53.0f - i * 123.f) * c.screenScale,
                              200.0f * c.screenScale, 50.0f * c.screenScale, c.fontMenuMultiplayerButtons,
                              c.multiplayerMenuButtons[i].getTextButton(), c.multiplayerMenuButtons[i].getIdleColorButton(),
                              c.multiplayerMenuButtons[i].getHoverColorButton(), c.multiplayerMenuButtons[i].getFontColorButton(), 0,
                              c.screenScale);

            c.multiplayerMenuButtons[i] = b;
        }
    }

    // Control if the start key is pressed or not
    bool startPressed = false;

    // Control if the escape key has been pressed
    bool escapePressed = false;

    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Control the option selected by the user
    int optionSelected = 0;

    // While start and escape have not been pressed
    while (!startPressed && !escapePressed) {

        // Make the textures repeated
        c.backgroundMultiplayerMenu.setRepeated(true);
        c.backgroundMultiplayerPanel.setRepeated(true);

        // Global rectangle of the background
        IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
        Sprite sprite(c.backgroundMultiplayerMenu, background);

        float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
        float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
        sprite.setScale(axis_x, axis_y);
        c.multiPlayerMenuBackground = sprite;

        // Creation of the panel rectangle of the menu
        RectangleShape shape;
        shape.setPosition((c.w.getSize().x / 2.f) - 180.0f * c.screenScale, c.w.getSize().y / 2.f - 170.0f * c.screenScale);
        shape.setSize(sf::Vector2f(350.0f * c.screenScale, 340.0f * c.screenScale));
        shape.setOutlineColor(c.colorBorderPanelMultiplayerMenu);
        shape.setOutlineThickness(5.0f * c.screenScale);
        shape.setTexture(&c.backgroundMultiplayerPanel, true);

        // Main Text of the menu
        Text mainText;
        mainText.setString(c.contentTitleMultiplayerMenu);
        mainText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        mainText.setFont(c.fontTitleMultiplayerMenu);
        mainText.setStyle(Text::Bold | Text::Underlined);
        mainText.setFillColor(c.colorTitleTextMultiplayerMenu);
        mainText.setOutlineColor(c.colorTitleBorderMultiplayerMenu);
        mainText.setOutlineThickness(5.0f * c.screenScale);
        mainText.setPosition((c.w.getSize().x / 2.f) - mainText.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f - 140.0f * c.screenScale);

        // Until the start keyword or escape keyword is not pressed
        while (!startPressed && !escapePressed) {

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)){

                if (e.type == Event::Closed){

                    // Complaining text
                    Text complainText;
                    complainText.setString("THIS BUTTON CANT'T BE USED NOW ");
                    complainText.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
                    complainText.setFont(c.fontTitleMultiplayerMenu);
                    complainText.setStyle(Text::Bold);
                    complainText.setFillColor(c.colorTitleTextMultiplayerMenu);
                    complainText.setOutlineColor(c.colorTitleBorderMultiplayerMenu);
                    complainText.setOutlineThickness(5.0f * c.screenScale);
                    if (c.isDefaultScreen){
                        complainText.setPosition(c.w.getSize().x / 2.f - complainText.getLocalBounds().width / 2.f,
                                                         c.w.getSize().y / 2.f + 220.0f * c.screenScale);
                    }
                    else {
                        complainText.setPosition((c.w.getSize().x / 2.f) - complainText.getLocalBounds().width / 2.f,
                                                  c.w.getSize().y / 2.f + 180.0f * c.screenScale);
                    }

                    for (int i = 0; i <= 120; i++){

                        Event e;
                        c.window.pollEvent(e);

                        // Draw the elements of the menu
                        c.w.draw(c.multiPlayerMenuBackground);
                        c.w.draw(shape);
                        c.w.draw(mainText);
                        c.w.draw(complainText);

                         // Show the buttons of the menu
                        for (int i = 0; i < (int)c.multiplayerMenuButtons.size(); i++) {
                            c.multiplayerMenuButtons.at(i).render(&c.w);
                        }

                        bufferSprite.setTexture(c.w.getTexture(), true);
                        c.w.display();
                        c.window.draw(bufferSprite);
                        c.window.display();
                    }
                }
            }

            // Check if the up or down cursor keys have been pressed or not
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Down)) {
                if (optionSelected != int(c.multiplayerMenuButtons.size() - 1)) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected++;
                    c.multiplayerMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    c.multiplayerMenuButtons[optionSelected - 1].setButtonState(BUTTON_IDLE);
                }
            }
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Up)) {
                if (optionSelected != 0) {
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected--;
                    // Change the color appearance of both buttons
                    c.multiplayerMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    c.multiplayerMenuButtons[optionSelected + 1].setButtonState(BUTTON_IDLE);
                }
            }

            // Draw the elements of the menu
            c.w.draw(c.multiPlayerMenuBackground);
            c.w.draw(shape);
            c.w.draw(mainText);

             // Show the buttons of the menu
            for (int i = 0; i < (int)c.multiplayerMenuButtons.size(); i++) {
                c.multiplayerMenuButtons.at(i).render(&c.w);
            }

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
            sleep(milliseconds(120));

            // Check if start has been pressed
            if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
                startPressed = true;
                r.soundEffects[2]->stop();
                r.soundEffects[2]->play();
            }
            // Check if escape has been pressed
            else if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Escape)) {
                escapePressed = true;
                r.soundEffects[11]->stop();
                r.soundEffects[11]->play();
            }
        }
    }

    // Control the pixel art flag to construct the view of the screen
    if (c.enablePixelArt) {
        if (c.isDefaultScreen){
            c.window.setView(View(Vector2f(DEFAULT_WIDTH / 4.0f, DEFAULT_HEIGHT / 4.0f),
                                  Vector2f(DEFAULT_WIDTH / 2.0f, DEFAULT_HEIGHT / 2.0f)));
        }
        else {
            c.window.setView(View(Vector2f(SCREEN_HD_WIDTH / 4.0f, SCREEN_HD_HEIGHT / 4.0f),
                                  Vector2f(SCREEN_HD_WIDTH / 2.0f, SCREEN_HD_HEIGHT / 2.0f)));
        }
        c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                   static_cast<unsigned int>(c.window.getView().getSize().y));
        c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);
    }

    if(startPressed){
        // Store how to start the multi player game
        multiplayerMode = optionSelected;
        return MULTIPLAYER_NAME_PLAYER;
    }

    else if (escapePressed) {
        r.soundTracks[18]->stop();
        r.soundTracks[1]->play();
        // Return to the player menu
        return PLAYER_MENU;
    }
    return EXIT;
}



/**
 * Shows the credits of the platform
 * @param c is the module configuration of the game
 * @param r is the sound player module of the game
 */
State credits(Configuration& c, SoundPlayer& r){

    // Set the scale of the console window
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));
    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Clean the console window of the game
    c.w.clear();
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Vector of textures and sprites of the main menu
    vector<Sprite> nameGames;

    // Stop the soundtrack of the main menu and play the credit soundtrack
    r.soundTracks[0]->stop();
    r.soundTracks[19]->play();

    // vector with the soundtracks developers
    string soundtrackDevelopers[9];

    // vector with the enterprise developers
    string enterpriseDevelopers1[9];

    soundtrackDevelopers[0] = "Super Hang on - 1989 - Sega Megadrive";
    soundtrackDevelopers[1] = "Alien 3 - 1992 - Sega Megadrive";
    soundtrackDevelopers[2] = "Mega Turricane - 1994 - Sega Megadrive";
    soundtrackDevelopers[3] = "Cruis'n USA - 1994 - N64";
    soundtrackDevelopers[4] = "Cruis'n USA 1994 - Arcade version";
    soundtrackDevelopers[5] = "Cruis'n World - 1996 - N64";
    soundtrackDevelopers[6] = "Cruis'n Exotica - 1999 - N64";
    soundtrackDevelopers[7] = "Mario kart Super Circuit - 2001 - Game Boy Advanced";
    soundtrackDevelopers[8] = "Mario Kart - 2005 - NDS";

    enterpriseDevelopers1[0] = "Sega AM2 and Sega";
    enterpriseDevelopers1[1] = "Acclaim Studios London and Bits Studios";
    enterpriseDevelopers1[2] = "Factor 5";
    enterpriseDevelopers1[3] = "Midway Games and WMS Industries";
    enterpriseDevelopers1[4] = "Midway Games and WMS Industries";
    enterpriseDevelopers1[5] = "Midway Games and Eurocom";
    enterpriseDevelopers1[6] = "Gratuitous Game, Crawfish Interactive and Midway Games";
    enterpriseDevelopers1[7] = "Intelligent Systems";
    enterpriseDevelopers1[8] = "Nintendo and Nintendo Entertainment Analysis and Development";

    // vector with the soundtracks developers
    string soundEffectskDevelopers[12];

    // vector with the enterprise developers
    string enterpriseDevelopers2[12];

    soundEffectskDevelopers[0] = "Out Run - 1986 - Arcade version";
    soundEffectskDevelopers[1] = "Chase HQ - 1988 - Arcade version";
    soundEffectskDevelopers[2] = "Super Hang on - 1989 - Sega Megadrive";
    soundEffectskDevelopers[3] = "Golden Axe - 1989 - Sega Megadrive";
    soundEffectskDevelopers[4] = "Cruis'n USA - N64 - 1994";
    soundEffectskDevelopers[5] = "Cruis'n World - N64 - 1996";
    soundEffectskDevelopers[6] = "Road Rash - 1999 - N64";
    soundEffectskDevelopers[7] = "Le Tour De France - 2002 - Play Station 2";
    soundEffectskDevelopers[8] = "Mario Kart - 2005 - NDS";
    soundEffectskDevelopers[9] = "Mario Kart 7 - 2011 - Nintendo 3DS";
    soundEffectskDevelopers[10] = "Mario Kart Wii - 2008 - Wii";
    soundEffectskDevelopers[11] = "Mario Kart Tour - 2019 - Android and iOS";

    enterpriseDevelopers2[0] = "Sega, Sega AM2, M2, NEC Corporation, Acclaim Studios London and SEGA Mobile";
    enterpriseDevelopers2[1] = "Taito Corporation, Ocean Software, The Hit Squad and John O'Brien";
    enterpriseDevelopers2[2] = "Sega AM2 and Sega";
    enterpriseDevelopers2[3] = "Sega, Bandai, Virgin Interactive, Sega Wow, Telenet Japan, Acclaim Studios London and SEGA Mobile";
    enterpriseDevelopers2[4] = "Midway Games and WMS Industries";
    enterpriseDevelopers2[5] = "Midway Games and Eurocom";
    enterpriseDevelopers2[6] = "Pacific Coast Power and Light";
    enterpriseDevelopers2[7] = "Konami";
    enterpriseDevelopers2[8] = "Nintendo and Entertainment Analysis and Development";
    enterpriseDevelopers2[9] = "Nintendo, Retro Studios and Nintendo Entertainment Analysis and Development";
    enterpriseDevelopers2[10] = "Nintendo";
    enterpriseDevelopers2[11] = "Nintendo, DeNA and Nintendo Entertainment Analysis and Development";

    // Backgrounds
    string enterpriseDevelopers3[6];

    enterpriseDevelopers3[0] = "Vectezzy";
    enterpriseDevelopers3[1] = "Pngocean";
    enterpriseDevelopers3[2] = "SpriteResource";
    enterpriseDevelopers3[3] = "PgnTree";
    enterpriseDevelopers3[4] = "VectorStock";
    enterpriseDevelopers3[5] = "Compfight ";

    // Sprites

    string sprites[6];

    sprites[0] = "Vectezzy";
    sprites[1] = "PngTree";
    sprites[2] = "SpriteResource";
    sprites[3] = "Vexels";
    sprites[4] = "VectorStock";
    sprites[5] = "Pngocean";

    string enterpriseDevelopers4[4];

    // Global rectangle of the background
    IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
    Sprite sprite(c.textureBackground, background);
    float axis_x = float(c.w.getSize().x) / DEFAULT_WIDTH;
    float axis_y = float(c.w.getSize().y) / DEFAULT_HEIGHT;
    sprite.setScale(axis_x, axis_y);
    c.sBackground = sprite;

    // Partial state of the game
    State state = START;

    // Change the background texture
    c.w.draw(c.sBackground);

    // Control if the start key has been pressed
    bool startPressed = false;

    // Title of te credits animation
    Text creditTitle;
    creditTitle.setCharacterSize(static_cast<unsigned int>(int(45.0f * c.screenScale)));
    creditTitle.setFont(c.fontsMainMenu[0]);
    creditTitle.setFillColor(Color::White);
    creditTitle.setOutlineColor(Color::Black);
    creditTitle.setOutlineThickness(5.0f * c.screenScale);
    creditTitle.setStyle(Text::Bold);

    // Information credits
    Text info;
    info.setCharacterSize(static_cast<unsigned int>(int(19.0f * c.screenScale)));
    info.setFont(c.fontsMainMenu[0]);
    info.setFillColor(Color::White);
    info.setOutlineColor(Color::Black);
    info.setOutlineThickness(5.0f * c.screenScale);
    info.setStyle(Text::Bold);

    // Name of the simulator
    Text simulatorName;
    simulatorName.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
    simulatorName.setFont(c.fontsMainMenu[0]);
    simulatorName.setString("MULTI RACE DRIVING");
    simulatorName.setFillColor(Color::White);
    simulatorName.setOutlineColor(Color::Black);
    simulatorName.setOutlineThickness(5.0f * c.screenScale);
    simulatorName.setStyle(Text::Bold);
    simulatorName.setPosition(c.w.getSize().x / 2.f - simulatorName.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f - 200.f * c.screenScale);

    // Designed text
    Text desginedBy;
    desginedBy.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));
    desginedBy.setFont(c.fontsMainMenu[0]);
    desginedBy.setString("DESIGNED BY");
    desginedBy.setFillColor(Color::White);
    desginedBy.setOutlineColor(Color::Black);
    desginedBy.setOutlineThickness(5.0f * c.screenScale);
    desginedBy.setStyle(Text::Bold);
    desginedBy.setPosition(c.w.getSize().x / 2.f - desginedBy.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f - 80.f * c.screenScale);

    // Author of the simulator
    Text author;
    author.setCharacterSize(static_cast<unsigned int>(int(25.0f * c.screenScale)));
    author.setFont(c.fontsMainMenu[0]);
    author.setString("ZGZINFINITY");
    author.setFillColor(Color::White);
    author.setOutlineColor(Color::Black);
    author.setOutlineThickness(5.0f * c.screenScale);
    author.setStyle(Text::Bold);
    author.setPosition(c.w.getSize().x / 2.f - author.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f - 10.f * c.screenScale);

    // Author of the simulator
    Text year;
    year.setCharacterSize(static_cast<unsigned int>(int(25.0f * c.screenScale)));
    year.setFont(c.fontsMainMenu[0]);
    year.setString("2020");
    year.setFillColor(Color::White);
    year.setOutlineColor(Color::Black);
    year.setOutlineThickness(5.0f * c.screenScale);
    year.setStyle(Text::Bold);
    year.setPosition(c.w.getSize().x / 2.f - year.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f + 70.f * c.screenScale);

    // Brand of the distributor company
    Text brandName;
    brandName.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
    brandName.setFont(c.fontsMainMenu[0]);
    brandName.setString("ZGZ INFINITGAMES ENTERTAINMENT. INC");
    brandName.setFillColor(Color::White);
    brandName.setOutlineColor(Color::Black);
    brandName.setOutlineThickness(5.0f * c.screenScale);
    brandName.setStyle(Text::Bold);
    brandName.setPosition(c.w.getSize().x / 2.f - brandName.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f + 150.f * c.screenScale);

    Text license;
    license.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
    license.setFont(c.fontsMainMenu[0]);
    license.setString("UNDER LICENSE GPL-3.0");
    license.setFillColor(Color::White);
    license.setOutlineColor(Color::Black);
    license.setOutlineThickness(5.0f * c.screenScale);
    license.setStyle(Text::Bold);
    license.setPosition(c.w.getSize().x / 2.f - license.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f + 180.f * c.screenScale);

    Text rights1;
    rights1.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));
    rights1.setFont(c.fontsMainMenu[0]);
    rights1.setString("ALL RIGHTS TO THE MUSIC, SFX AND SPRITES USED");
    rights1.setFillColor(Color::White);
    rights1.setOutlineColor(Color::Black);
    rights1.setOutlineThickness(5.0f * c.screenScale);
    rights1.setStyle(Text::Bold);
    rights1.setPosition(c.w.getSize().x / 2.f - rights1.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f - 120.f * c.screenScale);

    Text rights2;
    rights2.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));
    rights2.setFont(c.fontsMainMenu[0]);
    rights2.setString("BELONG TO THE DEVELOPING ENTERPRISES OF THE ");
    rights2.setFillColor(Color::White);
    rights2.setOutlineColor(Color::Black);
    rights2.setOutlineThickness(5.0f * c.screenScale);
    rights2.setStyle(Text::Bold);
    rights2.setPosition(c.w.getSize().x / 2.f - rights2.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f - 30.f * c.screenScale);

    Text rights3;
    rights3.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));
    rights3.setFont(c.fontsMainMenu[0]);
    rights3.setString("VIDEOGAMES IN WHICH MULTI RACE DRIVING HAS BEEN INSPIRED");
    rights3.setFillColor(Color::White);
    rights3.setOutlineColor(Color::Black);
    rights3.setOutlineThickness(5.0f * c.screenScale);
    rights3.setStyle(Text::Bold);
    rights3.setPosition(c.w.getSize().x / 2.f - rights3.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f + 70.f * c.screenScale);

    Text multiplayer;
    multiplayer.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));
    multiplayer.setFont(c.fontsMainMenu[0]);
    multiplayer.setString("MULTIPLAYER ENGINE POWERED BY BOREAS");
    multiplayer.setFillColor(Color::White);
    multiplayer.setOutlineColor(Color::Black);
    multiplayer.setOutlineThickness(5.0f * c.screenScale);
    multiplayer.setStyle(Text::Bold);
    multiplayer.setPosition(c.w.getSize().x / 2.f - multiplayer.getLocalBounds().width / 2.f,
                              c.w.getSize().y / 2.f - 30.f * c.screenScale);

    // Current animation to display
    int numAnimation = 1;

    // While the console window is opened
    while (c.window.isOpen()) {

        // While the ENTER keyword is not pressed

        while (!startPressed && numAnimation <= 10) {

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }

            // Assign the content of the title
            switch(numAnimation){
                case 3:
                case 4:
                    creditTitle.setString("SOUNDTRACKS");
                    break;
                case 5:
                case 6:
                case 7:
                    creditTitle.setString("SFX");
                    break;
                case 8:
                    creditTitle.setString("BACKGROUNDS");
                    break;
                case 9:
                    creditTitle.setString("SPRITES");
                    break;
                case 10:
                    creditTitle.setString("MULTIPLAYER SUPPORTING");
            }

            // Wait until the time pass displaying the info
            for (int i = 0; i <= 1000; i++){

                // Detect the possible events
                Event e{};
                while (c.window.pollEvent(e)) {
                    if (e.type == Event::Closed) {
                        return EXIT;
                    }
                }

                creditTitle.setPosition((c.w.getSize().x - creditTitle.getGlobalBounds().width) / 2.f,
                                             c.w.getSize().y / 2.f - 250.0f * c.screenScale);

                // Display the animation
                c.w.clear();
                c.w.draw(c.sBackground);
                c.w.draw(creditTitle);

                switch(numAnimation){
                    case 1:
                        // General information of the simulator
                        c.w.draw(simulatorName);
                        c.w.draw(desginedBy);
                        c.w.draw(author);
                        c.w.draw(year);
                        c.w.draw(brandName);
                        c.w.draw(license);
                        break;
                    case 2:
                        c.w.draw(rights1);
                        c.w.draw(rights2);
                        c.w.draw(rights3);
                        break;
                    case 3:
                        // Information of the first soundtrack
                        info.setString(soundtrackDevelopers[0]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 165.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers1[0]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 135.0f * c.screenScale);
                        c.w.draw(info);

                        // Information of the second soundtrack
                        info.setString(soundtrackDevelopers[1]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 80.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers1[1]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 55.0f * c.screenScale);
                        c.w.draw(info);

                        // Information of the third soundtrack
                        info.setString(soundtrackDevelopers[2]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers1[2]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 25.0f * c.screenScale);
                        c.w.draw(info);

                        // Information of the fourth soundtrack
                        info.setString(soundtrackDevelopers[3]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 75.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers1[3]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 105.0f * c.screenScale);
                        c.w.draw(info);

                        // Information of the fourth soundtrack
                        info.setString(soundtrackDevelopers[4]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 155.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers1[4]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 185.0f * c.screenScale);
                        c.w.draw(info);
                        break;
                    case 4:
                         // Information of the first soundtrack
                        info.setString(soundtrackDevelopers[5]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 145.0f * c.screenScale);

                        c.w.draw(info);


                        info.setString(enterpriseDevelopers1[5]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 110.0f * c.screenScale);
                        c.w.draw(info);

                        // Information of the second soundtrack
                        info.setString(soundtrackDevelopers[6]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 60.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers1[6]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 25.0f * c.screenScale);
                        c.w.draw(info);

                        // Information of the third soundtrack
                        info.setString(soundtrackDevelopers[7]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 25.f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers1[7]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 60.0f * c.screenScale);
                        c.w.draw(info);

                        // Information of the fourth soundtrack
                        info.setString(soundtrackDevelopers[8]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 110.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers1[8]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 145.0f * c.screenScale);
                        c.w.draw(info);
                        break;
                    case 5:
                        // Sound effects information
                        info.setString(soundEffectskDevelopers[0]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 165.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers2[0]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 135.0f * c.screenScale);
                        c.w.draw(info);

                        // Information of the second soundtrack
                        info.setString(soundEffectskDevelopers[1]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 80.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers2[1]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 55.0f * c.screenScale);
                        c.w.draw(info);

                        // Information of the third soundtrack
                        info.setString(soundEffectskDevelopers[2]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers2[2]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 25.0f * c.screenScale);
                        c.w.draw(info);

                        // Information of the fourth soundtrack
                        info.setString(soundEffectskDevelopers[3]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 75.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers2[3]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 105.0f * c.screenScale);
                        c.w.draw(info);

                        // Information of the fourth soundtrack
                        info.setString(soundEffectskDevelopers[4]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 155.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers2[4]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 185.0f * c.screenScale);
                        c.w.draw(info);
                        break;
                    case 6:
                        // Sound effects information
                        info.setString(soundEffectskDevelopers[5]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 165.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers2[5]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 135.0f * c.screenScale);
                        c.w.draw(info);

                        // Information of the second soundtrack
                        info.setString(soundEffectskDevelopers[6]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 80.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers2[6]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 55.0f * c.screenScale);
                        c.w.draw(info);

                        // Information of the third soundtrack
                        info.setString(soundEffectskDevelopers[7]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers2[7]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 25.0f * c.screenScale);
                        c.w.draw(info);

                        // Information of the fourth soundtrack
                        info.setString(soundEffectskDevelopers[8]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 75.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers2[8]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 105.0f * c.screenScale);
                        c.w.draw(info);

                        // Information of the fourth soundtrack
                        info.setString(soundEffectskDevelopers[9]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 155.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers2[9]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 185.0f * c.screenScale);
                        c.w.draw(info);
                        break;
                    case 7:
                        // Sound effects information
                        info.setString(soundEffectskDevelopers[10]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 80.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers2[10]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 45.0f * c.screenScale);
                        c.w.draw(info);

                        // Information of the second soundtrack
                        info.setString(soundEffectskDevelopers[11]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 5.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(enterpriseDevelopers2[11]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 40.0f * c.screenScale);
                        c.w.draw(info);
                        break;
                    case 8:
                        // Information of the first font of backgrounds
                        info.setString(enterpriseDevelopers3[0]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 100.0f * c.screenScale);

                        c.w.draw(info);

                        // Information of the second font of backgrounds
                        info.setString(enterpriseDevelopers3[1]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 50.0f * c.screenScale);

                        c.w.draw(info);

                        // Information of the third font of backgrounds
                        info.setString(enterpriseDevelopers3[2]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 0.f * c.screenScale);

                        c.w.draw(info);

                        // Information of the fourth font of backgrounds
                        info.setString(enterpriseDevelopers3[3]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 50.0f * c.screenScale);

                        c.w.draw(info);

                        // Information of the fifth font of backgrounds
                        info.setString(enterpriseDevelopers3[4]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 100.0f * c.screenScale);

                        c.w.draw(info);
                        break;
                    case 9:
                        // Fonts of the sprites of the game

                        info.setString(sprites[0]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 125.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(sprites[1]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(sprites[2]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f - 25.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(sprites[3]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 25.f * c.screenScale);

                        c.w.draw(info);

                        info.setString(sprites[4]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 75.0f * c.screenScale);

                        c.w.draw(info);

                        info.setString(sprites[5]);
                        info.setPosition((c.w.getSize().x - info.getGlobalBounds().width) / 2.f,
                                          c.w.getSize().y / 2.f + 125.0f * c.screenScale);

                        c.w.draw(info);
                        break;
                    case 10:
                        c.w.draw(multiplayer);
                }


                bufferSprite.setTexture(c.w.getTexture(), true);
                c.w.display();
                c.window.draw(bufferSprite);
                c.window.display();

                // Check if the start keyword has been pressed
                if (c.window.hasFocus() && Keyboard::isKeyPressed(Keyboard::Enter)) {
                    // Pass to the second menu
                    startPressed = true;
                    // Stop the soundtrack of the main menu
                    r.soundTracks[0]->stop();
                    r.soundEffects[1]->stop();
                    r.soundEffects[1]->play();
                    state = PLAYER_MENU;
                }
            }
            // Increment the animation to be displayed
            numAnimation++;
        }

        // Control if the pixel art is active and draw the interface with better quality
        if (c.enablePixelArt) {
            if (c.isDefaultScreen)
                c.window.setView(View(Vector2f(DEFAULT_WIDTH / 4.0f, DEFAULT_HEIGHT / 4.0f),
                                      Vector2f(DEFAULT_WIDTH / 2.0f, DEFAULT_HEIGHT / 2.0f)));
            else
                c.window.setView(View(Vector2f(SCREEN_HD_WIDTH / 4.0f, SCREEN_HD_HEIGHT / 4.0f),
                                      Vector2f(SCREEN_HD_WIDTH / 2.0f, SCREEN_HD_HEIGHT / 2.0f)));
            c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
                       static_cast<unsigned int>(c.window.getView().getSize().y));
            c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);
        }

        // Stop the soundtrack of the credits menu and start the soundtrack of the player menu
        r.soundTracks[19]->stop();
        r.soundTracks[0]->play();
        return state;
    }
    return EXIT;
}

