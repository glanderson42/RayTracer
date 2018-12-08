//
// Created by glanderson on 11/27/18.
//

#ifndef RAYTRACING_HITABLE_LIST_HPP
#define RAYTRACING_HITABLE_LIST_HPP

#include "hitable.hpp"

struct hitable_list : public hitable
{
    hitable** list;
    int list_size;

    hitable_list() = default;
    hitable_list(hitable** l, int size) : list(l), list_size(size) {}

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const
    {
        hit_record temp_rec;
        bool hit_anything = false;
        double closes_so_far = t_max;
        for(int i = 0; i < list_size; ++i)
        {
            if(list[i]->hit(r, t_min, closes_so_far, temp_rec))
            {
                hit_anything = true;
                closes_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_anything;
    }
};

#endif //RAYTRACING_HITABLE_LIST_HPP
