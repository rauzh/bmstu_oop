#ifndef POINT_H
#define POINT_H

#include <cstdio>

#include "figure_actions.h"
#include "errors.h"

struct point_t
{
    double x;
    double y;
    double z;
};

result_t InputPoint(point_t &point, FILE *f);
void MovePoint(point_t &point, const move_t &coefs);
void ScalePoint(point_t &point, const point_t &center, const scale_t &coefs);
void MovePointToOrigin(point_t &point, const point_t &center);
void MovePointToCenter(point_t &point, const point_t &center);
void RotatePointX(point_t &point, const double &angle);
void RotatePointY(point_t &point, const double &angle);
void RotatePointZ(point_t &point, const double &angle);
void RotatePoint(point_t &point, const point_t &center, const rotate_t &coefs);

#endif // POINT_H
