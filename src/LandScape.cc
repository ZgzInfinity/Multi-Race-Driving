

#include "../include/LandScape.h"

using namespace rapidxml;




/**
 * Get the interval coordinates of any element of the scene
 * @param child is a pointer to the xml fils that points to a curve, mountain or sprite
 * @param objectCode controls what kind of element is been processed
 * @param startPos is going to store the initial interval position of the element of the scene
 * @param finalPos is going to store the initial interval position of the element of the scene
 */
inline void LandScape::getIntervalCoordinates(xml_node<> *child, int objectCode, int& startPos, int& finalPos){
    // Loop in order to iterate all the children of the Sprite node
    int elementsRead = 0, intervalsRead = 0;
    // Variable to store the possible attributes
    xml_attribute<>* attr;
    // Read one of the two optional attributes to specify the starting point of the interval
    attr = child->first_attribute("startPosGE");
    string startPosition = (attr != nullptr) ? attr->value() : "Unknown";
    if (startPosition == "Unknown"){
        // The first option is not in the file so looks for the second one
        attr = child->first_attribute("startPosGT");
        startPosition = (attr != nullptr) ? attr->value() : "Unknown";
        if (startPosition == "Unknown"){
            cerr << "There is not start position specification in the interval " << elementsRead << endl;
            exit(1);
        }
        else {
            // Check the final position of the interval
            // Read one of the two optional attributes to specify the starting point of the interval
            attr = child->first_attribute("finalPosLE");
            string finalPosition = (attr != nullptr) ? attr->value() : "Unknown";
            if (finalPosition == "Unknown"){
                // The first option is not in the file so looks for the second one
                attr = child->first_attribute("finalPosLT");
                finalPosition = (attr != nullptr) ? attr->value() : "Unknown";
                if (finalPosition == "Unknown"){
                    cerr << "There is not final position specification in the interval " << intervalsRead << endl;
                    exit(1);
                }
                else {
                    startPos = stoi(startPosition); startPos++;
                    finalPos = stoi(finalPosition); finalPos--;
                }
            }
            else {
                // The first option is not in the file so looks for the second one
                attr = child->first_attribute("finalPosLT");
                string finalPositionNew = (attr != nullptr) ? attr->value() : "Unknown";
                if (finalPositionNew != "Unknown"){
                    cerr << "Error, the interval " << intervalsRead <<
                            " cannot be specified with finalPosGE and finalPosGT and the same time " << endl;
                    exit(10);
                }
                else {
                    startPos = stoi(startPosition); startPos++;
                    finalPos = stoi(finalPosition);
                }
            }
        }
    }
    else {
        // The first option is in the file so looks for the second one
        // Cannot be at the same
        attr = child->first_attribute("startPosGT");
        string startPositionNew = (attr != nullptr) ? attr->value() : "Unknown";
        if (startPositionNew != "Unknown"){
            cerr << "Error, the interval " << intervalsRead <<
                    " cannot be specified with startPosGE and startPosGT and the same time " << endl;
            exit(10);
        }
        else {
            // Check the final position of the interval
            // Read one of the two optional attributes to specify the starting point of the interval
            attr = child->first_attribute("finalPosLE");
            string finalPosition = (attr != nullptr) ? attr->value() : "Unknown";
            if (finalPosition == "Unknown"){
                // The first option is not in the file so looks for the second one
                attr = child->first_attribute("finalPosLT");
                finalPosition = (attr != nullptr) ? attr->value() : "Unknown";
                if (finalPosition == "Unknown"){
                    cerr << "There is not final position specification in the interval " << intervalsRead << endl;
                }
                else {
                    startPos = stoi(startPosition);
                    finalPos = stoi(finalPosition); finalPos--;
                }
            }
            else {
                // The first option is not in the file so looks for the second one
                attr = child->first_attribute("finalPosLT");
                string finalPositionNew = (attr != nullptr) ? attr->value() : "Unknown";
                if (finalPositionNew != "Unknown"){
                    cerr << "Error, the interval " << intervalsRead <<
                            " cannot be specified with finalPosGE and finalPosGT and the same time " << endl;
                    exit(10);
                }
                else {
                    startPos = stoi(startPosition);
                    finalPos = stoi(finalPosition);
                }
            }
        }
    }
}



