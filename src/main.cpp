#include "dotglow.h"
#include "dotaim.h"

#include "utils/cbaseentity.h"
#include "utils/cglowobjectmanager.h"
#include "utils/types.h"

#include "config.h"
#include "engine.h"
#include "globals.h"
#include "helper.h"
#include "offsets.h"
#include "process.h"

#include <chrono>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <thread>

#include <signal.h>
#include <unistd.h>

#define LOG(X) std::cout << X << std::flush
#define PRINT_VERSION std::cout << "dotghost_linux64 v0.4.2 \n" << std::flush

bool shouldQuit = false;

void exitHandle(int)
{
    shouldQuit = true;
}

void connectSignals(struct sigaction &handle)
{
    handle.sa_handler = exitHandle;
    sigemptyset(&handle.sa_mask);
    handle.sa_flags = 0;
    sigaction(SIGINT, &handle, NULL);
    sigaction(SIGQUIT, &handle, NULL);
}

int main()
{
    if (getuid() != 0) {
        LOG("This program must be ran as root.\n");
        return 0;
    }

    if (!Helper::Init()) {
        LOG("Failed to initialize input handling.\n");
        return 0;
    }
    
    struct sigaction ccHandle;
    connectSignals(ccHandle);
    
    Process proc(PROCESS_NAME);

    PRINT_VERSION;
    
    LOG("Waiting for process...");
    
    while (!proc.Attach() && !shouldQuit) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    LOG("Done.\nWaiting for client and engine library...");

    while (!shouldQuit) {
        proc.ParseModules();
        if (proc.HasModule(CLIENT_SO) && proc.HasModule(ENGINE_SO)) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    if (shouldQuit) {
        return 0;
    }

    ReadConfig("config.ini");

    LOG("Done.\n");
    Signatures::Find(proc);
    Signatures::Print(proc);

    auto& eng = Engine::GetInstance();
    eng.SetProcessManager(&proc);
    eng.Update(true);
    dotglow dotglow(proc);
    dotaim dotaim(proc);

    while (!shouldQuit) {
        if (!proc.IsValid()) {
            shouldQuit = true;
            LOG("Lost connection to process... Exiting.\n");
            break;
        }
        if (eng.IsConnected()) {
            dotglow.Start();
            dotaim.Start();

            while (eng.IsConnected() && !shouldQuit) {
                eng.Update();
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            dotglow.Stop();
            dotaim.Stop();
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    Helper::Finalize();
    return 0;
}
