#include "iprocessor.h"

void iProcessor::attach(Observer *o)
{
    std::lock_guard<std::mutex> lock(m_observersMutex);
    m_observers.push_back(o);
}

void iProcessor::detach(Observer *o)
{
    std::lock_guard<std::mutex> lock(m_observersMutex);
    m_observers.remove(o);
}
