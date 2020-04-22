CXX = g++
PROTOC = protoc
PROTOS_PATH = ./
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which ${GRPC_CPP_PLUGIN}`
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
           -pthread\
           -lgrpc++_reflection\
           -ldl
all : dbclient dbserver

dbclient : db.pb.o db.grpc.pb.o dbclient.o tinyjson.o
	${CXX} $^ ${LDFLAGS} -o $@

dbserver : db.pb.o db.grpc.pb.o dbserver.o tinyjson.o
	${CXX} $^ ${LDFLAGS} -o $@

.PRECIOUS: %.grpc.pb.cc
%.grpc.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

.PRECIOUS: %.pb.cc
%.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=. $<

clean:
	rm -f *.o dbclient dbserver