#ifndef IPROCESSOR_H
#define IPROCESSOR_H
#include "observer.h"
#include <list>
#include <mutex>
class iProcessor
{
public:
    virtual ~iProcessor() {};
    virtual void attach(Observer *o);
    virtual void detach(Observer *o);

protected:
    iProcessor() = default;

private:
    std::list<Observer*> m_observers;
    std::mutex m_observersMutex;
};

#endif // IPROCESSOR_H
