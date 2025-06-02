#ifndef PLAYER_H
#define PLAYER_H

#include "Bancnota.h"
#include <iostream>
#include <vector>
#include "Observer.h"

class Player {
private:
    Bancnota bancnotaCurenta;
    int clicksCurent;
    int clicksTotal;
    int level;
    int clicksToUpgrade;
    bool doubleTapUnlocked;
    int doubleTapUpgradeCounter;


    std::vector<Observer*> observers;

    bool posibilUpgrade() const;
    void aplicaUpgrade();

public:
    Player();
    Player(int level, int clicksCurent, int clicksTotal, Bancnota tipBancnota, bool doubleTap);
    ~Player();


    void addObserver(Observer* obs);
    void notifyObservers() const;

    bool hasUsedBanknoteUpgrade = false;
    bool usedLevelUpgrade = false;

    bool getLevelUpgradeUsed() const;
    void setLevelUpgradeUsed(bool used);

    void primesteClickuri(int nr);
    void primesteBancnotaNoua(const Bancnota& b);

    bool getBanknoteUpgradeUsed() const;
    void setBanknoteUpgradeUsed(bool);

    void aruncaBancnota();
    void setClicks(int newClicks);
    void setBancnota(const Bancnota& b);
    void activeazaDoubleTap();
    void dezactiveazaDoubleTap();
    void aplicaBonusLevelUpgrade();
    void reset();

    int getClicks() const;
    int getClicksTotal() const;
    int getLevel() const;
    bool getDoubleTap() const;
    int getCurrentClickLimit() const;
    int getCurrentBanknoteValue() const;

    friend std::ostream& operator<<(std::ostream& os, const Player& p);
};

#endif