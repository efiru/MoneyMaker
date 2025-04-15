#include "Game.h"
#include <iostream>

Game::Game() : achievements({
    {"Click Master", "Ai dat 500 de clicks!"},
    {"Intermediate", "Ai ajuns la nivelul 3!"},
    {"Investor", "Ai activat DoubleTap!"}
}) {}

void Game::afiseazaMeniu() const {
    std::cout << "\n=== MENIU ===\n";
    std::cout << "1. Arunca o bancnota\n";
    std::cout << "2. Activeaza DoubleTap (downgrade bancnota)\n";
    std::cout << "3. Afiseaza starea jucatorului\n";
    std::cout << "4. Verifica Achievements\n";
    std::cout << "0. Iesire\n";
    std::cout << "Introdu optiunea: ";
}

void Game::proceseazaOptiune(int optiune) {
    switch (optiune) {
        case 1:
            player.aruncaBancnota();
        break;
        case 2:
            player.activeazaDoubleTap();
        break;
        case 3:
            std::cout << player << '\n';
        break;
        case 4:
            for (auto& ach : achievements) {
                ach.checkUnlock(player);
                std::cout << ach << '\n';
            }
        break;
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