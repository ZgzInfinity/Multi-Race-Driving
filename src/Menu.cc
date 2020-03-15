#include "../include/Menu.h"


/**
 * Constructor of the data type Animation
 * @param pathMenuFile is the path where are indicated the textures used to the menus
 */
Menu::Menu(char* pathMenuFile){
    // Read the textures used for the menus from the file

    // Document xml where the document is going to be parsed
    xml_document<> doc;
    file<> file(pathMenuFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *nodeMenu = doc.first_node();

    // Loop in order to iterate all the children of the principal node
    for (xml_node<> *texture = nodeMenu->first_node(); texture; texture = texture->next_sibling()){
        // Check if it's the node that controls the main menu of the game
        if ((string)texture->name() == "MainMenu"){
            xml_node<> *node = texture->first_node();
            // Add the texture of the company or the texture of the presents image
            if (!cover.loadFromFile(node->value())){
                cerr << "Error loading the cover image of the game" << endl;
                exit(1);
            }
            continue;
        }
    }
    // Establishing the position of the sprite
    menuSprite.setPosition(400, 350);
    coverText.setString("Press Start");
}



/**
 * Shows the main cover of the game until the player presses start
 * @param app is the console where the game is displayed to the players
 */
void Menu::showMainMenu(RenderWindow& app){
    // Clean the console of the game

    // Set position to the cover sprite
    menuSprite.setPosition(0, 0);

    // Load the texture to show it
    menuSprite.setTexture(cover, true);

    // Font of the text
    Font f;
    f.loadFromFile("Fonts/zorque.ttf");


    // Establish the format of the cover text
    coverText.setFillColor(Color::White);
    coverText.setCharacterSize(40);
    coverText.setStyle(Text::Bold);
    coverText.setPosition(400, 350);
    coverText.setFont(f);

    // Loop until start is pressed by the user
    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
        // Time to change the color of the font
        if (coverText.getColor() == Color::White){
            // Change color to transparent
            coverText.setFillColor(Color::Transparent);
        }
        else {
            // Change color to transparent
            coverText.setFillColor(Color::White);
        }
        // Clean the console of the game
        app.draw(menuSprite);
        app.draw(coverText);
        app.display();
        sleep(milliseconds(400));
    }
}
