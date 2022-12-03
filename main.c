/*
Входные данные: Файл в формате txt с текстом на русском или английском языке.
Реализовать код Хаффмана, опираясь на алгоритм приведенный по ссылке выше.
Программа должна уметь выполнять КОДИРОВАНИЕ и ДЕКОДИРОВАНИЕ – т.е. работать в
двух режимах.
После декодирования файл должен совпадать с исходным файлом.
Код должен быть «чистым».
*/

#include<stdlib.h>
#include<stdio.h>

#include"./function/compess.h"

typedef int error_code_t;

#define ERR_NOT_PTR 400
#define ERR_OPEN_FILE 401

int* createArrayInt(size_t _size)
{
    /*
    if(0 >= size)
    {
        return NULL;
    };
    */

    int* array = (int*)calloc(_size ,sizeof(int));
    return array;

};

error_code_t getFile(FILE* _inputFile);
error_code_t correctDateForProgramm();

int main()
{
    FILE* file = NULL;
    int* tab = symbolFrequency(file);

    if(NULL == tab)
    {
        return ERR_NOT_PTR;
    }
       
    for(int i=0; i<255; i++)
    {
        if(tab[i])
        {
            printf("i - %d cnt - %d \n",i, tab[i]);
        }
    }

    return 0;

};

error_code_t getFile(FILE* _inputFile)
{
    _inputFile = fopen("file1.txt", "w");
    if(NULL == _inputFile)
    {
        return ERR_OPEN_FILE;
    };


};

error_code_t correctDateForProgramm()
{

}

