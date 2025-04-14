#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>
#include <optional>

enum bancnote {
    UN_LEU,
    CINCI_LEI,
    ZECE_LEI,
    DOUAZECI_LEI,
    CINCIZECI_LEI,
    O_SUTA_LEI,
    DOUA_SUTE_LEI,
    CINCI_SUTE_LEI,
};

std::map<bancnote, int> Valori{
    {UN_LEU, 1},
    {CINCI_LEI, 5},
    {ZECE_LEI, 10},
    {DOUAZECI_LEI, 20},
    {CINCIZECI_LEI, 50},
    {O_SUTA_LEI, 100},
    {DOUA_SUTE_LEI, 200},
    {CINCI_SUTE_LEI, 500}
};

std::vector<bancnote> ordineBancnote = { UN_LEU, CINCI_LEI, ZECE_LEI, DOUAZECI_LEI, CINCIZECI_LEI, O_SUTA_LEI, DOUA_SUTE_LEI, CINCI_SUTE_LEI };

enum AchievementType {
    CLICKS,
    LEVEL,
    DOUBLE_TAP
};

std::map<AchievementType, int> Prag{
    {CLICKS, 500},
    {LEVEL, 3},
    {DOUBLE_TAP, 1},
};

std::map<std::string, AchievementType> achievementType{
    {"Click Master", CLICKS},
    {"Intermediate", LEVEL},
    {"Investor", DOUBLE_TAP}
};

