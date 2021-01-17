//
//  TypeMap.hpp
//  Serializer
//
//  Created by Gusts Kaksis on 01/09/2020.
//  Copyright © 2020 Gusts Kaksis. All rights reserved.
//

#ifndef TypeMap_h
#define TypeMap_h

#include <vector>
#include <map>

namespace gusc::Serializer
{
    
template<typename TType>
struct TypeTlvMap;

enum class SerializableType : uint32_t
{
    Bool = 1,
    
    Int8 = 10,
    UInt8,
    Int16,
    UInt16,
    Int32,
    UInt32,
    Int64,
    UInt64,
    Int128,
    UInt128,
    
    Float = 100,
    Double,
    
    Vector = 200,
    Map,
    
    Custom = 1000 // Define your mapped types with values of Custom+N
};

template<typename TType>
struct SerializableTypeMap;
    
// Map definitions

template<>
struct SerializableTypeMap<bool>
{
    static constexpr SerializableType typeId = SerializableType::Bool;
};
    
template<>
struct SerializableTypeMap<int8_t>
{
    static constexpr SerializableType typeId = SerializableType::Int8;
};

template<>
struct SerializableTypeMap<char>
{
    static constexpr SerializableType typeId = SerializableType::UInt8;
};
    
template<>
struct SerializableTypeMap<uint8_t>
{
    static constexpr SerializableType typeId = SerializableType::UInt8;
};
    
template<>
struct SerializableTypeMap<int16_t>
{
    static constexpr SerializableType typeId = SerializableType::Int16;
};
    
template<>
struct SerializableTypeMap<uint16_t>
{
    static constexpr SerializableType typeId = SerializableType::UInt16;
};

template<>
struct SerializableTypeMap<long>
{
    static constexpr SerializableType typeId = SerializableType::Int32;
};
    
template<>
struct SerializableTypeMap<int32_t>
{
    static constexpr SerializableType typeId = SerializableType::Int32;
};

template<>
struct SerializableTypeMap<unsigned long>
{
    static constexpr SerializableType typeId = SerializableType::UInt32;
};
    
template<>
struct SerializableTypeMap<uint32_t>
{
    static constexpr SerializableType typeId = SerializableType::UInt32;
};
 #if 0 
template<>
struct SerializableTypeMap<int64_t>
{
    static constexpr SerializableType typeId = SerializableType::Int64;
};
 
template<>
struct SerializableTypeMap<uint64_t>
{
    static constexpr SerializableType typeId = SerializableType::UInt64;
};
#endif   
template<>
struct SerializableTypeMap<float>
{
    static constexpr SerializableType typeId = SerializableType::Float;
};
    
template<>
struct SerializableTypeMap<double>
{
    static constexpr SerializableType typeId = SerializableType::Double;
};
    
template<typename TValue>
struct SerializableTypeMap<std::vector<TValue>>
{
    static constexpr SerializableType typeId = SerializableType::Vector;
};
    
template<typename TKey, typename TValue>
struct SerializableTypeMap<std::map<TKey, TValue>>
{
    static constexpr SerializableType typeId = SerializableType::Map;
};

// End map definitions
    
template<typename TType>
uint32_t FindTypeId()
{
    return static_cast<uint32_t>(SerializableTypeMap<TType>::typeId);
}
    
}


#endif /* TypeMap_h */
