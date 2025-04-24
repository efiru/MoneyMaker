#include "DoubleTapUpgrade.h"
#include <iostream>

DoubleTapUpgrade::DoubleTapUpgrade(): Upgrade("DoubleTap"){}

void DoubleTapUpgrade::aplica(Player& player) {
    if (player.getCurrentBanknoteValue() > 1 && !player.getDoubleTap()) {
        player.activeazaDoubleTap();
        std::cout << "Upgrade aplicat: DoubleTap activat!\n";
    }
    else {
        std:: cout << "Nu poti activa DoubleTap.\n";
    }
}

std::unique_ptr<Upgrade> DoubleTapUpgrade::clone() const {
    return std::make_unique<DoubleTapUpgrade>(*this);
}

void DoubleTapUpgrade::afiseaza() const {
    std::cout << "Upgrade: DoubleTap - Activeaza click dublu pentru un timp limitat.\n";
}


