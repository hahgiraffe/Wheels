/*
 * @Description: 简单的String类实现 
 * @Author: haha_giraffe
 * @Date: 2019-04-10 13:07:31
 */
#ifndef MY_STRING_H
#define MY_STRING_H
#include <iostream>
#include <string.h>
class My_String
{
public:
    My_String():_size(0),content(nullptr){ }
    My_String(const char *str=NULL);//构造函数
    ~My_String(){
        if(content){
            delete content;
        }
    }
    inline int getsize() const{
        return _size;
    }
    inline char* c_str() const{
        return content;
    }
    My_String(const My_String&);
    My_String operator =(const My_String&);
    inline void show() const{
        std::cout<<content<<std::endl;
    }
private:
    int _size;
    char *content;
};

#endif //MY_STRING_H