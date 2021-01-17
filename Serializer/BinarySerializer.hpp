//
//  BinarySerializer.hpp
//  Serializer
//
//  Created by Gusts Kaksis on 01/09/2020.
//  Copyright © 2020 Gusts Kaksis. All rights reserved.
//

#ifndef BinarySerializer_h
#define BinarySerializer_h

#include "BinaryPacker.hpp"
#include "TypeMap.hpp"
#include<string.h>

namespace gusc::Serializer
{

template<typename TChar,
    typename _ = typename std::enable_if<sizeof(TChar)==1>::type>
class BinarySerializer
{
public:
    BinarySerializer(std::vector<TChar>& initTargetVector)
        : packer(BinaryPacker<TChar>(initTargetVector))
    {}
    
    template<typename TValue>
    BinarySerializer& operator<<(const TValue& inValue);
    
private:
    BinaryPacker<TChar> packer;
};
    
template<typename TChar, typename TEnable>
template<typename TValue>
BinarySerializer<TChar, TEnable>& BinarySerializer<TChar, TEnable>::operator<<(const TValue& inValue)
{
    uint32_t typeId = FindTypeId<TValue>();
    packer << static_cast<uint32_t>(typeId);
    packer << static_cast<uint32_t>(sizeof(TValue));
    packer << inValue;
    return *this;
}
    
}


#endif /* BinarySerializer_h */
