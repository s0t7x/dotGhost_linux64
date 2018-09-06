#include "config.h"

#include <fstream>
#include <iostream>

#include "utils/inih/INIReader.h"

constexpr char defConfigFile[] = "config.ini";

bool  Config::Glow::Enabled   = true;
bool  Config::Glow::Radar     = true;
float Config::Glow::EnemyR    = 1.0f;
float Config::Glow::EnemyG    = 0.0f;
float Config::Glow::EnemyB    = 0.0f;
float Config::Glow::EnemyA    = 0.8f;
float Config::Glow::AllyR     = 0.0f;
float Config::Glow::AllyG     = 0.0f;
float Config::Glow::AllyB     = 0.1f;
float Config::Glow::AllyA     = 0.8f;

bool Config::AimBot::Enabled    = true;
int Config::AimBot::TargetBone  = 8;
int Config::AimBot::FOV         = 40;
bool Config::AimBot::Mode       = 1;
std::string Config::AimBot::Key = "v";

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
        WriteComment("dotghost_linux64");
        WriteSectionEnd();

        WriteSection(Glow);
        WritePair(Glow, Enabled);
        WritePair(Glow, Radar);
        WritePair(Glow, EnemyR);
        WritePair(Glow, EnemyG);
        WritePair(Glow, EnemyB);
        WritePair(Glow, EnemyA);
        WritePair(Glow, AllyR);
        WritePair(Glow, AllyG);
        WritePair(Glow, AllyB);
        WritePair(Glow, AllyA);
        WriteSectionEnd();

        WriteSection(AimBot);
        WritePair(AimBot, Enabled);
        WritePair(AimBot, TargetBone);
        WritePair(AimBot, FOV);
        WritePair(AimBot, Mode);
        WritePair(AimBot, Key);
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
    RCDBL (Glow, EnemyR);
    RCDBL (Glow, EnemyG);
    RCDBL (Glow, EnemyB);
    RCDBL (Glow, EnemyA);
    RCDBL (Glow, AllyR);
    RCDBL (Glow, AllyG);
    RCDBL (Glow, AllyB);
    RCDBL (Glow, AllyA);

    RCBOOL(AimBot, Enabled);
    RCINT(AimBot, TargetBone);
    RCINT(AimBot, FOV);
    RCBOOL(AimBot, Mode);
    RCSTR(AimBot, Key);
    
    UpdateConfig();
    return true;
}
