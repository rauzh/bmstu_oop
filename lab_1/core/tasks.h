#ifndef TASKS_HANDLING_H
#define TASKS_HANDLING_H

#include "figure.h"
#include "draw.h"
#include "errors.h"

enum action_t
{
    LOAD,
    MOVE,
    SCALE,
    ROTATE,
    DRAW,
    FREE
};

struct task_t
{
    filename_ptr_t filename; 
    point_t center;
    action_t action;
    union 
    {  
        move_t move_coefs;       
        scale_t scale_coefs;     
        rotate_t rotate_coefs;
    };
    scene_t scene;
};

result_t DoTask(task_t &task);

#endif // TASKS_HANDLING_H
