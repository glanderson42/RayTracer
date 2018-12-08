//
// Created by glanderson on 11/27/18.
//

#ifndef RAYTRACING_CAMERA_HPP
#define RAYTRACING_CAMERA_HPP

#include "ray.hpp"
#include "vec3.hpp"

vec3 random_in_unit_disk()
{
    vec3 p;
    do
    {
        p = 2.0f * vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
    } while(dot(p,p) >= 1.0f);
    return p;
}

struct camera
{
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    float lens_radius;

    camera(vec3& look_from, vec3& look_at, vec3 vup, float vertical_fov, float aspect, float aperture, float focus_dist)
    {
        lens_radius = aperture / 2;
        float theta = vertical_fov * (float)M_PI / 180.0f;
        float half_height = std::tan(theta / 2.0f);
        float half_width = aspect * half_height;
        origin = look_from;
        w = unit_vector(std::move(look_from - look_at));
        u = unit_vector(std::move(cross(vup, w)));
        v = cross(w, u);
        lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
        horizontal = 2 * half_width * focus_dist * u;
        vertical = 2 * half_height * focus_dist * v;
    }

    ray get_ray(float s, float t)
    {
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.getX() + v * rd.getY();
        return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
    }
};

#endif //RAYTRACING_CAMERA_HPP
