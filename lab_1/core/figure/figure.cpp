#include <cstdio>

#include "figure.h"

figure_t &InitFigure(void)
{
    static figure_t figure;
    InitPoints(figure.points);
    InitBindings(figure.bindings);

    return figure;
}

result_t CheckFigure(figure_t &figure)
{
    size_t points_count = get_points_count(figure.points);
    result_t res_code = CheckBindings(figure.bindings, points_count);

    return res_code;
}

void CopyFigure(figure_t &dst, const figure_t &src)
{
    dst = src;
}

static result_t LoadData(figure_t &temp_figure, FILE *f)
{
    temp_figure = InitFigure();
    result_t res_code = InputPoints(temp_figure.points, f);

    if (res_code == SUCCESS)
    {
        res_code = InputBindings(temp_figure.bindings, f);

        if (res_code != SUCCESS)
            FreePoints(temp_figure.points);
    }

    return res_code;
}

result_t LoadFigure(figure_t &figure, filename_ptr_t &filename)
{
    FILE *f = fopen(filename, "r");
    if (f == nullptr)
        return FILE_OPEN_ERROR;

    figure_t unsafe_figure;
    result_t res_code = LoadData(unsafe_figure, f);
    fclose(f);

    if (res_code == SUCCESS)
    {
        res_code = CheckFigure(unsafe_figure);

        if (res_code == SUCCESS)
        {
            FreeFigure(figure);
            CopyFigure(figure, unsafe_figure);
        }
        else
            FreeFigure(unsafe_figure);
    }

    return res_code;
}

result_t DrawFigure(const figure_t &figure, const scene_t &scene)
{
    ClearScene(scene);
    result_t res_code = DrawBindings(scene, figure.bindings, figure.points);

    return res_code;
}

result_t MoveFigure(figure_t &figure, const move_t &coefs)
{
    result_t res_code = MovePoints(figure.points, coefs);

    return res_code;
}

result_t ScaleFigure(figure_t &figure, const point_t &center, const scale_t &coefs)
{
    result_t res_code = ScalePoints(figure.points, center, coefs);

    return res_code;
}

result_t RotateFigure(figure_t &figure, const point_t &center, const rotate_t &coefs)
{
    result_t res_code = RotatePoints(figure.points, center, coefs);

    return res_code;
}

void FreeFigure(figure_t &figure)
{
    FreePoints(figure.points);
    FreeBindings(figure.bindings);
}
