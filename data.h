#ifndef DATA_H
#define DATA_H
#include <iostream>
using namespace std;

class Data{

public:
    Data();
    void setValue(int a);
    void getValue(int &a);

private:
    int value;
};

void getValue(int &a);
static Data d;

#endif // BASE_H
