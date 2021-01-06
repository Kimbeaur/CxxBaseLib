/*
Copyright © 2017-2019, orcaer@yeah.net  All rights reserved.

Author: orcaer@yeah.net

Last modified: 2018-10-24

Description: https://github.com/wlgq2/uv-cpp
*/
#ifndef   _CYCLE_BUFFER_H_
#define   _CYCLE_BUFFER_H_

#include "PacketBuffer.h"

//ArrayBuffer(cycle)
//---------------------------------------
//  Null  |   byte   |  byte   |  Null
//---------------------------------------
//        ↑                      ↑
//   read position           write position

//              ↓can not write
//---------------------------------------
//  byte   |   byte   |  byte   |  byte
//---------------------------------------
//         ↑          ↑
//   write position  read position

//not thread safe.



struct SizeInfo
{
    uint64_t size;
    uint64_t part1;
    uint64_t part2;
};

class CycleBuffer :public PacketBuffer
{
public:
    CycleBuffer();
    ~CycleBuffer();

    //写字节时必须距离读字节一个字节，否则无法区分缓存满/空。
    int Append(const char* data, uint64_t size) override;
    int ReadBufferN(std::string& data, uint64_t N) override;
    int ClearBufferN(uint64_t N) override;
    int Clear() override;
    uint64_t ReadSize()  override;

private:
    uint64_t UsableSize();
    void UsableSizeInfo(SizeInfo& info);
    void ReadSizeInfo(SizeInfo& info);

    int AddWriteIndex(uint64_t size);
    int AddReadIndex(uint64_t size);

private:
    uint8_t* buffer_;
    uint64_t writeIndex_;
    uint64_t readIndex_;

};

#endif 

