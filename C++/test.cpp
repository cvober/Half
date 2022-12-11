#include<iostream>
#include<vector>


namespace file_ns
{
    enum eFileError
    {
        UNKNOWN = -1
        ,NO = 0
        ,OPEN = 1
        ,CLOSE = 2
    };
};

void lessonOne()
{
    using namespace std;

    //for по диапазону, создан для вектора или массивов размеры которого известны на этапе компиляции
    int array[5];
    for(auto i : array)
    {
        cout << i << ",";
    };
    cout << endl;

    //vector
    vector<int> vi;
    vi.push_back(15);
    vi.push_back(1);
    for(auto i : vi)
    {
        cout << hex << i << ",";
    };
    cout << endl << vi.size() << endl;

    const int TEST_OS = 1;
    //Только на этапе компиляции
    constexpr int RESULT_CODE = 15*TEST_OS;
    cout << dec << RESULT_CODE;

    //тип auto
    auto type = vi;

    for(int i; cin >> i;)
    {
        type.push_back(i);
    };

    for(auto i : type)
    {
        cout << i << ",";
    };
};


int main()
{
    lessonOne();

};