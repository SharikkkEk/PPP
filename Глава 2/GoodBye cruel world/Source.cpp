import std;
#include <stdio.h>

int main()
{
    printf_s("Goodby,"  // Уберём кавычки - будет ошибка newline в константе, потому что строка "Goodbye" - константа(что логично, это ж как единица), а следующая строка как бы пытается её изменить 
        "cruel world"); 
}