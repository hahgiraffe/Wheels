/*
 * @Author: haha_giraffe
 * @Date: 2020-04-14 20:51:30
 * @Description: file content
 */
#include "fastring.h"

fastring::fastring() : _p(0){
}

fastring::fastring(size_t cap){
    this->_Init(cap);
}

fastring::fastring(const char* s){
    if(!*s){
        _p = 0;
        return;
    }
    size_t n = strlen(s);
    this->_Init(n+1, n);
    memcpy(_p->s, s, n);
}

fastring::fastring(const void* s, size_t n){
    if(n == 0){
        _p = 0;
        return;
    }
    this->_Init(n+1, n);
    memcpy(_p->s, (const char*)s, n);
}

fastring::fastring(const std::string& s){
    fastring(s.data(), s.size());
}

fastring::~fastring(){
    if(!_p){
        return;
    }
    if(this->_UnRef() == 0){
        free(_p->s);
        free(_p);
    }
}

fastring::fastring(const fastring& fs) : _p(fs._p){
    if(_p) this->_Ref();
}

fastring& fastring::operator = (const fastring& s){
    if(&s == this){
        return *this;
    }
    if(_p && this->_UnRef() == 0){
        free(_p->s);
        free(_p);
    }
    _p = s._p;
    if(_p){
        this->_Ref();
    }
}

fastring& fastring::operator = (const std::string& s){
    if(s.empty()){
        this->clear();
        return *this;
    }
    this->reserve(s.size() + 1);
    memcpy(_p->s, s.data(), s.size());
    _p->size = s.size();
    return *this;

}

fastring& fastring::operator = (const char* s){
    if(!*s){
        this->clear();
        return *this;
    }
    size_t n = strlen(s);
    if(_p){
        if(!this->_Inside(s)){
            this->_Reserve(n + 1);
            memcpy(_p->s, s, n + 1);
            _p->size = n;
        } else if(s != _p->s){
            assert(n <= _p->size);
            memmove(_p->s, s, n + 1);
            _p->size = n;
        }
    } else{
        this->_Init(n + 1, n);
        memcpy(_p->s, s, n + 1);
    }
    return *this;
}

fastring fastring::substr(size_t pos) const{
    if(pos >= this->size()) return fastring();
    return fastring(_p->s + pos, _p->size - pos);
}
    
fastring fastring::substr(size_t pos, size_t len) const{
    if(pos >= this->size()) return fastring();
    return pos + len >= _p->size ? fastring(_p->s + pos, _p->size - pos) : fastring(_p->s + pos, len);
}

//注意find和find_first_of的区别
//find是查找查找字符串中第一次出现字符c、字符串s的位置；
//find_first_of是查找字符串中字符c、字符数组s中任意一个字符第一次出现的位置。
size_t fastring::find(char c) const{
    if(!_p || this->empty()){
        return npos;
    }
    char* res = (char*)memchr(_p->s, c, _p->size);
    return res ? res - _p->s : npos;
}

size_t fastring::find(char c, size_t pos) const{
    if(!_p || this->empty()){
        return npos;
    }
    char* res = (char*)memchr(_p->s + pos, c, _p->size - pos);
    return res ? res - _p->s : npos;
}

size_t fastring::find(const char* s) const{
    if(!_p || this->empty()){
        return npos;
    }
    char* res = strstr((char*)this->c_str(), s);
    return res ? res - _p->s : npos;
}

size_t fastring::find(const char* s, size_t pos) const{
    if(!_p || this->empty()){
        return npos;
    }
    char* res = strstr((char*)this->c_str() + pos, s);
    return res ? res - _p->s : npos;
}

size_t fastring::find_first_of(const char* s) const{
    if(!_p || this->empty()){
        return npos;
    }
    //size_t strcspn(char* s, char* reject) 用来计算字符串s从头开始连续有几个字符都不属于字符串reject。
    size_t t = strcspn(this->c_str(), s);
    return _p->s[t] ? t : npos;
}

size_t fastring::find_first_not_of(const char* s) const{
    if(!_p || this->empty()){
        return npos;
    }
    //size_t strspn(char* s, char* accept) 用来计算字符串s从头开始连续有几个字符都属于字符串accept。
    size_t t = strspn(this->c_str(), s);
    return _p->s[t] ? t : npos;
}

size_t fastring::find_first_not_of(char c) const{
    char s[2] = {c, '\0'};
    return this->find_first_not_of(s);
}

