

#include "../include/Score.h"

Score::Score(unsigned long score, const string &name, int minutes, int secs, int centsSecond) : score(score),
                                                                                                name(name),
                                                                                                minutes(minutes),
                                                                                                secs(secs),
                                                                                                cents_second(
                                                                                                        centsSecond) {}

vector<Score> getGlobalScores(Configuration& c, const int typeOfGame) {

    vector<Score> globalScores;

        // xml file which stores the player with the highest score in the level
    string path = "Data/Records/";

    // Control the game mode selected by the player
    switch(typeOfGame){
        case 1:
            path += "OutRun/Scores_";
            break;
        case 3:
            path += "DrivingFury/Scores_";
            break;
        case 4:
            path += "Derramage/Scores_";
    }

    // Control if the player has played with the AI enabled or not
    if (c.enableAI){
        // Active AI
        path += "Enabled_";
    }
    else {
        // Disabled AI
        path += "Disabled_";
    }

    // Control the difficulty of the game
    switch (c.level){
        case EASY:
            path += "Easy.xml";
            break;
        case NORMAL:
            path += "Normal.xml";
            break;
        case HARD:
            path += "Hard.xml";
    }

    // Open the xml file of the scenario
    char* pFile = const_cast<char*>(path.c_str());
    xml_document<> doc;
    file<> file(pFile);
    // Parsing the content of file
    doc.parse<0>(file.data());
    // Get the principal node of the file
    xml_node<> *menuNode = doc.first_node()->first_node();

    // Local variables to store the information of the players
    unsigned long score;
    string name;
    int minutes, secs, cents_second;

    // Iterate to get the information of the best players of the game mode
    for (xml_node<> *players = menuNode->first_node(); players; players = players->next_sibling()){
        // Get the information of each player
        for (xml_node<> *property = players->first_node(); property; property = property->next_sibling()){
            // Get the score of the player
            if ((string)property->name() == "Score"){
                // Get the background image of the menu
                score = stoul(property->value(), nullptr, 0);
            }
            // Get the name of the player
            else if ((string)property->name() == "Name"){
                // Get the background image of the menu
                name = (string)property->value();
            }
            // Get the minutes of the time of the player
            else if ((string)property->name() == "Minutes"){
                // Get the background image of the menu
                minutes = stoi(property->value());
            }
            // Get the seconds of the time of the player
            else if ((string)property->name() == "Seconds"){
                // Get the background image of the menu
                secs = stoi(property->value());
            }
            // Get the hundredths of second of the time of the player
            else if ((string)property->name() == "HundredthsOfSecond"){
                // Get the background image of the menu
                cents_second = stoi(property->value());

                // Add the score read from the xml file
                globalScores.emplace_back(score, name, minutes, secs, cents_second);
            }
        }
    }

    return globalScores;
}

int isNewRecord(const vector<Score> &globalScores, unsigned long score) {
    int i = 0;
    for (; i < (int)globalScores.size() && i < 7; i++) {
        if (globalScores[i].score < score)
            return i;
    }

    if (globalScores.size() < 7)
        return i;

    return -1;
}

