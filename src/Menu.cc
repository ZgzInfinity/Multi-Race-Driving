#include "../include/Menu.h"


/**
 * Constructor of the data type Animation
 * @param pathMenuFile is the path where are indicated the textures used to the menus
 */
Menu::Menu(){}



/**
 * Load the main game menu from its xml configuration file
 * @param imagePath is the path of the background's image of the menu
 * @param fontPath is the text font of the main text of the menu
 * @param textContent is the text that appears in the main menu
 * @param positionXCover is the coordinate in the axis X of the main cover image
 * @param positionYCover is the coordinate in the axis Y of the main cover image
 * @param sizeText is the size of the font
 * @param channelR is the value of the red channel color of the text
 * @param channelG is the value of the green channel color of the text
 * @param channelB is the value of the blue channel color of the text
 */
inline void Menu::loadMainMenu(string& imagePath, string& fontPath, string& textContent,
                               int& positionXCover, int& positionYCover, int& positionXText,
                               int& positionYText, int& sizeText, int&channelR, int&channelG, int& channelB)
{
    // Document xml where the document is going to be parsed
    string menusFile = "Configuration/Menus/MainMenu.xml";
    char* menuF = const_cast<char*>(menusFile.c_str());
    xml_document<> doc;

    file<> file(menuF);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *nodeMenu = doc.first_node()->first_node();

    // Loop in order to iterate all the children of the principal node
    for (xml_node<> *mainMenu = nodeMenu->first_node(); mainMenu; mainMenu = mainMenu->next_sibling()){
        // Check if it's the node that controls the main menu of the game
        if ((string)mainMenu->name() == "Background"){
            // Loop in order to iterate all the children nodes of the background
            for (xml_node<> *node = mainMenu->first_node(); node; node = node->next_sibling()){
                // Check if it's the node that controls the main menu of the game
                if ((string)node->name() == "Path"){
                    // Path of the image background
                    imagePath = node->value();
                    continue;
                }
                // Check the x coordinate of the main cover
                else if ((string)node->name() == "PositionX"){
                    // Get x coordinate of the cover
                    positionXCover = stoi(node->value());
                    continue;
                }
                // Check the y coordinate of the main cover
                else if ((string)node->name() == "PositionY"){
                    // Get y coordinate of the cover
                    positionYCover = stoi(node->value());
                }
            }
        }
        // Check if it's the node of the text information
        else if ((string)mainMenu->name() == "Text"){
            // Loop in order to iterate all the children nodes of the text
            for (xml_node<> *node = mainMenu->first_node(); node; node = node->next_sibling()){
                // Check if it's the node that controls the main menu of the game
                if ((string)node->name() == "Content"){
                    // Content of the main text
                    textContent = node->value();
                    continue;
                }
                // Check the font of the main text
                else if ((string)node->name() == "Font"){
                    // Path of the main text font
                    fontPath = node->value();
                    continue;
                }
                // Check the size of the main text
                else if ((string)node->name() == "Size"){
                    // Size of the main text
                    sizeText = stoi(node->value());
                    continue;
                }
                // Check the x coordinate of the main text
                else if ((string)node->name() == "PositionX"){
                    // Get x coordinate of the cover
                    positionXText = stoi(node->value());
                    continue;
                }
                // Check the y coordinate of the main text
                else if ((string)node->name() == "PositionY"){
                    // Get y coordinate of the cover
                    positionYText = stoi(node->value());
                }
                // Check the color of the main text
                else if ((string)node->name() == "Color"){
                    // Loop in order to iterate all the children nodes of the text's color
                    for (xml_node<> *colorNode = node->first_node(); colorNode; colorNode = colorNode->next_sibling()){
                        // Check the value of the red channel
                        if ((string)colorNode->name() == "R"){
                            // Get y coordinate of the cover
                            channelR = stoi(colorNode->value());
                        }
                        // Check the value of the green channel
                        if ((string)colorNode->name() == "G"){
                            // Get y coordinate of the cover
                            channelG = stoi(colorNode->value());
                        }
                        // Check the value of the blue channel
                        if ((string)colorNode->name() == "B"){
                            // Get y coordinate of the cover
                            channelB = stoi(colorNode->value());
                        }
                    }
                }
            }
        }
    }
}



/**
 * Load the configuration of the player and game menus
 * @param pathFile is the xml file configuration of the menu to load
 */
inline void Menu::loadPlayerAndGameMenus(string pathFile, string& imagePath, string& textContent, string& fontPath,
                                         Font& f, int& positionXPanel, int& positionYPanel, int& width, int& height,
                                         int& border,int& positionXText, int& positionYText, int& sizeText, Color& colorText,
                                         Color& colorBorderPanel, int& posXDescription, int& posYDescription,
                                         int& widthDescription, int& heightDescription, int& borderDescription,
                                         Color& colorInsideDescription, Color& colorBorderDescription)
{
    // Path of the xml configuration file
    char* menuF = const_cast<char*>(pathFile.c_str());
    xml_document<> doc;
    file<> file(menuF);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *nodePanel = doc.first_node()->first_node()->first_node();

    // Loop for iterate throughout the node of the file
    for (xml_node<> *node = nodePanel->first_node(); node; node = node->next_sibling()){
        // Check if it's the node that controls the main menu of the game
        if ((string)node->name() == "Background"){
            // Path of the image background
            imagePath = node->value();
            continue;
        }
        // Check the x coordinate of the main cover
        else if ((string)node->name() == "PositionX"){
            // Get x coordinate of the cover
            positionXPanel = stoi(node->value());
            continue;
        }
        // Check the y coordinate of the main cover
        else if ((string)node->name() == "PositionY"){
            // Get y coordinate of the cover
            positionYPanel = stoi(node->value());
        }
        // Check the x coordinate of the main cover
        else if ((string)node->name() == "Width"){
            // Get x coordinate of the cover
            width = stoi(node->value());
            continue;
        }
        // Check the y coordinate of the main cover
        else if ((string)node->name() == "Height"){
            // Get y coordinate of the cover
            height = stoi(node->value());
            continue;
        }
        // Check the y coordinate of the main cover
        else if ((string)node->name() == "Border"){
            // Get y coordinate of the cover
            border = stoi(node->value());
            continue;
        }
        // Get y coordinate of the cover
        else if ((string)node->name() == "Color"){
            // Variables to define the color of the text
            int channelR, channelG, channelB;
            // Loop in order to iterate all the children nodes of the text's color
            for (xml_node<> *colorNode = node->first_node(); colorNode; colorNode = colorNode->next_sibling()){
                // Check the value of the red channel
                if ((string)colorNode->name() == "R"){
                    // Get y coordinate of the cover
                    channelR = stoi(colorNode->value());
                    continue;
                }
                // Check the value of the green channel
                if ((string)colorNode->name() == "G"){
                    // Get y coordinate of the cover
                    channelG = stoi(colorNode->value());
                    continue;
                }
                // Check the value of the blue channel
                if ((string)colorNode->name() == "B"){
                    // Get y coordinate of the cover
                    channelB = stoi(colorNode->value());
                    colorBorderPanel = Color(channelR, channelG, channelB);
                }
            }
        }
        // Check if it's the node of the text information
        else if ((string)node->name() == "Text"){
            // Loop in order to iterate all the children nodes of the text
            for (xml_node<> *nodeText = node->first_node(); nodeText; nodeText = nodeText->next_sibling()){
                // Check if it's the node that controls the main menu of the game
                if ((string)nodeText->name() == "Content"){
                    // Content of the main text
                    textContent = nodeText->value();
                    continue;
                }
                // Check the font of the main text
                else if ((string)nodeText->name() == "Font"){
                    // Path of the main text font
                    fontPath = nodeText->value();
                    f.loadFromFile(fontPath);
                    continue;
                }
                // Check the size of the main text
                else if ((string)nodeText->name() == "Size"){
                    // Size of the main text
                    sizeText = stoi(nodeText->value());
                    continue;
                }
                // Check the x coordinate of the main text
                else if ((string)nodeText->name() == "PositionX"){
                    // Get x coordinate of the cover
                    positionXText = stoi(nodeText->value());
                    continue;
                }
                // Check the y coordinate of the main text
                else if ((string)nodeText->name() == "PositionY"){
                    // Get y coordinate of the cover
                    positionYText = stoi(nodeText->value());
                }
                // Check the color of the main text
                else if ((string)nodeText->name() == "Color"){
                    // Variables to define the color of the text
                    int channelR, channelG, channelB;
                    // Loop in order to iterate all the children nodes of the text's color
                    for (xml_node<> *colorNode = nodeText->first_node(); colorNode; colorNode = colorNode->next_sibling()){
                        // Check the value of the red channel
                        if ((string)colorNode->name() == "R"){
                            // Get y coordinate of the cover
                            channelR = stoi(colorNode->value());
                            continue;
                        }
                        // Check the value of the green channel
                        if ((string)colorNode->name() == "G"){
                            // Get y coordinate of the cover
                            channelG = stoi(colorNode->value());
                            continue;
                        }
                        // Check the value of the blue channel
                        if ((string)colorNode->name() == "B"){
                            // Get y coordinate of the cover
                            channelB = stoi(colorNode->value());
                            colorText = Color(channelR, channelG, channelB);
                        }
                    }
                }
            }
        }
        // Check if it's the node of the text information
        else if ((string)node->name() == "DescriptionPanel"){
            // Loop in order to iterate all the children nodes of the text's color
            for (xml_node<> *nodeDescription = node->first_node(); nodeDescription; nodeDescription = nodeDescription->next_sibling()){
                // Check the x coordinate of the main cover
                if ((string)nodeDescription->name() == "PositionX"){
                    // Get x coordinate of the cover
                    posXDescription = stoi(nodeDescription->value());
                    continue;
                }
                // Check the y coordinate of the main cover
                else if ((string)nodeDescription->name() == "PositionY"){
                    // Get y coordinate of the cover
                    posYDescription = stoi(nodeDescription->value());
                    continue;
                }
                // Check the x coordinate of the main cover
                else if ((string)nodeDescription->name() == "Width"){
                    // Get x coordinate of the cover
                    widthDescription = stoi(nodeDescription->value());
                    continue;
                }
                // Check the y coordinate of the main cover
                else if ((string)nodeDescription->name() == "Height"){
                    // Get y coordinate of the cover
                    heightDescription = stoi(nodeDescription->value());
                    continue;
                }
                // Check the y coordinate of the main cover
                else if ((string)nodeDescription->name() == "Border"){
                    // Get y coordinate of the cover
                    borderDescription = stoi(nodeDescription->value());
                    continue;
                }
                // Check the y coordinate of the main cover
                else if ((string)nodeDescription->name() == "ColorInside" || (string)nodeDescription->name() == "ColorBorder"){
                    // Variables to define the color of the text
                    int channelR, channelG, channelB;
                    // Loop in order to iterate all the children nodes of the text's color
                    for (xml_node<> *colorNode = nodeDescription->first_node(); colorNode; colorNode = colorNode->next_sibling()){
                        // Check the value of the red channel
                        if ((string)colorNode->name() == "R"){
                            // Get y coordinate of the cover
                            channelR = stoi(colorNode->value());
                            continue;
                        }
                        // Check the value of the green channel
                        else if ((string)colorNode->name() == "G"){
                            // Get y coordinate of the cover
                            channelG = stoi(colorNode->value());
                            continue;
                        }
                        // Check the value of the blue channel
                        else if ((string)colorNode->name() == "B"){
                            // Get y coordinate of the cover
                            channelB = stoi(colorNode->value());
                            // Store the color in the correct color field
                            if ((string)nodeDescription->name() == "ColorInside"){
                                // Store the color of the text when the slot is selected
                                colorInsideDescription = Color(channelR, channelG, channelB);
                            }
                            else if ((string)nodeDescription->name() == "ColorBorder"){
                                // Store the color of the border when the slot is selected
                                colorBorderDescription = Color(channelR, channelG, channelB);
                            }
                        }
                    }
                }
            }
        }
        // Check if it's the node of the text information
        else if ((string)node->name() == "Buttons"){
            // Variables to store the information of the buttons
            int positionXTextButton, positionYTextButton, widthButton, heightButton, initialStateButton;
            string textContentButton;
            Texture icon;
            Sprite s;

            // Iterate throughout the different buttons of the menu
            for (xml_node<> *button = node->first_node(); button; button = button->next_sibling()){
                // Iterate the fields of the buttons
                for (xml_node<> *buttonNode = button->first_node(); buttonNode; buttonNode = buttonNode->next_sibling()){
                    // Check the x coordinate of the main text
                    if ((string)buttonNode->name() == "PositionX"){
                        // Get x coordinate of the cover
                        positionXTextButton = stoi(buttonNode->value());
                        continue;
                    }
                    // Check the y coordinate of the main text
                    else if ((string)buttonNode->name() == "PositionY"){
                        // Get y coordinate of the cover
                        positionYTextButton = stoi(buttonNode->value());
                        continue;
                    }
                    // Check the x coordinate of the main cover
                    else if ((string)buttonNode->name() == "Width"){
                        // Get x coordinate of the cover
                        widthButton = stoi(buttonNode->value());
                        continue;
                    }
                    // Check the y coordinate of the main cover
                    else if ((string)buttonNode->name() == "Height"){
                        // Get y coordinate of the cover
                        heightButton = stoi(buttonNode->value());
                        continue;
                    }
                    // Check the y coordinate of the main cover
                    else if ((string)buttonNode->name() == "Font"){
                        // Get y coordinate of the cover
                        fontPath = buttonNode->value();
                        f.loadFromFile(fontPath);
                        continue;
                    }
                    // Check if it's the node that controls the main menu of the game
                    else if ((string)buttonNode->name() == "Content"){
                        // Content of the main text
                        textContentButton = buttonNode->value();
                        continue;
                    }
                    // Check if it's the node that controls the main menu of the game
                    else if ((string)buttonNode->name() == "InitialState"){
                        // Content of the main text
                        initialStateButton = stoi(buttonNode->value());
                        continue;
                    }
                    // Check the color of the main text
                    else if ((string)buttonNode->name() == "Colors"){
                        // Clear the color of the last buttons
                        color_buttons.clear();
                        // Variables to store the color of the buttons
                        int channelR, channelG, channelB;
                        // Loop in order to iterate all the children nodes of the text's color
                        for (xml_node<> *colorNode = buttonNode->first_node(); colorNode; colorNode = colorNode->next_sibling()){
                            // Get the channel of this color
                            for (xml_node<> *colorChannel = colorNode->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                                // Check the value of the red channel
                                if ((string)colorChannel->name() == "R"){
                                    // Get y coordinate of the cover
                                    channelR = stoi(colorChannel->value());
                                    continue;
                                }
                                // Check the value of the green channel
                                else if ((string)colorChannel->name() == "G"){
                                    // Get y coordinate of the cover
                                    channelG = stoi(colorChannel->value());
                                    continue;
                                }
                                // Check the value of the blue channel
                                else if ((string)colorChannel->name() == "B"){
                                    // Get y coordinate of the cover
                                    channelB = stoi(colorChannel->value());
                                    color_buttons.push_back(Color(channelR, channelG, channelB));
                                }
                            }
                        }
                    }
                    else if ((string)buttonNode->name() == "Image"){
                        icon.loadFromFile((string)buttonNode->value());
                        texturesIcon.push_back(icon);
                        Sprite s;
                        iconButtons.push_back(s);
                    }
                    else if ((string)buttonNode->name() == "Description"){
                        // Creation of the button and addition to the vector
                        Button b = Button(positionXTextButton, positionYTextButton, widthButton, heightButton, f,
                                                     textContentButton, color_buttons[0], color_buttons[1], initialStateButton);

                        // Process the description text of the button
                        b.proccessDescription(buttonNode);
                        menuButtons.push_back(b);
                    }
                }
            }
        }
    }
}



