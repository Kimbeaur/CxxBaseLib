

#include "ListBuffer.h"
#include <iostream>
using namespace std;

ListBuffer::ListBuffer()
{

}

ListBuffer::~ListBuffer()
{

}

int ListBuffer::Append(const char* data, uint64_t size)
{
    for (uint64_t i = 0; i < size; i++)
        buffer_.push_back(data[i]);
    return 0;
}


int ListBuffer::ReadBufferN(std::string& data, uint64_t N)
{
    if (N > (uint64_t)buffer_.size())
        return -1;
    auto it = buffer_.begin();
    for (uint64_t i = 0; i < N; i++)
    {
        data.push_back(*it);
        it++;
    }
    return 0;
}

uint64_t ListBuffer::ReadSize()
{
    return (uint64_t)buffer_.size();
}

int ListBuffer::ClearBufferN(uint64_t N)
{
    for (uint64_t i = 0; i < N; i++)
    {
        if (buffer_.empty())
            break;
        buffer_.pop_front();
    }
    return 0;
}

int ListBuffer::Clear()
{
    buffer_.clear();
    return 0;
}
