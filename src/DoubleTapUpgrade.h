#ifndef DOUBLETAPUPGRADE_H
#define DOUBLETAPUPGRADE_H

#include "Upgrade.h"

class DoubleTapUpgrade : public Upgrade {
public:
    DoubleTapUpgrade();

    void aplica(Player& player) override;

    std::unique_ptr<Upgrade> clone() const override;

    void afiseaza() const override;
};

#endif
