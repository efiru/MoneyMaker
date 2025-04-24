#include "LevelUpgrade.h"
#include <iostream>

LevelUpgrade::LevelUpgrade(): Upgrade("Level Bonus Upgrade") {}

void LevelUpgrade::aplica(Player &player) {
    if (player.getClicksTotal() >= 1000) {
        std:: cout << "[Level Bonus Upgrade] Bonus Aplicat!\n";
        player.aplicaBonusLevelUpgrade();
    }
    else {
        std::cout << "[LevelUpgrade] Nu ai suficient progres pentru acest upgrade.\n";
    }
}

std::unique_ptr<Upgrade> LevelUpgrade::clone() const {
    return std::make_unique<LevelUpgrade>(*this);
}

void LevelUpgrade::afiseaza() const {
    std::cout << ">> Level Upgrade: Se activează la 1000 clickuri totale\n";
}



