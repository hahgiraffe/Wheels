#makefile for lru
#g++ -o main main.cpp lru.cpp -g -std=c++11
LIB = -g -std=c++11
cc = g++
prom = main
source = main.cpp lru.cpp

${prom} : ${source}
	${cc} -o ${prom} ${source} ${LIB} 

clean :
	rm main.o lru.o