/**
 * Shows the main cover of the game until the player presses start
 * @param app is the console where the game is displayed to the players
 */
void Menu::showMainMenu(RenderWindow* app, EffectReproductor* eR){

    // Variables to store the information read from the file of the menu
    string imagePath, fontPath, textContent;

    // Variables to control the main text of the cover
    int positionXText, positionYText, sizeText;

    // Color channels
    int channelR, channelG, channelB;

    // Control possible events
    Event ev;

    // Load the main menu from the file
    loadMainMenu(imagePath, fontPath, textContent, positionXCover, positionYCover,
                 positionXText, positionYText, sizeText, channelR, channelG, channelB);

    // Load the texture of the cover
    cover.loadFromFile(imagePath);

    // Initial text shown in the main cover of the game
    Text coverText;

    // Assignment of the text content
    coverText.setString(textContent);

    // Set position to the cover sprite
    menuSprite.setPosition(positionXCover, positionYCover);

    // Load the texture to show it
    menuSprite.setTexture(cover, true);

    // Font of the text
    Font f;
    f.loadFromFile(fontPath);

    // Create the color of the main text
    Color colorMainText = Color(channelR, channelG, channelB);

    // Establish the format of the cover text
    coverText.setFillColor(colorMainText);
    coverText.setCharacterSize(sizeText);
    coverText.setStyle(Text::Bold);
    coverText.setPosition(positionXText, positionYText);
    coverText.setFont(f);

    // Control the start key is pressed
    bool startPressed = false;

    // Loop until start is pressed by the user
    while (!startPressed){

        // Detect possible actions of the user on the console game
        if (app->pollEvent(ev) && ev.type == Event::Closed){
                app->close();
        }

        // Time to change the color of the font
        if (coverText.getFillColor() == colorMainText){
            // Change color to transparent
            coverText.setFillColor(Color::Transparent);
        }
        else {
            // Change color to transparent
            coverText.setFillColor(colorMainText);
        }
        // Clean the console of the game
        app->draw(menuSprite);
        app->draw(coverText);
        app->display();
        sleep(milliseconds(400));

        // Check if the start key has been pressed or not
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            startPressed = true;
            eR->stopEffect(1);
            eR->reproduceEffect(1);
            sleep(milliseconds(100));
        }
    }
}



