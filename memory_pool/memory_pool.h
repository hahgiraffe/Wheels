/*
 * @Author: haha_giraffe
 * @Date: 2019-10-13 13:44:01
 * @Description: memory_pool
 */
#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H
#include <stdlib.h>
#include <stdio.h>
typedef struct memory_pool memory_pool_t;
typedef struct Large_memory_data Large_memory_data_t;

struct memory_data{
    u_char* last;
    u_char* end;
    memory_pool_t* next;
};

struct Large_memory_data{
    Large_memory_data_t* next;
    void* alloc;
};


struct memory_pool{
    memory_data d;
    int maxsize;
    Large_memory_data*  large;  //链表
    memory_pool* current;
};

/* 这两个是操作内存池的申请内存，当内存池结束时候会自动释放 */
void* memory_palloc(memory_pool* pool, size_t size);    /* 在内存池上申请一块内存*/
void* memory_pcalloc(memory_pool* pool, size_t size);   /* 在内存池上申请一块内存并初始化为0*/
void memory_pfree(memory_pool* pool ,void* p);          /*提前释放一块大内存 */

/* 内部接口函数,分别申请小内存和大内存 */
void* memory_palloc_small(memory_pool* pool, size_t size);
void* memory_palloc_large(memory_pool* pool, size_t size);
void* memory_palloc_block(memory_pool* pool, size_t size);

/* 内存池操作 */
memory_pool* create_pool(size_t size);/*这个size不只是申请内存池大小，还包括管理结构的大小。默认16k以上 */
void destroy_pool(memory_pool* pool);


#endif