bool saveNewRecord(const vector<Score> &globalScores, const Score &newRecord, const int typeOfGame, Configuration & c) {

    // xml file which stores the player with the highest score in the level
    string path = "Data/Records/OutRun/Scores_";

    // Control the difficulty of the game
    switch (c.level){
        case EASY:
            path += "Easy.xml";
            break;
        case NORMAL:
            path += "Normal.xml";
            break;
        case HARD:
            path += "Hard.xml";
    }

    ofstream theFile (path);
    xml_document<> doc;

    // Add the headers to the file
    xml_node<>* decl = doc.allocate_node(node_declaration);
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "UTF-8"));
    doc.append_node(decl);

     // Create the node record
    string nameNode;

    switch(typeOfGame){
        case 1:
            nameNode = "RecordsOutRun";
            break;
        case 3:
            nameNode = "RecordsDrivingFury";
            break;
        case 4:
            nameNode = "RecordsDerramage";
    }

    xml_node<>* root = doc.allocate_node(node_element, nameNode.c_str());
    doc.append_node(root);

     // Create the node of the players
    xml_node<>* players = doc.allocate_node(node_element, "Players");
    root->append_node(players);

    // Control the position where the player must be stored in the ranking
    bool foundPosition = false;

    // Number of players checked
    int numPlayers = 0;

    string tags[7] = {"P1", "P2", "P3", "P4", "P5", "P6", "P7"};

    // While the position has not been found
    while (!foundPosition){
        // Check the actual player
        if (globalScores[numPlayers].score >= newRecord.score){

            // The actual player goes first
            xml_node<>* player = doc.allocate_node(node_element, tags[numPlayers].c_str());
            players->append_node(player);

            // Create the score node
            xml_node<>* score = doc.allocate_node(node_element, "Score");
            player->append_node(score);
            score->value(to_string(globalScores[numPlayers].score).c_str());

            // Create the name node
            xml_node<>* name = doc.allocate_node(node_element, "Name");
            player->append_node(name);
            name->value(globalScores[numPlayers].name.c_str());

            // Create the minutes node
            xml_node<>* minutes = doc.allocate_node(node_element, "Minutes");
            player->append_node(minutes);
            minutes->value(to_string(globalScores[numPlayers].minutes).c_str());

            // Create the seconds node
            xml_node<>* seconds = doc.allocate_node(node_element, "Seconds");
            player->append_node(seconds);
            seconds->value(to_string(globalScores[numPlayers].secs).c_str());

            // Create the Hundredths of second node
            xml_node<>* hundredthsOfSecond = doc.allocate_node(node_element, "HundredthsOfSecond");
            player->append_node(hundredthsOfSecond);
            hundredthsOfSecond->value(to_string(globalScores[numPlayers].cents_second).c_str());

            // Increment the number of players processed
            numPlayers++;
        }
        else {
            foundPosition = true;
        }
    }

    // Add the new record
    string idNode = "P" + to_string(numPlayers + 1);

    // The actual player goes first
    xml_node<>* player = doc.allocate_node(node_element, idNode.c_str());
    players->append_node(player);

    // Create the score node
    xml_node<>* score = doc.allocate_node(node_element, "Score");
    player->append_node(score);
    score->value(to_string(newRecord.score).c_str());

    // Create the name node
    xml_node<>* name = doc.allocate_node(node_element, "Name");
    player->append_node(name);
    name->value(newRecord.name.c_str());

    // Create the minutes node
    xml_node<>* minutes = doc.allocate_node(node_element, "Minutes");
    player->append_node(minutes);
    minutes->value(to_string(newRecord.minutes).c_str());

    // Create the seconds node
    xml_node<>* seconds = doc.allocate_node(node_element, "Seconds");
    player->append_node(seconds);
    seconds->value(to_string(newRecord.secs).c_str());

    // Create the Hundredths of second node
    xml_node<>* hundredthsOfSecond = doc.allocate_node(node_element, "HundredthsOfSecond");
    player->append_node(hundredthsOfSecond);
    hundredthsOfSecond->value(to_string(newRecord.cents_second).c_str());

    numPlayers++;

    // While the position has not been found
    for (int j = numPlayers; j < 7; j++){

        // The actual player goes first
        xml_node<>* lastPlayer = doc.allocate_node(node_element, tags[j].c_str());
        players->append_node(lastPlayer);

        // Create the score node
        xml_node<>* lastScore = doc.allocate_node(node_element, "Score");
        lastPlayer->append_node(lastScore);
        lastScore->value(to_string(globalScores[j - 1].score).c_str());

        // Create the name node
        xml_node<>* lastName = doc.allocate_node(node_element, "Name");
        lastPlayer->append_node(lastName);
        lastName->value(globalScores[j - 1].name.c_str());

        // Create the minutes node
        xml_node<>* lastMinutes = doc.allocate_node(node_element, "Minutes");
        lastPlayer->append_node(lastMinutes);
        lastMinutes->value(to_string(globalScores[j - 1].minutes).c_str());

        // Create the seconds node
        xml_node<>* lastSeconds = doc.allocate_node(node_element, "Seconds");
        lastPlayer->append_node(lastSeconds);
        lastSeconds->value(to_string(globalScores[j - 1].secs).c_str());

        // Create the Hundredths of second node
        xml_node<>* lastHundredthsOfSecond = doc.allocate_node(node_element, "HundredthsOfSecond");
        lastPlayer->append_node(lastHundredthsOfSecond);
        lastHundredthsOfSecond->value(to_string(globalScores[j - 1].cents_second).c_str());
    }

    // Store the new xml file configuration
    theFile << doc;
    theFile.close();
    doc.clear();

    return true;
}
