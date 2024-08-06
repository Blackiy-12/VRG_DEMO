#pragma once 

#include <Simulation/SimData.h>
#include <ArgumentParser/Arguments.h>
#include <Simulation/MovementSystem.h>

#include <entt/entt.hpp>

class Simulation
{
public:
    Simulation(const Arguments& Data);


    ~Simulation();


    /**
     * @brief Run simulations 
     */
    void run();

private:
    SimData m_Data {};

    std::shared_ptr<entt::registry> m_Registry;

    std::shared_ptr<MovementSystem> m_MovementSystem;

private:

    struct SimulationResult
    {
        enum Result
        {
            NONE,
            HIT,
            UNDERSHOT,
            OVERSHOT
        };

        Result SimRes = NONE;

        float Distance = 0.0f;
    };


    /**
     * @brief run single simulation of movement system
     * 
     * @param Print True - print data to output; False - dont print
     */
    SimulationResult runSimulation(bool Print);


    /**
     * @brief Clear all objects from registry
     */
    void clearRegistry();


    /**
     * @brief Change velocity vector according to angle of shoot
     */
    void countVelocityVector();
};