
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
                segaIcon.loadFromFile(pathNode->value());
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
void Animation::loadSegaIcons(RenderWindow* app, EffectReproductor* eR){

    app->setVerticalSyncEnabled(true);

	// create animation
	SfmlLogoAnimation logoAnim(*app);

	// load sound and texture
	eR->reproduceEffect(0);
    logoAnim.logo.setTexture(segaIcon);

	// set texture rects
	logoAnim.logo.setTextureRect({ 0, 0, 400, 304 });

	logoAnim.volume = 0.5f; // default is 1.f
	logoAnim.shakeStrength = 75.f; // default is 50.f
	logoAnim.letterScale = 1.f; // default is 0.7f
	logoAnim.shakeLength = sf::seconds(1.7f); // default is 0.6 seconds
	logoAnim.fadeStart = sf::seconds(6.f); // default is 11 seconds
	logoAnim.length = sf::seconds(13.f); // default is 13 seconds (approx. length of sound)

	// play animation
	logoAnim.play();

	app->clear(Color(0, 0, 0));
    app->display();

	// wait for sound to finish playing
	while (!logoAnim.isSoundFinished());
    eR->stopEffect(0);
}


/**
 * Shows the company of the game and also the presents image of the game
 * @param app is the console where the game is displayed to the players
 */
void Animation::loadGameData(RenderWindow* app){

    // Control possible events
    Event ev;

    app->setView(View(Vector2f(app->getSize().x / 2.f, app->getSize().y / 2.f), Vector2f(app->getSize().x, app->getSize().y)));

    // Detect possible actions of the user on the console game
    if (app->pollEvent(ev) && ev.type == Event::Closed){
        app->close();
    }

    // Clean the console of the game
    app->clear(Color::Black);
    // Set position to the company sprite
    menuSprite.setPosition(220, 100);
    // Load the texture to show it
    menuSprite.setTexture(company, true);
    // Store the textures of the menus in the console game
    app->draw(menuSprite);
    // Show the logos in the console
    app->display();
    // Sleep the process to see the menu icons correctly
    sleep(milliseconds(2500));

    // Clean the console of the game
    app->clear(Color::Black);
    // Set position to the presents sprite
    menuSprite.setPosition(300, 150);
    // Load the texture to show it
    menuSprite.setTexture(presents, true);
    // Store the textures of the menus in the console game
    app->draw(menuSprite);
    // Show the logos in the console
    app->display();
    // Sleep the process to see the menu icons correctly
    sleep(milliseconds(2500));
}
