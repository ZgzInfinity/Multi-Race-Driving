
#include "../include/LandScape.h"


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
                    // Store the intervals of the landscape fragment
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
                    // Store the intervals of the landscape fragment
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
                    // Store the intervals of the landscape fragment
                    startPos = stoi(startPosition);
                    finalPos = stoi(finalPosition);
                }
            }
        }
    }
}



/**
 * Add a new step of the landscape read from the file
 * @param x is the actual coordinate 3d of the map in the axis x
 * @param y is the actual coordinate 3d of the map in the axis y
 * @param z is the actual coordinate 3d of the map in the axis z
 * @param prevY is the coordinate 3d of the map in the axis y of the last step added
 * @param curve represents the coefficient radius of the step to add to the map
 * @param mainColor shows in which color the step is going to be painted
 * @param spriteNearLeft is the map element located near and on the left of the road
 * @param spriteNearRight is the map element located near and on the right of the road
 * @param spriteFarLeft is the map element located far and on the left of the road
 * @param spriteFarRight is the map element located far and on the right of the road
 * @param eachNearLeft represents every few steps the map element located near and on
          the left of the road has to be displayed
 * @param eachNearRight represents every few steps the map element located near and on
          the right of the road has to be displayed
 * @param eachFarLeft represents every few steps the map element located far and on
          the left of the road has to be displayed
 * @param eachFarRight represents every few steps the map element located far and on
          the right of the road has to be displayed
 * @param codeNearLeft is the code of the map element located near and on the left on the road
 * @param codeNearRight is the code of the map element located near and on the right on the road
 * @param codeFarLeft is the code of the map element located far and on the left on the road
 * @param codeFarRight is the code of the map element located far and on the right on the road
 * @param generatedRandomNearLeft controls if the map element located near and on the left of the road
          has to be displayed in a random position
 * @param generatedRandomNearRight controls if the map element located near and on the right of the road
          has to be displayed in a random position
 * @param generatedRandomFarLeft controls if the map element located far and on the left of the road
          has to be displayed in a random position
 * @param generatedRandomFarRight controls if the map element located far and on the right of the road
          has to be displayed in a random position
 * @param checkPointOffset is the distance that separates the check point of the road
 * @param checkPointPos is the position in the landscape where the check point is drawn
 * @param codeCheckPoint is the code id of the map element which corresponds to the check point
 * @param checkPointDrawn controls if the check point has been drawn or not
 * @param bgX is the background position of the map in axis x
 * @param offsetX is the controller offset to make the bifurcations
 * @param offsetInc is partial offset to increment the bifurcation direction
 */
inline void LandScape::addStepFromFile(float& x, float y, float& z, float prevY, float curve, bool mainColor, MapElement& spriteNearLeft,
                                       MapElement& spriteNearRight, MapElement& spriteFarLeft, MapElement& spriteFarRight, int& stepsRead,
                                       int& eachNearLeft, int& eachNearRight, int& eachFarLeft, int& eachFarRight, int& startPos, float& leftOffset,
                                       int& codeNearLeft, int& codeNearRight, int& codeFarLeft, int& codeFarRight, bool& generateRandomNearLeft,
                                       bool& generateRandomNearRight, bool& generateRandomFarLeft, bool& generateRandomFarRight,
                                       float& checkPointOffset, int& checkPointPos, int& codeCheckPoint, bool& checkPointDrawn, float &bgX,
                                       float &offsetX, const float offsetInc)
{
    // RECTANGLE indicates the steps number will be added
    float yInc = (y - prevY) / float(RECTANGLE);

    Step line;
    line.position_3d_x = x;
    line.position_3d_y = prevY;
    line.mainColor = mainColor;
    line.directionCurve = curve;

    // For each normal line, extra steps without objects for better visualization
    for (int i = 0; i < 2 * INTIAL_POS; i++) {
        line.position_3d_z = z;
        z += SEGL;

        if (offsetX > 0.0f) {
            if (offsetX >= xFork)
                line.yOffsetX = sqrt(FORK_RADIUS * FORK_RADIUS - pow(offsetX - firstRadiusFork, 2.0f)) + secondRadiusFork;
            else
                line.yOffsetX = -sqrt(FORK_RADIUS * FORK_RADIUS - offsetX * offsetX) + FORK_RADIUS;
            line.offsetX = offsetX;
            if (offsetX + offsetInc <= 2.0f * xFork)
                offsetX += offsetInc;
        }

        line.position_3d_y += yInc;
        bgX += line.directionCurve;
        line.bgX = bgX;

        // Control the drawing of the check point indicator
        if (!checkPointDrawn && startPos + stepsRead == checkPointPos){
            spriteNearLeft.codeMapElement = codeCheckPoint;
            spriteNearLeft.offset = checkPointOffset;
            checkPointPos = -1;
            codeCheckPoint = -1;
            checkPointDrawn = true;
            // Push the position of the checkpoint
            checkPointPositions.push_back(totalSteps);
        }
        else {
            // Draw the map element which is near and on the left of the road
            if ((startPos + stepsRead) % eachNearLeft != 0){
                spriteNearLeft.codeMapElement = -1;
            }
            else {
                spriteNearLeft.codeMapElement = codeNearLeft;
            }
            spriteNearLeft.offset = leftOffset;
        }
        // Control the near sprite of the right
        if ((startPos + stepsRead) % eachNearRight != 0){
            spriteNearRight.codeMapElement = -1;
        }
        else {
            spriteNearRight.codeMapElement = codeNearRight;
        }

        // Control the far sprite of the left
        if ((startPos + stepsRead) % eachFarLeft != 0){
            spriteFarLeft.codeMapElement = -1;
        }
        else {
            spriteFarLeft.codeMapElement = codeFarLeft;
        }

        // Control the far sprite of the right
        if ((startPos + stepsRead) % eachFarRight != 0){
            spriteFarRight.codeMapElement = -1;
        }
        else {
            spriteFarRight.codeMapElement = codeFarRight;
        }


        // Control if the position of the map element which is near and of the left of the road
        // has to be located randomly or not
        if (generateRandomNearLeft){
            mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
            uniform_real_distribution<float> offset(0.0f, 3.0f);
            spriteNearLeft.offset = offset(rng);
        }

        // Control if the position of the map element which is near and of the right of the road
        // has to be located randomly or not
        if (generateRandomNearRight){
            mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
            uniform_real_distribution<float> offset(0.0f, 3.0f);
            spriteNearRight.offset = offset(rng);
        }

        // Control if the position of the map element which is far and of the left of the road
        // has to be located randomly or not
        if (generateRandomFarLeft){
            mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
            uniform_real_distribution<float> offset(3.0f, 6.0f);
            spriteFarLeft.offset = offset(rng);
        }

        // Control if the position of the map element which is far and of the right of the road
        // has to be located randomly or not
        if (generateRandomFarRight){
            mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
            uniform_real_distribution<float> offset(3.0f, 6.0f);
            spriteFarRight.offset = offset(rng);
        }

        // Fill the map elements of the interval
        line.spriteNearLeft = spriteNearLeft;
        line.spriteNearRight = spriteNearRight;
        line.spriteFarLeft = spriteFarLeft;
        line.spriteFarRight = spriteFarRight;

        stepsRead++;
        newLines.push_back(line);
        totalSteps++;
    }
}



/**
 * Add a new step of the landscape but not from the file
 * @param x is the actual coordinate 3d of the map in the axis x
 * @param y is the actual coordinate 3d of the map in the axis y
 * @param z is the actual coordinate 3d of the map in the axis z
 * @param prevY is the coordinate 3d of the map in the axis y of the last step added
 * @param curve represents the coefficient radius of the step to add to the map
 * @param mainColor shows in which color the step is going to be painted
 * @param spriteNearLeft is the map element located near and on the left of the road
 * @param spriteNearRight is the map element located near and on the right of the road
 * @param bgX is the background position of the map in axis x
 * @param offsetX is the controller offset to make the bifurcations
 * @param offsetInc is partial offset to increment the bifurcation direction
 */
