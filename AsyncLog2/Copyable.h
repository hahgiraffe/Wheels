#pragma once

class Noncopyable{
public:
    Noncopyable(){ }
    ~Noncopyable(){ }
private:
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable operator = (const Noncopyable&) = delete;
};
