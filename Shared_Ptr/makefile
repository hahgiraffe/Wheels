#makefile for shared_ptr
LIB = -g -std=c++11
cc = g++
prom = main
source = main.cpp shared_ptr.cpp

${prom} : ${source}
	${cc} -o ${prom} ${source} ${LIB} 

clean :
	rm main.o shared_ptr.o