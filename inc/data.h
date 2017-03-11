#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <string>
using namespace std;

class Data{

public:
    Data();
    void SetValue(int a);
    void GetValue(int &a);

private:
    int value;
	int client_accept_fd;
};

void GetValue(int &a);
//static Data d;

#endif // BASE_H
