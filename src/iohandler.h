#ifndef IOHANDLER_H
#define IOHANDLER_H
#include <string>
#include <thread>
#include <unordered_map>
#include <mutex>

#include "printers.h"
class CommandThread;

class IOHandler : public std::enable_shared_from_this<IOHandler>
{
public:
    IOHandler() = default;
    ~IOHandler();

    std::thread::id connect(const size_t bulkSize);
    void recieve(std::string &&buf, std::thread::id context);
    void disconnect(std::thread::id id);

private:
    std::unordered_map<std::thread::id, CommandThread *> threads;
    std::mutex m_mutex;
};

//-----------------CommandThread--------------------------
class CommandThread
{
public:
    CommandThread(std::shared_ptr<IOHandler> ptr, const size_t bulkSize);
    ~CommandThread();

    void feed(std::string &&data);
    std::thread::id id() const
    {
        return m_workerThread.get_id();
    };

private:
    std::unique_ptr<CommandProcessor> processor;
    std::shared_ptr<IOHandler> m_ptr;

    std::thread t1;
    std::thread t2;
    std::thread t3;
    std::thread m_workerThread;

    void wait();
};

#endif // IOHANDLER_H
