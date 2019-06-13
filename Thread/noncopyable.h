#pragma once

class noncopyable{
public:
    noncopyable() = default;
    ~noncopyable() = default;
private:
    noncopyable operator = (const noncopyable&) = delete;
    noncopyable(const noncopyable&) = delete;
};

// class testnon : noncopyable{
// public:
//     testnon(int a):a_(a){ }
//     ~testnon(){ }
//     testnon(const testnon& t){
//         this->a_ = t.a_;
//     }
//     testnon operator = (const testnon& t){
//         if(this == &t){ //只能这样写
//             return *this;
//         }
//         this->a_ = t.a_;
//     }
// private:
//     int a_;
// };

// int main(){
//     testnon t(3);
//     testnon t1(t);
//     t = t1;
// }