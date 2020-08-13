

#include "../include/Menu.h"


State introAnimation(Configuration &c, SoundPlayer& r) {

    r.soundTracks[0]->play();

    // Vector of images with the logo of Sega
    Texture t;
    Sprite icon;

    // Loading the icon texture
    t.loadFromFile("Data/Animations/IntroAnimation/Icon.png");

    // Load the texture in the sprite reseting the last texture
    icon.setTexture(t, true);
    icon.setScale(c.screenScale, c.screenScale);

    // Iterate throughout all the icons of sega
    for (int i = 1; i < TIME_ANIMATION; i++) {

        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return EXIT;
            }
        }

        icon.setPosition((c.w.getSize().x - icon.getGlobalBounds().width) / 2.0f,
                             (c.w.getSize().y - icon.getGlobalBounds().height) / 2.0f);


        c.w.clear();
        c.w.draw(icon);
        // Show the logos in the console
        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

        // Sleep the process to see the menu icons correctly
        sleep(milliseconds(40));
    }


    // Loading the icon texture
    t.loadFromFile("Data/Animations/IntroAnimation/Presents.png");

    // Load the texture in the sprite reseting the last texture
    icon.setTexture(t, true);
    icon.setScale(c.screenScale, c.screenScale);

    // Iterate throughout all the icons of sega
    for (int i = 1; i < TIME_ANIMATION; i++) {

        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return EXIT;
            }
        }

        icon.setPosition((c.w.getSize().x - icon.getGlobalBounds().width) / 2.0f,
                             (c.w.getSize().y - icon.getGlobalBounds().height) / 2.0f);


        c.w.clear();
        c.w.draw(icon);
        // Show the logos in the console
        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

        // Sleep the process to see the menu icons correctly
        sleep(milliseconds(40));
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
    const int NUM_TEXTS = 6;

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
                                c.w.getSize().y / 2.f + 100.0f * c.screenScale);

    textElements[1].setString(c.contents[1]);
    textElements[1].setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    textElements[1].setFont(c.fontsMainMenu[1]);
    textElements[1].setFillColor(c.colorTexts[1]);
    textElements[1].setOutlineColor(c.colorBorders[1]);
    textElements[1].setOutlineThickness(3.0f * c.screenScale);
    float initialX = c.w.getSize().x - 1.2f * textElements[1].getGlobalBounds().width, initialY =
            c.w.getSize().y - 2.0f * float(textElements[1].getCharacterSize());
    textElements[1].setPosition(initialX, initialY);

    textElements[2].setString(c.contents[2]);
    textElements[2].setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    textElements[2].setFont(c.fontsMainMenu[2]);
    textElements[2].setFillColor(c.colorTexts[2]);
    textElements[2].setOutlineColor(c.colorBorders[2]);
    textElements[2].setOutlineThickness(3.0f * c.screenScale);
    textElements[2].setPosition(initialX - 1.5f * textElements[2].getGlobalBounds().width, initialY);

    initialX = textElements[1].getGlobalBounds().width;
    textElements[3].setString(c.contents[3]);
    textElements[3].setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    textElements[3].setFont(c.fontsMainMenu[3]);
    textElements[3].setFillColor(c.colorTexts[3]);
    textElements[3].setOutlineColor(c.colorBorders[4]);
    textElements[3].setOutlineThickness(3.0f * c.screenScale);
    textElements[3].setPosition(initialX / 2.5f, initialY);

    initialY -= 2.0f * textElements[3].getGlobalBounds().height;
    textElements[4].setString(c.contents[4]);
    textElements[4].setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    textElements[4].setFont(c.fontsMainMenu[4]);
    textElements[4].setFillColor(c.colorTexts[4]);
    textElements[4].setOutlineColor(c.colorBorders[4]);
    textElements[4].setOutlineThickness(3.0f * c.screenScale);
    textElements[4].setPosition(initialX / 2.5f, initialY);

    initialY -= 2.0f * textElements[4].getGlobalBounds().height;
    textElements[5].setString(c.contents[5]);
    textElements[5].setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    textElements[5].setFont(c.fontsMainMenu[5]);
    textElements[5].setFillColor(c.colorTexts[5]);
    textElements[5].setOutlineColor(c.colorBorders[5]);
    textElements[5].setOutlineThickness(3.0f * c.screenScale);
    textElements[5].setPosition(initialX / 2.5f, initialY);

    // Partial state of the game
    State state = START;

    // Change the background texture
    c.w.draw(c.sBackground);

    // Code of sprite to display
    int j = 0;

    float elapsed1, elapsed2;
    Clock blinkClcok;
    Time blink_delay = seconds(1.0);

    blinkClcok.restart().asSeconds();
    elapsed1 = blinkClcok.restart().asSeconds();
    bool blink = true;

    // While the console window is opened
    while (c.window.isOpen()) {
        // While the ENTER keyword is not pressed
        while (!startPressed) {
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

            bufferSprite.setTexture(c.w.getTexture(), true);

            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();

            // Check if the start keyword has been pressed
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                // Pass to the second menu
                startPressed = true;
                // Stop the soundtrack of the main menu
                r.soundTracks[0]->stop();
                r.soundEffects[1]->stop();
                r.soundEffects[1]->play();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Escape)){
                return EXIT;
            }
            j = (j < (int) nameGames.size() - 1) ? j + 1 : 0;
        }

        // Control the second menu
        startPressed = false;
        state = PLAYER_MENU;

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

        while (r.soundEffects[1]->getStatus() == SoundSource::Playing){
            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }
        }

        r.soundTracks[1]->play();
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
        // Check if it is the node that stores the information of the main text of the menu
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
 * Load the configuration of the player menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
