#include "lru.h"
int main(){
    Lru l;
    l.set(1,11);
    l.set(2,12);
    l.set(3,13);
    std::cout<<l.get(3)<<std::endl;
    l.show();
    return 0; 
}