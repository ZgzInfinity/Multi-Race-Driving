
#include "../include/Game.h"



/**
 * Load the Hud interface of the game
 */
void Game::loadHudGame(){
    // Load the elapsed time indicator with the time level indicator
    // and the speed indicator and the checkpoint
    Texture t;
    for (int i = 1; i <= 6; i++){
        // Load the textures of the three indicators
        t.loadFromFile("Data/Hud/" + to_string(i) + ".png");
        textures.push_back(t);
    }
    if (typeOfGame == 1 || (typeOfGame >= 3 && typeOfGame <= 5)){
        // Load the rest of textures necessary for the rest of game modes
        for (int i = 7; i <= 8; i++){
            // Load the textures of the rest of the game modes
            t.loadFromFile("Data/Hud/" + to_string(i) + ".png");
            textures.push_back(t);
        }

        // Code of first landscape
        int idFirstMap = 9;

        // Fill the matrix with the tree maps
        for (int i = 0; i <= 4; i++) {
            for (int j = 0; j <= i; j++) {
                t.loadFromFile("Data/Hud/" + to_string(idFirstMap) + ".png");
                treeMap[i][j] = t;
                idFirstMap++;
            }
        }
    }
}



/**
 * Draw the initial animation of the HUD
 */
void Game::drawHudAnimation(Configuration& c, SoundPlayer& r){

    float elapSedIndicator = 2.39f;
    float elapsedTextLap = 3.55f;
    float timeIndicator = 3.6f;
    float timeHud = 4.83f;

    float speedIndicator = -1.8f;
    float speedText = 1.6f;

    float levelInd = -1.8f;
    float levelIndicator = -1.8f;

    float scoreIndicator = 3.6f;
    float scoreHud = 4.78f;

    float treeIndicator = 1.6f;

    float distanceIndicator = 6.6f;

    float distancePanel = 6.3f;

    float checkPointIndicator = 4.83f;

    float checkPointDistance = 3.5f;

    // Check the initial sound to reproduce
    switch(typeOfGame){
        case 0:
        case 2:
            r.soundEffects[39]->stop();
            r.soundEffects[39]->play();
            break;
        case 1:
            r.soundEffects[38]->stop();
            r.soundEffects[38]->play();
            break;
        case 3:
        case 4:
            r.soundEffects[37]->stop();
            r.soundEffects[37]->play();
    }

    for (int i = 0; i <= 200; i++){

        // Detect the possible events
        Event e;
        c.window.pollEvent(e);

        // Draw the landscape
        currentMap->drawLandScape(c, cars);

        // Draw the vehicle
        switch(typeOfVehicle){
            case 0:
                player.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player.getPosY()));
                break;
            case 1:
                player2.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player2.getPosY()));
                break;
            case 2:
                player3.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player3.getPosY()));
                break;
            case 3:
                player4.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player4.getPosY()));
                break;
            case 4:
                player5.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player5.getPosY()));
        }

        Sprite s;

        // Assign positions in the game console for the game panel indicators
        const float up = float(c.w.getSize().y) / 10.0f;

        // UP
        s.setTexture(textures[0], true);
        s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
        const float separation = s.getGlobalBounds().width / 5.5f;
        s.setPosition(separation, up - elapSedIndicator * s.getGlobalBounds().height);
        float initial = separation + s.getGlobalBounds().width + separation;
        c.w.draw(s);

        // Indicator of the elapsed time
        Text elapsedTime;
        elapsedTime.setFont(c.fontElapsedTime);
        elapsedTime.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
        elapsedTime.setFillColor(Color::Green);

        // Available time to complete the level
        Text timeToPlay;
        timeToPlay.setString("000");
        timeToPlay.setFont(c.fontTimeToPlay);
        timeToPlay.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
        timeToPlay.setFillColor(Color::Yellow);
        timeToPlay.setOutlineColor(Color::Black);
        timeToPlay.setOutlineThickness(3.0f * c.screenScale);
        timeToPlay.setPosition(initial * 1.41f, up - timeIndicator * float(timeToPlay.getCharacterSize()));
        timeToPlay.setString(to_string(time));
        c.w.draw(timeToPlay);

        initial += elapsedTime.getGlobalBounds().width + separation;
        s.setTexture(textures[1], true);
        s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
        s.setPosition(initial * 1.15f, up - s.getGlobalBounds().height * timeHud);
        c.w.draw(s);
        initial += s.getGlobalBounds().width + separation;

        // Initialize the HUD indicator of lap time
        // Time of lap consumed
        Text textLap;
        textLap.setFont(c.fontElapsedTime);
        textLap.setString("00:00:00");
        textLap.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));
        textLap.setFillColor(Color::Green);
        initial = float(c.w.getSize().x) - separation - textLap.getGlobalBounds().width;
        textLap.setPosition(initial / 7.5f, up - elapsedTextLap * float(textLap.getCharacterSize()));
        c.w.draw(textLap);
        c.w.draw(s);

        // DOWN
        textures[2].loadFromFile("Data/Hud/7.png");
        s.setTexture(textures[2], true);
        s.setScale(2.f * c.screenScale, 1.5f * c.screenScale);
        const float down = float(c.w.getSize().y) - s.getGlobalBounds().height * 1.5f;
        s.setPosition(separation, float(c.w.getSize().y) - s.getGlobalBounds().height * 1.25f);
        initial = separation + s.getGlobalBounds().width / 4.0f;

        float speed;

        switch(typeOfVehicle){
            case 0:
                speed = player.getRealSpeed();
                break;
            case 1:
                speed = player2.getRealSpeed();
                break;
            case 2:
                speed = player3.getRealSpeed();
                break;
            case 3:
                speed = player4.getRealSpeed();
                break;
            case 4:
                speed = player5.getRealSpeed();
        }

        textures[2].loadFromFile("Data/Hud/3.png",
                                 IntRect(0, 0, static_cast<int>(speed * 117.0f / MAX_SPEED * c.screenScale),
                                         static_cast<int>(20.0f * c.screenScale)));


        s.setTexture(textures[2], true);
        if (speed > 0.0f)
            c.w.draw(s);

        // Text
        // HUD
        Text sText;
        sText.setFont(c.speedVehicle);
        sText.setString("0001");
        sText.setCharacterSize(static_cast<unsigned int>(int(70.0f * c.screenScale)));
        sText.setFillColor(Color(206, 73, 73));
        sText.setOutlineThickness(3.0f * c.screenScale);
        sText.setPosition(initial - (sText.getLocalBounds().width * speedText), down - float(sText.getCharacterSize()));
        initial += sText.getGlobalBounds().width;

        string strSpeed;

        switch(typeOfVehicle){
        case 0:
           strSpeed = to_string(player.getRealSpeed());
           break;
        case 1:
            strSpeed = to_string(player2.getRealSpeed());
            break;
        case 2:
            strSpeed = to_string(player3.getRealSpeed());
            break;
        case 3:
            strSpeed = to_string(player4.getRealSpeed());
            break;
        case 4:
            strSpeed = to_string(player5.getRealSpeed());
        }

        sText.setString(strSpeed.substr(0, strSpeed.find('.')));
        c.w.draw(sText);

        s.setTexture(textures[3], true);
        s.setScale(2.f * c.screenScale, 2.f * c.screenScale);
        s.setPosition(initial / 1.2f, down - s.getGlobalBounds().height * speedIndicator);
        c.w.draw(s);

        if (typeOfGame == 1 || (typeOfGame >= 3 && typeOfGame <= 5)){

            // Draw the tree map label with level of the player
            s.setTexture(treeMap[mapId.first][mapId.second], true);
            s.setScale(2.f * c.screenScale, 2.f * c.screenScale);
            initial = float(c.w.getSize().x) - separation - s.getGlobalBounds().width;
            s.setPosition(initial * treeIndicator, down - s.getGlobalBounds().height);
            c.w.draw(s);

            // Initialize the HUD stage indicator
            // Level indicator
            Text textLevel;
            textLevel.setFont(c.fontTimeToPlay);
            textLevel.setString("0");
            textLevel.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
            textLevel.setFillColor(Color(146, 194, 186));
            textLevel.setOutlineColor(Color::Black);
            textLevel.setOutlineThickness(3.0f * c.screenScale);
            initial -= separation + textLevel.getGlobalBounds().width;
            textLevel.setPosition(initial, down - levelInd * float(textLevel.getCharacterSize()));
            textLevel.setString(to_string(level));
            c.w.draw(textLevel);

            s.setTexture(textures[6], true);
            s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
            initial -= separation + s.getGlobalBounds().width;
            s.setPosition(initial * 1.03f, down - s.getGlobalBounds().height * levelIndicator);
            c.w.draw(s);

            // Score indicator
            s.setTexture(textures[7], true);
            s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
            const float separation = s.getGlobalBounds().width / 5.5f;
            s.setPosition(separation * 32.0f, up - scoreHud * s.getGlobalBounds().height);
            initial = separation + s.getGlobalBounds().width + separation;
            c.w.draw(s);

            // Initialize the HUD indicator of score
            // Score of the player displayed in the panel
            Text textScore;
            textScore.setFont(c.fontTimeToPlay);
            textScore.setString(to_string(int(BONIFICATION) * 100));
            textScore.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
            textScore.setFillColor(Color(183, 164, 190));
            textScore.setOutlineColor(Color::Black);
            textScore.setOutlineThickness(3.0f * c.screenScale);
            textScore.setString(to_string(score));
            textScore.setPosition(initial * 4.95f - textScore.getLocalBounds().width, up - scoreIndicator * float(textScore.getCharacterSize()));
            c.w.draw(textScore);

            // Add the distance tool bar if it's driving fury or Derramage mode
            if (typeOfGame == 3 || typeOfGame == 4){

                Text distanceText;
                distanceText.setFont(c.fontTimeToPlay);
                distanceText.setString(to_string(int(BONIFICATION) * 100));
                distanceText.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
                distanceText.setFillColor(Color(60, 235, 102));
                distanceText.setOutlineColor(Color::Black);
                distanceText.setOutlineThickness(3.0f * c.screenScale);
                distanceText.setString("DISTANCE");
                distanceText.setPosition(initial * distanceIndicator - distanceText.getLocalBounds().width, up * 2.5f - 2.6f * float(distanceText.getCharacterSize()));
                c.w.draw(distanceText);

                // Draw the rectangle
                RectangleShape shape;
                shape.setPosition(initial * distancePanel, up * 2.25f);
                shape.setSize(sf::Vector2f(40.0f * c.screenScale, 420.0f * c.screenScale));
                shape.setOutlineColor(Color::Black);
                shape.setOutlineThickness(3.0f * c.screenScale);
                shape.setFillColor(Color(119, 195, 187));
                c.w.draw(shape);

                /*
                Text healthText;
                healthText.setFont(c.fontTimeToPlay);
                healthText.setString(to_string(int(BONIFICATION) * 100));
                healthText.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
                healthText.setFillColor(Color(227, 17, 30));
                healthText.setOutlineColor(Color::Black);
                healthText.setOutlineThickness(3.0f * c.screenScale);
                healthText.setString("HEALTH");
                healthText.setPosition(initial / 1.1f - healthText.getLocalBounds().width, up * 2.5f - 2.6f * float(healthText.getCharacterSize()));
                c.w.draw(healthText);

                // Draw the rectangle
                shape.setPosition(initial / 2.0f, up * 2.25f);
                shape.setSize(sf::Vector2f(40.0f * c.screenScale, 420.0f * c.screenScale));
                shape.setOutlineColor(Color(43, 211, 30));
                shape.setOutlineThickness(3.0f * c.screenScale);
                shape.setFillColor(Color::Black);
                c.w.draw(shape);
                */
            }
        }
        else {
            // Check point indicator
            Text checkPoint;
            checkPoint.setFont(c.fontTimeToPlay);
            checkPoint.setCharacterSize(static_cast<unsigned int>(int(27.0f * c.screenScale)));
            checkPoint.setFillColor(Color::White);
            checkPoint.setOutlineColor(Color::Black);
            checkPoint.setOutlineThickness(3.0f * c.screenScale);

            int distance;

            // Check if it is the last checkPoint
            if (indexCheckPoint % 4 != 0){
                checkPoint.setString("NEXT CHECKPOINT");
                checkPoint.setPosition(initial * 3.1f, up - checkPointIndicator * float(checkPoint.getCharacterSize()));
                // Calculate the distance between the player and the checkpoint
                switch(typeOfVehicle){
                    case 0:
                        distance = (checkPointPositions[indexCheckPoint - 1] - player.getPosY()) / 7;
                        break;
                    case 1:
                        distance = (checkPointPositions[indexCheckPoint - 1] - player2.getPosY()) / 7;
                        break;
                    case 2:
                        distance = (checkPointPositions[indexCheckPoint - 1] - player3.getPosY()) / 7;
                        break;
                    case 3:
                        distance = (checkPointPositions[indexCheckPoint - 1] - player4.getPosY()) / 7;
                        break;
                    case 4:
                        distance = (checkPointPositions[indexCheckPoint - 1] - player5.getPosY()) / 7;
                }
            }
            else {
                checkPoint.setString("GOAL IN");
                checkPoint.setPosition(initial * 3.42f, up - checkPointIndicator * float(checkPoint.getCharacterSize()));

                switch(typeOfVehicle){
                    case 0:
                        distance = (currentMap->getMaxY() - player.getPosY()) / 7;
                        break;
                    case 1:
                        distance = (currentMap->getMaxY() - player2.getPosY()) / 7;
                        break;
                    case 2:
                        distance = (currentMap->getMaxY() - player3.getPosY()) / 7;
                        break;
                    case 3:
                        distance = (currentMap->getMaxY() - player4.getPosY()) / 7;
                        break;
                    case 4:
                        distance = (currentMap->getMaxY() - player5.getPosY()) / 7;
                }
            }

            c.w.draw(checkPoint);

            // Distance to the next checkpoint
            Text distanceCheckPoint;
            distanceCheckPoint.setFont(c.fontTimeToPlay);
            distanceCheckPoint.setString(to_string(distance) + " KM");
            distanceCheckPoint.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));

            // Check the color of the distance indicator
            if (distance >= 100){
                distanceCheckPoint.setFillColor(Color::Green);
            }
            else if(distance < 100 && distance >= 50){
                distanceCheckPoint.setFillColor(Color::Yellow);
            }
            else {
                distanceCheckPoint.setFillColor(Color::Red);
            }
            distanceCheckPoint.setOutlineColor(Color::Black);
            distanceCheckPoint.setOutlineThickness(3.0f * c.screenScale);
            distanceCheckPoint.setPosition(initial * 4.0f - distanceCheckPoint.getLocalBounds().width,
                                           up - checkPointDistance * float(distanceCheckPoint.getCharacterSize()));
            c.w.draw(distanceCheckPoint);
        }

        if (elapSedIndicator > 0.7f){
            elapSedIndicator -= 0.0095f;
        }

        if (elapsedTextLap > 0.6f){
            elapsedTextLap -= 0.0165f;
        }

        if (timeIndicator > 0.5f){
            timeIndicator -= 0.01705f;
        }

        if (scoreIndicator > 0.5f){
            scoreIndicator -= 0.01705f;
        }

        if (timeHud > 1.6f){
            timeHud -= 0.01705;
        }

        if (scoreHud > 1.55f){
            scoreHud -= 0.0173;
        }

        if (speedText > 0.26f){
            speedText -= 0.008;
        }

        if (speedIndicator < 1.0f){
            speedIndicator += 0.014;
        }

        if (levelInd < 1.0f){
            levelInd += 0.014;
        }

        if (levelIndicator < 1.0f){
            levelIndicator += 0.014;
        }

        if (treeIndicator > 1.0f){
            treeIndicator -= 0.0030;
        }

        if (distanceIndicator > 5.6f){
            distanceIndicator -= 0.0065f;
        }

        if (distancePanel > 5.14f){
            distancePanel -= 0.0065f;
        }

        if (checkPointIndicator > 1.8f){
            checkPointIndicator -= 0.0163;
        }

        if (checkPointDistance > 0.5f){
            checkPointDistance -= 0.01705f;
        }

        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();
    }
}


/**
 * Draw the HUD interface of the game
 * @param c is the configuration of the game
 */
