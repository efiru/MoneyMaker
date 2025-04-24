#ifndef LEVELUPGRADE_H
#define LEVELUPGRADE_H

#include "Upgrade.h"

class LevelUpgrade : public Upgrade {
public:
    LevelUpgrade();



    void aplica(Player &player) override;

    std::unique_ptr<Upgrade> clone() const override;

    void afiseaza() const override;
};

#endif