#include <cstdlib>

#include "bindings.h"

void InitBindings(bindings_t &bindings)
{
    bindings.array = nullptr;
    bindings.count = 0;
}

static void set_bindings_count(bindings_t &bindings, size_t count)
{
    bindings.count = count;
}

static bool BindingsIsFree(const bindings_t &bindings)
{
    bool res = true;
    if (bindings.array != nullptr)
        res = false;

    return res;
}

static result_t AllocateBindingsArray(bindings_t &bindings)
{
    result_t res_code = SUCCESS;
    bindings.array = (bind_t *)malloc(bindings.count * sizeof(bind_t));

    if (bindings.array == nullptr)
        res_code = MEMORY_ALLOCATE_ERROR;

    return res_code;
}

static result_t InputBindingsArray(bindings_t &bindings, FILE *f)
{
    result_t res_code = SUCCESS;

    for (size_t i = 0; (res_code == SUCCESS) && (i < bindings.count); ++i)
        res_code = InputBinding(bindings.array[i], f);

    return res_code;
}

static result_t InputBindingsCount(bindings_t &bindings, FILE *f)
{
    result_t res_code = SUCCESS;
    int64_t unsafe_bindings_count;

    if (fscanf(f, "%lld", &unsafe_bindings_count) != 1)
        res_code = INCORRECT_NUMBER;
    else if (unsafe_bindings_count <= 0 || unsafe_bindings_count > SIZE_MAX)
        res_code = INCORRECT_BINDINGS_COUNT;
    else
        set_bindings_count(bindings, (size_t) unsafe_bindings_count);

    return res_code;
}

result_t InputBindings(bindings_t &bindings, FILE *f)
{
    if (!BindingsIsFree(bindings) || f == nullptr)
        return MEMORY_ERROR;

    result_t res_code = InputBindingsCount(bindings, f);

    if (res_code == SUCCESS)
    {
        res_code = AllocateBindingsArray(bindings);

        if (res_code == SUCCESS)
        {
            res_code = InputBindingsArray(bindings, f);

            if (res_code != SUCCESS) FreeBindings(bindings);
        }
    }

    return res_code;
}

result_t CheckBindings(bindings_t &bindings, size_t &points_count)
{
    if (BindingsIsFree(bindings))
        return MEMORY_ERROR;

    result_t res_code = SUCCESS;

    for (size_t i = 0; (res_code == SUCCESS) && (i < bindings.count); ++i)
    {
        bind_t cur_binding = bindings.array[i];

        if (cur_binding.point_1 >= points_count || cur_binding.point_2 >= points_count)
            res_code = INCORRECT_BINDING_DATA;
    }

    return res_code;
}

result_t DrawBindings(const scene_t &scene, const bindings_t &bindings, const points_t &points)
{
    if (BindingsIsFree(bindings) || PointsIsFree(points))
        return MEMORY_ERROR;

    for (size_t i = 0; i < bindings.count; ++i)
        DrawBinding(scene, bindings.array[i], points);

    return SUCCESS;
}

void FreeBindings(bindings_t &bindings)
{
    if (bindings.array != nullptr)
    {
        free(bindings.array);
        bindings.array = nullptr;
    }
}
