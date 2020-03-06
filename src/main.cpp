
#include <vector>
#include <iostream>
#include "../include/Step.h"
#include "../include/Player.h"
#include "../include/IntervalCurve.h"
#include "../include/LandScape.h"
#include <SFML/Graphics.hpp>


const int NUMBER_FPS = 60;


using namespace std;

void drawQuad(RenderWindow &w, Color c, int x1,int y1,int w1,int x2,int y2,int w2){
    ConvexShape shape(4);
    shape.setFillColor(c);
    shape.setPoint(0, Vector2f(x1-w1,y1));
    shape.setPoint(1, Vector2f(x2-w2,y2));
    shape.setPoint(2, Vector2f(x2+w2,y2));
    shape.setPoint(3, Vector2f(x1+w1,y1));
    w.draw(shape);
}


int main(int argc, char* argv[]){

    string name = "Configuration/Scenes/SherwoodForest.xml";
    char* n = const_cast<char*>(name.c_str());
    LandScape L = LandScape(n);

    // Creation of the screen game
    RenderWindow app(VideoMode(WIDTH, HEIGHT), "Super Hang On!");
    // Control the fotograms per second, 60 FPS more less
    app.setFramerateLimit(NUMBER_FPS);

    string path = "images/player/";
    char* p = const_cast<char*>(path.c_str());
    // Motorbike of the player
    Player h = Player(p);

    h.loadSpritesFromPath();

    // Number of steps done
    int pos = 0, lastPos = 0;
    // Height position unnecessary
    int H = 1500;

    // Possible event detected
    bool eventDetected = false;

    // Colors of the map
    Color grass, rumble, middle, road;

    // Possible event detected
    bool onCurve = false;

    // Velocity
    int speed = INITIAL_SPEED;

    // Variable to control the different possible curves
    IntervalCurve curve;

    // Controlling possible events in the console of the game
    Event ev;

    // While the game console is opened
    while (app.isOpen()){

        // Detect possible actions of the user on the console game
        if (app.pollEvent(ev) && ev.type == Event::Closed){
                app.close();
        }

        // New speed updated
        if (h.getModeCollision() == -1){
            // Check the advance of the motorbike of the player
            h.advancePlayer(eventDetected);

            // Control the possible actions if the user
            h.controlActionPlayer(speed, eventDetected, app);

            // Store my the actual position before the move
            lastPos = pos;

            pos += speed;
        }

        // Get the nearest sprite found to the actual position
        Step nearestStep;

        // Checking of the motorbike is in a curve of the scene
        nearestStep = L.checkingPossibleCollision(pos);

        // Check possible collisions of the motorbike or if there is a collision been processed now
        if (h.controlPossibleCollision(nearestStep, lastPos, pos) || h.getModeCollision() != -1){
            // There is collision
            h.collisionShow();
            speed = INITIAL_SPEED;
        }

        L.lookForCurve(pos, curve, onCurve);

        // Control the inertia force of the motorbike
        h.controlInertiaForce(onCurve, curve, speed);

        // Check the upper bound limit
        while (pos >=  MAX_SPACE_DIMENSION * segL){
            pos -= MAX_SPACE_DIMENSION * segL;
        }

        // Check the lower bound limit
        while (pos < 0){
            pos += MAX_SPACE_DIMENSION * segL;
        }

        // Rendering the landscape of Sherwood forest
        app.clear(Color(105, 205, 4));
        app.draw(L.getBackGround());

        // Preparing to draw the new elements of the map
        int startPos = pos / segL;
        int camH = L.lines[startPos].position_3d_y + H;

        // Check if advance
        if (speed > 0 && h.getModeCollision() == -1){
            // Advance
            // Checking of the motorbike is in a curve of the scene
            Sprite newBack;
            newBack = L.getBackGround();
            newBack.move(-(L.lines[startPos].directionCurve) * 2, 0);
            L.setBackGround(newBack);
        }

        // Variables
        int maxy = HEIGHT;
        float x = 0, dx = 0;

        // Drawing the road
        for(int n = startPos; n < startPos + 300; n++){
            // Create a new line
            Step &l = L.lines[n % MAX_SPACE_DIMENSION];
            // Project the 3d coordinates in 2d coordinates image
            l.project(h.getPlayerX() * WIDTH_ROAD - x, camH, startPos * segL - (n>= MAX_SPACE_DIMENSION ? MAX_SPACE_DIMENSION * segL : 0));
            x += dx;
            dx += l.directionCurve;

            l.clip = maxy;
            if (l.position_2d_y < maxy){
                maxy = l.position_2d_y;

                // Paint the scene
                L.paintScene(n, grass, rumble, middle, road);
                Step p = L.lines[(n - 1)% MAX_SPACE_DIMENSION];

                // Draw the grass and the road
                drawQuad(app, grass, 0, p.position_2d_y, WIDTH, 0, l.position_2d_y, WIDTH);
                drawQuad(app, rumble, p.position_2d_x, p.position_2d_y, p.position_2d_w * 1.2, l.position_2d_x, l.position_2d_y, l.position_2d_w * 1.2);
                drawQuad(app, road,  p.position_2d_x, p.position_2d_y, p.position_2d_w, l.position_2d_x, l.position_2d_y, l.position_2d_w);
                drawQuad(app, middle, p.position_2d_x, p.position_2d_y, p.position_2d_w * 0.05, l.position_2d_x, l.position_2d_y, l.position_2d_w * 0.05);
            }
       }
       // Drawing the objects of the map
       for(int n = startPos + 300; n > startPos; n--){
          // Draw sprite in that position
          L.lines[n % MAX_SPACE_DIMENSION].drawSprite(app);
       }

       //Show all the elements in the console game
       h.drawPlayer(app);
       app.display();

       // Sleep loop
       if (h.getModeCollision() == -1){
            sleep(milliseconds(70));
       }
       else {
            sleep(milliseconds(100));
       }
    }
    return 0;
}
