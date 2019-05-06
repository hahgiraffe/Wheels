#include "my_string.h"

My_String::My_String(const char *str){
    if(str){
        _size=strlen(str);
        content=new char[_size+1];
        strcpy(content,str);
    }else
    {
        //str=NULL
        _size=0;
        content=new char[1];
        *content='\0';
    }
    
}

My_String::My_String(const My_String& str){
    this->_size=str._size;
    // 拷贝构造函数不会之前赋值了
    // if(this->content){
    //     delete this->content;
    // }
    content=new char[this->_size];
    for(int i=0;i<this->_size;i++){
        this->content[i]=str.content[i];
    }
}

My_String My_String::operator =(const My_String& str){
    //首先要判断是否相同
    if(this==&str) return *this;
    delete [] content;
    _size=str._size;
    content=new char[_size+1];
    strcpy(content,str.content);
    return *this;
}