/**
 * Shows the menu of selecting the number of players
 * @param app is the console where the game is displayed to the players
 * @param optionParameter is the flag where is stored the option selected by the
 * the player in the menu
*/
void Menu::showStandardMenu(RenderWindow* app, string pathFile, int& optionParameter, Game_status& status, EffectReproductor* eR){
    // Clean the console window
    app->clear(Color(0, 0 ,0));

    // Control possible events
    Event ev;

    sleep(milliseconds(100));

    // Clear the list of buttons of the last possible menus
    menuButtons.clear();
    iconButtons.clear();
    texturesIcon.clear();

    // Variables to store all the information of the menu panel
    string imagePath, textContent, fontPath, textContentButton;
    int positionXPanel, positionYPanel, width, height, border, borderDescription,
        positionXText, positionYText, sizeText;
    int posXDescription, posYDescription, widthDescription, heightDescription;
    Color colorText, colorBorderPanel, colorInsideDescription, colorBorderDescription;
    Font fontPanel, fontButton;

    // Load from file the player menu
    loadPlayerAndGameMenus(pathFile, imagePath, textContent, fontPath, fontButton,
                           positionXPanel, positionYPanel, width, height, border, positionXText,
                           positionYText, sizeText, colorText, colorBorderPanel, posXDescription,
                           posYDescription, widthDescription, heightDescription, borderDescription,
                           colorInsideDescription, colorBorderDescription);

    // Set position to the cover sprite
    menuSprite.setPosition(positionXCover, positionYCover);
    // Load the texture to show it
    menuSprite.setTexture(cover, true);
    app->draw(menuSprite);

    // Draw the rectangle of the player menu
    rectangle.setPosition(positionXPanel, positionYPanel);
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setOutlineColor(colorBorderPanel);
    rectangle.setOutlineThickness(border);
    Texture background;
    background.loadFromFile(imagePath);
    rectangle.setTexture(&background, true);
    app->draw(rectangle);

    // Draw the rectangle of the player menu
    description.setPosition(posXDescription, posYDescription);
    description.setSize(sf::Vector2f(widthDescription, heightDescription));
    description.setFillColor(colorInsideDescription);
    description.setOutlineColor(colorBorderPanel);
    description.setOutlineThickness(borderDescription);

    // Draw the text introduction of the menu
    Text playerText;
    playerText.setString(textContent);
    playerText.setFillColor(colorText);
    playerText.setCharacterSize(sizeText);
    playerText.setStyle(Text::Bold | Text::Underlined);
    playerText.setPosition(positionXText, positionYText);
    fontPanel.loadFromFile(fontPath);
    playerText.setFont(fontPanel);
    app->draw(playerText);

    // Draw the text description of the menu
    Text descriptionText;
    descriptionText.setStyle(Text::Bold);
    descriptionText.setFillColor(Color::Blue);
    descriptionText.setCharacterSize(12);
    descriptionText.setFont(fontButton);

    // Identifier of the actual button selected
    optionParameter = 0;

    app->draw(description);

    int posXDescriptionInit = posXDescription + 10;
    int posYDescriptionInit = posYDescription + 10;

    // Show the buttons of the menu
    for (int i = 0; i < (int)menuButtons.size(); i++){
        menuButtons.at(i).render(app);

        if (i == optionParameter){

            int posXDescriptionOffset = posXDescription + 10;
            int posYDescriptionOffset = posYDescription + 10;

            // Draw the button description
            // Display the description of the button
            vector<string> wordsButton =  menuButtons.at(i).getDescriptionButton();

            for (string s : wordsButton){
                descriptionText.setString(s);
                if (posXDescriptionOffset + descriptionText.getLocalBounds().width <= 720){
                    descriptionText.setPosition(posXDescriptionOffset, posYDescriptionOffset);
                    app->draw(descriptionText);
                    posXDescriptionOffset += descriptionText.getLocalBounds().width + 10;
                }
                else {
                    posXDescriptionOffset = posXDescriptionInit;
                    posYDescriptionOffset += 20;
                    descriptionText.setPosition(posXDescriptionOffset, posYDescriptionOffset);
                    app->draw(descriptionText);
                    posXDescriptionOffset += descriptionText.getLocalBounds().width + 10;
                }
            }
            // Display the icon of the button
            iconButtons[i].setTexture(texturesIcon[i], true);
            posXDescriptionOffset = (app->getSize().x / 2.f) + (iconButtons[i].getLocalBounds().width / 1.3f);
            posYDescriptionOffset += 30;
            iconButtons[i].setPosition(posXDescriptionOffset, posYDescriptionOffset);

            app->draw(iconButtons[i]);
        }
    }

    // Display the changes of the buttons' appearance
    app->display();

    // Control the start key is pressed
    bool startPressed = false;

    // Control if backspace key is pressed
    bool backspacePressed = false;

    // Loop until the player selects a mode pressing enter
    while (!startPressed && !backspacePressed){

        // Detect possible actions of the user on the console game
        if (app->pollEvent(ev) && ev.type == Event::Closed){
                app->close();
        }

        // Check if the up cursor keyword has been pressed
        if (Keyboard::isKeyPressed(Keyboard::Up)){
            // Check if the first button is hovered or not
            if (optionParameter != 0){
                // Move the button hovered
                optionParameter--;
                // Change the color appearance of both buttons
                menuButtons[optionParameter].setButtonState(BUTTON_HOVER);
                menuButtons[optionParameter + 1].setButtonState(BUTTON_IDLE);

                // Reproduce the sound
                eR->stopEffect(2);
                eR->reproduceEffect(2);

                // Render the buttons with the changes
                app->draw(rectangle);
                app->draw(playerText);
                app->draw(description);

                // Show the buttons of the menu
                for (int i = 0; i < (int)menuButtons.size(); i++){
                    // Draw the button figure
                    menuButtons.at(i).render(app);
                    if (i == optionParameter){

                        int posXDescriptionOffset = posXDescription + 10;
                        int posYDescriptionOffset = posYDescription + 10;

                        // Draw the button description
                        // Display the description of the button
                        vector<string> wordsButton =  menuButtons.at(i).getDescriptionButton();

                        for (string s : wordsButton){
                            descriptionText.setString(s);
                            if (posXDescriptionOffset + descriptionText.getLocalBounds().width <= 720){
                                descriptionText.setPosition(posXDescriptionOffset, posYDescriptionOffset);
                                app->draw(descriptionText);
                                posXDescriptionOffset += descriptionText.getLocalBounds().width + 10;
                            }
                            else {
                                posXDescriptionOffset = posXDescriptionInit;
                                posYDescriptionOffset += 20;
                                descriptionText.setPosition(posXDescriptionOffset, posYDescriptionOffset);
                                app->draw(descriptionText);
                                posXDescriptionOffset += descriptionText.getLocalBounds().width + 10;
                            }
                        }

                        // Display the icon of the button
                        iconButtons[i].setTexture(texturesIcon[i], true);
                        posXDescriptionOffset = (app->getSize().x / 2.f) + (iconButtons[i].getLocalBounds().width / 1.3f);
                        posYDescriptionOffset += 30;
                        iconButtons[i].setPosition(posXDescriptionOffset, posYDescriptionOffset);

                        app->draw(iconButtons[i]);
                    }
                }
                app->display();
                sleep(milliseconds(180));
            }
        }
        // Check if the down cursor keyword has been pressed
        else if (Keyboard::isKeyPressed(Keyboard::Down)){
            // Check if the first button is hovered or not
            if (optionParameter != (int)menuButtons.size() - 1){
                // Move the button hovered
                optionParameter++;
                // Change the color appearance of both buttons
                menuButtons[optionParameter].setButtonState(BUTTON_HOVER);
                menuButtons[optionParameter - 1].setButtonState(BUTTON_IDLE);

                // Reproduce the sound
                eR->stopEffect(2);
                eR->reproduceEffect(2);

                // Render the buttons with the changes
                app->draw(menuSprite);
                app->draw(rectangle);
                app->draw(playerText);
                app->draw(description);

                // Show the buttons of the menu
                for (int i = 0; i < (int)menuButtons.size(); i++){
                    menuButtons.at(i).render(app);

                    if (i == optionParameter){

                        int posXDescriptionOffset = posXDescription + 10;
                        int posYDescriptionOffset = posYDescription + 10;

                        // Draw the button description
                        // Display the description of the button
                        vector<string> wordsButton =  menuButtons.at(i).getDescriptionButton();

                        for (string s : wordsButton){
                            descriptionText.setString(s);
                            if (posXDescriptionOffset + descriptionText.getLocalBounds().width <= 720){
                                descriptionText.setPosition(posXDescriptionOffset, posYDescriptionOffset);
                                app->draw(descriptionText);
                                posXDescriptionOffset += descriptionText.getLocalBounds().width + 10;
                            }
                            else {
                                posXDescriptionOffset = posXDescriptionInit;
                                posYDescriptionOffset += 20;
                                descriptionText.setPosition(posXDescriptionOffset, posYDescriptionOffset);
                                app->draw(descriptionText);
                                posXDescriptionOffset += descriptionText.getLocalBounds().width + 10;
                            }
                        }

                        // Display the icon of the button
                        iconButtons[i].setTexture(texturesIcon[i], true);
                        posXDescriptionOffset = (app->getSize().x / 2.f) + (iconButtons[i].getLocalBounds().width / 1.3f);
                        posYDescriptionOffset += 30;
                        iconButtons[i].setPosition(posXDescriptionOffset, posYDescriptionOffset);
                        app->draw(iconButtons[i]);
                    }
                }
                app->display();
                sleep(milliseconds(180));
            }
        }
        // Check if the start key has been pressed or not
        else if (Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            startPressed = true;
            if (status == PLAYER_MENU){
                switch(optionParameter){
                    case 0:
                        status = SINGLE_GAME_MODE;
                        break;
                    case 1:
                        status = MULTI_GAME_MODE;
                        break;
                    case 2:
                        status = OPTIONS;
                }
            }
            else if (status == SINGLE_GAME_MODE || status == MULTI_GAME_MODE){
                status = LEVEL_MENU;
            }
            else if (status == LEVEL_MENU){
                status = PREPARING_GAME_MODE;
            }
            // Reproduce the sound
            eR->stopEffect(3);
            eR->reproduceEffect(3);
        }
        // Check if the start key has been pressed or not
        else if (Keyboard::isKeyPressed(sf::Keyboard::Backspace)){
            backspacePressed = true;
            if (status == PLAYER_MENU){
                status = MAIN_MENU;
            }
            else if (status == SINGLE_GAME_MODE || MULTI_GAME_MODE){
                status = PLAYER_MENU;
            }
            else if (status == LEVEL_MENU){
                status == SINGLE_GAME_MODE;
            }

            // Reproduce the sound
            eR->stopEffect(5);
            eR->reproduceEffect(5);
        }
    }
}




/**
 * Shows the menu of selecting the number of players
 * @param app is the console where the game is displayed to the players
 * @param c stores the current configuration of the game
 */
