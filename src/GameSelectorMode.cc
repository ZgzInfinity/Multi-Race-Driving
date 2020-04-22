

#include "../include/GameSelectorMode.h"



/**
 * Constructor by default
 */
GameSelectorMode::GameSelectorMode(){}



/**
 * Constructor of the data type Game mode selector
 * @param difficult is the difficult level validated by the player
 * @param game is the game mode selected by the user
 */
GameSelectorMode::GameSelectorMode(const int& difficult, const int& game){

    // Assignment of the variables
    difficultMode = difficult;

    // Game mode selected by the player
    gameMode = game;

    // Control the available vehicles of the game mode
    motorbikeIsOn = false;
    minivanIsOn = false;
    truckIsOn = false;
    ferrariIsOn = false;
}


/**
 * Get the vector with the different paths of the landscapes
 */
vector<string> GameSelectorMode::getVectorOfLandScapes(){
    return pathLandScapeFiles;
}



inline void GameSelectorMode::controlAvailableVehicles(xml_node<> *worldTourNode){
    // Iteration throughout vehicles of the game mode
    for (xml_node<> *vehicleNode = worldTourNode->first_node(); vehicleNode; vehicleNode = vehicleNode->next_sibling()){
        // Get the type of vehicle
        string typeOfVehicle = vehicleNode->name();
        // Iteration of all the attributes of the vehicles
        for (xml_node<> *attributeVehicle = vehicleNode->first_node(); attributeVehicle; attributeVehicle = attributeVehicle->next_sibling()){
            // Check if it's the node that controls the available vehicles of the game mode
            if ((string)attributeVehicle->name() == "Availability"){
                // Get the availability of the vehicle
                int availability = stoi(attributeVehicle->value());
                // Check if the vehicle is available or not
                if (availability == 1){
                    // Check the kind of vehicle
                    if (typeOfVehicle == "Motorbike"){
                        // The vehicle is available and the path is read
                        motorbikeIsOn = true;
                        continue;
                    }
                    else if (typeOfVehicle == "Ferrari"){
                        // The vehicle is available and the path is read
                        ferrariIsOn = true;
                        continue;
                    }
                    else if (typeOfVehicle == "Minivan"){
                        // The vehicle is available and the path is read
                        minivanIsOn = true;
                        continue;
                    }
                    else if (typeOfVehicle == "Truck"){
                        // The vehicle is available and the path is read
                        truckIsOn = true;
                        continue;
                    }
                }
                else {
                    // Continue to the next vehicle
                    break;
                }
            }
            // Check if it's the node that controls the available vehicles of the game mode
            else if ((string)attributeVehicle->name() == "Path"){
                // Get the path of the vehicle due to it's available
                string pathVehicle = attributeVehicle->value();
            }
        }
    }
}




inline void GameSelectorMode::processFirstPanel(xml_node<> *panel, string& pathSpeedIndicator, int& posX, int& posY,
                                                string& fontPath, int& sizeText, int& posXText, int& posYText, Color& colorText){
    // Iteration of all the sub panels of the main panel
    for (xml_node<> *panelNode = panel->first_node(); panelNode; panelNode = panelNode->next_sibling()){
        // Check if it's the node that controls the speed panel
        if ((string)panelNode->name() == "Path"){
            pathSpeedIndicator = panelNode->value();
        }
        // Check if it's the node that controls the coordinate in axis x of the speed panel
        else if ((string)panelNode->name() == "PositionX"){
            posX = stoi(panelNode->value());
        }
        // Check if it's the node that controls the coordinate in axis y of the speed panel
        else if ((string)panelNode->name() == "PositionY"){
            posY = stoi(panelNode->value());
        }
        // Check if it's the node that controls the text of the speed panel
        else if ((string)panelNode->name() == "Text"){
            // Process the text information panel
            processTextPanel(panelNode, fontPath, sizeText, posXText, posYText, colorText);
        }
    }
}



