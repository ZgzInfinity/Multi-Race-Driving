
#include "../include/Animation.h"


/**
 * Constructor of the data type Animation
 * @param pathMenuFile is the path where are indicated the textures used to the menus
 */
Animation::Animation(char* pathMenuFile){
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
        // Check if the actual node is the controller of the paths of the sega icons
        if ((string)texture->name() == "SegaAnimation"){
            // Loop for iterate throughout the path files and add then to the vector
            for (xml_node<> * pathNode = texture->first_node(); pathNode; pathNode = pathNode->next_sibling()){
                // Add the texture to the vector
                if (t.loadFromFile(pathNode->value())){
                    // Increment the textures read
                    menuTextures.push_back(t);
                }
            }
            continue;
        }
        // Check if the actual node is the controller of the path of the company images or yhe presents image
        else if ((string)texture->name() == "CompanyAnimation"){
            xml_node<> *node = texture->first_node();
            // Add the texture of the company or the texture of the presents image
            if (!company.loadFromFile(node->value())){
                cerr << "Error loading the company image of the game" << endl;
                exit(1);
            }
            continue;
        }
        // Check if the actual node is the controller of the path of the presents image of the game
        else if ((string)texture->name() == "PresentsAnimation"){
            xml_node<> *node = texture->first_node();
            // Add the texture of the company or the texture of the presents image
            if (!presents.loadFromFile(node->value())){
                cerr << "Error loading the presents image of the game" << endl;
                exit(1);
            }
            continue;
        }
    }
    // Establishing the position of the sprite
    menuSprite.setPosition(400, 350);
}



/**
 * Shows the different menus with the icons of Sega
 * @param app is the console where the game is displayed to the players
 */
void Animation::loadSegaIcons(RenderWindow& app){
    // Iterate thorough the different textures of the sega icons
    for (int i = 0; i < (int)menuTextures.size() - 3; i++){
        // Load the texture in the sprite in order to show it
        menuSprite.setTexture(menuTextures.at(i), true);
        // Store the textures of the menus in the console game
        app.draw(menuSprite);
        // Show the logos in the console
        app.display();
        // Sleep the process to see the menu icons correctly
        sleep(milliseconds(35));
    }
}


/**
 * Shows the company of the game and also the presents image of the game
 * @param app is the console where the game is displayed to the players
 */
void Animation::loadGameData(RenderWindow& app){
    // Clean the console of the game
    app.clear(Color::Black);
    // Set position to the company sprite
    menuSprite.setPosition(220, 100);
    // Load the texture to show it
    menuSprite.setTexture(company, true);
    // Store the textures of the menus in the console game
    app.draw(menuSprite);
    // Show the logos in the console
    app.display();
    // Sleep the process to see the menu icons correctly
    sleep(milliseconds(4000));

    // Clean the console of the game
    app.clear(Color::Black);
    // Set position to the presents sprite
    menuSprite.setPosition(300, 150);
    // Load the texture to show it
    menuSprite.setTexture(presents, true);
    // Store the textures of the menus in the console game
    app.draw(menuSprite);
    // Show the logos in the console
    app.display();
    // Sleep the process to see the menu icons correctly
    sleep(milliseconds(4000));
}
