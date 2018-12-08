//
// Created by glanderson on 11/26/18.
//

#ifndef RAYTRACING_RAY_HPP
#define RAYTRACING_RAY_HPP

#include "vec3.hpp"

struct ray {
    vec3 origin;
    vec3 direction;

    ray() = default;
    ray(const vec3& origin_vector, const vec3& direction_vector) : origin(origin_vector), direction(direction_vector) {}

    vec3 origin_vector() const    { return this->origin; }
    vec3 direction_vector() const { return this->direction; }
    vec3 point_at_parameter(float t) const { return origin + t * direction; }
};


#endif //RAYTRACING_RAY_HPP
