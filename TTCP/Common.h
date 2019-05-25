#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <assert.h>
#include <string.h> //bzero
//首先要协议规定发送的次数和大小
//__attribute__ ((_packed__))表示该结构体不按照字节对齐
struct __attribute__ ((_packed__)) SessionMessage{
    int number;//传多少次消息
    int length;//每次消息多大
};
//数据包格式
struct Message{
    int length;
    char data[0];//char[0]不定长数组，这里的长度应该和sessionmessage.length一致
};
//写
int write_n(int sockfd,const void* buf,int length){
    int size = 0;
    while(size < length){//这个循环保证所有数据都写入文件描述符
        ssize_t ret = ::write(sockfd,static_cast<const void*>(buf)+size,length-size);
        if(ret > 0){
            //当返回ret代表已经写入的字节数，如果全都写入成功ret=length
            size += static_cast<int> (ret);
        }
        else if(ret == 0){
            break; //EOF
        }
        else {
            perror("write error");
            break;
        }
    }
    return size;
}

//读,从sockfd中读数据，存入buf
int read_n(int sockfd,void* buf,int length){
    int size = 0;
    while(size < length){//这个循环保证所有数据都从fd中读出
        ssize_t ret = ::read(sockfd,static_cast<char*>(buf)+size,length-size);
        if(ret > 0){
            //当返回ret代表已经写入的字节数，如果全都写入成功ret=length
            size += static_cast<int> (ret);
        }
        else if(ret == 0){
            break; //EOF
        }
        else {
            perror("write error");
            break;
        }
    }
    return size;
}