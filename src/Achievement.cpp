#include "Achievement.h"
#include <iostream>

// Definition of external maps
std::map<AchievementType, int> Prag{
        {CLICKS, 500},
        {LEVEL, 3},
        {DOUBLE_TAP, 1},
    };

std::map<std::string, AchievementType> achievementType{
        {"Click Master", CLICKS},
        {"Intermediate", LEVEL},
        {"Investor", DOUBLE_TAP}
};

Achievement::Achievement(const std::string& n, const std::string& d)
    : nume(n), descriere(d), tip(achievementType.at(n)), prag(Prag.at(tip)) {}

void Achievement::checkUnlock(const Player& p) {
    if (activat) return;
    switch (tip) {
        case CLICKS:
            if (p.getClicksTotal() >= prag) activat = true;
        break;
        case LEVEL:
            if (p.getLevel() >= prag) activat = true;
        break;
        case DOUBLE_TAP:
            if (p.getDoubleTap()) activat = true;
        break;
    }
}

bool Achievement::isUnlocked() const {
    return activat;
}

std::ostream& operator<<(std::ostream& os, const Achievement& a) {
    os << "Achievement: " << a.nume << " - " << a.descriere
       << " [" << (a.activat ? "UNLOCKED" : "LOCKED") << "]";
    return os;
}