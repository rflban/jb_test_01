#include <cstdio>
#include <cstdlib>

#include <queue>
#include <string>
#include <utility>

#include "my_str.h"

#define is_spacer(chr) (chr == ' ' || chr == '\n' || chr == '\t')
#define help_message(executable_name) ("Example: " + std::string(executable_name) + " <input file name>").c_str()

void parse_fname(const std::string &s, std::string &n, std::string &e)
{
    size_t dot_pos = s.find_first_of('.');

    if (int(dot_pos) == -1)
    {
        n = s;
        e = "";
    }
    else
    {
        n = s.substr(0, dot_pos);
        e = s.substr(dot_pos);
    }
}

std::string parse_line(const std::string &input_str, size_t &idx)
{
    return 0;
}

std::pair< std::string, std::string > cut_defination(const std::string &input_str, std::string &code, size_t &idx)
{
    if (input_str[idx] != '=')
    {
        return {"", ""};
    }
    
    std::string name = "";
    std::string value = "";
    std::string temp;

    while (is_spacer(code.back()))
    {
        code = code.substr(0, code.length() - 1);
    }
    
    while (!is_spacer(code.back()))
    {
        name = code.back() + name;
        code = code.substr(0, code.length() - 1);
    }
    
    temp = "";
    while (is_spacer(code.back()))
    {
        temp = code.back() + temp;
        code = code.substr(0, code.length() - 1);
    }

    if (code.back() == 'r' || code.back() == 'a' || code.back() == 'v')
    {
        code = code.substr(0, code.length() - 3);

        while (is_spacer(code.back()))
        {
            code = code.substr(0, code.length() - 1);
        }
    }
    else
    {
        code += temp + name + " =";
        return {"", ""};
    }
    

    for (idx = idx + 1; is_spacer(input_str[idx]); idx++);

    for (; !is_spacer(input_str[idx]) && input_str[idx] != ';'; idx++)
    {
        value += input_str[idx];
    }

    for (; is_spacer(input_str[idx]); idx++);

    if (input_str[idx] == ';')
    {
        idx++;
    }

    idx--;
    return {name, value};
}

std::string parse_block(const std::string &input_str, size_t &idx)
{
    std::string block = "";
    std::string indention = "";
    std::queue< std::pair< std::string, std::string > > q;

    {
        size_t i;
        for (i = idx; input_str[i] != '\0' && input_str[i] != '\n'; i++);

        if (input_str[idx] != '\0')
        {
            for (i = i + 1; input_str[i] == ' ' || input_str[i] == '\t'; i++)
            {
                indention += input_str[i];
            }
        }
    }
    

    for (idx = idx + 1; input_str[idx] != '\0'; idx++)
    {
        if (input_str[idx] == '{')
        {
            block += parse_block(input_str, idx);
        }
        else if (input_str[idx] == '=')
        {
            auto res = cut_defination(input_str, block, idx);

            if (res.first != "")
            {
                q.push(res);
            }
        }
        else
        {
            block += input_str[idx];

            if (input_str[idx] == '}')
            {
                break;
            }
        }
    }

    std::string names = "[";
    std::string values = "[";

    while (!q.empty())
    {
        names += q.front().first;
        values += q.front().second;
        q.pop();

        if (!q.empty())
        {
            names += ", ";
            values += ", ";
        }
    }
    names += "]";
    values += "]";

    if (names != "[]")
    {
        block = std::string("{") + "\n" + indention + "var " + names + " = " + values + ";" + block;
    }
    else
    {
        block = "{" + block;
    }
    

    return block;
}

std::string parse_data(const std::string &input_str)
{
    size_t idx;
    size_t len;
    std::string data = "";

    for (idx = 0, len = input_str.length(); idx < len; idx++)
    {
        if (input_str[idx] != '{')
        {
            data += input_str[idx];
        }
        else
        {
            data += parse_block(input_str, idx);
        }
    }

    return data;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Invalid usage.\n%s\n", help_message(argv[0]));
        return EXIT_FAILURE;
    }

    FILE *inputf;
    FILE *outputf;

    std::string name;
    std::string extension;
    std::string output_fname;
    std::string input_fname = argv[1];

    inputf = fopen(input_fname.c_str(), "r");
    if (!inputf)
    {
        fprintf(stderr, "Wrong input file name.\n");
        return EXIT_FAILURE;
    }

    parse_fname(input_fname, name, extension);
    output_fname = name + ".out" + extension;

    outputf = fopen(output_fname.c_str(), "w");

    std::string file_content = "";

    while (!feof(inputf))
    {
        char *temp_s = 0;
        size_t temp_n = 0;

        my_getline(&temp_s, &temp_n, inputf);

        file_content += temp_s;
        free(temp_s);
    }

    std::string result = file_content;
    result = parse_data(file_content);
    fprintf(outputf, "%s", result.c_str());

    fclose(outputf);
    fclose(inputf);

    return EXIT_SUCCESS;
}
