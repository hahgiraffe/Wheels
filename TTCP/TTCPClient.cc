/*
 * @Description: TTCP客户端 ,
 * @Author: haha_giraffe
 * @Date: 2019-05-26 03:17:16
 */
#include "Common.h"

int main(int argc,char* argv[]){
    if(argc != 5){
        printf("usage:%s <ip> <port> <message_number> <message_length> \n",argv[0]);
        return 0;
    }
    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET,argv[1],&addr.sin_addr.s_addr);
    int sockfd = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    assert(sockfd >= 0);
    int ret = ::connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret != 0){
        perror("connect");
        ::close(sockfd);
        return 0;
    }
    printf("connected\n");
    struct timeval time1;
    gettimeofday(&time1,NULL);
    //printf("gettimeofday: tv_sec=%ld, tv_usec=%ld\n", us.tv_sec, us.tv_usec);
    struct SessionMessage sessionmessage = {0,0};
    sessionmessage.number = htonl(atoi(argv[3]));
    sessionmessage.length = htonl(atoi(argv[4]));
    //首先传输消息个数和每个消息的长度
    if(write_n(sockfd,&sessionmessage,sizeof(sessionmessage)) != sizeof(sessionmessage)){
        perror("write sessionmessage");
        exit(1);
    }
    //每个消息总长度
    const int totallen = (int)sizeof(int32_t)+atoi(argv[4]);
    Message* mess = (Message*)::malloc(totallen);
    assert(mess);
    mess->length = sessionmessage.length;
    for (int i = 0; i < atoi(argv[4]); ++i)
    {
        mess->data[i] = "0123456789ABCDEF"[i % 16];
    }
    double total_mb = 1.0 * atoi(argv[3]) * atoi(argv[4]) / 1024 / 1024;
    printf("%.3f MiB in total\n", total_mb);

    for (int i = 0; i < atoi(argv[3]); ++i)
    {
        int nw = write_n(sockfd, mess, totallen);
        assert(nw == totallen);

        int ack = 0;
        int nr = read_n(sockfd, &ack, sizeof(ack));
        assert(nr == sizeof(ack));
        ack = ntohl(ack);
        assert(ack == atoi(argv[4]));
    }

    ::free(mess);
    ::close(sockfd);

    struct timeval time2;
    gettimeofday(&time2,NULL);
    float timeuse=1000000*(time2.tv_sec-time1.tv_sec)+time2.tv_usec-time1.tv_usec;
    timeuse/=1000000;       
    //printf("used time:%f sec\n",timeuse);
    printf("%.3f seconds\n%.3f MiB/s\n", timeuse, total_mb / timeuse);
    return 0;
}