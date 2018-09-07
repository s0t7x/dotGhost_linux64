#pragma once

#include "utils/types.h"
#include "utils/vector.h"
#include "process.h"
#include "utils/_thread.h"
#include <chrono>

class dotaim : public _thread {
    Process &m_mem;
    public:
    dotaim(Process &mem) : m_mem(mem)
    { 
    }
    bool active = true;
    protected:
    void Run();

    private:
    void aim(uintptr_t localPlayer);
    bool getBonePosition(uintptr_t ePtr, int bone, Vector *out);
};