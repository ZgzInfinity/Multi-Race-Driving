

#ifndef VEHICLE_H
#define VEHICLE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Menu.h"

using namespace std;
using namespace sf;

const int COUNTER = 2;

const float INCREMENT_X = 0.033f; // x increment
const float ACCELERATION_INCREMENT = 0.01f;
const float TIME_HALF_SPEED = 16.322f;
const float MAX_SPEED = 300.0f;

/**
 * La información del vehículo está compuesta por su velocidad, aceleración, posición x, conjunto de texturas del
 * vehículo, sprite actual y acción actual y dirección actual.
 */
class Vehicle {
public:
    enum Elevation {
        UP,
        FLAT,
        DOWN
    };
    enum Action {
        NONE,
        BRAKE,
        ACCELERATE,
        CRASH,
        BOOT
    };
    enum Direction {
        RIGHT,
        TURNLEFT,
        TURNRIGHT
    };

protected:
    float maxSpeed, halfMaxSpeed, scale;
    int maxCounterToChange;

    float speed;
    float posX, posY, previousY, minScreenX, maxScreenX;

    vector<sf::Texture> textures;
    int current_code_image;
    int counter_code_image; // Counter to change actual_code_image

public:

     Vehicle();


    /**
     * Inicializa el vehículo.
     * @param maxSpeed
     * @param scale
     * @param maxCounterToChange
     * @param speed
     * @param posX
     * @param posY
     * @param previousY
     * @param minScreenX
     * @param maxScreenX
     * @param vehicle
     * @param numTextures
     * @param currentCodeImage
     * @param counterCodeImage
     */
    Vehicle(float maxSpeed, float scale, int maxCounterToChange, float speed, float posX, float posY, float previousY,
            float minScreenX, float maxScreenX, const std::string &vehicle, int numTextures, int currentCodeImage,
            int counterCodeImage);

    /**
     * Establece la posición actual del vehículo.
     * @param pX
     * @param pY
     */
    void setPosition(float pX, float pY);


    void setVehicle();


    /**
     * Devuelve la posición actual X.
     * @return
     */
    float getPosX() const;

    /**
     * Devuelve la posición actual Y.
     * @return
     */
    float getPosY() const;

    /**
     * Devuelve la coordenada mínima de pantalla en X que ocupa el vehículo.
     * @return
     */
    float getMinScreenX() const;

    /**
     * Devuelve la coordenada máxima de pantalla en X que ocupa el vehículo.
     * @return
     */
    float getMaxScreenX() const;

    /**
     * Devuelve la aceleración del vehículo.
     * @return
     */
    float getAcceleration() const;
};


#endif // VEHICLE_H
