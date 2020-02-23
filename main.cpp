
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SherwoodForest.h"
#include "Egypt.h"
#include "Step.h"
#include "Player.h"
#include "IntervalCurve.h"

const int NUMBER_FPS = 60;
const int MAX_ELEMENTS = 20;


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

    // Creation of the screen game
    RenderWindow app(VideoMode(WIDTH, HEIGHT), "Super Hang on!");
    // Control the fotograms per second, 60 FPS more less
    app.setFramerateLimit(NUMBER_FPS);

    // Texture and sprite vectors
    Texture t[MAX_ELEMENTS];
    Sprite object[MAX_ELEMENTS];

    // Processing the index of the scene
    int indexScene = atoi(argv[1]);

    // Sherwood Forest scene instance
    SherwoodForest s;

    // Egypt scene instance
    Egypt e;

    // Paint the background of the scene

    switch(indexScene){
    case 1:
        // Load background of Sherwood forest
        s.loadBackground();
        // Load all the elements of Sherwood forest
        s.loadSprites(t, object);
        break;
    case 2:
        // Load background of Egypt
        e.loadBackground();
        // Load all the elements of Egypt
        e.loadSprites(t, object);
        break;
    }

    // Vector of steps to do
    vector<Step> lines;

    // Motorbike of the player
    Player h = Player();

    switch(indexScene){
    case 1:
        // Rendering the landscape of Sherwood forest
        s.renderLandScape(lines, object);

        // Order the sprites of Sherwood forest
        s.orderSpritesInLandScape();
        break;
    case 2:
        // Rendering the landscape of Egypt
        e.renderLandScape(lines, object);

        // Order the sprites of Egypt
        e.orderSpritesInLandScape();
        break;
    }

    // Number of steps done
    int pos = 0, lastPos = 0;
    // Height position unnecessary
    int H = 1500;

    // Colors to represent the landscape
    Color grass, rumble, road, middle;

    // Possible event detected
    bool eventDetected = false;

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

        // Check the advance of the motorbike of the player
        h.advancePlayer(eventDetected);

        // Control the possible actions if the user
        h.controlActionPlayer(speed, eventDetected);

        // Store my the actual position before the move
        lastPos = pos;

        // New speed updated
        pos += speed;

        // Get the nearest sprite found to the actual position
        Step nearestStep;

        switch(indexScene){
            case 1:
                // Checking of the motorbike is in a curve of the scene
                nearestStep = s.checkingPossibleCollision(pos);
                break;
            case 2:
                // Rendering the landscape of Egypt
                nearestStep = e.checkingPossibleCollision(pos);
                break;
        }

        // Check possible collisions of the motorbike
        if (h.controlPossibleCollision(nearestStep, lastPos, pos)){
            // There is collision
            app.close();
        }

        switch(indexScene){
            case 1:
                // Checking of the motorbike is in a curve of the scene
                s.lookForCurve(pos, curve, onCurve);
                break;
            case 2:
                // Rendering the landscape of Egypt
                e.lookForCurve(pos, curve, onCurve);
                break;
        }

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

        // Draw the background in the consoles
        app.clear(Color(105, 205, 4));

        switch(indexScene){
            case 1:
                // Rendering the landscape of Sherwood forest
                app.draw(s.getBackGround());
                break;
            case 2:
                // Rendering the landscape of Egypt
                app.draw(e.getBackGround());
                break;
        }

        // Preparing to draw the new elements of the map
        int startPos = pos / segL;
        int camH = lines[startPos].position_3d_y + H;

        // Check if advance
        if (speed > 0){
            // Advance

            switch(indexScene){
            case 1:
                // Checking of the motorbike is in a curve of the scene
                s.getBackGround().move(-lines[startPos].directionCurve * 2,0);
                break;
            case 2:
                // Rendering the landscape of Egypt
                e.getBackGround().move(-lines[startPos].directionCurve * 2,0);
                break;
            }
        }

        // Variables
        int maxy = HEIGHT;
        float x = 0, dx = 0;

        // Drawing the road
        for(int n = startPos; n < startPos+300; n++){
            // Create a new line
            Step &l = lines[n % MAX_SPACE_DIMENSION];
            // Project the 3d coordinates in 2d coordinates image
            l.project(h.getPlayerX() * WIDTH_ROAD - x, camH, startPos * segL - (n>= MAX_SPACE_DIMENSION ? MAX_SPACE_DIMENSION * segL : 0));
            x += dx;
            dx += l.directionCurve;

            l.clip = maxy;
            if (l.position_2d_y < maxy){
                maxy = l.position_2d_y;

                // Paint the scene

                switch(indexScene){
                case 1:
                    // Rendering the landscape of Sherwood forest
                    s.paintScene(n, grass, rumble, middle, road);
                    break;
                case 2:
                    // Rendering the landscape of Egypt
                    e.paintScene(n, grass, rumble, middle, road);
                    break;
                }

                Step p = lines[(n - 1)% MAX_SPACE_DIMENSION]; //previous line

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
          lines[n % MAX_SPACE_DIMENSION].drawSprite(app);
       }

       //Show all the elements in the console game
       h.drawPlayer(app);
       app.display();

       // Sleep loop
       sleep(milliseconds(70));
    }

    return 0;
}
