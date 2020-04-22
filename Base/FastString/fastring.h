/*
 * @Author: haha_giraffe
 * @Date: 2020-04-14 20:52:06
 * @Description: fastring是一种高效cpp字符串的实现方式，基本上可以替代std::string 
 */

#include <string>
#include <ostream>
#include <assert.h>
#include <string.h>
#include <atomic>

class fastring{
public:
static const size_t npos = (size_t)-1;
    fastring();
    explicit fastring(size_t cap);
    explicit fastring(const char* s);
    fastring(const void* s, size_t n);
    fastring(const std::string& s);

    ~fastring();
    fastring(const fastring& s);
    fastring& operator = (const fastring& s);

    fastring& operator = (const std::string& s);
    fastring& operator = (const char* s);

    const char* data() const {
        return _p ? _p->s : (const char*)&_p;
    }

    bool empty() const{
        return this->size() == 0;
    }

    size_t size() const{
        return _p ? _p->size : 0;
    }

    size_t capacity() const{
        return _p ? _p->cap : 0;
    }

    //c_str()和data()的区别，c_str()返回的字符串后面有'\0'，data()没有，std::string也有着两个函数
    const char* c_str() const{
        if(!_p) return (const char*)&_p;
        ((fastring*)this)->_Reserve(_p->size + 1);
        if(_p->s[this->size()] != '\0'){
            _p->s[this->size()] = '\0';
        }
        return _p->s;
    }

    void clear(){
        if(_p) _p->size = 0;
    }

    void reserve(size_t n){
        _p ? this->_Reserve(n) : this->_Init(0);
    }

    void resize(size_t n){
        this->reserve(n);
        _p->size = n;
    }

    char& back() const{
        return _p->s[this->size()];
    }

    char& front() const{
        return _p->s[0];
    }

    char& operator [](size_t i) const{
        return _p->s[i];
    }

    fastring& append(const void* p, size_t n){
        return this->_Append_Safe(p, n);
    }
    fastring& append(const fastring& fs){
        return this->_Append_Safe(fs._p->s, fs.size());
    }
    fastring& append(const std::string& s){
        return this->_Append_Safe(s.data(), s.size());
    }
    fastring& append(const char* s){
        return this->_Append_Safe(s, strlen(s));
    }
    fastring& append(char c, size_t n){
        if(_p){
            this->_Ensure(n);
        } else{
            this->_Ensure(n + 1);
        }
        memset(_p->s + _p->size, c, n);
        _p->size += n;
        return *this;
    }
    fastring& append(char c){
        if(_p){
            this->_Ensure(1);
        } else{
            this->_Init(16);
        }
        _p->s[_p->size++] = c;
        return *this;
    }

    fastring& operator += (const fastring& fs){
        return this->append(fs);
    }
    fastring& operator += (const std::string& s){
        return this->append(s);
    }
    fastring& operator += (const char* s){
        return this->append(s);
    }
    fastring& operator += (char c){
        return this->append(c);
    }

    fastring clone() const{
        return _p ? fastring(_p->s, _p->size) : fastring();
    }

    fastring substr(size_t pos) const;
    fastring substr(size_t pos, size_t len) const;

    size_t find(char c) const;
    size_t find(char c, size_t pos) const;
    size_t find(const char* s) const;
    size_t find(const char* s, size_t pos) const;

    size_t find_first_of(const char* s) const;
    size_t find_first_not_of(const char* s) const;
    size_t find_first_not_of(char c) const;

    size_t find_last_of(const char* s) const;
    size_t find_last_not_of(const char* s) const;
    size_t find_last_not_of(char c) const;

    void replace(const char* sub, const char* to, size_t maxreplace = 0);

    void strip(const char* s = " \t\r\n", char d = 'b');
    void strip(char c, char d = 'b');

    bool start_with(char c) const;
    bool start_with(const char* s, size_t n) const;
    bool start_with(const char* s) const;
    bool start_with(const fastring& s) const;
    bool start_with(const std::string& s) const;

    bool end_with(char c) const;
    bool end_with(const char* s, size_t n) const;
    bool end_with(const char* s) const;
    bool end_with(const fastring& s) const;
    bool end_with(const std::string& s) const;

    fastring& toupper();
    fastring& tolower();
    fastring upper() const;
    fastring lower() const;
    
    void swap(fastring& s);
    void swap(fastring&& s);

private:

    void _Init(size_t cap, size_t n = 0){
        _p = (_Mem*) malloc(sizeof(_Mem));
        _p->cap = cap;
        _p->size = n;
        _p->refn = 1;
        _p->s = (char*) malloc(sizeof(_p->cap));
    }

    bool _Inside(const void* p){
        return _p->s <= p && p < _p->s + _p->size;
    }

