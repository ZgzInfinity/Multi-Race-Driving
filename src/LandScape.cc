

#include "../include/LandScape.h"

using namespace rapidxml;


/**
 * Constructor of the data type
 * @param path is the path of the xml file which contains the scene to render
 */
LandScape::LandScape(char* path){
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
        // Check if it's the node that contains the checkpoints of the level
        else if ((string)child->name() == "Checkpoint"){
            // Parse the information referent to the checkpoints of the levels
            parseCheckpoints(child);
            continue;
        }
        // Check if it's the node that contains the star point of the level
        else if ((string)child->name() == "StartingPoint"){
            // Parse the information referent to the start point of the levels
            parseStartPoint(child);
            continue;
        }
        // Check if it's the node that contains the goal point of the level
        else if ((string)child->name() == "GoalPoint"){
            // Parse the information referent to the goal point of the levels
            parseGoalPoint(child);
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
Sprite LandScape::getBackGround(){
    return sBackground;
}



/**
 * Assigns the sprite of the background
 * @param sBack is the sprite which contains the background to assign
 */
void LandScape::setBackGround(Sprite sBack){
    sBackground = sBack;
}



/**
 * Parses all the configuration of the background written in the xml
 * configuration file of the scene
 * @param child is a node of the xml file that points to the background information
 */
inline void LandScape::parseBackgroundScene(xml_node<> * child){
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
 * Parses all the information referent to the sprites of the landscape
 * @param child is a pointer to a node of the xml file that contains the all the
 * information of the sprites
 */
inline void LandScape::parseSpritesScene(xml_node<> * child){
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
inline void LandScape::parseCurvesScene(xml_node<> * child){
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
inline void LandScape::parseMountainsScene(xml_node<> * child){
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
 * Parses the configuration of the checkpoints of the scene which stored in its configuration file
 * @param child is a node of the xml file that points to the mountains information
 * @param path is the relative path of the image that contains the image of the checkpoint
 */
inline void LandScape::parseCheckpoints(xml_node<> * child){
    // Variables to store the attributes of the checkpoint
    float posX; int stepPosition, checkpointsRead = 0; string path;
    // Iterate throughout the different checkpoints of the scene
    for (xml_node<> *checkpointNode = child->first_node(); checkpointNode; checkpointNode = checkpointNode->next_sibling()){
        // Increment the number of checkpoints read
        checkpointsRead++;
        // Check the attribute path of the file
        if ((string)checkpointNode->name() == "Path"){
            // Store the step of the checkpoint
            path = checkpointNode->value();
            continue;
        }
        // Looping parsing the information contained in its tag fields
        for (xml_node<> *actualCheckpoint = checkpointNode->first_node(); actualCheckpoint; actualCheckpoint = actualCheckpoint->next_sibling()){
            // Getting all the information of the checkpoint
            if ((string)actualCheckpoint->name() == "Position"){
                // Store the step of the checkpoint
                stepPosition = stoi(actualCheckpoint->value());
                continue;
            }
            if ((string)actualCheckpoint->name() == "Xpos"){
                // Store the position of the checkpoint in the axis X
                posX = stof(actualCheckpoint->value());
            }
        }
        // Store the checkpoint read into the vector
        Checkpoint c = Checkpoint(path, posX, stepPosition);
        checkpointsScene.push_back(c);
    }
}



/**
 * Parses the information referent to the starting point of the scene
 * @param child is a node pointer of the xml configuration file that points to the
 * data of the starting point
 */
inline void LandScape::parseStartPoint(xml_node<> * child){
    // Variables to control the information of the starting point
    string path; float xPos; int stepPosition;
    // Loop that iterates in all the attributes of the staring point
    for (xml_node<> *grandchild = child->first_node(); grandchild; grandchild = grandchild->next_sibling()){
        // Check if the starting goal point has the attribute path
        if ((string)grandchild->name() == "Path" ){
            // Store the path of the starting point
            path = grandchild->value();
            continue;
        }
        // Check if the starting goal point has the attribute position
        else if ((string)grandchild->name() == "Position" ){
            // Store the step of the map where is the starting point
            stepPosition = stoi(grandchild->value());
            continue;
        }
        // Check if the starting point has the attribute Xpos
        else if ((string)grandchild->name() == "Xpos" ){
            // Store the position of the starting point in the axis X
            xPos = stof(grandchild->value());
        }
    }

    // Store the starting point data recovered
    startPoint = StartingPoint(path, xPos, stepPosition);
}



/**
 * Parses the information referent to the goal point of the scene
 * @param child is a node pointer of the xml configuration file that points to the
 * data of the goal point
 */
inline void LandScape::parseGoalPoint(xml_node<> * child){
    // Variables to control the information of the starting point
    string path; float xPos; int stepPosition;
    // Loop that iterates in all the attributes of the goal point
    for (xml_node<> *grandchild = child->first_node(); grandchild; grandchild = grandchild->next_sibling()){
        // Check if the goal goal point has the attribute path
        if ((string)grandchild->name() == "Path" ){
            // Store the path of the goal point
            path = grandchild->value();
            continue;
        }
        // Check if the goal point has the attribute position
        else if ((string)grandchild->name() == "Position" ){
            // Store the step of the map where is the goal point
            stepPosition = stoi(grandchild->value());
            continue;
        }
        // Check if the goal goal point has the attribute Xpos
        else if ((string)grandchild->name() == "Xpos" ){
            // Store the position of the goal point in the axis X
            xPos = stof(grandchild->value());
        }
    }

    // Store the goal point data recovered
    goalPoint = GoalPoint(path, xPos, stepPosition);
}



/**
 * Parses all the configuration of the color of the road written in the xml
 * configuration file of the scene
 * @param child is a node of the xml file that points to the color of the road information
 */
inline void LandScape::parseColorRoadScene(xml_node<> * child){
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
inline void LandScape::parseColorGrassScene(xml_node<> * child){
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
inline void LandScape::parseColorRumbleScene(xml_node<> * child){
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
inline void LandScape::parseColorMiddleScene(xml_node<> * child){
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



/**
 * Renders all the landscape with all the elements already parsed and stored
 */
inline void LandScape::renderLandScape(){
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
        printCheckpoints(i);
        printStartingPoints(i);
        printGoalPoints(i);
        lines.push_back(lines[i]);
    }
}



/**
 * Load the background of the landscape
 */
inline void LandScape::loadBackground(const string path, const int lowerLeft, const int upperLeft,
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
Step LandScape::checkingPossibleCollision(const int position_axis_Y){
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
void LandScape::lookForCurveToPrint(int& pos, IntervalCurve& curve, bool& exist){
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
void LandScape::lookForCurve(int& pos, IntervalCurve& curve, bool& exist){
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
void LandScape::lookForMountain(int& pos, Mountain& m, bool& exist){
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
void LandScape::lookForMapElement(int& pos, vector<MapElement>& m, bool& exist){
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
 * Determines if there is checkpoint or not in the actual step of the map
 * @param step is the actual step of the map where is going to be evaluated if there
 * is or not checkpoint
 * @param c is the possible checkpoint that can be in the actual step of the map
 * @param exists is a boolean that controls if there is or not a checkpoint in the actual step
 */
void LandScape::lookForCheckpoint(int& step, Checkpoint& c, bool& exists){
    // Limits of the search
    int start = 0, last = checkpointsScene.size() - 1, medium;
    // Binary search
    while (start != last){
        // Calculation of the center element of the search
        medium = (start + last) / 2;
        if (checkpointsScene[medium].stepPosition < step){
            // Look for the possible checkpoint in the right
            start = medium + 1;
        }
        else {
            // Look for the possible checkpoint in the left
            last = medium;
        }
    }
    // Check if the final checkpoint get is the solution
    if (checkpointsScene[start].stepPosition == step){
        // Correct
        exists = true;
        // Assign the checkpoint
        c = checkpointsScene[start];
    }
    else {
        // Control if there is checkpoint in the actual step or not
        exists = false;
    }
}



/**
 * Order the curves and the mountains of the map using the coordinates of the map X and Y
 */
void LandScape::orderElementsInLandScape(){
    // Ordenation of the vector
    sort(curves.begin(), curves.end());
    sort(curvesInScene.begin(), curvesInScene.end());
    sort(mountains.begin(), mountains.end());
    sort(checkpointsScene.begin(), checkpointsScene.end());
}



/**
 * Print the possible curve of the map which can be stored in the position of the map i
 * @param i is the step or position index of the map where is going to be evaluated if
 * there is or not curve
 */
void LandScape::printCurves(int i){
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
void LandScape::printMountains(int i){
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
void LandScape::printSprites(int i){
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
 * Print the possible checkpoint of the map which can be stored in the position of the map i
 * @param i is the step or position index of the map where is going to be evaluated if
 * there is or not a checkpoint
 */
void LandScape::printCheckpoints(int i){
    // Variables to make the search of the curve
    Checkpoint c;
    // Control if the coordinate i there is a checkpoint or not
    bool exits = false;
    // Check if the curve is on the vector of curves of the scene
    lookForCheckpoint(i, c, exits);
    // If there is a checkpoint
    if (exits){
        // Load the texture and save it into a sprite
        if (tCheckpoint.loadFromFile(c.path)){
            // Set the texture of the sprite
            lines[i].character.setTexture(tCheckpoint);
            lines[i].spriteX = c.posX;
        }
    }
}



/**
 * Print the possible checkpoint of the map which can be stored in the position of the map i
 * @param i is the step or position index of the map where is going to be evaluated if
 * there is or not a checkpoint
 */
void LandScape::printStartingPoints(int i){
    // Check if it's the same step of the scene where the starting point is
    if (startPoint.stepPosition == i){
        // Load the texture and save it into a sprite
        if (tStartingPoint.loadFromFile(startPoint.path)){
            // Set the texture of the starting point
            lines[i].character.setTexture(tStartingPoint);
            lines[i].spriteX = startPoint.posX;
        }
    }
}



/**
 * Print the possible checkpoint of the map which can be stored in the position of the map i
 * @param i is the step or position index of the map where is going to be evaluated if
 * there is or not a checkpoint
 */
void LandScape::printGoalPoints(int i){
    // Check if it's the same step of the scene where the starting point is
    if (goalPoint.stepPosition == i){
        // Load the texture and save it into a sprite
        if (tGoalPoint.loadFromFile(goalPoint.path)){
            // Set the texture of the starting point
            lines[i].character.setTexture(tGoalPoint);
            lines[i].spriteX = startPoint.posX;
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
void LandScape::paintScene(const int n, Color& grass, Color& rumble, Color& middle, Color& road){
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



void LandScape::addLine(float x, float y, float &z, float prevY, float curve, bool mainColor,
                        const Step::SpriteInfo &spriteLeft, const Step::SpriteInfo &spriteRight)
{
    float yInc = (y - prevY) / 5.0f; // 5 is total lines number will be added
    Step line, lineAux;
    line.position_3d_x = x;
    line.position_3d_y = prevY;
    line.mainColor = mainColor;
    line.directionCurve = curve;

    lineAux = line; // without objects

    line.spriteLeft = spriteLeft;
    line.spriteRight = spriteRight;

    // For each normal line, 4 extras without objects for better visualization
    lineAux.position_3d_z = z;
    z += segL - 50;
    lineAux.position_3d_y += yInc;
    newLines.push_back(lineAux);

    lineAux.position_3d_z = z;
    z += segL - 50;
    lineAux.position_3d_y += yInc;
    newLines.push_back(lineAux);

    line.position_3d_z = z;
    z += segL - 50;
    lineAux.position_3d_y += yInc;
    line.position_3d_y = lineAux.position_3d_y;
    newLines.push_back(line);

    lineAux.position_3d_z = z;
    z += segL - 50;
    lineAux.position_3d_y += yInc;
    newLines.push_back(lineAux);

    lineAux.position_3d_z = z;
    z += segL - 50;
    lineAux.position_3d_y += yInc;
    newLines.push_back(lineAux);
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

void LandScape::fileError(const string &error="") {
    cerr << "Error: Formato de fichero incorrecto." << endl;
    if (!error.empty())
        cerr << "\t" + error << endl;
    exit(1);
}

vector<vector<string>> LandScape::randomMap(const int numLines, const vector<int> &objectIndexes) {

    vector<vector<string>> instructions;
    // Random
    random_device rd;
    mt19937 generator(rd());
    uniform_real_distribution<float> dist(0.0f, 1.0f);
    uniform_int_distribution<int> distRB(0, 20), distG(0, 255);

    // Colors
    instructions.push_back({"107", "107", "107"});
    instructions.push_back({"105", "105", "105"});
    instructions.push_back({to_string(distRB(generator)), to_string(distG(generator)), to_string(distRB(generator))});
    instructions.push_back({to_string(distRB(generator)), to_string(distG(generator)), to_string(distRB(generator))});

    // Instructions
    float prob;
    int line = 0, untilLine = 0;
    while (line < numLines) {
        vector<string> inst;

        prob = dist(generator);
        if (line < untilLine || prob < 0.90f) {
            // Line
            inst.emplace_back("ROAD");

            if (!objectIndexes.empty() && dist(generator) > 0.75f) {
                // Left object
                if (dist(generator) > 0.75f) {
                    // Repetitive
                    inst.emplace_back("+");
                }

                uniform_int_distribution<int> distObj(0, objectIndexes.size() - 1);
                inst.push_back(to_string(objectIndexes[distObj(generator)]));
                if (dist(generator) > 0.75f) {
                    // Offset
                    inst.push_back(to_string(dist(generator)));
                }
            }

            inst.emplace_back("-");

            if (!objectIndexes.empty() && dist(generator) > 0.75f) {
                // Right object
                if (dist(generator) > 0.75f) {
                    // Repetitive
                    inst.emplace_back("+");
                }

                uniform_int_distribution<int> distObj(0, objectIndexes.size() - 1);
                inst.push_back(to_string(objectIndexes[distObj(generator)]));
                if (dist(generator) > 0.75f) {
                    // Offset
                    inst.push_back(to_string(dist(generator)));
                }
            }

            line++;
        }
        else if (prob < 0.92f) {
            // Curve
            inst.emplace_back("CURVE");
            inst.push_back(to_string(dist(generator) / 2.0f));
        }
        else if (prob < 0.94f) {
            // Curve
            inst.emplace_back("CURVE");
            inst.push_back(to_string(-dist(generator) / 2.0f));
        }
        else if (prob < 0.96f) {
            // Straight
            inst.emplace_back("STRAIGHT");
        }
        else if (prob < 0.98f) {
            // Climb
            inst.emplace_back("CLIMB");

            uniform_int_distribution<int> distLines(1 + line, numLines);
            untilLine = distLines(generator);

            inst.push_back(to_string(dist(generator) * float(untilLine - line) * 100.0f));
            inst.push_back(to_string(untilLine - line));
        }
        else {
            // Drop
            inst.emplace_back("DROP");

            uniform_int_distribution<int> distLines(1 + line, numLines);
            untilLine = distLines(generator);

            inst.push_back(to_string(dist(generator) * float(untilLine - line) * 100.0f));
            inst.push_back(to_string(untilLine - line));
        }

        instructions.push_back(inst);
    }

    return instructions;
}

vector<vector<string>> LandScape::readMapFile(const std::string &file) {

    vector<vector<string>> instructions;
    ifstream fin(file);
    if (fin.is_open()) {
        bool road = false, grass = false, comment = false;
        int lines = 0, lastInclinationIndex = -1;

        vector<string> buffer;
        string s;
        while (!fin.eof()) {
            fin >> s;

            if (s.size() >= 2 && s[0] == '/' && s[1] == '*')
                comment = true;
            if (comment) {
                if (s.size() >= 2 && s[s.size() - 1] == '/' && s[s.size() - 2] == '*')
                    comment = false;
            }
            else {
                buffer.push_back(s);

                if (!road) {
                    if (buffer.size() == 6) {
                        instructions.push_back({buffer[0], buffer[1], buffer[2]});
                        instructions.push_back({buffer[3], buffer[4], buffer[5]});
                        buffer.clear();
                        road = true;
                    }
                }
                else if (!grass) {
                    if (buffer.size() == 6) {
                        instructions.push_back({buffer[0], buffer[1], buffer[2]});
                        instructions.push_back({buffer[3], buffer[4], buffer[5]});
                        buffer.clear();
                        grass = true;
                    }
                }
                else if (buffer.size() > 1 && (s == "ROAD" || s == "CURVE" || s == "STRAIGHT" || s == "CLIMB" ||
                                               s == "FLAT" || s == "DROP" || s == "RANDOM" || s  == "END")) {
                    if (buffer[0] == "CLIMB" || buffer[0] == "DROP" || buffer[0] == "FLAT") {
                        if (lastInclinationIndex > -1 && (instructions[lastInclinationIndex][0] == "CLIMB" ||
                                instructions[lastInclinationIndex][0] == "DROP")) {
                            instructions[lastInclinationIndex].push_back(to_string(lines));
                            lastInclinationIndex = -1;
                        }

                        if (buffer[0] == "CLIMB" || buffer[0] == "DROP") {
                            lines = 0;
                            lastInclinationIndex = instructions.size();

                            buffer.pop_back();
                            instructions.push_back(buffer);
                        }
                    }
                    else if (buffer[0] == "RANDOM") {
                        if (buffer.size() < 3)
                            fileError(buffer[0] + " necesita argumentos.");

                        vector<int> objectIndexes;
                        for (int i = 2; i < buffer.size() - 1; i++)
                            objectIndexes.push_back(stoi(buffer[i]));

                        const vector<vector<string>> randomInstructions = randomMap(stoi(buffer[1]), objectIndexes);
                        for (int i = 4; i < randomInstructions.size(); i++) {
                            instructions.push_back(randomInstructions[i]);
                        }
                    }
                    else {
                        if (s == "ROAD")
                            lines++;

                        buffer.pop_back();
                        instructions.push_back(buffer);
                    }

                    buffer.clear();
                    buffer.push_back(s);
                }
            }
        }
        fin.close();

        if (buffer[0] != "END")
            fileError("El fichero debe terminar en END.");
        if (instructions.size() < 4)
            fileError();
    }

    return instructions;
}

void LandScape::addLines(float x, float y, float &z, const vector<vector<string>> &instructions) {
    float curveCoeff = 0.0f, elevation = 0.0f;
    int elevationIndex = 0, elevationLines = -1;
    bool mainColor = true;

    // Colors
    roadColor[0] = Color(stoi(instructions[0][0]), stoi(instructions[0][1]), stoi(instructions[0][2]));
    roadColor[1] = Color(stoi(instructions[1][0]), stoi(instructions[1][1]), stoi(instructions[1][2]));
    grassColor[0] = Color(stoi(instructions[2][0]), stoi(instructions[2][1]), stoi(instructions[2][2]));
    grassColor[1] = Color(stoi(instructions[3][0]), stoi(instructions[3][1]), stoi(instructions[3][2]));

    for (int i = 4; i < instructions.size(); i++) {
        const vector<string> &inst = instructions[i];

        if (inst[0] == "CURVE") {
            if (inst.size() < 2)
                fileError(inst[0] + " necesita argumentos.");
            curveCoeff = stof(inst[1]);
        }
        else if (inst[0] == "STRAIGHT") {
            curveCoeff = 0.0f;
        }
        else if (inst[0] == "CLIMB") {
            if (inst.size() < 3)
                fileError(inst[0] + " necesita argumentos.");
            elevation = stof(inst[1]);
            elevationLines = stoi(inst[2]);
            elevationIndex = 0;
        }
        else if (inst[0] == "DROP") {
            if (inst.size() < 3)
                fileError(inst[0] + " necesita argumentos.");
            elevation = -stof(inst[1]);
            elevationLines = stoi(inst[2]);
            elevationIndex = 0;
        }
        else if (inst[0] == "ROAD") {
            Step::SpriteInfo spriteLeft, spriteRight;

            // Elevation
            float yAux = y;
            if (elevationIndex < elevationLines) {
                yAux += float(elevation) / 2.0f +
                        (float(elevation) / 2.0f) * cosf(M_PI + (M_PI / float(elevationLines)) * float(elevationIndex));
                elevationIndex++;
            }
            if (!newLines.empty() && elevationIndex == elevationLines) {
                y = newLines[newLines.size() - 1].position_3d_y;
                yAux = y;
                elevationLines = -1;
            }

            // Objects
            int j = 1; // inst index
            if (inst[j] != "-") { // Left object
                if (inst[j] == "+") {
                    spriteLeft.repetitive = true;
                    j++;
                }
                spriteLeft.spriteNum = stoi(inst[j]) - 1;
                j++;
                if (inst[j] != "-") {
                    spriteLeft.offset = stof(inst[j]);
                    j++;
                }
            }
            if (j >= inst.size() || inst[j] != "-") { // Checkpoint
                fileError(inst[0] + " tiene argumentos incorrectos.");
            }
            j++;
            if (j < inst.size()) { // Right object
                if (inst[j] == "+") {
                    spriteRight.repetitive = true;
                    j++;
                }
                spriteRight.spriteNum = stoi(inst[j]) - 1;
                j++;
                if (j < inst.size()) {
                    spriteRight.offset = stof(inst[j]);
                    j++;
                }
            }
            if (j != inst.size()) { // Checkpoint
                fileError(inst[0] + " tiene argumentos incorrectos.");
            }

            addLine(x, yAux, z, newLines.empty() ? y : newLines[newLines.size() - 1].position_3d_y, curveCoeff, mainColor,
                    spriteLeft, spriteRight);
            mainColor = !mainColor;
        }
    }
}

LandScape::LandScape(const std::string &path, const std::string &bgName,
                     const std::vector<std::string> &objectNames, bool random) : posX(0), posY(0), next(nullptr)
{
    bg.loadFromFile(path + bgName);
    bg.setRepeated(true);

    int k = 0;
    vector<int> objectIndexes;
    objectIndexes.reserve(objectNames.size());
    objects.reserve(objectNames.size());
    hitCoeff.reserve(objectNames.size());
    for (const string &s : objectNames) {
        // Load indexes
        objectIndexes.push_back(k);
        k++;

        // Load textures
        Texture t;
        t.loadFromFile(path + s);
        t.setSmooth(true);
        objects.push_back(t);

        // Load hit percentage from center
        ifstream fin(path + s + ".info");
        float coeff = 1.0f;
        if (fin.is_open()) {
            fin >> coeff;
            fin.close();
        }
        hitCoeff.push_back(coeff);
    }

    // Colors
    roadColor[0] = Color(107, 107, 107);
    roadColor[1] = Color(105, 105, 105);
    grassColor[0] = Color(16, 200, 16);
    grassColor[1] = Color(0, 154, 0);

    // Line generation
    float z = 0; // Line position
    if (random) { // Random generation
        addLines(0, 0, z, randomMap(1000, objectIndexes));
    }
    else { // Predefined map
        addLines(0, 0, z, readMapFile(path + "map.info"));
    }

    if (newLines.empty())
        fileError();
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

            Color grass, road;
            if (n < N || next == nullptr) {
                grass = grassColor[l->mainColor];
                road = roadColor[l->mainColor];
            }
            else {
                grass = next->grassColor[l->mainColor];
                road = next->roadColor[l->mainColor];
            }
            Color rumble = l->mainColor ? road : Color::White;
            Color dash = l->mainColor ? Color::White : road;

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
            drawQuad(app, dash, x1 + int(float(w1) * 0.333f), y1, dw1, x2 + int(float(w2) * 0.333f), y2, dw2); // Second left dash
            drawQuad(app, dash, x1 + int(float(w1) * 0.666f), y1, dw1, x2 + int(float(w2) * 0.666f), y2, dw2); // Second right dash
        }
    }

    ////////draw objects////////
    for (int n = int(posY); n < int(posY) + 300; n++) { // Reset draw info
        l = getLine(n);
        l->spriteLeft.spriteMinX = 0;
        l->spriteLeft.spriteMaxX = 0;
        l->spriteRight.spriteMinX = 0;
        l->spriteRight.spriteMaxX = 0;
    }
    for (int n = startPos + c->getRenderLen(); n > startPos; n--) {
        l = getLine(n);

        if (l->spriteLeft.spriteNum > -1) {
            if (n < N || next == nullptr)
                l->drawSprite(app, objects, hitCoeff, l->spriteLeft, true);
            else
                l->drawSprite(app, next->objects, next->hitCoeff, l->spriteLeft, true);
        }
        if (l->spriteRight.spriteNum > -1) {
            if (n < N || next == nullptr)
                l->drawSprite(app, objects, hitCoeff, l->spriteRight, false);
            else
                l->drawSprite(app, next->objects, next->hitCoeff, l->spriteRight, false);
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


