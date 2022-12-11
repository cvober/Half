#include"./function/classNode.hpp"

#include <iostream>
#include <fstream>

#include <cstring>
#include <vector>
#include <queue>

using error_code_t = int;
using queueNodePointer = std::priority_queue<Node::pointer , std::vector<Node::pointer>, LowestPriority>;


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

error_code_t getFrequency(std::vector<int>& _frequency, std::string _pathFile)
{
    int fileSize = getSizeFile(_pathFile);
    if (fileSize < 0)
    {
        std::cerr << "Error in [" << __PRETTY_FUNCTION__ << "]:" << strerror(errno) << std::endl;
        return ns_file::FILE_CLEAR;
    };

    std::ifstream file(_pathFile, std::ifstream::binary);
    if(!file)
    {
        std::cerr << "Error in [" << __PRETTY_FUNCTION__ << "]: " << strerror(errno) << std::endl;
        return ns_file::ERR_OPEN;
    };

    int i = 0;
    while(true)
    {        
        char ch;
        file.read(&ch, 1);

        //Баг с последним символом
        if(file.eof())
        {
            break;
        };

        _frequency[static_cast<unsigned char>(ch)]++;

        int var = (i+ fileSize * 100.0) / fileSize;
        std::cout << "\r" << var << "%" << std::flush;
        ++i;
    };
    return 0;
};

void makeCode(Node::pointer& _node, std::string _str, std::vector<std::string>& _codes)
{

    if(_node->left != nullptr)
    {
        makeCode(_node->left, _str + '0', _codes);
    };

    if(_node->right != nullptr)
    {
        makeCode(_node->right, _str + '1', _codes);
    };

    if(_node->right == nullptr && _node->left == nullptr)
    {
        _codes[_node->getSymbol()] = _str;
        std::cout << "char- " << _node->getName() << " frequ- " << _node->getFrequency() << " code- " << _codes[_node->getSymbol()] << std::endl;
        _node->setCode(_str);
    };
};

void filingQueueFrequency(queueNodePointer& _queue, std::vector<int> _frequency)
{
    for(int i = 0; i < _frequency.size(); i++)
    {
        if(_frequency[i])
        {   
            Node::pointer node = std::make_shared<Node>(i, _frequency[i]);
            _queue.push(node);
        };
    };
};

void buildTree(queueNodePointer& _queue)
{
    while (_queue.size() > 1)
    {
        Node::pointer x = _queue.top();
        _queue.pop();

        Node::pointer y = _queue.top();
        _queue.pop();

        std::string name = x->getName() + y->getName();
        Node::pointer z = std::make_shared<Node>(name, x->getFrequency() + y->getFrequency());
        z->left = x;
        z->right = y;

        x->parent = z;
        y->parent = z;

        _queue.push(z);
    };
};

std::string getMessageCode(const std::string& _pathFile, const std::vector<std::string>& _codes)
{
    std::string msg {""};

    std::ifstream file(_pathFile, std::ifstream::binary);
    if(!file)
    {
        std::cerr << "Error in [" << __PRETTY_FUNCTION__ << "]: " << strerror(errno) << std::endl;
        return msg;
    };

    while(true)
    {        
        char ch;
        file.read(&ch, 1);

        //Баг с последним символом
        if(file.eof())
        {
            break;
        };

        msg += _codes[static_cast<ubyte>(ch)];
    };

    return msg;



};

int main()
{
    using namespace std;

    string pathFile = "./text/input.txt";
    string outFile = "./text/result.txt";

    /*
    Открытие файла для заполнения частот
    */

    vector<int> frequency(255, 0); 
    
    cout << "READING FILE" << endl;
    getFrequency(frequency, pathFile);
    cout << endl;

    /*
    Создаем очередь приоритетов
    */

    queueNodePointer queue;
    filingQueueFrequency(queue, frequency);

/*
    while(queue.size() > 0)
    {
        cout << (*queue.top());
        queue.pop();

    };

    //return 0;
*/


    /*
    Создаем дерево
    */

    buildTree(queue);
    
    /*
    auto _queue = queue;

    Node::pointer x = _queue.top();
        _queue.pop();

        Node::pointer y = _queue.top();
        _queue.pop();

        std::string name = x->getName() + y->getName();
        Node::pointer z = std::make_shared<Node>(name, x->getFrequency() + y->getFrequency());
        z->left = x;
        z->right = y;

        x->parent = z;
        y->parent = z;

        _queue.push(z);

     x = _queue.top();
        _queue.pop();

        y = _queue.top();
        _queue.pop();

        name = x->getName() + y->getName();
        z = std::make_shared<Node>(name, x->getFrequency() + y->getFrequency());
        z->left = x;
        z->right = y;

        x->parent = z;
        y->parent = z;

        _queue.push(z);

    while(queue.size() > 0)
    {
        cout << (*queue.top());
        queue.pop();
    };
*/
    //return 0;
    /*
    Создаем коды
    */
    vector<string> codes(255, "");
    Node::pointer root = queue.top();
    makeCode(root, "", codes);

    return 0;
    for(auto i : codes)
    {
        if(!i.empty())
        cout << i << " ";
    };

    return 0;
    string messageCode = getMessageCode(pathFile, codes);
    cout << messageCode << endl;
};


///////////////////////////////////////////////////////////////////////////////
/*
    cout << "-------------------------------------------\n";

    cout << " Enter path to file:";
    cin >> pathFile;        
   
    cout << " Enter result to file(You want to save next to the file [Y/n]):";
    string answer;
    cin >> answer;

    if(answer == "Y" || answer == "y" || answer == "Yes" || answer == "yes")
    {
        outFile = pathFile;
        string tmp = outFile;
        
        while(tmp != "/" || tmp != "\\" || !outFile.empty())
        {
            tmp = outFile.back();
            cout << tmp;
            outFile.pop_back();
        };

        outFile += "result.txt"; 
        //cout << outFile;
    }

    else
        cin >> outFile;

    cout << outFile;

    return 0;
   
    cout << "-------------------------------------------\n";
*/