void Game::showHudInterface(Configuration &c) {

    // Sprite to draw the elements of the HUD interface
    Sprite s;

    // Assign positions in the game console for the game panel indicators
    const float up = float(c.w.getSize().y) / 10.0f;

    // UP
    s.setTexture(textures[0], true);
    s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
    const float separation = s.getGlobalBounds().width / 5.5f;
    s.setPosition(separation, up - 0.7f * s.getGlobalBounds().height);
    float initial = separation + s.getGlobalBounds().width + separation;
    c.w.draw(s);

    // Indicator of the elapsed time
    Text elapsedTime;
    elapsedTime.setFont(c.fontElapsedTime);
    elapsedTime.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
    elapsedTime.setFillColor(Color::Green);

    // Available time to complete the level
    Text timeToPlay;
    timeToPlay.setString("000");
    timeToPlay.setFont(c.fontTimeToPlay);
    timeToPlay.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
    timeToPlay.setFillColor(Color::Yellow);
    timeToPlay.setOutlineColor(Color::Black);
    timeToPlay.setOutlineThickness(3.0f * c.screenScale);
    timeToPlay.setPosition(initial * 1.41f, up - 0.5f * float(timeToPlay.getCharacterSize()));
    timeToPlay.setString(to_string(time));
    c.w.draw(timeToPlay);

    initial += elapsedTime.getGlobalBounds().width + separation;
    s.setTexture(textures[1], true);
    s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
    s.setPosition(initial * 1.15f, up - s.getGlobalBounds().height * 1.6f);
    c.w.draw(s);
    initial += s.getGlobalBounds().width + separation;

    // Initialize the HUD indicator of lap time
    // Time of lap consumed
    Text textLap;
    textLap.setFont(c.fontElapsedTime);
    textLap.setString("00:00:00");
    textLap.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));
    textLap.setFillColor(Color::Green);
    initial = float(c.w.getSize().x) - separation - textLap.getGlobalBounds().width;
    textLap.setPosition(initial / 7.5f, up - 0.6f * float(textLap.getCharacterSize()));
    textLap.setString(lap);
    c.w.draw(textLap);
    c.w.draw(s);

    // DOWN
    textures[2].loadFromFile("Data/Hud/7.png");
    s.setTexture(textures[2], true);
    s.setScale(2.f * c.screenScale, 1.5f * c.screenScale);
    const float down = float(c.w.getSize().y) - s.getGlobalBounds().height * 1.5f;
    s.setPosition(separation, float(c.w.getSize().y) - s.getGlobalBounds().height * 1.25f);
    initial = separation + s.getGlobalBounds().width / 4.0f;

    float speed;

    switch(typeOfVehicle){
        case 0:
            speed = player.getRealSpeed();
            break;
        case 1:
            speed = player2.getRealSpeed();
            break;
        case 2:
            speed = player3.getRealSpeed();
            break;
        case 3:
            speed = player4.getRealSpeed();
            break;
        case 4:
            speed = player5.getRealSpeed();
    }

    textures[2].loadFromFile("Data/Hud/3.png",
                             IntRect(0, 0, static_cast<int>(speed * 117.0f / MAX_SPEED * c.screenScale),
                                     static_cast<int>(20.0f * c.screenScale)));


    s.setTexture(textures[2], true);
    if (speed > 0.0f)
        c.w.draw(s);

    // Text
    // HUD
    Text sText;
    sText.setFont(c.speedVehicle);
    sText.setString("0001");
    sText.setCharacterSize(static_cast<unsigned int>(int(70.0f * c.screenScale)));
    sText.setFillColor(Color(206, 73, 73));
    sText.setOutlineThickness(3.0f * c.screenScale);
    sText.setPosition(initial - (sText.getLocalBounds().width * 0.26f), down - float(sText.getCharacterSize()));
    initial += sText.getGlobalBounds().width;

    string strSpeed;

    switch(typeOfVehicle){
    case 0:
       strSpeed = to_string(player.getRealSpeed());
       break;
    case 1:
        strSpeed = to_string(player2.getRealSpeed());
        break;
    case 2:
        strSpeed = to_string(player3.getRealSpeed());
        break;
    case 3:
        strSpeed = to_string(player4.getRealSpeed());
        break;
    case 4:
        strSpeed = to_string(player5.getRealSpeed());
    }

    sText.setString(strSpeed.substr(0, strSpeed.find('.')));
    c.w.draw(sText);

    s.setTexture(textures[3], true);
    s.setScale(2.f * c.screenScale, 2.f * c.screenScale);
    s.setPosition(initial / 1.2f, down - s.getGlobalBounds().height);
    c.w.draw(s);

    if (typeOfGame == 1 || (typeOfGame >= 3 && typeOfGame <= 5)){

        // Draw the tree map label with level of the player
        s.setTexture(treeMap[mapId.first][mapId.second], true);
        s.setScale(2.f * c.screenScale, 2.f * c.screenScale);
        initial = float(c.w.getSize().x) - separation - s.getGlobalBounds().width;
        s.setPosition(initial, down - s.getGlobalBounds().height);
        c.w.draw(s);

        // Initialize the HUD stage indicator
        // Level indicator
        Text textLevel;
        textLevel.setFont(c.fontTimeToPlay);
        textLevel.setString("0");
        textLevel.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        textLevel.setFillColor(Color(146, 194, 186));
        textLevel.setOutlineColor(Color::Black);
        textLevel.setOutlineThickness(3.0f * c.screenScale);
        initial -= separation + textLevel.getGlobalBounds().width;
        textLevel.setPosition(initial, down - 1.0f * float(textLevel.getCharacterSize()));
        textLevel.setString(to_string(level));
        c.w.draw(textLevel);

        s.setTexture(textures[6], true);
        s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
        initial -= separation + s.getGlobalBounds().width;
        s.setPosition(initial * 1.03f, down - s.getGlobalBounds().height);
        c.w.draw(s);

        // Score indicator
        s.setTexture(textures[7], true);
        s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
        const float separation = s.getGlobalBounds().width / 5.5f;
        s.setPosition(separation * 32.0f, up - 1.55f * s.getGlobalBounds().height);
        initial = separation + s.getGlobalBounds().width + separation;
        c.w.draw(s);

        // Initialize the HUD indicator of score
        // Score of the player displayed in the panel
        Text textScore;
        textScore.setFont(c.fontTimeToPlay);
        textScore.setString(to_string(int(BONIFICATION) * 100));
        textScore.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
        textScore.setFillColor(Color(183, 164, 190));
        textScore.setOutlineColor(Color::Black);
        textScore.setOutlineThickness(3.0f * c.screenScale);
        textScore.setString(to_string(score));
        textScore.setPosition(initial * 4.95f - textScore.getLocalBounds().width, up - 0.5f * float(textScore.getCharacterSize()));
        c.w.draw(textScore);

        // Add the distance tool bar if it's driving fury or Derramage mode
        if (typeOfGame == 3 || typeOfGame == 4){

            Text distanceText;
            distanceText.setFont(c.fontTimeToPlay);
            distanceText.setString(to_string(int(BONIFICATION) * 100));
            distanceText.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
            distanceText.setFillColor(Color(60, 235, 102));
            distanceText.setOutlineColor(Color::Black);
            distanceText.setOutlineThickness(3.0f * c.screenScale);
            distanceText.setString("DISTANCE");
            distanceText.setPosition(initial * 5.6f - distanceText.getLocalBounds().width, up * 2.5f - 2.6f * float(distanceText.getCharacterSize()));
            c.w.draw(distanceText);

            // Draw the rectangle
            RectangleShape shape;
            shape.setPosition(initial * 5.14f, up * 2.25f);
            shape.setSize(sf::Vector2f(40.0f * c.screenScale, 420.0f * c.screenScale));
            shape.setOutlineColor(Color::Black);
            shape.setOutlineThickness(3.0f * c.screenScale);
            shape.setFillColor(Color(119, 195, 187));
            c.w.draw(shape);

            Text healthText;
            healthText.setFont(c.fontTimeToPlay);
            healthText.setString(to_string(int(BONIFICATION) * 100));
            healthText.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
            healthText.setFillColor(Color(227, 17, 30));
            healthText.setOutlineColor(Color::Black);
            healthText.setOutlineThickness(3.0f * c.screenScale);
            healthText.setString("HEALTH");
            healthText.setPosition(initial / 1.1f - healthText.getLocalBounds().width, up * 2.5f - 2.6f * float(healthText.getCharacterSize()));
            c.w.draw(healthText);

            // Draw the rectangle
            shape.setPosition(initial / 2.0f, up * 2.25f);
            shape.setSize(sf::Vector2f(40.0f * c.screenScale, 420.0f * c.screenScale));
            shape.setOutlineColor(Color(43, 211, 30));
            shape.setOutlineThickness(3.0f * c.screenScale);
            shape.setFillColor(Color::Black);
            c.w.draw(shape);
        }
    }
    else {
        // Check point indicator
        Text checkPoint;
        checkPoint.setFont(c.fontTimeToPlay);
        checkPoint.setCharacterSize(static_cast<unsigned int>(int(27.0f * c.screenScale)));
        checkPoint.setFillColor(Color::White);
        checkPoint.setOutlineColor(Color::Black);
        checkPoint.setOutlineThickness(3.0f * c.screenScale);

        int distance;

        // Check if it is the last checkPoint
        if (indexCheckPoint % 4 != 0){
            checkPoint.setString("NEXT CHECKPOINT");
            checkPoint.setPosition(initial * 3.1f, up - 1.8f * float(checkPoint.getCharacterSize()));
            // Calculate the distance between the player and the checkpoint
            switch(typeOfVehicle){
                case 0:
                    distance = (checkPointPositions[indexCheckPoint - 1] - player.getPosY()) / 7;
                    break;
                case 1:
                    distance = (checkPointPositions[indexCheckPoint - 1] - player2.getPosY()) / 7;
                    break;
                case 2:
                    distance = (checkPointPositions[indexCheckPoint - 1] - player3.getPosY()) / 7;
                    break;
                case 3:
                    distance = (checkPointPositions[indexCheckPoint - 1] - player4.getPosY()) / 7;
                    break;
                case 4:
                    distance = (checkPointPositions[indexCheckPoint - 1] - player5.getPosY()) / 7;
            }
        }
        else {
            checkPoint.setString("GOAL IN");
            checkPoint.setPosition(initial * 3.42f, up - 1.8f * float(checkPoint.getCharacterSize()));

            switch(typeOfVehicle){
                case 0:
                    distance = (currentMap->getMaxY() - player.getPosY()) / 7;
                    break;
                case 1:
                    distance = (currentMap->getMaxY() - player2.getPosY()) / 7;
                    break;
                case 2:
                    distance = (currentMap->getMaxY() - player3.getPosY()) / 7;
                    break;
                case 3:
                    distance = (currentMap->getMaxY() - player4.getPosY()) / 7;
                    break;
                case 4:
                    distance = (currentMap->getMaxY() - player5.getPosY()) / 7;
            }
        }

        c.w.draw(checkPoint);

        // Distance to the next checkpoint
        Text distanceCheckPoint;
        distanceCheckPoint.setFont(c.fontTimeToPlay);
        distanceCheckPoint.setString(to_string(distance) + " KM");
        distanceCheckPoint.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));

        // Check the color of the distance indicator
        if (distance >= 100){
            distanceCheckPoint.setFillColor(Color::Green);
        }
        else if(distance < 100 && distance >= 50){
            distanceCheckPoint.setFillColor(Color::Yellow);
        }
        else {
            distanceCheckPoint.setFillColor(Color::Red);
        }
        distanceCheckPoint.setOutlineColor(Color::Black);
        distanceCheckPoint.setOutlineThickness(3.0f * c.screenScale);
        distanceCheckPoint.setPosition(initial * 4.0f - distanceCheckPoint.getLocalBounds().width,
                                       up - 0.5f * float(distanceCheckPoint.getCharacterSize()));
        c.w.draw(distanceCheckPoint);
    }
}



/**
 * Change the soundtrack which is been sounding during the game
 * @param c is the configuration of the game
 * @param r is the sound reproducer of the game
 */
void Game::checkSoundtrackChanging(Configuration& c, SoundPlayer& r){

    // Check if the time to change the soundtrack has spent
    elapsed14 = soundtrackClock.getElapsedTime().asSeconds();

    //Check the time
    if (elapsed14 - elapsed13 >= soundtrack_delay.asSeconds()){
        // Check if the key to change the soundtrack has been pressed
        if (Keyboard::isKeyPressed(c.soundtrackKey)){
            // Inform that the soundtrack has been changed
            r.soundtrackChanged = true;
             // Stop the soundtrack of the game
            r.soundTracks[r.currentSoundtrack]->stop();
            // Change the soundtrack which is been reproduced
            if (r.currentSoundtrack != 11){
                // Advance to the following track
                r.currentSoundtrack++;
            }
            else {
                // Start the soundtrack list again
                r.currentSoundtrack = 2;
            }
            // Reproduce the new soundtrack
            r.soundTracks[r.currentSoundtrack]->play();

            // Restart the clock
            soundtrackClock.restart();
        }
        else {
            r.soundtrackChanged = false;
        }
    }
    else {
        // The time has not passed but could be changed before
        if (r.soundtrackChanged){
            // Display the title of the soundtrack
            Text titleSoundtrack;
            titleSoundtrack.setFont(c.fontTimeToPlay);
            titleSoundtrack.setString(r.titleSoundtracks[r.currentSoundtrack - 2]);
            titleSoundtrack.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
            titleSoundtrack.setFillColor(Color::Yellow);
            titleSoundtrack.setOutlineColor(Color(14, 29, 184));
            titleSoundtrack.setOutlineThickness(3.0f * c.screenScale);
            titleSoundtrack.setPosition((float(c.w.getSize().x) - titleSoundtrack.getGlobalBounds().width) / 2.0f,
                                 (float(c.w.getSize().y) - float(titleSoundtrack.getCharacterSize())) / 6.0f);

            c.w.draw(titleSoundtrack);
        }
    }
}



/**
 * Display the message of check point the screen of the game
 * @param c is the configuration of the game
 * @param visible controls if the check point message is visible or not
 */
void Game::showCheckpointIndications(Configuration &c, bool visible) {
    Sprite s;

    // CheckPoint title
    Text checkPointTitle;
    checkPointTitle.setFont(c.fontTimeToPlay);
    checkPointTitle.setString("CHECKPOINT!");
    checkPointTitle.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));

    checkPointTitle.setOutlineThickness(3.0f * c.screenScale);
    float initial = c.w.getSize().y / 3.0f + 0.25f * float(checkPointTitle.getCharacterSize());
    checkPointTitle.setPosition((float(c.w.getSize().x) - checkPointTitle.getGlobalBounds().width) / 2.0f,
                                c.w.getSize().y / 3.0f - float(checkPointTitle.getCharacterSize()));

    if (visible) {
        checkPointTitle.setFillColor(Color::Yellow);
        checkPointTitle.setOutlineColor(Color(14, 29, 184));
        c.w.draw(s);
        c.w.draw(checkPointTitle);

    }
    else {
        checkPointTitle.setFillColor(Color::Transparent);
        checkPointTitle.setOutlineColor(Color::Transparent);
    }

    Text textForLap;
    textForLap.setFont(c.fontElapsedTime);
    textForLap.setString("00:00:00");
    textForLap.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
    textForLap.setOutlineThickness(3.0f * c.screenScale);
    textForLap.setPosition(float(c.w.getSize().x) - s.getGlobalBounds().width / 2.0f, initial);

    Text extendTime;
    extendTime.setFont(c.fontTimeToPlay);
    extendTime.setString("EXTENDED TIME!");
    extendTime.setCharacterSize(static_cast<unsigned int>(int(25.0f * c.screenScale)));
    extendTime.setOutlineThickness(3.0f * c.screenScale);
    extendTime.setPosition((float(c.w.getSize().x) + textForLap.getGlobalBounds().width / 2.0f) / 2.8f, initial * 1.1f);

    s.setTexture(textures[4], true);
    s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
    textForLap.setPosition(
            (float(c.w.getSize().x) - textForLap.getGlobalBounds().width - s.getGlobalBounds().width) / 1.7f,
            initial + 3.4f * s.getGlobalBounds().height);
    s.setPosition((float(c.w.getSize().x) + textForLap.getGlobalBounds().width / 2.0f) / 2.4f, initial * 1.3f);

    if (visible) {
        textForLap.setFillColor(Color(146, 194, 186));
        textForLap.setOutlineColor(Color::Black);
        extendTime.setFillColor(Color(222, 42, 14));
        extendTime.setOutlineColor(Color::Black);
        c.w.draw(extendTime);
        c.w.draw(s);
    }
    else {
        textForLap.setFillColor(Color::Transparent);
        textForLap.setOutlineColor(Color::Transparent);
        extendTime.setFillColor(Color::Transparent);
        extendTime.setOutlineColor(Color::Transparent);
    }

    textForLap.setString(lapCheckPoint);
    c.w.draw(textForLap);
}



/**
 * Displays the message of game over in the console window
 * @param c is the configuration of the game
 */
void Game::showGameOver(Configuration &c) {
    // Game over text
    Text gameOver;
    gameOver.setFont(c.fontTimeToPlay);
    gameOver.setString("GAME OVER");
    gameOver.setCharacterSize(static_cast<unsigned int>(int(60.0f * c.screenScale)));
    gameOver.setFillColor(Color::Yellow);
    gameOver.setOutlineColor(Color(14, 29, 184));
    gameOver.setOutlineThickness(3.0f * c.screenScale);
    gameOver.setPosition((float(c.w.getSize().x) - gameOver.getGlobalBounds().width) / 2.0f,
                         (float(c.w.getSize().y) - float(gameOver.getCharacterSize())) / 2.0f);
    c.w.draw(gameOver);
}



/**
 * Shows the bonus message when the player arrives to the goal
 * @param c is the configuration of the game
 * @param seconds shows how many seconds the message will be shown
 * @param decs_second shows how many tenths of seconds the message will be shown
 */
void Game::showBonusIndications(Configuration &c, int seconds, int decs_second) {
    // Only for separation
    Sprite s;
    s.setTexture(textures[0], true);
    s.setScale(1.5f * c.screenScale, 1.5f * c.screenScale);
    const float separation = s.getGlobalBounds().width / 3.0f;

    // Final score after completing all the levels
    Text bonification;
    bonification.setFont(c.fontTimeToPlay);
    bonification.setString("BONUS POINTS!");
    bonification.setCharacterSize(static_cast<unsigned int>(int(65.0f * c.screenScale)));
    bonification.setFillColor(Color::Yellow);
    bonification.setOutlineColor(Color(12, 12, 12));
    bonification.setOutlineThickness(3.0f * c.screenScale);
    float initialY = float(c.w.getSize().y) / 3.0f + float(bonification.getCharacterSize());
    float initial = (float(c.w.getSize().x) - bonification.getGlobalBounds().width) / 2.0f;
    bonification.setPosition(initial, float(c.w.getSize().y) / 3.0f - float(bonification.getCharacterSize()));
    c.w.draw(bonification);

    // Time bonus to the player
    Text timeBonus;
    timeBonus.setFont(c.fontTimeToPlay);
    timeBonus.setString("000.0");
    timeBonus.setCharacterSize(static_cast<unsigned int>(int(55.0f * c.screenScale)));
    timeBonus.setFillColor(Color::Yellow);
    timeBonus.setOutlineColor(Color(12, 12, 12));
    timeBonus.setOutlineThickness(3.0f * c.screenScale);
    initial -= timeBonus.getLocalBounds().width;
    timeBonus.setPosition(initial, initialY);
    initialY += float(timeBonus.getCharacterSize());
    initial += 1.25f * timeBonus.getLocalBounds().width;
    timeBonus.setString(to_string(seconds) + "." + to_string(decs_second));
    c.w.draw(timeBonus);

    // Seconds arrival indicator
    Text secondsIndicator;
    secondsIndicator.setFont(c.fontTimeToPlay);
    secondsIndicator.setString("SEC");
    secondsIndicator.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
    secondsIndicator.setFillColor(Color(183, 164, 190));
    secondsIndicator.setOutlineColor(Color::Black);
    secondsIndicator.setOutlineThickness(3.0f * c.screenScale);
    secondsIndicator.setPosition(initial, initialY - float(secondsIndicator.getCharacterSize()));
    initial += separation + secondsIndicator.getLocalBounds().width;
    c.w.draw(secondsIndicator);

    // Seconds arrival indicator
    Text crossSign;
    crossSign.setFont(c.fontTimeToPlay);
    crossSign.setString("x");
    crossSign.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    crossSign.setFillColor(Color(232, 191, 157));
    crossSign.setOutlineColor(Color::Black);
    crossSign.setOutlineThickness(3.0f * c.screenScale);
    crossSign.setPosition(initial, initialY - float(crossSign.getCharacterSize()));
    initial += separation + crossSign.getLocalBounds().width;
    c.w.draw(crossSign);

    // Score factor to multiply
    Text scoreMultiply;
    scoreMultiply.setFont(c.fontTimeToPlay);
    scoreMultiply.setString(to_string((long long) BONIFICATION));
    scoreMultiply.setCharacterSize(static_cast<unsigned int>(int(55.0f * c.screenScale)));
    scoreMultiply.setFillColor(Color::Yellow);
    scoreMultiply.setOutlineColor(Color(12, 12, 12));
    scoreMultiply.setOutlineThickness(3.0f * c.screenScale);
    scoreMultiply.setPosition(initial, initialY - float(scoreMultiply.getCharacterSize()));
    initial += separation + scoreMultiply.getLocalBounds().width;
    c.w.draw(scoreMultiply);

    // Seconds arrival indicator
    Text pointsIndicator;
    pointsIndicator.setFont(c.fontTimeToPlay);
    pointsIndicator.setString("PTS");
    pointsIndicator.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
    pointsIndicator.setFillColor(Color(183, 164, 190));
    pointsIndicator.setOutlineColor(Color::Black);
    pointsIndicator.setOutlineThickness(3.0f * c.screenScale);
    pointsIndicator.setPosition(initial, initialY - float(pointsIndicator.getCharacterSize()));
    c.w.draw(pointsIndicator);
}



