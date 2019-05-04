#include "lru.h"
//进入链表或者更新
void Lru::set(int key,int value){
    if(m.find(key)==m.end()){
        if(l.size()==capacity){
            m.erase(l.back().key);
            l.pop_back();
        }
        l.push_front(Lru_Node(key,value));
        m[key]=l.begin();
    }else{
        m[key]->value=value;
        l.splice(l.begin(),l,m[key]);
        m[key]=l.begin();
    }
}
//退出链表
int Lru::get(int key){
    if(m.find(key)==m.end()){
        //在缓存中没有找到对应的页面，缺页中断
        return -1;
    }
    else{
        //把key对应的节点移动到list的begin()
        l.splice(l.begin(),l,m[key]);//把m[key]迭代器所对应的位置移动到l.begin()后面（也就是整个链表最前面）
        m[key]=l.begin();
        return m[key]->value;
    }
}

void Lru::show(){
    for(auto a:l){
        std::cout<<a.key<<" ";
    }
}