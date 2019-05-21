#include "exit.h"

int exit_code = __EXIT_SUCCESS;

void usage_check(const int argc, char **argv)
{
    exit_code = __EXIT_SUCCESS;

    if (argc != 7)
        exit_code = __EXIT_IVALID_USAGE;
    else if (!(argv[3][0] == '-' && argv[3][1] == 's' && argv[3][2] == '\0'))
        exit_code = __EXIT_IVALID_USAGE;
    else if (!(argv[5][0] == '-' && argv[5][1] == 'r' && argv[5][2] == '\0'))
        exit_code = __EXIT_IVALID_USAGE;
}

void exit_process(int leave)
{
    switch (exit_code)
    {
        case __EXIT_FAILURE:
            fprintf(stderr, "Error\n");
            __EXIT(exit_code, leave);
            break;
        case __EXIT_IVALID_USAGE:
            fprintf(stderr, "Invalid usage. Exapmle:\n"
                "app.exe <in> <out> –s <search> –r <replace>\n");
            __EXIT(exit_code, leave);
            break;
        case __EXIT_FOPEN_ERROR:
            fprintf(stderr, "Could not open file:\n%s\n", strerror(errno));
            __EXIT(exit_code, leave);
            break;
        case __EXIT_FCLOSE_ERROR:
            fprintf(stderr, "Could not close file:\n%s\n", strerror(errno));
            __EXIT(exit_code, leave);
            break;
        case __EXIT_READ_ERROR:
            fprintf(stderr, "Invalid input data\n");
            __EXIT(exit_code, leave);
            break;
        case __EXIT_REQUEST_NULL:
            fprintf(stderr, "Null pointer request\n");
            __EXIT(exit_code, leave);
            break;
        case __EXIT_MEM_ERROR:
            fprintf(stderr, "Memory allocation error\n");
            __EXIT(exit_code, leave);
            break;
    }
}