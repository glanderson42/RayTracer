//
// Created by glanderson on 11/26/18.
//

#ifndef RAYTRACING_HITABLE_HPP
#define RAYTRACING_HITABLE_HPP

#include "ray.hpp"

struct material;

struct hit_record
{
    float t;
    vec3 p;
    vec3 normal;
    material* mat_ptr;
};

struct hitable {
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};


#endif //RAYTRACING_HITABLE_HPP