inline void GameSelectorMode::processTextPanel(xml_node<> *panelNode, string& fontPath, int& sizeText, int& posXText, int& posYText,
                                               Color& colorText){
    // Process the time panel or the destiny panel
    for (xml_node<> *textNode = panelNode->first_node(); textNode; textNode = textNode->next_sibling()){
        // Check if it's the node that controls the speed panel
        if ((string)textNode->name() == "Font"){
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



inline void GameSelectorMode::processSecondPanel(xml_node<> *panel, string& fontPathTimeText, int& sizeTimeText,
                                                 int& posXTimeText, int& posYTimeText, string& fontPathTimeIndicator,
                                                 int& sizeTimeIndicator, int& posXTimeIndicator, int& posYTimeIndicator,
                                                 string& fontPathDestinyText, int& sizeDestinyText, int& posXDestinyText,
                                                 int& posYDestinyText, string& fontPathDistanceText, int& sizeDistanceText,
                                                 int& posXDistanceText, int& posYDistanceText, Color& colorTimeText,
                                                 Color& colorTimeIndicator, Color& colorDestinyText, Color& colorDistanceText)
{
    // Store the information of the time panel
    for (xml_node<> *panelNode = panel->first_node(); panelNode; panelNode = panelNode->next_sibling()){
        // Iteration of all the attributes of the text
        if ((string)panelNode->name() == "TimeText"){
            // Store the text information of the time panel
            processTextPanel(panelNode, fontPathTimeText, sizeTimeText, posXTimeText, posYTimeText, colorTimeText);
            continue;
        }
        else if ((string)panelNode->name() == "TimeIndicator"){
            // Store the text information of the time panel
            processTextPanel(panelNode, fontPathTimeIndicator, sizeTimeIndicator, posXTimeIndicator, posYTimeIndicator, colorTimeIndicator);
            continue;
        }
        else if ((string)panelNode->name() == "DestinyText"){
            // Store the text information of the destiny panel
            processTextPanel(panelNode, fontPathDestinyText, sizeDestinyText, posXDestinyText, posYDestinyText, colorDestinyText);
            continue;
        }
        else if ((string)panelNode->name() == "DistanceText"){
            // Store the text information of the destiny panel
            processTextPanel(panelNode, fontPathDistanceText, sizeDistanceText, posXDistanceText, posYDistanceText, colorDistanceText);
            continue;
        }
    }
}



void GameSelectorMode::loadWorldTourMode(char* pathFile, Environment& e, vector<string>& landscapePaths){
    // Read the xml configuration file from the world tour mode
    xml_document<> doc;
    file<> file(pathFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *mainNode = doc.first_node();

    // Variables to store the information of the speed indicator
    string pathSpeedIndicator, fontPathSpeedPanel;
    int posXSpeedPanel, posYSpeedPanel, sizeTextSpeedPanel, posXTextSpeedPanel, posYTextSpeedPanel;

    // Variables to store the information of the elapsed indicator
    string pathElapsedIndicator, fontPathElapsedPanel;
    int posXElapsedPanel, posYElapsedPanel, sizeTextElapsedPanel, posXTextElapsedPanel, posYTextElapsedPanel;

    // Variables to store the information of the time panel
    string fontPathTimeText;
    int sizeTimeText, posXTimeText, posYTimeText;

    string fontPathTimeIndicator;
    int sizeTimeIndicator, posXTimeIndicator, posYTimeIndicator;

    // Variables to store the information of the destiny panel
    string fontPathDestinyText;
    int sizeDestinyText, posXDestinyText, posYDestinyText;

    string fontPathDestinyIndicator;
    int sizeDestinyIndicator, posXDestinyIndicator, posYDestinyIndicator;

    // Color of the different texts of the panels
    Color colorSpeedPanel, colorElapsedPanel, colorTimeText, colorTimeIndicator,
          colorDestinyText, colorDestinyIndicator;

    // Iteration throughout the nodes of the file
    for (xml_node<> *worldTourNode = mainNode->first_node(); worldTourNode; worldTourNode = worldTourNode->next_sibling()){
        // Check if it's the node that controls the available vehicles of the game mode
        if ((string)worldTourNode->name() == "Vehicles"){
            // Control the vehicles which are available
            controlAvailableVehicles(worldTourNode);
        }
        // Check if it's the node that control the game information panel
        else if ((string)worldTourNode->name() == "GamePanel"){
            // Iteration of all the sub panels of the main panel
            for (xml_node<> *panel = worldTourNode->first_node(); panel; panel = panel->next_sibling()){
                // Check the actual node read and process the speed panel
                if ((string)panel->name() == "SpeedPanel"){
                    // Check the speed panel
                    processFirstPanel(panel, pathSpeedIndicator, posXSpeedPanel, posYSpeedPanel, fontPathSpeedPanel,
                                      sizeTextSpeedPanel, posXTextSpeedPanel, posYTextSpeedPanel, colorSpeedPanel);
                }
                // Check the actual node read and process the elapsed panel
                else if ((string)panel->name() == "ElapsedPanel"){
                    // Check the elapsed panel
                    processFirstPanel(panel, pathElapsedIndicator, posXElapsedPanel, posYElapsedPanel, fontPathElapsedPanel,
                                      sizeTextElapsedPanel, posXTextElapsedPanel, posYTextElapsedPanel, colorElapsedPanel);
                }
                // Check the actual node read and process the time panel
                else if ((string)panel->name() == "TimePanel"){
                    // Check the speed panel
                    processSecondPanel(panel, fontPathTimeText, sizeTimeText, posXTimeText, posYTimeText, fontPathTimeIndicator,
                                       sizeTimeIndicator, posXTimeIndicator, posYTimeIndicator, fontPathDestinyText, sizeDestinyText,
                                       posXDestinyText, posYDestinyText, fontPathDestinyIndicator, sizeDestinyIndicator,
                                       posXDestinyIndicator, posYDestinyIndicator, colorTimeText, colorTimeIndicator,
                                       colorDestinyText, colorDestinyIndicator);
                }
                // Check the actual node read and process the destiny panel
                else if ((string)panel->name() == "DestinyPanel"){
                    // Check the destiny panel
                    processSecondPanel(panel, fontPathTimeText, sizeTimeText, posXTimeText, posYTimeText, fontPathTimeIndicator,
                                       sizeTimeIndicator, posXTimeIndicator, posYTimeIndicator, fontPathDestinyText, sizeDestinyText,
                                       posXDestinyText, posYDestinyText, fontPathDestinyIndicator, sizeDestinyIndicator,
                                       posXDestinyIndicator, posYDestinyIndicator, colorTimeText, colorTimeIndicator,
                                       colorDestinyText, colorDestinyIndicator);
                }
            }
        }
        // Check the actual node read and process the destiny panel
        else if ((string)worldTourNode->name() == "LandScapes"){
            // Store the paths of all the landscapes to play
            for (xml_node<> *panel = worldTourNode->first_node(); panel; panel = panel->next_sibling()){
                // Store the path to play
                landscapePaths.push_back((string)panel->value());
            }
        }
    }
    // Configuration of the environment with all the information read
    e.configure(pathSpeedIndicator, fontPathSpeedPanel, posXSpeedPanel, posYSpeedPanel, sizeTextSpeedPanel, posXTextSpeedPanel,
                posYTextSpeedPanel, pathElapsedIndicator, fontPathElapsedPanel, posXElapsedPanel, posYElapsedPanel, sizeTextElapsedPanel,
                posXTextElapsedPanel, posYTextElapsedPanel, fontPathTimeText, sizeTimeText, posXTimeText, posYTimeText, fontPathTimeIndicator,
                sizeTimeIndicator, posXTimeIndicator, posYTimeIndicator, fontPathDestinyText, sizeDestinyText, posXDestinyText,
                posYDestinyText, fontPathDestinyIndicator, sizeDestinyIndicator, posXDestinyIndicator, posYDestinyIndicator,
                colorSpeedPanel, colorElapsedPanel, colorTimeText, colorTimeIndicator, colorDestinyText, colorDestinyIndicator);
}



void GameSelectorMode::loadOutRun(char* pathFile, Environment& e, vector<string>& landscapePaths){
    // Read the xml configuration file from the world tour mode
    xml_document<> doc;
    file<> file(pathFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *mainNode = doc.first_node();

    // Variables to store the information of the speed indicator
    string pathSpeedIndicator, fontPathSpeedPanel;
    int posXSpeedPanel, posYSpeedPanel, sizeTextSpeedPanel, posXTextSpeedPanel, posYTextSpeedPanel;

    // Variables to store the information of the elapsed indicator
    string pathElapsedIndicator, fontPathElapsedPanel;
    int posXElapsedPanel, posYElapsedPanel, sizeTextElapsedPanel, posXTextElapsedPanel, posYTextElapsedPanel;

    // Variables to store the information of the time panel
    string fontPathTimeText;
    int sizeTimeText, posXTimeText, posYTimeText;

    string fontPathTimeIndicator;
    int sizeTimeIndicator, posXTimeIndicator, posYTimeIndicator;

    // Variables to store the information of the destiny panel
    string fontPathDestinyText;
    int sizeDestinyText, posXDestinyText, posYDestinyText;

    string fontPathDestinyIndicator;
    int sizeDestinyIndicator, posXDestinyIndicator, posYDestinyIndicator;

    // Color of the different texts of the panels
    Color colorSpeedPanel, colorElapsedPanel, colorTimeText, colorTimeIndicator,
          colorDestinyText, colorDestinyIndicator;

    // Iteration throughout the nodes of the file
    for (xml_node<> *worldTourNode = mainNode->first_node(); worldTourNode; worldTourNode = worldTourNode->next_sibling()){
        // Check if it's the node that controls the available vehicles of the game mode
        if ((string)worldTourNode->name() == "Vehicles"){
            // Control the vehicles which are available
            controlAvailableVehicles(worldTourNode);
        }
        // Check if it's the node that control the game information panel
        else if ((string)worldTourNode->name() == "GamePanel"){
            // Iteration of all the sub panels of the main panel
            for (xml_node<> *panel = worldTourNode->first_node(); panel; panel = panel->next_sibling()){
                // Check the actual node read and process the speed panel
                if ((string)panel->name() == "SpeedPanel"){
                    // Check the speed panel
                    processFirstPanel(panel, pathSpeedIndicator, posXSpeedPanel, posYSpeedPanel, fontPathSpeedPanel,
                                      sizeTextSpeedPanel, posXTextSpeedPanel, posYTextSpeedPanel, colorSpeedPanel);
                }
                // Check the actual node read and process the elapsed panel
                else if ((string)panel->name() == "ElapsedPanel"){
                    // Check the elapsed panel
                    processFirstPanel(panel, pathElapsedIndicator, posXElapsedPanel, posYElapsedPanel, fontPathElapsedPanel,
                                      sizeTextElapsedPanel, posXTextElapsedPanel, posYTextElapsedPanel, colorElapsedPanel);
                }
                // Check the actual node read and process the time panel
                else if ((string)panel->name() == "TimePanel"){
                    // Check the speed panel
                    processSecondPanel(panel, fontPathTimeText, sizeTimeText, posXTimeText, posYTimeText, fontPathTimeIndicator,
                                       sizeTimeIndicator, posXTimeIndicator, posYTimeIndicator, fontPathDestinyText, sizeDestinyText,
                                       posXDestinyText, posYDestinyText, fontPathDestinyIndicator, sizeDestinyIndicator,
                                       posXDestinyIndicator, posYDestinyIndicator, colorTimeText, colorTimeIndicator,
                                       colorDestinyText, colorDestinyIndicator);
                }
                // Check the actual node read and process the destiny panel
                else if ((string)panel->name() == "DestinyPanel"){
                    // Check the destiny panel
                    processSecondPanel(panel, fontPathTimeText, sizeTimeText, posXTimeText, posYTimeText, fontPathTimeIndicator,
                                       sizeTimeIndicator, posXTimeIndicator, posYTimeIndicator, fontPathDestinyText, sizeDestinyText,
                                       posXDestinyText, posYDestinyText, fontPathDestinyIndicator, sizeDestinyIndicator,
                                       posXDestinyIndicator, posYDestinyIndicator, colorTimeText, colorTimeIndicator,
                                       colorDestinyText, colorDestinyIndicator);
                }
            }
        }
        // Check the actual node read and process the destiny panel
        else if ((string)worldTourNode->name() == "LandScapes"){
            // Store the paths of all the landscapes to play
            for (xml_node<> *panel = worldTourNode->first_node(); panel; panel = panel->next_sibling()){
                // Store the path to play
                landscapePaths.push_back((string)panel->value());
            }
        }
    }
    // Configuration of the environment with all the information read
    e.configure(pathSpeedIndicator, fontPathSpeedPanel, posXSpeedPanel, posYSpeedPanel, sizeTextSpeedPanel, posXTextSpeedPanel,
                posYTextSpeedPanel, pathElapsedIndicator, fontPathElapsedPanel, posXElapsedPanel, posYElapsedPanel, sizeTextElapsedPanel,
                posXTextElapsedPanel, posYTextElapsedPanel, fontPathTimeText, sizeTimeText, posXTimeText, posYTimeText, fontPathTimeIndicator,
                sizeTimeIndicator, posXTimeIndicator, posYTimeIndicator, fontPathDestinyText, sizeDestinyText, posXDestinyText,
                posYDestinyText, fontPathDestinyIndicator, sizeDestinyIndicator, posXDestinyIndicator, posYDestinyIndicator,
                colorSpeedPanel, colorElapsedPanel, colorTimeText, colorTimeIndicator, colorDestinyText, colorDestinyIndicator);
}


/**
* Load the game mode from the correspondent xml file of configuration
* @param gameMode is the mode selected by the player to play
* @param e is the environment of the game which is going to be configured
*/
void GameSelectorMode::loadFileConfigurationMode(Environment& e, vector<string>& landscapePaths){
    // Check the game mode selected by the user to load the correct configuration file
    switch(gameMode){
        case 0:
            // Executing the world tour mode
            gameStatus = WORLD_TOUR;
            pathFile = "Configuration/GameModes/WorldTour.xml";
            // Load the xml configuration file of world tour mode
            loadWorldTourMode(pathFile, e, landscapePaths);
            break;
        case 1:
            // Executing the out run mode
            gameStatus = OUT_RUN;
            pathFile = "Configuration/GameModes/OutRun.xml";
            // Load the xml configuration file of out run mode
            loadOutRun(pathFile, e, landscapePaths);
            break;
        case 2:
            // Executing the pole position mode
            gameStatus = POLE_POSITION;
            // Load the xml configuration file of pole position mode
            pathFile = "Configuration/GameModes/PolePosition.xml";
            // loadPolePosition();
            break;
        case 3:
            // Executing the driving fury mode
            gameStatus = DRIVING_FURY;
            // Load the xml configuration file of driving fury mode
            pathFile = "Configuration/GameModes/DrivingFury.xml";
            // loadDrivingFury();
            break;
        case 4:
            // Executing the delivery mode
            gameStatus = DELIVERY;
            // Load the xml configuration file of delivery mode
            pathFile = "Configuration/GameModes/Delivery.xml";
            // loadDelivery();
            break;
        case 5:
            // Executing the demarrage mode
            gameStatus = DEMARRAGE;
            // Load the xml configuration file of demarrage mode
            pathFile = "Configuration/GameModes/Demarrage.xml";
            // loadDemarrage();
            break;
        default:
            // Error while selecting the game mode
            cerr << "Error while selecting game mode";
    }
}
