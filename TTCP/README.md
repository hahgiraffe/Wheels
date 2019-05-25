# TTCP
TTCP协议：主要是用来测试通信带宽，是一个停等协议
可以在两台主机上运行，也可以在同一台机器上测试TCP通信带宽
其过程：
（1）client向server发送协议字段，说明发送消息的次数number和每次消息的字节数量length
（2）server向client回复收到的字节数
（3）client发送number次消息，server回复收到的字节数，当client收到消息后再接着发送下一条消息（停等）