/**
 * Load the properties of the different available vehicles to play
 * @param path is the path of the xml configuration file of the vehicle
 * @param name is the brand of the vehicle
 * @param max_speed is the top speed reached by the vehicle in km/h / 100
 * @param angle is the turning angle of the vehicle
 * @param motorName is the brand's motor of the vehicle
 */
 void Game::loadVehicleProperties(const string path, string& name, float& max_speed, float& angle,
                                  string& motorName){

    // Preparing the cml file to be read
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *vehicleNode = doc.first_node();

    // Iterate throughout the properties of the vehicle
    for (xml_node<> *property = vehicleNode->first_node(); property; property = property->next_sibling()){
        // Get the name brand of the vehicle
        if ((string)property->name() == "Name"){
            name = (string)property->value();
        }
        // Get the stop speed reached by the vehicle
        else if ((string)property->name() == "MaxSpeed"){
            // Get the red channel
            max_speed = stof((string)property->value());
        }
        // Get the turning angle of the vehicle
        else if ((string)property->name() == "Angle"){
            // Get the red channel
            angle = stof((string)property->value());
        }
        // Get the motor brand of the vehicle
        else if ((string)property->name() == "Motor"){
            // Get the red channel
            motorName = (string)property->value();
        }
    }
 }




/**
 * Constructor of the game
 * @param c is the configuration of the game
 */
Game::Game(Configuration &c) : goalMap(goalFlagger, goalEnd, typeOfGame)
{

    // Variables to store the vehicle properties
    string brandName, motorName, pathFile;
    float max_speed, angle;

    // Load the properties of the motorbike
    pathFile = "Data/Vehicles/Motorbike/Configuration/Configuration.xml";
    loadVehicleProperties(pathFile, brandName, max_speed, angle, motorName);

    // Create the motorbike vehicle
    player = Motorbike(max_speed, SPEED_FACTOR, max_speed * ACCELERATION_INCREMENT / MAX_SPEED, 2.5f, 2.5f,
                       COUNTER, "Motorbike", 0.0f, RECTANGLE, brandName, angle, motorName);

    // Load the properties of the Devastator
    pathFile = "Data/Vehicles/Devastator/Configuration/Configuration.xml";
    loadVehicleProperties(pathFile, brandName, max_speed, angle, motorName);

    // Create the Devastator vehicle
    player2 = Devastator(max_speed, SPEED_FACTOR, max_speed * ACCELERATION_INCREMENT / MAX_SPEED, 4.f, 4.f,
                       COUNTER, "Devastator", 0.0f, RECTANGLE, brandName, angle, motorName);

     // Load the properties of the Devastator
    pathFile = "Data/Vehicles/Minivan/Configuration/Configuration.xml";
    loadVehicleProperties(pathFile, brandName, max_speed, angle, motorName);

    // Create the minivan vehicle
    player3 = Minivan(max_speed, SPEED_FACTOR, max_speed * ACCELERATION_INCREMENT / MAX_SPEED, 4.f, 4.f,
                       COUNTER, "Minivan", 0.0f, RECTANGLE, brandName, angle, motorName);

     // Load the properties of the Devastator
    pathFile = "Data/Vehicles/Truck/Configuration/Configuration.xml";
    loadVehicleProperties(pathFile, brandName, max_speed, angle, motorName);

    // Load the properties of the Truck
    player4 = Truck(max_speed, SPEED_FACTOR, max_speed * ACCELERATION_INCREMENT / MAX_SPEED, 4.5f, 4.5f,
                       COUNTER, "Truck", 0.0f, RECTANGLE, brandName, angle, motorName);

     // Load the properties of the Police car
    pathFile = "Data/Vehicles/Police/Configuration/Configuration.xml";
    loadVehicleProperties(pathFile, brandName, max_speed, angle, motorName);

    // Create the properties of the police car
    player5 = Police(max_speed, SPEED_FACTOR, max_speed * ACCELERATION_INCREMENT / MAX_SPEED, 4.f, 4.f,
                       COUNTER, "Police", 0.0f, RECTANGLE, brandName, angle, motorName);


    typeOfVehicle = 0;
    lastY = 0;
    vehicleCrash = false;
    timeMul = 1.0f;
    scoreMul = 1.0f;
    timeAI = 0.0f;

    // Control if the player is still playing
    finalGame = false;
    inGame = false;
    onPause = false;
    comeFromOptions = false;
    blink = false;
    arrival = false;
    updatedTimeCheck = false;
    woman_delay = seconds(5.0f);
    traffic_delay = seconds(2.f);
    blink_delay = seconds(0.5f);
    bonus_delay = seconds(0.01f);

    minutes = 0;
    secs = 0;
    cents_second = 0;
    minutesTrip = 0;
    secsTrip = 0;
    cents_secondTrip = 0;
    timeCheck = 0;
    posArrival = 1;

    goalMap = LandScape(goalFlagger, goalEnd, typeOfGame);
    lap = "00:00:00";
    typeOfGame = 1;

    // Loads enemies and time
    checkDifficulty(c);
}



/**
 * Load the configuration of the world tour and pole position modes
 * @param c is the configuration of the game
 */
State Game::loadWorldTourPolePositionConf(Configuration& c){
    // Times of each scenario
    const int times[] = {40, 43, 44, 45};

    // Loop for load the maps
    for (int i = 0; i < 4; i++) {
        // Load the landscape using the correspond path
        LandScape m(c, "Data/Gamemodes/WorldTour/LandScapes/LandScape" + to_string(i + 1) + "/", "bg.png", times[i], typeOfGame);
        tourLandScapes.push_back(m);
    }

    // Index of the first landscape
    indexLandScape = 0;
    // Definition of the first landScape
    currentMap = &tourLandScapes[indexLandScape];

    // Back door
    int bdTime = 0;
    time = int(float(currentMap->getTimeToPlay()) * timeMul) + bdTime;
    score = 0;
    level = -1;

    // Load the game mode hud
    loadHudGame();

    // Loads enemies and time
    checkDifficulty(c);

    // Initialize the checkpoint index
    indexCheckPoint = 1;
    checkPointPositions = tourLandScapes[indexLandScape].getCheckPointPositions();

    return PLAY_GAME;
}



/**
 * Load the configuration of the Out Run, Driving Fury and Demarrage modes
 * @param c is the configuration of the game
 */
State Game::loadOutRunDrivingFuryDemarrageConf(Configuration& c){
    // Control the loading of the landscapes
    int nm = 0;
    // Times of each scenario
    const int times[] = {85, 58, 68, 50, 75, 69, 53, 54, 49, 48, 46, 42, 42, 41, 42};

    // Path which depends of the mode selected by the player
    string pathMode;

    switch(typeOfGame){
        case 0:
            // World tour mode
            pathMode = "Data/Gamemodes/WorldTour/LandScapes/LandScape";
            break;
        case 1:
            // Out Run mode
            pathMode = "Data/Gamemodes/OutRun/LandScapes/LandScape";
            break;
        case 2:
            // Pole Position mode
            pathMode = "Data/Gamemodes/PolePosition/LandScapes/LandScape";
            break;
        case 3:
            // Driving fury mode
            pathMode = "Data/Gamemodes/DrivingFury/LandScapes/LandScape";
            typeOfVehicle = 4;
            break;
        case 4:
            // Demarrage mode
            pathMode = "Data/Gamemodes/Derramage/LandScapes/LandScape";
            break;
        case 5:
            // Delivery mode
            pathMode = "Data/Gamemodes/Delivery/LandScapes/LandScape";
    }


    // Loop for load the maps
    for (int i = 0; i < 5; i++) {
        vector<LandScape> vm;
        for (int j = 0; j <= i; j++) {
            // Load the landscape using the correspond path
            LandScape m(c, pathMode + to_string(nm + 1) + "/", "bg.png", times[nm], typeOfGame);
            vm.push_back(m);
            nm++;
        }
        // Store the map in the matrix
        maps.emplace_back(vm);
    }
    mapId = make_pair(0, 0);

    // Back door
    int bdTime = 0;
    ifstream fin("Data/backdoor.info");
    if (fin.is_open()) {
        int bdMap = 1;
        while (!fin.eof()) {
            string s;
            fin >> s;
            if (s == "MAP:" && !fin.eof()) {
                fin >> bdMap;
                if (bdMap > 0 && bdMap <= 15) {
                    for (int i = 1; i < bdMap; i++) {
                        if (mapId.second < mapId.first) {
                            mapId.second++;
                        } else {
                            mapId.second = 0;
                            mapId.first++;
                        } // Level????????????????????????
                    }
                }
            } else if (s == "TIME:" && !fin.eof()) {
                fin >> bdTime;
            }
        }
        fin.close();
    }

    currentMap = &maps[mapId.first][mapId.second];
    if (mapId.first < 4)
        currentMap->addFork(&maps[mapId.first + 1][mapId.second], &maps[mapId.first + 1][mapId.second + 1]);
    else {
        goalMap.setColorsLandScape(*currentMap);
        currentMap->addNewLandScape(&goalMap);
    }

    // Load the game mode hud
    loadHudGame();

    // Start the time of the first level
    time = int(float(currentMap->getTimeToPlay()) * timeMul) + bdTime;
    score = 0;
    level = mapId.first + 1;

    // Loads enemies and time
    checkDifficulty(c);

    // Start the game
    return PLAY_GAME;
}



/**
 * Check the level of difficulty and regulates the parameters
 * @param c
 */
void Game::checkDifficulty(Configuration &c) {
    int numCars = static_cast<int>(cars.size()); // Number of vehicles simultaneously
    time = int(float(time - int(timeAI)) / timeMul); // Restore original time

    float prevScoreMul = scoreMul;
    switch (c.level) {
        case PEACEFUL:
            numCars = 0;
            timeMul = 1.1f;
            scoreMul = 0.25f;
            if (c.enableAI)
                c.maxAggressiveness = 0.0f;
            break;
        case EASY:
            numCars = 5;
            timeMul = 1.1f;
            scoreMul = 0.5f;
            if (c.enableAI)
                c.maxAggressiveness = 0.25f;
            break;
        case NORMAL:
            numCars = 10;
            timeMul = 1.0f;
            scoreMul = 1.0f;
            if (c.enableAI)
                c.maxAggressiveness = 0.5f;
            break;
        case HARD:
            numCars = 15;
            timeMul = 0.9f;
            scoreMul = 1.5f;
            if (c.enableAI)
                c.maxAggressiveness = 0.75f;
            break;
        default:
            break;
    }
    if (prevScoreMul < scoreMul) // Keep the least multiplier
        scoreMul = prevScoreMul;

    if (!c.enableAI)
        c.maxAggressiveness = 0.0f;

    // Vehicles
    cars.reserve(static_cast<unsigned long>(numCars));
    if (cars.size() > numCars) {
        while (cars.size() > numCars)
            cars.pop_back();
    }
    else if (cars.size() < numCars) {
        const int maxSprites = 6;
        const float vehicleScales[maxSprites] = {1.5f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f};
        for (int i = static_cast<int>(cars.size()); i < numCars; i++) {
            TrafficCar v(MAX_SPEED, SPEED_FACTOR, vehicleScales[i % maxSprites], COUNTER,
                    "TrafficCars/Car" + to_string(1 + i % maxSprites), -RECTANGLE * DEL_DISTANCE * 3.0f);
            cars.push_back(v);
        }
    }

    for (TrafficCar &v : cars){
        v.setAI(c.maxAggressiveness);
    }

    time = int(float(time) * timeMul);
    timeAI = !cars.empty() ? float(time) * c.maxAggressiveness / 3.0f : 0.0f;
    time += int(timeAI);

    if (time < 0)
        time = 0;
}



/**
 * Returns true if the player is during the game.
 * Otherwise returns false.
 * @return
 */
bool Game::isInGame() const {
    return inGame;
}



/**
 * Set the type of game selected by the player in the game modes menu
 * @param typeGame is the game selected by the player
 */
void Game::setTypeOfGame(const int typeGame){
    typeOfGame = typeGame;
}



/**
 * Returns the game mode selected by the player
 * @return
 */
int Game::typeGame() const {
    return typeOfGame;
}



/**
     * Returns the total score got by the player
     * @return
     */
unsigned long Game::getScore() const {
    return static_cast<unsigned long>(score);
}



/**
 * Returns the total minutes inverted by the player
 * @return
 */
float Game::getMinutesTrip() const {
    return minutesTrip;
}



/**
 * Returns the total seconds inverted by the player
 * @return
 */
float Game::getSecsTrip() const {
    return secsTrip;
}



/**
 * Returns the total hundredths of a second inverted by the player
 * @return
 */
float Game::getCents_SecondTrip() const {
    return cents_secondTrip;
}



/**
 * Updates the logic of the game and refreshes the screen until you leave the game.
 * @param c is the configuration of the game
 * @return
 */
State Game::play(Configuration &c, SoundPlayer& r) {

    if (!inGame) {
        inGame = true;
        showsInitialAnimation(c, r);
    }
    else if ((typeOfGame == 0 || typeOfGame == 2) && !comeFromOptions){
        showsInitialAnimation(c, r);
    }

    c.window.setKeyRepeatEnabled(false);

    // Time to update the clock counter
    Time shot_delayTime = seconds(1.0);

    // Time to update the clock counter lap
    Time shot_delayLap = seconds(0.01);

    // Time to change again the soundtrack
    soundtrack_delay = seconds(3.0);

    // Initialize the clock counters of time
    gameClockTime.restart().asSeconds();
    elapsed1 = gameClockTime.restart().asSeconds();

    gameClockLap.restart();
    elapsed3 = gameClockLap.getElapsedTime().asSeconds();

    womanShot.restart();
    elapsed5 = womanShot.getElapsedTime().asSeconds();

    trafficCarSound.restart();
    elapsed7 = trafficCarSound.getElapsedTime().asSeconds();

    blinkTime.restart();
    elapsed9 = blinkTime.getElapsedTime().asSeconds();

    soundtrackClock.restart();
    elapsed13 = soundtrackClock.getElapsedTime().asSeconds();

    Vehicle::Action action;
    Vehicle::Direction direction;

    State status;

    while (!finalGame && !arrival && c.window.isOpen()) {
        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)){
            if (e.type == Event::Closed){
                return EXIT;
            }
        }

        // Update the status of the game
        updateGameStatus(c, r, action, direction);

        // Control the final of the game
        if (!finalGame) {
            // Check is the game is on pause
            if (Keyboard::isKeyPressed(c.menuKey) || onPause) {
                // Pause the game
                r.soundEffects[1]->stop();
                r.soundEffects[1]->play();
                status = pause(c, r, action, direction);

                // Control the exit of the game
                if (status == OPTIONS) {
                    comeFromOptions = true;
                    finalGame = true;
                }
                else if (status == START) {
                    finalGame = true;
                    inGame = false;
                    r.soundTracks[r.currentSoundtrack]->stop();
                    return START;
                }
                else if (status == PLAY_GAME) {
                    r.soundTracks[r.currentSoundtrack]->play();
                }
                else if (status == EXIT) {
                    return EXIT;
                }
                gameClockLap.restart();
            }

            float speed;

            switch(typeOfVehicle){
                case 0:
                    speed = player.getRealSpeed();
                    // Update the score of the player if the player is not stopped
                    if (speed > 0.0f) {
                        // Add score
                        score += int(player.getRealSpeed() * scoreMul);
                    }
                    break;
                case 1:
                    speed = player2.getRealSpeed();
                    // Update the score of the player if the player is not stopped
                    if (speed > 0.0f) {
                        // Add score
                        score += int(player2.getRealSpeed() * scoreMul);
                    }
                    break;
                case 2:
                    speed = player3.getRealSpeed();
                    // Update the score of the player if the player is not stopped
                    if (speed > 0.0f) {
                        // Add score
                        score += int(player3.getRealSpeed() * scoreMul);
                    }
                    break;
                case 3:
                    speed = player4.getRealSpeed();
                    // Update the score of the player if the player is not stopped
                    if (speed > 0.0f) {
                        // Add score
                        score += int(player4.getRealSpeed() * scoreMul);
                    }
                    break;
                case 4:
                    speed = player5.getRealSpeed();
                    // Update the score of the player if the player is not stopped
                    if (speed > 0.0f) {
                        // Add score
                        score += int(player5.getRealSpeed() * scoreMul);
                    }

            }

            // Get the actual time
            elapsed4 = gameClockLap.getElapsedTime().asSeconds();

            // Check if a tenth of second has passed between both timestamps
            if (elapsed4 - elapsed3 >= shot_delayLap.asSeconds()) {
                cents_second += elapsed4;
                if (cents_second >= 1.f) {
                    cents_second -= 1.f;
                    secs++;
                    if (secs == 60.f) {
                        secs = 0;
                        minutes++;
                    }
                }
                cents_secondTrip += elapsed4;
                if (cents_secondTrip >= 1.f) {
                    cents_secondTrip -= 1.f;
                    secsTrip++;
                    if (secsTrip == 60.f) {
                        secsTrip = 0;
                        minutesTrip++;
                    }
                }
                gameClockLap.restart();
            }

            // Get the actual time
            elapsed2 = gameClockTime.getElapsedTime().asSeconds();

            // Check if a second has passed between both timestamps
            if (elapsed2 - elapsed1 >= shot_delayTime.asSeconds()) {
                // Draw time
                time--;
                gameClockTime.restart();
            }

            // Update the indicators
            lap = (minutes < 10) ? "0" + to_string(int(minutes)) + ":" : to_string(int(minutes)) + ":";
            lap += (secs < 10) ? "0" + to_string(int(secs)) + ":" : to_string(int(secs)) + ":";
            int cent_sec = cents_second * 100.f;
            lap += (cent_sec < 10) ? "0" + to_string(cent_sec) : to_string(cent_sec);

            // Draw the HUD of the game
            showHudInterface(c);

            // Control if the music has been change by the player
            checkSoundtrackChanging(c, r);


            Sprite bufferSprite(c.w.getTexture());
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();

            if (time == 10) {
                r.soundEffects[26]->stop();
                r.soundEffects[26]->play();
            }

            // Check if the player has time to continue
            if (time == 0) {
                // Final game
                finalGame = true;
            }
        }
    }

    finalGame = false;

    if (arrival) {
        arrival = false;
        if (typeOfGame == 0 || typeOfGame == 2){
            // World tour and Pole Position modes
            return CLASIFICATION;
        }
        else {
            // The rest of the modes
            return RANKING;
        }
    }

    if (status != OPTIONS && status != START) {
        // Draw the game over text in the console window
        showGameOver(c);
        r.soundTracks[r.currentSoundtrack]->stop();
        r.soundEffects[25]->stop();
        r.soundEffects[25]->play();
        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();
        sleep(r.soundEffects[24]->getDuration());

        bool startPressed = false;
        r.soundTracks[13]->play();
        while (!startPressed) {

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }

            startPressed = Keyboard::isKeyPressed(c.menuEnterKey);
        }
        r.soundTracks[13]->stop();
        r.soundEffects[2]->stop();
        r.soundEffects[2]->play();
        return START;
    }
    return status;
}



