/*
 * @Description:  TTCP协议服务器端
 * @Author: haha_giraffe
 * @Date: 2019-05-26 03:15:57
 */
#include "Common.h"

int acceptOrDie(int port){
    int sockfd = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    assert(sockfd >= 0);
    int yes=1;
    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) != 0){
        perror("setsocckopt");
        exit(1);
    }
    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(sockfd,(struct sockaddr*)(&addr),sizeof(addr)) != 0){
        perror("bind");
        exit(1);
    }
    if(listen(sockfd,5)){
        perror("listen");
        exit(1);
    }
    struct sockaddr_in peer_addr;
    bzero(&peer_addr,sizeof(peer_addr));
    socklen_t addrlen = 0;
    int clientfd = ::accept(sockfd,(struct sockaddr*)&peer_addr,&addrlen);
    assert(clientfd >= 0);
    ::close(sockfd);
    return clientfd;

}

int main(){
    int clientfd = acceptOrDie(9876);//默认端口9876
    struct SessionMessage sessionMessage {0,0};
    //这里是读取协议中要传输几条数据，每条数据多大
    if(read_n(clientfd,&sessionMessage,sizeof(sessionMessage)) != sizeof(sessionMessage)){
        perror("read SessionMessage");
        exit(1);
    }
    sessionMessage.number = ntohl(sessionMessage.number);
    sessionMessage.length = ntohl(sessionMessage.length);
    printf("receive number :%d\n receive length :%d\n",sessionMessage.number,sessionMessage.length);
    //每个消息的长度
    int totallen = sizeof(int32_t) + sessionMessage.length;
    Message* mess =(Message*) malloc(totallen);
    assert(mess);
    //接下来接受number条数据
    for(int i=0;i<sessionMessage.number;i++){
        mess->length=0;
        //先读消息长度
        if(read_n(clientfd,&mess->length,sizeof(mess->length)) != sizeof(mess->length)){
            perror("read length");
            exit(1);
        }
        mess->length = ntohl(mess->length);
        //再度消息内容
        if(read_n(clientfd,&mess->data,mess->length) !=mess->length){
            perror("read data");
            exit(1);
        }
        int32_t ack = htonl(mess->length);//返回消息长度
        if(write_n(clientfd,&ack,sizeof(ack)) != sizeof(ack)){
            perror("write ack");
            exit(1);
        }
    }
    ::free(mess);
    ::close(clientfd);
    //这里可以测试吞吐量，每秒收发多少消息
    return 0;
}
