#include "my_str.h"

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
    if (lineptr == NULL || n == NULL || stream == NULL)
    {
        exit_code = __EXIT_REQUEST_NULL;
        return EOF;
    }

    char *buffer;
    char read_ending = '\0';
    size_t buf_size = BUFFER_INIT_SIZE;
    ssize_t read_counter = 0;

    if (*lineptr == NULL || *n == 0)
    {
        *n = BUFFER_INIT_SIZE;

        if (!(*lineptr))
            *lineptr = (char*)malloc(*n);
        else
            *lineptr = (char*)realloc(*lineptr, *n);

        if (!(*lineptr))
        {
            exit_code = __EXIT_MEM_ERROR;
            return EOF;
        }
    }

    buffer = (char*)malloc(buf_size);
    if (!buffer)
    {
        exit_code = __EXIT_MEM_ERROR;
        return EOF;
    }

    while (read_ending != '\n' && buffer != NULL)
    {
        char *temp = buffer;
        ssize_t zero_ind = 0;

        buffer = fgets(buffer, buf_size, stream);

        if (buffer)
        {
            while (buffer[zero_ind] != '\0')
                zero_ind++;

            if (read_counter + zero_ind + 1 > *n)
            {
                *n = (read_counter + zero_ind + 1);

                *lineptr = (char*)realloc(*lineptr, *n);
                if (!(*lineptr))
                {
                    exit_code = __EXIT_MEM_ERROR;
                    free(buffer);
                    return EOF;
                }
            }

            for (ssize_t i = 0; i < zero_ind; i++)
                (*lineptr)[read_counter + i] = buffer[i];
                
            read_counter += zero_ind;
            read_ending = buffer[zero_ind - 1];
        }
        else
            free(temp);
    }
    (*lineptr)[read_counter] = '\0';

    free(buffer);

    if (read_counter == 0)
        return EOF;

    return read_counter;
}

char *str_replace(const char *source, const char *search, const char *replace)
{
    if (source == NULL || search == NULL || replace == NULL)
    {
        exit_code = __EXIT_REQUEST_NULL;
        return NULL;
    }

    char *res;
    int res_len;
    int src_len;
    int srch_len;
    int rplc_len;
    int srch_cnt;

    for (src_len = 0; source[src_len] != '\0'; src_len++);
    for (srch_len = 0; search[srch_len] != '\0'; srch_len++);
    for (rplc_len = 0; replace[rplc_len] != '\0'; rplc_len++);

    if (srch_len == 0)
    {
        res_len = src_len + rplc_len * (src_len + 1);
        res = (char*)malloc((res_len + 1) * sizeof(char));
        
        if (!res)
        {
            exit_code = __EXIT_MEM_ERROR;
            return NULL;
        }
        res[res_len] = '\0';

        for (int i = 0, j = 0; i < src_len + 1; i++, j++)
        {
            for (int k = 0; k < rplc_len; k++, j++)
                res[j] = replace[k];

            res[j] = source[i];
        }

        return res;
    }

    srch_cnt = 0;
    for (int i = 0; i < src_len; i++)
    {
        if (str_find(&source[i], search) == &source[i])
        {
            i += srch_len - 1;
            srch_cnt++;
        }
    }

    res_len = src_len - srch_cnt * (srch_len - rplc_len);
    res = (char*)malloc((res_len + 1) * sizeof(char));

    if (!res)
    {
        exit_code = __EXIT_MEM_ERROR;
        return NULL;
    }

    for (int i = 0, j = 0; i < src_len; i++, j++)
    {
        if (&source[i] == str_find(&source[i], search))
        {
            for (int k = 0; k < rplc_len; k++, j++)
                res[j] = replace[k];

            i += srch_len - 1;
            j--;
        }
        else
            res[j] = source[i];
    }
    res[res_len] = '\0';

    return res;
}

char *str_find(const char *source, const char *search)
{
    if (source == NULL || search == NULL)
    {
        exit_code = __EXIT_REQUEST_NULL;
        return NULL;
    }

    if (search[0] == '\0')
        return (char*)source;

    int src_len;
    int srch_len;

    for (src_len = 0; source[src_len] != '\0'; src_len++);
    for (srch_len = 0; search[srch_len] != '\0'; srch_len++);

    for (int i = 0, j = 0, finded = 0; i < src_len; i++)
    {            
        if (finded)
        {
            if (source[i] == search[j])
                j++;
            else
            {
                finded = 0;
                j = 0;
            }
        }
        else
        {
            if (source[i] == search[j])
            {
                finded = 1;
                j++;
            }
        }

        if (j >= srch_len)
            return (char*)(&source[i] - srch_len + 1);
    }

    return NULL;
}