CC = g++	#rename g++/gcc operation..
GDB = -g


core: inc/data.h	inc/threadpool.h	src/threadpool.cpp	src/data.cpp	src/main.cpp
			$(CC) src/threadpool.cpp src/data.cpp src/main.cpp -o main -Iinc -lpthread -ldl \
				-Wl,--export-dynamic -std=c++0x $(GDB)

lib: inc/data.h	test.cpp
				$(CC) -c test.cpp -o test.o -fPIC -Iinc
				$(CC) -shared -o libtest.so test.o
clean:
	rm -f test.o libtest.so main