/**
 * Parses all the configuration of the color of the road written in the xml
 * configuration file of the scene
 * @param child is a node of the xml file that points to the color of the grass information
 */
inline void LandScape::parseColorGrassRoadScene(xml_node<> * child){
    int colorRed, colorGreen, colorBlue;
    // Loop in order to iterate throughout the colors of the grass
    for (xml_node<> *color_node = child->first_node(); color_node; color_node = color_node->next_sibling()){
        // Loop for iterate the three color channels in RGB format
        for (xml_node<> *color = color_node->first_node(); color; color = color->next_sibling()){
            parseColors(color, colorRed, colorGreen, colorBlue);
        }
        // Check where the color has been stored
        if ((string)child->name() == "Color_grass"){
            grassColor.push_back(Color(colorRed, colorGreen, colorBlue));
        }
        else if ((string)child->name() == "Color_road"){
            roadColor.push_back(Color(colorRed, colorGreen, colorBlue));
        }
        else if ((string)child->name() == "Color_rumble"){
            rumbleColor.push_back(Color(colorRed, colorGreen, colorBlue));
        }
    }
}




/**
 * Parses all the configuration of the colors of the grass, the rumble of the road and the middle of the road
 * configuration file of the scene
 * @param color is a node of the xml file that points to the color of the middle of the road information
 * @param colorRed is where is going to be stored the value of the red channel in RGB color space read from the file
 * @param colorGreen is where is going to be stored the value of the green channel in RGB color space read from the file
 * @param colorBlue is where is going to be stored the value of the blue channel in RGB color space read from the file
 */
inline void LandScape::parseColors(xml_node<> * color, int& colorRed, int& colorGreen, int& colorBlue){
    // Check the upper right coordinate of the background image
    if ((string)color->name() == "R"){
        // Store the lower right coordinate
        colorRed = stoi(color->value());
    }
    else if ((string)color->name() == "G"){
        // Store the lower right coordinate
        colorGreen = stoi(color->value());
    }
    else if ((string)color->name() == "B"){
        // Store the lower right coordinate
        colorBlue = stoi(color->value());
    }
}



void LandScape::addLine(float x, float y, float &z, float prevY, float curve, bool mainColor,
                        Step::SpriteInfo &spriteNearLeft, Step::SpriteInfo &spriteNearRight,
                        Step::SpriteInfo &spriteFarLeft, Step::SpriteInfo &spriteFarRight,
                        int& stepsRead, int& eachNearLeft, int& eachNearRight, int& eachFarLeft,
                        int&eachFarRight, const int startPos, int& codeNearLeft, int& codeNearRight,
                        int& codeFarLeft, int& codeFarRight, bool& generateRandomNearLeft,
                        bool& generateRandomNearRight, bool& generateRandomFarLeft, bool& generateRandomFarRight)

{
    Step lineAux;
    lineAux.position_3d_y = prevY;

    float yInc = (y - prevY) / 5.0f; // 5 is total lines number will be added
    for (int i = 1; i <= 5; i++){
        Step line;
        line.position_3d_x = x;
        line.position_3d_y = lineAux.position_3d_y + yInc;
        line.mainColor = mainColor;
        line.directionCurve = curve;
        line.position_3d_z = z;
        z += segL - 50;

        if ((startPos + stepsRead) % eachNearLeft != 0){
            spriteNearLeft.spriteNum = -1;
        }
        else {
            spriteNearLeft.spriteNum = codeNearLeft;
        }
        if ((startPos + stepsRead) % eachNearRight != 0){
            spriteNearRight.spriteNum = -1;
        }
        else {
            spriteNearRight.spriteNum = codeNearRight;
        }

        if ((startPos + stepsRead) % eachFarLeft != 0){
            spriteFarLeft.spriteNum = -1;
        }
        else {
            spriteFarLeft.spriteNum = codeFarLeft;
        }
        if ((startPos + stepsRead) % eachFarRight != 0){
            spriteFarRight.spriteNum = -1;
        }
        else {
            spriteFarRight.spriteNum = codeFarRight;
        }

        if (generateRandomNearLeft){
            mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
            uniform_real_distribution<float> offset(0.0f, 3.0f);
            spriteNearLeft.offset = offset(rng);
        }

        if (generateRandomNearRight){
            mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
            uniform_real_distribution<float> offset(0.0f, 3.0f);
            spriteNearRight.offset = offset(rng);
        }

        if (generateRandomFarLeft){
            mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
            uniform_real_distribution<float> offset(3.0f, 6.0f);
            spriteFarLeft.offset = offset(rng);
        }

        if (generateRandomFarRight){
            mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
            uniform_real_distribution<float> offset(3.0f, 6.0f);
            spriteFarRight.offset = offset(rng);
        }

        line.spriteNearLeft = spriteNearLeft;
        line.spriteNearRight = spriteNearRight;
        line.spriteFarLeft = spriteFarLeft;
        line.spriteFarRight = spriteFarRight;
        newLines.push_back(line);
        stepsRead++;
        lineAux.position_3d_y += yInc;
    }
}


