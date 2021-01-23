#include "Msg.hpp"
#include "Queue.hpp"
#include <atomic>

namespace ThreadCom {

namespace {

Uint64 generateUniqueId()
{
    static std::atomic<Uint64> i(0);
    return ++i;
}

}

Msg::Msg(int msgId)
  : msgId_(msgId), uniqueId_(generateUniqueId())
{
}

std::unique_ptr<Msg> Msg::move()
{
    return std::unique_ptr<Msg>(new Msg(std::move(*this)));
}

int Msg::getMsgId() const
{
    return msgId_;
}

Uint64 Msg::getUniqueId() const
{
    return uniqueId_;
}

}
