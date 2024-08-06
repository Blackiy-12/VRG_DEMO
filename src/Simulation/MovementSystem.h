#pragma once

#include <Vector3/Vector3.h>

#include <entt/entt.hpp>

class MovementSystem
{

public:
    MovementSystem(std::shared_ptr<entt::registry> Registry, float Gravity = 9.8f, float AirDensity = 1.2f);

    ~MovementSystem();

    /**
     * @brief simulation step. Update objects position and velocity
     * 
     * @param StepSize Delta time for simulation
     */
    void step(double StepSize);
    
private:

    std::shared_ptr<entt::registry> m_Registry;

    float m_Gravity;

    float m_AirDensity;

private:

    /**
     * @brief Check collision with Object with others objects with collision area
     * 
     * @param ObjectID ID of object
     * @param PrevPosition Start of line
     * @param NextPosition End of line
     */
    bool checkCollision(int const ObjectID, Vector3<float> const PrevPosition, Vector3<float> const NextPosition) const;
};