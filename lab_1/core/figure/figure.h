#ifndef FIGURE_H
#define FIGURE_H

#include <cstdio>

#include "figure_actions.h"
#include "points.h"
#include "bindings.h"
#include "draw.h"
#include "errors.h"

struct figure_t
{
    points_t points;
    bindings_t bindings;
};

typedef const char* filename_ptr_t;

figure_t &InitFigure(void);
result_t CheckFigure(figure_t &figure);
void CopyFigure(figure_t &dst, const figure_t &src);
result_t LoadFigure(figure_t &figure, filename_ptr_t &filename);
result_t DrawFigure(const figure_t &figure, const scene_t &scene);
result_t MoveFigure(figure_t &figure, const move_t &coefs);
result_t ScaleFigure(figure_t &figure, const point_t &center, const scale_t &coefs);
result_t RotateFigure(figure_t &figure, const point_t &center, const rotate_t &coefs);
void FreeFigure(figure_t &figure);

#endif // FIGURE_H
