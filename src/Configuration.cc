
#include "../include/Configuration.h"

Configuration::Configuration(const Difficult difficulty, const bool activeAI, const bool pixelArt, const bool fullScreen, const int axis_x,
                             const int axis_y, const string controlLeft,const string controlRight, const string controlAccelerate,
                             const string controlBrake, const string controlSoundtrack)
                             : resolutions({SCREEN_DEFAULT, SCREEN_1, SCREEN_2, SCREEN_3, SCREEN_4, SCREEN_5}), camD(0.87), renderLen(450)
{
    if (axis_x == DEFAULT_WIDTH && axis_y == DEFAULT_HEIGHT){
        isDefaultScreen = true;
        resIndex = 0;
    }
    else {
        isDefaultScreen = false;
    }

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

    if (!fullScreen){
        window.create(VideoMode(static_cast<unsigned int>(resolutions[resIndex].first),
                                static_cast<unsigned int>(resolutions[resIndex].second)), "Multi Race Driving",
                      Style::Titlebar | Style::Close);
    }
    else {
        window.create(VideoMode::getFullscreenModes()[0], "Out Run", Style::Fullscreen);
        resIndex = -1;
    }

    window.setFramerateLimit(FPS);
    window.setKeyRepeatEnabled(false);

    mainMenuRead = false;
    playerMenuRead = false;
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

    w.create(static_cast<unsigned int>(window.getView().getSize().x),
             static_cast<unsigned int>(window.getView().getSize().y));

    window.setView(View(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f),
                          Vector2f(window.getSize().x, window.getSize().y)));
    w.create(static_cast<unsigned int>(window.getView().getSize().x),
               static_cast<unsigned int>(window.getView().getSize().y));

    screenScale = float(w.getSize().x) / float(DEFAULT_WIDTH);

    if (isDefaultScreen){
        imageOffset = IMAGE_DEFAULT_OFFSET;
        thresholdDescriptionX = SCREEN_HD_HEIGHT;
        thresholdDescriptionY = VERTICAL_OFFSET;
    }
    else {
        thresholdDescriptionX = w.getSize().x * SCREEN_HD_HEIGHT / DEFAULT_WIDTH;
        thresholdDescriptionY = int((w.getSize().y * VERTICAL_OFFSET / DEFAULT_HEIGHT) * 1.2f);
        imageOffset = float(w.getSize().y) * IMAGE_DEFAULT_OFFSET / DEFAULT_HEIGHT;
    }

    Image i;
    i.loadFromFile("Data/Icon/Multi_Race_Driving.png");
    window.setIcon(i.getSize().x, i.getSize().y, i.getPixelsPtr());

    screenScale = float(w.getSize().x) / float(DEFAULT_WIDTH);

    menuKey = Keyboard::Escape;
    menuUpKey = Keyboard::Up;
    menuDownKey = Keyboard::Down;
    menuEnterKey = Keyboard::Enter;

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

    fontElapsedTime = initializeFontElapsedTime();

    fontTimeToPlay = initializeFontTimeToPlay();

    fontMenus = initializeFontMenus();

    fontScore = initializeFontScore();

    speedVehicle = initializeFontElapsedTime();

    options = initializeFontOptions();

    level = difficulty;

    modifiedConfig = false;
    changeAnyParameter = false;

    maxAggressiveness = 0.0f;
    enableAI = activeAI;
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

    // Iterate to get the information of the player menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check it is the node that contains the information of the background
        if ((string)property->name() == "Background"){
            // Get the background image of the menu
            backgroundTexture = (string)property->value();
            graphicsMenuBackground.loadFromFile(backgroundTexture);
        }
        // Check it is the node that contains the information of the main panel
        else if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the player menu
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
        // Check if it is the node that the different buttons of the menu
        else if ((string)property->name() == "MenuButtons"){
            // Iterate to get the information of the buttons of the player menu
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
                    // Iterate to get the information of the player menu
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
                        }
                    }
                }
            }
        }
    }
    // The player menu has been read correctly
    graphicsMenuRead = true;
}



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


        graphicsMenuBackground.setRepeated(true);
        graphicsMenuPanelBack.setRepeated(true);

        IntRect background(0, 0, w.getSize().x, w.getSize().y);
        Sprite sprite(graphicsMenuBackground, background);
        float axis_x = float(w.getSize().x) / DEFAULT_WIDTH;
        float axis_y = float(w.getSize().y) / DEFAULT_HEIGHT;
        sprite.setScale(axis_x, axis_y);
        ghMenuBackground = sprite;

        RectangleShape shape;
        shape.setPosition((w.getSize().x / 2.f) - 300.0f * screenScale, w.getSize().y / 2.f - 250.0f * screenScale);
        shape.setSize(sf::Vector2f(610.0f * screenScale, 500.0f * screenScale));
        shape.setOutlineColor(colorBorderPanelGraphicsMenu);
        shape.setOutlineThickness(5.0f * screenScale);
        shape.setTexture(&graphicsMenuPanelBack, true);

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
                                 200.0f * screenScale, 30.0f * screenScale, fontMenuGraphicsButtons,
                                 contentButtonsGraphics[0], colorButtons[0], colorButtons[1], colorFontMenuGraphicsButtons, 1, screenScale);

        menuButtons.emplace_back(w.getSize().x / 2.f - 270.0f * screenScale, w.getSize().y / 2.f, 200.0f * screenScale,
                                 30.0f * screenScale, fontMenuGraphicsButtons,
                                 contentButtonsGraphics[1], colorButtons[2], colorButtons[3], colorFontMenuGraphicsButtons, 0, screenScale);

        // Option configurations
        const string res = resIndex > -1 ? to_string(resolutions[resIndex].first) + "x" +
                                           to_string(resolutions[resIndex].second) : "FULLSCREEN";
        menuButtons.emplace_back(w.getSize().x / 2.f + 80.0f * screenScale, w.getSize().y / 2.f - 70.0f * screenScale,
                                 200.0f * screenScale, 30.0f * screenScale, fontMenuGraphicsButtons,
                                 res, colorButtons[0], colorButtons[1], colorFontMenuGraphicsButtons, 1, screenScale);

        menuButtons.emplace_back(w.getSize().x / 2.f + 80.0f * screenScale, w.getSize().y / 2.f, 200.0f * screenScale,
                                 30.0f * screenScale, fontMenuGraphicsButtons,
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
            if (Keyboard::isKeyPressed(menuDownKey)) {
                // Up cursor pressed and change the soundtrack selected in the list
                if (optionSelected != int(menuButtons.size() - 1) / 2) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->play();
                    optionSelected++;
                    menuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                    menuButtons[optionSelected - 1].setButtonState(BUTTON_IDLE);
                    menuButtons[optionSelected + 2].setButtonState(BUTTON_HOVER);
                    menuButtons[optionSelected + 1].setButtonState(BUTTON_IDLE);
                }
            }
            else if (Keyboard::isKeyPressed(menuUpKey)) {
                // Down cursor pressed and change the soundtrack selected in the list
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
                // Volume music
                // Check if left or right cursor keys have been pressed or not
                if (Keyboard::isKeyPressed(Keyboard::Left)) {
                    if (resized) {
                        resized = false;
                    } else if (resIndex > -1) {
                        resIndex--;
                        menuButtons[optionSelected + 2].setTextButton(resIndex > -1 ?
                                                                      to_string(resolutions[resIndex].first) + "x" +
                                                                      to_string(resolutions[resIndex].second)
                                                                                    : "FULLSCREEN");
                        if (resIndex > -1) {
                            window.create(VideoMode(static_cast<unsigned int>(resolutions[resIndex].first),
                                                    static_cast<unsigned int>(resolutions[resIndex].second)),
                                          "Multi Race Driving",
                                          Style::Titlebar | Style::Close);
                            fullScreen = true;
                        }
                        else {
                            window.create(VideoMode::getFullscreenModes()[0], "Multi Race Driving", Style::Fullscreen);
                            fullScreen = false;
                        }
                        window.setFramerateLimit(FPS);
                        window.setKeyRepeatEnabled(false);

                        isDefaultScreen = resIndex == 0;


                        window.setView(View(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f),
                                            Vector2f(window.getSize().x, window.getSize().y)));
                        w.create(static_cast<unsigned int>(window.getView().getSize().x),
                                 static_cast<unsigned int>(window.getView().getSize().y));

                        screenScale = float(w.getSize().x) / float(DEFAULT_WIDTH);
                        currentResized = true;
                        resized = true;

                    }
                    thresholdDescriptionX = w.getSize().x * SCREEN_HD_HEIGHT / DEFAULT_WIDTH;
                    thresholdDescriptionY = int((w.getSize().y * VERTICAL_OFFSET / DEFAULT_HEIGHT) * 1.2f);
                    imageOffset = float(w.getSize().y) * IMAGE_DEFAULT_OFFSET / DEFAULT_HEIGHT;
                }
                else if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    if (resized) {
                        resized = false;
                    }
                    if (resIndex < int(resolutions.size()) - 1 && !resized) {
                        resIndex++;
                        menuButtons[optionSelected + 2].setTextButton(to_string(resolutions[resIndex].first) + "x" +
                                                                      to_string(resolutions[resIndex].second));

                        window.create(VideoMode(static_cast<unsigned int>(resolutions[resIndex].first),
                                                static_cast<unsigned int>(resolutions[resIndex].second)), "Multi Race Driving",
                                      Style::Titlebar | Style::Close);
                        window.setFramerateLimit(FPS);
                        window.setKeyRepeatEnabled(false);



                        isDefaultScreen = resIndex == 0;


                        window.setView(View(Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f),
                                            Vector2f(window.getSize().x, window.getSize().y)));
                        w.create(static_cast<unsigned int>(window.getView().getSize().x),
                                 static_cast<unsigned int>(window.getView().getSize().y));

                        screenScale = float(w.getSize().x) / float(DEFAULT_WIDTH);
                        currentResized = true;
                        resized = true;
                    }
                }
                thresholdDescriptionX = (w.getSize().x * SCREEN_HD_HEIGHT / DEFAULT_WIDTH);
                thresholdDescriptionY = int((w.getSize().y * VERTICAL_OFFSET / DEFAULT_HEIGHT) * 1.2f);
                imageOffset = float(w.getSize().y) * IMAGE_DEFAULT_OFFSET / DEFAULT_HEIGHT;
            }
            else {
                // Volume effects
                // Check if left or right cursor keys have been pressed or not
                if (Keyboard::isKeyPressed(Keyboard::Left)) {
                    if (enablePixelArt) {
                        enablePixelArt = false;
                        menuButtons[optionSelected + 2].setTextButton("Disabled");
                    }
                }
                else if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    if (!enablePixelArt) {
                        enablePixelArt = true;
                        menuButtons[optionSelected + 2].setTextButton("Enabled");
                    }
                }
            }
            w.draw(sprite);
            w.draw(shape);
            w.draw(optionsText);

            // Show the buttons of the menu
            for (auto &menuButton : menuButtons) {
                menuButton.render(&w);
            }

            bufferSprite.setTexture(w.getTexture(), true);
            w.display();
            window.draw(bufferSprite);
            window.display();
            sleep(milliseconds(120));
            r.soundEffects[0]->stop();

            // Check if left or right cursor keys have been pressed or not
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
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



Font initializeFontElapsedTime() {
    Font f;
    if (!f.loadFromFile("Data/Fonts/digital.ttf")) exit(1);
    return f;
}

Font initializeFontTimeToPlay() {
    Font f;
    if (!f.loadFromFile("Data/Fonts/zorque.ttf")) exit(1);
    return f;
}


Font initializeFontMenus() {
    Font f;
    if (!f.loadFromFile("Data/Fonts/Hetikademo.otf")) exit(1);
    return f;
}

Font initializeFontOptions() {
    Font f;
    if (!f.loadFromFile("Data/Fonts/needForSpeed.ttf")) exit(1);
    return f;
}


Font initializeFontScore(){
    Font f;
    if (!f.loadFromFile("Data/Fonts/DisposableDroid.ttf")) exit(1);
    return f;
}
