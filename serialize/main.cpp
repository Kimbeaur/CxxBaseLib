
#include <cstdlib>
#include <iostream>
#include <exception>
#include <memory>
#include <ctime>
#include<functional>
#include<string.h>
#include "BSerialize.hpp"
#include "unittest.h"
using namespace std;
using namespace CPM_BSERIALIZE_NS;
using namespace CPM_BSERIALIZE_NS::detail;



class TestSomething: public Test {
public:
    TestSomething(): Test() {
        registerTest(TestSomething::testInt);
        registerTest(TestSomething::testFloat);
    }
    void testInt() {
        int aac = 1;
        int bbd = 3;
        assertEqual(aac, bbd);
        assertEqual(aac, 1);
    }
    void testFloat() {
        float f1 = 3.14;
        float f2 = 3.14;
        assertEqual(f1, f2);
    }
};

void test(void)
{
  const size_t bufferSize = 1024;
  char* buffer = static_cast<char*>(std::malloc(bufferSize));
  BSerialize serializeOut(buffer, bufferSize);  

  uint8_t magicBytes[4];
  magicBytes[0] = 'T';
  magicBytes[1] = 'M';
  magicBytes[2] = 198;
  magicBytes[3] = 3;

  const char* nullTermString = "My null terminated string.";

  uint8_t   u8  =  248;
  int8_t    i8  = -34;

  uint16_t  u16 =  8329;
  int16_t   i16 = -298;

  uint32_t  u32 =  983287;
  int32_t   i32 = -1898223;

  uint64_t  u64 =  9182304812340712;
  int64_t   i64 = -328989777;

  float     f   =  389.082;
  double    d   = -89723.098;

  std::string str = "My string";

  // Write to buffer.
  serializeOut.writeBytes(reinterpret_cast<char*>(magicBytes), 4);
  serializeOut.writeNullTermString(nullTermString);
  serializeOut.write<uint8_t>(u8);
  serializeOut.write<int8_t>(i8);

  serializeOut.write(u16);
  serializeOut.write(i16);

  serializeOut.write(u32);
  serializeOut.write(i32);

  serializeOut.write(u64);
  serializeOut.write(i64);

  serializeOut.write<float>(f);
  serializeOut.write<double>(d);

  serializeOut.write(str);

  // Read from buffer
  BSerialize serializeIn(buffer, bufferSize);  

  uint8_t* inMagicBytes = reinterpret_cast<uint8_t*>(serializeIn.readBytes(4));

  std::cout<<inMagicBytes[0]<<std::endl;
  std::cout<<inMagicBytes[1]<<std::endl;
  std::cout<<inMagicBytes[2]<<std::endl;
  std::cout<<inMagicBytes[3]<<std::endl;


  const char* inStr = serializeIn.readNullTermString();
  std::cout<<inStr<<std::endl;
  


  std::cout<<serializeIn.read<uint8_t>()<<std::endl;
 
  std::cout<<serializeIn.read<int8_t>()<<std::endl;

  std::cout<<serializeIn.read<uint16_t>()<<std::endl;

  std::cout<<serializeIn.read<int16_t>()<<std::endl;
  std::cout<<serializeIn.read<uint32_t>()<<std::endl;

  std::cout<<serializeIn.read<int32_t>()<<std::endl;

 
  std::cout<<serializeIn.read<uint64_t>()<<std::endl;
 
  std::cout<<serializeIn.read<int64_t>()<<std::endl;

  
  std::cout<<serializeIn.read<float>()<<std::endl;

  std::cout<<serializeIn.read<double>()<<std::endl;


  std::cout<<serializeIn.read<std::string>()<<std::endl;

  std::free(buffer);
}

int main(int argc, char** argv)
{

  test();
  TestSomething t;
  t.testAll();
  return 0;
}

