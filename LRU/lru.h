/*
 * @Description:  c++实现LRU（最近最少未使用算法，通常用于磁盘页面调度和缓存中）
 * LRU的实现基于hashmap+双向链表
 * @Author: haha_giraffe
 * @Date: 2019-04-10 16:00:40
 */
#ifndef LRU_H
#define LRU_H
#include <iostream>
#include <unordered_map>
#include <list>//双向链表

class Lru_Node{
public:
    int key;
    int value;
    Lru_Node(int k,int v):key(k),value(v){ }
};

class Lru{
public:
    void set(int key,int value);
    int get(int key);
    void show();

private:
    int capacity=5;
    std::unordered_map<int,std::list<Lru_Node>::iterator> m;
    std::list<Lru_Node> l;
};



#endif //LRU_H