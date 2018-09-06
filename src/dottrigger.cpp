#include "dottrigger.h"
#include "engine.h"
#include "utils/cbaseentity.h"
#include "utils/types.h"
#include "config.h"
#include "offsets.h"
#include "utils/_thread.h"
#include "helper.h"

#include <chrono>

void dottrigger::Run(){
    const int triggerKey = Helper::StringToKeycode(Config::AimBot::Key);

    while(!ShouldStop()){
        uintptr_t localPlayer;
        if (!m_mem.Read(Offset::Client::LocalPlayer, &localPlayer)) {
            continue;
        }

        int crosshairId;
        if (!m_mem.Read(localPlayer + Netvar::CBasePlayer::m_iCrosshairID ,&crosshairId)) {
            WaitMs(20);
            continue;
        }

        CBaseEntity e;
        auto& eng = Engine::GetInstance();
        if (!eng.GetEntityById(crosshairId, &e)){
            continue;
        }

        bool mode = true;
        if (Config::AimBot::Mode) {
            mode = Helper::IsKeyDown(triggerKey);
        }

        if (Config::AimBot::TriggerBot && mode) {
            int pTeam;
            if (!m_mem.Read(localPlayer + Netvar::CBaseEntity::m_iTeamNum, &pTeam)){
                continue;
            }
            int eTeam = e.m_iTeamNum;
            if ( pTeam != eTeam ){
                m_mem.Write(Offset::Client::ForceAttack, true, sizeof(bool));
                WaitMs(40);
            }
        }
    }
}