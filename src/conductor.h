#ifndef CONDUCTOR_H
#define CONDUCTOR_H
#include "iohandler.h"

class Conductor
{
public:
    static Conductor &instance();
    std::thread::id connect(const size_t bulkSize);
    void recieve(std::string &&buf, std::thread::id context);
    void disconnect(std::thread::id id);

private:
    Conductor() : iohandler(new IOHandler()) { }
    std::shared_ptr<IOHandler> iohandler;

public:
    Conductor(Conductor const &) = delete;
    void operator=(Conductor const &) = delete;
};

#endif // CONDUCTOR_H
