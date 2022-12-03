/*
Функции не делают проверки на корректность данных
Ориентированны на работу с файлом
*/
#include<stdlib.h>
#include<stdio.h>
//#include<stdio.h>

int* symbolFrequency(FILE* _inputFile)
{
    _inputFile = fopen("function/text/input.txt", "r");
    if(NULL == _inputFile)
    {
        return NULL;
    }
    //printf("NO");   

    int* tabFrequency = (int*)calloc(256, sizeof(int));

    char el;
    while(fscanf(_inputFile,"%c",&el)!=-1)//Пока не конец файла
    {
        tabFrequency[el] += 1;
    }
    fclose(_inputFile); //Обязательно закрываем файл

    return tabFrequency;
};

/*
int main()
{
    FILE* file = NULL;
    int* tab = symbolFrequency(file);

    for(int i=0; i<256; i++)
    {
        if(tab[i])
        {
            printf("%d", tab[i]);
        }
    }
}
*/

