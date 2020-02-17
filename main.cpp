#include "Step.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "SherwoodForest.h"

const int NUMBER_FPS = 60;
const int MAX_ELEMENTS = 20;

using namespace std;

void drawQuad(RenderWindow &w, Color c, int x1,int y1,int w1,int x2,int y2,int w2)
{
    ConvexShape shape(4);
    shape.setFillColor(c);
    shape.setPoint(0, Vector2f(x1-w1,y1));
    shape.setPoint(1, Vector2f(x2-w2,y2));
    shape.setPoint(2, Vector2f(x2+w2,y2));
    shape.setPoint(3, Vector2f(x1+w1,y1));
    w.draw(shape);
}




int main(){

    // Creation of the screen game
    RenderWindow app(VideoMode(WIDTH, HEIGHT), "Outrun Racing!");
    // Control the fotograms per second, 60 FPS more less
    app.setFramerateLimit(NUMBER_FPS);

    // Texture and sprite vectors
    Texture t[MAX_ELEMENTS];
    Sprite object[MAX_ELEMENTS];

    // Sherwood Forest scene instance
    SherwoodForest s;

    // Load all the elements of the scene
    s.loadSprites(t, object);

    // Loading backbground texture
    Texture bg;
    bg.loadFromFile("images/bg.png");
    // Set repetition of texture active and assignation
    bg.setRepeated(true);
    Sprite sBackground(bg);
    // Fix the dimensions of the rectangle which contains the texture
    sBackground.setTextureRect(IntRect(-3000, 0, 5000, 411));
    // Assign the position of the texture
    sBackground.setPosition(-2000,0);

    // Vector of steps to do
    vector<Step> lines;

    // For each tep walked
    for(int i = 0; i <= MAX_SPACE_DIMENSION - 1; i++){
       // Creation of the line and justify its depth in the 3d dimension
       Step line;
       line.position_3d_z = i * segL;

       // Drawing the curves of the game scene
       s.printCurves(line, i);

       // Drawing the possible mountain in the step i of the scene
       s.printMountains(line, i);

       // Draw the possible sprites in the step i of the scene
       s.printSpritesInScene(line, object, i);

       // Added vector
       lines.push_back(line);
    }

   // Initial position of the main character
   float playerX = 0;
   // Number of steps done
   int pos = 0;
   // Height position unnecessary
   int H = 1500;

   // Colors to represent the landscape
   Color grass, rumble, road, middle;

    // While the game console is opened
    while (app.isOpen())
    {
        // Register a new event and detecting it
        Event e;
        while (app.pollEvent(e)){
            // Check if the evnt is close the window
            if (e.type == Event::Closed){
                app.close();
            }

            // Velocity
            int speed = 400;

            // Control the keys pressed
            if (Keyboard::isKeyPressed(Keyboard::Right)) playerX+=0.1;
            if (Keyboard::isKeyPressed(Keyboard::Left)) playerX-=0.1;
            if (Keyboard::isKeyPressed(Keyboard::Up)) speed=400;
            if (Keyboard::isKeyPressed(Keyboard::Tab)) speed*=3;

            // Increment of the position
            pos += speed;

            // Check the upper bound limit
            while (pos >=  MAX_SPACE_DIMENSION * segL){
                    pos -= MAX_SPACE_DIMENSION * segL;
            }
            // Check the lower bound limit
            while (pos < 0){
                pos += MAX_SPACE_DIMENSION * segL;
            }

            app.clear(Color(105,205,4));
            app.draw(sBackground);
            int startPos = pos / segL;
            int camH = lines[startPos].position_3d_y + H;

            // Check if advance or return
            if (speed > 0){
                // Advance
                sBackground.move(-lines[startPos].directionCurve * 2,0);
            }
            if (speed < 0){
                // Return
                sBackground.move( lines[startPos].directionCurve * 2,0);
            }

            // Variables
            int maxy = HEIGHT;
            float x = 0, dx = 0;

            // Drawing the road
            for(int n = startPos; n < startPos+300; n++){
                // Create a new line
                Step &l = lines[n % MAX_SPACE_DIMENSION];
                // Project the 3d coordinates in 2d coordinates image
                l.project(playerX * WIDTH_ROAD - x, camH, startPos * segL - (n>= MAX_SPACE_DIMENSION ? MAX_SPACE_DIMENSION * segL : 0));
                x += dx;
                dx += l.directionCurve;

                l.clip = maxy;
                if (l.position_2d_y < maxy){
                    maxy = l.position_2d_y;

                    // Determinacion of the color to paint in the screen
                    if ((n / 3) % 2){
                        grass = Color(16, 200, 16);
                        rumble = Color(255, 255, 255);
                        road = Color(128, 128, 128);
                        middle = Color(255, 255, 255);
                    }
                    else {
                        grass = Color(0, 154, 0);
                        rumble = Color(255, 0, 0);
                        road = Color(77, 77, 77);
                        middle = Color(77, 77, 77);
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
            app.display();
        }
    }

    return 0;
}
