#include <cstdlib>

#include "binding.h"

static void set_binding_points(bind_t &binding, size_t point_1, size_t point_2)
{
    binding.point_1 = point_1;
    binding.point_2 = point_2;
}

result_t InputBinding(bind_t &binding, FILE *f)
{
    result_t res_code = SUCCESS;
    int64_t unsafe_point_1, unsafe_point_2;

    if (fscanf(f, "%lld %lld", &unsafe_point_1, &unsafe_point_2) != 2)
        res_code = INCORRECT_NUMBER;
    else if (unsafe_point_1 > SIZE_MAX|| unsafe_point_2 > SIZE_MAX|| 
            unsafe_point_1 < 0 || unsafe_point_2 < 0)
        res_code = INCORRECT_BINDING_DATA;
    else
        set_binding_points(binding, (size_t) unsafe_point_1, (size_t) unsafe_point_2);

    return res_code;
}

void DrawBinding(const scene_t &scene, const bind_t &binding, const points_t &points)
{
    point_t point_1 = points.array[binding.point_1];
    point_t point_2 = points.array[binding.point_2];

    DrawLine(scene, point_1, point_2);
}
