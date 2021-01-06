#ifndef    _PACKET_H_
#define    _PACKET_H_

#include <string>
#include "PacketBuffer.h"

/************************************************
     packet
    ---------------------------------------
    head  |  size   | data   |  end   |
    1 byte | 2 bytes | N bytes| 1 byte |
    ---------------------------------------
 ************************************************/

class Packet
{
public:
    Packet();
    ~Packet();

    void Pack(const char *data, uint16_t size);
    const char* GetData();
    const uint16_t DataSize();
    const std::string& Buffer();
    const u_int32_t PacketSize();

    void Swap(std::string &str);
    static int ReadFromBuffer(PacketBuffer* ,Packet&);

    template<typename NumType>
    static void UnPackNum(const uint8_t *data, NumType &num);

    template<typename NumType>
    static void PackNum(char *data, NumType num);

    static uint32_t PacketMinSize();

public:
    enum DataMode
    {
        BigEndian,
        LittleEndian
    };

    static uint8_t HeadByte;
    static uint8_t EndByte;
    static DataMode Mode;
protected:
    std::string buffer_;
    uint16_t dataSize_;


};

template<typename NumType>
inline void Packet::UnPackNum(const uint8_t* data, NumType& num)
{
    num = 0;
    auto size = static_cast<int>(sizeof(NumType));
    if (Packet::DataMode::BigEndian == Packet::Mode)
    {
        for (int i = 0; i < size; i++)
        {
            num <<= 8;
            num |= data[i];

        }
    }
    else
    {
        for (int i = size-1; i >= 0; i--)
        {
            num <<= 8;
            num |= data[i];
        }
    }
}

template<typename NumType>
inline void Packet::PackNum(char* data, NumType num)
{
    int size = static_cast<int>(sizeof(NumType));
    if (Packet::DataMode::BigEndian == Packet::Mode)
    {
        for (int i = size-1; i >= 0; i--)
        {
            data[i] = num & 0xff;
            num >>= 8;
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = num & 0xff;
            num >>= 8;
        }
    }
}



#endif