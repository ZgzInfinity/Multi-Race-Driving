
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

    float lastSpeed;

    Direction currentDirection, calculatedPath;
    int current_direction_counter, max_direction_counter;

    bool firstTurnLeft, firstTurnRight;

    // Number of textures of textures of the vehicle
    int numTextures;

    // Texture thresholds to control the movements of the vehicle
    int minTextureRight, maxTextureRight,
        minTextureRightBrake, maxTextureRightBrake;

    int minTextureTurnleft, maxTextureTurnLeft,
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

    float probAI, scalingFactor;

    /**
     * Tipos de IA:
     *      OBSTACLE: Intenta chocar con el jugador poni�ndose en su trayectoria e intentando alcanzarlo.
     *      EVASIVE: Huye al carril m�s alejado del jugador para intentar evitarlo.
     *      INCONSTANT: Cambia de carriles muy a menudo sin tener en cuenta la posici�n del jugador.
     */
    enum TypeAI {
        OBSTACLE,
        EVASIVE,
        INCONSTANT
    };

    TypeAI typeAI;

public:


    RivalCar();


    /**
     * Inicializa el veh�culo rival.
     * @param maxSpeed
     * @param speedMul multiplicador de la velocidad que multiplicado por speed obtiene la velocidad real
     * @param scale escalado del sprite del veh�culo
     * @param maxCounterToChange cuando counter_code_image llega a maxCounterToChange se actualiza el sprite
     * @param vehicle nombre del veh�culo
     * @param pY
     */
    RivalCar(float maxSpeed, float speedMul, float scale, int maxCounterToChange, const string &vehicle, float pX, float pY,
             int totalTextures, int lowTextureRight, int highTextureRight, int lowTextureRightBrake, int highTextureRightBrake,
             int lowTextureTurnleft, int highTextureTurnLeft, int lowTextureTurnLeftBrake, int highTextureTurnLeftBrake,
             int lowTextureTurnRight, int highTextureTurnRight, int lowTextureTurnRightBrake, int highTextureTurnRightBrake,
             int lowTextureUp, int highTextureUp, int lowTextureUpBrake, int highTextureUpBrake, int lowTextureTurnleftUp,
             int highTextureTurnLeftUp, int lowTextureTurnLeftBrakeUp, int highTextureTurnLeftBrakeUp,  int lowTextureTurnRightUp,
             int highTextureTurnRightUp, int lowTextureTurnRightBrakeUp, int highTextureTurnRightBrakeUp, int mediumTurnLeft,
             int mediumTurnRight, int mediumTurnLeftUp, int mediumTurnRightUp, int mediumTurnLeftBrake, int mediumTurnRightBrake,
             int mediumTurnLeftBrakeUp, int mediumTurnRightBrakeUp, float scaling);



    /**
     * Actualiza la l�gica del veh�culo de manera autom�tica para el movimiento actual.
     *
     * La IA s�lo se activar� si la distancia entre el veh�culo y el jugador es menor o igual a la distancia
     * de render (rect�ngulos que ve el jugador).
     *
     * La agresividad de la IA est� dentro de la clase (probAI). Es un valor entre 0 y 1 que indica la probabilidad de
     * que la IA act�e en este movimiento.
     *
     *      Si la agresividad de la IA es 0, el movimiento ser� como en el juego original, es decir, el coche seguir�
     *      a velocidad constante sin salirse de la carretera y siguiendo una trayectoria recta o con giro (elegida
     *      de manera aleatoria) y sin ser influenciado por el jugador.
     *
     *      Si la agresividad de la IA es 1, el movimiento ser� controlado por la IA y su movimiento depender� del tipo
     *      de IA:
     *          OBSTACLE: Intenta chocar con el jugador poni�ndose en su trayectoria e intentando alcanzarlo.
     *          EVASIVE: Huye al carril m�s alejado del jugador para intentar evitarlo.
     *          INCONSTANT: Cambia de carriles muy a menudo sin tener en cuenta la posici�n del jugador.
     *
     *      Si la agresividad de la IA se encuentra entre 0 y 1, realiza una de las dos acciones descritas (original
     *      o IA) con probabilidad p de que act�e la IA y p' = (1 - p) de que sea como en el original.
     *
     * @param c
     * @param playerPosX
     * @param playerPosY
     */
    void autoControl(const Configuration &c, float playerPosX, float playerPosY);

    /**
     * Inicializa el estado del veh�culo. Actualiza la agresividad de la IA del veh�culo con un valor aleatorio entre 0
     * y maxAggressiveness.
     * @param iniPos
     * @param endPos
     * @param maxAggressiveness, 0 <= maxAggressiveness <= 1
     */
    void update(Configuration& c, float iniPos, float endPos, float maxAggressiveness, Action& a, Direction& d, float directionCurve,
                const Difficult& difficulty, const float playerPosX, const float playerPosY);

    /**
     * Actualiza la agresividad de la IA del veh�culo con un valor aleatorio entre 0 y maxAggressiveness.
     * @param maxAggressiveness, 0 <= maxAggressiveness <= 1
     */
    void setAI(float maxAggressiveness, const Difficult& difficulty);

    /**
     * Actualiza el sprite del veh�culo enemigo.
     * @param e
     * @param camX actual de la c�mara
     */
    void draw(const Action &a, const Direction &d, const Elevation &e);

    /**
     * Establece la coordenada X m�nima que ocupa el veh�culo.
     * @param screenX
     */
    void setMinScreenX(float screenX);

    /**
     * Establece la coordenada X m�xima que ocupa el veh�culo.
     * @param screenX
     */
    void setMaxScreenX(float screenX);

    /**
     * Devuelve la textura actual del veh�culo.
     * @return
     */
    const sf::Texture *getCurrentTexture() const;

    /**
     * Devuelve la escala actual del veh�culo.
     * @return
     */
    float getScale() const;


    /**
     * Devuelve la escala actual del veh�culo.
     * @return
     */
    float getScalingFactor() const;


    /**
     * Devuelve true si pos corresponde al veh�culo actual. En caso de que sea true, tambi�n devuelve la posici�n Y
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
};


#endif // RIVAL_CAR_H
