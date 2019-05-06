#include "shared_ptr.h"

int main(){
    My_Share_Ptr<int> ptr1(new int(123));
    My_Share_Ptr<int> ptr2(ptr1);
    My_Share_Ptr<std::string> ptr3(new std::string("qwe"));
    //My_Share_Ptr<int> ptr4=new int(122);当把构造函数声明为explicit，就不能这样构造
    std::cout<<ptr1.user_count()<<std::endl;
    std::cout<<*ptr3.get();
    return 0;
}