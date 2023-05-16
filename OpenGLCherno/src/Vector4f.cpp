#include "Vector4f.h"
#include <iostream>

int Vector4f::getX() {
    return x;
}

int Vector4f::getY() {
    return y;
}

int Vector4f::getZ() {
    return z;
}

int Vector4f::getW() {
    return w;
}

void Vector4f::printVector()
{
    std::cout << x << ", " << y << ", " << z << std::endl;
}

Vector4f Vector4f::make_vector4f(float a, float b, float c, float d)
{
    Vector4f result;

    result.x = a;
    result.y = b;
    result.z = c;
    result.w = d;

    return result;
}

Vector4f Vector4f::normalize(Vector4f v)
{
    Vector4f result = v;

    float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    if (length > 0.0f) {
        float invLength = 1.0f / length;
        result.x *= invLength;
        result.y *= invLength;
        result.z *= invLength;
        result.w *= invLength;
    }
    return result;
}

Vector4f Vector4f::operator+(const Vector4f& other) const
{
    Vector4f result;

    result.x = x + other.x;
    result.y = y + other.y;
    result.z = z + other.z;
    result.w = w + other.w;

    return result;
}

Vector4f Vector4f::operator-(const Vector4f& other) const
{
    Vector4f result;

    result.x = x - other.x;
    result.y = y - other.y;
    result.z = z - other.z;
    result.w = w - other.w;

    return result;
}

float Vector4f::operator*(const Vector4f& other) const
{
    float result = 0.0;

    result += (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);

    return result;
}

Vector4f Vector4f::operator*(const float& other) const
{
    Vector4f result;

    result.x = x * other;
    result.y = y * other;
    result.z = z * other;
    result.w = w * other;

    return result;
}

Vector4f Vector4f::operator&(const Vector4f& other) const
{
    Vector4f result;

    result.x = y * other.z - z * other.y;
    result.y = z * other.x - x * other.z;
    result.z = x * other.y - y * other.x;

    result.w = 0;

    return result;
}
