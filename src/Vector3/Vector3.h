#pragma once

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