State playerMenu(Configuration &c, SoundPlayer& r){

    // The xml configuration file of the player menu has been read
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

    // Control if the backspace key has been pressed
    bool backSpacePressed = false;

    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Control the option selected by the user
    int optionSelected = 0;

    // While start and backspace have not been pressed
    while (!startPressed && !backSpacePressed) {

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

        // Until the start keyword is not pressed
        while (!startPressed && !backSpacePressed) {

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)){
                if (e.type == Event::Closed){
                    return EXIT;
                }
            }

            // Check if the up or down cursor keys have been pressed or not
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                // Up cursor pressed and change the soundtrack selected in the list
                if (optionSelected != int(c.menuPlayerButtons.size() - 1)) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected++;
                    c.menuPlayerButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    c.menuPlayerButtons[optionSelected - 1].setButtonState(BUTTON_IDLE);
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Up)) {
                // Down cursor pressed and change the soundtrack selected in the list
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
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                // Change the controllers of the car
                startPressed = true;
                r.soundEffects[2]->stop();
                r.soundEffects[2]->play();
            }
            // Check if backspace has been pressed
            else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                // Change the controllers of the car
                backSpacePressed = true;
                r.soundEffects[11]->stop();
                r.soundEffects[11]->play();
            }
        }
    }

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

    State status = PLAYER_MENU;

    switch(optionSelected){
        case 0:
            status = GAME_MODES_MENU;
            break;
        case 1:
            status = MULTIPLYER_MENU;
            break;
        case 2:
            status = OPTIONS;
    }

    // Control the backspace key
    if (backSpacePressed){
        r.soundTracks[1]->stop();
        r.soundTracks[0]->play();
        status = START;
    }

    return status;
}




/**
 * Load the configuration of the game modes menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadGameModesMenuConfiguration(const string path, Configuration& c){

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
            // Iterate to get the information of the buttons of the player menu
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
    // The player menu has been read correctly
    c.gameModesMenuRead = true;
}



/**
 * Load the configuration of the game modes menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 * @param typeOfGame is the game mode selected by the player
 */
State gameModesMenu(Configuration &c, SoundPlayer& r, int& typeOfGame){

    // The xml configuration file of the player menu has been read
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));
    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Read the player menu if it has not been read
    if (!c.gameModesMenuRead){
        // Read the player menu xml configuration file
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

    // Control if the backspace key is pressed or not
    bool backSpacePressed = false;

    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Game selected by the user
    int optionSelected;

    // While start is not been pressed
    while (!startPressed && !backSpacePressed) {

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
        panelButton.setFillColor(c.colorDescriptionPanelInsidePlayerMenu);
        panelButton.setOutlineColor(c.colorDescriptionPanelBorderPlayerMenu);
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

        // Until the start keyword or backspace keyword are not pressed
        while (!startPressed && !backSpacePressed) {

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)){
                if (e.type == Event::Closed){
                    return EXIT;
                }
            }

            // Check if the up or down cursor keys have been pressed or not
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                // Up cursor pressed and change the soundtrack selected in the list
                if (optionSelected != int(c.gameModeMenuButtons.size() - 1)) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected++;
                    c.gameModeMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    c.gameModeMenuButtons[optionSelected - 1].setButtonState(BUTTON_IDLE);
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Up)) {
                // Down cursor pressed and change the soundtrack selected in the list
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
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                // Change the controllers of the car
                startPressed = true;
                r.soundEffects[2]->stop();
                r.soundEffects[2]->play();
            }
            // Check if backspace key has been pressed
            else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                // Change the controllers of the car
                backSpacePressed = true;
                r.soundEffects[11]->stop();
                r.soundEffects[11]->play();
            }
        }
    }

    // Control the backspace key has been pressed
    if (backSpacePressed){
        return PLAYER_MENU;
    }
    // Store the game selected by the player
    typeOfGame = optionSelected;

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
        return LOAD_GAME;
    }
    else if (typeOfGame != 3){
        r.soundTracks[1]->stop();
        return VEHICLE_SELECTION;
    }
    else {
        // Stop the soundtrack of the menu
        r.soundTracks[1]->stop();
        return LOAD_GAME;
    }
}



