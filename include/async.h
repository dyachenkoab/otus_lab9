#ifndef ASYNC_H
#define ASYNC_H
#include <thread>
#include <string>

namespace packer {
std::thread::id connect(const size_t bulkSize);
void recieve(std::string &&buf, std::thread::id context);
void disconnect(std::thread::id id);
} // namespace packer

#endif // ASYNC
