#include "UltraUpgrade.h"
#include <iostream>
#include <stdexcept>
#include "Player.h"
#include "UpgradeException.h"

UltraUpgrade::UltraUpgrade() : Upgrade("Ultra Upgrade"), activat(false) {}

void UltraUpgrade::aplica(Player& player) {
    if (activat)
        throw UpgradeAlreadyUsedException();

    if (!player.getDoubleTap() || !player.getLevelUpgradeUsed() || !player.getBanknoteUpgradeUsed())
        throw UpgradeRequirementException();

    if (player.getLevel() < 5)
        throw UpgradeInsufficientClicksException();

    player.setBancnota(Bancnota(CINCI_SUTE_LEI));
    activat = true;
    std::cout << "[ULTRA UPGRADE] Ai primit bancnota de 500 de lei.Felicitari , ai terminat jocul!\n";
}

std::unique_ptr<Upgrade> UltraUpgrade::clone() const {
    return std::make_unique<UltraUpgrade>(*this);
}

void UltraUpgrade::afiseaza() const {
    std::cout << "UltraUpgrade - Activabil doar dacă ai toate celelalte upgrade-uri + nivel 5. Acordă +3 niveluri și 500 LEI bancnotă.\n";
}