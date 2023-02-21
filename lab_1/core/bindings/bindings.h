#ifndef BINDINGS_H
#define BINDINGS_H

#include <cstdio>

#include "points.h"
#include "draw.h"
#include "errors.h"
#include "binding.h"

struct bindings_t
{
    bind_t *array;
    size_t count;
};

void InitBindings(bindings_t &bindings);
result_t InputBindings(bindings_t &bindings, FILE *f);
result_t CheckBindings(bindings_t &bindings, size_t &points_count);
result_t DrawBindings(const scene_t &scene, const bindings_t &bindings, const points_t &points);
void FreeBindings(bindings_t &bindings);

#endif // BINDINGS_H