/**
 * Stops the game
 * @param c is the configuration of the game
 * @param a is the last action done by the player
 * @param d is the last direction done by the player
 * @return
 */
State Game::showsInitialAnimation(Configuration &c, SoundPlayer& r) {

    int flagger, semaphore;

    if (indexLandScape == 0){
        r.soundTracks[r.currentSoundtrack]->stop();
        LandScape *initMap = new LandScape(*currentMap, flagger, semaphore, typeOfGame);
        initMap->addNewLandScape(currentMap);
        initMap->setColorsLandScape(*currentMap);

        if (typeOfGame == 0 || typeOfGame == 2){
            goalMap.setColorsLandScape(*currentMap);
            currentMap->addNewLandScape(&goalMap);
        }
        currentMap = initMap;
    }
    else {
        LandScape *initMap = new LandScape(*currentMap, flagger, semaphore, typeOfGame);
        initMap->addNewLandScape(currentMap);
        initMap->setColorsLandScape(*currentMap);

        if (typeOfGame == 0 || typeOfGame == 2){
            goalMap.setColorsLandScape(*currentMap);
            currentMap->addNewLandScape(&goalMap);
        }
        currentMap = initMap;
    }

    // Semaphore and flagger
    currentMap->addMapElelementIndex(flagger, false, -1);
    int ms = 1000;

    currentMap->drawLandScape(c, cars);

     // Draw the hud animation
    drawHudAnimation(c, r);

    switch(typeOfVehicle){
        case 0:
            player.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player.getPosY()));
            break;
        case 1:
            player2.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player2.getPosY()));
            break;
        case 2:
            player3.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player3.getPosY()));
            break;
        case 3:
            player4.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player4.getPosY()));
            break;
        case 4:
            player5.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player5.getPosY()));
    }


    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Detect the possible events
    Event e;

    for (int i = 0; i < 3; i++) {

        // Detect the possible events
        while (c.window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return EXIT;
            }
        }

        // Draw map
        c.w.clear();
        currentMap->drawLandScape(c, cars);

        switch(typeOfVehicle){
            case 0:
                player.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player.getPosY()));
                break;
            case 1:
                player2.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player2.getPosY()));
                break;
            case 2:
                player3.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player3.getPosY()));
                break;
            case 3:
                player4.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player4.getPosY()));
                break;
            case 4:
                player5.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player5.getPosY()));
        }

        // Draw the HUD of the game
        showHudInterface(c);


        bufferSprite.setTexture(c.w.getTexture(), true);
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

        // Flagger
        if (i == 2) {
            for (; ms > 0; ms -= 200) {
                sleep(milliseconds(200));

                currentMap->addMapElelementIndex(flagger, false);

                // Draw map
                c.w.clear();
                currentMap->drawLandScape(c, cars);

                switch(typeOfVehicle){
                    case 0:
                        player.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player.getPosY()));
                        break;
                    case 1:
                        player2.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player2.getPosY()));
                        break;
                    case 2:
                        player3.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player3.getPosY()));
                        break;
                    case 3:
                        player4.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player4.getPosY()));
                        break;
                    case 4:
                        player5.draw(c, r, Vehicle::Action::NONE, Vehicle::Direction::RIGHT, currentMap->getElevation(player5.getPosY()));
                }

                showHudInterface(c);

                bufferSprite.setTexture(c.w.getTexture(), true);
                c.w.display();
                c.window.draw(bufferSprite);
                c.window.display();
            }
        }

        // Change semaphore state
        if (ms > 0) {
            sleep(milliseconds(ms));
            r.soundEffects[4]->stop();
            r.soundEffects[4]->play();
        }
        currentMap->addMapElelementIndex(semaphore, false);
        r.soundEffects[5]->stop();
        r.soundEffects[5]->play();
    }
    currentMap->addMapElelementIndex(flagger, false, -1);
    r.soundTracks[r.currentSoundtrack]->play();
    return PLAY_GAME;
}



/**
 * Shows the goal animation when the player is in the start point
 * @param c is the configuration of the game
 */
State Game::showsGoalAnimation(Configuration &c, SoundPlayer& r) {
    // Stop music level
    r.soundTracks[r.currentSoundtrack]->stop();

    // Position of the player in the race
    string place;
    Text positionText;

    float elapsed1, elapsed2;
    Clock blinkClcok;
    Time blink_delay = seconds(0.5f);

    blinkClcok.restart().asSeconds();
    elapsed1 = blinkClcok.restart().asSeconds();
    bool blink = true;

    if (typeOfGame == 0 || typeOfGame == 2){

        // Get the position of the player in the race
        switch(posArrival){
            case 1:
                place = "FIRST PLACE!";
                break;
            case 2:
                place = "SECOND PLACE!";
                break;
            case 3:
                place = "THIRD PLACE!";
                break;
            case 4:
                place = "FOURTH PLACE";
                break;
            case 5:
                place = "FIFTH PLACE";
                break;
            case 6:
                place = "SIXTH PLACE";
                break;
            case 7:
                place = "SEVENTH PLACE";
                break;
            case 8:
                place = "EIGHT PLACE";
        }

        // Store the position
        positionText.setString(place);
        positionText.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
        positionText.setFont(c.fontTimeToPlay);
        positionText.setStyle(Text::Bold);
        positionText.setFillColor(Color::White);
        positionText.setOutlineColor(Color::Black);
        positionText.setOutlineThickness(5.0f * c.screenScale);
        positionText.setPosition((c.w.getSize().x / 2.f) - (positionText.getLocalBounds().width / 2.f),
                                 c.w.getSize().y / 2.f - 15.f * c.screenScale);

        // GoalSound
        switch(posArrival){
            case 1:
                r.soundEffects[43]->stop();
                r.soundEffects[43]->play();
                break;
            case 2:
            case 3:
                r.soundEffects[44]->stop();
                r.soundEffects[44]->play();
                break;
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                r.soundEffects[45]->stop();
                r.soundEffects[45]->play();
        }
    }

    // Hide enemies
    for (TrafficCar &v : cars)
        v.setPosition(v.getPosX(), -RECTANGLE);

    int increment = 0;
    float currentTime = gameClockTime.getElapsedTime().asMilliseconds();

    int position;

    switch(typeOfVehicle){
        case 0:
            player.setPosition(player.getPosX(), 5.f);
            position = int(player.getPosY());
            break;
        case 1:
            player2.setPosition(player2.getPosX(), 5.f);
            position = int(player2.getPosY());
            break;
        case 2:
            player3.setPosition(player3.getPosX(), 5.f);
            position = int(player3.getPosY());
            break;
        case 3:
            player4.setPosition(player4.getPosX(), 5.f);
            position = int(player4.getPosY());
            break;
        case 4:
            player5.setPosition(player5.getPosX(), 5.f);
            position = int(player5.getPosY());
    }

    // claps
    if (posArrival <= 3){
        r.soundEffects[29]->stop();
        r.soundEffects[29]->play();
    }

    float positionX, positionY;

    while (position < goalEnd) {

        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return EXIT;
            }
        }

        switch(typeOfVehicle){
            case 0:
                positionX = player.getPosX();
                positionY = player.getPosY();
                break;
            case 1:
                positionX = player2.getPosX();
                positionY = player2.getPosY();
                break;
            case 2:
                positionX = player3.getPosX();
                positionY = player3.getPosY();
                break;
            case 3:
                positionX = player4.getPosX();
                positionY = player4.getPosY();
                break;
            case 4:
                positionX = player5.getPosX();
                positionY = player5.getPosY();
        }

        // Update camera
        currentMap->updateCamera(positionX, positionY - RECTANGLE);

        // Draw map
        c.w.clear();
        currentMap->drawLandScape(c, cars);

        switch(typeOfVehicle){
            case 0:
                player.setPosition(player.getPosX(), player.getPosY() + 1);
                player.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                        currentMap->getElevation(player.getPosY()), false);
                break;
            case 1:
                player2.setPosition(player2.getPosX(), player2.getPosY() + 1);
                player2.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                        currentMap->getElevation(player2.getPosY()), false);
                break;
            case 2:
                player3.setPosition(player3.getPosX(), player3.getPosY() + 1);
                player3.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                        currentMap->getElevation(player3.getPosY()), false);
                break;
            case 3:
                player4.setPosition(player4.getPosX(), player4.getPosY() + 1);
                player4.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                        currentMap->getElevation(player4.getPosY()), false);
                break;
            case 4:
                player5.setPosition(player5.getPosX(), player5.getPosY() + 1);
                player5.draw(c, r, Vehicle::Action::ACCELERATE, Vehicle::Direction::RIGHT,
                        currentMap->getElevation(player5.getPosY()), false);
        }

        if (typeOfGame == 0 || typeOfGame == 2){

            elapsed2 = blinkClcok.getElapsedTime().asSeconds();
            // Change the color of the main text
            if (elapsed2 - elapsed1 >= blink_delay.asSeconds()) {
                blink = !blink;
                blinkClcok.restart();
            }
            if (blink) {
                positionText.setFillColor(c.colorTexts[0]);
                positionText.setOutlineColor(c.colorBorders[0]);
            }
            else {
                positionText.setFillColor(Color::Transparent);
                positionText.setOutlineColor(Color::Transparent);
            }


            c.w.draw(positionText);
        }

        // Flager animation
        if (gameClockTime.getElapsedTime().asMilliseconds() - currentTime >= 200.0f) {
            if (increment >= 5) {
                increment = 0;
                currentMap->addMapElelementIndex(goalFlagger, false, -5);
            }
            else {
                currentMap->addMapElelementIndex(goalFlagger, false);
                increment++;
            }
            currentTime = gameClockTime.getElapsedTime().asMilliseconds();
        }

        switch(typeOfVehicle){
            case 0:
                position = int(player.getPosY());
                break;
            case 1:
                position = int(player2.getPosY());
                break;
            case 2:
                position = int(player3.getPosY());
                break;
            case 3:
                position = int(player4.getPosY());
                break;
            case 4:
                position = int(player5.getPosY());
        }

        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();
    }

    // Reproduce the music soundtrack
    r.soundTracks[15]->play();

    for (int i = 0; i <= 255; i += 5){

        // Update camera
        currentMap->updateCamera(positionX, positionY - RECTANGLE);

        RectangleShape shape;
        shape.setPosition(0, 0);
        shape.setSize(sf::Vector2f(c.w.getSize().x, c.w.getSize().y));
        shape.setFillColor(Color(0, 0, 0, i));
        c.w.draw(shape);

        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

        sleep(milliseconds(20));
    }

    if (typeOfGame == 0 || typeOfGame == 2){
        return CLASIFICATION;
    }
    else {
        return RANKING;
    }
}



/**
 * Updates the logic of the landscapes and vehicles and draws the current landscape fragment
 * with the vehicles on the screen.
 * @param c is the configuration of the game
 */
