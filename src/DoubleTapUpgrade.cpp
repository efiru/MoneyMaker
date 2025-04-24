#include "DoubleTapUpgrade.h"
#include <iostream>

DoubleTapUpgrade::DoubleTapUpgrade(): Upgrade("DoubleTap"){}

void DoubleTapUpgrade::aplica(Player& player) {
    if (player.getDoubleTap()) {
        throw std::runtime_error("DoubleTap este deja activat.");
    }

    if (player.getCurrentBanknoteValue() <= 1) {
        throw std::runtime_error("Nu poti activa DoubleTap cu o bancnota de 1 leu.");
    }

    player.activeazaDoubleTap();
}

std::unique_ptr<Upgrade> DoubleTapUpgrade::clone() const {
    return std::make_unique<DoubleTapUpgrade>(*this);
}

void DoubleTapUpgrade::afiseaza() const {
    std::cout << "Upgrade: DoubleTap - Activeaza click dublu pentru un timp limitat.\n";
}


