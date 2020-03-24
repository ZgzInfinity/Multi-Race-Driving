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
inline void Menu::loadPlayerAndGameMenus(string pathFile){

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
                    fontPanel.loadFromFile(fontPath);
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
        else if ((string)node->name() == "Buttons"){
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
                        fontButton.loadFromFile(fontPath);
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
                        color_buttons.clear();
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
                        // Creation of the button and addition to the vector
                        menuButtons.push_back(Button(positionXTextButton, positionYTextButton, widthButton, heightButton,
                                                     fontButton, textContentButton, color_buttons[0], color_buttons[1],
                                                     color_buttons[2], initialStateButton));
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
void Menu::showMainMenu(RenderWindow* app){

    // Variables to store the information read from the file of the menu
    string imagePath, fontPath, textContent;

    // Coordinates of the cover and the main text
    int positionXCover, positionYCover, positionXText, positionYText, sizeText;

    // Color channels
    int channelR, channelG, channelB;

    // Load the main menu from the file
    loadMainMenu(imagePath, fontPath, textContent, positionXCover, positionYCover,
                 positionXText, positionYText, sizeText, channelR, channelG, channelB);

    // Variable to store the texture of the game's presents main cover
    Texture cover;
    cover.loadFromFile(imagePath);

    // Sprite where the different textures are loaded
    Sprite menuSprite;

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

    // Loop until start is pressed by the user
    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
        // Time to change the color of the font
        if (coverText.getColor() == colorMainText){
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
    }
}



/**
 * Shows the menu of selecting the number of players
 * @param app is the console where the game is displayed to the players
*/
void Menu::showPlayerMenu(RenderWindow* app){

    // Variables to store all the information of the menu panel
    string imagePath, textContent, fontPath, textContentButton;
    int positionXPanel, positionYPanel, width, height, border, positionXText, positionYText, sizeText;
    int positionXTextButton, positionYTextButton, widthButton, heightButton, initialStateButton;
    Color colorText;

    // Color channels
    int channelR, channelG, channelB;
    Font fontPanel, fontButton;

    // Load from file the player menu
    loadPlayerAndGameMenus("Configuration/Menus/PlayerMenu.xml");

    // Draw the rectangle of the player menu
    sf::RectangleShape rectangle;
    rectangle.setPosition(positionXPanel, positionYPanel);
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setOutlineColor(Color::Green);
    rectangle.setOutlineThickness(border);
    Texture background;
    background.loadFromFile(imagePath);
    rectangle.setTexture(&background, false);
    app->draw(rectangle);

    // Draw the text introduction of the menu
    Text playerText;
    playerText.setString(textContent);
    playerText.setFillColor(colorText);
    playerText.setCharacterSize(sizeText);
    playerText.setStyle(Text::Bold | Text::Underlined);
    playerText.setPosition(positionXText, positionYText);
    playerText.setFont(fontPanel);
    app->draw(playerText);

    // Identifier of the actual button selected
    int actualButtonHover = 0;

    // Show the buttons of the menu
    for (int i = 0; i < menuButtons.size(); i++){
        menuButtons.at(i).render(app);
    }
    // Display the changes of the buttons' appearance
    app->display();

    // Loop until the player selects a mode pressing enter
    while (!Keyboard::isKeyPressed(Keyboard::Space)){
        // Check if the up cursor keyword has been pressed
        if (Keyboard::isKeyPressed(Keyboard::Up)){
            // Check if the first button is hovered or not
            if (actualButtonHover != 0){
                // Move the button hovered
                actualButtonHover--;
                // Change the color appearance of both buttons
                menuButtons[actualButtonHover].setButtonState(BUTTON_HOVER);
                menuButtons[actualButtonHover + 1].setButtonState(BUTTON_IDLE);

                // Render the buttons with the changes
                app->draw(rectangle);
                app->draw(playerText);

                // Show the buttons of the menu
                for (int i = 0; i < menuButtons.size(); i++){
                    menuButtons.at(i).render(app);
                }
                app->display();
            }
        }
        // Check if the down cursor keyword has been pressed
        else if (Keyboard::isKeyPressed(Keyboard::Down)){
            // Check if the first button is hovered or not
            if (actualButtonHover != (int)menuButtons.size() - 1){
                // Move the button hovered
                actualButtonHover++;
                // Change the color appearance of both buttons
                menuButtons[actualButtonHover].setButtonState(BUTTON_HOVER);
                menuButtons[actualButtonHover - 1].setButtonState(BUTTON_IDLE);

                // Render the buttons with the changes
                app->draw(rectangle);
                app->draw(playerText);

                // Show the buttons of the menu
                for (int i = 0; i < menuButtons.size(); i++){
                    menuButtons.at(i).render(app);
                }
                app->display();
            }
        }
    }
}



/**
 * Shows the menu of selecting the game modes
 * @param app is the console where the game is displayed to the players
*/
void Menu::showGameModesMenu(RenderWindow* app){

    menuButtons.clear();

    // Variables to store all the information of the menu panel
    string imagePath, textContent, fontPath, textContentButton;
    int positionXPanel, positionYPanel, width, height, border, positionXText, positionYText, sizeText;
    int positionXTextButton, positionYTextButton, widthButton, heightButton, initialStateButton;
    Color colorText;

    // Color channels
    int channelR, channelG, channelB;
    Font fontPanel, fontButton;

     // Load from file the player menu
    loadPlayerAndGameMenus("Configuration/Menus/GameMenu.xml";)

    // Draw the rectangle of the player menu
    sf::RectangleShape rectangle;
    rectangle.setPosition(positionXPanel, positionYPanel);
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setOutlineColor(Color::Green);
    rectangle.setOutlineThickness(border);
    Texture background;
    background.loadFromFile(imagePath);
    rectangle.setTexture(&background, false);
    app->draw(rectangle);

    // Draw the text introduction of the menu
    Text playerText;
    playerText.setString(textContent);
    playerText.setFillColor(colorText);
    playerText.setCharacterSize(sizeText);
    playerText.setStyle(Text::Bold | Text::Underlined);
    playerText.setPosition(positionXText, positionYText);
    playerText.setFont(fontPanel);
    app->draw(playerText);

    // Identifier of the actual button selected
    int actualButtonHover = 0;

    // Show the buttons of the menu
    for (int i = 0; i < menuButtons.size(); i++){
        menuButtons.at(i).render(app);
    }
    // Display the changes of the buttons' appearance
    app->display();

    // Loop until the player selects a mode pressing enter
    while (!Keyboard::isKeyPressed(Keyboard::S)){
        // Check if the up cursor keyword has been pressed
        if (Keyboard::isKeyPressed(Keyboard::Up)){
            // Check if the first button is hovered or not
            if (actualButtonHover != 0){
                // Move the button hovered
                actualButtonHover--;
                // Change the color appearance of both buttons
                menuButtons[actualButtonHover].setButtonState(BUTTON_HOVER);
                menuButtons[actualButtonHover + 1].setButtonState(BUTTON_IDLE);

                // Render the buttons with the changes
                app->draw(rectangle);
                app->draw(playerText);

                // Show the buttons of the menu
                for (int i = 0; i < menuButtons.size(); i++){
                    menuButtons.at(i).render(app);
                }
                app->display();

                sleep(milliseconds(200));
            }
        }
        // Check if the down cursor keyword has been pressed
        else if (Keyboard::isKeyPressed(Keyboard::Down)){
            // Check if the first button is hovered or not
            if (actualButtonHover != (int)menuButtons.size() - 1){
                // Move the button hovered
                actualButtonHover++;
                // Change the color appearance of both buttons
                menuButtons[actualButtonHover].setButtonState(BUTTON_HOVER);
                menuButtons[actualButtonHover - 1].setButtonState(BUTTON_IDLE);

                // Render the buttons with the changes
                app->draw(rectangle);
                app->draw(playerText);

                // Show the buttons of the menu
                for (int i = 0; i < menuButtons.size(); i++){
                    menuButtons.at(i).render(app);
                }

                app->display();
                sleep(milliseconds(200));
            }
        }
    }
}
