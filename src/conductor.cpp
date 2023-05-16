#include "conductor.h"

Conductor &Conductor::instance()
{
    static Conductor instance;
    return instance;
}

std::thread::id Conductor::connect(const size_t bulkSize)
{
    return iohandler->connect(bulkSize);
}

void Conductor::recieve(std::string &&buf, std::thread::id context)
{
    iohandler->recieve(std::move(buf), context);
}

void Conductor::disconnect(std::thread::id id)
{
    iohandler->disconnect(id);
}
