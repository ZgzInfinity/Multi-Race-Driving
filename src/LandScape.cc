

#include "../include/LandScape.h"


using namespace rapidxml;


/**
 * Constructor of the data type
 * @param path is the path of the xml file which contains the scene to render
 */
LandScapeNew::LandScapeNew(char* path){
    // Document xml where the document is going to be parsed
    xml_document<> doc;
    file<> file(path);
    // Parsing the content of file
    doc.parse<0>(file.data());

    // Get the principal node of the file
    xml_node<> *nodeCircuit = doc.first_node();

    // Loop in order to iterate all the children of the principal node
    for (xml_node<> *child = nodeCircuit->first_node(); child; child = child->next_sibling()){
        // Process the child node found
        // Check if it's the node that contains the name of the circuit
        if ((string)child->name() == "Name"){
            // Store the name of the circuit
            name = child->value();
            continue;
        }
        // Check if it's the node that contains the information of the background
        else if ((string)child->name() == "Background"){
            // Parse the background information of the file
            parseBackgroundScene(child);
            continue;
        }
        // Check if it's the node that contains the different sprites of the scene
        else if ((string)child->name() == "Sprites"){
            // Parse the sprites of the landscape
            parseSpritesScene(child);
            continue;
        }
        // Check if it's the node that contains the different curves of the scene
        else if ((string)child->name() == "Curves"){
            // Parse the information of the curves of the xml file
            parseCurvesScene(child);
            continue;
        }
        // Check if it's the node that contains the different mountains of the scene
        else if ((string)child->name() == "Mountains"){
            // Parse the information of the mountains of the xml file
            parseMountainsScene(child);
            continue;
        }
        // Check if it's the node that contains the different colors of the road
        else if ((string)child->name() == "Color_road"){
            // Parse the information of the color of the road
            parseColorRoadScene(child);
            continue;
        }
        // Check if it's the node that contains the different colors of the grass
        else if ((string)child->name() == "Color_grass"){
            parseColorGrassScene(child);
            continue;
        }
        // Check if it's the node that contains the different colors of the rumble
        else if ((string)child->name() == "Color_rumble"){
            // Parse the information of the color rumble of the road
            parseColorRumbleScene(child);
            continue;
        }
         // Check if it's the node that contains the different colors of the middle
        else if ((string)child->name() == "Color_middle"){
            // Parse the information of the color middle of the road
            parseColorMiddleScene(child);
            continue;
        }
    }
    // Order the curves in the landScape
    orderElementsInLandScape();

    // Rendering all the landscape
    renderLandScape();
}



/**
 * Get the sprite which contains the background
 */
Sprite LandScapeNew::getBackGround(){
    return sBackground;
}



/**
 * Assigns the sprite of the background
 * @param sBack is the sprite which contains the background to assign
 */
void LandScapeNew::setBackGround(Sprite sBack){
    sBackground = sBack;
}



/**
 * Parses all the configuration of the background written in the xml
 * configuration file of the scene
 * @param child is a node of the xml file that points to the background information
 */
inline void LandScapeNew::parseBackgroundScene(xml_node<> * child){
    // Get the value of the path node if it exists
    string path;
    // Coordinates of the rectangle that contains the background and its center
    int LLcord, ULcord, LRcord, URcord, xCenter, yCenter;
    // Loop in order to iterate all the the children of the node Background
    for (xml_node<> *grandchild = child->first_node(); grandchild; grandchild = grandchild->next_sibling()){
        // Check the path of the background image
        if ((string)grandchild->name() == "Path"){
            // Store the name of the circuit
            path = grandchild->value();
            continue;
        }
        // Check the lower left coordinate of the background image
        else if ((string)grandchild->name() == "LL"){
            // Store the lower left coordinate
            LLcord = stoi(grandchild->value());
            continue;
        }
        // Check the upper left coordinate of the background image
        else if ((string)grandchild->name() == "UL"){
            // Store the upper left coordinate
            ULcord = stoi(grandchild->value());
            continue;
        }
        // Check the upper right coordinate of the background image
        else if ((string)grandchild->name() == "LR"){
            // Store the lower right coordinate
            LRcord = stoi(grandchild->value());
            continue;
        }
        // Check the upper right coordinate of the background image
        else if ((string)grandchild->name() == "UR"){
            // Store the upper right coordinate
            URcord = stoi(grandchild->value());
            continue;
        }
        // Check the image center in axis X
        else if ((string)grandchild->name() == "Xcenter"){
            // Store the center of the image in the axis X
            xCenter = stoi(grandchild->value());
            continue;
        }
        // Check the image center in axis Y
        else if ((string)grandchild->name() == "Ycenter"){
            // Store the center of the image in the axis Y
            yCenter = stoi(grandchild->value());
        }
    }
    // All the attributes to configure the background are correct
    loadBackground(path, LLcord, ULcord, LRcord, URcord, xCenter, yCenter);
}



