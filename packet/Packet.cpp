

#include "packet.h"


uint8_t Packet::HeadByte = 0x7E;
uint8_t Packet::EndByte = 0xE7;
Packet::DataMode Packet::Mode = Packet::DataMode::LittleEndian;

Packet::Packet()
:buffer_(""),dataSize_(0)
{
}

Packet::~Packet()
{
}

int Packet::ReadFromBuffer(PacketBuffer *packetbuf, Packet &out)
{
    std::string data("");
    while (true)
    {
        auto size = packetbuf->ReadSize();
        //数据小于包头大小
        if(size < PacketMinSize())
        {
            return -1;
        }
        //找包头
        uint16_t dataSize;
        packetbuf->ReadBufferN(data, sizeof(dataSize+1));
        if((uint8_t)data[0] != HeadByte)
        {
            data.clear();
            packetbuf->ClearBufferN(1);
            continue;
        }
        UnPackNum((uint8_t*)data.c_str() + 1, dataSize);
        uint16_t msgsize = dataSize + PacketMinSize();
        //包不完整
        if (size < msgsize)
        {
            return -1;
        }
        packetbuf->ClearBufferN(sizeof(dataSize)+1);
        packetbuf->ReadBufferN(data, dataSize +1);
        //检查包尾
        if ((uint8_t)data.back() == EndByte)
        {
            packetbuf->ClearBufferN(dataSize +1);
            break;
        }
    }
        out.Swap(data);
    return 0;
}


void Packet::Pack(const char* data, uint16_t size)
{
    dataSize_ = size;
    buffer_.resize(size+ PacketMinSize());

    buffer_[0] = HeadByte;
    PackNum(&buffer_[1],size);

    std::copy(data, data + size, &buffer_[sizeof(HeadByte) + sizeof(dataSize_)]);
    buffer_.back() = EndByte;
}


const char* Packet::GetData()
{
    return buffer_.c_str()+sizeof(HeadByte)+sizeof(dataSize_);
}

const uint16_t Packet::DataSize()
{
    return dataSize_;
}

const std::string& Packet::Buffer()
{
    return buffer_;
}

const uint32_t Packet::PacketSize()
{
    return (uint32_t)buffer_.size();
}

void Packet::Swap(std::string& str)
{
    buffer_.swap(str);
    dataSize_ = (uint16_t)(buffer_.size() - PacketMinSize());
}


uint32_t Packet::PacketMinSize()
{
    return 4;
}



