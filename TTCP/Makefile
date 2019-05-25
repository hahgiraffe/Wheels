#makefile for TTCP
all : client server
LIB = -g -lpthread -std=c++11
cc = g++
client = client
server = server
sourceclient = TTCPClient.cc
sourceserver = TTCPServer.cc
${client} : ${sourceclient}
	${cc} -o ${client} ${sourceclient} ${LIB} 
${server} : ${sourceserver}
	${cc} -o ${server} ${sourceserver} ${LIB} 
