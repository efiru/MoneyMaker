#ifndef BANKNOTE_UPGRADE_H
#define BANKNOTE_UPGRADE_H

#include "Upgrade.h"

class BanknoteUpgrade : public Upgrade {
private:
    bool folosita;

public:
    BanknoteUpgrade();

    void aplica(Player& player) override;
    std::unique_ptr<Upgrade> clone() const override;
    void afiseaza() const override;
};

#endif