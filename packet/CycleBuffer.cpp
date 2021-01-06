/*
Copyright © 2017-2020, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2019-10-24

Description: https://github.com/wlgq2/uv-cpp
*/
#include "CycleBuffer.h"
#include "PacketConfig.h"



CycleBuffer::CycleBuffer()
    :writeIndex_(0),
    readIndex_(0)
{
    buffer_ = new uint8_t[PacketConfig::PacketConfig::CycleBufferSize];
}

CycleBuffer::~CycleBuffer()
{
    delete[] buffer_;
}


int CycleBuffer::Append(const char* data, uint64_t size)
{
    SizeInfo info;
    UsableSizeInfo(info);

    if (info.size < size)
    {
        //缓存不够
        return -1;
    }
    if (info.part1 >= size)
    {
        std::copy(data, data + size, buffer_ + writeIndex_);
    }
    else
    {
        std::copy(data, data + info.part1, buffer_ + writeIndex_);
        std::copy(data + info.part1, data + size, buffer_);
    }
    AddWriteIndex(size);
    return 0;

}

int CycleBuffer::ReadBufferN(std::string& data, uint64_t N)
{
    SizeInfo info;
    ReadSizeInfo(info);
    if (N > ReadSize())
    {
        return -1;
    }
    int start = (int)data.size();
    data.resize(start + N);
    //string被resize空间，所以操作指针安全
    char* out = const_cast<char*>(data.c_str());
    out += start;
    if (N <= info.part1)
    {
        std::copy(buffer_ + readIndex_, buffer_ + readIndex_ + N, out);
    }
    else
    {
        std::copy(buffer_ + readIndex_, buffer_ + PacketConfig::CycleBufferSize, out);
        uint64_t remain = N - info.part1;
        std::copy(buffer_, buffer_ + remain, out + info.part1);
    }

    return 0;
}

int CycleBuffer::ClearBufferN(uint64_t N)
{
    if(N>ReadSize())
    {
        N =ReadSize();
    }
    AddReadIndex(N);
    return 0;
}

int CycleBuffer::Clear()
{
    writeIndex_ = 0;
    readIndex_ = 0;
    return 0;
}

uint64_t CycleBuffer::UsableSize()
{
    uint64_t usable;
    if (writeIndex_ < readIndex_)
    {
        usable = readIndex_ - writeIndex_ - 1;
    }
    else
    {
        usable = PacketConfig::CycleBufferSize + readIndex_- writeIndex_-1;
    }
    return usable;
}

void CycleBuffer::UsableSizeInfo(SizeInfo& info)
{
    if (writeIndex_ < readIndex_)
    {
        info.part1 = readIndex_ - writeIndex_ - 1;
        info.part2 = 0;
    }
    else
    {
        bool readIsZore = (0 == readIndex_);
        info.part1 = readIsZore ? PacketConfig::CycleBufferSize - writeIndex_-1: PacketConfig::CycleBufferSize - writeIndex_;
        info.part2 = readIsZore ? 0 : readIndex_ - 1;
    }
    info.size = info.part1 + info.part2;
}

uint64_t CycleBuffer::ReadSize()
{
    SizeInfo info;
    ReadSizeInfo(info);
    return info.size;
}

void CycleBuffer::ReadSizeInfo(SizeInfo& info)
{
    if (writeIndex_ >= readIndex_)
    {
        info.part1 = writeIndex_ - readIndex_;
        info.part2 = 0;
    }
    else
    {
        info.part1 = PacketConfig::CycleBufferSize - readIndex_;
        info.part2 = writeIndex_;
    }
    info.size = info.part1 + info.part2;
}

int CycleBuffer::AddWriteIndex(uint64_t size)
{
    if (size > PacketConfig::CycleBufferSize)
        return -1;
    writeIndex_ += size;
    if (writeIndex_ >= PacketConfig::CycleBufferSize)
        writeIndex_ -= PacketConfig::CycleBufferSize;
    return 0;
}

int CycleBuffer::AddReadIndex(uint64_t size)
{
    if (size > PacketConfig::CycleBufferSize)
        return -1;
    readIndex_ += size;
    if (readIndex_ >= PacketConfig::CycleBufferSize)
        readIndex_ -= PacketConfig::CycleBufferSize;
    return 0;
}
