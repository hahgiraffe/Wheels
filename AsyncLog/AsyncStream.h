#ifndef LOGSTREAM_H
#define LOGSTREAM_H

#include <string.h>
#include <string>
namespace haha_giraffe{
    
// 缓冲区大小
const int SMALL_BUFFER_SIZE = 1024;
const int LARGE_BUFFER_SIZE = 1024 * 1000;

// 缓冲区模板类，用以存放日志数据
// 大小为存放SIZE个char类型的数组
template<int SIZE>
class Buffer
{
public:
    Buffer() : cur_(data_) {}

    // 往缓冲区添加数据
    void Append(const char* buf, size_t len)
    {
        if (GetAvailable() > static_cast<int>(len))
        {
            memcpy(cur_, buf, len);
            AppendComplete(len);
        }
    }
    // 添加数据完成后更新cur指针位置
    void AppendComplete(size_t len) { cur_ += len; }
    // 清空数据
    void Bzero() { bzero(data_, sizeof(data_)); }
    // 重置数据
    void Reset() { cur_ = data_; }

    // 获取数据
    const char* GetData() const { return data_; }
    // 获取数据长度
    int         GetLength() const { return static_cast<int>(cur_ - data_); }
    // 获取当前数据尾后指针
    char*       GetCur() { return cur_; }
    // 获取剩余可用空间
    int         GetAvailable() const { return static_cast<int>(GetEnd() - cur_); }

private:
    // 获取末尾指针
    const char* GetEnd() const { return data_ + sizeof(data_); }

    // 实际存放数据
    char data_[SIZE];
    // 当前数据尾后指针
    char* cur_;
};


// 日志流对象
class AsyncStream
{
public:
    // 固定大小缓冲区
    typedef Buffer<SMALL_BUFFER_SIZE> FixedBuffer;

    // 流输出操作符
    AsyncStream& operator<<(bool);
    AsyncStream& operator<<(short);
    AsyncStream& operator<<(int);
    AsyncStream& operator<<(long);
    AsyncStream& operator<<(long long);
    AsyncStream& operator<<(float);
    AsyncStream& operator<<(double);
    AsyncStream& operator<<(char);
    AsyncStream& operator<<(const char*);
    AsyncStream& operator<<(const std::string&);

    // 输出数据到缓冲区
    void Append(const char* data, int len) { buffer_.Append(data, len); }
    // 获取缓冲区对象
    const FixedBuffer& GetBuffer() const { return buffer_; }
private:
    // 格式化整型为字符串并输出到缓冲区
    template<typename T>
    void FormatInteger(T);

    // 缓冲区
    FixedBuffer buffer_;
    // 数字转为字符串后占用的最大字节数
    static const int MAX_NUMERIC_SIZE = 32;
};

}
#endif // LOGSTREAM_H