/*
 * ====================================================
 * Copyright (c) 2020-2100
 *     FileName: bytearray.h
 *       Author: Ye Gui Wu
 *        Email: yeguiwu@qq.com
 *      Version: 1.0
 *     Compiler: gcc
 *  Create Date: 2020-09-16
 *  Description: 二进制数组(序列化/反序列化)
 * ====================================================
 */
#ifndef __YGW_BYTEARRAY_H__
#define __YGW_BYTEARRAY_H__

#include <sys/types.h>
#include <sys/socket.h>

#include <cstdint>

#include <memory>
#include <string>
#include <vector>

namespace ygw {

    //-------------------------------------------------------------

    namespace container {

        class ByteArray
        {
        public:
            using ptr = std::shared_ptr<ByteArray>;

            //----------------------------------------
            // struct Node begin
            /**
             * @brief ByteArray的存储节点
             */
            struct Node {

                /**
                 * @brief 构造指定大小的内存块
                 * @param[in] s 内存块字节数
                 */
                Node(size_t s);

                /**
                 * 无参构造
                 */
                Node();

                /**
                 * 析构函数，释放内存
                 */
                ~Node();

                /// 内存块地址指针
                char* ptr;
                /// 下一块内存块地址
                Node* next;
                /// 内存块大小
                size_t size;
            }; // struct Node end
            //----------------------------------------


            /**
             * @brief 使用指定长度的内存块构造ByteArray
             * @param[in] base_size 内存块大小
             */
            ByteArray(size_t base_size = 4096);

            /**
             * @brief 析构函数
             */
            ~ByteArray();

            /**
             * @brief 写入固定长度int8_t类型的数据
             * @post position_ += sizeof(value)
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteFint8(int8_t value);
            /**
             * @brief 写入固定长度uint8_t类型的数据
             * @post position_ += sizeof(value)
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteFuint8(uint8_t value);
            /**
             * @brief 写入固定长度int16_t类型的数据(大端/小端)
             * @post position_ += sizeof(value)
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteFint16(int16_t value);
            /**
             * @brief 写入固定长度uint16_t类型的数据(大端/小端)
             * @post position_ += sizeof(value)
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteFuint16(uint16_t value);

            /**
             * @brief 写入固定长度int32_t类型的数据(大端/小端)
             * @post position_ += sizeof(value)
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteFint32 (int32_t value);

            /**
             * @brief 写入固定长度uint32_t类型的数据(大端/小端)
             * @post position_ += sizeof(value)
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteFuint32(uint32_t value);

            /**
             * @brief 写入固定长度int64_t类型的数据(大端/小端)
             * @post position_ += sizeof(value)
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteFint64 (int64_t value);

            /**
             * @brief 写入固定长度uint64_t类型的数据(大端/小端)
             * @post position_ += sizeof(value)
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteFuint64(uint64_t value);

            /**
             * @brief 写入有符号Varint32类型的数据
             * @post position_ += 实际占用内存(1 ~ 5)
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteInt32  (int32_t value);
            /**
             * @brief 写入无符号Varint32类型的数据
             * @post position_ += 实际占用内存(1 ~ 5)
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteUint32 (uint32_t value);

            /**
             * @brief 写入有符号Varint64类型的数据
             * @post position_ += 实际占用内存(1 ~ 10)
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteInt64  (int64_t value);

            /**
             * @brief 写入无符号Varint64类型的数据
             * @post position_ += 实际占用内存(1 ~ 10)
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteUint64 (uint64_t value);

            /**
             * @brief 写入float类型的数据
             * @post position_ += sizeof(value)
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteFloat  (float value);

            /**
             * @brief 写入double类型的数据
             * @post position_ += sizeof(value)
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteDouble (double value);

            /**
             * @brief 写入std::string类型的数据,用uint16_t作为长度类型
             * @post position_ += 2 + value.size()
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteStringF16(const std::string& value);

            /**
             * @brief 写入std::string类型的数据,用uint32_t作为长度类型
             * @post position_ += 4 + value.size()
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteStringF32(const std::string& value);

            /**
             * @brief 写入std::string类型的数据,用uint64_t作为长度类型
             * @post position_ += 8 + value.size()
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteStringF64(const std::string& value);

            /**
             * @brief 写入std::string类型的数据,用无符号Varint64作为长度类型
             * @post position_ += Varint64长度 + value.size()
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteStringVint(const std::string& value);

            /**
             * @brief 写入std::string类型的数据,无长度
             * @post position_ += value.size()
             *       如果position_ > size_ 则 size_ = position_
             */
            void WriteStringWithoutLength(const std::string& value);

            /**
             * @brief 读取int8_t类型的数据
             * @pre GetReadSize() >= sizeof(int8_t)
             * @post position_ += sizeof(int8_t);
             * @exception 如果GetReadSize() < sizeof(int8_t) 抛出 std::out_of_range
             */
            int8_t ReadFint8();

