#if !defined __EXIT_H
#define __EXIT_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define __EXIT(exit_code, leave) ((leave) ? exit(exit_code) : (void)0)

#define __EXIT_SUCCESS 0
#define __EXIT_FAILURE 1
#define __EXIT_IVALID_USAGE 2
#define __EXIT_FOPEN_ERROR 3
#define __EXIT_FCLOSE_ERROR 4
#define __EXIT_READ_ERROR 5
#define __EXIT_REQUEST_NULL 6
#define __EXIT_MEM_ERROR 7

extern int exit_code;

/*!
Обрабатывает код выхода из функции, хранящийся в exit_code.
Если leave содержит в себе ненулевое значение, завершает работу программы.

@param leave [in]

@return Ничего не возвращает.
*/
void exit_process(int leave);

/*!
Проверяет правильность использования программы
по параметрам командной строки
согласно заданию лабораторной работы.

@param argc [in]
@param argv [in]

@return Ничего не возвращает.
*/
void usage_check(const int argc, char **argv);

#endif /*__EXIT_H*/