size_t fastring::find_last_of(const char* s) const{
    if(!_p || this->empty()){
        return npos;
    }
    char bs[256] = {0};
    while(*s){
        bs[*s++] = 1;
    }
    for(size_t i = _p->size; i > 0;){
        if(bs[_p->s[--i]]) return i;
    }
    return npos;
}
size_t fastring::find_last_not_of(const char* s) const{
    if(!_p || this->empty()) return npos;
    char bs[256] = {0};
    while(*s){
        bs[*s++] = 1;
    }
    for(size_t i = _p->size; i > 0;){
        if(!bs[_p->s[--i]]) return i;
    }
    return npos;
}

size_t fastring::find_last_not_of(char c) const{
    if(!_p) return npos;
    for(size_t i = _p->size; i > 0;){
        if(_p->s[--i] != c) return i;
    }
    return npos;
}

void fastring::replace(const char* sub, const char* to, size_t maxreplace){
    if(!_p) return;

    const char* from = this->c_str();
    const char* p = strstr(from, sub);
    if(!p) return;

    size_t n = strlen(sub);
    size_t m = strlen(to);
    fastring s(_p->size);

    //这一段是不断从from字符串中查找第一个sub，然后替换成to加到新的字符串上
    do{
        s.append(from, p-from).append(to, m);
        from = p + n;
        if(maxreplace && --maxreplace == 0) break;
    }while((p = strstr(from, sub)));

    //如果后面还有，则一起加到新字符串中
    if(from < _p->s + _p->size)
        s.append(from);

    this->resize(s.size());
    memcpy(_p->s, s.data(), s.size());
}

//strip是消除字符串两头出现的s中的字符，d为'r' or 'l' or 'b'
void fastring::strip(const char* s , char d){
    if(!_p || this->empty()){
        return;
    }
    char bs[256] = {0};
    while(*s){
        bs[(*s++)] = 1;
    }

    if(d == 'l' || d == 'L'){
        size_t b = 0;
        while(b < _p->size && bs[_p->s[b]]) ++b;
        if(b == 0 || (_p->size -= b) == 0) return;
        memmove(_p->s, _p->s + b, _p->size);
    } else if (d == 'r' || d == 'R'){
        size_t e = _p->size;
        while(e > 0 && bs[_p->s[e - 1]]) --e;
        if(e != _p->size) _p->size = e;
    } else{
        size_t e = _p->size;
        while(e > 0 && bs[_p->s[e - 1]]) --e;
        if(e != _p->size) _p->size = e;
        if(e == 0) return;

        size_t b = 0;
        while(b < _p->size && bs[_p->s[b]]) ++b;
        if(b == 0 || (_p->size -= b) == 0) return;
        memmove(_p->s, _p->s + b, _p->size);
    }
}

void fastring::strip(char c, char d){
    char s[2] = {c, '\0'};
    this->strip(s, d);
}

bool fastring::start_with(char c) const{
    return !this->empty() && this->front() == c;
}
bool fastring::start_with(const char* s, size_t n) const{
    if(n == 0) return true;
    return this->size() >= n && memcmp(_p->s, s, n) == 0;
}
bool fastring::start_with(const char* s) const{
    return this->start_with(s, strlen(s));
}
bool fastring::start_with(const fastring& s) const{
    return this->start_with(s.data(), s.size());
}
bool fastring::start_with(const std::string& s) const{
    return this->start_with(s.data(), s.size());
}

bool fastring::end_with(char c) const{
    return !this->empty() && this->back() == c;
}
bool fastring::end_with(const char* s, size_t n) const{
    if(n == 0) return true;
    return this->size() >= n && memcmp(_p->s + this->size() - n, s, n) == 0;
}
bool fastring::end_with(const char* s) const{
    return this->end_with(s, strlen(s));
}
bool fastring::end_with(const fastring& s) const{
    return this->end_with(s.data(), s.size());
}
bool fastring::end_with(const std::string& s) const{
    return this->end_with(s.data(), s.size());
}

fastring& fastring::toupper(){
    if(!_p) return *this;
    for(size_t i = 0; i < _p->size; ++i){
        char& c = _p->s[i];
        if('a' <= c && c <= 'z') c ^= 32;   //单字符大小写转换可以直接c ^= 32
    }
    return *this;
}
fastring& fastring::tolower(){
    if(!_p) return *this;
    for(size_t i = 0; i < _p->size; ++i){
        char& c = _p->s[i];
        if('A' <= c && c <= 'Z') c ^= 32;
    }
    return *this;
}
fastring fastring::upper() const{
    return this->clone().toupper();
}
fastring fastring::lower() const{
    return this->clone().tolower();
}

void fastring::swap(fastring& s){
    _Mem* tmp = s._p;
    s._p = this->_p;
    this->_p = tmp;
}
void fastring::swap(fastring&& s){
    s.swap(*this);
}

