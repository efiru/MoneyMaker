#ifndef PLAYER_H
#define PLAYER_H

#include "Bancnota.h"
#include <iostream>

class Player {
private:
    Bancnota bancnotaCurenta;
    int clicksCurent;
    int clicksTotal;
    int level;
    int clicksToUpgrade;
    bool doubleTapUnlocked;
    int doubleTapUpgradeCounter;

    bool posibilUpgrade() const;
    void aplicaUpgrade();

public:
    Player();
    Player(int level, int clicksCurent, int clicksTotal, Bancnota tipBancnota, bool doubleTap);
    ~Player();

    bool hasUsedBanknoteUpgrade = false;

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
