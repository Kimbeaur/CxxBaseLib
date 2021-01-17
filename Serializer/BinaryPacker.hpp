//
//  BinaryPacker.hpp
//  Serializer
//
//  Created by Gusts Kaksis on 31/08/2020.
//  Copyright © 2020 Gusts Kaksis. All rights reserved.
//

#ifndef BinaryPacker_h
#define BinaryPacker_h
#include<string.h>
namespace gusc::Serializer
{
    
template<typename TChar,
         typename _ = typename std::enable_if<sizeof(TChar)==1>::type>
class BinaryPacker
{
public:
    BinaryPacker(std::vector<TChar>& initTargetVector)
        : targetVector(initTargetVector)
    {}
    
    template<typename TValue>
    BinaryPacker& operator<<(const TValue& inValue);
    
    inline void write(const TChar* data, size_t numElements)
    {
        targetVector.insert(targetVector.end(), data, data + numElements);
    }
    
private:
    std::vector<TChar>& targetVector;
};

template<typename TChar, typename TEnable>
template<typename TValue>
BinaryPacker<TChar, TEnable>& BinaryPacker<TChar, TEnable>::operator<<(const TValue& inValue)
{
    to_pack(*this, inValue);
    return *this;
}

template<typename TChar>
void to_pack(BinaryPacker<TChar>& packer, const TChar& inValue)
{
    packer.write(&inValue, 1);
}

template<typename TChar,
         typename TValue>
void to_pack(BinaryPacker<TChar>& packer, const TValue& inValue)
{
    TChar tmp[sizeof(TValue)];
    memcpy(tmp, &inValue, sizeof(TValue));
    packer.write(&tmp[0], sizeof(TValue));
}

template<typename TChar,
         typename TValue>
void to_pack(BinaryPacker<TChar>& packer, const std::vector<TValue>& inValue)
{
    for (const auto& it : inValue)
    {
        packer << *it;
    }
}

}

#endif /* BinaryPacker_h */
