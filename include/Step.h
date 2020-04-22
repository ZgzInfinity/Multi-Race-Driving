
#ifndef STEP_H
#define STEP_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// Dimension of the road lines black or white
const int segL = 200;
const float camD = 0.84;

// Dimensions of the screen of the game
const int WIDTH = 1024;
const int HEIGHT = 768;
const int WIDTH_ROAD = 2000;

// Number of steps to complete the map and repeat
const int MAX_SPACE_DIMENSION = 12000;
const int NORMAL_HEIGHT = 1500;


// Current elevation type of the Step
enum Elevation {
    UP,
    FLAT,
    DOWN
};


/*
 * Step data type
 */
struct Step{

    /**
     * Información de un objeto correspondiente a objects[spriteNum] si spriteNum != -1, con un offset en x.
     * Si repetitive es true el objeto se repetirá hasta el borde de la pantalla.
     */
    struct SpriteInfo {
        int intervalShow;
        int spriteNum;
        string path;
        float offset, spriteMinX, spriteMaxX;
        bool repetitive;

        /**
         * Inicializa el sprite.
         */
        SpriteInfo();
    };

    // Attributes of the type of data
    // 3d coordinates of the line in three axis X, Y and Z
    float position_3d_x, position_3d_y, position_3d_z;
    // Coordinates of the screen in two dimensions X and Y point and W offset
    float position_2d_x, position_2d_y, position_2d_w;
    // Control if there curve to right or to left
    float directionCurve;
    // Control the position of the possible sprite in the axis X
    float spriteX;
    // Control the position of the possible sprite in the axis Y
    int spriteY;
    // Unknown
    float clip;
    // Scale to transform 3d coordinates to 2d coordinates
    float scalingValue;
    // Offset to control the possible collisions
    float offset;
    // Possible sprites to draw
    SpriteInfo spriteNearLeft, spriteNearRight, spriteFarLeft, spriteFarRight;

    bool mainColor;

    /**
     * Constructor of the data type Step
     * @return an instance of the data type Step
     */
    Step();



    /**
     * Projects a point in 3d in the equivalent 2d plane
     * @param camX is the coordinate in the axis X
     * @param camY is the coordinate in the axis Y
     * @param camZ is the coordinate in the axis Z
     */
    void project(int camX,int camY,int camZ);



    /**
     * Draw a sprite in the console game
     * @param app is the console game where the user is playing
     */
    void drawSprite(RenderWindow* app);



    /**
     * Compares to sprites to determine which is first in the order
     * @param line is the other step to be compared
     * @return true is the instance caller to the method is lower than <<line>>.
     *         Otherwise returns false
     */
     bool operator < (Step& line_2);


     /**
         * Establece las coordenadas en la pantalla que corresponen al rectángulo y su escala. Esta función debe ser
         * llamada para actualizar el rectángulo si se ha variado la posición del mapa y.
         * @param camX
         * @param camY
         * @param camZ
         * @param camD
         * @param width
         * @param height
         * @param rW
         * @param zOffset
         */
        void project(float camX, float camY, float camZ, float camD, float width, float height, float rW, float zOffset);


        /**
         * Dibuja el objeto en la pantalla. Esta función debe ser llamada después de project().
         * @param w
         * @param objs
         * @param coeff
         * @param object
         * @param left indica si el objeto está a la izquierda de la pantalla
         */
        void drawSprite(sf::RenderWindow* w, const std::vector<sf::Texture> &objs, const std::vector<float> &coeff,
                Step::SpriteInfo &object, bool left);

};



#endif // STEP_H

