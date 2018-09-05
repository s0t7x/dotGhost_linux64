#include "_thread.h"

#include <chrono>
#include <iostream>

_thread::_thread()
{
    m_stop = false;
}

_thread::~_thread()
{
    Stop();
}

void _thread::Start()
{
    Stop();
    m_stop = false;
    m_thread = std::thread(&_thread::Run, this);
}

void _thread::Stop()
{
    m_stop = true;
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

void _thread::Log(const std::string &msg)
{
    std::cout << msg << std::endl;
}

void _thread::LogWait(const std::string &msg, size_t timeout)
{
    Log(msg);
    Wait(timeout);
}

