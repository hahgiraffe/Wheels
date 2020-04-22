/*
 * @Author: haha_giraffe
 * @Date: 2020-04-20 11:14:20
 * @Description: dbserver
 */
#include <iostream>
#include <string>
#include <memory>
#include <tuple>
#include <vector>
#include <fstream>
#include "grpcpp/health_check_service_interface.h"
#include "grpcpp/ext/proto_server_reflection_plugin.h"
#include "grpc++/grpc++.h"
#include "tinyjson.h"
#include "db.grpc.pb.h"

class Dbserver final : public dbcontent::QueryDB::Service{
public:
    Dbserver(const std::string dbp) : dbpath_(dbp){ }

    grpc::Status DoQuery(grpc::ServerContext* context, const dbcontent::QueryRequest* req, dbcontent::QueryReply* rep) override{
        std::string tmpname = req->name(); 
        auto res = doquery(tmpname);
        rep->set_mess_age(std::get<0>(res).c_str());
        rep->set_mess_school(std::get<1>(res).c_str());

        int tmpsize = std::get<2>(res).size();
        for(int i = 0; i < tmpsize; ++i){
            std::string tmp = std::get<2>(res)[i];
            rep->add_mess_hobby(tmp);
        }
        return grpc::Status::OK;
    }

    grpc::Status DoAllQuery(grpc::ServerContext* context, 
                            const dbcontent::QueryRequest* req, 
                            grpc::ServerWriter<dbcontent::QueryReply>* writer){
        std::string name = req->name();
        //打开文件
        std::ifstream ifs(dbpath_);
        std::string str((std::istreambuf_iterator<char>(ifs)),std::istreambuf_iterator<char>());
        ifs.close();
        //去除空格
        int begin = 0;
        begin = str.find(" ",begin);
        while(begin != -1){
            str.replace(begin, 1, "");
            begin = str.find(" ",begin);
        }
        const char* data = str.c_str();
        //解析json
        JsonValue value;
        json_parse(&value, data);
        assert(get_type(&value) == TYPE_ARRAY);
        size_t sz = get_array_size(&value);
        for(int i = 0; i < sz; ++i){
            JsonValue* obj = get_array_value(&value, i);
            assert(get_type(obj) == TYPE_OBJECT);
            size_t objsz = get_object_size(obj);
            std::string age;
            std::string school;
            std::vector<std::string> hobby;
            std::string tmpname = std::string(get_string(get_object_value(obj, 0)));
            if(tmpname == name){
                continue;
            }
            for(int j = 1; j < objsz; ++j){
                const char* key = get_object_key(obj, j);
                JsonValue* value = get_object_value(obj, j);
                if(strcmp(key, "age") == 0){
                    const char* val = get_string(value);
                    age = std::string((char*)val);
                } else if(strcmp(key, "school") == 0){
                    const char* val = get_string(value);
                    school = std::string((char*)val);
                } else {
                    assert(get_type(value) == TYPE_ARRAY);
                    size_t arrsize = get_array_size(value);
                    for(size_t i = 0; i < arrsize; ++i){
                        hobby.push_back(std::string(get_string(get_array_value(value, i))));
                    }
                }
            }
            dbcontent::QueryReply rep;
            rep.set_mess_age(age);
            rep.set_mess_school(school);
            rep.set_mess_name(tmpname);
            for(int i = 0; i < hobby.size(); ++i){
                rep.add_mess_hobby(hobby[i]);
            }
            writer->Write(rep);
        }
        return grpc::Status::OK;
    }

private:
    std::tuple<std::string, std::string, std::vector<std::string>> doquery(const std::string& name) {
        //在这解析json，并返回值
        std::ifstream ifs(dbpath_);
        std::string str((std::istreambuf_iterator<char>(ifs)),std::istreambuf_iterator<char>());
        ifs.close();
        int begin = 0;
        begin = str.find(" ",begin);
        while(begin != -1){
            str.replace(begin, 1, "");
            begin = str.find(" ",begin);
        }
        const char* data = str.c_str();
        std::string age;
        std::string school;
        std::vector<std::string> hobby;
        JsonValue value;
        json_parse(&value, data);
        assert(get_type(&value) == TYPE_ARRAY);
        size_t sz = get_array_size(&value);
        for(int i = 0; i < sz; ++i){
            JsonValue* obj = get_array_value(&value, i);
            assert(get_type(obj) == TYPE_OBJECT);
            size_t objsz = get_object_size(obj);
            if(std::string(get_string(get_object_value(obj, 0))) != name){
                continue;
            }
            for(int j = 1; j < objsz; ++j){
                const char* key = get_object_key(obj, j);
                JsonValue* value = get_object_value(obj, j);
                if(strcmp(key, "age") == 0){
                    const char* val = get_string(value);
                    age = std::string((char*)val);
                } else if(strcmp(key, "school") == 0){
                    const char* val = get_string(value);
                    school = std::string((char*)val);
                } else {
                    assert(get_type(value) == TYPE_ARRAY);
                    size_t arrsize = get_array_size(value);
                    for(size_t i = 0; i < arrsize; ++i){
                        hobby.push_back(std::string(get_string(get_array_value(value, i))));
                    }
                }
            }
        }
        return std::make_tuple(age, school, hobby);
    }


private:
    std::string dbpath_;
};

void runserver(const std::string& addr){
    Dbserver server("./db.json");
    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    grpc::ServerBuilder builder;
    builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder.RegisterService(&server);
    std::unique_ptr<grpc::Server> ptr(builder.BuildAndStart());
    std::cout << "[Start Server] at port: " << addr << std::endl;
    ptr->Wait();
}

int main(){
    std::string addr = "0.0.0.0:8889";
    runserver(addr);
    return 0;
}
