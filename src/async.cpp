#include <thread>
#include <string>
#include "conductor.h"

namespace packer {
std::thread::id connect(const size_t bulkSize)
{
    return Conductor::instance().connect(bulkSize);
}
void recieve(std::string &&buf, std::thread::id context)
{
    Conductor::instance().recieve(std::move(buf), context);
}
void disconnect(std::thread::id id)
{
    Conductor::instance().disconnect(id);
}
} // namespace packer
