#include "LevelUpgrade.h"
#include <iostream>

#include "UpgradeException.h"

LevelUpgrade::LevelUpgrade() : Upgrade("Level Bonus Upgrade") {}

void LevelUpgrade::aplica(Player &player) {
    if (player.getLevelUpgradeUsed()) {
        throw UpgradeAlreadyUsedException();
    }

    if (player.getClicksTotal() >= 300) {
        player.aplicaBonusLevelUpgrade();
        player.setLevelUpgradeUsed(true);
    } else {
        throw UpgradeRequirementException();
    }
}

std::unique_ptr<Upgrade> LevelUpgrade::clone() const {
    return std::make_unique<LevelUpgrade>(*this);
}



void LevelUpgrade::afiseaza() const {
    std::cout << ">> Level Upgrade: Se activează la 300 clickuri totale\n";
}



