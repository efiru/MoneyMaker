#include "Game.h"
#include "DoubleTapUpgrade.h"
#include "LevelUpgrade.h"
#include "BanknoteUpgrade.h"
#include <iostream>
#include <memory>

#include "UltraUpgrade.h"

Game::Game() : achievements({
    {"Click Master", "Ai dat 500 de clicks!"},
    {"Intermediate", "Ai ajuns la nivelul 3!"},
    {"Investor", "Ai activat DoubleTap!"}
}) {
    initUpgrades();
}

void Game::initUpgrades() {
    upgrades.push_back(std::make_unique<DoubleTapUpgrade>());
    upgrades.push_back(std::make_unique<LevelUpgrade>());
    upgrades.push_back(std::make_unique<BanknoteUpgrade>());
    upgrades.push_back(std::make_unique<UltraUpgrade>());

}

void Game::activeazaToateUpgradeurile() {
    for (const auto& upgrade : upgrades) {
        try {
            upgrade->aplica(player);

            if (auto* dbl = dynamic_cast<DoubleTapUpgrade*>(upgrade.get())) {
                std::cout << "[Upgrade Info] Activat DoubleTapUpgrade\n";
            } else if (auto* lvl = dynamic_cast<LevelUpgrade*>(upgrade.get())) {
                std::cout << "[Upgrade Info] Activat LevelUpgrade\n";
            } else if (auto* bnk = dynamic_cast<BanknoteUpgrade*>(upgrade.get())) {
                std::cout << "[Upgrade Info] Activat BanknoteUpgrade\n";
            }

        } catch (const std::exception& e) {
            std::cout << "❌ Upgrade eșuat: " << e.what() << "\n";
        }
    }
}

void Game::afiseazaMeniu() const {
    std::cout << "\n=== MENIU ===\n";
    std::cout << "1. Arunca o bancnota\n";
    std::cout << "2. Activeaza DoubleTap (downgrade bancnota)\n";
    std::cout << "3. Afiseaza starea jucatorului\n";
    std::cout << "4. Verifica Achievements\n";
    std::cout << "5. Activeaza LevelUpgrade (bonus la 1000 clickuri totale)\n";
    std::cout << "6. Activeaza BanknoteUpgrade (cost 250 clicks)\n";
    std::cout << "7. Activeaza toate upgrade-urile disponibile\n";
    std::cout << "8. Activeaza UltraUpgrade (x/3)";
    std::cout << "0. Iesire\n";
    std::cout << "Introdu optiunea: ";
}

void Game::proceseazaOptiune(int optiune) {
    switch (optiune) {
        case 1:
            player.aruncaBancnota();
            break;
        case 2: {
            DoubleTapUpgrade upgrade;
            upgrade.aplica(player);
            break;
        }
        case 3:
            std::cout << player << '\n';
            break;
        case 4:
            for (auto& ach : achievements) {
                ach.checkUnlock(player);
                std::cout << ach << '\n';
            }
            break;
        case 5: {
            LevelUpgrade upgrade;
            upgrade.aplica(player);
            break;
        }
        case 6: {
            try {
                BanknoteUpgrade upgrade;
                upgrade.aplica(player);
                std::cout << "BanknoteUpgrade activat! Ai primit o bancnota de 50 LEI.\n";
            } catch (const std::exception& e) {
                std::cout << "Eroare: " << e.what() << '\n';
            }
            break;
        }
        case 7: {
            activeazaToateUpgradeurile();
            break;
        }
        case 0:
            std::cout << "Iesire...\n";
            running = false;
            break;
        default:
            std::cout << "Optiune invalida.\n";
    }
}

void Game::run() {
    while (running) {
        afiseazaMeniu();
        int optiune;
        std::cin >> optiune;
        std::cin.ignore();
        proceseazaOptiune(optiune);
    }
}

void Game::set_player(const Player& player) {
    this->player = player;
}

Player& Game::getPlayer() {
    return player;
}

std::vector<Achievement>& Game::getAchievements() {
    return achievements;
}