class Bancnota {
private:
    bancnote tip;
public:
    Bancnota() : tip(UN_LEU) {}
    explicit Bancnota(bancnote tip) : tip{tip} {}
    [[nodiscard]] int valoare1() const {
        return Valori.at(tip);
    }
    [[maybe_unused]] void set_valoare(bancnote tipNou) {
        tip = tipNou;
    }
    Bancnota(const Bancnota& other) : tip(other.tip) {}
    Bancnota& operator=(const Bancnota& other) {
        if (this != &other) {
            tip = other.tip;
        }
        return *this;
    }
    ~Bancnota() = default;
    void upgrade(const int nr_upgrades) {
        auto it = std::find(ordineBancnote.begin(), ordineBancnote.end(), tip);
        if (it != ordineBancnote.end()) {
            int index = std::distance(ordineBancnote.begin(), it);
            index = std::min(index + nr_upgrades, static_cast<int>(ordineBancnote.size() - 1));
            tip = ordineBancnote[index];
        }
    }
    void downgrade(const int nr_downgrades) {
        auto it = std::find(ordineBancnote.begin(), ordineBancnote.end(), tip);
        if (it != ordineBancnote.end()) {
            int index = std::distance(ordineBancnote.begin(), it);
            index = std::max(index - nr_downgrades, 0);
            tip = ordineBancnote[index];
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const Bancnota& b) {
        os << "Bancnota: " << Valori.at(b.tip) << " LEI";
        return os;
    }
    int operator+(const Bancnota& other) const {
        return this->valoare1() + other.valoare1();
    }
    int operator-(const Bancnota& other) const {
        return this->valoare1() - other.valoare1();
    }
    bool operator<(const Bancnota& other) const {
        return this->valoare1() < other.valoare1();
    }
    bool operator>(const Bancnota& other) const {
        return this->valoare1() > other.valoare1();
    }
    bool operator<=(const Bancnota& other) const {
        return this->valoare1() <= other.valoare1();
    }
    bool operator>=(const Bancnota& other) const {
        return this->valoare1() >= other.valoare1();
    }
    bool operator==(const Bancnota& other) const {
        return this->valoare1() == other.valoare1();
    }
    bool operator!=(const Bancnota& other) const {
        return this->valoare1() != other.valoare1();
    }
};

class Player {
private:
    Bancnota bancnotaCurenta;
    int clicksCurent = 0;
    int clicksTotal = 0;
    int level = 1;
    int clicksToUpgrade = 10;
    bool doubleTapUnlocked = false;
    int doubleTapUpgradeCounter = 0;
    bool posibilUpgrade() const {
        return clicksCurent >= clicksToUpgrade;
    }
    void aplicaUpgrade() {
        bancnotaCurenta.upgrade(1);
        level++;
        clicksCurent = 0;
        clicksToUpgrade = bancnotaCurenta.valoare1() * 10;
        if (doubleTapUnlocked) {
            doubleTapUpgradeCounter++;
            if (doubleTapUpgradeCounter >= 2) {
                dezactiveazaDoubleTap();
            }
        }
    }
public:
    Player() : bancnotaCurenta(UN_LEU) {}
    Player(int level, int clicksCurent, int clicksTotal, Bancnota tipBancnota, bool doubleTap)
        : bancnotaCurenta(tipBancnota),
          clicksCurent(clicksCurent),
          clicksTotal(clicksTotal),
          level(level),
          clicksToUpgrade(tipBancnota.valoare1() * 10),
          doubleTapUnlocked(doubleTap) {}
    ~Player() = default;
    void aruncaBancnota() {
        if (doubleTapUnlocked) {
            clicksCurent += 2;
            clicksTotal += 2;
        } else {
            clicksCurent++;
            clicksTotal++;
        }
        std::cout << "Bancnota aruncata\n";
        if (posibilUpgrade()) {
            aplicaUpgrade();
            std::cout << "Bancnota upgradata\n";
        }
    }
    void activeazaDoubleTap() {
        if (bancnotaCurenta.valoare1() > 1 && doubleTapUnlocked == false) {
            bancnotaCurenta.downgrade(1);
            clicksToUpgrade = bancnotaCurenta.valoare1() * 10;
            clicksCurent = 0;
            doubleTapUnlocked = true;
            doubleTapUpgradeCounter = 0;
            std::cout << "DoubleTap Activat\n";
        }
        else {
            std::cout << "Nu poti activa DoubleTap.";
        }
    }
    void dezactiveazaDoubleTap() {
        doubleTapUnlocked = false;
        doubleTapUpgradeCounter = 0;
        std::cout << "DoubleTap Deactivat\n";
    }
    [[maybe_unused]] void reset() {
        bancnotaCurenta = Bancnota(UN_LEU);
        clicksCurent = 0;
        clicksTotal = 0;
        level = 1;
        clicksToUpgrade = 10;
        doubleTapUnlocked = false;
    }
    [[maybe_unused]] [[nodiscard]] int getClicks() const { return clicksCurent; }
    [[nodiscard]] int getClicksTotal() const { return clicksTotal; }
    [[nodiscard]] int getLevel() const { return level; }
    [[nodiscard]] bool getDoubleTap() const {
        return doubleTapUnlocked;
    }
    friend std::ostream& operator<<(std::ostream& os, const Player& p) {
        os << "Nivel: " << p.level
           << ", Clickuri Curente: " << p.clicksCurent
           << ", Clickuri Total: " << p.clicksTotal
           << ", Bancnota: " << p.bancnotaCurenta
           << ", DoubleTap: " << (p.doubleTapUnlocked ? "DA" : "NU");
        return os;
    }
};

class Achievement {
private:
    std::string nume;
    std::string descriere;
    AchievementType tip;
    int prag;
    bool activat = false;
public:
    Achievement(const std::string& n, const std::string& d)
        : nume(n),
          descriere(d),
          tip(achievementType.at(n)),
          prag(Prag.at(tip)) {}
    void checkUnlock(const Player& p) {
        if (activat) return;
        switch (tip) {
            case AchievementType::CLICKS:
                if (p.getClicksTotal() >= prag) activat = true;
                break;
            case AchievementType::LEVEL:
                if (p.getLevel() >= prag) activat = true;
                break;
            case AchievementType::DOUBLE_TAP:
                if (p.getDoubleTap()) activat = true;
                break;
        }
    }
    [[nodiscard]] bool isUnlocked() const {
        return activat;
    }
    friend std::ostream& operator<<(std::ostream& os, const Achievement& a) {
        os << "Achievement: " << a.nume << " - " << a.descriere
           << " [" << (a.activat ? "UNLOCKED" : "LOCKED") << "]";
        return os;
    }
};

class Game {
private:
    Player player;
    std::vector<Achievement> achievements;
    bool running = true;
    void afiseazaMeniu() const {
        std::cout << "\n=== MENIU ===\n";
        std::cout << "1. Arunca o bancnota\n";
        std::cout << "2. Activeaza DoubleTap (downgrade bancnota)\n";
        std::cout << "3. Afiseaza starea jucatorului\n";
        std::cout << "4. Verifica Achievements\n";
        std::cout << "0. Iesire\n";
        std::cout << "Introdu optiunea: ";
    }
    void proceseazaOptiune(int optiune) {
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
public:
    void set_player(const Player &player) {
        this->player = player;
    }
    Player& getPlayer() { return player; }
    std::vector<Achievement>& getAchievements() { return achievements; }
    Game() : achievements({
            {"Click Master", "Ai dat 500 de clicks!"},
            {"Intermediate", "Ai ajuns la nivelul 3!"},
            {"Investor", "Ai activat DoubleTap!"}
        }) {}
    void run() {
        while (running) {
            afiseazaMeniu();
            int optiune;
            std::cin >> optiune;
            std::cin.ignore();
            proceseazaOptiune(optiune);
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode({800u, 600u}), sf::String("MoneyMaker"));

    sf::Font font;
    if (!font.openFromFile("assets/arial.ttf")) {
        std::cerr << "Eroare la încărcarea fontului\n";
        return 1;
    }

    Game game;

    std::vector<std::string> options = {
        "1. Arunca o bancnota",
        "2. Activeaza DoubleTap",
        "3. Afiseaza starea jucatorului",
        "4. Verifica Achievements",
        "0. Iesire"
    };

    std::vector<sf::Text> menuItems;
    for (int i = 0; i < options.size(); ++i) {
        sf::Text item(font, options[i], 28); // Constructor direct
        item.setFillColor(sf::Color::White);
        item.setPosition({100.f, 100.f + i * 60.f});
        menuItems.push_back(item);
    }

    bool running = true;
    while (window.isOpen() && running) {
        while (auto event = window.pollEvent()) {
            // Dacă e închidere fereastră
            if (event->is<sf::Event::Closed>()) {
                window.close();
                running = false;
                break;
            }

            // Dacă e click stânga
            if (const auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseEvent->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos(
                        static_cast<float>(mouseEvent->position.x),
                        static_cast<float>(mouseEvent->position.y)
                    );

                    for (int i = 0; i < menuItems.size(); ++i) {
                        if (menuItems[i].getGlobalBounds().contains(mousePos)) {
                            switch (i) {
                                case 0:
                                    game.getPlayer().aruncaBancnota();
                                    break;
                                case 1:
                                    game.getPlayer().activeazaDoubleTap();
                                    break;
                                case 2:
                                    std::cout << game.getPlayer() << '\n';
                                    break;
                                case 3:
                                    for (auto& ach : game.getAchievements()) {
                                        ach.checkUnlock(game.getPlayer());
                                        std::cout << ach << '\n';
                                    }
                                    break;
                                case 4:
                                    running = false;
                                    window.close();
                                    break;
                            }
                        }
                    }
                }
            }
        }

        window.clear(sf::Color(20, 20, 20));
        for (auto& item : menuItems)
            window.draw(item);
        window.display();
    }

    return 0;
}