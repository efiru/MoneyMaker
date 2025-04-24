#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "Player.h"
#include "Achievement.h"
#include "Upgrade.h"

class Game {
private:
    Player player;
    std::vector<Achievement> achievements;
    bool running = true;

    std::vector<std::unique_ptr<Upgrade>> upgrades;

    void afiseazaMeniu() const;
    void proceseazaOptiune(int optiune);
    void initUpgrades();

public:
    Game();
    void run();

    void set_player(const Player& player);
    Player& getPlayer();
    std::vector<Achievement>& getAchievements();
    void activeazaToateUpgradeurile();
};

#endif