            /**
             * @brief 读取uint8_t类型的数据
             * @pre GetReadSize() >= sizeof(uint8_t)
             * @post position_ += sizeof(uint8_t);
             * @exception 如果GetReadSize() < sizeof(uint8_t) 抛出 std::out_of_range
             */
            uint8_t ReadFuint8();

            /**
             * @brief 读取int16_t类型的数据
             * @pre GetReadSize() >= sizeof(int16_t)
             * @post position_ += sizeof(int16_t);
             * @exception 如果GetReadSize() < sizeof(int16_t) 抛出 std::out_of_range
             */
            int16_t  ReadFint16();

            /**
             * @brief 读取uint16_t类型的数据
             * @pre GetReadSize() >= sizeof(uint16_t)
             * @post position_ += sizeof(uint16_t);
             * @exception 如果GetReadSize() < sizeof(uint16_t) 抛出 std::out_of_range
             */
            uint16_t ReadFuint16();

            /**
             * @brief 读取int32_t类型的数据
             * @pre GetReadSize() >= sizeof(int32_t)
             * @post position_ += sizeof(int32_t);
             * @exception 如果GetReadSize() < sizeof(int32_t) 抛出 std::out_of_range
             */
            int32_t  ReadFint32();

            /**
             * @brief 读取uint32_t类型的数据
             * @pre GetReadSize() >= sizeof(uint32_t)
             * @post position_ += sizeof(uint32_t);
             * @exception 如果GetReadSize() < sizeof(uint32_t) 抛出 std::out_of_range
             */
            uint32_t ReadFuint32();

            /**
             * @brief 读取int64_t类型的数据
             * @pre GetReadSize() >= sizeof(int64_t)
             * @post position_ += sizeof(int64_t);
             * @exception 如果GetReadSize() < sizeof(int64_t) 抛出 std::out_of_range
             */
            int64_t  ReadFint64();

            /**
             * @brief 读取uint64_t类型的数据
             * @pre GetReadSize() >= sizeof(uint64_t)
             * @post position_ += sizeof(uint64_t);
             * @exception 如果GetReadSize() < sizeof(uint64_t) 抛出 std::out_of_range
             */
            uint64_t ReadFuint64();

            /**
             * @brief 读取有符号Varint32类型的数据
             * @pre GetReadSize() >= 有符号Varint32实际占用内存
             * @post position_ += 有符号Varint32实际占用内存
             * @exception 如果GetReadSize() < 有符号Varint32实际占用内存 抛出 std::out_of_range
             */
            int32_t  ReadInt32();

            /**
             * @brief 读取无符号Varint32类型的数据
             * @pre GetReadSize() >= 无符号Varint32实际占用内存
             * @post position_ += 无符号Varint32实际占用内存
             * @exception 如果GetReadSize() < 无符号Varint32实际占用内存 抛出 std::out_of_range
             */
            uint32_t ReadUint32();

            /**
             * @brief 读取有符号Varint64类型的数据
             * @pre GetReadSize() >= 有符号Varint64实际占用内存
             * @post position_ += 有符号Varint64实际占用内存
             * @exception 如果GetReadSize() < 有符号Varint64实际占用内存 抛出 std::out_of_range
             */
            int64_t  ReadInt64();

            /**
             * @brief 读取无符号Varint64类型的数据
             * @pre GetReadSize() >= 无符号Varint64实际占用内存
             * @post position_ += 无符号Varint64实际占用内存
             * @exception 如果GetReadSize() < 无符号Varint64实际占用内存 抛出 std::out_of_range
             */
            uint64_t ReadUint64();

            /**
             * @brief 读取float类型的数据
             * @pre GetReadSize() >= sizeof(float)
             * @post position_ += sizeof(float);
             * @exception 如果GetReadSize() < sizeof(float) 抛出 std::out_of_range
             */
            float    ReadFloat();

            /**
             * @brief 读取double类型的数据
             * @pre GetReadSize() >= sizeof(double)
             * @post position_ += sizeof(double);
             * @exception 如果GetReadSize() < sizeof(double) 抛出 std::out_of_range
             */
            double   ReadDouble();

            /**
             * @brief 读取std::string类型的数据,用uint16_t作为长度
             * @pre GetReadSize() >= sizeof(uint16_t) + size
             * @post position_ += sizeof(uint16_t) + size;
             * @exception 如果GetReadSize() < sizeof(uint16_t) + size 抛出 std::out_of_range
             */
            std::string ReadStringF16();

            /**
             * @brief 读取std::string类型的数据,用uint32_t作为长度
             * @pre GetReadSize() >= sizeof(uint32_t) + size
             * @post position_ += sizeof(uint32_t) + size;
             * @exception 如果GetReadSize() < sizeof(uint32_t) + size 抛出 std::out_of_range
             */
            std::string ReadStringF32();

            /**
             * @brief 读取std::string类型的数据,用uint64_t作为长度
             * @pre GetReadSize() >= sizeof(uint64_t) + size
             * @post position_ += sizeof(uint64_t) + size;
             * @exception 如果GetReadSize() < sizeof(uint64_t) + size 抛出 std::out_of_range
             */
            std::string ReadStringF64();

