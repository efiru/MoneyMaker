#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Bancnota.h"
#include "Player.h"
#include "Achievement.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <optional>
#include <nlohmann/json.hpp>
#include <fstream>
using json = nlohmann::json;


void to_json(json& j, const Player& p) {
    j = json{
            {"level", p.getLevel()},
            {"clicksCurent", p.getClicks()},
            {"clicksTotal", p.getClicksTotal()},
            {"banknote", p.getCurrentBanknoteValue()},
            {"doubleTap", p.getDoubleTap()},
               {"usedBanknoteUpgrade", p.getBanknoteUpgradeUsed()}
    };
}

void from_json(const json& j, Player& p) {
    int level = j.at("level").get<int>();
    int clicksCurent = j.at("clicksCurent").get<int>();
    int clicksTotal = j.at("clicksTotal").get<int>();
    int banknoteVal = j.at("banknote").get<int>();
    bool doubleTap = j.at("doubleTap").get<bool>();
    bool usedUpgrade = j.at("usedBanknoteUpgrade").get<bool>();
    p.setBanknoteUpgradeUsed(usedUpgrade);

    // Find the matching bancnote type by value
    bancnote tip = UN_LEU;
    for (const auto& pair : Valori) {
        if (pair.second == banknoteVal) {
            tip = pair.first;
            break;
        }
    }

    p = Player(level, clicksCurent, clicksTotal, Bancnota(tip), doubleTap);
}

void savePlayer(const Player& player, const std::string& filename = "player_save.json") {
    json j = player;
    std::ofstream file(filename);
    file << j.dump(4);  // pretty print with 4 spaces
}

bool loadPlayer(Player& player, const std::string& filename = "player_save.json") {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    json j;
    file >> j;
    player = j.get<Player>();
    return true;
}


int main() {
    // Fullscreen setup
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "MoneyMaker", sf::Style::Default);
    window.setFramerateLimit(60);

    // Load font
    sf::Font font;
    if (!font.openFromFile("assets/arial.ttf")) {
        std::cerr << "Eroare la încărcarea fontului\n";
        return 1;
    }

    // Game setup
    Game game;

    if (loadPlayer(game.getPlayer())) {
        std::cout << "✔️ Player loaded from save.\n";
    } else {
        std::cout << "⚠️ No save found. Starting fresh.\n";
    }

    // Title
    sf::Text title(font, " MoneyMaker ", 64);
    title.setFillColor(sf::Color::Cyan);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    title.setPosition({250.f, 40.f});

    // Menu options
    std::vector<std::string> options = {
        "0. Iesire ",
        "1. Arunca o bancnota ",
        "2. Activeaza DoubleTap ",
        "3. Starea Jucatorului ",
        "4. Verifica Achievements ",
        "5. Activeaza BanknoteUpgrade "
    };

    std::vector<sf::Text> menuItems;
    for (int i = 0; i < static_cast<int>(options.size()); ++i) {
        sf::Text item(font, options[i], 40);
        item.setFillColor(sf::Color::White);
        item.setPosition({100.f, 150.f + i * 80.f});
        menuItems.push_back(item);
    }

    // Logs
    std::vector<sf::Text> logs;
    auto addLog = [&](const std::string& message, sf::Color color = sf::Color::White) {
        sf::Text log(font, message, 28);
        log.setFillColor(color);
        logs.push_back(log);
        if (logs.size() > 6) logs.erase(logs.begin());
    };

    // HUD elements
    sf::Text levelText(font, "", 28);
    sf::Text progressText(font, "", 28);
    sf::Text doubleTapText(font, "", 28);
    sf::Text bancnotaText(font, "", 28);

    levelText.setFillColor(sf::Color::Green);
    progressText.setFillColor(sf::Color::Yellow);
    doubleTapText.setFillColor(sf::Color::Magenta);
    bancnotaText.setFillColor(sf::Color::Cyan);

    bool running = true;
    while (window.isOpen() && running) {
        // Update HUD every frame
        levelText.setString("Level: " + std::to_string(game.getPlayer().getLevel()));

        progressText.setString(
            "Clicks: " + std::to_string(game.getPlayer().getClicks()) +
            " / " + std::to_string(game.getPlayer().getCurrentClickLimit())
        );

        doubleTapText.setString("DoubleTap: " + std::string(game.getPlayer().getDoubleTap() ? "ON ⚡" : "OFF"));

        bancnotaText.setString(
            std::to_string(game.getPlayer().getCurrentBanknoteValue()) + " LEI"
        );

        float hudX = static_cast<float>(window.getSize().x) - 300.f;
        levelText.setPosition(sf::Vector2f(hudX, 30.f));
        progressText.setPosition(sf::Vector2f(hudX, 70.f));
        doubleTapText.setPosition(sf::Vector2f(hudX, 110.f));
        bancnotaText.setPosition(sf::Vector2f(hudX, 150.f));

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                running = false;
                break;
            }

            if (const auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseEvent->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos(mouseEvent->position);

                    for (int i = 0; i < static_cast<int>(menuItems.size()); ++i) {
                        if (menuItems[i].getGlobalBounds().contains(mousePos)) {
                            switch (i) {
                                case 0:
                                    running = false;
                                window.close();
                                break;
                                case 1: {
                                    int before = game.getPlayer().getClicksTotal();
                                    game.getPlayer().aruncaBancnota();
                                    int after = game.getPlayer().getClicksTotal();
                                    int diff = after - before;
                                    addLog("+" + std::to_string(diff), sf::Color::Green);
                                    break;
                                }
                                case 2: {
                                    bool before = game.getPlayer().getDoubleTap();
                                    game.getPlayer().activeazaDoubleTap();
                                    bool after = game.getPlayer().getDoubleTap();
                                    if (after && !before)
                                        addLog("DoubleTap ACTIVAT! ⚡", sf::Color::Yellow);
                                    else
                                        addLog("DoubleTap indisponibil 😕", sf::Color::Red);
                                    break;
                                }
                                case 3: {
                                    std::ostringstream oss;
                                    oss << game.getPlayer();
                                    addLog(oss.str(), sf::Color::Cyan);
                                    break;
                                }
                                case 4: {
                                    for (auto& ach : game.getAchievements()) {
                                        ach.checkUnlock(game.getPlayer());
                                        std::ostringstream oss;
                                        oss << ach;
                                        addLog(oss.str(), ach.isUnlocked() ? sf::Color::Green : sf::Color(150, 150, 150));
                                    }
                                    break;
                                }
                                case 5: {
                                    try {
                                        BanknoteUpgrade upgrade;
                                        upgrade.aplica(game.getPlayer());
                                        addLog("✅ BanknoteUpgrade activat! 🤑", sf::Color::Yellow);
                                    } catch (const std::exception& e) {
                                        addLog(std::string("❌ ") + e.what(), sf::Color::Red);
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        // Rendering
        window.clear(sf::Color(30, 30, 30));
        window.draw(title);

        for (auto& item : menuItems)
            window.draw(item);

        for (size_t i = 0; i < logs.size(); ++i) {
            logs[i].setPosition({50.f, static_cast<float>(window.getSize().y - 240 + i * 30)});
            window.draw(logs[i]);
        }

        // Draw HUD
        window.draw(levelText);
        window.draw(progressText);
        window.draw(doubleTapText);
        window.draw(bancnotaText);

        window.display();
    }

    savePlayer(game.getPlayer());
    std::cout << "💾 Player progress saved!\n";

    return 0;
}