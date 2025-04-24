#include "BanknoteUpgrade.h"
#include "Bancnota.h"
#include <iostream>
#include <stdexcept>

BanknoteUpgrade::BanknoteUpgrade()
    : Upgrade("Banknote Upgrade"), folosita(false) {}

void BanknoteUpgrade::aplica(Player& player) {
    if (folosita) {
        throw std::runtime_error("Acest upgrade a fost deja folosit!");
    }

    if (player.getBanknoteUpgradeUsed()) {
        throw std::runtime_error("Acest upgrade a fost deja activat!");
    }

    if (player.getClicksTotal() < 250) {
        throw std::runtime_error("Ai nevoie de 250 clickuri totale pentru a activa acest upgrade!");
    }

    player.setBancnota(Bancnota(CINCIZECI_LEI));
    player.setBanknoteUpgradeUsed(true);

    player.setBancnota(Bancnota(CINCIZECI_LEI));
    folosita = true;
}

std::unique_ptr<Upgrade> BanknoteUpgrade::clone() const {
    return std::make_unique<BanknoteUpgrade>(*this);
}

void BanknoteUpgrade::afiseaza() const {
    std::cout << nume << " (necesită 250 clickuri totale, utilizabil o singură dată)\n";
}