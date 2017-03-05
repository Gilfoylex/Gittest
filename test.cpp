#include "data.h"

void display()
{
	int value;
	GetValue(value);
	cout<<"test program value is:"<<value<<endl;
}

extern "C"
void test()
{
	display();
}