void Menu::showMenuOptions(RenderWindow* app, string pathFile, Type_control& control, Configuration* c,
                           KeywordMapper* kM, EffectReproductor* eR){
    // Clean the console window
    app->clear(Color(0, 0 ,0));

    // Control possible events
    Event ev;

    sleep(milliseconds(100));

    // Clear the list of buttons of the last possible menus
    menuButtons.clear();

    // Variables to store all the information of the menu panel
    string imagePath, textContent, fontPath, textContentButton;
    int positionXPanel, positionYPanel, width, height, border, borderDescription,
        positionXText, positionYText, sizeText;
    int posXDescription, posYDescription, widthDescription, heightDescription;
    Color colorText, colorBorderPanel, colorInsideDescription, colorBorderDescription;
    Font fontPanel, fontButton;

    // Load from file the player menu
    loadPlayerAndGameMenus(pathFile, imagePath, textContent, fontPath, fontButton,
                           positionXPanel, positionYPanel, width, height, border, positionXText,
                           positionYText, sizeText, colorText, colorBorderPanel, posXDescription,
                           posYDescription, widthDescription, heightDescription, borderDescription,
                           colorInsideDescription, colorBorderDescription);

    // Set position to the cover sprite
    menuSprite.setPosition(positionXCover, positionYCover);
    // Load the texture to show it
    menuSprite.setTexture(cover, true);
    app->draw(menuSprite);

    // Draw the rectangle of the player menu
    rectangle.setPosition(positionXPanel, positionYPanel);
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setOutlineColor(colorBorderPanel);
    rectangle.setOutlineThickness(border);
    Texture background;
    background.loadFromFile(imagePath);
    rectangle.setTexture(&background, true);
    app->draw(rectangle);

    // Draw the text introduction of the menu
    Text playerText;
    playerText.setString(textContent);
    playerText.setFillColor(colorText);
    playerText.setCharacterSize(sizeText);
    playerText.setStyle(Text::Bold | Text::Underlined);
    playerText.setPosition(positionXText, positionYText);
    fontPanel.loadFromFile(fontPath);
    playerText.setFont(fontPanel);
    app->draw(playerText);

    Text info1;
    info1.setString("Press Space to select a controller");
    info1.setFillColor(Color(10, 201, 235));
    info1.setOutlineColor(Color(3, 39, 8));
    info1.setOutlineThickness(3);
    info1.setCharacterSize(sizeText - 10);
    info1.setStyle(Text::Bold);
    info1.setPosition(positionXText - 130, positionYText + 50);
    info1.setFont(fontPanel);
    app->draw(info1);

    Text info2;
    info2.setString("Then the key to change its configuration");
    info2.setFillColor(Color(10, 201, 235));
    info2.setOutlineColor(Color(3, 39, 8));
    info2.setCharacterSize(sizeText - 10);
    info2.setOutlineThickness(3);
    info2.setCharacterSize(sizeText - 10);
    info2.setStyle(Text::Bold);
    info2.setPosition(positionXText - 160, positionYText + 70);
    info2.setFont(fontPanel);
    app->draw(info2);


    // Identifier of the actual button selected
    int optionParameter = 0;

    // Show the buttons of the menu
    for (int i = 0; i < (int)menuButtons.size(); i++){
        // Get the configuration of the controller
        int code;
        switch(i){
            case 13:
                code = kM->lookForIdKeyWord(c->getChangeSoundtrack());
                menuButtons[i].setTextButton(kM->mapperIdKeyWord[code]);
                break;
            case 14:
                code = kM->lookForIdKeyWord(c->getAccelerateKey());
                menuButtons[i].setTextButton(kM->mapperIdKeyWord[code]);
                break;
            case 15:
                code = kM->lookForIdKeyWord(c->getBrakeKey());
                menuButtons[i].setTextButton(kM->mapperIdKeyWord[code]);
                break;
            case 16:
                code = kM->lookForIdKeyWord(c->getLeftKey());
                menuButtons[i].setTextButton(kM->mapperIdKeyWord[code]);
                break;
            case 17:
                code = kM->lookForIdKeyWord(c->getRightKey());
                menuButtons[i].setTextButton(kM->mapperIdKeyWord[code]);
        }
    }

    // Show the buttons of the menu
    for (int i = 0; i < (int)menuButtons.size(); i++){
        menuButtons.at(i).render(app);
    }

    // Display the changes of the buttons' appearance
    app->display();

    // Control the start key is pressed
    bool startPressed = false;

    // Loop until the player selects a mode pressing enter
    while (!startPressed){

        // Detect possible actions of the user on the console game
        if (app->pollEvent(ev) && ev.type == Event::Closed){
                app->close();
        }

        // Check if the up cursor keyword has been pressed
        if (Keyboard::isKeyPressed(Keyboard::Up)){
            // Check if the first button is hovered or not
            if (optionParameter != 0){
                // Move the button hovered
                optionParameter--;
                // Change the color appearance of both buttons
                menuButtons[optionParameter].setButtonState(BUTTON_HOVER);
                menuButtons[optionParameter + 9].setButtonState(BUTTON_HOVER);
                menuButtons[optionParameter + 1].setButtonState(BUTTON_IDLE);
                menuButtons[optionParameter + 10].setButtonState(BUTTON_IDLE);

                // Reproduce the sound
                eR->stopEffect(2);
                eR->reproduceEffect(2);
            }
        }
        // Check if the down cursor keyword has been pressed
        else if (Keyboard::isKeyPressed(Keyboard::Down)){
            // Check if the first button is hovered or not
            if (optionParameter != ((int)menuButtons.size() / 2) - 1){
                // Move the button hovered
                optionParameter++;
                // Change the color appearance of both buttons
                menuButtons[optionParameter].setButtonState(BUTTON_HOVER);
                menuButtons[optionParameter + 9].setButtonState(BUTTON_HOVER);
                menuButtons[optionParameter - 1].setButtonState(BUTTON_IDLE);
                menuButtons[optionParameter + 8].setButtonState(BUTTON_IDLE);

                // Reproduce the sound
                eR->stopEffect(2);
                eR->reproduceEffect(2);
            }
        }
        // Check if the start key has been pressed or not
        else if (Keyboard::isKeyPressed(Keyboard::Enter)){
            startPressed = true;
            // Reproduce the sound
            eR->stopEffect(4);
            eR->reproduceEffect(4);
        }

        // Press keyword space in order to change the control
        if (Keyboard::isKeyPressed(Keyboard::Space)){
            // Check where is the button selected
            switch(optionParameter){
                case 0:
                case 1:
                case 2:
                case 3:
                    // Change one of the three first configuration parameters
                    modifyOptionConfiguration(optionParameter, control, c, kM, eR);
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                    modifyOptionConfigurationPlayer(app, optionParameter, c, kM, eR);
                    break;
            }
        }

        // Render the buttons with the changes
        app->draw(menuSprite);
        app->draw(rectangle);
        app->draw(playerText);
        app->draw(info1);
        app->draw(info2);

        // Show the buttons of the menu
        for (int i = 0; i < (int)menuButtons.size(); i++){
            menuButtons.at(i).render(app);
        }
        app->display();
        sleep(milliseconds(90));
    }
}



