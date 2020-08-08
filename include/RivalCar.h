
#ifndef RIVAL_CAR_H
#define RIVAL_CAR_H

#include "Step.h"
#include "Vehicle.h"
#include "Randomizer.h"
#include <cmath>


using namespace std;
using namespace sf;

namespace Vehicle_RivalCar {
    const int MAX_DIRECTION = 1000;
}


class RivalCar : public Vehicle {
    float oriX;

    float lastSpeed, angleTurning;

    Direction currentDirection, calculatedPath;
    int current_direction_counter, max_direction_counter;

    bool firstTurnLeft, firstTurnRight, newPath, crashing,
         onStraight, shoutDone, smoking, firing, fireSmoking;;

    int vehicleType;

    // Number of textures of textures of the vehicle
    int numTextures, mode;

    // Texture thresholds to control the movements of the vehicle
    int minTextureRight, maxTextureRight,
        minTextureRightBrake, maxTextureRightBrake;

    int minTextureTurnLeft, maxTextureTurnLeft,
        minTextureTurnLeftBrake, maxTextureTurnLeftBrake;

    int minTextureTurnRight, maxTextureTurnRight,
        minTextureTurnRightBrake, maxTextureTurnRightBrake;

    int minTextureUp, maxTextureUp,
        minTextureUpBrake, maxTextureUpBrake;

    int minTextureTurnLeftUp, maxTextureTurnLeftUp,
        minTextureTurnLeftBrakeUp, maxTextureTurnLeftBrakeUp;

    int minTextureTurnRightUp, maxTextureTurnRightUp,
        minTextureTurnRightBrakeUp, maxTextureTurnRightBrakeUp;

    int medTurnLeft, medTurnRight, medTurnLeftUp, medTurnRightUp,
        medTurnLeftBrake, medTurnRightBrake, medTurnLeftBrakeUp,
        medTurnRightBrakeUp;

    float probAI, scalingFactor, speedCollision, xDest, speedFactor;

    /**
     * Tipos de IA:
     *      OBSTACLE: Intenta chocar con el jugador poniéndose en su trayectoria e intentando alcanzarlo.
     *      EVASIVE: Huye al carril más alejado del jugador para intentar evitarlo.
     *      INCONSTANT: Cambia de carriles muy a menudo sin tener en cuenta la posición del jugador.
     */
    enum TypeAI {
        OBSTACLE,
        EVASIVE,
        INCONSTANT,
        MANIAC
    };

    TypeAI typeAI;

public:


    RivalCar();


    /**
     * Inicializa el vehículo rival.
     * @param maxSpeed
     * @param speedMul multiplicador de la velocidad que multiplicado por speed obtiene la velocidad real
     * @param scale escalado del sprite del vehículo
     * @param maxCounterToChange cuando counter_code_image llega a maxCounterToChange se actualiza el sprite
     * @param vehicle nombre del vehículo
     * @param pY
     */
    RivalCar(int typeOfVehicle, float maxSpeed, float speedMul, float scale, int maxCounterToChange, const string &vehicle, float pX, float pY,
             int totalTextures, int lowTextureRight, int highTextureRight, int lowTextureRightBrake, int highTextureRightBrake,
             int lowTextureTurnleft, int highTextureTurnLeft, int lowTextureTurnLeftBrake, int highTextureTurnLeftBrake,
             int lowTextureTurnRight, int highTextureTurnRight, int lowTextureTurnRightBrake, int highTextureTurnRightBrake,
             int lowTextureUp, int highTextureUp, int lowTextureUpBrake, int highTextureUpBrake, int lowTextureTurnleftUp,
             int highTextureTurnLeftUp, int lowTextureTurnLeftBrakeUp, int highTextureTurnLeftBrakeUp,  int lowTextureTurnRightUp,
             int highTextureTurnRightUp, int lowTextureTurnRightBrakeUp, int highTextureTurnRightBrakeUp, int mediumTurnLeft,
             int mediumTurnRight, int mediumTurnLeftUp, int mediumTurnRightUp, int mediumTurnLeftBrake, int mediumTurnRightBrake,
             int mediumTurnLeftBrakeUp, int mediumTurnRightBrakeUp, float scaling);

    float getRealSpeed() const;


    void setSmoking();


    float getSmoking() const;


    void hitControl(const bool vehicleCrash, SoundPlayer& r);


    bool isCrashing() const;

    /**
     * Inicializa el estado del vehículo. Actualiza la agresividad de la IA del vehículo con un valor aleatorio entre 0
     * y maxAggressiveness.
     * @param iniPos
     * @param endPos
     * @param maxAggressiveness, 0 <= maxAggressiveness <= 1
     */
    void update(Configuration& c, float iniPos, float endPos, float maxAggressiveness, Action& a, float directionCurve,
                const Difficult& difficulty, const float playerPosX, const float playerPosY, const float playerSpeed);

    /**
     * Actualiza la agresividad de la IA del vehículo con un valor aleatorio entre 0 y maxAggressiveness.
     * @param maxAggressiveness, 0 <= maxAggressiveness <= 1
     */
    void setAI(float maxAggressiveness, const Difficult& difficulty, const int typeOfGame);

    /**
     * Actualiza el sprite del vehículo enemigo.
     * @param e
     * @param camX actual de la cámara
     */
    void draw(const Action &a, const Elevation &e);

    /**
     * Establece la coordenada X mínima que ocupa el vehículo.
     * @param screenX
     */
    void setMinScreenX(float screenX);

    /**
     * Establece la coordenada X máxima que ocupa el vehículo.
     * @param screenX
     */
    void setMaxScreenX(float screenX);

    /**
     * Devuelve la textura actual del vehículo.
     * @return
     */
    const sf::Texture *getCurrentTexture() const;

    /**
     * Devuelve la escala actual del vehículo.
     * @return
     */
    float getScale() const;



    float getPreviousY() const;


    /**
     * Devuelve la escala actual del vehículo.
     * @return
     */
    float getScalingFactor() const;


    /**
     * Devuelve true si pos corresponde al vehículo actual. En caso de que sea true, también devuelve la posición Y
     * donde han colisionado.
     * @param currentY
     * @param prevY
     * @param minX
     * @param maxX
     * @param crashPos
     * @return
     */
    bool hasCrashed(float prevY, float currentY, float minX, float maxX, float &crashPos) const;

    /**
     * Devuelve true si el coche se muestra en pantalla y la distancia al jugador, sino devuelve false.
     * @param c
     * @param minY
     * @param playerX
     * @param playerY
     * @param distanceX
     * @param distanceY
     * @return
     */
    bool isVisible(const Configuration &c, float minY, float playerX, float playerY, float &distanceX, float &distanceY) const;



    void setOnStraight();


    void drawSmokingPlayer(Configuration& c, const float destW, const float destH, const float widthOri,
                           const float heightOri, const float maxY);


    int getVehicleType();


    void setFiring(const bool fire);


    bool getFiring();


    void setFiringSmoke(const bool fireSmoke);


    void drawFirePlayer(Configuration& c, const float destW, const float destH, const float widthOri,
                        const float heightOri, const float maxY);


    void drawSmokingFirePlayer(Configuration& c, const float destW, const float destH, const float widthOri,
                               const float heightOri, const float maxY);


    bool getFiringSmoke();

};


#endif // RIVAL_CAR_H
