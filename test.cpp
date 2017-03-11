#include "mesdata.h"

void display()
{
	string value;
	string v;
	GetValue(value, "a");
	GetValue(v, "b");
	cout<<"test program value is:"<<value<<"------b:"<<v<<endl;
	string c = value + "----" + v;

	MakeResult("c:"+ c);
}

extern "C"
void test()
{
	display();
}
