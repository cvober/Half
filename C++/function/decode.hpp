error_code_t readFile(
    const std::string& _pathFile
    ,std::vector<int>& _frequency
    ,std::string& _messange
    )
{
    //std::string _pathFile = _pathFile;
    //_pathFile = _pathFile + ".hff.code";
    std::ifstream file(_pathFile, std::ifstream::binary);
    if(!file)
    {
        std::cerr << "Error in [" << __PRETTY_FUNCTION__ << "]: " << strerror(errno) << std::endl;
        return ns_file::ERR_OPEN ;
    };

    ubyte count = 0;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    std::cout << int(count) << std::endl;

    int i = 0;
    while (i < count)
    {
        ubyte ch;
        file.read(reinterpret_cast<char*>(&ch), sizeof(ch));

        int f = 0;
        file.read(reinterpret_cast<char*>(&f), sizeof(f));

        _frequency[ch] = f;
        ++i;
    };

    int byteCount = 0;
    int moduls =0;

    file.read(reinterpret_cast<char*>(&byteCount), byteCount);
    file.read(reinterpret_cast<char*>(&moduls), moduls);

    i = 0;
    for(; i < byteCount; i++)
    {
        char byte;
        file.read(reinterpret_cast<char*>(&byte), sizeof(byte));

        std::bitset<__CHAR_BIT__> b(byte);

        _messange += b.to_string();
    };

    if(moduls > 0)
    {
        char byte;
        file.read(reinterpret_cast<char*>(&byte), sizeof(byte));

        std::bitset<__CHAR_BIT__> b(byte);

        _messange += b.to_string().substr(__CHAR_BIT__ - moduls, __CHAR_BIT__);
    };
    
    return 0;
};

void makeChar(
    const Node::pointer& _root, 
    std::string& _messange, 
    std::string& _text
    )
{
    Node::pointer node = _root;

    for(int i = 0; i < _messange.size(); i++)
    {
        char ch = _messange[i];

        if(ch == '0')
        {
            if(node->left != nullptr)
            {
                node = node->left;

                if(node->left == nullptr && node->right == nullptr)
                {
                    _text += node->getSymbol();
                    node = _root;
                };
            };
            continue;
        };

        if(ch == '1')
        {
            if(node->right != nullptr)
            {
                node = node->right;
                
                if(node->left == nullptr && node->right == nullptr)
                {
                    _text += node->getSymbol();
                    node = _root;
                };
            };
            continue;
        };
    };
    
};

error_code_t writeDecodeFile(std::string _pathFile, std::string _text)
{
    std::string pathResultFile = _pathFile + ".hff.decode";

    std::ofstream resultFile(pathResultFile, std::ofstream::binary);
    if(!resultFile)
    {
        std::cerr << "Error in [" << __PRETTY_FUNCTION__ << "]: " << strerror(errno) << std::endl;
        return ns_file::ERR_OPEN ;
    };

    resultFile << _text;

    return 0;
};