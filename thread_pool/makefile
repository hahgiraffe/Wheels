#makefile for thread_pool
#g++ -o main main.cpp thread_pool.cpp -g -std=c++11
LIB = -g -lpthread -std=c++11
cc = g++
prom = main
source = main.cpp thread_pool.cpp

${prom} : ${source}
	${cc} -o ${prom} ${source} ${LIB} 

clean :
	rm main.o thread_pool.o