#ifndef UPGRADE_H
#define UPGRADE_H

#include <string>
#include <memory>
#include <utility>
#include "Player.h"

class Upgrade {
protected:
    std::string nume;

    public:
    explicit Upgrade(std::string nume) : nume(std::move(nume)) {}
    virtual ~Upgrade() = default;

    virtual void aplica(Player& player) = 0;

    virtual std::unique_ptr<Upgrade> clone() const = 0;

    virtual void afiseaza() const {
        std::cout << nume << std::endl;
    }

    const std::string getNume() const {
        return nume;
    }
};

#endif