/**
 * Load the configuration of the options menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadOptionsMenuConfiguration(const string path, Configuration& c){

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

    // Iterate to get the information of the player menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check it is the node that contains the information of the background
        if ((string)property->name() == "Background"){
            // Get the background image of the menu
            backgroundTexture = (string)property->value();
            c.optionsMenuBackground.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the player menu
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
            // Iterate to get the information of the buttons of the player menu
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
                                // Creation of the button and addition to the vector
                                posX = c.w.getSize().x / 2.f - 270.0f * c.screenScale;
                                posY = c.w.getSize().y / 2.f - (130.0f - idButton * 70.0f) * c.screenScale;
                                widthButton = 200.0f * c.screenScale;
                                heightButton = 30.0f * c.screenScale;

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
    // The player menu has been read correctly
    c.optionsMenuRead = true;
}



/**
 * Load the configuration of the sound menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadSoundMenuConfiguration(const string path, Configuration& c){

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

    // Iterate to get the information of the player menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check it is the node that contains the information of the background
        if ((string)property->name() == "Background"){
            // Get the background image of the menu
            backgroundTexture = (string)property->value();
            c.soundMenuBackground.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the player menu
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
            // Iterate to get the information of the buttons of the player menu
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
                                // Creation of the button and addition to the vector
                                posX = c.w.getSize().x / 2.f - 270.0f * c.screenScale;
                                posY = c.w.getSize().y / 2.f - (70.0f - idButton * 70.0f) * c.screenScale;
                                widthButton = 200.0f * c.screenScale;
                                heightButton = 30.0f * c.screenScale;

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
    // The player menu has been read correctly
    c.soundMenuRead = true;
}



/**
 * Load the configuration of the sound menu stored in its xml
 * configuration file
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

    // The xml configuration file of the options menu has been read
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
                          200.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenuOptionsButtons, c.soundMenuButtons[0].getTextButton(),
                          c.soundMenuButtons[0].getIdleColorButton(), c.soundMenuButtons[0].getHoverColorButton(),
                          c.soundMenuButtons[0].getFontColorButton(), 1, c.screenScale);

        c.soundMenuButtons[0] = b;

        // Eliminate the buttons of the right column
        for (int i = 1; i < int(c.soundMenuButtons.size()); i++){
            // Change the state of the first color
            Button b = Button(c.w.getSize().x / 2.f - 270.0f * c.screenScale, c.w.getSize().y / 2.f - (70.0f - i * 70.f) * c.screenScale,
                              200.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenuOptionsButtons, c.soundMenuButtons[i].getTextButton(),
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
                             30.0f * c.screenScale, c.fontMenuSoundButtons,
                             to_string(r.volumeMusic), c.soundMenuButtons[0].getIdleColorButton(), c.soundMenuButtons[0].getHoverColorButton(),
                             c.soundMenuButtons[0].getFontColorButton(), 1, c.screenScale);


    c.soundMenuButtons.emplace_back(c.w.getSize().x / 2.f + 80.0f * c.screenScale, c.w.getSize().y / 2.f,
                             200.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenuSoundButtons,
                             to_string(r.volumeEffects), c.soundMenuButtons[1].getIdleColorButton(), c.soundMenuButtons[1].getHoverColorButton(),
                             c.soundMenuButtons[1].getFontColorButton(), 0, c.screenScale);

    // Control if the start key is pressed or not
    bool startPressed = false;

    // Control the option selected by the user
    int optionSelected = 0;

    // Until the start keyword is not pressed
    while (!startPressed) {
        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return EXIT;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            // Up cursor pressed and change the soundtrack selected in the list
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
        else if (Keyboard::isKeyPressed(Keyboard::Up)) {
            // Down cursor pressed and change the soundtrack selected in the list
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
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                if (r.volumeMusic != 0) {
                    r.volumeMusic--;
                    for (int i = 0; i <= 16; i++) {
                        r.soundTracks[i]->setVolume(float(r.volumeMusic));
                        if (i == 14) {
                            r.soundTracks[i]->pause();
                            r.soundTracks[i]->play();
                        }
                    }
                    c.soundMenuButtons[optionSelected + 2].setTextButton((to_string(r.volumeMusic)));
                    c.changeAnyParameter = true;
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Right)) {
                if (r.volumeMusic != 100) {
                    r.volumeMusic++;
                    for (int i = 0; i <= 16; i++) {
                        r.soundTracks[i]->setVolume(float(r.volumeMusic));
                        if (i == 14) {
                            r.soundTracks[i]->pause();
                            r.soundTracks[i]->play();
                        }
                    }
                    c.soundMenuButtons[optionSelected + 2].setTextButton((to_string(r.volumeMusic)));
                    c.changeAnyParameter = true;
                }
            }
        }
        else {
            // Volume effects
            // Check if left or right cursor keys have been pressed or not
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                if (r.volumeEffects != 0) {
                    r.volumeEffects--;
                    for (int i = 0; i <= 42; i++) {
                        r.soundEffects[i]->setVolume(float(r.volumeEffects));
                    }
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    c.soundMenuButtons[optionSelected + 2].setTextButton((to_string(r.volumeEffects)));
                    c.changeAnyParameter = true;
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Right)) {
                if (r.volumeEffects != 100) {
                    r.volumeEffects++;
                    for (int i = 0; i <= 42; i++) {
                        r.soundEffects[i]->setVolume(float(r.volumeEffects));
                    }
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    c.soundMenuButtons[optionSelected + 2].setTextButton((to_string(r.volumeEffects)));
                    c.changeAnyParameter = true;
                }
            }
        }

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

        // Check if left or right cursor keys have been pressed or not
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            // Change the controllers of the car
            startPressed = true;
            c.modifiedConfig = true;
            r.soundEffects[2]->stop();
            r.soundEffects[2]->play();
        }
    }
    c.comeFromSound = true;
    return OPTIONS;
}



/**
 * Load the configuration of the game modes menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
State optionsMenu(Configuration &c, SoundPlayer& r, const bool &inGame){

    // Stop the soundtrack of the player menu
    r.soundTracks[1]->stop();

    // The xml configuration file of the options menu has been read
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
        Button b = Button(c.w.getSize().x / 2.f - 270.0f * c.screenScale, c.w.getSize().y / 2.f - 130.0f * c.screenScale,
                          200.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenuOptionsButtons, c.optionsMenuButtons[0].getTextButton(),
                          c.optionsMenuButtons[0].getIdleColorButton(), c.optionsMenuButtons[0].getHoverColorButton(),
                          c.optionsMenuButtons[0].getFontColorButton(), 1, c.screenScale);

        c.optionsMenuButtons[0] = b;

        // Eliminate the buttons of the right column
        for (int i = 1; i < int(c.optionsMenuButtons.size()); i++){
            // Change the state of the first color
            Button b = Button(c.w.getSize().x / 2.f - 270.0f * c.screenScale, c.w.getSize().y / 2.f - (130.0f - i * 70.f) * c.screenScale,
                              200.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenuOptionsButtons, c.optionsMenuButtons[i].getTextButton(),
                              c.optionsMenuButtons[i].getIdleColorButton(), c.optionsMenuButtons[i].getHoverColorButton(),
                              c.optionsMenuButtons[i].getFontColorButton(), 0, c.screenScale);

            c.optionsMenuButtons[i] = b;
        }
    }

    // Control if the start key is pressed or not
    bool startPressed = false;

    // Control the option selected by the user
    int optionSelected = 0;

    // While the start key and the backspace key have not been pressed
    while (!startPressed) {

        // Clean the console window
        c.w.clear(Color(0, 0, 0));
        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

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

        RectangleShape shape;
        shape.setPosition((c.w.getSize().x / 2.f) - 350.0f * c.screenScale, c.w.getSize().y / 2.f - 250.0f * c.screenScale);
        shape.setSize(sf::Vector2f(710.0f * c.screenScale, 500.0f * c.screenScale));
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
                                 c.w.getSize().y / 2.f - 230.0f * c.screenScale);

        // Option configurations

        string difficulty;
        switch (c.level) {
            case PEACEFUL:
                difficulty = "Peaceful";
                break;
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

        const string submenu = "Menu", access = "Press Enter", saved = "Saved!";

        c.optionsMenuButtons.emplace_back(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                          c.w.getSize().y / 2.f - 130.0f * c.screenScale, 200.0f * c.screenScale,
                                          30.0f * c.screenScale, c.fontMenuPlayerButtons,
                                          difficulty, c.optionsMenuButtons[0].getIdleColorButton(),
                                          c.optionsMenuButtons[0].getHoverColorButton(),
                                          c.optionsMenuButtons[0].getFontColorButton(), 1, c.screenScale);

        c.optionsMenuButtons.emplace_back(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                          c.w.getSize().y / 2.f - 60.0f * c.screenScale, 200.0f * c.screenScale,
                                          30.0f * c.screenScale, c.fontMenuPlayerButtons,
                                          c.enableAI ? "Enabled" : "Disabled", c.optionsMenuButtons[1].getIdleColorButton(),
                                          c.optionsMenuButtons[1].getHoverColorButton(),
                                          c.optionsMenuButtons[1].getFontColorButton(), 0, c.screenScale);

        c.optionsMenuButtons.emplace_back(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                          c.w.getSize().y / 2.f + 10.0f * c.screenScale, 200.0f * c.screenScale,
                                          30.0f * c.screenScale, c.fontMenuPlayerButtons,
                                          submenu, c.optionsMenuButtons[2].getIdleColorButton(),
                                          c.optionsMenuButtons[2].getHoverColorButton(),
                                          c.optionsMenuButtons[2].getFontColorButton(), 0, c.screenScale);

        c.optionsMenuButtons.emplace_back(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                          c.w.getSize().y / 2.f + 80.0f * c.screenScale, 200.0f * c.screenScale,
                                          30.0f * c.screenScale, c.fontMenuPlayerButtons,
                                          submenu, c.optionsMenuButtons[3].getIdleColorButton(),
                                          c.optionsMenuButtons[3].getHoverColorButton(),
                                          c.optionsMenuButtons[3].getFontColorButton(), 0, c.screenScale);

        c.optionsMenuButtons.emplace_back(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                          c.w.getSize().y / 2.f + 150.0f * c.screenScale, 200.0f * c.screenScale,
                                          30.0f * c.screenScale, c.fontMenuPlayerButtons,
                                          submenu, c.optionsMenuButtons[4].getIdleColorButton(),
                                          c.optionsMenuButtons[4].getHoverColorButton(),
                                          c.optionsMenuButtons[4].getFontColorButton(), 0, c.screenScale);


        // Until the start keyword and the backspace keyword have not pressed
        while (!startPressed) {
            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)){
                if (e.type == Event::Closed){
                    return EXIT;
                }
            }

            // Check if the up or down cursor keys have been pressed or not
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                // Up cursor pressed and change the soundtrack selected in the list
                if (optionSelected != int(c.optionsMenuButtons.size() - 1) / 2) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected++;
                    c.optionsMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    c.optionsMenuButtons[optionSelected - 1].setButtonState(BUTTON_IDLE);
                    c.optionsMenuButtons[optionSelected + 5].setButtonState(BUTTON_HOVER);
                    c.optionsMenuButtons[optionSelected + 4].setButtonState(BUTTON_IDLE);
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Up)) {
                // Down cursor pressed and change the soundtrack selected in the list
                if (optionSelected != 0) {
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected--;
                    // Change the color appearance of both buttons
                    c.optionsMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    c.optionsMenuButtons[optionSelected + 1].setButtonState(BUTTON_IDLE);
                    c.optionsMenuButtons[optionSelected + 5].setButtonState(BUTTON_HOVER);
                    c.optionsMenuButtons[optionSelected + 6].setButtonState(BUTTON_IDLE);
                }
            }


            // Modify the option parameter if it's necessary
            switch (optionSelected) {
                case 0:
                    // Check if left or right cursor keys have been pressed or not
                    if (Keyboard::isKeyPressed(Keyboard::Left)) {
                        if (c.level != PEACEFUL) {

                            r.soundEffects[0]->stop();
                            r.soundEffects[0]->play();

                            // Change the difficult level
                            if (c.level == EASY) {
                                c.level = PEACEFUL;
                                c.optionsMenuButtons[optionSelected + 5].setTextButton("Peaceful");
                            }
                            if (c.level == NORMAL) {
                                c.level = EASY;
                                c.optionsMenuButtons[optionSelected + 5].setTextButton("Easy");
                            }
                            else if (c.level == HARD) {
                                c.level = NORMAL;
                                c.optionsMenuButtons[optionSelected + 5].setTextButton("Normal");
                            }
                            c.changeAnyParameter = true;
                        }
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Right)) {
                        if (c.level != HARD) {

                            r.soundEffects[0]->stop();
                            r.soundEffects[0]->play();

                            // Change the difficult level
                            if (c.level == PEACEFUL) {
                                c.level = EASY;
                                c.optionsMenuButtons[optionSelected + 5].setTextButton("Easy");
                            }
                            if (c.level == EASY) {
                                c.level = NORMAL;
                                c.optionsMenuButtons[optionSelected + 5].setTextButton("Normal");
                            }
                            else if (c.level == NORMAL) {
                                c.level = HARD;
                                c.optionsMenuButtons[optionSelected + 5].setTextButton("Hard");
                            }
                            c.changeAnyParameter = true;
                        }
                    }
                    break;
                case 1:
                    // AI aggressiveness level
                    // Check if left or right cursor keys have been pressed or not
                    if (Keyboard::isKeyPressed(Keyboard::Left)) {
                        if (c.enableAI) {
                            r.soundEffects[0]->stop();
                            r.soundEffects[0]->play();
                            c.enableAI = false;
                            c.optionsMenuButtons[optionSelected + 5].setTextButton("Disabled");
                            c.changeAnyParameter = true;
                        }
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Right)) {
                        if (!c.enableAI) {
                            r.soundEffects[0]->stop();
                            r.soundEffects[0]->play();
                            c.enableAI = true;
                            c.optionsMenuButtons[optionSelected + 5].setTextButton("Enabled");
                            c.changeAnyParameter = true;
                        }
                    }

                    c.optionsMenuButtons[optionSelected + 6].setTextButton(submenu);
                    break;
                case 2:
                    // Change the volume of the game
                    c.optionsMenuButtons[optionSelected + 5].setTextButton(access);

                    // Check if left or right cursor keys have been pressed or not
                    if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                        r.soundEffects[1]->stop();
                        r.soundEffects[1]->play();
                        State status = soundMenu(c, r, inGame);
                        if (status == EXIT) {
                            return status;
                        }
                        if (c.modifiedConfig) {
                            c.optionsMenuButtons[optionSelected + 5].setTextButton(saved);
                        }
                    }

                    c.optionsMenuButtons[optionSelected + 6].setTextButton(submenu);
                    break;
                case 3:
                    // Change the graphics of the game
                    c.optionsMenuButtons[optionSelected + 5].setTextButton(access);

                    // Check if left or right cursor keys have been pressed or not
                    if (Keyboard::isKeyPressed(Keyboard::Enter)) {
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

                            // Main Text of the menu
                            optionsText.setString(c.contentTitleOptionsMenu);
                            optionsText.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));
                            optionsText.setFont(c.fontOptionsMenu);
                            optionsText.setStyle(Text::Bold | Text::Underlined);
                            optionsText.setFillColor(c.colorTitleTextOptionsMenu);
                            optionsText.setOutlineColor(c.colorTitleBorderOptionsMenu);
                            optionsText.setOutlineThickness(5.0f * c.screenScale);
                            optionsText.setPosition((c.w.getSize().x / 2.f) - optionsText.getLocalBounds().width / 2.f,
                                                     c.w.getSize().y / 2.f - 230.0f * c.screenScale);

                            c.optionsMenuButtons[optionSelected + 5].setTextButton(saved);
                            shape.setPosition((c.w.getSize().x / 2.f) - 350.0f * c.screenScale,
                                              c.w.getSize().y / 2.f - 250.0f * c.screenScale);
                            shape.setSize(sf::Vector2f(710.0f * c.screenScale, 500.0f * c.screenScale));
                            optionsText.setPosition((c.w.getSize().x / 2.f) - 90.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 230.0f * c.screenScale);
                            optionsText.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));

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
                                posY = c.w.getSize().y / 2.f - (130.0f - idButton * 70.0f) * c.screenScale;
                                widthButton = 200.0f * c.screenScale;
                                heightButton = 30.0f * c.screenScale;

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
                            posY = c.w.getSize().y / 2.f - (130.0f - idButton * 70.0f) * c.screenScale;
                            widthButton = 200.0f * c.screenScale;
                            heightButton = 30.0f * c.screenScale;

                            b = Button(posX, posY, widthButton, heightButton, c.fontMenuPlayerButtons,
                                           c.optionsMenuButtons[i].getTextButton(), c.optionsMenuButtons[i].getIdleColorButton(),
                                           c.optionsMenuButtons[i].getHoverColorButton(),
                                           c.optionsMenuButtons[i].getFontColorButton(), 0, c.screenScale);

                            // Replace the all button by the new one
                            c.optionsMenuButtons[i] = b;

                            i++;
                            b = Button(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                       c.w.getSize().y / 2.f - 130.0f * c.screenScale,
                                       200.0f * c.screenScale,
                                       30.0f * c.screenScale, c.fontMenuPlayerButtons,
                                       difficulty, c.optionsMenuButtons[i - 5].getIdleColorButton(),
                                       c.optionsMenuButtons[i - 5].getHoverColorButton(),
                                       c.optionsMenuButtons[i - 5].getFontColorButton(), 0, c.screenScale);
                            c.optionsMenuButtons[i] = b;

                            i++;
                            b = Button(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                       c.w.getSize().y / 2.f - 60.0f * c.screenScale,
                                       200.0f * c.screenScale,
                                       30.0f * c.screenScale, c.fontMenuPlayerButtons,
                                       c.enableAI ? "Enabled" : "Disabled", c.optionsMenuButtons[i - 5].getIdleColorButton(),
                                       c.optionsMenuButtons[i - 5].getHoverColorButton(),
                                       c.optionsMenuButtons[i - 5].getFontColorButton(), 0, c.screenScale);
                            c.optionsMenuButtons[i] = b;

                            i++;
                            b = Button(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                       c.w.getSize().y / 2.f + 10.0f * c.screenScale,
                                       200.0f * c.screenScale,
                                       30.0f * c.screenScale, c.fontMenuPlayerButtons,
                                       submenu, c.optionsMenuButtons[i - 5].getIdleColorButton(),
                                       c.optionsMenuButtons[i - 5].getHoverColorButton(),
                                       c.optionsMenuButtons[i - 5].getFontColorButton(), 0, c.screenScale);
                            c.optionsMenuButtons[i] = b;

                            i++;
                            b = Button(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                       c.w.getSize().y / 2.f + 80.0f * c.screenScale,
                                       200.0f * c.screenScale,
                                       30.0f * c.screenScale, c.fontMenuPlayerButtons,
                                       submenu, c.optionsMenuButtons[i - 5].getIdleColorButton(),
                                       c.optionsMenuButtons[i - 5].getHoverColorButton(),
                                       c.optionsMenuButtons[i - 5].getFontColorButton(), 1, c.screenScale);
                            c.optionsMenuButtons[i] = b;

                            i++;
                            b = Button(c.w.getSize().x / 2.f + 80.0f * c.screenScale,
                                       c.w.getSize().y / 2.f + 150.0f * c.screenScale,
                                       200.0f * c.screenScale,
                                       30.0f * c.screenScale, c.fontMenuPlayerButtons,
                                       submenu, c.optionsMenuButtons[i - 5].getIdleColorButton(),
                                       c.optionsMenuButtons[i - 5].getHoverColorButton(),
                                       c.optionsMenuButtons[i - 5].getFontColorButton(), 0, c.screenScale);
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

                    c.optionsMenuButtons[optionSelected + 4].setTextButton(submenu);
                    c.optionsMenuButtons[optionSelected + 6].setTextButton(submenu);
                    break;
                case 4:
                    // Change the controllers of the game
                    c.optionsMenuButtons[optionSelected + 5].setTextButton(access);

                    // Check if left or right cursor keys have been pressed or not
                    if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                        // Change the controllers of the car
                        r.soundEffects[1]->stop();
                        r.soundEffects[1]->play();
                        State status = vehicleControllersMenu(c, r);
                        if (status == EXIT) {
                            return status;
                        }
                        if (c.modifiedConfig) {
                            c.optionsMenuButtons[optionSelected + 5].setTextButton(saved);
                        }
                    }

                    c.optionsMenuButtons[optionSelected + 4].setTextButton(submenu);
                    break;
                default:
                    break;
            }

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

            // Check if the start key has been pressed
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                // Change the controllers of the car
                startPressed = true;
                r.soundEffects[2]->stop();
                r.soundEffects[2]->play();
            }
        }
        r.soundTracks[14]->stop();

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

        int index = kM.lookForKeyBoardId(c.leftKey);
        string controlLeft = kM.mapperIdKeyWord[index];

        // Get the keyword to control the turn to the left
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

        // Update the file
        updateGameConfiguration(path, c.level, c.enableAI, r.volumeMusic, r.volumeEffects, c.enablePixelArt, c.resIndex,
                                c.resolutions[c.resIndex].first, c.resolutions[c.resIndex].second, controlLeft, controlRight,
                                controlAccelerate, controlBrake, controlSoundtrack);

        c.changeAnyParameter = false;
    }

    if (inGame) {
        return PLAY_GAME;
    }
    else {
        // Reproduce the soundtrack of the player menu
        r.soundTracks[1]->play();
        return playerMenu(c, r);
    }
}



/**
 * Load the configuration of the vehicle controllers menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void loadVehicleControllersMenuConfiguration(const string path, Configuration& c){
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

    // Iterate to get the information of the player menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check it is the node that contains the information of the background
        if ((string)property->name() == "Background"){
            // Get the background image of the menu
            backgroundTexture = (string)property->value();
            c.vehicleControllersMenuBackground.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the player menu
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
            // Iterate to get the information of the buttons of the player menu
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
    // The player menu has been read correctly
    c.vehicleControllersMenuRead = true;
}



/**
 * Load the configuration of the vehicle controllers menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
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


    // Control if the start key is pressed or not
    bool startPressed = false;

    // Control the option selected by the user
    int optionSelected = 0;

    // Until the start keyword is not pressed
    while (!startPressed) {
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
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            // Up cursor pressed and change the soundtrack selected in the list
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
        else if (Keyboard::isKeyPressed(Keyboard::Up)) {
            // Down cursor pressed and change the soundtrack selected in the list
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
        while (Keyboard::isKeyPressed(Keyboard::Space) && !Keyboard::isKeyPressed(Keyboard::Enter)) {
            // Check if any keyword has been pressed or not
            c.window.waitEvent(e);
            if (e.type == Event::KeyPressed && e.key.code != -1 && e.key.code != Keyboard::Enter &&
                e.key.code != Keyboard::Space) {
                // Modify the option parameter if it's necessary
                switch (optionSelected) {
                    case 0:
                        if (kM.mapperCodeKeyWord[e.key.code] == c.rightKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.accelerateKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.brakeKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.soundtrackKey) {
                            r.soundEffects[3]->stop();
                            r.soundEffects[3]->play();
                        }
                        else {
                            c.vehicleControllersMenuButtons[optionSelected + 5].setTextButton(kM.mapperIdKeyWord[e.key.code]);
                            c.leftKey = kM.mapperCodeKeyWord[e.key.code];
                            r.soundEffects[1]->stop();
                            r.soundEffects[1]->play();
                            c.changeAnyParameter = true;
                        }
                        break;
                    case 1:
                        // Get the code of the keyword if it's not the up pr down cursor keys
                        if (kM.mapperCodeKeyWord[e.key.code] == c.leftKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.accelerateKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.brakeKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.soundtrackKey) {
                            r.soundEffects[3]->stop();
                            r.soundEffects[3]->play();
                        }
                        else {
                            c.vehicleControllersMenuButtons[optionSelected + 5].setTextButton(kM.mapperIdKeyWord[e.key.code]);
                            c.rightKey = kM.mapperCodeKeyWord[e.key.code];
                            r.soundEffects[1]->stop();
                            r.soundEffects[1]->play();
                            c.changeAnyParameter = true;
                        }
                        break;
                    case 2:
                        // Get the code of the keyword if it's not the up pr down cursor keys
                        if (kM.mapperCodeKeyWord[e.key.code] == c.leftKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.rightKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.brakeKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.soundtrackKey) {
                            r.soundEffects[3]->stop();
                            r.soundEffects[3]->play();
                        }
                        else {
                            c.vehicleControllersMenuButtons[optionSelected + 5].setTextButton(kM.mapperIdKeyWord[e.key.code]);
                            c.accelerateKey = kM.mapperCodeKeyWord[e.key.code];
                            r.soundEffects[1]->stop();
                            r.soundEffects[1]->play();
                            c.changeAnyParameter = true;
                        }
                        break;
                    case 3:
                        // Get the code of the keyword if it's not the up pr down cursor keys
                        if (kM.mapperCodeKeyWord[e.key.code] == c.leftKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.rightKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.accelerateKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.soundtrackKey) {
                            r.soundEffects[3]->stop();
                            r.soundEffects[3]->play();
                        }
                        else {
                            c.vehicleControllersMenuButtons[optionSelected + 5].setTextButton(kM.mapperIdKeyWord[e.key.code]);
                            c.brakeKey = kM.mapperCodeKeyWord[e.key.code];
                            r.soundEffects[1]->stop();
                            r.soundEffects[1]->play();
                            c.changeAnyParameter = true;
                        }
                        break;
                    case 4:
                        // Get the code of the keyword if it's not the up pr down cursor keys
                        if (kM.mapperCodeKeyWord[e.key.code] == c.leftKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.rightKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.accelerateKey ||
                            kM.mapperCodeKeyWord[e.key.code] == c.brakeKey) {
                            r.soundEffects[3]->stop();
                            r.soundEffects[3]->play();
                        }
                        else {
                            c.vehicleControllersMenuButtons[optionSelected + 5].setTextButton(kM.mapperIdKeyWord[e.key.code]);
                            c.soundtrackKey = kM.mapperCodeKeyWord[e.key.code];
                            r.soundEffects[1]->stop();
                            r.soundEffects[1]->play();
                            c.changeAnyParameter = true;
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        // Check if left or right cursor keys have been pressed or not
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            // Change the controllers of the car
            startPressed = true;
            c.modifiedConfig = true;
            r.soundEffects[2]->stop();
            r.soundEffects[2]->play();
        }
    }
    return OPTIONS;
}



State rankingMenu(Configuration &c, SoundPlayer& r, const unsigned long scorePlayerGame, const int minutes, const int secs,
                  const int cents_Second, const int typeOfGame)
{

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

    KeywordMapper kM = KeywordMapper();

    r.soundTracks[r.currentSoundtrack]->stop();

    Clock rankingTime, blinkStart;

    Time ranking_delay = seconds(1.f);

    int time = 28;
    float elapsed1, elapsed2, elapsed3, elapsed4;

    r.soundTracks[12]->play();

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
    rankingBackground.loadFromFile("Data/RankingMenu/bg.png");
    Sprite palm_trees(rankingBackground);
    palm_trees.setScale((float) c.w.getSize().x / rankingBackground.getSize().x,
                        (float) c.w.getSize().y / rankingBackground.getSize().y);

    // Get the best seventh out runners
    vector<Score> scoreRankingPlayer = getGlobalScores(c, typeOfGame);

    // Check if there is a new record
    int record = isNewRecord(scoreRankingPlayer, scorePlayerGame);
    bool startPressed = false;
    bool blink = false;
    int lettersIntroduced = 0;
    string name = "_";

    rankingTime.restart();
    elapsed1 = rankingTime.getElapsedTime().asSeconds();
    elapsed3 = blinkStart.getElapsedTime().asSeconds();

    r.soundEffects[29]->play();
    Event e{};

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
                } else if (event.type == Event::KeyPressed) {
                    // Get code of the key
                    int code = event.key.code;
                    // Check if the key pressed is a letter or not
                    if (code >= 0 && code <= 25) {
                        lettersIntroduced++;
                        string keyLetter = kM.mapperIdKeyWord[code];
                        if (name == "_") {
                            name = keyLetter;
                            r.soundEffects[1]->stop();
                            r.soundEffects[1]->play();
                        } else {
                            if (lettersIntroduced == 3) {
                                name = name.substr(0, name.size() - 1);
                                name += keyLetter;
                                r.soundEffects[2]->stop();
                                r.soundEffects[2]->play();
                            } else {
                                name += keyLetter + "_";
                                r.soundEffects[1]->stop();
                                r.soundEffects[1]->play();
                            }
                        }
                    } else {
                        r.soundEffects[3]->stop();
                        r.soundEffects[3]->play();
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(c.menuEnterKey)) {
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
        saveNewRecord(scoreRankingPlayer, s, typeOfGame, c);
    }

    r.soundEffects[2]->stop();
    r.soundEffects[2]->play();
    r.soundEffects[29]->stop();
    r.soundTracks[12]->stop();

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



// Update the file
void updateGameConfiguration(const string path, const Difficult difficulty, const bool activeAI, const int volumeSoundtracks,
                             const int volumeEffects, const bool pixelArt, const int fullScreen, const int axis_x, const int axis_y,
                             const string controlLeft, const string controlRight, const string controlAccelerate, const string controlBrake,
                             const string controlSoundtrack)
{
    // xml file which stores the player with the highest score in the level
    ofstream theFile (path);
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
    string level;
    switch(difficulty){
        case 0:
            level = "Peaceful";
            break;
        case 1:
            level = "Easy";
            break;
        case 2:
            level = "Normal";
            break;
        case 3:
            level = "Hard";
    }
    levelDifficulty->value(level.c_str());

    // Create the node of the AI level
    xml_node<>* levelAI = doc.allocate_node(node_element, "AI");
    root->append_node(levelAI);
    string active;
    if (activeAI){
        active = "Enabled";
    }
    else {
        active = "Disabled";
    }
    levelAI->value(active.c_str());

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
    string activePixelArt;
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
    string activeFullScreen;
    if (fullScreen == -1){
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



State showLoadingAnimation(Configuration& c, SoundPlayer& r){

    // The xml configuration file of the player menu has been read
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

    int totalPoints, offsetText;
    if (c.isDefaultScreen){
        totalPoints = 25;
        offsetText = 235;
    }
    else {
        totalPoints = 35;
        offsetText = 205;
    }


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

    // Buttons of the menu
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

    // Right buttons
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
            if (e.type == Event::Closed){
                return EXIT;
            }
        }

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

        sleep(milliseconds(350));
    }

    // Reproduce the soundtrack of the game
    r.soundTracks[17]->stop();

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

