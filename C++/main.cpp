#include"./function/classNode.hpp"

#include <iostream>
#include <fstream>

#include <cstring>
#include <vector>
#include <queue>

using error_code_t = int;

namespace ns_file
{
    enum eFileError : unsigned char
    {
        ERR_UNKNOWN = 1
        ,NO = 0
        ,ERR_OPEN = 2
        ,ERR_CLOSE = 3
        ,FILE_CLEAR = 255
    };
};

std::ifstream::pos_type getSizeFile(const std::string& _file)
{
    std::ifstream file(_file, std::ifstream::ate);
    return file.tellg();
};

void getFrequency(
    std::vector<int>& _frequency
    ,const int _fileSize
    ,std::ifstream& _file
    )
{
    using namespace std;

    int i = 0;
    while(true)
    {        
        char ch;
        _file.read(&ch, 1);

        //Баг с последним символом
        if(_file.eof())
        {
            break;
        };

        _frequency[static_cast<unsigned char>(ch)]++;

        int var = (i+_fileSize * 100.0) / _fileSize;
        cout << "\r" << var << "%" << std::flush;
        ++i;
    };

    cout << endl;
};




int main()
{
    using namespace std;

    std::string pathFile = "./text/input.txt";

    std::cout << "-------------------------------------------\n";
    std::cout << "           Enter path to file:             \n";
    //std::cin >> pathFile;        
    std::cout << "-------------------------------------------\n";

    int fileSize = getSizeFile(pathFile);
    if (fileSize < 0)
    {
        cerr << "Error in [" << __PRETTY_FUNCTION__ << "]:" << strerror(errno) << endl;
        return ns_file::FILE_CLEAR;
    };

    /*
    Open file and заполнение
    */

    std::ifstream file(pathFile, std::ifstream::binary);
    if(!file)
    {
        cerr << "Error in [" << __PRETTY_FUNCTION__ << "]: " << strerror(errno) << std::endl;
        return ns_file::ERR_OPEN;
    };

    vector<int> frequency(255, 0); 
    cout << "READING FILE" << endl;

    getFrequency(frequency, fileSize, file);

    /*
    Создаем очередь приоритетов
    */

    priority_queue<Node, vector<Node>, LowestPriority> queue;

    for(int i = 0; i < frequency.size(); i++)
    {
        if(frequency[i])
        {   
            Node node(i, frequency[i]);
            queue.push(node);
        };
    };





/*
    for(int i = 0; i < frequency.size(); i++)
    {
        if(frequency[i] != 0)
        cout << i << " " << endl;
    };
*/



};


///////////////////////////////////////////////////////////////////////////////











