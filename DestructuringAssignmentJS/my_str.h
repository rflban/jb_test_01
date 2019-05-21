#if !defined __MY_STR_H
#define __MY_STR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "exit.h"

#if !defined ssize_t
#if defined __unix__ && __unix__
#include <unistd.h>
#endif /*unix ssize_t*/
#endif /*ssize_t*/

#define BUFFER_INIT_SIZE 120
#define __SIZE_MAX SIZE_MAX

/*!
Считывает последовательность символов до EOL или EOF, включая EOL,
из потока stream в строку *lineptr. Для *lineptr должен быть возможен
вызов free. Память под результрующую строку выделяется динамически.
В *n записывается объем выделенной памяти в байтах.

@param [in, out] lineptr
@param [in, out] n
@param [in] stream

@return Возвращает кол-во считанных символов в случае успеха.
Иначе - EOF.
*/
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);

/*!
Создает новую строку на основе source, заменяя в ней подстроку
search на replace. Память выделяется динамически.

@param [in] source
@param [in] search
@param [in] replace

@return Возвращает указатель на первый элемент новой строки.
*/
char *str_replace(const char *source, const char *search, const char *replace);

/*!
Ищет подстроку search в строке source.

@param [in] source
@param [in] search

@return Возвращает указатель на первый элемент подстроки 
search в строке source если поиск успешен. Иначе - NULL.
*/
char *str_find(const char *source, const char *search);

#endif /*__MY_STR_H*/