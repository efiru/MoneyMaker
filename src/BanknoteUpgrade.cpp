#include "BanknoteUpgrade.h"
#include "Bancnota.h"
#include <iostream>
#include <stdexcept>
#include "UpgradeException.h"


BanknoteUpgrade::BanknoteUpgrade()
    : Upgrade("Banknote Upgrade"), folosita(false) {}

void BanknoteUpgrade::aplica(Player& player) {
    if (folosita) {
        throw UpgradeAlreadyUsedException();
    }

    if (player.getBanknoteUpgradeUsed()) {
        throw UpgradeAlreadyUsedException();
    }

    if (player.getClicksTotal() < 250) {
        throw UpgradeInsufficientClicksException();
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