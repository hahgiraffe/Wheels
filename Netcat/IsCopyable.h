#ifndef NETCAT_ISCOPYABLE_H
#define NETCAT_ISCOPYABLE_H

class Noncopyable{
public:
    Noncopyable(){ }
private:
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable operator = (const Noncopyable&) = delete;
};

#endif