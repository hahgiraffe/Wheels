#makefile for MyThread
LIB = -g -Wall -lpthread -std=c++11
cc = g++
prom = threadtest
source = testthread.cc MyThread.cc MyMutex.cc

${prom} : ${source}
	${cc} -o ${prom} ${source} ${LIB}

clean :
	rm MyThread.o MyMutex.o