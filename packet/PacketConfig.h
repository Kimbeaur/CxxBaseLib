#ifndef    _PACKET_CONFIG_H_
#define    _PACKET_CONFIG_H_

#include <string>
#include <functional>

class PacketBuffer;
class Packet;

using ReadBufferStringFunc = std::function<int(PacketBuffer*, std::string&)>;
using ReadBufferPacketFunc = std::function<int(PacketBuffer*, Packet&)>;
using ReadBufferVoidFunc = std::function<int(PacketBuffer*, void*)>;


class PacketConfig
{
public:
    enum BufferMode
    {
        NoBuffer,
        CycleBuffer,
        ListBuffer
    };

    static BufferMode BufferModeStatus;
    static uint64_t CycleBufferSize;

    static ReadBufferStringFunc ReadBufferStringCb;
    static ReadBufferPacketFunc ReadBufferPacketCb;
    static ReadBufferVoidFunc ReadBufferVoidCb;
};


#endif