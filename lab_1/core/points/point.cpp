#include <cstdlib>
#include <limits.h>
#include <cmath>

#include "point.h"

result_t InputPoint(point_t &point, FILE *f)
{
    result_t res_code = SUCCESS;

    if (fscanf(f, "%lf %lf %lf", &point.x, &point.y, &point.z) != 3)
        res_code = INCORRECT_POINT_DATA;

    return res_code;
}

void MovePoint(point_t &point, const move_t &coefs)
{
    point.x += coefs.dx;
    point.y += coefs.dy;
    point.z += coefs.dz;
}

void ScalePoint(point_t &point, const point_t &center, const scale_t &coefs)
{
    point.x = coefs.kx * point.x + (1 - coefs.kx) * center.x;
    point.y = coefs.ky * point.y + (1 - coefs.ky) * center.y;
    point.z = coefs.kz * point.z + (1 - coefs.kz) * center.z;
}

move_t InitMove(double dx, double dy, double dz)
{
    move_t move;

    move.dx = dx;
    move.dy = dy;
    move.dz = dz;

    return move;
}

static double to_radians(const double &angle)
{
    return angle * M_PI / 180.0;
}

void MovePointToOrigin(point_t &point, const point_t &center)
{
    move_t move_to_origin = InitMove(-center.x, -center.y, -center.z);

    MovePoint(point, move_to_origin);
}

void MovePointToCenter(point_t &point, const point_t &center)
{
    move_t move_to_center = InitMove(center.x, center.y, center.z);

    MovePoint(point, move_to_center);
}

void RotatePointX(point_t &point, const double &angle)
{
    double temp_y = point.y;
    point.y = point.y * cos(to_radians(angle)) - point.z * sin(to_radians(angle));
    point.z = temp_y * sin(to_radians(angle)) + point.z * cos(to_radians(angle));
}

void RotatePointY(point_t &point, const double &angle)
{
    double temp_x = point.x;
    point.x = point.x * cos(to_radians(angle)) + point.z * sin(to_radians(angle));
    point.z = -temp_x * sin(to_radians(angle)) + point.z * cos(to_radians(angle));
}

void RotatePointZ(point_t &point, const double &angle)
{
    double temp_x = point.x;
    point.x = point.x * cos(to_radians(angle)) - point.y * sin(to_radians(angle));
    point.y = temp_x * sin(to_radians(angle)) + point.y * cos(to_radians(angle));
}

void RotatePoint(point_t &point, const point_t &center, const rotate_t &coefs)
{
    MovePointToOrigin(point, center);

    RotatePointX(point, coefs.ax);
    RotatePointY(point, coefs.ay);
    RotatePointZ(point, coefs.az);

    MovePointToCenter(point, center);
}
