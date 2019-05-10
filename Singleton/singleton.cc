/*
 * @Description: 系统保证这个类只能有一个实例,单线程版本 -> 多线程加锁版本 -> 多线程双检查锁（为了防止reorder问题）的实现
 * @Author: haha_giraffe
 * @Date: 2019-05-09 22:11:43
 */
#include <atomic>
#include <mutex>
using namespace std;

class Singleton{
private:
    Singleton();
    ~Singleton();
    Singleton(const Singleton&);
    Singleton& operator =(const Singleton&);
public:
    static Singleton* ptr;
    static Singleton* getinstance();
};

Singleton* Singleton::ptr = nullptr;

//单线程版本，（还可以返回引用，而不是指针）
Singleton* Singleton::getinstance(){
    if(ptr == nullptr){
        ptr = new Singleton();
    }
    return ptr;
}

//多线程加锁版本，没有问题，只是加锁的开销太大，因为有时候只是读
Singleton* Singleton::getinstance(){
    Lock_guard lock;
    if(ptr == nullptr){
        ptr = new Singleton();
    }
    return ptr;
}

//双检查锁的机制，逻辑没有问题，第一层if是为了提高性能，增加锁粒度，第二层if是保证只有一个实例，
//但是这个会出现reorder的问题（原来new的步骤是先申请空间、再调用构造函数、最后赋值，但是编译器有可能改变三者顺序，变成先申请空间、赋值ptr，最后调用构造函数
//这样在多线程的环境下，就有可能出现，某一个线程得到的指针已经有空间，不为nullptr，但是没有初始化，就会造成很大的麻烦
Singleton* Singleton::getinstance(){
    if(ptr == nullptr){
        Lock_guard lock;
        if(ptr == nullptr){
            ptr = new Singleton();
        }
    }
    return ptr;
}


//这个版本是消除reorder问题的，利用atomic，但是有点复杂
std::atomic<Singleton*> Singleton::ptr;
std::mutex Singleton::m_mutex;

Singleton* Singleton::getInstance() {
    Singleton* tmp = ptr.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);
    if (tmp == nullptr) {
        std::lock_guard<std::mutex> lock(m_mutex);
        tmp = ptr.load(std::memory_order_relaxed);
        if (tmp == nullptr) {
            tmp = new Singleton;
            std::atomic_thread_fence(std::memory_order_release);
            ptr.store(tmp, std::memory_order_relaxed);
        }
    }
    return tmp;
}




//最后一个模板+pthread_once_t可以保证多线程中只有一个线程执行
template<typename T>  
class Singleton : boost::noncopyable  
{
    public:
        static T& instance()
        {
            pthread_once(&ponce_, &Singleton::init);
            return *value_;
        }
        static void init()
        {
            value_ = new T();
        }
    private:
        static pthread_once_t ponce_;
        static T* value_;
};
template<typename T>  
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;
     
template<typename T>  
T* Singleton<T>::value_ = NULL;  


int main(){
    Singleton* s = Singlenton::getinstance();
}