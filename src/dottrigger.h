#pragma once

#include "engine.h"
#include "utils/types.h"
#include "utils/vector.h"
#include "process.h"
#include "utils/_thread.h"
#include <chrono>

class dottrigger : public _thread {
    Process &m_mem;
    public:
    dottrigger(Process &mem) : m_mem(mem)
    { 
    }
    protected:
    void Run();
};