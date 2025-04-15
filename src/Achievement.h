#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <string>
#include <map>
#include "Player.h"

enum AchievementType {
    CLICKS,
    LEVEL,
    DOUBLE_TAP
};

extern std::map<AchievementType, int> Prag;
extern std::map<std::string, AchievementType> achievementType;

class Achievement {
private:
    std::string nume;
    std::string descriere;
    AchievementType tip;
    int prag;
    bool activat = false;

public:
    Achievement(const std::string& n, const std::string& d);
    void checkUnlock(const Player& p);
    [[nodiscard]] bool isUnlocked() const;
    friend std::ostream& operator<<(std::ostream& os, const Achievement& a);
};

#endif