/**
 * Get the interval coordinates of any element of the scene
 * @param child is a pointer to the xml fils that points to a curve, mountain or sprite
 * @param objectCode controls what kind of element is been processed
 * @param startPos is going to store the initial interval position of the element of the scene
 * @param finalPos is going to store the initial interval position of the element of the scene
 */
inline void LandScapeNew::getIntervalCoordinates(xml_node<> *child, int objectCode, int& startPos, int& finalPos){
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
 * Parses all the information referent to the sprites of the landscape
 * @param child is a pointer to a node of the xml file that contains the all the
 * information of the sprites
 */
inline void LandScapeNew::parseSpritesScene(xml_node<> * child){
    // Established the code number to indicate that curves are in process
    int objectCode = 1;
    // Loop in order to iterate all the children of the Sprite node
    int spritesRead = 0;
    // Variable to store the possible attributes
    xml_attribute<>* attr;
    // Variables to control the interval position of the sprite
    int startPos, finalPos;
    // Loop in order to iterate the sprites of all the scene
    for (xml_node<> *grandchild = child->first_node(); grandchild; grandchild = grandchild->next_sibling()){
        // Increment the number of sprites read
        spritesRead++;
        // Read the path attribute of the sprite
        attr = grandchild->first_attribute("id");
        string id = (attr != nullptr) ? attr->value() : "Unknown";
        // Check if the attribute id is or not in the file
        if (id == "Unknown"){
            cerr << "Unknown id for the sprite " <<  spritesRead << endl;
            exit(8);
        }
        else {
            // Iteration in the fields of the sprite
            for (xml_node<> *spriteNode = grandchild->first_node(); spriteNode; spriteNode = spriteNode->next_sibling()){
                if ((string)spriteNode->name() == "Path"){
                    // Store the path
                    spritePaths.push_back((string)spriteNode->value());
                    continue;
                }
                // Check the node interval of the sprite
                else if ((string)spriteNode->name() == "Interval"){
                    string frequency, xPos;
                    float posX;
                    // Loop throughout the intervals of the sprite
                    for (xml_node<> *intervalNode = spriteNode->first_node(); intervalNode; intervalNode = intervalNode->next_sibling()){
                        // Get the coordinates of the interval
                        getIntervalCoordinates(intervalNode, objectCode, startPos, finalPos);
                        // Loop for iterate the properties of the interval of the sprite
                        for (xml_node<> *newNode = intervalNode->first_node(); newNode; newNode = newNode->next_sibling()){
                            if ((string)newNode->name() == "Each"){
                                frequency = (string)newNode->value();
                                continue;
                            }
                            if ((string)newNode->name() == "Xpos"){
                                xPos = (string)newNode->value();
                            }
                            if (xPos != "Random"){
                                posX = stof(xPos);
                            }
                            else {
                                newNode = newNode->next_sibling();
                                if ((string)newNode->name() == "Margin"){
                                    if ((string)newNode->value() == "Left"){
                                        posX = -(rand() % 8 + 3.f);
                                    }
                                    else if ((string)newNode->value() == "Right"){
                                        posX = rand() % 8 + 3.f;
                                    }
                                    else {
                                        cerr << "Invalid specification in Margin attribute" << endl;
                                        exit(20);
                                    }
                                }
                            }
                        }
                        // Store the sprite of the scene with all its information
                        MapElement mE = MapElement(stoi(id), startPos, finalPos, stoi(frequency), posX);
                        elementsOfMap.push_back(mE);
                    }
                }
            }
        }
    }
}



/**
 * Parses all the configuration of the curves written in the xml configuration file of the scene
 * @param child is a node of the xml file that points to the curves information
 */
inline void LandScapeNew::parseCurvesScene(xml_node<> * child){
    // Established the code number to indicate that curves are in process
    int objectCode = 2;
    // Variables to control the intervals of the elements
    int startPos, finalPos;
    // Number of curves read already
    int curvesRead = 0;
    // Loop in order to iterate the curve nodes
    for (xml_node<> *grandchild = child->first_node(); grandchild; grandchild = grandchild->next_sibling()){
        // Increment the number of curves read
        curvesRead++;
        // Get interval coordinate of the sprite
        getIntervalCoordinates(grandchild, objectCode, startPos, finalPos);
        // Check the direction of the curve
        xml_node<> *nodeDirection = grandchild->first_node();
        if ((string)nodeDirection->name() == "Direction"){
            string direction = (string)nodeDirection->value();
            IntervalCurve iC = IntervalCurve(startPos, finalPos, stof(direction));
            curves.push_back(iC);
        }
        else {
            cerr << "Error, the direction of the curve " << curvesRead << "has not been specified " << endl;
            exit(1);
        }
    }
}



/**
 * Parses all the configuration of the mountains written in the xml configuration file of the scene
 * @param child is a node of the xml file that points to the mountains information
 */
inline void LandScapeNew::parseMountainsScene(xml_node<> * child){
    // Established the code number to indicate that mountains are in process
    int objectCode = 3;
    // Variables to control the intervals of the elements
    int startPos, finalPos;
    // Number of mountains read already
    int mountainsRead = 0;
    // Loop in order to iterate the curve nodes
    for (xml_node<> *grandchild = child->first_node(); grandchild; grandchild = grandchild->next_sibling()){
        // Increment the number of mountains read
        mountainsRead++;
        // Get interval coordinate of the sprite
        getIntervalCoordinates(grandchild, objectCode, startPos, finalPos);
        // Check the direction of the mountain
        xml_node<> *nodeAtenuation = grandchild->first_node();
        xml_node<> *nodeHeight = nodeAtenuation->next_sibling();
        float atenuation; int height;
        if ((string)nodeAtenuation->name() == "Atenuation"){
            atenuation = stof(nodeAtenuation->value());
        }
        else {
            cerr << "Error, the atenuation of the mountain " << mountainsRead << "has not been specified " << endl;
            exit(1);
        }
        if ((string)nodeHeight->name() == "Height"){
            height = stoi(nodeHeight->value());
        }
        else {
            cerr << "Error, the height of the mountain " << mountainsRead << "has not been specified " << endl;
            exit(1);
        }
        Mountain m = Mountain(startPos, finalPos, atenuation, height);
        mountains.push_back(m);
    }
}



/**
 * Parses all the configuration of the color of the road written in the xml
 * configuration file of the scene
 * @param child is a node of the xml file that points to the color of the road information
 */
inline void LandScapeNew::parseColorRoadScene(xml_node<> * child){
    // Colors of the three channels in RGB format
    int colorRed, colorGreen, colorBlue;
    // Loop in order to iterate throughout the color channels
    for (xml_node<> *grandchild = child->first_node(); grandchild; grandchild = grandchild->next_sibling()){
        // Check the upper right coordinate of the background image
        if ((string)grandchild->name() == "R"){
            // Store the lower right coordinate
            colorRed = stoi(grandchild->value());
            continue;
        }
        else if ((string)grandchild->name() == "G"){
            // Store the lower right coordinate
            colorGreen = stoi(grandchild->value());
            continue;
        }
        else if ((string)grandchild->name() == "B"){
            // Store the lower right coordinate
            colorBlue = stoi(grandchild->value());
        }
    }
    // Store the color of the road
    color_road = Color(colorRed, colorGreen, colorBlue);
}



/**
 * Parses all the configuration of the color of the road written in the xml
 * configuration file of the scene
 * @param child is a node of the xml file that points to the color of the grass information
 */
inline void LandScapeNew::parseColorGrassScene(xml_node<> * child){
    int colorRed, colorGreen, colorBlue;
    // Loop in order to iterate throughout the colors of the grass
    for (xml_node<> *color_node = child->first_node(); color_node; color_node = color_node->next_sibling()){
        // Loop for iterate the three color channels in RGB format
        for (xml_node<> *color = color_node->first_node(); color; color = color->next_sibling()){
            parseColors(color, colorRed, colorGreen, colorBlue);
        }
        colors_grass.push_back(Color(colorRed, colorGreen, colorBlue));
    }
}



/**
 * Parses all the configuration of the color of the rumble of the road written in the xml
 * configuration file of the scene
 * @param child is a node of the xml file that points to the color of the rumble of road information
 */
inline void LandScapeNew::parseColorRumbleScene(xml_node<> * child){
    int colorRed, colorGreen, colorBlue;
    // Loop in order to iterate throughout the colors of the rumble of the road
    for (xml_node<> *color_node = child->first_node(); color_node; color_node = color_node->next_sibling()){
        // Loop for iterate the three color channels in RGB format
        for (xml_node<> *color = color_node->first_node(); color; color = color->next_sibling()){
            // Store the color of the road
            parseColors(color, colorRed, colorGreen, colorBlue);
        }
        colors_rumble.push_back(Color(colorRed, colorGreen, colorBlue));
    }
}



/**
 * Parses all the configuration of the color of the middle of the road written in the xml
 * configuration file of the scene
 * @param child is a node of the xml file that points to the color of the middle of the road information
 */
inline void LandScapeNew::parseColorMiddleScene(xml_node<> * child){
    int colorRed, colorGreen, colorBlue;
    // Loop in order to iterate throughout the colors of the middle of the road
    for (xml_node<> *color_node = child->first_node(); color_node; color_node = color_node->next_sibling()){
        // Loop for iterate the three color channels in RGB format
        for (xml_node<> *color = color_node->first_node(); color; color = color->next_sibling()){
            // Store the color of the road
            parseColors(color, colorRed, colorGreen, colorBlue);
        }
        colors_middle.push_back(Color(colorRed, colorGreen, colorBlue));
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
inline void LandScapeNew::parseColors(xml_node<> * color, int& colorRed, int& colorGreen, int& colorBlue){
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



/**
 * Renders all the landscape with all the elements already parsed and stored
 */
inline void LandScapeNew::renderLandScape(){
    // Iterate throw the vector of curves of the landscape in 2d
    for (IntervalCurve iC : curves){
        // Add the curve in 3d coordinates
        IntervalCurve iCin3d = IntervalCurve(iC.startCurvePosition * segL, iC.finalCurvePosition * segL, iC.directionCurve);
        // Necessary to control the inertia force
        curvesInScene.push_back(iCin3d);
    }
    for (int i = 0; i < MAX_ELEMENTS; i++){
        textures[i] = false;
    }
    // All the curves have been processed correctly
    for (int i = 0; i < MAX_SPACE_DIMENSION - 1; i++){
        // Store the curves in the scene
        lines[i].position_3d_z = i * segL;
        printCurves(i);
        printMountains(i);
        printSprites(i);
        lines.push_back(lines[i]);
    }
}



/**
 * Load the background of the landscape
 */
inline void LandScapeNew::loadBackground(const string path, const int lowerLeft, const int upperLeft,
                                  const int lowerRight, const int upperRight, const int x_center,
                                  const int y_center)
{
    bg.loadFromFile(path);
    // Set repetition of texture active and assignation
    bg.setRepeated(true);
    sBackground.setTexture(bg);
    // Fix the dimensions of the rectangle which contains the texture
    sBackground.setTextureRect(IntRect(lowerLeft, upperLeft, lowerRight, upperRight));
    // Assign the position of the texture
    sBackground.setPosition(x_center, y_center);
}



/**
 * Get the element of the map which the nearest to the actual position
 * @param position_axis_Y is the actual coordinate of the player in the axis Y
 */
Step LandScapeNew::checkingPossibleCollision(const int position_axis_Y){
    // Indexes of the binary search
    int init = 0, last = stepsWithSprite.size() - 1, medium;
    // Loop for find the sprite
    while (init != last){
        // Central sprite obtained
        medium = (init + last) / 2;
        // Check if the last sprite is on the left or on the right
        if (stepsWithSprite.at(medium).spriteY <= position_axis_Y){
            // Right
            init = medium + 1;
        }
        else {
            // Left
            last = medium;
        }
    }
    // Check if the last sprite passed is in the same position of the motorbike
    if (stepsWithSprite.at(init).spriteY == position_axis_Y){
        // Get that sprite
        return stepsWithSprite.at(init - 1);
    }
    else {
        // Get the last found because the collision could have occurred during the movement
        return stepsWithSprite.at(init - 1);
    }
}



/**
 * Determines if there is a curve to print or not in the position of the map pos
 * @param pos is the position of the map to evaluate if there is a curve or not
 * @param curve is the possible curve in which interval of coordinates is located pos
 * @param exists is a boolean to control if there is curve to print or not in the position of the map pos
 */
void LandScapeNew::lookForCurveToPrint(int& pos, IntervalCurve& curve, bool& exist){
    // Defect value of the boolean variable
    exist = false;
    // Indexes of the binary search
    int init = 0, last = curves.size() - 1, medium;
    // Loop for find the sprite
    while (init <= last){
        // Central sprite obtained
        medium = (init + last) / 2;
        // Check if the last sprite is on the left or on the right
        if (pos >= curves.at(medium).startCurvePosition &&
            pos <= curves.at(medium).finalCurvePosition)
        {
            // Right
            exist = true;
            break;
        }
        else if (pos > curves.at(medium).startCurvePosition &&
                 pos > curves.at(medium).startCurvePosition)
        {
            // Left
            init = medium + 1;
        }
        else if (pos < curves.at(medium).startCurvePosition &&
                 pos < curves.at(medium).finalCurvePosition)
        {
            last = medium - 1;
        }
    }
    // Check if the last sprite passed is in the same position of the motorbike
    if (exist){
        // Get that sprite
        curve = curvesInScene.at(medium);
    }
}



/**
 * Determines if there is a curve or not in the position of the map pos
 * @param pos is the position of the map to evaluate if there is a curve or not
 * @param curve is the possible curve in which interval of coordinates is located pos
 * @param exists is a boolean to control if there is curve or not in the position of the map pos
 */
void LandScapeNew::lookForCurve(int& pos, IntervalCurve& curve, bool& exist){
    // Defect value of the boolean variable
    exist = false;
    // Indexes of the binary search
    int init = 0, last = curves.size() - 1, medium;
    // Loop for find the sprite
    while (init <= last){
        // Central sprite obtained
        medium = (init + last) / 2;
        // Check if the last sprite is on the left or on the right
        if (pos >= curvesInScene.at(medium).startCurvePosition &&
            pos <= curvesInScene.at(medium).finalCurvePosition)
        {
            // Right
            exist = true;
            break;
        }
        else if (pos > curvesInScene.at(medium).startCurvePosition &&
                 pos > curvesInScene.at(medium).startCurvePosition)
        {
            // Left
            init = medium + 1;
        }
        else if (pos < curvesInScene.at(medium).startCurvePosition &&
                 pos < curvesInScene.at(medium).finalCurvePosition)
        {
            last = medium - 1;
        }
    }
    // Check if the last sprite passed is in the same position of the motorbike
    if (exist){
        // Get that sprite
        curve = curvesInScene.at(medium);
    }
}



/**
 * Determines if there is a mountain or not in the position of the map pos
 * @param pos is the position of the map to evaluate if there is a mountain or not
 * @param m is the possible mountain in which interval of coordinates is located pos
 * @param exists is a boolean to control if there is mountain or not in the position of the map pos
 */
void LandScapeNew::lookForMountain(int& pos, Mountain& m, bool& exist){
    // Defect value of the boolean variable
    exist = false;
    // Indexes of the binary search
    int init = 0, last = mountains.size() - 1, medium;
    // Loop for find the sprite
    while (init <= last){
        // Central sprite obtained
        medium = (init + last) / 2;
        // Check if the last sprite is on the left or on the right
        if (pos >= mountains.at(medium).startMountainPos &&
            pos <= mountains.at(medium).finalMountainPos)
        {
            // Right
            exist = true;
            break;
        }
        else if (pos > mountains.at(medium).startMountainPos &&
                 pos > mountains.at(medium).startMountainPos)
        {
            // Left
            init = medium + 1;
        }
        else if (pos < mountains.at(medium).startMountainPos &&
                 pos < mountains.at(medium).finalMountainPos)
        {
            last = medium - 1;
        }
    }
    // Check if the last sprite passed is in the same position of the motorbike
    if (exist){
        // Get that sprite
        m = mountains.at(medium);
    }
}



/**
 * Determines if there is a mountain or not in the position of the map pos
 * @param m is a vector where all the possible sprites to print are going to be kept
 * @param exists is a boolean to control if there are sprites or not in the position of the map pos
 */
void LandScapeNew::lookForMapElement(int& pos, vector<MapElement>& m, bool& exist){
    // Defect value of the boolean variable
    for (MapElement mE : elementsOfMap){
        // Check if the pos is in the interval of a sprite
        if (pos >= mE.startPosition && pos <= mE.finalPosition){
            // Add to the list of intervals of sprites
            m.push_back(mE);
            // Update the control of interval found only one time
            if (!exist){
                // Updated the control of sprite intervals
                exist = true;
            }
        }
    }

}



/**
 * Order the curves and the mountains of the map using the coordinates of the map X and Y
 */
void LandScapeNew::orderElementsInLandScape(){
    // Ordenation of the vector
    sort(curves.begin(), curves.end());
    sort(curvesInScene.begin(), curvesInScene.end());
    sort(mountains.begin(), mountains.end());
}



/**
 * Print the possible curve of the map which can be stored in the position of the map i
 * @param i is the step or position index of the map where is going to be evaluated if
 * there is or not curve
 */
void LandScapeNew::printCurves(int i){
    // Variables to make the search of the curve
    IntervalCurve curve;
    // Control if the coordinate i is in a curve or not
    bool exits = false;
    // Check if the curve is on the vector of curves of the scene
    lookForCurveToPrint(i, curve, exits);
    // If it's in a curve
    if (exits){
        lines[i].directionCurve = curve.directionCurve;
    }
}



/**
 * Print the possible mountain of the map which can be stored in the position of the map i
 * @param i is the step or position index of the map where is going to be evaluated if
 * there is or not mountain
 */
void LandScapeNew::printMountains(int i){
    // Variables to make the search of the curve
    Mountain m;
    // Control if the coordinate i is in a curve or not
    bool exits = false;
    // Check if the curve is on the vector of curves of the scene
    lookForMountain(i, m, exits);
    // If it's in a curve
    if (exits){
        lines[i].position_3d_y = sin(i / m.atenuationMountain) * m.heightMountain;
    }
}



/**
 * Print the possible sprite of the map which can be stored in the position of the map i
 * @param i is the step or position index of the map where is going to be evaluated if
 * there is or not sprite
 */
void LandScapeNew::printSprites(int i){
    // Variables to make the search of the curve
    vector<MapElement> m;
    // Control if the coordinate i is in a curve or not
    bool exits = false;
    // Check if the curve is on the vector of curves of the scene
    lookForMapElement(i, m, exits);

    if (exits){
        for (MapElement mE : m){
            // Check if the texture has been loaded already before
            if (!textures[mE.id - 1]){
                // Load the texture with the sprite
                // Load textures and sprites of the game
                t[mE.id - 1].loadFromFile(spritePaths.at(mE.id - 1));
                t[mE.id - 1].setSmooth(true);
                object[mE.id - 1].setTexture(t[mE.id - 1]);
                textures[mE.id - 1] = true;
            }
            // If it's in a curve
            if (i % mE.each == 0){
                lines[i].spriteX = mE.xPos;
                lines[i].spriteY = i * segL;
                lines[i].character = object[mE.id - 1];
                if (lines[i].spriteX > 0.f){
                    lines[i].offset = lines[i].spriteX - 1.2f;
                }
                else {
                    lines[i].offset = lines[i].spriteX + 1.2f;
                }
                // Adding the step with the sprite and its coordinates to the list
                stepsWithSprite.push_back(lines[i]);
            }
        }
    }
}



/**
 * Render the landscape appearance and the step of the map
 * @param n is the index of the map position to be processed
 * @param grass is the color which is going to be used to paint the grass of the scene
 * @param rumble is the color which is going to be used to paint the rumble of the scene
 * @param middle is the color which is going to be used to paint the middle road of the scene
 * @param road is the color which is going to be used to paint the road of the scene
 */
void LandScapeNew::paintScene(const int n, Color& grass, Color& rumble, Color& middle, Color& road){
    // Determination of the color to paint in the screen
    if ((n / 5) % 2){
        grass = colors_grass.at(0);
        rumble = colors_rumble.at(0);
        middle = colors_middle.at(0);
    }
    else {
        grass = colors_grass.at(1);
        rumble = colors_rumble.at(1);
        middle = colors_middle.at(1);
    }
    road = color_road;
}

