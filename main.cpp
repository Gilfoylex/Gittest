#include "thread.h"

int main(int argc, char** argv)
{
	MultiThread A(2);
	MultiThread B(3);
	MultiThread C(4);
	A.start();
	A.join();
	B.start();
	B.join();
	C.start();
	C.join();
	return 0;
}
