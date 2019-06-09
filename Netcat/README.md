# Netcat
模仿实现Netcat，分为客户端和服务器端，两者的功能类似
可以同时监听连接的fd和标准输入输出
（1）第一种实现方法是 阻塞io + Thread per connection，用两个线程实现，每个线程一个循环(注意：SIGPIPE信号，TCP自连接，TCP_NODELAY，SO_REUSEADDR，读取消息不完整等问题)
（2）第二种实现方法是 非阻塞IO + 多路复用（epoll/poll/select）