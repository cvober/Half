#include<iostream>
#include <memory>


using ubyte = unsigned char;

class Node 
{
    public:
        using pointer = std::shared_ptr<Node>;

        pointer left {nullptr};
        pointer right {nullptr};
        pointer parent {nullptr};


    public:        
        Node() = default;
        Node(ubyte _symbol, int _frequency): symbol(_symbol), frequency(_frequency) {};    
        Node(std::string& _name, int _frequency): name(_name), frequency(_frequency) {};    

    public:
        int getFrequency()const{return frequency;};
        std::string getCode()const{return codeString;};
        ubyte getSymbol()const{return symbol;};
        std::string getName()const
        {
            if(symbol == 0)
                return name;
            else
                return std::string(1, static_cast<char>(symbol));
        };

    public:
        void setFrequency(int _f){frequency =_f;};
        void setCode(std::string _code){codeString =_code;};

    public:
        bool operator<(const Node& _other)const;
        friend std::ostream& operator<<(std::ostream& _out, const Node& _this); 

    private:
        std::string name {""};

        ubyte symbol {0};
        int frequency {0};
        std::string codeString {""};
};

std::ostream& operator<<(std::ostream& _os, const Node& _node)
{
    _os << "[" << _node.getName() << "]=" << _node.frequency << std::endl;
    return _os;
};

bool Node::operator<(const Node& _other) const
{
    return frequency < _other.frequency;
};

class LowestPriority
{
    public:
        bool operator()(const Node::pointer& _left, const Node::pointer& _right) const
        {
            return _left->getFrequency() > _right->getFrequency();
        };
};