void Game::updateGameStatus(Configuration &c, SoundPlayer& r, Vehicle::Action &action, Vehicle::Direction &direction) {
    // Update camera
    switch(typeOfVehicle){
        case 0:
            currentMap->updateCamera(player.getPosX(), player.getPosY() - RECTANGLE);
            break;
        case 1:
            currentMap->updateCamera(player2.getPosX(), player2.getPosY() - RECTANGLE);
            break;
        case 2:
            currentMap->updateCamera(player3.getPosX(), player3.getPosY() - RECTANGLE);
            break;
        case 3:
            currentMap->updateCamera(player4.getPosX(), player4.getPosY() - RECTANGLE);
            break;
        case 4:
            currentMap->updateCamera(player5.getPosX(), player5.getPosY() - RECTANGLE);
    }

    switch (typeOfGame){
        case 0:
        case 2:
            // World tour and pole position modes
            if (currentMap->isOutSideLandScape()) {
                // Update player and vehicle positions

                switch(typeOfVehicle){
                    case 0:
                        player.setPosition(player.getPosX() + currentMap->getOffsetX(), player.getPosY() - currentMap->getMaxY());
                        break;
                    case 1:
                        player2.setPosition(player2.getPosX() + currentMap->getOffsetX(), player2.getPosY() - currentMap->getMaxY());
                        break;
                    case 2:
                        player3.setPosition(player3.getPosX() + currentMap->getOffsetX(), player3.getPosY() - currentMap->getMaxY());
                        break;
                    case 3:
                        player4.setPosition(player4.getPosX() + currentMap->getOffsetX(), player4.getPosY() - currentMap->getMaxY());
                        break;
                    case 4:
                        player5.setPosition(player5.getPosX() + currentMap->getOffsetX(), player5.getPosY() - currentMap->getMaxY());
                }

                for (TrafficCar &v : cars)
                    v.setPosition(v.getPosX(), v.getPosY() - currentMap->getMaxY());

                // Update to the map
                if (level < 0){
                    level++;
                    currentMap = &tourLandScapes[indexLandScape];
                    checkPointPositions = currentMap->getCheckPointPositions();
                }
                else {
                    finalGame = true;
                }
            }
            else {
                // The player is still inside the landscape
                float pos, halfspeed;

                switch(typeOfVehicle){
                    case 0:
                        pos = player.getPosY();
                        halfspeed = player.getHalfMaxSpeed();
                        break;
                    case 1:
                        pos = player2.getPosY();
                        halfspeed = player2.getHalfMaxSpeed();
                        break;
                    case 2:
                        pos = player3.getPosY();
                        halfspeed = player3.getHalfMaxSpeed();
                        break;
                    case 3:
                        pos = player4.getPosY();
                        halfspeed = player4.getHalfMaxSpeed();
                        break;
                    case 4:
                        pos = player5.getPosY();
                        halfspeed = player5.getHalfMaxSpeed();
                }

                if (pos >= checkPointPositions[indexCheckPoint - 1]){
                    // Increment the next checkpoint to pass
                    if (indexCheckPoint % 4 != 0){
                        indexCheckPoint++;
                        // Activate the checkPoint animation
                        checkPoint = true;
                        // Initialize the clock again
                        updatedTimeCheck = true;

                        // Get the position of the vehicle in the landscape
                        int posY;

                        // Add the time to complete the landscape
                        if (indexCheckPoint != 4){
                            time += ((checkPointPositions[indexCheckPoint - 1] - pos) / (halfspeed * 65.f)) ;
                        }
                        else {
                            time += ((currentMap->getMaxY() - pos) / (halfspeed * 60.f));
                        }
                        // Update the checkpoint time
                        timeCheck = time;
                    }
                }
                if (!checkPoint){
                    // Update the time
                    lapCheckPoint = (minutes < 10) ? "0" + to_string(int(minutes)) + ":" : to_string(int(minutes)) + ":";
                    lapCheckPoint += (secs < 10) ? "0" + to_string(int(secs)) + ":" : to_string(int(secs)) + ":";
                    int cent_sec = cents_second * 100.f;
                    lapCheckPoint += (cent_sec < 10) ? "0" + to_string(cent_sec) : to_string(cent_sec);
                }
                else if (updatedTimeCheck){
                    // Updated the counters of time to zero
                    minutes = 0;
                    secs = 0;
                    cents_second = 0;
                    // Initialize the clock again to zero one time
                    updatedTimeCheck = false;

                    // Reproduce checkpoint sound effect
                    r.soundEffects[24]->stop();
                    r.soundEffects[24]->play();
                }

            }
        case 1:
        case 3:
        case 4:
        case 5:
            // Out Run and Driving Fury and Demarrage modes
            if (currentMap->isOutSideLandScape()) {
                if (currentMap->getNextLeft() != nullptr) {

                    // Update player and vehicle positions
                    switch(typeOfVehicle){
                        case 0:
                            player.setPosition(player.getPosX() + currentMap->getOffsetX(), player.getPosY() - currentMap->getMaxY());
                            break;
                        case 1:
                            player2.setPosition(player2.getPosX() + currentMap->getOffsetX(), player2.getPosY() - currentMap->getMaxY());
                            break;
                        case 2:
                            player3.setPosition(player3.getPosX() + currentMap->getOffsetX(), player3.getPosY() - currentMap->getMaxY());
                            break;
                        case 3:
                            player4.setPosition(player4.getPosX() + currentMap->getOffsetX(), player4.getPosY() - currentMap->getMaxY());
                            break;
                        case 4:
                            player5.setPosition(player5.getPosX() + currentMap->getOffsetX(), player5.getPosY() - currentMap->getMaxY());
                    }

                    for (TrafficCar &v : cars)
                        v.setPosition(v.getPosX(), v.getPosY() - currentMap->getMaxY());

                    const bool isInitMap = currentMap->isStartingLandScape();
                    currentMap = currentMap->getNextLeft();
                    if (!isInitMap && !currentMap->isFinalLandScape()) {
                        level++;
                        // Update fork maps
                        if (currentMap == &maps[mapId.first + 1][mapId.second + 1])
                            mapId.second++;
                        mapId.first++;

                        if (mapId.first < 4)
                            currentMap->addFork(&maps[mapId.first + 1][mapId.second], &maps[mapId.first + 1][mapId.second + 1]);
                        else {
                            goalMap.setColorsLandScape(*currentMap);
                            currentMap->addNewLandScape(&goalMap);
                        }
                        // Update time when map changes
                        time += int(float(currentMap->getTimeToPlay()) * timeMul);

                        // Update the indicators
                        if (!checkPoint) {
                            lapCheckPoint = (minutes < 10) ? "0" + to_string(int(minutes)) + ":" : to_string(int(minutes)) + ":";
                            lapCheckPoint += (secs < 10) ? "0" + to_string(int(secs)) + ":" : to_string(int(secs)) + ":";
                            int cent_sec = cents_second * 100.f;
                            lapCheckPoint += (cent_sec < 10) ? "0" + to_string(cent_sec) : to_string(cent_sec);


                            // Initialize to zero the time
                            cents_second = 0;
                            secs = 0;
                            minutes = 0;
                        }
                        checkPoint = true;
                        timeCheck = time;
                        // CheckPointEffect
                        r.soundEffects[23]->stop();
                        r.soundEffects[23]->play();
                    }

                    switch(typeOfVehicle){
                        case 0:
                            currentMap->updateCamera(player.getPosX(), player.getPosY() - RECTANGLE);
                            break;
                        case 1:
                            currentMap->updateCamera(player2.getPosX(), player2.getPosY() - RECTANGLE);
                            break;
                        case 2:
                            currentMap->updateCamera(player3.getPosX(), player3.getPosY() - RECTANGLE);
                            break;
                        case 3:
                            currentMap->updateCamera(player4.getPosX(), player4.getPosY() - RECTANGLE);
                            break;
                        case 4:
                            currentMap->updateCamera(player5.getPosX(), player5.getPosY() - RECTANGLE);
                    }

                    lastY = currentMap->getCameraPosY();
                }
                else {
                    finalGame = true;
                }
            }
            if (currentMap->isFinalLandScape()) {
                State status = showsGoalAnimation(c, r);
                if (status == EXIT) {
                    exit(1);
                }
                arrival = true;
            }
            break;
    }
    if (!finalGame) {
        // Update and prepare cars to draw
        if (lastY <= currentMap->getCameraPosY() + float(c.renderLen)){
            lastY = currentMap->getCameraPosY() + float(c.renderLen);
        }
        for (TrafficCar &v : cars) {
            if (currentMap->inFork(v.getPosY())) {
                v.setPosition(v.getPosX(), -RECTANGLE * DEL_DISTANCE * 3.0f);
            }
            else if (v.getPosY() + DEL_DISTANCE < currentMap->getCameraPosY()) {
                v.update(lastY, lastY + float(c.renderLen) / DENSITY_SPACE, c.maxAggressiveness);
                lastY = v.getPosY() + DISTANCE_TRESHOLD * RECTANGLE;
            }

            float posY = v.getPosY();
            v.draw(currentMap->getElevation(posY), currentMap->getCameraPosX());
        }

        // Draw map with cars
        c.w.clear();
        currentMap->drawLandScape(c, cars);

        // Player update and draw
        action = Vehicle::CRASH;
        direction = Vehicle::RIGHT;

        switch(typeOfVehicle){
            case 0:
                if (!player.isCrashing()) { // If not has crashed
                    action = player.accelerationControl(c, currentMap->isOutSideRoad(player.getPosX(), player.getPosY()));
                    direction = player.rotationControl(c, currentMap->getCurveCoefficient(player.getPosY()));
                }
                else {
                    player.hitControl(vehicleCrash);
                }

                player.draw(c, r, action, direction, currentMap->getElevation(player.getPosY()));

                if (!player.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player.getPreviousY(), player.getPosY(), player.getPosX(),
                                                        player.getMinScreenX(), player.getMaxScreenX(), crashPos);
                    if (!crash)
                        for (int i = 0; !vehicleCrash && i < cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player.getPreviousY(), player.getPosY(),
                                                              player.getMinScreenX(), player.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        int mode = rand_generator_int(0, 1);
                        player.setPosition(player.getPosX(), crashPos);
                        player.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player.draw(c, r, action, direction, currentMap->getElevation(player.getPosY()));
                    }
                }

                for (TrafficCar &v : cars)
                    v.autoControl(c, player.getPosX(), player.getPosY());
                break;
            case 1:
                if (!player2.isCrashing()) { // If not has crashed
                    action = player2.accelerationControl(c, currentMap->isOutSideRoad(player2.getPosX(), player2.getPosY()));
                    direction = player2.rotationControl(c, currentMap->getCurveCoefficient(player2.getPosY()));
                }
                else {
                    player2.hitControl(vehicleCrash);
                }

                player2.draw(c, r, action, direction, currentMap->getElevation(player2.getPosY()));

                if (!player2.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player2.getPreviousY(), player2.getPosY(), player2.getPosX(),
                                                        player2.getMinScreenX(), player2.getMaxScreenX(), crashPos);
                    if (!crash)
                        for (int i = 0; !vehicleCrash && i < cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player2.getPreviousY(), player2.getPosY(),
                                                              player2.getMinScreenX(), player2.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        player2.setModeCollision();
                        player2.setPosition(player2.getPosX(), crashPos);
                        player2.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player2.draw(c, r, action, direction, currentMap->getElevation(player2.getPosY()));
                    }
                }

                for (TrafficCar &v : cars)
                    v.autoControl(c, player2.getPosX(), player2.getPosY());
                break;
            case 2:
                if (!player3.isCrashing()) { // If not has crashed
                    action = player3.accelerationControl(c, currentMap->isOutSideRoad(player3.getPosX(), player3.getPosY()));
                    direction = player3.rotationControl(c, currentMap->getCurveCoefficient(player3.getPosY()));
                }
                else {
                    player3.hitControl(vehicleCrash);
                }

                player3.draw(c, r, action, direction, currentMap->getElevation(player3.getPosY()));

                if (!player3.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player3.getPreviousY(), player3.getPosY(), player3.getPosX(),
                                                        player3.getMinScreenX(), player3.getMaxScreenX(), crashPos);
                    if (!crash)
                        for (int i = 0; !vehicleCrash && i < cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player3.getPreviousY(), player3.getPosY(),
                                                              player3.getMinScreenX(), player3.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        player3.setModeCollision();
                        player3.setPosition(player3.getPosX(), crashPos);
                        player3.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player3.draw(c, r, action, direction, currentMap->getElevation(player3.getPosY()));
                    }
                }

                for (TrafficCar &v : cars)
                    v.autoControl(c, player3.getPosX(), player3.getPosY());
                break;
            case 3:
                if (!player4.isCrashing()) { // If not has crashed
                    action = player4.accelerationControl(c, currentMap->isOutSideRoad(player4.getPosX(), player4.getPosY()));
                    direction = player4.rotationControl(c, currentMap->getCurveCoefficient(player4.getPosY()));
                }
                else {
                    player4.hitControl(vehicleCrash);
                }

                player4.draw(c, r, action, direction, currentMap->getElevation(player4.getPosY()));

                if (!player4.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player4.getPreviousY(), player4.getPosY(), player4.getPosX(),
                                                        player4.getMinScreenX(), player4.getMaxScreenX(), crashPos);
                    if (!crash)
                        for (int i = 0; !vehicleCrash && i < cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player4.getPreviousY(), player4.getPosY(),
                                                              player4.getMinScreenX(), player4.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        player4.setModeCollision();
                        player4.setPosition(player4.getPosX(), crashPos);
                        player4.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player4.draw(c, r, action, direction, currentMap->getElevation(player4.getPosY()));
                    }
                }

                for (TrafficCar &v : cars)
                    v.autoControl(c, player4.getPosX(), player4.getPosY());
                break;
            case 4:
                if (!player5.isCrashing()) { // If not has crashed
                    action = player5.accelerationControl(c, currentMap->isOutSideRoad(player5.getPosX(), player5.getPosY()));
                    direction = player5.rotationControl(c, currentMap->getCurveCoefficient(player5.getPosY()));
                }
                else {
                    player5.hitControl(vehicleCrash);
                }

                player5.draw(c, r, action, direction, currentMap->getElevation(player5.getPosY()));

                if (!player5.isCrashing()) {
                    vehicleCrash = false;
                    float crashPos;
                    bool crash = currentMap->hasCrashed(c, player5.getPreviousY(), player5.getPosY(), player5.getPosX(),
                                                        player5.getMinScreenX(), player5.getMaxScreenX(), crashPos);
                    if (!crash)
                        for (int i = 0; !vehicleCrash && i < cars.size(); i++)
                            vehicleCrash = cars[i].hasCrashed(player5.getPreviousY(), player5.getPosY(),
                                                              player5.getMinScreenX(), player5.getMaxScreenX(),
                                                              crashPos);

                    if (crash || vehicleCrash) {
                        // Determine the type of collision
                        player5.setModeCollision();
                        player5.setPosition(player5.getPosX(), crashPos);
                        player5.hitControl(vehicleCrash);
                        action = Vehicle::CRASH;
                        direction = Vehicle::RIGHT;

                        player5.draw(c, r, action, direction, currentMap->getElevation(player5.getPosY()));
                    }
                }

                for (TrafficCar &v : cars)
                    v.autoControl(c, player5.getPosX(), player5.getPosY());
        }

        // Check if enemies are displayed on the screen
        for (TrafficCar &v : cars) {
            float distX, distY;

            bool visible;

            switch(typeOfVehicle){
                case 0:
                    visible = v.isVisible(c, currentMap->getCameraPosY(), player.getPosX(), player.getPosY(), distX, distY);
                    break;
                case 1:
                    visible = v.isVisible(c, currentMap->getCameraPosY(), player2.getPosX(), player2.getPosY(), distX, distY);
                    break;
                case 2:
                    visible = v.isVisible(c, currentMap->getCameraPosY(), player3.getPosX(), player3.getPosY(), distX, distY);
                    break;
                case 3:
                    visible = v.isVisible(c, currentMap->getCameraPosY(), player4.getPosX(), player4.getPosY(), distX, distY);
                    break;
                case 4:
                    visible = v.isVisible(c, currentMap->getCameraPosY(), player5.getPosX(), player5.getPosY(), distX, distY);
            }

            if (visible) {
                if (distY <= 20.f && distX <= 0.3f) {
                    // Thread with sound of the woman
                    elapsed6 = womanShot.getElapsedTime().asSeconds();
                    if (elapsed6 - elapsed5 >= woman_delay.asSeconds()) {
                        // WomanSound
                        r.soundEffects[13]->stop();
                        r.soundEffects[14]->stop();
                        r.soundEffects[15]->stop();
                        r.soundEffects[rand_generator_int(13, 15)]->play();
                        womanShot.restart();
                    }
                }
                if (distY <= 30.f && distX <= 1.2f) {
                    // Thread with sound of the woman
                    elapsed8 = trafficCarSound.getElapsedTime().asSeconds();
                    if (elapsed8 - elapsed7 >= traffic_delay.asSeconds()) {
                        // makeCarTrafficSound
                        r.soundEffects[20]->stop();
                        r.soundEffects[21]->stop();
                        r.soundEffects[22]->stop();
                        r.soundEffects[rand_generator_int(20, 22)]->play();
                        trafficCarSound.restart();
                    }
                }
            }
        }
        if (checkPoint) {
            elapsed10 = blinkTime.getElapsedTime().asSeconds();
            if (elapsed10 - elapsed9 >= blink_delay.asSeconds()) {
                blink = !blink;
                blinkTime.restart();
            }
            if (blink) {
                showCheckpointIndications(c, true);
                // BeepSound
                r.soundEffects[48]->stop();
                r.soundEffects[48]->play();
            }
            else {
                showCheckpointIndications(c, false);
            }
            if (timeCheck - time > 5) {
                checkPoint = false;
            }
        }
    }
}



/**
 * Load the configuration of the pause menu stored in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void Game::loadPauseMenuConfiguration(const string path, Configuration& c){
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
        // Check it is the node that contains the information of the main panel
        if ((string)property->name() == "MenuPanel"){
            // Iterate to get the information of the player menu
            for (xml_node<> *panelProp = property->first_node(); panelProp; panelProp = panelProp->next_sibling()){
                // Get the name of the node
                content = (string)panelProp->name();
                // Check it is the node that contains the information of the color border of the panel
                if ((string)panelProp->name() == "ColorPanel" || (string)panelProp->name() == "ColorBorder"){
                    // Get the border color of the panel
                    int colorRed, colorGreen, colorBlue;
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
                    //Store the color correctly
                    if (content == "ColorPanel"){
                        c.colorInsidePanelPauseMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    else if (content == "ColorBorder"){
                        c.colorBorderPanelPauseMenu = Color(colorRed, colorGreen, colorBlue);
                    }
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
                    c.contentTitlePauseMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontPauseMenu.loadFromFile(fontPath);
                }
                // Get color text of the title
                else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                    // Get the kind of color to process
                    colorKind = (string)titleProp->name();
                    // Get the border color of the panel
                    int colorRed, colorGreen, colorBlue;
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
                        c.colorTitleTextPauseMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderPauseMenu = Color(colorRed, colorGreen, colorBlue);
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
                    c.fontMenuPauseButtons.loadFromFile(fontPath);
                }
                // Get the color font of the buttons
                else if ((string)buttonProp->name() == "ColorFont"){
                    // Read the font from the file
                    int colorRed, colorGreen, colorBlue;
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
                    c.colorFontMenuPauseButtons = Color(colorRed, colorGreen, colorBlue);
                }
                // Get the information of the buttons
                else if ((string)buttonProp->name() == "Buttons"){
                    // Local variables to store the attributes of the buttons
                    string contentButton;
                    int buttonState;
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
                                    int colorRed, colorGreen, colorBlue;
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
                                posX = c.w.getSize().x / 2.f - 95.0f * c.screenScale;
                                posY = c.w.getSize().y / 2.f - (70.0f - idButton * 70.0f) * c.screenScale;
                                widthButton = 200.0f * c.screenScale;
                                heightButton = 30.0f * c.screenScale;

                                // Creation of the button
                                Button b = Button(posX, posY, widthButton, heightButton, c.fontMenuPauseButtons,
                                                  contentButton, colorButtons[0], colorButtons[1], c.colorFontMenuPauseButtons,
                                                  buttonState, c.screenScale);

                                // Process the description text of the button
                                c.pauseMenuButtons.push_back(b);
                                idButton++;
                            }
                        }
                    }
                }
            }
        }
    }
    // The pause menu has been read correctly
    c.pauseMenuRead = true;
}


/**
 * Display the pause menu of the game
 */
State Game::pause(Configuration &c, SoundPlayer& r,const Vehicle::Action &a, const Vehicle::Direction &d) {
    c.w.clear();

    // Draw the map
    currentMap->drawLandScape(c, cars);

    switch(typeOfVehicle){
        case 0:
            player.draw(c, r, a, d, currentMap->getElevation(player.getPosY()), false);
            break;
        case 1:
            player2.draw(c, r, a, d, currentMap->getElevation(player2.getPosY()), false);
            break;
        case 2:
            player3.draw(c, r, a, d, currentMap->getElevation(player3.getPosY()), false);
            break;
        case 3:
            player4.draw(c, r, a, d, currentMap->getElevation(player4.getPosY()), false);
            break;
        case 4:
            player5.draw(c, r, a, d, currentMap->getElevation(player5.getPosY()), false);
    }
    // Draw the vehicle of the player

    showHudInterface(c);

    c.w.display();
    const Texture bgTexture(c.w.getTexture());
    Sprite bgSprite(bgTexture);
    bgSprite.setScale(float(c.window.getSize().x) / float(c.w.getSize().x),
                      float(c.window.getSize().y) / float(c.w.getSize().y));

    c.w.clear();
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));
    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Game in pause
    onPause = true;

    // Control if the pause menu configuration file has been read or not
    if (!c.pauseMenuRead){
        // Read the pause menu xml configuration file
        string pathFile = "Data/Menus/PauseMenu/Configuration/PauseMenu.xml";
        loadPauseMenuConfiguration(pathFile, c);
    }
    else {
        // Restart all the buttons to its initial state
        Button b = Button(c.w.getSize().x / 2.f - 95.0f * c.screenScale, c.w.getSize().y / 2.f - 70.0f * c.screenScale,
                          200.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenuPauseButtons, c.pauseMenuButtons[0].getTextButton(),
                          c.pauseMenuButtons[0].getIdleColorButton(), c.pauseMenuButtons[0].getHoverColorButton(),
                          c.pauseMenuButtons[0].getFontColorButton(), 1, c.screenScale);

        c.pauseMenuButtons[0] = b;

        for (int i = 1; i < int(c.pauseMenuButtons.size()); i++){
            // Change the state of the first color
            Button b = Button(c.w.getSize().x / 2.f - 95.0f * c.screenScale, c.w.getSize().y / 2.f - (70.0f - i * 70.f) * c.screenScale,
                              200.0f * c.screenScale, 30.0f * c.screenScale, c.fontMenuPauseButtons, c.pauseMenuButtons[i].getTextButton(),
                              c.pauseMenuButtons[i].getIdleColorButton(), c.pauseMenuButtons[i].getHoverColorButton(),
                              c.pauseMenuButtons[i].getFontColorButton(), 0, c.screenScale);

            c.pauseMenuButtons[i] = b;
        }
    }

    // Stop the music of the level
    r.soundTracks[r.currentSoundtrack]->pause();

    RectangleShape shape;
    shape.setPosition(0, 0);
    shape.setSize(Vector2f(c.w.getSize().x, c.w.getSize().y));
    shape.setFillColor(Color(0, 0, 0, 200));

    RectangleShape pauseShape;
    pauseShape.setPosition(c.w.getSize().x / 2.f - 120.0f * c.screenScale, c.w.getSize().y / 2.f - 180.0f * c.screenScale);
    pauseShape.setSize(sf::Vector2f(250.0f * c.screenScale, 400.0f * c.screenScale));
    pauseShape.setFillColor(c.colorInsidePanelPauseMenu);
    pauseShape.setOutlineColor(c.colorBorderPanelPauseMenu);
    pauseShape.setOutlineThickness(5.0f * c.screenScale);

    Text textMenu;
    textMenu.setPosition(c.w.getSize().x / 2.f - 75.0f * c.screenScale, c.w.getSize().y / 2.f - 150.0f * c.screenScale);
    textMenu.setFont(c.fontPauseMenu);
    textMenu.setFillColor(c.colorTitleTextPauseMenu);
    textMenu.setOutlineColor(c.colorTitleBorderPauseMenu);
    textMenu.setOutlineThickness(2.0f * c.screenScale);
    textMenu.setCharacterSize(static_cast<unsigned int>(int(35.0f * c.screenScale)));
    textMenu.setString(c.contentTitlePauseMenu);

    // Control if the start key is pressed or not
    bool startPressed = false;

    // Control the option selected by the user
    int optionSelected = 0;

    // While the start button has not been pressed
    while (!startPressed) {
        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return EXIT;
            }
        }

        // Check if the up or down cursor keys have been pressed or not
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            // Up cursor pressed and change the soundtrack selected in the list
            if (optionSelected != int(c.pauseMenuButtons.size() - 1)) {
                // Change the color appearance of both buttons
                r.soundEffects[0]->stop();
                r.soundEffects[0]->play();
                optionSelected++;
                c.pauseMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                c.pauseMenuButtons[optionSelected - 1].setButtonState(BUTTON_IDLE);
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::Up)) {
            // Down cursor pressed and change the soundtrack selected in the list
            if (optionSelected != 0) {
                r.soundEffects[0]->stop();
                r.soundEffects[0]->play();
                optionSelected--;
                // Change the color appearance of both buttons
                c.pauseMenuButtons[optionSelected].setButtonState(BUTTON_HOVER);
                c.pauseMenuButtons[optionSelected + 1].setButtonState(BUTTON_IDLE);
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            if (comeFromOptions) {
                comeFromOptions = false;
            } else {
                startPressed = true;
            }
        }

        c.w.draw(bgSprite);

        c.w.draw(shape);

        c.w.draw(pauseShape);
        c.w.draw(textMenu);

        for (Button b : c.pauseMenuButtons) {
            b.render(&c.w);
        }

        Sprite bufferSprite(c.w.getTexture());
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();
        sleep(milliseconds(100));
    }

    r.soundEffects[2]->stop();
    r.soundEffects[2]->play();

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

    // Check the option selected by the user
    switch (optionSelected) {
        case 0:
            // Resume button selected and reanudate the music
            onPause = false;
            return PLAY_GAME;
        case 1:
            // Options button selected
            return OPTIONS;
        case 2:
            // Quit button selected
            onPause = false;
            return START;
        default:
            return EXIT;
    }
}