inline void LandScape::addStep(float x, float y, float &z, float prevY, float curve, bool mainColor,
                               const MapElement &spriteNearLeft, const MapElement &spriteNearRight, float &bgX, float &offsetX,
                               const float offsetInc)
{
    float yInc = (y - prevY) / float(RECTANGLE); // RECTANGLE is total lines number will be added

    Step line, lineAux;
    line.position_3d_x = x;
    line.position_3d_y = prevY;
    line.mainColor = mainColor;
    line.directionCurve = curve;

    lineAux = line; // without objects

    line.spriteNearLeft = spriteNearLeft;
    line.spriteNearRight = spriteNearRight;

    // For each normal line, extra lines without objects for better visualization
    for (int i = 0; i < INTIAL_POS; i++) {
        lineAux.position_3d_z = z;
        z += SEGL;
        if (offsetX > 0.0f) {
            if (offsetX >= xFork)
                lineAux.yOffsetX = sqrt(FORK_RADIUS * FORK_RADIUS - pow(offsetX - firstRadiusFork, 2.0f)) + secondRadiusFork;
            else
                lineAux.yOffsetX = -sqrt(FORK_RADIUS * FORK_RADIUS - offsetX * offsetX) + FORK_RADIUS;
            lineAux.offsetX = offsetX;
            if (offsetX + offsetInc <= 2.0f * xFork)
                offsetX += offsetInc;
        }
        lineAux.position_3d_y += yInc;
        bgX += lineAux.directionCurve;
        lineAux.bgX = bgX;
        newLines.push_back(lineAux);
    }

    line.position_3d_z = z;
    z += SEGL;
    if (offsetX > 0.0f) {
        if (offsetX >= xFork)
            line.yOffsetX = sqrt(FORK_RADIUS * FORK_RADIUS - pow(offsetX - firstRadiusFork, 2.0f)) + secondRadiusFork;
        else
            line.yOffsetX = -sqrt(FORK_RADIUS * FORK_RADIUS - offsetX * offsetX) + FORK_RADIUS;
        line.offsetX = offsetX;
        if (offsetX + offsetInc <= 2.0f * xFork)
            offsetX += offsetInc;
    }
    lineAux.position_3d_y += yInc;
    line.position_3d_y = lineAux.position_3d_y;
    bgX += line.directionCurve;
    line.bgX = bgX;
    newLines.push_back(line);

    for (int i = 0; i < INTIAL_POS; i++) {
        lineAux.position_3d_z = z;
        z += SEGL;
        if (offsetX > 0.0f) {
            if (offsetX >= xFork)
                lineAux.yOffsetX = sqrt(FORK_RADIUS * FORK_RADIUS - pow(offsetX - firstRadiusFork, 2.0f)) + secondRadiusFork;
            else
                lineAux.yOffsetX = -sqrt(FORK_RADIUS * FORK_RADIUS - offsetX * offsetX) + FORK_RADIUS;
            lineAux.offsetX = offsetX;
            if (offsetX + offsetInc <= 2.0f * xFork)
                offsetX += offsetInc;
        }
        lineAux.position_3d_y += yInc;
        bgX += lineAux.directionCurve;
        lineAux.bgX = bgX;
        newLines.push_back(lineAux);
    }
}



/**
 * Return the step of the landscape with index n
 * @param n is the index of a landscape's step
 * @return
 */
Step *LandScape::getStep(const int n) {
    if (n < (int)newLines.size() || nextLeft == nullptr){
        return &newLines[n % newLines.size()];
    }
    else {
        return &nextLeft->newLines[(n - newLines.size()) % nextLeft->newLines.size()];
    }
}



/**
 * Return the step of the landscape with index n
 * @param n is the index of a landscape's step
 * @return
 */
Step LandScape::getStep(const int n) const {
    if (n < (int)newLines.size() || nextLeft == nullptr){
        return newLines[n % newLines.size()];
    }
    else {
        return nextLeft->newLines[(n - newLines.size()) % nextLeft->newLines.size()];
    }
}



/**
 * Returns the previous step of the landscape to the step with index n
 * @param is the index of a landscape's step
 * @return
 */
Step *LandScape::getLastStep(const int n) {
    if ((n > 0 && n - 1 < (int)newLines.size()) || nextLeft == nullptr)
        return &newLines[(n - 1) % newLines.size()];
    else
        return &nextLeft->newLines[(n - 1 - newLines.size()) % nextLeft->newLines.size()];
}



/**
 * Returns the previous step of the landscape to the step with index n
 * @param is the index of a landscape's step
 * @return
 */
Step LandScape::getLastStep(const int n) const {
    if ((n > 0 && n - 1 < (int)newLines.size()) || nextLeft == nullptr){
        return newLines[(n - 1) % newLines.size()];
    }
    else {
        return nextLeft->newLines[(n - 1 - newLines.size()) % nextLeft->newLines.size()];
    }
}



/**
 * Read the map element properties stored in its xml configuration file
 * @param path is the path of the xml configuration file with the properties of the map element
 * @param hitC is the collision coefficient damage of the map element
 * @param scaleC is the scaling coefficient of the map element
 * @param hitCoeffType is the type of hitting coefficient of collision
 */
inline void LandScape::readMapElementProperties(const string path, float& hitC, float& scaleC, HitThresholdObject& hitCoeffType){

    // Open the xml configuration file
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *mapElement = doc.first_node();

    // Iterate throughout the properties of the map element
    for (xml_node<> *property = mapElement->first_node(); property; property = property->next_sibling()){
        // Check if it's the node of the hit coefficient center
        if ((string)property->name() == "Hit_center"){
            hitC = stof(property->value());
            hitCoeffType = HIT_CENTER;
        }
        // Check if it's the node of the hit coefficient left
        else if ((string)property->name() == "Hit_left"){
            hitC = stof(property->value());
            hitCoeffType = HIT_LEFT;
        }
        // Check if it's the node of the hit coefficient right
        else if ((string)property->name() == "Hit_right"){
            hitC = stof(property->value());
            hitCoeffType = HIT_RIGHT;
        }
        // Check if it's the node of the hit coefficient sides
        else if ((string)property->name() == "Hit_sides"){
            hitC = stof(property->value());
            hitCoeffType = HIT_SIDES;
        }
         // Check if it's the node of the scaling value
        else if ((string)property->name() == "Scale"){
            scaleC = stof(property->value());
        }
    }
}



/**
 * Load all the textures of the map elements located in the landscape
 * @param path is the path of the xml file which contains the configuration of the landscape
 * @param objectIndexes is a vector which contains the code ids of the map elements
 */
void LandScape::loadMapElements(const string &path, vector<int> &objectIndexes) {

    // Variable to store temporary the paths of the map elements
    string pathMapElement;

    // Load textures
    Texture t;

    // Index of the map element
    int indexMapElement = 0;

    // Open the xml file of the scenario
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *nodeLandScape = doc.first_node();

    // Iteration throughout the nodes of the file
    for (xml_node<> *node = nodeLandScape->first_node(); node; node = node->next_sibling()){
        // Check if the node contains the name of the landscape
        if ((string)node->name() == "Name"){
            name = (string)node->value();
        }
        // Check if the node contains the name of the landscape
        else if ((string)node->name() == "Type"){
            // Check the kind of landScape
            if ((string)node->value() == "Grass"){
                terrain = 0;
            }
            else if ((string)node->value() == "Land"){
                terrain = 1;
            }
            // Check the kind of landScape
            if ((string)node->value() == "Snow"){
                terrain = 2;
            }
        }
        // Check if the node contains the sprites of the scenario
        else if ((string)node->name() == "Sprites"){
            // Iteration throughout the nodes of the file
            for (xml_node<> *mapElement = node->first_node(); mapElement; mapElement = mapElement->next_sibling()){
                // Get the path of the actual map element
                pathMapElement = (string)mapElement->value();

                // Load the texture oof the map element
                t.loadFromFile(pathMapElement);
                t.setSmooth(true);
                mapElementTextures.push_back(t);

                // Load index of the map element
                objectIndexes.push_back(indexMapElement);
                indexMapElement++;

                // Load hit percentage from center and scale coeff
                pathMapElement = pathMapElement.substr(0, pathMapElement.size() - 4);
                const string path = pathMapElement + ".xml";

                // Default collision and scale coefficients
                float hitC = 1.0f, scaleC = 1.0f;
                HitThresholdObject hitCoeffType = HIT_CENTER;

                // Check if the file exists or not
                ifstream fin(path);
                if (fin.is_open()){
                    // The file exits
                    fin.close();
                    // Load the map element properties stored in the file
                    readMapElementProperties(path, hitC, scaleC, hitCoeffType);
                }
                // Store the properties of the file
                hittMapElementsCofs.push_back(hitC);
                hitKindCofs.push_back(hitCoeffType);
                scalingFactors.push_back(scaleC);
            }
        }
    }
}



/**
 * Process an interval of the landscape whose configuration is been read
 * @param roadNode is the xml node which contains the information of a part of the landscape
 * @param curveCoeff is the coefficient of the curve
 * @param elevation is the possible elevation of the terrain
 * @param mainColor is the color which is going to be used to paint this part of landscape
 * @param elevationIndex is the threshold to know if an elevation on the terrain has to be drawn
 * @param elevationLines indicates how many steps has the change of elevation
 * @param flatTerrain controls if the actual part of the landscape is flat or not
 * @param cordX is the actual 3d coordinate of the landscape in the axis x
 * @param cordY is the actual 3d coordinate of the landscape in the axis y
 * @param cordZ is the actual 3d coordinate of the landscape in the axis z
 * @param bgX is the actual background position of the landscape
 */
