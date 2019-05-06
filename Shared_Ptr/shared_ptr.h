/*
 * @Description:  share_ptr的实现，注意不能用一个生指针给智能指针初始化（所以构造函数要声明为显式）
 * @Author: haha_giraffe
 * @Date: 2019-04-11 19:55:17
 */
#ifndef _SHARED_PTR_H
#define _SHARED_PTR_H
#include <iostream>
#include <string>
template<typename T>
class My_Share_Ptr{
public:
    My_Share_Ptr():a(NULL),num(new int(0)){ }
    explicit My_Share_Ptr(T *ptr):a(ptr),num(new int(1)){ }
    My_Share_Ptr(const My_Share_Ptr& ptr):a(ptr.a),num(ptr.num)
    {
        (*num)++;//引用计数+1
    }
    My_Share_Ptr operator =(const My_Share_Ptr& ptr);
    ~My_Share_Ptr(){
        if(a && (*num)--){
            delete a;
            delete num;
        }
    }
public:
    T& operator*();

    T* operator->();

    inline T* get() const {
        return a;
    }
    inline int user_count() const{
        return *num;
    }
private:
    T *a;//内部指针
    int* num;//引用计数,注意这里一定要指针
};


#endif