/**
 * Load the configuration of the vehicle selection menu in its xml file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
void Game::loadVehicleSelectionMenuConfiguration(const string path, Configuration& c){

    // Open the xml file of the configuration
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Local variables to store the information
    string backgroundTexture, content, fontPath, colorKind;

    // Iterate to get the information of the vehicle selection menu
    for (xml_node<> *property = menuNode->first_node(); property; property = property->next_sibling()){
        // Check if its the node of the background information
        if ((string)property->name() == "Background"){
            // Get the background image of the menu
            backgroundTexture = (string)property->value();
            c.backgroundSelectionMenu.loadFromFile(backgroundTexture);
        }
        // Check if its the node of the background color
        else if ((string)property->name() == "BackgroundColor"){
            // Get the background image of the menu
            int colorRed, colorGreen, colorBlue;
            // Iterate to get the information of the background menu color
            for (xml_node<> *colorChannel = property->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
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
            c.colorBackground = Color(colorRed, colorGreen, colorBlue);
        }
        // Check if its the node of the title
        else if ((string)property->name() == "Title"){
            // Iterate to get the information of the title
            for (xml_node<> *titleProp = property->first_node(); titleProp; titleProp = titleProp->next_sibling()){
                // Get the red color channel
                if ((string)titleProp->name() == "Content"){
                    // Get the content of the title
                    content = (string)titleProp->value();
                    c.contentTitleVehicleSelectionMenu = content;
                }
                // Get the green color channel
                else if ((string)titleProp->name() == "Font"){
                    // Read the font from the file
                    fontPath = (string)titleProp->value();
                    c.fontVehicleSelectionMenu.loadFromFile(fontPath);
                }
                // Get color text of the title
                else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                    // Get the kind of color to process
                    colorKind = (string)titleProp->name();
                    // Get the border color of the panel
                    int colorRed, colorGreen, colorBlue;
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
                        c.colorTitleTextVehicleSelectionMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                    // Check if it is the color of the border
                    else if (colorKind == "ColorBorder"){
                        c.colorTitleBorderVehicleSelectionMenu = Color(colorRed, colorGreen, colorBlue);
                    }
                }
            }
        }
        // Check if its the node of the vehicle panel
        else if ((string)property->name() == "VehiclePanel"){
            // Iterate throughout the information of the vehicle panel
            for (xml_node<> *vehiclePanel = property->first_node(); vehiclePanel; vehiclePanel = vehiclePanel->next_sibling()){
                // Check if its the node of the title
                if ((string)vehiclePanel->name() == "Title"){
                    // Iterate to get the information of the title
                    for (xml_node<> *titleProp = vehiclePanel->first_node(); titleProp; titleProp = titleProp->next_sibling()){
                        // Get the green color channel
                        if ((string)titleProp->name() == "Font"){
                            // Read the font from the file
                            fontPath = (string)titleProp->value();
                            c.fontVehicleSelectionMenuPanelTitle.loadFromFile(fontPath);
                        }
                        // Get color text of the title
                        else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                            // Get the kind of color to process
                            colorKind = (string)titleProp->name();
                            // Get the border color of the panel
                            int colorRed, colorGreen, colorBlue;
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
                                c.colorTitleTextVehicleSelectionMenuName = Color(colorRed, colorGreen, colorBlue);
                            }
                            // Check if it is the color of the border
                            else if (colorKind == "ColorBorder"){
                                c.colorTitleBorderVehicleSelectionMenuName = Color(colorRed, colorGreen, colorBlue);
                            }
                        }
                    }
                }
                // Check if its the node of the border color of the panel
                else if ((string)vehiclePanel->name() == "ColorBorder"){
                    int colorRed, colorGreen, colorBlue;
                    // Iterate to get the information of the background menu color
                    for (xml_node<> *colorChannel = vehiclePanel->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
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
                    c.colorBorderVehiclePanel = Color(colorRed, colorGreen, colorBlue);
                }
            }
        }
         // Check if its the node of the description panel
        else if ((string)property->name() == "DescriptionPanel"){
            // Iterate throughout the information of the vehicle panel
            for (xml_node<> *vehiclePanel = property->first_node(); vehiclePanel; vehiclePanel = vehiclePanel->next_sibling()){
                // Check if its the node of the title
                if ((string)vehiclePanel->name() == "Title"){
                    // Iterate to get the information of the title
                    for (xml_node<> *titleProp = vehiclePanel->first_node(); titleProp; titleProp = titleProp->next_sibling()){
                        // Get the green color channel
                        if ((string)titleProp->name() == "Font"){
                            // Read the font from the file
                            fontPath = (string)titleProp->value();
                            c.fontVehicleSelectionMenuPanelTitleProp.loadFromFile(fontPath);
                        }
                        // Get color text of the title
                        else if ((string)titleProp->name() == "ColorText" || (string)titleProp->name() == "ColorBorder"){
                            // Get the kind of color to process
                            colorKind = (string)titleProp->name();
                            // Get the border color of the panel
                            int colorRed, colorGreen, colorBlue;
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
                                c.colorTitleTextVehicleSelectionMenuProp = Color(colorRed, colorGreen, colorBlue);
                            }
                            // Check if it is the color of the border
                            else if (colorKind == "ColorBorder"){
                                c.colorTitleBorderVehicleSelectionMenuNameProp = Color(colorRed, colorGreen, colorBlue);
                            }
                        }
                    }
                }
                 // Check if its the node of the vehicle properties
                if ((string)vehiclePanel->name() == "Properties"){
                    // Iterate to get the information of the vehicle properties
                    for (xml_node<> *vehicleProp = vehiclePanel->first_node(); vehicleProp; vehicleProp = vehicleProp->next_sibling()){
                        // Check if it is the node of the content information
                        if ((string)vehicleProp->name() == "Content"){
                            // Iterate to get the information of the vehicle properties
                            for (xml_node<> *prop = vehicleProp->first_node(); prop; prop = prop->next_sibling()){
                                // Get the green color channel
                                if ((string)prop->name() == "Font"){
                                    // Read the font from the file
                                    fontPath = (string)prop->value();
                                    c.fontVehicleSelectionMenuPanelProp.loadFromFile(fontPath);
                                }
                                // Get color text of the title
                                else if ((string)prop->name() == "ColorText" || (string)prop->name() == "ColorBorder" ||
                                         (string)prop->name() == "ColorInside")
                                {
                                    // Get the kind of color to process
                                    colorKind = (string)prop->name();
                                    // Get the border color of the panel
                                    int colorRed, colorGreen, colorBlue;
                                    // Iterate to get the information of the player menu
                                    for (xml_node<> *colorChannel = prop->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
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
                                        c.colorTextVehicleSelectionProp = Color(colorRed, colorGreen, colorBlue);
                                    }
                                    // Check if it is the color of the border
                                    else if (colorKind == "ColorBorder"){
                                        c.colorBorderVehicleSelectionProp = Color(colorRed, colorGreen, colorBlue);
                                    }
                                    // Check if it is the inside color of the vehicle properties panel
                                    else if (colorKind == "ColorInside"){
                                        c.colorInsideVehicleSelectionMenuPanelProp = Color(colorRed, colorGreen, colorBlue);
                                    }
                                }
                            }
                        }
                        // Check if it is the node of the border color
                        else if ((string)vehicleProp->name() == "ColorBorder"){
                            int colorRed, colorGreen, colorBlue;
                            // Iterate to get the information of the background menu color
                            for (xml_node<> *colorChannel = vehicleProp->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
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
                            c.colorBorderPropertiesPanel = Color(colorRed, colorGreen, colorBlue);
                        }
                    }
                }
            }
        }
        // Check the color buttons of the menu
        else if ((string)property->name() == "Buttons"){
            int colorRed, colorGreen, colorBlue;
            // Iterate to get the information of the color buttons
            for (xml_node<> *colorChannel = property->first_node(); colorChannel; colorChannel = colorChannel->next_sibling()){
                // Iterate to get the information of the background menu color
                for (xml_node<> *color = colorChannel->first_node(); color; color = color->next_sibling()){
                    // Get the red color channel
                    if ((string)color->name() == "R"){
                        // Get the red channel
                        colorRed = stoi((string)color->value());
                    }
                    // Get the green color channel
                    else if ((string)color->name() == "G"){
                        // Get the red channel
                        colorGreen = stoi((string)color->value());
                    }
                    // Get the blue color channel
                    else if ((string)color->name() == "B"){
                        // Get the red channel
                        colorBlue = stoi((string)color->value());
                    }
                }
                // Store the color border of the panel
                c.vehicleSelectionMenuColorButtons.push_back(Color(colorRed, colorGreen, colorBlue));
            }
        }
    }
    // Tge file has been read correctly
    c.vehicleSelectionMenuRead = true;
}



/**
 * Load the configuration of the vehicle selection menu in its xml
 * configuration file
 * @param path contains the path of the xml configuration file
 * @param c is the configuration of the game
 */
State Game::selectionVehicleMenu(Configuration& c, SoundPlayer& r){

    c.w.clear();
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));
    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    // Check if the vehicle selection menu has been read
    if (!c.vehicleSelectionMenuRead){
        // Read the configuration of the xml file
        string path = "Data/Menus/VehicleSelectionMenu/Configuration/VehicleSelectionMenu.xml";
        loadVehicleSelectionMenuConfiguration(path, c);
    }

    // Loading the background texture
    Texture carTexture;
    carTexture.loadFromFile("Data/Menus/VehicleSelectionMenu/Images/image.png");
    carTexture.setRepeated(true);
    c.backgroundSelectionMenu.setRepeated(true);

    r.soundTracks[16]->play();

    // Control if the player presses the start key or not
    bool startPressed = false;

    // Control if the player presses the backspace key or not
    bool backSpacePressed = false;

    // Control the vehicle selected by the player
    int optionSelected;

    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    // Load the textures of the vehicles to show
    Texture t;
    vector<Texture> vehicleTextures;

    t.loadFromFile("Data/Vehicles/Motorbike/Images/c44.png");
    vehicleTextures.push_back(t);

    t.loadFromFile("Data/Vehicles/Devastator/Images/c57.png");
    vehicleTextures.push_back(t);

    t.loadFromFile("Data/Vehicles/Minivan/Images/c49.png");
    vehicleTextures.push_back(t);

    t.loadFromFile("Data/Vehicles/Truck/Images/c75.png");
    vehicleTextures.push_back(t);

    // Show the vehicle selected
    Sprite vehicleCar;

    vehicleCar.setTexture(vehicleTextures[0], true);
    vehicleCar.setScale(1.6f * c.screenScale, 1.6f * c.screenScale);
    vehicleCar.setPosition((c.w.getSize().x / 2.f) + 160.0f * c.screenScale, c.w.getSize().y / 2.f - 25.f * c.screenScale);

    // While start and backspace have not been pressed
    while (!startPressed && !backSpacePressed) {

        optionSelected = 0;

        IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
        Sprite sprite(c.backgroundSelectionMenu, background);
        sprite.setColor(c.colorBackground);

        Sprite garage;
        garage.setTexture(carTexture, true);

        if (c.w.getSize().x != DEFAULT_WIDTH && c.w.getSize().y != DEFAULT_HEIGHT){
            garage.setScale(float(c.w.getSize().x) / DEFAULT_WIDTH, float(c.w.getSize().y) / DEFAULT_HEIGHT * 1.34f);
        }
        garage.setPosition((c.w.getSize().x / 2.f) + 80.0f * c.screenScale, c.w.getSize().y / 2.f - 163.0f * c.screenScale);

        RectangleShape vehicleShape;
        vehicleShape.setPosition((c.w.getSize().x / 2.f) + 80.0f * c.screenScale, c.w.getSize().y / 2.f - 163.0f * c.screenScale);
        vehicleShape.setSize(sf::Vector2f(318.0f * c.screenScale, 350.0f * c.screenScale));
        vehicleShape.setOutlineColor(c.colorBorderVehiclePanel);
        vehicleShape.setOutlineThickness(5.0f * c.screenScale);

        RectangleShape descriptionShape;
        descriptionShape.setPosition((c.w.getSize().x / 2.f) - 400.0f * c.screenScale, c.w.getSize().y / 2.f - 163.0f * c.screenScale);
        descriptionShape.setSize(sf::Vector2f(360.0f * c.screenScale, 350.0f * c.screenScale));
        descriptionShape.setOutlineColor(c.colorBorderPropertiesPanel);
        descriptionShape.setOutlineThickness(5.0f * c.screenScale);
        descriptionShape.setFillColor(c.colorInsideVehicleSelectionMenuPanelProp);

        // Main Text of the menu
        Text selectionVehicleText;
        selectionVehicleText.setString(c.contentTitleVehicleSelectionMenu);
        selectionVehicleText.setPosition(c.w.getSize().x / 2.f - 200.0f * c.screenScale, c.w.getSize().y / 2.f - 240.0f * c.screenScale);
        selectionVehicleText.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
        selectionVehicleText.setFont(c.fontVehicleSelectionMenu);
        selectionVehicleText.setStyle(Text::Bold | Text::Underlined);
        selectionVehicleText.setFillColor(c.colorTitleTextVehicleSelectionMenu);
        selectionVehicleText.setOutlineColor(c.colorTitleBorderVehicleSelectionMenu);
        selectionVehicleText.setOutlineThickness(5.0f * c.screenScale);

        // Main Text of the menu
        Text vehiclePropertiesText;
        vehiclePropertiesText.setString("PROPERTIES");
        vehiclePropertiesText.setPosition(c.w.getSize().x / 2.f - 320.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);
        vehiclePropertiesText.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
        vehiclePropertiesText.setFont(c.fontVehicleSelectionMenuPanelTitleProp);
        vehiclePropertiesText.setStyle(Text::Bold | Text::Underlined);
        vehiclePropertiesText.setFillColor(c.colorTitleTextVehicleSelectionMenuProp);
        vehiclePropertiesText.setOutlineColor(c.colorTitleBorderVehicleSelectionMenuNameProp);
        vehiclePropertiesText.setOutlineThickness(3.0f * c.screenScale);

        // Vehicle Properties
        Text speedVehicleText;
        speedVehicleText.setString("TOP SPEED: ");
        speedVehicleText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale, c.w.getSize().y / 2.f - 75.0f * c.screenScale);
        speedVehicleText.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        speedVehicleText.setFont(c.fontVehicleSelectionMenuPanelProp);
        speedVehicleText.setStyle(Text::Bold);
        speedVehicleText.setFillColor(c.colorTextVehicleSelectionProp);
        speedVehicleText.setOutlineColor(c.colorBorderVehicleSelectionProp);
        speedVehicleText.setOutlineThickness(2.0f * c.screenScale);

        Text angleTurnText;
        angleTurnText.setString("ANGLE OF TURN: ");
        angleTurnText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale, c.w.getSize().y / 2.f  - 5.f * c.screenScale);
        angleTurnText.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        angleTurnText.setFont(c.fontVehicleSelectionMenuPanelProp);
        angleTurnText.setStyle(Text::Bold);
        angleTurnText.setFillColor(c.colorTextVehicleSelectionProp);
        angleTurnText.setOutlineColor(c.colorBorderVehicleSelectionProp);
        angleTurnText.setOutlineThickness(2.0f * c.screenScale);

        Text motorText;
        motorText.setString("MOTOR: ");
        motorText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale, c.w.getSize().y / 2.f + 65.0f * c.screenScale);
        motorText.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        motorText.setFont(c.fontVehicleSelectionMenuPanelProp);
        motorText.setStyle(Text::Bold);
        motorText.setFillColor(c.colorTextVehicleSelectionProp);
        motorText.setOutlineColor(c.colorBorderVehicleSelectionProp);
        motorText.setOutlineThickness(2.0f * c.screenScale);

        Text accelerationText;
        accelerationText.setString("0 - " + to_string(int(player.getTopSpeed()) / 2) + " KM/H:");
        accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale, c.w.getSize().y / 2.f + 135.0f * c.screenScale);
        accelerationText.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        accelerationText.setFont(c.fontVehicleSelectionMenuPanelProp);
        accelerationText.setStyle(Text::Bold);
        accelerationText.setFillColor(c.colorTextVehicleSelectionProp);
        accelerationText.setOutlineColor(c.colorBorderVehicleSelectionProp);
        accelerationText.setOutlineThickness(2.0f * c.screenScale);

        // Main Text of the menu
        Text vehicleName;
        vehicleName.setString(player.getBrandName());
        vehicleName.setPosition(c.w.getSize().x / 2.f + 130.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);
        vehicleName.setCharacterSize(static_cast<unsigned int>(int(30.0f * c.screenScale)));
        vehicleName.setFont(c.fontVehicleSelectionMenuPanelTitle);
        vehicleName.setStyle(Text::Bold | Text::Underlined);
        vehicleName.setFillColor(c.colorTitleTextVehicleSelectionMenuName);
        vehicleName.setOutlineColor(c.colorTitleBorderVehicleSelectionMenuName);
        vehicleName.setOutlineThickness(3.0f * c.screenScale);

        Text speed;
        speed.setString(to_string(int(player.getTopSpeed())) + "KM/H");
        speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                     c.w.getSize().y / 2.f - 75.0f * c.screenScale);
        speed.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        speed.setFont(c.fontVehicleSelectionMenuPanelProp);
        speed.setStyle(Text::Bold);
        speed.setFillColor(c.colorTextVehicleSelectionProp);
        speed.setOutlineColor(c.colorBorderVehicleSelectionProp);
        speed.setOutlineThickness(2.0f * c.screenScale);

        Text angle;
        string value = to_string(player.getAngle());
        angle.setString(value.substr(0, value.find(".") + 3) + " RAD/S");
        angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                          c.w.getSize().y / 2.f - 5.0f * c.screenScale);
        angle.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        angle.setFont(c.fontVehicleSelectionMenuPanelProp);
        angle.setStyle(Text::Bold);
        angle.setFillColor(c.colorTextVehicleSelectionProp);
        angle.setOutlineColor(c.colorBorderVehicleSelectionProp);
        angle.setOutlineThickness(2.0f * c.screenScale);

        Text motor;
        motor.setString(player.getMotorName());
        motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                          c.w.getSize().y / 2.f + 65.0f * c.screenScale);
        motor.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        motor.setFont(c.fontVehicleSelectionMenuPanelProp);
        motor.setStyle(Text::Bold);
        motor.setFillColor(c.colorTextVehicleSelectionProp);
        motor.setOutlineColor(c.colorBorderVehicleSelectionProp);
        motor.setOutlineThickness(2.0f * c.screenScale);

        Text acceleration;
        value = to_string((player.getTopSpeed() / 2.f) / TIME_HALF_SPEED);
        acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
        acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                 c.w.getSize().y / 2.f + 135.0f * c.screenScale);
        acceleration.setCharacterSize(static_cast<unsigned int>(int(20.0f * c.screenScale)));
        acceleration.setFont(c.fontVehicleSelectionMenuPanelProp);
        acceleration.setStyle(Text::Bold);
        acceleration.setFillColor(c.colorTextVehicleSelectionProp);
        acceleration.setOutlineColor(c.colorBorderVehicleSelectionProp);
        acceleration.setOutlineThickness(2.0f * c.screenScale);

        CircleShape triangle(30 * c.screenScale, 3);
        triangle.setFillColor(c.vehicleSelectionMenuColorButtons[0]);
        triangle.setOutlineColor(c.vehicleSelectionMenuColorButtons[3]);
        triangle.setOutlineThickness(2.0f * c.screenScale);
        triangle.setRotation(30);
        triangle.setPosition(c.w.getSize().x / 2.f - 20.0f * c.screenScale, c.w.getSize().y / 2.f + 185.0f * c.screenScale);

        CircleShape triangle2(30 * c.screenScale, 3);
        triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[1]);
        triangle2.setOutlineColor(c.vehicleSelectionMenuColorButtons[3]);
        triangle2.setOutlineThickness(2.0f * c.screenScale);
        triangle2.setRotation(90);
        triangle2.setPosition(c.w.getSize().x / 2.f + 75.0f * c.screenScale, c.w.getSize().y / 2.f + 196.0f * c.screenScale);

        // Reproduce the sound effect
        r.soundEffects[40]->play();

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
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                // Up cursor pressed and change the soundtrack selected in the list
                if (optionSelected != 3) {
                    // Change the color appearance of both buttons
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected++;

                    switch(optionSelected){
                        case 1:

                            accelerationText.setString("0 - " + to_string(int(player2.getTopSpeed()) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[1], true);
                            vehicleCar.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 105.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 5.f * c.screenScale);

                            vehicleName.setString(player2.getBrandName());
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 130.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(player2.getTopSpeed())) + "KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(player2.getAngle());
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(player2.getMotorName());
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((player2.getTopSpeed() / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                            break;
                        case 2:

                            accelerationText.setString("0 - " + to_string(int(player3.getTopSpeed()) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[2], true);
                            vehicleCar.setScale(2.7f * c.screenScale, 3.2f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 100.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 30.f * c.screenScale);

                            vehicleName.setString(player3.getBrandName());
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 130.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(player3.getTopSpeed())) + "KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(player3.getAngle());
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(player3.getMotorName());
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((player3.getTopSpeed() / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                            break;
                        case 3:

                            accelerationText.setString("0 - " + to_string(int(player4.getTopSpeed()) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[3], true);
                            vehicleCar.setScale(2.7f * c.screenScale, 3.5f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 90.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 55.f * c.screenScale);

                            vehicleName.setString(player4.getBrandName());
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 110.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(player4.getTopSpeed())) + "KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(player4.getAngle());
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(player4.getMotorName());
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((player4.getTopSpeed() / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                    }
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Left)) {
                // Down cursor pressed and change the soundtrack selected in the list
                if (optionSelected != 0) {
                    r.soundEffects[0]->stop();
                    r.soundEffects[0]->play();
                    optionSelected--;

                    switch(optionSelected){
                        case 0:

                            accelerationText.setString("0 - " + to_string(int(player.getTopSpeed()) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[0], true);
                            vehicleCar.setScale(1.6f * c.screenScale, 1.6f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 160.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 25.f * c.screenScale);

                            vehicleName.setString(player.getBrandName());
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 130.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(player.getTopSpeed())) + "KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(player.getAngle());
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(player.getMotorName());
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((player.getTopSpeed() / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                            break;
                        case 1:

                            accelerationText.setString("0 - " + to_string(int(player2.getTopSpeed()) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[1], true);
                            vehicleCar.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 105.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 5.f * c.screenScale);

                            vehicleName.setString(player2.getBrandName());
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 130.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(player2.getTopSpeed())) + "KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(player2.getAngle());
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(player2.getMotorName());
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((player2.getTopSpeed() / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                            break;
                        case 2:

                            accelerationText.setString("0 - " + to_string(int(player3.getTopSpeed()) / 2) + " KM/H:");
                            accelerationText.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale,
                                                         c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            vehicleCar.setTexture(vehicleTextures[2], true);
                            vehicleCar.setScale(2.7f * c.screenScale, 3.2f * c.screenScale);
                            vehicleCar.setPosition((c.w.getSize().x / 2.f) + 100.0f * c.screenScale,
                                                    c.w.getSize().y / 2.f - 30.f * c.screenScale);

                            vehicleName.setString(player3.getBrandName());
                            vehicleName.setPosition(c.w.getSize().x / 2.f + 130.0f * c.screenScale, c.w.getSize().y / 2.f - 143.0f * c.screenScale);

                            speed.setString(to_string(int(player3.getTopSpeed())) + "KM/H");
                            speed.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + speedVehicleText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 75.0f * c.screenScale);

                            value = to_string(player3.getAngle());
                            angle.setString(value.substr(0, value.find(".") + 4) + " RAD/S");
                            angle.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + angleTurnText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f - 5.0f * c.screenScale);

                            motor.setString(player3.getMotorName());
                            motor.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + motorText.getLocalBounds().width + 5.f,
                                              c.w.getSize().y / 2.f + 65.0f * c.screenScale);

                            value = to_string((player3.getTopSpeed() / 2.f) / TIME_HALF_SPEED);
                            acceleration.setString(value.substr(0, value.find(".") + 3) + " SEC");
                            acceleration.setPosition(c.w.getSize().x / 2.f - 385.0f * c.screenScale + accelerationText.getLocalBounds().width + 5.f,
                                                     c.w.getSize().y / 2.f + 135.0f * c.screenScale);

                            triangle.setFillColor(c.vehicleSelectionMenuColorButtons[2]);
                    }
                }
            }

            c.w.draw(sprite);
            c.w.draw(selectionVehicleText);
            c.w.draw(vehicleShape);
            c.w.draw(garage);
            c.w.draw(descriptionShape);
            c.w.draw(vehiclePropertiesText);
            c.w.draw(vehicleName);
            c.w.draw(speedVehicleText);
            c.w.draw(angleTurnText);
            c.w.draw(motorText);
            c.w.draw(accelerationText);
            c.w.draw(speed);
            c.w.draw(angle);
            c.w.draw(motor);
            c.w.draw(acceleration);
            c.w.draw(vehicleCar);
            c.w.draw(triangle);
            c.w.draw(triangle2);

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
            else if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
                // Change the controllers of the car
                backSpacePressed = true;
                r.soundEffects[11]->stop();
                r.soundEffects[11]->play();
            }

            switch(optionSelected){
                case 0:
                    triangle.setFillColor(c.vehicleSelectionMenuColorButtons[0]);
                    triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[1]);
                    break;
                case 1:
                case 2:
                    triangle.setFillColor(c.vehicleSelectionMenuColorButtons[1]);
                    triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[1]);
                    break;
                case 3:
                    triangle.setFillColor(c.vehicleSelectionMenuColorButtons[1]);
                    triangle2.setFillColor(c.vehicleSelectionMenuColorButtons[0]);
            }
        }
    }

    r.soundTracks[16]->stop();
    r.soundEffects[40]->stop();

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

    if (backSpacePressed){
        r.soundTracks[1]->play();
        return GAME_MODES_MENU;
    }
    else if (startPressed){

        // Store the car selected by the player
        typeOfVehicle = optionSelected;

        return LOAD_GAME;
    }
}



