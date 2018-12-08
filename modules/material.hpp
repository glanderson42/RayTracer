//
// Created by glanderson on 11/27/18.
//

#ifndef RAYTRACING_MATERIAL_HPP
#define RAYTRACING_MATERIAL_HPP

struct  hit_record;

#include "ray.hpp"
#include "hitable.hpp"
#include "vec3.hpp"

float schlick(float cosine, float ref_idx)
{
    float r_0 = std::pow((1 - ref_idx) / (1 + ref_idx), 2.0f);
    return r_0 + (1 - r_0) * std::pow((1 - cosine), 5.0f);
}

bool refract(vec3&& v, const vec3& n, float ni_over_nt, vec3& refracted)
{
    vec3 uv = unit_vector(std::move(v));
    float dt = dot(uv, n);
    float discriminant = 1.0f - std::pow(ni_over_nt, 2.0f) * (1 - std::pow(dt, 2.0f));
    if(discriminant > 0)
    {
        refracted = ni_over_nt * (uv - n * dt) - n * std::sqrt(discriminant);
        return true;
    }

    return false;
}

vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2 * dot(v, n) * n;
}

vec3 random_in_unit_sphere()
{
    vec3 p;
    do
    {
        p = 2.0f * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while(p.squared_length() >= 1.0f);
    return p;
}

struct material
{
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

struct lambertian : public material
{
    vec3 albedo;

    lambertian(const vec3& vec) : albedo(vec) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
    {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }
};

struct metal : public material // \m/
{
    vec3 albedo;
    float fuzz;

    metal(const vec3& a, float f) : albedo(a)
    {
        if(f < 1) fuzz = f;
        else fuzz = 1;
    }

    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
    {
        vec3 reflected = reflect(unit_vector(r_in.direction_vector()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;

        return (dot(scattered.direction_vector(), rec.normal) > 0);
    }
};

struct dialetric : public material
{
    float ref_idx;
    dialetric(float rf) : ref_idx(rf) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
    {
        vec3 outward_normal;
        vec3 reflected = reflect(r_in.direction_vector(), rec.normal);
        float ni_over_nt;
        attenuation = vec3(1.0f, 1.0f, 1.0f);
        vec3 refracted;
        float reflect_prob;
        float cosine;
        if(dot(r_in.direction_vector(), rec.normal) > 0)
        {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = dot(r_in.direction_vector(), rec.normal) / r_in.direction_vector().length();
            cosine = std::sqrt(1 - ref_idx * ref_idx * (1 - cosine * cosine));
        }
        else
        {
            outward_normal = rec.normal;
            ni_over_nt = 1.0f / ref_idx;
            cosine = -dot(r_in.direction_vector(), rec.normal) / r_in.direction_vector().length();
        }

        if(refract(r_in.direction_vector(), outward_normal, ni_over_nt, refracted))
        {
            reflect_prob = schlick(cosine, ref_idx);
        }
        else
        {
            reflect_prob = 1.0f;
        }
        if(drand48() < reflect_prob)
        {
            scattered = ray(rec.p, reflected);
        }
        else
        {
            scattered = ray(rec.p, refracted);
        }

        return true;
    }
};

#endif //RAYTRACING_MATERIAL_HPP
