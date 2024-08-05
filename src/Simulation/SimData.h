#pragma once

#include <Vector3/Vector3.h>

struct SimData
{
    Vector3<float> Start{0.0f, 0.0f, 0.0f};

    Vector3<float> Goal{-1.0f, -1.0f, -1.0f};

    float AccuracyToHit = 0.5f;


    Vector3<float> VelocityVector{0.0f, 0.0f, 0.0f};

    float StartVelocity = -1.0f;


    float Gravity = .0f;

    float AirDensity = 0.0f;


    float Weight = 0.0f;


    double SimStep = .0f;

    int MaxCountOfSimulation = 100000;

    float AngleOfShout = 0.0f;



    float CrossSectionalArea = 0.0f;

    float DragCoefficient = 0.0f;

};