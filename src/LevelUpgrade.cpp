#include "LevelUpgrade.h"
#include <iostream>

LevelUpgrade::LevelUpgrade() : Upgrade("Level Bonus Upgrade") {}

void LevelUpgrade::aplica(Player &player) {
    if (player.getLevelUpgradeUsed()) {
        throw std::runtime_error("Acest upgrade a fost deja folosit.");
    }

    if (player.getClicksTotal() >= 1000) {
        player.aplicaBonusLevelUpgrade();
        player.setLevelUpgradeUsed(true);
    } else {
        throw std::runtime_error("Nu ai suficient progres pentru acest upgrade.");
    }
}

std::unique_ptr<Upgrade> LevelUpgrade::clone() const {
    return std::make_unique<LevelUpgrade>(*this);
}



void LevelUpgrade::afiseaza() const {
    std::cout << ">> Level Upgrade: Se activează la 1000 clickuri totale\n";
}



