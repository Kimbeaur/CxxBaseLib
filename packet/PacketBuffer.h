#ifndef    _PACKET_BUFFER_H_
#define    _PACKET_BUFFER_H_

#include <string>
#include <memory>
#include <functional>

#include "PacketConfig.h"

class Packet;
class PacketBuffer
{
public:
    PacketBuffer(){}
    virtual ~PacketBuffer(){}

    virtual int Append(const char *data, uint64_t size) = 0;
    virtual int ReadBufferN(std::string &data, uint64_t N) = 0;
    virtual int ClearBufferN(uint64_t N) = 0;
    virtual int Clear() = 0;
    virtual uint64_t ReadSize() = 0;

    int ReadSting(std::string &out)
    {
        if(nullptr != PacketConfig::ReadBufferStringCb)
        {
            return PacketConfig::ReadBufferStringCb(this, out);
        }
        else
        {
            fprintf(stderr, "not defineed packet parse func");
            return -1;
        }
    }

    int ReadPacket(Packet &out)
    {
        if(nullptr != PacketConfig::ReadBufferPacketCb)
        {
            return PacketConfig::ReadBufferPacketCb(this, out);
        }
        else
        {
            fprintf(stderr, "not defineed packet parse func");
            return -1;
        }
        
    }


    int ReadGeneric(void *out)
    {
        if(nullptr != PacketConfig::ReadBufferVoidCb)
        {
            return PacketConfig::ReadBufferVoidCb(this, out);
        }
        else
        {
            fprintf(stderr, "not defineed packet parse func");
            return -1;         
        }
        
    }

};

using PacketBufferPtr = std::shared_ptr<PacketBuffer>;

#endif