void LandScape::processRoadPart(xml_node<> * roadNode, float& curveCoeff, float& elevation, bool& mainColor,
                                int elevationIndex, int& elevationLines, bool flatTerrain, float& cordX,
                                float& cordY, float& cordZ, float& bgX)
{
    // Local variables
    int startPos, finalPos;
    int eachNearLeft = 0, eachNearRight = 0, eachFarLeft = 0, eachFarRight = 0,
        codeNearLeft = -1, codeNearRight = -1, codeFarLeft = -1, codeFarRight = -1,
        codeCheckPoint = -1;

    // Sprites of the step
    MapElement spriteNearLeft, spriteNearRight, spriteFarLeft, spriteFarRight;

    int stepsRead = 0, checkPointPos = -1;

    // Control if the offset of the sprites must be random or not
    bool generateRandomNearLeft = false, generateRandomNearRight = false,
         generateRandomFarLeft = false, generateRandomFarRight = false;

    // Control if the check point map element has been drawn
    bool checkPointDrawn = false;

    // Strange variable
    float leftOffset = 0.0, checkPointOffset = 0.0;

    // Get the interval coordinates of the terrain
    getIntervalCoordinates(roadNode, 0, startPos, finalPos);

    // Get the sprite information of the terrain
    for (xml_node<> *spriteNode = roadNode->first_node(); spriteNode; spriteNode = spriteNode->next_sibling()){
        // Check if it's the check point
        if ((string)spriteNode->name() == "CheckPoint"){
            // Iteration to get the attributes of the sprite object
            for (xml_node<> *attributeNode = spriteNode->first_node(); attributeNode; attributeNode = attributeNode->next_sibling()){
                // Check the interval to show the sprite
                if ((string)attributeNode->name() == "Offset"){
                    // Check if the offset has be initialized randomly
                    generateRandomNearLeft = false;
                    checkPointOffset = stof((string)attributeNode->value());
                }
                // Check the path of the sprite
                else if ((string)attributeNode->name() == "Position"){
                    checkPointPos = stoi(attributeNode->value());
                }
                // Check the path of the sprite
                else if ((string)attributeNode->name() == "Code"){
                    codeCheckPoint = stoi(attributeNode->value()) - 1;
                }
            }
        }
        // Check if it's the left or right object
        else if ((string)spriteNode->name() == "SpriteNearLeft"){
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
                        leftOffset = stof((string)attributeNode->value());
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
                        spriteNearRight.offset = stof((string)attributeNode->value());
                    }
                }
                // Check the path of the sprite
                else if ((string)attributeNode->name() == "Code"){
                     codeNearRight = stoi(attributeNode->value()) - 1;
                }
            }
        }
        // Check if it's the left or right object
        else if ((string)spriteNode->name() == "SpriteFarLeft"){
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
                        spriteFarLeft.offset = stof((string)attributeNode->value());
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
                        spriteFarRight.offset = stof((string)attributeNode->value());
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

        float offsetX = 0.0f;
        // Add the line of the file
        addStepFromFile(cordX, yAux, cordZ, newLines.empty() ? cordY : newLines[newLines.size() - 1].position_3d_y, curveCoeff, mainColor,
                        spriteNearLeft, spriteNearRight, spriteFarLeft, spriteFarRight, stepsRead, eachNearLeft, eachNearRight,
                        eachFarLeft, eachFarRight, startPos, leftOffset, codeNearLeft, codeNearRight, codeFarLeft, codeFarRight,
                        generateRandomNearLeft, generateRandomNearRight, generateRandomFarLeft, generateRandomFarRight,
                        checkPointOffset, checkPointPos, codeCheckPoint, checkPointDrawn, bgX, offsetX);

        mainColor = !mainColor;
    }
}



/**
 * Parses all the configuration of the color of the road written in the xml
 * configuration file of the scene
 * @param child is a node of the xml file that points to the color of the grass information
 */
inline void LandScape::parseColorGrassRoadScene(xml_node<> * child){
    int colorRed = 0, colorGreen = 0, colorBlue = 0, index = 0;
    // Loop in order to iterate throughout the colors of the grass
    for (xml_node<> *color_node = child->first_node(); color_node; color_node = color_node->next_sibling()){
        // Loop for iterate the three color channels in RGB format
        for (xml_node<> *color = color_node->first_node(); color; color = color->next_sibling()){
            parseColors(color, colorRed, colorGreen, colorBlue);
        }
        // Check where the color has been stored
        if ((string)child->name() == "Color_grass"){
            grassColor[index] = Color(colorRed, colorGreen, colorBlue);
            index++;
            index = (index == 2) ? 0 : index;
        }
        else if ((string)child->name() == "Color_road"){
            roadColor[index] = Color(colorRed, colorGreen, colorBlue);
            index++;
            index = (index == 2) ? 0 : index;
        }
        else if ((string)child->name() == "Color_rumble"){
            rumbleColor = Color(colorRed, colorGreen, colorBlue);
        }
        else if ((string)child->name() == "Color_dash"){
            dashColor = Color(colorRed, colorGreen, colorBlue);
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



/**
 * Parses the xml configuration file of a landscape of the game
 * @param pathFile is the path of the xml configuration file of the landscape
 */
inline void LandScape::parseLandScape(const string& pathFile){
    // Open the xml file of the scenario
    char* pFile = const_cast<char*>(pathFile.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *nodeLandScape = doc.first_node();

    // Variables to control the different types of terrain
    float curveCoeff = 0.0f, elevation = 0, cordX = 0, cordY = 0, cordZ = 0, bgX = 0;
    int elevationIndex = 0, elevationLines = -1;
    bool mainColor = true;

    // Iteration throughout the nodes of the file
    for (xml_node<> *node = nodeLandScape->first_node(); node; node = node->next_sibling()){
        // Check if the node contains the sprites of the scenario
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
                                        elevationLines, true, cordX, cordY, cordZ, bgX);
                    }
                    else if ((string)nodeTerrain->name() == "Curve"){
                        // Get the direction of the curve
                        curveCoeff = stof(nodeTerrain->first_attribute("direction")->value());
                        // Read and parse the road properties in this part of terrain
                        processRoadPart(nodeTerrain->first_node(), curveCoeff, elevation, mainColor,
                                        elevationIndex, elevationLines, true, cordX, cordY, cordZ, bgX);
                    }
                    else if ((string)nodeTerrain->name() == "Dropping" || (string)nodeTerrain->name() == "Climbing"){
                        // Get the elevation of the terrain
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
                                                    elevationIndex, elevationLines, false, cordX, cordY, cordZ, bgX);
                                }
                            }
                        }
                    }
                }
            }
        }
        // Check if it's the node that contains the different colors of the road
        else if ((string)node->name() == "Color_grass" || (string)node->name() == "Color_road" ||
                 (string)node->name() == "Color_rumble" || (string)node->name() == "Color_dash")
        {
            // Parse the information of the color of the road
            parseColorGrassRoadScene(node);
        }
    }
}



/**
 * Load the properties configuration of the landscape's road
 * @param pathRoadFile is the path of the file which contains the properties of the road
 */
