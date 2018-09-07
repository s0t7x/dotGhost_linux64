#include "dottrigger.h"

#include "utils/cbaseentity.h"
#include "config.h"
#include "offsets.h"
#include "helper.h"
#include "engine.h"

#include <cstdio>
#include <cstdlib>
#include <X11/Xlib.h>

#include <chrono>

void dottrigger::trigger(uintptr_t localPlayer){
    auto &eng = Engine::GetInstance();
    int pTeam;
    if (!m_mem.Read(localPlayer + Netvar::CBaseEntity::m_iTeamNum, &pTeam)){
        return;
    }

   
int inCrossID;
            if (!m_mem.Read(localPlayer + Netvar::CBasePlayer::m_iCrosshairID, &inCrossID)) {
                return;
            }

            if (inCrossID > 0 && inCrossID < 65) {
                CBaseEntity ent;
                if (!eng.GetEntityById(inCrossID, &ent)) {
                    return;
                }
                if (ent.m_iHealth > 0) {
                    if (ent.m_iTeamNum != pTeam) {
                        eng.ForceAttack(true);
                        WaitMs(10);
                        eng.ForceAttack(false);
                    }
                }
            }    
}

void dottrigger::Run(){
    if(!Config::AimBot::TriggerBot){
        return;
    }
    
    Log("trigger activated");

    while(!ShouldStop()){
        uintptr_t localPlayer;
        if (!m_mem.Read(Offset::Client::LocalPlayer, &localPlayer)) {
            continue;
        }
        if(active) {
            this->trigger(localPlayer);
        }
        WaitMs(10);
    }
    Log("trigger deactivated");
}