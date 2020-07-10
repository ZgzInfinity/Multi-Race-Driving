
#ifndef PLAYER_H
#define PLAYER_H

#include "Vehicle.h"
#include "../include/Randomizer.h"
#include <cmath>

using namespace std;
using namespace sf;

namespace Motorbike_vehicle {
    const int FORCE_INERTIA = 8;
    const int PLAYER_TEXTURES = 67;
}


class Motorbike : public Vehicle {
    float speedMul, maxAcc, accInc, scaleY;
    float acceleration, minCrashAcc, xDest;
    int inertia;

    sf::Sprite sprite;
    bool crashing;      // True if crashing state is on
    bool smoking;       // True if player generates smoke
    bool skidding;      // True if player is skidding
    bool crashNow;      // True if a crash has happened

    string brand;           // Name of the vehicle
    string motor;           // Brand of the motor's vehicle
    float angleTurning;     // Turning angle of the vehicle
    float topSpeed;         // Top speed of the vehicle
    bool outSideRoad;       // Control if the motorbike is outside the road
    float speedCollision;   // Initial speed when starts the collision


    bool firstCrash, firstTurnLeft, firstTurnRight;

public:


    Motorbike();

    /**
     * Inicializa el vehículo del jugador.
     * @param maxSpeed
     * @param speedMul multiplicador de la velocidad que multiplicado por speed obtiene la velocidad real
     * @param accInc incremento de la aceleración
     * @param scaleX escalado del sprite del vehículo
     * @param scaleY escalado del sprite del vehículo
     * @param maxCounterToChange cuando counter_code_image llega a maxCounterToChange se actualiza el sprite
     * @param vehicle nombre del vehículo
     * @param pX
     * @param pY
     */
    Motorbike(float maxSpeed, float speedMul, float accInc, float scaleX, float scaleY, int maxCounterToChange,
           const std::string &vehicle, float pX, float pY, const string brandName, const float angle,
           const string motorName);

    /**
     * Devuelve la posición previa Y.
     * @return
     */
    float getPreviousY() const;

    /**
     * Actualiza la lógica del choque y restablece la velocidad y aceleración.
     * @param vehicleCrash true si es un choque entre vehículos
     */
    void hitControl(bool vehicleCrash);

    /**
     * Devuelve true si la lógica de choque está en ejecución.
     * @return
     */
    bool isCrashing() const;

    /**
     * Devuelve la velocidad real del vehículo.
     * @return
     */
    float getRealSpeed() const;

    /**
     * Actualiza la lógica de la aceleración y frenado del vehículo.
     * @param c
     * @param hasGotOut indica si se ha salido del camino
     * @return
     */
    Action accelerationControl(Configuration &c, bool hasGotOut);

    /**
     * Actualiza la lógica de giro del vehículo.
     * @param c
     * @param curveCoefficient pertenece [-0.9, 0.9]
     * @return
     */
    Direction rotationControl(Configuration &c, float curveCoefficient, const bool& isFinalMap, const int& limitMap);

    /**
     * Actualiza el sprite del vehículo jugador y lo dibuja en la pantalla.
     * @param c
     * @param a
     * @param d
     * @param e
     * @param enableSound
     */
    void draw(Configuration &c, SoundPlayer &r, const Action &a, const Direction &d, const Elevation &e, int terrain, bool enableSound = true);

    /**
     * Dibuja la animación inicial en la pantalla y devuelve si ha acabado.
     * @param c
     * @param x
     * @param end
     */
    void drawInitialAnimation(Configuration &c, float x, bool &end);

    /**
     * Dibuja la animación final en la pantalla y devuelve si ha acabado.
     * @param c
     * @param step
     * @param end
     * @param smoke
     */
    void drawGoalAnimation(Configuration &c, int &step, bool &end, bool smoke = true);

    /**
     * Fuerza a que el coche esté echando humo o no.
     * @param smoke
     */
    void setSmoking(bool smoke);


    void setVehicle();


    float getHalfMaxSpeed();


    string getBrandName();


    float getAngle();


    string getMotorName();


    float getTopSpeed();
};


#endif // PLAYER_H
