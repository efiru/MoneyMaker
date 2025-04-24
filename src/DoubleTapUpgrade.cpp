#include "DoubleTapUpgrade.h"
#include <iostream>

#include "UpgradeException.h"

DoubleTapUpgrade::DoubleTapUpgrade(): Upgrade("DoubleTap"){}

void DoubleTapUpgrade::aplica(Player& player) {
    if (player.getDoubleTap()) {
        throw UpgradeAlreadyUsedException();
    }

    if (player.getCurrentBanknoteValue() <= 1) {
        throw UpgradeRequirementException();
    }

    player.activeazaDoubleTap();
}

std::unique_ptr<Upgrade> DoubleTapUpgrade::clone() const {
    return std::make_unique<DoubleTapUpgrade>(*this);
}

void DoubleTapUpgrade::afiseaza() const {
    std::cout << "Upgrade: DoubleTap - Activeaza click dublu pentru un timp limitat.\n";
}


