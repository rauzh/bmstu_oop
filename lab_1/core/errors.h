#ifndef ERRORS_H
#define ERRORS_H

enum result_t
{
    SUCCESS,
    FILE_OPEN_ERROR,
    MEMORY_ALLOCATE_ERROR,
    MEMORY_ERROR,
    INCORRECT_COMMAND,
    INCORRECT_NUMBER,
    INCORRECT_POINTS_COUNT,
    INCORRECT_BINDINGS_COUNT,
    INCORRECT_POINT_DATA,
    INCORRECT_BINDING_DATA
};

void HandleError(const result_t &error);

#endif // ERRORS_H
