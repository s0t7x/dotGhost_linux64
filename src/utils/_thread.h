#pragma once

#include <atomic>
#include <chrono>
#include <thread>

class _thread {
    public:
        _thread();
        virtual ~_thread();
        _thread(_thread const &) = delete;
        void operator=(_thread const &) = delete;
        void Start();
        void Stop();

    protected:
        virtual void Run() = 0;
        void Log(const std::string &msg);
        void LogWait(const std::string &msg, size_t timeout = 1);
        inline void Wait(size_t timeout = 1) {
            std::this_thread::sleep_for(std::chrono::seconds(timeout));
        }
        inline void WaitMs(size_t timeout) {
            std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
        }
        inline bool ShouldStop() { return m_stop; }

    private:
        std::thread m_thread;
        std::atomic<bool> m_stop;
};
