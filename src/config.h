#pragma once

#include <string>

bool ReadConfig(const std::string &configFile);

namespace Config {
    namespace Glow {
        extern bool  Enabled;
        extern bool  Radar;
        extern float EnemyR;
        extern float EnemyG;
        extern float EnemyB;
        extern float EnemyA;
        extern float AllyR;
        extern float AllyG;
        extern float AllyB;
        extern float AllyA;
    };

    namespace AimBot {
        extern bool Enabled;
        extern bool TriggerBot;
        extern int TargetBone;
        extern int FOV;
        extern bool Mode;
        extern std::string Key;
    }
};

