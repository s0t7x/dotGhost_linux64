#pragma once

#include "process.h"
#include "utils/_thread.h"

class dotglow final : public _thread {
    Process &m_mem;
    public:
        dotglow(Process &mem) : m_mem(mem) {};
    protected:
        void Run();
    private:
        void Radar(uintptr_t entPtr, int lTeam, int rTeam);
};
