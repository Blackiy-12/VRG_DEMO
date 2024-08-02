#pragma once

#include <Vector3/Vector3.h>

/**
 * @brief Store arguments from User
 */
struct Arguments
{
    Vector3<float> Start{0.0f, 0.0f, 0.0f};

    Vector3<float> Goal{-1.0f, -1.0f, -1.0f};

    float StartVelocity = -1.0f;

    float Weight = 0.0f;

    double SimStep = .0f;

    bool WithAir = false; //TODO add later
};
