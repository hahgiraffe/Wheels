/*
 * @Author: haha_giraffe
 * @Date: 2019-10-13 14:54:40
 * @Description: file content
 */
#include "memory_pool.h"
#include <vector>
void test_mem_pool(){
    int num = 3;
    memory_pool* pool_ptr = create_pool(1024);
    std::vector<int*> vec;
    for(int i=0;i<1000;++i){
        int* intptr =(int*)memory_palloc(pool_ptr,sizeof(int));
        intptr = &num;
        vec.push_back(intptr);        
    }
    // for(auto a : vec){
    //     printf("%d ",*a);
    // }
    destroy_pool(pool_ptr);
}

int main(int agrc,char* argv[]){
    test_mem_pool();
    return 0;
}