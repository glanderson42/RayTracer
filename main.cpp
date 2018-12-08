#include <iostream>
#include <limits>
#include <fstream>
#include <values.h>

#include "modules/raytracing_modules.hpp"

vec3 color(const ray& r, hitable *world, int depth) {
    hit_record rec;
    if(world->hit(r, 0.001, MAXFLOAT, rec))
    {
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation*color(scattered, world, depth+ 1);
        }
        else {
            return vec3(0,0,0);
        }
    }
    else
    {
        vec3 unit_direction = unit_vector(r.direction_vector());
        float t = 0.5f * (unit_direction.getY() + 1.0f);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

hitable* random_scene()
{
    int n = 500;
    hitable** list = new hitable*[n + 1];
    list[0] = new sphere(vec3(0.0f, -10000.0f, 0.0f), 1000.0f, new lambertian(vec3(0.5f, 0.5f, 0.5f)));
    int i = 1;
    for(int j = -11; j < 11; ++j)
    {
        for(int k = -11; k < 11; ++k)
        {
            float choose_mat = drand48();
            vec3 center(j + 0.9 * drand48(), 0.2, k + 0.9 * drand48());
            if((center - vec3(4, 0.2f, 0)).length() > 0.9)
            {
                if(choose_mat < 0.8)
                {
                    list[i++] = new sphere(center, 0.2,
                            new lambertian(vec3(std::pow(drand48(), 2.0f), std::pow(drand48(), 2.0f), std::pow(drand48(), 2.0f))));
                }
                else if(choose_mat < 0.95)
                {
                    list[i++] = new sphere(center, 0.2,
                            new metal(vec3(0.5*(1 + drand48()), 0.5*(1 + drand48()), 0.5*(1 + drand48())), 0.5*drand48()));
                }
                else
                {
                    list[i++] = new sphere(center, 0.2, new dialetric(1.5));
                }
            }
        }
    }

    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dialetric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

    return new hitable_list(list ,i);
}

int main()
{
    int nx = 1920;
    int ny = 1080;
    int ns = 69;
    std::ofstream outfile("raytracing.ppm");
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    outfile << "P3\n" << nx << " " << ny << "\n255\n";
    hitable* list[5];

    float R = cosf(M_PI / 4.0f);
    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.0));
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new dialetric(1.5));
    list[4] = new sphere(vec3(-1,0,-1), -0.45, new dialetric(1.5));
    hitable* world = new hitable_list(list,5);
    world = random_scene();

    vec3 lookfrom(13,2,3);
    vec3 lookat(0,0,0);
    float dist_to_focus = 10.0;
    float aperture = 0.5;

    camera cam(lookfrom, lookat, vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus);

    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s=0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world,0);
            }
            col /= float(ns);
            col = vec3( std::sqrt(col[0]), std::sqrt(col[1]), std::sqrt(col[2]) );
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            std::cout << ir << " " << ig << " " << ib << '\n';
            outfile << ir << " " << ig << " " << ib << '\n';
        }
    }
}