    void _Ensure(size_t n){
        if(n + _p->size > _p->cap){
            this->_Reserve(n + this->size() + 1);
        }
    }
    
    size_t _Ref(){
        return __atomic_add_fetch(&_p->refn, 1, __ATOMIC_SEQ_CST);
    }

    size_t _UnRef(){
        return __atomic_sub_fetch(&_p->refn, 1, __ATOMIC_SEQ_CST);
    }
    
    fastring& _Append_Safe(const void* s, size_t n){
        if(!_p){
            this->_Init(n+1, n);
            memcpy(_p->s + _p->size, s, n);
            return *this;
        }
        if(!_Inside(s)){
            this->_Ensure(n);
            strcat(_p->s, (const char*)s);
        } else {
            size_t pos = (const char*)s - _p->s;
            this->_Ensure(n);
            strcat(_p->s, _p->s + pos);
        }
        _p->size += n;
        return *this;
    }

    void _Reserve(size_t n){
        if(_p->cap >= n) return;
        _p->s = (char*) realloc(_p->s, n);
        assert(_p->s);
        _p->cap = n;
    }

private:
    //为什么要成员变量放在一个内部类中？首先这样sizeof(fastring)更小，其次当复制的时候引用计数要一起变化
    struct _Mem{
        size_t cap;     //容量
        size_t size;    //长度
        size_t refn;    //引用计数
        char* s;        //字符串
    };
    _Mem* _p;
};

inline fastring operator + (const fastring& lhs, char rhs){
    return fastring(lhs.size() + 2).append(lhs).append(rhs);
}
inline fastring operator + (char lhs, const fastring& rhs){
    return fastring(rhs.size() + 2).append(lhs).append(rhs);
}
inline fastring operator + (const fastring& lhs, const fastring& rhs){
    return fastring(lhs.size() + rhs.size() + 1).append(lhs).append(rhs);
}
inline fastring operator + (const fastring& lhs, const char* rhs){
    return fastring(lhs.size() + strlen(rhs) + 1).append(lhs).append(rhs, strlen(rhs));
}
inline fastring operator + (const char* lhs, const fastring& rhs){
    return fastring(strlen(lhs) + rhs.size() + 1).append(lhs, strlen(lhs)).append(rhs);
}

inline bool operator == (const fastring& lhs, const char* rhs){
    if(lhs.size() != strlen(rhs)) return false;
    return lhs.size() == 0 || memcmp(lhs.data, rhs, lhs.size()) == 0;
}
inline bool operator == (const fastring& lhs, const fastring& rhs){
    if(lhs.size() != rhs.size()) return false;
    return lhs.size() == 0 || memcmp(lhs.data(), rhs.data(), lhs.size()) == 0;
}
inline bool operator == (const char* lhs, const fastring& rhs){
    return rhs == lhs;
}

inline bool operator != (const fastring& lhs, const fastring& rhs){
    return !(lhs == rhs);
}
inline bool operator != (const fastring& lhs, const char* rhs){
    return !(lhs == rhs);
}
inline bool operator != (const char* lhs, const fastring& rhs){
    return !(lhs == rhs);
}

inline bool operator < (const fastring& lhs, const fastring& rhs){
    if(lhs.size() < rhs.size()){
        return lhs.size() == 0 || memcmp(lhs.data(), rhs.data(), lhs.size()) <= 0;
    } else {
        return memcmp(lhs.data(), rhs.data(), rhs.size()) < 0;
    }
}
inline bool operator < (const fastring& lhs, const char* rhs){
    size_t n = strlen(rhs);
    if(lhs.size() < n){
        return lhs.size() == 0 || memcmp(lhs.data(), rhs, lhs.size()) <= 0;
    } else {
        return memcmp(lhs.data(), rhs, n) < 0;
    }
}
inline bool operator < (const char* lhs, const fastring& rhs){
    return rhs > lhs;
}

inline bool operator > (const fastring& lhs, const fastring& rhs){
    if(lhs.size() > rhs.size()){
        return rhs.size() == 0 || memcmp(lhs.data(), rhs.data(), rhs.size()) >= 0;
    } else {
        return memcmp(lhs.data(), rhs.data(), lhs.size()) > 0;
    }
}
inline bool operator > (const fastring& lhs, const char* rhs){
    size_t n = strlen(rhs);
    if(lhs.size() > n){
        return n == 0 || memcmp(lhs.data(), rhs, n) >= 0;
    } else {
        return memcmp(lhs.data(), rhs, lhs.size()) > 0;
    }
}
inline bool operator > (const char* lhs, const fastring& rhs){
    return rhs < lhs;
}

inline std::ostream& operator << (std::ostream& os, const fastring& fs){
    return os << fs.c_str();
}