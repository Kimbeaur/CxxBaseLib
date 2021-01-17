//
//  BinaryDeserializer.hpp
//  Serializer
//
//  Created by Gusts Kaksis on 01/09/2020.
//  Copyright © 2020 Gusts Kaksis. All rights reserved.
//

#ifndef BinaryDeserializer_h
#define BinaryDeserializer_h

#include "BinaryUnpacker.hpp"
#include "TypeMap.hpp"

namespace gusc::Serializer
{

template<typename TChar,
    typename _ = typename std::enable_if<sizeof(TChar)==1>::type>
class BinaryDeserializer
{
public:
    BinaryDeserializer(std::vector<TChar>& initTargetVector)
        : unpacker(BinaryUnpacker<TChar>(initTargetVector))
    {}
    
    template<typename TValue>
    BinaryDeserializer& operator>>(TValue& inValue);
    
    void skip(size_t numElements)
    {
        while(numElements != 0)
        {
            uint32_t tmp;
            unpacker >> tmp; // type ID
            unpacker >> tmp; // length of the value
            unpacker.skip(tmp); // skip value
            --numElements;
        }
    }
    
private:
    BinaryUnpacker<TChar> unpacker;
};
    
template<typename TChar, typename TEnable>
template<typename TValue>
BinaryDeserializer<TChar, TEnable>& BinaryDeserializer<TChar, TEnable>::operator>>(TValue& outValue)
{
    uint32_t type;
    TChar tmp[sizeof(uint32_t)];
    unpacker.peek(&tmp[0], sizeof(uint32_t));
    memcpy(&type, tmp, sizeof(uint32_t));
    uint32_t ttype = FindTypeId<TValue>();
    if (type != ttype)
    {
        throw std::invalid_argument("Type does not match");
    }
    unpacker.skip(sizeof(uint32_t));
    
    uint32_t length;
    unpacker >> length;
    unpacker >> outValue;
    return *this;
}
    
}

#endif /* BinaryDeserializer_h */
