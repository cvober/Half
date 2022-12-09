/*
Функции не делают проверки на корректность данных
Ориентированны на работу с файлом
*/
#include<stdlib.h>
#include<stdio.h>
#include"PriorityS.h"


#define SIZE_TAB 256

typedef int error_code_t;
typedef unsigned char ubyte;


#define ERR_NOT_PTR 400
#define ERR_OPEN_FILE 401
//#include<stdio.h>

/*
Вход: Файл
Выход: Таблица с ассоциацией аски. В 0 элементе кол-во всех символов
*/

int* symbolFrequency(FILE* _inputFile)
{
    _inputFile = fopen("function/text/input.txt", "r");
    if(NULL == _inputFile)
    {
        return NULL;
    }
    //printf("NO");   

    int* tabFrequency = (int*)calloc(SIZE_TAB, sizeof(int));
    if(NULL == tabFrequency)
    {
        return NULL;
    };

    int countSymbol = 0;
    char el;

    while(fscanf(_inputFile, "%c", &el) != -1)//Пока не конец файла
    {

        if(tabFrequency[el] == 0)
        {
            countSymbol++;
        };

        tabFrequency[el] += 1;
        //if(tabFrequency[el] == 0)
    }
    tabFrequency[0] = countSymbol;
    fclose(_inputFile); //Обязательно закрываем файл

    return tabFrequency;
};

void printStage(int _percent)
{
    printf("\r%d\%", _percent);
};

/*
int* symbolPyramid(int* _tab, size_t _sizeTab)
{
    if(NULL == _tab || _sizeTab != SIZE_TAB)
    {
        return NULL;
    };

    int sizePyramid = _tab[0];

    int* tabPyramid = (int*)calloc(sizePyramid, sizeof(int));
    if(NULL == tabPyramid)
    {
        return NULL;
    };

    int buff;
    for(int i = 1; i < _sizeTab; i++)
    {
        int countSymbol = _tab[i];

        if(countSymbol)
        {
            for(int j = 0; j < sizePyramid; j++)
            {
                if(0 == tabPyramid[j])
                {
                    tabPyramid[j] = countSymbol;
                    break;
                };

                if(tabPyramid[j] < countSymbol)
                {
                    buff = tabPyramid[j];
                    tabPyramid[j] = countSymbol;
                    countSymbol = buff;
                    continue;
                };

            };
        };
    };
    
    return tabPyramid;
};
*/

Priority* symbolPyramidN(int* _tab, size_t _sizeTab)
{
    if(NULL == _tab || _sizeTab != SIZE_TAB)
    {
        return NULL;
    };

    int sizePyramid = _tab[0] + 1;

    Priority* tabPyramid = (Priority*)calloc(sizePyramid, sizeof(Priority)); //Под количество элементов
    if(NULL == tabPyramid)
    {
        return NULL;
    };

    Priority buff;
    char tmpSymbol;

    tabPyramid[0].count = _tab[0];
    tabPyramid[0].symbol = 0;


    for(int i = 1; i < _sizeTab; i++)
    {
        int countSymbol = _tab[i];
        tmpSymbol = i;

        if(countSymbol)
        {
            for(int j = 1; j < sizePyramid; j++)
            {
                if(0 == tabPyramid[j].count)
                {
                    tabPyramid[j].count = countSymbol;
                    tabPyramid[j].symbol = tmpSymbol;
                    tabPyramid[j].code = 0;

                    break;
                };

                if(tabPyramid[j].count < countSymbol)
                {
                    buff = tabPyramid[j];

                    tabPyramid[j].count = countSymbol;
                    tabPyramid[j].symbol = tmpSymbol;

                    countSymbol = buff.count;
                    tmpSymbol = buff.symbol;

                    continue;
                };

            };
        };
    };
    
    return tabPyramid;
};

error_code_t createCode(Priority* _tabPyramid )
{
    if(NULL == _tabPyramid)
    {
        return ERR_NOT_PTR;
    };

    size_t size = _tabPyramid->count;

    if(size <= 2)
    {
        if(size == 0)
        {
            return -1;
        };

        if(size == 1)
        {
            _tabPyramid->code = 0; 
            return 0;
        };

        _tabPyramid->code = 1;
        return 0;
    };

    _tabPyramid[0].code;
    _tabPyramid[1].code |= 3;

    unsigned int parentCode;
    int i = 2;
    while(i < size)
    {
        if(i<6)
            parentCode = _tabPyramid[i/2-1].code;
        else   
            parentCode = _tabPyramid[i/2].code;

            
        if(parentCode & 1)
        {
            printf("1 - %d\n", i);
            //_tabPyramid[i].code = parentCode | 1<<i/2 + 1;
            parentCode <<= 1;
            parentCode |= 1;
            parentCode &= ~(1<<1); 
            _tabPyramid[i].code = parentCode;
        }

        else
        {
            printf("0 - %d\n", i);
            //_tabPyramid[i].code = parentCode | 1<<(i/2)+1;
            parentCode <<= 1;
            parentCode |= 4;
            _tabPyramid[i].code = parentCode; 
        };
        i++;

        parentCode = _tabPyramid[i-1].code;

        if(parentCode & 1)
        {
            printf("1 - %d\n", i);
            //_tabPyramid[i].code = parentCode | 1<<i/2 + 1;
            parentCode <<= 1;
            parentCode |= 1;
            parentCode &= ~(1<<1); 
            _tabPyramid[i].code = parentCode;
        }

        else
        {
            printf("0 - %d\n", i);
            //_tabPyramid[i].code = parentCode | 1<<(i/2)+1;
            parentCode <<= 1;
            parentCode |= 4;
            _tabPyramid[i].code = parentCode; 
        };
        i++;


        /*
        parent = (i/2)-1;
        
//10001
        if(parent % 2)
        {
            _tabPyramid[i] = _tabPyramid[parent].code
        }
//01110
        else
        {

        }
*/

        /*
        if(i + 2*i < size)
        {
            _tabPyramid[i].code = i+1;
        };

        if((i + (2*i+1)) < size)
        {
            _tabPyramid->code = i+1;
        };
        */
    };

};



/////////////////////////////////////////////////////////////////////
/*
void qs(char* _array, int _first, int _last)
{
    int i = _first, j = _last, x = _array[(_first + _last) / 2];
  
    do {
        while (_array[i] < x) i++;
        while (_array[j] > x) j--;
  
        if(i <= j) {
            if (_array[i] > _array[j]) 
                swap(_array, i, j);//swap(&_array[i], &_array[j]);

            i++;
            j--;
        }
    } while (i <= j);
  
    if (i < _last)
        qs(_array, i, _last);

    if (_first < j)
        qs(_array, _first, j);
};

error_code_t swap(
        char *_array,
        size_t i,
        size_t j)
{
    if ((_array == NULL))
    {
        return ERR_NOT_PTR;
    }

    char tmp;
    tmp = _array[i];
    _array[i] = _array[j];
    _array[j] = tmp;

    return 0;
};
*/


