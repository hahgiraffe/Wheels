/*
 * @Author: haha_giraffe
 * @Date: 2020-04-20 11:14:51
 * @Description: dbclient
 */
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include "grpc++/grpc++.h"
#include "db.grpc.pb.h"

class Dbclient{
public:
    Dbclient(std::shared_ptr<grpc::Channel> ptr) : stub_(dbcontent::QueryDB::NewStub(ptr)) { }

    std::tuple<std::string, std::string, std::vector<std::string>> Db_call(const std::string& name){
        dbcontent::QueryRequest req;
        dbcontent::QueryReply rep;
        req.set_name(name);
        grpc::ClientContext context;
        grpc::Status status = stub_->DoQuery(&context, req, &rep);
        if(status.ok()){
            std::cout << "RPC OK" << std::endl;
            std::vector<std::string> hobby;
            for(int i = 0; i < rep.mess_hobby_size(); ++i){
                hobby.push_back(rep.mess_hobby(i));
            }
            return {rep.mess_age(), rep.mess_school(), hobby};
        } else {
            std::cout << "RPC FAIL, StatusCode : " << status.error_code() << 
            " StatusMessage: " << status.error_message() << 
            " StatusDetails: " << status.error_details() << std::endl;
            return {"GETAGE FAIL", "GETSCHOOL FAIL", {}};
        }
    }

    void DBQueryAll(const std::string& name){
        dbcontent::QueryRequest req;
        dbcontent::QueryReply rep;
        req.set_name(name);
        grpc::ClientContext context;
        std::unique_ptr<grpc::ClientReader<dbcontent::QueryReply>> reader(stub_->DoAllQuery(&context, req));
        while(reader->Read(&rep)){
            std::cout << "mess_age: " << rep.mess_age() <<
            " mess_school: " << rep.mess_school() << 
            " mess_name: " << rep.mess_name() << 
            " mess_hobby_size: " << rep.mess_hobby_size() << std::endl;
        }
        grpc::Status status = reader->Finish();
        if(status.ok()){
            std::cout << "RPC OK" << std::endl;
        } else {
            std::cout << "RPC FAIL" << std::endl;
        }
    }
private:
    std::unique_ptr<dbcontent::QueryDB::Stub> stub_;
};

int main(int argc, char* argv[]){
    Dbclient client(grpc::CreateChannel("localhost:8889", grpc::InsecureChannelCredentials()));
    std::cout << "-----------DoQuery----------" << std::endl;
    auto res = client.Db_call("chs");    
    std::cout << std::get<0>(res) << " " << std::get<1>(res) <<" " << std::get<2>(res).size() << std::endl;
    for(auto a : std::get<2>(res)){
        std::cout << a << std::endl;
    }
    std::cout << "-----------QueryAll----------" << std::endl;
    client.DBQueryAll("chs");
    return 0;
}