void LandScape::loadRoadProperties(const string& pathRoadFile){
    // Open the xml file of the scenario
    char* pFile = const_cast<char*>(pathRoadFile.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *propertyRoad = doc.first_node();

    // Iterate to get the information road specifications
    for (xml_node<> *property = propertyRoad->first_node(); property; property = property->next_sibling()){
        // Check if it's the node that control the possible curve coefficient
        if ((string)property->name() == "Width_road"){
           width_road = stoi(property->value());
        }
        else if ((string)property->name() == "Number_tracks"){
            number_tracks = stoi(property->value());
        }
        else if ((string)property->name() == "Rumble_limit"){
            limit_rumble = stof(property->value());
        }
    }
}



/**
 * Draw how many tracks in the road as there has been specified in the road file configuration
 * @param w is the console window of the game
 * @param dash is the color which is going to be used to paint the tracks in the road
 * @param x1 is the lower left corner coordinate x of the rectangle to draw
 * @param w1 is the width of the rectangle to paint
 * @param y1 is the lower left corner coordinate y of the rectangle to draw
 * @param dw1 is the the half of the rectangle's width
 * @param x2 is the upper left corner coordinate x of the rectangle to draw
 * @param w2 is the height of the rectangle to paint
 * @param y2 is the upper left corner coordinate y of the rectangle to draw
 * @param dw2 is the the half of the rectangle's height
 */
inline void LandScape::drawRoadTracks(RenderTexture& w, Color& dash, const int x1, const int w1, const int y1,
                       const int dw1, const int x2, const int w2, const int y2, const int dw2)
{
    if (number_tracks == 2){
        drawQuad(w, dash, x1 + int(float(w1) * 0.5f), y1, dw1, x2 + int(float(w2) * 0.5f), y2, dw2);
    }
    else {
        for (int i = 1; i < number_tracks; i++){
            drawQuad(w, dash, x1 + int(float(w1) * (0.25f * i)), y1, dw1, x2 + int(float(w2) * (0.25f * i)), y2, dw2);
        }
    }
}



/**
 * Creates a landscape reading its xml configuration file
 * @param c is the configuration of the game
 * @param path is the path of the xml file that contains the configuration of the landscape
 * @param bgName is the path of the image that represents the background of the landscape
 * @param time is the time available to complete the landscape
 * @param typeOfGame represents the game mode selected by the player
 */
LandScape::LandScape(Configuration &c, const string &path, const string &bgName,
                     const int time, const int typeOfGame, const int numRivals) : posCameraY(0), nextLeft(nullptr), nextRight(nullptr),
                     startingLandScape(false), finalLandScape(false), middleLandScape(false), timeToPlay(time)
{

    if (typeOfGame == 0 || typeOfGame == 2){
        if (numRivals == 0){
            posCameraX = 0.f;
        }
        else {
            posCameraX = -0.3f;
        }
    }
    else {
        posCameraX = 0.f;
    }

    // Load the background texture of the map
    background.loadFromFile(path + bgName);
    background.setRepeated(true);

    // Load objects
    vector<int> objectIndexes;

    // Completing the path of the file to read
    string pathComplete = path + "LandScape.xml";

    // Load the map elements of the scenario
    loadMapElements(pathComplete, objectIndexes);

    totalSteps = 0;

    // Read the xml map file
    parseLandScape(pathComplete);

    string pathRoadFile;

    switch(typeOfGame){
    case 0:
        // World tour mode
        pathRoadFile = "Data/GameModes/WorldTour/Configuration/Configuration.xml";
        break;
    case 1:
        // Out Run mode
        pathRoadFile = "Data/GameModes/OutRun/Configuration/Configuration.xml";
        break;
    case 2:
        // Pole Position mode
        pathRoadFile = "Data/GameModes/PolePosition/Configuration/Configuration.xml";
        break;
    case 3:
        // Driving fury mode
        pathRoadFile = "Data/GameModes/DrivingFury/Configuration/Configuration.xml";
        break;
    case 4:
        // Demarrage mode
        pathRoadFile = "Data/GameModes/Derramage/Configuration/Configuration.xml";
        break;
    case 5:
        // Delivery mode
        pathRoadFile = "Data/GameModes/Delivery/Configuration/Configuration.xml";
    }

    // Load properties of the road
    loadRoadProperties(pathRoadFile);
}



LandScape::LandScape(){}

/**
 * Creates a straight flat map which represents the starting point of a landscape
 * @param landscape is the landscape to be displayed
 * @param flagger is the flagger position while is announcing the start
 * @param semaphore is the color of the semaphore in the starting
 */
LandScape::LandScape(const LandScape &landScape, int &flagger, int &semaphore, const int typeOfGame, const int numRivals) :
                     background(landScape.background), posCameraY(0), nextLeft(nullptr), nextRight(nullptr), startingLandScape(true),
                     finalLandScape(false), middleLandScape(false), timeToPlay(0)
{

    if (typeOfGame == 0 || typeOfGame == 2){
        if (numRivals == 0){
            posCameraX = 0.f;
        }
        else {
            posCameraX = -0.3f;
        }
    }
    else {
        posCameraX = 0.f;
    }

    int rectangles = 0, peopleDisplayed, treesDisplayed;

    if (typeOfGame == 0 || typeOfGame == 2){
        peopleDisplayed = 8;
        treesDisplayed = 6;
        if (typeOfGame == 2){
            switch(numRivals){
                case 0:
                case 1:
                    rectangles = 50;
                    break;
                case 2:
                case 3:
                    rectangles = 55;
                    break;
                case 4:
                case 5:
                    rectangles = 60;
                    break;
                case 6:
                case 7:
                    rectangles = 65;
                }
        }
        else {
            rectangles = 65;
        }
    }
    else {
        rectangles = 50;
        treesDisplayed = 4;
        peopleDisplayed = 2;
    }

    // Map size
    const string mapPath = "Data/LandScapeCommon/LandScape.xml"; // File with all the textures

    // Colors
    roadColor[0] = landScape.roadColor[0];
    roadColor[1] = landScape.roadColor[1];
    grassColor[0] = landScape.grassColor[0];
    grassColor[1] = landScape.grassColor[1];
    rumbleColor = landScape.rumbleColor;
    dashColor = landScape.dashColor;

    vector<int> objectIndexes;

    loadMapElements(mapPath, objectIndexes);

    // Hardcoded sprites
    vector<MapElement> leftSprites, rightSprites;
    leftSprites.reserve(rectangles);
    rightSprites.reserve(rectangles);
    for (int i = 0; i < rectangles; i++) {
        leftSprites.emplace_back();
        rightSprites.emplace_back();
    }

    if (typeOfGame == 1){
        // People
        leftSprites[1].codeMapElement = 12; // 29 - 1
        leftSprites[1].offset = -1.75f;
        rightSprites[1].codeMapElement = 13;
        rightSprites[1].offset = -1.75f;
    }

    // Signals
    leftSprites[rectangles - 44].codeMapElement = 6;
    leftSprites[rectangles - 44].offset = -1;
    rightSprites[rectangles - 44].codeMapElement = 11;
    rightSprites[rectangles - 44].offset = -1;

    // Flagger
    leftSprites[rectangles - 45].codeMapElement = 1;
    if (typeOfGame == 0 || typeOfGame == 2){
        leftSprites[rectangles - 45].offset = -2;
    }
    else {
        leftSprites[rectangles - 45].offset = -4;
    }

    rightSprites[rectangles - 46].codeMapElement = 10;
    rightSprites[rectangles - 46].offset = -0.95f;

    // Trees
    leftSprites[rectangles - 47].codeMapElement = 18;
    leftSprites[rectangles - 47].offset = -1.15f;
    rightSprites[rectangles - 47].codeMapElement = 17;
    rightSprites[rectangles - 47].offset = -1.15f;

    // Fill
    if (typeOfGame == 0 || typeOfGame == 2){
        for (int i = 0; i <= rectangles; i++) {
            if (i >= 0 && i <= rectangles - 47){
                if (i % treesDisplayed == 4) {
                    // Trees
                    leftSprites[i].codeMapElement = 18;
                    leftSprites[i].offset = -0.15f;
                    rightSprites[i].codeMapElement = 17;
                    rightSprites[i].offset = -0.15f;
                }
                else if (i % peopleDisplayed == 1 && (typeOfGame <= 2 || typeOfGame > 4)) {
                    // People
                    leftSprites[i].codeMapElement = 15;
                    rightSprites[i].codeMapElement = 14;
                }
            }
            else if (i > rectangles - 42){
                if (i % treesDisplayed == 4) {
                    // Trees
                    leftSprites[i].codeMapElement = 18;
                    leftSprites[i].offset = -0.15f;
                    rightSprites[i].codeMapElement = 17;
                    rightSprites[i].offset = -0.15f;
                }
                else if (i % peopleDisplayed == 1 && (typeOfGame <= 2 || typeOfGame > 4)) {
                    // People
                    leftSprites[i].codeMapElement = 15;
                    rightSprites[i].codeMapElement = 14;
                }
            }
        }
    }
    else {
        for (int i = 7; i < rectangles; i++) {
            if (i % treesDisplayed == 3) {
                // Trees
                leftSprites[i].codeMapElement = 18;
                leftSprites[i].offset = -0.15f;
                rightSprites[i].codeMapElement = 17;
                rightSprites[i].offset = -0.15f;
            }
            else if (i % peopleDisplayed == 0 && (typeOfGame <= 2 || typeOfGame > 4)) {
                // People
                leftSprites[i].codeMapElement = 15;
                rightSprites[i].codeMapElement = 14;
            }
        }
    }

    // Line generation
    bool mainColor = true;
    vector<vector<string>> instructions;
    instructions.reserve(rectangles);
    float z = 0; // Line position
    float bgX = 0; // Background position
    for (int i = 0; i < rectangles; i++) {
        float offset = 0.0f;
        addStep(0, 0, z, 0, 0, mainColor, leftSprites[i], rightSprites[i], bgX, offset);
        mainColor = !mainColor;
    }

    flagger = RECTANGLE * (rectangles - 45) + INTIAL_POS;
    semaphore = RECTANGLE * (rectangles - 44) + INTIAL_POS;
}



/**
 * Creates a straight flat map which represents the starting point of a landscape
 * @param landscape is the landscape to be displayed
 * @param flagger is the flagger position while is announcing the start
 * @param semaphore is the color of the semaphore in the starting
 */
LandScape::LandScape(const LandScape &landScape, const int typeOfGame, const int numRivals) :
                     background(landScape.background), posCameraY(0), nextLeft(nullptr), nextRight(nullptr),
                     startingLandScape(false), finalLandScape(false), middleLandScape(true), timeToPlay(0)
{

    if (typeOfGame == 0 || typeOfGame == 2){
        if (numRivals == 0){
            posCameraX = 0.f;
        }
        else {
            posCameraX = -0.3f;
        }
    }
    else {
        posCameraX = 0.f;
    }

    int rectangles = 0;

    if (typeOfGame == 2){
        switch(numRivals){
            case 0:
            case 1:
                rectangles = 50;
                break;
            case 2:
            case 3:
                rectangles = 55;
                break;
            case 4:
            case 5:
                rectangles = 60;
                break;
            case 6:
            case 7:
                rectangles = 65;
        }
    }

    // Map size
    const string mapPath = "Data/LandScapeCommon/LandScape.xml"; // File with all the textures

    vector<int> objectIndexes;

    loadMapElements(mapPath, objectIndexes);

    // Hardcoded sprites
    vector<MapElement> leftSprites, rightSprites;
    leftSprites.reserve(rectangles);
    rightSprites.reserve(rectangles);
    for (int i = 0; i < rectangles; i++) {
        leftSprites.emplace_back();
        rightSprites.emplace_back();
    }

    // Signals
    leftSprites[rectangles - 44].codeMapElement = 6;
    leftSprites[rectangles - 44].offset = -1;
    rightSprites[rectangles - 44].codeMapElement = 11;
    rightSprites[rectangles - 44].offset = -1;

    // Flagger
    leftSprites[rectangles - 45].codeMapElement = 1;
    leftSprites[rectangles - 45].offset = -2;


    rightSprites[rectangles - 46].codeMapElement = 10;
    rightSprites[rectangles - 46].offset = -0.95f;

    // Trees
    leftSprites[rectangles - 47].codeMapElement = 18;
    leftSprites[rectangles - 47].offset = -1.15f;
    rightSprites[rectangles - 47].codeMapElement = 17;
    rightSprites[rectangles - 47].offset = -1.15f;

    // Fill
    for (int i = 7; i < rectangles; i++) {
        if (i % 6 == 3) {
            // Trees
            leftSprites[i].codeMapElement = 18;
            leftSprites[i].offset = -0.15f;
            rightSprites[i].codeMapElement = 17;
            rightSprites[i].offset = -0.15f;
        }
        else if (i % 8 == 0 && (typeOfGame <= 2 || typeOfGame > 4)) {
            // People
            leftSprites[i].codeMapElement = 15;
            rightSprites[i].codeMapElement = 14;
        }
    }

    // Line generation
    bool mainColor = true;
    vector<vector<string>> instructions;
    instructions.reserve(rectangles);
    float z = 0; // Line position
    float bgX = 0; // Background position
    for (int i = 0; i < rectangles; i++) {
        float offset = 0.0f;
        addStep(0, 0, z, 0, 0, mainColor, leftSprites[i], rightSprites[i], bgX, offset);
        mainColor = !mainColor;
    }
}



/**
 * Creates a straight flat map which represents the goal point of a landscape
 * @param landscape is the landscape to be displayed
 * @param flagger is the flagger position while is announcing the goal
 * @param semaphore is the color of the semaphore in the goal
 */
LandScape::LandScape(int &flagger, int &goalEnd, const int typeOfGame, const int numRivals) : posCameraY(0), nextLeft(nullptr),
                     nextRight(nullptr), startingLandScape(false), finalLandScape(true), middleLandScape(false),
                     timeToPlay(0)
{

    if (typeOfGame == 0 || typeOfGame == 2){
        if (numRivals == 0){
            posCameraX = 0.f;
        }
        else {
            posCameraX = -0.3f;
        }
    }
    else {
        posCameraX = 0.f;
    }

    const int rectangles = 180; // Map size
    const string mapPath = "Data/LandScapeCommon/LandScape.xml"; // Folder with common objects

    vector<int> objectIndexes;
    loadMapElements(mapPath, objectIndexes);

    // Hardcoded sprites
    vector<MapElement> leftSprites, rightSprites;
    leftSprites.reserve(rectangles);
    rightSprites.reserve(rectangles);
    for (int i = 0; i < rectangles; i++) {
        leftSprites.emplace_back();
        rightSprites.emplace_back();
    }

    // Flagger
    leftSprites[6].codeMapElement = 0;
    leftSprites[6].offset = -2;

    // Second goal
    rightSprites[7].codeMapElement = 16;
    rightSprites[7].offset = -0.95f;

    // Trees
    leftSprites[5].codeMapElement = 18;
    leftSprites[5].offset = -1.15f;
    rightSprites[5].codeMapElement = 17;
    rightSprites[5].offset = -1.15f;

    // Fill
    for (int i = 8; i < rectangles; i++) {
        if (i % 4 == 3) {
            // Trees
            leftSprites[i].codeMapElement = 18;
            leftSprites[i].offset = -0.15f;
            rightSprites[i].codeMapElement = 17;
            rightSprites[i].offset = -0.15f;
        }
        else if (i % 2 == 0 && (typeOfGame <= 2 || typeOfGame > 4)) {
            // People
            leftSprites[i].codeMapElement = 15;
            rightSprites[i].codeMapElement = 14;
        }
    }

    // Line generation
    bool mainColor = true;
    vector<vector<string>> instructions;
    instructions.reserve(rectangles);
    float z = 0; // Line position
    float bgX = 0; // Background position
    for (int i = 0; i < rectangles; i++) {
        float offset = 0.0f;
        addStep(0, 0, z, 0, 0, mainColor, leftSprites[i], rightSprites[i], bgX, offset);
        mainColor = !mainColor;
    }

    flagger = RECTANGLE * INTIAL_POS;
    goalEnd = 500;
}





/**
 * Initialize the colors of the landscape
 * @param landscape is the map whose colors are going to be initialized
 */
void LandScape::setColorsLandScape(const LandScape &landScape) {
    // Colors
    background = landScape.background;
    roadColor[0] = landScape.roadColor[0];
    roadColor[1] = landScape.roadColor[1];
    grassColor[0] = landScape.grassColor[0];
    grassColor[1] = landScape.grassColor[1];
    rumbleColor = landScape.rumbleColor;
    dashColor = landScape.dashColor;
    width_road = landScape.width_road;
    number_tracks = landScape.number_tracks;
    limit_rumble = landScape.limit_rumble;
    terrain = landScape.terrain;
}



/**
 * Increase the code id of the map element of the step if it exits
 * @param step is the actual step of the landscape with the map elements
 * @param right controls if there are more map elements of the step
 * @param increment is how to code id has to be increased
 */
void LandScape::addMapElelementIndex(int line, bool right, int increment) {
    if (line < (int)newLines.size()) {
        MapElement &sprite = right ? newLines[line].spriteNearRight : newLines[line].spriteNearLeft;
        if (sprite.codeMapElement > -1){
            sprite.codeMapElement += increment;
        }
    }
}



/**
 * Add a landscape to follow the actual
 * @param landscape is the scenario to be added
 */
void LandScape::addNewLandScape(LandScape *landScape) {
    this->nextLeft = landScape;
    float yOffset = 0.0f;
    if (!newLines.empty()){
        yOffset = newLines[newLines.size() - 1].position_3d_y;
    }
    this->nextLeft->setOffset(yOffset);
}



/**
 * Create a fork between the actual landscape and its neighbors
 * @param left is the left landscape of the fork
 * @param right is the right landscape of the fork
 */
void LandScape::addFork(LandScape *left, LandScape *right) {
    if (this->nextRight == nullptr) {
        this->nextLeft = left;
        this->nextRight = right;
        float yOffset = 0.0f;
        if (!newLines.empty())
            yOffset = newLines[newLines.size() - 1].position_3d_y;
        this->nextLeft->setOffset(yOffset);
        if (this->nextLeft != this->nextRight)
            this->nextRight->setOffset(yOffset);

        // Add fork to current map
        if (!newLines.empty()) {
            float x = newLines[newLines.size() - 1].position_3d_x;
            float y = newLines[newLines.size() - 1].position_3d_y;
            float z = newLines[newLines.size() - 1].position_3d_z + SEGL;
            float bgX = newLines[newLines.size() - 1].bgX;
            bool mainColor = !newLines[newLines.size() - 1].mainColor;

            float xOffset = newLines[newLines.size() - 1].offsetX + LIMIT_FORK;
            for (int i = 0; i < RECTANGLES_FORK + RECTANGLES_LIMIT; i++) { // 20 rectangles to fork
                addStep(x, y, z, y, 0.0f, mainColor, MapElement(), MapElement(), bgX, xOffset, LIMIT_FORK);
                mainColor = !mainColor;
            }

            xOffset = 0.0f;
            vector<Step> auxLines;
            swap(left->newLines, auxLines);
            left->newLines.clear();
            left->newLines.reserve(auxLines.size() + RECTANGLES_LIMIT * RECTANGLE);
            z = 0.0f;
            bgX = 0.0f;
            if (!newLines[newLines.size() - 1].mainColor){
                left->addStep(x, y, z, y, 0.0f, false, MapElement(), MapElement(), bgX, xOffset);
            }
            mainColor = true;
            for (int i = 0; i < RECTANGLES_LIMIT; i++) {
                left->addStep(x, y, z, y, 0.0f, mainColor, MapElement(), MapElement(), bgX, xOffset);
                mainColor = !mainColor;
            }
            for (const Step &l : auxLines) {
                left->newLines.push_back(l);
                left->newLines.back().position_3d_z += z;
                left->newLines.back().bgX += bgX;
            }
            auxLines.clear();

            if (right != left) {
                swap(right->newLines, auxLines);
                right->newLines.clear();
                right->newLines.reserve(auxLines.size() + RECTANGLES_LIMIT * RECTANGLE);
                z = 0.0f;
                if (!newLines[newLines.size() - 1].mainColor){
                    right->addStep(x, y, z, y, 0.0f, false, MapElement(), MapElement(), bgX, xOffset);
                }
                mainColor = true;
                for (int i = 0; i < RECTANGLES_LIMIT; i++) {
                    right->addStep(x, y, z, y, 0.0f, mainColor, MapElement(), MapElement(), bgX, xOffset);
                    mainColor = !mainColor;
                }
                for (const Step &l : auxLines) {
                    right->newLines.push_back(l);
                    right->newLines.back().position_3d_z += z;
                    right->newLines.back().bgX += bgX;
                }
                auxLines.clear();
            }
        }
    }
}



/**
 * Adds the offset to the landscape to be displayed correctly
 * @param yOffset is the offset to add
 */
void LandScape::setOffset(float yOffset) {
    for (Step &l : newLines) {
        l.position_3d_y += yOffset;
    }
}




/**
 * Updates the postion of the camera in the landscape
 * @param pX is the new coordinate in the axis x of the camera
 * @param pY is the new coordinate in the axis y of the camera
 */
void LandScape::updateCamera(float pX, float pY) {
    if (pY < 0.0f)
        pY = 0.0f;
    this->posCameraX = pX;
    this->posCameraY = pY;
}



/**
 * Returns the coordiante x of the camera
 * @return
 */
float LandScape::getCameraPosX() const {
    return this->posCameraX;
}



/**
 * Returns the coordinate y of the camera
 * @return
 */
float LandScape::getCameraPosY() const {
    return this->posCameraY;
}



/**
 * Returns the name of the landscape
 * @return
 */
 string LandScape::getName() const {
    return this->name;
 }



/**
 * Returns the kind of terrain of the landscape
 * @return
 */
 int LandScape::getTerrain() const {
    return this->terrain;
 }



/**
 * Draws the percent of landscape visible with all the traffic cars in it
 * @param c is the configuration of the player
 * @param vehicles is the vector with all the traffic cars
 */
void LandScape::drawLandScape(Configuration &c, vector<TrafficCar> &vehicles, vector<RivalCar> &carRivals, const int typeOfGame) {

    const int N = static_cast<const int>(newLines.size());
    const int startPos = int(posCameraY) % N;
    const int lastPos = startPos + c.renderLen - 1;
    Step *l = getStep(startPos), *p;

    if (l->offsetX >= xFork && nextRight != nullptr) {
        if (posCameraX >= 0.0f){
            nextLeft = nextRight;
        }
        nextRight = nullptr;
    }

    // Sort the traffic cars
    vector<TrafficCar *> sortedVehicles;
    sortedVehicles.reserve(vehicles.size());
    for (TrafficCar &v : vehicles){
        sortedVehicles.push_back(&v);
    }
    sort(sortedVehicles.begin(), sortedVehicles.end(), ascendingSortTrafficCars);

    // Discard all the vehicles which are behind the player
    while (!sortedVehicles.empty() && (int(sortedVehicles.back()->getPosY()) < int(posCameraY) ||
                                       int(sortedVehicles.back()->getPosY()) > int(posCameraY) + c.renderLen - 1))
    {
        sortedVehicles.pop_back();
    }

    // Sort the traffic cars
    vector<RivalCar *> sortedRivals;
    sortedRivals.reserve(carRivals.size());
    for (RivalCar &v : carRivals){
        sortedRivals.push_back(&v);
    }
    sort(sortedRivals.begin(), sortedRivals.end(), ascendingSortRivalCars);

    // Background drawing with possible movement in curves
    drawQuad(c.w, grassColor[0], 0, 0, c.w.getSize().x, 0, c.w.getSize().y, c.w.getSize().x);
    Sprite sbg;
    sbg.setTexture(background);
    sbg.setScale( Vector2f(2.0f * (float) c.w.getSize().x / background.getSize().x, (float) c.w.getSize().y * BGS / background.getSize().y));
    sbg.setTextureRect(IntRect(0, 0, static_cast<int>(80.0f * sbg.getGlobalBounds().width), background.getSize().y));
    sbg.setPosition(0, 0);

    sbg.move(-16.0f * c.w.getSize().x - l->bgX - posCameraX, 0);
    c.w.draw(sbg);

    // Initialize lines
    float camH = l->position_3d_y + 1500.0f;
    float maxy = c.w.getSize().y;
    float x = 0, dx = 0;
    vector<int> visibleLines;

    for (int n = startPos; n <= lastPos; n++) {
        l = getStep(n);
        l->spriteNearLeft.spriteMinX = 0;
        l->spriteNearLeft.spriteMaxX = 0;
        l->spriteNearLeft.spriteToSideX = 0;
        l->spriteNearRight.spriteMinX = 0;
        l->spriteNearRight.spriteMaxX = 0;
        l->spriteNearRight.spriteToSideX = 0;

        l->project(posCameraX * width_road - x, camH, float(startPos * SEGL), c.camD,
                   c.w.getSize().x, c.w.getSize().y, width_road, n < N ? 0.0f : newLines[newLines.size() - 1].position_3d_z);

        x += dx;
        dx += l->directionCurve;

        l->clip = maxy;
        if (l->position_2d_y < maxy) {
            // This line is visible and will be drawn
            visibleLines.push_back(n);
            maxy = l->position_2d_y;
        }
    }

    // Draw the road and the map elements
    for (int n = lastPos; n >= startPos; n--) {
        l = getStep(n);
        dx -= l->directionCurve;
        x -= dx;

        // Draw road
        if (visibleLines.back() == n) {

            visibleLines.pop_back();

            Color grassRight, grass, roadRight, road, rumbleRight, rumble, dashRight, dash;
            if ((startingLandScape && n < N) || (!startingLandScape && n < N - (RECTANGLES_LIMIT + RECTANGLES_FORK) * RECTANGLE) ||
                nextLeft == nullptr) {
                grassRight = grassColor[l->mainColor];
                roadRight = roadColor[l->mainColor];
                rumbleRight = l->mainColor ? roadRight : rumbleColor;
                dashRight = l->mainColor ? dashColor : roadRight;

                grass = grassRight;
                road = roadRight;
                rumble = rumbleRight;
                dash = dashRight;
            }
            else {
                grass = nextLeft->grassColor[l->mainColor];
                road = nextLeft->roadColor[l->mainColor];
                rumble = l->mainColor ? road : nextLeft->rumbleColor;
                dash = l->mainColor ? nextLeft->dashColor : road;
                if (nextRight != nullptr) {
                    grassRight = nextRight->grassColor[l->mainColor];
                    roadRight = nextRight->roadColor[l->mainColor];
                    rumbleRight = l->mainColor ? roadRight : nextRight->rumbleColor;
                    dashRight = l->mainColor ? nextRight->dashColor : roadRight;
                }
                else {
                    grassRight = grass;
                    roadRight = road;
                    rumbleRight = rumble;
                    dashRight = dash;
                }
            }

            float prevX = l->position_2d_x, prevY = c.w.getSize().y, prevW = l->position_2d_w;
            p = l;
            if (n > 0) {
                p = getLastStep(n);
                prevX = p->position_2d_x;
                prevY = p->position_2d_y;
                prevW = p->position_2d_w;
            }

            // Drawing grass
            drawQuad(c.w, grassRight, 0, int(prevY), c.w.getSize().x, 0, int(l->position_2d_y), c.w.getSize().x);

            // Drawing road
            int x1 = int(prevX - prevW - p->scalingValue * (p->position_3d_x - p->yOffsetX * width_road) * c.w.getSize().x / 2.0f);
            int x2 = int(l->position_2d_x - l->position_2d_w - l->scalingValue * (l->position_3d_x - l->yOffsetX * width_road) * c.w.getSize().x / 2.0f);

            // Constants to draw the dashes and  the rumbles
            const int y1 = int(prevY), w1 = int(2.0f * prevW);
            const int y2 = int(l->position_2d_y);
            const int w2 = int(2.0f * l->position_2d_w);
            const int rw1 = int(prevW * limit_rumble);
            const int rw2 = int(l->position_2d_w * limit_rumble);
            const int dw1 = rw1 / 2;
            const int dw2 = rw2 / 2;

            // Draw the left rumble of the road
            drawQuad(c.w, roadRight, x1, y1, w1, x2, y2, w2);
            drawQuad(c.w, rumbleRight, x1, y1, rw1, x2, y2, rw2);

            // Draw the right rumble of the road
            drawQuad(c.w, rumbleRight, x1 + w1 - rw1, y1, rw1, x2 + w2 - rw2, y2, rw2);

            // Draw the first left dash of the road
            drawQuad(c.w, dashRight, x1 + rw1, y1, dw1, x2 + rw2, y2, dw2);

            // Draw the first right dash of the road
            drawQuad(c.w, dashRight, x1 + w1 - rw1 - dw1, y1, dw1, x2 + w2 - rw2 - dw2, y2, dw2);


            drawRoadTracks(c.w, dashRight, x1, w1, y1, dw1, x2, w2, y2, dw2);

            // Controls the colors to paint the landscape
            if (l->yOffsetX > 0.0f) {
                const int x1right = x1, x2right = x2;
                x1 = int(prevX - prevW + p->scalingValue * (p->position_3d_x - p->yOffsetX * width_road) * c.w.getSize().x / 2.0f);
                x2 = int(l->position_2d_x - l->position_2d_w + l->scalingValue * (l->position_3d_x - l->yOffsetX * width_road) * c.w.getSize().x / 2.0f);
                if ((x1 + w1) >= x1right) {

                    // Intersection
                    grassRight = grassColor[l->mainColor];
                    roadRight = roadColor[l->mainColor];
                    rumbleRight = l->mainColor ? roadRight : rumbleColor;
                    dashRight = l->mainColor ? dashColor : roadRight;

                    grass = grassRight;
                    road = roadRight;
                    rumble = rumbleRight;
                    dash = dashRight;

                    // Draw the grass
                    drawQuad(c.w, grassRight, 0, int(prevY), c.w.getSize().x, 0, int(l->position_2d_y), c.w.getSize().x);

                    // Draw the left part of the road
                    drawQuad(c.w, road, x1, y1, w1, x2, y2, w2);

                    // Draw the left rumble of the road
                    drawQuad(c.w, rumble, x1, y1, rw1, x2, y2, rw2);

                    // Draw the right part of the road
                    drawQuad(c.w, roadRight, x1right, y1, w1, x2right, y2, w2);

                    // Draw the right rumble of the road
                    drawQuad(c.w, rumbleRight, x1right + w1 - rw1, y1, rw1, x2right + w2 - rw2, y2, rw2);

                    // Draw the first dash on the right of the road
                    drawQuad(c.w, dashRight, x1right + w1 - rw1 - dw1, y1, dw1, x2right + w2 - rw2 - dw2, y2, dw2);


                    drawRoadTracks(c.w, dashRight, x1right, w1, y1, dw1, x2right, w2, y2, dw2);
                }
                else {
                    // Draw grass
                    drawQuad(c.w, grass, 0, int(prevY), int(prevX), 0, int(l->position_2d_y), int(l->position_2d_x));
                    drawQuad(c.w, road, x1, y1, w1, x2, y2, w2);

                    // Draw the left rumble of the road
                    drawQuad(c.w, rumble, x1, y1, rw1, x2, y2, rw2);

                    // Draw the right rumble of the road
                    drawQuad(c.w, rumble, x1 + w1 - rw1, y1, rw1, x2 + w2 - rw2, y2, rw2);

                    // Draw the first dash on the right side of the road
                    drawQuad(c.w, dash, x1 + w1 - rw1 - dw1, y1, dw1, x2 + w2 - rw2 - dw2, y2, dw2); // First right dash
                }

                // Draw the first dash on the left of the road
                drawQuad(c.w, dash, x1 + rw1, y1, dw1, x2 + rw2, y2, dw2);


                drawRoadTracks(c.w, dash, x1, w1, y1, dw1, x2, w2, y2, dw2);
            }
        }

        // Draw the map elements
        // Near left map element
        if (l->spriteNearLeft.codeMapElement > -1) {
            if (n < N || nextLeft == nullptr){
                l->drawSprite(c.w, mapElementTextures, hittMapElementsCofs, hitKindCofs,
                              scalingFactors, l->spriteNearLeft, true);
            }
            else {
                l->drawSprite(c.w, nextLeft->mapElementTextures, nextLeft->hittMapElementsCofs,
                              nextLeft->hitKindCofs, nextLeft->scalingFactors, l->spriteNearLeft, true);
            }
        }
        // Near right map element
        if (l->spriteNearRight.codeMapElement > -1) {
            if (n < N || nextLeft == nullptr){
                l->drawSprite(c.w, mapElementTextures, hittMapElementsCofs, hitKindCofs,
                              scalingFactors, l->spriteNearRight, false);
            }
            else {
                l->drawSprite(c.w, nextLeft->mapElementTextures, nextLeft->hittMapElementsCofs,
                              nextLeft->hitKindCofs, nextLeft->scalingFactors, l->spriteNearRight, false);
            }
        }
        // Far left map element
        if (l->spriteFarLeft.codeMapElement > -1) {
            if (n < N || nextLeft == nullptr){
                l->drawSprite(c.w, mapElementTextures, hittMapElementsCofs, hitKindCofs,
                              scalingFactors, l->spriteFarLeft, true);
            }
            else {
                l->drawSprite(c.w, nextLeft->mapElementTextures, nextLeft->hittMapElementsCofs,
                              nextLeft->hitKindCofs, nextLeft->scalingFactors, l->spriteFarLeft, true);
            }
        }
        // Far right map element
        if (l->spriteFarRight.codeMapElement > -1) {
            if (n < N || nextLeft == nullptr){
                l->drawSprite(c.w, mapElementTextures, hittMapElementsCofs, hitKindCofs,
                              scalingFactors, l->spriteFarRight, false);
            }
            else {
                l->drawSprite(c.w, nextLeft->mapElementTextures, nextLeft->hittMapElementsCofs,
                              nextLeft->hitKindCofs, nextLeft->scalingFactors, l->spriteFarRight, false);
            }
        }

        if (typeOfGame == 0 || typeOfGame == 2){
            // Draw rival cars
            while (!sortedRivals.empty() && int(sortedRivals.back()->getPosY()) == n - startPos + int(posCameraY)) {

                RivalCar *v = sortedRivals.back();
                Sprite sv;
                sv.setTexture(*v->getCurrentTexture(), true);
                const float width = v->getScalingFactor() * sv.getTextureRect().width;
                const float widthOri = sv.getTextureRect().width;
                const float height = v->getScalingFactor() * sv.getTextureRect().height;
                const float heightOri = sv.getTextureRect().height;
                float destW = width * l->position_2d_w / SCALE_RESOLUTION;
                float destH = height * l->position_2d_w / SCALE_RESOLUTION;

                sv.setScale(destW / widthOri, destH / heightOri);
                v->setMinScreenX(l->position_2d_x + l->position_2d_w * v->getPosX() - sv.getGlobalBounds().width / 2.0f);
                v->setMaxScreenX(v->getMinScreenX() + sv.getGlobalBounds().width);
                sv.setPosition(v->getMinScreenX(), l->position_2d_y - destH);
                c.w.draw(sv);

                // Check if the rival is smoking or not
                if (v->getSmoking()){
                    // Draw the smoking of the rival car
                    v->drawSmokingPlayer(c, destW, destH, widthOri, heightOri, sv.getPosition().y + sv.getGlobalBounds().height * 0.8f);
                }

                sortedRivals.pop_back();
            }
        }

        if (typeOfGame != 2){
            // Draw vehicles
            while (!sortedVehicles.empty() && int(sortedVehicles.back()->getPosY()) == n - startPos + int(posCameraY)) {
                TrafficCar *v = sortedVehicles.back();

                Sprite sv;
                sv.setTexture(*v->getCurrentTexture(), true);
                const float width = v->getScale() * sv.getTextureRect().width;
                const float widthOri = sv.getTextureRect().width;
                const float height = v->getScale() * sv.getTextureRect().height;
                const float heightOri = sv.getTextureRect().height;
                float destW = width * l->position_2d_w / SCALE_RESOLUTION;
                float destH = height * l->position_2d_w / SCALE_RESOLUTION;

                sv.setScale(destW / widthOri, destH / heightOri);
                v->setMinScreenX(l->position_2d_x + l->position_2d_w * v->getPosX() - sv.getGlobalBounds().width / 2.0f);
                v->setMaxScreenX(v->getMinScreenX() + sv.getGlobalBounds().width);
                sv.setPosition(v->getMinScreenX(), l->position_2d_y - destH);
                c.w.draw(sv);

                sortedVehicles.pop_back();
            }
        }
    }
}



/**
 * Returns true if the vehicle has crashed with any element of the landscape or with its borders
 * @param c is the configuration of the player
 * @param prevY is the previous position of the player in the axis y of the landscape
 * @param currentY is the actual position of the player in the axis y of the landscape
 * @param currentX is the actual position of the player in the axis x of the landscape
 * @param minX is the minimum threshold to detect a collision
 * @param maxX is the maximum threshold to detect a collision
 * @param crashPos is the possible position of crash detected
 * @return
 */
bool LandScape::hasCrashed(Configuration &c, float prevY, float currentY, float currentX, float minX, float maxX,
                     float &crashPos, const int typeOfGame) const
{
    if (inFork(currentY)){
        // has left the map
        if (abs(currentX) > 30.0f){
            crashPos = posCameraY;
            return true;
        }
    }
    else {
        if (abs(currentX) > 2.8f){
            crashPos = posCameraY;
            return true;
        }
    }

    Step l;
    for (int n = int(posCameraY); n < int(posCameraY) + c.renderLen; n++) {
        l = getStep(n);

        float spriteMinX, spriteMaxX;
        int spriteNum;
        for (int i = 0; i < 4; i++) {
            if (i == 0) {
                spriteNum = l.spriteNearLeft.codeMapElement;
                spriteMinX = l.spriteNearLeft.spriteMinX;
                spriteMaxX = l.spriteNearLeft.spriteMaxX;
            }
            else if (i == 1) {
                spriteNum = l.spriteNearLeft.codeMapElement;
                spriteMinX = l.spriteNearLeft.spriteMinX + l.spriteNearLeft.spriteToSideX;
                spriteMaxX = l.spriteNearLeft.spriteMaxX + l.spriteNearLeft.spriteToSideX;
            }
            else if (i == 2) {
                spriteNum = l.spriteNearRight.codeMapElement;
                spriteMinX = l.spriteNearRight.spriteMinX;
                spriteMaxX = l.spriteNearRight.spriteMaxX;
            }
            else {
                spriteNum = l.spriteNearRight.codeMapElement;
                spriteMinX = l.spriteNearRight.spriteMinX + l.spriteNearRight.spriteToSideX;
                spriteMaxX = l.spriteNearRight.spriteMaxX + l.spriteNearRight.spriteToSideX;
            }

            if (spriteNum != -1 && spriteMinX != spriteMaxX && // l has an object that can crash
                prevY <= float(n) && currentY >= float(n) && // y matches
                ((minX >= spriteMinX && minX <= spriteMaxX) || (maxX >= spriteMinX && maxX <= spriteMaxX) ||
                 (spriteMinX >= minX && spriteMinX <= maxX) ||
                 (spriteMaxX >= minX && spriteMaxX <= maxX))) { // x matches
                crashPos = float(n);
                return true;
            }
        }
    }
    return false;
}



/**
 * Returns true if the actual position in axis x is outside the road.
 * Otherwise returns false
 * @param currentX is the position on axis x
 * @param currentY is the position on axis y
 * @return
 */
bool LandScape::isOutSideRoad(float currentX, float currentY) const {
    float offset;
    if (posCameraX >= 0.0f){
        offset = -newLines[int(currentY) % newLines.size()].yOffsetX;
    }
    else{
        offset = newLines[int(currentY) % newLines.size()].yOffsetX;
    }
    return abs(currentX + offset) > 1.0f;
}



/**
 * Returns the curvature coefficient corresponding to the currentY rectangle. The coefficient is positive if the
 * curve is to the right, negative if it's to the left and 0 if it's a straight line
 * @param currentY currentY is the current of the landscape where is the player
 * @return
 */
float LandScape::getCurveCoefficient(float currentY) const {
    return getStep(int(currentY)).directionCurve;
}



/**
 * Returns the elevation corresponding to the currentY rectangle based on the previous rectangle.
 * @param currentY is the current of the landscape where is the player
 * @return
 */
Vehicle::Elevation LandScape::getElevation(float currentY) const {
    const int n = int(currentY);
    const Step currentLine = getStep(n);
    const Step prevLine = getLastStep(n);
    if (n != 0 && abs(currentLine.position_3d_y) > 1000 && currentLine.position_3d_y > prevLine.position_3d_y + 1.0f){
        return Vehicle::Elevation::UP;
    }
    else if (n != 0 && abs(currentLine.position_3d_y) > 1000 && currentLine.position_3d_y < prevLine.position_3d_y - 1.0f){
        return Vehicle::Elevation::DOWN;
    }
    else {
        return Vehicle::Elevation::FLAT;
    }
}



/**
 * Returns true  if the landscae has been finished.
 * Otherwise returns false
 * @return
 */
bool LandScape::isOutSideLandScape() const {
    if (startingLandScape || finalLandScape || middleLandScape || (nextLeft != nullptr && nextLeft->finalLandScape) ||
        (nextLeft != nullptr && nextLeft->isMiddleMap())){
        return posCameraY >= newLines.size();
    }
    else {
        return posCameraY >= float(newLines.size() - RECTANGLES_LIMIT * RECTANGLE);
    }
}



/**
 * Returns the height of the landscape
 * @return
 */
float LandScape::getMaxY() const {
    if (startingLandScape || finalLandScape || middleLandScape || (nextLeft != nullptr && nextLeft->finalLandScape) ||
        (nextLeft != nullptr && nextLeft->isMiddleMap())){
        return newLines.size();
    }
    else {
        return float(newLines.size() - RECTANGLES_LIMIT * RECTANGLE);
    }
}



/**
 * Returns the offset of the road in the axis x.
 * @return
 */
float LandScape::getOffsetX() const {
    if (posCameraX >= 0.0f){
        return -newLines[newLines.size() - 1].yOffsetX;
    }
    else {
        return newLines[newLines.size() - 1].yOffsetX;
    }
}



/**
 * Returns true if the player is on a fork. Otherwise returns false
 * @param currentY is the coordinate in axis Y which to be tested to know
 *        if the player is on a fork or not
 * @return
 */
bool LandScape::inFork(const float currentY) const {
    if (startingLandScape || finalLandScape || middleLandScape || (nextLeft != nullptr && nextLeft->finalLandScape)){
        return false;
    }
    else {
        return currentY >= float(newLines.size() - (RECTANGLES_FORK + RECTANGLES_LIMIT) * RECTANGLE);
    }
}



/**
 * Returns the next landscape or null if it is the last one
 * @return
 */
LandScape *LandScape::getNextLeft() const {
    return nextLeft;
}



/**
 * Returns true if is the init landscape. Otherwise returns false
 * @return
 */
bool LandScape::isStartingLandScape() const {
    return startingLandScape;
}



/**
 * Returns true if is the goal landscape. Otherwise returns false
 * @return
 */
bool LandScape::isFinalLandScape() const {
    return finalLandScape;
}



bool LandScape::isMiddleMap() const {
    return middleLandScape;
}


/**
 * Returns the time to complete the map
 * @return
 */
int LandScape::getTimeToPlay() const {
    return timeToPlay;
}



/**
 * Returns the coordinates of the checkpoints
 * @return
 */
 vector<int> LandScape::getCheckPointPositions() const{
    return checkPointPositions;
 }



/**
 * Draw a rectangle with a width and height in the screen console
 * @param w is the console window of the game
 * @param c is the color with the rectangle is going to be painted
 * @param x1 is the lower bound vertex coordinate in axis x of the rectangle
 * @param y1 is the lower bound vertex coordinate in axis y of the rectangle
 * @param w1 is the width of the rectangle
 * @param x2 is the upper bound vertex coordinate in axis x of the rectangle
 * @param y2 is the upper bound vertex coordinate in axis y of the rectangle
 * @param w2 is the height of the rectangle
 */
inline void drawQuad(RenderTexture &w, Color c, int x1, int y1, int w1, int x2, int y2, int w2) {
    ConvexShape shape(4);
    shape.setFillColor(c);
    shape.setPoint(0, Vector2f(x1, y1));
    shape.setPoint(1, Vector2f(x2, y2));
    shape.setPoint(2, Vector2f(x2 + w2, y2));
    shape.setPoint(3, Vector2f(x1 + w1, y1));
    w.draw(shape);
}



/**
 * Returns true is the traffic car v1 is lower than the traffic car v2.
 * Otherwise returns false
 */
bool ascendingSortTrafficCars(const TrafficCar *v1, const TrafficCar *v2) {
    return v1->getPosY() < v2->getPosY();
}



/**
 * Returns true is the traffic car v1 is lower than the traffic car v2.
 * Otherwise returns false
 */
bool ascendingSortRivalCars(const RivalCar *v1, const RivalCar *v2) {
    return v1->getPosY() < v2->getPosY();
}



/*
 * Returns true is the traffic car v1 is lower than the traffic car v2.
 * Otherwise returns false
 */
bool ascendingRanking(const float p1, const float p2){
    return p1 >= p2;
}
