//
// Created by glanderson on 11/26/18.
//

#ifndef RAYTRACING_SPHERE_HPP
#define RAYTRACING_SPHERE_HPP


#include "hitable.hpp"
#include "vec3.hpp"
#include "ray.hpp"

struct sphere : public hitable {
    vec3 center;
    float radius;
    material* mat_ptr;

    sphere() = default;
    sphere(vec3 _center, float _radius, material* _material) : center(_center), radius(_radius), mat_ptr(_material) {}

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const
    {
        vec3 oc = r.origin_vector() - center;
        float a = dot(r.direction_vector(), r.direction_vector());
        float b = dot(oc, r.direction_vector());
        float c = dot(oc, oc) - std::pow(radius, 2.0f);
        float discriminant = std::pow(b, 2.0f) - a * c;
        if(discriminant > 0)
        {
            auto temp = (- b - std::sqrt(discriminant)) / a;
            if(temp < t_max && temp > t_min)
            {
                rec.t = temp;
                rec.p = r.point_at_parameter(rec.t);
                rec.normal = (rec.p - center) / radius;
                rec.mat_ptr = mat_ptr;
                return true;
            }

            temp = (- b + std::sqrt(discriminant)) / a;
            if(temp < t_max && temp > t_min)
            {
                rec.t = temp;
                rec.p = r.point_at_parameter(rec.t);
                rec.normal = (rec.p - center) / radius;
                rec.mat_ptr = mat_ptr;
                return true;
            }
        }

        return false;
    }
};


#endif //RAYTRACING_SPHERE_HPP
