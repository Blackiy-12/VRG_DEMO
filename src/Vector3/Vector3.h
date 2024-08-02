#pragma once

#include <cmath>

template <typename T>
class Vector3
{
public:
    T x;
    T y;
    T z;

public:

    Vector3()
    {
        x = 0;
        y = 0;
        z = 0;
    }


    Vector3(T x, T y, T z) :
        x(x),
        y(y),
        z(z)
    {

    }


    ~Vector3()
    {

    }


    float getLength() const
    {
        return static_cast<T>(sqrt(pow(this->x, 2) + pow(this->y, 2)+ pow(this->z, 2)));
    }


    Vector3<T> getUnitVector() const
    {
        if (getLength() == 0) return Vector3<T>{};

        return Vector3<T>{ x / getLength(), y / getLength(), z / getLength() };
    }


    bool operator==(const Vector3<T> &Right) const
    {
       return (this->x == Right.x && this->y == Right.y && this->z == Right.z);
    }


    bool operator!=(const Vector3<T> &Right) const
    {
       return !(*this == Right);
    }


    Vector3<T> operator+(const Vector3<T> &Right) const
    {
        return Vector3<T>{this->x + Right.x, this->y + Right.y, this->z + Right.z};
    }


    void operator+=(const Vector3<T> &Right)
    {
        this->x += Right.x;
        this->y += Right.y;
        this->z += Right.z;
    }


    Vector3<T> operator-(const Vector3<T> &Right) const
    {
        return Vector3<T>{this->x - Right.x, this->y - Right.y, this->z - Right.z};
    }

    
    void operator-=(const Vector3<T> &Right)
    {
        this->x -= Right.x;
        this->y -= Right.y;
        this->z -= Right.z;
    }


    Vector3<T> operator*(const T &Argument) const
    {
        return Vector3<T>{this->x * Argument, this->y * Argument, this->z * Argument};
    }


    void operator*=(const T &Argument)
    {
        this->x *= Argument;
        this->y *= Argument;
        this->z *= Argument;
    }


    /**
     * @warning NOT CHECKING DIVIDED BY ZERO
     */
    Vector3<T> operator/(const T &Argument) const
    {
        return Vector3<T>{this->x / Argument, this->y / Argument, this->z / Argument};
    }


    /**
     * @warning NOT CHECKING DIVIDED BY ZERO
     */
    void operator/=(const T &Argument)
    {
        this->x /= Argument;
        this->y /= Argument;
        this->z /= Argument;
    }

};

template <typename T>
/**
 * @brief Cross function for vectors
 * @return Vector
 */
Vector3<T> cross(const Vector3<T>& Left, const Vector3<T>& Right)
{
    Vector3<T> New{};

    New.x = Left.y * Right.z - Left.z * Right.y;
    New.y = Left.z * Right.x - Left.x * Right.z;
    New.z = Left.x * Right.y - Left.y * Right.x;

    return New;
}