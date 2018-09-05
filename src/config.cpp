#include "config.h"

#include <fstream>
#include <iostream>

#include "utils/inih/INIReader.h"

constexpr char defConfigFile[] = "config.ini";

bool  Config::Glow::Enabled   = true;
bool  Config::Glow::Radar     = true;
bool  Config::Glow::LegitGlow = false;
bool  Config::Glow::GlowAllies = true;
bool  Config::Glow::GlowEnemies = true;
bool  Config::Glow::GlowOther   = false;
bool  Config::Glow::GlowWeapons = false;
float Config::Glow::EnemyR    = 0.8f;
float Config::Glow::EnemyG    = 0.8f;
float Config::Glow::EnemyB    = 0.0f;
float Config::Glow::EnemyA    = 0.8f;

float Config::Glow::AllyR     = 0.0f;
float Config::Glow::AllyG     = 0.8f;
float Config::Glow::AllyB     = 0.8f;
float Config::Glow::AllyA     = 0.8f;

#define WriteSection(key) \
    conf << "[" #key "]" << "\n";
#define WritePair(section, key) \
    conf << #key " = " << Config::section::key << "\n";
#define WriteSectionEnd() conf << "\n";
#define WriteComment(msg) conf << "; " << msg << '\n';

void UpdateConfig()
{
    std::ofstream conf(defConfigFile);
    if (conf.is_open()) {
        WriteSection(Glow);
        WritePair(Glow, Enabled);
        WritePair(Glow, Radar);
        WritePair(Glow, LegitGlow);
        WritePair(Glow, GlowAllies);
        WritePair(Glow, GlowEnemies);
        WritePair(Glow, GlowOther);
        WritePair(Glow, GlowWeapons);
        WritePair(Glow, EnemyR);
        WritePair(Glow, EnemyG);
        WritePair(Glow, EnemyB);
        WritePair(Glow, EnemyA);
        WritePair(Glow, AllyR);
        WritePair(Glow, AllyG);
        WritePair(Glow, AllyB);
        WritePair(Glow, AllyA);
        WriteSectionEnd();
    }
}

#define RCBOOL(section, key) \
    Config::section::key = reader.GetBoolean(#section, #key, Config::section::key);
#define RCSTR(section, key) \
    Config::section::key = reader.Get(#section, #key, Config::section::key);
#define RCDBL(section, key) \
    Config::section::key = reader.GetReal(#section, #key, Config::section::key);
#define RCINT(section, key) \
    Config::section::key = reader.GetInteger(#section, #key, Config::section::key);
bool ReadConfig(const std::string &configFile)
{
    INIReader reader(configFile);

    if (reader.ParseError() < 0) {
        UpdateConfig();
        return false;
    }

    RCBOOL(Glow, Enabled);
    RCBOOL(Glow, Radar);
    RCBOOL(Glow, LegitGlow);
    RCBOOL(Glow, GlowAllies);
    RCBOOL(Glow, GlowEnemies);
    RCBOOL(Glow, GlowOther);
    RCBOOL(Glow, GlowWeapons);
    RCDBL (Glow, EnemyR);
    RCDBL (Glow, EnemyG);
    RCDBL (Glow, EnemyB);
    RCDBL (Glow, EnemyA);
    RCDBL (Glow, AllyR);
    RCDBL (Glow, AllyG);
    RCDBL (Glow, AllyB);
    RCDBL (Glow, AllyA);
    
    UpdateConfig();
    return true;
}
