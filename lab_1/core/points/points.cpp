#include <cstdlib>
#include <limits.h>
#include <cmath>

#include "points.h"

void InitPoints(points_t &points)
{
    points.array = nullptr;
    points.count = 0;
}

static void set_points_count(points_t &points, size_t count)
{
    points.count = count;
}

size_t get_points_count(const points_t &points)
{
    return points.count;
}

bool PointsIsFree(const points_t &points)
{
    bool res = true;
    if (points.array != nullptr)
        res = false;

    return res;
}

result_t AllocatePointsArray(points_t &points)
{
    result_t res_code = SUCCESS;
    points.array = (point_t *)malloc(points.count * sizeof(point_t));

    if (points.array == nullptr)
        res_code = MEMORY_ALLOCATE_ERROR;

    return res_code;
}

result_t InputPointsArray(points_t &points, FILE *f)
{
    result_t res_code = SUCCESS;

    for (size_t i = 0; (res_code == SUCCESS) && (i < points.count); ++i)
        res_code = InputPoint(points.array[i], f);

    return res_code;
}

static result_t InputPointsCount(points_t &points, FILE *f)
{
    result_t res_code = SUCCESS;
    int64_t unsafe_points_count;

    if (fscanf(f, "%lld", &unsafe_points_count) != 1)
        res_code = INCORRECT_NUMBER;
    else if (unsafe_points_count < 2 || unsafe_points_count > SIZE_MAX)
        res_code = INCORRECT_POINTS_COUNT;
    else
        set_points_count(points, (size_t) unsafe_points_count);

    return res_code;
}

result_t InputPoints(points_t &points, FILE *f)
{
    if (!PointsIsFree(points) || f == nullptr)
        return MEMORY_ERROR;

    result_t res_code = InputPointsCount(points, f);

    if (res_code == SUCCESS)
    {
        res_code = AllocatePointsArray(points);

        if (res_code == SUCCESS)
        {
            res_code = InputPointsArray(points, f);

            if (res_code != SUCCESS) FreePoints(points);
        }
    }

    return res_code;
}

result_t MovePoints(points_t &points, const move_t &coefs)
{
    if (PointsIsFree(points))
        return MEMORY_ERROR;

    for (size_t i = 0; i < points.count; ++i)
        MovePoint(points.array[i], coefs);

    return SUCCESS;
}

result_t ScalePoints(points_t &points, const point_t &center, const scale_t &coefs)
{
    if (PointsIsFree(points))
        return MEMORY_ERROR;

    for (size_t i = 0; i < points.count; ++i)
        ScalePoint(points.array[i], center, coefs);

    return SUCCESS;
}

result_t RotatePoints(points_t &points, const point_t &center, const rotate_t &coefs)
{
    if (PointsIsFree(points))
        return MEMORY_ERROR;

    for (size_t i = 0; i < points.count; ++i)
        RotatePoint(points.array[i], center, coefs);

    return SUCCESS;
}

void FreePoints(points_t &points)
{
    if (points.array != nullptr)
    {
        free(points.array);
        points.array = nullptr;
    }
}
