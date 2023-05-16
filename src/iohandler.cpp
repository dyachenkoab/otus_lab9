#include "iohandler.h"

IOHandler::~IOHandler()
{
    for (auto &[_, x] : threads) {
        x->feed("");
        delete x;
    }
    threads.erase(threads.begin(), threads.end());
}

std::thread::id IOHandler::connect(const size_t bulkSize)
{
    std::unique_lock { m_mutex };
    auto commandThread = new CommandThread(shared_from_this(), bulkSize);
    auto id = commandThread->id();
    threads[id] = commandThread;
    return id;
}

void IOHandler::recieve(std::string &&buf, std::thread::id id)
{
    std::unique_lock { m_mutex };
    threads.at(id)->feed(std::move(buf));
}

void IOHandler::disconnect(std::thread::id id)
{
    std::unique_lock { m_mutex };
    threads.at(id)->feed("");
    delete threads.at(id);
    threads.erase(id);
}

//----------------------CommandThread----------------------------------
CommandThread::CommandThread(std::shared_ptr<IOHandler> ptr, const size_t bulkSize) : m_ptr(ptr)
{
    processor.reset(new CommandProcessor("{", "}", bulkSize > 0 ? bulkSize : 3));
    ConsolePrinter printer(*processor);
    FilePrinter fPrinter(*processor);
    FilePrinter fPrinter1(*processor);

    t1 = std::thread(&ConsolePrinter::update, printer);
    t2 = std::thread(&FilePrinter::update, fPrinter);
    t3 = std::thread(&FilePrinter::update, fPrinter1);

    m_workerThread = std::thread(&CommandThread::wait, this);
}

CommandThread::~CommandThread()
{
    m_workerThread.join();
}

void CommandThread::feed(std::string &&data)
{
    if (processor)
        processor->push(std::move(data));
}

void CommandThread::wait()
{
    t1.join();
    t2.join();
    t3.join();
}
