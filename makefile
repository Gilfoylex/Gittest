CC = g++	#rename g++ operation..

makecorepart: data.h	data.cpp	thread.h	thread.cpp	main.cpp
				$(CC) data.cpp thread.cpp main.cpp -o main -lpthread -ldl \
				-Wl,--export-dynamic

makedynamiclib:	data.h	test.cpp
				$(CC) -c test.cpp -o test.o -fPIC
				$(CC) -shared -o libtest.so test.o

clean:
	rm test.o libtest.so main
