#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Achievement.h"

class Game {
private:
    Player player;
    std::vector<Achievement> achievements;
    bool running = true;

    void afiseazaMeniu() const;
    void proceseazaOptiune(int optiune);

public:
    Game();
    void run();

    void set_player(const Player& player);
    Player& getPlayer();
    std::vector<Achievement>& getAchievements();
};

#endif