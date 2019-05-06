#include <memory>
#include <iostream>
#include <string>
using namespace std;
class Test{
private:
    string _s;
public:
    Test():_s(""){ }
    Test(string s):_s(s){ }
    ~Test(){ }
    string show() const {
        return _s;
    }
};

class Read_write{
private:
    shared_ptr<Test> global_ptr;
public:
    Read_write(const shared_ptr<Test> &ptr):global_ptr(ptr){ }
    void read(){
        shared_ptr<Test> localptr;
        localptr=global_ptr;
        cout<<localptr->show()<<" "<<localptr.use_count()<<endl;
    }
    void write(){
        shared_ptr<Test> newptr(new Test("qwe"));
        cout<<global_ptr->show()<<" "<<global_ptr.use_count();
        global_ptr=newptr;
        cout<<global_ptr->show()<<" "<<global_ptr.use_count()<<endl;

    }
};

int main(){
    //std::shared_ptr<int> ptr(new int(123));
    //std::shared_ptr<int> ptr = new int(123);不行，因为其默认构造函数explicit
    //std::shared_ptr<double> ptr2=std::make_shared<double> (10.2);
    //std::shared_ptr<double> ptr3=ptr2;
    //std::cout<<*ptr.get()<<" "<<*ptr2.get()<<std::endl;//get只是返回内部指针
    //std::cout<<ptr.use_count()<<" "<<ptr2.use_count();//返回指针个数

    // shared_ptr<Test> test_ptr=make_shared<Test>("1sda");
    // cout<<test_ptr.use_count()<<endl;
    // cout<<test_ptr->show();
    shared_ptr<Test> ptr=make_shared<Test>("asd");
    Read_write rw(ptr);
    rw.read();
    rw.write();
    cout<<ptr->show()<<" "<<ptr.use_count();

}
