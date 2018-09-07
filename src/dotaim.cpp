#include "dotaim.h"

#include "config.h"
#include "engine.h"
#include "helper.h"
#include "offsets.h"
#include "utils/mathlib.h"
#include "utils/types.h"
#include "utils/vector.h"
#include "utils/utils.h"

#include <cstdlib>
#include <cstdio>

bool dotaim::getBonePosition(uintptr_t ePtr, int bone, Vector *out) {
    matrix3x4_t mat;
    uintptr_t pBoneMatrix;
    if (!m_mem.Read(ePtr + Offset::Static::BoneMatrix, &pBoneMatrix)) {
        return false;
    }
    if (!m_mem.Read(pBoneMatrix + Offset::Static::BoneDistance * bone, &mat)) {
        return false;
    }
    out->x = mat[0][3];
    out->y = mat[1][3];
    out->z = mat[2][3];
    return true;
}

void dotaim::aim(uintptr_t localPlayer)
{
    Vector vecEyes;
    Vector vecEyesOffset;
    Vector viewAngle;
    Vector punchAngle;
    int localIndex;

    if (!m_mem.Read(localPlayer + Netvar::CBaseEntity::m_vecOrigin, &vecEyes)) {
        LogWait("Failed to read CBaseEntity::m_vecOrigin");
        return;
    }
    
    if (!m_mem.Read(localPlayer + Netvar::CBaseEntity::m_vecViewOffset, &vecEyesOffset)) {
        LogWait("Failed to read CBaseEntity::m_vecViewOffset");
        return;
    }
    
    if (!m_mem.Read(Offset::Engine::ClientState + Offset::Static::ViewAngles, &viewAngle)) {
        LogWait("Failed to read ClientState::ViewAngles");
        return;
    }

    if (!m_mem.Read(localPlayer + Netvar::CBasePlayer::Local::m_aimPunchAngle, &punchAngle)) {
        LogWait("Failed to read CBasePlayer::Local::m_aimPunchAngle");
        return;
    }

    if (!m_mem.Read(localPlayer + Netvar::CBaseEntity::index, &localIndex)) {
        LogWait("Failed to read CBaseEntity::index");
        return;
    }

    vecEyes += vecEyesOffset;
    float bestVal = FLT_MAX;
    Vector bestTarget;
    
    CEntInfo entInfo;
    if (!m_mem.Read(Offset::Client::EntityList, &entInfo)) {
        LogWait("Failed to read initial EntityList");
        return;
    }

    bool firstRead = true;
    
    while (entInfo.m_pNext != NULL) {
        if (!firstRead) {
            if (!m_mem.Read(entInfo.m_pNext, &entInfo)) {
                LogWait("Failed to update EntityList");
            }
        }
        firstRead = false;
        if (entInfo.m_pEntity == 0) {
            continue;
        }
        CBaseEntity ent;
        if (!m_mem.Read(entInfo.m_pEntity, &ent)) {
            continue;
        }

        int pTeam;
        if (!m_mem.Read(localPlayer + Netvar::CBaseEntity::m_iTeamNum, &pTeam)) {
            continue;
        }

        if (ent.index == localIndex) {
            continue;
        }

        if (ent.m_iTeamNum != TEAM_T && ent.m_iTeamNum != TEAM_CT) {
            continue;
        }

        if (ent.m_iTeamNum == pTeam) {
            continue;
        }

        if (ent.m_iHealth < 1) {
            continue;
        }

        Vector hitbox;
        if (!getBonePosition(entInfo.m_pEntity, Config::AimBot::TargetBone, &hitbox)) {
            continue;
        }
        float fov = utils::GetFov(viewAngle, vecEyes, hitbox);
        if (std::abs(fov) > Config::AimBot::FOV) {
            continue;
        }
        if (fov < bestVal) {
            bestVal = fov;
            bestTarget = hitbox;
        }
    }

    if (bestTarget.x != 0.f) {
        vecEyes -= bestTarget;
        vecEyes.NormalizeInPlace();
        Vector anglesDir = utils::VectorAngles(vecEyes);
        Vector clampedDir = utils::ClampAngle(anglesDir);
        Vector diffAngles = utils::ClampAngle(viewAngle - clampedDir + punchAngle);

        float aimSpeed = 2;
        float aimCorrection = 1.f;
        Vector out = utils::ClampAim(diffAngles, aimSpeed, aimCorrection);
        viewAngle -= out;
        m_mem.Write(Offset::Engine::ClientState + Offset::Static::ViewAngles, viewAngle);
        }
}

void dotaim::Run() {
    
    Log("aimbot started");

    while (!ShouldStop()) {
        uintptr_t localPlayer;
        if (!m_mem.Read(Offset::Client::LocalPlayer, &localPlayer)) {
            continue;
        }

        int myTeam;
        if (!m_mem.Read(localPlayer + Netvar::CBaseEntity::m_iTeamNum, &myTeam)) {
            WaitMs(20);
            continue;
        }

        if (Config::AimBot::Enabled && active) {
            this->aim(localPlayer);
        }

        WaitMs(1);
    }
    Log("aimbot stopped");
}