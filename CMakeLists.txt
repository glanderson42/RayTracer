cmake_minimum_required(VERSION 3.12)
project(RayTracing)

set(CMAKE_CXX_STANDARD 14)

add_executable(RayTracing main.cpp modules/vec3.hpp modules/hitable.hpp modules/ray.hpp modules/sphere.hpp modules/material.hpp modules/hitable_list.hpp modules/camera.hpp modules/raytracing_modules.hpp)