void Game::readRecordFromLandScape(const string path, string& namePlayer, int& minutesLap, int& secondsLap, int& centsSecondLap){

    // Open the xml file of the scenario
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node();

    // Iterate to get the information of the player menu
    for (xml_node<> *record = menuNode->first_node(); record; record = record->next_sibling()){
        // Check it is the node that contains the information of the player's name
        if ((string)record->name() == "NamePlayer"){
            // Get the background image of the menu
            namePlayer = (string)record->value();
        }
        else if ((string)record->name() == "Minutes"){
            // Get the minutes of the record time
            minutesLap = stoi(record->value());
        }
        else if ((string)record->name() == "Seconds"){
            // Get the seconds of the record time
            secondsLap = stoi(record->value());
        }
        else if ((string)record->name() == "HundredthsOfSecond"){
            // Get the hundredths of second of the record time
            centsSecondLap = stoi(record->value());
        }
    }
}



void Game::writeRecordFromLandScape(const string path, string namePlayer, int minutesLap, int secondsLap, int centsSecondLap){
    // xml file which stores the player with the highest score in the level
    ofstream theFile (path);
    xml_document<> doc;

    // Add the headers to the file
    xml_node<>* decl = doc.allocate_node(node_declaration);
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "UTF-8"));
    doc.append_node(decl);

    // Create the node record
    xml_node<>* root = doc.allocate_node(node_element, "Record");
    doc.append_node(root);

    // Create a node with the new name of the player
    xml_node<>* name = doc.allocate_node(node_element, "NamePlayer");
    root->append_node(name);
    name->value(namePlayer.c_str());

    // Create a new node with the minutes of the time's player
    xml_node<>* minutes = doc.allocate_node(node_element, "Minutes");
    root->append_node(minutes);
    minutes->value(to_string(minutesLap).c_str());

    // Create a new node with the seconds of the time's player
    xml_node<>* seconds = doc.allocate_node(node_element, "Seconds");
    root->append_node(seconds);
    seconds->value(to_string(secondsLap).c_str());

    // Create a new node with the hundredths of seconds of the time's player
    xml_node<>* hundredtsOfSeconds = doc.allocate_node(node_element, "HundredthsOfSecond");
    root->append_node(hundredtsOfSeconds);
    hundredtsOfSeconds->value(to_string(centsSecondLap).c_str());

    // Store the new xml file configuration
    theFile << doc;
    theFile.close();
    doc.clear();
}



