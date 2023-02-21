#include "tasks.h"

result_t DoTask(task_t &task)
{
    result_t res_code = SUCCESS;
    static figure_t figure;

    switch (task.action)
    {
        case LOAD:
            res_code = LoadFigure(figure, task.filename);
            break;
        case MOVE:
            res_code = MoveFigure(figure, task.move_coefs);
            break;
        case SCALE:
            res_code = ScaleFigure(figure, task.center, task.scale_coefs);
            break;
        case ROTATE:
            res_code = RotateFigure(figure, task.center, task.rotate_coefs);
            break;
        case DRAW:
            res_code = DrawFigure(figure, task.scene);
            break;
        case FREE:
            FreeFigure(figure);
            break;
        default:
            res_code = INCORRECT_COMMAND;
            break;
    }

    return res_code;
}