void Menu::loadVehiclesMenu(Sprite& menuVehicle, Font& fontMainText, Font& fontVehicleName, Font& fontVehicleIndicator, Font& fontTitle,
                            Text& mainText, Text& propertyText,vector<Slot>& slotsMenu, vector<Text>& vehicleIndicators,
                            RectangleShape& panelIndicator){
    // Control the attributes of the background configuration
    string imagePath;
    int positionXBackground, positionYBackground;

    // Control the attributes of the main text of the menu
    string textContent, fontPath;
    int sizeText, posXText, posYText;
    Color colorText;

    // Path of the xml configuration file
    char* menuF = const_cast<char*>("Configuration/Menus/VehicleMenu.xml");
    xml_document<> doc;
    file<> file(menuF);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *nodePanel = doc.first_node()->first_node();

    // Loop for iterate throughout the different nodes of the file
    for (xml_node<> *node = nodePanel->first_node(); node; node = node->next_sibling()){
        // Check if it's the node that controls the main menu of the game
        if ((string)node->name() == "Background"){
            // Loop for iterate throughout the different nodes of the background
            for (xml_node<> *nodeBackground = node->first_node(); nodeBackground; nodeBackground = nodeBackground->next_sibling()){
                // Process the attributes of the background
                if ((string)nodeBackground->name() == "Path"){
                    imagePath = nodeBackground->value();
                    continue;
                }
                // Check the coordinate of the background in axis X
                else if ((string)nodeBackground->name() == "PositionX"){
                    positionXBackground = stoi(nodeBackground->value());
                    continue;
                }
                // Check the coordinate of the background in the axis Y
                else if ((string)nodeBackground->name() == "PositionY"){
                    positionYBackground = stoi(nodeBackground->value());
                    continue;
                }
                // Check the main text of the vehicle menu
                else if ((string)nodeBackground->name() == "Text"){
                    // Process the time panel or the destiny panel
                    for (xml_node<> *textNode = nodeBackground->first_node(); textNode; textNode = textNode->next_sibling()){
                        // Check if it's the node that controls the speed panel
                        if ((string)textNode->name() == "Content"){
                            textContent = textNode->value();
                            continue;
                        }
                        // Check if it's the node that controls the speed panel
                        else if ((string)textNode->name() == "Font"){
                            fontPath = textNode->value();
                            continue;
                        }
                        // Check if it's the node that controls the coordinate in axis x of the speed panel
                        else if ((string)textNode->name() == "Size"){
                            sizeText = stoi(textNode->value());
                            continue;
                        }
                        // Check if it's the node that controls the coordinate in axis x of the speed panel
                        else if ((string)textNode->name() == "PositionX"){
                            posXText = stoi(textNode->value());
                            continue;
                        }
                        // Check if it's the node that controls the coordinate in axis y of the speed panel
                        else if ((string)textNode->name() == "PositionY"){
                            posYText = stoi(textNode->value());
                            continue;
                        }
                        // Check if it's the node that controls the text of the speed panel
                        else if ((string)textNode->name() == "Color"){
                            // Variables to define the color of the text
                            int channelR, channelG, channelB;
                            // Loop in order to iterate all the children nodes of the text's color
                            for (xml_node<> *colorNode = textNode->first_node(); colorNode; colorNode = colorNode->next_sibling()){
                                // Check the value of the red channel
                                if ((string)colorNode->name() == "R"){
                                    // Get y coordinate of the cover
                                    channelR = stoi(colorNode->value());
                                    continue;
                                }
                                // Check the value of the green channel
                                else if ((string)colorNode->name() == "G"){
                                    // Get y coordinate of the cover
                                    channelG = stoi(colorNode->value());
                                    continue;
                                }
                                // Check the value of the blue channel
                                else if ((string)colorNode->name() == "B"){
                                    // Get y coordinate of the cover
                                    channelB = stoi(colorNode->value());
                                    colorText = Color(channelR, channelG, channelB);
                                }
                            }
                        }
                    }
                }
            }
            // Load all the information read from the background with the main text
            cover.loadFromFile(imagePath);
            menuVehicle.setPosition(positionXBackground, positionYBackground);
            menuVehicle.setTexture(cover, true);

            mainText.setString(textContent);
            mainText.setFillColor(colorText);
            mainText.setCharacterSize(sizeText);
            mainText.setStyle(Text::Bold | Text::Underlined);
            mainText.setPosition(posXText, posYText);
            fontMainText.loadFromFile(fontPath);
            mainText.setFont(fontMainText);
        }
        // Check the main text of the vehicle menu
        else if ((string)node->name() == "VehicleSlots"){
            // Load the configuration of the different slots for the vehicle

            // Attributes for load the different texts of the slots
            int posXSlot, posYSlot, sizeXSlot, sizeYSlot, border, borderText;
            // Colors for the slot
            Color colorSelected, colorUnSelected, colorBorderSelected, colorBorderUnSelected;
            // Colors for the text of the slot
            Color colorTextSelected, colorTextUnSelected, colorTextBorderSelected, colorTextBorderUnSelected;

            // Attributes to store the vehicle to show in the slot
            Texture t;
            int posXVehicle, posYVehicle;
            vector<Texture> vehicleTextures;

            // Process the information of the actual slot
            for (xml_node<> *slotNode = node->first_node(); slotNode; slotNode = slotNode->next_sibling()){
                // Loop for iterate throughout the different attributes of the slot
                for (xml_node<> *attributeSlot = slotNode->first_node(); attributeSlot; attributeSlot = attributeSlot->next_sibling()){
                    // Check if it's the node that stores the position in the axis X
                    if ((string)attributeSlot->name() == "PositionX"){
                        posXSlot = stoi(attributeSlot->value());
                        continue;
                    }
                    // Check if it's the node that stores the position in the axis Y
                    else if ((string)attributeSlot->name() == "PositionY"){
                        posYSlot = stoi(attributeSlot->value());
                        continue;
                    }
                    // Check if it's the node that stores the size in the axis X
                    else if ((string)attributeSlot->name() == "SizeX"){
                        sizeXSlot = stoi(attributeSlot->value());
                        continue;
                    }
                    // Check if it's the node that stores the size in the axis Y
                    else if ((string)attributeSlot->name() == "SizeY"){
                        sizeYSlot = stoi(attributeSlot->value());
                        continue;
                    }
                    // Check if it's the node that controls the coordinate in axis y of the speed panel
                    else if ((string)attributeSlot->name() == "Border"){
                        border = stoi(attributeSlot->value());
                        continue;
                    }
                    // Check if it's the node that controls the text of the slot that indicates the vehicle
                    else if ((string)attributeSlot->name() == "Text"){
                        // Loop for read all the information of the text that indicates the kind of vehicle
                        for (xml_node<> *textNode = attributeSlot->first_node(); textNode; textNode = textNode->next_sibling()){
                            // Check if it's the node that controls the text information
                            if ((string)textNode->name() == "Content"){
                                textContent = textNode->value();
                                continue;
                            }
                            // Check if it's the node that controls the speed panel
                            else if ((string)textNode->name() == "Font"){
                                fontVehicleName.loadFromFile((string)textNode->value());
                                continue;
                            }
                            // Check if it's the node that controls the coordinate in axis x of the speed panel
                            else if ((string)textNode->name() == "Size"){
                                sizeText = stoi(textNode->value());
                                continue;
                            }
                            // Check if it's the node that controls the coordinate in axis x of the speed panel
                            else if ((string)textNode->name() == "PositionX"){
                                posXText = stoi(textNode->value());
                                continue;
                            }
                            // Check if it's the node that controls the coordinate in axis y of the speed panel
                            else if ((string)textNode->name() == "PositionY"){
                                posYText = stoi(textNode->value());
                                continue;
                            }
                            // Check if it's the node that controls the coordinate in axis y of the speed panel
                            else if ((string)textNode->name() == "Border"){
                                borderText = stoi(textNode->value());
                                continue;
                            }
                            // Check if it's the node that controls the text of the speed panel
                            else if ((string)textNode->name() == "ColorInsideSelected" || (string)textNode->name() == "ColorBorderSelected" ||
                                     (string)textNode->name() == "ColorInsideUnSelected" || (string)textNode->name() == "ColorBorderUnSelected")
                            {
                                // Variables to define the color of the text
                                int channelR, channelG, channelB;
                                // Loop in order to iterate all the children nodes of the text's color
                                for (xml_node<> *colorNode = textNode->first_node(); colorNode; colorNode = colorNode->next_sibling()){
                                    // Check the value of the red channel
                                    if ((string)colorNode->name() == "R"){
                                        // Get y coordinate of the cover
                                        channelR = stoi(colorNode->value());
                                        continue;
                                    }
                                    // Check the value of the green channel
                                    else if ((string)colorNode->name() == "G"){
                                        // Get y coordinate of the cover
                                        channelG = stoi(colorNode->value());
                                        continue;
                                    }
                                    // Check the value of the blue channel
                                    else if ((string)colorNode->name() == "B"){
                                        // Get y coordinate of the cover
                                        channelB = stoi(colorNode->value());
                                        // Store the color in the correct color field
                                        if ((string)textNode->name() == "ColorInsideSelected"){
                                            // Store the color of the text when the slot is selected
                                            colorTextSelected = Color(channelR, channelG, channelB);
                                        }
                                        else if ((string)textNode->name() == "ColorBorderSelected"){
                                            // Store the color of the border when the slot is selected
                                            colorTextBorderSelected = Color(channelR, channelG, channelB);
                                        }
                                        else if ((string)textNode->name() == "ColorInsideUnSelected"){
                                            // Store the color of the text when the slot is unselected
                                            colorTextUnSelected = Color(channelR, channelG, channelB);
                                        }
                                        else if ((string)textNode->name() == "ColorBorderUnSelected"){
                                            // Store the color of the border when the slot is unselected
                                            colorTextBorderUnSelected = Color(channelR, channelG, channelB);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // Check if it's the node that controls the text of the speed panel
                    else if ((string)attributeSlot->name() == "ColorSelected" || (string)attributeSlot->name() == "ColorBorderSelected" ||
                             (string)attributeSlot->name() == "ColorUnSelected" || (string)attributeSlot->name() == "ColorBorderUnSelected")
                    {
                        // Variables to define the color of the text
                        int channelR, channelG, channelB;
                        // Loop in order to iterate all the children nodes of the text's color
                        for (xml_node<> *colorNode = attributeSlot->first_node(); colorNode; colorNode = colorNode->next_sibling()){
                            // Check the value of the red channel
                            if ((string)colorNode->name() == "R"){
                                // Get y coordinate of the cover
                                channelR = stoi(colorNode->value());
                                continue;
                            }
                            // Check the value of the green channel
                            else if ((string)colorNode->name() == "G"){
                                // Get y coordinate of the cover
                                channelG = stoi(colorNode->value());
                                continue;
                            }
                            // Check the value of the blue channel
                            else if ((string)colorNode->name() == "B"){
                                // Get y coordinate of the cover
                                channelB = stoi(colorNode->value());

                                // Store the color in the correct color field
                                if ((string)attributeSlot->name() == "ColorSelected"){
                                    // Store the color of the text when the slot is selected
                                    colorSelected = Color(channelR, channelG, channelB);
                                }
                                else if ((string)attributeSlot->name() == "ColorBorderSelected"){
                                    // Store the color of the border when the slot is selected
                                    colorBorderSelected = Color(channelR, channelG, channelB);
                                }
                                else if ((string)attributeSlot->name() == "ColorUnSelected"){
                                    // Store the color of the text when the slot is unselected
                                    colorUnSelected = Color(channelR, channelG, channelB);
                                }
                                else if ((string)attributeSlot->name() == "ColorBorderUnSelected"){
                                    // Store the color of the border when the slot is unselected
                                    colorBorderUnSelected = Color(channelR, channelG, channelB);
                                }
                            }
                        }
                    }
                    // Check it's the node that contains the sprites of the vehicles
                    else if ((string)attributeSlot->name() == "VehicleSprites"){
                        // Clear the possible textures of the last vehicle processed
                        vehicleTextures.clear();
                        // Loop to process all the sprites of the vehicle to show in the slot
                        for (xml_node<> *vehicle = attributeSlot->first_node(); vehicle; vehicle = vehicle->next_sibling()){
                            // Check if it's the attribute that controls the position the axis X
                            if ((string)vehicle->name() == "PositionX"){
                                // Get the coordinate in the axis X
                                posXVehicle = stoi(vehicle->value());
                                continue;
                            }
                            // Check if it's the attribute that controls the position the axis X
                            else if ((string)vehicle->name() == "PositionY"){
                                // Get the coordinate in the axis X
                                posYVehicle = stoi(vehicle->value());
                                continue;
                            }
                            // Check if it's the attribute that controls the paths of the different sprites
                            else if ((string)vehicle->name() == "Paths"){
                                // Loop for iterate the paths of the sprites
                                for (xml_node<> *sprite = vehicle->first_node(); sprite; sprite = sprite->next_sibling()){
                                    // Load the texture from the path read
                                    t.loadFromFile((string)sprite->value());
                                    // Add the texture read to the vector
                                    vehicleTextures.push_back(t);
                                }
                            }
                        }
                    }
                }
                // Creation of the slot with all the information retrieved
                Slot s = Slot(posXSlot, posYSlot, sizeXSlot, sizeYSlot, border, textContent, fontVehicleName, posXText, posYText,
                              borderText, sizeText, colorTextSelected, colorTextBorderSelected, colorTextUnSelected,
                              colorTextBorderUnSelected, colorSelected, colorBorderSelected, colorUnSelected, colorBorderUnSelected,
                              posXVehicle, posYVehicle, vehicleTextures);

                // Added the slot to the vector
                slotsMenu.push_back(s);
            }
        }
        // Check if it's the node that control the panel of the vehicle properties
        else if ((string)node->name() == "VehiclePropertiesPanel"){
            // Loop to process all the indicators of the vehicle
            for (xml_node<> *property = node->first_node(); property; property = property->next_sibling()){
                // Check if it's the title of the panel
                if ((string)property->name() == "Title"){
                    int posX, posY, sizeText;
                    string textContent;
                    // Loop to process all the attributes of the title
                    for (xml_node<> *titleNode = property->first_node(); titleNode; titleNode = titleNode->next_sibling()){
                        // Check if it's the title of the panel
                        if ((string)titleNode->name() == "Font"){
                            fontTitle.loadFromFile((string)titleNode->value());
                            continue;
                        }
                        // Check if it's the title of the panel
                        else if ((string)titleNode->name() == "PositionX"){
                            posX = stoi(titleNode->value());
                            continue;
                        }
                        // Check if it's the title of the panel
                        else if ((string)titleNode->name() == "PositionY"){
                            posY = stoi(titleNode->value());
                            continue;
                        }
                        else if ((string)titleNode->name() == "Content"){
                            textContent = string(titleNode->value());
                            continue;
                        }
                        else if ((string)titleNode->name() == "Size"){
                            sizeText = stoi(titleNode->value());
                            continue;
                        }
                        // Check if it's the node that controls the text of the speed panel
                        else if ((string)titleNode->name() == "Color"){
                            // Variables to define the color of the text
                            int channelR, channelG, channelB;
                            // Loop in order to iterate all the children nodes of the text's color
                            for (xml_node<> *colorNode = titleNode->first_node(); colorNode; colorNode = colorNode->next_sibling()){
                                // Check the value of the red channel
                                if ((string)colorNode->name() == "R"){
                                    // Get y coordinate of the cover
                                    channelR = stoi(colorNode->value());
                                    continue;
                                }
                                // Check the value of the green channel
                                else if ((string)colorNode->name() == "G"){
                                    // Get y coordinate of the cover
                                    channelG = stoi(colorNode->value());
                                    continue;
                                }
                                // Check the value of the blue channel
                                else if ((string)colorNode->name() == "B"){
                                    // Get y coordinate of the cover
                                    channelB = stoi(colorNode->value());
                                    propertyText.setPosition(posX, posY);
                                    propertyText.setString(textContent);
                                    propertyText.setCharacterSize(sizeText);
                                    propertyText.setFillColor(Color(channelR, channelG, channelB));
                                }
                            }
                        }
                    }
                }
                else if ((string)property->name() == "Properties"){
                    // Loop to process all the indicators of the vehicle
                    for (xml_node<> *modeProperty = property->first_node(); modeProperty; modeProperty = modeProperty->next_sibling()){
                        // Check if it's the title of the panel
                        if ((string)modeProperty->name() == "Panel"){
                            int posX, posY, width, height, borderPanel;
                            // Loop to process all the attributes of the panel
                            for (xml_node<> *infoInd = modeProperty->first_node(); infoInd; infoInd = infoInd->next_sibling()){
                                // Check if it's the title of the panel
                                if ((string)infoInd->name() == "PositionX"){
                                    posX = stoi(infoInd->value());
                                    continue;
                                }
                                // Check if it's the title of the panel
                                else if ((string)infoInd->name() == "PositionY"){
                                    posY = stoi(infoInd->value());
                                    continue;
                                }
                                else if ((string)infoInd->name() == "SizeX"){
                                    width = stoi(infoInd->value());
                                    continue;
                                }
                                else if ((string)infoInd->name() == "SizeY"){
                                    height = stoi(infoInd->value());
                                    continue;
                                }
                                else if ((string)infoInd->name() == "Border"){
                                    borderPanel = stoi(infoInd->value());
                                    continue;
                                }
                                else if ((string)infoInd->name() == "ColorPanel" || (string)infoInd->name() == "ColorBorder"){
                                     // Variables to define the color of the text
                                    int channelR, channelG, channelB;
                                    // Loop in order to iterate all the children nodes of the text's color
                                    for (xml_node<> *colorNode = infoInd->first_node(); colorNode; colorNode = colorNode->next_sibling()){
                                        // Check the value of the red channel
                                        if ((string)colorNode->name() == "R"){
                                            // Get y coordinate of the cover
                                            channelR = stoi(colorNode->value());
                                            continue;
                                        }
                                        // Check the value of the green channel
                                        else if ((string)colorNode->name() == "G"){
                                            // Get y coordinate of the cover
                                            channelG = stoi(colorNode->value());
                                            continue;
                                        }
                                        // Check the value of the blue channel
                                        else if ((string)colorNode->name() == "B"){
                                            // Get y coordinate of the cover
                                            channelB = stoi(colorNode->value());
                                            if ((string)infoInd->name() == "ColorPanel"){
                                                panelIndicator.setFillColor(Color(channelR, channelG, channelB));
                                            }
                                            else if ((string)infoInd->name() == "ColorBorder"){
                                                panelIndicator.setOutlineColor(Color(channelR, channelG, channelB));
                                            }
                                            panelIndicator.setPosition(posX, posY);
                                            panelIndicator.setSize(sf::Vector2f(width, height));
                                            panelIndicator.setOutlineThickness(borderPanel);
                                        }
                                    }
                                }
                            }
                        }
                        // Check if it's the title of the panel
                        else if ((string)modeProperty->name() == "Font"){
                            // Load the font to specify the vehicle properties
                            fontVehicleIndicator.loadFromFile((string)modeProperty->value());
                            propertyText.setFont(fontVehicleIndicator);
                            continue;
                        }
                        else if ((string)modeProperty->name() == "Indicators"){
                            // Number of text processed
                            int posX, posY;
                            Text indicatorText;
                            // Loop to process all the indicators of the vehicle
                            for (xml_node<> *infoInd = modeProperty->first_node(); infoInd; infoInd = infoInd->next_sibling()){
                                // Loop to process all the indicators of the vehicle
                                for (xml_node<> *info = infoInd->first_node(); info; info = info->next_sibling()){
                                    // Check if it's the title of the panel
                                    if ((string)info->name() == "Content"){
                                        indicatorText.setString((string)info->value());
                                        continue;
                                    }
                                    // Check if it's the title of the panel
                                    else if ((string)info->name() == "PositionX"){
                                        posX = stoi(info->value());
                                        continue;
                                    }
                                    // Check if it's the title of the panel
                                    if ((string)info->name() == "PositionY"){
                                        posY = stoi(info->value());
                                        indicatorText.setPosition(posX, posY);
                                        continue;
                                    }
                                    // Check if it's the title of the panel
                                    else if ((string)info->name() == "Size"){
                                        indicatorText.setCharacterSize(stoi(info->value()));
                                        continue;
                                    }
                                    // Check if it's the node that controls the text of the speed panel
                                    else if ((string)info->name() == "Color"){
                                        // Variables to define the color of the text
                                        int channelR, channelG, channelB;
                                        // Loop in order to iterate all the children nodes of the text's color
                                        for (xml_node<> *colorNode = info->first_node(); colorNode; colorNode = colorNode->next_sibling()){
                                            // Check the value of the red channel
                                            if ((string)colorNode->name() == "R"){
                                                // Get y coordinate of the cover
                                                channelR = stoi(colorNode->value());
                                                continue;
                                            }
                                            // Check the value of the green channel
                                            else if ((string)colorNode->name() == "G"){
                                                // Get y coordinate of the cover
                                                channelG = stoi(colorNode->value());
                                                continue;
                                            }
                                            // Check the value of the blue channel
                                            else if ((string)colorNode->name() == "B"){
                                                // Get y coordinate of the cover
                                                channelB = stoi(colorNode->value());
                                                indicatorText.setFillColor(Color(channelR, channelG, channelB));
                                                vehicleIndicators.push_back(indicatorText);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}



void Menu::readVehicleSpecifications(char* pathVehicleName, int& topSpeed, float& angle,
                                     string& motor, float& timeBraking, float& timeAcceleration){

    // Path of the xml configuration file
    xml_document<> doc;
    file<> file(pathVehicleName);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *vehicle = doc.first_node();

    // Read the attributes of the vehicle
    for (xml_node<> *attributeVehicle = vehicle->first_node(); attributeVehicle; attributeVehicle = attributeVehicle->next_sibling()){
        // Check the value of the red channel
        if ((string)attributeVehicle->name() == "MaxSpeed"){
            // Get y coordinate of the cover
            topSpeed = stoi(attributeVehicle->value());
            continue;
        }
        // Check the value of the green channel
        else if ((string)attributeVehicle->name() == "Angle"){
            // Get y coordinate of the cover
            angle = stof(attributeVehicle->value());
            continue;
        }
        // Check the value of the red channel
        else if ((string)attributeVehicle->name() == "Motor"){
            // Get y coordinate of the cover
            motor = attributeVehicle->value();
            continue;
        }
        // Check the value of the green channel
        else if ((string)attributeVehicle->name() == "Braking"){
            // Get y coordinate of the cover
            timeBraking = stof(attributeVehicle->value());
            continue;
        }
        // Check the value of the green channel
        else if ((string)attributeVehicle->name() == "Acceleration"){
            // Get y coordinate of the cover
            timeAcceleration = stof(attributeVehicle->value());
        }
    }
}



/**
 * Shows the menu of selecting vehicle
 * @param app is the console where the game is displayed to the players
 * @param typeOfVehicle is the kind of vehicle selected by the user in the menu
 * @param colorVehicle is the vehicle's color selected by the user in the menu
 */
void Menu::showSelectionVehicleMenu(RenderWindow* app, int& typeOfVehicle, int& colorVehicle, Game_status& status, EffectReproductor* eR){

    // Clean the console window
    app->clear(Color(0, 0 ,0));

    // Control possible events
    Event ev;

    // Vector of the slots of the menu
    vector<Slot> slotsMenu;

    // Vector of the slots of the menu
    vector<Text> vehicleIndicators;

    // Vector of the texts for present the vehicle specifications
    vector<Text> vehicleSpecifications(5);

    // Variables to store the specifications of the vehicles
    int topSpeed;
    float angle, timeBraking, timeAcceleration;
    string motor;

    // Vector of vehicle specification values
    vector<VehicleSpecifications> specifications;

    VehicleSpecifications vH;

    // For each vehicle read it's specifications
    readVehicleSpecifications("Configuration/Vehicles/Motorbike.xml", topSpeed, angle, motor, timeBraking, timeAcceleration);
    vH = VehicleSpecifications(topSpeed, angle, motor, timeBraking, timeAcceleration);
    specifications.push_back(vH);

    readVehicleSpecifications("Configuration/Vehicles/Devastator.xml", topSpeed, angle, motor, timeBraking, timeAcceleration);
    vH = VehicleSpecifications(topSpeed, angle, motor, timeBraking, timeAcceleration);
    specifications.push_back(vH);

    readVehicleSpecifications("Configuration/Vehicles/Minivan.xml", topSpeed, angle, motor, timeBraking, timeAcceleration);
    vH = VehicleSpecifications(topSpeed, angle, motor, timeBraking, timeAcceleration);
    specifications.push_back(vH);

    readVehicleSpecifications("Configuration/Vehicles/Truck.xml", topSpeed, angle, motor, timeBraking, timeAcceleration);
    vH = VehicleSpecifications(topSpeed, angle, motor, timeBraking, timeAcceleration);
    specifications.push_back(vH);

    Sprite menuVehicle;
    Font fontMainText, fontVehicleName, fontVehicleIndicator, fontTitle;
    Text mainText, propertyText;

    RectangleShape panelIndicator;

    // Load the configuration of the vehicle's menu
    loadVehiclesMenu(menuVehicle, fontMainText, fontVehicleName, fontVehicleIndicator, fontTitle,
                     mainText, propertyText, slotsMenu, vehicleIndicators, panelIndicator);


    // Initialize the fonts of all the text
    for (int i = 0; i < (int)vehicleIndicators.size(); i++){
        vehicleIndicators[i].setFont(fontVehicleIndicator);
    }

    // Reproduce the sound
    eR->stopEffect(6);
    eR->reproduceEffect(6);

    // Change the texture of the cover
    app->draw(menuVehicle);
    app->draw(mainText);
    app->draw(panelIndicator);
    app->draw(propertyText);

    // Initialize the fonts of all the text
    for (int i = 0; i < (int)vehicleIndicators.size(); i++){
        app->draw(vehicleIndicators[i]);
    }

    string value;
    // Fill the specifications of the actual vehicle selected
    for (int i = 0; i < (int)vehicleSpecifications.size(); i++){
        vehicleSpecifications[i].setPosition(vehicleIndicators[i].getPosition().x + vehicleIndicators[i].getGlobalBounds().width + 10,
                                             vehicleIndicators[i].getPosition().y);

        vehicleSpecifications[i].setCharacterSize(vehicleIndicators[i].getCharacterSize());
        vehicleSpecifications[i].setFont(*vehicleIndicators[i].getFont());
        vehicleSpecifications[i].setFillColor(vehicleIndicators[i].getFillColor());
        switch(i){
            case 0:
                vehicleSpecifications[i].setString(to_string(specifications[0].speed));
                break;
            case 1:
                value = to_string(specifications[0].angle);
                vehicleSpecifications[i].setString(value.substr(0, value.find(".") + 3));
                break;
            case 2:
                vehicleSpecifications[i].setString(specifications[0].motor);
                break;
             case 3:
                value = to_string(specifications[0].timeToBrake);
                vehicleSpecifications[i].setString(value.substr(0, value.find(".") + 3) + " seconds");
                break;
            case 4:
                value = to_string(specifications[0].timeAccelerate);
                vehicleSpecifications[i].setString(value.substr(0, value.find(".") + 3) + " seconds");
        }
        app->draw(vehicleSpecifications[i]);
    }

    app->display();

    for (int i = 0; i < (int)slotsMenu.size(); i++){
        // Paint the slots with their initial colors
        if (i == 0){
            // The first is been selected
            slotsMenu[i].shape.setFillColor(slotsMenu[i].colorSelected);
            slotsMenu[i].shape.setOutlineColor(slotsMenu[i].colorBorderSelected);
            slotsMenu[i].vehicleName.setFillColor(slotsMenu[i].colorTextSelected);
            slotsMenu[i].vehicleName.setOutlineColor(slotsMenu[i].colorTextBorderSelected);
            slotsMenu[i].vehicleSprite.setTexture(slotsMenu[i].texturesOfVehicle[slotsMenu[i].actualTextureVehicle + 1]);
        }
        else {
            // The rest are not selected
            slotsMenu[i].shape.setFillColor(slotsMenu[i].colorUnSelected);
            slotsMenu[i].shape.setOutlineColor(slotsMenu[i].colorBorderUnSelected);
            slotsMenu[i].vehicleName.setFillColor(slotsMenu[i].colorTextUnSelected);
            slotsMenu[i].vehicleName.setOutlineColor(slotsMenu[i].colorTextBorderUnSelected);
            slotsMenu[i].vehicleSprite.setTexture(slotsMenu[i].texturesOfVehicle[slotsMenu[i].actualTextureVehicle]);
        }
        app->draw(slotsMenu[i].shape);
        app->draw(slotsMenu[i].vehicleName);
        app->draw(slotsMenu[i].vehicleSprite);
        app->draw(slotsMenu[i].vehicleName);
    }

    app->display();

    // Identifier of the actual button selected
    int optionParameter = 0;

    // Control the start key is pressed
    bool startPressed = false;

    // Control the backspace key is pressed
    bool backspacePressed = false;

    // While there is no vehicle selected
    // Loop until the player selects a mode pressing enter
    while (!startPressed && !backspacePressed){

        // Detect possible actions of the user on the console game
        if (app->pollEvent(ev) && ev.type == Event::Closed){
                app->close();
        }

        // Check if the left cursor keyword has been pressed
        if (Keyboard::isKeyPressed(Keyboard::Left)){
            // Check if the first slot is hovered or not
            if (optionParameter != 0){
                // Move the button hovered
                optionParameter--;
                // Change the color appearance of both buttons
                slotsMenu[optionParameter].shape.setOutlineColor(slotsMenu[optionParameter].colorBorderSelected);
                slotsMenu[optionParameter].shape.setFillColor(slotsMenu[optionParameter].colorSelected);
                slotsMenu[optionParameter + 1].shape.setOutlineColor(slotsMenu[optionParameter].colorBorderUnSelected);
                slotsMenu[optionParameter + 1].shape.setFillColor(slotsMenu[optionParameter].colorUnSelected);

                slotsMenu[optionParameter].vehicleName.setOutlineColor(slotsMenu[optionParameter].colorTextBorderSelected);
                slotsMenu[optionParameter].vehicleName.setFillColor(slotsMenu[optionParameter].colorTextSelected);
                slotsMenu[optionParameter + 1].vehicleName.setOutlineColor(slotsMenu[optionParameter].colorTextBorderUnSelected);
                slotsMenu[optionParameter + 1].vehicleName.setFillColor(slotsMenu[optionParameter].colorTextUnSelected);

                // Fill the specifications of the actual vehicle selected
                for (int i = 0; i < (int)vehicleSpecifications.size(); i++){
                    vehicleSpecifications[i].setPosition(vehicleIndicators[i].getPosition().x +
                                             vehicleIndicators[i].getGlobalBounds().width + 10, vehicleIndicators[i].getPosition().y);

                    vehicleSpecifications[i].setCharacterSize(vehicleIndicators[i].getCharacterSize());
                    vehicleSpecifications[i].setFont(*vehicleIndicators[i].getFont());
                    vehicleSpecifications[i].setFillColor(vehicleIndicators[i].getFillColor());
                    switch(i){
                        case 0:
                            vehicleSpecifications[i].setString(to_string(specifications[optionParameter].speed));
                            break;
                        case 1:
                            value = to_string(specifications[optionParameter].angle);
                            vehicleSpecifications[i].setString(value.substr(0, value.find(".") + 3));
                            break;
                        case 2:
                            vehicleSpecifications[i].setString(specifications[optionParameter].motor);
                            break;
                        case 3:
                            value = to_string(specifications[optionParameter].timeToBrake);
                            vehicleSpecifications[i].setString(value.substr(0, value.find(".") + 3) + " seconds");
                            break;
                        case 4:
                            value = to_string(specifications[optionParameter].timeAccelerate);
                            vehicleSpecifications[i].setString(value.substr(0, value.find(".") + 3) + " seconds");
                    }
                    app->draw(vehicleSpecifications[i]);
                }
                eR->stopEffect(2);
                eR->reproduceEffect(2);
            }
        }
        // Check if the down cursor keyword has been pressed
        else if (Keyboard::isKeyPressed(Keyboard::Right)){
            // Check if the first button is hovered or not
            if (optionParameter != (int)slotsMenu.size() - 1){
                // Move the button hovered
                optionParameter++;
                // Change the color appearance of both buttons
                slotsMenu[optionParameter].shape.setOutlineColor(slotsMenu[optionParameter].colorBorderSelected);
                slotsMenu[optionParameter].shape.setFillColor(slotsMenu[optionParameter].colorSelected);
                slotsMenu[optionParameter - 1].shape.setOutlineColor(slotsMenu[optionParameter].colorBorderUnSelected);
                slotsMenu[optionParameter - 1].shape.setFillColor(slotsMenu[optionParameter].colorUnSelected);

                slotsMenu[optionParameter].vehicleName.setOutlineColor(slotsMenu[optionParameter].colorTextBorderSelected);
                slotsMenu[optionParameter].vehicleName.setFillColor(slotsMenu[optionParameter].colorTextSelected);
                slotsMenu[optionParameter - 1].vehicleName.setOutlineColor(slotsMenu[optionParameter].colorTextBorderUnSelected);
                slotsMenu[optionParameter - 1].vehicleName.setFillColor(slotsMenu[optionParameter].colorTextUnSelected);

                // Fill the specifications of the actual vehicle selected
                for (int i = 0; i < (int)vehicleSpecifications.size(); i++){
                    vehicleSpecifications[i].setPosition(vehicleIndicators[i].getPosition().x +
                                             vehicleIndicators[i].getGlobalBounds().width + 10, vehicleIndicators[i].getPosition().y);

                    vehicleSpecifications[i].setCharacterSize(vehicleIndicators[i].getCharacterSize());
                    vehicleSpecifications[i].setFont(*vehicleIndicators[i].getFont());
                    vehicleSpecifications[i].setFillColor(vehicleIndicators[i].getFillColor());
                    switch(i){
                        case 0:
                            vehicleSpecifications[i].setString(to_string(specifications[optionParameter].speed));
                            break;
                        case 1:
                            value = to_string(specifications[optionParameter].angle);
                            vehicleSpecifications[i].setString(value.substr(0, value.find(".") + 3));
                            break;
                        case 2:
                            vehicleSpecifications[i].setString(specifications[optionParameter].motor);
                            break;
                        case 3:
                            value = to_string(specifications[optionParameter].timeToBrake);
                            vehicleSpecifications[i].setString(value.substr(0, value.find(".") + 3) + " seconds");
                            break;
                        case 4:
                            value = to_string(specifications[optionParameter].timeAccelerate);
                            vehicleSpecifications[i].setString(value.substr(0, value.find(".") + 3) + " seconds");
                    }
                    app->draw(vehicleSpecifications[i]);
                }
                eR->stopEffect(2);
                eR->reproduceEffect(2);
            }
        }

        // Get the number of sprites of the vehicle currently selected
        int numberOfSprites = (int)slotsMenu[optionParameter].texturesOfVehicle.size();

        // Control the sprite to turn
        switch(optionParameter){
            case 0:
                // Motorbike
                slotsMenu[optionParameter + 1].actualTextureVehicle = 0;
                slotsMenu[optionParameter + 1].vehicleSprite.setTexture(slotsMenu[optionParameter + 1].
                                        texturesOfVehicle[slotsMenu[optionParameter + 1].actualTextureVehicle]);
                break;
            case 1:
            case 2:
                // Devastator and minivan
                slotsMenu[optionParameter - 1].actualTextureVehicle = 0;
                slotsMenu[optionParameter + 1].actualTextureVehicle = 0;

                slotsMenu[optionParameter - 1].vehicleSprite.setTexture(slotsMenu[optionParameter - 1].
                                       texturesOfVehicle[slotsMenu[optionParameter - 1].actualTextureVehicle]);
                slotsMenu[optionParameter + 1].vehicleSprite.setTexture(slotsMenu[optionParameter + 1].
                                       texturesOfVehicle[slotsMenu[optionParameter + 1].actualTextureVehicle]);
                break;
            case 3:
                // Truck
                slotsMenu[optionParameter - 1].actualTextureVehicle = 0;

                slotsMenu[optionParameter - 1].vehicleSprite.setTexture(slotsMenu[optionParameter - 1].
                                       texturesOfVehicle[slotsMenu[optionParameter - 1].actualTextureVehicle]);
        }

        if (slotsMenu[optionParameter].actualTextureVehicle != numberOfSprites - 1){
            slotsMenu[optionParameter].actualTextureVehicle++;
        }
        else {
            slotsMenu[optionParameter].actualTextureVehicle = 1;
        }

        slotsMenu[optionParameter].vehicleSprite.setTexture(slotsMenu[optionParameter].
                                   texturesOfVehicle[slotsMenu[optionParameter].actualTextureVehicle]);

        app->draw(menuVehicle);
        app->draw(mainText);
        app->draw(panelIndicator);
        app->draw(propertyText);

        // Initialize the fonts of all the text
        for (int i = 0; i < (int)vehicleIndicators.size(); i++){
            app->draw(vehicleIndicators[i]);
            app->draw(vehicleSpecifications[i]);
        }

        // Show the buttons of the menu
        for (int i = 0; i < (int)slotsMenu.size(); i++){
            app->draw(slotsMenu[i].shape);
            app->draw(slotsMenu[i].vehicleSprite);
            app->draw(slotsMenu[i].vehicleName);
        }

        app->display();
        sleep(milliseconds(180));

        // Check if the start key has been pressed or not
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            startPressed = true;
            status = PLAYING;
            eR->stopEffect(4);
            eR->reproduceEffect(4);
        }
        // Check if the start key has been pressed or not
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)){
            backspacePressed = true;
            status = LEVEL_MENU;
            eR->stopEffect(5);
            eR->reproduceEffect(5);
        }
    }
    // Store the type of vehicle selected
    typeOfVehicle = optionParameter;
}



/**
 * Change a configuration parameter of the game that it's not relative to the player
 * @param optionParameter is the code of the parameter to modify
 */
void Menu::modifyOptionConfiguration(const int optionParameter, Type_control& control, Configuration* c,
                                     KeywordMapper* kM, EffectReproductor* eR)
{
    int volumeMusic;
    // Check if the left cursor keyword has been pressed
    if (Keyboard::isKeyPressed(Keyboard::Left)){
        // Control which configuration button is currently selected
        switch(optionParameter){
            case 0:
                // Check the control with mouse or keyword or joystick
                if (control == KEYBOARD){
                    // Control with keyword
                    menuButtons[optionParameter + 9].setTextButton("Mouse");
                    control = MOUSE;
                }
                else if (control == JOYSTICK){
                    // Control with keyboard
                    menuButtons[optionParameter + 9].setTextButton("Keyboard");
                    control = KEYBOARD;
                }
                // Check if the new type control is with the mouse
                if (control == MOUSE){
                    // Change the mode of the control to turn left and turn right
                    menuButtons[optionParameter + 16].setTextButton("Mouse to left");
                    menuButtons[optionParameter + 17].setTextButton("Mouse to right");
                }
                else {
                    // Change the mode of the control to turn left and turn right
                    int codeLeftKey = kM->lookForIdKeyWord(c->getLeftKey());
                    int codeRightKey = kM->lookForIdKeyWord(c->getRightKey());
                    string codeLeft = kM->mapperIdKeyWord[codeLeftKey];
                    string codeRight = kM->mapperIdKeyWord[codeRightKey];
                    menuButtons[optionParameter + 16].setTextButton(codeLeft);
                    menuButtons[optionParameter + 17].setTextButton(codeRight);
                }
                break;
            case 1:
                // Check the state of the traffic
                if (menuButtons[optionParameter + 9].getTextButton() == "No"){
                    // Desactivate the traffic in the game
                    menuButtons[optionParameter + 9].setTextButton("Yes");
                }
                break;
            case 2:
            case 3:
                // Check the state of the traffic
                volumeMusic = stoi(menuButtons[optionParameter + 9].getTextButton()) - 1;
                if (volumeMusic >= 0){
                    // Desactivate the traffic in the game
                    menuButtons[optionParameter + 9].setTextButton(to_string(volumeMusic));
                }
        }
    }
    // Check if the left cursor keyword has been pressed
    else if (Keyboard::isKeyPressed(Keyboard::Right)){
        // Control which configuration button is currently selected
        switch(optionParameter){
            case 0:
                // Check the control with mouse or keyword or joystick
                if (control == MOUSE){
                    // Control with keyboard
                    menuButtons[optionParameter + 9].setTextButton("Keyboard");
                    control = KEYBOARD;
                }
                else if (menuButtons[optionParameter + 9].getTextButton() == "Keyboard"){
                    // Control with joystick
                    menuButtons[optionParameter + 9].setTextButton("Joystick");
                    control = JOYSTICK;
                }
                // Check if the new type control is with the mouse
                if (control == MOUSE){
                    // Change the mode of the control to turn left and turn right
                    menuButtons[optionParameter + 16].setTextButton("Mouse to left");
                    menuButtons[optionParameter + 17].setTextButton("Mouse to right");
                }
                else {
                    // Change the mode of the control to turn left and turn right
                    int codeLeftKey = kM->lookForIdKeyWord(c->getLeftKey());
                    int codeRightKey = kM->lookForIdKeyWord(c->getRightKey());
                    string codeLeft = kM->mapperIdKeyWord[codeLeftKey];
                    string codeRight = kM->mapperIdKeyWord[codeRightKey];
                    menuButtons[optionParameter + 16].setTextButton(codeLeft);
                    menuButtons[optionParameter + 17].setTextButton(codeRight);
                }
                break;
            case 1:
                // Check the state of the traffic
                if (menuButtons[optionParameter + 9].getTextButton() == "Yes"){
                    // Desactivate the traffic in the game
                    menuButtons[optionParameter + 9].setTextButton("No");
                }
                break;
            case 2:
            case 3:
                // Check the state of the traffic
                volumeMusic = stoi(menuButtons[optionParameter + 9].getTextButton()) + 1;
                if (volumeMusic <= 100){
                    // Desactivate the traffic in the game
                    menuButtons[optionParameter + 9].setTextButton(to_string(volumeMusic));
                }
        }
    }
}



/**
 * Change a configuration parameter of the game that it's  relative to the player
 * @param optionParameter is the code of the parameter to modify
 */
void Menu::modifyOptionConfigurationPlayer(RenderWindow* app, const int optionParameter, Configuration* c,
                                           KeywordMapper* kM, EffectReproductor* eR)
{
    // Check what key is going to be modified
    // Check if any recognized keyword has been pressed or not
    Event e;
    app->waitEvent(e);
    if (e.type == Event::KeyPressed && e.key.code != -1 && e.key.code != Keyboard::Enter){
        // Check the configuration option that has to be changed
        Keyboard::Key key = kM->mapperCodeKeyWord[e.key.code];
        string codeKeyWord = kM->mapperIdKeyWord[e.key.code];
        // Change the configuration parameter if all is correct
        switch(optionParameter){
            case 4:
                // Change music selector
                if (!c->isRepeated(key)){
                    c->setChangeSoundtrack(key);
                    menuButtons[optionParameter + 9].setTextButton(codeKeyWord);
                }
                break;
            case 5:
                // Acceleration
                if (!c->isRepeated(key)){
                    c->setAccelerateKey(key);
                    menuButtons[optionParameter + 9].setTextButton(codeKeyWord);
                }
                break;
            case 6:
                // Braking
                if (!c->isRepeated(key)){
                    c->setBrakeKey(key);
                    menuButtons[optionParameter + 9].setTextButton(codeKeyWord);
                }
                break;
            case 7:
                // Turning left
                if (!c->isRepeated(key)){
                    c->setLeftKey(key);
                    menuButtons[optionParameter + 9].setTextButton(codeKeyWord);
                }
                break;
            case 8:
                // Turning right
                if (!c->isRepeated(key)){
                    c->setRightKey(key);
                    menuButtons[optionParameter + 9].setTextButton(codeKeyWord);
                }
        }
        eR->stopEffect(3);
        eR->reproduceEffect(3);
    }
}



