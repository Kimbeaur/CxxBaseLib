
#ifndef _LIST_BUFFER_H_
#define _LIST_BUFFER_H_


#include <list>

#include "PacketBuffer.h"


//ListBuffer
//---------------------------------------
//  Null  |  Packet   |  Packet   |  Null 
//---------------------------------------
//        ↑                      ↑
//   read position           write position

//not thread safe.


class ListBuffer : public PacketBuffer
{
public:
    ListBuffer();
    ~ListBuffer();
 
    int Append(const char* data, uint64_t size) override;
    int ReadBufferN(std::string& data, uint64_t N) override;
    uint64_t ReadSize() override;
    int ClearBufferN(uint64_t N) override;
    int Clear() override;

private:
    std::list<uint8_t> buffer_;

};

#endif // AGILNET_NET_BUFFER