State Game::classificationRace(Configuration& c, SoundPlayer& r){

    // Clean the cars
    cars.clear();

    // Loads enemies and time
    checkDifficulty(c);

    // Set the scale of the console window
    c.window.setView(View(Vector2f(c.window.getSize().x / 2.0f, c.window.getSize().y / 2.0f),
                          Vector2f(c.window.getSize().x, c.window.getSize().y)));
    c.w.create(static_cast<unsigned int>(c.window.getView().getSize().x),
               static_cast<unsigned int>(c.window.getView().getSize().y));
    c.screenScale = float(c.w.getSize().x) / float(DEFAULT_WIDTH);

    c.w.clear(Color(0, 0, 0));
    Sprite bufferSprite(c.w.getTexture());
    c.w.display();
    c.window.draw(bufferSprite);
    c.window.display();

    Texture t;
    t.loadFromFile("Data/Menus/MainMenu/Images/cover.png");
    t.setRepeated(true);
    t.setSmooth(true);

    // Global rectangle of the background
    IntRect background(0, 0, c.w.getSize().x, c.w.getSize().y);
    Sprite sprite(t, background);

    // Control if the start key is pressed
    bool startPressed = false;

    // Offset of the rectangle shape
    float offsetY = 700.f;

    float offsetTitleText = -1.0f;

    float offsetTimeLapTexts = 3.0f;

    float carOffset = 1.f;

    Text recordText;
    recordText.setString("NEW RECORD!");
    recordText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    recordText.setFont(c.fontTimeToPlay);
    recordText.setStyle(Text::Bold);
    recordText.setFillColor(Color(64, 147, 225));
    recordText.setOutlineColor(Color::Black);
    recordText.setOutlineThickness(3.0f * c.screenScale);
    recordText.setPosition((c.w.getSize().x / 2.f) - (recordText.getLocalBounds().width / 2.f), c.w.getSize().y / 2.f + 175.0f * c.screenScale);

    // Vehicle sprite
    Sprite vehicle;
    Texture vehicleTexture;

    bool soundMap = false;

    r.soundEffects[47]->stop();
    r.soundEffects[47]->play();

    bool mainTextArrived = false;
    bool lapTextsArrived = false;
    bool carSpriteArrived = false;


    // Until start key is pressed
    while(!mainTextArrived && !lapTextsArrived && !carSpriteArrived){

        // Creation of the panel rectangle of the menu
        RectangleShape shape;
        shape.setPosition((c.w.getSize().x / 2.f) - 350.0f * c.screenScale, c.w.getSize().y / 2.f - offsetY * c.screenScale);
        shape.setSize(sf::Vector2f(710.0f * c.screenScale, 490.0f * c.screenScale));
        shape.setOutlineColor(Color::Green);
        shape.setOutlineThickness(5.0f * c.screenScale);
        shape.setFillColor(Color(0, 0, 0, 200));

        // Main Text of the menu
        Text titleText;
        titleText.setString(tourLandScapes[indexLandScape].getName());
        titleText.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
        titleText.setFont(c.fontTimeToPlay);
        titleText.setStyle(Text::Bold);
        titleText.setFillColor(Color::White);
        titleText.setOutlineColor(Color::Black);
        titleText.setOutlineThickness(3.0f * c.screenScale);
        titleText.setPosition(((c.w.getSize().x / 2.f) - (titleText.getLocalBounds().width / 2.f)) * offsetTitleText,
                                c.w.getSize().y / 2.f - 230.0f * c.screenScale);

        // Main Text of the menu
        Text totalTime;
        totalTime.setString("TOTAL TIME");
        totalTime.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        totalTime.setFont(c.fontTimeToPlay);
        totalTime.setStyle(Text::Bold);
        totalTime.setFillColor(Color(64, 147, 225));
        totalTime.setOutlineColor(Color::Black);
        totalTime.setOutlineThickness(3.0f * c.screenScale);
        totalTime.setPosition(((c.w.getSize().x / 2.f) - (totalTime.getLocalBounds().width / 2.f)) * offsetTimeLapTexts,
                                c.w.getSize().y / 2.f - 140.0f * c.screenScale);

        // Update the indicators
        string lapTime;
        lapTime = (minutesTrip < 10) ? "0" + to_string(int(minutesTrip)) + ":" : to_string(int(minutesTrip)) + ":";
        lapTime += (secsTrip < 10) ? "0" + to_string(int(secsTrip)) + ":" : to_string(int(secsTrip)) + ":";
        int cent_sec = cents_secondTrip * 100.f;
        lapTime += (cent_sec < 10) ? "0" + to_string(cent_sec) : to_string(cent_sec);

        Text timeLap;
        timeLap.setString(lapTime);
        timeLap.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        timeLap.setFont(c.fontTimeToPlay);
        timeLap.setStyle(Text::Bold);
        timeLap.setFillColor(Color(64, 147, 225));
        timeLap.setOutlineColor(Color::Black);
        timeLap.setOutlineThickness(3.0f * c.screenScale);
        timeLap.setPosition(((c.w.getSize().x / 2.f) - (timeLap.getLocalBounds().width / 2.f)) * offsetTimeLapTexts,
                              c.w.getSize().y / 2.f - 80.0f * c.screenScale);

        switch(typeOfVehicle){
            case 0:
                vehicleTexture.loadFromFile("Data/Vehicles/Motorbike/Images/c45.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(1.6f * c.screenScale, 1.6f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 90.0f * c.screenScale, c.w.getSize().y / carOffset - 2.f * c.screenScale);
                break;
            case 1:
                vehicleTexture.loadFromFile("Data/Vehicles/Devastator/Images/c38.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset + 17.f * c.screenScale);
                break;
            case 2:
                vehicleTexture.loadFromFile("Data/Vehicles/Minivan/Images/c30.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(2.7f * c.screenScale, 3.2f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset - 14.f * c.screenScale);
                break;
            case 3:
                vehicleTexture.loadFromFile("Data/Vehicles/Truck/Images/c56.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(2.7f * c.screenScale, 3.5f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset - 20.f * c.screenScale);
        }

        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return EXIT;
            }
        }

        c.w.draw(sprite);
        c.w.draw(shape);

        if (offsetTitleText < 1.f){
            offsetTitleText += 0.1;
        }
        else {
            mainTextArrived = true;
        }

        if (offsetTimeLapTexts > 1.1f){
            offsetTimeLapTexts -= 0.1;
        }
        else {
            lapTextsArrived = true;
        }

        if (carOffset < 2.0f){
            carOffset += 0.04705;
        }
        else {
            carSpriteArrived = true;
        }

        if (offsetY > 250.f){
            offsetY -= 35.f;
        }
        else {
            if (!soundMap){
                soundMap = true;
                r.soundEffects[46]->stop();
                r.soundEffects[46]->play();
            }
        }

        c.w.draw(titleText);
        c.w.draw(totalTime);
        c.w.draw(timeLap);
        c.w.draw(vehicle);

        bufferSprite.setTexture(c.w.getTexture(), true);
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

         // Check if the start keyword has been pressed
        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            // Pass to the second menu
            startPressed = true;
            r.soundEffects[1]->stop();
            r.soundEffects[1]->play();
        }

        sleep(milliseconds(50));
    }


    // Creation of the panel rectangle of the menu
    RectangleShape shape;
    shape.setPosition((c.w.getSize().x / 2.f) - 350.0f * c.screenScale, c.w.getSize().y / 2.f - offsetY * c.screenScale);
    shape.setSize(sf::Vector2f(710.0f * c.screenScale, 490.0f * c.screenScale));
    shape.setOutlineColor(Color::Green);
    shape.setOutlineThickness(5.0f * c.screenScale);
    shape.setFillColor(Color(0, 0, 0, 200));

    // Main Text of the menu
    Text titleText;
    titleText.setString(tourLandScapes[indexLandScape].getName());
    titleText.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
    titleText.setFont(c.fontTimeToPlay);
    titleText.setStyle(Text::Bold);
    titleText.setFillColor(Color::White);
    titleText.setOutlineColor(Color::Black);
    titleText.setOutlineThickness(3.0f * c.screenScale);
    titleText.setPosition(((c.w.getSize().x / 2.f) - (titleText.getLocalBounds().width / 2.f)) * offsetTitleText,
                            c.w.getSize().y / 2.f - 230.0f * c.screenScale);

    // Main Text of the menu
    Text totalTime;
    totalTime.setString("TOTAL TIME");
    totalTime.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    totalTime.setFont(c.fontTimeToPlay);
    totalTime.setStyle(Text::Bold);
    totalTime.setFillColor(Color(64, 147, 225));
    totalTime.setOutlineColor(Color::Black);
    totalTime.setOutlineThickness(3.0f * c.screenScale);
    totalTime.setPosition(((c.w.getSize().x / 2.f) - (totalTime.getLocalBounds().width / 2.f)) * offsetTimeLapTexts,
                            c.w.getSize().y / 2.f - 140.0f * c.screenScale);

    // Update the indicators
    string lapTime;
    lapTime = (minutesTrip < 10) ? "0" + to_string(int(minutesTrip)) + ":" : to_string(int(minutesTrip)) + ":";
    lapTime += (secsTrip < 10) ? "0" + to_string(int(secsTrip)) + ":" : to_string(int(secsTrip)) + ":";
    int cent_sec = cents_secondTrip * 100.f;
    lapTime += (cent_sec < 10) ? "0" + to_string(cent_sec) : to_string(cent_sec);

    Text timeLap;
    timeLap.setString(lapTime);
    timeLap.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    timeLap.setFont(c.fontTimeToPlay);
    timeLap.setStyle(Text::Bold);
    timeLap.setFillColor(Color(64, 147, 225));
    timeLap.setOutlineColor(Color::Black);
    timeLap.setOutlineThickness(3.0f * c.screenScale);
    timeLap.setPosition(((c.w.getSize().x / 2.f) - (timeLap.getLocalBounds().width / 2.f)) * offsetTimeLapTexts,
                          c.w.getSize().y / 2.f - 80.0f * c.screenScale);

    switch(typeOfVehicle){
        case 0:
            vehicleTexture.loadFromFile("Data/Vehicles/Motorbike/Images/c45.png");
            vehicle.setTexture(vehicleTexture, true);
            vehicle.setScale(1.6f * c.screenScale, 1.6f * c.screenScale);
            vehicle.setPosition((c.w.getSize().x / 2.f) - 90.0f * c.screenScale, c.w.getSize().y / carOffset - 2.f * c.screenScale);
            break;
        case 1:
            vehicleTexture.loadFromFile("Data/Vehicles/Devastator/Images/c38.png");
            vehicle.setTexture(vehicleTexture, true);
            vehicle.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
            vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset + 17.f * c.screenScale);
            break;
        case 2:
            vehicleTexture.loadFromFile("Data/Vehicles/Minivan/Images/c30.png");
            vehicle.setTexture(vehicleTexture, true);
            vehicle.setScale(2.7f * c.screenScale, 3.2f * c.screenScale);
            vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset - 14.f * c.screenScale);
            break;
        case 3:
            vehicleTexture.loadFromFile("Data/Vehicles/Truck/Images/c56.png");
            vehicle.setTexture(vehicleTexture, true);
            vehicle.setScale(2.7f * c.screenScale, 3.5f * c.screenScale);
            vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset - 20.f * c.screenScale);
    }


    float elapsed1, elapsed2;
    Clock blinkClcok;
    Time blink_delay = seconds(0.5f);

    blinkClcok.restart().asSeconds();
    elapsed1 = blinkClcok.restart().asSeconds();
    bool blink = true;

    // Read the file with the best time
    string path = "Data/Records/WorldTour_PolePosition/LandScape" + to_string(indexLandScape + 1) + "_";

    // Control if the game has been played with the AI enabled or not
    if (c.enableAI){
        // Record with AI active
        path += "Enabled_";
    }
    else {
        // Record with AI disabled
        path += "Disabled_";
    }

    // Control the difficulty of the game
    switch (c.level){
        case PEACEFUL:
            path += "Peaceful.xml";
            break;
        case EASY:
            path += "Easy.xml";
            break;
        case NORMAL:
            path += "Normal.xml";
            break;
        case HARD:
            path += "Hard.xml";
    }

    string namePlayer;
    int minutesLap, secondsLap, centsSecondLap;

    // Read the record of the land scape
    readRecordFromLandScape(path, namePlayer, minutesLap, secondsLap, centsSecondLap);

    // Control if there is a new record or not
    bool record = false;

    if (minutesTrip < minutesLap){
        // There is a new record
        record = true;
    }
    else if (minutesTrip == minutesLap){
        // Both have the same minutes
        if (secsTrip < secondsLap){
            // Same minutes but less seconds
            record = true;
        }
        else if (secsTrip == secondsLap){
            // Both have the same minutes and seconds
            if (cents_secondTrip < centsSecondLap){
                // Same minutes and seconds but less hundredths of seconds
                record = true;
            }
        }
    }

    // Reproduce sound effect of record
    if (record){
        r.soundEffects[50]->stop();
        r.soundEffects[50]->play();

        // Until start key is pressed
        for (int j = 0; j <= 150; j++){

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }

            c.w.draw(sprite);
            c.w.draw(shape);
            c.w.draw(titleText);

            elapsed2 = blinkClcok.getElapsedTime().asSeconds();

            // Change the color of the main text
            if (elapsed2 - elapsed1 >= blink_delay.asSeconds()) {
                blink = !blink;
                blinkClcok.restart();
            }

            if (blink) {
                totalTime.setFillColor(Color(64, 147, 225));
                totalTime.setOutlineColor(Color::Black);
                timeLap.setFillColor(Color(64, 147, 225));
                timeLap.setOutlineColor(Color::Black);
                recordText.setFillColor(Color(64, 147, 225));
                recordText.setOutlineColor(Color::Black);
            }
            else {
                totalTime.setFillColor(Color::Transparent);
                totalTime.setOutlineColor(Color::Transparent);
                timeLap.setFillColor(Color::Transparent);
                timeLap.setOutlineColor(Color::Transparent);
                recordText.setFillColor(Color::Transparent);
                recordText.setOutlineColor(Color::Transparent);
            }

            c.w.draw(totalTime);
            c.w.draw(timeLap);
            c.w.draw(vehicle);
            c.w.draw(recordText);

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
            sleep(milliseconds(50));
        }
        // Ask the player to introduce his name
        int lettersIntroduced = 0;

        recordText.setString("ENTER YOUR NAME: ");
        recordText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        recordText.setFont(c.fontTimeToPlay);
        recordText.setStyle(Text::Bold);
        recordText.setFillColor(Color(64, 147, 225));
        recordText.setOutlineColor(Color::Black);
        recordText.setOutlineThickness(3.0f * c.screenScale);
        recordText.setPosition((c.w.getSize().x / 2.f) - 280.f * c.screenScale, c.w.getSize().y / 2.f + 175.0f * c.screenScale);

        string name = "_";

        Text playerName;
        playerName.setString(name);
        playerName.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        playerName.setFont(c.fontTimeToPlay);
        playerName.setStyle(Text::Bold);
        playerName.setFillColor(Color(64, 147, 225));
        playerName.setOutlineColor(Color::Black);
        playerName.setOutlineThickness(3.0f * c.screenScale);
        playerName.setPosition((c.w.getSize().x / 2.f) + 170.f * c.screenScale, c.w.getSize().y / 2.f + 175.0f * c.screenScale);

        KeywordMapper kM = KeywordMapper();

        // The player have to introduce all the letters
        while (lettersIntroduced != 3) {

            // while there are pending events...
            Event event;
            while (c.window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    return EXIT;
                }
                else if (event.type == Event::KeyPressed) {
                    // Get code of the key
                    int code = event.key.code;
                    // Check if the key pressed is a letter or not
                    if (code >= 0 && code <= 25) {
                        lettersIntroduced++;
                        string keyLetter = kM.mapperIdKeyWord[code];
                        if (name == "_") {
                            name = keyLetter + "_";
                            r.soundEffects[1]->stop();
                            r.soundEffects[1]->play();
                        }
                        else {
                            if (lettersIntroduced == 3) {
                                name = name.substr(0, name.size() - 1);
                                name += keyLetter;
                                r.soundEffects[2]->stop();
                                r.soundEffects[2]->play();
                            }
                            else {
                                name = name.substr(0, name.size() - 1);
                                name += keyLetter + "_";
                                r.soundEffects[1]->stop();
                                r.soundEffects[1]->play();
                            }
                        }
                    }
                    else {
                        r.soundEffects[3]->stop();
                        r.soundEffects[3]->play();
                    }
                }
            }

            playerName.setString(name);
            playerName.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
            playerName.setFont(c.fontTimeToPlay);
            playerName.setStyle(Text::Bold);
            playerName.setFillColor(Color(64, 147, 225));
            playerName.setOutlineColor(Color::Black);
            playerName.setOutlineThickness(3.0f * c.screenScale);
            playerName.setPosition((c.w.getSize().x / 2.f) + 160.f * c.screenScale, c.w.getSize().y / 2.f + 175.0f * c.screenScale);

            // Draw the elements of the menu
            c.w.draw(sprite);
            c.w.draw(shape);
            c.w.draw(titleText);
            c.w.draw(totalTime);
            c.w.draw(timeLap);
            c.w.draw(vehicle);
            c.w.draw(recordText);
            c.w.draw(playerName);

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
            sleep(milliseconds(50));
        }

        // Store the name in the file
        writeRecordFromLandScape(path, name, minutesTrip, secsTrip, int(cents_secondTrip * 100.f));
    }
    else {

        string record = "";

        record = (minutesLap < 10) ? "0" + to_string(int(minutesLap)) + ":" : to_string(int(minutesLap)) + ":";
        record += (secondsLap < 10) ? "0" + to_string(int(secondsLap)) + ":" : to_string(int(secondsLap)) + ":";
        int cent_sec = centsSecondLap * 100.f;
        record += (cent_sec < 10) ? "0" + to_string(cent_sec) : to_string(cent_sec);

        recordText.setString("CURRENT RECORD: " + record);
        recordText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        recordText.setFont(c.fontTimeToPlay);
        recordText.setStyle(Text::Bold);
        recordText.setFillColor(Color(64, 147, 225));
        recordText.setOutlineColor(Color::Black);
        recordText.setOutlineThickness(3.0f * c.screenScale);
        recordText.setPosition((c.w.getSize().x / 2.f) - (recordText.getLocalBounds().width / 2.f), c.w.getSize().y / 2.f + 175.0f * c.screenScale);

        for (int j = 0; j <= 150; j++){

            // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }

            c.w.draw(sprite);
            c.w.draw(shape);
            c.w.draw(titleText);

            elapsed2 = blinkClcok.getElapsedTime().asSeconds();

            // Change the color of the main text
            if (elapsed2 - elapsed1 >= blink_delay.asSeconds()) {
                blink = !blink;
                blinkClcok.restart();
            }

            if (blink) {
                totalTime.setFillColor(Color(64, 147, 225));
                totalTime.setOutlineColor(Color::Black);
                timeLap.setFillColor(Color(64, 147, 225));
                timeLap.setOutlineColor(Color::Black);
                recordText.setFillColor(Color(64, 147, 225));
                recordText.setOutlineColor(Color::Black);
            }
            else {
                totalTime.setFillColor(Color::Transparent);
                totalTime.setOutlineColor(Color::Transparent);
                timeLap.setFillColor(Color::Transparent);
                timeLap.setOutlineColor(Color::Transparent);
                recordText.setFillColor(Color::Transparent);
                recordText.setOutlineColor(Color::Transparent);
            }

            c.w.draw(totalTime);
            c.w.draw(timeLap);
            c.w.draw(vehicle);
            c.w.draw(recordText);

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();
            sleep(milliseconds(50));
        }
    }

    // Main Text of the menu
    Text startText;
    startText.setString("PRESS START!");
    startText.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
    startText.setFont(c.fontTimeToPlay);
    startText.setStyle(Text::Bold);
    startText.setFillColor(Color::Green);
    startText.setOutlineColor(Color::Black);
    startText.setOutlineThickness(3.0f * c.screenScale);
    startText.setPosition((c.w.getSize().x / 2.f) - (startText.getLocalBounds().width / 2.f), c.w.getSize().y / 2.f + 175.0f * c.screenScale);


    while(!startPressed){
        // Detect the possible events
            Event e{};
            while (c.window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    return EXIT;
                }
            }

            c.w.draw(sprite);
            c.w.draw(shape);
            c.w.draw(titleText);

            elapsed2 = blinkClcok.getElapsedTime().asSeconds();

            // Change the color of the main text
            if (elapsed2 - elapsed1 >= blink_delay.asSeconds()) {
                blink = !blink;
                blinkClcok.restart();
            }

            if (blink) {
                totalTime.setFillColor(Color(64, 147, 225));
                totalTime.setOutlineColor(Color::Black);
                timeLap.setFillColor(Color(64, 147, 225));
                timeLap.setOutlineColor(Color::Black);
                startText.setFillColor(Color::Green);
                startText.setOutlineColor(Color::Black);
            }
            else {
                totalTime.setFillColor(Color::Transparent);
                totalTime.setOutlineColor(Color::Transparent);
                timeLap.setFillColor(Color::Transparent);
                timeLap.setOutlineColor(Color::Transparent);
                startText.setFillColor(Color::Transparent);
                startText.setOutlineColor(Color::Transparent);
            }

            c.w.draw(totalTime);
            c.w.draw(timeLap);
            c.w.draw(vehicle);
            c.w.draw(startText);

            bufferSprite.setTexture(c.w.getTexture(), true);
            c.w.display();
            c.window.draw(bufferSprite);
            c.window.display();

             // Check if the start keyword has been pressed
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                // Pass to the second menu
                startPressed = true;
                r.soundEffects[1]->stop();
                r.soundEffects[1]->play();
                r.soundEffects[49]->stop();
                r.soundEffects[49]->play();
            }

            sleep(milliseconds(50));
    }

    mainTextArrived = false;
    lapTextsArrived = false;
    carSpriteArrived = false;
    soundMap = false;

    // Until start key is pressed
    while(!mainTextArrived && !lapTextsArrived && !carSpriteArrived){

        // Creation of the panel rectangle of the menu
        RectangleShape shape;
        shape.setPosition((c.w.getSize().x / 2.f) - 350.0f * c.screenScale, c.w.getSize().y / 2.f - offsetY * c.screenScale);
        shape.setSize(sf::Vector2f(710.0f * c.screenScale, 490.0f * c.screenScale));
        shape.setOutlineColor(Color::Green);
        shape.setOutlineThickness(5.0f * c.screenScale);
        shape.setFillColor(Color(0, 0, 0, 200));

        // Main Text of the menu
        Text titleText;
        titleText.setString(tourLandScapes[indexLandScape].getName());
        titleText.setCharacterSize(static_cast<unsigned int>(int(50.0f * c.screenScale)));
        titleText.setFont(c.fontTimeToPlay);
        titleText.setStyle(Text::Bold);
        titleText.setFillColor(Color::White);
        titleText.setOutlineColor(Color::Black);
        titleText.setOutlineThickness(3.0f * c.screenScale);
        titleText.setPosition(((c.w.getSize().x / 2.f) - (titleText.getLocalBounds().width / 2.f)) * offsetTitleText,
                                c.w.getSize().y / 2.f - 230.0f * c.screenScale);

        // Main Text of the menu
        Text totalTime;
        totalTime.setString("TOTAL TIME");
        totalTime.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        totalTime.setFont(c.fontTimeToPlay);
        totalTime.setStyle(Text::Bold);
        totalTime.setFillColor(Color(64, 147, 225));
        totalTime.setOutlineColor(Color::Black);
        totalTime.setOutlineThickness(3.0f * c.screenScale);
        totalTime.setPosition(((c.w.getSize().x / 2.f) - (totalTime.getLocalBounds().width / 2.f)) * offsetTimeLapTexts,
                                c.w.getSize().y / 2.f - 140.0f * c.screenScale);

        // Update the indicators
        string lapTime;
        lapTime = (minutesTrip < 10) ? "0" + to_string(int(minutesTrip)) + ":" : to_string(int(minutesTrip)) + ":";
        lapTime += (secsTrip < 10) ? "0" + to_string(int(secsTrip)) + ":" : to_string(int(secsTrip)) + ":";
        int cent_sec = cents_secondTrip * 100.f;
        lapTime += (cent_sec < 10) ? "0" + to_string(cent_sec) : to_string(cent_sec);

        Text timeLap;
        timeLap.setString(lapTime);
        timeLap.setCharacterSize(static_cast<unsigned int>(int(40.0f * c.screenScale)));
        timeLap.setFont(c.fontTimeToPlay);
        timeLap.setStyle(Text::Bold);
        timeLap.setFillColor(Color(64, 147, 225));
        timeLap.setOutlineColor(Color::Black);
        timeLap.setOutlineThickness(3.0f * c.screenScale);
        timeLap.setPosition(((c.w.getSize().x / 2.f) - (timeLap.getLocalBounds().width / 2.f)) * offsetTimeLapTexts,
                              c.w.getSize().y / 2.f - 80.0f * c.screenScale);

        switch(typeOfVehicle){
            case 0:
                vehicleTexture.loadFromFile("Data/Vehicles/Motorbike/Images/c45.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(1.6f * c.screenScale, 1.6f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 90.0f * c.screenScale, c.w.getSize().y / carOffset - 2.f * c.screenScale);
                break;
            case 1:
                vehicleTexture.loadFromFile("Data/Vehicles/Devastator/Images/c38.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(2.5f * c.screenScale, 2.5f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset + 17.f * c.screenScale);
                break;
            case 2:
                vehicleTexture.loadFromFile("Data/Vehicles/Minivan/Images/c30.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(2.7f * c.screenScale, 3.2f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset - 14.f * c.screenScale);
                break;
            case 3:
                vehicleTexture.loadFromFile("Data/Vehicles/Truck/Images/c56.png");
                vehicle.setTexture(vehicleTexture, true);
                vehicle.setScale(2.7f * c.screenScale, 3.5f * c.screenScale);
                vehicle.setPosition((c.w.getSize().x / 2.f) - 120.0f * c.screenScale, c.w.getSize().y / carOffset - 20.f * c.screenScale);
        }

        // Detect the possible events
        Event e{};
        while (c.window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return EXIT;
            }
        }

        c.w.draw(sprite);
        c.w.draw(shape);

        if (offsetTitleText > -1.f){
            offsetTitleText -= 0.1;
        }
        else {
            mainTextArrived = true;
        }

        if (offsetTimeLapTexts < 3.0f){
            offsetTimeLapTexts += 0.1;
        }
        else {
            lapTextsArrived = true;
        }

        if (carOffset > 1.0f){
            carOffset -= 0.03705;
        }
        else {
            carSpriteArrived = true;
        }

        if (offsetY < 800.f){
            offsetY += 25.f;
        }

        c.w.draw(titleText);
        c.w.draw(totalTime);
        c.w.draw(timeLap);
        c.w.draw(vehicle);

        bufferSprite.setTexture(c.w.getTexture(), true);
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();

        sleep(milliseconds(50));
    }

    c.w.draw(sprite);

     // Creation of the panel rectangle of the menu
    RectangleShape blackShape;
    blackShape.setPosition(0, 0);
    blackShape.setSize(sf::Vector2f(c.w.getSize().x, c.w.getSize().y));

    for (int i = 0; i <= 70; i++){
        blackShape.setFillColor(Color(0, 0, 0, i));
        c.w.draw(blackShape);
        bufferSprite.setTexture(c.w.getTexture(), true);
        c.w.display();
        c.window.draw(bufferSprite);
        c.window.display();
        sleep(milliseconds(20));
    }

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

    // Start with the initial map again
    level = -1;
    indexLandScape++;

    currentMap = &tourLandScapes[indexLandScape];

    int bdTime = 0;
    time = int(float(tourLandScapes[indexLandScape].getTimeToPlay()) * timeMul) + bdTime;
    finalGame = false;

    lastY = 0;
    vehicleCrash = false;

    onPause = false;
    comeFromOptions = false;
    blink = false;
    arrival = false;
    updatedTimeCheck = false;

    minutes = 0;
    secs = 0;
    cents_second = 0;
    minutesTrip = 0;
    secsTrip = 0;
    cents_secondTrip = 0;
    timeCheck = 0;
    lap = "00:00:00";
    indexCheckPoint = 1;
    posArrival = 1;

    switch(typeOfVehicle){
        case 0:
            player.setVehicle();
            break;
        case 1:
            player2.setVehicle();
            break;
        case 2:
            player3.setVehicle();
            break;
        case 3:
            player4.setVehicle();
    }

    r.soundTracks[15]->stop();
    return PLAY_GAME;
}
