#include "shared_ptr.h"

template<typename T>
My_Share_Ptr<T> My_Share_Ptr<T>::operator =(const My_Share_Ptr<T>& ptr){
    if(this==&ptr){
        return *this;
    }
    *num--;
    if(*num==0){
        delete num;
        delete a;
    }
    num=ptr.num;
    *num++;
    a=ptr->a;
    return *this;
}

template<typename T>
T& My_Share_Ptr<T>::operator *(){
    if(num==0){
        return (T*) 0;
    }
    return *a;
}

template<typename T>
T* My_Share_Ptr<T>::operator->(){
    if(num==0){
        return 0;
    }
    return a;
}