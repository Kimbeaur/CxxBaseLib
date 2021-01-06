#ifndef _UUID_H_
#define _UUID_H_

#include <random>


class UUID
{
public:
  static uint64_t GenerateUuid()
  {
    uint64_t uuid = std::chrono::system_clock::now().time_since_epoch().count();
    std::random_device rd;
    uuid = (uuid << 16) | rd();
    return uuid;
  }
};

#endif