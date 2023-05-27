#include <thread>
#include <string>
#include "conductor.h"

namespace packer {
size_t connect(const size_t bulkSize)
{
    return Conductor::instance().connect(bulkSize);
}
void recieve(std::string &&buf, const size_t context)
{
    Conductor::instance().recieve(std::move(buf), context);
}
void disconnect(const size_t id)
{
    Conductor::instance().disconnect(id);
}
} // namespace packer
