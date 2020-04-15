/******************************************************************************
 * @file    Map.cpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Rubén Rodríguez Esteban, 737215
 * @date    Marzo 2020
 * @coms    Videojuegos - OutRun
 ******************************************************************************/

#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <random>
#include <fstream>
#include "../include/Map.h"

using namespace std;
using namespace sf;

#define BGS 0.525F // Background size
#define ROADW 2000 // Road Width
#define RUMBLECOEFF 0.1f // Ruble size = Road size * Rumble coeff


void Map::addLine(float x, float y, float &z, float prevY, float curve, bool mainColor,
        const Step::SpriteInfo &spriteLeft, const Step::SpriteInfo &spriteRight) {
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
    lines.push_back(lineAux);

    lineAux.position_3d_z = z;
    z += segL - 50;
    lineAux.position_3d_y += yInc;
    lines.push_back(lineAux);

    line.position_3d_z = z;
    z += segL - 50;
    lineAux.position_3d_y += yInc;
    line.position_3d_y = lineAux.position_3d_y;
    lines.push_back(line);

    lineAux.position_3d_z = z;
    z += segL - 50;
    lineAux.position_3d_y += yInc;
    lines.push_back(lineAux);

    lineAux.position_3d_z = z;
    z += segL - 50;
    lineAux.position_3d_y += yInc;
    lines.push_back(lineAux);
}


float Map::getPosX(){
    return posX;
}



float Map::getPosY(){
    return posY;
}


Step *Map::getLine(const int n) {
    if (n < lines.size() || next == nullptr)
        return &lines[n % lines.size()];
    else
        return &next->lines[(n - lines.size()) % next->lines.size()];
}

Step Map::getLine(const int n) const{
    if (n < lines.size() || next == nullptr)
        return lines[n % lines.size()];
    else
        return next->lines[(n - lines.size()) % next->lines.size()];
}

Step *Map::getPreviousLine(const int n) {
    if ((n > 0 && n - 1 < lines.size()) || next == nullptr)
        return &lines[(n - 1) % lines.size()];
    else
        return &next->lines[(n - 1 - lines.size()) % next->lines.size()];
}

Step Map::getPreviousLine(const int n) const {
    if ((n > 0 && n - 1 < lines.size()) || next == nullptr)
        return lines[(n - 1) % lines.size()];
    else
        return next->lines[(n - 1 - lines.size()) % next->lines.size()];
}

void fileError(const string &error="") {
    cerr << "Error: Formato de fichero incorrecto." << endl;
    if (!error.empty())
        cerr << "\t" + error << endl;
    exit(1);
}

vector<vector<string>> randomMap(const int numLines, const vector<int> &objectIndexes) {
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

vector<vector<string>> readMapFile(const std::string &file) {
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

void Map::addLines(float x, float y, float &z, const vector<vector<string>> &instructions) {
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
            if (!lines.empty() && elevationIndex == elevationLines) {
                y = lines[lines.size() - 1].position_3d_y;
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

            addLine(x, yAux, z, lines.empty() ? y : lines[lines.size() - 1].position_3d_y, curveCoeff, mainColor,
                    spriteLeft, spriteRight);
            mainColor = !mainColor;
        }
    }
}

Map::Map(const std::string &path, const std::string &bgName,
        const std::vector<std::string> &objectNames, bool random) : posX(0), posY(0), next(nullptr) {
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

    if (lines.empty())
        fileError();
}


void Map::addNextMap(Map *map) {
    this->next = map;
    float yOffset = 0.0f;
    if (!lines.empty())
        yOffset = lines[lines.size() - 1].position_3d_y;
    this->next->setOffset(yOffset);
}


void Map::setOffset(float yOffset) {
    for (Step &l : lines) {
        l.position_3d_y += yOffset;
    }
}


void Map::updateView(pair<float, float> pos) {
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


void Map::draw(RenderWindow* app, Configuration* c) {
    Step *l = getLine(int(posY)), *p;
    int N = lines.size();

    // Background
    drawQuad(app, grassColor[0], 0, 0, app->getSize().x, 0, app->getSize().y, app->getSize().x);
    Sprite sbg;
    sbg.setTexture(bg);
    sbg.setScale(Vector2f(2.0f * (float)app->getSize().x / bg.getSize().x, (float)app->getSize().y * BGS / bg.getSize().y));
    sbg.setPosition(0, 0);
    sbg.move(-sbg.getGlobalBounds().width / 3.0f - posX, 0);
    if (l->directionCurve > 0.0f)
        sbg.move(XINC / 2.0f, 0);
    else if (l->directionCurve < 0.0f)
        sbg.move(-XINC / 2.0f, 0);
    app->draw(sbg);

    int startPos = int(posY) % N;
    float camH = l->position_3d_y + 1500.0f;

    float maxy = app->getSize().y;
    float x = 0, dx = 0;

    ///////draw road////////
    for (int n = startPos; n < startPos + 300; n++) {
        l = getLine(n);

        l->project(posX * ROADW - x, camH, float(startPos * (segL - 50)), 0.84,
                  app->getSize().x, app->getSize().y, ROADW, n < N ? 0.0f : lines[lines.size() - 1].position_3d_z);
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


bool Map::hasGotOut(float currentX) const {
    return abs(currentX) > 1.0f;
}

float Map::getCurveCoefficient(float currentY) const {
    return getLine(int(currentY)).directionCurve;
}

Elevation Map::getElevation(float currentY) const {
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

bool Map::isOver() const {
    return posY >= lines.size();
}
