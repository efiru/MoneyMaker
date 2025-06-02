#ifndef ACHIEVEMENT_OBSERVER_H
#define ACHIEVEMENT_OBSERVER_H

#include "Observer.h"
#include "Player.h"
#include "Achievement.h"
#include <vector>
#include <iostream>

class AchievementObserver : public Observer {
private:
    std::vector<Achievement>& achievements;

public:
    explicit AchievementObserver(std::vector<Achievement>& achievements)
        : achievements(achievements) {}

    void update(const Player& player) override {
        std::cout << "[DEBUG] AchievementObserver triggered\n";
        for (auto& ach : achievements) {
            bool before = ach.isUnlocked();
            ach.checkUnlock(player);
            if (!before && ach.isUnlocked()) {
                std::cout << "[Achievement deblocat] " << ach << "\n";
            }
        }
    }
};

#endif