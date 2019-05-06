#makefile for Mystring
#g++ -o main main.cpp my_string.cpp -g -std=c++11
LIB = -g -std=c++11
cc = g++
prom = main
source = main.cpp my_string.cpp

${prom} : ${source}
	${cc} -o ${prom} ${source} ${LIB} 

clean :
	rm main.o my_string.o