            /**
             * @brief 读取std::string类型的数据,用无符号Varint64作为长度
             * @pre GetReadSize() >= 无符号Varint64实际大小 + size
             * @post position_ += 无符号Varint64实际大小 + size;
             * @exception 如果GetReadSize() < 无符号Varint64实际大小 + size 抛出 std::out_of_range
             */
            std::string ReadStringVint();

            /**
             * @brief 清空ByteArray
             * @post position_ = 0, size_ = 0
             */
            void Clear();

            /**
             * @brief 写入size长度的数据
             * @param[in] buf 内存缓存指针
             * @param[in] size 数据大小
             * @post position_ += size, 如果position_ > size_ 则 size_ = position_
             */
            void Write(const void* buf, size_t size);

            /**
             * @brief 读取size长度的数据
             * @param[out] buf 内存缓存指针
             * @param[in] size 数据大小
             * @post position_ += size, 如果position_ > size_ 则 size_ = position_
             * @exception 如果GetReadSize() < size 则抛出 std::out_of_range
             */
            void Read(void* buf, size_t size);

            /**
             * @brief 读取size长度的数据
             * @param[out] buf 内存缓存指针
             * @param[in] size 数据大小
             * @param[in] position 读取开始位置
             * @exception 如果 (size_ - position) < size 则抛出 std::out_of_range
             */
            void Read(void* buf, size_t size, size_t position) const;

            /**
             * @brief 返回ByteArray当前位置
             */
            size_t GetPosition() const { return position_;}

            /**
             * @brief 设置ByteArray当前位置
             * @post 如果position_ > size_ 则 size_ = position_
             * @exception 如果position_ > capacity_ 则抛出 std::out_of_range
             */
            void SetPosition(size_t v);

            /**
             * @brief 把ByteArray的数据写入到文件中
             * @param[in] name 文件名
             */
            bool WriteToFile(const std::string& name) const;

            /**
             * @brief 从文件中读取数据
             * @param[in] name 文件名
             */
            bool ReadFromFile(const std::string& name);

            /**
             * @brief 返回内存块的大小
             */
            size_t GetBaseSize() const { return base_size_;}

            /**
             * @brief 返回可读取数据大小
             */
            size_t GetReadSize() const { return size_ - position_;}

            /**
             * @brief 是否是小端
             */
            bool IsLittleEndian() const;

            /**
             * @brief 设置是否为小端
             */
            void SetIsLittleEndian(bool val);

            /**
             * @brief 将ByteArray里面的数据[position_, size_)转成std::string
             */
            std::string ToString() const;

            /**
             * @brief 将ByteArray里面的数据[position_, size_)转成16进制的std::string(格式:FF FF FF)
             */
            std::string ToHexString() const;

            /**
             * @brief 获取可读取的缓存,保存成iovec数组
             * @param[out] buffers 保存可读取数据的iovec数组
             * @param[in] len 读取数据的长度,如果len > GetReadSize() 则 len = GetReadSize()
             * @return 返回实际数据的长度
             */
            uint64_t GetReadBuffers(std::vector<iovec>& buffers, uint64_t len = ~0ull) const;

            /**
             * @brief 获取可读取的缓存,保存成iovec数组,从position位置开始
             * @param[out] buffers 保存可读取数据的iovec数组
             * @param[in] len 读取数据的长度,如果len > GetReadSize() 则 len = GetReadSize()
             * @param[in] position 读取数据的位置
             * @return 返回实际数据的长度
             */
            uint64_t GetReadBuffers(std::vector<iovec>& buffers, uint64_t len, uint64_t position) const;

            /**
             * @brief 获取可写入的缓存,保存成iovec数组
             * @param[out] buffers 保存可写入的内存的iovec数组
             * @param[in] len 写入的长度
             * @return 返回实际的长度
             * @post 如果(position_ + len) > capacity_ 则 capacity_扩容N个节点以容纳len长度
             */
            uint64_t GetWriteBuffers(std::vector<iovec>& buffers, uint64_t len);

            /**
             * @brief 返回数据的长度
             */
            size_t GetSize() const { return size_;}
        private:

            /**
             * @brief 扩容ByteArray,使其可以容纳size个数据(如果原本可以可以容纳,则不扩容)
             */
            void AddCapacity(size_t size);

            /**
             * @brief 获取当前的可写入容量
             */
            size_t GetCapacity() const { return capacity_ - position_;}
        private:
            /// 内存块的大小
            size_t base_size_;
            /// 当前操作位置
            size_t position_;
            /// 当前的总容量
            size_t capacity_;
            /// 当前数据的大小
            size_t size_;
            /// 第一个内存块指针
            Node* root_;
            /// 当前操作的内存块指针
            Node* cur_;
            /// 字节序,默认大端
            int8_t endian_;

        }; // class ByteArray


    } // namespace container

    //-------------------------------------------------------------

} // namespace ygw

#endif
