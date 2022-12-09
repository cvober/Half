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
void print_bit_byte(unsigned int _vector); //Для проверки что коды корректны


int main()
{
    FILE* file = NULL;
    printf("Reading file: \n");
    /*
    int* tab = symbolFrequency(file);

    if(NULL == tab)
    {
        return ERR_NOT_PTR;
    }
    
    
    
    for(int i = 0; i < 255; i++)
    {
        if(tab[i])
        {
            printf("i - %d cnt - %u \n",i, tab[i]);
        }
    }
    
    int* tabSym = symbolPyramid(tab, 256);

    for(int i = 0; i < 7; i++)
    {
        printf("i - %d cnt - %u \n",i, tabSym[i]);
    }
    */
    int* tab = symbolFrequency(file);

    for(int i = 0; i < 255; i++)
    {
        if(tab[i])
        {
            printf("i - %d cnt - %u \n",i, tab[i]);
        }
    }
    
    Priority* tabSym = symbolPyramidN(tab, 256);
    createCode(tabSym);

    for(int i = 0; i < tabSym[0].count; i++)
    {
        printf("i - %d cnt - %d \n",i, tabSym[i].code);
        /*
        printf("%d ", i);
        print_bit_byte(tabSym[i].code);
        printf("\n");
        */
    };


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


void print_bit_byte(unsigned int _vector)
{
    
        //printf (1<<32 & _vector) ? '1' : '0';
        printf ("%c", ((1<<31 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<30 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<29 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<28 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<27 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<26 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<25 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<24 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<23 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<22 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<21 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<20 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<19 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<18 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<17 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<16 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<15 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<14 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<13 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<12 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<11 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<10 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<9 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<8 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<7 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<6 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<5 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<4 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<3 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<2 & _vector) ? '1' : '0'));
        printf ("%c", ((1<<1 & _vector) ? '1' : '0'));
        printf ("%c", ((1 & _vector) ? '1' : '0'));

        printf (" ");  
};