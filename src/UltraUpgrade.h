#ifndef ULTRAUPGRADE_H
#define ULTRAUPGRADE_H

#include "Upgrade.h"

class UltraUpgrade : public Upgrade {
    bool activat;

public:
    UltraUpgrade();

    void aplica(Player& player) override;
    std::unique_ptr<Upgrade> clone() const override;
    void afiseaza() const override;
};

#endif