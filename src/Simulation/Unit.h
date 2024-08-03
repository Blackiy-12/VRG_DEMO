#pragma once

#include <Vector3/Vector3.h>

struct ID
{
    const int ID;    
};


struct Velocity
{
    Vector3<float> VelocityVector{0, 0, 0}; // in m/s
};


struct Weight
{
    const float KG;
};


struct Position
{
    Vector3<float> Position; // in meters
};


struct HitIndicator
{
    bool Hit = false;
};


struct CollisionArea
{
    const float Radius = 0.0f;
};


struct Aerodynamic
{
    const float CrossSectionalArea = 0.0f; //m^2

    const float DragCoefficient = 0.0f;

};