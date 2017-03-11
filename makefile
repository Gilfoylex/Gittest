CC = g++	#rename g++/gcc operation..
GDB = -g


core: inc/mesdata.h	inc/threadpool.h	src/threadpool.cpp	src/mesdata.cpp	src/main.cpp	\
		inc/tcp_server.h src/tcp_server.cpp
			$(CC) src/threadpool.cpp src/mesdata.cpp  src/tcp_server.cpp src/main.cpp -o main -Iinc -lpthread -ldl \
				-Wl,--export-dynamic -std=c++0x $(GDB)

lib: inc/mesdata.h	test.cpp
				$(CC) -c test.cpp -o test.o -fPIC -Iinc
				$(CC) -shared -o libtest.so test.o
clean:
	rm -f test.o libtest.so main
