#include "Player.h"
#include "Observer.h"
#include <iostream>

Player::Player()
    : bancnotaCurenta(UN_LEU),
      clicksCurent(0),
      clicksTotal(0),
      level(1),
      clicksToUpgrade(10),
      doubleTapUnlocked(false),
      doubleTapUpgradeCounter(0) {}

Player::Player(int level, int clicksCurent, int clicksTotal, Bancnota tipBancnota, bool doubleTap)
    : bancnotaCurenta(tipBancnota),
      clicksCurent(clicksCurent),
      clicksTotal(clicksTotal),
      level(level),
      clicksToUpgrade(tipBancnota.valoare1() * 10),
      doubleTapUnlocked(doubleTap),
      doubleTapUpgradeCounter(0) {}

Player::~Player() = default;

bool Player::posibilUpgrade() const {
    return clicksCurent >= clicksToUpgrade;
}

bool Player::getLevelUpgradeUsed() const {
    return usedLevelUpgrade;
}

void Player::setLevelUpgradeUsed(bool used) {
    usedLevelUpgrade = used;
}

bool Player::getBanknoteUpgradeUsed() const {
    return hasUsedBanknoteUpgrade;
}

void Player::setBanknoteUpgradeUsed(bool used) {
    hasUsedBanknoteUpgrade = used;
}

void Player::aplicaUpgrade() {
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

void Player::primesteClickuri(int nr) {
    clicksCurent += nr;
    clicksTotal += nr;
    notifyObservers();
}

void Player::primesteBancnotaNoua(const Bancnota& b) {
    bancnotaCurenta = b;
}

void Player::addObserver(Observer* obs) {
    observers.push_back(obs);
}

void Player::notifyObservers() const {
    for (auto obs : observers) {
        if (obs)
            obs->update(*this);
    }
}

void Player::aruncaBancnota() {
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

void Player::setClicks(int newClicks) {
    clicksCurent = newClicks;
    notifyObservers();
}

void Player::setBancnota(const Bancnota& b) {
    bancnotaCurenta = b;
    clicksToUpgrade = bancnotaCurenta.valoare1() * 10;
    notifyObservers();
}

void Player::activeazaDoubleTap() {
    if (bancnotaCurenta.valoare1() > 1 && !doubleTapUnlocked) {
        bancnotaCurenta.downgrade(1);
        clicksToUpgrade = bancnotaCurenta.valoare1() * 10;
        clicksCurent = 0;
        doubleTapUnlocked = true;
        doubleTapUpgradeCounter = 0;
        notifyObservers();
        std::cout << "DoubleTap Activat\n";
    } else {
        std::cout << "Nu poti activa DoubleTap.\n";
    }
}

void Player::dezactiveazaDoubleTap() {
    doubleTapUnlocked = false;
    doubleTapUpgradeCounter = 0;
    notifyObservers();
    std::cout << "DoubleTap Deactivat\n";
}
void Player::aplicaBonusLevelUpgrade() {
    level++;
    notifyObservers();
    std::cout << "[BONUS] Ai primit un nivel bonus ca recompensă pentru progres!\n";
}

void Player::reset() {
    bancnotaCurenta = Bancnota(UN_LEU);
    clicksCurent = 0;
    clicksTotal = 0;
    level = 1;
    clicksToUpgrade = 10;
    doubleTapUnlocked = false;
    notifyObservers();
}

int Player::getClicks() const {
    return clicksCurent;
}

int Player::getClicksTotal() const {
    return clicksTotal;
}

int Player::getLevel() const {
    return level;
}

bool Player::getDoubleTap() const {
    return doubleTapUnlocked;
}

int Player::getCurrentClickLimit() const {
    return clicksToUpgrade;
}

int Player::getCurrentBanknoteValue() const {
    return bancnotaCurenta.valoare1();
}



std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << "Nivel: " << p.level
       << ", Clickuri Curente: " << p.clicksCurent
       << ", Clickuri Total: " << p.clicksTotal
       << ", Bancnota: " << p.bancnotaCurenta
       << ", DoubleTap: " << (p.doubleTapUnlocked ? "DA" : "NU");
    return os;
}