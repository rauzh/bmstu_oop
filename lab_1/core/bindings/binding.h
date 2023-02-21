#ifndef BINDING_H
#define BINDING_H

#include <cstdio>

#include "points.h"
#include "draw.h"
#include "errors.h"

struct bind_t
{
    size_t point_1;
    size_t point_2;
};

void DrawBinding(const scene_t &scene, const bind_t &binding, const points_t &points);
result_t InputBinding(bind_t &binding, FILE *f);

#endif // BINDING_H
