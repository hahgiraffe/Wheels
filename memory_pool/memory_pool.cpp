/*
 * @Author: haha_giraffe
 * @Date: 2019-10-13 13:44:11
 * @Description: memory_pool
 */
#include <string.h>
#include "memory_pool.h"
#define DEFAULT_POOL_SIZE 16

void* memory_palloc_small(memory_pool* pool, size_t size){
    memory_pool* p = pool->current;
    u_char* m;

    do{
        m=p->d.last;
        if( (p->d.end - m) >= size){
            p->d.last = m + size;
            return m;
        }
        p = p->d.next;
    }while(p);

    return memory_palloc_block(pool,size);
}

void* memory_palloc_block(memory_pool* pool, size_t size){
    size_t psize = pool->d.end - (u_char*)pool;
    void* m;
    int err = posix_memalign(&m,DEFAULT_POOL_SIZE,psize);
    if(m == NULL){
        printf("block error\n");
        return NULL;
    }
    memory_pool* newnode = (memory_pool*)m;
    newnode->d.end = (u_char*) m+psize;
    newnode->d.next = NULL;
    m =(u_char*)m+ sizeof(memory_pool);
    newnode->d.last =(u_char*) m+size;

    memory_pool* p;
    for(p = pool->current ; p->d.next;p = p->d.next){}
    p->d.next = newnode;
    return m;
}

void* memory_palloc_large(memory_pool* pool, size_t size){
    void* p =malloc(size);
    Large_memory_data* l;
    if(p == NULL){
        return NULL;
    }
    for(l = pool->large;l;l = l->next){
        if(l->alloc == NULL){
            l->alloc = p;
            return p;
        }
    }

    l =(Large_memory_data*)memory_palloc_small(pool,sizeof(Large_memory_data));
    if(l == NULL){
        printf("error on memory_palloc_large");
        return NULL;
    }
    /* 插入单向链表最前面 */
    l->alloc = p;
    l->next = pool->large;
    pool->large = l;
    return p;
}


void* memory_palloc(memory_pool* pool, size_t size){
    if(size <= pool->maxsize){
        return memory_palloc_small(pool,size);
    }
    return memory_palloc_large(pool,size);
}

void* memory_pcalloc(memory_pool* pool, size_t size){
    memory_pool* p ;
    p =(memory_pool*)memory_palloc(pool,size);
    memset(p,0,size);
    return p;
}

void memory_pfree(memory_pool* pool, void* p){
    Large_memory_data* l;
    for(l = pool->large;l;l = l->next){
        if(p == l->alloc){
            free(l->alloc);
            l->alloc = NULL;
        }
    }    
}


memory_pool* create_pool(size_t size){
    memory_pool* pool;
    void* p;
    int err = posix_memalign(&p,DEFAULT_POOL_SIZE,size);   /*分配内存 */
    if(err){
        printf("error memalign\n");
        return NULL;
    }
    pool = (memory_pool*)p;
    pool->d.last = (u_char*)pool + sizeof(memory_pool);
    pool->d.end  = (u_char*)pool + size;
    pool->d.next = NULL;
    
    size = size - sizeof(memory_pool);

    pool->maxsize = size;
    pool->large = NULL;
    pool->current = pool;

    return pool;
}

void destroy_pool(memory_pool* pool){
    memory_pool *p , *n ;
    Large_memory_data* large;
    /*只释放大块内存中的内存，并不释放节点 */
    for(large = pool->large; large;large = large->next){
        free(large->alloc);
    }

    /*释放pool */
    for(p = pool,n = pool->d.next;;p = n , n = n->d.next){
        free(p);
        if(n == NULL){
            break;
        }
    }

}

