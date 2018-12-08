//
// Created by glanderson on 11/26/18.
//

#ifndef RAYTRACING_VEC3_HPP
#define RAYTRACING_VEC3_HPP

#include <cmath>
#include <iostream>

struct vec3
{
    float r;
    float g;
    float b;

    vec3() = default;
    vec3(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
    vec3(const vec3& v)
    {
        this->r = v.r;
        this->g = v.g;
        this->b = v.b;
    }

    float getX() const { return r; }
    float getY() const { return g; }
    float getZ() const { return b; }
    float getR() const { return r; }
    float getG() const { return g; }
    float getB() const { return b; }

    const vec3& operator+() const { return *this; }
    vec3 operator-() const { return vec3(-r, -g, -b); }
    float operator[](const int index)
    {
        if(index == 0) return r;
        else if(index == 1) return g;
        else if(index == 2) return b;
    }

    float length() const
    {
        return std::sqrt(std::pow(r, 2.0f) + std::pow(g, 2.0f) + std::pow(b, 2.0f));
    }

    float squared_length() const
    {
        return std::pow(r, 2.0f) + std::pow(g, 2.0f) + std::pow(b, 2.0f);
    }

    void make_unit_vector()
    {
        auto k = 1.0 / std::sqrt((float)std::pow(r, 2) + (float)std::pow(g, 2) + (float)std::pow(b, 2));
        r *= k;
        g *= k;
        b *= k;
    }

    vec3& operator+=(const vec3& v)
    {
        this->r += v.r;
        this->g += v.g;
        this->b += v.b;

        return *this;
    }

    vec3& operator*=(const vec3& v)
    {
        this->r *= v.r;
        this->g *= v.g;
        this->b *= v.b;

        return *this;
    }

    vec3& operator/=(const vec3& v)
    {
        this->r /= v.r;
        this->g /= v.g;
        this->b /= v.b;

        return *this;
    }

    vec3& operator-=(const vec3& v)
    {
        this->r -= v.r;
        this->g -= v.g;
        this->b -= v.b;

        return *this;
    }

    vec3& operator*=(const float t)
    {
        this->r *= t;
        this->g *= t;
        this->b *= t;

        return *this;
    }

    vec3& operator/=(const float t)
    {
        this->r /= t;
        this->g /= t;
        this->b /= t;

        return *this;
    }
};

std::istream& operator>>(std::istream& in, vec3& v)
{
    in >> v.r >> v.g >> v.b;
    return in;
}

std::ostream& operator<<(std::ostream& out, vec3& v)
{
    out << v.r << v.g << v.b;
    return out;
}

vec3 operator+(const vec3& v1, const vec3& v2)
{
    return vec3(v1.r + v2.r, v1.g + v2.g, v1.b + v2.b);
}

vec3 operator-(const vec3& v1, const vec3& v2)
{
    return vec3(v1.r - v2.r, v1.g - v2.g, v1.b - v2.b);
}

vec3 operator*(const vec3& v1, const vec3& v2)
{
    return vec3(v1.r * v2.r, v1.g * v2.g, v1.b * v2.b);
}

vec3 operator/(const vec3& v1, const vec3& v2)
{
    return vec3(v1.r / v2.r, v1.g / v2.g, v1.b / v2.b);
}

vec3 operator*(float t, const vec3& v)
{
    return vec3(t * v.r, t * v.g, t * v.b);
}

vec3 operator/(const vec3 v, float t)
{
    return vec3(v.r / t, v.g / t, v.b / t);
}

vec3 operator*(const vec3& v, float t)
{
    return vec3(t * v.r, t * v.g, t * v.b);
}

float dot(const vec3& v1, const vec3& v2)
{
    return v1.r * v2.r + v1.g * v2.g + v1.b * v2.b;
}

vec3 cross(const vec3& v1, const vec3& v2)
{
    return vec3(
            (v1.g * v2.b - v1.b * v2.g),
           -(v1.r * v2.b - v1.b * v2.r),
            (v1.r * v2.g - v1.g * v2.r)
            );
}

vec3 unit_vector(vec3&& v)
{
    return v / v.length();
}

#endif //RAYTRACING_VEC3_HPP