float LandScape::getPosX(){
    return posX;
}



float LandScape::getPosY(){
    return posY;
}


Step *LandScape::getLine(const int n) {
    if (n < newLines.size() || next == nullptr)
        return &newLines[n % newLines.size()];
    else
        return &next->newLines[(n - newLines.size()) % next->newLines.size()];
}

Step LandScape::getLine(const int n) const{
    if (n < newLines.size() || next == nullptr)
        return newLines[n % newLines.size()];
    else
        return next->newLines[(n - newLines.size()) % next->newLines.size()];
}

Step *LandScape::getPreviousLine(const int n) {
    if ((n > 0 && n - 1 < newLines.size()) || next == nullptr)
        return &newLines[(n - 1) % newLines.size()];
    else
        return &next->newLines[(n - 1 - newLines.size()) % next->newLines.size()];
}

Step LandScape::getPreviousLine(const int n) const {
    if ((n > 0 && n - 1 < newLines.size()) || next == nullptr)
        return newLines[(n - 1) % newLines.size()];
    else
        return next->newLines[(n - 1 - newLines.size()) % next->newLines.size()];
}



void LandScape::parseBackgroundScene(string pathFile){
    // Document xml where the document is going to be parsed
    char* pFile = const_cast<char*>(pathFile.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *nodeLandScape = doc.first_node();

    // Variables to control the different types of terrain
    float curveCoeff = 0.0f, elevation = 0, cordX = 0, cordY = 0, cordZ = 0;
    int elevationIndex = 0, elevationLines = -1;
    bool mainColor = true;

    // Iteration throughout the nodes of the file
    for (xml_node<> *node = nodeLandScape->first_node(); node; node = node->next_sibling()){
        // Check if the node contains the kinds of terrain
        if ((string)node->name() == "Terrain"){
            // Iteration throughout the nodes of the file
            for (xml_node<> *part = node->first_node(); part; part = part->next_sibling()){
                // Iteration throughout the nodes of the file
                for (xml_node<> *nodeTerrain = part->first_node(); nodeTerrain; nodeTerrain = nodeTerrain->next_sibling()){
                    // Iteration of the elements of the actual part of the terrain
                    if ((string)nodeTerrain->name() == "Straight"){
                        // The road goes in straight direction
                        curveCoeff = 0.0f;
                        // Read and parse the road properties in this part of terrain
                        processRoadPart(nodeTerrain->first_node(), curveCoeff, elevation, mainColor, elevationIndex,
                                        elevationLines, true, cordX, cordY, cordZ);
                    }
                    if ((string)nodeTerrain->name() == "Curve"){
                        // Get the direction of the curve
                        curveCoeff = stof(nodeTerrain->first_attribute("direction")->value());
                        // Read and parse the road properties in this part of terrain
                        processRoadPart(nodeTerrain->first_node(), curveCoeff, elevation, mainColor,
                                        elevationIndex, elevationLines, true, cordX, cordY, cordZ);
                    }
                    else if ((string)nodeTerrain->name() == "Dropping" || (string)nodeTerrain->name() == "Climbing") {
                        if ((string)nodeTerrain->name() == "Climbing") {
                            // Get the elevation of the terrain
                            elevation = stof(nodeTerrain->first_attribute("elevation")->value());
                        }
                        else if ((string)nodeTerrain->name() == "Dropping"){
                            // Get the elevation of the terrain
                            elevation = -stof(nodeTerrain->first_attribute("elevation")->value());
                        }
                        // Iterate to get the information of the climb of drop terrain part
                        for (xml_node<> *partTerrain = nodeTerrain->first_node(); partTerrain; partTerrain = partTerrain->next_sibling()){
                            // Iterate to get the elements of each part of the terrain
                            for (xml_node<> *terrain = partTerrain->first_node(); terrain; terrain = terrain->next_sibling()){
                                // Check if it's the node that control the possible curve coefficient
                                if ((string)terrain->name() == "Direction"){
                                    curveCoeff = stof(terrain->value());
                                }
                                else if ((string)terrain->name() == "Road"){
                                    processRoadPart(terrain, curveCoeff, elevation, mainColor,
                                                    elevationIndex, elevationLines, false, cordX, cordY, cordZ);
                                }
                            }
                        }
                    }
                }
            }
        }
        // Check if it's the node that contains the different colors of the road
        else if ((string)node->name() == "Color_grass" || (string)node->name() == "Color_road" ||
                 (string)node->name() == "Color_rumble")
        {
            // Parse the information of the color of the road
            parseColorGrassRoadScene(node);
        }
    }
}


void LandScape::processRoadPart(xml_node<> * roadNode, float& curveCoeff, float& elevation, bool& mainColor,
                                int elevationIndex, int& elevationLines, bool flatTerrain, float& cordX,
                                float& cordY, float& cordZ)
{
    // Local variables
    int startPos, finalPos;
    int eachNearLeft = 0, eachNearRight = 0, eachFarLeft, eachFarRight,
        codeNearLeft = -1, codeNearRight = -1, codeFarLeft = -1, codeFarRight;

    // Sprites of the step
    Step::SpriteInfo spriteNearLeft, spriteNearRight, spriteFarLeft, spriteFarRight;
    int stepsRead = 0;
    // Control if the offset of the sprites must be random or not
    bool generateRandomNearLeft = false, generateRandomNearRight = false,
         generateRandomFarLeft = false, generateRandomFarRight = false;

    // Get the interval coordinates of the terrain
    getIntervalCoordinates(roadNode, 0, startPos, finalPos);

    // Get the sprite information of the terrain
    for (xml_node<> *spriteNode = roadNode->first_node(); spriteNode; spriteNode = spriteNode->next_sibling()){
        // Check if it's the left or right object
        if ((string)spriteNode->name() == "SpriteNearLeft"){
            // Iteration to get the attributes of the sprite object
            for (xml_node<> *attributeNode = spriteNode->first_node(); attributeNode; attributeNode = attributeNode->next_sibling()){
                // Check the interval to show the sprite
                if ((string)attributeNode->name() == "Each"){
                    eachNearLeft = stoi((string)attributeNode->value());
                }
                // Check the offset
                else if ((string)attributeNode->name() == "Offset"){
                    // Check if the offset has be initialized randomly
                    if ((string)attributeNode->value() == "Random"){
                        // Initialize randomly
                        generateRandomNearLeft = true;
                    }
                    else {
                        // Get the offset value from the file
                        generateRandomNearLeft = false;
                        spriteNearLeft.offset = stoi((string)attributeNode->value());
                    }
                }
                // Check the path of the sprite
                else if ((string)attributeNode->name() == "Code"){
                     codeNearLeft = stoi(attributeNode->value()) - 1;
                }
            }
        }
        // Check if it's the left or right object
        else if ((string)spriteNode->name() == "SpriteNearRight"){
            // Iteration to get the attributes of the sprite object
            for (xml_node<> *attributeNode = spriteNode->first_node(); attributeNode; attributeNode = attributeNode->next_sibling()){
                // Check the interval to show the sprite
                if ((string)attributeNode->name() == "Each"){
                    eachNearRight = stoi((string)attributeNode->value());
                }
                // Check the offset
                else if ((string)attributeNode->name() == "Offset"){
                    // Check if the offset has be initialized randomly
                    if ((string)attributeNode->value() == "Random"){
                        // Initialize randomly
                        generateRandomNearRight = true;
                    }
                    else {
                        // Get the offset value from the file
                        generateRandomNearRight = false;
                        spriteNearRight.offset = stoi((string)attributeNode->value());
                    }
                }
                // Check the path of the sprite
                else if ((string)attributeNode->name() == "Code"){
                     codeNearRight = stoi(attributeNode->value()) - 1;
                }
            }
        }
        // Check if it's the left or right object
        if ((string)spriteNode->name() == "SpriteFarLeft"){
            // Iteration to get the attributes of the sprite object
            for (xml_node<> *attributeNode = spriteNode->first_node(); attributeNode; attributeNode = attributeNode->next_sibling()){
                // Check the interval to show the sprite
                if ((string)attributeNode->name() == "Each"){
                    eachFarLeft = stoi((string)attributeNode->value());
                }
                // Check the offset
                else if ((string)attributeNode->name() == "Offset"){
                    // Check if the offset has be initialized randomly
                    if ((string)attributeNode->value() == "Random"){
                        // Initialize randomly
                        generateRandomFarLeft = true;
                    }
                    else {
                        // Get the offset value from the file
                        generateRandomFarLeft = false;
                        spriteFarLeft.offset = stoi((string)attributeNode->value());
                    }
                }
                // Check the path of the sprite
                else if ((string)attributeNode->name() == "Code"){
                     codeFarLeft = stoi(attributeNode->value()) - 1;
                }
            }
        }
        // Check if it's the left or right object
        else if ((string)spriteNode->name() == "SpriteFarRight"){
            // Iteration to get the attributes of the sprite object
            for (xml_node<> *attributeNode = spriteNode->first_node(); attributeNode; attributeNode = attributeNode->next_sibling()){
                // Check the interval to show the sprite
                if ((string)attributeNode->name() == "Each"){
                    eachFarRight = stoi((string)attributeNode->value());
                }
                // Check the offset
                else if ((string)attributeNode->name() == "Offset"){
                    // Check if the offset has be initialized randomly
                    if ((string)attributeNode->value() == "Random"){
                        // Initialize randomly
                        generateRandomFarRight = true;
                    }
                    else {
                        // Get the offset value from the file
                        generateRandomFarRight = false;
                        spriteFarRight.offset = stoi((string)attributeNode->value());
                    }
                }
                // Check the path of the sprite
                else if ((string)attributeNode->name() == "Code"){
                     codeFarRight = stoi(attributeNode->value()) - 1;
                }
            }
        }
    }
    // Check if the kind of terrain
    if (!flatTerrain){
        // Climbing or dropping terrain
        elevationLines = finalPos - startPos;
        elevationIndex = 0;
    }

    // All the information is obtained
    for (int i = startPos; i <= finalPos; i++){
        // Control the elevation of the terrain
        float yAux = cordY;
        if (elevationIndex < elevationLines) {
            yAux += float(elevation) / 2.0f +
                    (float(elevation) / 2.0f) * cosf(M_PI + (M_PI / float(elevationLines)) * float(elevationIndex));
            elevationIndex++;
        }
        if (!newLines.empty() && elevationIndex == elevationLines) {
            cordY = newLines[newLines.size() - 1].position_3d_y;
            yAux = cordY;
            elevationLines = -1;
        }

        addLine(cordX, yAux, cordZ, newLines.empty() ? cordY : newLines[newLines.size() - 1].position_3d_y, curveCoeff, mainColor,
                    spriteNearLeft, spriteNearRight, spriteFarLeft, spriteFarRight, stepsRead, eachNearLeft, eachNearRight,
                    eachFarLeft, eachFarRight, startPos, codeNearLeft, codeNearRight, codeFarLeft, codeFarRight,
                    generateRandomNearLeft, generateRandomNearRight, generateRandomFarLeft, generateRandomFarRight);

        mainColor = !mainColor;
    }
}



LandScape::LandScape(const std::string path, bool random) : posX(0), posY(0), next(nullptr)
{
    Texture t;
    // Document xml where the document is going to be parsed
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *nodeLandScape = doc.first_node()->first_node();

    if ((string)nodeLandScape->name() == "Background"){
        bg.loadFromFile((string)nodeLandScape->value());
        bg.setRepeated(true);
    }
    nodeLandScape = nodeLandScape->next_sibling();
    if ((string)nodeLandScape->name() == "Sprites"){
        // Check the sprite paths of the level
        for (xml_node<> *sprite = nodeLandScape->first_node(); sprite; sprite = sprite->next_sibling()){
            t.loadFromFile(sprite->value());
            t.setSmooth(true);
            objects.push_back(t);

            // Load hit percentage from center
            float coeff = 1.0f;

            /*
            ifstream fin(path + s + ".info");
            if (fin.is_open()) {
                fin >> coeff;
                fin.close();
            }
            */

            hitCoeff.push_back(coeff);
        }
    }
    parseBackgroundScene(path);
}


void LandScape::addNextMap(LandScape *map) {
    this->next = map;
    float yOffset = 0.0f;
    if (!newLines.empty())
        yOffset = newLines[newLines.size() - 1].position_3d_y;
    this->next->setOffset(yOffset);
}


void LandScape::setOffset(float yOffset) {
    for (Step &l : newLines) {
        l.position_3d_y += yOffset;
    }
}


void LandScape::updateView(pair<float, float> pos) {
    this->posX = pos.first;
    this->posY = pos.second;
}


void drawQuad(RenderWindow* w, Color c, int x1, int y1, int w1, int x2, int y2, int w2) {
    ConvexShape shape(4);
    shape.setFillColor(c);
    shape.setPoint(0, Vector2f(x1, y1));
    shape.setPoint(1, Vector2f(x2, y2));
    shape.setPoint(2, Vector2f(x2 + w2, y2));
    shape.setPoint(3, Vector2f(x1 + w1, y1));
    w->draw(shape);
}


void LandScape::draw(RenderWindow* app, Configuration* c) {
    Step *l = getLine(int(posY)), *p;
    int N = newLines.size();

    // Background
    drawQuad(app, grassColor[0], 0, 0, app->getSize().x, 0, app->getSize().y, app->getSize().x);
    Sprite sbg;
    sbg.setTexture(bg);
    sbg.setScale(Vector2f(2.0f * (float)app->getSize().x / bg.getSize().x, (float)app->getSize().y * BGS / bg.getSize().y));
    sbg.setPosition(0, 0);
    sbg.move(-sbg.getGlobalBounds().width / 3.0f - posX, 0);
    if (l->directionCurve > 0.0f)
        sbg.move(0.05 / 2.0f, 0);
    else if (l->directionCurve < 0.0f)
        sbg.move(-0.05 / 2.0f, 0);
    app->draw(sbg);

    int startPos = int(posY) % N;
    float camH = l->position_3d_y + 1500.0f;

    float maxy = app->getSize().y;
    float x = 0, dx = 0;

    ///////draw road////////
    for (int n = startPos; n < startPos + 300; n++) {
        l = getLine(n);

        l->project(posX * ROADW - x, camH, float(startPos * (segL - 50)), 0.84,
                  app->getSize().x, app->getSize().y, ROADW, n < N ? 0.0f : newLines[newLines.size() - 1].position_3d_z);
        x += dx;
        dx += l->directionCurve;

        l->clip = maxy;
        if (l->position_2d_y < maxy) {
            maxy = l->position_2d_y;

            Color grass, road, rumble, dash, dashMedLeft, dashMedRight;

            if (n < N || next == nullptr) {
                grass = grassColor[l->mainColor];
                road = roadColor[l->mainColor];
                rumble = rumbleColor[l->mainColor];
            }
            else {
                grass = next->grassColor[l->mainColor];
                road = next->roadColor[l->mainColor];
                rumble = next->rumbleColor[l->mainColor];
            }
            dash = l->mainColor ? rumbleColor[0] : rumbleColor[1];
            dashMedLeft = l->mainColor ? road : Color::White;
            dashMedRight = l->mainColor ? road : Color::White;

            p = getPreviousLine(n);

            // Draw grass
            drawQuad(app, grass, 0, int(p->position_2d_y), app->getSize().x, 0, int(l->position_2d_y), app->getSize().x);

            // Draw road
            const int x1 = int(p->position_2d_x - p->position_2d_w), y1 = int(p->position_2d_y), w1 = int(2.0f * p->position_2d_w),
                      x2 = int(l->position_2d_x - l->position_2d_w), y2 = int(l->position_2d_y), w2 = int(2.0f * l->position_2d_w),
                      rw1 = int(p->position_2d_w * RUMBLECOEFF), rw2 = int(l->position_2d_w * RUMBLECOEFF),
                      dw1 = rw1 / 2, dw2 = rw2 / 2;
            drawQuad(app, road, x1, y1, w1, x2, y2, w2);
            drawQuad(app, rumble, x1, y1, rw1, x2, y2, rw2); // Left rumble
            drawQuad(app, rumble, x1 + w1 - rw1, y1, rw1, x2 + w2 - rw2, y2, rw2); // Right rumble
            drawQuad(app, dash, x1 + rw1, y1, dw1, x2 + rw2, y2, dw2); // First left dash
            drawQuad(app, dash, x1 + w1 - rw1 - dw1, y1, dw1, x2 + w2 - rw2 - dw2, y2, dw2); // First right dash
            drawQuad(app, dashMedLeft, x1 + int(float(w1) * 0.333f), y1, dw1, x2 + int(float(w2) * 0.333f), y2, dw2); // Second left dash
            drawQuad(app, dashMedRight, x1 + int(float(w1) * 0.666f), y1, dw1, x2 + int(float(w2) * 0.666f), y2, dw2); // Second right dash
        }
    }

    ////////draw objects////////
    for (int n = int(posY); n < int(posY) + 300; n++) { // Reset draw info
        l = getLine(n);
        l->spriteNearLeft.spriteMinX = 0;
        l->spriteNearLeft.spriteMaxX = 0;
        l->spriteNearRight.spriteMinX = 0;
        l->spriteNearRight.spriteMaxX = 0;
    }

    for (int n = startPos + c->getRenderLen(); n > startPos; n--) {
        l = getLine(n);

        if (l->spriteNearLeft.spriteNum > -1) {
            if (n < N || next == nullptr)
                l->drawSprite(app, objects, hitCoeff, l->spriteNearLeft, true);
            else
                l->drawSprite(app, next->objects, next->hitCoeff, l->spriteNearLeft, true);
        }
        if (l->spriteNearRight.spriteNum > -1) {
            if (n < N || next == nullptr)
                l->drawSprite(app, objects, hitCoeff, l->spriteNearRight, false);
            else
                l->drawSprite(app, next->objects, next->hitCoeff, l->spriteNearRight, false);
        }
        if (l->spriteFarLeft.spriteNum > -1) {
            if (n < N || next == nullptr)
                l->drawSprite(app, objects, hitCoeff, l->spriteFarLeft, true);
            else
                l->drawSprite(app, next->objects, next->hitCoeff, l->spriteFarLeft, true);
        }
        if (l->spriteFarRight.spriteNum > -1) {
            if (n < N || next == nullptr)
                l->drawSprite(app, objects, hitCoeff, l->spriteFarRight, false);
            else
                l->drawSprite(app, next->objects, next->hitCoeff, l->spriteFarRight, false);
        }
    }
}


bool LandScape::hasGotOut(float currentX) const {
    return abs(currentX) > 1.0f;
}

float LandScape::getCurveCoefficient(float currentY) const {
    return getLine(int(currentY)).directionCurve;
}

Elevation LandScape::getElevation(float currentY) const {
    const int n = int(currentY);
    const Step currentLine = getLine(n);
    const Step prevLine = getPreviousLine(n);
    if (n != 0 && abs(currentLine.position_3d_y) > 1000 && currentLine.position_3d_y > prevLine.position_3d_y + 1.0f)
        return UP;
    else if (n != 0 && abs(currentLine.position_3d_y) > 1000 && currentLine.position_3d_y < prevLine.position_3d_y - 1.0f)
        return DOWN;
    else
        return FLAT;
}

bool LandScape::isOver() const {
    return posY >= newLines.size();
}


