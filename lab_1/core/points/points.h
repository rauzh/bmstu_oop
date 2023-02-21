#ifndef POINTS_H
#define POINTS_H

#include <cstdio>

#include "figure_actions.h"
#include "errors.h"
#include "point.h"

struct points_t
{
    point_t *array;
    size_t count;
};

void InitPoints(points_t &points);
bool PointsIsFree(const points_t &points);
move_t InitMove(double dx, double dy, double dz);
result_t InputPoints(points_t &points, FILE *f);
size_t get_points_count(const points_t &points);
result_t MovePoints(points_t &points, const move_t &coefs);
result_t ScalePoints(points_t &points, const point_t &center, const scale_t &coefs);
result_t RotatePoints(points_t &points,const point_t &center,  const rotate_t &coefs);
void FreePoints(points_t &points);

#endif // POINTS_H
